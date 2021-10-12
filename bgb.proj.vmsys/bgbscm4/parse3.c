#include <scmcc.h>

char *ScmParseLB2_EatWhite(char *s)
{
	int i, cl;

	i=0;
	while(*s && (*s<=' ') && (*s!='\n'))
	{
		i=1;
		s++;
	}
	if(*s=='\n')return(s);

	if((s[0] == '/') && (s[1] == '/'))while(*s && (*s!='\n'))
	{
		i=1;
		s++;
	}
	if(*s=='\n')return(s);

	if((*s == '/') && (s[1]=='*'))
	{
		cl=1;
		while(*s && cl)
		{
			i=1;
			s++;
			if((*s == '/') && (s[1]=='*'))cl++;
			if((*s == '*') && (s[1]=='/'))cl--;
		}
		if((*s=='*') && (s[1]=='/'))
		{
			s++;
			s++;
		}
//		printf("%p\n", s);
	}

	if(*s == '\\')
	{
		while(*s && *s!='\n')
		{
			i=1;
			s++;
		}
		if(*s=='\n')s++;
	}
//	printf("%p\n", s);
	if(i)s=ScmParseLB2_EatWhite(s);
//	printf("%p\n\n", s);

	return(s);
}

int ScmParseLB2_SpecialP(char *s)
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
//	case '.':
//		return(1);
//		break;
	case '|':
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

int ScmParseLB2_InfixP(char *s)
{
	switch(*s)
	{
	case '!':
		return(1);
		break;
	case '$':
		return(1);
		break;
	case '%':
		return(1);
		break;
	case '&':
		return(1);
		break;
	case '*':
		return(1);
		break;
	case '+':
		return(1);
		break;
	case '-':
		return(1);
		break;
	case '.':
		return(1);
		break;
	case '/':
		return(1);
		break;
	case ':':
		return(1);
		break;
	case '<':
		return(1);
		break;
	case '=':
		return(1);
		break;
	case '>':
		return(1);
		break;
	case '?':
		return(1);
		break;
	case '~':
		return(1);
		break;
	default:
		return(0);
		break;
	}
	return(0);
}

char *ScmParseLB2_Token(char *s, char *b, int *t)
{
	char *ob, buf[8];
	ob=b;
	*b=0;

	if(t)*t=0;

	s=ScmParseLB2_EatWhite(s);
	if(!*s)return(s);
	if(*s=='\n')return(s);

	if(ScmParseLB2_SpecialP(s))
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
				case 'x':
					buf[0]='0';
					buf[1]='x';
					buf[2]=s[1];
					buf[3]=s[2];
					buf[4]=0;
					s++;
					s++;

					*b++=sa_atoi(buf);
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
	}else if(*s>' ')
	{	/* alphanumeric string that can contain '_' */
		if(t)*t=OBJECT_SYMBOL;

		while(*s && *s>' ' && !ScmParseLB2_SpecialP(s)) // || (*s=='.'))
			*b++=*s++;
		*b++=0;
	}

	return(s);
}

int ScmParseLB2_Indent(char *s)
{
	int c;
	c=0;
	while(*s && *s<=' ' && *s!='\n')
	{
		if(*s=='\t')c+=7;
//		Con_Printf("%s", s);
		s++;
		c++;
	}
	if(*s=='\n')return(-1);
	return(c);
}

char *ScmParseLB2_FindLine(char *s)
{
	char *lp;
	lp=s;
	while(*s)
	{
		while(*s && *s<=' ' && *s!='\n')s++;
		if(!*s)continue;
		if(*s=='\n')
		{
			s++;
			lp=s;
			continue;
		}
		if(s[0] == '/' && s[1] == '/')
		{
			while(*s && *s!='\n')s++;
			if(!*s)continue;
			s++;
			lp=s;
			continue;
		}
		if(*s == '/' && s[1]=='*')
		{
			while(*s && !(*s=='*' && s[1]=='/'))s++;
			if(*s=='*' && s[1]=='/')s+=2;
			continue;
		}
		break;
	}
	if(!*s)return(NULL);
	return(lp);
}

