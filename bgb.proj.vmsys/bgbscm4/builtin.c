#include <scmcc.h>
#include <interpctx.h>

InterpCtx *interp_context; //used to pass context to called functions
extern elem interp_cur_ctx;

elem TyFcn_SymCount();


elem Builtin_EqP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a==b));
}

elem Builtin_EqvP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a==b));
}

elem Builtin_EqualP(elem a, elem b)
{
	return(TyFcn_EqualP(a, b));

#if 0
	elem cur, cur2, t;
	int i, j;
	if(ELEM_CONSP(a) && ELEM_CONSP(b))
	{
		cur=a;
		cur2=b;
		while(ELEM_CONSP(cur) && ELEM_CONSP(cur2))
		{
			t=Builtin_EqualP(CAR(cur), CAR(cur2));
			if(t==MISC_FALSE)return(t);
			cur=CDR(cur);
			cur2=CDR(cur2);
		}
		return(Builtin_EqualP(cur, cur2));
	}else if(ELEM_VECTORP(a) && ELEM_VECTORP(b))
	{
		cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(0));
		cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(0));
		if((cur>>16)!=(cur2>>16))return(MISC_FALSE);
		j=(cur>>16);
		for(i=0; i<j; i++)
		{
			cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(i+1));
			cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(i+1));
			t=Builtin_EqualP(cur, cur2);
			if(t==MISC_FALSE)return(t);
		}
		return(MISC_TRUE);
	}else if(ELEM_STRINGP(a) && ELEM_STRINGP(b))return(TyFcn_StringEP(a, b));
	return(Builtin_EqvP(a, b));
#endif
}

elem Builtin_NEqP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a!=b));
}

elem Builtin_NEqualP(elem a, elem b)
{
	return((TyFcn_EqualP(a, b)==MISC_FALSE)?MISC_TRUE:MISC_FALSE);
}

elem Builtin_Not(elem a)
{
	return((a==MISC_FALSE)?MISC_TRUE:MISC_FALSE);
}

elem Builtin_BooleanP(elem a)
{
	return(((a==MISC_FALSE)||(a==MISC_TRUE))?MISC_TRUE:MISC_FALSE);
}

elem Builtin_BitAndP(elem a, elem b)
{
	return((ELEM_TOFIXNUM(a)&ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem Builtin_BitOrP(elem a, elem b)
{
	return((ELEM_TOFIXNUM(a)|ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem Builtin_BitAnd(elem a, elem b)
{
	return(FIXNUM(ELEM_TOFIXNUM(a)&ELEM_TOFIXNUM(b)));
}

elem Builtin_BitOr(elem a, elem b)
{
	return(FIXNUM(ELEM_TOFIXNUM(a)|ELEM_TOFIXNUM(b)));
}

// lists

elem Builtin_Car(elem a)
{
	elem t, t2;

//	t=CAR(a);
	t=TyFcn_CarEv(a, interp_cur_ctx);
	if(ELEM_CONSTRAINTP(t))
	{
		interp_context->ax=t;
		t=HpiCmd_EvalConstraint(interp_context);
	}
	if(ELEM_TYPEXP(t))
	{
		t2=TypeX_EvalMulti(t, MISC_NULL, interp_cur_ctx);
		if(t2!=MISC_UNDEFINED)return(t2);
		t2=TypeX_EvalSingle(t, interp_cur_ctx);
		if(t2!=MISC_UNDEFINED)
		{
			TyFcn_SetCar(a, t2);
			return(t2);
		}
	}
//	interp_context->rax=TyFcn_CarM(a);
	return(t);
}

elem Builtin_Cdr(elem a)
{
	elem t, t2;

	t=CDR(a);
//	t=TyFcn_CdrEv(a, interp_cur_ctx);
	if(ELEM_CONSTRAINTP(t))
	{
		interp_context->ax=t;
		t=HpiCmd_EvalConstraint(interp_context);
	}
	if(ELEM_TYPEXP(t))
	{
		t2=TypeX_EvalMulti(t, MISC_NULL, interp_cur_ctx);
		if(t2!=MISC_UNDEFINED)return(t2);
		t2=TypeX_EvalSingle(t, interp_cur_ctx);
		if(t2!=MISC_UNDEFINED)
		{
			TyFcn_SetCdr(a, t2);
			return(t2);
		}
	}
//	interp_context->rax=TyFcn_CdrM(a);
	return(t);
}

elem Builtin_PairP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_CONSP(a)));
}

elem Builtin_NullP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_EOLP(a)));
}

elem Builtin_ListP(elem a)
{
	elem cur;
	cur=a;
	while(ELEM_CONSP(cur))cur=CDR(cur);
	return(ELEM_FROMBOOL(ELEM_EOLP(cur)));
}

elem Builtin_List(elem a)
{
	return(a);
}

elem Builtin_Append(elem a)
{
	elem cur, lst;

	lst=MISC_EOL;
	cur=a;
	while(ELEM_CONSP(cur))
	{
		lst=TyFcn_NAppend(lst, TyFcn_ListCopy(CAR(cur)));
		cur=CDR(cur);
	}

	return(lst);
}

// symbols

