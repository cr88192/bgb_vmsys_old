#include <general.h>
#include <net/mrp01.h>

#include <string.h>


int mrp_port;
VFILE *mrp_sock;
VFILE *mrp_sock_udp;

VGUID *mrp_guid;
elem mrp_guid_elem;

//MRP_Connection mrp_con[MRP_MAXCONS];
//elem mrp_convec;
//int mrp_connum;
elem mrp_con_lst;

MRP_FindBuf mrp_findbuf[MRP_FINDBUF];
int mrp_findbuf_rover;

//elem mrp_stacks;

//extern elem interp_repl_ctx;
//extern elem interp_cur_ctx;
//extern elem interp_apply_rax;

elem mrp_handlers; //((sym handler) ...)
elem mrp_scion_lst;

elem mrp_ret_value[8];
elem mrp_ret_setter[8];
int mrp_ret_cont[8];
int mrp_ret_pos=0;

elem mrp_objstack; //help send circular structures

extern char local_hostname[64];
extern unsigned long local_ipv4addr;
extern byte local_ipv6addr[16];

int mrp_continuation=1;

VGUID mrp_null_guid;

int MRP_Export(elem c)
{
	elem cur, lst;
	int i;

	i=0;
	lst=MISC_EOL;
	cur=mrp_scion_lst;
	while(ELEM_CONSP(cur))
	{
		if(CAR(cur)==c)return(i);
		lst=cur;
		cur=CDR(cur);
		i++;
	}
	if(!ELEM_CONSP(lst))mrp_scion_lst=CONS(c, MISC_EOL);
		else TyFcn_SetCdr(lst, CONS(c, MISC_EOL));
	return(i);
}

elem MRP_Import(int n)
{
	elem cur;
	int i;

	i=n;
	cur=mrp_scion_lst;
	while(ELEM_CONSP(cur) && i)
	{
		cur=CDR(cur);
		i--;
	}
	if(ELEM_CONSP(cur))return(CAR(cur));
	kprint("MRP_Import: invalid ref %d\n", n);
	return(MISC_UNDEFINED);
}

MRP_LongRef *MRP_CheckLinks(MRP_Connection *con, elem lst)
{
	MRP_LongRef *ref;
	MRP_Connection *con2;
	elem cur;

	cur=lst;

	while(ELEM_CONSP(cur))
	{
		if(TypeX_TypeP(CAAR(cur), "longref"))
		{
			ref=TypeX_Data(CAAR(cur));
			con2=TypeX_Data(ref->con);

			if(con==con2)return(ref);
		}

		cur=CDR(cur);
	}
	return(NULL);
}

int MRP_CheckObjStack(elem c)
{
	elem cur;
	int i;

	i=0;
	cur=mrp_objstack;
	while(cur!=MISC_EOL)
	{
		if(CAR(cur)==c)return(i);
		i++;
		cur=CDR(cur);
	}
	return(-1);
}

extern int tyobj_notify;

