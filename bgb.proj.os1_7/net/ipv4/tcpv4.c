#include <general.h>

/*
RFC 793

                                    
    0                   1                   2                   3   
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Sequence Number                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Acknowledgment Number                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Data |           |U|A|P|R|S|F|                               |
   | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
   |       |           |G|K|H|T|N|N|                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Checksum            |         Urgent Pointer        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             data                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define TCP_STATE_LISTEN	1
#define TCP_STATE_SYNSENT	2
#define TCP_STATE_SYNRECIEVED	3
#define TCP_STATE_ESTABLISHED	4
#define TCP_STATE_FINWAIT1	5
#define TCP_STATE_FINWAIT2	6
#define TCP_STATE_CLOSEWAIT	7
#define TCP_STATE_CLOSING	8
#define TCP_STATE_LASTACK	9
#define TCP_STATE_TIMEWAIT	10
#define TCP_STATE_CLOSED	11

#define TCP_FLAG_FIN	1
#define TCP_FLAG_SYN	2
#define TCP_FLAG_RST	4
#define TCP_FLAG_PSH	8
#define TCP_FLAG_ACK	16
#define TCP_FLAG_URG	32

#define TCP_FLAG_TERMINAL	1	//close after all data sent
#define TCP_FLAG_WACTIVE	2	//tcp is handling sending

typedef struct tcp_datagram_s tcp_datagram;
typedef struct tcp_sockinfo_s tcp_sockinfo;

struct tcp_datagram_s {
tcp_datagram *next;
unsigned int from_addr;
unsigned int from_port;

int seq;
int ack;

int sz;
void *buffer;
};

struct tcp_sockinfo_s {
tcp_sockinfo *next;
tcp_sockinfo *first;	//list of children (listener sockets)
tcp_sockinfo *accept;	//list of to-be-accepted sockets
int port;
int state;
int flags;		//1&=terminal

unsigned int to_addr;
unsigned int to_port;

unsigned int base, end; //base of recieve window, end of window.
byte *recv_win;

unsigned int seq, ack, nxt; //base of send window, ack sent, next to be sent
byte *send_win;

kmutex *lock;
};

struct tcphead_s {
unsigned short src_port;
unsigned short dst_port;
unsigned int seq;

unsigned int ack;
unsigned short offs_flags;
unsigned short window;

unsigned short checksum;
unsigned short urgent;
};

struct ipheader_s {
byte ver_ihl;
byte tos;
short len;

short ident;
short flags_offs;

byte ttl;
byte protocol;
unsigned short crc;

unsigned int source;
unsigned int dest;
};

tcp_sockinfo *tcp_root;
byte *tcp_portmap;

int TCPv4_SetMapBit(int bit)
{
	tcp_portmap[bit>>3]|=128>>(bit&7);
	return(0);
}

int TCPv4_ClearMapBit(int bit)
{
	tcp_portmap[bit>>3]&=~(128>>(bit&7));
	return(0);
}

int TCPv4_AllocMapBit()
{
	int i, j;

	for(i=(1024/8); i<(65536/8); i++)
		if(tcp_portmap[i]!=0xff)break;
	if(i>=(65536/8))return(-1);

	for(j=0; j<8; j++)
		if(!(tcp_portmap[i]&(128>>j)))
	{
		TCPv4_SetMapBit((i<<3)+j);
		return((i<<3)+j);
	}

	return(-1);
}

int TCPv4_ComputeChecksum(struct ipheader_s *hdr, byte *data, int sz)
{
	int i;
	int ax;
	unsigned short *hsp;

	struct {
	unsigned int src;
	unsigned int dst;
	byte z;
	byte proto;
	unsigned short len;
	}phdr;

	phdr.src=hdr->source;
	phdr.dst=hdr->dest;
	phdr.z=0;
	phdr.proto=hdr->protocol;
	phdr.len=htons(sz);

	ax=0;

	hsp=(unsigned short *)&phdr;
	for(i=0; i<6; i++)
	{
		ax+=hsp[i];
		if(ax>0xffff)
		{
			ax++;
			ax&=0xffff;
		}
	}

	hsp=(unsigned short *)data;
	sz=(sz+1)>>1;
	for(i=0; i<sz; i++)
	{
		ax+=hsp[i];
		if(ax>0xffff)
		{
			ax++;
			ax&=0xffff;
		}
	}
	ax=(~ax)&0xffff;

	return(ax);
}

int TCPv4_SendResponse(int to_addr, int to_port, int from_port,
	int seq, int ack, int flags, int window,
	void *msg, int len)
{
	byte *dg, *buf;
	struct tcphead_s *hdr;
	int i, hsz;

	hsz=20;
	dg=IPV4_NewDatagram(len+hsz, 6, to_addr);
	buf=IPV4_DatagramBody(dg);
	hdr=(struct tcphead_s *)buf;

	hdr->src_port=htons(from_port);
	hdr->dst_port=htons(to_port);
	hdr->seq=htonl(seq);
	hdr->ack=htonl(ack);

	hdr->offs_flags=htons(((hsz/4)<<12)+flags);
	hdr->window=htons(window);
	hdr->urgent=0;

	if(msg)memcpy(buf+hsz, msg, len);

	hdr->checksum=0;

	hdr->checksum=
		TCPv4_ComputeChecksum((struct ipheader_s *)dg,
		buf, len+hsz);

	i=TCPv4_ComputeChecksum((struct ipheader_s *)dg,
		buf, len+hsz);

//	kprint("CRC=%d, CRC2=%d\n", hdr->checksum, i);

	kprint("Out TCP:\n");
	kprint("\tFROM=%d TO=%d\n",
		ntohs(hdr->src_port), ntohs(hdr->dst_port));
	kprint("\tSEQUENCE=%X ACKNOWLEGEMENT=%X\n",
		ntohl(hdr->seq), ntohl(hdr->ack));
//	kprint("\tOFFS=%d\n", (ntohs(hdr->offs_flags)>>12)*4);
	kprint("\tFLAGS=%X\n", ntohs(hdr->offs_flags)&4095);
//	kprint("\tWINDOW=%d\n", ntohs(hdr->window));
//	kprint("\tCHECKSUM=%d\n", ntohs(hdr->checksum));
//	kprint("\tURGENT=%d\n", ntohs(hdr->urgent));

	IPV4_SendDatagram(dg);
	return(0);
}

tcp_sockinfo *TCPv4_NewSocket(int port)
{
	tcp_sockinfo *tmp;

	if(!port)port=TCPv4_AllocMapBit();

	tmp=kalloc(sizeof(tcp_sockinfo));
	tmp->port=port;
	TCPv4_SetMapBit(port);

	tmp->state=TCP_STATE_CLOSED;
	tmp->lock=kmutex_new();

	tmp->next=tcp_root;
	tcp_root=tmp;

	return(tmp);
}

tcp_sockinfo *TCPv4_NewSocketAccept(tcp_sockinfo *parent, int port)
{
	tcp_sockinfo *tmp;

	if(!port)port=TCPv4_AllocMapBit();

	tmp=kalloc(sizeof(tcp_sockinfo));
	tmp->port=port;
	TCPv4_SetMapBit(port);

	tmp->state=TCP_STATE_CLOSED;
	tmp->lock=kmutex_new();

	tmp->next=parent->accept;
	parent->accept=tmp;

	return(tmp);
}

tcp_sockinfo *TCPv4_AcceptSocket(tcp_sockinfo *parent)
{
	tcp_sockinfo *tmp;

	tmp=parent->accept;
	if(!tmp)return(NULL);
	if(tmp->state!=TCP_STATE_ESTABLISHED)return(NULL);

	parent->accept=parent->accept->next;

	tmp->next=parent->first;
	parent->first=tmp;

	return(tmp);
}

tcp_sockinfo *TCPv4_UnlinkSocket(tcp_sockinfo *first, tcp_sockinfo *inf)
{
	tcp_sockinfo *cur, *lst;

	lst=NULL;
	cur=first;
	while(cur)
	{
		cur->first=TCPv4_UnlinkSocket(cur->first, inf);
		cur->accept=TCPv4_UnlinkSocket(cur->accept, inf);

		if(cur==inf)
		{
			if(lst)lst->next=cur->next;
				else first=cur->next;
			cur=cur->next;
			continue;
		}

		lst=cur;
		cur=cur->next;
	}

	return(first);
}

tcp_sockinfo *TCPv4_Connect(unsigned int addr, int port)
{
	tcp_sockinfo *tmp;

	tmp=TCPv4_NewSocket(0);

	tmp->state=TCP_STATE_SYNSENT;

	tmp->seq=Sys_TimeMS()<<10;
	tmp->ack=tmp->seq;
	tmp->send_win=kalloc(65536);

	tmp->to_addr=addr;
	tmp->to_port=port;

	TCPv4_SendResponse(addr, port, tmp->port,
		tmp->seq, 0, TCP_FLAG_SYN,
		0, NULL, 0);

	return(tmp);
}

int TCPv4_AcceptSegment(tcp_sockinfo *inf, struct tcphead_s *hdr, int sz)
{
#if 0
	msg=kalloc(sizeof(tcp_datagram));
	msg->from_addr=from;
	msg->from_port=ntohs(hdr->src_port);

	msg->sz=ntohs(hdr->len)-8;
	msg->buffer=kalloc(msg->sz);
	memcpy(msg->buffer, buf+8, msg->sz);

	if(cur->first)
	{
		msg->next=NULL;
		cur->last->next=msg;
		cur->last=msg;
	}else
	{
		msg->next=NULL;
		cur->first=msg;
		cur->last=msg;
	}
#endif
}

byte *TCPv4_GetData(struct tcphead_s *hdr)
{
	int offs;
	byte *buf;

	offs=(ntohs(hdr->offs_flags)>>12)*4;
	buf=((byte *)hdr)+offs;
	return(buf);
}

int TCPv4_HandleDatagramSock(tcp_sockinfo *inf,
	struct tcphead_s *hdr, int sz, int from)
{
	tcp_sockinfo *tmp;
	int fl, len, i;
	unsigned int seq;

	fl=ntohs(hdr->offs_flags)&4095;
	len=sz-((ntohs(hdr->offs_flags)>>12)*4);
	seq=ntohl(hdr->seq);

	switch(inf->state)
	{
	case TCP_STATE_CLOSED:
		kprint("TCP: closed state\n");
		if(fl&TCP_FLAG_RST)
		{
			kprint("TCP: dead\n");
			break;
		}
		TCPv4_SendResponse(from, ntohs(hdr->src_port),
			ntohs(hdr->dst_port),
			0, 0, TCP_FLAG_RST, 0, NULL, 0);
		break;
	case TCP_STATE_LISTEN:
		if(!(fl&TCP_FLAG_SYN))
		{
			kprint("TCP: Listener %d, no SYN\n", inf->port);
			TCPv4_SendResponse(from, ntohs(hdr->src_port),
				ntohs(hdr->dst_port),
				0, 0, TCP_FLAG_RST, 0, NULL, 0);
			break;
		}

		kprint("TCP: Listener %d, connect\n", inf->port);
//		tmp=inf;
		tmp=TCPv4_NewSocketAccept(inf, inf->port);

		tmp->to_addr=from;
		tmp->to_port=ntohs(hdr->src_port);

		tmp->state=TCP_STATE_SYNRECIEVED;

		tmp->seq=Sys_TimeMS()<<10;
		tmp->ack=tmp->seq;
		tmp->nxt=tmp->seq;
		tmp->send_win=kalloc(65536);

		tmp->base=ntohl(hdr->seq)+1;
		tmp->end=tmp->base;
		tmp->recv_win=kalloc(65536);

		TCPv4_SendResponse(from, ntohs(hdr->src_port), tmp->port,
			tmp->seq, tmp->end, TCP_FLAG_SYN|TCP_FLAG_ACK,
			0, NULL, 0);
		break;

	case TCP_STATE_SYNRECIEVED:
		if(!(fl&TCP_FLAG_ACK))
		{
			kprint("TCP: SynRecieved %d, no ACK\n", inf->port);
			TCPv4_SendResponse(from, ntohs(hdr->src_port),
				ntohs(hdr->dst_port),
				0, 0, TCP_FLAG_RST, 0, NULL, 0);
			break;
		}
		if(ntohl(hdr->ack)>(tmp->seq+65536))
		{
			kprint("TCP: SynRecieved %d, bad window\n", inf->port);
			break;
		}
		inf->state=TCP_STATE_ESTABLISHED;
		inf->to_addr=from;
		inf->to_port=ntohs(hdr->src_port);

		kprint("TCP: SynRecieved %d, connected %X:%d\n",
			inf->port, inf->to_addr, inf->to_port);

//		inf->seq=0;
		inf->ack=ntohl(hdr->ack);
//		memcpy(inf->send_win, inf->send_win+(inf->ack-inf->seq),
//			65536-(inf->ack-inf->seq));
		inf->seq=inf->ack;
		inf->nxt=inf->seq;

#if 0
		i=inf->nxt-inf->seq;
		if(i>0)
		{
			if(i>576)i=576;

			TCPv4_SendResponse(
				inf->to_addr, inf->to_port, inf->port,
				inf->seq, inf->end, TCP_FLAG_ACK,
				64512-(inf->end-inf->base),
				inf->send_win, i);
		}
#endif
//		inf->state=TCP_STATE_ESTABLISHED;

		break;

	case TCP_STATE_ESTABLISHED:
		if(fl&TCP_FLAG_FIN)
		{
			kprint("TCP: Established: connection close\n");
			TCPv4_SendResponse(from,
				ntohs(hdr->src_port), inf->port,
				inf->seq, inf->end,
				TCP_FLAG_ACK|TCP_FLAG_FIN,
				64512-(inf->end-inf->base), NULL, 0);
			inf->state=TCP_STATE_LASTACK;
			break;
		}
		if(fl&TCP_FLAG_RST)
		{
			kprint("TCP: Established: connection reset\n");
			inf->state=TCP_STATE_CLOSED;
			break;
		}
		if(fl&TCP_FLAG_ACK)
		{
			kprint("TCP: Established: Recieved ACK\n");
			if((ntohl(hdr->ack)>inf->ack) &&
				(ntohl(hdr->ack)<=inf->nxt))
			{
				inf->ack=ntohl(hdr->ack);
				memcpy(inf->send_win,
					inf->send_win+(inf->ack-inf->seq),
					65536-(inf->ack-inf->seq));
				inf->seq=inf->ack;

				inf->flags&=~TCP_FLAG_WACTIVE;

#if 1
				i=inf->nxt-inf->seq;
				if(i>576)i=576;

				if(i>0)
				{
					TCPv4_SendResponse(
						inf->to_addr, inf->to_port,
						inf->port,
						inf->seq, inf->end,
						TCP_FLAG_ACK,
						64512-(inf->end-inf->base),
						inf->send_win, i);
					inf->flags|=TCP_FLAG_WACTIVE;
				}
#endif
			}
		}

		kprint("TCP: recv %d bytes\n", len);
		kprint("TCP: SEQ=%X END=%X\n", seq, inf->end);

		if((seq==inf->end) && (len<(65536-(seq-inf->base))) && (len>0))
		{
			inf->end+=len;

			memcpy(inf->recv_win+(seq-inf->base),
				TCPv4_GetData(hdr), len);
		}

		i=inf->nxt-inf->seq;
		if(i>576)i=576;

		if((i>0) || (len>0))
		{
			if(i<0)i=0;
			TCPv4_SendResponse(from,
				ntohs(hdr->src_port), inf->port,
				inf->seq, inf->end, TCP_FLAG_ACK,
				64512-(inf->end-inf->base), inf->send_win, i);
			if(i>0)inf->flags|=TCP_FLAG_WACTIVE;
		}

		if(!i && (inf->flags&TCP_FLAG_TERMINAL))
		{
			TCPv4_SendResponse(from,
				ntohs(hdr->src_port), inf->port,
				inf->seq, inf->end,
				TCP_FLAG_ACK|TCP_FLAG_FIN,
				64512-(inf->end-inf->base), NULL, 0);
			inf->state=TCP_STATE_FINWAIT1;
		}
		break;

	case TCP_STATE_FINWAIT1:
	case TCP_STATE_FINWAIT2:
		if(fl&TCP_FLAG_FIN)
			inf->state=TCP_STATE_CLOSED;
			else inf->state=TCP_STATE_FINWAIT2;

		TCPv4_SendResponse(from,
			ntohs(hdr->src_port), inf->port,
			inf->seq, inf->end,
			TCP_FLAG_ACK,
			64512-(inf->end-inf->base), NULL, 0);

		if(inf->state==TCP_STATE_CLOSED)
		{
			tcp_root=TCPv4_UnlinkSocket(tcp_root, inf);

			if(inf->send_win)kfree(inf->send_win);
			if(inf->recv_win)kfree(inf->recv_win);
//			kfree(inf);
		}
		break;

	case TCP_STATE_LASTACK:
		inf->end+=len;

		TCPv4_SendResponse(from,
			ntohs(hdr->src_port), inf->port,
			inf->seq, inf->end+1, TCP_FLAG_ACK,
			64512-(inf->end-inf->base), NULL, 0);
		inf->state=TCP_STATE_CLOSED;
		break;

	case TCP_STATE_SYNSENT:
		if(!(fl&TCP_FLAG_SYN))
		{
			kprint("TCP: SynRecieved %d, no SYN\n", inf->port);
			TCPv4_SendResponse(from, ntohs(hdr->src_port),
				ntohs(hdr->dst_port),
				0, 0, TCP_FLAG_RST, 0, NULL, 0);
			break;
		}
		if(!(fl&TCP_FLAG_ACK))
		{
			kprint("TCP: SynRecieved %d, no ACK\n", inf->port);
			TCPv4_SendResponse(from, ntohs(hdr->src_port),
				ntohs(hdr->dst_port),
				0, 0, TCP_FLAG_RST, 0, NULL, 0);
			break;
		}

		inf->state=TCP_STATE_ESTABLISHED;
		inf->to_addr=from;
		inf->to_port=ntohs(hdr->src_port);

//		inf->seq=Sys_TimeMS()<<10;
//		inf->ack=inf->seq;
//		inf->send_win=kalloc(65536);

		inf->seq=ntohl(hdr->ack);
		inf->ack=ntohl(hdr->ack);

		inf->base=ntohl(hdr->seq)+1;
		inf->end=inf->base;
		inf->recv_win=kalloc(65536);

		TCPv4_SendResponse(from,
			ntohs(hdr->src_port), inf->port,
			inf->seq, inf->end, TCP_FLAG_ACK,
			0, NULL, 0);
		break;

	default:
		kprint("TCP: unknown state\n");
		TCPv4_SendResponse(from, ntohs(hdr->src_port),
			ntohs(hdr->dst_port),
			0, 0, TCP_FLAG_RST, 0, NULL, 0);
		break;
	}

	return(0);
}

int TCPv4_Dispatch(tcp_sockinfo *first, struct tcphead_s *hdr,
	int sz, int from, int port)
{
	tcp_sockinfo *cur;

	cur=first;
	while(cur)
	{
		if((cur->port==port) && (cur->to_addr==from)
			&& (cur->to_port==ntohs(hdr->src_port)))
		{
			kmutex_lock(cur->lock);
			kprint("TCP: handle connected\n");
			TCPv4_HandleDatagramSock(cur, hdr, sz, from);
			kmutex_unlock(cur->lock);
			break;
		}

		if((cur->port==port) && (cur->state==TCP_STATE_LISTEN))
		{
			kmutex_lock(cur->lock);

			if(!TCPv4_Dispatch(cur->first, hdr, sz, from, port))
			{
				kmutex_unlock(cur->lock);
				return(0);
			}
			if(!TCPv4_Dispatch(cur->accept, hdr, sz, from, port))
			{
				kmutex_unlock(cur->lock);
				return(0);
			}

			kprint("TCP: handle listener\n");
			TCPv4_HandleDatagramSock(cur, hdr, sz, from);
			kmutex_unlock(cur->lock);
			break;
		}
		cur=cur->next;
	}

	if(cur)return(0);
	return(-1);
}

int TCPv4_HandleDatagram(byte *buf, int sz, int from)
{
	struct tcphead_s *hdr;
	int port;

	hdr=(struct tcphead_s *)buf;

	kprint("TCP:\n");
	kprint("\tFROM=%d TO=%d\n",
		ntohs(hdr->src_port), ntohs(hdr->dst_port));
	kprint("\tSEQUENCE=%X ACKNOWLEGEMENT=%X\n",
		ntohl(hdr->seq), ntohl(hdr->ack));
//	kprint("\tOFFS=%d\n", (ntohs(hdr->offs_flags)>>12)*4);
	kprint("\tFLAGS=%X\n", ntohs(hdr->offs_flags)&4095);
//	kprint("\tWINDOW=%d\n", ntohs(hdr->window));
//	kprint("\tCHECKSUM=%d\n", ntohs(hdr->checksum));
//	kprint("\tURGENT=%d\n", ntohs(hdr->urgent));

	port=ntohs(hdr->dst_port);

	if(!TCPv4_Dispatch(tcp_root, hdr, sz, from, port))return(0);

	kprint("TCP: no sock\n");
	TCPv4_SendResponse(from, ntohs(hdr->src_port),
		ntohs(hdr->dst_port),
		0, ntohl(hdr->seq), TCP_FLAG_RST,
		64240, NULL, 0);

	return(0);
}

#if 0
int tcpv4_get(byte *buffer, int sz, VADDR *addr, VFILE *fd)
{
	tcp_sockinfo *inf;
	tcp_datagram *msg;
	int i;

	inf=fd->buffer;

	if(!inf->first)return(-1);
	msg=inf->first;
	inf->first=msg->next;
	if(!inf->first)inf->last=NULL;

	i=msg->sz;
	if(sz<i)i=sz;

	memcpy(buffer, msg->buffer, i);

	addr->proto=PROTO_IPV4TCP;
	addr->ipv4.flags=0;
	addr->ipv4.port=htons(msg->from_port);
	addr->ipv4.addr=htons(msg->from_addr);

	return(i);
}

int tcpv4_send(VFILE *fd, VADDR *targ, void *msg, int len, int flags)
{
	tcp_sockinfo *inf;
	byte *dg, *buf;
	struct tcphead_s *hdr;
	int i;

	inf=fd->buffer;

	i=ntohl(targ->ipv4.addr);
	dg=IPV4_NewDatagram(len+8, 17, i);
	buf=IPV4_DatagramBody(dg);
	hdr=(struct tcphead_s *)buf;

	hdr->src_port=htons(inf->port);
	hdr->dst_port=targ->ipv4.port;
	hdr->len=htons(len+8);
	hdr->checksum=0;	//need compute
//	IPV4_ComputeChecksum(buf, sz);

	memcpy(buf+8, msg, len);

	IPV4_SendDatagram(dg);
	return(0);
}
#endif

int tcpv4_write(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	tcp_sockinfo *inf;

	inf=fd->buffer;

	if(!len)return(0);

//	return(0);
	while(len)
	{
		i=inf->nxt-inf->seq;
		j=65536-i;

		if(!j)
		{
			kthread_blocked();
			continue;
		}

		kmutex_lock(inf->lock);

		if(len<j)j=len;

		memcpy(inf->send_win+i, buf, j);
		inf->nxt+=j;
		len-=j;

		k=inf->nxt-inf->seq;
		if(k>576)k=576;

		if(!(inf->flags&TCP_FLAG_WACTIVE))
		{
			TCPv4_SendResponse(
				inf->to_addr, inf->to_port, inf->port,
				inf->seq, inf->end, TCP_FLAG_ACK,
				64512-(inf->end-inf->base), inf->send_win, k);
			inf->flags|=TCP_FLAG_WACTIVE;
		}

		kmutex_unlock(inf->lock);
	}

	return(j);
}

int tcpv4_read(void *buf, int len, VFILE *fd)
{
	int i;
	tcp_sockinfo *inf;

	inf=fd->buffer;

	kmutex_lock(inf->lock);

	i=inf->end-inf->base;
	if(len<i)i=len;

	if(i>0)
	{
		memcpy(buf, inf->recv_win, i);
		memcpy(inf->recv_win, inf->recv_win+i, 65536-i);
		inf->base+=i;
	}

	kmutex_unlock(inf->lock);

	return(i);
}

int tcpv4_inready(VFILE *fd)
{
	int i;
	tcp_sockinfo *inf;

	inf=fd->buffer;

	kmutex_lock(inf->lock);

	i=inf->end-inf->base;
	if(i>0)return(1);

	kmutex_unlock(inf->lock);

	return(0);
}

int tcpv4_eof(VFILE *fd)
{
	tcp_sockinfo *inf;

	inf=fd->buffer;

	if(inf->state==TCP_STATE_CLOSED)return(1);
	return(0);
}

int tcpv4_ioctl(VFILE *fd, int req, void *argp)
{
	int i;
	int stat;

	tcp_sockinfo *inf, *inf2;
	struct {
	VFILE *fd;
	VADDR *addr;
	}*acc;

	inf=fd->buffer;

	kmutex_lock(inf->lock);

	switch(req&0xffff)
	{
	case IOCTL_ACCEPT:
		stat=0;
		acc=argp;
		acc->fd=NULL;

		inf2=TCPv4_AcceptSocket(inf);
		if(!inf2)break;

		acc->fd=TCPv4_WrapSocket(inf2);
		if(acc->addr)
		{
			acc->addr->proto=PROTO_IPV4TCP;
			acc->addr->ipv4.addr=htonl(inf2->to_addr);
			acc->addr->ipv4.port=htons(inf2->to_port);
		}
		break;
	default:
		stat=-1;
		break;
	}

	kmutex_unlock(inf->lock);

	return(stat);
}

int tcpv4_close(VFILE *fd)
{
	tcp_sockinfo *inf;

	inf=fd->buffer;

	inf->flags|=TCP_FLAG_TERMINAL;

//	tcp_root=TCPv4_UnlinkSocket(tcp_root, inf);

//	if(inf->send_win)kfree(inf->send_win);
//	if(inf->recv_win)kfree(inf->recv_win);
//	kfree(inf);

	vfdestroy(fd);

	return(0);
}

VFILE *TCPv4_WrapSocket(tcp_sockinfo *inf)
{
	VFILE *tmp;

	tmp=vfnew();
	tmp->buffer=inf;
	tmp->read_proc=&tcpv4_read;
	tmp->write_proc=&tcpv4_write;
	tmp->inready_proc=&tcpv4_inready;
	tmp->ioctl_proc=&tcpv4_ioctl;
	tmp->eof_proc=&tcpv4_eof;
	tmp->close_proc=&tcpv4_close;

	return(tmp);
}

VFILE *TCPv4_OpenSocketListen(int socknum)
{
	VFILE *tmp;
	tcp_sockinfo *inf;

	inf=TCPv4_NewSocket(socknum);
	inf->state=TCP_STATE_LISTEN;

	tmp=vfnew();
	tmp->buffer=inf;
	tmp->ioctl_proc=&tcpv4_ioctl;
	tmp->eof_proc=&tcpv4_eof;
	tmp->close_proc=&tcpv4_close;

	return(tmp);
}

VFILE *TCP_OpenListen(int port)
{
	VFILE *fd;
	fd=TCPv4_OpenSocketListen(port);
	return(fd);
}

VFILE *TCPv4_OpenSocketConnect(int addr, int port)
{
	VFILE *tmp;
	tcp_sockinfo *inf;

	inf=TCPv4_Connect(addr, port);

	tmp=vfnew();
	tmp->buffer=inf;
	tmp->read_proc=&tcpv4_read;
	tmp->write_proc=&tcpv4_write;
	tmp->inready_proc=&tcpv4_inready;
	tmp->ioctl_proc=&tcpv4_ioctl;
	tmp->eof_proc=&tcpv4_eof;
	tmp->close_proc=&tcpv4_close;

	return(tmp);
}

VFILE *TCP_OpenConnect(VADDR *addr)
{
	VFILE *fd;
	fd=TCPv4_OpenSocketConnect(ntohl(addr->ipv4.addr),
		ntohs(addr->ipv4.port));
	return(fd);
}

VFILE *tcpv4_open_listen(char *name, void *data)
{
	VFILE *tmp;
	int port;
	char *s;

	kprint("TCPv4_OpenListen\n");
	s=Driver_ExtractArg(name, "port");
	if(s)
	{
//		kprint("\tport='%s'\n", s);
		port=katoi(s);
	}else port=0;

	kprint("\tport=%d\n", port);

	tmp=TCPv4_OpenSocketListen(port);

	return(tmp);
}

VFILE *tcpv4_open_connect(char *name, void *data)
{
	VFILE *tmp;
	int addr, port;
	char *s;

	kprint("TCPv4_OpenConnect\n");
	s=Driver_ExtractArg(name, "host");
	if(s)
	{
//		kprint("\thost='%s'\n", s);
		addr=0;

		addr<<=8;
		addr+=katoi(s);
		while(*s && (*s!='.'))s++;
		if(*s)s++;

		addr<<=8;
		addr+=katoi(s);
		while(*s && (*s!='.'))s++;
		if(*s)s++;

		addr<<=8;
		addr+=katoi(s);
		while(*s && (*s!='.'))s++;
		if(*s)s++;

		addr<<=8;
		addr+=katoi(s);
		while(*s && (*s!='.'))s++;
		if(*s)s++;
	}else
	{
		kprint("TCP: OpenConnect: no host\n");
		return(NULL);
	}

	s=Driver_ExtractArg(name, "port");
	if(s)
	{
//		kprint("\tport='%s'\n", s);
		port=katoi(s);
	}else
	{
		kprint("TCP: OpenConnect: no port\n");
		return(NULL);
	}

	kprint("\thost=%X port=%d\n", addr, port);

	tmp=TCPv4_OpenSocketConnect(addr, port);

	return(tmp);
}
int TCPv4_Init()
{
	tcp_sockinfo *inf;

	kprint("TCPv4_Init\n");

	tcp_portmap=kalloc(65536/8);
	tcp_root=NULL;

	inf=TCPv4_NewSocket(23);
	inf->state=TCP_STATE_LISTEN;

//	TCPv4_Connect(0xC0A80164, 80);

	Driver_RegisterStream("ipv4/tcp/listen", &tcpv4_open_listen, NULL);
	Driver_RegisterStream("ipv4/tcp/connect", &tcpv4_open_connect, NULL);

	return(0);
}
