/*
	codegen for x86 nasm
	this will work by peicewise forming a list of string segments and merging
	them together eventually out to disk.
 */

#include <scmcc.h>

extern elem form_return, form_apply, form_halt;
elem asmcg_opcodes_n, asmcg_opcodes_d;

int asmcg_lastlabel;

extern elem hpicomp_topbinds, hpicomp_exports, hpicomp_imports, hpicomp_modname;

#if 0
int HpiInterp_Run2(elem ip, elem ax, elem sp, elem ep, elem rp, elem dep)
{
	elem op, ins, t, cur, lst;

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

int HpiInterp_Run(elem form) //AH:ignore
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

#endif

elem AsmCG_DefineSpecial(char *name, int (*func)(), int pc)
{
//	asmcg_opcodes=CONS(
//		TyFcn_SymbolDef(TyFcn_Symbol(name), TyFcn_Special(func, pc), MISC_EOL),
//		asmcg_opcodes);

	asmcg_opcodes_n=CONS(TyFcn_Symbol(name), asmcg_opcodes_n);
	asmcg_opcodes_d=CONS(TyFcn_Function((elem (*)())func, pc), asmcg_opcodes_d);

	return(MISC_NULL);
}

int AsmCG_GenFrag(elem form, elem *code, elem *data)
{
	elem cur, lst, t;

	lst=TyFcn_Reverse(form);
	cur=lst;
	while(cur!=MISC_EOL)
	{
//		t=Namespace_LookupVarList(CAR(CAR(cur)), asmcg_opcodes);
//		t=TyMisc_EvalSpecial(TyFcn_SymdefData(t), CONS(CAR(cur), CONS((int)code, CONS((int)data, MISC_EOL))));

		t=Namespace2_Lookup(asmcg_opcodes_n, asmcg_opcodes_d, CAR(CAR(cur)));
		if(t==MISC_UNDEFINED)
			sa_fatal("unknown opcode '%s'\n", ELEM_TOSTRING(CAR(CAR(cur))));
		t=TyMisc_EvalSpecial(t, CONS(CAR(cur), CONS((int)code, CONS((int)data, MISC_EOL))));
		cur=CDR(cur);
	}
	return(0);
}

#if 0
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
#endif

char *AsmCG_Label(char *base)
{
	char *s;
	s=sa_ralloc(64);
	sprintf(s, "%s%d", base, asmcg_lastlabel++);
	return(s);
}

char *AsmCG_ASIfy(char *base)
{
	char *tmp;
	int i;

	tmp=sa_ralloc(strlen(base)+3);

	sprintf(tmp, "S_%s", base);
	for(i=0; i<strlen(tmp); i++)switch(tmp[i])
	{
	case '?':
		tmp[i]='P';
		break;
	case '!':
		tmp[i]='X';
		break;
	case '+':
		tmp[i]='A';
		break;
	case '-':
		tmp[i]='S';
		break;
	case '<':
		tmp[i]='L';
		break;
	case '>':
		tmp[i]='G';
		break;
	case '*':
		tmp[i]='M';
		break;
	case '/':
		tmp[i]='D';
		break;
	default:
		break;
	}

	return(tmp);
}


char *AsmCG_GenObject(elem obj, elem *code, elem *data)
{
	char buf[256], *s, *t, *u;
	elem *p, *q, lst, lst2;
	int i, l;

	unsigned char *v;
	unsigned short *w;

	lst=MISC_EOL;
	s=NULL;

	switch(ELEM_TYPE3(obj))
	{
	case 0:
		s=sa_ralloc(16);
		sprintf(s, "0x%08X", obj);
		break;
	case 2:
		s=sa_ralloc(16);
		sprintf(s, "0x%08X", obj);
		break;
	case 3:
		switch((OBJECT_HEAD(obj)>>3)&31)
		{
		case 1:
			if(!s)s=AsmCG_Label("vector");
		case 2:
			if(!s)s=AsmCG_Label("string");
		case 3:
			if(!s)s=AsmCG_Label("symbol");

			p=ELEM_TOOBJECT(obj);
			l=(p[0]>>16)&4095;

			sprintf(buf, "align 8\n%s:\ndd 0x%08X\n", s, p[0]);
			lst=CONS(STRING(buf), lst);

			switch((p[0]>>8)&255)
			{
			case 1:
				for(i=0; i<l; i++)
				{
					t=AsmCG_GenObject(p[i+1], code, data);
					sprintf(buf, "dd %s\n", t);
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 4:
				v=(unsigned char *)(p+1);
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "db %d, %d, %d, %d,  %d, %d, %d, %d\n",
						v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
					v+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "db %d\n", *v);
					v++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 5:
				w=(unsigned short *)(p+1);
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "dw %d, %d, %d, %d,  %d, %d, %d, %d\n",
						w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7]);
					w+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "dw %d\n", *w);
					w++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 6:
				q=p+1;
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "dd %d, %d, %d, %d,  %d, %d, %d, %d\n",
						q[0], q[1], q[2], q[3], q[4], q[5], q[6], q[7]);
					q+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "dd %d\n", *q);
					q++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 8:
				v=(unsigned char *)(p+1);
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "db %d, %d, %d, %d,  %d, %d, %d, %d\n",
						v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
					v+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "db %d\n", *v);
					v++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 9:
				w=(unsigned short *)(p+1);
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "dw %d, %d, %d, %d,  %d, %d, %d, %d\n",
						w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7]);
					w+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "dw %d\n", *w);
					w++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			case 10:
				q=p+1;
				for(i=0; (l-i)>8; i++)
				{
					sprintf(buf, "dd %d, %d, %d, %d,  %d, %d, %d, %d\n",
						q[0], q[1], q[2], q[3], q[4], q[5], q[6], q[7]);
					q+=8;
					lst=CONS(STRING(buf), lst);
				}
				for(; i<l; i++)
				{
					sprintf(buf, "dd %d\n", *q);
					q++;
					lst=CONS(STRING(buf), lst);
				}
				break;
			default:
				sa_error("unknown vector type %d\n", (p[0]>>8)&255);
				lst=MISC_EOL;
				break;
			}
			lst2=TyFcn_NReverse(lst);
			TyFcn_SetCdr(lst, *data);
			*data=lst2;
			break;
		default:
			sa_error("unknown type.\n");
			break;
		}

		t=sa_ralloc(64);
		sprintf(t, "(%s+%d)", s, ELEM_TYPE3(obj));
		s=t;
		break;
	case 7:
		s=AsmCG_Label("cons");
		t=AsmCG_GenObject(CAR(obj), code, data);
		u=AsmCG_GenObject(CDR(obj), code, data);
		sprintf(buf, "align 8\n%s:\ndd %s, %s\n", s, t, u);
		*data=CONS(STRING(buf), *data);

		t=sa_ralloc(64);
		sprintf(t, "(%s+%d)", s, ELEM_TYPE3(obj));
		s=t;
		break;
	}

	return(s);
}