int MRP_Write(MRP_Connection *con, elem c)
{
	MRP_LongRef *ref;
	VADDR *addr;
	int i, l;
	void *p;
	MRP_Connection *con2;
	elem t, t2, cur;
	static int inflat=0;

	if(TypeX_TypeP(c, "longref"))
	{
		ref=TypeX_Data(c);
		con2=TypeX_Data(ref->con);
		addr=&con2->addr;

		if(con2 != con)
//		if(1)
		{
			MRPTrans_WriteULong(con->sock, ntohl(addr->ipv4.addr));
			MRPTrans_WriteUShort(con->sock, ntohs(addr->ipv4.port));
			MRPTrans_WriteSInt(con->sock, MRPVAL_IPV4TCP);
			MRPTrans_WriteOpcode(con->sock, MRPOP_ADDR);

			MRPTrans_WriteULong(con->sock, ref->pid);
			MRPTrans_WriteUInt(con->sock, ref->type);

			MRPTrans_WriteOpcode(con->sock, MRPOP_LREF);
		}else
		{
			MRPTrans_WriteULong(con->sock, ref->pid);
			MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);
		}
	}

	if(ELEM_TYPEXP(c))
	{
		t=TypeX_Mirrors(c);
		ref=MRP_CheckLinks(con, t);
		if(ref)
		{
			MRPTrans_WriteULong(con->sock, ref->pid);
			MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);
			return(0);
		}

		if(t!=MISC_UNDEFINED)
		{
			t=CONS(CONS(TyFcn_Box(c), CONS(MISC_TRUE, MISC_EOL)), t);
			MRP_Write(con, t);
			MRP_Write(con, TypeX_Sym(c));
			MRPTrans_WriteOpcode(con->sock, MRPOP_TYSTUB);
			return(0);
		}
		t=TypeX_Flatten(c);
		if(t!=MISC_UNDEFINED)
		{
			MRP_Write(con, t);
			MRP_Write(con, TypeX_Sym(c));
			MRPTrans_WriteOpcode(con->sock, MRPOP_TYFLAT);
			return(0);
		}

		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_GENERAL_BI);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}

	if(ELEM_CONSP(c))
	{
		if(Builtin_ListP(c)==MISC_TRUE)
		{
			MRPTrans_WriteOpcode(con->sock, MRPOP_MARK);
			cur=c;
			while(ELEM_CONSP(cur))
			{
				MRP_Write(con, CAR(cur));
				cur=CDR(cur);
			}
			MRPTrans_WriteOpcode(con->sock, MRPOP_LIST);
			return(0);
		}
		if(LENGTH(c)>2)
		{
			MRPTrans_WriteOpcode(con->sock, MRPOP_MARK);
			cur=c;
			while(ELEM_CONSP(cur))
			{
				MRP_Write(con, CAR(cur));
				cur=CDR(cur);
			}
			MRP_Write(con, cur);
			MRPTrans_WriteOpcode(con->sock, MRPOP_LISTI);
			return(0);
		}

		MRP_Write(con, CAR(c));
		MRP_Write(con, CDR(c));
		MRPTrans_WriteOpcode(con->sock, MRPOP_CONS);
		return(0);
	}
	if(ELEM_FIXNUMP(c))
	{
		MRPTrans_WriteSInt(con->sock, TOINT(c));
		return(0);
	}
	if(ELEM_FLONUMP(c))
	{
		MRPTrans_WriteFloat(con->sock, TOFLOAT(c));
		return(0);
	}
	if(ELEM_STRINGP(c))
	{
		MRPTrans_WriteString(con->sock, ELEM_TOSTRING(c));
		return(0);
	}
	if(ELEM_SYMBOLP(c))
	{
		MRPTrans_WriteSymbol(con->sock, ELEM_TOSYMBOL(c));
		return(0);
	}

	if(ELEM_BOXP(c))
	{
		t=TyFcn_UnBox(c);
		MRPTrans_WriteUInt(con->sock, MRP_Export(t));
		if(ELEM_ENVOBJP(t))
			MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_ENVOBJ);
			else MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_FUNCTION);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}

	if(ELEM_CONTEXTP(c))
	{
//		MRPTrans_WriteULong(con->sock, c>>3);
		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_CONTEXT);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}
	if(ELEM_ENVOBJP(c))
	{
#if 0
		t=TyObj_GetLinks(c);
		ref=MRP_CheckLinks(con, t);
		if(ref)
		{
			MRPTrans_WriteULong(con->sock, ref->pid);
			MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);
			return(0);
		}

		i=MRP_CheckObjStack(c);
		if(i!=-1)
		{
			kprint("obj stackref %d\n", i);
			MRPTrans_WriteConst(con->sock, (i<<4)+MRPVAL_STACK);
			return(0);
		}

		t2=mrp_objstack;
		mrp_objstack=CONS(c, t2);

		MRPTrans_WriteOpcode(con->sock, MRPOP_BEGINFLAT);
		t=Builtin_Flatten(c);
		MRP_Write(con, t);
		MRPTrans_WriteOpcode(con->sock, MRPOP_FLAT);

//		mrp_objstack=t2;
#endif
#if 0
		//HACK: control condition where object sends self in links...
		if(!inflat && !tyobj_notify)
		{
			inflat=1;
			t=Builtin_Flatten(c);
			MRP_Write(con, t);
			MRPTrans_WriteOpcode(con->sock, MRPOP_FLAT);
			inflat=0;
		}else
		{
//			MRPTrans_WriteULong(con->sock, c>>3);
			MRPTrans_WriteUInt(con->sock, MRP_Export(c));
			MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_ENVOBJ);
			MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		}
#endif

