#include <scmcc.h>

elem tyfcn_symlist=MISC_EOL;

//elem tyfcn_free_cons=MISC_EOL;

int TyFcn_Init()
{
	MMGC3_AddRoot(&tyfcn_symlist);

	TypeX_Init();
}

elem TyFcn_Cons(elem a, elem b)
{
	elem *t;
	elem u;

/*
	if(tyfcn_free_cons!=MISC_EOL)
	{
//		sa_print(".");
		u=tyfcn_free_cons;
		tyfcn_free_cons=CDR(tyfcn_free_cons);
		t=(elem *)(u&(~7));
	}else */
//	t=sa_alloc(2*ELEM_SZ);
//	t=kpgcons();

//	t=ELEM_TOCONS(MMGC3_Cons());
	t=sa_cons();

	t[0]=a;
	t[1]=b;
	u=ELEM_FROMCONS(t);
//	printf("CONS: %d %d %lX\n", ELEM_SZ, (int)&t[1]-(int)t, u);
	return(u);
}

/*
elem TyFcn_UnCons(elem c)
{
	elem *t, u;

	if(!ELEM_CONSP(c))
	{
		sa_error("uncons: non-cons argument.\n");
//		*(int *)0=0;
		sa_abort();
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	u=t[1];
	t[0]=MISC_NULL;
	t[1]=tyfcn_free_cons;
	tyfcn_free_cons=c;

	return(u);
}
*/

elem TyFcn_Car(elem c)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("car: non-cons argument.\n");
//		*(int *)0=0;
		sa_abort();
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	return(t[0]);
}

elem TyFcn_Cdr(elem c)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("cdr: non-cons argument.\n");
//		*(int *)0=0;
		sa_abort();
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	return(t[1]);
}

elem TyFcn_CarM(elem c)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("car*: non-cons argument.\n");
//		*(int *)0=0;
		sa_abort();
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	return(ELEM_FROMLOCATIVE(&t[0]));
}

elem TyFcn_CdrM(elem c)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("cdr*: non-cons argument.\n");
//		*(int *)0=0;
		sa_abort();
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	return(ELEM_FROMLOCATIVE(&t[1]));
}

elem TyFcn_SetCar(elem c, elem a)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("set-car!: non-cons argument.\n");
		*(int *)0=0;
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	t[0]=a;
	return(MISC_UNDEFINED);
}

elem TyFcn_SetCdr(elem c, elem a)
{
	elem *t;

	if(!ELEM_CONSP(c))
	{
		sa_error("set-cdr!: non-cons argument.\n");
		*(int *)0=0;
		return(MISC_UNDEFINED);
	}

	t=ELEM_TOCONS(c);
	t[1]=a;
	return(MISC_UNDEFINED);
}

elem TyFcn_NewLocative(elem *addr)
{
	elem *t;

	t=sa_alloc(4*ELEM_SZ);
	t[0]=OBJECT_LOCATIVE|(VECTOR_ELEMENT<<8);
	t[1]=(elem)addr;
	t[2]=0;
	t[3]=(elem)-1;
	
	return(ELEM_FROMOBJECT(t));
}

elem *TyFcn_GetLocativeAddr(elem loc)
{
	elem *t;

	t=ELEM_TOOBJECT(loc);
	
	return((elem *)t[1]);
}

elem TyFcn_SetLocativeAddr(elem loc, elem *addr)
{
	elem *t;

	t=ELEM_TOOBJECT(loc);
	if(((elem)addr<t[2]) || ((elem)addr>t[3]))return(MISC_UNDEFINED);
	t[1]=(elem)addr;
	return(loc);
}


