#define CONF_USEIPV6

#include <general.h>

#include <windows.h>

#ifdef CONF_USEIPV6
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <winsock.h>
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif

char local_hostname[MAXHOSTNAMELEN];
unsigned long local_ipv4addr;
byte local_ipv6addr[16];

static byte in6_addr_any[16]=
	{0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0};
static byte in6_addr_loopback[16]=
	{0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1};

static char *ipv4tostr(unsigned long addr)
{
	unsigned long addrc;
	static char buf[4][16], slot=0;
	addrc=ntohl(addr);
	slot%=4;
	sprintf(buf[slot++], "%d.%d.%d.%d", (addrc>>24)&0xff, (addrc>>16)&0xff,
		(addrc>>8)&0xff, addrc&0xff);
	return(buf[slot-1]);
}

static char *ipv6tostr(byte *addr)
{
	unsigned short *addrc;
	char *buf, *s;
	int i;

	addrc=(unsigned short *)addr;
	buf=kralloc(64);

//	sprintf(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 
//		ntohs(addrc[0]), ntohs(addrc[1]), ntohs(addrc[2]), ntohs(addrc[3]),
//		ntohs(addrc[4]), ntohs(addrc[5]), ntohs(addrc[6]), ntohs(addrc[7]));

	s=buf;
	i=0;

	while(ntohs(addrc[i]))
	{
		if(i>=8)break;
		if(i)*s++=':';
		sprintf(s, "%x", ntohs(addrc[i]));
		s+=strlen(s);
		i++;
	}
	if((i<8) && !ntohs(addrc[i]))
	{
		*s++=':';
		*s=0;

		while(!ntohs(addrc[i]))
			i++;
	}
	while(ntohs(addrc[i]))
	{
		if(i>=8)break;
		if(i)*s++=':';
		sprintf(s, "%x", ntohs(addrc[i]));
		s+=strlen(s);
		i++;
	}

	return(buf);
}

char *NET_Addr2Str(VADDR *addr)
{
	char *s, *t;
	int addrc;

	switch(addr->proto)
	{
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		s=kralloc(64);

		addrc=ntohl(addr->ipv4.addr);
		sprintf(s, "%d.%d.%d.%d:%d",
			(addrc>>24)&0xff, (addrc>>16)&0xff,
			(addrc>>8)&0xff, addrc&0xff,
			ntohs(addr->ipv4.port));
		break;
	case PROTO_IPV6UDP:
	case PROTO_IPV6TCP:
		s=ipv6tostr(addr->ipv6.addr);
		t=kralloc(strlen(s)+10);
		sprintf(t, "[%s]:%d", s, ntohs(addr->ipv6.port));
		break;
	default:
		s=kralloc(1);
		*s=0;
		break;
	}
	return(s);
}

static int str2ipv4(char *s, int *port)
{
	int a, b, c, d;

	sscanf(s, "%d.%d.%d.%d:%d", &a, &b, &c, &d, port);
	return((a<<24)+(b<<16)+(c<<8)+d);
}

static int ishexnum(char c)
{
	if((c>='0') && (c<='9'))return(1);
	if((c>='A') && (c<='F'))return(1);
	if((c>='a') && (c<='f'))return(1);
	return(0);
}

static int hexval(char c)
{
	if((c>='0') && (c<='9'))return(c-'0');
	if((c>='A') && (c<='F'))return((c-'A')+10);
	if((c>='a') && (c<='f'))return((c-'a')+10);
	return(0);
}

static char *str2ipv6(byte *addr, char *s)
{
	short buf1[16], buf2[16];
	short *t1, *t2, *t3;
	int i;

	char buf[16];
	char *t;

	memset(buf1, 0, 16);
	memset(buf2, 0, 16);

	if(*s=='[')s++;

	t1=buf1;
	while(*s)
	{
		t=buf;
		while(ishexnum(*s))*t++=*s++;
		*t++=0;

		if(buf[0])
		{
			i=0;
			t=buf;
			while(*t)i=(i<<4)+hexval(*t++);
			*t1++=i;
		}
		if(*s!=':')break;
		s++;
		if(*s==':')
		{
			s++;
			break;
		}
	}

	t1=buf2;
	while(*s)
	{
		t=buf;
		while(ishexnum(*s))*t++=*s++;
		*t++=0;

		if(buf[0])
		{
			i=0;
			t=buf;
			while(*t)i=(i<<4)+hexval(*t++);
			*t1++=i;
		}
		if(*s!=':')break;
		s++;
		if(*s==':')
		{
			s++;
			break;
		}
	}

	if(*s==']')s++;

	t2=buf1+(8-(t1-buf2));
	t3=buf2;
	while(t3<t1)*t2++=*t3++;

	t=addr;
	for(i=0; i<8; i++)
	{
		*t++=buf1[i]>>8;
		*t++=buf1[i]&0xff;
	}

	return(s);
}

