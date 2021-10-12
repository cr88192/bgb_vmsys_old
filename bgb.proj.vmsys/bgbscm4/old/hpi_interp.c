#include <scmcc.h>

elem form_return, form_apply, form_halt;

elem HpiInterp_RetrieveValue(elem pos, elem binds)
{
	int y, x;
	int i;
	elem cur;

	y=(pos>>20)&4095;
	x=(pos>>8)&4095;
	cur=binds;

	for(i=0; i<y; i++)cur=CDR(cur);
	cur=CAR(cur);
	for(i=0; i<x; i++)cur=CDR(cur);
	return(CAR(cur));
}

elem HpiInterp_SetValue(elem pos, elem binds, elem val)
{
	int y, x;
	int i;
	elem cur;

	y=(pos>>20)&4095;
	x=(pos>>8)&4095;
	cur=binds;

	for(i=0; i<y; i++)cur=CDR(cur);
	cur=CAR(cur);
	for(i=0; i<x; i++)cur=CDR(cur);
	return(TyFcn_SetCar(cur, val));
}

elem HpiInterp_RetrieveValueM(elem pos, elem binds)
{
	int y, x;
	int i;
	elem cur;

	y=(pos>>20)&4095;
	x=(pos>>8)&4095;
	cur=binds;

	for(i=0; i<y; i++)cur=CDR(cur);
	cur=CAR(cur);
	for(i=0; i<x; i++)cur=CDR(cur);
	return(TyFcn_CarM(cur));
}

elem HpiInterp_CreateClosure(elem env, elem binds, elem body)
{
	elem *buf;
	int l;

	if(binds!=MISC_EOL)
	{
		l=ELEM_TOFIXNUM(TyFcn_ListLength(CAR(binds)));
		if(TyFcn_ListGetEnd(CAR(binds))!=MISC_EOL)l|=32;
	}
	buf=sa_alloc(4*ELEM_SZ);
	buf[0]=OBJECT_CLOSURE|(l<<8);
	buf[1]=env;
	buf[2]=body;
	buf[3]=binds;

	return(ELEM_FROMOBJECT(buf));
}

elem HpiInterp_Fold(elem rp, int c)
{
	elem cur;
	int i;

	if(TyFcn_ListLength(rp)<c)
	{
		sa_error("too few arguments.\n");
		return(MISC_NULL);
	}
	cur=rp;
	for(i=0; i<(c-1); i++)cur=CDR(cur);
	TyFcn_SetCdr(cur, CONS(CDR(cur), MISC_EOL));
	return(rp);
}