elem Builtin_SymbolP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_SYMBOLP(a)));
}

elem Builtin_SymbolToString(elem a)
{
	return(ELEM_FROMSTRING(ELEM_TOSYMBOL(a)));
}

elem Builtin_StringToSymbol(elem a)
{
	return(SYM(ELEM_TOSTRING(a)));
}

elem Builtin_Gensym()
{
	static int last=0;
	char buf[16];
	sprintf(buf, "GS:%X", last++);
	return(SYM(buf));
}

// characters

elem Builtin_CharP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_CHARP(a)));
}

elem Builtin_CharEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a==b));
}

elem Builtin_CharLP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a<b));
}

elem Builtin_CharGP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a>b));
}

elem Builtin_CharLEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a<=b));
}

elem Builtin_CharGEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(a>=b));
}

static elem Builtin_CharDownCase(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('A') && a<=ELEM_FROMCHAR('Z'))
		t=a-ELEM_FROMCHAR('A')+ELEM_FROMCHAR('a');
		else t=a;
	return(t);
}

static elem Builtin_CharUpCase(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('a') && a<=ELEM_FROMCHAR('z'))
		t=a-ELEM_FROMCHAR('a')+ELEM_FROMCHAR('A');
		else t=a;
	return(t);
}

elem Builtin_CharCiEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(Builtin_CharDownCase(a)==Builtin_CharDownCase(b)));
}

elem Builtin_CharCiLP(elem a, elem b)
{
	return(ELEM_FROMBOOL(Builtin_CharDownCase(a)<Builtin_CharDownCase(b)));
}

elem Builtin_CharCiGP(elem a, elem b)
{
	return(ELEM_FROMBOOL(Builtin_CharDownCase(a)>Builtin_CharDownCase(b)));
}

elem Builtin_CharCiLEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(Builtin_CharDownCase(a)<=Builtin_CharDownCase(b)));
}

elem Builtin_CharCiGEP(elem a, elem b)
{
	return(ELEM_FROMBOOL(Builtin_CharDownCase(a)>=Builtin_CharDownCase(b)));
}

elem Builtin_CharToInteger(elem a)
{
	return(ELEM_FROMFIXNUM(ELEM_TOCHAR(a)));
}

elem Builtin_IntegerToChar(elem a)
{
	return(ELEM_FROMCHAR(ELEM_TOFIXNUM(a)));
}

static elem Builtin_CharAlphabeticP(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('a') && a<=ELEM_FROMCHAR('z'))return(MISC_TRUE);
	if(a>=ELEM_FROMCHAR('A') && a<=ELEM_FROMCHAR('Z'))return(MISC_TRUE);
	return(MISC_FALSE);
}

static elem Builtin_CharNumericP(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('0') && a<=ELEM_FROMCHAR('9'))return(MISC_TRUE);
	return(MISC_FALSE);
}

static elem Builtin_CharWhitespaceP(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR(' '))return(MISC_TRUE);
	return(MISC_FALSE);
}

static elem Builtin_CharUpperCaseP(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('A') && a<=ELEM_FROMCHAR('Z'))return(MISC_TRUE);
	return(MISC_FALSE);
}

static elem Builtin_CharLowerCaseP(elem a)
{
	elem t;
	if(a>=ELEM_FROMCHAR('a') && a<=ELEM_FROMCHAR('z'))return(MISC_TRUE);
	return(MISC_FALSE);
}

// strings

elem Builtin_StringP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_STRINGP(a)));
}

elem Builtin_MakeString(elem a, elem b)
{
	return(TyFcn_MakeString(a, (ELEM_EOLP(b)?ELEM_FROMCHAR(0):CAR(b))));
}

// both string and list->string
elem Builtin_String(elem a)
{
	elem *t, cur;
	short *u;
	int l, ch, i;

	l=ELEM_TOFIXNUM(TyFcn_ListLength(a));

	t=sa_alloc(ELEM_SZ+(l*2)+2);
	t[0]=OBJECT_STRING|(l<<16)|256;
	u=(short *)(t+1);
	cur=a;
	while(cur!=MISC_EOL)
	{
		ch=ELEM_TOCHAR(CAR(cur));
		*u++=ch;
		cur=CDR(cur);
	}

	return(ELEM_FROMOBJECT(t));
}

elem Builtin_StringLength(elem a)
{
	elem *t;

	t=ELEM_TOOBJECT(a);
	return(ELEM_FROMFIXNUM(t[0]>>16));
}

elem Builtin_StringRect(elem a)
{
	short *s;
	elem t;
	int xs, ys, i;

	xs=0;
	ys=0;
	i=0;

	s=ELEM_TOSTRING16(a);
	while(*s)
	{
		if(*s<' ')switch(*s)
		{
		case '\n':
			i=0;
			ys++;
			break;
		case '\t':
			i=(i+7)&(~8);
			break;
		default:
			i++;
			break;
		}else i++;
		if(i>xs)xs=i;
		s++;
	}
	if(!xs)xs++;
	if(!ys)ys++;

	t=VECTOR_NEW(2);
	VECTOR_SET(t, 0, FIXNUM(xs));
	VECTOR_SET(t, 1, FIXNUM(ys));

	return(t);
}

