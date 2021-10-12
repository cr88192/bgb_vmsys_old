/*
	2002-09-22:
	objects will have 3 slots: binds_n; binds_d; and handlers.
	handlers will be a list of closures.
	the top rib of the closure bindings will be the pattern.

 */

#include <scmcc.h>
#include <interpctx.h>

extern InterpCtx *repl_ctx, *interp_context;
extern elem interp_repl_ctx;
elem root_object, null_object;
extern elem form_return;

elem TyObj_GetSlot(elem obj, elem sym)
{
	elem ep_n, ep_d, t;

	if(!ELEM_ENVOBJP(obj))
	{
		sa_print("TyObj_GetSlot: non-object.\n");
		abort();
		return(MISC_UNDEFINED);
	}

	ep_n=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1));

	t=Namespace2_Lookup(ep_n, ep_d, sym);
//	if(t==MISC_UNDEFINED)sa_print("obj get-slot: no var.\n");

	return(t);
}

elem TyObj_GetSlot2(elem obj, elem sym)
{
	elem ep_n, ep_d, t;

	ep_n=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1));

//	t=Namespace2_Lookup(ep_n, ep_d, sym);
//	if(t==MISC_UNDEFINED)sa_print("obj get-slot: no var.\n");

	t=Namespace2_Trace(ep_n, ep_d, MISC_EOL, sym);
	if(t==MISC_UNDEFINED)
	{
		sa_print("obj get-slot: no var.\n");
		return(t);
	}
	interp_context->ax=Namespace2_RetrieveTrace(ep_n, ep_d, t);
	interp_context->rax=Namespace2_LocativeTrace(ep_n, ep_d, t);

	return(interp_context->ax);
}

elem TyObj_SetSlot(elem obj, elem var, elem val)
{
	elem ep_n, ep_d, t;

//	sa_print("obj set\n");

	ep_n=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1));

	t=Namespace2_Assign(ep_n, ep_d, var, val);
	if(t==MISC_UNDEFINED)
	{
//		sa_print("obj set: bind\n");
		ep_n=CONS(var, ep_n);
		ep_d=CONS(val, ep_d);
		TyFcn_VectorSet(obj, ELEM_FROMFIXNUM(0), ep_n);
		TyFcn_VectorSet(obj, ELEM_FROMFIXNUM(1), ep_d);
		t=val;
	}

	return(t);
}

elem TyObj_Clone(elem obj)
{
	elem ep_n, ep_d, x;

//	sa_print("obj clone\n");

	x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_ENVOBJ));

	ep_n=TyFcn_ListCopy(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0)));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), ep_n);
	ep_d=TyFcn_ListCopy(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1)));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ep_d);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2)));

/*
	t=Namespace2_Assign(ep_n, ep_d, SYM("parent"), obj);
	if(t==MISC_UNDEFINED)
	{
//		sa_print("obj clone: bind\n");
		ep_n=CONS(SYM("parent"), ep_n);
		ep_d=CONS(obj, ep_d);
		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), ep_n);
		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ep_d);
	}
*/

	return(x);
}

elem TyObj_AddHandler(elem obj, elem proc)
{
	elem t;

//	sa_print("obj handler\n");

	t=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2));
	TyFcn_VectorSet(obj, ELEM_FROMFIXNUM(2), CONS(proc, t));

	return(proc);
}

elem TyObj_Dispatch(InterpCtx *ctx)
{
	elem ep_n, ep_d, cur, t, close, dist;
	close=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	cur=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(2));
	while(ELEM_CONSP(cur))
	{
		t=CAR(TyFcn_VectorRef(CAR(cur), ELEM_FROMFIXNUM(0)));
		t=TyFcn_MatchV(t, ctx->rp);
		if(t!=MISC_FALSE)if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			close=CAR(cur);
			dist=t;
		}
		cur=CDR(cur);
	}

	if(close!=MISC_NULL)
	{
		ctx->ax=close;
		HpiOp_Apply(ctx);
		return(MISC_NULL);
	}

//	sa_error("TyObj_dispatch: no handler for message '");
//	TyFcn_DumpElem(ctx->rp);
//	sa_print("'\n");
	
	ctx->ax=MISC_UNDEFINED;
	ctx->ip=form_return;

	return(MISC_UNDEFINED);
}

