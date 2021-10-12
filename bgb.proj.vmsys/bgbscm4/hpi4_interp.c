#include <scmcc.h>
#include <interpctx.h>

elem opcodes_n, opcodes_d;
extern elem form_return, form_apply, form_halt;

static elem sym_apply=MISC_NULL;
static elem sym_argument=MISC_NULL;
static elem sym_halt=MISC_NULL;
static elem sym_block=MISC_NULL;
static elem sym_noints=MISC_NULL;
static elem sym_nuate=MISC_NULL;
static elem sym_refer=MISC_NULL;

InterpCtx *interp_context; //used to pass context to called functions
extern elem interp_cur_ctx;

elem HpiInterp_Fold(elem rp, elem args);

int interp_totalusloop;
int interp_totalopsloop;
static elem sym_self=MISC_NULL;

elem interp_freeframes;

elem HpiOp_Apply(InterpCtx *ctx)
{
	elem t, t2, ep_n, ep_d;
	int x;

	SYMG(sym_self, "self");

	ctx->rax=MISC_NULL;

	//allow typex objs to be applied, not like apply isn't a hack anyways...
	if(ELEM_TYPEXP(ctx->ax))
	{
		ctx->rp=CONS(ctx->ax, ctx->rp);
		ctx->ax=TypeX_Func(ctx->ax);
		if(ctx->ax==MISC_UNDEFINED)
		{
			sa_fatal("apply: typex with invalid apply handler.\n");
			return(MISC_UNDEFINED);
		}
	}

	if(ELEM_FUNCTIONP(ctx->ax))
	{
		interp_context=ctx;
		interp_cur_ctx=ELEM_FROMOBJECT(ctx);

		x=ctx->rp;
		ctx->rp=MISC_EOL;

		HpiOp_Return(ctx);

		ctx->ax=TyMisc_EvalSpecial(ctx->ax, x);

		TyFcn_UnConsList(x);

		return(MISC_NULL);
	}else if(ELEM_CLOSUREP(ctx->ax))
	{
		ctx->ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));

		t=CAR(ctx->ep_n);

		ctx->ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(ctx->rp, ctx->ep_d);

		ctx->ip=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(2));

		ctx->sep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(3));
		ctx->sep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(4));

		if(ctx->lrp!=MISC_EOL)TyFcn_UnCons(ctx->lrp);
		ctx->lrp=ctx->rp;
		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_ENVOBJP(ctx->ax))
	{
		ctx->dyn_n=CONS(sym_self, ctx->dyn_n);
		ctx->dyn_d=CONS(ctx->ax, ctx->dyn_d);

		ctx->ip=MISC_EOL;

		TyObj_Dispatch(ctx);

		return(MISC_NULL);
	}else if(ELEM_ENVP(ctx->ax))
	{
		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));

		if(CDR(ctx->rp)==MISC_EOL)
		{
			t=Namespace3_Trace(ep_n, ep_d, MISC_EOL, CAR(ctx->rp));
			ctx->ax=Namespace3_RetrieveTrace(ep_n, ep_d, t);
			if(ELEM_CONSTRAINTP(ctx->ax))
				ctx->ax=HpiCmd_EvalConstraint(ctx);
//			ctx->rax=Namespace3_LocativeTrace(ep_n, ep_d, t);
		}else
		{
			t=ctx->ax;
			t2=Namespace3_Trace(ep_n, ep_d, MISC_EOL, CAR(ctx->rp));

			if(t2==MISC_UNDEFINED)
			{
				ep_n=CONS(CONS(CAR(ctx->rp), CAR(ep_n)), CDR(ep_n));
				ep_d=CONS(CONS(CADR(ctx->rp), CAR(ep_d)), CDR(ep_d));
				TyFcn_VectorSet(t, ELEM_FROMFIXNUM(0), ep_n);
				TyFcn_VectorSet(t, ELEM_FROMFIXNUM(1), ep_d);
			}else
			{
				ctx->ax=Namespace3_RetrieveTrace(ep_n, ep_d, t2);
				if(ELEM_CONSTRAINTP(ctx->ax) && !ELEM_CONSTRAINTP(CADR(ctx->rp)))
				{
					t=VECTOR_REF(ctx->ax, 6);
					HpiCmd_InvalidateConstraint(ctx->ax);
					VECTOR_SET(ctx->ax, 6, CADR(ctx->rp));
					ctx->ax=t;
				}else
				{
					if(ELEM_CONSTRAINTP(ctx->ax))
						HpiCmd_InvalidateConstraint(ctx->ax);
					ctx->ax=Namespace3_AssignTrace(ep_n, ep_d, t, CADR(ctx->rp));
				}
			}
		}
		ctx->ip=form_return;
		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_CONTEXTP(ctx->ax))
	{
		Interp_SendThread(ctx->ax, ctx->rp);
		ctx->ax=MISC_NULL;
		ctx->ip=form_return;
		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_VECTORP(ctx->ax)) /* placed after other "vector" types... */
	{
		if(ctx->rp==MISC_EOL)
		{
			sa_error("apply with vector, no args...\n");
			ctx->ax=MISC_UNDEFINED;
			ctx->ip=form_return;
			ctx->rp=MISC_EOL;
			return(MISC_UNDEFINED);
		}
		if(CDR(ctx->rp)==MISC_EOL)
		{
			t=TyFcn_VectorRef(ctx->ax, CAR(ctx->rp));
			ctx->rax=TyFcn_VectorRefM(ctx->ax, CAR(ctx->rp));
			ctx->ax=t;
		}else ctx->ax=TyFcn_VectorSet(ctx->ax, CAR(ctx->rp), CADR(ctx->rp));

		ctx->ip=form_return;
		ctx->rp=MISC_EOL;
		return(MISC_NULL);
	}else
	{
		sa_error("apply with invalid object: '");
		TyFcn_DumpElem(ctx->ax);
		sa_print("'\n");

		ctx->ax=MISC_UNDEFINED;
		ctx->ip=form_return;

		sa_abort();

		return(MISC_UNDEFINED);
	}
	return(MISC_NULL);
}