//		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
//		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_ENVOBJ);
//		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);

		t=TyObj_GetLinks(c);
		ref=MRP_CheckLinks(con, t);
		if(ref)
		{
			MRPTrans_WriteULong(con->sock, ref->pid);
			MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);
			return(0);
		}

		t=CONS(CONS(TyFcn_Box(c), CONS(MISC_TRUE, MISC_EOL)), t);
		MRP_Write(con, t);
		MRPTrans_WriteOpcode(con->sock, MRPOP_STUB);

		return(0);
	}
	if(ELEM_ENVP(c))
	{
//		MRPTrans_WriteULong(con->sock, c>>3);
		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_ENV);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}
	if(ELEM_CLOSUREP(c))
	{
//		MRPTrans_WriteULong(con->sock, c>>3);
		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_CLOSURE);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}
	if(ELEM_FUNCTIONP(c))
	{
//		MRPTrans_WriteULong(con->sock, c>>3);
		MRPTrans_WriteUInt(con->sock, MRP_Export(c));
		MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_FUNCTION);
		MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);
		return(0);
	}

	if(ELEM_BYTEVECTORP(c))
	{
		l=VECTOR_LEN(c);
		p=TyFcn_ByteVectorBody(c);
		MRPTrans_WriteData(con->sock, p, l, MRPVAL_DATA_BYTEVECTOR);
//		MRPTrans_WriteUInt(con->sock, l);
//		MRPTrans_WriteOpcode(con->sock, MRPOP_BYTEVEC);
		return(0);
	}

	if(ELEM_VECTORP(c))
	{
		l=VECTOR_LEN(c);
		MRPTrans_WriteOpcode(con->sock, MRPOP_MARK);
		for(i=0; i<l; i++)
			MRP_Write(con, VECTOR_REF(c, i));
		MRPTrans_WriteOpcode(con->sock, MRPOP_VECTOR);
		return(0);
	}

	if(ELEM_CHARP(c))
	{
		MRPTrans_WriteConst(con->sock,
			(ELEM_TOCHAR(c)<<4)+1);
		return(0);
	}

	switch(c)
	{
	case MISC_TRUE:
		MRPTrans_WriteConst(con->sock, MRPVAL_TRUE);
		return(0);
		break;
	case MISC_FALSE:
		MRPTrans_WriteConst(con->sock, MRPVAL_FALSE);
		return(0);
		break;
	case MISC_NULL:
		MRPTrans_WriteConst(con->sock, MRPVAL_NULL);
		return(0);
		break;
	case MISC_EOL:
		MRPTrans_WriteConst(con->sock, MRPVAL_EOL);
		return(0);
		break;
	default:
		break;
	}

	MRPTrans_WriteConst(con->sock, MRPVAL_NULL);

	return(-1);
}

int MRP_SendDeltas(MRP_Connection *con)
{
	elem cur, msg;
	MRP_LongRef *ref;
	int d;

	if(con->deltas==MISC_EOL)return(-1);
	if(con->pong)return(-1);

	if((Sys_TimeMS()-con->lastdelta)<100)return(-1);

	d=Sys_TimeMS()-con->lastdelta;
	con->lastdelta=Sys_TimeMS();

//	kprint("PING1 %d t:%d\n", d, Sys_TimeMS());

	cur=MISC_EOL;
	cur=con->deltas;
	while(ELEM_CONSP(cur))
	{
		msg=CAR(cur);

		ref=TypeX_Data(CAR(msg));
		MRPTrans_WriteUInt(con->sock, ref->pid);
		MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

		MRP_Write(con, CADR(msg));
		MRP_Write(con, CADDR(msg));
		MRPTrans_WriteUInt(con->sock, 0);
		MRPTrans_WriteOpcode(con->sock, MRPOP_DELTA);

		cur=CDR(cur);
	}

	con->deltas=MISC_EOL;
	con->pong=1;

	d=Sys_TimeMS();
//	kprint("PING2 t:%d\n", d);

	MRPTrans_WriteUInt(con->sock, d);
	MRPTrans_WriteOpcode(con->sock, MRPOP_PING);

	return(0);
}

int MRP_AddDelta(MRP_Connection *con, elem to, elem var, elem val)
{
	elem cur, msg, lst;

	lst=MISC_EOL;
	cur=con->deltas;
	while(ELEM_CONSP(cur))
	{
		msg=CAR(cur);
		if((CAR(msg)==to) && (CADR(msg)==var))
		{
			msg=CONS(to, CONS(var, CONS(val, MISC_EOL)));
			TyFcn_SetCar(cur, msg);
			return(0);
		}

		lst=cur;
		cur=CDR(cur);
	}
	if(lst!=MISC_EOL)
	{
		msg=CONS(to, CONS(var, CONS(val, MISC_EOL)));
		TyFcn_SetCdr(lst, CONS(msg, MISC_EOL));
		return(0);
	}

	msg=CONS(to, CONS(var, CONS(val, MISC_EOL)));
	con->deltas=CONS(msg, MISC_EOL);
	return(0);
}

int MRP_Notify(elem to, elem from)
{
	MRP_LongRef *ref;
	MRP_Connection *con;

	ref=TypeX_Data(to);
	con=TypeX_Data(ref->con);
	if(con->state==3)MRP_TryReconnect(con);	
	if(con->state==3)return(-1);

	MRPTrans_WriteUInt(con->sock, ref->pid);
	MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

	MRPTrans_WriteUInt(con->sock, MRP_Export(from));
	MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_GENERAL_BI);
	MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);

	MRPTrans_WriteOpcode(con->sock, MRPOP_NOTIFY);

	return(0);
}

