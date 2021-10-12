/*
2002-03-09:
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
remove cells, replace with buddy allocator.

may decide to page out parts of the freelist blocks' data/release blocks.

2002-03-11:
gc written, mark-sweep algo. possibly make scan stack for references.

scan stack, for each member determine: is it part of an object on the used
list; either keep that object, or further verify that the member points to
the start of the object (p-4) points to object header (this may avoid extra
retention), also this would be needed to verify if it is safe to pass the
entry to mark...

2002-03-13:
ok, all object crap removed. the idea is that objects are managed almost
entirely entirely elsewhere, and the gc does not have to worry about object
type issues.
added support for destructors.
ok, now there is no real structural difference between collected and non
collected blocks. also made gc functions better check pointers.
*/

#include <general.h>

int MM2_Init()
{
	kprint("MM2_Init.\n");
	MM2_InitLow();
//	MMGC_Init();
}

mem2block *MM2_InsertBlock(mem2block *list, mem2block *block)
{
	mem2block *cur;

	block->lnext=list;
	block->lprev=NULL;
	if(list)list->lprev=block;
	list=block;
	return(list);

//	kprint("insert %p\n", block);
	if(list)
	{
		if(block->size>list->size)
		{
			cur=list;
			while(cur->lnext)
			{
				if(cur->lnext->size>=block->size)break;
				cur=cur->lnext;
			}
			block->lnext=cur->lnext;
			block->lprev=cur;
			if(cur->lnext)cur->lnext->lprev=block;
			cur->lnext=block;
		}else
		{
			block->lnext=list;
			block->lprev=NULL;
			list->lprev=block;
			list=block;
		}
	}else
	{
		list=block;
		block->lprev=NULL;
		block->lnext=NULL;
	}

//	kprint("insert list %p\n", list);
	return(list);
}

mem2block *MM2_UnlinkBlock(mem2block *list, mem2block *block)
{
	if(block->lprev)block->lprev->lnext=block->lnext;
		else list=block->lnext;
	if(block->lnext)block->lnext->lprev=block->lprev;
	block->lnext=NULL;
	block->lprev=NULL;
	return(list);
}

mem2block *MM2_SearchFirst(mem2block *cur, int size)
{
//	mem2block *cur;
//	cur=list;
//	kprint("MM2_SearchFirst{");
	while(cur)
	{
//		kprint("search %p\n\n", cur);
//		fflush(stdout);
		if((cur->size-sizeof(mem2block))>=size)
		{
//			kprint("one}\n");
			return(cur);
		}
		cur=cur->lnext;
	}
//	kprint("none}\n");
	return(NULL);
}

int MM2_Split(mem2block *block, int size)
{
	int sz2, sz3, i;
	mem2block *tmp;

	sz2=(size+sizeof(mem2block)+7);
	sz2=sz2&(~7);

	sz3=block->size-sz2;

	if(sz3<(sizeof(mem2block)+8))return(0); /* don't bother if smaller */

//	printf("Split: %d=%d+%d\n", block->size, sz2, sz3);

	block->size=sz2;
	i=(int)block;

	tmp=(mem2block *)(i+sz2);
	memset(tmp, 0, sizeof(mem2block));

	tmp->jprev=block;
	tmp->jnext=block->jnext;
	block->jnext=tmp;
	if(tmp->jnext)tmp->jnext->jprev=tmp;

	tmp->size=sz3;
	tmp->flags=MEM2BLOCK_UPPER;

	free_list=MM2_InsertBlock(free_list, tmp);

	return(1);
}

mem2block *MM2_Alloc(int size)
{
	mem2block *tmp;

//	kprint("MM2_Alloc: ");

	tmp=MM2_SearchFirst(free_list, size);
	if(tmp)
	{
//		kprint("Old Block ");
		free_list=MM2_UnlinkBlock(free_list, tmp);
		MM2_Split(tmp, size);

//		used_list=MM2_InsertBlock(used_list, tmp);

//		tmp->lnext=used_list;
//		if(used_list)used_list->lprev=tmp;
//		used_list=tmp;

		tmp->lnext=used_list;
		tmp->lprev=NULL;
		if(used_list)used_list->lprev=tmp;
		used_list=tmp;

		tmp->flags|=MEM2BLOCK_USED;
//		kprint("OK (oldblock)\n");
		return(tmp);
	}
//	kprint("New Block ");
	tmp=MM2_NewBlock(size);
//	kprint("0");
	MM2_Split(tmp, size);
//	kprint("1");
	used_list=MM2_InsertBlock(used_list, tmp);
//	kprint("2");
	tmp->flags|=MEM2BLOCK_USED;
//	kprint("OK (newblock)\n");
	return(tmp);
}

