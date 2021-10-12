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
*/

#include <general.h>

int MM2_Init()
{
	kprint("MM2_Init.\n");
	MM2_InitLow();
	MMGC_Init();
}

mem2block *MM2_InsertBlock(mem2block *list, mem2block *block)
{
	mem2block *cur;
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

mem2block *MM2_SearchFirst(mem2block *list, int size)
{
	mem2block *cur;
	cur=list;
//	kprint("MM2_SearchFirst{");
	while(cur)
	{
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
	sz2-=sz2&7;

	sz3=block->size-sz2;

	if(sz3<(sizeof(mem2block)+16))return(0); /* don't bother if smaller */

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
		used_list=MM2_InsertBlock(used_list, tmp);
//		tmp->lnext=used_list;
//		if(used_list)used_list->lprev=tmp;
//		used_list=tmp;

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
	kprint("MM2: %dKiB in %d allocs used, %dKiB in %d allocs free.\n",
		(MM2_ListSpace(used_list, 1, 1)+1023)>>10, MM2_ListCount(used_list, 1, 1),
		(MM2_ListSpace(free_list, 0, 1)+1023)>>10, MM2_ListCount(free_list, 0, 1));
	MMGC_Print();
}

mem2block *MM2_AllocObject(int size, int type)
{
	mem2block *tmp;
	unsigned int *t;

	tmp=MM2_Alloc(size+8);
	tmp->flags|=MEM2BLOCK_OBJECT;
	tmp->flags&=0xffffff;
	tmp->flags|=(type<<24);
	t=(unsigned int *)((void *)tmp+sizeof(mem2block));
//	*t=type+(size<<16);
	t[0]=0; /* back link */
	t[1]=(unsigned int)tmp; /* PAlloc and objects in common: *(p-4) points to self */
	return(tmp);
}

void *MM2_GetData(mem2block *block, int slot)
{
	mem2block *tmp;
	void *t;
	byte *s;

	t=((void *)block)+sizeof(mem2block);
	if(block->flags&MEM2BLOCK_OBJECT)t+=8;
		else if(block->flags&MEM2BLOCK_CELLS)
	{
		s=t;
		t++;
		t+=((*s *2)+7)>>3;
		t=(void *)(((int)t+3)&(~3));
		t+=slot<<3;
		return(t);
	}
	return(t);
}

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

void *MM2_PAlloc(int size)
{
	mem2block *blk;
	int *t;

//	kprint("MM2_PAlloc\n");
	blk=MM2_Alloc(size+sizeof(mem2block *)+4);
	if(!blk)return(NULL);
	t=(int *)MM2_GetData(blk, 0);
	*t++=(int)blk;

	memset(t, 0, size);

//	kprint("MM2_PAlloc: OK\n");
	return(t);
}

int MM2_PFree(void *p)
{
	mem2block *blk;
	blk=*(mem2block **)(p-4);
	MM2_Free(blk);
	return(0);
}

void *MM2_CAlloc(int sz)
{
	mem2block *blk;
	int c;
	void *p;

	blk=MM2_AllocCells(used_list, (sz+7)>>3, &c);
	p=MM2_GetData(blk, c);
	return(p);
}

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

/* after this needs to come gc */

gc_type *gct_root=NULL;
int gct_last=1;

#define MMGC_MAXROOTS	256
void **gc_roots=NULL;
void *stackbase=NULL;

int MMGC_Init()
{
	gc_type *type;
	kprint("MMGC_Init\n");
	/* doesn't do much */
	return(0);
}

/* chances are this will be called before the mm/gc is set up */
int MMGC_Enter(int (*mainfunc)())
{
	int i;
	stackbase=&i;
	return(mainfunc());
}

gc_type *MMGC_NewType(char *name)
{
	gc_type *tmp;
	tmp=MM2_PAlloc(sizeof(gc_type));
	tmp->num=gct_last++;
	tmp->name=kstrdup(name);
	tmp->next=gct_root;
	gct_root=tmp;
	return(tmp);
}

gc_type *MMGC_LookupTypeNum(int num)
{
	gc_type *cur;
	cur=gct_root;
	while(cur)
	{
		if(cur->num==num)return(cur);
		cur=cur->next;
	}
	return(NULL);
}

gc_type *MMGC_LookupTypeName(char *name)
{
	gc_type *cur;
	cur=gct_root;
	while(cur)
	{
		if(!strcmp(cur->name, name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

int MM2_GetObjType(void *p)
{
	mem2block *blk;
//	unsigned long *t;
	blk=*(mem2block **)(p-sizeof(mem2block *));
//	t=(unsigned long *)(blk+1);
//	return(*t&0x1ff);
	return(blk->flags>>24);
}

int MM2_GetObjSize(void *p)
{
	mem2block *blk;
	unsigned long *t;
	blk=*(mem2block **)(p-sizeof(mem2block *));
//	t=(unsigned long *)(blk+1);
//	return(*t>>16);
	return(blk->size);
}

void *MM2_ObjAlloc(int size, int type)
{
	void *p;
	p=MM2_AllocObject(size, type);
	p+=sizeof(mem2block)+8;
	return(p);
}

void *MM2_ObjAllocS(int size, char *type)
{
	void *p;
	gc_type *typ;
	typ=MMGC_LookupTypeName(type);
	if(!typ)return(NULL);
//	kprint("ObjAllocS: %s %s %d\n", type, typ->name, typ->num);
	p=MM2_ObjAlloc(size, typ->num);
	return(p);
}

int MMGC_MarkObject(void *p)
{
	mem2block *blk;
	unsigned long *t;
	gc_type *typ;

	if(!p)return(0); /* OK, just nothing to mark */

//	kprint("mark %d, alt %d\n", p, *(void **)(p-4));

	blk=*(mem2block **)(p-sizeof(mem2block *));
	if(!blk->flags&MEM2BLOCK_OBJECT)return(0); /* ignore non-objects */
	if(blk->flags&MEM2BLOCK_MARK)return(0);
	blk->flags|=MEM2BLOCK_MARK;

//	kprint("Marked %d.\n", blk);

	typ=MMGC_LookupTypeNum(blk->flags>>24);
	if(typ)if(typ->markall)return(typ->markall(p));
	return(0);
}

int MMGC_DestroyObject(void *p)
{
	mem2block *blk;
	gc_type *typ;

	if(!p)return(0); /* OK, just nothing to mark */

	blk=*(mem2block **)(p-sizeof(mem2block *));

//	kprint("destroy %d\n", blk);

	typ=MMGC_LookupTypeNum(blk->flags>>24);
	if(typ)if(typ->destroy)return(typ->destroy(p));

//	MM2_Free(blk);
	MM2_PFree(p);

	return(0);
}

int MMGC_AddRoot(void *ptr)
{
	int i;
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

/* safely get/verify p and return a block if one is a valid match */
mem2block *MM2_GetBlockPtr(void *p)
{
	mem2block *cur, *tmp;

	cur=used_list;
	while(cur)
	{
		if((p>(void *)cur) && (p<((void *)cur+cur->size)))
		{
			tmp=*(mem2block **)(p-4);
			if(cur==tmp)return(cur);
		}
		cur=cur->lnext;
	}
	return(NULL);
}

int MMGC_MarkAll()
{
	int i;

	if(!gc_roots)return(-1);
	for(i=0; i<MMGC_MAXROOTS; i++)if(gc_roots[i])if(MM2_GetBlockPtr(*(void **)gc_roots[i]))
		MMGC_MarkObject(*(void **)gc_roots[i]);
	return(0);
}

int MMGC_MarkSafe(void *p)
{
	if(MM2_GetBlockPtr(p))return(MMGC_MarkObject(p));
}

int MMGC_Sweep()
{
	mem2block *cur;
	void *p;

	cur=used_list;
	while(cur)
	{
		if((cur->flags&MEM2BLOCK_OBJECT) && (!(cur->flags&MEM2BLOCK_MARK)) && (!(cur->flags&MEM2BLOCK_LOCK)))
		{
//			printf("free %p.\n", cur);
			/* this is counter-intuitive */
			p=MM2_GetData(cur, 0);
//			kprint("sweep: %d\n", cur->flags>>24);
//			p=(void *)cur+sizeof(mem2block)+8;
//			*(void **)(p-4)=cur;

			MMGC_DestroyObject(p);
		}
		cur=cur->lnext;
	}
	return(0);
}

int MMGC_ClearMarks()
{
	mem2block *cur;

	cur=used_list;
	while(cur)
	{
		if((cur->flags&MEM2BLOCK_OBJECT) && (cur->flags&MEM2BLOCK_MARK))
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
		if(MM2_GetBlockPtr(*(void **)sp))
			MMGC_MarkObject(*(void **)sp);
		sp++;
	}
	return(0);
}

int MMGC_ScanRange(int *p, int cnt)
{
	int i;
	for(i=0; i<cnt; i++)if(MM2_GetBlockPtr(*(void **)p[i]))
		MMGC_MarkObject(*(void **)p[i]);
	return(0);
}

int MMGC_Collect()
{
	MMGC_MarkAll();
	MMGC_ScanStack();
	MMGC_Sweep();
	MMGC_ClearMarks();
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
		if(cur->flags&MEM2BLOCK_OBJECT)
		{
			objects++;
			objsize+=cur->size;
		}
		cur=cur->lnext;
	}
	kprint("MMGC: %d objects using %dKiB.\n", objects, (objsize+1023)>>10);
	return(0);
}
