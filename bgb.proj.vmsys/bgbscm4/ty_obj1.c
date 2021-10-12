/*
	2002-09-22:
	objects will have 3 slots: binds_n; binds_d; and handlers.
	handlers will be a list of closures.
	the top rib of the closure bindings will be the pattern.

	2003-06-26:
	redesign of tyobj: unify slots and handlers, add links field.

	2003-07-06:
	plans for lazy mirroring:
	initial values for slots fields are #z. it maintains mirror list,
	attempt to invoke causes it to be coppied from a mirror.
	it will not recieve updates until it is mirrored (until then it will
	act like a placeolder...).

 */

#include <scmcc.h>
#include <interpctx.h>

extern InterpCtx *repl_ctx, *interp_context;
extern elem interp_repl_ctx;
elem root_object, null_object;
extern elem form_return;

elem sym_x=MISC_NULL;
elem sym_self=MISC_NULL;

int tyobj_notify=0;
elem tyobj_unflat;

elem TyObj_GetSlot(elem obj, elem sym)
{
	elem ep_n, ep_d, t;
	elem cur_n, cur_d;
	elem b;

	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

//	sa_print("obj get slot\n");

	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	cur_n=ep_n;
	cur_d=ep_d;

	b=sym;
	if(ELEM_SYMBOLP(b))b=TyFcn_Keywordify(b);

	while(ELEM_CONSP(cur_n))
	{
		if(TyFcn_EqualP(CAR(cur_n), b)==MISC_TRUE)
			return(CAR(cur_d));
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

	return(MISC_UNDEFINED);
}

elem TyObj_GetSlot2(elem obj, elem sym)
{
	elem ep_n, ep_d, t;
	elem cur_n, cur_d;
	elem b;

	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

//	sa_print("obj get slot 2\n");

	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	cur_n=ep_n;
	cur_d=ep_d;

	b=sym;
	if(ELEM_SYMBOLP(b))b=TyFcn_Keywordify(b);

	while(ELEM_CONSP(cur_n))
	{
		if(TyFcn_EqualP(CAR(cur_n), b)==MISC_TRUE)
			return(CAR(cur_d));
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

	return(MISC_UNDEFINED);
}

elem TyObj_SetSlot(elem obj, elem var, elem val)
{
	elem ep_n, ep_d, t;
	elem cur_n, cur_d;
	elem b;

//	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

//	sa_print("obj set slot:");
//	TyFcn_DumpElem(var);
//	sa_print(" <= ");
//	TyFcn_DumpElem(val);
//	sa_print("\n");

	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	cur_n=ep_n;
	cur_d=ep_d;

	b=var;
	if(ELEM_SYMBOLP(b))b=TyFcn_Keywordify(b);

	while(ELEM_CONSP(cur_n))
	{
		if(TyFcn_EqualP(CAR(cur_n), b)==MISC_TRUE)
		{
			t=CAR(cur_d);
			if(ELEM_CONSTRAINTP(t) && !ELEM_CONSTRAINTP(val))
			{
				b=VECTOR_REF(t, 6);
				HpiCmd_InvalidateConstraint(t);
				VECTOR_SET(t, 6, val);
				t=b;
			}else
			{
				if(ELEM_CONSTRAINTP(t))
					HpiCmd_InvalidateConstraint(t);
				TyFcn_SetCar(cur_d, val);
			}
			return(t);
		}
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

//	sa_print("obj set: bind\n");
	ep_n=CONS(b, ep_n);
	ep_d=CONS(val, ep_d);
	VECTOR_SET(obj, 0, ep_n);
	VECTOR_SET(obj, 1, ep_d);

	t=val;

	return(t);
}

elem TyObj_SetSlot2(elem obj, elem var, elem val)
{
	elem cur, t;
	elem var2, val2;

	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

//	var2=CONS(SYM("quote"), CONS(var, MISC_EOL));
	var2=TyFcn_Keywordify(var);
	val2=CONS(SYM("quote"), CONS(val, MISC_EOL));

	cur=TyObj_GetLinks(obj);
	while(cur!=MISC_EOL)
	{
		t=CONS(SYM("::assign"), CONS(var,
			CONS(val, CONS(obj, MISC_EOL))));
//		t=CONS(SYM("-*>"), CONS(CAAR(cur), t));
//		Builtin_Eval(t);
		if(CADR(CAR(cur))==MISC_TRUE)
			Interp_ApplyCtxSafe(interp_repl_ctx, CAAR(cur), t);
		cur=CDR(cur);
	}

	return(TyObj_SetSlot(obj, var, val));
}

elem TyObj_Clone(elem obj)
{
	elem x;

//	sa_print("obj clone\n");
	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

	x=VECTOR_NEWT(3, VECTOR_ENVOBJ);

	VECTOR_SET(x, 0, TyFcn_ListCopy(VECTOR_REF(obj, 0)));
	VECTOR_SET(x, 1, TyFcn_ListCopy(VECTOR_REF(obj, 1)));
	VECTOR_SET(x, 2, MISC_EOL);

	return(x);
}

elem TyObj_CloneRoot()
{
	return(TyObj_Clone(root_object));
}

elem TyObj_CloneNull()
{
	return(TyObj_Clone(null_object));
}

elem TyObj_AddHandler(elem obj, elem proc)
{
	elem t;

//	sa_print("obj handler\n");
	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

	t=CAR(VECTOR_REF(proc, 0));
	t=TyObj_SetSlot(obj, t, proc);

	return(t);
}

elem TyObj_SlotNames(elem obj)
{
	elem cur, t, x;

	x=MISC_EOL;
	cur=VECTOR_REF(obj, 0);
	while(ELEM_CONSP(cur))
	{
		t=CAR(cur);
		if(ELEM_SYMKEYWORDP(t))
		{
			t=TyFcn_KeywordBase(t);
			x=CONS(t, x);
		}
		cur=CDR(cur);
	}
	return(x);
}

elem TyObj_Dispatch(InterpCtx *ctx)
{
	elem ep_n, ep_d, cur, t, x;
	elem cl_n, cl_d, dist;

//	sa_print("obj dispatch: '");
//	TyFcn_DumpElem(ctx->rp);
//	sa_print("'\n");

#if 0
	t=ctx->rp;
	if(ELEM_CONSP(t))
	{
		if(CAR(t)==SYM("::notify-stub"))
		{
//			sa_print("got notify: ");
//			TyPrint_PrintDefaults(CADR(t));
//			sa_print("\n");

			x=CADR(t);
			x=CONS(x, CONS(MISC_FALSE, MISC_EOL));

			TyObj_SetLinks(ctx->ax,
				CONS(x, TyObj_GetLinks(ctx->ax)));
			ctx->ax=MISC_NULL;
			ctx->ip=form_return;
			return(MISC_NULL);
		}

		if(CAR(t)==SYM("::notify-active"))
		{
//			sa_print("got notify: ");
//			TyPrint_PrintDefaults(CADR(t));
//			sa_print("\n");

			x=CADR(t);
			x=CONS(x, CONS(MISC_TRUE, MISC_EOL));

			TyObj_SetLinks(ctx->ax,
				CONS(x, TyObj_GetLinks(ctx->ax)));
			ctx->ax=MISC_NULL;
			ctx->ip=form_return;
			return(MISC_NULL);
		}

		if(CAR(t)==SYM("::assign"))
		{
			sa_print("got assign\n");
			t=TyObj_SetSlot(ctx->ax, CADR(t), CADDR(t));

			ctx->ax=t;
			ctx->ip=form_return;
			return(MISC_NULL);
		}
	}
#endif

	if(VECTOR_REF(ctx->ax, 0)==MISC_NULL)TyObj_Sync(ctx->ax);

	cl_n=MISC_NULL;
	cl_d=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	ep_n=VECTOR_REF(ctx->ax, 0);
	ep_d=VECTOR_REF(ctx->ax, 1);

	while(ELEM_CONSP(ep_n))
	{
		t=CAR(ep_n);
		if(ELEM_SYMKEYWORDP(t))t=CONS(t, SYMG(sym_x, "x"));
		t=TyFcn_MatchV(t, ctx->rp);
		if(t!=MISC_FALSE)if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			cl_n=CAR(ep_n);
			cl_d=CAR(ep_d);
			dist=t;
		}
		ep_n=CDR(ep_n);
		ep_d=CDR(ep_d);
	}

	if(ELEM_SYMKEYWORDP(cl_n))
	{
		if(CDR(ctx->rp)!=MISC_EOL)
		{
			ctx->ax=TyObj_SetSlot2(ctx->ax,
				CAR(ctx->rp), CADR(ctx->rp));
		}else
		{
			ctx->ax=cl_d;
			if(ELEM_CONSTRAINTP(ctx->ax))
				ctx->ax=HpiCmd_EvalConstraint(ctx);
		}
		ctx->ip=form_return;
		return(MISC_NULL);
	}

	if(cl_d!=MISC_NULL)
	{
		ctx->ax=cl_d;
		HpiOp_Apply(ctx);
		return(MISC_NULL);
	}

#if 0
	if(ELEM_CONSP(ctx->rp))if(ELEM_CONSP(CAR(ctx->rp)))
	{
		if(CDR(ctx->rp)!=MISC_EOL)
			ctx->ax=TyObj_SetSlot(ctx->ax,
				CAR(ctx->rp), CADR(ctx->rp));
			else ctx->ax=TyObj_SetSlot(ctx->ax, CAR(ctx->rp));
		ctx->ip=form_return;
		return(MISC_NULL);
	}
#endif

//	sa_error("TyObj_dispatch: no handler for message '");
//	TyFcn_DumpElem(ctx->rp);
//	sa_print("'\n");
	
	ctx->ax=MISC_UNDEFINED;
	ctx->ip=form_return;

	return(MISC_UNDEFINED);
}

elem TyObj_InvokeObject(elem obj, elem msg)
{
	elem ep_n, ep_d, t, cl_n, cl_d, dist;
	elem a, b;

//	sa_print("obj invoke\n");
	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

	cl_n=MISC_NULL;
	cl_d=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	while(ELEM_CONSP(ep_n))
	{
		a=CAR(ep_n);
		t=TyFcn_MatchV(a, msg);
		if((t!=MISC_FALSE) && (CAR(msg)==CAR(a)))
			if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			cl_n=CAR(ep_n);
			cl_d=CAR(ep_d);
			dist=t;
		}
		ep_n=CDR(ep_n);
		ep_d=CDR(ep_d);
	}

	if(cl_d!=MISC_NULL)
	{
		b=TyFcn_CopyVector(interp_repl_ctx);
		Interp_LetDynCtx(b, SYMG(sym_self, "self"), obj);
		a=Interp_ApplyCtx(b, cl_d, msg);
		return(a);
	}

	return(MISC_UNDEFINED);
}

elem TyObj_ApplySelf(elem obj, elem rest)
{
	elem ep_n, ep_d, t, cl_n, cl_d, dist;
	elem a;

//	sa_print("obj apply self\n");
	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

	cl_n=MISC_NULL;
	cl_d=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	while(ELEM_CONSP(ep_n))
	{
		a=CAR(ep_n);
		t=TyFcn_MatchV(a, rest);
		if((t!=MISC_FALSE) && (CAR(rest)==CAR(a)))
			if(ELEM_TOFIXNUM(t)>ELEM_TOFIXNUM(dist))
		{
			cl_n=CAR(ep_n);
			cl_d=CAR(ep_d);
			dist=t;
		}
		ep_n=CDR(ep_n);
		ep_d=CDR(ep_d);
	}

	if(cl_d!=MISC_NULL)
	{
		HpiCmd_NewFrame(interp_context);

		interp_context->ax=cl_d;
		HpiOp_Apply(interp_context);
		return(MISC_NULL);
	}
	
	HpiCmd_NewFrame(interp_context);
	interp_context->ax=MISC_UNDEFINED;
	interp_context->ip=form_return;

	return(MISC_UNDEFINED);
}

elem TyObj_ObjectP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_ENVOBJP(a)));
}