int MM2_Free(mem2block *block)
{
	used_list=MM2_UnlinkBlock(used_list, block);
	free_list=MM2_InsertBlock(free_list, block);
	block->flags=0;
	return(0);
}

int MM2_ListSpace(mem2block *list, int fl, int mask)
{
	mem2block *cur;
	int i;

	i=0;
	cur=list;
	while(cur)
	{
		if((cur->flags&mask)!=fl)kprint("MM2_ListSpace(wrong flags)\n");
		i+=cur->size;
		cur=cur->lnext;
	}
	return(i);
}

int MM2_ListCount(mem2block *list, int fl, int mask)
{
	mem2block *cur;
	int i;

	i=0;
	cur=list;
	while(cur)
	{
		if((cur->flags&mask)!=fl)kprint("MM2_ListSpace(wrong flags)\n");
		i++;
		cur=cur->lnext;
	}
	return(i);
}

int MM2_Print()
{
//	MM3_Print();
	kprint("MM2: %dKiB in %d allocs used, %dKiB in %d allocs free.\n",
		(MM2_ListSpace(used_list, 1, 1)+1023)>>10, MM2_ListCount(used_list, 1, 1),
		(MM2_ListSpace(free_list, 0, 1)+1023)>>10, MM2_ListCount(free_list, 0, 1));
	MMGC_Print();
}


void *MM2_GetData(mem2block *block, int slot)
{
	mem2block *tmp;
	void *t;
	byte *s;

	t=((void *)block)+sizeof(mem2block);
#if 0
	if(block->flags&MEM2BLOCK_CELLS)
	{
		s=t;
		t++;
		t+=((*s *2)+7)>>3;
		t=(void *)(((int)t+3)&(~3));
		t+=slot<<3;
		return(t);
	}
#endif
	return(t);
}

#if 0
mem2block *MM2_AllocCellBlock(int cells)
{
	mem2block *tmp;
	byte *t;

	tmp=MM2_Alloc((((cells*2)+7)>>3)+cells*8);
	tmp->flags|=MEM2BLOCK_CELLS;
	t=(byte *)(tmp+1);
	*t=cells;
	t++;
	memset(t, 0, (((cells*2)+7)>>3));

	return(tmp);
}

mem2block *MM2_AllocCells(mem2block *list, int size, int *c)
{
	mem2block *cur;
	byte *t;
	int sz, i, r[2];

	cur=list;
//	kprint("MM2_SearchFirst{");
	while(cur)
	{
		if(cur->flags&MEM2BLOCK_CELLS)
		{
			t=(byte *)(cur+1);
			sz=*t;
			r[0]=0;
			r[1]=size*2;
			i=BitArray2_FindShortestRun(t+1, sz*2, r);
			if(!i)
			{
				r[1]=size*2;
				BitArray2_SetRun(t+1, r);
				*c=r[0];
				return(cur);
			}
		}
		cur=cur->lnext;
	}
	cur=MM2_AllocCellBlock(492);
	t=(byte *)(cur+1);

	r[0]=0;
	r[1]=size*2;
	BitArray2_SetRun(t+1, r);
	*c=r[0];
	return(cur);

//	kprint("none}\n");
//	return(NULL);
}

#endif


void *MM2_PAlloc(int size)
{
	mem2block *blk;
	int *t;

	panic("deprecated.\n");

//	kprint("MM2_PAlloc\n");
	blk=MM2_Alloc(size+sizeof(mem2block *));
	if(!blk)return(NULL);
	t=(int *)MM2_GetData(blk, 0);
//	*t++=(int)blk;

	memset(t, 0, size);

//	kprint("MM2_PAlloc: OK\n");
	return(t);
}

mem2block *MM2_GetBlockPtr(void *p);

int MM2_PFree(void *p)
{
	mem2block *blk;
//	blk=*(mem2block **)(p-4);
	blk=MM2_GetBlockPtr(p);
	MM2_Free(blk);
	return(0);
}

#if 0
void *MM2_CAlloc(int sz)
{
	mem2block *blk;
	int c;
	void *p;

	blk=MM2_AllocCells(used_list, (sz+7)>>3, &c);
	p=MM2_GetData(blk, c);
	return(p);
}
#endif

/* safely get/verify p and return a block if one is a valid match */
mem2block *MM2_GetBlockPtr(void *p)
{
	mem2block *cur, *tmp;

	cur=used_list;
	while(cur)
	{
		if(((int)p>(int)cur) && ((int)p<((int)cur+cur->size)))
		{
#if 0
			tmp=*(mem2block **)(p-4);
			if(cur==tmp)return(cur);
#endif
			return(cur); /* inexact match */
		}
		cur=cur->lnext;
	}
	return(NULL);
}

