#include <scmcc.h>

char *ScmParse_EatWhite(char *s)
{
	int i, r;

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
	if(*s == '#' && s[1]=='!')
	{
		i=1;
		r=1;
		s+=2;
		while(*s && r)
		{
			if(*s=='!' && s[1]=='#')
			{
				r--;
				s+=2;
				continue;
			}
			if(*s=='#' && s[1]=='!')
			{
				r++;
				s+=2;
				continue;
			}
			s++;
		}
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
#if 0
		i=1;
		while(*s && !(*s=='|' && s[1]=='#'))
		{
			s++;
		}
		if(s[0]=='|' && s[1]=='#')s+=2;
#endif
	}
	if(*s == '#' && s[1]==';')
	{
		i=1;
		s+=2;
		ScmParse_Item(&s, 0);
	}

	if(i)s=ScmParse_EatWhite(s);

	return(s);
}

int ScmParse_SpecialP(char *s)
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

char *ScmParse_Token(char *s, char *b, int *t)
{
	char *ob;

	if(!b)b=sa_ralloc(256);
	ob=b;
	*b=0;

	if(t)*t=0;

	s=ScmParse_EatWhite(s);
	if(!*s)return(s);

	if(ScmParse_SpecialP(s))
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
				case '"':
					*b++='"';
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

		while(*s && *s>' ' && !ScmParse_SpecialP(s))
			*b++=*s++;
		*b++=0;
	}
	return(s);
}

elem ScmParse_List(char **s, int ind)
{
	elem t, l;
	char buf[256];
	int ty;

	l=MISC_EOL;

	while(1)
	{
		if(!**s)return(MISC_UNDEFINED);
		ScmParse_Token(*s, buf, &ty);

		if(ty!=OBJECT_STRING)
		{
			if(buf[0]==')')break;
			if(buf[0]==']')break;
			if(buf[0]=='}')break;

			if((buf[0]=='.') && (buf[1]==0))
			{
//				sa_print("append.\n");
				*s=ScmParse_Token(*s, buf, &ty);
				t=ScmParse_Item(s, ind);
				*s=ScmParse_Token(*s, buf, &ty);
				l=TyFcn_NReverse(l);
				TyFcn_NAppend(l, t);
				return(l);
			}
		}

		t=ScmParse_Item(s, ind);
		l=TyFcn_Cons(t, l);
		if(l>1<<31)sa_print("cons returns large value.\n");
	}
//	printf("LARGE1 %lX.\n", l);
	*s=ScmParse_Token(*s, buf, &ty);
//	printf("LARGE2 %lX.\n", l);
	l=TyFcn_NReverse(l);
	return(l);
}

elem ScmParse_Vector(char **s, int ind)
{
	elem lst, t;
	lst=ScmParse_List(s, ind);
	t=TyFcn_ListToVector(lst);
	return(t);
}

elem ScmParse_Symbol(char *s)
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

double ScmParse_Float(char *s)
{
	double x, y;
	int sg;

	sg=1;
	x=0;
	y=0;
	while(*s)
	{
		if(*s=='-')
		{
			sg*=-1;
			s++;
		}
		if(*s=='.')
		{
			y=1;
			s++;
		}

		if(*s>='0' && *s<='9')
		{
			x=(x*10)+(*s-'0');
			y=y*10;
			s++;
		}
	}
	if(y==0)y=1;
	x=(x*sg)/y;
	return(x);
}