elem HpiOp_Argument(InterpCtx *ctx)
{
	ctx->rp=CONS(ctx->ax, ctx->rp);
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Assign(InterpCtx *ctx)
{
	elem pos, t;
	pos=CARF(CDRF(CARF(ctx->ip)));
	if(ELEM_SYMBOLP(pos))
	{
		t=Namespace3_Assign(ctx->dyn_n, ctx->dyn_d, pos, ctx->ax);
		if(t==MISC_UNDEFINED)
		{
			sa_error("Assign: unbound var '%s'\n", ELEM_TOSYMBOL(pos));
			ctx->ip=CDRF(ctx->ip);
			return(MISC_UNDEFINED);
		}
	}else if(ELEM_CONSP(pos))
	{
		Namespace3_AssignTrace(ctx->ep_n, ctx->ep_d, pos, ctx->ax);
	}
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiCmd_InvalidateConstraint(elem c)
{
	elem cur, l, t, lst;

	t=VECTOR_REF(c, 6);
	if(t==MISC_UNDEFINED)return(MISC_NULL);
	VECTOR_SET(c, 6, MISC_UNDEFINED);

//	sa_print("invalidate constraint %X\n", c);

	lst=VECTOR_REF(c, 7);

	l=MISC_EOL;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		if(!ELEM_CONSTRAINTP(CAR(cur)))
		{
			if(l!=MISC_EOL)
				TyFcn_SetCdr(l, CDR(cur));
				else lst=CDR(cur);
			cur=CDR(cur);
			continue;
		}

		HpiCmd_InvalidateConstraint(CAR(cur));

		l=cur;
		cur=CDR(cur);
	}
	
	VECTOR_SET(c, 7, lst);
	return(MISC_NULL);
}

elem HpiOp_Assign2(InterpCtx *ctx)
{
	elem pos, t;
	pos=CARF(CDRF(CARF(ctx->ip)));
	if(ELEM_SYMBOLP(pos))
	{
		t=Namespace3_Assign(ctx->dyn_n, ctx->dyn_d, pos, ctx->ax);
		if(t==MISC_UNDEFINED)
		{
			sa_error("Assign: unbound var '%s'\n", ELEM_TOSYMBOL(pos));
			ctx->ip=CDRF(ctx->ip);
			return(MISC_UNDEFINED);
		}
	}else if(ELEM_CONSP(pos))
	{
		t=Namespace3_RetrieveTrace(ctx->ep_n, ctx->ep_d, pos);
		if(ELEM_CONSTRAINTP(t) && !ELEM_CONSTRAINTP(ctx->ax))
		{
			HpiCmd_InvalidateConstraint(t);
			VECTOR_SET(t, 6, ctx->ax);
		}else
		{
			if(ELEM_CONSTRAINTP(t))
				HpiCmd_InvalidateConstraint(t);
			Namespace3_AssignTrace(ctx->ep_n, ctx->ep_d, pos, ctx->ax);
		}
	}
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Bind(InterpCtx *ctx)
{
	elem t, t2;
	elem cn, cd;

	t=CARF(CDRF(CARF(ctx->ip)));
	t2=ctx->ax;

#if 0
	ctx->ep_n=CONS(CONS(t,	CAR(ctx->ep_n)), CDR(ctx->ep_n));
	ctx->ep_d=CONS(CONS(t2,	CAR(ctx->ep_d)), CDR(ctx->ep_d));
#else
	Namespace3_Bind(&ctx->ep_n, &ctx->ep_d, t, t2);
#endif

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_BindArgs(InterpCtx *ctx)
{
	elem t, t2;

	t=CAR(CDR(CAR(ctx->ip)));
	t2=ctx->rp;

#if 0
	ctx->ep_n=CONS(t, ctx->ep_n);
	ctx->ep_d=CONS(t2, ctx->ep_d);
#endif
	Namespace3_BindArgs(&ctx->ep_n, &ctx->ep_d, t, t2);

	ctx->rp=MISC_EOL;
	ctx->ip=CDRF(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_BindVar(InterpCtx *ctx)
{
	elem t, t2;
	elem cn, cd;

	t=CARF(CDRF(CARF(ctx->ip)));
	t2=ctx->ax;

#if 1
	ctx->dyn_n=CONS(CONS(t, CAR(ctx->dyn_n)), CDR(ctx->dyn_n));
	ctx->dyn_d=CONS(CONS(t2, CAR(ctx->dyn_d)), CDR(ctx->dyn_d));
#endif

//	Namespace3_Bind(&ctx->dyn_n, &ctx->dyn_d, t, t2);

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_BindArgsVar(InterpCtx *ctx)
{
	elem t, t2;

	t=CAR(CDR(CAR(ctx->ip)));
	t2=ctx->rp;

#if 1
	ctx->dyn_n=CONS(t, ctx->dyn_n);
	ctx->dyn_d=CONS(t2, ctx->dyn_d);
#endif

//	Namespace3_BindArgs(&ctx->dyn_n, &ctx->dyn_d, t, t2);

	ctx->rp=MISC_EOL;
	ctx->ip=CDRF(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_Block(InterpCtx *ctx)
{
	ctx->vax=SYMG(sym_block, "block");
	ctx->ip=CDRF(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_Close(InterpCtx *ctx)
{
	elem t, x;

	x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(6), ELEM_FROMFIXNUM(VECTOR_CLOSURE));

	t=CADR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), CONS(t, ctx->ep_n));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ctx->ep_d);

	t=CADDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(3), ctx->sep_n);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(4), ctx->sep_d);

	t=CADDDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(5), t);

	ctx->ax=x;

	ctx->flags|=CTX_CLOSE;

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Constant(InterpCtx *ctx)
{
	ctx->ax=CARF(CDRF(CARF(ctx->ip)));
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Constraint(InterpCtx *ctx)
{
	elem t, x;

	x=VECTOR_NEWT(8, VECTOR_CONST);

	VECTOR_SET(x, 0, ctx->ep_n);
	VECTOR_SET(x, 1, ctx->ep_d);
	VECTOR_SET(x, 2, ctx->sep_n);
	VECTOR_SET(x, 3, ctx->sep_d);

	t=CADR(CAR(ctx->ip));
	VECTOR_SET(x, 4, t);

	t=CADDR(CAR(ctx->ip));
	VECTOR_SET(x, 5, t);

	VECTOR_SET(x, 6, MISC_UNDEFINED);
	VECTOR_SET(x, 7, MISC_EOL);

	ctx->ax=x;

	ctx->flags|=CTX_CLOSE;

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Conti(InterpCtx *ctx)
{
	elem t, x, tmp;

	tmp=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(3), ELEM_FROMFIXNUM(VECTOR_CLOSURE));

	t=CONS(SYMG(sym_nuate, "nuate"), CONS(ctx->sp, MISC_EOL));
	x=CONS(t, MISC_EOL);
	t=CONS(SYMG(sym_refer, "refer"), CONS(CONS(ELEM_FROMFIXNUM(0), CONS(ELEM_FROMFIXNUM(0), MISC_EOL)), MISC_EOL));
	x=CONS(t, x);

	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(0), CONS(t, ctx->ep_n));
	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(1), ctx->ep_d);
	TyFcn_VectorSet(tmp, ELEM_FROMFIXNUM(2), x);

	ctx->ax=tmp;
	ctx->flags|=CTX_CONTI|CTX_CLOSE;

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_CurrentEnv(InterpCtx *ctx)
{
	ctx->ax=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(4), ELEM_FROMFIXNUM(VECTOR_ENV));

	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(0), ctx->ep_n);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(1), ctx->ep_d);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(2), ctx->sep_n);
	TyFcn_VectorSet(ctx->ax, ELEM_FROMFIXNUM(3), ctx->sep_d);

	ctx->flags|=CTX_CLOSE;

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiCmd_NewFrame(InterpCtx *ctx)
{
	elem x, t;
	elem *s;

	if(interp_freeframes!=MISC_EOL)
//	if(0)
	{
		x=interp_freeframes;
		interp_freeframes=CDRF(x);

//		TyFcn_SetCdr(x, ctx->sp);
		CDRF(x)=ctx->sp;
		ctx->sp=x;

		t=CARF(x);
		s=TyFcn_VectorBody(t);

//		ctx->sp=CONS(t, ctx->sp);
//		interp_freeframes=CDRF(x);
	}else
	{
		t=VECTOR_NEW(10);
		s=TyFcn_VectorBody(t);
		ctx->sp=CONS(t, ctx->sp);
	}

	s[0]=ctx->ep_n;
	s[1]=ctx->ep_d;
	s[2]=ctx->dyn_n;
	s[3]=ctx->dyn_d;
	s[4]=ctx->sep_n;
	s[5]=ctx->sep_d;
	s[6]=ctx->rp;
	s[7]=ctx->lrp;
	s[8]=CDRF(ctx->ip);
	s[9]=ctx->flags;

	ctx->flags=ctx->flags&(~(CTX_CONTI|CTX_CLOSE));
	ctx->lrp=MISC_EOL;

#if 0
	x=ctx->sp;
	x=CONS(ctx->ep_n, x);
	x=CONS(ctx->ep_d, x);
	x=CONS(ctx->dyn_n, x);
	x=CONS(ctx->dyn_d, x);
	x=CONS(ctx->sep_n, x);
	x=CONS(ctx->sep_d, x);
	x=CONS(ctx->rp, x);
	x=CONS(CDR(ctx->ip), x);
	ctx->sp=x;
#endif

	return(MISC_NULL);
}

elem HpiOp_Frame(InterpCtx *ctx)
{
	elem x;

/*	x=ctx->sp;
	x=CONS(ctx->ep_n, x);
	x=CONS(ctx->ep_d, x);
	x=CONS(ctx->dyn_n, x);
	x=CONS(ctx->dyn_d, x);
	x=CONS(ctx->sep_n, x);
	x=CONS(ctx->sep_d, x);
	x=CONS(ctx->rp, x);
	x=CONS(CDR(ctx->ip), x);
	ctx->sp=x; */

	HpiCmd_NewFrame(ctx);

	ctx->ip=CARF(CDRF(CARF(ctx->ip)));
	ctx->rp=MISC_EOL;

	return(MISC_NULL);
}

elem HpiOp_Func(InterpCtx *ctx)
{
	elem t, x;

	x=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(6), ELEM_FROMFIXNUM(VECTOR_MINIFRAG));

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), ctx->ep_n);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ctx->ep_d);

	t=CDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(2), t);

	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(3), ctx->sep_n);
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(4), ctx->sep_d);

	t=CDR(CAR(ctx->ip));
	TyFcn_VectorSet(x, ELEM_FROMFIXNUM(5), t);

	ctx->rp=CONS(x, ctx->rp);

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Halt(InterpCtx *ctx)
{
	ctx->ip=MISC_TRUE;
	ctx->vax=SYMG(sym_halt, "halt");

	return(MISC_NULL);
}