int MM2_GetSize(void *p)
{
	mem2block *blk;
	int i;
//	blk=*(mem2block **)(p-sizeof(mem2block *));
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(-1);
	i=blk->size-sizeof(mem2block);
	return(i);
}

#if 0
void *MM_PAlloc(int size)
{
	return(MM2_PAlloc(size));
}

int MM_PFree(void *p)
{
	return(MM2_PFree(p));
}

int MM_Print()
{
	MM2_Print();
}

int MM_Init()
{
	MM2_Init();
}

#endif

/* after this needs to come gc */
#define MMGC_MAXROOTS	256
#define MMGC_HEAPLIM	(1<<24)

static void **gc_roots=NULL;
static void *stackbase=NULL;
static int (**destructors)(void *p);
static byte tagmap[32];

static int gc_alloced;

int MMGC_Init()
{
	kprint("MMGC_Init\n");
	memset(tagmap, 0, 32);
	destructors=MM2_PAlloc(256*sizeof(void *));

	gc_alloced=0;

	return(0);
}

/*
int MMGC_AllocTag()
{
	return(BitArray2_AllocBit(tagmap, 32));
}

int MMGC_FreeTag(int num)
{
	return(BitArray2_ClearBit(tagmap, num));
}
*/

int MMGC_SetDestructor(int tag, int (*proc)(void *p))
{
	destructors[tag]=proc;
	return(0);
}

int MMGC_ClearDestructor(int tag)
{
	destructors[tag]=NULL;
	return(0);
}

/* chances are this will be called before the mm/gc is set up */
int MMGC_Enter(int (*mainfunc)())
{
	int i;
	stackbase=&i;
	return(mainfunc());
}

int MMGC_StackBase(void *p)
{
	int i;
	stackbase=p;
	return(0);
}

void *MMGC_PAlloc(int size)
{
	mem2block *blk;
	int *t, vsz;

//	kprint("MM2_PAlloc\n");
	blk=MM2_Alloc(size);
	if(!blk)return(NULL);
	blk->flags|=MEM2BLOCK_COLLECT;
	t=(int *)MM2_GetData(blk, 0);
//	*t++=(int)blk;

	vsz=size+sizeof(mem2block);
	vsz=(vsz+7)&(~7);
	gc_alloced+=vsz;

	memset(t, 0, size);

//	kprint("MM2_PAlloc: OK\n");
	return(t);
}

int MMGC_MakeTagged(void *p, int tag)
{
	mem2block *blk;

//	blk=*(mem2block **)(p-sizeof(mem2block *));
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(0);

	blk->flags|=MEM2BLOCK_TAGGED;
	blk->flags&=0xffffff;
	blk->flags|=tag<<24;
	return(0);
}

int MMGC_MarkObject(void *p)
{
	mem2block *blk;
	unsigned long *t;

	if(!p)return(0); /* OK, just nothing to mark */

	if(!MM2LL_VerifyPointer(p))return(0);

	p=(void *)(((int)p)&(~7));
	blk=(mem2block *)(p-sizeof(mem2block));
	if(!MM2LL_VerifyPointer(blk))return(0);
	if(!((blk->flags & 0xffffff00)==MEM2BLOCK_UPPER))return(0);

//	blk=MM2_GetBlockPtr(p);
//	if(!blk)return(0);

//	kprint("mark %d, alt %d\n", p, *(void **)(p-4));

	if(!(blk->flags&MEM2BLOCK_COLLECT))return(0); /* ignore non-objects */
	if(blk->flags&MEM2BLOCK_MARK)return(0);
	blk->flags|=MEM2BLOCK_MARK;

//	kprint("Marked %X.\n", blk);

	//p=(void *)((int)p&(~7)); //in case a tagged pointer...
	p=MM2_GetData(blk, 0);
	MMGC_ScanRange(p, (blk->size-sizeof(mem2block))>>2);

	return(0);
}

int MMGC_AddRoot(void *ptr)
{
	int i;

	return(MMGC3_AddRoot(ptr));

	if(!gc_roots)gc_roots=(void **)MM2_PAlloc(MMGC_MAXROOTS*sizeof(void **));

	for(i=0; i<MMGC_MAXROOTS; i++)if(gc_roots[i]==ptr)return(0); /* don't add if allready here */

	for(i=0; i<MMGC_MAXROOTS; i++)if(!gc_roots[i])
	{
		gc_roots[i]=ptr;
		return(i);
	}
	kprint("MMGC_AddRoot: too many roots.\n");
	return(-1);
}

