#include <general.h>

/*
	RFC826

    Ethernet transmission layer (not necessarily accessible to
	 the user):
	48.bit: Ethernet address of destination
	48.bit: Ethernet address of sender
	16.bit: Protocol type = ether_type$ADDRESS_RESOLUTION
    Ethernet packet data:
	16.bit: (ar$hrd) Hardware address space (e.g., Ethernet,
			 Packet Radio Net.)
	16.bit: (ar$pro) Protocol address space.  For Ethernet
			 hardware, this is from the set of type
			 fields ether_typ$<protocol>.
	 8.bit: (ar$hln) byte length of each hardware address
	 8.bit: (ar$pln) byte length of each protocol address
	16.bit: (ar$op)  opcode (ares_op$REQUEST | ares_op$REPLY)
	nbytes: (ar$sha) Hardware address of sender of this
			 packet, n from the ar$hln field.
	mbytes: (ar$spa) Protocol address of sender of this
			 packet, m from the ar$pln field.
	nbytes: (ar$tha) Hardware address of target of this
			 packet (if known).
	mbytes: (ar$tpa) Protocol address of target.
*/

typedef struct ArpAddress_s ArpAddress;

struct arp_header_s {
unsigned short hw_type;
unsigned short pr_type;
unsigned char hw_addr_len;
unsigned char pr_addr_len;
unsigned short op;
};

struct ArpAddress_s {
ArpAddress *next;
int proto;
int hln, pln;
byte hw_addr[16];
byte pr_addr[16];
};

ArpAddress *arp_root;

extern byte ethernet_mac[6];
extern int ipv4_addr;

int ARP_ProtoSup(int proto)
{
	int i;
	switch(proto)
	{
	case 0x0800:
		i=1;
		break;
	defualt:
		i=0;
		break;
	}
	return(i);
}

int ARP_ProtoLen(int proto)
{
	int i;
	switch(proto)
	{
	case 0x0800:
		i=4;
		break;
	defualt:
		i=0;
		break;
	}
	return(i);
}

int ARP_AmTarget(int proto, byte *addr)
{
	int i, j;
	switch(proto)
	{
	case 0x0800:
		j=ntohl(*(int *)addr);
		if(j==ipv4_addr)i=1;
			else i=0;
		break;
	defualt:
		i=0;
		break;
	}
	return(i);
}

byte *ARP_AddrPtr(int proto)
{
	int i, j;
	byte *buf;

	switch(proto)
	{
	case 0x0800:
		buf=kralloc(4);
		*(int *)buf=htonl(ipv4_addr);
		break;
	defualt:
		buf=NULL;
		break;
	}
	return(buf);
}

char *ARP_Addr2Str(byte *addr, int l)
{
	int i, j, k;
	char *buf;

	buf=kralloc(l*2+1);

	for(i=0; i<l; i++)
	{
		j=addr[i];

		k=(j>>4)&0xf;
		if(k<10)k=k+'0';
			else k=k-10+'A';
		buf[(i*2)]=k;

		k=j&0xf;
		if(k<10)k=k+'0';
			else k=k-10+'A';
		buf[(i*2)+1]=k;

		buf[(i*2)+2]=0;
	}

	return(buf);
}

int ARP_AddrEq(byte *a, byte *b, int l)
{
	int i;
	for(i=0; i<l; i++)if(a[i]!=b[i])return(0);
	return(1);
}

int ARP_UpdateCache(int proto, int hln, byte *sha, int pln, byte *spa)
{
	ArpAddress *cur;

	cur=arp_root;
	while(cur)
	{
		if(ARP_AddrEq(spa, cur->pr_addr, pln) && (cur->proto==proto))
		{
			memcpy(cur->hw_addr, sha, hln);
			return(0);
		}
		cur=cur->next;
	}

	return(-1);
}

int ARP_InsertCache(int proto, int hln, byte *sha, int pln, byte *spa)
{
	ArpAddress *cur;
	int i;

	i=ARP_UpdateCache(proto, hln, sha, pln, spa);
	if(!i)return(0);

	cur=kalloc(sizeof(ArpAddress));
	cur->proto=proto;
	cur->hln=hln;
	cur->pln=pln;
	memcpy(cur->hw_addr, sha, hln);
	memcpy(cur->pr_addr, spa, pln);

	cur->next=arp_root;
	arp_root=cur;

	return(0);
}

