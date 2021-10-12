/*
tcp based.

 */

#include <general.h>
#include <graphics/render.h>
#include <graphics/gfxapi.h>
#include <net/bgbmrp.h>

#include <string.h>

int mrp_port;
VFILE *mrp_sock;
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
extern elem interp_repl_ctx;
extern elem interp_cur_ctx;
extern elem interp_apply_rax;

elem mrp_handlers; //((sym handler) ...)
elem mrp_scion_lst;

int mrp_ret_value[8];
int mrp_ret_setter[8];
int mrp_ret_cont[8];
int mrp_ret_pos;

extern char local_hostname[64];
extern unsigned long local_ipv4addr;
extern byte local_ipv6addr[16];

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

	mrp_con_lst=CONS(MMGC3_GetReference(con), mrp_con_lst);

	return(con);
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

	GfxApi_WriteParam(sock, "MRP");
	GfxApi_WriteParam(sock, "NAME");
	GfxApi_WriteParam(sock, "GUID");
	GfxApi_WriteParam(sock, "PORT");

	i=Sys_TimeMS();
	while(con->state==1)
	{
		t=Sys_TimeMS();
		if((t-i)>10000)break;
		MRP_Poll();
		kusleep(1000);
	}

	return(con);
}

int MRP_TryReconnect(MRP_Connection *con)
{
	int i, t;
	VFILE *sock;
	VGUID guid;

	kprint("MRP_TryReconnect %X\n", con);

	memcpy(&guid, &con->guid, 16);

	sock=TCP_OpenConnect(&con->addr);
	if(!sock)
	{
//		kprint("open connection fail (open socket).\n");
//		return(-1);

		kprint("no sock\n");

		i=MRP_FindGuid(&guid, &con->addr);
		if(i==-1)return(-1);
		return(MRP_TryReconnect(con));
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
		if(i==-1)return(-1);
		return(MRP_TryReconnect(con));
	}

	GfxApi_WriteParam(sock, "MRP");
	GfxApi_WriteParam(sock, "NAME");
	GfxApi_WriteParam(sock, "GUID");
	GfxApi_WriteParam(sock, "PORT");

	i=Sys_TimeMS();
	while(con->state==1)
	{
		t=Sys_TimeMS();
		if((t-i)>10000)break;
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

		if(i==-1)return(-1);
		return(MRP_TryReconnect(con));
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
	ref->con=MMGC3_GetReference(con);
	ref->pid=pid;
	ref->type=type;

	return(MMGC3_GetReference(ref));
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

	case MRPOP_RCONS:
		con->stackpos-=2;
		st=con->stack+con->stackpos;
		st[0]=CONS(st[1], st[0]);
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

	case MRPOP_BYTEVEC:
		con->stackpos-=2;
		st=con->stack+con->stackpos;

		t=ELEM_TOOBJECT(st[0]);
		l=TOINT(st[1]);
		a=VECTOR_NEWT(l, VECTOR_U8);
		t2=TyFcn_ByteVectorBody(a);

		memcpy(t2, t, l);

		st[0]=a;
		con->stackpos++;
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
		con->stackpos-=3;
		st=con->stack+con->stackpos;
//		break;

		if(ELEM_SYMBOLP(st[2]))
		{
			MRP_DispatchSymbol(st[2], st[1], st[0]);
			break;
		}
//		a=MMGC3_GetReference(TOINT(st[2])<<3);
		a=MRP_Import(TOINT(st[2]));

		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: dispatch: invalid refnum\n");
			break;
		}

		if(ELEM_CONTEXTP(a))
		{
			Interp_SendThreadFrom(a, st[1], st[0]);
		}else
		{
			b=TyFcn_CopyVector(interp_repl_ctx);
			Interp_LetDynCtx(b, SYM("from"), st[1]);
			Interp_ApplyCtxTh(b, a, st[0]);
		}
		break;

	case MRPOP_RDISPATCH:
		con->stackpos-=4;
		st=con->stack+con->stackpos;

		if(ELEM_SYMBOLP(st[2]))
		{
			a=MRP_DispatchSymbol(st[2], st[1], st[0]);
			b=interp_apply_rax;

//			sa_print("disp sym: ");
//			TyFcn_DumpElem(a);
//			sa_print("\n");

			MRP_Write(con, b);
			MRP_Write(con, st[3]);
			GfxApi_WriteOpcode(con->sock, MRPOP_SETTER);

			MRP_Write(con, a);
			MRP_Write(con, st[3]);
			GfxApi_WriteOpcode(con->sock, MRPOP_RETURN);
			break;
		}

//		a=MMGC3_GetReference(TOINT(st[2])<<3);
		a=MRP_Import(TOINT(st[2]));
		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: rdispatch: invalid refnum %d\n",
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

			b=TyFcn_CopyVector(interp_repl_ctx);
			Interp_LetDynCtx(b, SYM("from"), st[1]);
			a=Interp_ApplyCtx(b, a, st[0]);

			b=interp_apply_rax;
		}
		MRP_Write(con, b);
		MRP_Write(con, st[3]);
		GfxApi_WriteOpcode(con->sock, MRPOP_SETTER);

		if(a==MISC_UNDEFINED)a=MISC_FALSE;
		MRP_Write(con, a);
		MRP_Write(con, st[3]);
		GfxApi_WriteOpcode(con->sock, MRPOP_RETURN);

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

	case MRPOP_COPY:
		kprint("copy\n");
		con->stackpos-=2;
		st=con->stack+con->stackpos;

