#include <scmcc.h>

elem Namespace2_Define(elem *ntree, elem *dtree, elem sym, elem val)
{
	*ntree=CONS(sym, *ntree);
	*dtree=CONS(val, *dtree);
}

elem Namespace2_Lookup(elem ntree, elem dtree, elem sym)
{
	elem cur1, cur2, t;
	cur1=ntree;
	cur2=dtree;

	if(ELEM_VECTORP(ntree))
		return(Namespace3_Lookup(ntree, dtree, sym));

//	sa_print("[");
	while(ELEM_CONSP(cur1))
	{
		if(ELEM_CONSP(CAR(cur1)))
		{
			t=Namespace2_Lookup(CAR(cur1), CAR(cur2), sym);
			if(t!=MISC_UNDEFINED)return(t);
		}else if(ELEM_TYPEXP(CAR(cur1)))
		{
			TypeX_Apply(CAR(cur1), CONS(sym, MISC_EOL));
		}else if(CAR(cur1)==sym)return(CAR(cur2));
//		sa_print("failed match \"%s\"(%08X) \"%s\"(%08X)\n", ELEM_TOSTRING(CAR(cur1)), CAR(cur1), ELEM_TOSTRING(sym), sym);
		cur1=CDR(cur1);
		cur2=CDR(cur2);
//		sa_print(".");
	}
//	sa_print("]");
	if(cur1==sym)return(cur2);

	return(MISC_UNDEFINED);
}

elem Namespace2_Assign(elem ntree, elem dtree, elem sym, elem value)
{
	elem cur1, cur2, t;

	if(ELEM_VECTORP(ntree))
		return(Namespace3_Assign(ntree, dtree, sym, value));

	cur1=ntree;
	cur2=dtree;
	t=MISC_EOL;

	while(ELEM_CONSP(cur1))
	{
		if(ELEM_CONSP(CAR(cur1)))
		{
			t=Namespace2_Assign(CAR(cur1), CAR(cur2), sym, value);
			if(t!=MISC_UNDEFINED)return(t);
		}else if(ELEM_TYPEXP(CAR(cur1)))
		{
			TypeX_Apply(CAR(cur1), CONS(sym, CONS(value, MISC_EOL)));
		}else if(CAR(cur1)==sym)
		{
//			sa_print("Assign: bound var '%s'\n", ELEM_TOSYMBOL(sym));
			TyFcn_SetCar(cur2, value);
			return(CAR(cur2));
		}
		cur1=CDR(cur1);
		t=cur2;
		cur2=CDR(cur2);
	}
	if(cur1==sym)
	{
		TyFcn_SetCdr(t, value);
		return(value);
	}
//	sa_print("Assign: unbound var '%s'\n", ELEM_TOSYMBOL(sym));
	return(MISC_UNDEFINED);
}

elem Namespace2_Trace(elem ntree, elem dtree, elem last, elem sym)
{
	elem cur1, cur2, t;
	int i, j;

	if(ELEM_VECTORP(ntree))
		return(Namespace3_Trace(ntree, dtree, last, sym));

	cur1=ntree;
	cur2=dtree;

	i=0;
	if(last!=MISC_EOL)
	{
		j=ELEM_TOFIXNUM(CAR(last));

		while(cur1!=MISC_EOL && i<j)
		{
			cur1=CDR(cur1);
			cur2=CDR(cur2);
			i++;
		}

		if(ELEM_CONSP(CDR(last)))
		{
			t=Namespace2_Trace(CAR(cur1), CAR(cur2), CDR(last), sym);
			if(t!=MISC_UNDEFINED)return(CONS(CAR(last), t));
		}
	}

	while(ELEM_CONSP(cur1))
	{
		if(ELEM_CONSP(CAR(cur1)))
		{
			if(CAR(cur1)==ntree)
			{
				sa_error("trace: circular 0.\n");
				return(MISC_UNDEFINED);
			}
			t=Namespace2_Trace(CAR(cur1), CAR(cur2), MISC_EOL, sym);
			if(t!=MISC_UNDEFINED)return(CONS(ELEM_FROMFIXNUM(i), t));
		}else if(ELEM_TYPEXP(CAR(cur1)))
		{
			t=TypeX_Apply(CAR(cur1), CONS(sym, MISC_EOL));
			if(t!=MISC_UNDEFINED)
				return(CONS(ELEM_FROMFIXNUM(i), CONS(sym, MISC_EOL)));
		}else if(CAR(cur1)==sym)
			return(CONS(ELEM_FROMFIXNUM(i), MISC_EOL));
		cur1=CDR(cur1);
		cur2=CDR(cur2);
		i++;
	}
	if(cur1==sym)return(CONS(ELEM_FROMFIXNUM(i), MISC_EOL));

	return(MISC_UNDEFINED);
}

