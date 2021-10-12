#include <general.h>
#include <stdarg.h>

/* s-expression parse duplicated for reason of possible seperation from main s-expr parser */

elem FilterSExpr_Item(char **s);

char *FilterSExpr_EatWhite(char *s)
{
	int i;

	i=0;
	while(*s && *s<=' ')
	{
		i=1;
		s++;
	}
	if(*s == ';')while(*s && *s!='\n')
	{
		i=1;
		s++;
	}
	if(*s == '#' && s[1]=='!')while(*s && !(*s=='!' && s[1]=='#'))
	{
		i=1;
		s++;
	}
	if(i)s=FilterSExpr_EatWhite(s);

	return(s);
}

int FilterSExpr_SpecialP(char *s)
{
	switch(*s)
	{
	case '(':
		return(1);
		break;
	case ')':
		return(1);
		break;
	case '\'':
		return(1);
		break;
	case '`':
		return(1);
		break;
	case '#':
		return(1);
		break;
	case '.':
		return(1);
		break;
	case '\\':
		return(1);
		break;
	case ',':
		return(1);
		break;
	case '@':
		return(1);
		break;
	default:
		return(0);
		break;
	}
	return(0);
}

char *FilterSExpr_Token(char *s, char *b, int *t)
{
	char *ob;

	if(!b)b=sa_ralloc(256);
	ob=b;
	*b=0;

	if(t)*t=0;

	s=FilterSExpr_EatWhite(s);
	if(!*s)return(s);

	if(FilterSExpr_SpecialP(s))
	{
		if(t)*t=TYPE_SPECIAL;

		*b++=*s++;
		*b=0;
	}else if(*s=='"') /* quoted string */
	{
		if(t)*t=OBJECT_STRING;
		s++;
		while(*s && *s!='"')
		{
			if(*s=='\\')
			{
				s++;
				switch(*s)
				{
				case 'n':
					*b++='\n';
					break;
				case 't':
					*b++='\t';
					break;
				case 'r':
					*b++='\r';
					break;
				case '\\':
					*b++='\\';
					break;
				default:
					break;
				}
				s++;
			}else *b++=*s++;
		}
		*b++=0;
		s++;
	}else
	{	/* alphanumeric string that can contain '_' */
		if(t)*t=OBJECT_SYMBOL;

		while(*s && *s>' ' && !FilterSExpr_SpecialP(s))
			*b++=*s++;
		*b++=0;
	}
	return(s);
}

elem FilterSExpr_List(char **s)
{
	elem t, l;
	char buf[256];
	int ty;

	l=MISC_EOL;

	while(1)
	{
		if(!**s)return(MISC_UNDEFINED);
		FilterSExpr_Token(*s, buf, &ty);
		if(buf[0]==')')break;
		if(buf[0]=='.')
		{
//			sa_print("append.\n");
			*s=FilterSExpr_Token(*s, buf, &ty);
			t=FilterSExpr_Item(s);
			*s=FilterSExpr_Token(*s, buf, &ty);
			l=TyFcn_NReverse(l);
			TyFcn_NAppend(l, t);
			return(l);
		}

		t=FilterSExpr_Item(s);
		l=CONS(t, l);
		if(l>1<<31)sa_print("cons returns large value.\n");
	}
//	printf("LARGE1 %lX.\n", l);
	*s=FilterSExpr_Token(*s, buf, &ty);
//	printf("LARGE2 %lX.\n", l);
	l=TyFcn_NReverse(l);
	return(l);
}

elem FilterSExpr_Vector(char **s)
{
	elem lst, t;
	lst=FilterSExpr_List(s);
	t=TyFcn_ListToVector(lst);
	return(t);
}

elem FilterSExpr_Item(char **s)
{
	char buf[256];
	int ty, i;
	elem t;

	t=MISC_UNDEFINED;

	*s=FilterSExpr_EatWhite(*s);
	if(!**s)return(MISC_UNDEFINED);

	*s=FilterSExpr_Token(*s, buf, &ty);
	switch(ty)
	{
	case OBJECT_STRING:
		t=TyFcn_String(buf);
		break;
	case OBJECT_SYMBOL:
		if(isdigit(buf[0]) || ((buf[0]=='-') && isdigit(buf[1])))
			t=ELEM_FROMFIXNUM(sa_atoi(buf));
			else t=SYM(buf);
		break;
	case TYPE_SPECIAL:
		switch(buf[0])
		{
		case '(':
			t=FilterSExpr_List(s);
			break;
		case '#':
			switch(**s)
			{
			case 't':
				*s=FilterSExpr_Token(*s, buf, &ty);
				t=MISC_TRUE;
				break;
			case 'f':
				*s=FilterSExpr_Token(*s, buf, &ty);
				t=MISC_FALSE;
				break;
			case '(':
				*s=FilterSExpr_Token(*s, buf, &ty); /* ( */
				t=FilterSExpr_Vector(s);
				break;
			case '\\':
				*s=FilterSExpr_Token(*s, buf, &ty); /* slash */
				i=**s;
				if(isalpha(i))*s=FilterSExpr_Token(*s, buf, &ty); /* char name */
					else *s=*s+1;
				t=ELEM_FROMCHAR(i);
				break;
			}
			break;
		case '\'':
			t=FilterSExpr_Item(s);
			t=CONS(t, MISC_EOL);
			t=CONS(SYM("quote"), t);
			break;
		case '`':
			t=FilterSExpr_Item(s);
			t=CONS(t, MISC_EOL);
			t=CONS(SYM("quasiquote"), t);
			break;
		case ',':
			if(**s=='@')
			{
				*s=*s+1;
				t=FilterSExpr_Item(s);
				t=CONS(t, MISC_EOL);
				t=CONS(SYM("unquote-splicing"), t);
			}else
			{
				t=FilterSExpr_Item(s);
				t=CONS(t, MISC_EOL);
				t=CONS(SYM("unquote"), t);
			}
			break;
		default:
			sa_error("parse: unknown special.\n");
			break;
		}
		break;
	default:
		sa_error("parse wrong type.\n");
		return(MISC_NULL);
		break;
	}
	return(t);
}

