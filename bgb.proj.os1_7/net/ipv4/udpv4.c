#include <general.h>

/*
RFC 768
*/

typedef struct udp_datagram_s udp_datagram;
typedef struct udp_sockinfo_s udp_sockinfo;

struct udp_datagram_s {
udp_datagram *next;
unsigned int from_addr;
unsigned int from_port;

int sz;
void *buffer;
};

struct udp_sockinfo_s {
udp_sockinfo *next;
int port;
udp_datagram *first, *last;
};

struct udphead_s {
unsigned short src_port;
unsigned short dst_port;
unsigned short len;
unsigned short checksum;
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

udp_sockinfo *udp_root;
byte *udp_portmap;

int UDPv4_SetMapBit(int bit)
{
	udp_portmap[bit>>3]|=128>>(bit&7);
	return(0);
}

int UDPv4_ClearMapBit(int bit)
{
	udp_portmap[bit>>3]&=~(128>>(bit&7));
	return(0);
}

int UDPv4_AllocMapBit()
{
	int i, j;

	for(i=(1024/8); i<(65536/8); i++)
		if(udp_portmap[i]!=0xff)break;
	if(i>=(65536/8))return(-1);

	for(j=0; j<8; j++)
		if(!(udp_portmap[i]&(128>>j)))
	{
		UDPv4_SetMapBit((i<<3)+j);
		return((i<<3)+j);
	}

	return(-1);
}

int UDPv4_HandleDatagram(byte *buf, int sz, int from)
{
	struct udphead_s *hdr;
	udp_sockinfo *cur;
	udp_datagram *msg;
	int port;

	hdr=(struct udphead_s *)buf;
//	kprint("UDP: SRC=%d DST=%d LEN=%d CRC=%d\n",
//		ntohs(hdr->src_port), ntohs(hdr->dst_port),
//		ntohs(hdr->len), ntohs(hdr->checksum));

	port=ntohs(hdr->dst_port);

	cur=udp_root;
	while(cur)
	{
		if(cur->port==port)
		{
			msg=kalloc(sizeof(udp_datagram));
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
			break;
		}
		cur=cur->next;
	}

	return(0);
}

udp_sockinfo *UDPv4_NewSocket(int port)
{
	udp_sockinfo *tmp;

	tmp=kalloc(sizeof(udp_sockinfo));
	tmp->port=port;
	UDPv4_SetMapBit(port);

	tmp->next=udp_root;
	udp_root=tmp;

	return(tmp);
}

int udpv4_get(byte *buffer, int sz, VADDR *addr, VFILE *fd)
{
	udp_sockinfo *inf;
	udp_datagram *msg;
	int i;

	inf=fd->buffer;

	if(!inf->first)return(-1);
	msg=inf->first;
	inf->first=msg->next;
	if(!inf->first)inf->last=NULL;

	i=msg->sz;
	if(sz<i)i=sz;

	memcpy(buffer, msg->buffer, i);

	addr->proto=PROTO_IPV4UDP;
	addr->ipv4.flags=0;
	addr->ipv4.port=htons(msg->from_port);
	addr->ipv4.addr=htonl(msg->from_addr);

	return(i);
}

int udpv4_send(VFILE *fd, VADDR *targ, void *msg, int len, int flags)
{
	udp_sockinfo *inf;
	byte *dg, *buf;
	struct udphead_s *hdr;
	int i;

	inf=fd->buffer;

	i=ntohl(targ->ipv4.addr);
	dg=IPV4_NewDatagram(len+8, 17, i);
	buf=IPV4_DatagramBody(dg);
	hdr=(struct udphead_s *)buf;

	hdr->src_port=htons(inf->port);
	hdr->dst_port=targ->ipv4.port;
	hdr->len=htons(len+8);
	hdr->checksum=0;	//need compute

//	hdr->checksum=
//		TCPv4_ComputeChecksum((struct ipheader_s *)dg,
//		buf, len+8);

//	IPV4_ComputeChecksum(buf, sz);

	memcpy(buf+8, msg, len);

	IPV4_SendDatagram(dg);
	return(0);
}

VFILE *UDPv4_OpenSocket(int socknum)
{
	VFILE *tmp;
	udp_sockinfo *inf;

	if(!socknum)socknum=UDPv4_AllocMapBit();
	inf=UDPv4_NewSocket(socknum);

	tmp=vfnew();
	tmp->buffer=inf;

	tmp->get_proc=&udpv4_get;
	tmp->send_proc=&udpv4_send;
//	tmp->getaddr=&udpsock_getaddr;

	return(tmp);
}

VFILE *udpv4_open(char *name, void *data)
{
	VFILE *tmp;
	int port;
	char *s;

	kprint("UDPv4_Open\n");
	s=Driver_ExtractArg(name, "port");
	if(s)
	{
		kprint("\tport='%s'\n", s);
		port=katoi(s);
	}else port=0;

	kprint("\tport=%d\n", port);

	tmp=UDPv4_OpenSocket(port);

	return(tmp);
}

int UDPv4_Init()
{
	kprint("UDPv4_Init\n");

	udp_portmap=kalloc(65536/8);

	Driver_RegisterStream("ipv4/udp", &udpv4_open, NULL);

	return(0);
}