elem TyFcn_LocativeNew(elem lower, elem upper, elem ty)
{
	elem *t;

	t=sa_alloc(4*ELEM_SZ);
	t[0]=OBJECT_LOCATIVE|(ELEM_TOFIXNUM(ty)<<8);
	t[1]=lower;
	t[2]=lower;
	t[3]=upper;
	
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_LocativeCopy(elem a)
{
	elem *s, *t;

	s=ELEM_TOOBJECT(a);
	t=sa_alloc(4*ELEM_SZ);
	t[0]=s[0];
	t[1]=s[1];
	t[2]=s[2];
	t[3]=s[3];

	return(ELEM_FROMOBJECT(t));
}

int vec_sizetable[]={
1, ELEM_SZ, 4, 8, // 0-3
1, 2, 4, 8, // 4-7
1, 2, 4, 8, // 8-11
1, 1, 1, 1, // 12-15
1, 1, 1, 1, // 16-19
1, 1, 1, 1, // 20-23
1, 1, 1, 1, // 24-27
1, 1, 1, 1, // 28-31
ELEM_SZ, ELEM_SZ, ELEM_SZ, ELEM_SZ, // 32-35
ELEM_SZ, ELEM_SZ, ELEM_SZ, ELEM_SZ, // 36-39
ELEM_SZ, ELEM_SZ, ELEM_SZ, ELEM_SZ, // 40-43
ELEM_SZ, ELEM_SZ, ELEM_SZ, ELEM_SZ, // 44-47
};

elem TyFcn_ListToVector(elem lst)
{
	int len;
	elem *buf, cur;
	int i;

//	sa_print("list->vector {");

	len=ELEM_TOFIXNUM(TyFcn_ListLength(lst));
//	printf("vec %d\n", len);
	buf=sa_alloc((len+1)*ELEM_SZ);
//	printf("vecbuf %p %p\n", buf, ELEM_TOOBJECT(ELEM_FROMOBJECT(buf)));
	buf[0]=OBJECT_VECTOR|(1<<8)|(len<<16);
//	buf[1]=len;

	for(i=0; i<len; i++)buf[i+1]=MISC_NULL;

	i=0;
	cur=lst;
	while(cur!=MISC_EOL)
	{
		buf[i+1]=CAR(cur);
		i++;
		cur=CDR(cur);
	}

//	sa_print("}\n");

	return(ELEM_FROMOBJECT(buf));
}

elem TyFcn_CopyVector(elem a)
{
	elem *s, *t;
	int l, i, ty;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_CopyVector: non-vector.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&63;
	l=(s[0]>>16)&4095;
	t=sa_alloc(ELEM_SZ+(l*vec_sizetable[ty]));
	t[0]=s[0];
	memcpy(t+1, s+1, l*vec_sizetable[ty]);
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_ResizeVector(elem a, elem nl)
{
	elem *s, *t;
	int l, l2, i, ty;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_ResizeVector: non-vector.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&255;
	l=ELEM_TOFIXNUMi(nl);
	t=sa_alloc(ELEM_SZ+(l*vec_sizetable[ty]));
	if(ty==1)for(i=0; i<(l+1); i++)t[i]=MISC_NULL;
	t[0]=OBJECT_VECTOR|(ty<<8)|(l<<16);
	l2=((s[0]>>16)&4095<l)?(s[0]>>16)&4095:l;

//	for(i=0; i<l2; i++)t[i+2]=s[i+2];
	memcpy(t+1, s+1, l2*vec_sizetable[ty]);
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_NewVector(elem a)
{
	elem *t;
	int l, i;

	l=ELEM_TOFIXNUM(a);

	if(l>4095)l=4095;

	t=sa_alloc((l+2)*ELEM_SZ);
	t[0]=OBJECT_VECTOR|(1<<8)|(l<<16);
//	t[1]=l;
	for(i=0; i<l; i++)t[i+1]=MISC_NULL;
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_NewTypedVector(elem a, elem ty)
{
	elem *t;
	int l, i;

	i=ELEM_TOFIXNUM(ty);
	l=ELEM_TOFIXNUM(a);
	t=sa_alloc((l+2)*ELEM_SZ);
	t[0]=OBJECT_VECTOR|(i<<8)|(l<<16);
//	t[1]=l;
	if(i==1 || (i>=32 && i<=47))for(i=0; i<l; i++)t[i+1]=MISC_NULL;
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_VectorLength(elem a)
{
	elem *s;
	int l;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_VectorLength: non-vector.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	l=(s[0]>>16)&4095;
	return(ELEM_FROMFIXNUM(l));
}

elem TyFcn_VectorIs(elem a, elem ty)
{
	elem *t;
	int i;

	if(!ELEM_VECTORP(a))return(MISC_FALSE);

	i=ELEM_TOFIXNUM(ty);
	t=ELEM_TOOBJECT(a);
	if(((t[0]>>8)&255)==i)return(MISC_TRUE);
	return(MISC_FALSE);
}

elem TyFcn_BignumIs(elem a, elem ty)
{
	elem *t;
	int i;

	if(!ELEM_BIGNUMP(a))return(MISC_FALSE);

	i=ELEM_TOFIXNUM(ty);
	t=ELEM_TOOBJECT(a);
	if(((t[0]>>8)&255)==i)return(MISC_TRUE);
	return(MISC_FALSE);
}

elem TyFcn_VectorType(elem a)
{
	elem *t;
	int i;

	if(!ELEM_VECTORP(a))return(MISC_FALSE);
	t=ELEM_TOOBJECT(a);
	i=((t[0]>>8)&255);

	return(ELEM_FROMFIXNUM(i));
}

elem TyFcn_VectorRef(elem a, elem b)
{
	elem *s;
	elem t;
	int ty, i;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_VectorRef: non-vector.\n");
		sa_print("\t%d\n", OBJECT_HEAD(a));
		sa_abort();
		return(MISC_UNDEFINED);
	}
	if((b>TyFcn_VectorLength(a)) || (ELEM_TOFIXNUM(b)<0))
	{
		sa_error("TyFcn_VectorRef: out of vector bounds.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&255;
	i=ELEM_TOFIXNUM(b);

	switch(ty)
	{
	case VECTOR_ELEMENT:
		t=s[i+1];
		break;
	case VECTOR_U8:
		t=ELEM_FROMFIXNUM(((unsigned char *)(s+1))[i]);
		break;
	case VECTOR_U16:
		t=ELEM_FROMFIXNUM(((unsigned short *)(s+1))[i]);
		break;
	case VECTOR_U32:
		t=ELEM_FROMFIXNUM(((unsigned int *)(s+1))[i]);
		break;
	case VECTOR_S8:
		t=ELEM_FROMFIXNUM(((signed char *)(s+1))[i]);
		break;
	case VECTOR_S16:
		t=ELEM_FROMFIXNUM(((signed short *)(s+1))[i]);
		break;
	case VECTOR_S32:
		t=ELEM_FROMFIXNUM(((signed int *)(s+1))[i]);
		break;

	case VECTOR_F32:
		t=ELEM_FROMFLONUM(((float *)(s+1))[i]);
		break;
	case VECTOR_F64:
		t=ELEM_FROMFLONUM(((double *)(s+2))[i]);
		break;

	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		t=s[i+1];
		break;
	default:
		t=MISC_NULL;
		break;
	}
	return(t);
}

elem TyFcn_VectorSet(elem a, elem b, elem c)
{
	elem *s;
	elem t;
	int ty, i, j;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_VectorSet: non-vector.\n");
		sa_abort();
		return(MISC_UNDEFINED);
	}
	if((b>TyFcn_VectorLength(a)) || (ELEM_TOFIXNUM(b)<0))
	{
		sa_error("TyFcn_VectorSet: out of vector bounds.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&255;
	i=ELEM_TOFIXNUM(b);
	j=ELEM_TOFIXNUM(c);

	switch(ty)
	{
	case VECTOR_ELEMENT:
		s[i+1]=c;
		break;
	case VECTOR_U8:
		((unsigned char *)(s+1))[i]=j;
		break;
	case VECTOR_U16:
		((unsigned short *)(s+1))[i]=j;
		break;
	case VECTOR_U32:
		((unsigned int *)(s+1))[i]=j;
		break;
	case VECTOR_S8:
		((signed char *)(s+1))[i]=j;
		break;
	case VECTOR_S16:
		((signed short *)(s+1))[i]=j;
		break;
	case VECTOR_S32:
		((signed int *)(s+1))[i]=j;
		break;

	case VECTOR_F32:
		((float *)(s+1))[i]=ELEM_TOFLONUM(c);
		break;
	case VECTOR_F64:
		((double *)(s+2))[i]=ELEM_TOFLONUM(c);
		break;

	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		s[i+1]=c;
		break;

	default:
		break;
	}
	return(MISC_UNDEFINED);
}

elem TyFcn_VectorRefM(elem a, elem b)
{
	elem *s;
	elem t;
	int ty, i;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_VectorRefM: non-vector.\n");
		return(MISC_UNDEFINED);
	}
	if((b>TyFcn_VectorLength(a)) || (ELEM_TOFIXNUM(b)<0))
	{
		sa_error("TyFcn_VectorRefM: out of vector bounds.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&255;
	i=ELEM_TOFIXNUM(b);

	switch(ty)
	{
	case VECTOR_ELEMENT:
		t=ELEM_FROMLOCATIVE(s+i+1);
		break;
//	case VECTOR_U8:
//		t=ELEM_FROMLOCATIVE(((unsigned char *)(s+1))+i);
//		break;
//	case VECTOR_U16:
//		t=ELEM_FROMLOCATIVE(((unsigned short *)(s+1))+i);
//		break;
	case VECTOR_U32:
		t=ELEM_FROMLOCATIVE(((unsigned int *)(s+1))+i);
		break;
//	case VECTOR_S8:
//		t=ELEM_FROMLOCATIVE(((signed char *)(s+1))+i);
//		break;
//	case VECTOR_S16:
//		t=ELEM_FROMLOCATIVE(((signed short *)(s+1))+i);
//		break;
	case VECTOR_S32:
		t=ELEM_FROMLOCATIVE(((signed int *)(s+1))+i);
		break;

	case VECTOR_F32:
		t=ELEM_FROMLOCATIVE(((float *)(s+1))+i);
		break;
	case VECTOR_F64:
		t=ELEM_FROMLOCATIVE(((double *)(s+2))+i);
		break;

	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		t=ELEM_FROMLOCATIVE(s+i+1);
		break;
	default:
		t=MISC_NULL;
		break;
	}
	return(t);
}

/* specialized vector ref for math functions... */
double TyFcn_VectorRefF(elem a, int b)
{
	elem *s;
	elem t;
	int ty, i;

	double f;

	if(!ELEM_VECTORP(a))
	{
		sa_error("TyFcn_VectorRefF: non-vector.\n");
		sa_print("\t%d\n", OBJECT_HEAD(a));
		sa_abort();
		return(MISC_UNDEFINED);
	}
	if((b>TyFcn_VectorLength(a)) || (ELEM_TOFIXNUM(b)<0))
	{
		sa_error("TyFcn_VectorRef: out of vector bounds.\n");
		return(MISC_UNDEFINED);
	}

	s=ELEM_TOOBJECT(a);
	ty=(s[0]>>8)&255;
	i=b;

	switch(ty)
	{
	case VECTOR_ELEMENT:
		f=ELEM_TOFLONUM(s[i+1]);
		break;
	case VECTOR_U8:
		f=((unsigned char *)(s+1))[i];
		break;
	case VECTOR_U16:
		f=((unsigned short *)(s+1))[i];
		break;
	case VECTOR_U32:
		f=((unsigned int *)(s+1))[i];
		break;
	case VECTOR_S8:
		f=((signed char *)(s+1))[i];
		break;
	case VECTOR_S16:
		f=((signed short *)(s+1))[i];
		break;
	case VECTOR_S32:
		f=((signed int *)(s+1))[i];
		break;

	case VECTOR_F32:
		f=((float *)(s+1))[i];
		break;
	case VECTOR_F64:
		f=((double *)(s+2))[i];
		break;

	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		f=ELEM_TOFLONUM(s[i+1]);
		break;
	default:
		f=0;
		break;
	}
	return(f);
}


elem TyFcn_String(char *s)
{
	short *t;
	elem *u;
	int i, l;
//	u4 *v;

	l=strlen(s);
	u=sa_alloc(2*ELEM_SZ+(2*l)+2);
//	v=u;

	u[0]=OBJECT_STRING|(VECTOR_U16<<8)|(l<<16);
//	u[1]=l;
	t=(short *)(u+1);
	for(i=0; i<l; i++)t[i]=s[i];

//	v[0]=OBJECT_STRING|(strlen(s)<<16);
//	t=(short *)(v+2);
//	for(i=0; i<l; i++)t[i]=s[i];

	return(ELEM_FROMOBJECT(u));
}

elem TyFcn_MakeString(elem k, elem c)
{
	elem *t;
	short *u;
	int l, ch, i;

	l=ELEM_TOFIXNUM(k);
	ch=ELEM_TOCHAR(k);

	t=sa_alloc((2*ELEM_SZ)+(l*2)+2);
	t[0]=OBJECT_STRING|(VECTOR_U16<<8)|(l<<16);
//	t[1]=l;
	u=(short *)(t+1);
	for(i=0; i<l; i++)u[i]=ch;

	return(ELEM_FROMOBJECT(t));
}

char *TyFcn_UnString(elem a)
{
	char *s;
	elem *t;
	short *u;
	int i, l;

/*	static char *rotbuf[16];
	static int rotlen[16];
	static int rotpos=-1; */

/*	if(rotpos==-1)
	{
		memset(rotbuf, 0, 16*sizeof(char *));
		memset(rotlen, 0, 16*sizeof(int));
		rotpos=0;
	} */

	if(!ELEM_STRINGP(a) && !ELEM_SYMBOLP(a))
	{
		sa_error("TyFcn_Unstring: type error\n");
		return(NULL);
	}

	t=ELEM_TOOBJECT(a);
	u=(short *)(t+1);
	l=(t[0]>>16)&4095;

	s=sa_ralloc(l+1);

/*	if(!rotbuf[rotpos] || rotlen[rotpos]<l || rotlen[rotpos]>(l*4))
	{
		if(rotbuf[rotpos])sa_free(rotbuf[rotpos]);
		rotbuf[rotpos]=sa_malloc(l+1);
		rotlen[rotpos]=l;
	}
	s=rotbuf[rotpos];
	rotpos++;
	if(rotpos>=16)rotpos=0;
	*/

	for(i=0; i<l; i++)s[i]=u[i];
	s[i]=0;
	return(s);
}

short *TyFcn_UnString16(elem a)
{
	short *s;
	elem *t;
	short *u;
	int i, l;

	if(!ELEM_STRINGP(a) && !ELEM_SYMBOLP(a))
	{
		sa_error("TyFcn_Unstring: type error\n");
		return(NULL);
	}

	t=ELEM_TOOBJECT(a);
	u=(short *)(t+1);
	l=(t[0]>>16)&4095;

	s=sa_ralloc((l*2)+2);

	for(i=0; i<l; i++)s[i]=u[i];
	s[i]=0;
	return(s);
}

elem TyFcn_StringEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if(((s[0]>>16)&4095)!=((t[0]>>16)&4095))return(MISC_FALSE);
	l=(s[0]>>16)&4095;

	u=(short *)(s+1);
	v=(short *)(t+1);
	for(i=0; i<l; i++)if(u[i]!=v[i])return(MISC_FALSE);
	return(MISC_TRUE);
}

static sh_lower(short c)
{
	if((c>='A') && (c<='Z'))return(c-'A'+'a');
	return(c);
}

elem TyFcn_StringCiEP(elem a, elem b)
{
	elem *s, *t;
	short *u, *v;
	int i, l;

	s=ELEM_TOOBJECT(a);
	t=ELEM_TOOBJECT(b);

	if((s[0]>>16)&4095!=(t[0]>>16)&4095)return(MISC_FALSE);
	l=(s[0]>>16)&4095;

	u=(short *)(s+2);
	v=(short *)(t+2);
	for(i=0; i<l; i++)if(sh_lower(u[i])!=sh_lower(v[i]))return(MISC_FALSE);
	return(MISC_TRUE);
}

elem TyFcn_StringE(elem a, elem b)
{
	int t;

//	if(!ELEM_STRINGP(a) && !ELEM_SYMBOLP(a))return(MISC_UNDEFINED);
//	if(!ELEM_STRINGP(b) && !ELEM_SYMBOLP(b))return(MISC_UNDEFINED);
	if(!ELEM_SYMBOLP(a))return(MISC_UNDEFINED);
	if(!ELEM_SYMBOLP(b))return(MISC_UNDEFINED);

	*(int *)0=1;

	t=sa_stricmp(ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b));
//	if(!t)sa_print("match: %s %s\n", ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b));
	return((!t)?MISC_TRUE:MISC_FALSE);
//	return(TyFcn_StringCiEP(a, b));
}

elem TyFcn_Symbol2(char *s, int flag)
{
	short *t;
	elem *u;
	int i, l;
//	u4 *v;

	l=strlen(s);
	u=sa_alloc(ELEM_SZ+(2*l)+2);
//	v=u;

	u[0]=OBJECT_SYMBOL|(VECTOR_U16<<8)|(flag<<30)|(l<<16);
	t=(short *)(u+1);
	for(i=0; i<l; i++)t[i]=s[i];

//	v[0]=OBJECT_STRING|(strlen(s)<<16);
//	t=(short *)(v+2);
//	for(i=0; i<l; i++)t[i]=s[i];

	return(ELEM_FROMOBJECT(u));
}

elem TyFcn_FindSymbolInList(char *name, elem lst)
{
	elem cur;

	cur=lst;
	while(cur!=MISC_EOL)
	{
		if(!sa_stricmp(name, ELEM_TOSYMBOL(CAR(cur))))
			return(CAR(cur));
		cur=CDR(cur);
	}
	return(MISC_NULL);
}

#define char_upper(a) ((((a)>='a') && ((a)<='z'))?((a)-('a'-'A')):(a))

elem TyFcn_Symbol(char *s)
{
	elem u, w, cur, *t;
	short *v;
	int i, f, l, a, b;

//	u=TyFcn_FindSymbolInList(s, tyfcn_symlist);
	u=MISC_NULL;

	w=MISC_EOL;
	cur=tyfcn_symlist;
	while(cur!=MISC_EOL)
	{
		t=ELEM_TOOBJECT(CAR(cur));
		v=(short *)(t+1);
		l=(t[0]>>16)&4095;

		for(i=0; i<l; i++)
		{
			if(char_upper(s[i])!=char_upper(v[i]))break;

//			a=s[i];
//			b=v[i];
//			if(a>='a' && a<='z')a-='a'-'A';
//			if(b>='a' && b<='z')b-='a'-'A';
//			if(a!=b)break;
		}

		if((i==l) && !(s[i]))
		{
			u=CAR(cur);
			if(w!=MISC_EOL)
			{
				TyFcn_SetCdr(w, CDR(cur));
				TyFcn_SetCdr(cur, tyfcn_symlist);
				tyfcn_symlist=cur;
			}
			break;
		}
		w=cur;
		cur=CDR(cur);
	}

	f=0;

	if(u==MISC_NULL)
	{
//		sa_print("new symbol %s\n", s);
		if(s[strlen(s)-1]==':')f=2;
		if(s[strlen(s)-1]==';')f=1;
		u=TyFcn_Symbol2(s, f);
		tyfcn_symlist=CONS(u, tyfcn_symlist);
	}
//	if(ELEM_SYMHYGENICP(u))sa_print("hygenic %s\n", s);
	return(u);
}

elem TyFcn_KeywordBase(elem sym)
{
	char *s, buf[16];

	if(!ELEM_SYMKEYWORDP(sym) && !ELEM_SYMHYGENICP(sym))return(sym);
	s=ELEM_TOSYMBOL(sym);
	strcpy(buf, s);
	buf[strlen(buf)-1]=0;

//	sa_print("keyword-base: '%s'\n", buf);
	return(TyFcn_Symbol(buf));
}

elem TyFcn_ObjectInListP(elem obj, elem lst)
{
	elem cur;
	int c;

	c=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		if(obj==CAR(cur))
			return(MISC_TRUE);
		c++;
		cur=CDR(cur);
	}
	if(cur==obj)return(MISC_TRUE);
	return(MISC_FALSE);
}

elem TyFcn_ObjPeekElem(elem obj, elem num)
{
	elem *t;
	t=ELEM_TOOBJECT(obj);
	return(t[ELEM_TOFIXNUM(num)]);
}

elem TyFcn_ObjPokeElem(elem obj, elem num, elem val)
{
	elem *t;
	t=ELEM_TOOBJECT(obj);
	t[ELEM_TOFIXNUM(num)]=val;
	return(val);
}

elem TyFcn_NReverse(elem lst)
{
	elem cur, last, n;

	last=MISC_EOL;
	cur=lst;

	while(cur!=MISC_EOL)
	{
		n=TyFcn_Cdr(cur);
		TyFcn_SetCdr(cur, last);

		last=cur;
		cur=n;
//		printf("LARGE3 %lX %lX.\n", cur, last);
	}
	return(last);
}

elem TyFcn_Reverse(elem lst)
{
	elem cur, t;

	cur=lst;
	t=MISC_EOL;
	while(cur!=MISC_EOL)
	{
		t=CONS(CAR(cur), t);
		cur=CDR(cur);
	}
	return(t);
}

elem TyFcn_ListCopy(elem a)
{
	if(!ELEM_CONSP(a))return(a);
	return(CONS(CAR(a), TyFcn_ListCopy(CDR(a))));
}

#if 0
elem TyFcn_ListCopy(elem a)
{
	elem cur, last, lst, t;
	cur=a;
	last=MISC_EOL;
	lst=MISC_EOL;
	while(ELEM_CONSP(cur))
	{
		t=CONS(CAR(cur), MISC_EOL);
		if(ELEM_CONSP(last))TyFcn_SetCdr(last, t);
		last=t;
		if(ELEM_EOLP(lst))lst=last;
		cur=CDR(cur);
	}
	if(ELEM_CONSP(last))TyFcn_SetCdr(last, cur);
	if(ELEM_EOLP(lst))lst=last;
	return(lst);
}
#endif

elem TyFcn_ListCopyRec(elem a)
{
	elem cur, last, lst, t;
	cur=a;
	last=MISC_EOL;
	lst=MISC_EOL;
	while(ELEM_CONSP(cur))
	{
		t=CAR(cur);
		if(ELEM_CONSP(t))t=TyFcn_ListCopyRec(t);
		t=CONS(t, MISC_EOL);
		if(ELEM_CONSP(last))TyFcn_SetCdr(last, t);
		last=t;
		if(ELEM_EOLP(lst))lst=last;
		cur=CDR(cur);
	}
	if(ELEM_CONSP(last))TyFcn_SetCdr(last, cur);
	if(ELEM_EOLP(lst))lst=last;
	return(lst);
}

elem TyFcn_NAppend(elem lst, elem a)
{
	elem cur, last;

	if(lst==MISC_EOL)return(a);

	cur=lst;
	while(ELEM_CONSP(cur))
	{
		last=cur;
		cur=TyFcn_Cdr(cur);
	}
	if(cur==MISC_EOL)TyFcn_SetCdr(last, a);
	return(lst);
}

elem TyFcn_Append(elem lst, elem a)
{
	if(!ELEM_CONSP(lst))return(a);
	return(CONS(CAR(lst), TyFcn_Append(CDR(lst), a)));
}

elem TyFcn_FoldMark(elem lst)
{
	elem cur, t;

	t=MISC_EOL;
	cur=lst;
	while((cur!=MISC_EOL) && (CAR(cur)!=MISC_MARK))
	{
		t=CONS(CAR(cur), t);
		cur=CDR(cur);
	}
	if(CAR(cur)==MISC_MARK)cur=CDR(cur);
	t=TyFcn_NReverse(t);

	return(CONS(t, cur));
}

elem TyFcn_ListLength(elem lst)
{
	elem cur;
	int i;

	i=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		i++;
		cur=TyFcn_Cdr(cur);
	}
	return(ELEM_FROMFIXNUM(i));
}

elem TyFcn_ListGetEnd(elem lst)
{
	elem cur;

	cur=lst;
	while(ELEM_CONSP(cur))
		cur=TyFcn_Cdr(cur);
	return(cur);
}

/*
elem TyFcn_UnList(elem lst)
{
	elem cur;

	cur=lst;
	while(ELEM_CONSP(cur))
		cur=UCDR(cur);
	return(cur);
}
*/

elem TyFcn_ListRef(elem lst, elem idx)
{
	elem cur;
	int i, j;

	j=ELEM_TOFIXNUM(idx);

	i=0;
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		if(i==j)return(CAR(cur));
		i++;
		cur=CDR(cur);
	}
	return(MISC_UNDEFINED);
}

elem TyFcn_Function(elem (*func)(), int pc)
{
	elem *t;
	t=sa_alloc(4*ELEM_SZ);
	if(pc<0)pc=(~pc)|64;
	t[0]=OBJECT_FUNCTION | (pc<<9);
	t[1]=(elem)(int)func;
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_Special(elem (*func)(), int pc)
{
	elem *t;
	t=sa_alloc(4*ELEM_SZ);
	if(pc<0)pc=(~pc)|64;
	t[0]=OBJECT_SYNTAX | (pc<<9);
	t[1]=(elem)(int)func;
	return(ELEM_FROMOBJECT(t));
}

elem TyFcn_EqualP(elem a, elem b)
{
	elem cur, cur2, t;
	int i, j;

	if(a==b)return(MISC_TRUE);

	if(ELEM_CONSP(a) && ELEM_CONSP(b))
	{
		cur=a;
		cur2=b;
		while(ELEM_CONSP(cur) && ELEM_CONSP(cur2))
		{
			t=TyFcn_EqualP(CAR(cur), CAR(cur2));
			if(t==MISC_FALSE)return(t);
			cur=CDR(cur);
			cur2=CDR(cur2);
		}
		return(TyFcn_EqualP(cur, cur2));
	}
	if(ELEM_VECTORP(a) && ELEM_VECTORP(b))
	{
		cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(0));
		cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(0));
		if((cur>>16)!=(cur2>>16))return(MISC_FALSE);
		j=(cur>>16);
		for(i=0; i<j; i++)
		{
			cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(i+1));
			cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(i+1));
			t=TyFcn_EqualP(cur, cur2);
			if(t==MISC_FALSE)return(t);
		}
		return(MISC_TRUE);
	}

	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))return(TyFcn_StringEP(a, b));
	return(MISC_FALSE);
}

