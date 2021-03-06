#include <pdlib.h>
#include <pdnet.h>

#if 0
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <errno.h>
#endif

#include <windows.h>
#include <winsock.h>

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif

#if 0
unsigned long local_ipv4addr;

#ifdef CONF_USEIPV6
byte local_ipv6addr[16];
#endif

char *ipv4tostr(unsigned long addr)
{
	unsigned long addrc;
	static char buf[4][16], slot=0;
	addrc=ntohl(addr);
	slot%=4;
	sprintf(buf[slot++], "%d.%d.%d.%d", (addrc>>24)&0xff, (addrc>>16)&0xff,
		(addrc>>8)&0xff, addrc&0xff);
	return(buf[slot-1]);
}

char *ipv6tostr(byte addr[16])
{
	unsigned short *addrc;
	static char buf[4][41], slot=0;
	int i;

	addrc=(unsigned short *)addr;
	slot%=4;

	sprintf(buf[slot++], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 
		ntohs(addrc[0]), ntohs(addrc[1]), ntohs(addrc[2]), ntohs(addrc[3]),
		ntohs(addrc[4]), ntohs(addrc[5]), ntohs(addrc[6]), ntohs(addrc[7]));

	return(buf[slot-1]);
}

int NET_InitLow (void)
{
	struct hostent *local;
	char	buff[MAXHOSTNAMELEN];
	char *colon;

	printf("Net Init Low (posix: UDP/IP).\n");

	// determine my name & address
	gethostname(buff, MAXHOSTNAMELEN);
	local = gethostbyname(buff);
	if(local)local_ipv4addr = *(int *)local->h_addr_list[0];
		else local_ipv4addr = INADDR_ANY;
	printf("  hostname=%s\n", buff);
	printf("  IPv4=%s\n", ipv4tostr(local_ipv4addr));

#ifdef CONF_USEIPV6
	local = gethostbyname2(buff, AF_INET6);
	if(local)memcpy(local_ipv6addr, local->h_addr_list[0], 16);
		else memcpy(local_ipv6addr, &in6addr_any, 16);
	printf("  IPv6: %s\n", ipv6tostr(local_ipv6addr));
#endif

	printf("UDP Initialized\n");
}

#endif