elem ScmParse_Item(char **s, int ind)
{
	char buf[256], buf2[16];
	int ty, i;
	elem t;

	t=MISC_UNDEFINED;

	*s=ScmParse_EatWhite(*s);
	if(!**s)return(MISC_UNDEFINED);

	*s=ScmParse_Token(*s, buf, &ty);
	switch(ty)
	{
	case OBJECT_STRING:
		t=TyFcn_String(buf);
		break;
	case OBJECT_SYMBOL:
		if(isdigit(buf[0]) || ((buf[0]=='-') && isdigit(buf[1])))
		{
//			printf("parse num - from %s\n", buf);
			t=FLONUM(ScmParse_Float(buf));
		}else t=ScmParse_Symbol(buf);
		break;
	case TYPE_SPECIAL:
		switch(buf[0])
		{
		case '(':
			t=ScmParse_List(s, ind);
			break;
		case '[':
			t=ScmParse_List(s, ind);
			t=CONS(SYM("list"), t);
			break;
		case '#':
			switch(**s)
			{
			case 't':
				*s=ScmParse_Token(*s, buf, &ty);
				t=MISC_TRUE;
				break;
			case 'f':
				*s=ScmParse_Token(*s, buf, &ty);
				t=MISC_FALSE;
				break;
			case 'z':
				*s=ScmParse_Token(*s, buf, &ty);
				t=MISC_NULL;
				break;

			case 'o':
				*s=ScmParse_Token(*s, buf, &ty);
				buf[0]='0';
				t=FIXNUM(sa_atoi(buf));
				break;
			case '(':
//				*s=ScmParse_Token(*s, buf, &ty); /* ( */
//				t=ScmParse_Vector(s, ind);

				t=ScmParse_Item(s, ind);
				t=TyFcn_ListToVector(t);
				break;
			case '[':
				*s=*s+1;
				t=ScmParse_List(s, ind);
				t=CONS(SYM("vector"), t);
				break;
			case '\\':
				//*s=ScmParse_Token(*s, buf, &ty); /* slash */
				*s=*s+1;
				i=**s;
				buf[1]=0;
				if(isalpha(i))*s=ScmParse_Token(*s, buf, &ty); /* char name */
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
					if(buf[0]=='x')
					{
//						buf[0]='0';
						strcpy(buf2, "0x");
						strcat(buf2, buf+1);
						t=ELEM_FROMCHAR(sa_atoi(buf2));
					}
					if(t==MISC_NULL)
					{
						sa_print("parse: unknown character nmonic '%s'\n", buf);
						t=ELEM_FROMCHAR(' ');
					}
				}else t=ELEM_FROMCHAR(i);
				break;
			case '"':
				*s=ScmParse_Token(*s, buf, &ty);
				t=SYM(buf);
				break;
			case 'x':
				*s=*s+2;
				*s=ScmParse_Token(*s, buf, &ty);
				t=ScmParse_Item(s, ind);
				t=TypeX_UnFlatten(SYM(buf), t);
				*s=ScmParse_Token(*s, buf, &ty);
				break;
			default:
				sa_error("parse: unknown special form '#%c'.\n", **s);
				break;
			}
			break;
		case '\'':
			t=ScmParse_Item(s, ind);
			t=TyFcn_Cons(t, MISC_EOL);
			t=TyFcn_Cons(TyFcn_Symbol("quote"), t);
			break;
		case '`':
			t=ScmParse_Item(s, ind);
			t=TyFcn_Cons(t, MISC_EOL);
			t=TyFcn_Cons(TyFcn_Symbol("quasiquote"), t);
			break;
		case ',':
			if(**s=='@')
			{
				*s=*s+1;
				t=ScmParse_Item(s, ind);
				t=TyFcn_Cons(t, MISC_EOL);
				t=TyFcn_Cons(TyFcn_Symbol("unquote-splicing"), t);
			}else if(**s==',')
			{
				*s=*s+1;
				t=ScmParse_Item(s, ind);
				t=CONS(t, MISC_EOL);
				t=CONS(TyFcn_Symbol("doublemark"), t);
			}else
			{
				t=ScmParse_Item(s, ind);
				t=TyFcn_Cons(t, MISC_EOL);
				t=TyFcn_Cons(TyFcn_Symbol("unquote"), t);
			}
			break;
		default:
			sa_error("parse: unknown special '%c'.\n", buf[0]);
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

elem ScmParse_Line(char **s, int sk)
{
	elem t;
	if(sk==1)
	{
		t=ScmParseSK_Line(s);
		if(ELEM_CONSP(t))
			if(CAR(t)==SYM("^"))return(CADR(t));
		return(t);
	}else if(sk==2)
	{
		t=ScmParseLB2_Line(s);
		if(ELEM_CONSP(t))
			if(CAR(t)==SYM("^"))return(CADR(t));
		return(t);
	}
	return(ScmParse_Item(s, 0));
}