//		a=MMGC3_GetReference(TOINT(st[0])<<3);
		a=MRP_Import(TOINT(st[0]));
		if(a==MISC_NULL || a==MISC_UNDEFINED)
		{
			kprint("MRP: COPY: invalid refnum %d\n",
				TOINT(st[0]));
			break;
		}
		a=Builtin_Flatten(a);

		if(a==MISC_UNDEFINED)a=MISC_FALSE;
		MRP_Write(con, a);
		MRP_Write(con, st[1]);
		GfxApi_WriteOpcode(con->sock, MRPOP_RETURN);

		break;

	case MRPOP_FLAT:
		con->stackpos--;
		st=con->stack+con->stackpos;
		a=st[0];

		t=con->buffer;
		t2=con->bufend;
		con->buffer=kalloc(16384);
		con->bufend=con->buffer;

		b=Builtin_Eval(a);

		kfree(con->buffer);
		con->buffer=t;
		con->bufend=t2;

//		kprint("flat ");
//		TyFcn_DumpElem(a);
//		kprint(" -> ");
//		TyFcn_DumpElem(b);
//		kprint("\n");

		st[0]=b;
		con->stackpos++;
		break;

	case MRPOP_BEGINFLAT:
		TyObj_BeginUnflatten();
		break;

	default:
		kprint("MRP: unknown opcode %d.\n", op);
		return(-1);
		break;
	}
	return(0);
}

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
		GfxApi_WriteParam(con->sock, buf);
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
			GfxApi_WriteParam(con->sock, buf);
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
			GfxApi_WriteParam(con2->sock, buf);
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
			GfxApi_WriteParam(con2->sock, buf);
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
//		GfxApi_WriteParam(con->sock, "GO");
		return(0);
	}

	if(!strncmp(param, "GUID=", 5))
	{
//		strcpy(con->name, param+5);
		NET_String2Guid(&con->guid, param+5);
		kprint("other guid: %s\n", NET_Guid2String(&con->guid));
//		GfxApi_WriteParam(con->sock, "GO");
		return(0);
	}

	if(!strncmp(param, "PORT=", 5))
	{
//		strcpy(con->name, param+5);
		con->addr.ipv4.port=htons((short)atoi(param+5));
		GfxApi_WriteParam(con->sock, "GO");
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
		GfxApi_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "GUID"))
	{
		strcpy(buf, "GUID=");
		strcat(buf, NET_Guid2String(mrp_guid));
		GfxApi_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "PORT"))
	{
		sprintf(buf, "PORT=%d", mrp_port);
		GfxApi_WriteParam(con->sock, buf);
		return(0);
	}

	if(!strcmp(param, "GO"))
	{
		con->state=2;
		return(0);
	}

	return(-1);
}

