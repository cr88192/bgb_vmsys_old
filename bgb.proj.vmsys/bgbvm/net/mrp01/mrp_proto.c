/*
tcp based.

 */

#include <general.h>
#include <net/mrp01.h>

#include <string.h>

int mrp_port;
VFILE *mrp_sock;
VFILE *mrp_sock_udp;

VGUID *mrp_guid;
elem mrp_guid_elem;

//MRP_Connection *mrp_con[MRP_MAXCONS];
//elem mrp_convec;
//int mrp_connum;
elem mrp_con_lst;

MRP_FindBuf mrp_findbuf[MRP_FINDBUF];
int mrp_findbuf_rover;
int mrp_find_id;

VADDR mrp_found_addr;
int mrp_found_id;

//elem mrp_stacks;
//extern elem interp_repl_ctx;
//extern elem interp_cur_ctx;
//extern elem interp_apply_rax;

elem mrp_handlers; //((sym handler) ...)
elem mrp_scion_lst;

int mrp_ret_value[8];
int mrp_ret_setter[8];
int mrp_ret_cont[8];
int mrp_ret_pos;

extern char local_hostname[64];
extern unsigned long local_ipv4addr;
extern byte local_ipv6addr[16];

byte *con_framestack[1024];
int con_framestack_pos=0;

int MRP_AddrEqual(VADDR *a, VADDR *b)
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

MRP_Connection *MRP_FindCon(VADDR *addr)
{
	int i;
	elem t, cur;
	MRP_Connection *con;

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
		t=CAR(cur);
		if(ELEM_TYPEXP(t))
		{
			con=TypeX_Data(t);
			if(con->state && MRP_AddrEqual(&con->addr, addr))
				return(con);
		}
		cur=CDR(cur);
	}
	return(NULL);
}

MRP_Connection *MRP_NewCon(VADDR *addr)
{
	int i;
	elem t, cur;
	MRP_Connection *con;

	con=TypeX_Alloc("mrp-connection", sizeof(MRP_Connection));

	con->state=1;
	memcpy(&con->addr, addr, sizeof(VADDR));

	t=VECTOR_NEW(4095);
	con->stack_elem=t;
	con->stack=TyFcn_VectorBody(t);
	con->stackpos=0;
	con->mark=0;

	con->lastdelta=Sys_TimeMS();
	con->deltas=MISC_EOL;

	mrp_con_lst=CONS(TypeX_GetReference(con), mrp_con_lst);

	return(con);
}

int MRP_WriteParam(VFILE *sock, char *sym)
{
	MRPTrans_WriteSymbol(sock, sym);
	MRPTrans_WriteOpcode(sock, MRPOP_REQATTR);
	return(0);
}

MRP_Connection *MRP_GetOrConnect(VADDR *to)
{
	int i, t;
	VFILE *sock;
	MRP_Connection *con;

	con=MRP_FindCon(to);
	if(con)
	{
		i=0;
		if(con->state==3)
			i=MRP_TryReconnect(con);
		if(!i)return(con);
	}
	//not connected, connect
	con=MRP_NewCon(to);
	strcpy(con->name, "(connect)");
	con->state=1;

	sock=TCP_OpenConnect(to);
//	sock=UDPBUF_OpenConnect(to);

	if(!sock)
	{
		kprint("open connection fail (open socket).\n");
		con->state=0;
		return(NULL);
	}

	con->sock=sock;

	t=5;
	vfioctls(sock, "can-write?", &t);
	if(!t)
	{
		vfclose(sock);
		kprint("open connection fail (connect host).\n");
		con->state=0;
		return(NULL);
	}

//	MRPTrans_WriteParam(sock, "MRP");
	MRP_WriteParam(sock, "NAME");
	MRP_WriteParam(sock, "GUID");
	MRP_WriteParam(sock, "PORT");

	i=Sys_TimeMS();
	while(con->state==1)
	{
		t=Sys_TimeMS();
		if((t-i)>5000)break;
		MRP_Poll();
		kusleep(1000);
	}

	if(con->state==1)kprint("link failed full init.\n");

	return(con);
}