elem Builtin_StringRef(elem a, elem b)
{
	elem *t;
	short *u;

	t=ELEM_TOOBJECT(a);
	u=(short *)(t+1);
	return(ELEM_FROMCHAR(u[ELEM_TOFIXNUM(b)+1]));
}

elem Builtin_StringSetN(elem a, elem b, elem c)
{
	elem *t;
	short *u;

	t=ELEM_TOOBJECT(a);
	u=(short *)(t+1);
	u[ELEM_TOFIXNUM(b)+1]=ELEM_TOCHAR(c);
	return(MISC_NULL);
}

elem Builtin_StringLP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(u[i]>v[i])return(MISC_FALSE);
		if(u[i]<v[i])return(MISC_TRUE);
	}
	return(MISC_FALSE);
}

elem Builtin_StringGP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(u[i]<v[i])return(MISC_FALSE);
		if(u[i]>v[i])return(MISC_TRUE);
	}
	return(MISC_FALSE);
}

elem Builtin_StringLEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(u[i]>v[i])return(MISC_FALSE);
		if(u[i]<v[i])return(MISC_TRUE);
	}
	return(MISC_TRUE);
}

elem Builtin_StringGEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(u[i]<v[i])return(MISC_FALSE);
		if(u[i]>v[i])return(MISC_TRUE);
	}
	return(MISC_TRUE);
}

static sh_lower(short c)
{
	if((c>='A') && (c<='Z'))return(c-'A'+'a');
	return(c);
}

elem Builtin_StringCiLP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(sh_lower(u[i])>sh_lower(v[i]))return(MISC_FALSE);
		if(sh_lower(u[i])<sh_lower(v[i]))return(MISC_TRUE);
	}
	return(MISC_FALSE);
}

elem Builtin_StringCiGP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(sh_lower(u[i])<sh_lower(v[i]))return(MISC_FALSE);
		if(sh_lower(u[i])>sh_lower(v[i]))return(MISC_TRUE);
	}
	return(MISC_FALSE);
}

elem Builtin_StringCiLEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(sh_lower(u[i])>sh_lower(v[i]))return(MISC_FALSE);
		if(sh_lower(u[i])<sh_lower(v[i]))return(MISC_TRUE);
	}
	return(MISC_TRUE);
}

elem Builtin_StringCiGEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)!=(t[0]>>16))return(MISC_FALSE);

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)
	{
		if(sh_lower(u[i])<sh_lower(v[i]))return(MISC_FALSE);
		if(sh_lower(u[i])>sh_lower(v[i]))return(MISC_TRUE);
	}
	return(MISC_TRUE);
}

elem Builtin_Substring(elem a, elem b, elem c)
{
	elem *s, *t;
	short *u, *v;
	int l;

	s=ELEM_TOOBJECT(a);
	u=(short *)(s+1);
	l=ELEM_TOFIXNUM(c)-ELEM_TOFIXNUM(b);

	t=sa_alloc(ELEM_SZ+(l*2)+2);
	t[0]=OBJECT_STRING|(l<<16)|256;
	v=(short *)(t+1);
	memcpy(v, u+ELEM_TOFIXNUM(b), l*2);

	return(ELEM_FROMOBJECT(t));
}

elem Builtin_StringAppend(elem a)
{
	elem *s, *t, cur;
	short *u, *v;
	int l, i;

	l=0;
	cur=a;
	while(cur!=MISC_EOL)
	{
		l+=ELEM_TOFIXNUM(Builtin_StringLength(CAR(cur)));
		cur=CDR(cur);
	}

	t=sa_alloc(ELEM_SZ+(l*2)+2);
	t[0]=OBJECT_STRING|(l<<16)|256;
	u=(short *)(t+1);

	cur=a;
	while(cur!=MISC_EOL)
	{
		i=ELEM_TOFIXNUM(Builtin_StringLength(CAR(cur)));
		s=ELEM_TOOBJECT(CAR(cur));
		v=(short *)(s+1);
		memcpy(u, v, i*2);
		u+=i;
		cur=CDR(cur);
	}

	return(ELEM_FROMOBJECT(t));
}

elem Builtin_StringToList(elem a)
{
	elem *t, lst;
	short *u;
	int l, i;

	t=ELEM_TOOBJECT(a);
	u=(short *)(t+1);
	l=t[0]>>16;

	lst=MISC_EOL;
	for(i=0; i<l; i++)lst=CONS(ELEM_FROMCHAR(u[i]), lst);
	lst=TyFcn_NReverse(lst);
	return(lst);
}

elem Builtin_StringCopy(elem a)
{
	elem *s, *t;
	int l;

	t=ELEM_TOOBJECT(a);
	l=t[0]>>16;
	s=sa_alloc(ELEM_SZ+(l*2)+2);
	s[0]=OBJECT_STRING|(l<<16);
	memcpy(s+1, t+1, l*2);

	return(ELEM_FROMOBJECT(s));
}

elem Builtin_StringFillN(elem a, elem b)
{
	elem *t;
	short *u;
	int i, l;

	t=ELEM_TOOBJECT(a);
	l=t[0]>>16;
	u=(short *)(t+1);
	for(i=0; i<l; i++)u[i]=ELEM_TOCHAR(b);

	return(MISC_UNDEFINED);
}

