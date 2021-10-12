#include <unistd.h>
#include <stdio.h>

int __malloc_init()
{
	__OS1_MM2_Init();
	return(0);
}

void *malloc(int size)
{
	return(__OS1_MM2_PAlloc(size));
}

int free(void *p)
{
	return(__OS1_MM2_PFree(p));
}
