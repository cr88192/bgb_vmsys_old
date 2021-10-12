/*
MRP messages have a header and then data.

header:
"MRP"
byte msg_type; //0=null head, 1=connect, 2=message
(head_type != 0)
{
	short len;
	(msg_type == 1)
	{
		string name;
	}
}
messages...

 */

#include <general.h>
#include <net/bgbmrp.h>

typedef struct {
int con;
int pid;
}MRP_LongRef;

typedef struct {
char name[16];
VADDR addr;
int state; //0=unused, 1=connecting, 2=connected

elem *stack;
int stackpos, mark;

VFILE *pa, *pb; //2 ends of a pipe

}MRP_Connection;

int mrp_port;
VFILE *mrp_sock;

MRP_Connection mrp_con[64];
int mrp_connum;

int MRP_AddrEqual(VADDR *a, VADDR *b)
{
	if(!a || !b)return(0);
	if(a->proto != b->proto)return(0);
	switch(a->proto)
	{
	case PROTO_IPV4UDP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port != b->ipv4.port)return(0);
		break;
	case PROTO_IPV4TCP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port != b->ipv4.port)return(0);
		break;
	default:
		return(0);
		break;
	}
	return(1);
}

int MRP_FindCon(VADDR *addr)
{
	int i;

	for(i=0; i<64; i++)
		if(mrp_con[i].state &&
		MRP_AddrEqual(&mrp_con[i].addr, addr))
			return(i);
	return(-1);
}

int MRP_NewCon(VADDR *addr)
{
	int i;

	for(i=0; i<64; i++)
		if(!mrp_con[i].state)
	{
		mrp_con[i].state=1;
		memcpy(&mrp_con[i].addr, addr, sizeof(VADDR));
		return(i);
	}
	return(-1);
}

int MRP_SendConnect(VADDR *addr)
{
	byte buf[512], buf2[64];
	byte *t;
	char *s;
	int i;

	gethostname(buf2, 64);
	s=buf2;

	t=buf;
	*t++='M';
	*t++='R';
	*t++='P';
	*t++=1;

	i=strlen(s)+1;
	*t++=(i>>8)&0xff;
	*t++=i&0xff;

	strcpy(t, s);
	t+=i;

	s=buf;

	vfsend(mrp_sock, addr, buf, t-s, 0);

	return(0);
}

int MRP_ParseConnect(byte *msg, int sz, VADDR *from)
{
	int i;

	i=MRP_FindCon(from);
	if(i!=-1)
	{
		strcpy(mrp_con[i].name, msg+6);
		mrp_con[i].state=2;
		return(i);
	}

	//didn't initiate, send response
	i=MRP_NewCon(from);
	strcpy(mrp_con[i].name, msg+6);
	mrp_con[i].state=2;
	MRP_SendConnect(from);
	return(i);
}

int MRP_GetOrConnect(VADDR *to)
{
	int i;

	i=MRP_FindCon(from);
	if(i!=-1)return(i);

	//not connected, connect
	i=MRP_NewCon(to);
	strcpy(mrp_con[i].name, "(connect)");
	mrp_con[i].state=1;
	MRP_SendConnect(to);
	return(i);
}

elem mrp_genref(VADDR *addr, long pid)
{
	MRP_LongRef *ref;

	ref=TypeX_Alloc("longref", sizeof(MRP_LongRef));

//	memcpy(ref->addr, addr, sizeof(VADDR));
	ref->con=MRP_GetOrConnect(addr);
	ref->pid=pid;

	return(MMGC3_GetReference(ref));
}