// vectors

elem Builtin_VectorP(elem a)
{
	elem t;
	if(!ELEM_VECTORP(a))return(MISC_FALSE);
	t=TyFcn_VectorType(a);
	if(ELEM_TOFIXNUM(t)>=32)return(MISC_FALSE);
	return(MISC_TRUE);
}

elem Builtin_MakeVector(elem a, elem b)
{
	elem t;
	int i;

	t=TyFcn_NewVector(a);
	if(b!=MISC_EOL)for(i=0; i<ELEM_TOFIXNUM(a); i++)
//		TyFcn_ObjPokeElem(t, ELEM_FROMFIXNUM(i+2), CAR(b));
		TyFcn_VectorSet(t, ELEM_FROMFIXNUM(i), CAR(b));

	return(t);
}

elem Builtin_VectorRef(elem a, elem b)
{
	elem x;
//	x=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(ELEM_TOFIXNUM(b)+2));
	x=TyFcn_VectorRef(a, b);
	interp_context->rax=TyFcn_VectorRefM(a, b);
	return(x);
}

elem Builtin_VectorSetN(elem a, elem b, elem c)
{
//	TyFcn_ObjPokeElem(a, ELEM_FROMFIXNUM(ELEM_TOFIXNUM(b)+2), c);
	TyFcn_VectorSet(a, b, c);
	return(MISC_UNDEFINED);
}

elem Builtin_VectorToList(elem a)
{
	elem t;
	int i, c;

	c=ELEM_TOFIXNUM(TyFcn_VectorLength(a));
	t=MISC_EOL;
	for(i=0; i<c; i++)t=CONS(TyFcn_VectorRef(a, ELEM_FROMFIXNUM(i)), t);
	t=TyFcn_NReverse(t);
	return(t);
}

elem Builtin_VectorFillN(elem a, elem b)
{
	int i, l;

	l=ELEM_TOFIXNUM(TyFcn_VectorLength(a));
	for(i=0; i<l; i++)TyFcn_VectorSet(a, ELEM_FROMFIXNUM(i), b);

	return(MISC_UNDEFINED);
}

elem Builtin_MakeTaggedVector(elem a, elem b, elem c)
{
	elem t;
	int i;

	t=TyFcn_NewTypedVector(a, b);
	if(c!=MISC_EOL)for(i=0; i<ELEM_TOFIXNUM(a); i++)
//		TyFcn_ObjPokeElem(t, ELEM_FROMFIXNUM(i+2), CAR(b));
		TyFcn_VectorSet(t, ELEM_FROMFIXNUM(i), CAR(c));

	return(t);
}

// control
elem Builtin_ProcedureP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_FUNCTIONP(a)|ELEM_CLOSUREP(a)));
}

// extensions
elem Builtin_LocativeP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_LOCATIVEP(a)));
}

elem Builtin_LocativeToInteger(elem a)
{
	elem b;
	b=(elem)ELEM_TOLOCATIVE(a);
	return((b&(~3))|TYPE_FIXNUM);
}

elem Builtin_IntegerToLocativeM(elem a)
{
	return(ELEM_FROMLOCATIVE((elem *)(a&(~3))));
}

elem Builtin_Contents(elem a)
{
	elem *p;
	p=ELEM_TOLOCATIVE(a);

	return(p[0]);
}

elem Builtin_SetM(elem a, elem b)
{
	elem *p;
	p=ELEM_TOLOCATIVE(a);
	p[0]=b;
	return(MISC_UNDEFINED);
}

elem Builtin_ClosureP(elem a)
{
	return(ELEM_FROMBOOL(ELEM_CLOSUREP(a)));
}

elem CleanSyntax_Inner(elem a, elem *lst)
{
	elem cur;

#if 0
	if(!ELEM_CONSP(a))return(a);

	if(ELEM_CONSP(CAR(a)))if(CAR(CAR(a))==SYM("doublemark"))
	{
		cur=*lst;
		while(ELEM_CONSP(cur))
		{
			if(CAR(CAR(cur))==CADR(CAR(a)))
			{
				cur=CADR(CAR(cur));
				break;
			}
			cur=CDR(cur);
		}
		if(cur==MISC_EOL)
		{
			cur=Builtin_Gensym();
			*lst=CONS(CONS(CADR(CAR(a)), CONS(cur, MISC_EOL)), *lst);
		}
		return(CONS(cur, CleanSyntax_Inner(CDR(a), lst)));
	}

	return(CONS(CleanSyntax_Inner(CAR(a), lst), CleanSyntax_Inner(CDR(a), lst)));

#else
	if(ELEM_CONSP(a))
		return(CONS(
			CleanSyntax_Inner(CAR(a), lst),
			CleanSyntax_Inner(CDR(a), lst)));

	if(ELEM_SYMHYGENICP(a))
	{
//		sa_print("hygvar.\n");
		cur=*lst;
		while(ELEM_CONSP(cur))
		{
			if(CAR(CAR(cur))==a)
				return(CADR(CAR(cur)));
			cur=CDR(cur);
		}
		cur=Builtin_Gensym();
		*lst=CONS(CONS(a, CONS(cur, MISC_EOL)), *lst);
		return(cur);
	}

//	sa_print("normal: ");
//	TyFcn_DumpElem(a);
//	sa_print("\n");
	return(a);
#endif
}

