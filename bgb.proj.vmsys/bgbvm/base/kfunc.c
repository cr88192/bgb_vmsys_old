#include <general.h>

void *kfunc_rotbuf;
int kfunc_rotpos;

int kprint(char *s, ...)
{
//	if(!con_stream)Text_WriteString(s); /* hack to get console messages before devices come up */

	KCon_VPrintf(s, (void **)&s);
	return(0);
}

int kvprint(char *s, kva_list lst)
{
	if(!kstdout)Text_WriteString(s); /* hack to get console messages before devices come up */

	KCon_VPrintf(s, lst);
	return(0);
}

int panic(char *s)
{
	kprint("panic: ");
	kprint(s);
	while(1);
}

void *kalloc(int size)
{
	elem t, *s;

	t=MMGC3_Object(size+8);
	s=(elem *)(t&(~7));
	s[0]=OBJECT_CDATA;
	s[1]=ELEM_FROMFIXNUM(size);

	return(s+2);
//	MMGC_Collect();
//	return(MM2_PAlloc(size));
}

int kfree(void *ptr)
{
//	return(MM2_PFree(ptr));
	return(MMGC3_FreeElem((elem)ptr));
}

void *kgalloc(int size)
{
	elem t, *s;

	t=MMGC3_Object(size+8);
	s=(elem *)(t&(~7));
	s[0]=OBJECT_CDATA;
	s[1]=ELEM_FROMFIXNUM(size);

	return(s+2);

//	return(MMGC_PAlloc(size));
}

void *kpgalloc(int size)
{
//	return(Store_Object((size+7)>>3));
}

void *kpgcons()
{
//	return(Store_Cons());
}

#if 0
int kalloclen(void *p)
{
	elem t;
	elem *s;


	t=MMGC3_GetReference(p);
	if(!ELEM_OBJECTP(t))return(-1);
	s=ELEM_TOOBJECT(t);
	if(s[0]!=OBJECT_CDATA)return(-1);

	return(s[1]);
}
#endif

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

void *kmemdup(void *p, int sz)
{
	void *t;

	t=kalloc(sz);
	memcpy(t, p, sz);
	return(t);
}

int printltohs(char *str, long l, int n)
{
	char digs[16]="0123456789ABCDEF";
	char tstr[10];
	int i;
	for(i=0;i<n;i++)
	{
		tstr[i]=digs[l&0x0F];
		l>>=4;
	}
	tstr[n]='x';
	tstr[n+1]='0';
	for(i=(n+1);i>=0;i--)
	{
		*str++=tstr[i];
	}
	*str++=0;
}

int kgets(char *str, char **t)
{
	return(KCon_GetString(str, t));
}

int kgetch()
{
	return(KCon_Getch());
}

int kprintlong(long l)
{
//	Text_WriteLong(l);
	return(0);
}

char *kstrdup(char *s)
{
	char *t;
	t=kalloc(strlen(s)+1);
	strcpy(t, s);
	return(t);
}

char *kgstrdup(char *s)
{
	char *t;
	t=kgalloc(strlen(s)+1);
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

char *kprints(char *d, char *s, ...)
{
	void **lst;

	lst=(void **)&s;
	KCon_VSPrintf(d, s, lst);

	return(d+strlen(d));
}

char *kvprints(char *d, char *s, void **lst)
{
	KCon_VSPrintf(d, s, lst);

	return(d+strlen(d));
}

int kprintvf(VFILE *fd, char *s, ...)
{
	void **lst;
	char  *d;

	d=kralloc(1024);

	lst=(void **)&s;
	KCon_VSPrintf(d, s, lst);

	vfwrite(d, 1, strlen(d), fd);

	return(strlen(d));
}

int katoi(char *s)
{
	int si, t;

	if(*s=='-')
	{
		si=1;
		s++;
	}else si=0;

	t=0;
	while(*s && isdigit(*s))
	{
		t=(t*10)+(*s-'0');
		s++;
	}
	return(t);
}

void *kmmap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	if(fd)return(vfmmap(addr, length, prot, flags, fd, offs));
	return(KPFH_BasicMMap(addr, length, prot, flags, fd, offs));
}

int kmunmap(void *start, int length)
{
	return(KPFH_Munmap(start, length));
}

int kmsync(void *start, int length, int flags)
{
	return(KPFH_Msync(start, length, flags));
}

int kmprotect(void *start, int length, int prot)
{
	return(KPFH_Mprotect(start, length, prot));
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
