/*
goal: be simple xml parser/printer

internal:
(key (opts*) . body)

(key) => '<key/>'
(key (opts...)) => <key opts />
(key () body...) => <key>body</key>
(key (opts...) body...) <key opts>body</key>

for now do io on strings and provide file loading/saving.
 */
#include <general.h>

#define TOKEN_SPECIAL	1
#define TOKEN_STRING	2
#define TOKEN_SYMBOL	3

static int line=1;

char *ParseXML_EatWhite(char *s)
{
	int i, r;

	i=0;
	while(*s && *s<=' ')
	{
		if(*s=='\n')
		{
			line++;
			*s=' ';
		}
		i=1;
		s++;
	}

	if(i)s=ParseXML_EatWhite(s);

	return(s);
}

int ParseXML_SpecialP(char *s)
{
	switch(*s)
	{
	case '<':
		return(1);
		break;
	case '>':
		return(1);
		break;
	case '/':
		return(1);
		break;
	case '=':
		return(1);
		break;
	case '?':
		return(1);
		break;
	default:
		return(0);
		break;
	}
	return(0);
}

int ParseXML_ContSpecialP(char *s)
{
	switch(*s)
	{
	case '<':
		return(1);
		break;
	case '&':
		return(1);
		break;
	default:
		return(0);
		break;
	}
	return(0);
}

char *ParseXML_Token(char *s, char *b, int *ty)
{
	char *ob, *t;
	char buf[16];

	if(!b)b=sa_ralloc(256);
	ob=b;
	*b=0;

	if(ty)*ty=0;

	s=ParseXML_EatWhite(s);
	if(!*s)return(s);

	if(ParseXML_SpecialP(s))
	{
		if(ty)*ty=TOKEN_SPECIAL;

		*b++=*s++;
		*b=0;
	}else if(*s=='"') /* quoted string */
	{
		if(ty)*ty=TOKEN_STRING;
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
			}else if(*s=='&')
			{
				s++;
				t=buf;
				while(*s!=';')*t++=*s++;
				*t++=0;
				s++;

				if(!strcmp(buf, "amp"))*b++='&';
				if(!strcmp(buf, "lt"))*b++='<';
				if(!strcmp(buf, "gt"))*b++='>';
				if(!strcmp(buf, "quot"))*b++='"';
				if(!strcmp(buf, "nbsp"))*b++=' ';
			}else *b++=*s++;
		}
		*b++=0;
		s++;
	}else
	{
		if(ty)*ty=TOKEN_SYMBOL;

		while(*s && *s>' ' && !ParseXML_SpecialP(s) &&
			((b-ob)<254))
			*b++=*s++;
		*b++=0;
	}
	return(s);
}

char *ParseXML_ParseText(char *s, char *b)
{
	char *ob, *t;
	char buf[16];

	if(!b)b=sa_ralloc(4096);
	ob=b;
	*b=0;

	s=ParseXML_EatWhite(s);
	if(!*s)return(s);

//	while(*s==' ')*b++=*s++;

	while(1)
	{
		while((*s>' ') && !ParseXML_ContSpecialP(s))
			*b++=*s++;
		if(!*s || ParseXML_ContSpecialP(s))break;

		if(*s<=' ')
		{
			s=ParseXML_EatWhite(s);
			*b++=' ';
		}

		if(*s=='&')
		{
			s++;
			t=buf;
			while(*s!=';')*t++=*s++;
			*t++=0;
			s++;

			if(!strcmp(buf, "amp"))*b++='&';
			if(!strcmp(buf, "lt"))*b++='<';
			if(!strcmp(buf, "gt"))*b++='>';
			if(!strcmp(buf, "quot"))*b++='"';
			if(!strcmp(buf, "nbsp"))*b++=' ';
		}
	}
	*b++=0;

	return(s);
}

elem ParseXML_ParseOpts(char **s)
{
	char var[32];
	char eq[16];
	char val[256];
	int ty;
	elem x, t;

	x=MISC_EOL;

	while(1)
	{
		ParseXML_Token(*s, var, &ty);
		if((var[0]=='>') && (ty==TOKEN_SPECIAL))
			break;
		if((var[0]=='/') && (ty==TOKEN_SPECIAL))
			break;
		if((var[0]=='?') && (ty==TOKEN_SPECIAL))
			break;
		if(ty!=TOKEN_SYMBOL)
		{
			kprint("parse error (inv attribute).\n");
			return(MISC_UNDEFINED);
		}

		*s=ParseXML_Token(*s, var, &ty);
		*s=ParseXML_Token(*s, eq, &ty);

		if((ty!=TOKEN_SPECIAL) || (eq[0]!='='))
		{
			kprint("parse error (attr equal).\n");
			return(MISC_UNDEFINED);
		}

		*s=ParseXML_Token(*s, val, &ty);
		if(ty!=TOKEN_STRING)
		{
			kprint("parse error (inv attribute arg).\n");
			return(MISC_UNDEFINED);
		}

		t=CONS(SYM(var), CONS(STRING(val), MISC_EOL));
		x=CONS(t, x);
	}
	x=TyFcn_NReverse(x);

	return(x);
}

