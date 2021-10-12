#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

#if 0
static int Con_WriteLongHexStr(char *d, long p)
{
	static char *chrs="0123456789ABCDEF";
	int i;
//	for(i=0; i<8; i++)*d++=chrs[(p>>((7-i)*4))&0xf];
	*d++=0;
	return(0);
}

static int Con_WriteLowerLongHexStr(char *d, long p)
{
	static char *chrs="0123456789abcdef";
	int i;
	for(i=0; i<8; i++)*d++=chrs[(p>>((7-i)*4))&0xf];
	*d++=0;
	return(0);
}

static int Con_WriteLongOctStr(char *d, long p)
{
	static char *chrs="01234567";
	int i;
	for(i=0; i<8; i++)*d++=chrs[(p>>((7-i)*4))&0xf];
	*d++=0;
	return(0);
}
#endif

static int Con_WriteLongStr(char *d, long p, int n)
{
	char stk[16],pos,sign;
	pos=0;
	sign=0;
	if(p<0)
	{
		p=(~p)+1;
		sign=1;
	}
	if(n)
	{
		for(pos=0; pos<n; pos++)
		{
			stk[pos]='0'+(p%10);
			p/=10;
		}
	}else
	{
		if(!p)stk[pos++]='0';
		while(p)
		{
			stk[pos++]='0'+(p%10);
			p/=10;
		}
	}
	if(sign)
	{
		stk[pos]='-';
		pos++;
	}
	while(pos)
	{
		pos--;
		*d++=stk[pos];
	}
	*d=0;
}

static int Con_WriteLongBaseStr(char *d, long p, int n, int b, int c)
{
	static char *chrs1="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char *chrs2="0123456789abcdefghijklmnopqrstuvwxyz";

	char stk[16], pos;
	pos=0;
	if(n)
	{
		for(pos=0; pos<n; pos++)
		{
			if(!c)
				stk[pos]=chrs1[p%b];
				else stk[pos]=chrs2[p%b];
			p/=b;
		}
	}else
	{
		if(!p)stk[pos++]='0';
		while(p)
		{
			if(!c)
				stk[pos++]=chrs1[p%b];
				else stk[pos++]=chrs2[p%b];
			p/=b;
		}
	}
	while(pos)
	{
		pos--;
		*d++=stk[pos];
	}
	*d=0;
}

static int printf_flagp(int c)
{
	if(c=='-')return(1);
	if(c=='+')return(1);
	if(c==' ')return(1);
	if(c=='0')return(1);
	if(c=='#')return(1);
	return(0);
}

int vsprintf(char *d, char *s, va_list p)
{
	char *s2;
	char buf[16];
	int n, l;

	int just, sc, sp, zp, width, prec;

	while(*s)
	{
		if(*s=='%')
		{
			s++;

			just=0;
			sc=0;
			sp=0;
			zp=0;
			width=0;
			prec=0;

			while(printf_flagp(*s))switch(*s)
			{
			case '-':
				just=1;
				s++;
				break;
			case '+':
				sc=1;
				s++;
				break;
			case ' ':
				sp=1;
				s++;
				break;
			case '0':
				zp=1;
				s++;
				break;
			case '#':
				s+=2;
				break;
			}
			if((*s>='0') && (*s<='9'))
			{
				s2=buf;
				while((*s>='0') && (*s<='9'))*s2++=*s++;
				*s2++=0;
				width=atoi(buf);
			}
			if(*s=='.')
			{
				s++;
				s2=buf;
				while((*s>='0') && (*s<='9'))*s2++=*s++;
				*s2++=0;
				prec=atoi(buf);
			}

			if((*s=='h') || (*s=='l') || (*s=='L'))s++;

			switch(*s)
			{
			case '%':
				*d++='%';
				break;
			case 's':
				s2=va_arg(p, char *);
				if(!s2)s2="(null)";
				l=strlen(s2);
				if(prec)l=prec;
				n=0;
				if(width)
				{
					n=width-l;
					if(n<0)n=0;
				}
				//while(*s2)*d++=*s2++;
				if(!just)while(n--)*d++=(zp?'0':' ');
				while(l--)*d++=*s2++;
				if(just)while(n--)*d++=(zp?'0':' ');
				break;
			case 'i':
			case 'd':
				n=va_arg(p, int);
				Con_WriteLongStr(buf, n, width);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'o':
				n=va_arg(p, int);
				Con_WriteLongBaseStr(buf, n, width, 8, 0);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'u':
				n=va_arg(p, int);
				Con_WriteLongBaseStr(buf, n, width, 10, 0);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'X':
				n=va_arg(p, int);
				Con_WriteLongBaseStr(buf, n, width, 16, 0);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'x':
				n=va_arg(p, int);
				Con_WriteLongBaseStr(buf, n, width, 16, 1);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'p':
				n=va_arg(p, int);
				*d++='0';
				*d++='x';
				Con_WriteLongBaseStr(buf, n, 8, 16, 0);
				s2=buf;
				while(*s2)*d++=*s2++;
				break;
			case 'c':
				n=va_arg(p, int);
				*d++=n;
				break;

			default:
				break;
			}
			*d=0;
			s++;
			continue;
		}
//		if(*s=='\n')*d++='\r';
		*d=*s;
		d++;
		s++;
	}
	*d=0;

	return(0);
}