elem TyFcn_MatchP(elem lit, elem a, elem b)
{
	elem cur, cur2, t;
	int i, j;

	if(a==b)return(MISC_TRUE);

	if(ELEM_SYMBOLP(a))
	{
		t=TyFcn_ObjectInListP(a, lit);
		if(t!=MISC_FALSE || ELEM_SYMKEYWORDP(a))if(a!=b)return(MISC_FALSE);
		return(MISC_TRUE);
	}

	if(ELEM_CONSP(a) && ELEM_CONSP(b))
	{
		cur=a;
		cur2=b;
		while(ELEM_CONSP(cur) && ELEM_CONSP(cur2))
		{
			if(CAR(cur)==SYM("..."))return(MISC_TRUE);

			t=TyFcn_MatchP(lit, CAR(cur), CAR(cur2));
			if(t==MISC_FALSE)return(t);
			cur=CDR(cur);
			cur2=CDR(cur2);
		}
		return(TyFcn_MatchP(lit, cur, cur2));
	}
	if(ELEM_VECTORP(a) && ELEM_VECTORP(b))
	{
		cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(0));
		cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(0));
		if((cur>>16)!=(cur2>>16))return(MISC_FALSE);
		j=(cur>>16);
		for(i=0; i<j; i++)
		{
			cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(i+1));
			cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(i+1));
			t=TyFcn_MatchP(lit, cur, cur2);
			if(t==MISC_FALSE)return(t);
		}
		return(MISC_TRUE);
	}

	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))return(TyFcn_StringEP(a, b));
	return(MISC_FALSE);
}

