/*
numbers will be vectors with the type "bignum".

s32 will be used for bignums.
f64 will be used for flonums.

bignums will have the words ordered in a low-high fashion.
on little endian machines bignums can be computed as an array of shorts, on big endian systems
the order would need to be swapped.
 */

#include <scmcc.h>

#include <math.h>

#if 0
elem TyMath_AddBignum(elem a, elem b)
{
	elem c;
	elem *s, *t, *u;
	unsigned short *x, *y, *z;

	int al, al, ds;

	int l, g, i, j;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(a);

	al=ELEM_TOFIXNUM(TyFcn_VectorLength(a));
	bl=ELEM_TOFIXNUM(TyFcn_VectorLength(b));

	if(al<bl)
		l=al;
		else l=bl;
	if(al>bl)
		g=al;
		else g=bl;

	x=(short *)(s+1);
	y=(short *)(t+1);
	z=sa_malloc((g+1)*2);

	ds=0;
	if(x[(al*2)-1]&0x8000)ds^=1;
	if(y[(bl*2)-1]&0x8000)ds^=1;

	j=0;
	for(i=0; i<l; i++)
	{
		j+=x[i]+y[i];
		z[i]=j&0xffff;
		j>>=16;
	}
	if(ELEM_TOFIXNUM(TyFcn_VectorLength(a))<ELEM_TOFIXNUM(TyFcn_VectorLength(b)))
		x=y;
	for(; i<g; i++)
	{
		j+=x[i];
		z[i]=j&0xffff;
		j>>=16;
	}
	z[i]=j&0xffff;

}
#endif

int TyMath_ToBignum(elem a, unsigned short *buf, int *len)
{
	double f;
	elem t, *s;
	int i;

	if(ELEM_WIDENUMP(a))
	{
		s=ELEM_TOOBJECT(a);
		i=(*s>>16)&0xfff;
		memcpy(buf, s+1, i*sizeof(unsigned short));
		*len=i;
		return(0);
	}

	if(ELEM_FLONUMP(a))
	{
		s=ELEM_TOOBJECT(a);
		f=((double *)s)[1];
		i=0;
		while(f>=1.0)
		{
			buf[i++]=((int)f)&0xffff;
			f/=65536;
		}
		*len=i;
		return(0);
	}

	if(ELEM_FIXNUMP(a))
	{
		i=ELEM_TOFIXNUM(a);
		*len=2;
		buf[0]=i&0xffff;
		buf[1]=(i>>8)&0xffff;
		return(0);
	}

	return(-1);
}

elem TyMath_FromBignum(unsigned short *buf, int *len)
{
	elem t, *s;
	int i, l;
	unsigned short *dbuf;

	l=*len;
	s=sa_alloc(ELEM_SZ+(l*2));
	s[0]=OBJECT_BIGNUM|(VECTOR_U16<<8)|(l<<16);

	dbuf=(unsigned short *)(s[1]);

	for(i=0; i<l; i++)
		dbuf[i]=buf[i];

	t=ELEM_FROMOBJECT(s);
	return(t);
}


double TyMath_ToDouble(elem a)
{
	double x;
	elem t, *s;

	if(ELEM_FLONUMP(a))
	{
		s=ELEM_TOOBJECT(a);
		x=((double *)s)[1];
		return(x);
	}

	if(ELEM_FIXNUMP(a))
	{
		x=ELEM_TOFIXNUM(a);
		return(x);
	}
	return(0);
}

elem TyMath_FromDouble(double a)
{
	elem t, *s;

//	t=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(1), ELEM_FROMFIXNUM(VECTOR_F64));
//	s=ELEM_TOOBJECT(t);

//	printf("f->e %lf\n", a);
//	return(ELEM_FROMFIXNUM((int)a));

	if((a==(int)a) && (fabs(a)<(1<<27)))return(ELEM_FROMFIXNUM((int)a));

	s=sa_alloc(4*ELEM_SZ);
	s[0]=OBJECT_BIGNUM|(VECTOR_F64<<8)|(1<<16);

	((double *)s)[1]=a;

	t=ELEM_FROMOBJECT(s);
	return(t);
}

