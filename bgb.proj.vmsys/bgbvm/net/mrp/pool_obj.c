/*
	2002-09-22:
	objects will have 3 slots: binds_n; binds_d; and handlers.
	handlers will be a list of closures.
	the top rib of the closure bindings will be the pattern.

	2003-06-26:
	redesign object system to support pooling, make use type-x and
	integrate with the not code.

	next thought: since I have done this, it would be better just to
	modify ty-obj, as then I can leverage all the existing ty-obj based
	stuff...
 */

#include <scmcc.h>
#include <interpctx.h>

extern InterpCtx *repl_ctx, *interp_context;
extern elem interp_repl_ctx;
extern elem form_apply;

elem plobj_null_obj;

typedef struct {
elem links; //links to mirrors
elem hdl_n; //handler names, symbols and lists for handlers, keywords for names
elem hdl_d; //handler data
}PlObj_Object;

elem PlObj_Clone(elem obj)
{
	PlObj_Object *a, *b;

	a=TypeX_Data(obj);
	b=TypeX_Alloc("plobj-object", sizeof(PlObj_Object));

	b->links=MISC_EOL;
	b->hdl_n=TyFcn_ListCopy(a->hdl_n);
	b->hdl_d=TyFcn_ListCopy(a->hdl_d);

	return(x);
}

elem PlObj_Bind(elem obj, elem pattern, elem value)
{
	PlObj_Object *a;

	a=TypeX_Data(obj);
	a->hdl_n=CONS(pattern, a->hdl_n);
	a->hdl_d=CONS(value, a->hdl_d);

	return(MISC_NULL);
}

