#include <general.h>

int NET_AddrEqual(VADDR *a, VADDR *b)
{
	if(!a || !b)return(0);
	if(a->proto != b->proto)return(0);
	switch(a->proto)
	{
	case PROTO_IPV4UDP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port && b->ipv4.port)
			if(a->ipv4.port != b->ipv4.port)
			return(0);
		break;
	case PROTO_IPV4TCP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port && b->ipv4.port)
			if(a->ipv4.port != b->ipv4.port)
			return(0);
		break;
	default:
		return(0);
		break;
	}
	return(1);
}

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
	int addr;

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
	while(*s && (*s!=':'))s++;
	if(*s)s++;

	*port=katoi(s);

	return(addr);

//	sscanf(s, "%d.%d.%d.%d:%d", &a, &b, &c, &d, port);
//	return((a<<24)+(b<<16)+(c<<8)+d);
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
		s++;
//		sscanf(s, ":%d", &tmp->ipv6.port);
		tmp->ipv6.port=katoi(s);
		tmp->ipv6.port=htons(tmp->ipv6.port);
		break;
	default:
		tmp=NULL;
		break;
	}
	return(tmp);
}

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

	tmp=NULL;

#ifdef CONF_USEIPV6
	tmp=NET_LookupHost2(name, PROTO_IPV6);
	if(tmp)return(tmp);
#endif
#if 0
	tmp=NET_LookupHost(name);
#endif
	return(tmp);
}

int NET_Init()
{
	char *opts[8];

	kprint("NET_Init\n");
	NetVal_Init();
	NETAPI_Init();
	Meta0_Init();

	Ethernet_Init();

	HttpNode_Init();

	opts[0]="192.168.1.100:50000";
	opts[1]=NULL;
	VPath_Mount("/shroot",	"bshfs", opts);

//	while(1);

	return(0);
}
