#include <scmcc.h>

elem Namespace3_List2Vec(elem lst)
{
	elem cur, t;
	int i, l, l2;

	if(ELEM_VECTORP(lst))return(lst);

	l=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		l++;
		cur=CDR(cur);
	}

	if(ELEM_VECTORP(cur))
	{
		l2=l+VECTOR_LEN(cur);

		t=VECTOR_NEW(l2);
		for(i=l; i<l2; i++)
			VECTOR_SET(t, i, VECTOR_REF(cur, i-l));
	}else
	{
		l++;
		t=VECTOR_NEW(l);
	}

	i=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		VECTOR_SET(t, i, CAR(cur));
		i++;
		cur=CDR(cur);
	}
	if(!ELEM_VECTORP(cur))
		VECTOR_SET(t, i, cur);

	return(t);
}

elem Namespace3_Bind(elem *ntree, elem *dtree, elem sym, elem val)
{
	elem cn, cd;

#if 0
	*ntree=Namespace3_List2Vec(*ntree);
	*dtree=Namespace3_List2Vec(*dtree);

	cn=VECTOR_REF(*ntree, 0);
	cd=VECTOR_REF(*dtree, 0);

	cn=CONS(sym, cn);
	cd=CONS(val, cd);

	cn=Namespace3_List2Vec(cn);
	cd=Namespace3_List2Vec(cd);

	VECTOR_SET(*ntree, 0, cn);
	VECTOR_SET(*dtree, 0, cd);
#else
	*ntree=CONS(CONS(sym,	CAR(*ntree)), CDR(*ntree));
	*dtree=CONS(CONS(val,	CAR(*dtree)), CDR(*dtree));
#endif

	return(MISC_NULL);
}

elem Namespace3_BindArgs(elem *ntree, elem *dtree, elem vars, elem vals)
{
	elem cn, cd;

#if 0
	*ntree=Namespace3_List2Vec(*ntree);
	*dtree=Namespace3_List2Vec(*dtree);

	cn=Namespace3_List2Vec(vars);
	cd=Namespace3_List2Vec(vals);

	cn=CONS(cn, *ntree);
	cd=CONS(cd, *dtree);

	cn=Namespace3_List2Vec(cn);
	cd=Namespace3_List2Vec(cd);

	*ntree=cn;
	*dtree=cd;
#else
	*ntree=CONS(vars, *ntree);
	*dtree=CONS(vals, *dtree);
#endif

	return(MISC_NULL);
}

elem Namespace3_Lookup(elem ntree, elem dtree, elem sym)
{
	elem t, t2;
	int i, li;

	if(ELEM_CONSP(ntree))
		return(Namespace2_Lookup(ntree, dtree, sym));

	li=VECTOR_LEN(ntree);

	for(i=0; i<li; i++)
	{
		t=VECTOR_REF(ntree, i);
		t2=VECTOR_REF(dtree, i);
		if(ELEM_VECTORP(t))
		{
			t2=Namespace3_Lookup(t, t2, sym);
			if(t2!=MISC_UNDEFINED)return(t2);
		}else if(t==sym)
			return(t2);
	}

	return(MISC_UNDEFINED);
}

elem Namespace3_Assign(elem ntree, elem dtree, elem sym, elem value)
{
	elem t, t2;
	int i, li;

	if(ELEM_CONSP(ntree))
		return(Namespace2_Assign(ntree, dtree, sym, value));

	li=VECTOR_LEN(ntree);

	for(i=0; i<li; i++)
	{
		t=VECTOR_REF(ntree, i);
		t2=VECTOR_REF(dtree, i);
		if(ELEM_VECTORP(t))
		{
			t2=Namespace3_Assign(t, t2, sym, value);
			if(t2!=MISC_UNDEFINED)return(t2);
		}else if(t==sym)
		{
			VECTOR_SET(dtree, i, value);
			return(t2);
		}
	}
	return(MISC_UNDEFINED);
}

elem Namespace3_Trace(elem ntree, elem dtree, elem last, elem sym)
{
	elem t, t2;
	int i, l;

	if(ELEM_CONSP(ntree))
		return(Namespace2_Trace(ntree, dtree, last, sym));

	if(last!=MISC_EOL)
	{
		i=TOINT(CAR(last));
		t=VECTOR_REF(ntree, i);
		t2=VECTOR_REF(dtree, i);

		t=Namespace3_Trace(t, t2, CDR(last), sym);
		if(t!=MISC_UNDEFINED)return(CONS(CAR(last), t));

//		return(MISC_UNDEFINED);
	}else i=0;

	l=VECTOR_LEN(ntree);

	for(; i<l; i++)
	{
		t=VECTOR_REF(ntree, i);
		t2=VECTOR_REF(dtree, i);
		if(ELEM_VECTORP(t))
		{
			t2=Namespace3_Trace(t, t2, MISC_EOL, sym);
			if(t2!=MISC_UNDEFINED)
				return(CONS(FIXNUM(i), t2));
		}else if(t==sym)
		{
			t=CONS(FIXNUM(i), MISC_EOL);
			return(t);
		}
	}
	return(MISC_UNDEFINED);
}

elem Namespace3_RetrieveTrace(elem ntree, elem dtree, elem last)
{
	elem t, t2;
	int i, li;

	if(ELEM_CONSP(ntree))
		return(Namespace2_RetrieveTrace(ntree, dtree, last));

	if(!ELEM_CONSP(last))
		sa_fatal("Namespace3_RetrieveTrace: bad trace\n");

	i=TOINT(CAR(last));
	t=VECTOR_REF(ntree, i);
	t2=VECTOR_REF(dtree, i);

	if(CDR(last)!=MISC_EOL)
	{
		t2=Namespace3_RetrieveTrace(t, t2, CDR(last));
		return(t2);
	}

	return(t2);
}

elem Namespace3_AssignTrace(elem ntree, elem dtree, elem last, elem value)
{
	elem t, t2;
	int i, li;

	if(ELEM_CONSP(ntree))
		return(Namespace2_AssignTrace(ntree, dtree, last, value));

	if(!ELEM_CONSP(last))
		sa_fatal("Namespace3_AssignTrace: bad trace\n");

	i=TOINT(CAR(last));
	t=VECTOR_REF(ntree, i);
	t2=VECTOR_REF(dtree, i);

	if(CDR(last)!=MISC_EOL)
	{
		t2=Namespace3_AssignTrace(t, t2, CDR(last), value);
		return(t2);
	}

	VECTOR_SET(dtree, i, value);
	return(t2);
}