elem PlObj_Apply(elem obj, elem rest)
{
	elem cur_n, cur_d, t, x;
	elem close, dist, cpat;
	PlObj_Object *a;

	a=TypeX_Data(obj);
	close=MISC_NULL;
	cpat=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	cur_n=a->hdl_n;
	cur_d=a->hdl_d;
	while(ELEM_CONSP(cur_n))
	{
		t=CAR(cur_n);
		if(ELEM_SYMKEYWORDP(t))t=CONS(t, MISC_EOL);

		t=TyFcn_MatchV(t, rest);
		if(t!=MISC_FALSE)if(TOINT(t)>TOINT(dist))
		{
			cpat=CAR(cur_n);
			close=CAR(cur_d);
			dist=t;
		}
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

	if(ELEM_SYMKEYWORDP(cpat))return(close);

	if(close!=MISC_NULL)
	{
		HpiCmd_NewFrame(interp_context);

		interp_context->dyn_n=CONS(SYM("self"),
			interp_context->dyn_n);
		interp_context->dyn_d=CONS(obj,
			interp_context->dyn_d);

		interp_context->rp=rest;
		interp_context->ax=close;
		HpiOp_Apply(interp_context);
		return(MISC_NULL);
	}

//	sa_error("PlObj_dispatch: no handler for message '");
//	TyFcn_DumpElem(rest);
//	sa_print("'\n");

	return(MISC_UNDEFINED);
}

elem PlObj_InvokeObject(elem obj, elem msg)
{
	elem cur_n, cur_d, t, x;
	elem close, dist, cpat;
	PlObj_Object *a;

	a=TypeX_Data(obj);
	close=MISC_NULL;
	cpat=MISC_NULL;
	dist=ELEM_FROMFIXNUM(0);

	cur_n=a->hdl_n;
	cur_d=a->hdl_d;
	while(ELEM_CONSP(cur_n))
	{
		t=CAR(cur_n);
		if(ELEM_SYMKEYWORDP(t))t=CONS(t, MISC_EOL);

		t=TyFcn_MatchV(t, rest);
		if(t!=MISC_FALSE)if(TOINT(t)>TOINT(dist))
		{
			cpat=CAR(cur_n);
			close=CAR(cur_d);
			dist=t;
		}
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

	if(ELEM_SYMKEYWORDP(cpat))return(close);

	if(close!=MISC_NULL)
	{
		t=TyFcn_CopyVector(interp_repl_ctx);
		Interp_LetDynCtx(t, SYM("self"), obj);
		t=Interp_ApplyCtx(t, close, msg);
		return(t);
	}

//	sa_error("PlObj_dispatch: no handler for message '");
//	TyFcn_DumpElem(rest);
//	sa_print("'\n");

	return(MISC_UNDEFINED);
}

elem PlObj_ObjectP(elem a)
{
	return(ELEM_FROMBOOL(TypeX_TypeP("plobj-object", a)));
}

elem PlObj_MemberP(elem a, elem b)
{
	elem cur_n, cur_d, t;
	PlObj_Object *obj;

	obj=TypeX_Data(a);
	b=TyFcn_Keywordify(b);

	cur_n=obj->hdl_n;
	cur_d=obj->hdl_d;

	while(ELEM_CONSP(cur_n))
	{
		if(CAR(cur_n)==b)return(MISC_TRUE);
		cur_n=CDR(cur_n);
		cur_d=CDR(cur_d);
	}

	return(MISC_FALSE);
}

elem PlObj_ObjectFlatten(elem obj)
{
	elem t;
	elem c_n, c_d, x;
	PlObj_Object *a;

	a=TypeX_Data(obj);

	x=MISC_EOL;

	c_n=a->hdl_n;
	c_d=a->hdl_d;

	while(c_n!=MISC_EOL)
	{
		t=CAR(c_d);
		if(ELEM_CLOSUREP(t))t=Builtin_ClosureBody(t);
		if(ELEM_SYMBOLP(t))t=CONS(SYM("quote"), CONS(t, MISC_EOL));

		t=CONS(CAR(c_n), CONS(t, MISC_EOL));
		x=CONS(t, x);

		c_n=CDR(c_n);
		c_d=CDR(c_d);
	}

	x=CONS(SYM("quote"), CONS(x, MISC_EOL));
	x=CONS(SYM("plobj-flat"), CONS(x, MISC_EOL));

	return(t);
}

elem PlObj_ObjectUnflatten(elem rest)
{
	elem cur, e;
	elem o;

	o=PlObj_Clone(plobj_null_obj);

	cur=rest;
	while(cur!=MISC_EOL)
	{
		e=CAR(cur);
		PlObj_Bind(o, CAR(e),
			Interp_EvalCurrent(CADR(e), MISC_EOL));
		cur=CDR(cur);
	}

	return(o);
}

elem PlObj_ObjectPrint(elem obj)
{
	elem t;
	elem c_n, c_d, cur, x;
	PlObj_Object *a;

	t=PlObj_InvokeObject(obj, CONS(SYM("print:"), MISC_EOL));
	if(t!=MISC_UNDEFINED)return(t);

	a=TypeX_Data(obj);

	x=MISC_EOL;

	c_n=a->hdl_n;
	c_d=a->hdl_d;

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

	TyPrint_PrintFlags(x, FIXNUM(TYPRINT_CODE));
	return(MISC_NULL);
}

elem PlObj_Init()
{
	elem x;
	PlObj_Object *a;

	MMGC3_AddRoot(&plobj_null_obj);

	a=TypeX_Alloc("plobj-object", sizeof(PlObj_Object));

	a->links=MISC_EOL;
	a->hdl_n=MISC_EOL;
	a->hdl_d=MISC_EOL;

	plobj_null_obj=MMGC3_GetReference(a);

	Interp_DefinePrimative("pl-clone",	&PlObj_Clone,		1);
	Interp_DefinePrimative("pl-bind",	&PlObj_Bind,		3);

	Interp_DefinePrimative("pl-object?",	&PlObj_ObjectP,		1);
	Interp_DefinePrimative("pl-member?",	&PlObj_MemberP,		2);

	Interp_DefinePrimative("pl-apply-self",	&PlObj_Apply,		2);
	Interp_DefinePrimative("plobj-flatten",	&PlObj_ObjectFlatten,	1);
	Interp_DefinePrimative("plobj-flat",	&PlObj_ObjectUnflatten,	1);

	repl_ctx->ep_n=CONS(CONS(SYM("pl-null-obj"),	CAR(repl_ctx->ep_n)), CDR(repl_ctx->ep_n));
	repl_ctx->ep_d=CONS(CONS(plobj_null_obj,	CAR(repl_ctx->ep_d)), CDR(repl_ctx->ep_d));

	return(0);
}
