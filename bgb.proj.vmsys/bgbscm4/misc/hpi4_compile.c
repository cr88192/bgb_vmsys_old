/*
	for macros I will implement a variation of syntax-case.
	for this there will be an actual macro-time environment.

	the encoding of syntax objects has not really been resolved yet. one
	possibility would be to have 2 trees, one for the symbolic encoding
	and the other for the semi-resolved encoding.
	syntax objects may be represented as vectors, with slot 0 being the
	symbolic representation and slot 1 being the semi-resolved
	representation.

	there will be 2 steps in the compile process, the first will be macro
	expansion and the second compilation. the output of the first stage is
	to be an expanded syntax tree using semi-resolved symbols, with the
	second stepping along that tree performing actual compilation.

	thought: first it may be possible to maintain a single step process,
	just by inlining macro expansion and compilation, thus in each step
	it will try to expand macros and then compile the results.

	2002-09-12:
	make the syntax special rename definitions.
	(syntax (let ((x 2) (y 3)) (+ x y))) => (let ((#:0 2) (#:1 3)) (+ #:0 #:1))
	for the time being syntax objects will just be s-exprs.

	2002-09-16:
	car and cdr can be defined in terms of argument currying:
	(define (car (h . t)) h)
	(define (cdr (h . t)) t)
	consider argument currying a possibly useful feature.

	pattern matched multimethods could be useful. consider it discouraged for
	multiple functions to have overlapping definitions.

	(defmacro name args body) => (define-syntax name (lambda ((args)) body))

	consider 'name;' notation for explicit hygenic variables.

	2002-09-17:
	make define-syntax similar to define:
	(define-syntax name value)
	(define-syntax (name . args) body) -> (define-syntax (lambda args body))

 */

#include <scmcc.h>
#include <interpctx.h>

elem form_return, form_apply, form_halt, form_frame_apply_halt;

elem form_return_u, form_apply_u, form_halt_u, form_frame_apply_halt_u;

extern InterpCtx *repl_ctx;

elem hpicomp_topbinds, hpicomp_exports, hpicomp_imports, hpicomp_modname;

elem HpiComp_PushEnv(InterpCtx *ctx)
{
	ctx->sp=CONS(ctx->ep_d, CONS(ctx->ep_n, ctx->sp));
}

elem HpiComp_PopEnv(InterpCtx *ctx)
{
	ctx->ep_d=CAR(ctx->sp);
	ctx->sp=CDR(ctx->sp);
	ctx->ep_n=CAR(ctx->sp);
	ctx->sp=CDR(ctx->sp);
}

elem HpiComp_PushSEnv(InterpCtx *ctx)
{
	ctx->sp=CONS(ctx->sep_d, CONS(ctx->sep_n, ctx->sp));
}

elem HpiComp_PopSEnv(InterpCtx *ctx)
{
	ctx->sep_d=CAR(ctx->sp);
	ctx->sp=CDR(ctx->sp);
	ctx->sep_n=CAR(ctx->sp);
	ctx->sp=CDR(ctx->sp);
}

static elem invoke_func(int func, int pc, int *parms)
{
	elem t;
	union {
	elem f;
	elem (*f0)();
	elem (*f1)(elem a);
	elem (*f2)(elem a, elem b);
	elem (*f3)(elem a, elem b, elem c);
	elem (*f4)(elem a, elem b, elem c, elem d);
	elem (*f5)(elem a, elem b, elem c, elem d, elem e);
	elem (*f6)(elem a, elem b, elem c, elem d, elem e, elem f);
	elem (*f7)(elem a, elem b, elem c, elem d, elem e, elem f, elem g);
	elem (*f8)(elem a, elem b, elem c, elem d, elem e, elem f, elem g, elem h);
	}fp;

	fp.f=func;
	switch(pc)
	{
	case 0:
		t=fp.f0();
		break;
	case 1:
		t=fp.f1(parms[0]);
		break;
	case 2:
		t=fp.f2(parms[0], parms[1]);
		break;
	case 3:
		t=fp.f3(parms[0], parms[1], parms[2]);
		break;
	case 4:
		t=fp.f4(parms[0], parms[1], parms[2], parms[3]);
		break;
	case 5:
		t=fp.f5(parms[0], parms[1], parms[2], parms[3], parms[4]);
		break;
	case 6:
		t=fp.f6(parms[0], parms[1], parms[2], parms[3], parms[4], parms[5]);
		break;
	case 7:
		t=fp.f7(parms[0], parms[1], parms[2], parms[3], parms[4], parms[5], parms[6]);
		break;
	case 8:
		t=fp.f8(parms[0], parms[1], parms[2], parms[3], parms[4], parms[5], parms[6], parms[7]);
		break;
	}
	return(t);
}

elem TyMisc_EvalSpecial(elem func, elem parms)
{
	elem cur, t;
	elem parm[16], xa;
	int pc, pl, pa;

	cur=parms;

	t=func;
	pl=(OBJECT_HEAD(t)>>9)&127;

	pa=pl&31;
	pc=0;
	while(cur!=MISC_EOL && (pc<pa))
	{
		parm[pc++]=TyFcn_Car(cur);
		cur=TyFcn_Cdr(cur);
	}

	if(pc<pa)
	{
		sa_print("(apply builtin) missing args: %d <= ", pa);
		TyFcn_DumpElem(parms);
		sa_print("\n");
		return(MISC_UNDEFINED);
	}

	if(pl&64)
	{
		xa=MISC_EOL;
		while(cur!=MISC_EOL)
		{
			xa=CONS(TyFcn_Car(cur), xa);
			cur=TyFcn_Cdr(cur);
		}
		xa=TyFcn_NReverse(xa);
		parm[pc++]=xa;
	}
//	SCMCC_ASSERT(cur==MISC_EOL, "(apply builtin) extra args.\n");

	if(cur!=MISC_EOL)
	{
		sa_print("(apply builtin) extra args: %d <= ", pa);
		TyFcn_DumpElem(parms);
		sa_print("\n");
		return(MISC_UNDEFINED);
	}

	t=OBJ_PEEK(func, 1); // hack: t is not a cons...
	t=invoke_func(t, pc, parm);
	return(t);
}

