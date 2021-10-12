#include <scmcc.h>

typrint_info *typrint_stack[16];
int typrint_stackpos;
elem typrint_jn1_lst;

int TyPrint_Indent(typrint_info *inf)
{
	int i;
	for(i=0; i<inf->ind; i++)
		inf->end=sa_prints(inf->end, " ");
	return(0);
}

int TyPrint_VecType(elem obj, typrint_info *inf)
{
	elem *buf;

	buf=ELEM_TOOBJECT(obj);

	switch(((buf[0]>>8)&255))
	{
	case VECTOR_CLOSURE:
		inf->end=sa_prints(inf->end, "#<closure %X: ", obj);
		TyPrint_List(CAR(VECTOR_REF(obj, 0)), inf);
		inf->end=sa_prints(inf->end, ">");
		break;
	case VECTOR_ENV:
		inf->end=sa_prints(inf->end, "#<binding-env %X>", obj);
		break;

	case VECTOR_ENVOBJ:
		if(inf->flags&TYPRINT_NOOBJ)
			inf->end=sa_prints(inf->end, "#<object %X>", obj);
			else TyObj_ObjectPrint(obj);
		break;

	case VECTOR_CONTEXT:
		inf->end=sa_prints(inf->end, "#<context %X>", obj);
		break;

	default:
		inf->end=sa_prints(inf->end, "#<vector-type %d %X>",
			((buf[0]>>8)&255), obj);
		break;
	}
	return(0);
}

int TyPrint_Object(elem obj, typrint_info *inf)
{
	elem *buf;
	int i, c;
	double x;
	char t[64];

	buf=ELEM_TOOBJECT(obj);

	if(ELEM_FLONUMP(obj))
	{
		x=TyMath_ToDouble(obj);
		sprintf(t, "%f", (float)x);
		strcat(inf->end, t);
		inf->end=inf->end+strlen(inf->end);
		return(0);
	}

	switch(buf[0]&255)
	{
	case OBJECT_VECTOR:
		if(((buf[0]>>8)&255)>11)
		{
			TyPrint_VecType(obj, inf);
			break;
		}

		c=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
//		c=0;
		inf->end=sa_prints(inf->end, "#(");
		for(i=0; i<c; i++)
		{
//			TyPrint_Elem(buf[i+2]);
			TyPrint_Elem(TyFcn_VectorRef(obj,
				ELEM_FROMFIXNUM(i)), inf);
			if((i+1)<c)inf->end=sa_prints(inf->end, " ");
		}
		inf->end=sa_prints(inf->end, ")");
		break;
	case OBJECT_STRING:
		if(inf->flags&TYPRINT_DISPLAY)
			inf->end=sa_prints(inf->end, "%s",
				ELEM_TOSTRING(obj));
			else inf->end=sa_prints(inf->end, "\"%s\"",
				ELEM_TOSTRING(obj));
		break;
	case OBJECT_SYMBOL:
		inf->end=sa_prints(inf->end, "%s", ELEM_TOSYMBOL(obj));
		break;
	case OBJECT_TYPEX:
		TypeX_Print(obj, inf);
		break;
	default:
		inf->end=sa_prints(inf->end, "#<obj-type %d %X>",
			buf[0]&255, obj);
		break;
	}
	return(0);
}

int TyPrint_Misc(elem obj, typrint_info *inf)
{
	int i;

	if(ELEM_CHARP(obj))
	{
		i=ELEM_TOCHAR(obj);
		if((i>' ') && (i<127))
			inf->end=sa_prints(inf->end, "#\\%c", i);
			else inf->end=sa_prints(inf->end, "#\\x%x", i);
		return(0);
	}
	switch(obj)
	{
	case MISC_EOL:
		inf->end=sa_prints(inf->end, "()");
		return(0);
		break;
	case MISC_TRUE:
		inf->end=sa_prints(inf->end, "#t");
		return(0);
		break;
	case MISC_FALSE:
		inf->end=sa_prints(inf->end, "#f");
		return(0);
		break;
	case MISC_NULL:
		inf->end=sa_prints(inf->end, "#z");
		return(0);
		break;
	default:
		break;
	}
	inf->end=sa_prints(inf->end, "#<misc %d %d>", (obj>>3)&31, obj>>8);
	return(0);
}