elem TyObj_MemberP(elem a, elem b)
{
	elem ep_n, ep_d;

	if(VECTOR_REF(a, 0)==MISC_NULL)TyObj_Sync(a);

	ep_n=VECTOR_REF(a, 0);
	ep_d=VECTOR_REF(a, 1);

	b=TyFcn_Keywordify(b);

	while(ELEM_CONSP(ep_n))
	{
		if(CAR(ep_n)==b)return(MISC_TRUE);
		ep_n=CDR(ep_n);
		ep_d=CDR(ep_d);
	}

	return(MISC_FALSE);
}


elem TyObj_NotifyLinks(elem obj, elem sym, elem lst)
{
	elem cur, t;

	tyobj_notify=1;

	sa_print("Notify ");

	cur=lst;
	while(cur!=MISC_EOL)
	{
		TyPrint_PrintDefaults(CAR(cur));
		sa_print(" ");
		t=CONS(sym, CONS(TyFcn_Box(obj), MISC_EOL));
		t=CONS(SYM("->"), CONS(CAAR(cur), t));
		Builtin_Eval(t, MISC_NULL);
//		Interp_ApplyCtxSafe(interp_repl_ctx, CAAR(cur), t);
//		MRP_ApplyU(CAR(cur), t);
		cur=CDR(cur);
	}
	sa_print("\n");

	tyobj_notify=0;

	return(MISC_NULL);
}