elem FilterSExpr_ParseMessage(char *msg)
{
	elem cur;
	cur=MISC_EOL;

	while(*msg)
		cur=CONS(FilterSExpr_Item(&msg), cur);
	cur=TyFcn_NReverse(cur);
	return(cur);
}


static int sprint(char **s, char *form, ...)
{
	va_list lst;

	va_start(lst, form);
	vsprintf(*s, form, lst);
	*s=*s+strlen(*s);
	va_end(lst);
}

int FilterSExpr_DumpObject(char **s, elem obj)
{
	elem *buf;
	int i, c;
	double x;

	buf=ELEM_TOOBJECT(obj);
//	printf("objbuf %p\n", buf);

	if(ELEM_FLONUMP(obj))
	{
		x=TyMath_ToDouble(obj);
		sprint(s, "%g", x);
		return(0);
	}

	switch(buf[0]&255)
	{
	case OBJECT_VECTOR:
		if(((buf[0]>>8)&255)>11)
		{
//			sa_print("#<vector-type %d>", ((buf[0]>>8)&255));
			sa_error("FilterSExpr_DumpObject: unknown vector type\n");
			sprint(s, "#u");
			break;
		}

		c=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
//		c=0;
		sprint(s, "#(");
		for(i=0; i<c; i++)
		{
//			FilterSExpr_DumpElem(s, buf[i+2]);
			FilterSExpr_DumpElem(s, TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(i)));
			if((i+1)<c)sprint(s, " ");
		}
		sprint(s, ")");
		break;
	case OBJECT_STRING:
		sprint(s, "\"%s\"", ELEM_TOSTRING(obj));
		break;
	case OBJECT_SYMBOL:
		sprint(s, "%s", ELEM_TOSYMBOL(obj));
		break;
	default:
		sa_error("FilterSExpr_DumpObject: unknown object type\n");
//		sa_print("#<obj-type %d>", buf[0]&255);
		sprint(s, "#u");
		break;
	}
	return(0);
}

int FilterSExpr_DumpMisc(char **s, elem obj)
{
	if(ELEM_CHARP(obj))
	{
		sprint(s, "#\\%c", ELEM_TOCHAR(obj));
		return(0);
	}
	switch(obj)
	{
	case MISC_EOL:
		sprint(s, "()");
		return(0);
		break;
	case MISC_TRUE:
		sprint(s, "#t");
		return(0);
		break;
	case MISC_FALSE:
		sprint(s, "#f");
		return(0);
		break;
	case MISC_NULL:
		sprint(s, "#z");
		return(0);
		break;
	default:
		break;
	}
	sprint(s, "(!misc %d %d)", (obj>>3)&31, obj>>8);
	return(0);
}

int FilterSExpr_DumpElem(char **s, elem obj)
{
	switch(ELEM_TYPE3(obj))
	{
	case TYPE_FIXNUM:
		sprint(s, "%d", ELEM_TOFIXNUMi(obj));
		break;
//	case TYPE_LOCATIVE:
//	case TYPE_LOCATIVE2:
//		sa_print("%X", ELEM_TOLOCATIVE(obj));
//		break;
	case TYPE_CONS:
		FilterSExpr_DumpList(s, obj);
		break;
	case TYPE_OBJECT:
		FilterSExpr_DumpObject(s, obj);
		break;
	case TYPE_MISC:
		FilterSExpr_DumpMisc(s, obj);
		break;
	default:
		sa_error("FilterSExpr_DumpElem: unknown elem type\n");
		sprint(s, "#u", ELEM_TYPE3(obj));
		break;
	}
	return(0);
}

int FilterSExpr_DumpList(char **s, elem lst)
{
	elem cur;

	cur=lst;
	sprint(s, "(");
	while(cur!=MISC_EOL)
	{
		FilterSExpr_DumpElem(s, CAR(cur));
		if(CDR(cur)!=MISC_EOL)sprint(s, " ");

		if(!ELEM_CONSP(CDR(cur)) && (CDR(cur) != MISC_EOL))
		{
			sprint(s, " . ");
			FilterSExpr_DumpElem(s, CDR(cur));
			cur=MISC_EOL;
			break;
		}
		cur=CDR(cur);
	}
	sprint(s, ")");
}

elem FilterSExpr_FillBuf(char *buf, int lim, elem lst)
{
	static char t[1024], *tp;
	elem cur;

	cur=lst;
	while(ELEM_CONSP(cur))
	{
		tp=&t;
		FilterSExpr_DumpElem(&tp, CAR(cur));
		if(strlen(t)>=lim)return(cur);

		kprint("FilterSExpr_FillBuf: write \"%s\"\n", t);

		strcpy(buf, t);
		lim-=strlen(buf)+1;
		buf=buf+strlen(buf);
		*buf++='\n';
		*buf=0;

		cur=CDR(cur);
	}
	return(cur);
}
