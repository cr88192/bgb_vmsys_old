/*
functions will have the form:
CTX *func(CTX *ctx);

ctx will contain: ep_n, ep_d, dyn_n, dyn_d, ax, rp.
lexical bindings will be resolved inline (for now), due to the reason that
(unlike in the interpreter) the exact contents of the environment can't be
determined.

elem LBRTL_Refer(CTX *ctx, elem sym);
will resolve sym.

elem LBRTL_Assign(CTX *ctx, elem sym, elem val);
will resolve sym.

elem LBRTL_Close(CTX *ctx, elem pattern, CTX *(*func)(CTX *ctx));
will close over a function.

elem LBRTL_Apply(CTX *ctx, elem func);
will apply func. non-tail optimizing (for now).
*/
#include <scmcc.h>

elem cgen_top;
elem cgen_func;
elem cgen_main;

int cgen_idx;

elem CGEN_ExpandForm(elem body, elem c)
{
	elem x;

	x=body;
	if(ELEM_SYMBOLP(c))
	{
		x=CONS(STRING("SYM(\""), x);
		x=CONS(STRING(ELEM_TOSYMBOL(c)), x);
		x=CONS(STRING("\")"), x);
		return(x);
	}

	if(ELEM_CONSP(c))
	{
		x=CONS(STRING("CONS("), x);
		x=CGEN_ExpandForm(x, CAR(c));
		x=CONS(STRING(", "), x);
		x=CGEN_ExpandForm(x, CDR(c));
		x=CONS(STRING(")"), x);
		return(x);
	}

	if(ELEM_STRINGP(c))
	{
		x=CONS(STRING("STRING(\""), x);
		x=CONS(c, x);
		x=CONS(STRING("\")"), x);
		return(x);
	}

	if(ELEM_FIXNUMP(c))
	{
		x=CONS(STRING("FIXNUM("), x);
		x=CONS(STRING(sa_itoa(TOINT(c))), x);
		x=CONS(STRING(")"), x);
		return(x);
	}

	if(ELEM_CHARP(c))
	{
		x=CONS(STRING("ELEM_FROMCHAR("), x);
		x=CONS(STRING(sa_itoa(ELEM_TOCHAR(c))), x);
		x=CONS(STRING(")"), x);
		return(x);
	}

	switch(c)
	{
	case MISC_EOL:
		x=CONS(STRING("MISC_EOL"), x);
		return(x);
		break;
	case MISC_TRUE:
		x=CONS(STRING("MISC_TRUE"), x);
		return(x);
		break;
	case MISC_FALSE:
		x=CONS(STRING("MISC_FALSE"), x);
		return(x);
		break;
	case MISC_NULL:
		x=CONS(STRING("MISC_NULL"), x);
		return(x);
		break;
	default:
		break;
	}

	sa_error("CGEN_ExpandForm: unknown type\n");
	x=CONS(STRING("MISC_UNDEFINED /* unknown type */"), x);
	return(x);
}

elem CGEN_ExpandFunction(elem form)
{
	char buf[64];
	elem fname;
	elem x;

	sa_prints(buf, "CG%d", cgen_idx++);
	fname=STRING(buf);

	x=cgen_top;
	x=CONS(STRING("static CTX *"), x);
	x=CONS(fname, x);
	x=CONS(STRING("(CTX *ctx);\n"), x);
	cgen_top=x;

	x=MISC_EOL;
	x=CONS(STRING("static CTX *"), x);
	x=CONS(fname, x);
	x=CONS(STRING("(CTX *ctx)\n{\n"), x);

	x=CGEN_CompileFrag(x, form);
	x=CONS(STRING("}\n\n"), x);

	cgen_func=CONS(x, cgen_func);
	return(fname);
}

elem CGEN_Op_Apply(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tLBRTL_Apply(ctx, ctx->ax);\n"), x);
	return(x);
}

elem CGEN_Op_Argument(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->rp=CONS(ctx->ax, ctx->rp);\n"), x);
	return(x);
}