#ifndef CONF_USEIPV6
int __UDP_OpenSocket (int port)
{
	int newsocket;
	struct sockaddr_in address;
//	byte _true=1;

	if ((newsocket = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		return -1;

//	ioctl (newsocket, FIONBIO, (char *)&_true);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if( bind (newsocket, (void *)&address, sizeof(address)) == -1)
		return(-1);

	return newsocket;
}

#else

int __UDP_OpenSocket (int port)
{
	int newsocket;
	struct sockaddr_in6 address;
//	byte _true=1;

	if ((newsocket = socket (PF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		return -1;

//	ioctlsocket (newsocket, FIONBIO, (char *)&_true);

	address.sin6_family = AF_INET6;
	memcpy(&address.sin6_addr, &in6addr_any, 16);
	address.sin6_port = htons(port);
	if( bind (newsocket, (void *)&address, sizeof(address)) == -1)
		return(-1);

	return newsocket;
}

#endif


int UDP_GetSocketAddr(int socket, VADDR *addrbuf)
{
	union {
		struct sockaddr addru;
		struct sockaddr_in address4;
#ifdef CONF_USEIPV6
		struct sockaddr_in6 address6;
#endif
	}address;

	int s, t;

	addrbuf->proto=0;

	s=sizeof(address);
	if(getsockname(socket, &address, &s))return(-1);

	switch(address.addru.sa_family)
	{
	case AF_INET:
		addrbuf->proto=PROTO_IPV4UDP;
		addrbuf->ipv4.port=ntohs(address.address4.sin_port);
		addrbuf->ipv4.addr=ntohl(address.address4.sin_addr.s_addr);
		break;
#ifdef CONF_IPV6
	case AF_INET6:
		addrbuf->proto=PROTO_IPV6UDP;
		addrbuf->ipv6.port=ntohs(address.address6.sin6_port);
		memcpy(addrbuf->targ.ipv6.addr, address.address6.sin6_addr, 16);
		break;
#endif
	default:
		break;
	}
	return(0);
}

/* VFILE interface */

int udpsock_get(void *buf, int lim, VADDR *from, VFILE *sock)
{
	int fhnd, stat, sz;
	fd_set rfds;
	struct timeval tv;
	union {
		struct sockaddr_in in4;
#ifdef CONF_USEIPV6
		struct sockaddr_in6 in6;
#endif
	}name;
	int namelen=sizeof(name);


//	printf("try get message.\n");

	fhnd=*(int *)sock->buffer;

/*	FD_ZERO(&rfds);
	FD_SET(fhnd, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;

	stat=select(1, &rfds, NULL, NULL, &tv);

	if(!stat)return(NULL);
*/

	sz=recvfrom(fhnd, buf, lim, 0, (struct sockaddr *)&name, &namelen);

	if(sz==-1)return(sz);

//	kprint("udpsock_get: got message \"%s\".\n", buf);
//	kprint("udpsock_get: got %d.\n", sz);

	if(name.in4.sin_family==AF_INET)
	{
		from->proto=PROTO_IPV4UDP;
		from->ipv4.addr=name.in4.sin_addr.s_addr;
		from->ipv4.port=name.in4.sin_port;
	}
#ifdef CONF_USEIPV6
	else if(name.in6.sin6_family==AF_INET6)
	{
		from->proto=PROTO_IPV6UDP;
		memcpy(from->targ.ipv6.addr, name.in6.sin6_addr.in6_u.u6_addr8, 16);
		from->ipv6.port=name.in6.sin6_port;
	}
#endif
	else printf("udp: getmessage: unknown source protocol.\n");

	return(sz);
}

int udpsock_send(VFILE *sock, VADDR *targ, void *msg, int len, int flags)
{
	struct sockaddr_in name4;
#ifdef CONF_USEIPV6
	struct sockaddr_in6 name6;
#endif

//	kprint("udpsock_send: sending message \"%s\".\n", msg);

	if(targ->proto==PROTO_IPV4UDP)
	{
//		printf("send ipv4 to %s:%d.\n", ipv4tostr(targ->ipv4.addr), ntohs(targ->ipv4.port));
//		printf("size=%d\n", len);
		name4.sin_family = AF_INET;
		name4.sin_addr.s_addr = targ->ipv4.addr;
		name4.sin_port = targ->ipv4.port;

		sendto(*(int *)sock->buffer, msg, len, 0, (struct sockaddr *)&name4, sizeof(name4));
		return(0);
	}
#ifdef CONF_USEIPV6
	else if(targ->proto==PROTO_IPV6UDP)
	{
/*		printf("send ipv6 to %s.%d.\n", ipv6tostr(targ->targ.ipv6.addr), ntohs(targ->targ.ipv6.port));
		printf("size=%d\n", msg->length); */

		name6.sin6_family = AF_INET6;
		memcpy(&name6.sin6_addr, targ->ipv6.addr, 16);
		name6.sin6_port = targ->ipv6.port;

		sendto(*(int *)sock->buffer, msg, len, 0, (struct sockaddr *)&name6, sizeof(name6));
		return(0);
	}
#endif
	printf("udpsocket: send: invalid protocol in target\n");
	return(-1);
}


VADDR *udpsock_getaddr(VFILE *sock)
{
	VADDR *tmp;
	tmp=kalloc(sizeof(VADDR));
	if(UDP_GetSocketAddr(*(int *)sock->buffer, tmp))
	{
		kfree(tmp);
		tmp=NULL;
	}
	return(tmp);
}

VFILE *UDP_OpenSocket(int socknum)
{
	VFILE *tmp;
	int *hnd, sock;
	int t=1;

	sock=__UDP_OpenSocket(socknum);
	if(sock==-1)
	{
		printf("socket creation error.\n");
		return(NULL);
	}

	ioctlsocket(sock, FIONBIO, &t);

	tmp=vfnew();
	tmp->buffer=kalloc(sizeof(int));
	hnd=tmp->buffer;
	*hnd=sock;

	tmp->get_proc=&udpsock_get;
	tmp->send_proc=&udpsock_send;
//	tmp->getaddr=&udpsock_getaddr;

	return(tmp);
}

#if 0

VADDR *NET_LookupHost(char *name)
{
	struct hostent *local;
	VADDR *tmp;

	tmp=kalloc(sizeof(VADDR));

#ifdef CONF_USEIPV6
	local = gethostbyname2(name, AF_INET6);
	if(local)
	{
		tmp->proto=PROTO_IPV6UDP;
		tmp->ipv6.port=0;
		memcpy(tmp->ipv6.addr, local->h_addr_list[0], 16);
		return(tmp);
	}
#endif

//	local = gethostbyname2(name, AF_INET);
	local = gethostbyname(name);
	if(local)
	{
		tmp->proto=PROTO_IPV4UDP;
		tmp->ipv4.port=0;
		tmp->ipv4.addr = *(int *)local->h_addr_list[0];
		return(tmp);
	}

	kfree(tmp);
	return(NULL);
}
#endif
