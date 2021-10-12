#include <scmcc.h>
#include <interpctx.h>

elem opcodes_n, opcodes_d;
extern elem form_return, form_apply, form_halt;
//extern elem toplevel_n, toplevel_d, topvar_n, topvar_d;

InterpCtx *interp_context; //used to pass context to called functions
extern elem interp_cur_ctx;

elem HpiInterp_Fold(elem rp, elem args);

int interp_totalusloop;

elem HpiOp_Apply(InterpCtx *ctx)
{
	elem t, ep_n, ep_d;
	int x;

	static elem sym_self=MISC_NULL;
	if(sym_self==MISC_NULL)sym_self=SYM("self");

	ctx->rax=MISC_NULL;

	if(ELEM_FUNCTIONP(ctx->ax))
	{
		interp_context=ctx;
		interp_cur_ctx=ELEM_FROMOBJECT(ctx);

		x=ctx->rp;
		ctx->ip=form_return;

		ctx->ax=TyMisc_EvalSpecial(ctx->ax, ctx->rp);
//		TyFcn_UnList(x);
		return(MISC_NULL);
	}else if(ELEM_CLOSUREP(ctx->ax))
	{
		ctx->ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));

		t=CAR(ctx->ep_n);
//		if(TyFcn_ListGetEnd(t)!=MISC_EOL)
//			ctx->rp=HpiInterp_Fold(ctx->rp, t);

		ctx->ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(ctx->rp, ctx->ep_d);

		ctx->ip=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(2));

		ctx->sep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(3));
		ctx->sep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(4));

		ctx->rp=MISC_EOL;

//		TyFcn_DumpElem(ctx->ep_n);
//		sa_print("\n");
//		TyFcn_DumpElem(ctx->ep_d);
//		sa_print("\n");

		return(MISC_NULL);
	}else if(ELEM_ENVOBJP(ctx->ax))
	{
#if 0
		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		t=Namespace2_Lookup(ep_n, ep_d, SYM("access"));
		ctx->ax=t;

		ctx->dyn_n=CONS(SYM("self"), ctx->dyn_n);
		ctx->dyn_d=CONS(t, ctx->dyn_d);

		ctx->ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));

		t=CAR(ctx->ep_n);
//		if(TyFcn_ListGetEnd(t)!=MISC_EOL)
//			ctx->rp=HpiInterp_Fold(ctx->rp, t);

		ctx->ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(ctx->rp, ctx->ep_d);

		ctx->ip=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(2));

		ctx->rp=MISC_EOL;

//		TyFcn_DumpElem(ctx->ep_n);
//		sa_print("\n");
//		TyFcn_DumpElem(ctx->ep_d);
//		sa_print("\n");
#endif
		ctx->dyn_n=CONS(sym_self, ctx->dyn_n);
		ctx->dyn_d=CONS(ctx->ax, ctx->dyn_d);

		ctx->ip=MISC_EOL;

		TyObj_Dispatch(ctx);

		return(MISC_NULL);
	}else if(ELEM_ENVP(ctx->ax))
	{
		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));

		if(CDR(ctx->rp)==MISC_EOL)
		{
//			t=Namespace2_Lookup(ep_n, ep_d, CAR(ctx->rp));
//			ctx->ax=t;

			t=Namespace2_Trace(ep_n, ep_d, MISC_EOL, CAR(ctx->rp));
			ctx->ax=Namespace2_RetrieveTrace(ep_n, ep_d, t);
			ctx->rax=Namespace2_LocativeTrace(ep_n, ep_d, t);
		}else
		{
			t=ctx->ax;
			ctx->ax=Namespace2_Assign(ep_n, ep_d, CAR(ctx->rp), CADR(ctx->rp));
			if(ctx->ax==MISC_UNDEFINED)
			{
				ep_n=CONS(CONS(CAR(ctx->rp), CAR(ep_n)), CDR(ep_n));
				ep_d=CONS(CONS(CADR(ctx->rp), CAR(ep_d)), CDR(ep_d));
				TyFcn_VectorSet(t, ELEM_FROMFIXNUM(0), ep_n);
				TyFcn_VectorSet(t, ELEM_FROMFIXNUM(1), ep_d);
			}
		}