int mrp_opcode(int op, byte *s, MRP_Connection *con)
{
	elem *st;
	byte *t, *t2;
	u2 *tu;
	int i;
	long l;
	elem a;
	VADDR *addr, *from;

	from=&con->addr;

	switch(op)
	{
	case GFXOP_NOP:
		break;

	case GFXOP_POPRET:
		con->stackpos--;
		st=con->stack+con->stackpos;
//		gfxdev_outbuf_pos=0;
//		GfxDev_WriteSLong(st[0]);
		break;

	case GFXOP_MARK:
		st=con->stack+con->stackpos;
		st[0]=con->mark;
		con->mark=con->stackpos;
		con->stackpos++;
		break;

	case MRPOP_CONS:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=CONS(st[0], st[1]);
		con->stackpos++;
		break;

	case MRPOP_RCONS:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=CONS(st[1], st[0]);
		con->stackpos++;
		break;

	case MRPOP_LIST:
		a=MISC_EOL;
		for(i=con->stackpos-1; i>=con->mark; i--)
			a=CONS(con->stack[i], a);
		con->stackpos=con->mark;
		con->mark=con->stack[con->stackpos-1];
		con->stack[con->stackpos-1]=a;
		break;

	case MRPOP_LISTI:
		a=con->stack[con->stackpos-1];
		for(i=con->stackpos-2; i>=con->mark; i--)
			a=CONS(con->stack[i], a);
		con->stackpos=con->mark;
		con->mark=con->stack[con->stackpos-1];
		con->stack[con->stackpos-1]=a;
		break;

	case MRPOP_ADDR:
		con->stackpos-=3;
		st=con->stack+con->stackpos;
		switch(TOINT(st[2]))
		{
		case 1:
			addr=TypeX_Alloc("addr", sizeof(VADDR));
			addr->proto=PROTO_IPV4UDP;
			addr->ipv4.addr=htonl(TOINT(st[0]));
			addr->ipv4.port=htons(TOINT(st[1]));

			a=MMGC3_GetReference(addr);
			st[0]=a;
			con->stackpos++;
			break;

		case 2:
			addr=TypeX_Alloc("addr", sizeof(VADDR));
			addr->proto=PROTO_IPV4TCP;
			addr->ipv4.addr=htonl(TOINT(st[0]));
			addr->ipv4.port=htons(TOINT(st[1]));

			a=MMGC3_GetReference(addr);
			st[0]=a;
			con->stackpos++;
			break;

		default:
			kprint("MRP: ADDR: unknown protocol %d\n",
				TOINT(st[2]));
			st[0]=MISC_NULL;
			con->stackpos++;
			break;
		}
		break;

	case MRPOP_RREF:
		con->stackpos-=1;
		st=con->stack+con->stackpos;
		st[0]=mrp_genref(from, TOINT(st[0]));
		con->stackpos++;
		break;

	case MRPOP_LREF:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		addr=TypeX_Data(st[0]);
		st[0]=mrp_genref(addr, TOINT(st[1]));
		con->stackpos++;
		break;

	default:
		kprint("MRP: unknown opcode %d.\n", op);
		return(-1);
		break;
	}
	return(0);
}

