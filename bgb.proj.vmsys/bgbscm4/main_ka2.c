#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>
#include <stdarg.h>

#define HEAP_SIZE (1<<26)

void *sa_heap, *sa_end, *sa_rbuf=NULL;
int sa_rpos;
extern elem toplevel_n, toplevel_d;

#if 0
void *sa_alloc(int size)
{
	void *t;

	if(!sa_heap)
	{
		sa_heap=malloc(HEAP_SIZE);
		memset(sa_heap, 0, HEAP_SIZE);
		sa_end=sa_heap;
		sa_end=(void *)(((int)sa_end+7)&(~7));
	}

	t=sa_end;
	sa_end+=size;
	sa_end=(void *)(((int)sa_end+7)&(~7));

	if((int)(sa_end-sa_heap)>HEAP_SIZE)
	{
		printf("heap overflow, %d with %d/%d.\n", size, (int)(sa_end-sa_heap), HEAP_SIZE);
		*(int *)(0)=0;
		exit(-1);
	}

	return(t);
}
#else

void *sa_alloc(int size)
{
	void *t;

	t=ELEM_TOOBJECT(MMGC3_Object(size));
	memset(t, 0, (size+7)&(~7));

//	t=kgalloc(size);
	if((int)t&7)
	{
		sa_error("sa_alloc: unaligned alloc.\n");
		abort();
	}

	return(t);
}

void *sa_cons()
{
//	return(sa_alloc(2*ELEM_SZ));
	return(ELEM_TOCONS(MMGC3_Cons()));
}

elem sa_multicons(int num, elem lst)
{
	return(MMGC3_MultiCons(num, lst));
}

#endif

void *sa_ralloc(int size)
{
	void *t;

	if(!sa_rbuf)
	{
		sa_rbuf=kalloc(1<<20);
		sa_rpos=0;
	}

	size=(size+7)&(~7);
	if((size+sa_rpos)>(1<<20))sa_rpos=0;
	t=sa_rbuf+sa_rpos;
	sa_rpos+=size;

	return(t);
}

void *sa_malloc(int size)
{
	void *t;

//	sa_print("sa_malloc.\n");

	t=(void *)kgalloc(size);

	return(t);
}

int sa_free(void *buf)
{
	kfree(buf);
	return(0);
}

int sa_mark(elem ref)
{
	MMGC3_TracePush(ref);
	return(0);
}

char *sa_strdup(char *s)
{
	return(kstrdup(s));
}

int sa_fatal(char *s, ...)
{
	kva_list lst;
	kva_start(lst, s);
	kprint("fatal: ");
	kvprint(s, lst);
	kva_end(lst);
	sa_abort();

	return(0);
}

int sa_error(char *s, ...)
{
	kva_list lst;
	kva_start(lst, s);
	kprint("error: ");
	kvprint(s, lst);
	kva_end(lst);

	return(0);
}

int sa_print(char *s, ...)
{
	kva_list lst;
	static char buf[1024];

	kva_start(lst, s);
	kvprint(s, lst);
//	kprint(buf);

//	lprint(buf);
	kva_end(lst);

	return(0);
}

char *sa_prints(char *t, char *s, ...)
{
	kva_list lst;
	static char buf[1024];

	kva_start(lst, s);
	t=kvprints(t, s, lst);
	kva_end(lst);

	return(t);
}

int sa_atoi(char *s)
{
	int x;
	if(*s=='0')
	{
		x=0;
		while(*s>='0' && *s<='7')x=(x<<3)+((*s++)-'0');
		return(x);
	}
	return(atoi(s));
}

char *sa_itoa(int i)
{
	char *s;

	s=kralloc(16);
	kprints(s, "%d", i);
	return(s);
}

int sa_stricmp(char *s1, char *s2)
{
	return(stricmp(s1, s2));
}

char *sa_loadfile(char *name, int *sz)
{
	VFILE *fd;
	int fsz;
	byte *buf;
	char *s, *s2;

	fd=vffopen(name, "rb");
	if(!fd)
	{
		sa_print("SA_LoadFile: no file \"%s\"\n", name);
		return(NULL);
	}

	sa_print("Interp_Load: loading \"%s\"\n", name);

	vfseek(fd, 0, 2);
	fsz=vftell(fd);
	vfseek(fd, 0, 0);
	buf=sa_malloc(fsz+8);
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

int sa_abort()
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
//	return(ELEM_FROMFIXNUM((int)sa_end-(int)sa_heap));
}

elem MF_HeapWorking()
{
	return(ELEM_FROMFIXNUM(MMGC3_Working()));
//	return(ELEM_FROMFIXNUM(MMGC_Used()));
//	return(ELEM_FROMFIXNUM((int)sa_end-(int)sa_heap));
}

elem MF_GCStats()
{
	return(MMGC3_Stats());
//	return(ELEM_FROMFIXNUM(MMGC_Used()));
//	return(ELEM_FROMFIXNUM((int)sa_end-(int)sa_heap));
}

elem MF_Quit()
{
	main_kill=1;
	return(MISC_NULL);
}