//		ctx->ax=t;

		ctx->ip=form_return;

		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_CONTEXTP(ctx->ax))
	{
		Interp_SendThread(ctx->ax, ctx->rp);
		ctx->ax=MISC_NULL;
		ctx->ip=form_return;
		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_VECTORP(ctx->ax)) /* placed after other "vector" types... */
	{
//		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
//		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		if(ctx->rp==MISC_EOL)
		{
			sa_error("apply with vector, no args...\n");
			ctx->ax=MISC_UNDEFINED;
			ctx->ip=form_return;
			ctx->rp=MISC_EOL;
			return(MISC_UNDEFINED);
		}
		if(CDR(ctx->rp)==MISC_EOL)
		{
			t=TyFcn_VectorRef(ctx->ax, CAR(ctx->rp));
			ctx->rax=TyFcn_VectorRefM(ctx->ax, CAR(ctx->rp));
			ctx->ax=t;
		}else ctx->ax=TyFcn_VectorSet(ctx->ax, CAR(ctx->rp), CADR(ctx->rp));

//		ctx->ax=t;
		ctx->ip=form_return;
		ctx->rp=MISC_EOL;
		return(MISC_NULL);
	}else
	{
		sa_error("apply with invalid object: '");
		TyFcn_DumpElem(ctx->ax);
		sa_print("'\n");

		ctx->ax=MISC_UNDEFINED;
		ctx->ip=form_return;

		abort();

		return(MISC_UNDEFINED);
	}
	return(MISC_NULL);
}

elem HpiOp_Argument(InterpCtx *ctx)
{
	ctx->rp=CONS(ctx->ax, ctx->rp);
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Assign(InterpCtx *ctx)
{
	elem pos, t;
	pos=CAR(CDR(CAR(ctx->ip)));
	if(ELEM_SYMBOLP(pos))
	{
		t=Namespace2_Assign(ctx->dyn_n, ctx->dyn_d, pos, ctx->ax);
		if(t==MISC_UNDEFINED)
		{
			sa_error("Assign: unbound var '%s'\n", ELEM_TOSYMBOL(pos));
			ctx->ip=CDR(ctx->ip);
			return(MISC_UNDEFINED);
		}
	}else if(ELEM_CONSP(pos))
	{
		Namespace2_AssignTrace(ctx->ep_n, ctx->ep_d, pos, ctx->ax);
	}
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Bind(InterpCtx *ctx)
{
	elem t;
	t=CAR(CDR(CAR(ctx->ip)));
//	ctx->ep_n=CONS(t, ctx->ep_n);
//	ctx->ep_d=CONS(ctx->ax, ctx->ep_d);
//	TyFcn_SetCar(ctx->ep_n, CONS(t, CAR(ctx->ep_n)));
//	TyFcn_SetCar(ctx->ep_d, CONS(ctx->ax, CAR(ctx->ep_d)));

	ctx->ep_n=CONS(CONS(t,			CAR(ctx->ep_n)), CDR(ctx->ep_n));
	ctx->ep_d=CONS(CONS(ctx->ax,	CAR(ctx->ep_d)), CDR(ctx->ep_d));

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_BindArgs(InterpCtx *ctx)
{
	elem t;
	t=CAR(CDR(CAR(ctx->ip)));
	ctx->ep_n=CONS(t, ctx->ep_n);
	ctx->ep_d=CONS(ctx->rp, ctx->ep_d);
	ctx->rp=MISC_EOL;
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_BindVar(InterpCtx *ctx)
{
	elem t;
	t=CAR(CDR(CAR(ctx->ip)));
	ctx->dyn_n=CONS(CONS(t,			CAR(ctx->dyn_n)), CDR(ctx->dyn_n));
	ctx->dyn_d=CONS(CONS(ctx->ax,	CAR(ctx->dyn_d)), CDR(ctx->dyn_d));

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_BindArgsVar(InterpCtx *ctx)
{
	elem t;
	t=CAR(CDR(CAR(ctx->ip)));
	ctx->dyn_n=CONS(t, ctx->dyn_n);
	ctx->dyn_d=CONS(ctx->rp, ctx->dyn_d);
	ctx->rp=MISC_EOL;
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Block(InterpCtx *ctx)
{
	ctx->vax=SYM("block");
	ctx->ip=CDR(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_Close(InterpCtx *ctx)
{
	elem t, x;

	x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(6), ELEM_FROMFIXNUM(VECTOR_CLOSURE));
//	x=TyFcn_NewVector(ELEM_FROMFIXNUM(3));

	t=CADR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), CONS(t, ctx->ep_n));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ctx->ep_d);

	t=CADDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(3), ctx->sep_n);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(4), ctx->sep_d);

	t=CADDDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(5), t);

//	OBJECT_HEAD(x)=(OBJECT_HEAD(x)&(~255))+OBJECT_CLOSURE;
	ctx->ax=x;

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Constant(InterpCtx *ctx)
{
	ctx->ax=CAR(CDR(CAR(ctx->ip)));
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Conti(InterpCtx *ctx)
{
	elem t, x, tmp;

	tmp=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_CLOSURE));

	t=CONS(SYM("nuate"), CONS(ctx->sp, MISC_EOL));
	x=CONS(t, MISC_EOL);
	t=CONS(SYM("refer"), CONS(CONS(ELEM_FROMFIXNUM(0), CONS(ELEM_FROMFIXNUM(0), MISC_EOL)), MISC_EOL));
	x=CONS(t, x);

	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(0), CONS(t, ctx->ep_n));
	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(1), ctx->ep_d);
	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(2), x);