int TyPrint_Elem(elem obj, typrint_info *inf)
{
	if((inf->end-inf->buf)>(1<<13))
	{
		inf->end=sa_prints(inf->end, "<<overflow>>");
		return(-1);
	}

	switch(obj)
	{
	case MISC_EOL:
		inf->end=sa_prints(inf->end, "()");
		return(0);
		break;
	case MISC_TRUE:
		inf->end=sa_prints(inf->end, "#t");
		return(0);
		break;
	case MISC_FALSE:
		inf->end=sa_prints(inf->end, "#f");
		return(0);
		break;
	default:
		break;
	}
	switch(ELEM_TYPE3(obj))
	{
	case TYPE_FIXNUM:
		inf->end=sa_prints(inf->end, "%d", ELEM_TOFIXNUMi(obj));
		break;
	case TYPE_CONS:
	case TYPE_WEAKCONS:
		TyPrint_List(obj, inf);
		break;
	case TYPE_OBJECT:
	case TYPE_WEAKOBJECT:
		TyPrint_Object(obj, inf);
		break;
	case TYPE_MISC:
		TyPrint_Misc(obj, inf);
		break;
	default:
		inf->end=sa_prints(inf->end, "#<type %d>", ELEM_TYPE3(obj));
		break;
	}
	return(0);
}

int TyPrint_ListCode(elem lst, typrint_info *inf)
{
	elem cur;
	int sp, jn, jn1, idx;

	cur=lst;
//	TyPrint_Indent(inf);
	inf->end=sa_prints(inf->end, "(");
	inf->ind+=2;
	jn=1;
	idx=0;

	jn1=0;
	if(TyFcn_ObjectInListP(CAR(lst), typrint_jn1_lst)==MISC_TRUE)
		jn1=1;


	while(cur!=MISC_EOL)
	{
		sp=0;
		if(ELEM_CONSP(CAR(cur)))
		{
			if(CAAR(cur)==SYM("quote"))
			{
				TyPrint_Elem(CADR(CAR(cur)), inf);
				sp=1;
			}else jn=0; //if(idx || !jn1)jn=0;
		}
		if(!sp)
			TyPrint_Elem(CAR(cur), inf);
		if(ELEM_CONSP(CDR(cur))) //inf->end=sa_prints(inf->end, "\n");
		{
			if(ELEM_CONSP(CADR(cur)))
			{
				if(CAR(CADR(cur))==SYM("quote"))
				{
					inf->end=sa_prints(inf->end, " '");
				}else if(!jn || !jn1)
				{
					inf->end=sa_prints(inf->end, "\n");
					TyPrint_Indent(inf);
				}else inf->end=sa_prints(inf->end, " ");
			}else if(!jn)
			{
				inf->end=sa_prints(inf->end, "\n");
				TyPrint_Indent(inf);
			}else inf->end=sa_prints(inf->end, " ");
		}

		if(!ELEM_CONSP(CDR(cur)) && (CDR(cur) != MISC_EOL))
		{
			inf->end=sa_prints(inf->end, " . ");
			TyPrint_Elem(CDR(cur), inf);
			cur=MISC_EOL;
			break;
		}
		idx++;
		cur=CDR(cur);
	}
	inf->end=sa_prints(inf->end, ")");
	inf->ind-=2;
	return(0);
}

int TyPrint_ListFormatted(elem lst, typrint_info *inf)
{
	elem cur;

	cur=lst;
	while(cur!=MISC_EOL)
	{
		//symbols would be commands
		if(ELEM_CONSP(CAR(cur)))
			TyPrint_ListFormatted(CAR(cur), inf);
		if(ELEM_STRINGP(CAR(cur)))
		{
			inf->end=sa_prints(inf->end, "%s",
				ELEM_TOSTRING(CAR(cur)));
		}

		cur=CDR(cur);
	}
	return(0);
}