elem TyMath_ToFlonum(elem a)
{
	elem t, *s;

	if(ELEM_FLONUMP(a))return(a);

	if(ELEM_FIXNUMP(a))
	{
		t=TyFcn_NewTypedVector(ELEM_FROMFIXNUM(1), ELEM_FROMFIXNUM(VECTOR_F64));
		s=ELEM_TOOBJECT(t);
		((double *)s)[1]=ELEM_TOFIXNUM(a);
		return(t);
	}
	return(MISC_UNDEFINED);
}

int TyMath_CmpFlonum(elem a, elem b)
{
	double x, y;

	x=TyMath_ToDouble(a);
	y=TyMath_ToDouble(b);

	if(x<y)return(-1);
	if(x>y)return(1);
	return(0);
}

elem TyMath_AddFlonum(elem lst)
{
	double x;
	elem cur;

	x=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		x+=TyMath_ToDouble(CAR(cur));
		cur=CDR(cur);
	}

	cur=TyMath_FromDouble(x);
	return(cur);
}

elem TyMath_SubFlonum(elem lst)
{
	double x;
	elem cur;

	x=0;
	cur=lst;

	if(LENGTH(lst)>1)
	{
		x=TOFLOAT(CAR(cur));
		cur=CDR(cur);
	}

	while(ELEM_CONSP(cur))
	{
		x-=TOFLOAT(CAR(cur));
		cur=CDR(cur);
	}

	cur=FLONUM(x);
	return(cur);
}


elem TyMath_MulFlonum(elem lst)
{
	double x;
	elem cur;

	x=1;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		x*=TyMath_ToDouble(CAR(cur));
		cur=CDR(cur);
	}

	cur=TyMath_FromDouble(x);
	return(cur);
}

elem TyMath_DivFlonum(elem lst)
{
	double x;
	elem cur;

	x=1;
	cur=lst;

	if(ELEM_TOFIXNUM(TyFcn_ListLength(lst))>1)
	{
		x=TyMath_ToDouble(CAR(cur));
		cur=CDR(cur);
	}

	while(ELEM_CONSP(cur))
	{
		x/=TyMath_ToDouble(CAR(cur));
		cur=CDR(cur);
	}

	cur=TyMath_FromDouble(x);
	return(cur);
}

// numbers

elem TyMath_ZeroP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(TyMath_ToDouble(a)==0));
	return(ELEM_FROMBOOL(!ELEM_TOFIXNUM(a)));
}

elem TyMath_NonZeroP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(TyMath_ToDouble(a)!=0));
	return(ELEM_FROMBOOL(ELEM_TOFIXNUM(a)));
}

elem TyMath_PositiveP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(TyMath_ToDouble(a)>0));
	return(ELEM_FROMBOOL(ELEM_TOFIXNUM(a)>0));
}

elem TyMath_NegativeP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(TyMath_ToDouble(a)<0));
	return(ELEM_FROMBOOL(ELEM_TOFIXNUM(a)<0));
}

elem TyMath_EvenP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(!((int)TyMath_ToDouble(a)%2)));
	return(ELEM_FROMBOOL(!(ELEM_TOFIXNUM(a)%2)));
}

elem TyMath_OddP(elem a)
{
	if(ELEM_FLONUMP(a))return(ELEM_FROMBOOL(!((int)TyMath_ToDouble(a)%2)));
	return(ELEM_FROMBOOL(ELEM_TOFIXNUM(a)%2));
}

elem TyMath_Min(elem a)
{
	elem cur;
	double i, j;

//	j=ELEM_TOFIXNUM(CAR(a));
	j=TyMath_ToDouble(CAR(a));

	cur=a;
	while(cur!=MISC_EOL)
	{
//		i=ELEM_TOFIXNUM(CAR(cur));
		i=TyMath_ToDouble(CAR(cur));
		if(i<j)j=i;
		cur=CDR(cur);
	}
//	return(ELEM_FROMFIXNUM(j));
	return(TyMath_FromDouble(j));
}

