#include <general.h>

/*
RFC 791

    0                   1                   2                   3   
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

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

unsigned int ipv4_addr=0xC0A801FE;

int IPV4_ComputeChecksum(void *data, int sz)
{
	int i;
	int ax;
	unsigned short *hsp;

	hsp=data;

	sz=(sz+1)>>1;
	ax=0;
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

byte *IPV4_NewDatagram(int sz, int protocol, int dst)
{
	byte *buf;
	struct ipheader_s *hdr;

//	if(dst==ipv4_addr)
//	{
//		kprint("IPv4: self directed packet\n");
//		return(NULL);
//	}

	buf=kalloc(sz+20);
	hdr=(struct ipheader_s *)buf;

	hdr->ver_ihl=(4<<4)+5;
	hdr->len=htons(sz+20);
	hdr->ttl=128;
	hdr->protocol=protocol;

	hdr->source=htonl(ipv4_addr);
	hdr->dest=htonl(dst);

	return(buf);
}

byte *IPV4_DatagramBody(byte *buffer)
{
	struct ipheader_s *hdr;
	int ihl;

	hdr=(struct ipheader_s *)buffer;
	ihl=(hdr->ver_ihl&0xf)*4;

	return(buffer+ihl);
}

int IPV4_SendDatagram(byte *buffer)
{
	struct ipheader_s *hdr;
	int i, ihl, ax;
	int sz;
	byte *mac;

	hdr=(struct ipheader_s *)buffer;

	ihl=(hdr->ver_ihl&0xf)*4;
	sz=ntohs(hdr->len);

//	kprint("IPv4_SendDatagram: sz=%d\n", sz);

	//compute ip header checksum
	hdr->crc=0;
	ax=IPV4_ComputeChecksum(buffer, ihl);
	hdr->crc=ax;

//	kprint("IPv4_SendDatagram: checksum=%d\n", ax);

	//send over ethernet
	mac=ARP_LookupCache(0x0800, &hdr->dest);
	if(!mac)
	{
		kprint("IPV4_SendDatagram: failed resolve %X\n",
			ntohl(hdr->dest));
		return(-1);
	}
	Ethernet_Send(mac, 0x0800, buffer, sz);
	return(0);
}

int IPV4_HandleDatagram(byte *buffer, int sz)
{
	struct ipheader_s *hdr;
	int ihl, len;

	hdr=(struct ipheader_s *)buffer;
//	kprint("tag=%X\n", hdr->ver_ihl);
	if(((hdr->ver_ihl>>4)&0xf)!=4)
	{
		kprint("non-ipv4 datagram\n");
		return(-1);
	}
	ihl=(hdr->ver_ihl&0xf)*4;

	len=ntohs(hdr->len);

//	kprint("IPv4:\n");
//	kprint("\tIHL=%d\n", ihl);

//	kprint("\tTOS=%d\n", hdr->tos);
//	kprint("\tLEN=%d\n", ntohs(hdr->len));
//	kprint("\tIDENT=%d\n", ntohs(hdr->ident));
//	kprint("\tFLAGS=%d\n", ntohs(hdr->flags_offs)>>13);
//	kprint("\tOFFS=%d\n", ntohs(hdr->flags_offs)&0x1fff);
//	kprint("\tTTL=%d\n", hdr->ttl);
//	kprint("\tPROTOCOL=%d\n", hdr->protocol);
//	kprint("\tCRC=%d\n", ntohs(hdr->crc));

//	kprint("\tSRC=%X\n", ntohl(hdr->source));
//	kprint("\tDST=%X\n", ntohl(hdr->dest));

//	if(ntohl(hdr->dest)==ipv4_addr)
//		kprint("IPv4: SRC=%X DST=%X LEN=%d PROTOCOL=%d\n",
//		ntohl(hdr->source), ntohl(hdr->dest),
//		ntohs(hdr->len), hdr->protocol);

//	if(ntohl(hdr->dest)!=ipv4_addr)
//	{
//		kprint("IPv4: misdirected packet\n");
//		return(-1);
//	}

	switch(hdr->protocol)
	{
	case 1:
		ICMPv4_HandleMessage(buffer+ihl, len-ihl, ntohl(hdr->source));
		break;
	case 6:
		TCPv4_HandleDatagram(buffer+ihl, len-ihl, ntohl(hdr->source));
		break;
	case 17:
		UDPv4_HandleDatagram(buffer+ihl, len-ihl, ntohl(hdr->source));
		break;
	default:
		break;
	}
	return(0);
}

int IPV4_Init()
{
	kprint("IPV4_Init\n");
	UDPv4_Init();
	TCPv4_Init();

	return(0);
}
