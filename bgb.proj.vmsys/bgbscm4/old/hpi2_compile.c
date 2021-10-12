#include <scmcc.h>

elem hpicomp_specials_ntree, hpicomp_specials_dtree;
extern elem toplevel_n, toplevel_d;

elem form_return, form_apply, form_halt;

elem hpicomp_topbinds, hpicomp_exports, hpicomp_imports, hpicomp_modname;

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
	pl=(OBJECT_HEAD(t)>>9)&127; /* hack: t is not a cons... */

	pa=pl&31;
	pc=0;
	while(cur!=MISC_EOL && (pc<pa))
	{
		parm[pc++]=TyFcn_Car(cur);
		cur=TyFcn_Cdr(cur);
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
	SCMCC_ASSERT(cur==MISC_EOL, "extra args.\n");

	t=TyFcn_Cdr(func); /* hack: t is not a cons... */
	t=invoke_func(t, pc, parm);
	return(t);
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

	toplevel_n=CONS(CONS(TyFcn_Symbol(name), CAR(toplevel_n)), MISC_EOL);
	toplevel_d=CONS(CONS(TyFcn_Special(func, pc), CAR(toplevel_d)), MISC_EOL);

	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, elem binds_n, elem binds_d, int tail);
elem HpiInterp_Run(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d);

elem HpiComp_CompileExpr(elem form, elem next, elem binds_n, elem binds_d, int tail)
{
	elem cur, x, t, f;
	elem ep_n, ep_d;

//	t=Namespace_LookupVarList(CAR(form), hpicomp_specials);
//	t=Namespace2_Lookup(hpicomp_specials_ntree, hpicomp_specials_dtree, CAR(form));
	t=Namespace2_Lookup(binds_n, binds_d, CAR(form));
//	if(!ELEM_UNDEFP(t))
	if(ELEM_SYNTAXP(t))
	{
		t=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS(binds_n,CONS(binds_d,CONS(tail, MISC_EOL))))));
		return(t);
	}
	if(ELEM_MACROP(t))
	{
//		t=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS(binds_n,CONS(binds_d,CONS(tail, MISC_EOL))))));

		ep_n=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0));

//		x=CAR(ctx->ep_n);

		ep_d=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1));
		ep_d=CONS(CDR(form), ep_d);

		f=TyFcn_VectorRef(t, ELEM_FROMFIXNUM(2));

		t=HpiInterp_Run(f, ep_n, ep_d, CONS(MISC_EOL, MISC_EOL), CONS(MISC_EOL, MISC_EOL));
		x=HpiComp_Compile(t, next, binds_n, binds_d, tail);

		return(x);
	}

//	t=Namespace2_Lookup(hpicomp_specials_ntree, hpicomp_specials_dtree, CADR(form));
//	if(!ELEM_UNDEFP(t))
//	{
//		t=TyMisc_EvalSpecial(t,CONS(form,CONS(next,CONS(binds_n,CONS(binds_d,CONS(tail, MISC_EOL))))));
//		return(t);
//	}

//	slam=0;
//	t=HpiComp_Lookup(CAR(form), binds);
//	if(ELEM_SYMDEFP(t))
//	{
//		t=TyFcn_SymdefData(t);
//		if(ELEM_CLOSUREP(t))if(OBJECT_HEAD(t)&(1<<14))slam=1;
//		if(ELEM_FUNCTIONP(t))if(OBJECT_HEAD(t)&(1<<8))slam=1;
//	}

//	t=CONS(TyFcn_Symbol("apply"), MISC_EOL);
//	x=CONS(t, MISC_EOL);
	x=form_apply;

//	f=CAR(form);
//	t=Namespace2_Lookup(binds_n, binds_d, f);

	x=HpiComp_Compile(CAR(form), x, binds_n, binds_d, 0);
	if(ELEM_UNDEFP(x))return(MISC_UNDEFINED);

	cur=TyFcn_Cdr(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(TyFcn_Car(cur), x, binds_n, binds_d, 0);
		cur=CDR(cur);
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

		t=Namespace2_Trace(binds, binds, MISC_EOL, sym);
		if(t!=MISC_UNDEFINED)return(t);
	}

//	t=Namespace_SymbolInList(sym, hpicomp_topbinds);
//	if(t!=MISC_NULL)return(sym);

//	t=Namespace_SymbolInList(sym, hpicomp_imports);
//	if(t!=MISC_NULL)return(sym);

	return(sym);	// in this case sym refers to an implicit dynamic var.
