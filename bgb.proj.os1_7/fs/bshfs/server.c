#include <pdlib.h>

typedef unsigned short u16;
typedef unsigned int u32;

struct open_request_s {
u16 flags; //none, 1&=dir
u16 reqseq; //request sequence, sync requests/responses
//string name; //file name
//string access; //access, same as for fopen
};

struct open_response_s {
u32 handle; //file handle, -1(0xffffffff) for error
u16 reqseq; //request sequence from the original request
u16 error_code;
//string error_text; //description of error
};

struct io_request_s {
byte type; //1=read, 2=write, 3=close
byte flag; //none
u16 sequence; //sequence number
u32 handle;
u32 offset_high;
u32 offset_low; //wtf not?...
};

struct dirop_request_s {
byte type; //1=readdir, 2=mkdir, 3=delete
byte flag; //none
u16 sequence; //sequence number
u32 handle;
};

struct info_request_s {
byte op; //1=request
byte flags; //none
u16 reqseq; //request sequence, sync requests/responses
//string name; //name of requested property
};


struct open_file_s {
char *name;
FILE *fd;
};

VFILE *bshfs_sock;
struct open_file_s *bshfs_files[1024];

int BSHFS_OpenFile(char *name, char *attr)
{
	FILE *fd;
	int i;

	while(*name=='/')name++;

	for(i=0; i<1024; i++)
		if(!bshfs_files[i])
	{
		fd=fopen(name, attr);
		if(!fd)return(-1);

		bshfs_files[i]=malloc(sizeof(struct open_file_s));
		memset(bshfs_files[i], 0, sizeof(struct open_file_s));

		bshfs_files[i]->name=strdup(name);
		bshfs_files[i]->fd=fd;

		return(i);
	}
	return(-1);
}

char *BSHFS_GrabString(char **buf)
{
	int i;
	char *s, *t;

	s=*buf;
	i=*s++;
	t=malloc(i+1);
	memset(t, 0, i+1);
	memcpy(t, s, i);
	s+=i;
	*buf=s;
	return(t);
}

char *BSHFS_PutString(char *buf, char *s)
{
	int i;

	i=strlen(s);
	*buf++=i;
	memcpy(buf, s, i);
	buf+=i;

	return(buf);
}

int BSHFS_SendPacket(VADDR *to, int op,
	void *hdr, int hsz, void *data, int dsz)
{
	void *tbuf;
	char *t;

	tbuf=malloc(4+hsz+dsz);

	*(short *)tbuf=htons(op);
	*(byte *)(tbuf+3)=hsz;

	if(hdr)memcpy(tbuf+4, hdr, hsz);
	if(data)memcpy(tbuf+4+hsz, data, dsz);

	vfsend(bshfs_sock, to, tbuf, 4+hsz+dsz, 0);
	return(0);
}

int BSHFS_HandleOpenReq(void *hdr, int hsz, void *data, int dsz, VADDR *from)
{
	char *name, *attr, *s, *t;
	void *tbuf;
	int i;

	struct open_request_s *open_req;
	struct open_response_s *open_rep;

	open_req=(struct open_request_s *)hdr;
	s=hdr+4;
	name=BSHFS_GrabString(&s);
	attr=BSHFS_GrabString(&s);

	printf("Open '%s' '%s'\n", name, attr);

	i=BSHFS_OpenFile(name, attr);

	tbuf=malloc(256);
	open_rep=(struct open_request_s *)tbuf;
	t=tbuf+8;

	open_rep->handle=htonl(i);
	open_rep->reqseq=open_req->reqseq;
	if(i<0)
	{
		open_rep->error_code=1;
		t=BSHFS_PutString(t, "Open Failed");
	}else
	{
		open_rep->error_code=0;
		t=BSHFS_PutString(t, "OK");
	}

	BSHFS_SendPacket(from, 33, tbuf, (int)t-(int)tbuf, NULL, 0);

	return(0);
}

