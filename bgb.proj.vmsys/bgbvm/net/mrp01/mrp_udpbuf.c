#include <general.h>

typedef struct udpbuf_packet_s {
struct udpbuf_packet_s *next;
int seq;
int size; //size of packet
byte *buf, *bufe; //pointers to packet buffer
}udpbuf_packet;

typedef struct {
VFILE *sock;
VADDR *addr;
int conid; //conid of other end
int this_conid;
int this_seq; //sequence number on this end
int that_seq; //sequence number of other end, to ignore duplicates
int ping, last; //ping and last send attempt
udpbuf_packet *send;
udpbuf_packet *recv;

int cnt;
byte *buf, *bufe;
}udpbuf_inf;

udpbuf_inf *udpbuf_conns[1024];

udpbuf_inf *udpbuf_constack[1024];
int udpbuf_constack_pos=0;

VFILE *udpbuf_listen=NULL;

int UDPBUF_AllocCon()
{
	int i;

	for(i=1; i<1024; i++)if(!udpbuf_conns[i])
	{
		udpbuf_conns[i]=malloc(sizeof(udpbuf_inf));
		memset(udpbuf_conns[i], 0, sizeof(udpbuf_inf));
		udpbuf_conns[i]->this_conid=i;
		return(i);
	}
	return(0);
}

udpbuf_packet *UDPBUF_AllocPacket(int size)
{
	udpbuf_packet *tmp;

	tmp=malloc(sizeof(udpbuf_packet));
	tmp->next=NULL;
	tmp->seq=0;

	tmp->size=size;
	tmp->buf=malloc(size);
	tmp->bufe=tmp->buf;

	return(tmp);
}

int UDPBUF_SendPacket(udpbuf_inf *con, udpbuf_packet *msg)
{
	vfsend(con->sock, con->addr, msg->buf, msg->bufe-msg->buf, 0);
	return(0);
}

int UDPBUF_SendConnect(int conid)
{
	udpbuf_inf *con;
	byte tmp[8];

	con=udpbuf_conns[conid];

	tmp[0]='M';
	tmp[1]='R';
	tmp[2]='P';
	tmp[3]=1;

	tmp[4]=0x00;

	tmp[5]=(conid>>16)&0xff;
	tmp[6]=(conid>>8)&0xff;
	tmp[7]=conid&0xff;

	vfsend(con->sock, con->addr, tmp, 8, 0);

	return(0);
}

int UDPBUF_HandleConnect(VFILE *sock, VADDR *from, byte *buf, int sz)
{
	udpbuf_inf *con;
	int i;
	byte tmp[12];

	if(buf[4]!=0x00)
	{
		tmp[0]='M';
		tmp[1]='R';
		tmp[2]='P';
		tmp[3]=2;

		tmp[4]=2;
		tmp[5]=0;

		tmp[6]=buf[5];
		tmp[7]=buf[6];
		tmp[8]=buf[7];

		tmp[9]=0x00;
		tmp[10]=0x00;
		tmp[11]=0x00;

		vfsend(sock, from, tmp, 12, 0);

		free(buf);
		free(from);

		return(0);
	}

	i=UDPBUF_AllocCon();
	con=udpbuf_conns[i];

	udpbuf_constack[udpbuf_constack_pos++]=con;

	con->sock=sock;
	con->addr=from;
	con->conid=(buf[5]<<16)+(buf[6]<<8)+buf[7];
	con->ping=500;

	con->buf=malloc(8192);
	con->bufe=con->buf;

	con->this_seq=1;

	tmp[0]='M';
	tmp[1]='R';
	tmp[2]='P';
	tmp[3]=2;

	tmp[4]=1;
	tmp[5]=0;

	tmp[6]=buf[5];
	tmp[7]=buf[6];
	tmp[8]=buf[7];

	tmp[9]=(i>>16)&0xff;
	tmp[10]=(i>>8)&0xff;
	tmp[11]=i&0xff;

	vfsend(sock, from, tmp, 12, 0);

	free(buf);

	return(0);
}

