/*
2003-08-16:
reused from vmsys. stripping gc and leaving basic mm.
*/

#include <general.h>

int MM2_Init()
{
	kprint("MM2_Init.\n");
	MM2_InitLow();

	return(0);
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
	tmp->flags=0;

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
		tmp->flags|=1<<24;
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
	mem2block *tmp;
	int i;

	used_list=MM2_UnlinkBlock(used_list, block);
	free_list=MM2_InsertBlock(free_list, block);
	block->flags=0;

	while(1)	//coalesce
	{
		tmp=block->jnext;
		if(!tmp)break;		//not present
		if(tmp->flags)break;	//not free

		free_list=MM2_UnlinkBlock(free_list, tmp);

		i=(int)tmp-(int)block;
		i+=tmp->size;

		block->size=i;
		block->jnext=tmp->jnext;
	}

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
	return(0);
}

void *MM2_GetData(mem2block *block, int slot)
{
	void *t;

	t=((void *)block)+sizeof(mem2block);
	return(t);
}

void *MM2_PAlloc(int size)
{
	mem2block *blk;
	int *t;

//	kprint("MM2_PAlloc\n");
	blk=MM2_Alloc(size+sizeof(mem2block *));
	if(!blk)return(NULL);
	t=(int *)MM2_GetData(blk, 0);

	memset(t, 0, size);

//	kprint("MM2_PAlloc: OK\n");
	return(t);
}

int MM2_IncCount(mem2block *block)
{
	int i;

	i=(block->flags>>24)&0xff;
	block->flags&=0xffffff;
	i++;
	if(i>=0xff)i=0xff;
	block->flags|=i<<24;
	return(0);
}

int MM2_DecCount(mem2block *block)
{
	int i;

	i=(block->flags>>24)&0xff;
	if(i==0xff)return(0);

	block->flags&=0xffffff;
	i--;
	block->flags|=i<<24;
	if(i<=0)MM2_Free(block);

	return(0);
}

mem2block *MM2_GetBlockPtr(void *p);

int MM2_PFree(void *p)
{
	mem2block *blk;
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(-1);
	MM2_Free(blk);
	return(0);
}

/* safely get/verify p and return a block if one is a valid match */
mem2block *MM2_GetBlockPtr(void *p)
{
	mem2block *cur;

	cur=used_list;
	while(cur)
	{
		if(((int)p>(int)cur) && ((int)p<((int)cur+cur->size)))
		{
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
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(-1);
	i=blk->size-sizeof(mem2block);
	return(i);
}

void *MM2_GetBase(void *p)
{
	mem2block *blk;
	blk=MM2_GetBlockPtr(p);
	p=MM2_GetData(blk, 0);

	return(p);
}

int MM2_PInc(void *p)
{
	mem2block *blk;
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(-1);
	MM2_IncCount(blk);
	return(0);
}

int MM2_PDec(void *p)
{
	mem2block *blk;
	blk=MM2_GetBlockPtr(p);
	if(!blk)return(-1);
	MM2_DecCount(blk);
	return(0);
}