int BSHFS_HandleIOReq(void *hdr, int hsz, void *data, int dsz, VADDR *from)
{
	struct io_request_s *io_req;
	int hdl, offs, i;
	byte *buf;

	io_req=(struct io_request_s *)hdr;

	hdl=ntohl(io_req->handle);
	if(hdl<0)
	{
		printf("BSHFS: client used bad handle\n");
		io_req->type=0;
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		return(0);
	}
	if(!bshfs_files[hdl])
	{
		printf("BSHFS: client used non-open handle\n");
		io_req->type=0;
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		return(0);
	}
	if(ntohl(io_req->offset_high))
	{
		printf("BSHFS: client io past 4GB mark\n");
		io_req->type=0;
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		return(0);
	}
	offs=ntohl(io_req->offset_low);

	switch(io_req->type)
	{
	case 1:
		buf=malloc(512);
		fseek(bshfs_files[hdl]->fd, offs, 0);
		i=fread(buf, 1, 512, bshfs_files[hdl]->fd);
		BSHFS_SendPacket(from, 35, hdr, hsz, buf, i);
		break;
	case 2:
		fseek(bshfs_files[hdl]->fd, offs, 0);
		fwrite(data, 1, dsz, bshfs_files[hdl]->fd);
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		break;
	case 3:
		fclose(bshfs_files[hdl]->fd);
		free(bshfs_files[hdl]);
		bshfs_files[hdl]=NULL;
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		break;
	default:
		printf("BSHFS_HandleIOReq: bad operation\n");
		io_req->type=0;
		BSHFS_SendPacket(from, 35, hdr, hsz, NULL, 0);
		break;
	}
	return(0);
}

int BSHFS_HandleInfoReq(void *hdr, int hsz, void *data, int dsz, VADDR *from)
{
	struct info_request_s *info_req;
	char *name, *value, *s;
	char nbuf[64];

	info_req=(struct info_request_s *)hdr;
	s=hdr+4;
	name=BSHFS_GrabString(&s);

	switch(info_req->op)
	{
	case 1:
		value=NULL;
		if(!strcmp(name, "ServerID"))
			value="BGB SharedFS SV0/0.1";
		if(!strcmp(name, "ServerName"))
		{
			gethostname(nbuf, 64);
			value=nbuf;
		}
		if(!value)
		{
			info_req->op=0;
			value="Unknown Variable";
			BSHFS_SendPacket(from, 39, hdr, hsz, value, strlen(value));
			break;
		}
		BSHFS_SendPacket(from, 39, hdr, hsz, value, strlen(value));
		break;
	default:
		info_req->op=0;
		value="Unknown Request OP";
		BSHFS_SendPacket(from, 39, hdr, hsz, value, strlen(value));
		break;
	}
	return(0);
}

int BSHFS_HandlePacket(void *buf, int sz, VADDR *from)
{
	int op, hlen;

	op=ntohs(*(short *)buf);
	hlen=*(byte *)(buf+3);

	switch(op)
	{
	case 32:
		BSHFS_HandleOpenReq(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from);
		break;

	case 34:
		BSHFS_HandleIOReq(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from);
		break;

	case 38:
		BSHFS_HandleInfoReq(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from);
		break;

	default:
		break;
	}
}

int main()
{
	byte *buf;
	VADDR addr;
	int i;

	ObjType_Init();

	Var_Init();

	NET_Init();

	memset(&bshfs_files, 0, 1024*sizeof(void *));

	bshfs_sock=UDP_OpenSocket(50000);
	if(!bshfs_sock)
	{
		kprint("open socket failed\n");
		return(-1);
	}

	buf=kalloc(4096);

	while(1)
	{
		NET_Poll();
		i=vfget(buf, 4096, &addr, bshfs_sock);
		if(i>=0)
		{
			kprint("got %d byte packet from %s\n",
				i, NET_Addr2Str(&addr));
			BSHFS_HandlePacket(buf, i, &addr);
//			vfsend(sock, &addr, buf, i, 0); //bounce
		}
		usleep(100);
	}

	return(0);
}