elem TyObj_InvokeObject(elem obj, elem msg)
{
	elem cur, t, close, dist;
	elem a, b;

	close=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	cur=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2));
	while(ELEM_CONSP(cur))
	{
		a=CAR(TyFcn_VectorRef(CAR(cur), ELEM_FROMFIXNUM(0)));
		t=TyFcn_MatchV(a, msg);
		if((t!=MISC_FALSE) && (CAR(msg)==CAR(a)))
			if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			close=CAR(cur);
			dist=t;
		}
		cur=CDR(cur);
	}

	if(close!=MISC_NULL)
	{
		b=TyFcn_CopyVector(interp_repl_ctx);
		Interp_LetDynCtx(b, SYM("self"), obj);
		a=Interp_ApplyCtx(b, close, msg);
		return(a);
	}

	return(MISC_UNDEFINED);
}

elem TyObj_ApplySelf(elem obj, elem rest)
{
	elem ep_n, ep_d, cur, t, close, dist;
	close=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	cur=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2));
	while(ELEM_CONSP(cur))
	{
		t=CAR(TyFcn_VectorRef(CAR(cur), ELEM_FROMFIXNUM(0)));
		t=TyFcn_MatchV(t, rest);
		if(t!=MISC_FALSE)if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			close=CAR(cur);
			dist=t;
		}
		cur=CDR(cur);
	}

	if(close!=MISC_NULL)
	{
		HpiCmd_NewFrame(interp_context);

		interp_context->ax=close;
		HpiOp_Apply(interp_context);
		return(MISC_NULL);
	}
	
	HpiCmd_NewFrame(interp_context);
	interp_context->ax=MISC_UNDEFINED;
	interp_context->ip=form_return;

	return(MISC_UNDEFINED);
}

#if 0
elem TyObj_BuildHandler(InterpCtx *ctx, char *pattern, elem (*proc)())
{
	elem t, x, p;

	x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(5), ELEM_FROMFIXNUM(VECTOR_CLOSURE));

//	t=CADR(CAR(ctx->ip));
	p=ScmParse_Item(&pattern, 0);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), CONS(p, MISC_EOL));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), MISC_EOL);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(3), MISC_EOL);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(4), MISC_EOL);

//	t=CADDR(CAR(ctx->ip));
	t=TyFcn_Function(proc, ELEM_TOFIXNUM(TyFcn_ListLength(p))+1);
	t=CONS(CONS(SYM("trampoline"), CONS(t, MISC_EOL)), MISC_EOL);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

	return(x);
}
#endif

elem TyObj_ObjectP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_ENVOBJP(a)));
}

elem TyObj_MemberP(elem a, elem b)
{
	elem ep_n, ep_d, t;

	ep_n=TyFcn_VectorRef(a, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(a, ELEM_FROMFIXNUM(1));

	t=Namespace2_Lookup(ep_n, ep_d, b);

	return(ELEM_FROMBOOL(t!=MISC_UNDEFINED));
}

elem TyObj_ObjectFlatten(elem obj)
{
	elem ep_n, ep_d, t;
	elem c_n, c_d, cur, x;

	t=MISC_EOL;
	ep_n=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1));

	c_n=ep_n;
	c_d=ep_d;

	while(c_n!=MISC_EOL)
	{
		x=CAR(c_d);
		if(ELEM_CLOSUREP(x))x=Builtin_ClosureBody(x);
		if(ELEM_SYMBOLP(x))x=CONS(SYM("quote"), CONS(x, MISC_EOL));

		x=CONS(TyFcn_Keywordify(CAR(c_n)), CONS(x, MISC_EOL));
		t=CONS(x, t);

		c_n=CDR(c_n);
		c_d=CDR(c_d);
	}

	cur=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2));
	while(ELEM_CONSP(cur))
	{
		x=CAR(TyFcn_VectorRef(CAR(cur), ELEM_FROMFIXNUM(0)));
		x=CONS(x, CONS(Builtin_ClosureBody(CAR(cur)), MISC_EOL));
		t=CONS(x, t);
		cur=CDR(cur);
	}

	t=CONS(SYM("quote"), CONS(t, MISC_EOL));
	t=CONS(SYM("object-flat"), CONS(t, MISC_EOL));

	return(t);
}

