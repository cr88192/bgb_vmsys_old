#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <general.h>
#include <scmcc.h>
#include <stdarg.h>

#include <dll_info.h>

//AH:skip

#define HEAP_SIZE (1<<26)

void *sadll_heap, *sadll_end, *sadll_rbuf=NULL;
int sadll_rpos;
extern elem toplevel_n, toplevel_d;

int MMGC3_AddRoot(elem *r);
int MMGC3_AddNamedRoot(char *name, elem *r);
int MMGC3_BindNameAddr(char *name, void *r);
int MMGC3_PushRoot(elem *p);
int MMGC3_PopRoots(int n);

int Sys_TimeMS();
int Sys_TimeDUS();

void *sadll_alloc(int size)
{
	void *t;

	t=ELEM_TOOBJECT(MMGC3_Object(size));
	memset(t, 0, (size+7)&(~7));

//	t=kgalloc(size);
	if((int)t&7)
	{
		sadll_error("sadll_alloc: unaligned alloc.\n");
		abort();
	}

	return(t);
}

void *sadll_cons()
{
//	return(sadll_alloc(2*ELEM_SZ));
	return(ELEM_TOCONS(MMGC3_Cons()));
}

elem sadll_multicons(int num, elem lst)
{
	return(MMGC3_MultiCons(num, lst));
}

void *sadll_ralloc(int size)
{
	void *t;

	if(!sadll_rbuf)
	{
		sadll_rbuf=kalloc(1<<20);
		sadll_rpos=0;
	}

	size=(size+7)&(~7);
	if((size+sadll_rpos)>(1<<20))sadll_rpos=0;
	t=sadll_rbuf+sadll_rpos;
	sadll_rpos+=size;

	return(t);
}

void *sadll_malloc(int size)
{
	void *t;

//	sadll_print("sadll_malloc.\n");

	t=(void *)kgalloc(size);

	return(t);
}

int sadll_free(void *buf)
{
	kfree(buf);
	return(0);
}

int sadll_mark(elem ref)
{
	MMGC3_TracePush(ref);
	return(0);
}

char *sadll_strdup(char *s)
{
	return(kstrdup(s));
}

int sadll_fatal(char *s, va_list lst) //AH:ignore
{
	static char buf[1024];

	kprint("fatal: ");
	vsprintf(buf, s, lst);
	kprint(buf);
	sadll_abort();

	return(0);
}

int sadll_error(char *s, va_list lst) //AH:ignore
{
	static char buf[1024];

	kprint("error: ");
	vsprintf(buf, s, lst);
	kprint(buf);

	return(0);
}

int sadll_print(char *s, va_list lst) //AH:ignore
{
	static char buf[262144];

	vsprintf(buf, s, lst);
	kprint(buf);

	return(0);
}

char *sadll_prints(char *t, char *s, va_list lst) //AH:ignore
{
#if 0
	kva_list lst;
	static char buf[1024];

	kva_start(lst, s);
	t=kvprints(t, s, lst);
	kva_end(lst);

	return(t);
#endif
	vsprintf(t, s, lst);
	t+=strlen(t);
	return(t);
}

int sadll_atoi(char *s)
{
	int x, i;
	if(*s=='0')
	{
		if(s[1]=='x')
		{
			s+=2;
			x=0;
			while(*s)
			{
				i=-1;
				if((*s>='0') && (*s<='9'))i=*s-'0';
				if((*s>='a') && (*s<='f'))i=*s-'a'+10;
				if((*s>='A') && (*s<='F'))i=*s-'A'+10;
				if(i<0)break;
				x=(x<<4)+i;
				s++;
			}
			return(x);
		}
		x=0;
		while(*s>='0' && *s<='7')x=(x<<3)+((*s++)-'0');
		return(x);
	}
	return(atoi(s));
}

char *sadll_itoa(int i)
{
	char *s;

	s=kralloc(16);
	kprints(s, "%d", i);
	return(s);
}

int sadll_stricmp(char *s1, char *s2)
{
	return(stricmp(s1, s2));
}

