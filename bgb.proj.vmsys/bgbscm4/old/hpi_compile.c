/*
	this will be a heap based interpreter.
 */
#include <scmcc.h>

elem hpicomp_specials;
extern elem form_return, form_apply, form_halt;

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
	pl=(TyFcn_Car(t)>>9)&127; /* hack: t is not a cons... */

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
			xa=TyFcn_Cons(TyFcn_Car(cur), xa);
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
	hpicomp_specials=CONS(
		TyFcn_SymbolDef(TyFcn_Symbol(name), TyFcn_Special(func, pc), MISC_EOL),
		hpicomp_specials);
	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, elem binds);

elem HpiComp_CompileExpr(elem form, elem next, elem binds)
{
	elem cur, x, t;
	int slam;

	t=Namespace_LookupVarList(CAR(form), hpicomp_specials);
	if(!ELEM_UNDEFP(t))
	{
		t=TyMisc_EvalSpecial(TyFcn_SymdefData(t), CONS(form, CONS(next, CONS(binds, MISC_EOL))));
		return(t);
	}

	slam=0;
	t=HpiComp_Lookup(CAR(form), binds);
	if(ELEM_SYMDEFP(t))
	{
		t=TyFcn_SymdefData(t);
		if(ELEM_CLOSUREP(t))if(OBJECT_HEAD(t)&(1<<14))slam=1;
		if(ELEM_FUNCTIONP(t))if(OBJECT_HEAD(t)&(1<<8))slam=1;
	}

	t=TyFcn_Cons(TyFcn_Symbol("apply"), MISC_EOL);
	x=TyFcn_Cons(t, MISC_EOL);

	x=HpiComp_Compile(TyFcn_Car(form), x, binds);
	if(ELEM_UNDEFP(x))return(MISC_UNDEFINED);

	cur=TyFcn_Cdr(form);
	while(cur!=MISC_EOL)
	{
		t=TyFcn_Cons(TyFcn_Symbol("argument"), MISC_EOL);
		x=TyFcn_Cons(t, x);
		x=HpiComp_Compile(TyFcn_Car(cur), x, binds);
		cur=CDR(cur);
	}

	x=CONS(CONS(TyFcn_Symbol("frame"), CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiComp_Lookup(elem sym, elem binds)
{
	elem cur, t;
	int c;

	c=0;
	cur=binds;
	while(ELEM_CONSP(cur))
	{
		t=Namespace_SymbolInList(sym, CAR(cur));
		if(t!=MISC_NULL)return(ELEM_FROMFRAME(c, ELEM_TOFIXNUM(t)));
		c++;
		cur=CDR(cur);
	}
	if(ELEM_ENVP(cur))
	{
		t=Namespace_LookupEnvBinding(cur, sym);
		if(ELEM_UNDEFP(t))return(MISC_NULL);
		return(t);
	}
	return(MISC_NULL);
}

elem HpiComp_Compile(elem form, elem next, elem binds)
{
	elem t, x;

	if(ELEM_SYMBOLP(form))
	{
		if(ELEM_SYMKEYWORDP(form))
		{
			x=TyFcn_Cons(TyFcn_Symbol("constant"), TyFcn_Cons(form, MISC_EOL));
			x=TyFcn_Cons(x, next);
			return(x);
		}
		t=HpiComp_Lookup(form, binds);
		if(t==MISC_NULL)
		{
			sa_error("unbound var %s\n", ELEM_TOSYMBOL(form));
			return(MISC_UNDEFINED);
		}
		x=TyFcn_Cons(TyFcn_Symbol("refer"), TyFcn_Cons(t, MISC_EOL));
		x=TyFcn_Cons(x, next);
		return(x);
#if 0
		t=Namespace_SymbolInList(form, largs);
		if(t!=MISC_NULL)
		{
			x=TyFcn_Cons(TyFcn_Symbol("refer-local"), TyFcn_Cons(t, MISC_EOL));
			x=TyFcn_Cons(x, next);
			return(x);
		}
		t=Namespace_LookupVarList(form, disp);
		if(t!=MISC_UNDEFINED)
		{
			x=TyFcn_Cons(TyFcn_Symbol("refer-free"), TyFcn_Cons(t, MISC_EOL));
			x=TyFcn_Cons(x, next);
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
		x=HpiComp_CompileExpr(form, next, binds);
	}else
	{
		x=TyFcn_Cons(TyFcn_Symbol("constant"), TyFcn_Cons(form, MISC_EOL));
		x=TyFcn_Cons(x, next);
	}
	return(x);
}

elem HpiSpecial_If(elem form, elem next, elem binds)
{
	elem x, tc, fc;

	tc=HpiComp_Compile(CADDR(form), next, binds);
	x=CDDDR(form);
	if(x!=MISC_EOL)fc=HpiComp_Compile(CADDDR(form), next, binds);
		else fc=next;

	x=CONS(TyFcn_Symbol("test"), CONS(tc, CONS(fc, MISC_EOL)));
	x=CONS(x, MISC_EOL);

	x=HpiComp_Compile(CADR(form), x, binds);

	return(x);
}

elem HpiSpecial_CallCC(elem form, elem next, elem binds)
{
	elem x, t;
	x=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	x=HpiComp_Compile(CADR(form), x, binds);

	t=TyFcn_Cons(TyFcn_Symbol("argument"), MISC_EOL);
	x=TyFcn_Cons(t, x);

	t=CONS(TyFcn_Symbol("conti"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"), CONS(x, MISC_EOL)), next);
	return(x);
}

elem HpiSpecial_NamedLet(elem form, elem next, elem binds)
{
	elem x, cur, r, t;
	elem lbinds, ldef;

	r=MISC_EOL;
	cur=CADDR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	r=TyFcn_NReverse(r);

	lbinds=CONS(CONS(CADR(form), MISC_EOL), binds);

	x=CONS(TyFcn_Symbol("apply"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Lookup(CADR(form), lbinds);
	t=CONS(SYM("assign"), CONS(t, MISC_EOL));
	x=CONS(t, x);

	ldef=CONS(SYM("lambda"), CONS(r, CDDDR(form)));
//	t=HpiComp_Compile(CADDR(form), x, lbinds);
	x=HpiComp_Compile(ldef, x, lbinds);

	cur=CADDR(form);
	while(cur!=MISC_EOL)
	{
		t=TyFcn_Cons(TyFcn_Symbol("argument"), MISC_EOL);
		x=TyFcn_Cons(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, binds);
		cur=CDR(cur);
	}

	t=TyFcn_Cons(TyFcn_Symbol("bind-args"), MISC_EOL);
	x=TyFcn_Cons(t, x);

	t=TyFcn_Cons(TyFcn_Symbol("argument"), MISC_EOL);
	x=TyFcn_Cons(t, x);

	x=CONS(CONS(TyFcn_Symbol("frame"), CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Let(elem form, elem next, elem binds)
{
	elem x, cur, r, t;
	elem lbinds;

	if(ELEM_SYMBOLP(CADR(form)))return(HpiSpecial_NamedLet(form, next, binds));

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	lbinds=CONS(r, binds);

	x=CONS(TyFcn_Symbol("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Compile(CADDR(form), x, lbinds);

	x=CONS(TyFcn_Symbol("bind-args"), MISC_EOL);
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=TyFcn_Cons(TyFcn_Symbol("argument"), MISC_EOL);
		x=TyFcn_Cons(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, binds);
		cur=CDR(cur);
	}

	x=CONS(CONS(TyFcn_Symbol("frame"), CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_LetM(elem form, elem next, elem binds)
{
	elem x, cur, r, t;
	elem lbinds;
	elem flst, bf;

	lbinds=CONS(MISC_EOL, binds);

	flst=TyFcn_Reverse(CADR(form));

	bf=MISC_EOL;
	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CONS(CONS(SYM("bind"), MISC_EOL), MISC_EOL);
		t=HpiComp_Compile(CADR(CAR(cur)), t, lbinds);
		bf=TyFcn_NAppend(bf, t);

		t=CAR(CAR(cur));
		r=CONS(t, r);
		TyFcn_SetCar(lbinds, r);
		cur=CDR(cur);
	}

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	x=HpiComp_Compile(CADDR(form), x, lbinds);

	x=TyFcn_NAppend(bf, x);

	t=CONS(SYM("bind-args"), MISC_EOL);
	x=CONS(t, x);

	x=CONS(CONS(SYM("frame"), CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Letrec(elem form, elem next, elem binds)
{
	elem x, cur, r, t;
	elem lbinds;

	r=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=CAR(CAR(cur));
		r=CONS(t, r);
		cur=CDR(cur);
	}
	lbinds=CONS(r, binds);

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);

	t=HpiComp_Compile(CADDR(form), x, lbinds);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=HpiComp_Lookup(CAR(CAR(cur)), lbinds);
		t=TyFcn_Cons(SYM("assign"), CONS(t, MISC_EOL));
		x=TyFcn_Cons(t, x);
		x=HpiComp_Compile(CADR(CAR(cur)), x, lbinds);
		cur=CDR(cur);
	}

	x=CONS(SYM("bind-args"), MISC_EOL);
	x=CONS(x, t);

	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		t=TyFcn_Cons(SYM("bind"), MISC_EOL);
		x=TyFcn_Cons(t, x);
		cur=CDR(cur);
	}

	x=CONS(TyFcn_Symbol("constant"), CONS(MISC_NULL, MISC_EOL));
	x=CONS(x, t);

	x=CONS(CONS(TyFcn_Symbol("frame"), CONS(x, MISC_EOL)), next);

	return(x);
}

elem HpiSpecial_Define(elem form, elem next, elem binds)
{
	elem x, t, var, vars;

	var=CADR(form);
	if(ELEM_CONSP(var))
	{
		vars=CDR(var);
		var=CAR(var);
	}else vars=MISC_NULL;

	if(ELEM_ENVP(binds))
	{
		t=Namespace_CreateEnvBinding(binds, var, MISC_UNDEFINED);
		x=CONS(CONS(SYM("assign"), CONS(t, MISC_EOL)), next);
	}else if(ELEM_CONSP(binds))
	{
		TyFcn_SetCar(binds, CONS(var, CAR(binds)));
		x=CONS(CONS(SYM("bind"), MISC_EOL), next);
	}
	if(ELEM_NULLP(vars))x=HpiComp_Compile(CADDR(form), x, binds);
		else
	{
		t=CONS(SYM("lambda"), CONS(vars, CONS(CADDR(form), MISC_EOL)));
		x=HpiComp_Compile(t, x, binds);
	}
	return(x);
}

elem HpiSpecial_SetN(elem form, elem next, elem binds)
{
	elem x, t;
	t=HpiComp_Lookup(CADR(form), binds);
	x=CONS(TyFcn_Symbol("assign"), CONS(t, MISC_EOL));
	x=CONS(x, next);
	x=HpiComp_Compile(CADDR(form), x, binds);
	return(x);
}

elem HpiSpecial_LocativeM(elem form, elem next, elem binds)
{
	elem x, t;
	t=HpiComp_Lookup(CADR(form), binds);
	x=CONS(TyFcn_Symbol("locative"), CONS(t, MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_Lambda(elem form, elem next, elem binds)
{
	elem x, lbinds;

	lbinds=CONS(CADR(form), binds);

	x=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	x=HpiComp_Compile(CADDR(form), x, lbinds);
	x=CONS(TyFcn_Symbol("close"), CONS(lbinds, CONS(x, MISC_EOL)));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_Quote(elem form, elem next, elem binds)
{
	elem x;
	x=CONS(TyFcn_Symbol("constant"), CONS(CADR(form), MISC_EOL));
	x=CONS(x, next);
	return(x);
}

elem HpiSpecial_Begin(elem form, elem next, elem binds)
{
	elem x, cur, lst;
	lst=TyFcn_Reverse(CDR(form));
	cur=lst;
	x=next;
	while(cur!=MISC_EOL)
	{
		x=HpiComp_Compile(CAR(cur), x, binds);
		cur=CDR(cur);
	}
	return(x);
}

elem HpiSpecial_And(elem form, elem next, elem binds)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"), CONS(x, CONS(bc, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, binds);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Or(elem form, elem next, elem binds)
{
	elem x, bc, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		x=CONS(CONS(SYM("test"), CONS(bc, CONS(x, MISC_EOL))), MISC_EOL);
		x=HpiComp_Compile(CAR(cur), x, binds);
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Cond(elem form, elem next, elem binds)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, binds);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"), CONS(ec, CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, binds);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Case(elem form, elem next, elem binds)
{
	elem x, bc, ec, cur, lst;

	lst=TyFcn_Reverse(CDR(form));
	bc=next;
	x=next;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		ec=HpiComp_Compile(CADR(CAR(cur)), bc, binds);
		if(CAR(CAR(cur))!=SYM("else"))
		{
			x=CONS(CONS(SYM("test"), CONS(ec, CONS(x, MISC_EOL))), MISC_EOL);
			x=HpiComp_Compile(CAR(CAR(cur)), x, binds);
		}else x=ec;
		cur=CDR(cur);
	}
	x=CONS(CONS(SYM("constant"), CONS(MISC_TRUE, MISC_EOL)), x);
	return(x);
}

elem HpiSpecial_Quasiquote(elem form, elem next, elem binds)
{
	elem x, t, lst, cur;

	lst=MISC_EOL;
	cur=CADR(form);
	while(cur!=MISC_EOL)
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAR(CAR(cur))==SYM("unquote"))
				lst=CONS(CONS(SYM("#uqf"), HpiComp_Compile(CADR(CAR(cur)), form_halt, binds)), lst);
				else if(ELEM_CONSP(CAR(cur)))if(CAR(CAR(cur))==SYM("unquote-splicing"))
				lst=CONS(CONS(SYM("#uqs"), HpiComp_Compile(CADR(CAR(cur)), form_halt, binds)), lst);
				else lst=CONS(CAR(cur), lst);
		}else lst=CONS(CAR(cur), lst);
		cur=CDR(cur);
	}
	lst=TyFcn_NReverse(lst);

	x=CONS(SYM("qq"), CONS(lst, MISC_EOL));
	x=CONS(x, next);
	return(x);
}

int HpiComp_Init()
{
	MMGC_AddRoot(&hpicomp_specials);

	hpicomp_specials=MISC_EOL;
	HpiComp_DefineSpecial("quote", &HpiSpecial_Quote, 3);
	HpiComp_DefineSpecial("lambda", &HpiSpecial_Lambda, 3);
	HpiComp_DefineSpecial("set!", &HpiSpecial_SetN, 3);
	HpiComp_DefineSpecial("define", &HpiSpecial_Define, 3);
	HpiComp_DefineSpecial("let", &HpiSpecial_Let, 3);
	HpiComp_DefineSpecial("let*", &HpiSpecial_LetM, 3);
	HpiComp_DefineSpecial("letrec", &HpiSpecial_Letrec, 3);
	HpiComp_DefineSpecial("call/cc", &HpiSpecial_CallCC, 3);
	HpiComp_DefineSpecial("call-with-current-continuation", &HpiSpecial_CallCC, 3);
	HpiComp_DefineSpecial("if", &HpiSpecial_If, 3);
	HpiComp_DefineSpecial("begin", &HpiSpecial_Begin, 3);
	HpiComp_DefineSpecial("and", &HpiSpecial_And, 3);
	HpiComp_DefineSpecial("or", &HpiSpecial_Or, 3);
	HpiComp_DefineSpecial("cond", &HpiSpecial_Cond, 3);
	HpiComp_DefineSpecial("quasiquote", &HpiSpecial_Quasiquote, 3);

	HpiComp_DefineSpecial("locative*", &HpiSpecial_LocativeM, 3);

	//case do delay force, macros
}