//	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, elem binds_n, elem binds_d, int tail)
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
		t=HpiComp_Lookup(form, binds_n);
		if(t==MISC_NULL)
		{
			sa_error("unbound var %s\n", ELEM_TOSYMBOL(form));
			return(MISC_UNDEFINED);
		}
		x=CONS(TyFcn_Symbol("refer"), CONS(t, MISC_EOL));
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
		x=HpiComp_CompileExpr(form, next, binds_n, binds_d, tail);
	}else
	{
		x=CONS(TyFcn_Symbol("constant"), CONS(form, MISC_EOL));
		x=CONS(x, next);
	}
	return(x);
}


elem HpiSpecial_And(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"),CONS(x,CONS(bc, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, binds_n, binds_d, 0);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Begin(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, cur, lst;
	lst=TyFcn_Reverse(CDR(form));
	cur=lst;
	x=next;
	while(cur!=MISC_EOL)
	{
		x=HpiComp_Compile(CAR(cur), x, binds_n, binds_d, tail);
		if(tail)tail=0;
		cur=CDR(cur);
	}
	return(x);
}

elem HpiSpecial_CallCC(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t;
	x=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	x=HpiComp_Compile(CADR(form), x, binds_n, binds_d, 0);

	t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
	x=CONS(t, x);

	t=CONS(TyFcn_Symbol("conti"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);
	return(x);
}

elem HpiSpecial_Case(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, binds_n, binds_d, 0);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"),CONS(ec,CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, binds_n, binds_d, 0);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Cond(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, binds_n, binds_d, 0);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"), CONS(ec,CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, binds_n, binds_d, 0);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_CurrentEnv(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x;
	x=CONS(CONS(SYM("current-env"), MISC_EOL), next);
	return(x);
}

elem HpiSpecial_CurrentEnvObj(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x;
	x=CONS(CONS(SYM("current-envobj"), MISC_EOL), next);
	return(x);
}

elem HpiSpecial_Define(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t, var, vars;
	elem lbinds_n, lbinds_d;

	var=CADR(form);
	if(ELEM_CONSP(var))
	{
		vars=CDR(var);
		var=CAR(var);
	}else vars=MISC_NULL;

//	if(ELEM_ENVP(binds))
	if(binds_n==MISC_EOL)
	{
//		t=Namespace_CreateEnvBinding(binds, var, MISC_UNDEFINED);
//		x=CONS(CONS(SYM("assign"),CONS(t, MISC_EOL)), next);
		hpicomp_topbinds=CONS(var, hpicomp_topbinds);
		x=CONS(CONS(SYM("assign"),CONS(var, MISC_EOL)), next);
	}else if(ELEM_CONSP(binds_n))
	{
//		TyFcn_SetCar(binds_n,CONS(var, CAR(binds_n)));
//		TyFcn_SetCar(binds_d,CONS(MISC_NULL, CAR(binds_d)));
//		binds_n=CONS(var, binds_n);
//		binds_d=CONS(MISC_NULL, binds_d);
		lbinds_n=CONS(CONS(var, CAR(binds_n)), CDR(binds_n));
		lbinds_d=CONS(CONS(MISC_NULL, CAR(binds_d)), CDR(binds_d));
		t=HpiComp_Lookup(var, lbinds_n);
		x=CONS(CONS(SYM("assign"), CONS(t, MISC_EOL)), next);
	}
	if(!ELEM_NULLP(vars))
	{
		t=CONS(SYM("lambda"),CONS(vars,CONS(CADDR(form), MISC_EOL)));
		x=HpiComp_Compile(t, x, lbinds_n, lbinds_d, 1);
	}else x=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	if(binds_n!=MISC_EOL)x=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), x);

	return(x);
}

elem HpiSpecial_Defvar(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t, var, vars;

	var=CADR(form);
	if(ELEM_CONSP(var))
	{
		vars=CDR(var);
		var=CAR(var);
	}else vars=MISC_NULL;

	x=CONS(CONS(SYM("assign"), CONS(var, MISC_EOL)), next);

	if(!ELEM_NULLP(vars))
	{
		t=CONS(SYM("lambda"),CONS(vars,CONS(CADDR(form), MISC_EOL)));
		x=HpiComp_Compile(t, x, binds_n, binds_d, 1);
	}else x=HpiComp_Compile(CADDR(form), x, binds_n, binds_d, 1);

	x=CONS(CONS(SYM("bind-var"), CONS(var, MISC_EOL)), x);

	return(x);
}

