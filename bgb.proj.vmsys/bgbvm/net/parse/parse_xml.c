#include <general.h>
#include <net/pdnet.h>

#define TOKEN_SPECIAL	1
#define TOKEN_STRING	2
#define TOKEN_SYMBOL	3

static int line=1;

char *NetParse_XML_EatWhite(char *s)
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

	if(i)s=NetParse_XML_EatWhite(s);

	return(s);
}

int NetParse_XML_SpecialP(char *s)
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

int NetParse_XML_ContSpecialP(char *s)
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

char *NetParse_XML_Token(char *s, char *b, int *t)
{
	char *ob;

	if(!b)b=kralloc(256);
	ob=b;
	*b=0;

	if(t)*t=0;

	s=NetParse_XML_EatWhite(s);
	if(!*s)return(s);

	if(NetParse_XML_SpecialP(s))
	{
		if(t)*t=TOKEN_SPECIAL;

		*b++=*s++;
		*b=0;
	}else if(*s=='"') /* quoted string */
	{
		if(t)*t=TOKEN_STRING;
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
	{
		if(t)*t=TOKEN_SYMBOL;

		while(*s && *s>' ' && !NetParse_XML_SpecialP(s) &&
			((b-ob)<254))
			*b++=*s++;
		*b++=0;
	}
	return(s);
}

char *NetParse_XML_ParseText(char *s, char *b)
{
	char *ob, *t;
	char buf[16];

	if(!b)b=kralloc(4096);
	ob=b;
	*b=0;

	s=NetParse_XML_EatWhite(s);
	if(!*s)return(s);

	while(1)
	{
		while(*s && !NetParse_XML_ContSpecialP(s))
			*b++=*s++;
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
		}else break;
	}
	*b++=0;

	return(s);
}

NetParse_Attr *NetParse_XML_ParseOpts(char **s)
{
	char var[32];
	char eq[16];
	char val[256];
	int ty;
	NetParse_Attr *lst, *end, *tmp;

	lst=NULL;
	end=NULL;

	while(1)
	{
		NetParse_XML_Token(*s, var, &ty);
		if((var[0]=='>') && (ty==TOKEN_SPECIAL))
			break;
		if((var[0]=='/') && (ty==TOKEN_SPECIAL))
			break;
		if((var[0]=='?') && (ty==TOKEN_SPECIAL))
			break;
		if(ty!=TOKEN_SYMBOL)
		{
			kprint("parse error (inv attribute).\n");
			return(NULL);
		}

		*s=NetParse_XML_Token(*s, var, &ty);
		*s=NetParse_XML_Token(*s, eq, &ty);

		if((ty!=TOKEN_SPECIAL) || (eq[0]!='='))
		{
			kprint("parse error (attr equal).\n");
			return(NULL);
		}

		*s=NetParse_XML_Token(*s, val, &ty);
		if(ty!=TOKEN_STRING)
		{
			kprint("parse error (inv attribute arg).\n");
			return(NULL);
		}

//		t=CONS(SYM(var), CONS(STRING(val), MISC_EOL));
//		x=CONS(t, x);
		tmp=kalloc(sizeof(NetParse_Attr));
		tmp->next=NULL;
		tmp->key=kstrdup(var);
		tmp->value=kstrdup(val);

		if(end)
		{
			end->next=tmp;
			end=tmp;
		}else
		{
			lst=tmp;
			end=tmp;
		}
	}

	return(lst);
}