elem TyMisc_EvalSpecialI(elem func, elem *parms)
{
	elem cur, t;
	elem parm[16], xa;
	int pc, pl, pa;

	cur=parms;

	t=func;
	pl=(OBJECT_HEAD(t)>>9)&127;

	pa=pl&31;
	pc=0;
	while(cur!=MISC_EOL && (pc<pa))
	{
		parm[pc++]=TyFcn_Car(cur);
		cur=TyFcn_Cdr(cur);
	}

	if(pc<pa)
	{
		sa_print("(apply builtin) missing args: %d <= ", pa);
		TyFcn_DumpElem(parms);
		sa_print("\n");
		return(MISC_UNDEFINED);
	}

	*parms=cur;

	t=OBJ_PEEK(func, 1); // hack: t is not a cons...
	t=invoke_func(t, pc, parm);

	if(t!=MISC_UNDEFINED)
		*parms=CONS(t, *parms);

	return(MISC_NULL);
}

elem HpiComp_DefineSpecial(char *name, elem (*func)(), int pc)
{
//	hpicomp_specials=CONS(
//		TyFcn_SymbolDef(TyFcn_Symbol(name), TyFcn_Special(func, pc), MISC_EOL),
//		hpicomp_specials);

//	hpicomp_specials_ntree=CONS(TyFcn_Symbol(name), hpicomp_specials_ntree);
//	hpicomp_specials_dtree=CONS(TyFcn_Special(func, pc), hpicomp_specials_dtree);

//	toplevel_n=CONS(TyFcn_Symbol(name), toplevel_n);
//	toplevel_d=CONS(TyFcn_Special(func, pc), toplevel_d);

//	toplevel_n=CONS(CONS(TyFcn_Symbol(name), CAR(toplevel_n)), MISC_EOL);
//	toplevel_d=CONS(CONS(TyFcn_Special(func, pc), CAR(toplevel_d)), MISC_EOL);

	repl_ctx->sep_n=CONS(CONS(TyFcn_Symbol(name), CAR(repl_ctx->sep_n)), CDR(repl_ctx->sep_n));
	repl_ctx->sep_d=CONS(CONS(TyFcn_Special(func, pc), CAR(repl_ctx->sep_d)), CDR(repl_ctx->sep_d));

	SAGC_BindNameAddr(name, func);

	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, InterpCtx *ctx, int tail);
elem HpiInterp_Run(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d);

elem HpiComp_GatherBinds(elem form, InterpCtx *ctx)
{
	t=Namespace3_Lookup(ctx->sep_n, ctx->sep_d, CAR(form));
}

elem HpiComp_CompileExpr(elem form, elem next, InterpCtx *ctx, int tail)
{
	elem cur, x, t, f;
	elem ep_n, ep_d;

	if(ELEM_SYNSYNP(CAR(form)))
	{
		t=TyFcn_VectorRef(CAR(form), ELEM_FROMFIXNUM(1));
		if(ELEM_SYNTAXP(t))
		{
			t=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS((elem)ctx,CONS(tail, MISC_EOL)))));
			return(t);
		}
		if(ELEM_CLOSUREP(t))
		{

			f=ctx->ip;
			x=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(2));
			ctx->ip=CONS(CONS(SYM("frame"), CONS(x, MISC_EOL)),
				TyFcn_ListCopyRec(form_halt_u));
			HpiOp_Frame(ctx);

			ctx->ep_n=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0));

			ep_d=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1));
			ctx->ep_d=CONS(CONS(form, MISC_EOL), ep_d);

			t=HpiInterp_RunCtx(ctx->ip, ctx);

//			TyFcn_DumpElem(t);
//			sa_print("\n");

			x=HpiComp_Compile(t, next, ctx, tail);

			ctx->ip=f;

			return(x);
		}
	}

	t=Namespace3_Lookup(ctx->sep_n, ctx->sep_d, CAR(form));
	if(ELEM_SYNTAXP(t))
	{
		t=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS((elem)ctx,CONS(tail, MISC_EOL)))));
		return(t);
	}
	if(ELEM_MACROP(t))
	{

		ep_n=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0));

		ep_d=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1));
		ep_d=CONS(CDR(form), ep_d);

		f=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(2));

		t=HpiInterp_Run(f, ep_n, ep_d, CONS(MISC_EOL, MISC_EOL), CONS(MISC_EOL, MISC_EOL));
		x=HpiComp_Compile(t, next, ctx, tail);

		return(x);
	}
	if(ELEM_CLOSUREP(t))
	{
//		HpiComp_PushEnv(ctx); //? preserve env on entry
//		HpiComp_PushSEnv(ctx);

		f=ctx->ip;
		x=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(2));
		ctx->ip=CONS(CONS(SYM("frame"), CONS(x, MISC_EOL)),
			TyFcn_ListCopyRec(form_halt_u));
		HpiOp_Frame(ctx);

		ctx->ep_n=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0));

		ep_d=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(CONS(form, MISC_EOL), ep_d);

		t=HpiInterp_RunCtx(ctx->ip, ctx);
//		t=HpiInterp_Run(f, ep_n, ep_d, CONS(MISC_EOL, MISC_EOL), CONS(MISC_EOL, MISC_EOL));

//		TyFcn_DumpElem(t);
//		sa_print("\n");

//		HpiComp_PopSEnv(ctx); //? these should have no effect
//		HpiComp_PopEnv(ctx);

		x=HpiComp_Compile(t, next, ctx, tail);


//		TyFcn_DumpElem(ctx->sep_n);
//		sa_print("\n");

		ctx->ip=f;

		return(x);
	}

