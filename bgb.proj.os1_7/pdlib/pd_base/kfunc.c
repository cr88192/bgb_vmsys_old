#include <pdlib.h>

#include <stdarg.h>

void *kfunc_rotbuf;
int kfunc_rotpos;

int kprint(char *s, ...)
{
	va_list lst;

	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);

	return(0);
}

void *kalloc(int sz)
{
	return(MM2_PAlloc(sz));
}

int kfree(void *p)
{
	MM2_PFree(p);
	return(0);
}

int kincref(void *p)
{
	MM2_PInc(p);
	return(0);
}

int kdecref(void *p)
{
	MM2_PDec(p);
	return(0);
}

void *kralloc(int size)
{
	void *t;
	if(!kfunc_rotbuf)
	{
		kfunc_rotbuf=kalloc(262144);
		kfunc_rotpos=0;
	}
	kfunc_rotpos=(kfunc_rotpos+7)&~7;
	if((kfunc_rotpos+size)>262144)kfunc_rotpos=0;
	t=kfunc_rotbuf+kfunc_rotpos;
	kfunc_rotpos+=size;
	return(t);
}

char *kstrdup(char *s)
{
	char *t;
	t=kalloc(strlen(s)+1);
	strcpy(t, s);
	return(t);
}

char *krstrdup(char *s)
{
	char *t;
	t=kralloc(strlen(s)+1);
	strcpy(t, s);
	return(t);
}

char *kvprints(char *d, char *s, va_list lst)
{
	vsprintf(d, s, lst);

	return(d+strlen(d));
}

char *kprints(char *d, char *s, ...)
{
	va_list lst;

	va_start(lst, s);
	vsprintf(d, s, lst);
	va_end(lst);

	return(d+strlen(d));
}

int kprintvf(VFILE *fd, char *s, ...)
{
	va_list lst;
	char  *d;

	d=kralloc(1024);

	va_start(lst, s);
	vsprintf(d, s, lst);
	va_end(lst);

	vfwrite(d, 1, strlen(d), fd);

	return(strlen(d));
}

void *kmemdup(void *p, int sz)
{
	void *t;

	t=kalloc(sz);
	memcpy(t, p, sz);
	return(t);
}

char *ksgets(char *buf, int l, char *s)
{
	char *t, *is;

	is=s;
	t=buf;
	while(*s && l && (*s!='\n') && (*s!='\r'))
	{
		if(*s=='\x08')
		{
			s++;
			if(t>buf)
			{
				t--;
				l++;
			}
			continue;
		}
		*t++=*s++;
		l--;
	}

	if(!l || !*s)
	{
		*buf=0;
		return(is);
	}

	if(*s=='\r')s++;
	if(*s=='\n')s++;
	*t++=0;

	return(s);
}