elem TyFcn_Match2P(elem lit, elem a, elem b)
{
	elem t;

	t=TyFcn_MatchP(lit, a, b);

	sa_print("match: ");
	TyFcn_DumpElem(a);
	sa_print(" to: ");
	TyFcn_DumpElem(b);
	sa_print(" with: ");
	TyFcn_DumpElem(lit);
	sa_print(" yeilds: ");
	TyFcn_DumpElem(t);
	sa_print("\n");
	return(t);
}

elem TyFcn_MatchV(elem a, elem b)
{
	elem cur, cur2, t;
	int i, j, c;

	c=0;

	if(a==b)return(ELEM_FROMFIXNUM(1));

	if(ELEM_SYMBOLP(a))
	{
		if(ELEM_SYMKEYWORDP(a))
			if(a==SYM("_:") && ELEM_SYMKEYWORDP(b))return(ELEM_FROMFIXNUM(0));
				/* vague match keyword */
			else if(TyFcn_KeywordBase(a)!=TyFcn_KeywordBase(b))return(MISC_FALSE);
			else return(ELEM_FROMFIXNUM(1));
//			else return(MISC_FALSE);
		return(ELEM_FROMFIXNUM(0)); //vague match...
	}

	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))if(TyFcn_StringEP(a, b)==MISC_TRUE)
		return(ELEM_FROMFIXNUM(1));
		else return(MISC_FALSE);

	if(ELEM_CONSP(a) && ELEM_CONSP(b))
	{
		c++; //bias it a little tward lists/vectors, ie: where a symbol is also a match
		cur=a;
		cur2=b;

		while(ELEM_CONSP(cur) && ELEM_CONSP(cur2))
		{
			if(CAR(cur)==SYM("..."))return(MISC_TRUE);

			t=TyFcn_MatchV(CAR(cur), CAR(cur2));
			if(t==MISC_FALSE)return(t);
			c+=ELEM_TOFIXNUM(t);
			cur=CDR(cur);
			cur2=CDR(cur2);
		}
		t=TyFcn_MatchV(cur, cur2);
		if(t==MISC_FALSE)return(t);
		c+=ELEM_TOFIXNUM(t);
		return(ELEM_FROMFIXNUM(c));
	}
	if(ELEM_VECTORP(a) && ELEM_VECTORP(b))
	{
		c++; //bias it a little tward lists/vectors, ie: where a symbol is also a match
		cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(0));
		cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(0));

		if((cur>>16)!=(cur2>>16))return(MISC_FALSE);
		j=(cur>>16);
		for(i=0; i<j; i++)
		{
			cur=TyFcn_ObjPeekElem(a, ELEM_FROMFIXNUM(i+1));
			cur2=TyFcn_ObjPeekElem(b, ELEM_FROMFIXNUM(i+1));
			t=TyFcn_MatchV(cur, cur2);
			if(t==MISC_FALSE)return(t);
			c+=ELEM_TOFIXNUM(t);
		}
		return(ELEM_FROMFIXNUM(c));
	}

	return(MISC_FALSE);
}