elem ScmParseLB2_Block(char **s)
{
	elem x, t;

	x=MISC_EOL;
	while(1)
	{
		*s=ScmParseLB2_FindLine(*s);
		*s=ScmParseLB2_EatWhite(*s);
		if(!*s)break;
		if(**s=='}')
		{
			*s=*s+1;
			break;
		}
		t=ScmParseLB2_Line(s);
		if(ELEM_CONSP(t) && (CAR(t)==SYM("^")))
		{
			t=TyFcn_NReverse(CDR(t));
			x=TyFcn_NAppend(t, x);
		}else x=CONS(t, x);
	}

	x=TyFcn_NReverse(x);
//	x=CONS(SYM("begin"), x);

	return(x);
}

elem ScmParseLB2_Line(char **s)
{
	elem t, l;
	char buf[256];
	int ty;
	char *lp;

	*s=ScmParseLB2_FindLine(*s);
	*s=ScmParseLB2_EatWhite(*s);
	if(!*s)return(MISC_UNDEFINED);

	l=MISC_EOL;

	while(1)
	{
		if(!**s)return(MISC_UNDEFINED);
		if(**s=='\n')break;
		ScmParseLB2_Token(*s, buf, &ty);

		if((buf[0]==')') || (buf[0]==']') || (buf[0]=='}'))
		{
			l=TyFcn_NReverse(l);
			return(l);
		}

		if((buf[0]=='.') && (buf[1]==0) && (ty!=OBJECT_STRING))
		{
			*s=ScmParseLB2_Token(*s, buf, &ty);
			t=ScmParseLB2_Item(s, 0);
			l=TyFcn_NReverse(l);
			TyFcn_NAppend(l, t);
			return(l);
		}

#if 1
		if(ScmParseLB2_InfixP(buf) && strcmp(buf, "...") && !((buf[0]=='-') && buf[1])
			&& !((buf[0]=='.') && ScmParseLB2_InfixP(&buf[1])) && (l!=MISC_EOL) && (ty==OBJECT_SYMBOL))
		{
			t=ScmParseLB2_Item(s, 0);
			t=CONS(t, CDR(l));
			TyFcn_SetCdr(l, t);
		}else
		{
			t=ScmParseLB2_Item(s, 0);
			l=CONS(t, l);
		}
#endif
	}
	lp=*s;
	while(1)
	{
		lp=ScmParseLB2_FindLine(lp);
		if(!lp)break;
		lp=ScmParseLB2_EatWhite(lp);
		if(!lp)break;
		if(*lp=='{')
		{
			lp++;
			t=ScmParseLB2_Block(&lp);
			t=CONS(SYM("begin"), t);
			l=CONS(t, l);
			continue;
		}else if((lp[0]=='#') && (lp[1]=='{'))
		{
			lp+=2;
			t=ScmParseLB2_Block(&lp);
			t=TyFcn_NReverse(t);
			l=TyFcn_NAppend(t, l);
			continue;
		}else if((lp[0]=='#') && (lp[1]=='^'))
		{
			lp+=2;
			t=ScmParseLB2_Line(&lp);
			t=TyFcn_NReverse(t);
			l=TyFcn_NAppend(t, l);
			continue;
		}
		*s=lp;
		break;
	}
	*s=lp;

	l=TyFcn_NReverse(l);
	return(l);
}