int HpiInterp_Run2(elem ip, elem ax, elem sp, elem ep, elem rp, elem dep)
{
	elem op, ins, t, cur, lst;

/*	sp=MISC_EOL;
	ip=form;
	ep=MISC_EOL;
	rp=MISC_EOL; */

	while(ip!=MISC_EOL)
	{
		ins=CAR(ip);
		op=CAR(ins);
		if(op==SYM("halt"))
		{
			return(ax);
		}else if(op==SYM("refer"))
		{
			t=CADR(ins);
			if(ELEM_SYMDEFP(t))ax=TyFcn_SymdefData(t);
				else ax=HpiInterp_RetrieveValue(t, ep);
		}else if(op==SYM("assign"))
		{
			t=CADR(ins);
			if(ELEM_SYMDEFP(t))TyFcn_SetSymdefData(t, ax);
				else HpiInterp_SetValue(t, ep, ax);
		}else if(op==SYM("locative"))
		{
			t=CADR(ins);
			if(ELEM_SYMDEFP(t))ax=TyFcn_SymdefDataM(t);
				else ax=HpiInterp_RetrieveValueM(t, ep);
		}else if(op==SYM("close"))
		{
			ax=HpiInterp_CreateClosure(ep, CADR(ins), CADDR(ins));
		}else if(op==SYM("frame"))
		{
			sp=CONS(CDR(ip), CONS(rp, CONS(ep, sp)));
			rp=MISC_EOL;
			ip=CADR(ins);
			continue;
		}else if(op==SYM("apply"))
		{
			if(ELEM_FUNCTIONP(ax))
			{
				ax=TyMisc_EvalSpecial(ax, rp);
				ip=form_return;
			}else if(ELEM_CLOSUREP(ax))
			{
				t=TyFcn_ObjPeekElem(ax, ELEM_FROMFIXNUM(0));
				if(t&(1<<13))rp=HpiInterp_Fold(rp, (t>>8)&31);
				ep=TyFcn_ObjPeekElem(ax, ELEM_FROMFIXNUM(1));
				ep=CONS(rp, ep);
				ip=TyFcn_ObjPeekElem(ax, ELEM_FROMFIXNUM(2));
				rp=MISC_EOL;
			}else
			{
				sa_error("apply with invalid object.\n");
				return(MISC_NULL);
			}
			continue;
		}else if(op==SYM("return"))
		{
			ip=CAR(sp);
			sp=CDR(sp);

			rp=CAR(sp);
			sp=CDR(sp);

			ep=CAR(sp);
			sp=CDR(sp);

			continue;
		}else if(op==SYM("argument"))
		{
			rp=CONS(ax, rp);
		}else if(op==SYM("constant"))
		{
			ax=CADR(ins);
		}else if(op==SYM("bind"))
		{
			TyFcn_SetCar(ep, CONS(ax, CAR(ep)));
		}else if(op==SYM("bind-args"))
		{
			ep=CONS(rp, ep);
			rp=MISC_EOL;
		}else if(op==SYM("conti"))
		{
			t=CONS(CONS(SYM("nuate"), CONS(sp, CONS(ELEM_FROMFRAME(0,0), MISC_EOL))), MISC_EOL);
			ax=HpiInterp_CreateClosure(ep, MISC_EOL, t);
		}else if(op==SYM("nuate"))
		{
			ax=HpiInterp_RetrieveValue(CADDR(ins), ep);
			sp=CADR(ins);
			ip=form_return;
			continue;
		}else if(op==SYM("test"))
		{
			if(ax==MISC_TRUE)ip=CADR(ins);
				else ip=CADDR(ins);
			continue;
		}else if(op==SYM("qq"))
		{
			cur=CADR(ins);
			lst=MISC_EOL;
			while(cur!=MISC_EOL)
			{
				if(ELEM_CONSP(CAR(cur)))
				{
					if(CAR(CAR(cur))==SYM("#uqf"))
					{
//						TyFcn_DumpElem(CDR(CAR(cur)));
//						sa_print("\n");
						t=HpiInterp_Run2(CDR(CAR(cur)), ax, sp, ep, MISC_EOL, dep);
						lst=CONS(t, lst);
					}else if(CAR(CAR(cur))==SYM("#uqs"))
					{
						t=HpiInterp_Run2(CDR(CAR(cur)), ax, sp, ep, MISC_EOL, dep);
						t=TyFcn_NReverse(t);
						lst=TyFcn_NAppend(t, lst);
					}else lst=CONS(CAR(cur), lst);
				}else lst=CONS(CAR(cur), lst);
				cur=CDR(cur);
			}
			ax=TyFcn_NReverse(lst);
		}
		ip=CDR(ip);
	}
	sa_error("HpiInterp_Run: ran off end of op-stream.\n");
	return(MISC_UNDEFINED);
}

int HpiInterp_Run(elem form)
{
	return(HpiInterp_Run2(form, MISC_EOL, MISC_EOL, MISC_EOL, MISC_EOL, MISC_EOL));
}

int HpiInterp_Init()
{
	MMGC_AddRoot(&form_apply);
	MMGC_AddRoot(&form_return);
	MMGC_AddRoot(&form_halt);

	form_return=CONS(CONS(SYM("return"), MISC_EOL), MISC_EOL);
	form_apply=CONS(CONS(SYM("apply"), MISC_EOL), MISC_EOL);
	form_halt=CONS(CONS(SYM("halt"), MISC_EOL), MISC_EOL);
}