elem Builtin_CleanSyntax(elem a)
{
	elem gslst;

	gslst=MISC_EOL;
	return(CleanSyntax_Inner(a, &gslst));
}

elem SyntaxFunc_Inner(elem a, elem *lst)
{
	elem cur, t, nlst;
	InterpCtx *ctx;

	if(ELEM_CONSP(a))if(ELEM_CONSP(CAR(a)))
	{
		if(CAR(CAR(a))==SYM("unquote"))
		{
//			cur=Namespace2_Lookup(interp_context->ep_n, interp_context->ep_d, CADR(CAR(a)));
			ctx=HpiInterp_RunCtxSafe(CADR(CAR(a)), interp_context);
			cur=ctx->ax;
			return(CONS(cur, SyntaxFunc_Inner(CDR(a), lst)));
		}else if(CAR(CAR(a))==SYM("unquote-splicing"))
		{
			ctx=HpiInterp_RunCtxSafe(CADR(CAR(a)), interp_context);
			cur=TyFcn_ListCopy(ctx->ax);
			TyFcn_NAppend(cur, SyntaxFunc_Inner(CDR(a), lst));
			return(cur);
		}else if((CAR(CAR(a))==SYM("let")) || (CAR(CAR(a))==SYM("rlet")))
		{
			nlst=*lst;
			cur=CADR(CAR(a));
			while(ELEM_CONSP(cur))
			{
				t=Builtin_Gensym();
				nlst=CONS(CONS(CAR(CAR(cur)), CONS(t, MISC_EOL)), nlst);
				cur=CDR(cur);
			}

			cur=SyntaxFunc_Inner(CDDR(a), &nlst);
			cur=CONS(SyntaxFunc_Inner(CADR(a), lst), cur);
			cur=CONS(SyntaxFunc_Inner(CAR(a), lst), cur);

			return(cur);
		}else if((CAR(CAR(a))==SYM("letrec")) || (CAR(CAR(a))==SYM("let*")))
		{
			nlst=*lst;
			cur=CADR(CAR(a));
			while(ELEM_CONSP(cur))
			{
				t=Builtin_Gensym();
				nlst=CONS(CONS(CAR(CAR(cur)), CONS(t, MISC_EOL)), nlst);
				cur=CDR(cur);
			}

			cur=CONS(SyntaxFunc_Inner(CAR(a), &nlst), SyntaxFunc_Inner(CDR(a), &nlst));

			return(cur);
		}else if(CAR(CAR(a))==SYM("quote"))
		{
			cur=CONS(SyntaxFunc_Inner(CAR(a), &nlst), CDR(a));
			return(cur);
		}
	}

	if(ELEM_CONSP(a))
		return(CONS(
			SyntaxFunc_Inner(CAR(a), lst),
			SyntaxFunc_Inner(CDR(a), lst)));

	if(ELEM_SYMHYGENICP(a))
		return(TyFcn_KeywordBase(a));

	if(ELEM_SYMBOLP(a) && !ELEM_SYMHYGENICP(a) && !ELEM_SYMKEYWORDP(a))
	{
		cur=*lst;
		while(ELEM_CONSP(cur))
		{
			if(CAR(CAR(cur))==a)
				return(CADR(CAR(cur)));
			cur=CDR(cur);
		}
		cur=Namespace2_Lookup(interp_context->ep_n, interp_context->ep_d, a);
		if(cur!=MISC_UNDEFINED)
		{
			t=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(2), ELEM_FROMFIXNUM(VECTOR_SYNREF));
			TyFcn_VectorSet(t, ELEM_FROMFIXNUM(0), a);
			TyFcn_VectorSet(t, ELEM_FROMFIXNUM(1), cur);
			*lst=CONS(CONS(a, CONS(t, MISC_EOL)), *lst);
			return(t);
		}
		cur=Namespace2_Lookup(interp_context->sep_n, interp_context->sep_d, a);
		if(cur!=MISC_UNDEFINED)
		{
			t=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(2), ELEM_FROMFIXNUM(VECTOR_SYNSYN));
			TyFcn_VectorSet(t, ELEM_FROMFIXNUM(0), a);
			TyFcn_VectorSet(t, ELEM_FROMFIXNUM(1), cur);
			*lst=CONS(CONS(a, CONS(t, MISC_EOL)), *lst);
			return(t);
		}
		cur=Builtin_Gensym();
		*lst=CONS(CONS(a, CONS(cur, MISC_EOL)), *lst);
		return(cur);
	}

	return(a);
}

elem Builtin_SyntaxFunc(elem a)
{
	elem gslst;

	gslst=MISC_EOL;
	return(SyntaxFunc_Inner(a, &gslst));
}

/*
this is intended to help facilitate self modifying code,
this compiles some code and returns a fragment, which may only be safely
used within the defining context/frame.
 */