//	OBJECT_HEAD(tmp)=(OBJECT_HEAD(tmp)&(~255))+OBJECT_CLOSURE;
	ctx->ax=tmp;

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_CurrentEnv(InterpCtx *ctx)
{
	ctx->ax=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(4), ELEM_FROMFIXNUM(VECTOR_ENV));

	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(0), ctx->ep_n);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(1), ctx->ep_d);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(2), ctx->sep_n);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(3), ctx->sep_d);

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

#if 0
elem HpiOp_CurrentEnvObj(InterpCtx *ctx)
{
	ctx->ax=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(2), ELEM_FROMFIXNUM(VECTOR_ENVOBJ));

	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(0), ctx->ep_n);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(1), ctx->ep_d);

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}
#endif

elem HpiOp_Frame(InterpCtx *ctx)
{
	elem x;

	x=ctx->sp;
	x=CONS(ctx->ep_n, x);
	x=CONS(ctx->ep_d, x);
	x=CONS(ctx->dyn_n, x);
	x=CONS(ctx->dyn_d, x);
	x=CONS(ctx->sep_n, x);
	x=CONS(ctx->sep_d, x);
	x=CONS(ctx->rp, x);
	x=CONS(CDR(ctx->ip), x);
	ctx->sp=x;

	ctx->ip=CAR(CDR(CAR(ctx->ip)));
	ctx->rp=MISC_EOL;

	return(MISC_NULL);
}

elem HpiOp_Halt(InterpCtx *ctx)
{
	ctx->ip=MISC_TRUE;
	ctx->vax=SYM("halt");

//	toplevel_n=ctx->ep_n;
//	toplevel_d=ctx->ep_d;
//	topvar_n=ctx->dyn_n;
//	topvar_d=ctx->dyn_d;

	return(MISC_NULL);
}

