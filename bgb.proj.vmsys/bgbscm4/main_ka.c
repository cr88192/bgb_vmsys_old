#include <general.h>

#include "scmcc.h"

//AH:skip

//#define HEAP_SIZE (1<<20)

//void *sa_heap, *sa_end;

void *(*sa_allocfcn)(int size, void *data);
void *sa_allocdata;

void *sa_alloc(int size)
{
	void *t;

/*	t=sa_end;
	sa_end+=size;
	sa_end=(void *)(((int)sa_end+7)&(~7));

	if((int)(sa_end-sa_heap)>HEAP_SIZE)
	{
		printf("heap overflow, %d with %d/%d.\n", size, (int)(sa_end-sa_heap), HEAP_SIZE);
		exit(-1);
	} */

	if(sa_allocfcn)
	{
		t=sa_allocfcn(size, sa_allocdata);
	}else
	{
//		t=kpgalloc(size);

		t=kgalloc(size+15);
		t=(void *)(((int)t+15)&(~15));
	}

	return(t);
}

int sa_error(char *s, ...)
{
	kva_list lst;
	kva_start(lst, s);

	kprint("error: ");
	kvprint(s, lst);
	kva_end(lst);
}

int sa_print(char *s, ...)
{
	kva_list lst;
	kva_start(lst, s);

	kvprint(s, lst);
	kva_end(lst);
}

int sa_atoi(char *s)
{
	return(katoi(s));
}

int sa_stricmp(char *s1, char *s2)
{
	return(stricmp(s1, s2));
}

/*
int main(int argc, char *argv[])
{
	FILE *fd;
	int fsz;
	char *buf, *s;
	elem t, ro;

	fd=fopen(argv[1], "rt");
	fseek(fd, 0, 2);
	fsz=ftell(fd);
	fseek(fd, 0, 0);
	buf=malloc(fsz+1);
	buf[fsz]=0;
	fread(buf, 1, fsz, fd);

	Interp_Init();

	ro=TyFcn_Cons(MISC_UNDEFINED, MISC_EOL);

	s=buf;
	while(*s)
	{
		t=ScmParse_Item(&s);
		TyFcn_DumpElem(t);
		printf("\n");
		TyFcn_SetCar(ro, interp_globals);
		t=Interp_Eval(t, ro);
		TyFcn_DumpElem(t);
		printf("\n");
	}
	printf("\nheap %d/%d\n", sa_end-sa_heap, HEAP_SIZE);
}
*/