int MRP_TryReconnect(MRP_Connection *con)
{
	int i, t;
	VFILE *sock;
	VGUID guid;

	if((Sys_TimeMS()-con->conlast)<30000)return(-1);
	con->conlast=Sys_TimeMS();

	kprint("MRP_TryReconnect %X\n", con);

	memcpy(&guid, &con->guid, 16);

	sock=TCP_OpenConnect(&con->addr);
//	sock=UDPBUF_OpenConnect(&con->addr);
	if(!sock)
	{
//		kprint("open connection fail (open socket).\n");
//		return(-1);

		kprint("no sock\n");

		i=MRP_FindGuid(&guid, &con->addr);
		if(i==-1)
		{
			con->conlast=Sys_TimeMS();
			return(-1);
		}
		i=MRP_TryReconnect(con);
		con->conlast=Sys_TimeMS();
		return(i);
	}

	con->state=1;

	con->sock=sock;

	t=5;
	vfioctls(sock, "can-write?", &t);
	if(!t)
	{
//		vfclose(sock);
//		kprint("open connection fail (connect host).\n");
//		con->state=0;
//		return(NULL);

		i=MRP_FindGuid(&guid, &con->addr);
		if(i==-1)
		{
			con->conlast=Sys_TimeMS();
			return(-1);
		}
		i=MRP_TryReconnect(con);
		con->conlast=Sys_TimeMS();
		return(i);
	}

//	MRPTrans_WriteParam(sock, "MRP");
	MRP_WriteParam(sock, "NAME");
	MRP_WriteParam(sock, "GUID");
	MRP_WriteParam(sock, "PORT");

	i=Sys_TimeMS();
	while(con->state==1)
	{
		t=Sys_TimeMS();
		if((t-i)>1000)break;
		MRP_Poll();
		kusleep(1000);
	}

	kprint("connected\n");

	//connected but to wrong node
	if(!NET_GuidEqualP(&guid, &con->guid))
	{
		kprint("guid wrong\n");
		i=MRP_FindGuid(&guid, &con->addr);

		memcpy(&con->guid, &guid, 16);
		con->state=3;
		vfclose(sock);

		if(i==-1)
		{
			con->conlast=Sys_TimeMS();
			return(-1);
		}
		i=MRP_TryReconnect(con);
		con->conlast=Sys_TimeMS();
		return(i);
	}

	kprint("connection open\n");

	return(0);
}

elem mrp_genref(VADDR *addr, long pid, int type)
{
	MRP_LongRef *ref;
	int i;
	MRP_Connection *con;

	con=MRP_GetOrConnect(addr);
	if(!con)return(MISC_NULL);

	ref=TypeX_Alloc("longref", sizeof(MRP_LongRef));

//	memcpy(ref->addr, addr, sizeof(VADDR));
	ref->con=TypeX_GetReference(con);
	ref->pid=pid;
	ref->type=type;

	return(TypeX_GetReference(ref));
}

int mrp_repparam(MRP_Connection *con, elem sym, elem val)
{
	char buf[256];
	int l;

//	kprint("REP PARAM: ");
//	TyFcn_DumpElem(sym);
//	kprint(" ");
//	TyFcn_DumpElem(val);
//	kprint("\n");
	

	if(sym==SYM("NAME"))
	{
		strcpy(con->name, ELEM_TOSTRING(val));

		return(0);
	}

	if(sym==SYM("GUID"))
	{
		memcpy(&con->guid, TyFcn_ByteVectorBody(val), 16);
//		NET_String2Guid(&con->guid, ELEM_TOSTRING(val));
		kprint("other guid: %s\n", NET_Guid2String(&con->guid));
		return(0);
	}

	if(sym==SYM("PORT"))
	{
		con->addr.ipv4.port=htons((short)TOINT(val));
		MRPTrans_WriteSymbol(con->sock, "GO");
		MRPTrans_WriteOpcode(con->sock, MRPOP_REQATTR);
		return(0);
	}

	return(-1);
}

int mrp_reqparam(MRP_Connection *con, elem sym)
{
	char buf[256];

	kprint("PARAM: %s\n", ELEM_TOSYMBOL(sym));

	if(sym==SYM("NAME"))
	{
		MRPTrans_WriteSymbol(con->sock, "NAME");
		MRPTrans_WriteString(con->sock, local_hostname);
		MRPTrans_WriteOpcode(con->sock, MRPOP_REPATTR);
		return(0);
	}

	if(sym==SYM("GUID"))
	{
		MRPTrans_WriteSymbol(con->sock, "GUID");
		MRPTrans_WriteGuid(con->sock, mrp_guid);
		MRPTrans_WriteOpcode(con->sock, MRPOP_REPATTR);
		return(0);
	}

	if(sym==SYM("PORT"))
	{
		MRPTrans_WriteSymbol(con->sock, "PORT");
		MRPTrans_WriteUInt(con->sock, mrp_port);
		MRPTrans_WriteOpcode(con->sock, MRPOP_REPATTR);
		return(0);
	}

	if(sym==SYM("GO"))
	{
		con->state=2;
		return(0);
	}

	return(-1);
}