elem ScmParseLB2_List(char **s, int ind)
{
	elem t, l;
	char buf[256];
	int ty, ind2;
	char *lp;

	l=MISC_EOL;

	while(1)
	{
		if(!**s)return(MISC_UNDEFINED);
		if(**s=='\n')break;
		ScmParseLB2_Token(*s, buf, &ty);

		if((buf[0]==')') || (buf[0]==']') || (buf[0]=='}'))
		{
			*s=ScmParseLB2_Token(*s, buf, &ty);
			l=TyFcn_NReverse(l);
			return(l);
		}

		if((buf[0]=='.') && (buf[1]==0))
		{
//			sa_print("append.\n");
			*s=ScmParseLB2_Token(*s, buf, &ty);
			t=ScmParseLB2_Item(s, ind);
			*s=ScmParseLB2_Token(*s, buf, &ty);
			l=TyFcn_NReverse(l);
			TyFcn_NAppend(l, t);
			return(l);
		}

//		t=ScmParseLB2_Item(s, ind);
//		l=CONS(t, l);
//		if(l>1<<31)sa_print("cons returns large value.\n");

#if 1
		if(ScmParseLB2_InfixP(buf) && strcmp(buf, "...") && !((buf[0]=='-') && buf[1])
			&& !((buf[0]=='.') && ScmParseLB2_InfixP(&buf[1])) && (l!=MISC_EOL) && (ty==OBJECT_SYMBOL))
		{
			t=ScmParseLB2_Item(s, ind);
			t=CONS(t, CDR(l));
			TyFcn_SetCdr(l, t);
		}else
		{
			t=ScmParseLB2_Item(s, ind);
			l=CONS(t, l);
		}
#endif
	}

	lp=*s;
	while(1)
	{
		lp=ScmParseLB2_FindLine(lp);
		if(!lp)break;
		lp=ScmParseLB2_EatWhite(lp);
		if(!lp)break;
		if(*lp=='{')
		{
			lp++;
			t=ScmParseLB2_Block(&lp);
			t=CONS(SYM("begin"), t);
			l=CONS(t, l);
			continue;
		}else if((lp[0]=='#') && (lp[1]=='{'))
		{
			lp+=2;
			t=ScmParseLB2_Block(&lp);
			t=TyFcn_NReverse(t);
			l=TyFcn_NAppend(t, l);
			continue;
		}else if((lp[0]=='#') && (lp[1]=='^'))
		{
			lp+=2;
			t=ScmParseLB2_Line(&lp);
			t=TyFcn_NReverse(t);
			l=TyFcn_NAppend(t, l);
			continue;
		}
		*s=lp;
		break;
	}
	*s=lp;

	*s=ScmParseLB2_Token(*s, buf, &ty); /* assumes closing parenthesis is present... */

	l=TyFcn_NReverse(l);
	return(l);
}

elem ScmParseLB2_Symbol(char *s)
{
	char buf[64], *bp;
	elem t;

	if(!strcmp(s, ".."))return(SYM(s));
	if(!strcmp(s, "..."))return(SYM(s));

	if(*s=='.')s++;

	t=MISC_NULL;
	bp=buf;
	while(*s)
	{
		if(*s=='.')
		{
			if(t==MISC_NULL)t=SYM(buf);
				else t=CONS(t,CONS(CONS(SYM("quote"), CONS(SYM(buf), MISC_EOL)), MISC_EOL));
			bp=buf;
			*bp=0;
			s++;
			continue;
		}
		*bp++=*s++;
		*bp=0;
	}
	if(t==MISC_NULL)t=SYM(buf);
		else t=CONS(t,CONS(CONS(SYM("quote"), CONS(SYM(buf), MISC_EOL)), MISC_EOL));

	return(t);
}

