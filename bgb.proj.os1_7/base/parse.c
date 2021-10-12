#include <general.h>

char *Parse_EatWhite(char *s)
{
	int i;

	if(!s)return(s);
	i=0;
	while(*s && *s<=' ')
	{
		i=1;
		s++;
	}
	if(*s == '/' && s[1]=='/')while(*s && *s!='\n')
	{
		i=1;
		s++;
	}
	if(*s == '/' && s[1]=='*')while(*s && !(*s=='*' && s[1]=='/'))
	{
		i=1;
		s++;
	}
	if(i)s=Parse_EatWhite(s);

	if(!s)return(NULL);
	if(!*s)return(NULL);
	return(s);
}

char *Parse_Token(char *s, char *b)
{
	char *ob;
	ob=b;
	*b=0;

	s=Parse_EatWhite(s);
	if(!s)return(s);
	if(*s=='"') /* quoted string */
	{
		s++;
		while(*s && *s!='"')
			*b++=*s++;
		*b++=0;
		s++;
	}else if(*s=='[') /* notational, keep '[' and ']' */
	{
		while(*s && *s!=']')
			*b++=*s++;

		*b++=*s++;
		*b++=0;
		s++;
	}else if(isalpha(*s) || *s=='_')
	{	/* alphanumeric string that can contain '_' */
		while(isalnum(*s) || *s=='_')
			*b++=*s++;
		*b++=0;
	}else if(isdigit(*s) || (*s=='-'))
	{	/* numeric string */
		while(isdigit(*s) || *s=='.' || *s=='e' || *s=='E' || *s=='x' || *s=='-')
			*b++=*s++;
		*b++=0;
	}else if(*s>' ')
	{	/* single character */
		*b++=*s++;
		*b++=0;
	} /* otherwise is whitespace */
	return(s);

//	if(*s=='<') /* vector, keep '<' and '>' */
//	{
//		while(*s && *s!='>')
//			*b++=*s++;
//
//		*b++=*s++;
//		*b++=0;
//		s++;
//	}else

}

char *Parse_TokenS(char *s, char *b)
{
	char *ob;
	ob=b;
	*b=0;

	s=Parse_EatWhite(s);
	if(!s)return(s);
	if(*s=='"') /* quoted string */
	{
		s++;
		while(*s && *s!='"')
			*b++=*s++;
		*b++=0;
		s++;
	}else
	{	/* alphanumeric string that can contain '_' */
		while(*s && *s>' ')
			*b++=*s++;
		*b++=0;
	}
	return(s);
}

int Parse_StringIndex(char *s, char *l[])
{
	int i;
	for(i=0; l[i]; i++)if(!strcmp(s, l[i]))return(i+1);
	return(0);
}