int mrp_opcode(int op, byte *s, MRP_Connection *con)
{
	elem *st;
	byte *t, *t2;
	u2 *tu;
	int i;
	long l;
	elem a, b;
	VADDR *addr, *from;

	from=&con->addr;

//	kprint("op %d %X\n", op, op);

	switch(op)
	{
	case MRPOP_NOP:
		break;

	case MRPOP_POP:
		con->stackpos--;
		break;

	case MRPOP_MARK:
		st=con->stack+con->stackpos;
		st[0]=FIXNUM(con->mark);
		con->mark=con->stackpos;
		con->stackpos++;
		break;

	case MRPOP_CONS:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=CONS(st[0], st[1]);
		con->stackpos++;
		break;

	case MRPOP_LIST:
		a=MISC_EOL;
		for(i=con->stackpos-1; i>con->mark; i--)
			a=CONS(con->stack[i], a);
		con->stackpos=con->mark;
		con->mark=TOINT(con->stack[con->stackpos]);
		con->stack[con->stackpos]=a;
		con->stackpos++;
		break;

	case MRPOP_LISTI:
		a=con->stack[con->stackpos-1];
		for(i=con->stackpos-2; i>con->mark; i--)
			a=CONS(con->stack[i], a);
		con->stackpos=con->mark;
		con->mark=TOINT(con->stack[con->stackpos]);
		con->stack[con->stackpos]=a;
		con->stackpos++;
		break;

	case MRPOP_VECTOR:
		a=MISC_EOL;
		for(i=con->stackpos-1; i>con->mark; i--)
			a=CONS(con->stack[i], a);
		con->stackpos=con->mark;
		con->mark=TOINT(con->stack[con->stackpos]);
		con->stack[con->stackpos]=TyFcn_ListToVector(a);
		con->stackpos++;
		break;

	case MRPOP_INVOP:
		con->stackpos--;
		break;

	case MRPOP_INVTYPE:
		con->stackpos--;
		break;

	case MRPOP_REQATTR:
		con->stackpos--;
		st=con->stack+con->stackpos;
		mrp_reqparam(con, st[0]);
		break;
	case MRPOP_REPATTR:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		mrp_repparam(con, st[0], st[1]);
		break;

	case MRPOP_LOOKUP:
//		con->stackpos--;
		break;
	case MRPOP_BIND:
		con->stackpos-=2;
		break;

	case MRPOP_PING:
		con->stackpos--;
		st=con->stack+con->stackpos;
//		kprint("PONG %d\n", TOINT(st[0]));
		MRP_Write(con, st[0]);
		MRPTrans_WriteOpcode(con->sock, MRPOP_PONG);
		break;
	case MRPOP_PONG:
		con->stackpos--;
		con->pong=0;
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

			a=TypeX_GetReference(addr);
			st[0]=a;
			con->stackpos++;
			break;

		case 2:
			addr=TypeX_Alloc("addr", sizeof(VADDR));
			addr->proto=PROTO_IPV4TCP;
			addr->ipv4.addr=htonl(TOINT(st[0]));
			addr->ipv4.port=htons(TOINT(st[1]));

			a=TypeX_GetReference(addr);
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

	case MRPOP_GUID:
		con->stackpos--;
		break;

	case MRPOP_RREF:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=mrp_genref(from, TOINT(st[0]), TOINT(st[1]));
		con->stackpos++;
		break;

	case MRPOP_LREF:
		con->stackpos-=3;
		st=con->stack+con->stackpos;
		addr=TypeX_Data(st[0]);
		st[0]=mrp_genref(addr, TOINT(st[1]), TOINT(st[2]));
		con->stackpos++;
		break;

	case MRPOP_YREF:
		con->stackpos--;
		st=con->stack+con->stackpos;

//		a=MMGC3_GetReference(TOINT(st[0])<<3);
		a=MRP_Import(TOINT(st[0]));
		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: YREF: invalid refnum %d\n",
				TOINT(st[0]));
			break;
		}

		st[0]=a;
		con->stackpos++;
		break;

	case MRPOP_DISPATCH:
		con->stackpos-=4;
		st=con->stack+con->stackpos;

//		kprint("dispatch ");
//		TyFcn_DumpElem(st[0]);
//		sa_print(" ");
//		TyFcn_DumpElem(st[1]);
//		sa_print(" ");
//		TyFcn_DumpElem(st[2]);
//		sa_print(" ");
//		TyFcn_DumpElem(st[3]);
//		sa_print("\n");