int SKVM_Init()
{
//	sa_heap=malloc(HEAP_SIZE);
//	memset(sa_heap, 0, HEAP_SIZE);
//	sa_end=sa_heap;
//	sa_end=(void *)(((int)sa_end+7)&(~7));
	sa_heap=NULL;

	TyFcn_Init();
	Interp_Init();
	HpiComp_Init();
	HpiInterp_Init();
//	AsmCG_Init();
	LBSExt_Init();

	Builtin_Init();

	TyObj_Init();

	Interp_DefinePrimative("quit",		&MF_Quit,		0);
	Interp_DefinePrimative("heap-size",	&MF_HeapSize,		0);
	Interp_DefinePrimative("heap-usage",	&MF_HeapUsage,		0);
	Interp_DefinePrimative("heap-working",	&MF_HeapWorking,	0);
	Interp_DefinePrimative("gc-stats",	&MF_GCStats,		0);
}

int SKVM_DeInit()
{
}

#if 0
int main(int argc, char *argv[])
{
	FILE *fd, *ofd;
	int fsz;
	char *buf, *s;
	elem t, ro;
	char lbuf[256];
	elem x, cl, dl, ct, dt;

	sa_heap=malloc(HEAP_SIZE);
	memset(sa_heap, 0, HEAP_SIZE);
	sa_end=sa_heap;
	sa_end=(void *)(((int)sa_end+7)&(~7));

//	fd=fopen(argv[1], "rt");
//	fseek(fd, 0, 2);
//	fsz=ftell(fd);
//	fseek(fd, 0, 0);
//	buf=malloc(fsz+1);
//	buf[fsz]=0;
//	fread(buf, 1, fsz, fd);

//	ofd=fopen(argv[2], "wt");

	TyFcn_Init();
	Interp_Init();
	HpiComp_Init();
	HpiInterp_Init();
//	AsmCG_Init();

	Builtin_Init();

	TyObj_Init();

	Interp_DefinePrimative("quit",	&MF_Quit,				0);

	Interp_Load(STRING("bgb_init.sk"));

	ro=CONS(MISC_UNDEFINED, MISC_EOL);

#if 1
/*	s=buf;
	while(*s)
	{
		t=ScmParse_Item(&s);
		TyFcn_DumpElem(t);
		printf("\n");
		TyFcn_SetCar(ro, interp_globals);
		t=Interp_Eval(t, ro);
		TyFcn_DumpElem(t);
		printf("\n");
	} */
	while(!main_kill)
	{
		fgets(lbuf, 255, stdin);
		t=Interp_EvalStringTop(lbuf);

#if 0
		s=lbuf;
		t=ScmParse_Line(&s);

		t=HpiComp_Compile(t, MISC_EOL, MISC_EOL, 0);
		TyFcn_DumpElem(t);
		sa_print("\n");

		cl=MISC_EOL;
		dl=MISC_EOL;
		AsmCG_GenFrag(t, &cl, &dl);

		x=cl;
		while(x!=MISC_EOL)
		{
			TyFcn_DisplayElem(CAR(x));
			x=CDR(x);
		}

		x=dl;
		while(x!=MISC_EOL)
		{
			TyFcn_DisplayElem(CAR(x));
			x=CDR(x);
		}

		sa_print("\n");

//		s=lbuf;
//		t=ScmParse_Item(&s);
#endif

		TyFcn_DumpElem(t);
		printf("\n");
		if(t==SYM("kill:"))break;
		if(t==SYM("env:"))
		{
			TyFcn_DumpElem(toplevel_n);
			sa_print("\n");
			TyFcn_DumpElem(toplevel_d);
			sa_print("\n\n");
		}
	}
#else

	s=buf;

	cl=MISC_EOL;
	dl=MISC_EOL;

	while(*s)
	{
		t=ScmParse_Line(&s, 0);
		if(t==MISC_UNDEFINED)break;

		TyFcn_DumpElem(t);
		sa_print("\n");

		t=HpiComp_Compile(t, MISC_EOL, MISC_EOL, 0);
		TyFcn_DumpElem(t);
		sa_print("\n");

		ct=MISC_EOL;
		dt=MISC_EOL;
//		AsmCG_GenFrag(t, &ct, &dt);

#if 0
		x=ct;
		while(x!=MISC_EOL)
		{
			TyFcn_DisplayElem(CAR(x));
			x=CDR(x);
		}

		x=dt;
		while(x!=MISC_EOL)
		{
			TyFcn_DisplayElem(CAR(x));
			x=CDR(x);
		}
#endif

//		sa_print("\n");

		cl=TyFcn_NAppend(cl, ct);
		dl=TyFcn_NAppend(dl, dt);
	}
	ct=MISC_EOL;
	dt=MISC_EOL;
//	AsmCG_GenFinal(&ct, &dt);
	cl=TyFcn_NAppend(cl, ct);
	dl=TyFcn_NAppend(dl, dt);

//	AsmCG_GenInitial(&cl, &dl);

	x=cl;
	while(x!=MISC_EOL)
	{
//		TyFcn_DisplayElem(CAR(x));
		s=ELEM_TOSTRING(CAR(x));
		fprintf(ofd, "%s", s);
		x=CDR(x);
	}

	x=dl;
	while(x!=MISC_EOL)
	{
//		TyFcn_DisplayElem(CAR(x));
		s=ELEM_TOSTRING(CAR(x));
		fprintf(ofd, "%s", s);
		x=CDR(x);
	}
#endif

	printf("\nheap %d/%d\n", sa_end-sa_heap, HEAP_SIZE);
}

#endif