int printf(char *s, ...)
{
	va_list lst;
	static char chl[4096];

	va_start(lst, s);

	vsprintf(chl, s, lst);
	fwrite(chl, 1, strlen(chl), stdout);
	va_end(lst);

	return(0);
}

int vprintf(char *s, va_list lst)
{
	static char chl[4096];

	vsprintf(chl, s, lst);
	fwrite(chl, 1, strlen(chl), stdout);
	return(0);
}


int sprintf(char *d, char *s, ...)
{
	va_list lst;

	va_start(lst, s);
	vsprintf(d, s, lst);
	va_end(lst);

	return(0);
}

int fprintf(FILE *fd, char *s, ...)
{
	va_list lst;
	static char chl[4096];

	va_start(lst, s);
	vsprintf(chl, s, lst);
	fwrite(chl, 1, strlen(chl), fd);
	va_end(lst);

	return(0);
}

int vfprintf(FILE *fd, char *s, va_list lst)
{
	static char chl[4096];

	vsprintf(chl, s, lst);
	fwrite(chl, 1, strlen(chl), fd);
	return(0);
}

int saprintf(char **d, char *s, ...)
{
	va_list lst;
	static char chl[4096];

	va_start(lst, s);

	vsprintf(chl, s, lst);
	va_end(lst);

	*d=strdup(chl);

	return(0);
}

#if 0
int Con_GetString(char *buf, char **t)
{
	char c, *s;
	VFILE *fd;

	fd=Con_GetStdin();

	if(!fd)return(-1);

//	kprint("fd ok\n");

	s=*t;
	while(vfinready(fd))
	{
		c=vfgetc(fd);
		if(c<' ')switch(c)
		{
		case 0x00: /* extended character, ignored for now */
			vfgetc(fd);
			break;
		case 0x08:
			s--;
			if(s<buf)s=buf;
				else Con_Printf("%c", c);
			*s=0;
			break;
		case '\r':
		case '\n':
			c='\n';

			*s++=c;
			*s=0;
			Con_Printf("\r\n");
			return(0);
			break;
		default:
			break;
		}else
		{
			*s++=c;
			Con_Printf("%c", c);
		}
	}
	*t=s;
	return(-1);
}
#endif

static long Con_ReadLongBaseStr(char **str, int b)
{
	char *s;
	long ax;
	int t;

	s=*str;

	ax=0;
	while(*s)
	{
		t=-1;
		if((*s>='0')&&(*s<='9'))t=*s-'0';
		if((*s>='A')&&(*s<='Z'))t=*s-'A'+10;
		if((*s>='a')&&(*s<='z'))t=*s-'A'+10;
		if(t<0)
		{
			*str=s;
			return(ax);
		}
		if(t>=b)
		{
			*str=s;
			return(ax);
		}
		ax=(ax*b)+t;
		s++;
	}
	*str=s;
	return(ax);
}

static int scanf_flagp(int c)
{
	if(c=='*')return(1);
	if(c=='h')return(1);
	if(c=='l')return(1);
	if(c=='q')return(1);
	if(c=='L')return(1);
	return(0);
}