//	x=TyFcn_ListCopyRec(form_apply_u);
	x=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);

	x=HpiComp_Compile(CAR(form), x, ctx, 0);
	if(ELEM_UNDEFP(x))return(MISC_UNDEFINED);

	cur=TyFcn_Cdr(form);
	while(ELEM_CONSP(cur))
	{
		if(ELEM_CONSP(CAR(cur)))
			if(CAAR(cur)==SYM("unquote-splicing"))
		{
			t=CONS(SYM("splice"), MISC_EOL);
			x=CONS(t, x);
			x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
			cur=CDR(cur);
			continue;
		}

		t=CONS(SYM("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(CAR(cur), x, ctx, 0);
		cur=CDR(cur);
	}
	if(cur!=MISC_EOL)
	{
		sa_print("HpiComp_CompileExpr: bad form ");
		TyFcn_DumpElem(form);
		sa_print("\n");
	}

	if(!tail)x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiComp_Lookup(elem sym, elem binds)
{
	elem cur, t;
	int c;

	c=0;
	if(ELEM_CONSP(binds))
	{
//		t=Namespace_SymbolInList(sym, CAR(cur));
//		if(t!=MISC_NULL)return(ELEM_FROMFRAME(c, ELEM_TOFIXNUM(t)));
//		c++;
//		cur=CDR(cur);

		t=Namespace3_Trace(binds, binds, MISC_EOL, sym);
		if(t!=MISC_UNDEFINED)return(t);
	}

//	t=Namespace_SymbolInList(sym, hpicomp_topbinds);
//	if(t!=MISC_NULL)return(sym);

//	t=Namespace_SymbolInList(sym, hpicomp_imports);
//	if(t!=MISC_NULL)return(sym);

	return(sym);	// in this case sym refers to an implicit dynamic var.
//	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, InterpCtx *ctx, int tail)
{
	elem t, x;

	if(ELEM_SYMBOLP(form))
	{
		if(ELEM_SYMKEYWORDP(form))
		{
			x=CONS(TyFcn_Symbol("constant"), CONS(form, MISC_EOL));
			x=CONS(x, next);
			return(x);
		}
		t=Namespace3_Lookup(ctx->sep_n, ctx->sep_d, form);
		if(t!=MISC_UNDEFINED)
		{
//			x=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS((elem)ctx,CONS(tail, MISC_EOL)))));
//			x=HpiComp_Compile(t, next, ctx, tail);
			x=HpiComp_Compile(CONS(form, MISC_EOL), next, ctx, tail);
			return(x);
		}

//		t=HpiComp_Lookup(form, ctx->ep_n);
		t=Namespace3_Trace(ctx->ep_n, ctx->ep_d, MISC_EOL, form);
		if(t==MISC_UNDEFINED)t=form;

#if 0
		if(t==MISC_NULL)
		{
			sa_error("unbound var %s\n", ELEM_TOSYMBOL(form));
			return(MISC_UNDEFINED);
		}
#endif

		x=CONS(SYM("refer"), CONS(t, CONS(form, MISC_EOL)));
		x=CONS(x, next);
		return(x);
#if 0
		t=Namespace_SymbolInList(form, largs);
		if(t!=MISC_NULL)
		{
			x=CONS(TyFcn_Symbol("refer-local"), CONS(t, MISC_EOL));
			x=CONS(x, next);
			return(x);
		}
		t=Namespace_LookupVarList(form, disp);
		if(t!=MISC_UNDEFINED)
		{
			x=CONS(TyFcn_Symbol("refer-free"), CONS(t, MISC_EOL));
			x=CONS(x, next);
			return(x);
		}

		sa_error("StiComp_Compile: %s not in largs or disp.\n", ELEM_TOSTRING(form));
		x=MISC_NULL;
		t=Namespace_LookupEnvBinding(env, form);
		if(t==MISC_UNDEFINED)break;
		t=Namespace_InsertSymbolList(form, disp);
#endif
	}else if(ELEM_CONSP(form))
	{
		x=HpiComp_CompileExpr(form, next, ctx, tail);
	}else if(ELEM_SYNREFP(form))
	{
		x=CONS(TyFcn_Symbol("constant"), CONS(TyFcn_VectorRef(form, ELEM_FROMFIXNUM(1)), MISC_EOL));
		x=CONS(x, next);
	}else
	{
		x=CONS(TyFcn_Symbol("constant"), CONS(form, MISC_EOL));
		x=CONS(x, next);
	}
	return(x);
}


elem HpiSpecial_And(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"),CONS(x,CONS(bc, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, ctx, 0);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_AssignN(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t;

	t=HpiComp_Lookup(CADR(form), ctx->ep_n);
	x=CONS(SYM("assign2"),CONS(t, CONS(CADR(form), MISC_EOL)));
	x=CONS(x, next);
	x=HpiComp_Compile(CADDR(form), x, ctx, 0);
	return(x);
}

elem HpiSpecial_Begin(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, lst;
	lst=TyFcn_Reverse(CDR(form));
	cur=lst;
	x=next;

//	TyFcn_DumpElem(lst);
//	kprint("\n");

	while(cur!=MISC_EOL)
	{
		x=HpiComp_Compile(CAR(cur), x, ctx, tail);
		if(tail)tail=0;
		cur=CDR(cur);
	}
	return(x);
}

elem HpiSpecial_BeginFrame(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, lst;
	lst=TyFcn_Reverse(CDR(form));
	cur=lst;
	x=TyFcn_ListCopyRec(form_return_u);

	tail=1;
	while(cur!=MISC_EOL)
	{
		x=HpiComp_Compile(CAR(cur), x, ctx, tail);
		if(tail)tail=0;
		cur=CDR(cur);
	}
	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_BoundP(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x;

	x=Namespace3_Trace(ctx->ep_n, ctx->ep_d, MISC_EOL, CADR(form));
	if(x==MISC_UNDEFINED)
	{
		x=CONS(TyFcn_Symbol("constant"),CONS(MISC_FALSE, MISC_EOL));
		x=CONS(x, next);
	}else
	{
		x=CONS(TyFcn_Symbol("constant"),CONS(MISC_TRUE, MISC_EOL));
		x=CONS(x, next);
	}

	return(x);
}

elem HpiSpecial_CallCC(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t;
	x=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	x=HpiComp_Compile(CADR(form), x, ctx, 0);

	t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
	x=CONS(t, x);

	t=CONS(TyFcn_Symbol("conti"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);
	return(x);
}

elem HpiSpecial_Case(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, ctx, 0);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"),CONS(ec,CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, ctx, 0);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Cond(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, ctx, 0);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"), CONS(ec,CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, ctx, 0);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Constraint(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, lbinds_n, lbinds_d;

	lbinds_n=CONS(CADR(form), ctx->ep_n);
	lbinds_d=CONS(CADR(form), ctx->ep_d);

	x=CONS(CONS(SYM("halt"), MISC_EOL), MISC_EOL);

	x=HpiComp_Compile(CADR(form), x, ctx, 0);
//	x=HpiSpecial_Begin(CDR(form), x, ctx, 1);

	x=CONS(TyFcn_Symbol("constraint"), CONS(x, CONS(form, MISC_EOL)));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_CurrentEnv(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x;
	x=CONS(CONS(SYM("current-env"), MISC_EOL), next);
	return(x);
}

elem HpiSpecial_CurrentEnvObj(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x;
	x=CONS(CONS(SYM("current-envobj"), MISC_EOL), next);
	return(x);
}

elem HpiSpecial_Define(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var, vars;
	elem lbinds_n, lbinds_d;
	int bind;

	var=CADR(form);
	if(ELEM_CONSP(var))
	{
		vars=CDR(var);
		var=CAR(var);
	}else vars=MISC_NULL;

//	if(ELEM_ENVP(binds))
	if(ctx->ep_n==MISC_EOL)
	{
//		t=Namespace_CreateEnvBinding(binds, var, MISC_UNDEFINED);
//		x=CONS(CONS(SYM("assign"),CONS(t, MISC_EOL)), next);
		hpicomp_topbinds=CONS(var, hpicomp_topbinds);
		x=CONS(CONS(SYM("assign"),CONS(var, MISC_EOL)), next);
	}else if(ELEM_CONSP(ctx->ep_n))
	{
//		TyFcn_SetCar(ctx->ep_n,CONS(var, CAR(ctx->ep_n)));
//		TyFcn_SetCar(binds_d,CONS(MISC_NULL, CAR(binds_d)));
//		ctx->ep_n=CONS(var, ctx->ep_n);
//		binds_d=CONS(MISC_NULL, binds_d);

		bind=0;
		lbinds_n=ctx->ep_n;
		lbinds_d=ctx->ep_d;
		t=Namespace3_Lookup(lbinds_n, lbinds_d, var);
		if(t==MISC_UNDEFINED)
		{
			bind=1;
			lbinds_n=CONS(CONS(var, CAR(ctx->ep_n)), CDR(ctx->ep_n));
			lbinds_d=CONS(CONS(MISC_NULL, CAR(ctx->ep_d)), CDR(ctx->ep_d));
		}
		t=HpiComp_Lookup(var, lbinds_n);
		x=CONS(CONS(SYM("assign"), CONS(t, CONS(var, MISC_EOL))), next);
	}
	if(!ELEM_NULLP(vars))
	{
//		t=CONS(SYM("lambda"),CONS(vars,CONS(CADDR(form), MISC_EOL)));
		t=CONS(SYM("lambda"),CONS(vars,CDDR(form)));
		HpiComp_PushEnv(ctx);
		ctx->ep_n=lbinds_n;
		ctx->ep_d=lbinds_d;
		x=HpiComp_Compile(t, x, ctx, 0);
		HpiComp_PopEnv(ctx);
	}else
	{
		HpiComp_PushEnv(ctx);
		ctx->ep_n=lbinds_n;
		ctx->ep_d=lbinds_d;
		x=HpiComp_Compile(CADDR(form), x, ctx, 0);
		HpiComp_PopEnv(ctx);
	}
	if((ctx->ep_n!=MISC_EOL) && bind)
		x=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), x);

	return(x);
}

elem HpiSpecial_DefineSyntax(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var, vars;
	elem lbinds_n, lbinds_d;

	var=CADR(form);

	t=ctx->ip;
	x=HpiComp_Compile(CADDR(form), TyFcn_ListCopyRec(form_halt_u), ctx, 0);
	x=HpiInterp_RunCtx(x, ctx);
	ctx->ip=t;

	ctx->sep_n=CONS(CONS(var, CAR(ctx->sep_n)), CDR(ctx->sep_n));
	ctx->sep_d=CONS(CONS(x, CAR(ctx->sep_d)), CDR(ctx->sep_d));

	return(next);
}

elem HpiSpecial_DefMulti(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var;

	var=CADR(form);

	x=CONS(CONS(SYM("bind-args"), CONS(var, MISC_EOL)), next);
	x=HpiComp_Compile(CADDR(form), x, ctx, 0);

	return(x);
}

elem HpiSpecial_DefMultiVar(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var;

	var=CADR(form);

	x=CONS(CONS(SYM("bind-args-var"), CONS(var, MISC_EOL)), next);
	x=HpiComp_Compile(CADDR(form), x, ctx, 0);

	return(x);
}

elem HpiSpecial_Defvar(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var, vars;

	var=CADR(form);
	if(ELEM_CONSP(var))
	{
		vars=CDR(var);
		var=CAR(var);
	}else vars=MISC_NULL;

	x=CONS(CONS(SYM("assign"), CONS(var, CONS(var, MISC_EOL))), next);

	if(!ELEM_NULLP(vars))
	{
		t=CONS(SYM("lambda"),CONS(vars,CONS(CADDR(form), MISC_EOL)));
		x=HpiComp_Compile(t, x, ctx, 0);
	}else x=HpiComp_Compile(CADDR(form), x, ctx, 0);

	x=CONS(CONS(SYM("bind-var"), CONS(var, MISC_EOL)), x);

	return(x);
}

elem HpiSpecial_Defmacro(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var, args;
	elem lbinds_n, lbinds_d, lb2_d;

	var=CADR(form);
	args=CADDR(form);

//	if(ELEM_ENVP(binds))
	if(ctx->ep_n==MISC_EOL)
	{
//		t=Namespace_CreateEnvBinding(binds, var, MISC_UNDEFINED);
//		x=CONS(CONS(SYM("assign"),CONS(t, MISC_EOL)), next);
		hpicomp_topbinds=CONS(var, hpicomp_topbinds);
		x=CONS(CONS(SYM("assign"),CONS(var, MISC_EOL)), next);
	}else if(ELEM_CONSP(ctx->ep_n))
	{
//		lbinds_n=CONS(CONS(var, CAR(binds_n)), CDR(binds_n));
//		lbinds_d=CONS(CONS(MISC_NULL, CAR(binds_d)), CDR(binds_d));
//		t=HpiComp_Lookup(var, lbinds_n);
//		x=CONS(CONS(SYM("assign"), CONS(t, MISC_EOL)), next);

		lbinds_n=CONS(CONS(var, CAR(ctx->ep_n)), CDR(ctx->ep_n));
		lbinds_d=CONS(CONS(MISC_NULL, CAR(ctx->ep_d)), CDR(ctx->ep_d));

		HpiComp_PushEnv(ctx);
		ctx->ep_n=CONS(args, lbinds_n);
		ctx->ep_d=CONS(args, lbinds_d);
		x=HpiComp_Compile(CADDDR(form), TyFcn_ListCopyRec(form_halt_u), ctx, 0);
		HpiComp_PopEnv(ctx);

//		t=HpiComp_Compile(CADDDR(form), form_halt_u, CONS(args, lbinds_n), CONS(args, lbinds_d), 0);

		x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_MACRO));

		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), CONS(args, lbinds_n));
		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), lbinds_d);

		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