elem CGEN_Op_Assign(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tLBRTL_Assign(ctx, "), x);
	x=CGEN_ExpandForm(x, CADDR(op));
	x=CONS(STRING(", ctx->ax);\n"), x);
	return(x);
}

elem CGEN_Op_Bind(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->ep_n=CONS(CONS("), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(", CAR(ctx->ep_n)), CDR(ctx->ep_n));\n"), x);

	x=CONS(STRING("\tctx->ep_d=CONS(CONS(ctx->ax, CAR(ctx->ep_d)), CDR(ctx->ep_d));\n"), x);
	return(x);
}

elem CGEN_Op_BindArgs(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->ep_n=CONS(CONS("), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(", CAR(ctx->ep_n)), CDR(ctx->ep_n));\n"), x);

	x=CONS(STRING("\tctx->ep_d=CONS(CONS(ctx->ax, CAR(ctx->ep_d)), CDR(ctx->ep_d));\n"), x);
	return(x);
}

elem CGEN_Op_BindVar(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->dyn_n=CONS(CONS("), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(", CAR(ctx->dyn_n)), CDR(ctx->dyn_n));\n"), x);

	x=CONS(STRING("\tctx->dyn_d=CONS(CONS(ctx->ax, CAR(ctx->dyn_d)), CDR(ctx->dyn_d));\n"), x);
	return(x);
}

elem CGEN_Op_BindArgsVar(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->dyn_n=CONS(CONS("), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(", CAR(ctx->dyn_n)), CDR(ctx->dyn_n));\n"), x);

	x=CONS(STRING("\tctx->dyn_d=CONS(CONS(ctx->ax, CAR(ctx->dyn_d)), CDR(ctx->dyn_d));\n"), x);
	return(x);
}

elem CGEN_Op_Block(elem body, elem op)
{
	elem x;

	x=body;
	return(x);
}

elem CGEN_Op_Close(elem body, elem op)
{
	elem x, t;

	x=body;
	x=CONS(STRING("\tLBRTL_Close(ctx, "), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(", &"), x);
	t=CGEN_ExpandFunction(CADDR(op));
	x=CONS(t, x);
	x=CONS(STRING(");\n"), x);

	return(x);
}

elem CGEN_Op_Constant(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->ax="), x);
	x=CGEN_ExpandForm(x, CADR(op));
	x=CONS(STRING(";\n"), x);

	return(x);
}

elem CGEN_Op_Frame(elem body, elem op)
{
	elem x, t;

	x=body;
//	x=CONS(STRING("\tctx->ax="), x);

	x=CONS(STRING("\tctx->sp=CONS(ctx->ep_n, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->ep_d, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->dyn_n, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->dyn_d, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->sep_n, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->sep_d, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CONS(ctx->rp, ctx->sp);\n"), x);

	x=CONS(STRING("\tctx->rp=MISC_EOL;\n\n"), x);

	x=CONS(STRING("\t"), x);
	t=CGEN_ExpandFunction(CADR(op));
	x=CONS(t, x);
	x=CONS(STRING("(ctx);\n\n"), x);

	x=CONS(STRING("\tctx->rp=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);

	x=CONS(STRING("\tctx->sep_n=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sep_d=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);

	x=CONS(STRING("\tctx->dyn_n=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->dyn_d=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);

	x=CONS(STRING("\tctx->ep_n=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->ep_d=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);
	x=CONS(STRING("\n"), x);
	

	return(x);
}

elem CGEN_Op_Refer(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tLBRTL_Refer(ctx, "), x);
	x=CGEN_ExpandForm(x, CADDR(op));
	x=CONS(STRING(");\n"), x);

	return(x);
}

elem CGEN_Op_ReferSyntax(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tLBRTL_ReferSyntax(ctx, "), x);
	x=CGEN_ExpandForm(x, CADDR(op));
	x=CONS(STRING(");\n"), x);

	return(x);
}

elem CGEN_Op_Return(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\treturn(ctx);\n"), x);

	return(x);
}

elem CGEN_Op_Splice(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->rp=TyFcn_Append(ctx->ax, ctx->rp);\n"), x);

	return(x);
}

elem CGEN_Op_Test(elem body, elem op)
{
	elem x, t;

	x=body;
	x=CONS(STRING("\tif(ctx->ax==MISC_TRUE)\n"), x);

	x=CONS(STRING("\t\t"), x);
	t=CGEN_ExpandFunction(CADR(op));
	x=CONS(t, x);
	x=CONS(STRING("(ctx);\n"), x);

	x=CONS(STRING("\t\telse "), x);
	t=CGEN_ExpandFunction(CADDR(op));
	x=CONS(t, x);
	x=CONS(STRING("(ctx);\n"), x);

	return(x);
}

elem CGEN_Op_XchgRPAX(elem body, elem op)
{
	elem x;

	x=body;
	x=CONS(STRING("\tctx->sp=CONS(ctx->ax, ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->ax=ctx->rp;\n"), x);
	x=CONS(STRING("\tctx->rp=CAR(ctx->sp);\n"), x);
	x=CONS(STRING("\tctx->sp=CDR(ctx->sp);\n"), x);

	return(x);
}


elem CGEN_CompileOpcode(elem body, elem op)
{
	elem x;

	if(CAR(op)==SYM("apply"))
		return(CGEN_Op_Apply(body, op));
	if(CAR(op)==SYM("argument"))
		return(CGEN_Op_Argument(body, op));
	if(CAR(op)==SYM("assign"))
		return(CGEN_Op_Assign(body, op));
	if(CAR(op)==SYM("bind"))
		return(CGEN_Op_Bind(body, op));
	if(CAR(op)==SYM("bind-args"))
		return(CGEN_Op_BindArgs(body, op));
	if(CAR(op)==SYM("bind-var"))
		return(CGEN_Op_BindVar(body, op));
	if(CAR(op)==SYM("bind-args-var"))
		return(CGEN_Op_BindArgsVar(body, op));
	if(CAR(op)==SYM("block"))
		return(CGEN_Op_Block(body, op));
	if(CAR(op)==SYM("close"))
		return(CGEN_Op_Close(body, op));
	if(CAR(op)==SYM("constant"))
		return(CGEN_Op_Constant(body, op));
//	if(CAR(op)==SYM("conti"))
//		return(CGEN_Op_Conti(body, op));

	if(CAR(op)==SYM("frame"))
		return(CGEN_Op_Frame(body, op));

	if(CAR(op)==SYM("refer"))
		return(CGEN_Op_Refer(body, op));
	if(CAR(op)==SYM("refer-syntax"))
		return(CGEN_Op_ReferSyntax(body, op));
	if(CAR(op)==SYM("return"))
		return(CGEN_Op_Return(body, op));
//	if(CAR(op)==SYM("set-rax"))
//		return(CGEN_Op_SetRax(body, op));
	if(CAR(op)==SYM("splice"))
		return(CGEN_Op_Splice(body, op));
	if(CAR(op)==SYM("test"))
		return(CGEN_Op_Test(body, op));
	if(CAR(op)==SYM("xchg-rp-ax"))
		return(CGEN_Op_XchgRPAX(body, op));

	x=body;
	x=CONS(STRING("/* unknown op '"), x);
	x=CONS(TyPrint_PrintString(op, FIXNUM(0)), x);
	x=CONS(STRING("' */\n"), x);
	
	return(x);
}

elem CGEN_CompileFrag(elem body, elem frag)
{
	elem cur, x;

	x=body;
	cur=frag;
	while(cur!=MISC_EOL)
	{
		x=CGEN_CompileOpcode(x, CAR(cur));
		cur=CDR(cur);
	}
	return(x);
}

elem CGEN_BeginCompile(elem func)
{
	elem x;
	cgen_top=CONS(STRING("#include <lbrtl.h>\n\n"), MISC_EOL);

	cgen_func=MISC_EOL;

	x=CONS(STRING("CTX *"), MISC_EOL);
	x=CONS(STRING(ELEM_TOSYMBOL(func)), x);
	x=CONS(STRING("(CTX *ctx)\n{\n"), x);
	cgen_main=x;
}

elem CGEN_EndCompile()
{
	elem x;

	x=cgen_main;
	x=CONS(STRING("}\n"), x);
	cgen_main=x;

	x=MISC_EOL;

	x=CONS(cgen_top, x);
	x=CONS(STRING("\n\n"), x);
	x=CONS(cgen_func, x);
	x=CONS(STRING("\n\n"), x);
	x=CONS(cgen_main, x);

	cgen_top=MISC_EOL;
	cgen_func=MISC_EOL;
	cgen_main=MISC_EOL;

	x=TyFcn_ReverseTree(x);

	TyPrint_PrintFlags(x, FIXNUM(TYPRINT_FORMATTED));

	return(x);
}

elem CGEN_Compile(elem func, elem frag)
{
	elem x;

	CGEN_BeginCompile(func);
	cgen_main=CGEN_CompileFrag(cgen_main, frag);

	x=CGEN_EndCompile();
	return(x);
}

elem CGEN_CompileTop(elem frag)
{
	TyPrint_PrintFlags(frag, FIXNUM(0));
	sa_print("\n");

	cgen_main=CGEN_CompileFrag(cgen_main, frag);

	return(MISC_NULL);
}

int CGEN_Init()
{
	cgen_top=MISC_EOL;
	cgen_func=MISC_EOL;
	cgen_main=MISC_EOL;

	MMGC3_AddRoot(&cgen_top);
	MMGC3_AddRoot(&cgen_func);
	MMGC3_AddRoot(&cgen_main);

	Interp_DefinePrimative("cgen-compile", &CGEN_Compile, 2);

	Interp_DefinePrimative("cgen-begin", &CGEN_BeginCompile, 1);
	Interp_DefinePrimative("cgen-end", &CGEN_EndCompile, 0);
	Interp_DefinePrimative("cgen-frag", &CGEN_CompileTop, 1);
}