int AsmCG_Op_Apply(elem op, elem *code, elem *data)
{
	*code=CONS(STRING("jmp prim_apply\n"), *code);
	return(0);
}

int AsmCG_Op_Argument(elem op, elem *code, elem *data)
{
	*code=CONS(STRING("push eax\n"), *code);
	return(0);
}

int AsmCG_Op_Assign(elem op, elem *code, elem *data)
{
	char buf[256];
	int y, x;
	elem pos;

	pos=CAR(CDR(op));

	if(ELEM_SYMBOLP(pos))
	{
		sprintf(buf, "mov [%s], eax\n", AsmCG_ASIfy(ELEM_TOSYMBOL(pos)));
		*code=CONS(STRING(buf), *code);
	}else
	{
//		y=(pos>>20)&4095;
//		x=(pos>>8)&4095;

		y=ELEM_TOFIXNUM(CAR(pos));
		x=ELEM_TOFIXNUM(CADR(pos));

		sprintf(buf, "mov [esi+%d], eax\n", (x+2)*4);
		*code=CONS(STRING(buf), *code);
		if(y)
		{
			sprintf(buf, "mov ecx, %d\nrep mov esi, [esi+4]\n", y);
			*code=CONS(STRING(buf), *code);
		}
		*code=CONS(STRING("mov esi, [edi]\n"), *code);
	}

	return(0);
}

int AsmCG_Op_Bind(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s;

	*code=CONS(STRING("call prim_bind\n"), *code);

	s=AsmCG_GenObject(CAR(CDR(op)), code, data);
	sprintf(buf, "mov edx, %s\n", s);
	*code=CONS(STRING(buf), *code);

	return(0);
}

int AsmCG_Op_BindArgs(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s;

	*code=CONS(STRING("call prim_bindargs\n"), *code);

	s=AsmCG_GenObject(CAR(CDR(op)), code, data);
	sprintf(buf, "mov eax, %s\n", s);
	*code=CONS(STRING(buf), *code);

	return(0);
}

int AsmCG_Op_BindVar(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s;

	*code=CONS(STRING("call prim_bindvar\n"), *code);

	s=AsmCG_GenObject(CAR(CDR(op)), code, data);
	sprintf(buf, "mov edx, %s\n", s);
	*code=CONS(STRING(buf), *code);

	return(0);
}