elem TyObj_ObjectUnflatten(elem rest)
{
	elem cur, e;
	elem o;

	o=TyObj_Clone(null_object);

	cur=rest;
	while(cur!=MISC_EOL)
	{
		e=CAR(cur);
		if(ELEM_SYMKEYWORDP(CAR(e)))
		{
			TyObj_SetSlot(o,
				TyFcn_KeywordBase(CAR(e)),
				Interp_EvalCurrent(CADR(e)));
		}else
		{
			TyObj_AddHandler(o, Builtin_Eval(CADR(e), MISC_EOL));
		}
		cur=CDR(cur);
	}

	return(o);
}

elem TyObj_ObjectPrint(elem obj)
{
	elem ep_n, ep_d, t;
	elem c_n, c_d, cur, x;

//	t=Interp_ApplyCtxSafe(interp_repl_ctx, obj,
//		CONS(SYM("print:"), MISC_EOL));
	t=TyObj_InvokeObject(obj, CONS(SYM("print:"), MISC_EOL));
	if(t!=MISC_UNDEFINED)return(t);

	t=MISC_EOL;
	ep_n=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(0));
	ep_d=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(1));

	c_n=ep_n;
	c_d=ep_d;

	while(c_n!=MISC_EOL)
	{
		x=CAR(c_d);
		if(ELEM_CLOSUREP(x))x=Builtin_ClosureBody(x);
//		if(ELEM_SYMBOLP(x))x=CONS(SYM("quote"), CONS(x, MISC_EOL));

		x=CONS(TyFcn_Keywordify(CAR(c_n)), CONS(x, MISC_EOL));
		t=CONS(x, t);

		c_n=CDR(c_n);
		c_d=CDR(c_d);
	}

	cur=TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(2));
	while(ELEM_CONSP(cur))
	{
		x=CAR(TyFcn_VectorRef(CAR(cur), ELEM_FROMFIXNUM(0)));
		x=CONS(x, CONS(Builtin_ClosureBody(CAR(cur)), MISC_EOL));
		t=CONS(x, t);
		cur=CDR(cur);
	}

	TyPrint_PrintFlags(t, FIXNUM(TYPRINT_CODE));
	return(MISC_NULL);
}

elem TyObj_Init()
{
	elem x;

	MMGC3_AddRoot(&root_object);
	MMGC3_AddRoot(&null_object);

	null_object=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_ENVOBJ));

	TyFcn_VectorSet(null_object, ELEM_FROMFIXNUM(0), MISC_EOL);
	TyFcn_VectorSet(null_object, ELEM_FROMFIXNUM(1), MISC_EOL);
	TyFcn_VectorSet(null_object, ELEM_FROMFIXNUM(2), MISC_EOL);

	root_object=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_ENVOBJ));

	TyFcn_VectorSet(root_object, ELEM_FROMFIXNUM(0), MISC_EOL);
	TyFcn_VectorSet(root_object, ELEM_FROMFIXNUM(1), MISC_EOL);
	TyFcn_VectorSet(root_object, ELEM_FROMFIXNUM(2), MISC_EOL);

	Interp_DefinePrimative("clone",		&TyObj_Clone,		1);
	Interp_DefinePrimative("get-slot",	&TyObj_GetSlot2,	2);
	Interp_DefinePrimative("set-slot",	&TyObj_SetSlot,		3);
	Interp_DefinePrimative("add-handler",	&TyObj_AddHandler,	2);

	Interp_DefinePrimative("object?",	&TyObj_ObjectP,		1);
	Interp_DefinePrimative("member?",	&TyObj_MemberP,		2);

	Interp_DefinePrimative("apply-self",	&TyObj_ApplySelf,	2);
	Interp_DefinePrimative("object-flatten",&TyObj_ObjectFlatten,	1);
	Interp_DefinePrimative("object-flat",	&TyObj_ObjectUnflatten,	1);

	repl_ctx->ep_n=CONS(CONS(SYM("root-obj"),	CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
	repl_ctx->ep_d=CONS(CONS(root_object,		CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));

	repl_ctx->ep_n=CONS(CONS(SYM("null-obj"),	CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
	repl_ctx->ep_d=CONS(CONS(null_object,		CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));

	return(0);
}
