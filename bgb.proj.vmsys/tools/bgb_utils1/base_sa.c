#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>
#include <stdarg.h>

#define HEAP_SIZE (1<<24)

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
		sa_abort();
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

char *sa_strdup(char *s)
{
	return(strdup(s));
}

int sa_abort()
{
	*(int *)(-4)=0;
//	abort();
}

int sa_fatal(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	fprintf(stderr, "error: ");
	vfprintf(stderr, s, lst);
	va_end(lst);

	sa_abort();
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

int SKVM_Init()
{
	sa_heap=malloc(HEAP_SIZE);
	memset(sa_heap, 0, HEAP_SIZE);
	sa_end=sa_heap;
	sa_end=(void *)(((int)sa_end+7)&(~7));

	TyFcn_Init();
}

int SKVM_DeInit()
{
	printf("\nheap %d/%d\n", sa_end-sa_heap, HEAP_SIZE);
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

	TyFcn_Init();

	printf("\nheap %d/%d\n", sa_end-sa_heap, HEAP_SIZE);
}
#endif