VADDR *NET_Str2Addr(char *str, int proto)
{
	VADDR *tmp;
	char *s;

	switch(proto)
	{
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		tmp=kalloc(sizeof(VADDR));
		tmp->proto=proto;

		tmp->ipv4.addr=htonl(str2ipv4(str, &tmp->ipv4.port));
		tmp->ipv4.port=htons(tmp->ipv4.port);
		break;
	case PROTO_IPV6UDP:
	case PROTO_IPV6TCP:
		tmp=kalloc(sizeof(VADDR));
		tmp->proto=proto;

		s=str2ipv6(tmp->ipv6.addr, str);
		sscanf(s, ":%d", &tmp->ipv6.port);
		tmp->ipv6.port=htons(tmp->ipv6.port);
		break;
	default:
		tmp=NULL;
		break;
	}
	return(tmp);
}

int NET_InitLow (void)
{
	struct hostent *local;
	char	buff[MAXHOSTNAMELEN];
	char *colon;

	WSADATA wsaData;
	int err;
	VADDR *addr;

	static int started=0;

	if(started)return(0);
	started=1;

	printf("Net Init Low (Winsock).\n");

	err = WSAStartup(MAKEWORD( 1, 1 ), &wsaData);
	if (err != 0)
	{
		kprint("Winsock: winsock.dll error.\n");
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 )
	{
		kprint("Winsock: incompatible winsock version.\n");
		WSACleanup();
		return;   
	}

	// determine my name & address
	gethostname(buff, MAXHOSTNAMELEN);
	strcpy(local_hostname, buff);

	local = gethostbyname(buff);
	if(local)local_ipv4addr = *(int *)local->h_addr_list[0];
		else local_ipv4addr = INADDR_ANY;
	printf("  hostname=%s\n", buff);
	printf("  IPv4=%s\n", ipv4tostr(local_ipv4addr));

#ifdef CONF_USEIPV6
//	local = gethostbyname2(buff, AF_INET6);
//	if(local)memcpy(local_ipv6addr, local->h_addr_list[0], 16);
//		else memcpy(local_ipv6addr, &in6addr_any, 16);
	addr=NET_LookupHost2(buff, NULL, PROTO_IPV6TCP);
	if(addr)memcpy(local_ipv6addr, addr->ipv6.addr, 16);
		else memcpy(local_ipv6addr, &in6_addr_loopback, 16);

	printf("  IPv6: %s\n", ipv6tostr(local_ipv6addr));
#endif

	printf("TCP Initialized\n");
}

VADDR *NET_LookupHost(char *name)
{
	struct hostent *local;
	VADDR *tmp;
#ifdef CONF_USEIPV6
	struct addrinfo hint, *inf;
	char *serve="0";
	struct sockaddr_in6 *addr6;
#endif
	int i;

	tmp=kalloc(sizeof(VADDR));

//#ifdef CONF_USEIPV6
#if 0
//	local = gethostbyname2(name, AF_INET6);

	memset(&hint, 0, sizeof(struct addrinfo));
	hint.ai_family=AF_INET6;

	i=getaddrinfo(name, NULL, &hint, &inf);
	if(!i)
	{
		addr6=inf->ai_addr;
		tmp->proto=PROTO_IPV6TCP;
		tmp->ipv6.port=0;
		memcpy(tmp->ipv6.addr, &addr6->sin6_addr, 16);
		return(tmp);
	}
#endif

//	local = gethostbyname2(name, AF_INET);
	local = gethostbyname(name);
	if(local)
	{
		tmp->proto=PROTO_IPV4TCP;
		tmp->ipv4.port=0;
		tmp->ipv4.addr = *(int *)local->h_addr_list[0];
		return(tmp);
	}

	kfree(tmp);
	return(NULL);
}

#ifdef CONF_USEIPV6

VADDR *NET_LookupHost2(char *name, char *serv, int proto)
{
	struct hostent *local;
	VADDR *tmp;
	struct addrinfo hint, *inf;
	char *serve="0";
	struct sockaddr_in6 *addr6;
	int i;

	tmp=kalloc(sizeof(VADDR));

//	local = gethostbyname2(name, AF_INET6);

	memset(&hint, 0, sizeof(struct addrinfo));
	switch(proto)
	{
	case PROTO_IPV4:
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		hint.ai_family=AF_INET;
		break;
	case PROTO_IPV6:
	case PROTO_IPV6UDP:
	case PROTO_IPV6TCP:
		hint.ai_family=AF_INET6;
		break;
	default:
		hint.ai_family=AF_INET;
		proto=PROTO_IPV4TCP;
		break;
	}
	i=getaddrinfo(name, serv, &hint, &inf);
	if(!i)
	{
		addr6=inf->ai_addr;
		tmp->proto=proto;
		tmp->ipv6.port=0;
		memcpy(tmp->ipv6.addr, &addr6->sin6_addr, 16);
		return(tmp);
	}

	kfree(tmp);
	return(NULL);
}

#endif

VADDR *NET_DecodeHostname(char *name)
{
	VADDR *tmp;
	if(name[0]=='[')
	{
		tmp=NET_Str2Addr(name, PROTO_IPV6TCP);
		return(tmp);
	}
	if((name[0]>='0') && (name[0]<='9'))
	{
		tmp=NET_Str2Addr(name, PROTO_IPV4TCP);
		return(tmp);
	}

#ifdef CONF_USEIPV6
	tmp=NET_LookupHost2(name, NULL, PROTO_IPV6);
	if(tmp)return(tmp);
#endif
	tmp=NET_LookupHost(name);
	return(tmp);
}
