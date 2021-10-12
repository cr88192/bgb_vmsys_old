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

mem2block *mm2ll_rover, *mm2ll_initchain;

void *MM3_AllocBlock(int size);

int MM2_InitLow()
{
	mm2ll_rover=NULL;
	mm2ll_initchain=NULL;
}

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
	mem2block *head1, *head;

	size2=size+(sizeof(mem2block)*2)+4095;
	size2=1<<log2up(size2);

	if(size2<(1<<20))size2=1<<20;

	head1=malloc(size2);
	head1->next=mm2ll_initchain;
	head1->size=size2;
	mm2ll_initchain=head1;
	head=head1+1;

	memset(head, 0, size2-8);
	head->size=size2-8;
	head->size|=MEM2BLOCK_NEWCHUNK;

	return(head);
}

int MM2LL_VerifyPointer(void *p)
{
	mem2block *cur;
	mem2block *head;

	cur=mm2ll_initchain;
	while(cur)
	{
		if((p>(void *)cur) && (p<((void *)cur+(cur->size&MEM2BLOCK_SIZEMASK))))return(1);
		cur=cur->next;
	}
	return(0);
}