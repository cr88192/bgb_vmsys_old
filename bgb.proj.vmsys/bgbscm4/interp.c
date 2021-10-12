/* this is a general wrapper for the interpretation/compilation process */
#include <scmcc.h>
#include <interpctx.h>

//elem toplevel_n, toplevel_d, topvar_n, topvar_d;
extern elem form_return, form_apply, form_halt;
InterpCtx *repl_ctx;

elem interp_repl_ctx, interp_cur_ctx;
elem interp_ctx_list;
elem interp_apply_rax;

elem interp_running_list, interp_blocked_list, interp_running_cur;

elem interp_delay_list, interp_delay_times;

elem interp_sysroot;

static elem sym_pidmsgqueue=MISC_NULL;
static elem sym_block=MISC_NULL;
static elem sym_halt=MISC_NULL;

int Interp_Init()
{
	elem t;
//	toplevel_n=CONS(MISC_EOL, MISC_EOL);
//	toplevel_d=CONS(MISC_EOL, MISC_EOL);
//	topvar_n=CONS(MISC_EOL, MISC_EOL);
//	topvar_d=CONS(MISC_EOL, MISC_EOL);

	SAGC_AddRoot(&repl_ctx);
	SAGC_AddRoot(&interp_repl_ctx);
	SAGC_AddRoot(&interp_cur_ctx);

	SAGC_AddRoot(&interp_ctx_list);

	SAGC_AddRoot(&interp_running_list);
	SAGC_AddRoot(&interp_blocked_list);
	SAGC_AddRoot(&interp_running_cur);

	interp_running_list=MISC_EOL;
	interp_blocked_list=MISC_EOL;
	interp_running_cur=MISC_EOL;

	SAGC_AddRoot(&interp_delay_list);
	SAGC_AddRoot(&interp_delay_times);

	interp_delay_list=MISC_EOL;
	interp_delay_times=MISC_EOL;

	interp_sysroot=MISC_NULL;
	SAGC_AddNamedRoot(&interp_sysroot, "sys-root");
	SAGC_AddNamedRoot(&interp_running_list, "sys-threads");

	interp_cur_ctx=MISC_NULL;
	interp_ctx_list=MISC_EOL;

	t=VECTOR_NEWT(sizeof(InterpCtx)/sizeof(elem), VECTOR_CONTEXT);
	interp_repl_ctx=t;

	repl_ctx=(InterpCtx *)ELEM_TOOBJECT(t);
//	repl_ctx=sa_malloc(sizeof(InterpCtx));
	repl_ctx->ip=MISC_EOL;
	repl_ctx->ax=MISC_NULL;
	repl_ctx->sp=MISC_EOL;
	repl_ctx->rp=MISC_EOL;
	repl_ctx->lrp=MISC_EOL;

	repl_ctx->ep_n=CONS(MISC_EOL, MISC_EOL);
	repl_ctx->ep_d=CONS(MISC_EOL, MISC_EOL);
	repl_ctx->dyn_n=CONS(MISC_EOL, MISC_EOL);
	repl_ctx->dyn_d=CONS(MISC_EOL, MISC_EOL);
	repl_ctx->sep_n=CONS(MISC_EOL, MISC_EOL);
	repl_ctx->sep_d=CONS(MISC_EOL, MISC_EOL);
}

int Interp_HandleRestore()
{
	if(interp_sysroot==MISC_NULL || interp_sysroot==MISC_UNDEFINED)
//	if(1)
	{
		sa_print("spawn sys-root.\n");
		interp_sysroot=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(4), ELEM_FROMFIXNUM(VECTOR_ENV));

		TyFcn_VectorSet(interp_sysroot, ELEM_FROMFIXNUM(0), CONS(MISC_EOL, MISC_EOL));
		TyFcn_VectorSet(interp_sysroot, ELEM_FROMFIXNUM(1), CONS(MISC_EOL, MISC_EOL));
		TyFcn_VectorSet(interp_sysroot, ELEM_FROMFIXNUM(2), CONS(MISC_EOL, MISC_EOL));
		TyFcn_VectorSet(interp_sysroot, ELEM_FROMFIXNUM(3), CONS(MISC_EOL, MISC_EOL));
	}
	Namespace3_Assign(repl_ctx->ep_n, repl_ctx->ep_d, SYM("sys-root"), interp_sysroot);
}

elem Interp_ReplCtx()
{
	return(interp_repl_ctx);
}