elem HpiSpecial_Defmacro(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t, var, args;
	elem lbinds_n, lbinds_d, lb2_d;

	var=CADR(form);
	args=CADDR(form);

//	if(ELEM_ENVP(binds))
	if(binds_n==MISC_EOL)
	{
//		t=Namespace_CreateEnvBinding(binds, var, MISC_UNDEFINED);
//		x=CONS(CONS(SYM("assign"),CONS(t, MISC_EOL)), next);
		hpicomp_topbinds=CONS(var, hpicomp_topbinds);
		x=CONS(CONS(SYM("assign"),CONS(var, MISC_EOL)), next);
	}else if(ELEM_CONSP(binds_n))
	{
//		lbinds_n=CONS(CONS(var, CAR(binds_n)), CDR(binds_n));
//		lbinds_d=CONS(CONS(MISC_NULL, CAR(binds_d)), CDR(binds_d));
//		t=HpiComp_Lookup(var, lbinds_n);
//		x=CONS(CONS(SYM("assign"), CONS(t, MISC_EOL)), next);

		lbinds_n=CONS(CONS(var, CAR(binds_n)), CDR(binds_n));
		lbinds_d=CONS(CONS(MISC_NULL, CAR(binds_d)), CDR(binds_d));

		t=HpiComp_Compile(CADDDR(form), form_halt, CONS(args, lbinds_n), CONS(args, lbinds_d), 0);

		x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_MACRO));

		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), CONS(args, lbinds_n));
		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), lbinds_d);

		TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

//		TyFcn_SetCar(binds_n, CONS(var, CAR(binds_n)));
//		TyFcn_SetCar(binds_d, CONS(x, CAR(binds_d)));
	}

//	if(binds_n!=MISC_EOL)x=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), x);

	t=CONS(CONS(SYM("bind"), CONS(var, MISC_EOL)), next); //HACK: macros defined at runtime
	t=CONS(CONS(SYM("constant"), CONS(x, MISC_EOL)), t);

	return(t);
}

#if 0
elem HpiSpecial_Function(elem form, elem next, elem binds_n, elem binds_d, elem tail)
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
		TyFcn_SetCar(binds_n, CONS(var, CAR(binds_n)));
		TyFcn_SetCar(binds_d, CONS(ELEM_DUMMY(TYPE_FUNCTION), CAR(binds_d)));
		x=CONS(CONS(SYM("bind"), MISC_EOL), next);
	}

	t=CONS(SYM("lambda"),CONS(vars,CONS(CADDDR(form), MISC_EOL)));
	x=HpiComp_Compile(t, x, binds_n, binds_d, 1);

	return(x);
}
#endif

elem HpiSpecial_If(elem form, elem next, elem binds_n, elem binds_d, int tail)
{
	elem x, tc, fc;

	/* conditions are non-tail as if does not produce a frame */
	tc=HpiComp_Compile(CADDR(form), next, binds_n, binds_d, tail);
	x=CDDDR(form);
	if(x!=MISC_EOL)fc=HpiComp_Compile(CADDDR(form), next, binds_n, binds_d, tail);
		else fc=next;

	x=CONS(TyFcn_Symbol("test"),CONS(tc,CONS(fc, MISC_EOL)));
	x=CONS(x, MISC_EOL);

	x=HpiComp_Compile(CADR(form), x, binds_n, binds_d, 0);

	return(x);
}

elem HpiSpecial_Lambda(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, lbinds_n, lbinds_d;

	lbinds_n=CONS(CADR(form), binds_n);
	lbinds_d=CONS(CADR(form), binds_d);

	x=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	x=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);
	x=CONS(TyFcn_Symbol("close"),CONS(CADR(form), CONS(x, MISC_EOL)));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_NamedLet(elem form, elem next, elem binds_n, elem binds_d, elem tail);