elem HpiOp_IntsOff(InterpCtx *ctx)
{
	ctx->vax=SYMG(sym_noints, "no-ints");
	ctx->ip=CDRF(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_IntsOn(InterpCtx *ctx)
{
	if(ctx->vax==SYMG(sym_noints, "no-ints"))ctx->vax=MISC_NULL;
	ctx->ip=CDRF(ctx->ip);

	return(MISC_NULL);
}

elem HpiOp_Nuate(InterpCtx *ctx)
{
	ctx->sp=CAR(CDR(CAR(ctx->ip)));
//	ctx->ip=form_return;
	HpiOp_Return(ctx);

	ctx->flags|=CTX_CONTI|CTX_CLOSE;

	return(MISC_NULL);
}

elem HpiCmd_EvalConstraint(InterpCtx *ctx)
{
	InterpCtx *ctx2;
	elem t, oc;
	static elem c=MISC_EOL;

	if(c!=MISC_EOL)
	{
		if(TyFcn_ObjectInListP(ctx->ax, c)==MISC_TRUE)
		{
			sa_error("recursive constraint %X\n", ctx->ax);
			return(MISC_NULL);
		}

		t=VECTOR_REF(ctx->ax, 7);
		if(TyFcn_ObjectInListP(CAR(c), t)!=MISC_TRUE)
		{
			t=CONS(CAR(c), t);
			VECTOR_SET(ctx->ax, 7, t);
		}
	}

	t=VECTOR_REF(ctx->ax, 6);
	if(t==MISC_UNDEFINED)
	{
//		sa_print("constraint eval %X\n", ctx->ax);
		oc=c;
		c=CONS(ctx->ax, c);

		t=ELEM_FROMOBJECT(ctx);
		t=TyFcn_CopyVector(t);
		ctx2=ELEM_TOOBJECT(t);

		ctx2->ep_n=VECTOR_REF(ctx->ax, 0);
		ctx2->ep_d=VECTOR_REF(ctx->ax, 1);
		ctx2->sep_n=VECTOR_REF(ctx->ax, 2);
		ctx2->sep_d=VECTOR_REF(ctx->ax, 3);

		ctx2->ip=VECTOR_REF(ctx->ax, 4);
		ctx2->ax=MISC_NULL;
		ctx2->sp=MISC_EOL;

		t=HpiInterp_RunLoop(ctx2);
		VECTOR_SET(ctx->ax, 6, t);

		c=oc;
	}
	return(t);
}

elem HpiOp_Refer(InterpCtx *ctx)
{
	elem pos;

	pos=CARF(CDRF(CARF(ctx->ip)));
	ctx->ip=CDRF(ctx->ip);

	if(ELEM_SYMBOLP(pos))
	{
		ctx->ax=Namespace3_Lookup(ctx->dyn_n, ctx->dyn_d, pos);
		if(ctx->ax==MISC_UNDEFINED)
		{
			sa_error("Refer: unbound var '%s'\n", ELEM_TOSTRING(pos));
			return(MISC_UNDEFINED);
		}
	}else if(ELEM_CONSP(pos))
	{
		ctx->ax=Namespace3_RetrieveTrace(ctx->ep_n, ctx->ep_d, pos);
//		ctx->rax=Namespace3_LocativeTrace(ctx->ep_n, ctx->ep_d, pos);

		if(ELEM_CONSTRAINTP(ctx->ax))
			ctx->ax=HpiCmd_EvalConstraint(ctx);
	}else sa_print("refer: bad trace\n");

	return(MISC_NULL);
}

elem HpiOp_ReferSyntax(InterpCtx *ctx)
{
	elem pos;
	pos=CAR(CDR(CAR(ctx->ip)));

	ctx->ax=Namespace3_Lookup(ctx->sep_n, ctx->sep_d, pos);
	if(ctx->ax==MISC_UNDEFINED)
	{
		sa_error("Refer-Syntax: unbound syntax '%s'\n", ELEM_TOSTRING(pos));
		ctx->ip=CDRF(ctx->ip);
		return(MISC_UNDEFINED);
	}

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

#ifndef UCDR
#define UCDR(c) (TyFcn_UnCons(c))
#endif

elem HpiOp_Return(InterpCtx *ctx)
{
	elem x, t;
	elem *s;

#if 0
	x=ctx->sp;

	ctx->ip=CAR(x);
	x=CDR(x);
	if(CAR(x)!=MISC_UNDEFINED)
		ctx->rp=CAR(x);
//		else TyFcn_UnConsList(ctx->rp);
	x=CDR(x);
	ctx->sep_d=CAR(x);
	x=CDR(x);
	ctx->sep_n=CAR(x);
	x=CDR(x);
	ctx->dyn_d=CAR(x);
	x=CDR(x);
	ctx->dyn_n=CAR(x);
	x=CDR(x);
	ctx->ep_d=CAR(x);
	x=CDR(x);
	ctx->ep_n=CAR(x);
	x=CDR(x);

	ctx->sp=x;
#endif

	if(!(ctx->flags&CTX_CLOSE))
		TyFcn_UnConsList(ctx->rp);

	t=CARF(ctx->sp);
	x=CDRF(ctx->sp);
	s=TyFcn_VectorBody(t);

	ctx->ep_n=s[0];
	ctx->ep_d=s[1];
	ctx->dyn_n=s[2];
	ctx->dyn_d=s[3];
	ctx->sep_n=s[4];
	ctx->sep_d=s[5];
	ctx->rp=s[6];
	ctx->lrp=s[7];
	ctx->ip=s[8];

	ctx->flags=s[9]|(ctx->flags&0xffff);

	if(!(ctx->flags&CTX_CONTI))
//	if(1)
	{
//		TyFcn_SetCdr(ctx->sp, interp_freeframes);
		CDRF(ctx->sp)=interp_freeframes;
		interp_freeframes=ctx->sp;

//		interp_freeframes=CONS(t, interp_freeframes);
//		TyFcn_UnCons(ctx->sp);
	}

	ctx->sp=x;

	return(MISC_NULL);
}

elem HpiOp_SetRax(InterpCtx *ctx)
{
	elem t;

	if(ELEM_CONSP(ctx->rax))
	{
		TyMisc_EvalSpecial(CAR(ctx->rax),
			CONS(CAR(ctx->rp), CDR(ctx->rax)));
	}else if(ELEM_LOCATIVEP(ctx->rax))
	{
		ELEM_SETLOCATIVE(ctx->rax, CAR(ctx->rp));
	}else
	{
		sa_error("set-rax: invalid value '");
		TyFcn_DumpElem(ctx->rax);
		sa_print("' in rax.\n");

		ctx->rp=CDRF(ctx->rp);
		ctx->ip=CDRF(ctx->ip);
		return(MISC_UNDEFINED);
	}

	ctx->rp=CDRF(ctx->rp);
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Splice(InterpCtx *ctx)
{
	elem t;

	t=TyFcn_ListCopy(ctx->ax);
	ctx->rp=TyFcn_NAppend(t, ctx->rp);

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiOp_Test(InterpCtx *ctx)
{
	elem tc, fc;
	tc=CARF(CDRF(CARF(ctx->ip)));
	fc=CARF(CDRF(CDRF(CARF(ctx->ip))));

	if(ctx->ax==MISC_TRUE)ctx->ip=tc;
		else ctx->ip=fc;
	return(MISC_NULL);
}

elem HpiOp_Trampoline(InterpCtx *ctx)
{
	ctx->rp=CONS(ELEM_FROMLOCATIVE(ctx), CAR(ctx->ep_d));
	ctx->ax=CADR(CAR(ctx->ip));

	return(HpiOp_Apply(ctx));
}

elem HpiOp_XchgRPAX(InterpCtx *ctx)
{
	elem t;

	t=ctx->ax;
	ctx->ax=ctx->rp;
	ctx->rp=t;

	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}


int hpimisc_dumpops;

elem HpiMisc_DumpOps(InterpCtx *ctx)
{
	hpimisc_dumpops^=1;
	ctx->ip=CDRF(ctx->ip);
	return(MISC_NULL);
}

elem HpiInterp_Fold(elem rp, elem args)
{
	elem cur1, cur2;
	int i;

	if(!ELEM_CONSP(args))return(CONS(rp, MISC_EOL));

	if(TyFcn_ListLength(rp)<TyFcn_ListLength(args))
	{
		sa_error("too few arguments.\n");
		return(MISC_NULL);
	}

	cur1=rp;
	cur2=args;
	while(ELEM_CONSP(cur2))
	{
		cur1=CDR(cur1);
		cur2=CDR(cur2);
	}

	TyFcn_SetCdr(cur1, CONS(CDR(cur1), MISC_EOL));
	return(rp);
}

elem HpiInterp_DefineSpecial(char *name, elem (*func)(), int pc)
{
	opcodes_n=CONS(TyFcn_Symbol(name), opcodes_n);
	opcodes_d=CONS(TyFcn_Function(func, pc), opcodes_d);

	return(MISC_NULL);
}

elem HpiInterp_DefineOpcode(char *name, int op)
{
	opcodes_n=CONS(TyFcn_Symbol(name), opcodes_n);
	opcodes_d=CONS((op<<16)|MISCT_OPCODE, opcodes_d);

	return(MISC_NULL);
}

elem HpiInterp_MiniApply(InterpCtx *ctx, elem op)
{
	elem t, ep_n, ep_d;
	int x;

	SYMG(sym_self, "self");

	ctx->rax=MISC_NULL;

	if(ELEM_FUNCTIONP(op))
	{
		interp_context=ctx;
		interp_cur_ctx=ELEM_FROMOBJECT(ctx);

		ctx->ip=form_return;
		ctx->ax=TyMisc_EvalSpecialI(op, &ctx->rp);
		return(MISC_NULL);
	}else if(ELEM_CLOSUREP(op))
	{
		x=ctx->sp;
		x=CONS(ctx->ep_n, x);
		x=CONS(ctx->ep_d, x);
		x=CONS(ctx->dyn_n, x);
		x=CONS(ctx->dyn_d, x);
		x=CONS(ctx->sep_n, x);
		x=CONS(ctx->sep_d, x);
		x=CONS(ctx->rp, x);
		t=CONS(CONS(SYMG(sym_argument, "argument"), MISC_EOL), CDR(ctx->ip));
		x=CONS(t, x);
		ctx->sp=x;

		ctx->ep_n=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(0));

		t=CAR(ctx->ep_n);

		ctx->ep_d=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(ctx->rp, ctx->ep_d);

		ctx->ip=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(2));

		ctx->sep_n=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(3));
		ctx->sep_d=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(4));

		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_MINIFRAGP(op))
	{
		x=ctx->sp;
		x=CONS(ctx->ep_n, x);
		x=CONS(ctx->ep_d, x);
		x=CONS(ctx->dyn_n, x);
		x=CONS(ctx->dyn_d, x);
		x=CONS(ctx->sep_n, x);
		x=CONS(ctx->sep_d, x);
		x=CONS(MISC_UNDEFINED, x);
		x=CONS(CDR(ctx->ip), x);
		ctx->sp=x;

		ctx->ep_n=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(0));

		t=CAR(ctx->ep_n);

		ctx->ep_d=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(1));
		ctx->ep_d=CONS(ctx->rp, ctx->ep_d);

		ctx->ip=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(2));

		ctx->sep_n=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(3));
		ctx->sep_d=TyFcn_VectorRef(op, ELEM_FROMFIXNUM(4));