elem TyMath_Max(elem a)
{
	elem cur;
//	int i, j;
	double i, j;

//	j=ELEM_TOFIXNUM(CAR(a));
	j=TyMath_ToDouble(CAR(a));

	cur=a;
	while(cur!=MISC_EOL)
	{
//		i=ELEM_TOFIXNUM(CAR(cur));
		i=TyMath_ToDouble(CAR(cur));
		if(i>j)j=i;
		cur=CDR(cur);
	}
//	return(ELEM_FROMFIXNUM(j));
	return(TyMath_FromDouble(j));
}

elem TyMath_AddFixnum(elem lst)
{
	int accum;
	elem cur;

//	if(ELEM_FLONUMP(CAR(lst)))
	return(TyMath_AddFlonum(lst));

	accum=0;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		accum+=ELEM_TOFIXNUM(TyFcn_Car(cur));
		cur=TyFcn_Cdr(cur);
	}
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_MultiplyFixnum(elem lst)
{
	int accum;
	elem cur;

//	if(ELEM_FLONUMP(CAR(lst)))
	return(TyMath_MulFlonum(lst));

	accum=1;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		accum*=ELEM_TOFIXNUM(TyFcn_Car(cur));
		cur=TyFcn_Cdr(cur);
	}
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_SubtractFixnum(elem a, elem b)
{
	elem cur;
	int accum;

//	if(ELEM_FLONUMP(a))
	return(TyMath_SubFlonum(CONS(a, b)));

	if(ELEM_EOLP(b))accum=0-ELEM_TOFIXNUM(a);
		else accum=ELEM_TOFIXNUM(a);
	if(ELEM_FIXNUMP(b))accum-=ELEM_TOFIXNUM(b);
	if(ELEM_CONSP(b))
	{
		cur=b;
		while(cur!=MISC_EOL)
		{
			accum-=ELEM_TOFIXNUM(CAR(cur));
			cur=CDR(cur);
		}
	}
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_DivideFixnum(elem a, elem b)
{
	elem cur;
	int accum;

//	if(ELEM_FLONUMP(a))
	return(TyMath_DivFlonum(CONS(a, b)));

	if(ELEM_EOLP(b))accum=1/ELEM_TOFIXNUM(a);
		else accum=ELEM_TOFIXNUM(a);
	if(ELEM_FIXNUMP(b))accum/=ELEM_TOFIXNUM(b);
	if(ELEM_CONSP(b))
	{
		cur=b;
		while(cur!=MISC_EOL)
		{
			accum/=ELEM_TOFIXNUM(CAR(cur));
			cur=CDR(cur);
		}
	}
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_Quotient(elem a, elem b)
{
	int accum;

	if(ELEM_FLONUMP(a))a=ELEM_FROMFIXNUM((int)TyMath_ToDouble(a));
	if(ELEM_FLONUMP(b))b=ELEM_FROMFIXNUM((int)TyMath_ToDouble(b));

	accum=ELEM_TOFIXNUM(a)/ELEM_TOFIXNUM(b);
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_Remainder(elem a, elem b)
{
	int accum, i, j;

	if(ELEM_FLONUMP(a))a=ELEM_FROMFIXNUM((int)TyMath_ToDouble(a));
	if(ELEM_FLONUMP(b))b=ELEM_FROMFIXNUM((int)TyMath_ToDouble(b));

	i=ELEM_TOFIXNUM(a);
	j=ELEM_TOFIXNUM(b);
	accum=i%j;
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_Modulo(elem a, elem b)
{
	int accum, i, j;

	if(ELEM_FLONUMP(a))a=ELEM_FROMFIXNUM((int)TyMath_ToDouble(a));
	if(ELEM_FLONUMP(b))b=ELEM_FROMFIXNUM((int)TyMath_ToDouble(b));

	i=ELEM_TOFIXNUM(a);
	if(i<0)i=0-i;
	j=ELEM_TOFIXNUM(b);
	accum=i%j;
	if(j<0)accum=0-accum;
	return(ELEM_FROMFIXNUM(accum));
}

elem TyMath_NumberToString(elem a)
{
	char buf[16];

	if(ELEM_FLONUMP(a))
	{
		sprintf(buf, "%g", TyMath_ToDouble(a));
		return(ELEM_FROMSTRING(buf));
	}

	sprintf(buf, "%d", ELEM_TOFIXNUM(a));
	return(ELEM_FROMSTRING(buf));
}

elem TyMath_StringToNumber(elem a)
{
	char *s, *t;
	int f;

	s=ELEM_TOSTRING(a);
	t=s;
	f=0;
	while(*t)
	{
		if(*t=='.')f=1;
		if(*t=='e')f=1;
		t++;
	}
	if(!f)return(ELEM_FROMFIXNUM(atoi(s)));
		return(ELEM_FROMFLONUM(atof(s)));
}

elem TyMath_GreaterP(elem a, elem b)
{
//	if(ELEM_FLONUMP(a))
	return((TyMath_ToDouble(a)>TyMath_ToDouble(b))?MISC_TRUE:MISC_FALSE);
	
//	return((ELEM_TOFIXNUM(a)>ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem TyMath_LessP(elem a, elem b)
{
//	if(ELEM_FLONUMP(a))
	return((TyMath_ToDouble(a)<TyMath_ToDouble(b))?MISC_TRUE:MISC_FALSE);

//	return((ELEM_TOFIXNUM(a)<ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem TyMath_GreaterEqualP(elem a, elem b)
{
//	if(ELEM_FLONUMP(a))
	return((TyMath_ToDouble(a)>=TyMath_ToDouble(b))?MISC_TRUE:MISC_FALSE);

//	return((ELEM_TOFIXNUM(a)>=ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem TyMath_LessEqualP(elem a, elem b)
{
//	if(ELEM_FLONUMP(a))
	return((TyMath_ToDouble(a)<=TyMath_ToDouble(b))?MISC_TRUE:MISC_FALSE);

//	return((ELEM_TOFIXNUM(a)<=ELEM_TOFIXNUM(b))?MISC_TRUE:MISC_FALSE);
}

elem TyMath_Sqrt(elem a)
{
	return(ELEM_FROMFLONUM(sqrt(ELEM_TOFLONUM(a))));
}

elem TyMath_Abs(elem a)
{
	double s;

	s=TOFLOAT(a);
	s=(s<0)?0-s:s;
	return(FLONUM(s));
}

int TyMath_Init()
{
	Interp_DefinePrimative("zero?",			&TyMath_ZeroP,			1);
	Interp_DefinePrimative("nonzero?",		&TyMath_NonZeroP,		1);
	Interp_DefinePrimative("positive?",		&TyMath_PositiveP,		1);
	Interp_DefinePrimative("negative?",		&TyMath_NegativeP,		1);
	Interp_DefinePrimative("even?",			&TyMath_EvenP,			1);
	Interp_DefinePrimative("odd?",			&TyMath_OddP,			1);
	Interp_DefinePrimative("min",			&TyMath_Min,			-1);
	Interp_DefinePrimative("max",			&TyMath_Max,			-1);

	Interp_DefinePrimative("+",			&TyMath_AddFlonum,		-1);
	Interp_DefinePrimative("*",			&TyMath_MulFlonum,		-1);
	Interp_DefinePrimative("-",			&TyMath_SubFlonum,		-1);
	Interp_DefinePrimative("/",			&TyMath_DivFlonum,		-1);
	Interp_DefinePrimative("quotient",		&TyMath_Quotient,		2);
	Interp_DefinePrimative("remainder",		&TyMath_Remainder,		2);
	Interp_DefinePrimative("modulo",		&TyMath_Modulo,			2);

	Interp_DefinePrimative("number->string",	&TyMath_NumberToString,	1);
	Interp_DefinePrimative("string->number",	&TyMath_StringToNumber,	1);

	Interp_DefinePrimative(">",			&TyMath_GreaterP,		2);
	Interp_DefinePrimative("<",			&TyMath_LessP,			2);
	Interp_DefinePrimative(">=",			&TyMath_GreaterEqualP,		2);
	Interp_DefinePrimative("<=",			&TyMath_LessEqualP,		2);

	Interp_DefinePrimative("sqrt",			&TyMath_Sqrt,			1);
	Interp_DefinePrimative("abs",			&TyMath_Abs,			1);
}