//		if(ELEM_SYMBOLP(st[2]))
		if(st[2]==MISC_NULL)
		{
			a=MRP_DispatchSymbol(CAR(st[0]), st[1], CDR(st[0]));
//			b=interp_apply_rax;
			b=MISC_NULL;

//			sa_print("disp sym: ");
//			TyFcn_DumpElem(a);
//			sa_print("\n");

			if(TOINT(st[3]))
			{
				MRP_Write(con, b);
				MRP_Write(con, st[3]);
				MRPTrans_WriteOpcode(con->sock, MRPOP_SETTER);

				MRP_Write(con, a);
				MRP_Write(con, st[3]);
				MRPTrans_WriteOpcode(con->sock, MRPOP_RETURN);
			}
			break;
		}

		a=MRP_Import(TOINT(st[2]));
		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: dispatch: invalid refnum %d\n",
				TOINT(st[2]));
			break;
		}

		if(ELEM_CONTEXTP(a))
		{
			a=Interp_SendThreadFrom(a, st[1], st[0]);
			b=MISC_NULL;
		}else
		{
//			sa_print("disp pat: ");
//			TyFcn_DumpElem(st[0]);
//			sa_print("\n");

//			b=TyFcn_CopyVector(interp_repl_ctx);
			b=Interp_NewCtx();
			Interp_LetDynCtx(b, SYM("from"), st[1]);
			a=Interp_ApplyCtx(b, a, st[0]);

//			b=interp_apply_rax;
			b=MISC_NULL;
		}

		if(TOINT(st[3]))
		{
			MRP_Write(con, b);
			MRP_Write(con, st[3]);
			MRPTrans_WriteOpcode(con->sock, MRPOP_SETTER);

			if(a==MISC_UNDEFINED)a=MISC_FALSE;
			MRP_Write(con, a);
			MRP_Write(con, st[3]);
			MRPTrans_WriteOpcode(con->sock, MRPOP_RETURN);
		}
		break;

	case MRPOP_SETTER:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		mrp_ret_setter[mrp_ret_pos]=st[0];
		break;
	case MRPOP_RETURN:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		mrp_ret_cont[mrp_ret_pos]=TOINT(st[1]);
		mrp_ret_value[mrp_ret_pos++]=st[0];
		break;

	case MRPOP_POPRET:
		con->stackpos--;
		st=con->stack+con->stackpos;
		a=st[0];
		MRP_Write(con, a);
		MRP_Write(con, st[1]);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RETURN);
		break;

	case MRPOP_DROPREF:
		con->stackpos--;
		st=con->stack+con->stackpos;
//		gfxdev_outbuf_pos=0;
//		GfxDev_WriteSLong(st[0]);
		break;

	case MRPOP_SEARCH:
		con->stackpos-=4;
		st=con->stack+con->stackpos;
		break;

	case MRPOP_FOUND:
		con->stackpos-=4;
		st=con->stack+con->stackpos;
		break;


	case MRPOP_STUB:
		con->stackpos--;
		st=con->stack+con->stackpos;
		st[0]=TyObj_ObjStub(st[0]);
		con->stackpos++;
		break;

	case MRPOP_MIRROR:
//		kprint("copy\n");
		con->stackpos-=2;
		st=con->stack+con->stackpos;

		a=MRP_Import(TOINT(st[0]));
		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: COPY: invalid refnum %d\n",
				TOINT(st[0]));
			break;
		}
		a=Builtin_Flatten(a);

//		TyFcn_DumpElem(a);

		if(a==MISC_UNDEFINED)a=MISC_FALSE;
		MRP_Write(con, a);
		MRP_Write(con, st[1]);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RETURN);

		break;

	case MRPOP_NOTIFY:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		if(ELEM_ENVOBJP(st[0]))
			TyObj_Notify(st[0], st[1], MISC_FALSE);
		if(ELEM_TYPEXP(st[0]))
			TypeX_Notify(st[0], st[1], MISC_FALSE);
		break;

	case MRPOP_NOTIFYA:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		if(ELEM_ENVOBJP(st[0]))
			TyObj_Notify(st[0], st[1], MISC_TRUE);
		if(ELEM_TYPEXP(st[0]))
			TypeX_Notify(st[0], st[1], MISC_TRUE);
		break;

	case MRPOP_NOTIFYDEL:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		a=MRP_Import(TOINT(st[0]));
		if(ELEM_ENVOBJP(st[0]))
			TyObj_Notify(st[0], st[1], MISC_NULL);
		if(ELEM_TYPEXP(st[0]))
			TypeX_Notify(st[0], st[1], MISC_NULL);
		break;

	case MRPOP_DELTA:
		con->stackpos-=4;
		st=con->stack+con->stackpos;

//		kprint("delta ");
//		TyFcn_DumpElem(st[0]);
//		kprint(" ");
//		TyFcn_DumpElem(st[1]);
//		kprint(" ");
//		TyFcn_DumpElem(st[2]);
//		kprint(" ");
//		TyFcn_DumpElem(st[3]);
//		kprint("\n");

//		a=MRP_Import(TOINT(st[0]));
//		TyObj_ObjectUnflattenObj(a, st[1]);

		if(ELEM_ENVOBJP(st[0]))
			TyObj_SetSlot(st[0], st[1], st[2]);
		if(ELEM_TYPEXP(st[0]))
			TypeX_Delta(st[0], st[1], st[2]);

		break;

	case MRPOP_DELTA2:
		con->stackpos-=4;
		st=con->stack+con->stackpos;
		break;

	case MRPOP_TYFLAT:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=TypeX_UnFlatten(st[1], st[0]);
		con->stackpos++;
		break;

	case MRPOP_TYSTUB:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=TypeX_Stub(st[1], st[0]);
		con->stackpos++;
		break;

	default:
		kprint("MRP: unknown opcode %d.\n", op);
		return(-1);
		break;
	}
	return(0);
}