int TyPrint_List(elem lst, typrint_info *inf)
{
	elem cur;

	if(inf->flags & TYPRINT_CODE)
		return(TyPrint_ListCode(lst, inf));

	if(inf->flags & TYPRINT_FORMATTED)
		return(TyPrint_ListFormatted(lst, inf));

	cur=lst;
	inf->end=sa_prints(inf->end, "(");
	while(cur!=MISC_EOL)
	{
		TyPrint_Elem(CAR(cur), inf);
		if(ELEM_CONSP(CDR(cur)))inf->end=sa_prints(inf->end, " ");

		if(!ELEM_CONSP(CDR(cur)) && (CDR(cur) != MISC_EOL))
		{
			inf->end=sa_prints(inf->end, " . ");
			TyPrint_Elem(CDR(cur), inf);
			cur=MISC_EOL;
			break;
		}
		cur=CDR(cur);
	}
	inf->end=sa_prints(inf->end, ")");
	return(0);
}

elem TyPrint_PrintDefaults(elem obj)
{
	typrint_info *inf, *inf2;

	inf=sa_malloc(sizeof(typrint_info));
	inf->buf=sa_malloc(1<<14);
	inf->end=inf->buf;
	inf->flags=0;
	inf->ind=0;
	if(typrint_stackpos)inf->ind=typrint_stack[typrint_stackpos-1]->ind;
	typrint_stack[typrint_stackpos++]=inf;

	TyPrint_Elem(obj, inf);

	typrint_stackpos--;
	if(typrint_stackpos)
	{
		inf2=typrint_stack[typrint_stackpos-1];
		strcpy(inf2->end, inf->buf);
		inf2->end+=strlen(inf->buf);
	}else sa_print(inf->buf);

	sa_free(inf->buf);
	sa_free(inf);

	return(MISC_NULL);
}

elem TyPrint_PrintFlags(elem obj, elem flags)
{
	typrint_info *inf, *inf2;

	inf=sa_malloc(sizeof(typrint_info));
	inf->buf=sa_malloc(1<<14);
	memset(inf->buf, 0, 1<<14);
	inf->end=inf->buf;
	inf->flags=TOINT(flags);
	inf->ind=0;
	if(typrint_stackpos)inf->ind=typrint_stack[typrint_stackpos-1]->ind;
	typrint_stack[typrint_stackpos++]=inf;

	TyPrint_Elem(obj, inf);

	typrint_stackpos--;
	if(typrint_stackpos)
	{
		inf2=typrint_stack[typrint_stackpos-1];
		strcpy(inf2->end, inf->buf);
		inf2->end+=strlen(inf->buf);
	}else sa_print(inf->buf);

	sa_free(inf->buf);
	sa_free(inf);

	return(MISC_NULL);
}

elem TyPrint_PrintString(elem obj, elem flags)
{
	typrint_info *inf, *inf2;
	elem t;

	inf=sa_malloc(sizeof(typrint_info));
	inf->buf=sa_malloc(1<<14);
	memset(inf->buf, 0, 1<<14);
	inf->end=inf->buf;
	inf->flags=TOINT(flags);
	inf->ind=0;
	if(typrint_stackpos)inf->ind=typrint_stack[typrint_stackpos-1]->ind;
	typrint_stack[typrint_stackpos++]=inf;

	TyPrint_Elem(obj, inf);
	inf->end=0;

	typrint_stackpos--;

	t=STRING(inf->buf);

	sa_free(inf->buf);
	sa_free(inf);

	return(t);
}

int TyPrint_Init()
{
	SAGC_AddRoot(&typrint_jn1_lst);
	typrint_jn1_lst=MISC_EOL;

	typrint_jn1_lst=CONS(SYM("lambda"), typrint_jn1_lst);
	typrint_jn1_lst=CONS(SYM("if"), typrint_jn1_lst);
	typrint_jn1_lst=CONS(SYM("let"), typrint_jn1_lst);
}