int MRP_NotifyA(elem to, elem from)
{
	MRP_LongRef *ref;
	MRP_Connection *con;

	ref=TypeX_Data(to);
	con=TypeX_Data(ref->con);
	if(con->state==3)MRP_TryReconnect(con);	
	if(con->state==3)return(-1);

	MRPTrans_WriteUInt(con->sock, ref->pid);
	MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

	MRPTrans_WriteUInt(con->sock, MRP_Export(from));
	MRPTrans_WriteUInt(con->sock, MRPVAL_TYPE_GENERAL_BI);
	MRPTrans_WriteOpcode(con->sock, MRPOP_RREF);

	MRPTrans_WriteOpcode(con->sock, MRPOP_NOTIFYA);

	return(0);
}

int MRP_Delta(elem to, elem var, elem val)
{
	MRP_LongRef *ref;
	MRP_Connection *con;

	ref=TypeX_Data(to);
	con=TypeX_Data(ref->con);
	if(con->state==3)MRP_TryReconnect(con);	
	if(con->state==3)return(-1);

	MRP_AddDelta(con, to, var, val);

	return(0);
}

int MRP_SendRef(VADDR *addr, MRP_LongRef *ref, int d, elem from, elem msg)
{
	int i, c;
	MRP_Connection *con;
	elem t;

	con=MRP_FindCon(addr);
	if(!con)return(-1);

	mrp_ret_value[mrp_ret_pos]=MISC_UNDEFINED;
	mrp_ret_setter[mrp_ret_pos]=MISC_UNDEFINED;

	if(con->state==3)return(-1);

	if(CAR(msg)==SYM("::notify-stub"))
	{
//		kprint("notify stub ");
//		t=MMGC3_GetReference(ref);
//		MRP_Write(con, t);
//		TyFcn_DumpElem(t);

		MRPTrans_WriteUInt(con->sock, ref->pid);
		MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

//		kprint(" ");
		t=CADR(msg);
		MRP_Write(con, t);
//		TyFcn_DumpElem(t);
//		kprint("\n");

		MRPTrans_WriteOpcode(con->sock, MRPOP_NOTIFY);
		return(0);
	}
	if(CAR(msg)==SYM("::notify-active"))
	{
//		MRP_Write(con, MMGC3_GetReference(ref));
		MRPTrans_WriteUInt(con->sock, ref->pid);
		MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

		MRP_Write(con, CADR(msg));
		MRPTrans_WriteOpcode(con->sock, MRPOP_NOTIFYA);
		return(0);
	}
	if(CAR(msg)==SYM("::assign"))
	{
#if 0
		MRPTrans_WriteUInt(con->sock, 0);

		t=CONS(CADR(msg), CONS(CADDR(msg), MISC_EOL));
		t=CONS(t, MISC_EOL);
		MRP_Write(con, t);

		kprint("delta ");
		TyFcn_DumpElem(t);
		kprint("\n");

		MRP_Write(con, TypeX_GetReference(ref));
		MRP_Write(con, CADDR(msg));
		MRPTrans_WriteOpcode(con->sock, MRPOP_DELTA);
#endif
#if 0
		MRPTrans_WriteUInt(con->sock, ref->pid);
		MRPTrans_WriteOpcode(con->sock, MRPOP_YREF);

		MRP_Write(con, CADR(msg));
		MRP_Write(con, CADDR(msg));
		MRPTrans_WriteUInt(con->sock, 0);
		MRPTrans_WriteOpcode(con->sock, MRPOP_DELTA);
#endif
		MRP_AddDelta(con, TypeX_GetReference(ref),
			CADR(msg), CADDR(msg));
//		MRP_SendDeltas(con);

		return(0);
	}

	MRP_Write(con, msg);
	MRP_Write(con, from);

	MRPTrans_WriteSInt(con->sock, ref->pid);
	if((ref->type != MRPVAL_TYPE_CONTEXT) && (d!=1))
	{
//		sa_print("r-dispatch\n");
		c=mrp_continuation;
		MRP_Write(con, FIXNUM(mrp_continuation++));
		MRPTrans_WriteOpcode(con->sock, MRPOP_DISPATCH);

		while((!mrp_ret_pos || (mrp_ret_cont[mrp_ret_pos-1]!=c)) &&
			(con->state!=3))
		{
			MRP_Poll();
			kusleep(1000);
		}
		if(mrp_ret_pos)mrp_ret_pos--;
	}else
	{
		mrp_ret_value[mrp_ret_pos]=MISC_NULL;
		mrp_ret_setter[mrp_ret_pos]=MISC_NULL;

		c=mrp_continuation;
		MRP_Write(con, FIXNUM(0));
		MRPTrans_WriteOpcode(con->sock, MRPOP_DISPATCH);
	}

	return(0);
}