int TyFcn_DumpObject(elem obj)
{
	elem *buf;
	int i, c;
	double x;

	buf=ELEM_TOOBJECT(obj);
//	printf("objbuf %p\n", buf);

	if(ELEM_FLONUMP(obj))
	{
		x=TyMath_ToDouble(obj);
		sa_print("%g", x);
		return(0);
	}

	switch(buf[0]&255)
	{
	case OBJECT_VECTOR:
		if(((buf[0]>>8)&255)>11)
		{
			sa_print("#<vector-type %d>", ((buf[0]>>8)&255));
			break;
		}

		c=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
//		c=0;
		sa_print("#(");
		for(i=0; i<c; i++)
		{
//			TyFcn_DumpElem(buf[i+2]);
			TyFcn_DumpElem(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(i)));
			if((i+1)<c)sa_print(" ");
		}
		sa_print(")");
		break;
	case OBJECT_STRING:
		sa_print("\"%s\"", ELEM_TOSTRING(obj));
		break;
	case OBJECT_SYMBOL:
		sa_print("%s", ELEM_TOSYMBOL(obj));
		break;
	default:
		sa_print("#<obj-type %d>", buf[0]&255);
		break;
	}
	return(0);
}

int TyFcn_DisplayObject(elem obj)
{
	elem *buf;
	int i, c;
	double x;

	buf=ELEM_TOOBJECT(obj);
//	printf("objbuf %p\n", buf);

	if(ELEM_FLONUMP(obj))
	{
		x=TyMath_ToDouble(obj);
		sa_print("%g", x);
		return(0);
	}

	switch(buf[0]&255)
	{
	case OBJECT_VECTOR:
		if(((buf[0]>>8)&255)>=32)
		{
			sa_print("#<vector-type %d>", ((buf[0]>>8)&255));
			break;
		}

		c=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
//		c=0;
		sa_print("#(");
		for(i=0; i<c; i++)
		{
//			TyFcn_DumpElem(buf[i+2]);
			TyFcn_DumpElem(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(i)));
			if((i+1)<c)sa_print(" ");
		}
		sa_print(")");
		break;
	case OBJECT_STRING:
		sa_print("%s", ELEM_TOSTRING(obj));
		break;
	case OBJECT_SYMBOL:
		sa_print("%s", ELEM_TOSYMBOL(obj));
		break;
	default:
		sa_print("#<obj-type %d>", buf[0]&255);
		break;
	}
	return(0);
}