int MMGC_RemoveRoot(void *ptr)
{
	int i;
	if(!gc_roots)return(-1);
	for(i=0; i<MMGC_MAXROOTS; i++)if(gc_roots[i]==ptr)
	{
		gc_roots[i]=NULL;
		return(i);
	}
	kprint("MMGC_RemoveRoot: not found.\n");
	return(-1);
}

int MMGC_MarkAll()
{
	int i, j;

	if(!gc_roots)return(-1);
	for(i=0; i<MMGC_MAXROOTS; i++)if(gc_roots[i])
		MMGC_MarkObject(*(void **)gc_roots[i]);
	return(0);
}

int MMGC_Sweep()
{
	mem2block *cur, *cur2;
	void *p;
	int i, vsz;

	cur=used_list;
	while(cur)
	{
		cur2=cur->lnext;
		if((cur->flags&MEM2BLOCK_COLLECT) && (!(cur->flags&MEM2BLOCK_MARK)) && (!(cur->flags&MEM2BLOCK_LOCK)))
		{
//			kprint("free %X\n", cur);
			p=(void *)cur+sizeof(mem2block);
			if(cur->flags&MEM2BLOCK_TAGGED)if(destructors[cur->flags>>24])
				destructors[cur->flags>>24](p);

//			vsz=cur->size;
//			vsz=(vsz+7)&(~7);
//			gc_alloced-=vsz;

			MM2_Free(cur);
		}
		cur=cur2;
	}
	return(0);
}

int MMGC_ClearMarks()
{
	mem2block *cur;

	cur=used_list;
	while(cur)
	{
		if((cur->flags&MEM2BLOCK_COLLECT) && (cur->flags&MEM2BLOCK_MARK))
			cur->flags&=~MEM2BLOCK_MARK;
		cur=cur->lnext;
	}
	return(0);
}

int MMGC_ScanStack()
{
	unsigned long *sp;
	sp=(unsigned long *)&sp;
	while(sp<(unsigned long *)stackbase)
	{
		MMGC_MarkObject(*(void **)sp);
		sp++;
	}
	return(0);
}

int MMGC_ScanRange(int *p, int cnt)
{
	int i;
	for(i=0; i<cnt; i++)
		MMGC_MarkObject((void *)p[i]);
	return(0);
}

int MMGC_ScanStacks()
{
	kthread *cur;
	cur=rthread_list;
	while(cur)
	{
//		kprint("%X %X\n", cur->stacktop, cur->stackbottom);
		MMGC_ScanRange(cur->stackbottom, ((int)cur->stacktop - (int)cur->stackbottom)/4);
		cur=cur->rnext;
	}
}

int MMGC_Collect()
{
	int t;
	mem2block *cur;
	int objects, objsize, free, freesize;

//	if(gc_alloced<MMGC_HEAPLIM)return(0);

//	fflush(stdout);

//	kprint("\n\nGC Begin\n");

//	kprint("Mark:\n");
	t=Sys_TimeMS();
	MMGC_MarkAll();
	MMGC_ScanStacks();
//	kprint("\t%fs\n", (Sys_TimeMS()-t)/1000.0);

	t=Sys_TimeMS();
//	kprint("Sweep:\n");
	MMGC_Sweep();

//	kprint("\t%fs\n", (Sys_TimeMS()-t)/1000.0);
	t=Sys_TimeMS();

//	kprint("Clear Marks:\n");
	MMGC_ClearMarks();
//	kprint("\t%fs\n", (Sys_TimeMS()-t)/1000.0);

	objects=0;
	objsize=0;

	cur=used_list;
	while(cur)
	{
		if(cur->flags&MEM2BLOCK_COLLECT)
		{
			objects++;
			objsize+=(cur->size+7)&(~7);
		}
		cur=cur->lnext;
	}
	gc_alloced=objsize; //prevent drift

//	kprint("MMGC: %d objects using %dKiB.\n", objects, (objsize+1023)>>10);

	free=0;
	freesize=0;

	cur=free_list;
	while(cur)
	{
		free++;
		freesize+=(cur->size+7)&(~7);
		cur=cur->lnext;
	}

//	kprint("MMGC: %d objects using %dKiB.\n", free, (freesize+1023)>>10);

//	kprint("GC End.\n");

	return(0);
}

int MMGC_Print()
{
	mem2block *cur;
	int objects, objsize;

	objects=0;
	objsize=0;
	cur=used_list;
	while(cur)
	{
		if(cur->flags&MEM2BLOCK_COLLECT)
		{
			objects++;
			objsize+=(cur->size+7)&(~7);
		}
		cur=cur->lnext;
	}
	gc_alloced=objsize; //prevent drift

	kprint("MMGC: %d objects using %dKiB.\n", objects, (objsize+1023)>>10);
	return(0);
}

int MMGC_Used()
{
	return(gc_alloced);
}