int mrp_parse(void *buf, int len, VADDR *from)
{
	byte *s, *e, *t;
	u2 *su, *tu, *tu2;
	int sg, st, st2[2], i;
	double stf;

	MRP_Connection *con;

	static int rlen, renc; //remaining data to recieve, encoding
	static byte *rbuf, *erbuf; //recieve buffer and end recieve buf

	s=buf;
	e=s+len;

	i=MRP_FindCon(from);
	if(i==-1)return(-1);
	con=&mrp_con[i];

	while(s<e)
	{

		if(rlen)
		{
			st=e-s;
			i=(st<rlen)?st:rlen;
			memcpy(erbuf, s, i);
			s+=i;
			erbuf+=i;
			rlen-=i;

			if(!rlen)
				con->stack[con->stackpos++]=
				MMGC3_GetReference(rbuf);
			continue;
		}

		switch(*s&3)
		{
		case 0:
			sg=(*s>>3)&7;
			if((sg==0) || (sg==1))
				switch((*s>>6)&3)
			{
			case 0:
				if(sg)st=((signed char *)s)[1];
					else st=((unsigned char *)s)[1];
				stf=st;
				s+=2;
				break;
			case 1:
				st=(s[1]<<8)+s[2];
				if(sg && (st>32767))st|=~0xFFFF;
				stf=st;
				s+=3;
				break;
			case 2:
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				if(sg && (st>(1<<31)))st|=~0xFFFFFFFF;
				stf=st;
				s+=5;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			if(sg==2)switch((*s>>6)&3)
			{
			case 2:
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				stf=*(float *)&st;
				st=stf;
				s+=5;
				break;
			case 3:
				st2[1]=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				st2[0]=(s[5]<<24)+(s[6]<<16)+(s[7]<<8)+s[8];
				stf=*(double *)&st2;
				st=stf;
				s+=9;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			con->stack[gfx_stackpos++]=FLONUM(stf);
			break;
		case 1:
			st=((s[0]>>4)&15)+(s[1]<<4);
			s+=2;
			if(mrp_opcode(st, s, con)<0)
				return((int)s-(int)buf);
			break;
		case 2:
			switch((*s>>3)&31)
			{
			case 1:
				renc=s[1];
				st=(s[2]<<24)+(s[3]<<16)+(s[4]<<8)+s[5];
				rlen=st;
				rbuf=kalloc(rlen);
				erbuf=rbuf;
				s+=6;
				break;

			case 3:
				st=(s[1]<<8)+s[2];

				tu=kalloc((st*2)+2);
//				strncpy(t, s+2, s[1]);

				su=(u2 *)(s+3);
				tu2=tu;
				i=st;
				while(i--)*tu2++=*su++;
				*tu2++=0;
				s+=(st*2)+3;
				con->stack[con->stackpos++]=
					TyFcn_String16(tu);
//				kprint("parsed string \"%s\"\n", GfxDev_Uni2Asc(tu));
				break;

			default:
				kprint("GfxDev: object parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			break;
		default:
			kprint("MRP: cmd parse error.\n");
			return((int)s-(int)buf);
			break;
		}
	}
	return(len);
}

int MRP_Poll()
{
	byte buf[4096];
	VADDR addr;
	int sz, l;

	if(!mrp_port)return(-1);

	while(1)
	{
		sz=vfget(buf, 4096, &addr, mrp_port);
		if(sz<=0)break;
		if((buf[0]!='M') || (buf[1]!='R') || (buf[2]!='P'))
			continue;
		l=(buf[4]<<8)+buf[5];

		switch(buf[3])
		{
		case 0:
			break;
		case 1:
			MRP_ParseConnect(buf, sz, &addr);
			break;
		case 2:
			mrp_parse(&buf+l+6, sz-(l+6), &addr);
			break;
		default:
			break;
		}
	}
	return(0);
}

int MRP_Write(MRP_Connection *con, elem c)
{
	if(ELEM_CONSP(c))
	{
		MRP_Write(con, CAR(c));
		MRP_Write(con, CDR(c));
		GfxApi_WriteOpcode(con->pa, MRPOP_CONS);
		return(0);
	}
	if(ELEM_FIXNUMP(c))
	{
		GfxApi_WriteSInt(con->pa, TOINT(c));
		return(0);
	}
	if(ELEM_FLONUMP(c))
	{
		GfxApi_WriteFloat(con->pa, TOFLOAT(c));
		return(0);
	}
	if(ELEM_STRINGP(c))
	{
		GfxApi_WriteString(con->pa, ELEM_TOSTRING(c));
		return(0);
	}
	return(-1);
}

int MRP_Send(VADDR *addr, elem msg)
{
	int i;

	i=MRP_FindCon(addr);
}

int MRP_Init()
{
	NET_InitLow();

	mrp_port=8192;
	mrp_sock=NULL;
	while(mrp_port>(8192-256))
	{
		mrp_sock=UDP_OpenSocket(mrp_port);
		if(mrp_sock)break;
		mrp_port--;
	}
}