int TyFcn_DumpString(elem s, elem port)
{
}

int TyFcn_DumpMisc(elem obj)
{
	if(ELEM_CHARP(obj))
	{
		sa_print("#\\%c", ELEM_TOCHAR(obj));
		return(0);
	}
//	if(ELEM_FRAMEP(obj))
//	{
//		sa_print("#r(%d %d)", (obj>>20)&4095, (obj>>8)&4095);
//		return(0);
//	}
	switch(obj)
	{
	case MISC_EOL:
		sa_print("()");
		return(0);
		break;
	case MISC_TRUE:
		sa_print("#t");
		return(0);
		break;
	case MISC_FALSE:
		sa_print("#f");
		return(0);
		break;
	case MISC_NULL:
		sa_print("#z");
		return(0);
		break;
	default:
		break;
	}
	sa_print("#<misc %d %d>", (obj>>3)&31, obj>>8);
	return(0);
}

int TyFcn_DumpElem(elem obj)
{
	switch(obj)
	{
	case MISC_EOL:
		sa_print("()");
		return(0);
		break;
	case MISC_TRUE:
		sa_print("#t");
		return(0);
		break;
	case MISC_FALSE:
		sa_print("#f");
		return(0);
		break;
	default:
		break;
	}
	switch(ELEM_TYPE3(obj))
	{
	case TYPE_FIXNUM:
		sa_print("%d", ELEM_TOFIXNUMi(obj));
		break;
//	case TYPE_LOCATIVE:
//	case TYPE_LOCATIVE2:
//		sa_print("%X", ELEM_TOLOCATIVE(obj));
//		break;
	case TYPE_CONS:
		TyFcn_DumpList(obj);
		break;
	case TYPE_OBJECT:
		TyFcn_DumpObject(obj);
		break;
	case TYPE_MISC:
		TyFcn_DumpMisc(obj);
		break;
	default:
		sa_print("#<type %d>", ELEM_TYPE3(obj));
		break;
	}
	return(0);
}