elem TyObj_ObjStub(elem links)
{
	elem x;

	x=VECTOR_NEWT(3, VECTOR_ENVOBJ);

	VECTOR_SET(x, 0, MISC_NULL);
	VECTOR_SET(x, 1, MISC_NULL);
	VECTOR_SET(x, 2, links);

	TyObj_NotifyLinks(x, SYM("::notify-stub"), links);

	return(x);
}

elem TyObj_Sync(elem obj)
{
	elem x, t;

	x=VECTOR_REF(obj, 2);

	VECTOR_SET(obj, 0, MISC_EOL);
	VECTOR_SET(obj, 1, MISC_EOL);

	t=CAAR(x);
	t=CONS(SYM("req-copy"), CONS(t, MISC_EOL));
	t=Builtin_Eval(t, MISC_NULL);
//	TyFcn_DumpElem(t);
//	sa_print("\n");

	TyObj_ObjectUnflattenObj(obj, t);

	TyObj_NotifyLinks(obj, SYM("::notify-active"), x);

	return(MISC_NULL);
}

elem TyObj_ObjectFlatten(elem obj)
{
	elem ep_n, ep_d, t;
	elem c_n, c_d, cur, x;

	sa_print("flatten\n");
	if(VECTOR_REF(obj, 0)==MISC_NULL)TyObj_Sync(obj);

	x=MISC_EOL;
	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);


	//make last so that whole obj is created before possible updates
