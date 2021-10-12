/*
this will attempt to be a replacement for memory.c and objheap.c, plans will
be to use first fit+ascending order the reason being that it will be faster
than best fit. when an allocation is done any remaining space (if a usable
size) will be hacked off and added to the list of free blocks. if no block
large enough exists it will attempt to be allocated (from the page manager).

on freeing a block will be moved to a free list (the same it is allocated
from). blocks may have a next/prev reference to indicate what can be merged.
blocks will be mapped to the space 0x20000000 (512MiB), and thus will not
coexist with objheap (not like it were used anyways).

cells will be a form of minature mm for small data, not important for
now. the problem: each block has 24bytes of header, this is a problem for
smaller objects where this is a bit much overhead. the idea will be to
break blocks up into smaller parts (cells) and allocate them with a bitmap.
currently I am considring using 8 bytes as a cell size, though allocations
will be padded up to this it is not much of a problem (considering the
overhead of a normal allocation).

may decide to page out parts of the freelist blocks' data/release blocks.
*/

#include <general.h>

mem2block *used_list, *free_list;
void *mm2ll_initchain;

void *MM3_AllocBlock(int size);

int MM2_InitLow()
{
	used_list=NULL;
	free_list=NULL;
	mm2ll_initchain=NULL;
}

/* int MM2_InitLow2()
{
	used_list=NULL;
	free_list=NULL;
} */

static int log2up(int v)
{
	int c;
	c=0;
	while(v>1)
	{
		c++;
		if(v>1 && v&1)v++;
		v>>=1;
	}
	return(c);
}

mem2block *MM2_NewBlock(int size)
{
	int i, j, k;
	int s, size2;
	void *p;
	mem2block *head;

//	size2=size+sizeof(mem2block)+4095;
	size2=size+sizeof(mem2block)+4095;
	size2=1<<log2up(size2);

	if(size2<(1<<20))size2=1<<20;

//	size2-=size2&4095;
//	size2=size+sizeof(mem2block);

//	printf("size2=%d, size=%d\n", size2, size);

//	head=malloc(size2);
//	s=32-log2up(size2);
//	head=MM3_AllocBlock(size2);

	p=malloc(size2);
	*(void **)p=mm2ll_initchain;
	((int *)p)[1]=size2;
	mm2ll_initchain=p;
	head=p+8;

//	if((int)head<0x85851c0 && ((int)head+size2)>0x85851c0)head=malloc(size2);

	memset(head, 0, size2-8);
	head->size=size2-8;
	head->flags=MEM2BLOCK_UPPER;

//	head->jprev=j_end;
//	if(j_end)j_end->jnext=head;
//	j_end=head;

	return(head);
}

int MM2LL_VerifyPointer(void *p)
{
	void *cur;
	mem2block *head;

	cur=mm2ll_initchain;
	while(cur)
	{
		if((p>cur) && (p<(cur+((int *)cur)[1])))return(1);
		cur=*(void **)cur;
	}
	return(0);
}