#if 0
//s: "dst-guid src-guid id ttl"
//r: src-guid id v4 dst-ip dst-port ttl
int mrp_param_lookup(MRP_Connection *con, char *s)
{
	char buf[256];
	VGUID dst, src;
	int id, ttl;
	int i;
	elem t, cur;
	MRP_Connection *con2;

	s=NET_String2Guid(&dst, s);
	s++;
	s=NET_String2Guid(&src, s);
	s++;
	sscanf(s, "%d %d", &id, &ttl);

	if(NET_GuidEqualP(&dst, mrp_guid))
	{
		sprintf(buf, "FOUND: %s %d v4 %u %d %d",
			NET_Guid2String(&src), id,
			ntohl(local_ipv4addr), mrp_port, 16);
		MRPTrans_WriteParam(con->sock, buf);
		return(0);
	}

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
		t=CAR(cur);
		con2=TypeX_Data(t);

		if(NET_GuidEqualP(&dst, &con2->guid))
		{
			sprintf(buf, "FOUND: %s %d v4 %u %d %d",
				NET_Guid2String(&src), id,
				ntohl(con2->addr.ipv4.addr),
				ntohs(con2->addr.ipv4.port), 16);
			MRPTrans_WriteParam(con->sock, buf);
			return(0);
		}
		cur=CDR(cur);
	}

	//check ttl and if allready passed by here
	ttl--;
	if(!ttl)return(0);

	for(i=0; i<MRP_FINDBUF; i++)
	{
		if(NET_GuidEqualP(&src, &mrp_findbuf[i].guid) &&
			(id==mrp_findbuf[i].id))
			return(0);
	}

	//relay to other nodes
	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
		t=CAR(cur);
		con2=TypeX_Data(t);

		if(con2->state==2)
		{
			sprintf(buf, "FIND: %s %s %d %d",
				NET_Guid2String(&dst),
				NET_Guid2String(&src),
				id, ttl);
			MRPTrans_WriteParam(con2->sock, buf);
		}
		cur=CDR(cur);
	}

	//record return
	memcpy(&mrp_findbuf[mrp_findbuf_rover].guid, &src, sizeof(VGUID));
	mrp_findbuf[mrp_findbuf_rover].id=id;
	mrp_findbuf[mrp_findbuf_rover].con=con;

	mrp_findbuf_rover++;
	mrp_findbuf_rover&=MRP_FINDBUF-1;

	return(0);
}

int mrp_param_found(MRP_Connection *con, char *s)
{
	char buf[256];
	VGUID src;
	int id, ttl, ip, port;
	int i, j;
	MRP_Connection *con2;

	s=NET_String2Guid(&src, s);
	s++;
	sscanf(s, "%d v4 %u %d %d", &id, &ip, &port, &ttl);

	if(NET_GuidEqualP(&src, mrp_guid))
	{
		mrp_found_id=id;

		mrp_found_addr.proto=PROTO_IPV4TCP;
		mrp_found_addr.ipv4.addr=htonl(ip);
		mrp_found_addr.ipv4.port=htons(port);

		return(0);
	}

	ttl--;
	if(!ttl)return(0);

	for(i=0; i<MRP_FINDBUF; i++)
	{
		if(NET_GuidEqualP(&src, &mrp_findbuf[i].guid) &&
			(id==mrp_findbuf[i].id))
		{
			con2=mrp_findbuf[i].con;
			if(con2->state!=2)return(0);

			sprintf(buf, "FOUND: %s %d v4 %u %d %d",
				NET_Guid2String(&src),
				id, ip, port, ttl);
			MRPTrans_WriteParam(con2->sock, buf);
			return(0);
		}
	}
	return(-1);
}

int mrp_param(MRP_Connection *con, char *param)
{
	char buf[256];

	if(!strncmp(param, "NAME=", 5))
	{
		strcpy(con->name, param+5);
//		MRPTrans_WriteParam(con->sock, "GO");
		return(0);
	}

	if(!strncmp(param, "GUID=", 5))
	{
//		strcpy(con->name, param+5);
		NET_String2Guid(&con->guid, param+5);
		kprint("other guid: %s\n", NET_Guid2String(&con->guid));
//		MRPTrans_WriteParam(con->sock, "GO");
		return(0);
	}

	if(!strncmp(param, "PORT=", 5))
	{
//		strcpy(con->name, param+5);
		con->addr.ipv4.port=htons((short)atoi(param+5));
		MRPTrans_WriteParam(con->sock, "GO");
		return(0);
	}

	if(!strncmp(param, "FIND: ", 6))
	{
		mrp_param_lookup(con, param+6);
		return(0);
	}
	if(!strncmp(param, "FOUND: ", 7))
	{
		mrp_param_lookup(con, param+7);
		return(0);
	}

	if(!strcmp(param, "NAME"))
	{
		strcpy(buf, "NAME=");
		strcat(buf, local_hostname);
		MRPTrans_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "GUID"))
	{
		strcpy(buf, "GUID=");
		strcat(buf, NET_Guid2String(mrp_guid));
		MRPTrans_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "PORT"))
	{
		sprintf(buf, "PORT=%d", mrp_port);
		MRPTrans_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "GO"))
	{
		con->state=2;
		return(0);
	}

	return(-1);
}
#endif