elem MRP_ApplyRef(elem obj, elem msg)
{
	MRP_LongRef *ref;
	VADDR *addr;
	elem t;
	MRP_Connection *con;

	ref=TypeX_Data(obj);
	con=TypeX_Data(ref->con);
	if(con->state==3)MRP_TryReconnect(con);

	addr=&con->addr;
	MRP_SendRef(addr, ref, 0, Interp_CurCtx(), msg);

	Interp_SetRax(Interp_CurCtx(), mrp_ret_setter[mrp_ret_pos]);
	t=mrp_ret_value[mrp_ret_pos];

	mrp_ret_value[mrp_ret_pos]=MISC_UNDEFINED;
	mrp_ret_setter[mrp_ret_pos]=MISC_UNDEFINED;

	return(t);
}

elem MRP_SwizinRef(elem obj)
{
	MRP_LongRef *ref;

	ref=TypeX_Data(obj);
	ref->con=MMGC3_SwizRefIn(ref->con);

	return(MISC_NULL);
}

elem MRP_SwizoutRef(elem obj)
{
	MRP_LongRef *ref;

	ref=TypeX_Data(obj);
	ref->con=MMGC3_SwizRefOut(ref->con);

	return(MISC_NULL);
}

elem MRP_MarkRef(elem obj)
{
	MRP_LongRef *ref;

	ref=TypeX_Data(obj);
//	kprint("mark ref %X, con %X\n", ref, ref->con);

	ref->con=MMGC3_TracePush(ref->con);

//	kprint("  ncon %X\n", ref->con);

	return(MISC_NULL);
}

elem MRP_ApplyRefFrom(elem obj, elem from, elem d, elem msg)
{
	MRP_LongRef *ref;
	VADDR *addr;
	elem t;
	MRP_Connection *con;

	ref=TypeX_Data(obj);
	con=TypeX_Data(ref->con);
	addr=&con->addr;
	MRP_SendRef(addr, ref, TOINT(d), from, msg);

	Interp_SetRax(Interp_CurCtx(), mrp_ret_setter);
	t=mrp_ret_value[mrp_ret_pos];

	mrp_ret_value[mrp_ret_pos]=MISC_UNDEFINED;
	mrp_ret_setter[mrp_ret_pos]=MISC_UNDEFINED;

	return(t);
}

int MRP_SendSymbol(MRP_Connection *con, int d, elem from, elem sym, elem msg)
{
	int i, c;

//	mrp_ret_value=MISC_UNDEFINED;
//	mrp_ret_setter=MISC_UNDEFINED;

	if(con->state==3)return(-1);

//	sa_print("apply addr\n");
//	TyFcn_DumpElem(sym);
//	sa_print(" from: ");
//	TyFcn_DumpElem(obj);
//	sa_print(" with: ");
//	TyFcn_DumpElem(msg);
//	sa_print("\n");

	mrp_ret_value[mrp_ret_pos]=MISC_UNDEFINED;
	mrp_ret_setter[mrp_ret_pos]=MISC_UNDEFINED;

	MRP_Write(con, CONS(sym, msg));
	MRP_Write(con, from);
	MRP_Write(con, MISC_NULL);

	if(d!=1)
	{
		c=mrp_continuation++;
		MRP_Write(con, FIXNUM(c));

		MRPTrans_WriteOpcode(con->sock, MRPOP_DISPATCH);

		i=Sys_TimeMS();
		while((!mrp_ret_pos || (mrp_ret_cont[mrp_ret_pos-1]!=c)) &&
			(con->state!=3))
		{
			MRP_Poll();
			kusleep(1000);

			if((Sys_TimeMS()-i)>5000)
			{
				kprint("MRP_SendSymbol: no return.\n");
				break;
			}
		}
		if(mrp_ret_pos)mrp_ret_pos--;
	}else
	{
		c=mrp_continuation;
		MRP_Write(con, FIXNUM(0));

		MRPTrans_WriteOpcode(con->sock, MRPOP_DISPATCH);

		mrp_ret_value[mrp_ret_pos]=MISC_NULL;
		mrp_ret_setter[mrp_ret_pos]=MISC_NULL;
	}

	return(0);
}