//		TyFcn_SetCar(ctx->ep_n, CONS(var, CAR(ctx->ep_n)));
//		TyFcn_SetCar(ctx->ep_d, CONS(x, CAR(ctx->ep_d)));
	}

//	if(ctx->ep_n!=MISC_EOL)x=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), x);

	t=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), next); //HACK: macros defined at runtime
	t=CONS(CONS(SYM("constant"), CONS(x, MISC_EOL)), t);

	return(t);
}

#if 0
elem HpiSpecial_Function(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, var, vars;

	var=CADR(form);
	vars=CADDR(var);

	if(binds==MISC_EOL)
	{
		hpicomp_topbinds=CONS(var, hpicomp_topbinds);
		x=CONS(CONS(SYM("assign"),CONS(var, MISC_EOL)), next);
	}else if(ELEM_CONSP(binds))
	{
		TyFcn_SetCar(ctx->ep_n, CONS(var, CAR(ctx->ep_n)));
		TyFcn_SetCar(ctx->ep_d, CONS(ELEM_DUMMY(TYPE_FUNCTION), CAR(ctx->ep_d)));
		x=CONS(CONS(SYM("bind"), MISC_EOL), next);
	}

	t=CONS(SYM("lambda"),CONS(vars,CONS(CADDDR(form), MISC_EOL)));
	x=HpiComp_Compile(t, x, ctx, 1);

	return(x);
}
#endif

