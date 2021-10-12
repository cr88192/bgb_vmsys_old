#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>
#include <stdarg.h>

#include <sys/time.h>

//#define HEAP_SIZE (1<<26)
#define HEAP_SIZE (1<<20)

void *sa_heap, *sa_end, *sa_rbuf=NULL;
int sa_rpos;
extern elem toplevel_n, toplevel_d;

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
	return(sa_malloc(8));
}

elem sa_multicons(int num, elem lst)
{
	elem *t;

	while(num)
	{
		t=sa_cons();
		t[0]=MISC_NULL;
		t[1]=lst;
		lst=ELEM_FROMCONS(t);
		num--;
	}
	return(lst);
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

int sa_abort()
{
	abort();
	return(0);
}

int sa_fatal(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	fprintf(stderr, "error: ");
	vfprintf(stderr, s, lst);
	va_end(lst);

	sa_abort();
	return(0);
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

char *sa_prints(char *t, char *s, ...)
{
	va_list lst;

	va_start(lst, s);
	vsprintf(t, s, lst);
	va_end(lst);

	t+=strlen(t);

	return(t);
}

char *sa_itoa(int i)
{
	char *s;

	s=sa_alloc(16);
	sprintf(s, "%d", i);
	return(s);
}

char *sa_strdup(char *s)
{
	return(strdup(s));
}

int sa_stricmp(char *s1, char *s2)
{
	return(strcasecmp(s1, s2));
}

char *sa_loadfile(char *name, int *sz)
{
	FILE *fd;
	int fsz;
	char *buf;
	char *s, *s2;

	fd=fopen(name, "rb");
	if(!fd)
	{
		sa_print("Interp_Load: no file \"%s\"\n", name);
		return(NULL);
	}

	sa_print("Interp_Load: loading \"%s\"\n", name);

	fseek(fd, 0, 2);
	fsz=ftell(fd);
	*sz=fsz;
	fseek(fd, 0, 0);
	buf=sa_malloc(fsz+1);
	buf[fsz]=0;
	fread(buf, 1, fsz, fd);

	//HACK: strip out carriage returns
	s=buf;
	s2=buf;
	while(*s)
	{
		if(*s=='\r')s++;
		*s2++=*s++;
	}
	*s2++=0;

	return(buf);
}

int SAGC_AddRoot(elem *r)
{
}

int SAGC_AddNamedRoot(char *name, elem *r)
{
}

int SAGC_BindNameAddr(char *name, void *r)
{
}

int Sys_TimeMS()
{
	struct timeval	tp;
	struct timezone tzp; 
	static int      secbase; 

	gettimeofday(&tp, &tzp);  

	if (!secbase)
		secbase = tp.tv_sec;

	return (((tp.tv_sec - secbase)*1000) + tp.tv_usec/1000);
}

int Sys_TimeDUS()
{
	struct timeval	tp;
	struct timezone tzp; 
	static int      secbase, usecbase, delta; 

	gettimeofday(&tp, &tzp);  

	if (!secbase)
	{
		secbase = tp.tv_sec;
		usecbase = tp.tv_usec;
	}

	delta=((tp.tv_sec - secbase)*1000000) + (tp.tv_usec-usecbase);
	secbase = tp.tv_sec;
	usecbase = tp.tv_usec;

	return (delta);
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

//	Interp_Load(STRING("bgb_init.sk"));

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
//			TyFcn_DumpElem(toplevel_n);
//			sa_print("\n");
//			TyFcn_DumpElem(toplevel_d);
//			sa_print("\n\n");
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
