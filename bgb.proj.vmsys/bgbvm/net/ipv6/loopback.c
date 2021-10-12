#include <general.h>
#include <net/ipv6.h>

VFILE *ipv6_lofd;

int IPV6LO_DecodePacket(void *msg, int len, int flags)
{
	ipv6_header *head;
	byte *s;

	switch(flags&0xff)
	{
	case PROTO_PF_IPV6:
		kprint("IPV6LO_DecodePacket: IPV6 head\n");
		head=msg;
		s=msg+40;
		return(IPV6LO_DecodePacket(s, len-40, head->next_header));
		break;
	case PROTO_PF_TCP:
		kprint("IPV6LO_DecodePacket: tcp head\n");
		break;
	case PROTO_PF_UDP:
		kprint("IPV6LO_DecodePacket: udp head\n");
		break;
	}
}

static int ipv6lo_send(VFILE *sock, VADDR *target, void *msg, int len, int flags)
{
	return(IPV6_RoutePacket(msg, len, flags));
}

static VFILE *ipv6lo_open(char *name, void *data)
{
	return(ipv6_lofd);
}

int IPV6_Init()
{
	kprint("ipv6 init.\n");

	Driver_RegisterStream("net/ipv6/lo", &ipv6lo_open, NULL);

	ipv6_lofd=vfnew();
	ipv6_lofd->send_proc=ipv6lo_send;
}
