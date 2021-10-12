#include <general.h>

typedef struct {
VFILE *vfd;
VADDR *last;
char *msgbuf, *msgcur, *msgend;
int msgtime;
}sockinfo;

VFILE *UDP_OpenSocket(int socknum);

elem tysock_socklist; /* ((sock pid)...) */

elem TySock_SocketPid(elem pid, elem def)
{
	VFILE *vfd;
	int sock;
	sockinfo *si;
	elem tmp, t;

	sock=ELEM_TOFIXNUM(CADR(CADR(def)));
	vfd=UDP_OpenSocket(sock);

	if(!vfd)return(MISC_FALSE);

	tmp=TyFcn_TypeX(SYM("socket"), sizeof(sockinfo), NULL);
	si=TypeX_Data(t);

	si->vfd=vfd;
	si->last=NULL;
	si->msgbuf=NULL;
	si->msgcur=NULL;
	si->msgend=NULL;

	tysock_socklist=CONS(CONS(tmp, CONS(pid, MISC_EOL)), tysock_socklist);

	return(tmp);
}

elem TySock_SendMsg(elem sock, elem targ, elem msg)
{
	sockinfo *si;
	elem t;
	VADDR *addr;

	si=(sockinfo *)TypeX_Data(sock);
	addr=(VADDR *)TypeX_Data(targ);

	if(!si->msgbuf)
	{
		si->msgbuf=kalloc(16384);
		si->msgend=si->msgbuf+16384;
		si->msgcur=si->msgbuf;
		si->msgtime=Sys_TimeMS()+100;
	}

	if(!TySock_AddrEqual(addr, si->last))
	{
		if(si->msgcur-si->msgbuf)
			vfsend(si->vfd, si->last, si->msgbuf, si->msgcur-si->msgbuf, 0);
		si->last=addr;
		si->msgcur=si->msgbuf;
		si->msgtime=Sys_TimeMS()+100;
	}

	if(!si->msgtime)si->msgtime=Sys_TimeMS()+100;

//	t=FilterSExpr_FillBuf(si->msgcur, si->msgend-si->msgcur, CONS(msg, MISC_EOL));
//	si->msgcur+=strlen(si->msgcur);
	if(t!=MISC_EOL)
	{
		vfsend(si->vfd, si->last, si->msgbuf, si->msgcur-si->msgbuf, 0);
		si->msgcur=si->msgbuf;
		si->last=addr;
		si->msgtime=Sys_TimeMS()+100;
//		t=FilterSExpr_FillBuf(si->msgcur, si->msgend-si->msgcur, CONS(msg, MISC_EOL));
		si->msgcur+=strlen(si->msgcur);
		if(t!=MISC_EOL)kprint("TySock_SendMsg: buffer overflow.\n");
	}
	return(MISC_NULL);
}

int TySock_AddrEqual(VADDR *a, VADDR *b)
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

elem TySock_Addr2AddrObj(elem sock, VADDR *addr)
{
	elem tmp;

	tmp=TyFcn_TypeX(SYM("addr"), sizeof(VADDR), addr);

	return(tmp);
}

elem TySock_List2Addr(elem sock, elem def)
{
	elem tmp;
	VADDR *addr;
	unsigned long l;

	tmp=TyFcn_TypeX(SYM("addr"), sizeof(VADDR), NULL);
	addr=TypeX_Data(tmp);

	if(CAR(def)==SYM("ipv4udp"))
	{
		addr->proto=PROTO_IPV4UDP;
		l=ELEM_TOFIXNUM(CAR(CAR(CADR(def))))<<24;
		l+=ELEM_TOFIXNUM(CADR(CAR(CADR(def))))<<16;
		l+=ELEM_TOFIXNUM(CADDR(CAR(CADR(def))))<<8;
		l+=ELEM_TOFIXNUM(CADDDR(CAR(CADR(def))));
		addr->ipv4.addr=htonl(l);
		addr->ipv4.port=htons(ELEM_TOFIXNUM(CADR(CADR(def))));
	}

	return(tmp);
}

#if 0
elem TySock_RecieveMsg(elem sock)
{
	elem cur, t;
	char *buf;
	sockinfo *si;
	VADDR *addr;
	int sz;

	si=(sockinfo *)TypeX_Data(sock);

	cur=tysock_socklist;
	while(ELEM_CONSP(cur))
	{
		if(CAR(CAR(cur))==sock)break;
		cur=CDR(cur);
	}
	if(!ELEM_CONSP(cur))return(MISC_FALSE);

	buf=kalloc(4096);
	while(1)
	{
		addr=kalloc(sizeof(VADDR));
		sz=vfget(buf, 4096, addr, si->vfd);
		if(sz<=0)break;
	}
}
#endif

int TySock_HandleInput()
{
	elem cur, cur2, t, ado;
	char *buf;
	sockinfo *si;
	VADDR *addr;
	int sz, now;

	now=Sys_TimeMS();
	cur=tysock_socklist;
	while(ELEM_CONSP(cur))
	{
		t==CAR(CAR(cur));
		si=(sockinfo *)TypeX_Data(t);

		buf=kalloc(4096);
		while(1)
		{
			addr=kalloc(sizeof(VADDR));
			sz=vfget(buf, 4096, addr, si->vfd);
			if(sz<=0)break;
//			t=FilterSExpr_ParseMessage(buf);
			ado=TySock_Addr2AddrObj(CAR(CAR(cur)), addr);
			cur2=t;
			while(ELEM_CONSP(cur2))
			{
				Interp_SendThreadFrom(CADR(CAR(cur)), ado, CAR(cur2));
				cur2=CDR(cur2);
			}
		}
		if(si->msgtime && (si->msgtime<=now))
		{
			kprint("TySock_HandleInput: msg sent, timeout\n");

			if(si->msgcur-si->msgbuf)
				vfsend(si->vfd, si->last, si->msgbuf, si->msgcur-si->msgbuf, 0);
			si->last=NULL;
			si->msgcur=si->msgbuf;
			si->msgtime=0;
		}
		cur=CDR(cur);
	}
}

extern elem null_object;

int TySock_Init()
{
	NET_InitLow();

	tysock_socklist=MISC_EOL;
	MMGC3_AddNamedRoot(&tysock_socklist, "sys-sockets");

	Interp_DefinePrimative("socket-pid",	&TySock_SocketPid,		2);
	Interp_DefinePrimative("send-msg-sock",	&TySock_SendMsg,		3);
	Interp_DefinePrimative("list->addr",	&TySock_List2Addr,		2);
}
