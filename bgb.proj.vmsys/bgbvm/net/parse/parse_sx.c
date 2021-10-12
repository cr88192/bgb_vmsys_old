#include <general.h>
#include <net/pdnet.h>

#define TOKEN_SPECIAL	1
#define TOKEN_STRING	2
#define TOKEN_SYMBOL	3

static int line=1;

char *NetParse_SX_EatWhite(char *s)
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
	if(*s == ';')while(*s && *s!='\n')
	{
		i=1;
		s++;
	}

	if(*s == '#' && s[1]=='|')
	{
		i=1;
		r=1;
		s+=2;
		while(*s && r)
		{
			if(*s=='|' && s[1]=='#')
			{
				r--;
				s+=2;
				continue;
			}
			if(*s=='#' && s[1]=='|')
			{
				r++;
				s+=2;
				continue;
			}
			s++;
		}
	}

	if(i)s=NetParse_SX_EatWhite(s);

	return(s);
}

int NetParse_SX_SpecialP(char *s)
{
	switch(*s)
	{
	case '(':
		return(1);
		break;
	case ')':
		return(1);
		break;
	case '[':
		return(1);
		break;
	case ']':
		return(1);
		break;
	case '{':
		return(1);
		break;
	case '}':
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

char *NetParse_SX_Token(char *s, char *b, int *t)
{
	char *ob;

	if(!b)b=kralloc(256);
	ob=b;
	*b=0;

	if(t)*t=0;

	s=NetParse_SX_EatWhite(s);
	if(!*s)return(s);

	if(NetParse_SX_SpecialP(s))
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

		while(*s && *s>' ' && !NetParse_SX_SpecialP(s) &&
			((b-ob)<254))
			*b++=*s++;
		*b++=0;
	}
	return(s);
}


NetParse_Node *NetParse_SX_ParseExpr(char **s)
{
	char buf[256], buf2[16];
	char key[32];
	int ty, i;
	char *s2;

//	elem kv, opts, t, x;
	NetParse_Node *tmp, *t, *end;

	*s=NetParse_SX_EatWhite(*s);
	if(!*(*s))return(NULL);

//	strncpy(buf, *s, 5);
//	buf[5]=0;
//	kprint("parse: %s\n", buf);

	NetParse_SX_Token(*s, buf, &ty);
	if((buf[0]=='(') && (ty==TOKEN_SPECIAL))
	{
		*s=NetParse_SX_Token(*s, buf, &ty);
		*s=NetParse_SX_Token(*s, key, &ty);
		if(ty!=TOKEN_SYMBOL)
		{
			kprint("parse error (inv tag).\n");
			return(NULL);
		}

		tmp=kalloc(sizeof(NetParse_Node));
		tmp->next=NULL;
		tmp->key=kstrdup(key);
		tmp->text=NULL;
		tmp->attr=NULL;
		tmp->first=NULL;

		end=NULL;
		while(1)
		{
			NetParse_SX_Token(*s, buf, &ty);

			if(buf[0]==')')
			{
				*s=NetParse_SX_Token(*s, buf, &ty);
				break;
			}

			t=NetParse_SX_ParseExpr(s);
			if(!t)return(t);
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
	*s=NetParse_SX_Token(*s, s2, &ty);

	tmp=kalloc(sizeof(NetParse_Node));
	tmp->next=NULL;
	tmp->key=NULL;
	tmp->text=kstrdup(s2);
	tmp->attr=NULL;
	tmp->first=NULL;

	return(tmp);
}

char *NetParse_SX_PrintExpr(char *s, NetParse_Node *exp)
{
	NetParse_Node *cur;

	if(!exp->key)
	{
		s=kprints(s, "\"%s\"", exp->text);
		return(s);
	}

	s=kprints(s, "(%s", exp->key);

	cur=exp->first;
	while(cur)
	{
		s=kprints(s, " ");
		s=NetParse_SX_PrintExpr(s, cur);
		cur=cur->next;
	}
	s=kprints(s, ")");

	return(s);
}