elem HpiSpecial_Let(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;

	if(ELEM_SYMBOLP(CADR(form)))return(HpiSpecial_NamedLet(form, next, binds_n, binds_d, tail));

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	lbinds_n=CONS(r, binds_n);
	lbinds_d=CONS(r, binds_d);

	x=CONS(TyFcn_Symbol("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	x=CONS(TyFcn_Symbol("bind-args"),CONS(r, MISC_EOL));
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, binds_n, binds_d, 0);
		cur=CDR(cur);
	}

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

#if 0
elem HpiSpecial_LetM(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, cur, r, t;
	elem lbinds_n, lbinds_d;
	elem flst, bf;

	lbinds_n=CONS(MISC_EOL, binds_n);
	lbinds_d=CONS(MISC_EOL, binds_d);

	flst=TyFcn_Reverse(CADR(form));

	bf=MISC_EOL;
	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(CONS(SYM("bind"),CONS(CAR(CAR(cur)), MISC_EOL)), MISC_EOL);
		t=HpiComp_Compile(CADR(CAR(cur)), t, lbinds_n, lbinds_d, 0);
		bf=TyFcn_NAppend(bf, t);

		t=CAR(CAR(cur));
		r=CONS(t, r);
		TyFcn_SetCar(lbinds, r);
		cur=CDR(cur);
	}

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	x=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	x=TyFcn_NAppend(bf, x);

	t=CONS(SYM("bind-args"),CONS(MISC_EOL, MISC_EOL));
	x=CONS(t, x);

	x=CONS(CONS(SYM("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}
#endif

elem HpiSpecial_Letrec(elem form, elem next, elem binds_n, elem binds_d, elem tail)
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
	lbinds_n=CONS(r, binds_n);
	lbinds_d=CONS(r, binds_d);

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Compile(CADDR(form), x, lbinds_n, lbinds_d, 1);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=HpiComp_Lookup(CAR(CAR(cur)), lbinds_n);
		t=CONS(SYM("assign"),CONS(t, MISC_EOL));
		x=CONS(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, lbinds_n, lbinds_d, 0);
		cur=CDR(cur);
	}

	x=CONS(SYM("bind-args"),CONS(r, MISC_EOL));
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(SYM("argument"), MISC_EOL);
		x=CONS(t, x);
		cur=CDR(cur);
	}

	x=CONS(TyFcn_Symbol("constant"),CONS(MISC_NULL, MISC_EOL));
	x=CONS(x, t);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_LocativeM(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t;
	t=HpiComp_Lookup(CADR(form), binds_n);
	x=CONS(TyFcn_Symbol("locative"),CONS(t, MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_Mini(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x;
	x=CDR(form);
	return(x);
}

elem HpiSpecial_NamedLet(elem form, elem next, elem binds_n, elem binds_d, elem tail)
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

	lbinds_n=CONS(CONS(CADR(form), MISC_EOL), binds_n);
	lbinds_d=CONS(CONS(CADR(form), MISC_EOL), binds_d);

	x=CONS(TyFcn_Symbol("apply"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Lookup(CADR(form), lbinds_n);
	t=CONS(SYM("assign"),CONS(t, MISC_EOL));
	x=CONS(t, x);

	ldef=CONS(SYM("lambda"),CONS(r, CDDDR(form)));
//	t=HpiComp_Compile(CADDR(form), x, lbinds);
	x=HpiComp_Compile(ldef, x, lbinds_n, lbinds_d, 0);

	cur=CADDR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
		x=CONS(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, binds_n, binds_d, 0);
		cur=CDR(cur);
	}

	t=CONS(TyFcn_Symbol("bind-args"),CONS(CONS(CADR(form), MISC_EOL), MISC_EOL));
	x=CONS(t, x);

	t=CONS(TyFcn_Symbol("argument"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"),CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Or(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"),CONS(bc,CONS(x, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, binds_n, binds_d, 0);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"),CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_SetN(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t;
	t=HpiComp_Lookup(CADR(form), binds_n);
	x=CONS(TyFcn_Symbol("assign"),CONS(t, MISC_EOL));
	x=CONS(x, next);
	x=HpiComp_Compile(CADDR(form), x, binds_n, binds_d, 0);
	return(x);
}

elem HpiSpecial_Quasiquote(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x, t, lst, cur;

	lst=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAR(CAR(cur))==SYM("unquote"))
				lst=CONS(CONS(SYM("#uqf"), HpiComp_Compile(CADR(CAR(cur)), form_halt, binds_n, binds_d, 0)), lst);
				else if(ELEM_CONSP(CAR(cur)))if(CAR(CAR(cur))==SYM("unquote-splicing"))
				lst=CONS(CONS(SYM("#uqs"), HpiComp_Compile(CADR(CAR(cur)), form_halt, binds_n, binds_d, 0)), lst);
				else lst=CONS(CAR(cur), lst);
		}else lst=CONS(CAR(cur), lst);
		cur=CDR(cur);
	}
	lst=TyFcn_NReverse(lst);

	x=CONS(SYM("qq"),CONS(lst, MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_Quote(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	elem x;
	x=CONS(TyFcn_Symbol("constant"),CONS(CADR(form), MISC_EOL));
	x=CONS(x, next);
	return(x);
}


elem HpiComp_Import(elem form, elem next, elem binds_n, elem binds_d, elem tail)
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

elem HpiComp_Export(elem form, elem next, elem binds_n, elem binds_d, elem tail)
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

elem HpiComp_Module(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	hpicomp_modname=CAR(CDR(form));
	return(next);
}

elem HpiComp_Include(elem form, elem next, elem binds_n, elem binds_d, elem tail)
{
	FILE *fd;
	int fsz;
	char *buf, *s;
	elem t, x;

	s=ELEM_TOSTRING(CAR(CDR(form)));
	buf=sa_malloc(strlen(s)+1);
	strcpy(buf, s);
	s=buf;

	fd=fopen(s, "rb");
	fseek(fd, 0, 2);
	fsz=ftell(fd);
	fseek(fd, 0, 0);
	buf=sa_malloc(fsz+1);
	buf[fsz]=0;
	fread(buf, 1, fsz, fd);

	s=buf;

	x=next;
	while(*s)
	{
		t=ScmParse_Line(&s, 0);
		if(t==MISC_UNDEFINED)break;

		t=HpiComp_Compile(t, x, binds_n, binds_d, 0);
		x=t;
	}

	sa_free(buf);

	return(x);
}

int HpiComp_Init()
{
	MMGC_AddRoot(&hpicomp_specials_ntree);
	MMGC_AddRoot(&hpicomp_specials_dtree);

	MMGC_AddRoot(&form_apply);
	MMGC_AddRoot(&form_return);
	MMGC_AddRoot(&form_halt);

	form_return=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	form_apply=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	form_halt=CONS(CONS(SYM("halt"), MISC_EOL), MISC_EOL);

//	hpicomp_specials_ntree=MISC_EOL;
//	hpicomp_specials_dtree=MISC_EOL;
	HpiComp_DefineSpecial("and", &HpiSpecial_And, 5);
	HpiComp_DefineSpecial("begin", &HpiSpecial_Begin, 5);
	HpiComp_DefineSpecial("call/cc", &HpiSpecial_CallCC, 5);
	HpiComp_DefineSpecial("call-with-current-continuation", &HpiSpecial_CallCC, 5);
	HpiComp_DefineSpecial("cond", &HpiSpecial_Cond, 5);
	HpiComp_DefineSpecial("current-env", &HpiSpecial_CurrentEnv, 5);
	HpiComp_DefineSpecial("current-envobj", &HpiSpecial_CurrentEnvObj, 5);
	HpiComp_DefineSpecial("define", &HpiSpecial_Define, 5);
	HpiComp_DefineSpecial("defmacro", &HpiSpecial_Defmacro, 5);
	HpiComp_DefineSpecial("defvar", &HpiSpecial_Defvar, 5);
	HpiComp_DefineSpecial("if", &HpiSpecial_If, 5);
	HpiComp_DefineSpecial("lambda", &HpiSpecial_Lambda, 5);
	HpiComp_DefineSpecial("let", &HpiSpecial_Let, 5);
//	HpiComp_DefineSpecial("let*", &HpiSpecial_LetM, 5);
	HpiComp_DefineSpecial("letrec", &HpiSpecial_Letrec, 5);
	HpiComp_DefineSpecial("mini", &HpiSpecial_Mini, 5);
	HpiComp_DefineSpecial("or", &HpiSpecial_Or, 5);
	HpiComp_DefineSpecial("set!", &HpiSpecial_SetN, 5);
	HpiComp_DefineSpecial("quasiquote", &HpiSpecial_Quasiquote, 5);
	HpiComp_DefineSpecial("quote", &HpiSpecial_Quote, 5);

	HpiComp_DefineSpecial("locative*", &HpiSpecial_LocativeM, 5);


	HpiComp_DefineSpecial(":import", &HpiComp_Import, 5);
	HpiComp_DefineSpecial(":export", &HpiComp_Export, 5);
	HpiComp_DefineSpecial(":module", &HpiComp_Module, 5);
	HpiComp_DefineSpecial(":include", &HpiComp_Include, 5);

	//case do delay force, macros

	hpicomp_topbinds=MISC_EOL;
	hpicomp_imports=MISC_EOL;
	hpicomp_exports=MISC_EOL;
	hpicomp_modname=STRING("untitled");
}