elem Interp_CurCtx()
{
	return(interp_cur_ctx);
}

elem Interp_NewCtx()
{
	return(TyFcn_CopyVector(interp_repl_ctx));
}

int Interp_TreeBind(elem *ntree, elem *dtree, elem var, elem val)
{
	int a, b, c, d;
	if(!ELEM_CONSP(*ntree))
	{
		*ntree=CONS(CONS(MISC_EOL, MISC_EOL), MISC_EOL);
		*dtree=CONS(CONS(MISC_EOL, MISC_EOL), MISC_EOL);
	}
	if(!ELEM_CONSP(CAR(*ntree)))
	{
		TyFcn_SetCar(*ntree, CONS(MISC_EOL, MISC_EOL));
		TyFcn_SetCar(*dtree, CONS(MISC_EOL, MISC_EOL));
	}
	a=TyFcn_ListLength(CAAR(*ntree));
	b=TyFcn_ListLength(CDAR(*ntree));
	c=(a>b)?a:b;
	d=TyFcn_ListLength(CDR(*ntree));
	if(d<c)
	{
		*ntree=CONS(CONS(CONS(var, MISC_EOL), MISC_EOL), *ntree);
		*dtree=CONS(CONS(CONS(val, MISC_EOL), MISC_EOL), *dtree);
		return(0);
	}

	if(a<b)
	{
		TyFcn_SetCar(CAR(*ntree), CONS(var, CAAR(*ntree)));
		TyFcn_SetCar(CAR(*dtree), CONS(val, CAAR(*dtree)));
		return(0);
	}else
	{
		TyFcn_SetCdr(CAR(*ntree),
			CONS(CONS(var, MISC_EOL), CDAR(*ntree)));
		TyFcn_SetCdr(CAR(*dtree),
			CONS(CONS(val, MISC_EOL), CDAR(*dtree)));
		return(0);
	}
	return(0);
}

int Interp_DefinePrimative(char *name, elem (*func)(), int pc)
{
//	toplevel_n=CONS(CONS(TyFcn_Symbol(name), CAR(toplevel_n)), MISC_EOL);
//	toplevel_d=CONS(CONS(TyFcn_Function(func, pc), CAR(toplevel_d)), MISC_EOL);
#if 1
#if 1
	if(TyFcn_ListLength(CAR(repl_ctx->ep_n))>
		TyFcn_ListLength(CDR(repl_ctx->ep_n)))
	{
		repl_ctx->ep_n=CONS(CONS(SYM(name), MISC_EOL), repl_ctx->ep_n);
		repl_ctx->ep_d=CONS(CONS(TyFcn_Function(func, pc), MISC_EOL), repl_ctx->ep_d);
	}else
	{
		repl_ctx->ep_n=CONS(CONS(SYM(name), CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
		repl_ctx->ep_d=CONS(CONS(TyFcn_Function(func, pc), CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));
	}
#else
	Interp_TreeBind(&repl_ctx->ep_n, &repl_ctx->ep_d,
		SYM(name), TyFcn_Function(func, pc));
#endif
#else
	Namespace3_Bind(&repl_ctx->ep_n, &repl_ctx->ep_d,
		SYM(name), TyFcn_Function(func, pc));
#endif

	SAGC_BindNameAddr(name, func);

	return(MISC_NULL);
}

int Interp_DefineVar(char *name, elem val)
{
#if 1
#if 1
	if(TyFcn_ListLength(CAR(repl_ctx->ep_n))>TyFcn_ListLength(CDR(repl_ctx->ep_n)))
	{
		repl_ctx->ep_n=CONS(CONS(SYM(name), MISC_EOL), repl_ctx->ep_n);
		repl_ctx->ep_d=CONS(CONS(val, MISC_EOL), repl_ctx->ep_d);
	}else
	{
		repl_ctx->ep_n=CONS(CONS(TyFcn_Symbol(name), CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
		repl_ctx->ep_d=CONS(CONS(val, CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));
	}
#else
	Interp_TreeBind(&repl_ctx->ep_n, &repl_ctx->ep_d, SYM(name), val);
#endif
#else
	Namespace3_Bind(&repl_ctx->ep_n, &repl_ctx->ep_d,
		SYM(name), val);
#endif

	return(MISC_NULL);
}

int Interp_DefineDyn(char *name, elem val)
{
	repl_ctx->dyn_n=CONS(CONS(TyFcn_Symbol(name), CAR(repl_ctx->dyn_n)), CDR(repl_ctx->dyn_n));
	repl_ctx->dyn_d=CONS(CONS(val, CAR(repl_ctx->dyn_d)), CDR(repl_ctx->dyn_d));

//	Namespace3_Bind(&repl_ctx->dyn_n, &repl_ctx->dyn_d,
//		SYM(name), val);

	return(MISC_NULL);
}

int Interp_DefinePrimativeDyn(char *name, elem (*func)(), int pc)
{
	Interp_DefineDyn(name, TyFcn_Function(func, pc));
}

elem Interp_FetchDyn(elem name)
{
	elem t;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(interp_cur_ctx);
	t=Namespace3_Lookup(ctx->dyn_n, ctx->dyn_d, name);
	return(t);
}

int Interp_LetDyn(elem name, elem val)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(interp_cur_ctx);
	ctx->dyn_n=CONS(CONS(name, CAR(ctx->dyn_n)), CDR(ctx->dyn_n));
	ctx->dyn_d=CONS(CONS(val, CAR(ctx->dyn_d)), CDR(ctx->dyn_d));
//	Namespace3_Bind(&ctx->dyn_n, &ctx->dyn_d, name, val);

	return(MISC_NULL);
}

elem Interp_FetchDynCtx(elem cur, elem name)
{
	elem t;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(cur);
	t=Namespace3_Lookup(ctx->dyn_n, ctx->dyn_d, name);
	return(t);
}

int Interp_LetDynCtx(elem cur, elem name, elem val)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(cur);
	ctx->dyn_n=CONS(CONS(name, CAR(ctx->dyn_n)), CDR(ctx->dyn_n));
	ctx->dyn_d=CONS(CONS(val, CAR(ctx->dyn_d)), CDR(ctx->dyn_d));
//	Namespace3_Bind(&ctx->dyn_n, &ctx->dyn_d, name, val);

	return(MISC_NULL);
}

int Interp_SetterFunc(elem cur, elem (*f)(elem v, ...), elem arg)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(cur);
	ctx->rax=CONS(TyFcn_Function(f, -2), arg);
	return(0);
}

elem Interp_Rax(elem ectx)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);
	return(ctx->rax);
}