char *MRP_Uni2Asc(u2 *s)
{
	char *t;
	int i, j;

	for(i=0; s[i]; i++);

	t=kralloc(i);
	for(j=0; j<(i+1); j++)t[j]=s[j];

	return(t);
}

int mrp_conenter(MRP_Connection *con)
{
	if(!con_framestack_pos)
	{
		con->buffer=kalloc(16484);
		con->bufend=con->buffer;

		return(0);
	}

	con_framestack_pos--;
	con->buffer=con_framestack[con_framestack_pos];
	con->bufend=con->buffer;

	return(0);
}

int mrp_conexit(MRP_Connection *con)
{
	if(con_framestack_pos>=1023)
	{
		kfree(con->buffer);
		return(0);
	}

	con_framestack[con_framestack_pos++]=con->buffer;
	return(0);
}

char *mrp_decode(MRP_Connection *con, byte *b, byte *s, byte *e)
{
	byte *t, *t2, *t3;
	u2 *su, *tu, *tu2;
	byte *s2;
	int sg, st, st2[2], i, len;
	double stf;
	int op;
	elem x;

//	kprint("mrp decode %X\n", *s);

	if(con->rlen)
	{
//		kprint("mrp decode data\n");

		st=e-s;
		i=(st<con->rlen)?st:con->rlen;
		memcpy(con->erbuf, s, i);
		s+=i;
		con->erbuf+=i;
		con->rlen-=i;

		if(!con->rlen)
		{
			switch((con->renc>>3)&7)
			{
			case 0:
				con->stack[con->stackpos++]=
					MMGC3_GetReference(con->rbuf);
				break;
			case 1:
				len=con->erbuf-con->rbuf;
				x=VECTOR_NEWT(len, VECTOR_U8);
				t=TyFcn_ByteVectorBody(x);
				memcpy(t, con->rbuf, len);
				kfree(con->rbuf);
				con->stack[con->stackpos++]=x;
				break;
			case 2:
				len=con->erbuf-con->rbuf;
				t=TypeX_Alloc("mrp-block", len);
				x=TypeX_GetReference(t);
				memcpy(t, con->rbuf, len);
				kfree(con->rbuf);
				con->stack[con->stackpos++]=x;
				break;
			default:
				con->stack[con->stackpos++]=
					MMGC3_GetReference(con->rbuf);
				break;
			}
		}
		return(s);
	}

	switch(*s&3)
	{
	case 0:
//		kprint("mrp decode num %X\n", *s);

		sg=(*s>>3)&7;
		switch(sg)
		{
		case 0:
		case 1:
			switch((*s>>6)&3)
			{
			case 0:
				if((e-s)<2)break;
				if(sg)st=((signed char *)s)[1];
					else st=((unsigned char *)s)[1];
				stf=st;
				s+=2;
				break;
			case 1:
				if((e-s)<3)break;
				st=(s[1]<<8)+s[2];
				if(sg && (st>32767))st|=~0xFFFF;
				stf=st;
				s+=3;
				break;
			case 2:
				if((e-s)<5)break;
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				if(sg && (st>(1<<31)))st|=~0xFFFFFFFF;
				stf=st;
				s+=5;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return(s);
				break;
			}
//			printf("got num %f\n", stf);
			con->stack[con->stackpos++]=FLONUM(stf);
			break;

		case 2:
			switch((*s>>6)&3)
			{
			case 2:
				if((e-s)<5)break;
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				stf=*(float *)&st;
				st=stf;
				s+=5;
				break;
			case 3:
				if((e-s)<9)break;
				st2[1]=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				st2[0]=(s[5]<<24)+(s[6]<<16)+(s[7]<<8)+s[8];
				stf=*(double *)&st2;
				st=stf;
				s+=9;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return(s);
				break;
			}
//			printf("got num %f\n", stf);
			con->stack[con->stackpos++]=FLONUM(stf);
			break;

		case 3:
			switch((*s>>6)&3)
			{
			case 0:
				if((e-s)<2)break;
				st=((unsigned char *)s)[1];
				s+=2;
				break;
			case 1:
				if((e-s)<3)break;
				st=(s[1]<<8)+s[2];
				s+=2;
				break;
			case 2:
				if((e-s)<5)break;
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				s+=2;
				break;
			default:
				kprint("GfxDev: number:misc parse error.\n");
				return(s);
				break;
			}
			switch(st&0xf)
			{
			case 0:
				switch(st)
				{
				case MRPVAL_FALSE:
					con->stack[con->stackpos++]=
						MISC_FALSE;
					break;
				case MRPVAL_TRUE:
					con->stack[con->stackpos++]=
						MISC_TRUE;
					break;
				case MRPVAL_NULL:
					con->stack[con->stackpos++]=
						MISC_NULL;
					break;
				case MRPVAL_EOL:
					con->stack[con->stackpos++]=
						MISC_EOL;
					break;
				default:
					con->stack[con->stackpos++]=
						MISC_UNDEFINED;
					break;
				}
				break;
			case 1:
				con->stack[con->stackpos++]=
					ELEM_FROMCHAR(st>>4);
				break;
			case 2:
				con->stack[con->stackpos++]=
					ELEM_FROMSPECIAL(st>>4);
				break;
			default:
				con->stack[con->stackpos++]=
					MISC_UNDEFINED;
				break;
			}
//			printf("got misc\n");
			break;
		default:
			sa_fatal("mrp decode num, unknown type %d\n", sg);
			break;
		}
		break;
	case 1:
		if((e-s)<2)break;
		st=((s[0]>>4)&15)+(s[1]<<4);
		s+=2;

//		kprint("mrp decode op\n");

		//handle recursion
//		t=b;
//		while(s<e)*t++=*s++;
//		s=b;
//		e=t;
//		con->bufend=e;

		mrp_conenter(con);

		mrp_opcode(st, s, con);

		mrp_conexit(con);

		con->buffer=b;
		con->bufend=e;

		//more for recursion
//		s=b;
//		e=con->bufend;

		break;
	case 2:
		if((e-s)<2)break;
		st=0;
		t=s+1;
		while(t<e)
		{
			st=(st<<7)+(*t&0x7f);
			if(!(*t&0x80))break;
			t++;
		}
		if(!(t-e))break;
		len=st;
		t++;
		if((e-t)<len)break;

//		kprint("MRP: obj %d, len %d\n", (*s>>3)&31, len);

		switch((*s>>3)&31)
		{
		case 1:
			con->renc=*t++;
			con->rlen=len-1;
			con->rbuf=kalloc(con->rlen);
			con->erbuf=con->rbuf;
			s=t;
			break;
		case 2:
			tu=kralloc(len+2);

			s2=t;
			tu2=tu;
			i=len/2;
			while(i--)
			{
				*tu2++=(s2[0]<<8)+s2[1];
				s2+=2;
			}
			*tu2++=0;
			s=t+len;
			con->stack[con->stackpos++]=
				SYM(MRP_Uni2Asc(tu));

//			kprint("got sym %s\n", MRP_Uni2Asc(tu));
			break;

		case 3:
			tu=kralloc(len+2);

//			su=(u2 *)t;
			s2=t;
			tu2=tu;
			i=len/2;
//			while(i--)*tu2++=*su++;
			while(i--)
			{
				*tu2++=(s2[0]<<8)+s2[1];
				s2+=2;
			}
			*tu2++=0;
			s=t+len;
			con->stack[con->stackpos++]=
				TyFcn_String16(tu);
			break;

		case 4:
			break;

		case 5:
			t2=kralloc(len+2);

			s2=t;
			t3=t2;
			i=len;
			while(i--)*t3++=*s2++;
			*t3++=0;
			s=t+len;
			con->stack[con->stackpos++]=SYM(t2);
			break;

		case 6:
			t2=kralloc(len+2);

			s2=t;
			t3=t2;
			i=len;
			while(i--)*t3++=*s2++;
			*t3++=0;
			s=t+len;
			con->stack[con->stackpos++]=STRING(t2);
			break;

		default:
			kprint("MRP: object parse error.\n");
			sa_abort();

			return(s);
			break;
		}
		break;
	default:
		kprint("MRP: cmd parse error.\n");
		sa_abort();

		return(s);
		break;
	}
	return(s);
}

