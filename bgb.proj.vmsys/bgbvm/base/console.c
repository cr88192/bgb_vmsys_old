#include <general.h>

//#include <stdarg.h>

int debuglevel=99;
int usestdout=1;

byte promptbuf[80], promptpos;
int con_down;

//ConsoleCommand *con_cmdroot;

VFILE *kstdin=NULL, *kstdout=NULL, *con_stream=NULL;

int con_stdinkey, con_stdoutkey;

int KCon_Init()
{
	usestdout=1;
//	con_cmdroot=NULL;
	kstdin=NULL;
	kstdout=NULL;
	con_stream=NULL;

	con_stdinkey=kthread_newkey();
	con_stdoutkey=kthread_newkey();

//	Cmd_Init();

	KCon_Printf("console initialized.\n");
}

int KCon_Reset()
{
	var *v;
	VFILE *fd;

	usestdout=1;
	v=Var_Lookup("silent");
	if(v)if(v->dvalue!=0)usestdout=0;
	v=Var_Lookup("outlog");
	if(v)
	{
//		if(!outlog)outlog=fopen(v->value, "wt");
//		if(!outlog)printf("can't open log %s\n", v->value);
	}
	if(usestdout && (!KCon_GetStdin() || !KCon_GetStdout()))
	{
		if(!con_stream)con_stream=Driver_OpenStream("console");
//		fd=vffopen("/devices/console", "r+t");

		kstdin=con_stream;
		kstdout=con_stream;

		kthread_setlocal(con_stdinkey, con_stream);
		kthread_setlocal(con_stdoutkey, con_stream);
	}
/*
else
	{
		if(kstdin)vfclose(kstdin);
		if(kstdout)vfclose(kstdout);
		kstdin=NULL;
		kstdout=NULL;

		kthread_setlocal(con_stdinkey, kstdin);
		kthread_setlocal(con_stdoutkey, kstdout);
	}
*/
}

VFILE *KCon_GetStdin()
{
	return(kthread_getlocal(con_stdinkey));
}

int KCon_SetStdin(VFILE *fd)
{
	return(kthread_setlocal(con_stdinkey, fd));
}

VFILE *KCon_GetStdout()
{
	return(kthread_getlocal(con_stdoutkey));
}

int KCon_SetStdout(VFILE *fd)
{
	return(kthread_setlocal(con_stdoutkey, fd));
}

int Render_StringToConbuf(char *s);

int KCon_WriteLongHexStr(char *d, long p)
{
	static char *chrs="0123456789ABCDEF";
	int i;
	for(i=0; i<8; i++)*d++=chrs[(p>>((7-i)*4))&0xf];
	*d++=0;
	return(0);
}

int KCon_WriteLongStr(char *d, long p)
{
	char stk[11],pos,sign;
	pos=0;
	sign=0;
	if(p<0)
	{
		p=(~p)+1;
		sign=1;
	}
	if(!p)
	{
		stk[pos]='0';
		pos++;
	}
	while(p)
	{
		stk[pos]='0'+(p%10);
		pos++;
		p/=10;
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

int KCon_WriteLongNStr(char *d, long p,int n)
{
	char stk[11],pos,sign;
	pos=0;
	sign=0;
	if(p<0)
	{
		p=(~p)+1;
		sign=1;
	}
	for(pos=0;pos<n;pos++)
	{
		stk[pos]='0'+(p%10);
		p/=10;
	}
	while(pos)
	{
		pos--;
		*d++=stk[pos];
	}
	*d=0;
}

/* FIXME: make these not dependent on x86 stack organization */

int KCon_VSPrintf(char *d, char *s, void **p)
{
	char *s2;
	char buf[16];
	int n;

	p++;
	while(*s)
	{
		if(*s=='%')
		{
			s++;
			switch(*s)
			{
			case 's':
				s2=*p;
				p++;
				while(*s2)*d++=*s2++;
				*d=0;
				break;
			case 'd':
				n=(int)*p;
				p++;
				KCon_WriteLongStr(buf, n);
				s2=buf;
				while(*s2)*d++=*s2++;
				*d=0;
				break;
			case 'X':
				n=(int)*p;
				p++;
				KCon_WriteLongHexStr(buf, n);
				s2=buf;
				while(*s2)*d++=*s2++;
				*d=0;
				break;
			case 'c':
				n=(int)*p;
				p++;
				*d++=n;
				*d=0;
				break;

			default:
				break;
			}
			s++;
			continue;
		}
		if(*s=='\n')*d++='\r';
		*d=*s;
		d++;
		s++;
	}
	*d=0;
}

//int Rendercore_ConString(char *s);

int KCon_Printf(char *s, ...)
{
	void **lst;
	static char chl[4096];
	VFILE *fd;

//	va_start(lst, s);

	fd=KCon_GetStdout();

	lst=(void **)&s;
	KCon_VSPrintf(chl, s, lst);
//	vsprintf(chl, s, lst);

	if(fd)vfwrite(chl, 1, strlen(chl), fd);
		else Text_WriteString(s);
//	Rendercore_ConString(chl);

//	va_end(lst);
}

int KCon_VPrintf(char *s, void **lst)
{
	static char chl[4096];
	VFILE *fd;

	fd=KCon_GetStdout();

	KCon_VSPrintf(chl, s, lst);
	if(fd)vfwrite(chl, 1, strlen(chl), fd);
		else Text_WriteString(chl);
//	Rendercore_ConString(chl);
}

#if 0
int KCon_DPrintf(int level, char *s, ...)
{
//	va_list lst;

//	if(level>debuglevel)return(0);

//	va_start(lst, s);

//	if(usestdout)vprintf(s, lst);
//	if(outlog)vfprintf(outlog, s, lst);

//	va_end(lst);
}
#endif

int KCon_Getch()
{
	VFILE *fd;

	fd=KCon_GetStdin();

	if(!vfinready(fd))return(-1);
	return(vfgetc(fd));
}

int KCon_GetString(char *buf, char **t)
{
	char c, *s;
	VFILE *fd;

	fd=KCon_GetStdin();

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
				else KCon_Printf("%c", c);
			*s=0;
			break;
		case '\r':
		case '\n':
			c='\n';

			*s++=c;
			*s=0;
			KCon_Printf("\r\n");
			return(0);
			break;
		default:
			break;
		}else
		{
			*s++=c;
			KCon_Printf("%c", c);
		}
	}
	*t=s;
	return(-1);
}