elem MRP_ApplyAddr(elem obj, elem rest)
{
	int i;
	VADDR *addr;
	MRP_Connection *con;
	elem sym, msg;

	sym=CAR(rest);
	msg=CDR(rest);

	addr=TypeX_Data(obj);
	if(!addr->ipv4.port)
		addr->ipv4.port=htons(8192);
	con=MRP_GetOrConnect(addr);

	if(!con)return(MISC_FALSE);

	MRP_SendSymbol(con, 0, Interp_CurCtx(), sym, msg);

	return(mrp_ret_value[mrp_ret_pos]);
}

elem MRP_ApplyAddrFrom(elem obj, elem from, elem d, elem rest)
{
	int i;
	VADDR *addr;
	MRP_Connection *con;
	elem sym, msg;

	sym=CAR(rest);
	msg=CDR(rest);

	addr=TypeX_Data(obj);
	if(!addr->ipv4.port)
		addr->ipv4.port=htons(8192);
	con=MRP_GetOrConnect(addr);

	if(!con)return(MISC_FALSE);

	MRP_SendSymbol(con, TOINT(d), from, sym, msg);

	return(mrp_ret_value[mrp_ret_pos]);
}

elem MRP_ApplyFrom(elem obj, elem from, elem rest)
{
	int i;
	VADDR *addr;
	MRP_Connection *con;
	elem sym, msg;
	elem t;


	if(TypeX_TypeP(obj, "addr"))
	{
		t=MRP_ApplyAddrFrom(obj, from, FIXNUM(0), rest);
	}else if(TypeX_TypeP(obj, "longref"))
	{
//		sa_print("MRP_ApplyFrom, send: ");
//		TyFcn_DumpElem(rest);
//		sa_print("\n");

		t=MRP_ApplyRefFrom(obj, from, FIXNUM(0), rest);
	}else
	{
		t=Interp_NewCtx();
		Interp_LetDynCtx(t, SYM("from"), from);
		t=Interp_ApplyCtx(t, obj, rest);
		return(t);
	}

	return(t);
}

elem MRP_ApplyFromU(elem obj, elem from, elem rest)
{
	int i;
	VADDR *addr;
	MRP_Connection *con;
	elem sym, msg;
	elem t;


	if(TypeX_TypeP(obj, "addr"))
	{
		t=MRP_ApplyAddrFrom(obj, from, FIXNUM(1), rest);
	}else if(TypeX_TypeP(obj, "longref"))
	{
//		sa_print("MRP_ApplyFrom, send: ");
//		TyFcn_DumpElem(rest);
//		sa_print("\n");

		t=MRP_ApplyRefFrom(obj, from, FIXNUM(1), rest);
	}else
	{
		t=TyFcn_CopyVector(Interp_ReplCtx());
		Interp_LetDynCtx(t, SYM("from"), from);
		Interp_ApplyCtxTh(t, obj, rest);
		return(t);
	}

	return(t);
}

elem MRP_ApplyU(elem obj, elem rest)
{
	return(MRP_ApplyFromU(obj, Interp_CurCtx(), rest));
}

elem MRP_ReqCopy(elem obj)
{
	MRP_LongRef *ref;
	VADDR *addr;
	elem t;
	int i;
	MRP_Connection *con;

	ref=TypeX_Data(obj);
	con=TypeX_Data(ref->con);
	addr=&con->addr;
	con=MRP_FindCon(addr);
	if(!con)return(-1);

	mrp_ret_value[mrp_ret_pos]=MISC_UNDEFINED;
	mrp_ret_setter[mrp_ret_pos]=MISC_UNDEFINED;

	if(con->state==3)return(-1);

	MRPTrans_WriteSInt(con->sock, ref->pid);
	MRP_Write(con, FIXNUM(mrp_continuation++));
	MRPTrans_WriteOpcode(con->sock, MRPOP_MIRROR);

	while(!mrp_ret_pos && (con->state!=3))
	{
		MRP_Poll();
		kusleep(1000);
	}

	t=mrp_ret_value[--mrp_ret_pos];

//	mrp_ret_value=MISC_UNDEFINED;
//	mrp_ret_setter=MISC_UNDEFINED;

	return(t);
}

elem MRP_DispatchSymbol(elem sym, elem from, elem msg)
{
	elem cur, t;

//	sa_print("dispatch symbol ");
//	TyFcn_DumpElem(sym);
//	sa_print(" from: ");
//	TyFcn_DumpElem(from);
//	sa_print(" with: ");
//	TyFcn_DumpElem(msg);
//	sa_print("\n");

	cur=mrp_handlers;
	while(ELEM_CONSP(cur))
	{
		if(CAAR(cur)==sym)
		{
			if(ELEM_CONTEXTP(CADR(CAR(cur))))
			{
				Interp_SendThreadFrom(CADR(CAR(cur)),
					from, msg);
				t=MISC_NULL;
			}else
			{
//				t=TyFcn_CopyVector(Interp_ReplCtx());
				t=Interp_NewCtx();
				Interp_LetDynCtx(t, SYM("from"), from);
				t=Interp_ApplyCtx(t,
					CADR(CAR(cur)), msg);
			}
			return(t);
		}
		cur=CDR(cur);
	}
	return(MISC_FALSE);
}

