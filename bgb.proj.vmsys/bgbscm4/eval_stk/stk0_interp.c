/*
aim: to be a forth-ish interpreter, however I will treat both
the data stacks and execution stacks as usable stacks...

the interpreter will move by shifting objects from execution
stack to the data stack (this includes closures and other
such objects). opcodes will be popped from the execution stack
and evaluated.

this will also be a register machine, the register set will be a
vector and the same as the execution context. at present I
will have 8 data registers and some-odd amount of special
registers (directly following the data registers).

8 dsp (data stack), 9 isp (interpreter stack/ip), 10 ep_n, 11 ep_d,
12 dyn_n, 13 dyn_d, 14 sep_n, 15 sep_d

 */

#include <scmcc.h>
#include <stkvm.h>

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

elem StkInt_EvalSpecial(elem func, elem parms)
{
	elem cur, t;
	elem parm[16], xa;
	int pc, pl, pa;

	cur=parms;

	t=func;
	pl=(OBJECT_HEAD(t)>>9);

	pa=pl&31;
	pc=0;
	while((CAR(cur)!=MISC_MARK) && (pc<pa))
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

	if(pl&128)
	{
		parm[pc++]=cur;
	}else if(pl&64)
	{
		xa=MISC_EOL;
		while(CAR(cur)!=MISC_MARK)
		{
			xa=CONS(CAR(cur), xa);
			cur=CDR(cur);
		}
		xa=TyFcn_NReverse(xa);
		parm[pc++]=xa;
	}else
		if(CAR(cur)==MISC_MARK)cur=CDR(cur);

	t=OBJ_PEEK(func, 1);
	t=invoke_func(t, pc, parm);

	if(!(pl&128))t=CONS(t, cur);
	return(t);
}

elem StkOp_Apply(elem ctx)
{
	elem t, ep_n, ep_d;
	elem x, y;

	static elem sym_self=MISC_NULL;
	if(sym_self==MISC_NULL)sym_self=SYM("self");

	t=VECTOR_REF(ctx, 8);
	x=CAR(t);

	if(ELEM_FUNCTIONP(x))
	{
		t=StkInt_EvalSpecial(ctx->ax, ctx->rp);
		VECTOR_SET(ctx, 8, t);

		return(MISC_NULL);
	}else if(ELEM_CLOSUREP(x))
	{
		t=TyFcn_FoldMark(t);

		y=VECTOR_REF(x, 0);
		VECTOR_SET(x, 10, y);

		y=VECTOR_REF(x, 1);
		y=CONS(CAR(t), y);
		VECTOR_SET(x, 11, y);

		y=VECTOR_REF(ctx, 9);
		y=TyFcn_Append(VECTOR_REF(x, 2), y);
		VECTOR_SET(ctx, 9, y);

		y=VECTOR_REF(x, 3);
		VECTOR_SET(x, 14, y);
		y=VECTOR_REF(x, 4);
		VECTOR_SET(x, 15, y);

		return(MISC_NULL);
	}else if(ELEM_ENVOBJP(x))
	{
		y=CONS(sym_self, VECTOR_REF(ctx, 12));
		VECTOR_SET(ctx, 12, y);
		y=CONS(x, VECTOR_REF(ctx, 13));
		VECTOR_SET(ctx, 13, y);

//		ctx->ip=MISC_EOL;

		t=TyFcn_FoldMark(t);
//		TyObj_Dispatch(ctx);

		return(MISC_NULL);
	}else if(ELEM_ENVP(x))
	{
//		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
//		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
		ep_n=VECTOR_REF(x, 0);
		ep_d=VECTOR_REF(x, 1);

		if(CADR(t)==MISC_MARK)
		{
			x=Namespace2_Trace(ep_n, ep_d, MISC_EOL, CAR(t));
			t=CDDR(t);

			y=Namespace2_RetrieveTrace(ep_n, ep_d, x);
			t=CONS(y, t);
			y=Namespace2_LocativeTrace(ep_n, ep_d, x);
			VECTOR_SET(ctx, 7, y);
		}else
		{
			y=Namespace2_Assign(ep_n, ep_d, CAR(t), CADR(t));
			if(y==MISC_UNDEFINED)
			{
				ep_n=CONS(CONS(CAR(t), CAR(ep_n)), CDR(ep_n));
				ep_d=CONS(CONS(CADR(t), CAR(ep_d)), CDR(ep_d));
				TyFcn_VectorSet(x, ELEM_FROMFIXNUM(0), ep_n);
				TyFcn_VectorSet(x, ELEM_FROMFIXNUM(1), ep_d);
			}
			t=CDDR(t);
		}

		return(MISC_NULL);
	}else if(ELEM_CONTEXTP(ctx->ax))
	{
//		Interp_SendThread(ctx->ax, ctx->rp);
//		ctx->ax=MISC_NULL;
//		ctx->ip=form_return;
//		ctx->rp=MISC_EOL;

		return(MISC_NULL);
	}else if(ELEM_VECTORP(ctx->ax)) /* placed after other "vector" types... */
	{
/*
//		ep_n=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(0));
//		ep_d=TyFcn_VectorRef(ctx->ax, ELEM_FROMFIXNUM(1));
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

//		ctx->ax=t;
		ctx->ip=form_return;
		ctx->rp=MISC_EOL;
*/

		return(MISC_NULL);
	}else
	{
		sa_error("apply with invalid object: '");
		TyFcn_DumpElem(x);
		sa_print("'\n");

		abort();

		return(MISC_UNDEFINED);
	}
	return(MISC_NULL);
}

