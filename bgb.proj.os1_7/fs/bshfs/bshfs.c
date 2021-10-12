#include <general.h>

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
u32 size_high;
u32 size_low;
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


struct fileinfo_s {
struct fileinfo_s *next;
struct volinfo_s *vol;
char *name;
VADDR *addr;
int handle;
int seq;

u32 offset;
u32 size;
};

struct volinfo_s {
struct volinfo_s *next;
VADDR *addr;
struct fileinfo_s *fileroot;
VFILE *sock;
};

int bshfs_cl_reqseq;

int bshfs_cl_recv_reqseq;
char *bshfs_cl_recv_value;
int bshfs_cl_recv_handle;
char *bshfs_cl_recv_msg;

int bshfs_cl_recv_sequence;
byte *bshfs_cl_recv_buffer;
int bshfs_cl_recv_bufsz;
int bshfs_cl_recv_offset;

struct volinfo_s *bshfs_cl_volroot;

char *BSHFS_GrabString(char **buf)
{
	int i;
	char *s, *t;

	s=*buf;
	i=*s++;
	t=kalloc(i+1);
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

int BSHFS_SendPacket(VADDR *to, struct volinfo_s *vol, int op,
	void *hdr, int hsz, void *data, int dsz)
{
	void *tbuf;
	char *t;

	tbuf=kalloc(4+hsz+dsz);

	*(short *)tbuf=htons(op);
	*(byte *)(tbuf+3)=hsz;

	if(hdr)memcpy(tbuf+4, hdr, hsz);
	if(data)memcpy(tbuf+4+hsz, data, dsz);

	vfsend(vol->sock, to, tbuf, 4+hsz+dsz, 0);

	kfree(tbuf);

	return(0);
}

int BSHFS_HandleInfoResponse(void *hdr, int hsz, void *data, int dsz,
	VADDR *from, struct volinfo_s *vol)
{
	struct info_request_s *info_req;
	char *name, *value, *s;
	char nbuf[64];

	info_req=(struct info_request_s *)hdr;
	s=hdr+4;
	name=BSHFS_GrabString(&s);

	switch(info_req->op)
	{
	case 0:
		bshfs_cl_recv_reqseq=ntohs(info_req->reqseq);
		bshfs_cl_recv_value=NULL;
		break;

	case 1:
		value=kalloc(dsz+1);
		memcpy(value, data, dsz);
		bshfs_cl_recv_reqseq=ntohs(info_req->reqseq);
		bshfs_cl_recv_value=value;
		break;
	default:
		break;
	}
	return(0);
}

int BSHFS_HandleOpenResponse(void *hdr, int hsz, void *data, int dsz,
	VADDR *from, struct volinfo_s *vol)
{
	struct open_response_s *open_resp;
	char *msg, *s;
	int i, j;

	open_resp=(struct open_response_s *)hdr;
	s=hdr+16;
	msg=BSHFS_GrabString(&s);
	i=ntohl(open_resp->handle);
	j=ntohl(open_resp->size_low);
	kprint("Open Response handle=%d, size=%d, msg='%s'\n", i, j, msg);

	bshfs_cl_recv_reqseq=ntohs(open_resp->reqseq);
	bshfs_cl_recv_handle=i;
	bshfs_cl_recv_offset=j;
	bshfs_cl_recv_msg=msg;

	return(0);
}

int BSHFS_HandleIOResponse(void *hdr, int hsz, void *data, int dsz,
	VADDR *from, struct volinfo_s *vol)
{
	struct io_request_s *io_resp;
	int i;
	byte *buffer;

	io_resp=(struct io_request_s *)hdr;
	i=ntohl(io_resp->handle);

//	kprint("IO Response handle=%d, type=%d\n", i, io_resp->type);

	if(dsz)
	{
		buffer=kalloc(dsz);
		memcpy(buffer, data, dsz);
	}else buffer=NULL;

	bshfs_cl_recv_sequence=ntohs(io_resp->sequence);
	bshfs_cl_recv_handle=i;
	bshfs_cl_recv_offset=htons(io_resp->offset_low);

	bshfs_cl_recv_buffer=buffer;
	bshfs_cl_recv_bufsz=dsz;

	return(0);
}

int BSHFS_HandlePacket(void *buf, int sz, VADDR *from, struct volinfo_s *vol)
{
	int op, hlen;

	op=ntohs(*(short *)buf);
	hlen=*(byte *)(buf+3);

	switch(op)
	{
	case 33:
		BSHFS_HandleOpenResponse(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from, vol);
		break;

	case 35:
		BSHFS_HandleIOResponse(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from, vol);
		break;

	case 39:
		BSHFS_HandleInfoResponse(buf+4, hlen,
			buf+4+hlen, sz-(4+hlen), from, vol);
		break;

	default:
		break;
	}
}

int BSHFS_Poll(struct volinfo_s *vol)
{
	byte *buf;
	VADDR *addr;
	int i;

	buf=kalloc(4096);
	addr=kalloc(sizeof(VADDR));

	while(1)
	{
//		NET_Poll();
		i=vfget(buf, 4096, addr, vol->sock);
		if(i<0)break;
		if(i>=0)
		{
//			kprint("got %d byte packet from %s\n",
//				i, NET_Addr2Str(addr));
			BSHFS_HandlePacket(buf, i, addr, vol);
		}
	}
	kfree(addr);
	kfree(buf);

	return(0);
}

char *BSHFS_GetInfo(VADDR *sv, struct volinfo_s *vol, char *name)
{
	byte *buf, *s;
	struct info_request_s *info_req;
	int st, ct, lt;
	int seq;


	buf=kalloc(256);
	info_req=(struct info_request_s *)buf;

	seq=bshfs_cl_reqseq++;
	seq&=0xffff;

	info_req->op=1;
	info_req->flags=0;
	info_req->reqseq=htons(seq);
	s=buf+4;
	s=BSHFS_PutString(s, name);

	bshfs_cl_recv_reqseq=-1;
	bshfs_cl_recv_value=NULL;

	BSHFS_SendPacket(sv, vol, 38, buf, (int)s-(int)buf, NULL, 0);

	kfree(buf);

	st=Sys_TimeMS();
	lt=st;
	while(1)
	{
#if 1
		ct=Sys_TimeMS();
		if((ct-st)>500)break;
		if((ct-lt)>100)
		{
			lt=ct;
			BSHFS_SendPacket(sv, vol, 38, buf, (int)s-(int)buf, NULL, 0);
		}
#endif
		BSHFS_Poll(vol);
		if(seq==bshfs_cl_recv_reqseq)break;
		kusleep(10000);
	}

	if(seq!=bshfs_cl_recv_reqseq)return(NULL);
	return(bshfs_cl_recv_value);
}

int BSHFS_OpenRemoteFile(VADDR *sv, struct volinfo_s *vol, char *name, char *access)
{
	byte *buf, *s;
	struct open_request_s *open_req;
	int st, ct, lt;
	int seq;

	buf=kalloc(256);
	open_req=(struct open_request_s *)buf;

	seq=bshfs_cl_reqseq++;
	seq&=0xffff;

	open_req->flags=0;
	open_req->reqseq=htons(seq);
	s=buf+4;
	s=BSHFS_PutString(s, name);
	s=BSHFS_PutString(s, access);

	bshfs_cl_recv_reqseq=-1;
	bshfs_cl_recv_value=NULL;

	BSHFS_SendPacket(sv, vol, 32, buf, (int)s-(int)buf, NULL, 0);

	kfree(buf);

	st=Sys_TimeMS();
	lt=st;
	while(1)
	{
#if 1
		ct=Sys_TimeMS();
		if((ct-st)>500)break;
		if((ct-lt)>100)
		{
			lt=ct;
			BSHFS_SendPacket(sv, vol, 38, buf, (int)s-(int)buf, NULL, 0);
		}
#endif
		BSHFS_Poll(vol);
		if(seq==bshfs_cl_recv_reqseq)break;
		kusleep(10000);
	}

	if(seq!=bshfs_cl_recv_reqseq)return(-1);
	return(bshfs_cl_recv_handle);
}

int BSHFS_IORemoteFile(VADDR *sv, struct volinfo_s *vol, int hdl, int op,
	int seq, int offs, void *data, int sz)
{
	byte *buf, *s;
	struct io_request_s *io_req;
	int i;
	int st, ct, lt;

	buf=kalloc(256);
	io_req=(struct io_request_s *)buf;

	io_req->type=op;
	io_req->flag=0;
	io_req->sequence=htons(seq);
	io_req->handle=htonl(hdl);
	io_req->offset_high=htonl((offs==-1)?-1:0);
	io_req->offset_low=htonl(offs);

	bshfs_cl_recv_sequence=-1;
	bshfs_cl_recv_handle=-1;
	bshfs_cl_recv_buffer=NULL;
	bshfs_cl_recv_bufsz=0;

	if(op==2)
		BSHFS_SendPacket(sv, vol, 34, buf, 16, data, sz);
		else BSHFS_SendPacket(sv, vol, 34, buf, 16, NULL, 0);

	kfree(buf);

	st=Sys_TimeMS();
	lt=st;
	while(1)
	{
#if 1
		ct=Sys_TimeMS();
		if((ct-st)>500)break;
		if((ct-lt)>100)
		{
			lt=ct;
			BSHFS_SendPacket(sv, vol, 38, buf, (int)s-(int)buf, NULL, 0);
		}
#endif
		BSHFS_Poll(vol);
		if((hdl==bshfs_cl_recv_handle) &&
			(seq==bshfs_cl_recv_sequence))break;
		kusleep(10000);
	}

	if(hdl!=bshfs_cl_recv_handle)return(-1);
	if(seq!=bshfs_cl_recv_sequence)return(-1);

	if(bshfs_cl_recv_buffer)
	{
		i=bshfs_cl_recv_bufsz;
		if(sz<i)i=sz;
		memcpy(data, bshfs_cl_recv_buffer, i);
		kfree(bshfs_cl_recv_buffer);
		bshfs_cl_recv_buffer=NULL;
		return(i);
	}

	return(0);
}

/* file abstraction */
struct fileinfo_s *BSHFS_CL_OpenFile(struct volinfo_s *vol,
	char *name, char *attr)
{
	struct fileinfo_s *tmp;
	int i;

	i=BSHFS_OpenRemoteFile(vol->addr, vol, name, attr);
	if(i<0)return(NULL);

	tmp=kalloc(sizeof(struct fileinfo_s));
	tmp->name=kstrdup(name);

	tmp->addr=kalloc(sizeof(VADDR));
	memcpy(tmp->addr, vol->addr, sizeof(VADDR));
	tmp->vol=vol;

	tmp->handle=i;
	tmp->seq=0;
	tmp->offset=0;
	tmp->size=bshfs_cl_recv_offset;

	tmp->next=vol->fileroot;
	vol->fileroot=tmp;

	return(tmp);
}

int BSHFS_CL_ReadFile(void *buf, int len, struct fileinfo_s *inf)
{
	int i, j, k;
	void *p;

	i=len;
	p=buf;
	while(i>0)
	{
		if(i>512)k=512;
			else k=i;

		j=BSHFS_IORemoteFile(inf->addr, inf->vol, inf->handle, 1,
			inf->seq, inf->offset, p, k);
		inf->seq++;
		inf->seq&=0xffff;

		inf->offset+=j;
		p+=j;
		i-=j;

		if((i>0) && (j<k))break;
	}
	return(len-i);
}

int BSHFS_CL_WriteFile(void *buf, int len, struct fileinfo_s *inf)
{
	int i, j, k;
	void *p;

	i=len;
	p=buf;
	while(i>0)
	{
		if(i>512)k=512;
			else k=i;

		j=BSHFS_IORemoteFile(inf->addr, inf->vol, inf->handle, 2,
			inf->seq, inf->offset, p, k);
		inf->seq++;
		inf->seq&=0xffff;

//		if((i>0) && !j)break;

		inf->offset+=k;
		p+=k;
		i-=k;
	}
	return(len-i);
}

int BSHFS_CL_SeekFile(struct fileinfo_s *inf, int offs, int rel)
{
	switch(rel)
	{
	case 0:
		inf->offset=offs;
		break;
	case 1:
		inf->offset+=offs;
		break;
	case 2:
		inf->offset=inf->size;
		break;
	default:
		break;
	}
	return(inf->offset);
}

int BSHFS_CL_CloseFile(struct fileinfo_s *inf)
{
	BSHFS_IORemoteFile(inf->addr, inf->vol, inf->handle, 3, inf->seq, 0, NULL, 0);
	inf->seq++;
	inf->seq&=0xffff;

	kfree(inf->name);
	kfree(inf->addr);
	kfree(inf);

	return(0);
}

/* VFILE wrapper */
int bshfs_cl_read(void *buf, int len, VFILE *fd)
{
	int i;
	struct fileinfo_s *inf;

	inf=fd->buffer;
	i=BSHFS_CL_ReadFile(buf, len, inf);

	return(i);
}

int bshfs_cl_write(void *buf, int len, VFILE *fd)
{
	int i;
	struct fileinfo_s *inf;

	inf=fd->buffer;
	i=BSHFS_CL_WriteFile(buf, len, inf);

	return(i);
}

int bshfs_cl_seek(VFILE *fd, int offs, int rel)
{
	int i;
	struct fileinfo_s *inf;

	inf=fd->buffer;
	i=BSHFS_CL_SeekFile(inf, offs, rel);

	return(i);
}

int bshfs_cl_tell(VFILE *fd)
{
	struct fileinfo_s *inf;

	inf=fd->buffer;
	return(inf->offset);
}

int bshfs_cl_inready(VFILE *fd)
{
	return(1);
}

int bshfs_cl_eof(VFILE *fd)
{
	struct fileinfo_s *inf;

	inf=fd->buffer;

	return(0);
}

int bshfs_cl_ioctl(VFILE *fd, int req, void *argp)
{
	int i;
	int stat;

	struct fileinfo_s *inf;

	inf=fd->buffer;

	switch(req&0xffff)
	{
	default:
		stat=-1;
		break;
	}

	return(stat);
}

int bshfs_cl_close(VFILE *fd)
{
	struct fileinfo_s *inf;

	inf=fd->buffer;

	BSHFS_CL_CloseFile(inf);
	vfdestroy(fd);

	return(0);
}

VFILE *BSHFS_CL_WrapFile(struct fileinfo_s *inf)
{
	VFILE *tmp;

	if(!inf)return(NULL);

	tmp=vfnew();
	tmp->buffer=inf;
	tmp->read_proc=&bshfs_cl_read;
	tmp->write_proc=&bshfs_cl_write;
	tmp->seek_proc=&bshfs_cl_seek;
	tmp->tell_proc=&bshfs_cl_tell;
	tmp->inready_proc=&bshfs_cl_inready;
	tmp->ioctl_proc=&bshfs_cl_ioctl;
	tmp->eof_proc=&bshfs_cl_eof;
	tmp->close_proc=&bshfs_cl_close;

	return(tmp);
}

#if 0
int BSHFS_Init()
{
	VADDR *addr;
	int i, j;
	char *s;
	char b[512];
	struct fileinfo_s *inf;
	VFILE *fd;

	NET_Init();

//	bshfs_cl_sock=UDP_OpenSocket(0);
	bshfs_cl_sock=vffopen("/devices/ipv4/udp");

	if(!bshfs_cl_sock)
	{
		kprint("open socket failed\n");
		return(-1);
	}

	addr=NET_Str2Addr("192.168.1.100:50000", PROTO_IPV4UDP);

	s=BSHFS_GetInfo(addr, "ServerID");
	if(s)kprint("Got SV ID '%s'\n", s);
		else kprint("failed get server id\n");

	s=BSHFS_GetInfo(addr, "ServerName");
	if(s)kprint("Got SV Name '%s'\n", s);
		else kprint("failed get server name\n");

#if 0
	inf=BSHFS_CL_OpenFile(addr, "cltst.txt", "w+b");
	s="This is a test(L1)\n";
	j=BSHFS_CL_WriteFile(s, strlen(s), inf);
	s="This is a test(L2)\n";
	j=BSHFS_CL_WriteFile(s, strlen(s), inf);
	s="This is a test(L3)\n";
	j=BSHFS_CL_WriteFile(s, strlen(s), inf);
	BSHFS_CL_CloseFile(inf);
#endif
	inf=BSHFS_CL_OpenFile(addr, "cltst.txt", "w+b");
	fd=BSHFS_CL_WrapFile(inf);

	s="This is another test(L1)\n";
	vfwrite(s, 1, strlen(s), fd);
	s="This is another test(L2)\n";
	vfwrite(s, 1, strlen(s), fd);
	s="This is another test(L3)\n";
	vfwrite(s, 1, strlen(s), fd);

	vfclose(fd);

//	while(1)
//	{
//		kusleep(100);
//	}

	return(0);
}
#endif

VDIR *bshfs_opend(char *name, VMOUNT *mnt)
{
	struct reg_driver_t *cur;
	VDIR *tmp;
	char *s, *t;

	return(NULL);

	tmp=kalloc(sizeof(VDIR));
	tmp->close=&kfree;
//	tmp->readdir=&bshfs_readdir;
//	tmp->data=drv_root->first;

	return(tmp);
}

VFILE *bshfs_openf(char *name, char *fl, VMOUNT *mnt)
{
	char *s;
	struct fileinfo_s *inf;
	VFILE *fd;

	s=name;
	while(*s=='/')s++;

	inf=BSHFS_CL_OpenFile(mnt->data, name, fl);
	fd=BSHFS_CL_WrapFile(inf);

	return(fd);
}

VMOUNT *bshfs_mount(char **options)
{
	VMOUNT *tmp;
	struct volinfo_s *vol;
	VADDR *addr;

	kprint("BSHFS_Mount: '%s'\n", options[0]);

	vol=kalloc(sizeof(struct volinfo_s));
	addr=NET_Str2Addr(options[0], PROTO_IPV4UDP);
	kprint("BSHFS_Mount: '%s'\n", NET_Addr2Str(addr));

	vol->addr=addr;
	vol->sock=vffopen("/devices/ipv4/udp", "r+b");

	tmp=kalloc(sizeof(VMOUNT));
	tmp->data=vol;

	tmp->unmount=&kfree;
	tmp->openf=&bshfs_openf;
	tmp->opend=&bshfs_opend;

	return(tmp);
}

int bshfs_init()
{
	Vfs_RegisterType("bshfs", &bshfs_mount);
	return(0);
}