int UDPBUF_HandleConnectReply(VFILE *sock, VADDR *from, byte *buf, int sz)
{
	udpbuf_inf *con;
	int conid, i;

	switch(buf[4])
	{
	case 1:
		conid=(buf[6]<<16)+(buf[7]<<8)+buf[8];
		con=udpbuf_conns[conid];
		i=(buf[9]<<16)+(buf[10]<<8)+buf[11];
		con->conid=i;
		con->this_seq=1;
		break;
	case 2:
		conid=(buf[6]<<16)+(buf[7]<<8)+buf[8];
		con=udpbuf_conns[conid];
		free(con);
		udpbuf_conns[conid]=NULL;
		break;
	default:
		break;
	}

	free(from);
	free(buf);

	return(0);
}

int UDPBUF_SendAck(int conid, int seq, int stamp)
{
	udpbuf_inf *con;
	byte tmp[14];

//	kprint("SEND ACK %d %d\n", seq, stamp);

	con=udpbuf_conns[conid];

	tmp[0]='M';
	tmp[1]='R';
	tmp[2]='P';
	tmp[3]=4;

	tmp[4]=(con->conid>>16)&0xff;
	tmp[5]=(con->conid>>8)&0xff;
	tmp[6]=con->conid&0xff;

	tmp[7]=(conid>>16)&0xff;
	tmp[8]=(conid>>8)&0xff;
	tmp[9]=conid&0xff;

	tmp[10]=(seq>>8)&0xff;
	tmp[11]=seq&0xff;

	tmp[12]=(stamp>>8)&0xff;
	tmp[13]=stamp&0xff;

	vfsend(con->sock, con->addr, tmp, 14, 0);

	return(0);
}

int UDPBUF_HandleData(VFILE *sock, VADDR *from, byte *buf, int sz)
{
	udpbuf_inf *con;
	udpbuf_packet *msg, *cur;
	int conid, i, j;

	conid=(buf[4]<<16)+(buf[5]<<8)+buf[6];
	con=udpbuf_conns[conid];

	if(!con)
	{
		kprint("UDPBUF: DATA: invalid conn %d\n", conid);
		return(-1);
	}

	i=(buf[10]<<8)+buf[11];
	j=(buf[12]<<8)+buf[13];

//	kprint("DATA: %d %d\n", i, j);

	if(i!=((con->that_seq+1)&0xffff))
	{
		if(i==con->that_seq)
			UDPBUF_SendAck(conid, i, j);
		free(from);
		free(buf);
		return(0);
	}

	UDPBUF_SendAck(conid, i, j);
	con->that_seq=i;

	msg=UDPBUF_AllocPacket(sz-14);
	msg->seq=i;
	memcpy(msg->buf, buf+14, sz-14);

	free(from);
	free(buf);

	if(!con->recv)
	{
		con->recv=msg;
		return(0);
	}

	cur=con->recv;
	while(cur->next)cur=cur->next;
	cur->next=msg;
	return(0);
}

int UDPBUF_HandleAck(VFILE *sock, VADDR *from, byte *buf, int sz)
{
	udpbuf_inf *con;
	int conid, i, j, k;

	conid=(buf[4]<<16)+(buf[5]<<8)+buf[6];
	con=udpbuf_conns[conid];

	if(!con)
	{
		kprint("UDPBUF: ACK: invalid conn %d\n", conid);
		return(-1);
	}

	i=(buf[10]<<8)+buf[11];
	j=(buf[12]<<8)+buf[13];

//	kprint("ACK: %d %d\n", i, j);

	if(con->send)if(con->send->seq==i)
	{
		con->send=con->send->next;
		k=Sys_TimeMS()&0xffff;
		if(k<j)k+=65536;
		con->ping=k-j;
		con->last=0;

		kprint("UDP PING %d t:%d\n", con->ping, Sys_TimeMS());

		UDPBUF_TrySend(conid);
	}
	return(0);
}

int UDPBUF_HandlePacket(VFILE *sock, VADDR *from, byte *buf, int sz)
{
	if((buf[0]!='M') || (buf[1]!='R') || (buf[2]!='P'))
	{
		free(from);
		free(buf);
		return(0);
	}

	switch(buf[3])
	{
	case 0:
		free(from);
		free(buf);
		break;
	case 1:
		UDPBUF_HandleConnect(sock, from, buf, sz);
		break;
	case 2:
		UDPBUF_HandleConnectReply(sock, from, buf, sz);
		break;
	case 3:
		UDPBUF_HandleData(sock, from, buf, sz);
		break;
	case 4:
		UDPBUF_HandleAck(sock, from, buf, sz);
		break;
	default:
		free(from);
		free(buf);
		break;
	}
	return(0);
}