char *mrp_decode(MRP_Connection *con, byte *b, byte *s, byte *e)
{
	byte *t;
	u2 *su, *tu, *tu2;
	int sg, st, st2[2], i, len;
	double stf;
	int op;
	elem x;

	if(con->rlen)
	{
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
				break;
			case 2:
				len=con->erbuf-con->rbuf;
				t=TypeX_Alloc("mrp-block", len);
				x=MMGC3_GetReference(t);
				memcpy(t, con->rbuf, len);
				kfree(con->rbuf);
				break;
			default:
				break;
			}
		}
		return(s);
	}

	switch(*s&3)
	{
	case 0:
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

		case 4:
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
		}
		break;
	case 1:
		if((e-s)<2)break;
		st=((s[0]>>4)&15)+(s[1]<<4);
		s+=2;

		//handle recursion
		t=b;
		while(s<e)*t++=*s++;
		s=b;
		e=t;
		con->bufend=e;

		mrp_opcode(st, s, con);

		//more for recursion
		s=b;
		e=con->bufend;

		break;
	case 2:
		switch((*s>>3)&31)
		{
		case 1:
			if((e-s)<6)break;
			con->renc=s[1];
			st=(s[2]<<24)+(s[3]<<16)+(s[4]<<8)+s[5];
			con->rlen=st;
			con->rbuf=kalloc(con->rlen);
			con->erbuf=con->rbuf;
			s+=6;
			break;
		case 2:
			if((e-s)<2)break;
			st=s[1];
			if((e-s)<(st+2))break;

			t=kalloc(st+1);
			strncpy(t, s+2, st);
			t[st]=0;

			s+=st+2;
			con->stack[con->stackpos++]=SYM(t);
//			kprint("parsed symbol \"%s\"\n", t);
			break;

		case 3:
			if((e-s)<3)break;
			st=(s[1]<<8)+s[2];
			if((e-s)<(st*2)+3)break;

			tu=kalloc((st*2)+2);
//			strncpy(t, s+2, s[1]);

			su=(u2 *)(s+3);
			tu2=tu;
			i=st;
			while(i--)*tu2++=*su++;
			*tu2++=0;
			s+=(st*2)+3;
			con->stack[con->stackpos++]=
				TyFcn_String(GfxDev_Uni2Asc(tu));
//			kprint("parsed string \"%s\"\n", GfxDev_Uni2Asc(tu));
			break;

		case 4:
			if((e-s)<3)break;
			st=(s[1]<<8)+s[2];
			if((e-s)<(st+3))break;

			t=kalloc(st+1);
			strncpy(t, s+3, st);
			t[st]=0;

			s+=st+3;

			//do something...
			kprint("MRP: recieved param '%s'\n", t);
			mrp_param(con, t);
			kfree(t);

			break;

		case 5:
			if((e-s)<5)break;
			op=(s[1]<<8)+s[2];
			len=(s[3]<<8)+s[4];
			if((e-s)<(len*2)+5)break;

			switch(op)
			{
			default:
				break;
			}

			s+=(len*2)+5;
			break;

		default:
			kprint("MRP: object parse error.\n");
			return(s);
			break;
		}
		break;
	default:
		kprint("MRP: cmd parse error.\n");
		return(s);
		break;
	}
	return(s);
}

int mrp_handle(MRP_Connection *con)
{
	byte *buf;
	byte *s, *e, *t;
	u2 *su, *tu, *tu2;
	int sg, st, st2[2], i, len;
	double stf;
	int op;
	elem x;

	if(!con->state || (con->state==3))
		return(-1);

//	kprint("MRP_Handle %X\n", con);

	if(!con->buffer)
	{
		con->buffer=kalloc(16384);
		con->bufend=con->buffer;
	}
	buf=con->buffer;

	s=buf;
	e=con->bufend;

//	kprint("MRP: handle, %d bytes buffer.\n", e-s);

	while(1)
	{
		st=16384-(e-s);
		len=0;
		if(con->state && (con->state!=3))
			len=vfread(e, 1, st, con->sock);

		if(len<0)
		{
			//connection error, kill
			con->state=3;
			len=0;
		}

		e+=len;

		if(len>0)kprint("MRP: recv %d\n", len);

		if(s==e)break;

		s=mrp_decode(con, buf, s, e);

		if(!(s-buf))break; //no activity

		//shift buffer...
		t=buf;
		while(s<e)*t++=*s++;
		s=buf;
		e=t;
		con->bufend=e;
	}

	return(len);
}

int MRP_Poll()
{
	VADDR addr;
	int i;
	VFILE *newsock;
	MRP_Connection *con;
	elem t, cur;

	if(!mrp_sock)return(-1);

	while(1)
	{
		vfioctls(mrp_sock, "accept", &newsock, &addr);
		if(!newsock)break;

		kprint("MRP: recieved connection\n");

		con=MRP_NewCon(&addr);
		strcpy(con->name, "(connect)");
		con->state=1;
		con->sock=newsock;

		GfxApi_WriteParam(newsock, "MRP");
		GfxApi_WriteParam(newsock, "NAME");
		GfxApi_WriteParam(newsock, "GUID");
		GfxApi_WriteParam(newsock, "PORT");
	}

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
//		mrp_connum=i;
		t=CAR(cur);
		con=TypeX_Data(t);
		mrp_handle(con);
		cur=CDR(cur);
	}

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
			GfxApi_WriteParam(con->sock, buf);
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