elem HpiSpecial_If(elem form, elem next, InterpCtx *ctx, int tail)
{
	elem x, tc, fc;

	// conditions are non-tail as if does not produce a frame
	tc=HpiComp_Compile(CADDR(form), next, ctx, tail);
	x=CDDDR(form);
	if(x!=MISC_EOL)fc=HpiComp_Compile(CADDDR(form), next, ctx, tail);
		else fc=next;

	x=CONS(TyFcn_Symbol("test"),CONS(tc,CONS(fc, MISC_EOL)));
	x=CONS(x, MISC_EOL);

	x=HpiComp_Compile(CADR(form), x, ctx, 0);

	return(x);
}

elem HpiSpecial_Lambda(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, lbinds_n, lbinds_d;

	lbinds_n=CONS(CADR(form), ctx->ep_n);
	lbinds_d=CONS(CADR(form), ctx->ep_d);

	x=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
//	x=HpiComp_Compile(CADDR(form), form_return_u, ctx, 1);
	x=HpiSpecial_Begin(CDR(form), x, ctx, 1);
	HpiComp_PopEnv(ctx);

//	x=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);
	x=CONS(TyFcn_Symbol("close"), CONS(CADR(form), CONS(x, CONS(form, MISC_EOL))));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_NamedLet(elem form, elem next, InterpCtx *ctx, elem tail);

elem HpiSpecial_Let(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;

	if(ELEM_SYMBOLP(CADR(form)))return(HpiSpecial_NamedLet(form, next, ctx, tail));

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	r=TyFcn_NReverse(r);
	lbinds_n=CONS(r, ctx->ep_n);
	lbinds_d=CONS(r, ctx->ep_d);

//	x=CONS(TyFcn_Symbol("return"), MISC_EOL);
//	x=CONS(x, MISC_EOL);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
//	t=HpiComp_Compile(CADDR(form), x, ctx, 1);
	t=HpiSpecial_Begin(CDR(form), TyFcn_ListCopyRec(form_return_u), ctx, 1);
	HpiComp_PopEnv(ctx);

//	t=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	x=CONS(TyFcn_Symbol("bind-args"),CONS(r, MISC_EOL));
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
		cur=CDR(cur);
	}

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

#if 0
elem HpiSpecial_LetM(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;
	elem flst, bf;

	lbinds_n=CONS(MISC_EOL, ctx->ep_n);
	lbinds_d=CONS(MISC_EOL, ctx->ep_d);

	flst=TyFcn_Reverse(CADR(form));

	bf=MISC_EOL;
	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(CONS(SYM("bind"),CONS(CAR(CAR(cur)), MISC_EOL)), MISC_EOL);

		HpiComp_PushEnv(ctx);
		ctx->ep_n=lbinds_n;
		ctx->ep_d=lbinds_d;
		t=HpiComp_Compile(CADR(CAR(cur)), t, ctx, 0);
		HpiComp_PopEnv(ctx);

//		t=HpiComp_Compile(CADR(CAR(cur)), t, lbinds_n, lbinds_d, 0);
		bf=TyFcn_NAppend(bf, t);

		t=CAR(CAR(cur));
		r=CONS(t, r);
		TyFcn_SetCar(lbinds, r);
		cur=CDR(cur);
	}

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
	x=HpiComp_Compile(CADDR(form), x, ctx, 1);
	HpiComp_PopEnv(ctx);

//	x=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	x=TyFcn_NAppend(bf, x);

	t=CONS(SYM("bind-args"),CONS(MISC_EOL, MISC_EOL));
	x=CONS(t, x);

	x=CONS(CONS(SYM("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}
#endif

elem HpiSpecial_Letrec(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	lbinds_n=CONS(r, ctx->ep_n);
	lbinds_d=CONS(r, ctx->ep_d);

//	x=CONS(SYM("return"), MISC_EOL);
//	x=CONS(x, MISC_EOL);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
//	t=HpiComp_Compile(CADDR(form), x, ctx, 1);
	x=HpiSpecial_Begin(CDR(form), TyFcn_ListCopyRec(form_return_u), ctx, 1);
	HpiComp_PopEnv(ctx);

//	t=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=HpiComp_Lookup(CAR(CAR(cur)), lbinds_n);
		t=CONS(SYM("assign"),CONS(t, CONS(CAR(CAR(cur)), MISC_EOL)));
		x=CONS(t, x);

		HpiComp_PushEnv(ctx);
		ctx->ep_n=lbinds_n;
		ctx->ep_d=lbinds_d;
		x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
		HpiComp_PopEnv(ctx);

//		x=HpiComp_Compile(CADR(CAR(cur)), x, lbinds_n, lbinds_d, 0);
		cur=CDR(cur);
	}

	t=CONS(SYM("bind-args"),CONS(r, MISC_EOL));
	x=CONS(t, x);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(SYM("argument"), MISC_EOL);
		x=CONS(t, x);
		cur=CDR(cur);
	}

	t=CONS(TyFcn_Symbol("constant"),CONS(MISC_NULL, MISC_EOL));
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_LetVar(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;

	if(ELEM_SYMBOLP(CADR(form)))return(HpiSpecial_NamedLet(form, next, ctx, tail));

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	lbinds_n=CONS(r, ctx->ep_n);
	lbinds_d=CONS(r, ctx->ep_d);

	x=CONS(TyFcn_Symbol("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
	t=HpiComp_Compile(CADDR(form), x, ctx, 1);
	HpiComp_PopEnv(ctx);

//	t=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	x=CONS(TyFcn_Symbol("bind-args-var"),CONS(r, MISC_EOL));
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
		cur=CDR(cur);
	}

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_LocativeM(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t;
	t=HpiComp_Lookup(CADR(form), ctx->ep_n);
	x=CONS(TyFcn_Symbol("locative"),CONS(t, MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem Mini_Inner(elem a, elem b, InterpCtx *ctx)
{
	elem cur;

	if(a==MISC_EOL)return(b);
	if(!ELEM_CONSP(a))return(a);

	if(ELEM_CONSP(CAR(a)))if(CAR(CAR(a))==SYM("doublemark"))
		return(HpiComp_Compile(CADR(CAR(a)), Mini_Inner(CDR(a), b, ctx), ctx, 0));

	return(CONS(Mini_Inner(CAR(a), MISC_EOL, ctx), Mini_Inner(CDR(a), b, ctx)));
}

elem HpiSpecial_Mini(elem form, elem next, InterpCtx *ctx, elem tail)
{
//	elem x, t, cur, last;
//	elem cur2, last2;

	return(Mini_Inner(CDR(form), next, ctx));

#if 0
	x=TyFcn_ListCopy(CDR(form));
	cur=x;
	last=MISC_EOL;
	while(ELEM_CONSP(cur))
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAR(CAR(cur))==SYM("doublemark"))
			{
				t=HpiComp_Compile(CADR(CAR(cur)), CDR(cur), ctx, 0);
				if(last==MISC_EOL)
				{
					x=t;
					last=t;
					cur=CDR(t);
					continue;
				}else
				{
					TyFcn_SetCdr(last, t);
					last=t;
					cur=CDR(t);
					continue;
				}
			}
			cur2=CAR(cur);
			last2=MISC_EOL;
			while(ELEM_CONSP(cur2))
			{
				if(ELEM_CONSP(CAR(cur2)))
					if(CAR(CAR(cur2))==SYM("doublemark"))
				{
					t=HpiComp_Compile(CADR(CAR(cur2)), CDR(cur), ctx, 0);
					if(last2==MISC_EOL)
					{
						TyFcn_SetCar(cur, t);
						last2=t;
						cur2=CDR(t);
						continue;
					}else
					{
						TyFcn_SetCdr(last2, t);
						last2=t;
						cur2=CDR(t);
						continue;
					}
				}
				last2=cur2;
				cur2=CDR(cur2);
			}
		}
		last=cur;
		cur=CDR(cur);
	}

	x=TyFcn_NAppend(x, next);

	return(x);
#endif
}

elem HpiSpecial_NamedLet(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d, ldef;

	r=MISC_EOL;
	cur=CADDR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	r=TyFcn_NReverse(r);

	lbinds_n=CONS(CONS(CADR(form), MISC_EOL), ctx->ep_n);
	lbinds_d=CONS(CONS(CADR(form), MISC_EOL), ctx->ep_d);

	x=CONS(TyFcn_Symbol("apply"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Lookup(CADR(form), lbinds_n);
	t=CONS(SYM("assign"),CONS(t, CONS(CADR(form), MISC_EOL)));
	x=CONS(t, x);

	ldef=CONS(SYM("lambda"),CONS(r, CDDDR(form)));
//	t=HpiComp_Compile(CADDR(form), x, lbinds);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=lbinds_n;
	ctx->ep_d=lbinds_d;
	x=HpiComp_Compile(ldef, x, ctx, 0);
	HpiComp_PopEnv(ctx);

//	x=HpiComp_Compile(ldef, x, lbinds_n, lbinds_d, 0);

	cur=CADDR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);

		HpiComp_PushEnv(ctx);
		ctx->ep_n=lbinds_n;
		ctx->ep_d=lbinds_d;
		x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
		HpiComp_PopEnv(ctx);

		cur=CDR(cur);
	}

	t=CONS(TyFcn_Symbol("bind-args"),CONS(CONS(CADR(form), MISC_EOL), MISC_EOL));
	x=CONS(t, x);

	t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Or(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"),CONS(bc,CONS(x, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, ctx, 0);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

#if 0
elem HpiSpecial_Quasiquote(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, lst, cur;

	lst=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAR(CAR(cur))==SYM("unquote"))
				lst=CONS(CONS(SYM("#uqf"),
					HpiComp_Compile(CADR(CAR(cur)),
					TyFcn_ListCopyRec(form_halt_u),
					ctx, 0)), lst);
				else if(ELEM_CONSP(CAR(cur)))if(CAR(CAR(cur))==SYM("unquote-splicing"))
				lst=CONS(CONS(SYM("#uqs"),
					HpiComp_Compile(CADR(CAR(cur)),
					TyFcn_ListCopyRec(form_halt_u), ctx, 0)), lst);
				else lst=CONS(CAR(cur), lst);
		}else lst=CONS(CAR(cur), lst);
		cur=CDR(cur);
	}
	lst=TyFcn_NReverse(lst);

	x=CONS(SYM("qq"),CONS(lst, MISC_EOL));
	x=CONS(x, next);
	return(x);
}
#endif

elem HpiSpecial_QQ_Inner(elem cur, elem x, InterpCtx *ctx)
{
	elem t;

	while(ELEM_CONSP(cur))
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAR(CAR(cur))==SYM("unquote"))
			{
				x=CONS(CONS(SYM("argument"), MISC_EOL), x);
				x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
			}else if(CAR(CAR(cur))==SYM("unquote-splicing"))
			{
				x=CONS(CONS(SYM("splice"), MISC_EOL), x);
				x=HpiComp_Compile(CADR(CAR(cur)), x, ctx, 0);
			}else
			{
				x=CONS(CONS(SYM("argument"), MISC_EOL), x);

				t=CONS(CONS(SYM("xchg-rp-ax"), MISC_EOL), TyFcn_ListCopyRec(form_return_u));
				t=CONS(CONS(SYM("constant"), CONS(MISC_EOL, MISC_EOL)), t);

				t=HpiSpecial_QQ_Inner(CAR(cur), t, ctx);
				x=CONS(CONS(SYM("frame"), CONS(t, MISC_EOL)), x);
			}
		}else
		{
			x=CONS(CONS(SYM("argument"), MISC_EOL), x);
			x=CONS(CONS(SYM("constant"), CONS(CAR(cur), MISC_EOL)), x);
		}

		cur=CDR(cur);
	}

	return(x);
}

elem HpiSpecial_Quasiquote(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, lst, cur;
	x=CONS(CONS(SYM("xchg-rp-ax"), MISC_EOL), next);
	x=CONS(CONS(SYM("constant"), CONS(MISC_EOL, MISC_EOL)), x);
	cur=CADR(form);
	x=HpiSpecial_QQ_Inner(cur, x, ctx);

	return(x);
}

elem HpiSpecial_DoubleQQ(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, lst, cur;
	
	x=CONS(CONS(SYM("apply"), MISC_EOL), x);
	x=HpiComp_Compile(SYM("clean-syntax"), x, ctx, 0);
	x=CONS(CONS(SYM("argument"), MISC_EOL), x);
	x=CONS(CONS(SYM("xchg-rp-ax"), MISC_EOL), x);
	x=CONS(CONS(SYM("constant"), CONS(MISC_EOL, MISC_EOL)), x);
	cur=CADR(form);
	x=HpiSpecial_QQ_Inner(cur, x, ctx);

	if(!tail)x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Quote(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x;
	x=CONS(TyFcn_Symbol("constant"),CONS(CADR(form), MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_SetN(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t;

	if(ELEM_CONSP(CADR(form)))
	{
		x=CONS(CONS(SYM("set-rax"), MISC_EOL), next);
		x=HpiComp_Compile(CADR(form), x, ctx, 0);
		x=CONS(CONS(SYM("argument"), MISC_EOL), x);
		x=HpiComp_Compile(CADDR(form), x, ctx, 0);
		return(x);
	}

	t=HpiComp_Lookup(CADR(form), ctx->ep_n);
	x=CONS(SYM("assign"),CONS(t, CONS(CADR(form), MISC_EOL)));
	x=CONS(x, next);
	x=HpiComp_Compile(CADDR(form), x, ctx, 0);
	return(x);
}

elem HpiSpecial_SyntaxCase_Inner(elem kt, elem lit, elem expr, InterpCtx *ctx)
{
	elem x, y, t, tc, fc;

	if(expr==MISC_EOL)
	{
		x=CONS(SYM("constant"), CONS(MISC_UNDEFINED, MISC_EOL));
		x=CONS(x, TyFcn_ListCopyRec(form_return_u));
		return(x);
	}

	fc=HpiSpecial_SyntaxCase_Inner(kt, lit, CDR(expr), ctx);

	HpiComp_PushEnv(ctx);
	ctx->ep_n=CONS(CAR(CAR(expr)), ctx->ep_n);
	ctx->ep_d=CONS(CAR(CAR(expr)), ctx->ep_d);

//	x=HpiComp_Compile(CADR(CAR(expr)), TyFcn_ListCopyRec(form_return_u), ctx, 1);
	t=CONS(SYM("begin"), CDR(CAR(expr)));
	x=HpiComp_Compile(t, TyFcn_ListCopyRec(form_return_u), ctx, 1);

	t=CONS(SYM("bind-args"), CONS(CAR(CAR(expr)), MISC_EOL));
	x=CONS(t, x);
	t=CONS(SYM("splice"), MISC_EOL);
	x=CONS(t, x);
	t=CONS(SYM("refer"), CONS(kt, MISC_EOL));
	x=CONS(t, x);

	tc=x;

	HpiComp_PopEnv(ctx);

	t=CONS(SYM("test"), CONS(tc, CONS(fc, MISC_EOL)));
	y=CONS(t, MISC_EOL);

	t=CONS(SYM("apply"), MISC_EOL);
	x=CONS(t, x);
	t=CONS(SYM("refer"), CONS(HpiComp_Lookup(SYM("match?"), ctx->ep_n), MISC_EOL));
	x=CONS(t, x);
	t=CONS(SYM("argument"), MISC_EOL);
	x=CONS(t, x);
	t=CONS(SYM("constant"), CONS(lit, MISC_EOL));
	x=CONS(t, x);
	t=CONS(SYM("argument"), MISC_EOL);
	x=CONS(t, x);
	t=CONS(SYM("constant"), CONS(CAR(CAR(expr)), MISC_EOL));
	x=CONS(t, x);
	t=CONS(SYM("argument"), MISC_EOL);
	x=CONS(t, x);
	t=CONS(SYM("refer"), CONS(kt, MISC_EOL));
	x=CONS(t, x);

	t=CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL));
	x=CONS(t, y);

	return(x);
}

// syntax-case key literals . patterns
elem HpiSpecial_SyntaxCase(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem x, t, cur, kn, kt;

	HpiComp_PushEnv(ctx);

	kn=Builtin_Gensym();
	ctx->ep_n=CONS(CONS(kn, CAR(ctx->ep_n)), CDR(ctx->ep_n));
	ctx->ep_d=CONS(CONS(MISC_NULL, CAR(ctx->ep_d)), CDR(ctx->ep_d));

	kt=HpiComp_Lookup(kn, ctx->ep_n);

//	t=HpiComp_Lookup(CADR(form), ctx->ep_n);
//	x=CONS(TyFcn_Symbol("assign"),CONS(t, MISC_EOL));
//	x=CONS(x, next);
//	x=HpiComp_Compile(CADDR(form), x, ctx, 0);

	cur=CDDDR(form);
	t=HpiSpecial_SyntaxCase_Inner(kt, CADDR(form), cur, ctx);

	HpiComp_PopEnv(ctx);

	x=CONS(TyFcn_Symbol("bind"),CONS(kn, MISC_EOL));
	x=CONS(x, t);
	x=HpiComp_Compile(CADR(form), x, ctx, 0);

	t=CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL));
	x=CONS(t, next);


	return(x);
}

elem HpiSpecial_UnquoteSplicing(elem form, elem next, InterpCtx *ctx, int tail)
{
	elem t, x;

	x=next;
	t=CONS(SYM("splice"), MISC_EOL);
	x=CONS(t, x);

	x=HpiComp_Compile(CADR(form), x, ctx, 0);

	return(x);
}

elem HpiComp_Import(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem cur;

	cur=CDR(form);
	while(cur!=MISC_EOL)
	{
		hpicomp_imports=CONS(CAR(cur), hpicomp_imports);
		cur=CDR(cur);
	}
	return(next);
}

elem HpiComp_Export(elem form, elem next, InterpCtx *ctx, elem tail)
{
	elem cur;

	cur=CDR(form);
	while(cur!=MISC_EOL)
	{
		hpicomp_exports=CONS(CAR(cur), hpicomp_exports);
		cur=CDR(cur);
	}
	return(next);
}

elem HpiComp_Module(elem form, elem next, InterpCtx *ctx, elem tail)
{
	hpicomp_modname=CAR(CDR(form));
	return(next);
}

#if 0
elem HpiComp_Include(elem form, elem next, InterpCtx *ctx, elem tail)
{
	VFILE *fd;
	int fsz;
	char *buf, *s;
	elem t, x;

	s=ELEM_TOSTRING(CAR(CDR(form)));
	buf=sa_malloc(strlen(s)+1);
	strcpy(buf, s);
	s=buf;

	fd=vffopen(s, "rb");
	vfseek(fd, 0, 2);
	fsz=vftell(fd);
	vfseek(fd, 0, 0);
	buf=sa_malloc(fsz+1);
	buf[fsz]=0;
	vfread(buf, 1, fsz, fd);

	s=buf;

	x=next;
	while(*s)
	{
		t=ScmParse_Line(&s, 0);
		if(t==MISC_UNDEFINED)break;

		t=HpiComp_Compile(t, x, ctx, 0);
		x=t;
	}

	sa_free(buf);

	return(x);
}
#endif

int HpiComp_Init()
{
//	SAGC_AddRoot(&hpicomp_specials_ntree);
//	SAGC_AddRoot(&hpicomp_specials_dtree);

	SAGC_AddRoot(&form_apply);
	SAGC_AddRoot(&form_return);
	SAGC_AddRoot(&form_halt);
	SAGC_AddRoot(&form_frame_apply_halt);

	SAGC_AddRoot(&form_apply_u);
	SAGC_AddRoot(&form_return_u);
	SAGC_AddRoot(&form_halt_u);
	SAGC_AddRoot(&form_frame_apply_halt_u);

	form_return=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	form_apply=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	form_halt=CONS(CONS(SYM("halt"), MISC_EOL), MISC_EOL);

	form_frame_apply_halt=CONS(CONS(SYM("frame"), CONS(form_apply, MISC_EOL)), form_halt);

	form_return_u=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	form_apply_u=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	form_halt_u=CONS(CONS(SYM("halt"), MISC_EOL), MISC_EOL);
	form_frame_apply_halt_u=CONS(CONS(SYM("frame"), CONS(form_apply, MISC_EOL)), form_halt);

//	hpicomp_specials_ntree=MISC_EOL;
//	hpicomp_specials_dtree=MISC_EOL;
	HpiComp_DefineSpecial("and", &HpiSpecial_And, 4);
	HpiComp_DefineSpecial("begin", &HpiSpecial_Begin, 4);
	HpiComp_DefineSpecial("begin-frame", &HpiSpecial_BeginFrame, 4);
	HpiComp_DefineSpecial("bound?", &HpiSpecial_BoundP, 4);
	HpiComp_DefineSpecial("call/cc", &HpiSpecial_CallCC, 4);
	HpiComp_DefineSpecial("call-with-current-continuation", &HpiSpecial_CallCC, 4);
	HpiComp_DefineSpecial("cond", &HpiSpecial_Cond, 4);
	HpiComp_DefineSpecial("constraint", &HpiSpecial_Constraint, 4);
	HpiComp_DefineSpecial("current-env", &HpiSpecial_CurrentEnv, 4);
//	HpiComp_DefineSpecial("current-envobj", &HpiSpecial_CurrentEnvObj, 4);
	HpiComp_DefineSpecial("define", &HpiSpecial_Define, 4);
	HpiComp_DefineSpecial("define-syntax", &HpiSpecial_DefineSyntax, 4);
//	HpiComp_DefineSpecial("defmacro", &HpiSpecial_Defmacro, 4);
	HpiComp_DefineSpecial("defmulti", &HpiSpecial_DefMulti, 4);
	HpiComp_DefineSpecial("defmultivar", &HpiSpecial_DefMultiVar, 4);
	HpiComp_DefineSpecial("defvar", &HpiSpecial_Defvar, 4);
	HpiComp_DefineSpecial("if", &HpiSpecial_If, 4);
	HpiComp_DefineSpecial("lambda", &HpiSpecial_Lambda, 4);
	HpiComp_DefineSpecial("let", &HpiSpecial_Let, 4);
//	HpiComp_DefineSpecial("let*", &HpiSpecial_LetM, 4);
	HpiComp_DefineSpecial("letrec", &HpiSpecial_Letrec, 4);
	HpiComp_DefineSpecial("letvar", &HpiSpecial_LetVar, 4);
	HpiComp_DefineSpecial("mini", &HpiSpecial_Mini, 4);
	HpiComp_DefineSpecial("or", &HpiSpecial_Or, 4);
	HpiComp_DefineSpecial("quasiquote", &HpiSpecial_Quasiquote, 4);
//	HpiComp_DefineSpecial("doubleqq", &HpiSpecial_DoubleQQ, 4);
	HpiComp_DefineSpecial("quote", &HpiSpecial_Quote, 4);
	HpiComp_DefineSpecial("rlet", &HpiSpecial_NamedLet, 4);
	HpiComp_DefineSpecial("set!", &HpiSpecial_SetN, 4);
	HpiComp_DefineSpecial("assign!", &HpiSpecial_AssignN, 4);
	HpiComp_DefineSpecial(":=", &HpiSpecial_AssignN, 4);
	HpiComp_DefineSpecial("syntax-case", &HpiSpecial_SyntaxCase, 4);
//	HpiComp_DefineSpecial("unquote-splicing", &HpiSpecial_UnquoteSplicing, 4);

	HpiComp_DefineSpecial("locative*", &HpiSpecial_LocativeM, 4);


	HpiComp_DefineSpecial(":import", &HpiComp_Import, 4);
	HpiComp_DefineSpecial(":export", &HpiComp_Export, 4);
	HpiComp_DefineSpecial(":module", &HpiComp_Module, 4);
//	HpiComp_DefineSpecial(":include", &HpiComp_Include, 4);

	//case do delay force, macros

	hpicomp_topbinds=MISC_EOL;
	hpicomp_imports=MISC_EOL;
	hpicomp_exports=MISC_EOL;
	hpicomp_modname=STRING("untitled");
}