int UDPBUF_WriteData(int conid, byte *buf, int sz)
{
	udpbuf_inf *con;
	udpbuf_packet *msg, *cur;

	con=udpbuf_conns[conid];

	msg=UDPBUF_AllocPacket(sz);
	msg->seq=con->this_seq;
	memcpy(msg->buf, buf, sz);

	con->this_seq=(con->this_seq+1)&0xffff;

	if(!con->send)
	{
		con->send=msg;
		return(0);
	}

	cur=con->send;
	while(cur->next)cur=cur->next;
	cur->next=msg;
	return(0);
}

int UDPBUF_TrySend(int conid)
{
	udpbuf_inf *con;
	udpbuf_packet *msg;
	byte *buf;
	int i;

	con=udpbuf_conns[conid];
	if(!con)return(0);
	msg=con->send;
	i=Sys_TimeMS();

	if(!msg)return(0);
	if(((i-con->last)<(con->ping*1.5)) && con->last)
		return(0);
//	if(((i-con->last)<500) && con->last)
//		return(0);
	con->last=i;

	kprint("SEND DATA %d %d t:%d\n", msg->seq, i&0xffff, Sys_TimeMS());

	buf=malloc(msg->size+14);
	memcpy(buf+14, msg->buf, msg->size);

	buf[0]='M';
	buf[1]='R';
	buf[2]='P';
	buf[3]=3;

	buf[4]=(con->conid>>16)&0xff;
	buf[5]=(con->conid>>8)&0xff;
	buf[6]=con->conid&0xff;

	buf[7]=(conid>>16)&0xff;
	buf[8]=(conid>>8)&0xff;
	buf[9]=conid&0xff;

	buf[10]=(msg->seq>>8)&0xff;
	buf[11]=msg->seq&0xff;

	buf[12]=(i>>8)&0xff;
	buf[13]=i&0xff;

	vfsend(con->sock, con->addr, buf, msg->size+14, 0);

	return(0);
}

int UDPBUF_ConnectCon(VADDR *to)
{
	udpbuf_inf *con;
	VADDR *addr;
	int i;

	addr=malloc(sizeof(VADDR));
	memcpy(addr, to, sizeof(VADDR));

	i=UDPBUF_AllocCon();
	con=udpbuf_conns[i];

	con->sock=udpbuf_listen;
	con->addr=addr;

	con->ping=500;

	con->buf=malloc(8192);
	con->bufe=con->buf;

	UDPBUF_SendConnect(i);

	return(i);
}

int UDPBUF_PollSock(VFILE *sock)
{
	int sz;
	byte *buf;
	VADDR *addr;
	int i;

//	kprint("UDPBUF Poll Sock {\n");

	for(i=1; i<1024; i++)UDPBUF_TrySend(i);

//	kprint("UDPBUF Poll Sock: Send\n");

	while(1)
	{
//		kprint("a\n");
		addr=malloc(sizeof(VADDR));
		buf=malloc(8192);
//		kprint("b\n");
		sz=vfget(buf, 8192, addr, sock);
//		kprint("c\n");
		if(sz==-1)break;

//		kprint("UDPBUF Poll Sock: Packet %d\n", sz);

		UDPBUF_HandlePacket(sock, addr, buf, sz);
	}

	free(addr);
	free(buf);

//	kprint("UDPBUF Poll Sock }\n");

	return(0);
}

int UDPBUF_Poll()
{
	return(UDPBUF_PollSock(udpbuf_listen));
}

int UDPBUF_Init()
{
	memset(udpbuf_conns, 0, 1024*sizeof(udpbuf_inf *));
}

/* VFILE interface */

int vf_udpbuf_read(void *buf, int sz, VFILE *sock)
{
	udpbuf_inf *con;
	udpbuf_packet *cur, *cur2;
	int i, j;

	i=0;

	UDPBUF_Poll();

	con=sock->buffer;
	cur=con->recv;
	while(cur && sz)
	{
		j=cur->size-(cur->bufe-cur->buf);
		j=(j<sz)?j:sz;

		memcpy(buf, cur->bufe, j);
		cur->bufe+=j;
		sz-=j;
		i+=j;

		if((cur->bufe-cur->buf)>=cur->size)
		{
			cur2=cur->next;
//			free(cur->buf);
//			free(cur);
			cur=cur2;
		}
	}

	if(i)kprint("udpbuf_read: got %d\n", i);
	con->recv=cur;
	return(i);
}