elem HpiOp_IntsOff(InterpCtx *ctx)
{
	ctx->vax=SYM("no-ints");
	ctx->ip=CDR(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_IntsOn(InterpCtx *ctx)
{
	if(ctx->vax==SYM("no-ints"))ctx->vax=MISC_NULL;
	ctx->ip=CDR(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_Nuate(InterpCtx *ctx)
{
	ctx->sp=CAR(CDR(CAR(ctx->ip)));
	ctx->ip=form_return;
	return(MISC_NULL);
}

elem HpiOp_Refer(InterpCtx *ctx)
{
	elem pos;
	pos=CAR(CDR(CAR(ctx->ip)));
	if(ELEM_SYMBOLP(pos))
	{
		ctx->ax=Namespace2_Lookup(ctx->dyn_n, ctx->dyn_d, pos);
		if(ctx->ax==MISC_UNDEFINED)
		{
			sa_error("Refer: unbound var '%s'\n", ELEM_TOSTRING(pos));
			ctx->ip=CDR(ctx->ip);
			return(MISC_UNDEFINED);
		}
	}else if(ELEM_CONSP(pos))
	{
		ctx->ax=Namespace2_RetrieveTrace(ctx->ep_n, ctx->ep_d, pos);
		ctx->rax=Namespace2_LocativeTrace(ctx->ep_n, ctx->ep_d, pos);
	}else sa_print("refer: bad trace\n");

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_ReferSyntax(InterpCtx *ctx)
{
	elem pos;
	pos=CAR(CDR(CAR(ctx->ip)));

	ctx->ax=Namespace2_Lookup(ctx->sep_n, ctx->sep_d, pos);
	if(ctx->ax==MISC_UNDEFINED)
	{
		sa_error("Refer-Syntax: unbound syntax '%s'\n", ELEM_TOSTRING(pos));
		ctx->ip=CDR(ctx->ip);
		return(MISC_UNDEFINED);
	}

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Return(InterpCtx *ctx)
{
	elem x;

	x=ctx->sp;

	ctx->ip=CAR(x);
	x=CDR(x);
	ctx->rp=CAR(x);
	x=CDR(x);
	ctx->sep_d=CAR(x);
	x=CDR(x);
	ctx->sep_n=CAR(x);
	x=CDR(x);
	ctx->dyn_d=CAR(x);
	x=CDR(x);
	ctx->dyn_n=CAR(x);
	x=CDR(x);
	ctx->ep_d=CAR(x);
	x=CDR(x);
	ctx->ep_n=CAR(x);
	x=CDR(x);

	ctx->sp=x;

	return(MISC_NULL);
}

elem HpiOp_SetRax(InterpCtx *ctx)
{
	elem t;

	if(!ELEM_LOCATIVEP(ctx->rax))
	{
		sa_error("set-rax: invalid value in rax.\n");
		ctx->ip=CDR(ctx->ip);
		return(MISC_UNDEFINED);
	}

	ELEM_SETLOCATIVE(ctx->rax, CAR(ctx->rp));

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Splice(InterpCtx *ctx)
{
	elem t;

	t=TyFcn_ListCopy(ctx->ax);
	ctx->rp=TyFcn_NAppend(t, ctx->rp);

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Test(InterpCtx *ctx)
{
	elem tc, fc;
	tc=CADR(CAR(ctx->ip));
	fc=CADDR(CAR(ctx->ip));

	if(ctx->ax==MISC_TRUE)ctx->ip=tc;
		else ctx->ip=fc;
	return(MISC_NULL);
}

elem HpiOp_Trampoline(InterpCtx *ctx)
{
	ctx->rp=CONS(ELEM_FROMLOCATIVE(ctx), CAR(ctx->ep_d));
	ctx->ax=CADR(CAR(ctx->ip));

	return(HpiOp_Apply(ctx));
}

elem HpiOp_XchgRPAX(InterpCtx *ctx)
{
	elem t;

	t=ctx->ax;
	ctx->ax=ctx->rp;
	ctx->rp=t;

	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}


int hpimisc_dumpops;

elem HpiMisc_DumpOps(InterpCtx *ctx)
{
	hpimisc_dumpops^=1;
	ctx->ip=CDR(ctx->ip);
	return(MISC_NULL);
}

elem HpiInterp_Fold(elem rp, elem args)
{
	elem cur1, cur2;
	int i;

	if(!ELEM_CONSP(args))return(CONS(rp, MISC_EOL));

	if(TyFcn_ListLength(rp)<TyFcn_ListLength(args))
	{
		sa_error("too few arguments.\n");
		return(MISC_NULL);
	}

	cur1=rp;
	cur2=args;
	while(ELEM_CONSP(cur2))
	{
		cur1=CDR(cur1);
		cur2=CDR(cur2);
	}

	TyFcn_SetCdr(cur1, CONS(CDR(cur1), MISC_EOL));
	return(rp);
}

elem HpiInterp_DefineSpecial(char *name, elem (*func)(), int pc)
{
	opcodes_n=CONS(TyFcn_Symbol(name), opcodes_n);
	opcodes_d=CONS(TyFcn_Function(func, pc), opcodes_d);

	return(MISC_NULL);
}

elem HpiInterp_RunStep(InterpCtx *ctx)
{
	elem op;

	if(hpimisc_dumpops)
	{
		TyFcn_DumpElem(CAR(ctx->ip));
		sa_print("\n");
	}
	op=Namespace2_Lookup(opcodes_n, opcodes_d, CAR(CAR(ctx->ip)));
	if(op==MISC_UNDEFINED)
	{
		sa_print("unknown opcode \"%s\"\n", ELEM_TOSYMBOL(CAR(CAR(ctx->ip))));
		return(MISC_UNDEFINED);
	}
	TyMisc_EvalSpecial(op, CONS((elem)ctx, MISC_EOL));

	if(ctx->ip==MISC_TRUE)return(ctx->ax);
	return(MISC_UNDEFINED);
}

elem HpiInterp_RunLoop(InterpCtx *ctx)
{
	elem op;

	Sys_TimeDUS();

	while(ELEM_CONSP(ctx->ip))
	{
		if(hpimisc_dumpops)
		{
			TyFcn_DumpElem(CAR(ctx->ip));
			sa_print("\n");
		}

		op=Namespace2_Lookup(opcodes_n, opcodes_d, CAR(CAR(ctx->ip)));
		if(op==MISC_UNDEFINED)
		{
			sa_print("unknown opcode \"%s\"\n", ELEM_TOSYMBOL(CAR(CAR(ctx->ip))));
			return(MISC_UNDEFINED);
		}
		TyMisc_EvalSpecial(op, CONS((elem)ctx, MISC_EOL));
	}

	interp_totalusloop+=Sys_TimeDUS();

	if(ctx->ip==MISC_TRUE)return(ctx->ax);
	sa_print("hit end of op stream\n");
	return(MISC_UNDEFINED);
}

int HpiInterp_RunLoopQuantum(elem ectx, int ms)
{
	elem op, noints;
	int t, end;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);

	t=Sys_TimeMS();
	end=t+ms;

	ctx->vax=MISC_NULL;

	noints=SYM("no-ints");

	while(ELEM_CONSP(ctx->ip))
	{
		t=Sys_TimeMS();
		if(t>=end && !(ctx->vax==noints))break;

		if(ctx->vax!=MISC_NULL)
		{
			if(ctx->vax==SYM("halt"))break;
				else if(ctx->vax==SYM("block"))break;
				else ctx->vax=MISC_NULL;
		}

		if(hpimisc_dumpops)
		{
			TyFcn_DumpElem(CAR(ctx->ip));
			sa_print("\n");
		}

		op=Namespace2_Lookup(opcodes_n, opcodes_d, CAR(CAR(ctx->ip)));
		if(op==MISC_UNDEFINED)
		{
			sa_print("unknown opcode \"%s\"\n", ELEM_TOSYMBOL(CAR(CAR(ctx->ip))));
			return(MISC_UNDEFINED);
		}
		TyMisc_EvalSpecial(op, CONS((elem)ctx, MISC_EOL));
	}

	return(end-t);
}

elem HpiInterp_Run(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d)
{
	InterpCtx *tmp;
	elem t;

	tmp=sa_malloc(sizeof(InterpCtx));
	tmp->ip=form;
	tmp->ax=MISC_NULL;
	tmp->sp=MISC_EOL;
	tmp->rp=MISC_EOL;

	tmp->ep_n=env_n;
	tmp->ep_d=env_d;
	tmp->dyn_n=dyn_n;
	tmp->dyn_d=dyn_d;

	t=HpiInterp_RunLoop(tmp);

	sa_free(tmp);

	return(t);
}

elem HpiInterp_RunCtx(elem form, InterpCtx *ctx)
{
	elem t;

	ctx->ip=form;
	ctx->ax=MISC_NULL;
	ctx->rp=MISC_EOL;

	t=HpiInterp_RunLoop(ctx);

	return(t);
}

InterpCtx *HpiInterp_RunCtxSafe(elem form, InterpCtx *ctx)
{
	InterpCtx *newctx;
	elem x, t;

	t=TyFcn_CopyVector(ELEM_FROMOBJECT(ctx));
	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=form;
	newctx->ax=MISC_NULL;
	newctx->rp=MISC_EOL;

	t=HpiInterp_RunLoop(newctx);

	return(newctx);
}

int HpiInterp_Init()
{
	MMGC_AddRoot(&opcodes_n);
	MMGC_AddRoot(&opcodes_d);

	opcodes_n=MISC_EOL;
	opcodes_d=MISC_EOL;

	hpimisc_dumpops=0;

	HpiInterp_DefineSpecial("apply",			&HpiOp_Apply, 1);
	HpiInterp_DefineSpecial("argument",			&HpiOp_Argument, 1);
	HpiInterp_DefineSpecial("assign",			&HpiOp_Assign, 1);
	HpiInterp_DefineSpecial("bind",				&HpiOp_Bind, 1);
	HpiInterp_DefineSpecial("bind-args",		&HpiOp_BindArgs, 1);
	HpiInterp_DefineSpecial("bind-var",			&HpiOp_BindVar, 1);
	HpiInterp_DefineSpecial("bind-args-var",	&HpiOp_BindArgsVar, 1);
	HpiInterp_DefineSpecial("block",			&HpiOp_Block, 1);
	HpiInterp_DefineSpecial("close",			&HpiOp_Close, 1);
	HpiInterp_DefineSpecial("constant",			&HpiOp_Constant, 1);
	HpiInterp_DefineSpecial("conti",			&HpiOp_Conti, 1);
	HpiInterp_DefineSpecial("current-env",		&HpiOp_CurrentEnv, 1);
//	HpiInterp_DefineSpecial("current-envobj",	&HpiOp_CurrentEnvObj, 1);
	HpiInterp_DefineSpecial("frame",			&HpiOp_Frame, 1);
	HpiInterp_DefineSpecial("halt",				&HpiOp_Halt, 1);
	HpiInterp_DefineSpecial("ints-off",			&HpiOp_IntsOff, 1);
	HpiInterp_DefineSpecial("ints-on",			&HpiOp_IntsOn, 1);
	HpiInterp_DefineSpecial("nuate",			&HpiOp_Nuate, 1);
	HpiInterp_DefineSpecial("refer",			&HpiOp_Refer, 1);
	HpiInterp_DefineSpecial("refer-syntax",		&HpiOp_ReferSyntax, 1);
	HpiInterp_DefineSpecial("return",			&HpiOp_Return, 1);
	HpiInterp_DefineSpecial("set-rax",			&HpiOp_SetRax, 1);
	HpiInterp_DefineSpecial("splice",			&HpiOp_Splice, 1);
	HpiInterp_DefineSpecial("test",				&HpiOp_Test, 1);
	HpiInterp_DefineSpecial("trampoline",		&HpiOp_Trampoline, 1);
	HpiInterp_DefineSpecial("xchg-rp-ax",		&HpiOp_XchgRPAX, 1);

	HpiInterp_DefineSpecial("dump-ops",			&HpiMisc_DumpOps, 1);
}