char *sadll_loadfile(char *name, int *sz)
{
	VFILE *fd;
	int fsz;
	byte *buf;
	char *s, *s2;

	fd=vffopen(name, "rb");
	if(!fd)
	{
		kprint("sadll_LoadFile: no file \"%s\"\n", name);
		return(NULL);
	}

	kprint("Interp_Load: loading \"%s\"\n", name);

	vfseek(fd, 0, 2);
	fsz=vftell(fd);
	vfseek(fd, 0, 0);
	buf=sadll_malloc(fsz+8);
	memset(buf+fsz, 0, 8);
	vfread(buf, 1, fsz, fd);

#if 0
	//HACK: strip out carriage returns
	s=buf;
	s2=buf;
	while(*s)
	{
		if(*s=='\r')s++;
		*s2++=*s++;
	}
	*s2++=0;
#endif

	if(sz)*sz=fsz;
	return(buf);
}

int sadll_abort()
{
	*(int *)-4=0;
	return(0);
}

int main_kill=0;

elem MF_HeapSize()
{
//	return(ELEM_FROMFIXNUM(HEAP_SIZE));
	return(ELEM_FROMFIXNUM(MMGC3_Total()));
}

elem MF_HeapUsage()
{
	return(ELEM_FROMFIXNUM(MMGC3_Used()));
//	return(ELEM_FROMFIXNUM(MMGC_Used()));
//	return(ELEM_FROMFIXNUM((int)sadll_end-(int)sadll_heap));
}

elem MF_HeapWorking()
{
	return(ELEM_FROMFIXNUM(MMGC3_Working()));
//	return(ELEM_FROMFIXNUM(MMGC_Used()));
//	return(ELEM_FROMFIXNUM((int)sadll_end-(int)sadll_heap));
}

elem MF_GCStats()
{
	return(MMGC3_Stats());
//	return(ELEM_FROMFIXNUM(MMGC_Used()));
//	return(ELEM_FROMFIXNUM((int)sadll_end-(int)sadll_heap));
}

elem MF_Quit()
{
	main_kill=1;
	return(MISC_NULL);
}

int SKVM_Init()
{
	BGBSCM_Info *inf;

	inf=malloc(sizeof(BGBSCM_Info));
	memset(inf, 0, sizeof(BGBSCM_Info));
	inf->alloc=&sadll_alloc;
	inf->cons=&sadll_cons;
	inf->multicons=&sadll_multicons;
	inf->malloc=&sadll_malloc;
	inf->free=&sadll_free;
	inf->abort=&sadll_abort;
	inf->fatal=&sadll_fatal;
	inf->error=&sadll_error;
	inf->print=&sadll_print;
	inf->atoi=&sadll_atoi;
	inf->itoa=&sadll_itoa;
	inf->prints=&sadll_prints;
	inf->loadfile=&sadll_loadfile;

	inf->AddRoot=&MMGC3_AddRoot;
	inf->AddNamedRoot=&MMGC3_AddNamedRoot;
	inf->BindNameAddr=&MMGC3_BindNameAddr;
	inf->PushRoot=&MMGC3_PushRoot;
	inf->PopRoots=&MMGC3_PopRoots;

	inf->TimeMS=&Sys_TimeMS;
	inf->TimeDUS=&Sys_TimeDUS;

	SA_DLL_Init(inf);

	TyFcn_Init();
	Interp_Init();
	HpiComp_Init();
	HpiInterp_Init();
//	AsmCG_Init();
	LBSExt_Init();

	Builtin_Init();

	TyObj_Init();

//	Interp_DefinePrimative("quit",		&MF_Quit,		0);
	Interp_DefinePrimative("heap-size",	&MF_HeapSize,		0);
	Interp_DefinePrimative("heap-usage",	&MF_HeapUsage,		0);
	Interp_DefinePrimative("heap-working",	&MF_HeapWorking,	0);
	Interp_DefinePrimative("gc-stats",	&MF_GCStats,		0);
}

int SKVM_DeInit()
{
}