byte *ARP_LookupCache2(int proto, byte *addr)
{
	ArpAddress *cur;
	byte *buf;
	int pln;

	pln=ARP_ProtoLen(proto);
	if(!pln)return(NULL);

	cur=arp_root;
	while(cur)
	{
		if(ARP_AddrEq(addr, cur->pr_addr, pln) && (cur->proto==proto))
		{
			buf=kralloc(cur->hln);
			memcpy(buf, cur->hw_addr, cur->hln);
			return(buf);
		}
		cur=cur->next;
	}

	return(NULL);
}

byte *ARP_LookupCache(int proto, byte *addr)
{
	byte *buf;
	int pln, t, t2;

	pln=ARP_ProtoLen(proto);
	if(!pln)return(NULL);

	buf=ARP_LookupCache2(proto, addr);
	if(buf)return(buf);

	ARP_Request(proto, pln, addr);

	t=Sys_TimeMS();
	while((Sys_TimeMS()-t)<250)
	{
		buf=ARP_LookupCache2(proto, addr);
		if(buf)return(buf);
		Ethernet_Poll();
		kthread_blocked();
	}

	return(buf);
}

int ARP_Request(int proto, int pln, byte *tpa)
{
	byte *buf;
	struct arp_header_s *hdr;
	byte *s;
	int hln;

	hln=6;

	buf=kralloc(48);
	hdr=buf;
	s=buf+8;

	hdr->hw_type=htons(1);
	hdr->pr_type=htons(proto);
	hdr->hw_addr_len=hln;
	hdr->pr_addr_len=pln;

	hdr->op=htons(1);

	memcpy(s, ethernet_mac, hln);
	s+=hln;
	memcpy(s, ARP_AddrPtr(proto), pln);
	s+=pln;

	memset(s, 0, hln);
	s+=hln;
	memcpy(s, tpa, pln);
	s+=pln;

	s=kralloc(8);
	memset(s, 255, 6);

	Ethernet_Send(s, 0x806, buf, 46);

	return(0);
}

int ARP_Reply(int proto, int hln, byte *tha, int pln, byte *tpa)
{
	byte *buf;
	struct arp_header_s *hdr;
	byte *s;

	buf=kralloc(48);
	hdr=buf;
	s=buf+8;

	hdr->hw_type=htons(1);
	hdr->pr_type=htons(proto);
	hdr->hw_addr_len=hln;
	hdr->pr_addr_len=pln;

	hdr->op=htons(2);

	memcpy(s, ethernet_mac, hln);
	s+=hln;
	memcpy(s, ARP_AddrPtr(proto), pln);
	s+=pln;

	memcpy(s, tha, hln);
	s+=hln;
	memcpy(s, tpa, pln);
	s+=pln;

	Ethernet_Send(tha, 0x806, buf, 46);

	return(0);
}

int ARP_HandlePacket(byte *buf, int sz)
{
	struct arp_header_s *hdr;
	byte *s;
	int proto, op;
	int hln, pln;
	byte *sha, *spa;
	byte *tha, *tpa;

	hdr=(struct arp_header_s *)buf;

	proto=ntohs(hdr->pr_type);
	op=ntohs(hdr->op);
	hln=hdr->hw_addr_len;
	pln=hdr->pr_addr_len;

	s=buf+8;

	sha=s;
	s+=hln;
	spa=s;
	s+=pln;

	tha=s;
	s+=hln;
	tpa=s;
	s+=pln;

//	kprint("ARP:\n");
//	kprint("\tHW=%d, PROTO=%d\n",
//		ntohs(hdr->hw_type), proto);
//	kprint("\tHW_ADDR_LEN=%d, PROTO_ADDR_LEN=%d\n", hln, pln);
//	kprint("\tOP=%d\n", ntohs(hdr->op));

//	kprint("\tSender-HW-Addr=%s\n", ARP_Addr2Str(sha, hln));
//	kprint("\tSender-Proto-Addr=%s\n", ARP_Addr2Str(spa, pln));
//	kprint("\tReciever-HW-Addr=%s\n", ARP_Addr2Str(tha, hln));
//	kprint("\tReciever-Proto-Addr=%s\n", ARP_Addr2Str(tpa, pln));

	if(!ARP_ProtoSup(proto))return(-1);

	ARP_UpdateCache(proto, hln, sha, pln, spa);

	if(!ARP_AmTarget(proto, tpa))return(0);

	ARP_InsertCache(proto, hln, sha, pln, spa);

	if(op!=1)return(0);

	ARP_Reply(proto, hln, sha, pln, spa);

	return(0);
}