int vsscanf(char *str, char *fmt, va_list lst)
{
	int i, n, w;
	char buf[256];
	char *s, *s2, *is;

	int *dp;
	long *lp;

	is=str;

	i=0;
	while(*str && *fmt)
	{
		if(*fmt<=' ')
		{
			while(*str && (*str<=' '))str++;
			while(*fmt && (*fmt<=' '))fmt++;
			if(!*fmt)break;
			if(!*str)break;
		}

		switch(*fmt)
		{
		case '%':
			fmt++;
			while(scanf_flagp(*fmt))fmt++;

			s=buf;
			while((*fmt>='0') && (*fmt<='9'))*s++=*fmt++;
			*s++=0;
			w=atoi(buf);

			switch(*fmt)
			{
			case '%':
				if(*str!='%')return(i);
				break;
			case 'd':
			case 'i':
				while(*str && (*str<=' '))str++;
				s=buf;
				if(*str=='-')*s++=*str++;
				while((*str>='0') && (*str<='9'))
					*s++=*str++;
				*s++=0;
				dp=va_arg(lst, int *);
				*dp=atoi(buf);
				break;
			case 'D':
				while(*str && (*str<=' '))str++;
				s=buf;
				if(*str=='-')*s++=*str++;
				while((*str>='0') && (*str<='9'))
					*s++=*str++;
				*s++=0;
				lp=va_arg(lst, int *);
				*lp=atoi(buf);
				break;
			case 'o':
				while(*str && (*str<=' '))str++;
				dp=va_arg(lst, int *);
				*dp=Con_ReadLongBaseStr(&str, 8);
				break;
			case 'O':
				while(*str && (*str<=' '))str++;
				lp=va_arg(lst, int *);
				*dp=Con_ReadLongBaseStr(&str, 8);
				break;
			case 'u':
				while(*str && (*str<=' '))str++;
				dp=va_arg(lst, int *);
				*dp=Con_ReadLongBaseStr(&str, 10);
				break;
			case 'x':
				while(*str && (*str<=' '))str++;
				dp=va_arg(lst, int *);
				*dp=Con_ReadLongBaseStr(&str, 16);
				break;
			case 'X':
				while(*str && (*str<=' '))str++;
				lp=va_arg(lst, int *);
				*lp=Con_ReadLongBaseStr(&str, 16);
				break;
			case 's':
				while(*str && (*str<=' '))str++;
				s=va_arg(lst, char *);
				while(*str && (*str>' '))*s++=*str++;
				*s++=0;
				break;
			case 'S':
				while(*str && (*str<=' '))str++;
				s=va_arg(lst, char *);
				if(*str=='"')
				{
					str++;
					while(*str && (*str!='"'))*s++=*str++;
				}else if(*str=='\'')
				{
					str++;
					while(*str && (*str!='\''))*s++=*str++;
				}else
					while(*str && (*str>' '))*s++=*str++;
				*s++=0;
				break;
			case 'c':
				s=va_arg(lst, char *);
				n=w;
				while(n--)*s++=*str++;
				break;
			case '[':
				return(i);
				break;
			case 'p':
				while(*str && (*str<=' '))str++;
				str+=2;
				lp=va_arg(lst, int *);
				*lp=Con_ReadLongBaseStr(&str, 16);
				break;
			case 'n':
				dp=va_arg(lst, int *);
				*dp=str-is;
				break;

			case '\x00':
				return(-1);
				break;

			default:
				while(*str && (*str<=' '))str++;
				s=buf;
				if(*str=='-')*s++=*str++;
				while((*str>='0') && (*str<='9'))
					*s++=*str++;
				*s++=0;
				dp=va_arg(lst, int *);
				*dp=atoi(buf);
				break;
			}
			if(*fmt)fmt++;

			break;
		default:
			if(*str!=*fmt)return(i);
			str++;
			fmt++;
			break;
		}
	}
	return(i);
}

int sscanf(char *d, char *s, ...)
{
	va_list lst;
	int i;

	va_start(lst, s);
	i=vsscanf(d, s, lst);
	va_end(lst);

	return(i);
}

int fscanf(FILE *fd, char *s, ...)
{
	va_list lst;
	int i;
	static char buf[1024];

	fgets(buf, 1023, fd);

	va_start(lst, s);
	i=vsscanf(buf, s, lst);
	va_end(lst);

	return(i);
}