elem MRP_AddHandler(elem sym, elem func)
{
	mrp_handlers=CONS(CONS(sym, CONS(func, MISC_EOL)), mrp_handlers);
	return(MISC_NULL);
}

elem MRP_List2Addr(elem def)
{
	elem tmp;
	VADDR *addr;
	unsigned long l;

	tmp=TyFcn_TypeX(SYM("addr"), sizeof(VADDR), NULL);
	addr=TypeX_Data(tmp);

	if(CAR(def)==SYM("ipv4udp"))
	{
		addr->proto=PROTO_IPV4UDP;
		l=ELEM_TOFIXNUM(CAR(CADR(def)))<<24;
		l+=ELEM_TOFIXNUM(CADR(CADR(def)))<<16;
		l+=ELEM_TOFIXNUM(CADDR(CADR(def)))<<8;
		l+=ELEM_TOFIXNUM(CADDDR(CADR(def)));
		addr->ipv4.addr=htonl(l);
		addr->ipv4.port=htons(ELEM_TOFIXNUM(CADDR(def)));
	}
	if(CAR(def)==SYM("ipv4tcp"))
	{
		addr->proto=PROTO_IPV4TCP;
		l=ELEM_TOFIXNUM(CAR(CADR(def)))<<24;
		l+=ELEM_TOFIXNUM(CADR(CADR(def)))<<16;
		l+=ELEM_TOFIXNUM(CADDR(CADR(def)))<<8;
		l+=ELEM_TOFIXNUM(CADDDR(CADR(def)));
		addr->ipv4.addr=htonl(l);
		addr->ipv4.port=htons(ELEM_TOFIXNUM(CADDR(def)));
	}

//	MRP_GetOrConnect(addr); //force open, test

	return(tmp);
}

elem MRP_Addr2List(elem obj)
{
	VADDR *addr;
	int addrc;
	elem t;

	addr=TypeX_Data(obj);

	switch(addr->proto)
	{
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		addrc=ntohl(addr->ipv4.addr);
		t=CONS(FIXNUM(addrc&0xff), MISC_EOL);
		t=CONS(FIXNUM((addrc>>8)&0xff), t);
		t=CONS(FIXNUM((addrc>>16)&0xff), t);
		t=CONS(FIXNUM((addrc>>24)&0xff), t);

		t=CONS(SYM("ipv4tcp"), CONS(t,
			CONS(FIXNUM(ntohs(addr->ipv4.port)), MISC_EOL)));
		break;
	default:
		break;
	}
}

elem MRP_FindHost(elem name)
{
	elem tmp;
	VADDR *addr, *naddr;
	unsigned long l;

	naddr=NET_LookupHost(ELEM_TOSTRING(name));

	if(!naddr)return(MISC_NULL);

//	if(!naddr->ipv4.port)
//		naddr->ipv4.port=htons(8192);

	tmp=TyFcn_TypeX(SYM("addr"), sizeof(VADDR), NULL);
	addr=TypeX_Data(tmp);
	memcpy(addr, naddr, sizeof(VADDR));
	kfree(naddr);

//	MRP_GetOrConnect(addr); //force open, test

	return(tmp);
}

elem MRP_SwizinCon(elem obj)
{
	MRP_Connection *con;

	con=TypeX_Data(obj);
	con->state=3;

	con->stack_elem=VECTOR_NEW(4095);
//	con->stack_elem=MMGC3_SwizRefIn(con->stack_elem);
	con->stack=TyFcn_VectorBody(con->stack_elem);
	con->stackpos=0;
	con->mark=0;

	con->buffer=NULL;
	con->bufend=NULL;

	con->sock=NULL;

	return(MISC_NULL);
}

elem MRP_SwizoutCon(elem obj)
{
	MRP_Connection *con;

	con=TypeX_Data(obj);
//	con->stack_elem=MMGC3_SwizRefOut(con->stack_elem);

	return(MISC_NULL);
}

elem MRP_MarkCon(elem obj)
{
	MRP_Connection *con;

	con=TypeX_Data(obj);
	con->stack_elem=MMGC3_TracePush(con->stack_elem);
	con->stack=TyFcn_VectorBody(con->stack_elem);

	con->deltas=MMGC3_TracePush(con->deltas);

	return(MISC_NULL);
}