elem Interp_SetRax(elem ectx, elem rax)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);
	ctx->rax=rax;

	return(MISC_NULL);
}

elem Interp_Eval(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d)
{
	elem t;
//	t=HpiComp_Compile(form, form_halt, repl_ctx, 0);
//	if(t==MISC_UNDEFINED)return(t);

//	t=HpiInterp_RunCtx(t, ctx);
	return(t);
}

elem Interp_EvalTop(elem form)
{
	elem t;
	t=HpiComp_Compile(form, TyFcn_ListCopyRec(form_halt), repl_ctx, 0);
	if(t==MISC_UNDEFINED)return(t);

	t=HpiInterp_RunCtx(t, repl_ctx);
	interp_apply_rax=repl_ctx->rax;
	return(repl_ctx->ax);
}

elem Interp_EvalStringTop(char *s)
{
	elem t;
//	sa_print("Interp_EvalStingTop: parse '%s'.\n", s);
	t=ScmParse_Line(&s, 0);
	if(t==MISC_UNDEFINED)return(t);
//	sa_print("Interp_EvalStingTop: parsed.\n");
	return(Interp_EvalTop(t));
}

elem Interp_EvalCurrent(elem form)
{
	elem t;
	t=HpiComp_Compile(form, TyFcn_ListCopyRec(form_halt), interp_context, 0);
	if(t==MISC_UNDEFINED)return(t);

	t=HpiInterp_RunCtx(t, interp_context);
	interp_apply_rax=interp_context->rax;
	return(interp_context->ax);
}

elem Interp_EvalStringCurrent(char *s)
{
	elem t;
	t=ScmParse_Line(&s, 0);
	if(t==MISC_UNDEFINED)return(t);
	return(Interp_EvalCurrent(t));
}

elem Interp_EvalCurrentSafe(elem form)
{
	InterpCtx *newctx;
	elem t;

	t=HpiComp_Compile(form, TyFcn_ListCopyRec(form_halt), interp_context, 0);
	if(t==MISC_UNDEFINED)return(t);

	newctx=HpiInterp_RunCtxSafe(t, interp_context);
	interp_apply_rax=newctx->rax;
	return(newctx->ax);
}