int mrp_handle(MRP_Connection *con)
{
	byte *s, *t;
	u2 *su, *tu, *tu2;
	int sg, st, st2[2], i, len;
	double stf;
	int op;
	elem x;

	static int last;
	int stime, ust;

	if(!con->state || (con->state==3))
		return(-1);

	stime=Sys_TimeMS();
	ust=0;

//	MRP_SendDeltas(con);

//	kprint("MRP_Handle %X\n", con);

	if(!con->buffer)
	{
		con->buffer=kalloc(16384);
		con->bufend=con->buffer;
	}
	s=con->buffer;

//	kprint("MRP: handle, %d bytes buffer.\n", e-s);

	while(1)
	{
		st=16384-(con->bufend-s);
		len=0;
		if(con->state && (con->state!=3))
			len=vfread(con->bufend, 1, st, con->sock);

		if(len<0)
		{
			//connection error, kill
			con->state=3;
			len=0;
		}

		con->bufend+=len;

		if(len>0)
		{
//			kprint("MRP: recv %d, %d t:%d\n", len,
//				Sys_TimeMS()-last, Sys_TimeMS());
			ust=1;
		}

		if(s==con->bufend)break;

		t=s;
		s=mrp_decode(con, con->buffer, s, con->bufend);

		if(s==t)break; //no activity

		//shift buffer...
		if((s-con->buffer)>4096)
		{
			t=con->buffer;
			while(s<con->bufend)*t++=*s++;
			s=con->buffer;
			con->bufend=t;
		}
	}

	t=con->buffer;
	while(s<con->bufend)*t++=*s++;
	s=con->buffer;
	con->bufend=t;

	last=Sys_TimeMS();

//	if(ust)kprint("MRP: handle: took %dms\n", last-stime);

	return(len);
}

