#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>
#include <stdarg.h>

#include <dll_info.h>

static char *sa_rbuf=NULL;
static int sa_rpos;

static BGBSCM_Info *sa;

void *sa_alloc(int size)
{
	return(sa->alloc(size));
}

void *sa_cons()
{
	return(sa->cons());
}

elem sa_multicons(int num, elem lst)
{
	return(sa->multicons(num, lst));
}

void *sa_malloc(int size)
{
	void *t;

	t=sa->malloc(size);

	return(t);
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

int sa_free(void *buf)
{
	sa->free(buf);
	return(0);
}

int sa_abort()
{
	sa->abort();
	return(0);
}

int sa_fatal(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	sa->fatal(s, lst);
	va_end(lst);

	sa_abort();
	return(0);
}

int sa_error(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	sa->error(s, lst);
	va_end(lst);
}

int sa_print(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	sa->print(s, lst);
	va_end(lst);
}

int sa_atoi(char *s)
{
	return(sa->atoi(s));
}

char *sa_prints(char *t, char *s, ...)
{
	va_list lst;

	va_start(lst, s);
	vsprintf(t, s, lst);
	t=sa->prints(t, s, lst);
	va_end(lst);

	return(t);
}

char *sa_itoa(int i)
{
	char *s;

	s=sa->itoa(i);
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
	return(sa->loadfile(name, sz));
}

int SAGC_AddRoot(elem *r)
{
	return(sa->AddRoot(r));
}

int SAGC_AddNamedRoot(char *name, elem *r)
{
	return(sa->AddNamedRoot(name, r));
}

int SAGC_BindNameAddr(char *name, void *r)
{
	return(sa->BindNameAddr(name, r));
}

int SAGC_PushRoot(elem *r)
{
	return(sa->PushRoot(r));
}

int SAGC_PopRoot()
{
	return(sa->PopRoots(1));
}

int SAGC_PopRoots(int n)
{
	return(sa->PopRoots(n));
}

int Sys_TimeMS()
{
	return(sa->TimeMS());
}

int Sys_TimeDUS()
{
	return(sa->TimeDUS());
}

int main_kill=0;

elem MF_Quit()
{
	return(sa->Quit());
}

int SA_DLL_Init(BGBSCM_Info *inf) //AH:ignore
{
	sa=inf;
	return(0);
}