//		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else
	{
		ctx->rp=CONS(op, ctx->rp);
		ctx->ip=CDRF(ctx->ip);
		return(MISC_NULL);
	}

	return(MISC_NULL);
}

elem HpiInterp_RunStep(InterpCtx *ctx)
{
	elem op;

//	if(hpimisc_dumpops)
//	{
//		TyFcn_DumpElem(CAR(ctx->ip));
//		sa_print("\n");
//	}

//	sa_print(".");

//	if(ELEM_SYMBOLP(CAAR(ctx->ip)))
	op=CARF(CARF(ctx->ip));
	if(!ELEM_OPCODEP(op))
	{
		op=Namespace3_Lookup(opcodes_n, opcodes_d, CAR(CAR(ctx->ip)));
		if(op==MISC_UNDEFINED)
		{
			sa_print("unknown opcode \"%s\"\n", ELEM_TOSYMBOL(CAR(CAR(ctx->ip))));
			return(MISC_UNDEFINED);
		}
		TyFcn_SetCar(CAR(ctx->ip), op);
	}
//	TyMisc_EvalSpecial(op, CONS((elem)ctx, MISC_EOL));
	switch(op>>16)
	{
	case HPIOP_APPLY:
		HpiOp_Apply(ctx);
		break;
	case HPIOP_ARGUMENT:
		HpiOp_Argument(ctx);
		break;
	case HPIOP_ASSIGN:
		HpiOp_Assign(ctx);
		break;
	case HPIOP_ASSIGN2:
		HpiOp_Assign2(ctx);
		break;
	case HPIOP_BIND:
		HpiOp_Bind(ctx);
		break;
	case HPIOP_BINDARGS:
		HpiOp_BindArgs(ctx);
		break;
	case HPIOP_BINDVAR:
		HpiOp_BindVar(ctx);
		break;
	case HPIOP_BINDARGSVAR:
		HpiOp_BindArgsVar(ctx);
		break;
	case HPIOP_BLOCK:
		HpiOp_Block(ctx);
		break;
	case HPIOP_CLOSE:
		HpiOp_Close(ctx);
		break;
	case HPIOP_CONSTANT:
		HpiOp_Constant(ctx);
		break;
	case HPIOP_CONSTRAINT:
		HpiOp_Constraint(ctx);
		break;
	case HPIOP_CONTI:
		HpiOp_Conti(ctx);
		break;
	case HPIOP_CURRENTENV:
		HpiOp_CurrentEnv(ctx);
		break;
	case HPIOP_FRAME:
		HpiOp_Frame(ctx);
		break;
	case HPIOP_FUNC:
		HpiOp_Func(ctx);
		break;
	case HPIOP_HALT:
//		HpiOp_Halt(ctx);
		ctx->vax=SYMG(sym_halt, "halt");
		ctx->ip=MISC_TRUE;
		return(ctx->ax);
		break;
	case HPIOP_INTSOFF:
		HpiOp_IntsOff(ctx);
		break;
	case HPIOP_INTSON:
		HpiOp_IntsOn(ctx);
		break;
	case HPIOP_NUATE:
		HpiOp_Nuate(ctx);
		break;
	case HPIOP_REFER:
		HpiOp_Refer(ctx);
		break;
	case HPIOP_REFERSYNTAX:
		HpiOp_ReferSyntax(ctx);
		break;
	case HPIOP_RETURN:
		HpiOp_Return(ctx);
		break;
	case HPIOP_SETRAX:
		HpiOp_SetRax(ctx);
		break;
	case HPIOP_SPLICE:
		HpiOp_Splice(ctx);
		break;
	case HPIOP_TEST:
		HpiOp_Test(ctx);
		break;
	case HPIOP_XCHGRPAX:
		HpiOp_XchgRPAX(ctx);
		break;
	case HPIOP_DUMPOPS:
		HpiMisc_DumpOps(ctx);
		break;
	default:
		sa_fatal("unknown opcode %d\n", op>>16);
		break;
	}

//	if(ctx->ip==MISC_TRUE)return(ctx->ax);
	return(MISC_UNDEFINED);
}