int AsmCG_Op_Close(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s, *t, *u;

	s=AsmCG_Label("close_exit");
	sprintf(buf, "\n%s:\n", s);
	*code=CONS(STRING(buf), *code);

	AsmCG_GenFrag(CAR(CDR(CDR(op))), code, data);

	t=AsmCG_Label("close_entry");
	sprintf(buf, "\n%s:\n", t);
	*code=CONS(STRING(buf), *code);

	sprintf(buf, "jmp %s\n", s);
	*code=CONS(STRING(buf), *code);

	*code=CONS(STRING("call prim_close\n"), *code);

//	u=AsmCG_GenObject(CAR(CAR(CDR(op))), code, data);
	u=AsmCG_GenObject(CAR(CDR(op)), code, data);
	sprintf(buf, "mov edx, %s\n", u);
	*code=CONS(STRING(buf), *code);

	sprintf(buf, "mov eax, %s\n", t);
	*code=CONS(STRING(buf), *code);

	return(0);
}

int AsmCG_Op_Constant(elem op, elem *code, elem *data)
{
	elem obj;
	char *lab, buf[256];

	obj=CAR(CDR(op));
	lab=AsmCG_GenObject(obj, code, data);
	sprintf(buf, "mov eax, %s\n", lab);
	*code=CONS(STRING(buf), *code);

	return(0);
}

int AsmCG_Op_Frame(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s;

	s=AsmCG_Label("frame");
	sprintf(buf, "\n%s:\n", s);
	*code=CONS(STRING(buf), *code);

	AsmCG_GenFrag(CAR(CDR(op)), code, data);

//	*code=CONS(STRING("mov edi, esp\n\n"), *code);

//	*code=CONS(STRING("push dword [edi]\n"), *code);
//	*code=CONS(STRING("push dword [edi+4]\n"), *code);

//	*code=CONS(STRING("push edi\n"), *code);
//	*code=CONS(STRING("push esi\n"), *code);

//	sprintf(buf, "push dword %s\n", s);
	sprintf(buf, "mov eax, %s\ncall prim_frame\n", s);
	*code=CONS(STRING(buf), *code);

//	*code=CONS(STRING("mov esi, esp\n"), *code);

	return(0);
}

int AsmCG_Op_Halt(elem op, elem *code, elem *data)
{
	*code=CONS(STRING("ret\n"), *code);
	return(0);
}

int AsmCG_Op_Refer(elem op, elem *code, elem *data)
{
	char buf[256];
	int y, x;
	elem pos;

	pos=CAR(CDR(op));

	if(ELEM_SYMBOLP(pos))
	{
		sprintf(buf, "mov eax, [%s]\n", AsmCG_ASIfy(ELEM_TOSYMBOL(pos)));
		*code=CONS(STRING(buf), *code);
	}else
	{
//		y=(pos>>20)&4095;
//		x=(pos>>8)&4095;
		y=ELEM_TOFIXNUM(CAR(pos));
		if(CDR(pos)!=MISC_EOL)x=ELEM_TOFIXNUM(CADR(pos));
			else x=0;

		sprintf(buf, "mov eax, [esi+%d]\n", (x+2)*4);
		*code=CONS(STRING(buf), *code);
		if(y)
		{
			sprintf(buf, "mov ecx, %d\nrep mov esi, [esi+4]\n", y);
			*code=CONS(STRING(buf), *code);
		}
		*code=CONS(STRING("mov esi, [edi]\n"), *code);
	}
	return(0);
}

int AsmCG_Op_Return(elem op, elem *code, elem *data)
{
	*code=CONS(STRING(
		"mov edx, [edi+16]\n"
		"mov esp, [edi+12]\n"
		"mov edi, [edi+8]\n"
		"jmp edx\n"), *code);
	return(0);
}

int AsmCG_Op_Test(elem op, elem *code, elem *data)
{
	char buf[256];
	char *s, *t;

	s=AsmCG_Label("test_exit");
	t=AsmCG_Label("test_false");

	sprintf(buf, "%s:\n", s);
	*code=CONS(STRING(buf), *code);

	AsmCG_GenFrag(CAR(CDR(CDR(op))), code, data);

	sprintf(buf, "jmp %s\n%s:\n", s, t);
	*code=CONS(STRING(buf), *code);

	AsmCG_GenFrag(CAR(CDR(op)), code, data);

	sprintf(buf, "cmp eax, 0x%08X\njne %s\n", MISC_TRUE, t);
	*code=CONS(STRING(buf), *code);
	return(0);
}