int vf_udpbuf_write(void *msg, int len, VFILE *sock)
{
	udpbuf_inf *inf;
	int i;

//	kprint("UDPBUF: write %d\n", len);

	inf=sock->buffer;

	inf->cnt+=len;

	i=inf->bufe-inf->buf;
	if((i+len)<4096)
	{
		memcpy(inf->bufe, msg, len);
		inf->bufe+=len;
		return(len);
	}

	i=inf->bufe-inf->buf;
	if(i)UDPBUF_WriteData(inf->this_conid, inf->buf, i);
	inf->bufe=inf->buf;

	UDPBUF_WriteData(inf->this_conid, msg, len);

	return(i);
}

int vf_udpbuf_flush(VFILE *sock)
{
	udpbuf_inf *inf;
	int i;

	UDPBUF_Poll();

	inf=sock->buffer;

	i=inf->bufe-inf->buf;
	if(i)
	{
		UDPBUF_WriteData(inf->this_conid, inf->buf, i);
		UDPBUF_TrySend(inf->this_conid);

//		UDPBUF_Poll();

		inf->bufe=inf->buf;

		kprint("UDPBUF flush: %d bytes t:%d\n", inf->cnt, Sys_TimeMS());
		inf->cnt=0;
	}

	return(0);
}

int vf_udpbuf_ioctls(VFILE *fd, void **arg)
{
	char *s;
	udpbuf_inf *inf;
	int i, j;

	inf=fd->buffer;

	s=*arg;
	if(!strcmp(s, "accept"))
	{
		if(!udpbuf_constack_pos)
		{
			*(VFILE **)arg[1]=NULL;
			return(0);
		}

		udpbuf_constack_pos--;
		inf=udpbuf_constack[udpbuf_constack_pos];

		*(VFILE **)arg[1]=(VFILE *)UDPBUF_WrapCon(inf);
		memcpy((VADDR *)arg[2], inf->addr, sizeof(VADDR));

		return(0);
	}

	if(!strcmp(s, "can-write?"))
	{
		i=(*(int *)arg[1])*1000;
		j=Sys_TimeMS();
		while(((Sys_TimeMS()-j)<i) && !inf->conid)
			UDPBUF_Poll();
		if(!inf->conid)
		{
			*(int *)arg[1]=0;
			return(0);
		}
		*(int *)arg[1]=-1;
		return(0);
	}

	return(-1);
}


VFILE *UDPBUF_WrapCon(udpbuf_inf *inf)
{
	VFILE *tmp;

	tmp=vfnew();
	tmp->buffer=inf;

	tmp->read_proc=&vf_udpbuf_read;
	tmp->write_proc=&vf_udpbuf_write;
	tmp->ioctls_proc=&vf_udpbuf_ioctls;
	tmp->flush_proc=&vf_udpbuf_flush;

	return(tmp);
}

VFILE *UDPBUF_OpenListen(int port)
{
	VFILE *tmp;

	if(!udpbuf_listen)
		udpbuf_listen=(VFILE *)UDP_OpenSocket(port);

	tmp=vfnew();
	tmp->buffer=NULL;

//	tmp->read_proc=&vf_udpbuf_read;
//	tmp->write_proc=&vf_udpbuf_write;
	tmp->ioctls_proc=&vf_udpbuf_ioctls;
//	tmp->flush_proc=&vf_udpbuf_flush;

	return(tmp);
}

VFILE *UDPBUF_OpenConnect(VADDR *targ)
{
	udpbuf_inf *con;
	VFILE *tmp;
	int i;

	i=UDPBUF_ConnectCon(targ);
	con=udpbuf_conns[i];

	tmp=vfnew();
	tmp->buffer=con;

	tmp->read_proc=&vf_udpbuf_read;
	tmp->write_proc=&vf_udpbuf_write;
	tmp->ioctls_proc=&vf_udpbuf_ioctls;
	tmp->flush_proc=&vf_udpbuf_flush;

	return(tmp);
}