elem HpiInterp_RunLoop(InterpCtx *ctx)
{
	elem op;
	int c;

	interp_cur_ctx=ELEM_FROMOBJECT(ctx);

	Sys_TimeDUS();

//	sa_print("run: start\n");

//	c=1<<24;

	while(ELEM_CONSP(ctx->ip))
	{
		c=0;
		while(ELEM_CONSP(ctx->ip) && (c<(1<<16)))
		{
			HpiInterp_RunStep(ctx);
			c++;
		}
		interp_totalusloop+=Sys_TimeDUS();
		interp_totalopsloop+=c;

		if((interp_totalusloop>(1<<27)) || (interp_totalopsloop>(1<<27)))
		{
			interp_totalusloop>>=1;
			interp_totalopsloop>>=1;
		}

#if 1
		if(interp_totalusloop>1000000)
		{
			printf("interp clk %f ops/s\n",
				((float)interp_totalopsloop/
				(float)interp_totalusloop)*1000000);
			interp_totalusloop=0;
			interp_totalopsloop=0;
		}
#endif
	}

	if(!c)sa_fatal("RunLoop: runaway loop\n");

//	sa_print("\nrun: stop\n");


	if(ctx->ip==MISC_TRUE)return(ctx->ax);
//	sa_print("hit end of op stream\n");
	return(MISC_UNDEFINED);
}