elem AsmCG_Op_Splice(elem op, elem *code, elem *data)
{
	char buf[256];
	elem t;

//	t=ctx->ax;
//	ctx->ax=ctx->rp;
//	ctx->rp=t;

//	ctx->ip=CDR(ctx->ip);
//	return(MISC_NULL);

	sprintf(buf, "\n\n;splice opcode is broken\n\n");
	*code=CONS(STRING(buf), *code);

	return(0);
}

elem AsmCG_Op_XchgRPAX(elem op, elem *code, elem *data)
{
	char buf[256];
	elem t;

//	t=ctx->ax;
//	ctx->ax=ctx->rp;
//	ctx->rp=t;

//	ctx->ip=CDR(ctx->ip);
//	return(MISC_NULL);

	sprintf(buf, "\n\n;xchg-rp-ax opcode is broken\n\n");
	*code=CONS(STRING(buf), *code);

	return(0);
}

int AsmCG_Init()
{
	asmcg_lastlabel=0;
	asmcg_opcodes_n=MISC_EOL;
	asmcg_opcodes_d=MISC_EOL;

	AsmCG_DefineSpecial("apply", &AsmCG_Op_Apply, 3);
	AsmCG_DefineSpecial("argument", &AsmCG_Op_Argument, 3);
	AsmCG_DefineSpecial("assign", &AsmCG_Op_Assign, 3);
	AsmCG_DefineSpecial("bind", &AsmCG_Op_Bind, 3);
	AsmCG_DefineSpecial("bind-args", &AsmCG_Op_BindArgs, 3);
	AsmCG_DefineSpecial("bind-var", &AsmCG_Op_BindVar, 3);
	AsmCG_DefineSpecial("close", &AsmCG_Op_Close, 3);
	AsmCG_DefineSpecial("frame", &AsmCG_Op_Frame, 3);
	AsmCG_DefineSpecial("constant", &AsmCG_Op_Constant, 3);
	AsmCG_DefineSpecial("halt", &AsmCG_Op_Halt, 3);
	AsmCG_DefineSpecial("refer", &AsmCG_Op_Refer, 3);
	AsmCG_DefineSpecial("return", &AsmCG_Op_Return, 3);
	AsmCG_DefineSpecial("test", &AsmCG_Op_Test, 3);

	AsmCG_DefineSpecial("splice", &AsmCG_Op_Splice, 3);
	AsmCG_DefineSpecial("xchg-rp-ax", &AsmCG_Op_XchgRPAX, 3);
}

/* called after everything else is compiled */
int AsmCG_GenInitial(elem *code, elem *data)
{
	char buf[256];
	elem cur;

	sprintf(buf,
		"[section .text]\n"
		"[bits 32]\n"
		"\n"
		"%s:\n"
		"push ebp\n"
		"mov ebp, esp\n\n", AsmCG_ASIfy(ELEM_TOSTRING(hpicomp_modname)));
	*code=CONS(STRING(buf), *code);

	*code=CONS(STRING("\n\n"), *code);

	sprintf(buf, "\nglobal %s\n", AsmCG_ASIfy(ELEM_TOSTRING(hpicomp_modname)));
	*code=CONS(STRING(buf), *code);

	cur=hpicomp_exports;
	while(cur!=MISC_EOL)
	{
		sprintf(buf, "global %s\n", AsmCG_ASIfy(ELEM_TOSTRING(CAR(cur))));
		*code=CONS(STRING(buf), *code);
		cur=CDR(cur);
	}

	cur=hpicomp_imports;
	while(cur!=MISC_EOL)
	{
		sprintf(buf, "extern %s\n", AsmCG_ASIfy(ELEM_TOSTRING(CAR(cur))));
		*code=CONS(STRING(buf), *code);
		cur=CDR(cur);
	}

	*code=CONS(STRING(
		"extern prim_close\n"
		"extern prim_apply\n"
		"extern prim_frame\n"
		"extern prim_bind\n"
		"extern prim_bindargs\n\n"), *code);

	cur=hpicomp_topbinds;
	while(cur!=MISC_EOL)
	{
		sprintf(buf, "%s dd 0x%08X\n", AsmCG_ASIfy(ELEM_TOSTRING(CAR(cur))), MISC_NULL);
		*data=CONS(STRING(buf), *data);
		cur=CDR(cur);
	}

	sprintf(buf,
		"[section .data]\n"
		"[bits 32]\n"
		"\n");
	*data=CONS(STRING(buf), *data);
}

/* called before everything else */
int AsmCG_GenFinal(elem *code, elem *data)
{
	char buf[256];

	sprintf(buf,
		"\n"
		";exit stub\n"
		"pop ebp\n"
		"ret\n"
		"\n"
		"\n");
	*code=CONS(STRING(buf), *code);
	return(0);
}