elem ParseXML_ParseExpr(char **s)
{
	char buf[256], buf2[16];
	char key[32];
	int ty, i;
	char *s2;

	elem kv, opts, t, x;

	*s=ParseXML_EatWhite(*s);
	if(!*(*s))return(MISC_UNDEFINED);

//	strncpy(buf, *s, 5);
//	buf[5]=0;
//	kprint("parse: %s\n", buf);

	ParseXML_Token(*s, buf, &ty);
	if((buf[0]=='<') && (ty==TOKEN_SPECIAL))
	{
		*s=ParseXML_Token(*s, buf, &ty);
		if(*s[0]=='?')
			*s=*s+1;
		if(*s[0]=='!')
		{
			s2=*s;
			i=1;
			while(*s2 && i)
			{
				if(*s2=='<')i++;
				if(*s2=='>')i--;
				if(*s2=='[')i++;
				if(*s2==']')i--;
				s2++;
			}
			*s=s2;
			return(ParseXML_ParseExpr(s));
		}

		*s=ParseXML_Token(*s, key, &ty);
		if(ty!=TOKEN_SYMBOL)
		{
			kprint("parse error (inv tag).\n");
			return(MISC_UNDEFINED);
		}
		if((**s>' ') && (**s!='>') && (**s!='/'))
		{
			kprint("parse error (inv char after tag).\n");
			return(MISC_UNDEFINED);
		}

		kv=SYM(key);
		opts=ParseXML_ParseOpts(s);
		if(opts==MISC_UNDEFINED)return(t);

		*s=ParseXML_Token(*s, buf, &ty);
		if((buf[0]=='/') && (ty==TOKEN_SPECIAL))
		{
			*s=ParseXML_Token(*s, buf, &ty);
			return(CONS(kv, CONS(opts, MISC_EOL)));
		}
		if((buf[0]=='?') && (ty==TOKEN_SPECIAL))
		{
			*s=ParseXML_Token(*s, buf, &ty);
			x=CONS(kv, CONS(opts, MISC_EOL));
			x=CONS(SYM("?"), x);
			return(x);
		}
		if(buf[0]!='>')
		{
			kprint("parse error (expected close '>').\n");
			return(MISC_UNDEFINED);
		}

		x=MISC_EOL;
		while(1)
		{
			s2=*s;
			s2=ParseXML_Token(s2, buf, &ty);
			s2=ParseXML_Token(s2, buf2, &ty);

			if(buf[0]=='<' && buf2[0]=='/')
			{
				s2=ParseXML_Token(s2, buf, &ty);
				s2=ParseXML_Token(s2, buf, &ty);
				*s=s2;
				break;
			}

			t=ParseXML_ParseExpr(s);
			if(t==MISC_UNDEFINED)return(t);
			x=CONS(t, x);
		}
		x=TyFcn_NReverse(x);
		x=CONS(opts, x);
		x=CONS(kv, x);
		return(x);
	}

	s2=kralloc(2048);
	*s=ParseXML_ParseText(*s, s2);

	return(STRING(s2));
}

char *ParseXML_PrintExpr(char *s, elem exp)
{
	elem cur;

	if(ELEM_STRINGP(exp))
	{
		s=kprints(s, "%s", ELEM_TOSTRING(exp));
		return(s);
	}

	s=kprints(s, "<%s", ELEM_TOSYMBOL(CAR(exp)));

	cur=CADR(exp);
	while(ELEM_CONSP(cur))
	{
		s=kprints(s, " %s=\"%s\"",
			ELEM_TOSYMBOL(CAAR(cur)),
			ELEM_TOSTRING(CADR(CAR(cur))));
		cur=CDR(cur);
	}

	cur=CDDR(exp);
	if(cur==MISC_EOL)
	{
		s=kprints(s, "/>");
		return(s);
	}
	s=kprints(s, ">");

	while(ELEM_CONSP(cur))
	{
		s=ParseXML_PrintExpr(s, CAR(cur));
		cur=CDR(cur);
	}
	s=kprints(s, "</%s>", ELEM_TOSYMBOL(CAR(exp)));

	return(s);
}

elem ParseXML_Xml2List(elem str)
{
	char *buf, *s;
	elem t;

	buf=ELEM_TOSTRING(str);
	buf=strdup(buf);
	s=buf;
	t=ParseXML_ParseExpr(&s);
	free(buf);

	return(t);
}

elem ParseXML_List2Xml(elem exp)
{
	char *buf, *s;
	elem t;

	buf=kalloc(16384);
	s=ParseXML_PrintExpr(buf, exp);
	*s++=0;

	t=STRING(buf);
	kfree(buf);
	return(t);
}

elem ParseXML_LoadFile(elem str)
{
	char *buf, *s;
	elem t, x;
	int sz;

	buf=sa_loadfile(ELEM_TOSTRING(str), &sz);
	if(!buf)return(MISC_NULL);

	x=MISC_EOL;
	s=buf;
	while(*s)
	{
		t=ParseXML_ParseExpr(&s);
		if(t==MISC_UNDEFINED)break;
//		TyFcn_DumpElemBR(t);
		x=CONS(t, x);
	}
	x=TyFcn_NReverse(x);

	return(x);
}

int ParseXML_Init()
{
	Interp_DefinePrimative("xml->list", &ParseXML_Xml2List, 1);
	Interp_DefinePrimative("list->xml", &ParseXML_List2Xml, 1);
	Interp_DefinePrimative("load-xml-file", &ParseXML_LoadFile, 1);
}