elem Namespace2_RetrieveTrace(elem ntree, elem dtree, elem last)
{
	elem cur1, cur2, t;
	int i, j;

	if(ELEM_VECTORP(ntree))
		return(Namespace3_RetrieveTrace(ntree, dtree, last));

	cur1=ntree;
	cur2=dtree;

	i=0;
	if(last!=MISC_EOL)
	{
		j=ELEM_TOFIXNUM(CAR(last));

		while(ELEM_CONSP(cur1) && i<j)
		{
			cur1=CDRF(cur1);
			cur2=CDRF(cur2);
			i++;
		}

		if(ELEM_CONSP(CDR(last)))
		{
			if(!ELEM_CONSP(CAR(cur1)) || !ELEM_CONSP(CAR(cur2)))
			{
				sa_print("RetrieveTrace: trace/tree mismatch.\n");
				return(MISC_UNDEFINED);
			}
			t=Namespace2_RetrieveTrace(CAR(cur1), CAR(cur2), CDR(last));
			if(t!=MISC_UNDEFINED)return(t);
		}else
		{
//			sa_print("traced '");
//			TyFcn_DumpElem(CAR(cur1));
//			sa_print("', containing '");
//			TyFcn_DumpElem(CAR(cur2));
//			sa_print("'\n");
			if(!ELEM_CONSP(cur1))
			{
				if(ELEM_TYPEXP(cur1))
				{
					t=TypeX_Apply(cur1, CONS(CADR(last), MISC_EOL));
					return(t);
				}
				t=cur2;
				if(t==MISC_UNDEFINED)t=MISC_NULL;
				return(t);
			}
			if(!ELEM_CONSP(cur2))
			{
				sa_error("RetrieveTrace: mismatch at \"%s\"\n", ELEM_TOSYMBOL(CAR(cur1)));
				return(cur2);
			}
			t=CAR(cur2);
			if(t==MISC_UNDEFINED)t=MISC_NULL;
			return(t);
		}
	}

	sa_print("RetrieveTrace failed.\n");

	sa_abort();
	return(MISC_UNDEFINED);
}

elem Namespace2_AssignTrace(elem ntree, elem dtree, elem last, elem value)
{
	elem cur1, cur2, t;
	int i, j;

	if(ELEM_VECTORP(ntree))
		return(Namespace3_AssignTrace(ntree, dtree, last, value));

	cur1=ntree;
	cur2=dtree;

	i=0;
	if(last!=MISC_EOL)
	{
		j=ELEM_TOFIXNUM(CAR(last));
		t=MISC_EOL;

		while(ELEM_CONSP(cur1) && i<j)
		{
			cur1=CDRF(cur1);
			t=cur2;
			cur2=CDRF(cur2);
			i++;
		}

		if(ELEM_CONSP(CDR(last)))
		{
			if(!ELEM_CONSP(CAR(cur1)) || !ELEM_CONSP(CAR(cur2)))
			{
				sa_print("AssignTrace: trace/tree mismatch.\n");
				return(MISC_UNDEFINED);
			}
			t=Namespace2_AssignTrace(CAR(cur1), CAR(cur2), CDR(last), value);
			if(t!=MISC_UNDEFINED)return(t);
		}else
		{
			if(ELEM_CONSP(cur1))TyFcn_SetCar(cur2, value);
				else if(ELEM_TYPEXP(cur1))
			{
				t=TypeX_Apply(cur1, CONS(CADR(last), CONS(value, MISC_EOL)));
				return(t);
			}else TyFcn_SetCdr(t, value);
			return(value);
		}
	}
	return(MISC_UNDEFINED);
}

elem Namespace2_LocativeTrace(elem ntree, elem dtree, elem last)
{
	elem cur1, cur2, l1, l2, t;
	int i, j;

	cur1=ntree;
	cur2=dtree;
	l1=MISC_EOL;
	l2=MISC_EOL;

	i=0;
	if(last!=MISC_EOL)
	{
		j=ELEM_TOFIXNUM(CAR(last));

		while(ELEM_CONSP(cur1) && i<j)
		{
			l1=cur1;
			l2=cur2;
			cur1=CDR(cur1);
			cur2=CDR(cur2);
			i++;
		}

		if(ELEM_CONSP(CDR(last)))
		{
			if(!ELEM_CONSP(CAR(cur1)) || !ELEM_CONSP(CAR(cur2)))
			{
				sa_print("LocativeTrace: trace/tree mismatch.\n");
				return(MISC_UNDEFINED);
			}
			t=Namespace2_LocativeTrace(CAR(cur1), CAR(cur2), CDR(last));
			if(t!=MISC_UNDEFINED)return(t);
		}else
		{
//			sa_print("traced '");
//			TyFcn_DumpElem(CAR(cur1));
//			sa_print("', containing '");
//			TyFcn_DumpElem(CAR(cur2));
//			sa_print("'\n");
			if(!ELEM_CONSP(cur1))return(TyFcn_CdrM(l2));
			return(TyFcn_CarM(cur2));
		}
	}

	sa_print("RetrieveTrace failed.\n");
	return(MISC_UNDEFINED);
}