int MRP_HandleRestore()
{
	elem cur;

	if(mrp_guid_elem==MISC_NULL)
	{
		mrp_guid_elem=TyFcn_TypeX(SYM("guid"), 16, NULL);
		mrp_guid=TypeX_Data(mrp_guid_elem);

		NET_CreateGuid(mrp_guid);
		kprint("MRP NEW GUID: %s\n", NET_Guid2String(mrp_guid));
	}else
	{
		mrp_guid=TypeX_Data(mrp_guid_elem);
		kprint("MRP OLD GUID: %s\n", NET_Guid2String(mrp_guid));
	}
//	if(mrp_convec==MISC_NULL)mrp_convec=VECTOR_NEW(MRP_MAXCONS);
//	if(mrp_stacks==MISC_NULL)mrp_stacks=VECTOR_NEW(MRP_MAXCONS);

	cur=mrp_con_lst;
	while(cur!=MISC_EOL)
	{
//		MRP_TryReconnect(TypeX_Data(CAR(cur)));
		cur=CDR(cur);
	}
}

int MRP_Init()
{
	typexinfo *txi;
	int i;

//	NET_InitLow();
	UDPBUF_Init();

	mrp_port=8192;
	mrp_sock=NULL;
	while(mrp_port>(8192-256))
	{
		mrp_sock=TCP_OpenListen(mrp_port);
		if(mrp_sock)break;
		mrp_port--;
	}
	if(mrp_sock)
	{
		kprint("MRP: port opened %d\n", mrp_port);
	}else
	{
		kprint("MRP: fail open host port\n");
	}
	mrp_sock_udp=UDPBUF_OpenListen(mrp_port);

	mrp_scion_lst=MISC_EOL;
	mrp_guid_elem=MISC_NULL;
//	mrp_convec=MISC_NULL;
//	mrp_stacks=MISC_NULL;
	mrp_handlers=MISC_EOL;
	mrp_con_lst=MISC_EOL;

	mrp_objstack=MISC_EOL;

	MMGC3_AddNamedRoot(&mrp_guid_elem, "mrp-guid");
	MMGC3_AddNamedRoot(&mrp_scion_lst, "mrp-scions");
//	MMGC3_AddNamedRoot(&mrp_convec, "mrp-con-vec");
	MMGC3_AddNamedRoot(&mrp_con_lst, "mrp-con-lst");

//	MMGC3_AddNamedRoot(&mrp_stacks, "mrp-stacks");
	MMGC3_AddNamedRoot(&mrp_handlers, "mrp-handlers");

	MMGC3_AddRoot(&mrp_objstack);

	mrp_ret_pos=0;

	for(i=0; i<4; i++)
	{
		MMGC3_AddRoot(&mrp_ret_setter[i]);
		MMGC3_AddRoot(&mrp_ret_value[i]);
	}

//	mrp_guid_elem=TyFcn_TypeX(SYM("guid"), 16, NULL);
//	mrp_guid=TypeX_Data(mrp_guid_elem);

//	NET_CreateGuid(mrp_guid);
//	kprint("MRP GUID: %s\n", NET_Guid2String(mrp_guid));

	txi=TypeX_GetInfo("longref");
	txi->apply=&MRP_ApplyRef;
	txi->swizin=&MRP_SwizinRef;
	txi->swizout=&MRP_SwizoutRef;
	txi->mark=&MRP_MarkRef;

	txi=TypeX_GetInfo("addr");
//	kprint("txi %X\n", txi);
	txi->apply=&MRP_ApplyAddr;

	txi=TypeX_GetInfo("mrp-connection");
	txi->apply=&MRP_ApplyAddr;
	txi->swizin=&MRP_SwizinCon;
	txi->swizout=&MRP_SwizoutCon;
	txi->mark=&MRP_MarkCon;

	Interp_DefinePrimative("add-net-handler", &MRP_AddHandler, 2);
	Interp_DefinePrimative("list->addr",	&MRP_List2Addr, 1);
	Interp_DefinePrimative("addr->list",	&MRP_Addr2List, 1);
	Interp_DefinePrimative("find-host",	&MRP_FindHost, 1);

	Interp_DefinePrimative("send-u",	&MRP_ApplyU, 2);
	Interp_DefinePrimative("send-from",	&MRP_ApplyFrom, 3);
	Interp_DefinePrimative("send-from-u",	&MRP_ApplyFromU, 3);

	Interp_DefinePrimative("req-copy",	&MRP_ReqCopy, 1);

	Interp_DefinePrimative("->",	&MRP_ApplyU, -2);
	Interp_DefinePrimative("<*>",	&MRP_ApplyFrom, -3);
	Interp_DefinePrimative("*>",	&MRP_ApplyFromU, -3);

	return(0);
}