elem Interp_ApplyCurrent(elem func, elem args)
{
	elem t;

	t=interp_context->ip;
	interp_context->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(interp_context);

	interp_context->rp=args;
	interp_context->ax=func;

	HpiInterp_RunLoop(interp_context);

	interp_context->ip=t;
	interp_apply_rax=interp_context->rax;
	return(interp_context->ax);
}

elem Interp_ApplyCurrentSafe(elem func, elem args)
{
	elem t;
	InterpCtx *newctx;

	t=TyFcn_CopyVector(interp_cur_ctx);
	interp_ctx_list=CONS(t, interp_ctx_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=args;
	newctx->ax=func;

	HpiInterp_RunLoop(newctx);

	interp_ctx_list=CDR(interp_ctx_list);

	interp_apply_rax=newctx->rax;
	return(newctx->ax);
}

elem Interp_ApplyCtx(elem ctx, elem func, elem args)
{
	elem t;
	InterpCtx *newctx;

	interp_ctx_list=CONS(ctx, interp_ctx_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(ctx);

	t=newctx->ip;
	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=args;
	newctx->ax=func;

	HpiInterp_RunLoop(newctx);

	interp_ctx_list=CDR(interp_ctx_list);

	newctx->ip=t;
	interp_apply_rax=newctx->rax;
	return(newctx->ax);
}

elem Interp_ApplyCtxSafe(elem ctx, elem func, elem args)
{
	elem t;
	InterpCtx *newctx;

	t=TyFcn_CopyVector(ctx);
	interp_ctx_list=CONS(t, interp_ctx_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=args;
	newctx->ax=func;

	HpiInterp_RunLoop(newctx);

	interp_ctx_list=CDR(interp_ctx_list);

	interp_apply_rax=newctx->rax;
	return(newctx->ax);
}

#if 0
elem Interp_ApplyDelayed(elem thread, elem func, elem args)
{
	elem t;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(thread);

	t=ctx->ip;
	ctx->ip=CONS(CONS(SYM("frame"), CONS(CONS(CONS(SYM("block"), MISC_EOL), TyFcn_ListCopyRec(form_apply)), MISC_EOL)), t);

	HpiInterp_RunStep(ctx);

	ctx->rp=args;
	ctx->ax=func;

	sa_print("apply delayed: ");
	TyFcn_DumpElem(func);
	sa_print("\n");

//	HpiInterp_RunLoop(interp_context);

	return(MISC_NULL);
}
#endif

elem Interp_ApplyCtxTh(elem ctx, elem func, elem args)
{
	elem t;
	InterpCtx *newctx;

	interp_running_list=CONS(ctx, interp_running_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(ctx);
	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=args;
	newctx->ax=func;

	newctx->dyn_n=CONS(SYMG(sym_pidmsgqueue, "pid-msg-queue"),
		newctx->dyn_n);
	newctx->dyn_d=CONS(MISC_EOL, newctx->dyn_d);

	return(MISC_NULL);
}

elem Interp_ApplyThread(elem func, elem args)
{
	elem t;
	InterpCtx *newctx;

	t=TyFcn_CopyVector(interp_cur_ctx);
	interp_running_list=CONS(t, interp_running_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=args;
	newctx->ax=func;

	newctx->dyn_n=CONS(SYMG(sym_pidmsgqueue, "pid-msg-queue"),
		newctx->dyn_n);
	newctx->dyn_d=CONS(MISC_EOL, newctx->dyn_d);

//	HpiInterp_RunLoop(newctx);

	return(t);
}

elem Interp_Vax(elem ectx)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);
	return(ctx->vax);
}

elem Interp_ClearVax(elem ectx)
{
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);
	ctx->vax=MISC_NULL;
	return(MISC_NULL);
}

elem Interp_Thread(elem func)
{
	elem t;
	InterpCtx *newctx;

	t=TyFcn_CopyVector(interp_cur_ctx);
	interp_running_list=CONS(t, interp_running_list);

	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=TyFcn_ListCopyRec(form_frame_apply_halt);

	HpiInterp_RunStep(newctx);

	newctx->rp=MISC_EOL;
	newctx->ax=func;

	newctx->dyn_n=CONS(SYMG(sym_pidmsgqueue, "pid-msg-queue"),
		newctx->dyn_n);
	newctx->dyn_d=CONS(MISC_EOL, newctx->dyn_d);

//	HpiInterp_RunLoop(newctx);

	return(t);
}

elem Interp_BlockThread(elem thread)
{
	elem cur, last;

	if(thread == interp_repl_ctx)
		return(MISC_NULL);

	last=MISC_EOL;
	cur=interp_running_list;
	while(ELEM_CONSP(cur))
	{
		if(CAR(cur)==thread)
		{
			if(last==MISC_EOL)interp_running_list=CDR(cur);
				else TyFcn_SetCdr(last, CDR(cur));
			break;
		}
		last=cur;
		cur=CDR(cur);
	}
	return(MISC_NULL);
}

elem Interp_UnblockThread(elem thread)
{
	if(TyFcn_ObjectInListP(thread, interp_running_list)==MISC_TRUE)
		return(MISC_NULL);

	if(thread == interp_repl_ctx)
		return(MISC_NULL);

//	sa_print("Interp_UnblockThread\n");

	interp_running_list=TyFcn_NAppend(interp_running_list, CONS(thread, MISC_EOL));
	return(MISC_NULL);
}

#if 0
elem Interp_SendThread(elem thread, elem msg)
{
	InterpCtx *ctx;
	elem t;

	sa_print("Interp_SendThread\n");

	msg=CONS(interp_cur_ctx, msg);

	ctx=ELEM_TOOBJECT(thread);
	t=Namespace2_Lookup(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"));
	if(t!=MISC_UNDEFINED)
	{
		t=TyFcn_NAppend(t, CONS(msg, MISC_EOL));

//		sa_print("send, msg queue: ");
//		TyFcn_DumpElem(t);
//		sa_print("\n");

		Namespace2_Assign(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"), t);
	}else
	{
		ctx->dyn_n=CONS(SYMG(sym_pidmsgqueue, "pid-msg-queue"), ctx->dyn_n);
		ctx->dyn_d=CONS(CONS(msg, MISC_EOL), ctx->dyn_d);
	}

	Interp_UnblockThread(thread);

	sa_print("Interp_SendThread: done\n");

	return(MISC_NULL);
}
#endif

elem Interp_SendThreadFrom(elem thread, elem from, elem msg)
{
	InterpCtx *ctx;
	elem t;

//	sa_print("Interp_SendThreadFrom\n");

	msg=CONS(from, msg);

	ctx=ELEM_TOOBJECT(thread);
	t=Namespace2_Lookup(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"));
	if(t!=MISC_UNDEFINED)
	{
		t=TyFcn_NAppend(t, CONS(msg, MISC_EOL));

//		sa_print("send, msg queue: ");
//		TyFcn_DumpElem(t);
//		sa_print("\n");

		Namespace2_Assign(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"), t);
	}else
	{
		ctx->dyn_n=CONS(SYMG(sym_pidmsgqueue, "pid-msg-queue"), ctx->dyn_n);
		ctx->dyn_d=CONS(CONS(msg, MISC_EOL), ctx->dyn_d);
	}

	Interp_UnblockThread(thread);

//	sa_print("Interp_SendThreadFrom: done\n");

	return(MISC_NULL);
}

elem Interp_SendThread(elem thread, elem msg)
{
	return(Interp_SendThreadFrom(thread, interp_cur_ctx, msg));
}

elem Interp_RecieveThread()
{
	elem t;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(interp_cur_ctx);

	t=Namespace2_Lookup(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"));
	if(t==MISC_UNDEFINED)return(MISC_NULL);
	if(t!=MISC_EOL)
	{
		Namespace2_Assign(ctx->dyn_n, ctx->dyn_d, SYMG(sym_pidmsgqueue, "pid-msg-queue"), CDR(t));
		return(CAR(t));
	}

	ctx->vax=SYMG(sym_block, "block");
//	Interp_ApplyDelayed(interp_cur_ctx, TyFcn_Function(&Interp_RecieveThread, 0), MISC_EOL);

	return(MISC_NULL);
}

elem Interp_SleepThread(elem s)
{
	elem t;
	int end;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(interp_cur_ctx);

	end=Sys_TimeMS()+(ELEM_TOFLONUM(s)*1000);
	interp_delay_list=CONS(interp_cur_ctx, interp_delay_list);
	interp_delay_times=CONS(ELEM_FROMFIXNUM(end), interp_delay_times);

	ctx->vax=SYMG(sym_block, "block");

	return(MISC_NULL);
}

int Interp_CheckDelayed()
{
	elem cur1, cur2;
	elem last1, last2;

	cur1=interp_delay_list;
	cur2=interp_delay_times;

	last1=MISC_EOL;
	last2=MISC_EOL;

	while(ELEM_CONSP(cur1) && ELEM_CONSP(cur2))
	{
		if(ELEM_TOFIXNUM(CAR(cur2))<=Sys_TimeMS())
			if(last1!=MISC_EOL)
		{
			Interp_UnblockThread(CAR(cur1));
			TyFcn_SetCdr(last1, CDR(cur1));
			TyFcn_SetCdr(last2, CDR(cur2));
		}else
		{
			Interp_UnblockThread(CAR(cur1));
			interp_delay_list=CDR(cur1);
			interp_delay_times=CDR(cur2);
		}

		last1=cur1;
		last2=cur2;
		cur1=CDR(cur1);
		cur2=CDR(cur2);
	}

	return(0);
}

int Interp_RunQuantum(int ms)
{
	static elem cur=MISC_EOL, last=MISC_EOL;
	elem t;

	while(ms>0)
	{
		if(cur==MISC_EOL)
		{
			cur=interp_running_list;
			last=MISC_EOL;
		}
		if(cur==MISC_EOL)return(0);

		Interp_ClearVax(CAR(cur));

		ms=HpiInterp_RunLoopQuantum(CAR(cur), ms);

		if(Interp_Vax(CAR(cur))!=MISC_NULL)
		{
			if(Interp_Vax(CAR(cur))==SYMG(sym_halt, "halt"))
				Interp_BlockThread(CAR(cur));

//				if(last!=MISC_EOL)TyFcn_SetCdr(last, CDR(cur));
//					else interp_running_list=CDR(cur);
			if(Interp_Vax(CAR(cur))==SYMG(sym_block, "block"))
			{
//				if(last!=MISC_EOL)TyFcn_SetCdr(last, CDR(cur));
//					else interp_running_list=CDR(cur);
				t=CDR(cur);
				Interp_BlockThread(CAR(cur));

//				TyFcn_SetCdr(cur, interp_blocked_list);
//				interp_blocked_list=cur;

				cur=t;
				continue;
			}
		}
		cur=CDR(cur);
	}
	return(0);
}

elem Interp_Load(elem name)
{
//	VFILE *fd;
	int fsz, sk;
	char *buf, *s, *s2;
	elem t, x;

	elem oldsp;

	s=ELEM_TOSTRING(name);
	buf=sa_malloc(strlen(s)+1);
	strcpy(buf, s);
	s=buf;

	sk=0;
	if(!strcmp(s+(strlen(s)-3),".sk"))sk=1;
	if(!strcmp(s+(strlen(s)-3),".lb"))sk=1;
	if(!strcmp(s+(strlen(s)-4),".lb2"))sk=2;
//	if(sk)sa_print("load_sk\n");

#if 0
	fd=vffopen(s, "rb");
	if(!fd)
	{
		sa_print("Interp_Load: no file \"%s\"\n", s);
		return(MISC_UNDEFINED);
	}

	sa_print("Interp_Load: loading \"%s\"\n", s);

	vfseek(fd, 0, 2);
	fsz=vftell(fd);
	vfseek(fd, 0, 0);
	buf=sa_malloc(fsz+1);
	buf[fsz]=0;
	vfread(buf, 1, fsz, fd);

	//HACK: strip out carriage returns
	s=buf;
	s2=buf;
	while(*s)
	{
		if(*s=='\r')s++;
		*s2++=*s++;
	}
	*s2++=0;

#endif

	buf=sa_loadfile(s, NULL);
	if(!buf)
	{
		return(MISC_UNDEFINED);
	}

	s=buf;

//	kprint(s);

//	oldsp=repl_ctx->sp;
//	HpiOp_Return(repl_ctx);

	while(*s)
	{
		t=ScmParse_Line(&s, sk);
		if(t==MISC_UNDEFINED)break;

//		TyFcn_DumpElem(t);
//		sa_print("\n");

		t=Interp_EvalTop(t);

		if(!s)break;
		if(sk)s=ScmParseSK_EatWhite(s);
			else s=ScmParse_EatWhite(s);
	}

	sa_free(buf);

//	repl_ctx->sp=oldsp;

	return(t);
}
