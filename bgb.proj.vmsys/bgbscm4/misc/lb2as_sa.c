#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>
#include <stdarg.h>

#include <interpctx.h>

#define HEAP_SIZE (1<<22)

void *sa_heap, *sa_end, *sa_rbuf=NULL;
int sa_rpos;
extern elem toplevel_n, toplevel_d;

InterpCtx *repl_ctx;

void *sa_alloc(int size)
{
	void *t;
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

void *sa_cons()
{
	return(sa_alloc(2*ELEM_SZ));
}

void *sa_ralloc(int size)
{
	void *t;

	if(!sa_rbuf)
	{
		sa_rbuf=malloc(262144);
		sa_rpos=0;
	}

	size=(size+7)&(~7);
	if((size+sa_rpos)>262144)sa_rpos=0;
	t=sa_rbuf+sa_rpos;
	sa_rpos+=size;

	return(t);
}

void *sa_malloc(int size)
{
	void *t;

	t=malloc(size);

	return(t);
}

int sa_free(void *buf)
{
	free(buf);
	return(0);
}

int sa_fatal(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	fprintf(stderr, "fatal: ");
	vfprintf(stderr, s, lst);
	va_end(lst);
	abort();
}

int sa_error(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	fprintf(stderr, "error: ");
	vfprintf(stderr, s, lst);
	va_end(lst);
}

int sa_print(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);
}

int sa_atoi(char *s)
{
	return(atoi(s));
}

int MMGC3_AddRoot(void **r)
{
}

int MMGC3_AddNamedRoot(void **r, char *s)
{
}

int MMGC3_BindNameAddr(char *s, void *r)
{
}

FILE *vffopen(char *s, char *a)
{
	return(fopen(s, a));
}

int vfseek(FILE *fd, int p, int r)
{
	fseek(fd, p, r);
}

int vftell(FILE *fd)
{
	return(ftell(fd));
}

int vfread(void *buf, int s1, int s2, FILE *fd)
{
	return(fread(buf, s1, s2, fd));
}

int Sys_TimeMS()
{
	return(0);
}

int Sys_TimeDUS()
{
	return(0);
}

int sa_stricmp(char *s1, char *s2)
{
	return(strcasecmp(s1, s2));
}

int main_kill=0;

elem MF_Quit()
{
	main_kill=1;
	return(MISC_NULL);
}

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

	fd=fopen(argv[1], "rt");
	fseek(fd, 0, 2);
	fsz=ftell(fd);
	fseek(fd, 0, 0);
	buf=malloc(fsz+1);
	buf[fsz]=0;
	fread(buf, 1, fsz, fd);

	ofd=fopen(argv[2], "wt");

	TyFcn_Init();
	Interp_Init();
	HpiComp_Init();
	HpiInterp_Init();
	AsmCG_Init();

	Builtin_Init();

	TyObj_Init();

//	Interp_DefinePrimative("quit",	&MF_Quit,				0);

//	Interp_Load(STRING("bgb_init.sk"));

	ro=CONS(MISC_UNDEFINED, MISC_EOL);

#if 0
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
		t=ScmParse_Line(&s, 1);
		if(t==MISC_UNDEFINED)break;

		TyFcn_DumpElem(t);
		sa_print("\n");

		t=HpiComp_Compile(t, MISC_EOL, repl_ctx, 0);
		TyFcn_DumpElem(t);
		sa_print("\n");

		ct=MISC_EOL;
		dt=MISC_EOL;
		AsmCG_GenFrag(t, &ct, &dt);

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
	AsmCG_GenFinal(&ct, &dt);
	cl=TyFcn_NAppend(cl, ct);
	dl=TyFcn_NAppend(dl, dt);

	AsmCG_GenInitial(&cl, &dl);

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