//	t=CONS(TyFcn_Box(obj), TyObj_GetLinks(obj));
//	t=CONS(SYM("::links"), CONS(t, MISC_EOL));
//	x=CONS(t, x);

	c_n=ep_n;
	c_d=ep_d;

	while(c_n!=MISC_EOL)
	{
		t=CAR(c_d);
		if(ELEM_CONSP(t))t=CONS(SYM("quote"), CONS(t, MISC_EOL));
		if(ELEM_CLOSUREP(t))t=Builtin_ClosureBody(t);
		if(ELEM_SYMBOLP(t))t=CONS(SYM("quote"), CONS(t, MISC_EOL));

		t=CONS(CAR(c_n), CONS(t, MISC_EOL));
		x=CONS(t, x);

		c_n=CDR(c_n);
		c_d=CDR(c_d);
	}

//	x=CONS(SYM("quote"), CONS(x, MISC_EOL));
//	x=CONS(SYM("object-flat"), CONS(x, MISC_EOL));

	return(x);
}

elem TyObj_UnflatLinksub(elem obj)
{
	elem t, t2;
	int i;

	if(ELEM_SPECIALP(obj))
	{
		i=ELEM_TOSPECIAL(obj);
		t=TyFcn_ListRef(tyobj_unflat, FIXNUM(i));
		sa_print("obj special %d %X\n", i, t);
		return(t);
	}

	if(ELEM_CONSP(obj))
	{
		t=TyObj_UnflatLinksub(CAR(obj));
		t2=TyObj_UnflatLinksub(CDR(obj));
		return(CONS(t, t2));
	}

	return(obj);
}

elem TyObj_BeginUnflatten(elem rest)
{
	elem o, x;

	x=tyobj_unflat;
	o=TyObj_Clone(null_object);
	tyobj_unflat=CONS(o, x);

	return(MISC_NULL);
}