int HpiInterp_RunLoopQuantum(elem ectx, int ms)
{
	elem op, noints;
	int t, end;
	InterpCtx *ctx;

	ctx=(InterpCtx *)ELEM_TOOBJECT(ectx);

	interp_cur_ctx=ectx;

	t=Sys_TimeMS();
	end=t+ms;

	ctx->vax=MISC_NULL;

	noints=SYMG(sym_noints, "no-ints");

	while(ELEM_CONSP(ctx->ip))
	{
		t=Sys_TimeMS();
		if(t>=end && !(ctx->vax==noints))break;

		if(ctx->vax!=MISC_NULL)
		{
			if(ctx->vax==SYMG(sym_halt, "halt"))break;
				else if(ctx->vax==SYMG(sym_block, "block"))break;
				else ctx->vax=MISC_NULL;
		}

		HpiInterp_RunStep(ctx);
	}

	return(end-t);
}

elem HpiInterp_Run(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d)
{
	InterpCtx *tmp;
	elem t;

	t=VECTOR_NEWT(sizeof(InterpCtx)/sizeof(elem), VECTOR_CONTEXT);
	tmp=ELEM_TOOBJECT(t);

//	tmp=sa_malloc(sizeof(InterpCtx));
	tmp->ip=form;
	tmp->ax=MISC_NULL;
	tmp->sp=MISC_EOL;
	tmp->rp=MISC_EOL;

	tmp->ep_n=env_n;
	tmp->ep_d=env_d;
	tmp->dyn_n=dyn_n;
	tmp->dyn_d=dyn_d;

	t=HpiInterp_RunLoop(tmp);

//	sa_free(tmp);

	return(t);
}

