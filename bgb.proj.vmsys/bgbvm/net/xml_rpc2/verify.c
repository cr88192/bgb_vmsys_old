#include <general.h>
#include <net/pdnet.h>

void *Verify_FetchStructSlot(NET_Struct *ns, char *name)
{
	int i;

	for(i=0; ns->names[i]; i++)
		if(!strcmp(ns->names[i], name))
	{
		return(ns->values[i]);
	}
}

NET_Struct *Verify_NewNetStruct(int max)
{
	NET_Struct *tmp;

//	tmp=kalloc(sizeof(NET_Struct));

	tmp=ObjType_New("d_struct_t", 0);
	tmp->names=kalloc(max*sizeof(char *));
	tmp->values=kalloc(max*sizeof(void *));

	return(tmp);
}

int Verify_SetStructSlot(NET_Struct *ns, char *name, void *val)
{
	int i;

	for(i=0; ns->names[i]; i++)
		if(!strcmp(ns->names[i], name))
	{
		ns->values[i]=val;
		return(0);
	}
	ns->names[i]=NetVal_WrapStr(name);
	ns->values[i]=val;

	i++;
	ns->names[i]=NULL;
	ns->values[i]=NULL;

	return(0);
}

void *Verify_ArrayOfStructsTest(long arr)
{
	NET_Array *na;
	NET_Struct *ns;

	char *ty;
	int i, ax;
	void *l;

	na=(NET_Array *)arr;

	ax=0;
	for(i=0; na->values[i]; i++)
	{
		ns=(NET_Struct *)na->values[i];
		l=Verify_FetchStructSlot(ns, "curly");
		ax+=*(int *)l;
	}

	return(NetVal_WrapInt(ax));
}

void *Verify_CountTheEntities(char *str)
{
	char *s;
	int ltc, gtc, ampc, qc, dqc;
	NET_Struct *ns;

	ltc=0;
	gtc=0;
	ampc=0;
	qc=0;
	dqc=0;

	s=str;

	while(*s)
	{
		switch(*s++)
		{
		case '<':
			ltc++;
			break;
		case '>':
			gtc++;
			break;
		case '&':
			ampc++;
			break;
		case '\'':
			qc++;
			break;
		case '"':
			dqc++;
			break;
		default:
			break;
		}
	}

	ns=Verify_NewNetStruct(6);
	Verify_SetStructSlot(ns, "ctLeftAngleBrackets", NetVal_WrapInt(ltc));
	Verify_SetStructSlot(ns, "ctRightAngleBrackets", NetVal_WrapInt(gtc));
	Verify_SetStructSlot(ns, "ctAmpersands", NetVal_WrapInt(ampc));
	Verify_SetStructSlot(ns, "ctApostrophes", NetVal_WrapInt(qc));
	Verify_SetStructSlot(ns, "ctQuotes", NetVal_WrapInt(dqc));

	return(ns);
}

void *Verify_EasyStructTest(void *val)
{
	int *l;
	int i;

	i=0;

	l=Verify_FetchStructSlot(val, "moe");
	i+=*l;

	l=Verify_FetchStructSlot(val, "larry");
	i+=*l;

	l=Verify_FetchStructSlot(val, "curly");
	i+=*l;

	return(NetVal_WrapInt(i));
}

void *Verify_EchoStructTest(void *val)
{
	return(val);
}

void *Verify_ManyTypesTest(void *v1, void *v2, void *v3, void *v4, void *v5, void *v6)
{
	void **arr;

	arr=kalloc(8*sizeof(void *));

	arr[0]=v1;
	arr[1]=v2;
	arr[2]=v3;
	arr[3]=v4;
	arr[4]=v5;
	arr[5]=v6;
	arr[6]=NULL;

	return(NetVal_WrapArray(arr));
}

void *Verify_ModerateSizeArrayCheck(void *val)
{
	int i;
	char buf[256], *s;
	NET_Array *na;

	na=(NET_Array *)val;

	for(i=0; na->values[i]; i++);

	s=na->values[0];
	strcpy(buf, s);
	s=na->values[i-1];
	strcat(buf, s);

	return(NetVal_WrapStr(buf));
}