int TyFcn_DumpList(elem lst)
{
	elem cur;

	cur=lst;
	sa_print("(");
	while(cur!=MISC_EOL)
	{
		TyFcn_DumpElem(CAR(cur));
		if(CDR(cur)!=MISC_EOL)sa_print(" ");

		if(!ELEM_CONSP(CDR(cur)) && (CDR(cur) != MISC_EOL))
		{
			sa_print(" . ");
			TyFcn_DumpElem(CDR(cur));
			cur=MISC_EOL;
			break;
		}
		cur=CDR(cur);
	}
	sa_print(")");
}

int TyFcn_DisplayList(elem lst)
{
	elem cur;

	cur=lst;
	sa_print("(");
	while(cur!=MISC_EOL)
	{
		TyFcn_DisplayElem(CAR(cur));
		if(CDR(cur)!=MISC_EOL)sa_print(" ");

		if(!ELEM_CONSP(CDR(cur)) && (CDR(cur) != MISC_EOL))
		{
			sa_print(" . ");
			TyFcn_DisplayElem(CDR(cur));
			cur=MISC_EOL;
			break;
		}
		cur=CDR(cur);
	}
	sa_print(")");
}

// possibly pretier output but not as readable by the parser
int TyFcn_DisplayElem(elem obj)
{
	switch(ELEM_TYPE3(obj))
	{
	case TYPE_FIXNUM:
		sa_print("%d", ELEM_TOFIXNUMi(obj));
		break;
//	case TYPE_LOCATIVE:
//	case TYPE_LOCATIVE2:
//		sa_print("%p", ELEM_TOLOCATIVE(obj));
//		break;
	case TYPE_CONS:
		TyFcn_DisplayList(obj);
		break;
	case TYPE_OBJECT:
		TyFcn_DisplayObject(obj);
		break;
	case TYPE_MISC:
		TyFcn_DumpMisc(obj);
		break;
	}
	return(0);
}