elem HpiInterp_RunCtx(elem form, InterpCtx *ctx)
{
	elem t;

	ctx->ip=form;
	ctx->ax=MISC_NULL;
	ctx->rp=MISC_EOL;

	t=HpiInterp_RunLoop(ctx);

	return(t);
}

InterpCtx *HpiInterp_RunCtxSafe(elem form, InterpCtx *ctx)
{
	InterpCtx *newctx;
	elem x, t;

	t=TyFcn_CopyVector(ELEM_FROMOBJECT(ctx));
	newctx=(InterpCtx *)ELEM_TOOBJECT(t);

	newctx->ip=form;
	newctx->ax=MISC_NULL;
	newctx->rp=MISC_EOL;

	t=HpiInterp_RunLoop(newctx);

	return(newctx);
}

int HpiInterp_Init()
{
	SAGC_AddRoot(&opcodes_n);
	SAGC_AddRoot(&opcodes_d);

	SAGC_AddRoot(&interp_freeframes);

	opcodes_n=MISC_EOL;
	opcodes_d=MISC_EOL;
	interp_freeframes=MISC_EOL;

	hpimisc_dumpops=0;

	HpiInterp_DefineOpcode("apply",			HPIOP_APPLY);
	HpiInterp_DefineOpcode("argument",		HPIOP_ARGUMENT);
	HpiInterp_DefineOpcode("assign",		HPIOP_ASSIGN);
	HpiInterp_DefineOpcode("assign2",		HPIOP_ASSIGN2);
	HpiInterp_DefineOpcode("bind",			HPIOP_BIND);
	HpiInterp_DefineOpcode("bind-args",		HPIOP_BINDARGS);
	HpiInterp_DefineOpcode("bind-var",		HPIOP_BINDVAR);
	HpiInterp_DefineOpcode("bind-args-var",		HPIOP_BINDARGSVAR);
	HpiInterp_DefineOpcode("block",			HPIOP_BLOCK);
	HpiInterp_DefineOpcode("close",			HPIOP_CLOSE);
	HpiInterp_DefineOpcode("constant",		HPIOP_CONSTANT);
	HpiInterp_DefineOpcode("constraint",		HPIOP_CONSTRAINT);
	HpiInterp_DefineOpcode("conti",			HPIOP_CONTI);
	HpiInterp_DefineOpcode("current-env",		HPIOP_CURRENTENV);
	HpiInterp_DefineOpcode("frame",			HPIOP_FRAME);
	HpiInterp_DefineOpcode("func",			HPIOP_FUNC);
	HpiInterp_DefineOpcode("halt",			HPIOP_HALT);
	HpiInterp_DefineOpcode("ints-off",		HPIOP_INTSOFF);
	HpiInterp_DefineOpcode("ints-on",		HPIOP_INTSON);
	HpiInterp_DefineOpcode("nuate",			HPIOP_NUATE);
	HpiInterp_DefineOpcode("refer",			HPIOP_REFER);
	HpiInterp_DefineOpcode("refer-syntax",		HPIOP_REFERSYNTAX);
	HpiInterp_DefineOpcode("return",		HPIOP_RETURN);
	HpiInterp_DefineOpcode("set-rax",		HPIOP_SETRAX);
	HpiInterp_DefineOpcode("splice",		HPIOP_SPLICE);
	HpiInterp_DefineOpcode("test",			HPIOP_TEST);
	HpiInterp_DefineOpcode("xchg-rp-ax",		HPIOP_XCHGRPAX);
	HpiInterp_DefineOpcode("dump-ops",		HPIOP_DUMPOPS);
}