NetParse_Node *NetParse_XML_ParseExpr(char **s)
{
	char buf[256], buf2[16];
	char key[32];
	int ty, i;
	char *s2;

//	elem kv, opts, t, x;
	NetParse_Node *tmp, *t, *end;

	*s=NetParse_XML_EatWhite(*s);
	if(!*(*s))return(NULL);

//	strncpy(buf, *s, 5);
//	buf[5]=0;
//	kprint("parse: %s\n", buf);

	NetParse_XML_Token(*s, buf, &ty);
	if((buf[0]=='<') && (ty==TOKEN_SPECIAL))
	{
		*s=NetParse_XML_Token(*s, buf, &ty);
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
			return(NetParse_XML_ParseExpr(s));
		}

		*s=NetParse_XML_Token(*s, key, &ty);
		if(ty!=TOKEN_SYMBOL)
		{
			kprint("parse error (inv tag).\n");
			return(NULL);
		}
		if((**s>' ') && (**s!='>'))
		{
			kprint("parse error (inv char after tag).\n");
			return(NULL);
		}
//		kv=SYM(key);
//		opts=NetParse_XML_ParseOpts(s);
//		if(opts==MISC_UNDEFINED)return(t);

		tmp=kalloc(sizeof(NetParse_Node));
		tmp->next=NULL;
		tmp->key=kstrdup(key);
		tmp->attr=NetParse_XML_ParseOpts(s);
		tmp->first=NULL;

		*s=NetParse_XML_Token(*s, buf, &ty);
		if((buf[0]=='/') && (ty==TOKEN_SPECIAL))
		{
			*s=NetParse_XML_Token(*s, buf, &ty);
			return(tmp);
		}
		if((buf[0]=='?') && (ty==TOKEN_SPECIAL))
		{
			*s=NetParse_XML_Token(*s, buf, &ty);
//			x=CONS(kv, CONS(opts, MISC_EOL));
//			x=CONS(SYM("?"), x);
			strcpy(buf, "?");
			strcat(buf, tmp->key);
			kfree(tmp->key);
			tmp->key=kstrdup(buf);
			return(tmp);
		}
		if(buf[0]!='>')
		{
			kprint("parse error (expected close '>').\n");
			return(NULL);
		}

		end=NULL;
//		x=MISC_EOL;
		while(1)
		{
			s2=*s;
			s2=NetParse_XML_Token(s2, buf, &ty);
			s2=NetParse_XML_Token(s2, buf2, &ty);

			if(buf[0]=='<' && buf2[0]=='/')
			{
				s2=NetParse_XML_Token(s2, buf, &ty);
				s2=NetParse_XML_Token(s2, buf, &ty);
				*s=s2;
				break;
			}

			t=NetParse_XML_ParseExpr(s);
			if(!t)return(t);
//			x=CONS(t, x);
			if(end)
			{
				end->next=t;
				end=t;
			}else
			{
				tmp->first=t;
				end=t;
			}
		}
		return(tmp);
	}

	s2=kralloc(2048);
	*s=NetParse_XML_ParseText(*s, s2);

	tmp=kalloc(sizeof(NetParse_Node));
	tmp->next=NULL;
	tmp->key=NULL;
	tmp->text=kstrdup(s2);
	tmp->attr=NULL;
	tmp->first=NULL;

	return(tmp);
}

char *NetParse_XML_PrintText(char *s, char *t)
{
	kprint("'%s' ", t);

	while(*t)
	{
		switch(*t)
		{
		case '<':
			s=kprints(s, "&lt;");
			break;
		case '>':
			s=kprints(s, "&gt;");
			break;
		case '&':
			s=kprints(s, "&amp;");
			break;
		case '"':
			s=kprints(s, "&quot;");
			break;
		default:
			*s++=*t;
			break;
		}
		t++;
	}
	return(s);
}

char *NetParse_XML_PrintExpr(char *s, NetParse_Node *exp)
{
	NetParse_Attr *cur;
	NetParse_Node *cur2;

	if(!exp->key)
	{
		if(!exp->text)
		{
			kprint("XML_PrintExpr: Bad Expr\n");
			return(s);
		}
		s=NetParse_XML_PrintText(s, exp->text);
		return(s);
	}

	kprint("{%s ", exp->key);

	s=kprints(s, "<%s", exp->key);

	cur=exp->attr;
	while(cur)
	{
		s=kprints(s, " %s=\"%s\"", cur->key, cur->value);
		cur=cur->next;
	}

	if(!exp->first)
	{
		s=kprints(s, "/>");
		kprint("}");
		return(s);
	}else
		s=kprints(s, ">");

	cur2=exp->first;
	while(cur2)
	{
		s=NetParse_XML_PrintExpr(s, cur2);
		cur2=cur2->next;
	}
	s=kprints(s, "</%s>", exp->key);

	kprint("}");
	return(s);
}