elem ScmParseLB2_Item(char **s, int ind)
{
	char buf[256], *s2;
	int ty, i, f;
	elem t;

	t=MISC_UNDEFINED;

	*s=ScmParseLB2_EatWhite(*s);
	if(!**s)return(MISC_UNDEFINED);
	while((**s=='\r') || (**s=='\n'))
	{
		*s=*s+1; //gcc bug
		*s=ScmParseLB2_EatWhite(*s);
	}

	*s=ScmParseLB2_Token(*s, buf, &ty);
	switch(ty)
	{
	case OBJECT_STRING:
		t=TyFcn_String(buf);
		break;
	case OBJECT_SYMBOL:
		if(isdigit(buf[0]) || ((buf[0]=='-') && isdigit(buf[1])))
		{
			s2=buf;
			f=0;
			while(*s2)
			{
				if(*s2=='.')f++;
				if(*s2=='e')f++;
				s2++;
			}
			if(!f)t=ELEM_FROMFIXNUM(sa_atoi(buf));
				else t=TyMath_FromDouble(atof(buf));
		}else t=ScmParseLB2_Symbol(buf);
		break;
	case TYPE_SPECIAL:
		switch(buf[0])
		{
		case '(':
			t=ScmParseLB2_List(s, ind);
			break;
		case '[':
			t=ScmParseLB2_List(s, ind);
			t=CONS(SYM("list"), t);
			break;
		case '#':
			switch(**s)
			{
			case 't':
				*s=ScmParseLB2_Token(*s, buf, &ty);
				t=MISC_TRUE;
				break;
			case 'f':
				*s=ScmParseLB2_Token(*s, buf, &ty);
				t=MISC_FALSE;
				break;
			case 'z':
				*s=ScmParseLB2_Token(*s, buf, &ty);
				t=MISC_NULL;
				break;
			case '(':
				t=ScmParseLB2_Item(s, ind);
				t=TyFcn_ListToVector(t);
				break;
			case '[':
				*s=*s+1;
				t=ScmParseLB2_List(s, ind);
				t=CONS(SYM("vector"), t);
				break;
			case '\\':
				//*s=ScmParseLB2_Token(*s, buf, &ty); /* slash */
				*s=*s+1;
				i=**s;
				buf[1]=0;
				if(isalpha(i))*s=ScmParseLB2_Token(*s, buf, &ty); /* char name */
					else *s=*s+1;
//				sa_print("ch: %d\n", i);
				if(buf[1])
				{
//					sa_print("ch: %s\n", buf);
//					t=ELEM_FROMCHAR(i);
					t=MISC_NULL;
					if(!sa_stricmp(buf, "space"))t=ELEM_FROMCHAR(' ');
					if(!sa_stricmp(buf, "backspace"))t=ELEM_FROMCHAR('\x08');
					if(!sa_stricmp(buf, "tab"))t=ELEM_FROMCHAR('\t');
					if(!sa_stricmp(buf, "newline"))t=ELEM_FROMCHAR('\n');
					if(!sa_stricmp(buf, "return"))t=ELEM_FROMCHAR('\r');
					if(buf[1]=='x')
					{
						buf[0]='0';
						t=ELEM_FROMCHAR(sa_atoi(buf));
					}
					if(t==MISC_NULL)
					{
						sa_print("parse: unknown character nmonic '%s'\n", buf);
						t=ELEM_FROMCHAR(' ');
					}
				}else t=ELEM_FROMCHAR(i);
				break;
			}
			break;
		case '\'':
			t=ScmParseLB2_Item(s, ind);
			t=CONS(t, MISC_EOL);
			t=CONS(TyFcn_Symbol("quote"), t);
			break;
		case '`':
			if(**s=='`')
			{
				*s=*s+1;
				t=ScmParseLB2_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("doubleqq"), t);
				break;
			}
			if(**s=='[')
			{
				t=ScmParseLB2_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("adqq"), t);
				break;
			}
			t=ScmParseLB2_Item(s, ind);
			t=CONS(t, MISC_EOL);
			t=CONS(TyFcn_Symbol("quasiquote"), t);
			break;
		case ',':
			if(**s=='@')
			{
				*s=*s+1;
				t=ScmParseLB2_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("unquote-splicing"), t);
			}else if(**s==',')
			{
				*s=*s+1;
				t=ScmParseLB2_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("doublemark"), t);
			}else
			{
				t=ScmParseLB2_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("unquote"), t);
			}
			break;
		default:
			sa_error("parse: unknown special %c.\n", buf[0]);
			break;
		}
		break;
	default:
		sa_error("parse wrong type %d.\n", ty);
		return(MISC_NULL);
		break;
	}
	return(t);
}