elem Builtin_Build(elem a)
{
	elem x;

	x=CONS(SYM("return"), MISC_EOL);
	x=CONS(x, MISC_EOL);
	return(HpiComp_Compile(a, x, interp_context, 1));
}

elem Builtin_Eval(elem a, elem b)
{
	InterpCtx *ctx;
	elem t;
	t=HpiComp_Compile(a, form_halt, interp_context, 0);
	if(t==MISC_UNDEFINED)return(t);

	ctx=HpiInterp_RunCtxSafe(t, interp_context);
	return(ctx->ax);
}

elem Builtin_LsEnvInner(elem a)
{
	elem lst, cur, t, cur2;

	lst=MISC_EOL;
	cur=a;
	while(ELEM_CONSP(cur))
	{
		if(ELEM_CONSP(CAR(cur)))
		{
			t=Builtin_LsEnvInner(CAR(cur));
			cur2=t;
			while(ELEM_CONSP(cur2))
			{
				if(ELEM_SYMBOLP(CAR(cur2)))
					if(TyFcn_ObjectInListP(CAR(cur2), lst)==MISC_FALSE)
					lst=CONS(CAR(cur2), lst);
				cur2=CDR(cur2);
			}
		}else if(ELEM_SYMBOLP(CAR(cur)))
			if(TyFcn_ObjectInListP(CAR(cur), lst)==MISC_FALSE)
			lst=CONS(CAR(cur), lst);

		cur=CDR(cur);
	}
	return(lst);
}

elem Builtin_LsEnv(elem a)
{
	elem cur;

	cur=TyFcn_VectorRef(a, ELEM_FROMFIXNUM(0));
	return(Builtin_LsEnvInner(cur));
}

elem Builtin_ClosureBody(elem a)
{
	elem cur;

	if(!ELEM_CLOSUREP(a))return(MISC_FALSE);

	cur=TyFcn_VectorRef(a, ELEM_FROMFIXNUM(5));
	return(cur);
}

elem Builtin_Time()
{
	return(ELEM_FROMFLONUM(Sys_TimeMS()/1000.0));
}

elem Builtin_TimeMS()
{
	return(ELEM_FROMFIXNUM(Sys_TimeMS()));
}

elem Builtin_Print(elem a)
{
	elem cur;

	cur=a;
	while(ELEM_CONSP(cur))
	{
		TyPrint_PrintFlags(CAR(cur),
			FIXNUM(TYPRINT_DISPLAY));
		cur=CDR(cur);
	}

	return(MISC_NULL);
}

elem Builtin_PrintCode(elem a)
{
	elem cur;

	cur=a;
	while(ELEM_CONSP(cur))
	{
		TyPrint_PrintFlags(CAR(cur),
			FIXNUM(TYPRINT_CODE));
		cur=CDR(cur);
	}
	TyPrint_PrintFlags(STRING("\n"),
		FIXNUM(TYPRINT_DISPLAY));

	return(MISC_NULL);
}

elem Builtin_PrintString(elem a)
{
	elem cur, x, t;

	x=MISC_EOL;
	cur=a;
	while(ELEM_CONSP(cur))
	{
		t=TyPrint_PrintString(CAR(cur),
			FIXNUM(TYPRINT_DISPLAY));
		x=CONS(t, x);
		cur=CDR(cur);
	}
	t=TyPrint_PrintString(TyFcn_Reverse(x),
		FIXNUM(TYPRINT_FORMATTED));

	return(t);
}

elem Builtin_ParseString(elem a)
{
	char *s;
	elem t;

	s=ELEM_TOSTRING(a);
	t=ScmParse_Line(&s, 0);

	return(t);
}

elem Builtin_Flatten(elem a)
{
	elem t;

	t=a;
	if(ELEM_CLOSUREP(a))t=Builtin_ClosureBody(a);
	if(ELEM_ENVOBJP(a))t=TyObj_ObjectFlatten(a);
	if(ELEM_TYPEXP(a))t=TypeX_Flatten(a);
	return(t);
}

elem Builtin_Random(elem num)
{
	double f;
//	f=(1.0*rand())/RAND_MAX*TOINT(num);
	return(FIXNUM((int)f));
}

elem Builtin_Weaken(elem ref)
{
	elem t;

	t=ref;
	if(ELEM_CONSP(t))t=ELEM_FROMWEAKCONS(ELEM_TOCONS(ref));
	if(ELEM_OBJECTP(t))t=ELEM_FROMWEAKOBJECT(ELEM_TOOBJECT(ref));

	return(t);
}

// init