elem StkInt_Step(elem ctx)
{
	elem op, s, t, u, v, w;

	s=VECTOR_REF(ctx, 8);

	t=VECTOR_REF(ctx, 9);
	op=CAR(t);
	VECTOR_SET(ctx, 9, CDR(t));

	if(!ELEM_OPCODEP(op))
	{
		VECTOR_SET(ctx, 8, CONS(op, s));
		return(MISC_NULL);
	}

	switch(op>>16)
	{
	case STKVM_OP_APPLY:
		StkOp_Apply(ctx);
		break;
	case STKVM_OP_INVOKE:
		u=CAR(s);
		TyFcn_Append(u, t);
		VECTOR_SET(ctx, 9, CDR(t));
		break;
	case STKVM_OP_ASSIGN:
		v=CAR(s);
		if(ELEM_SYMBOLP(v))
		{
			t=VECTOR_REF(ctx, 12);
			u=VECTOR_REF(ctx, 13);
			w=CADDR(s);
			Namespace2_Assign(t, u, v, w);
			s=CDDR(s);
		}else
		{
			t=VECTOR_REF(ctx, 10);
			u=VECTOR_REF(ctx, 11);
			w=CADDR(s);
			Namespace2_AssignTrace(t, u, v, w);
			s=CDDR(s);
		}
		break;
	case STKVM_OP_REFER:
		v=CAR(s);

		if(ELEM_SYMBOLP(v))
		{
			t=VECTOR_REF(ctx, 12);
			u=VECTOR_REF(ctx, 13);
			w=Namespace2_Lookup(t, u, v);
			s=CDR(s);
		}else
		{
			t=VECTOR_REF(ctx, 10);
			u=VECTOR_REF(ctx, 11);
			w=Namespace2_RetrieveTrace(t, u, v);
			s=CDR(s);
		}
		break;
	case STKVM_OP_HALT:
		return(MISC_FALSE);
		break;
	case STKVM_OP_PUSH:
		t=CAR(s);
		u=TyFcn_VectorRef(ctx, t);
		s=CONS(u, CDR(s));
		break;
	case STKVM_OP_POP:
		t=CAR(s);
		u=CADR(s);
		u=TyFcn_VectorSet(ctx, t, u);
		s=CONS(u, CDDR(s));
		break;
	default:
		sa_print("unknown opcode %d\n", op>>16);
		abort();
		break;
	}

	s=VECTOR_SET(ctx, 8, s);
	return(MISC_NULL);
}

elem StkInt_Run(elem ctx)
{
	elem t;

	t=MISC_NULL;
	while(t==MISC_NULL)t=StkInt_Step(ctx);
	return(t);
}
