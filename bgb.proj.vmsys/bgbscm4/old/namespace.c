#include <scmcc.h>

elem Namespace_SymbolInList(elem name, elem lst)
{
	elem cur;
	int c;

	c=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		if(ELEM_SYMBOLP(TyFcn_Car(cur)))
			if(name==TyFcn_Car(cur))
			return(ELEM_FROMFIXNUM(c));
		c++;
		cur=TyFcn_Cdr(cur);
	}
	if(cur==name)return(ELEM_FROMFIXNUM(c));
	return(MISC_NULL);
}

elem Namespace_InsertSymbolList(elem sym, elem lst)
{
	elem cur, t;
	int c;

	c=0;
	cur=lst;
	while(TyFcn_Cdr(cur)!=MISC_EOL)
	{
		if(ELEM_SYMBOLP(TyFcn_Car(cur)))
			if(sym==TyFcn_Car(cur))
			return(ELEM_FROMFIXNUM(c));
		c++;
		cur=TyFcn_Cdr(cur);
	}
	TyFcn_SetCdr(cur, CONS(sym, MISC_EOL));
	return(ELEM_FROMFIXNUM(c));
}


elem Namespace_CreateEmptyEnv()
{
	elem *t;
	t=sa_alloc(2*ELEM_SZ);
	t[0]=OBJECT_ENV;
	t[1]=CONS(MISC_EOL, MISC_EOL);
	return(ELEM_FROMOBJECT(t));
}

elem Namespace_LookupVarList(elem name, elem binds)
{
	elem cur, t1, t2;

	cur=binds;

	SCMCC_ASSERT(ELEM_CONSP(cur) || (cur==MISC_EOL), "LookupVarList: invalid binds\n");

	while(cur!=MISC_EOL)
	{
		t1=TyFcn_Car(cur);
		if(ELEM_SYMDEFP(t1))
		{
			t2=TyFcn_SymdefName(t1);
			if(ELEM_SYMBOLP(t2))if(name==t2)
				return(t1);
		}
		cur=TyFcn_Cdr(cur);
	}
	return(MISC_UNDEFINED);
}

elem Namespace_LookupVarLayers(elem name, elem binds)
{
	elem cur, t;

	cur=binds;

	SCMCC_ASSERT2(ELEM_CONSP(cur) || (cur==MISC_EOL), 
		{sa_error("LookupVarLayers: invalid binds\n");return(MISC_UNDEFINED);})

	while(cur!=MISC_EOL)
	{
		t=Namespace_LookupVarList(name, TyFcn_Car(cur));
		if(t!=MISC_UNDEFINED)return(t);
		cur=TyFcn_Cdr(cur);
	}
	return(MISC_UNDEFINED);
}

elem Namespace_LookupEnvBinding(elem env, elem sym)
{
	elem t;
	t=TyFcn_ObjPeekElem(env, ELEM_FROMFIXNUM(1));
	SCMCC_ASSERT(ELEM_CONSP(t) || (t==MISC_EOL), "LookupEnvBinding: invalid env\n");
	t=Namespace_LookupVarLayers(sym, t);
	return(t);
}

elem Namespace_GetEnvBinding(elem env, elem sym)
{
	elem t;
	t=TyFcn_ObjPeekElem(env, ELEM_FROMFIXNUM(1));
	SCMCC_ASSERT(ELEM_CONSP(t) || (t==MISC_EOL), "LookupEnvBinding: invalid env\n");
	t=Namespace_LookupVarLayers(sym, t);
	if(ELEM_SYMDEFP(t))t=TyFcn_SymdefData(t);
	return(t);
}

elem Namespace_EnvWithBindings(elem env, elem vars)
{
	elem s, *t;

	s=TyFcn_ObjPeekElem(env, ELEM_FROMFIXNUM(1));
	t=sa_alloc(2*ELEM_SZ);
	t[0]=OBJECT_ENV;
	t[1]=CONS(vars, s);
	return(ELEM_FROMOBJECT(t));
}

elem Namespace_CreateEnvBinding(elem env, elem sym, elem val)
{
	elem t, u, v;
//	sa_print("fcn %d\n", val);

	t=TyFcn_ObjPeekElem(env, ELEM_FROMFIXNUM(1));
	u=TyFcn_Car(t);
	v=Namespace_LookupVarList(sym, u);
	if(v==MISC_UNDEFINED)
	{
		v=TyFcn_SymbolDef(sym, val, MISC_EOL);
//		sa_print("def symbol %d, bind %d\n", v, val);
		TyFcn_SetCar(t, CONS(v, u));
	}else TyFcn_SetSymdefData(v, val);
	return(v);
}

elem Namespace_DumpEnvBindings(elem env)
{
	elem cur;
	elem t, u, v;

	t=TyFcn_ObjPeekElem(env, ELEM_FROMFIXNUM(1));
	if(t!=MISC_EOL)u=TyFcn_Car(t);
		else u=t;

	cur=u;
	while(cur!=MISC_EOL)
	{
		if(ELEM_SYMDEFP(CAR(cur)))v=TyFcn_SymdefName(CAR(cur));
			else v=CAR(cur);
		TyFcn_DumpElem(v);
		sa_print("\t");
		cur=CDR(cur);
	}
	sa_print("\n");
	return(MISC_UNDEFINED);
}

elem Namespace_BindNamespaceEnv(elem lst, elem sym, elem env)
{
	elem t;
	t=Namespace_LookupVarList(sym, lst);
	if(t==MISC_UNDEFINED)
	{
		t=CONS(TyFcn_SymbolDef(sym, env, MISC_EOL), lst);
		return(t);
	}else TyFcn_SetSymdefData(t, env);
	return(lst);
}

elem Namespace_LookupSymInNamespace(elem lst, elem space, elem sym)
{
	elem t;
	t=Namespace_LookupVarList(space, lst);
	if(t==MISC_UNDEFINED)
	{
		sa_error("lookup-sym-in-namespace: unknown namespace.\n");
		return(t);
	}
	t=TyFcn_SymdefData(t);
	t=Namespace_LookupEnvBinding(t, sym);
	SCMCC_ASSERT(ELEM_SYMDEFP(t) || (t==MISC_UNDEFINED), "LookupSymInNamespace: return non-symbol\n");
	return(t);
}

elem Namespace_CreateDefault()
{
	elem t;
	t=TyFcn_SymbolDef(TyFcn_Symbol("lexical-bindings"), Namespace_CreateEmptyEnv(), MISC_EOL);
	t=CONS(t, MISC_EOL);
	return(t);
}

elem Namespace_DefineSymInNamespace(elem lst, elem space, elem sym, elem val)
{
	elem t;
	t=Namespace_LookupVarList(space, lst);
	if(t==MISC_UNDEFINED)
	{
		sa_error("define-sym-in-namespace: unknown namespace.\n");
		return(t);
	}
	t=TyFcn_SymdefData(t);
	t=Namespace_CreateEnvBinding(t, sym, val);
	return(t);
}