elem TyObj_ObjectUnflattenObj(elem obj, elem rest)
{
	elem cur, e;
	elem o, t, x;

	o=obj;

	cur=rest;
	while(cur!=MISC_EOL)
	{
		e=CAR(cur);
#if 0
		if(CAR(e)==SYM("::links"))
		{
			TyObj_NotifyLinks(o, CADR(e));
			TyObj_SetLinks(o, CADR(e));
			cur=CDR(cur);
			continue;
		}
#endif
		t=Builtin_Eval(CADR(e), MISC_NULL);
//		t=TyObj_UnflatLinksub(t);

		TyObj_SetSlot(o, CAR(e), t);
		cur=CDR(cur);
	}

	return(o);
}

elem TyObj_ObjectUnflatten(elem rest)
{
	elem o, t;

	o=TyObj_Clone(null_object);
	t=TyObj_ObjectUnflattenObj(o, rest);
	return(t);
}

elem TyObj_GetLinks(elem obj)
{
	return(VECTOR_REF(obj, 2));
}

elem TyObj_SetLinks(elem obj, elem links)
{
	VECTOR_SET(obj, 2, links);

	return(MISC_NULL);
}

elem TyObj_Notify(elem obj, elem obj2, elem state)
{
	elem s, t, x;

	x=VECTOR_REF(obj, 2);

	t=x;
	while(t!=MISC_EOL)
	{
		if(CAAR(t)==obj2)
		{
			s=CDR(CAR(t));
			TyFcn_SetCar(s, state);
			return(MISC_NULL);
		}
		t=CDR(t);
	}

	t=CONS(obj2, CONS(state, MISC_EOL));
	x=CONS(t, x);

	VECTOR_SET(obj, 2, x);

	return(MISC_NULL);
}

elem TyObj_ObjectPrint(elem obj)
{
	elem ep_n, ep_d, t;
	elem c_n, c_d, cur, x;

	if(VECTOR_REF(obj, 0)==MISC_NULL)
	{
		t=CONS(SYM("stub"), MISC_EOL);
		TyPrint_PrintDefaults(t);
		return(MISC_NULL);
	}

	t=TyObj_InvokeObject(obj, CONS(SYM("print:"), MISC_EOL));
	if(t!=MISC_UNDEFINED)return(t);

	x=MISC_EOL;
	ep_n=VECTOR_REF(obj, 0);
	ep_d=VECTOR_REF(obj, 1);

	c_n=ep_n;
	c_d=ep_d;

	while(c_n!=MISC_EOL)
	{
		t=CAR(c_d);
		if(ELEM_CLOSUREP(t))t=Builtin_ClosureBody(t);
//		if(ELEM_SYMBOLP(t))t=CONS(SYM("quote"), CONS(t, MISC_EOL));

		t=CONS(CAR(c_n), CONS(t, MISC_EOL));
		x=CONS(t, x);

		c_n=CDR(c_n);
		c_d=CDR(c_d);
	}

	TyPrint_PrintFlags(x, FIXNUM(TYPRINT_CODE|TYPRINT_NOOBJ));
	return(MISC_NULL);
}

elem TyObj_Init()
{
	elem x;

	SAGC_AddRoot(&root_object);
	SAGC_AddRoot(&null_object);

	SAGC_AddRoot(&tyobj_unflat);
	tyobj_unflat=MISC_EOL;

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
	Interp_DefinePrimative("set-slot",	&TyObj_SetSlot2,	3);
	Interp_DefinePrimative("add-handler",	&TyObj_AddHandler,	2);

	Interp_DefinePrimative("object?",	&TyObj_ObjectP,		1);
	Interp_DefinePrimative("member?",	&TyObj_MemberP,		2);

	Interp_DefinePrimative("apply-self",	&TyObj_ApplySelf,	2);
	Interp_DefinePrimative("object-flatten",&TyObj_ObjectFlatten,	1);
	Interp_DefinePrimative("object-flat",	&TyObj_ObjectUnflatten,	1);

//	repl_ctx->ep_n=CONS(CONS(SYM("root-obj"),	CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
//	repl_ctx->ep_d=CONS(CONS(root_object,		CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));

//	repl_ctx->ep_n=CONS(CONS(SYM("null-obj"),	CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
//	repl_ctx->ep_d=CONS(CONS(null_object,		CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));

	Interp_DefineVar("root-obj", root_object);
	Interp_DefineVar("null-obj", null_object);

	return(0);
}
