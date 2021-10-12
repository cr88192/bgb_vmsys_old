#include <general.h>
#include <net/ipv6.h>

VFILE *ipv6_routefd;
ipv6_routent *ipv6_routetab;

static int ipv6_cmpaddr(byte *saddr, byte *daddr, int mask)
{
	byte *s, *t;
	int i;

	s=saddr;
	t=daddr;
	i=mask;
	while(i>8)
	{
		if(*s!=*t)return(0);
		s++;
		t++;
		i-=8;
	}
	if(i)
	{
		i=~((1<<i)-1);
		if((*s&i)!=(*t&i))return(0);
	}
	return(1);
}

int IPV6_RoutePacket(void *msg, int len, int flags)
{
	ipv6_routent *cur, *best;
	ipv6_header *head;

	switch(flags&0xff)
	{
	case PROTO_PF_IPV6:
		head=msg;

		best=NULL;
		cur=ipv6_routetab;
		while(cur)
		{
			if(ipv6_cmpaddr(msg->dest_addr, cur->this->ipv6.addr, cur->this->flags&0xff))
			{
				if(best)
				{
					if((cur->this->ipv6.flags&0xff)>(best->this->ipv6.flags&0xff))
						best=cur;
				}else best=cur;
			}
			cur=cur->next;
		}
		if(best)return(vfsend(best->vfd, NULL, msg, len, flags));
			else kprint("IPV6_RoutePacket: no route found\n");
		break;
	default:
		kprint("IPV6_RoutePacket: unknown packet type\n");
		break;
	}
	return(0);
}

static int ipv6_send(VFILE *sock, VADDR *target, void *msg, int len, int flags)
{
	return(IPV6_RoutePacket(msg, len, flags));
}

static VFILE *ipv6_open(char *name, void *data)
{
	return(ipv6_routefd);
}

int IPV6_Init()
{
	kprint("ipv6 init.\n");

	Driver_RegisterStream("net/ipv6", &ipv6_open, NULL);

	routetab=NULL;

	ipv6_routefd=vfnew();
	ipv6_routefd->send_proc=ipv6_send;
}