int MRP_Poll()
{
	VADDR addr;
	int i;
	VFILE *newsock;
	MRP_Connection *con;
	elem t, cur;

	int stime;

	if(!mrp_sock)return(-1);

	stime=Sys_TimeMS();

	UDPBUF_Poll();

	while(1)
	{
		vfioctls(mrp_sock, "accept", &newsock, &addr);
		if(!newsock)break;

		kprint("MRP: recieved connection\n");

		con=MRP_NewCon(&addr);
		strcpy(con->name, "(connect)");
		con->state=1;
		con->sock=newsock;

//		MRPTrans_WriteParam(newsock, "MRP");
		MRP_WriteParam(newsock, "NAME");
		MRP_WriteParam(newsock, "GUID");
		MRP_WriteParam(newsock, "PORT");
	}

	while(1)
	{
		vfioctls(mrp_sock_udp, "accept", &newsock, &addr);
		if(!newsock)break;

		kprint("MRP: recieved connection\n");

		con=MRP_NewCon(&addr);
		strcpy(con->name, "(connect)");
		con->state=1;
		con->sock=newsock;

//		MRPTrans_WriteParam(newsock, "MRP");
		MRP_WriteParam(newsock, "NAME");
		MRP_WriteParam(newsock, "GUID");
		MRP_WriteParam(newsock, "PORT");
	}

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
//		mrp_connum=i;
		t=CAR(cur);
		con=TypeX_Data(t);

		mrp_handle(con);
		MRP_SendDeltas(con);
//		if(con->state==2)		
//			MRP_Ping(con);
		vfflush(con->sock);

		cur=CDR(cur);
	}

//	UDPBUF_Poll();
//	UDPBUF_Poll();

//	kprint("MRP Poll: took %dms\n", Sys_TimeMS()-stime);

	return(0);
}

int MRP_FindGuid(VGUID *guid, VADDR *addr)
{
	char buf[256];
	VGUID dst, src;
	int id, ttl;
	int i;
	elem t, cur;
	MRP_Connection *con;

#if 0
	for(i=0; i<MRP_MAXCONS; i++)
	{
		t=VECTOR_REF(mrp_convec, i);
		if(ELEM_TYPEXP(t))
		{
			con=TypeX_Data(t);

			if(NET_GuidEqualP(&dst, &con->guid))
			{
				memcpy(addr, &con->addr)
				if(!nolocal)return(0);
			}
		}
	}
#endif

	id=mrp_find_id++;
	ttl=16;

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
		t=CAR(cur);
		con=TypeX_Data(t);

		if(con->state==2)
		{
			sprintf(buf, "FIND: %s %s %d %d",
				NET_Guid2String(guid),
				NET_Guid2String(mrp_guid),
				id, ttl);
//			MRPTrans_WriteParam(con->sock, buf);
		}
		cur=CDR(cur);
	}

	mrp_found_id=-1;
	i=Sys_TimeMS();
	while(mrp_found_id!=id)
	{
		MRP_Poll();
		kusleep(1000);
		if((Sys_TimeMS()-i)>30000)return(-1);
	}
	memcpy(addr, &mrp_found_addr, sizeof(VADDR));

	return(0);
}

int MRP_Ping(MRP_Connection *con)
{
	int time;
	static int ping=0;

	if(con->pong || ping)return(-1);

	time=Sys_TimeMS();
	con->pong=1;
	ping=1;

	MRPTrans_WriteUInt(con->sock, time);

	MRPTrans_WriteOpcode(con->sock, MRPOP_PING);
	while(con->pong && (con->state!=3))
	{
		MRP_Poll();
		kusleep(1000);
	}
	kprint("IDLE PING: %dms\n", Sys_TimeMS()-time);
	ping=0;
	return(0);
}