void *Verify_NestedStructTest(void *st)
{
	void *t, *t2;
	int i;
	char *ty;

	t=st;
	t=Verify_FetchStructSlot(t, "2000");
	t=Verify_FetchStructSlot(t, "04");
	t=Verify_FetchStructSlot(t, "01");

	i=0;
	t2=Verify_FetchStructSlot(t, "curly");
	i+=*(int *)t2;
	t2=Verify_FetchStructSlot(t, "larry");
	i+=*(int *)t2;
	t2=Verify_FetchStructSlot(t, "moe");
	i+=*(int *)t2;

	return(NetVal_WrapInt(i));
}

void *Verify_SimpleStructReturnTest(void *num)
{
//	elem t;
	NET_Struct *ns;
	long l;
	float f, f2;

	f=*(int *)num;

	ns=Verify_NewNetStruct(4);

	Verify_SetStructSlot(ns, "times10", NetVal_WrapInt(f*10));
	Verify_SetStructSlot(ns, "times100", NetVal_WrapInt(f*100));
	Verify_SetStructSlot(ns, "times1000", NetVal_WrapInt(f*1000));

	return(ns);
}

#if 0

elem Verify_NestedStructTest(elem str)
{
	elem t, t2;
	int i;

	t=TyObj_GetSlot(str, SYM("2000"));
	t=TyObj_GetSlot(t, SYM("04"));
	t=TyObj_GetSlot(t, SYM("01"));

	i=0;
	i+=TOINT(TyObj_GetSlot(t, SYM("curly")));
	i+=TOINT(TyObj_GetSlot(t, SYM("larry")));
	i+=TOINT(TyObj_GetSlot(t, SYM("moe")));

	return(FIXNUM(i));
}

elem Verify_SimpleStructReturnTest(elem num)
{
	elem t;
	int i;

	t=TyObj_CloneNull();
	TyObj_SetSlot(t, SYM("times10"), FLONUM(TOFLOAT(num)*10));
	TyObj_SetSlot(t, SYM("times100"), FLONUM(TOFLOAT(num)*100));
	TyObj_SetSlot(t, SYM("times1000"), FLONUM(TOFLOAT(num)*1000));

	return(t);
}

elem Verify_Func(elem func, elem args)
{
	elem t;

	if(func==SYM("validator1.arrayOfStructsTest"))
	{
		t=Verify_ArrayOfStructsTest(CAR(args));
		return(t);
	}
	if(func==SYM("validator1.countTheEntities"))
	{
		t=Verify_CountTheEntities(CAR(args));
		return(t);
	}
	if(func==SYM("validator1.easyStructTest"))
	{
		t=Verify_EasyStructTest(CAR(args));
		return(t);
	}
	if(func==SYM("validator1.echoStructTest"))
	{
		t=CAR(args);
		return(t);
	}
	if(func==SYM("validator1.manyTypesTest"))
	{
		t=args;
		return(t);
	}
	if(func==SYM("validator1.moderateSizeArrayCheck"))
	{
		t=Verify_ModerateSizeArrayCheck(CAR(args));
		return(t);
	}
	if(func==SYM("validator1.nestedStructTest"))
	{
		t=Verify_NestedStructTest(CAR(args));
		return(t);
	}
	if(func==SYM("validator1.simpleStructReturnTest"))
	{
		t=Verify_SimpleStructReturnTest(CAR(args));
		return(t);
	}
	return(MISC_FALSE);
}
#endif

int Verify_Init()
{
	NET_ExportFunc("validator1.arrayOfStructsTest",
		&Verify_ArrayOfStructsTest);
	NET_ExportFunc("validator1.countTheEntities",
		&Verify_CountTheEntities);
	NET_ExportFunc("validator1.easyStructTest",
		&Verify_EasyStructTest);
	NET_ExportFunc("validator1.echoStructTest",
		&Verify_EchoStructTest);
	NET_ExportFunc("validator1.manyTypesTest",
		&Verify_ManyTypesTest);
	NET_ExportFunc("validator1.moderateSizeArrayCheck",
		&Verify_ModerateSizeArrayCheck);
	NET_ExportFunc("validator1.nestedStructTest",
		&Verify_NestedStructTest);

	NET_ExportFunc("validator1.simpleStructReturnTest",
		&Verify_SimpleStructReturnTest);

	return(0);
}