int Builtin_Init()
{
//	kprint("M_1\n");
	Interp_DefinePrimative("eq?",			&Builtin_EqP,			2);
	Interp_DefinePrimative("eqv?",			&Builtin_EqvP,			2);
	Interp_DefinePrimative("equal?",		&Builtin_EqualP,		2);
	Interp_DefinePrimative("match?",		&TyFcn_MatchP,			3);
	Interp_DefinePrimative("match",			&TyFcn_MatchV,			2);
	Interp_DefinePrimative("matchv?",		&TyFcn_MatchP2,			2);
	Interp_DefinePrimative("not",			&Builtin_Not,			1);

	Interp_DefinePrimative("==",			&Builtin_EqP,			2);
	Interp_DefinePrimative("=",			&Builtin_EqualP,		2);
	Interp_DefinePrimative("!==",			&Builtin_NEqP,			2);
	Interp_DefinePrimative("!=",			&Builtin_NEqualP,		2);

	Interp_DefinePrimative("bit-and?",		&Builtin_BitAndP,		2);
	Interp_DefinePrimative("bit-or?",		&Builtin_BitOrP,		2);
	Interp_DefinePrimative("bit-and",		&Builtin_BitAnd,		2);
	Interp_DefinePrimative("bit-or",		&Builtin_BitOr,			2);

	Interp_DefinePrimative("boolean?",		&Builtin_BooleanP,		1);
	Interp_DefinePrimative("pair?",			&Builtin_PairP,			1);

	Interp_DefinePrimative("cons",			&TyFcn_Cons,			2);
//	Interp_DefinePrimative("car",			&TyFcn_Car,			1);
//	Interp_DefinePrimative("cdr",			&TyFcn_Cdr,			1);
	Interp_DefinePrimative("car",			&Builtin_Car,			1);
	Interp_DefinePrimative("cdr",			&Builtin_Cdr,			1);
	Interp_DefinePrimative("set-car!",		&TyFcn_SetCar,			2);
	Interp_DefinePrimative("set-cdr!",		&TyFcn_SetCdr,			2);
	Interp_DefinePrimative("null?",			&Builtin_NullP,			1);
	Interp_DefinePrimative("list?",			&Builtin_ListP,			1);
	Interp_DefinePrimative("list",			&Builtin_List,			-1);
	Interp_DefinePrimative("length",		&TyFcn_ListLength,		1);
	Interp_DefinePrimative("append",		&Builtin_Append,		-1);
	Interp_DefinePrimative("reverse",		&TyFcn_Reverse,			1);
	Interp_DefinePrimative("list-ref",		&TyFcn_ListRef,			2);

	Interp_DefinePrimative("symbol?",		&Builtin_SymbolP,		1);
	Interp_DefinePrimative("symbol->string",	&Builtin_SymbolToString,	1);
	Interp_DefinePrimative("string->symbol",	&Builtin_StringToSymbol,	1);
	Interp_DefinePrimative("gensym",		&Builtin_Gensym,		0);
	Interp_DefinePrimative("keyword-base",		&TyFcn_KeywordBase,		1);

	Interp_DefinePrimative("char?",			&Builtin_CharP,			1);
	Interp_DefinePrimative("char=?",		&Builtin_CharEP,		2);
	Interp_DefinePrimative("char<?",		&Builtin_CharLEP,		2);
	Interp_DefinePrimative("char>?",		&Builtin_CharGEP,		2);
	Interp_DefinePrimative("char<=?",		&Builtin_CharLEP,		2);
	Interp_DefinePrimative("char>=?",		&Builtin_CharGEP,		2);
	Interp_DefinePrimative("char-ci=?",		&Builtin_CharCiEP,		2);
	Interp_DefinePrimative("char-ci<?",		&Builtin_CharCiLEP,		2);
	Interp_DefinePrimative("char-ci>?",		&Builtin_CharCiGEP,		2);
	Interp_DefinePrimative("char-ci<=?",		&Builtin_CharCiLEP,		2);
	Interp_DefinePrimative("char-ci>=?",		&Builtin_CharCiGEP,		2);
	Interp_DefinePrimative("char-upcase",		&Builtin_CharUpCase,		1);
	Interp_DefinePrimative("char-downcase",		&Builtin_CharDownCase,		1);
	Interp_DefinePrimative("char->integer",		&Builtin_CharToInteger,		1);
	Interp_DefinePrimative("integer->char",		&Builtin_IntegerToChar,		1);
	Interp_DefinePrimative("char-alphabetic?",	&Builtin_CharAlphabeticP,	1);
	Interp_DefinePrimative("char-numeric?",		&Builtin_CharNumericP,		1);
	Interp_DefinePrimative("char-whitespace?",	&Builtin_CharWhitespaceP,	1);
	Interp_DefinePrimative("char-upper-case?",	&Builtin_CharUpperCaseP,	1);
	Interp_DefinePrimative("char-lower-case?",	&Builtin_CharLowerCaseP,	1);

	Interp_DefinePrimative("string?",		&Builtin_StringP,		1);
	Interp_DefinePrimative("make-string",		&Builtin_MakeString,		-2);
	Interp_DefinePrimative("string",		&Builtin_String,		-1);
	Interp_DefinePrimative("string-length",		&Builtin_StringLength,		1);
	Interp_DefinePrimative("string-rect",		&Builtin_StringRect,		1);
	Interp_DefinePrimative("string-ref",		&Builtin_StringRef,		2);
	Interp_DefinePrimative("string-set!",		&Builtin_StringSetN,		3);
	Interp_DefinePrimative("string=?",		&TyFcn_StringEP,		2);
	Interp_DefinePrimative("string-ci=?",		&TyFcn_StringCiEP,		2);
	Interp_DefinePrimative("string<?",		&Builtin_StringLP,		2);
	Interp_DefinePrimative("string-ci<?",		&Builtin_StringCiLP,		2);
	Interp_DefinePrimative("string>?",		&Builtin_StringGP,		2);
	Interp_DefinePrimative("string-ci>?",		&Builtin_StringCiGP,		2);
	Interp_DefinePrimative("string<=?",		&Builtin_StringLEP,		2);
	Interp_DefinePrimative("string-ci<=?",		&Builtin_StringCiLEP,		2);
	Interp_DefinePrimative("string>=?",		&Builtin_StringGEP,		2);
	Interp_DefinePrimative("string-ci>=?",		&Builtin_StringCiGEP,		2);
	Interp_DefinePrimative("substring",		&Builtin_Substring,		3);
	Interp_DefinePrimative("string-append",		&Builtin_StringAppend,		-1);
	Interp_DefinePrimative("string->list",		&Builtin_StringToList,		1);
	Interp_DefinePrimative("list->string",		&Builtin_String,		1);
	Interp_DefinePrimative("string-copy",		&Builtin_StringCopy,		1);
	Interp_DefinePrimative("string-fill!",		&Builtin_StringFillN,		2);

	Interp_DefinePrimative("vector?",		&Builtin_VectorP,		1);
	Interp_DefinePrimative("make-vector",		&Builtin_MakeVector,		-2);
	Interp_DefinePrimative("vector",		&TyFcn_ListToVector,		-1);
	Interp_DefinePrimative("vector-length",		&TyFcn_VectorLength,		1);
	Interp_DefinePrimative("vector-ref",		&Builtin_VectorRef,		2);
	Interp_DefinePrimative("vector-set!",		&Builtin_VectorSetN,		3);
	Interp_DefinePrimative("string->list",		&Builtin_VectorToList,		1);
	Interp_DefinePrimative("list->vector",		&TyFcn_ListToVector,		1);
	Interp_DefinePrimative("vector-fill!",		&Builtin_VectorFillN,		2);
	Interp_DefinePrimative("make-typed-vector",	&Builtin_MakeTaggedVector,	-3);
	Interp_DefinePrimative("vector-copy",		&TyFcn_CopyVector,		1);

	Interp_DefinePrimative("locative?",		&Builtin_LocativeP,		1);
	Interp_DefinePrimative("locative->integer",	&Builtin_LocativeToInteger,	1);
	Interp_DefinePrimative("integer->locative*",	&Builtin_IntegerToLocativeM,	1);
	Interp_DefinePrimative("contents",		&Builtin_Contents,		1);
	Interp_DefinePrimative("set*",			&Builtin_SetM,			2);
	Interp_DefinePrimative("locative-new",		&TyFcn_LocativeNew,		3);
	Interp_DefinePrimative("locative-copy",		&TyFcn_LocativeCopy,		1);

	Interp_DefinePrimative("car*",			&TyFcn_CarM,			1);
	Interp_DefinePrimative("cdr*",			&TyFcn_CdrM,			1);

	Interp_DefinePrimative("closure?",		&Builtin_ClosureP,		1);

	Interp_DefinePrimative("clean-syntax",		&Builtin_CleanSyntax,		1);
	Interp_DefinePrimative("syntax-func",		&Builtin_SyntaxFunc,		1);

	Interp_DefinePrimative("build",			&Builtin_Build,			1);
	Interp_DefinePrimative("eval",			&Builtin_Eval,			-2);

	Interp_DefinePrimative("ls-env",		&Builtin_LsEnv,			1);
	Interp_DefinePrimative("closure-body",		&Builtin_ClosureBody,		1);
	Interp_DefinePrimative("time",			&Builtin_Time,			0);
	Interp_DefinePrimative("time-ms",		&Builtin_TimeMS,		0);

	Interp_DefinePrimative("print",			&Builtin_Print,			-1);
	Interp_DefinePrimative("print-code",		&Builtin_PrintCode,		-1);
//	Interp_DefinePrimative("write-string",		&Builtin_WriteString,		-1);
	Interp_DefinePrimative("print-string",		&Builtin_PrintString,		-1);
	Interp_DefinePrimative("parse-string",		&Builtin_ParseString,		1);

	Interp_DefinePrimative("flatten",		&Builtin_Flatten,		1);
//	Interp_DefinePrimative("random",		&Builtin_Random,		1);
	Interp_DefinePrimative("weaken",		&Builtin_Weaken,		1);

	Interp_DefinePrimative("thread",		&Interp_Thread,			1);
	Interp_DefinePrimative("block-thread",		&Interp_BlockThread,		1);
	Interp_DefinePrimative("unblock-thread",	&Interp_UnblockThread,		1);
	Interp_DefinePrimative("recieve-atom",		&Interp_RecieveThread,		0);
	Interp_DefinePrimative("sleep",			&Interp_SleepThread,		1);


	Interp_DefinePrimative("display",		(elem (*)())&TyFcn_DisplayElem,	1);
	Interp_DefinePrimative("load",			(elem (*)())&Interp_Load,	1);


	Interp_DefinePrimative("sym-count",	&TyFcn_SymCount,	1);

	Interp_DefineVar("sys-root", MISC_NULL);

	TyMath_Init();
}
