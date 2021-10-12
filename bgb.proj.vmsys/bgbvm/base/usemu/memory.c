#include <general.h>

memblock *memroot;
memheap *memheaproot;

memheap *memrheap; /* fast, temporary starage */

int MM_Init()
{
	memroot=NULL;
	memheaproot=NULL;
	MM2_Init();
}

memblock *MM_NewBlock(int size)
{
	memblock *tmp;
	int mbs;

	if(size)
	{
		size+=sizeof(memblock);
		size=(size+15)&(~15);
		size=size>MEM_BLOCKSIZE?size:MEM_BLOCKSIZE;
	}else size=MEM_BLOCKSIZE;

	mbs=(sizeof(memblock)+7)&(~7);
	tmp=malloc(size);
	memset(tmp, 0, size);
	tmp->data=(void *)((int)tmp+mbs);
	tmp->size=size-mbs;

	tmp->next=memroot;
	memroot=tmp;
	return(tmp);
}

memalloc *MM_Alloc(int size)
{
	memblock *p_block;
	int p_offs, p_size;

	memblock *bcur;
	memalloc *acur, *atmp;
	int j, rsize;

	rsize=size;

	size+=sizeof(memalloc);
	size=(size+15)&(~15);	/* pad up to 16 bytes for alignment reasons */

	p_block=NULL;
	p_size=MEM_BLOCKSIZE+1;
	p_offs=0;
	
	bcur=memroot;
	while(bcur)
	{
		acur=bcur->first;
		if(acur)
		{
			j=acur->offset;
			if(j>=size && j<p_size)
			{
				p_offs=0;
				p_size=j;
				p_block=bcur;
			}
			while(acur->next)
			{
				if(acur->next->offset<acur->offset)
				{
					printf("MM_Print: out of order allocs.\n");
					return(NULL);
				}
				if(acur->next->offset<(acur->offset+acur->size))
				{
					printf("MM_Print: overlapping allocs.\n");
					return(NULL);
				}

				j=acur->next->offset-(acur->offset+acur->size);
				if(j>=size && j<p_size)
				{
					p_offs=acur->offset+acur->size;
					p_size=j;
					p_block=bcur;
				}
				acur=acur->next;
			}
			j=bcur->size-(acur->offset+acur->size);
			if(j>=size && j<p_size)
			{
				p_offs=acur->offset+acur->size;
				p_size=j;
				p_block=bcur;
			}
		}else
		{
			j=bcur->size;
			if(j>=size && j<p_size)
			{
				p_offs=0;
				p_size=j;
				p_block=bcur;
			}
		}
		bcur=bcur->next;
	}
	if(p_block)
	{
		atmp=(memalloc *)(p_block->data+p_offs);
		atmp->block=p_block;
		atmp->next=NULL;
		atmp->prev=NULL;
		atmp->data=(void *)((int)((p_block->data+p_offs+sizeof(memalloc))+7)&(~7));
		atmp->offset=p_offs;
		atmp->size=size;
		atmp->flags=0;

		p_size=((int)p_block->data+p_offs+size)-(int)atmp->data;
		if(p_size<rsize)
			printf("MM_Alloc: buffer short.\n");

		acur=p_block->first;
		if(!acur)
		{
			p_block->first=atmp;
		}else if(atmp->offset<acur->offset)
		{
			acur->prev=atmp;
			atmp->next=acur;
			p_block->first=atmp;
		}else
		{
//			printf("atmp: %d-%d\n", atmp->offset, atmp->offset+acur->size);
			while(acur->next)
			{
//				printf("acur: %d-%d\n", acur->offset, acur->offset+acur->size);
				if(acur->next->offset>atmp->offset)break;
				acur=acur->next;
			}
//			printf("acur: %d-%d\n", acur->offset, acur->offset+acur->size);
			if(acur->next)acur->next->prev=atmp;
			atmp->prev=acur;
			atmp->next=acur->next;
			acur->next=atmp;
		}
		return(atmp);
	}else
	{
		bcur=MM_NewBlock(size);
		atmp=(memalloc *)((int)bcur->data+p_offs);
		atmp->block=bcur;
		atmp->next=NULL;
		atmp->prev=NULL;
		atmp->data=(void *)(( ((int)bcur->data+sizeof(memalloc))+7)&(~7));
		atmp->offset=0;
		atmp->size=size;
		atmp->flags=0;
		bcur->first=atmp;
		return(atmp);
	}
	return(NULL);
}

int MM_PrintHeaps()
{
	memheap *cur;
	int total1, total2;

	total1=0;
	total2=0;

	cur=memheaproot;
	while(cur)
	{
		printf("MM_Heap: %d total, %d used.\n", cur->blocksize*cur->blocks, cur->total);
		total1+=cur->blocksize*cur->blocks;
		total2+=cur->total;
		cur=cur->next;
	}
	printf("Heaps Use %d bytes, %d data.\n", total1, total2);
}

int MM_Print()
{
	int blocks, totalspace, usedspace, allocs;
	memblock *bcur;
	memalloc *acur;

	MM2_Print();

	blocks=0;
	totalspace=0;
	usedspace=0;
	allocs=0;

	bcur=memroot;
	while(bcur)
	{
		acur=bcur->first;
		while(acur)
		{
			if(acur->next)
			{
				if(acur->next->offset<acur->offset)
					printf("MM_Print: out of order allocs.\n");
				if(acur->next->offset<(acur->offset+acur->size))
					printf("MM_Print: overlapping allocs.\n");
			}
			if((int)acur->data&7)printf("MM_Print: unaligned alloc.\n");
			usedspace+=acur->size;
			allocs++;
			acur=acur->next;
		}
		blocks++;
		totalspace+=bcur->size;
		bcur=bcur->next;
	}
	printf("MM_Print: %d bytes in %d blocks, %d bytes used.\n", totalspace, blocks, usedspace);
	MM_PrintHeaps();
	return(0);
}

int MM_Free(memalloc *m)
{
	if(m->next)m->next->prev=m->prev;
	if(m->prev)m->prev->next=m->next;
		else m->block->first=m->next;
	return(0);
}

void *MM2_PAlloc(int size);

void *MM_PAlloc(int size)
{
	memalloc *tmp, **t2;
	void *data;

//	return(malloc(size));
	return(MM2_PAlloc(size));

	if(size>(MEM_BLOCKSIZE>>2)) /* big allocs go right around MM */
	{
		data=malloc(size+sizeof(memalloc *));
		memset(data, 0, size+sizeof(memalloc *));
		data+=sizeof(memalloc *);
		return(data);
	}

	size+=sizeof(memalloc *);
	tmp=MM_Alloc(size);
	if(!tmp)return(NULL);

	tmp->usecount=1;

	memset(tmp->data, 0, size);
	data=tmp->data;
	t2=(memalloc **)data;
	*t2=tmp;
	data+=sizeof(memalloc *);
	return(data);
}

int MM2_PFree(void *p);

int MM_PFree(void *p)
{
	memalloc *tmp;

//	return(free(p));
	return(MM2_PFree(p));

	return(-1);

	p-=sizeof(memalloc *);
	tmp=*(memalloc **)p;
	if(!tmp)
	{
		free(p);
		return(0);
	}
	MM_Free(tmp);
	return(0);
}

/* allow a simple degree of gc */
int MM_PGrab(void *p)
{
	memalloc *tmp;
	p-=sizeof(memalloc *);
	tmp=*(memalloc **)p;
	if(!tmp)
	{
		free(p);
		return(0);
	}
	tmp->usecount++;
	return(0);
}

int MM_PRelease(void *p)
{
	memalloc *tmp;
	p-=sizeof(memalloc *);
	tmp=*(memalloc **)p;
	if(!tmp)
	{
		free(p);
		return(0);
	}
	tmp->usecount--;
	if(!tmp->usecount)MM_Free(tmp);
	return(0);
}

/* same as MM_PAlloc, exept this may disappear whenever MM_Clean is called */
void *MM_TAlloc(int size)
{
	memalloc *tmp, **t2;
	void *data;

	if(size>(MEM_BLOCKSIZE>>2)) /* big allocs go right around MM */
	{
		data=malloc(size+sizeof(memalloc *));
		memset(data, 0, size+sizeof(memalloc *));
		data+=sizeof(memalloc *);
		return(data);
	}

	size+=sizeof(memalloc *);
	tmp=MM_Alloc(size);
	if(!tmp)return(NULL);
	tmp->flags=1;

	memset(tmp->data, 0, size);
	data=tmp->data;
	t2=(memalloc **)data;
	*t2=tmp;
	data+=sizeof(memalloc *);
	return(data);
}

/* allocates off the "rapid" heap, intended for variables in functions */
void *MM_RAlloc(int size)
{
	if(!memrheap)memrheap=MM_NewHeap(0);
	if(memrheap)return(MM_AllocHeap(memrheap, size));
	
}

int MM_Clean()
{
	memblock *bcur;
	memalloc *acur, *acur2;

	if(memrheap)
	{
		MM_DestroyHeap(memrheap);
		memrheap=MM_NewHeap(0);
	}

	bcur=memroot;
	while(bcur)
	{
		acur=bcur->first;
		while(acur)
		{
			if(acur->next)
			{
				if(acur->next->offset<acur->offset)
					printf("MM_Print: out of order allocs.\n");
				if(acur->next->offset<(acur->offset+acur->size))
					printf("MM_Print: overlapping allocs.\n");
			}
			if((int)acur->data&7)printf("MM_Print: unaligned alloc.\n");

			acur2=acur->next;
			if(acur->flags&1)MM_Free(acur);
			acur=acur2;
		}
		bcur=bcur->next;
	}
}

/* these are used when something will contain a large amount of small data, and when random allocation/freeing is not needed (ie: models) */
memheap *MM_NewHeap(int bsize)
{
	memheap *tmp;

	tmp=MM_PAlloc(sizeof(memheap));
	if(!bsize)bsize=MM_HEAP_DEFBS;
	tmp->blocksize=bsize;
	tmp->first=NULL;

	tmp->next=memheaproot;
	if(memheaproot)memheaproot->prev=tmp;
	memheaproot=tmp;

	return(tmp);
}

void *MM_AllocHeap_fake(memheap *heap, int size)
{
	return(MM_PAlloc(size));
}

void *MM_AllocHeap(memheap *heap, int size)
{
	void *tmp;

	if(!heap->first)
	{
		heap->first=MM_PAlloc(heap->blocksize);
		heap->cur=heap->first;
		heap->used=(sizeof(memheapblock)+7)&(~7);
		heap->blocks++;
	}

	if((heap->used+size+4)>=heap->blocksize) /* make sure will fit */
	{
		if(!heap->cur->next)
			heap->cur->next=MM_PAlloc(heap->blocksize);
		heap->cur=heap->cur->next;
		heap->used=(sizeof(memheapblock)+7)&(~7);
		heap->blocks++;
	}
	tmp=(void *)(((int)heap->cur)+heap->used);
	heap->used+=size;
	heap->used=(heap->used+3)&(~3); /* minimal pad up, make 8 on 64 bit archs */
	heap->total+=size;
	return(tmp);
}

int MM_DestroyHeap(memheap *heap)
{
	memheapblock *cur, *cur2;

	if(heap->next)heap->next->prev=heap->prev;
	if(heap->prev)heap->prev->next=heap->next;
		else memheaproot=heap->next;

	cur=heap->first;
	while(cur)
	{
		cur2=cur->next;
		MM_PFree(cur);
		cur=cur2;
	}

	MM_PFree(heap);
	return(0);
}

/* misc mm related functions */
char *MM_Pstrdup(char *s)
{
	char *t;
	t=MM_PAlloc(strlen(s)+1);
	strcpy(t, s);
	return(t);
}

char *MM_Hstrdup(char *s, memheap *h)
{
	char *t;
	t=MM_AllocHeap(h, strlen(s)+1);
	strcpy(t, s);
	return(t);
}

char *MM_Tstrdup(char *s)
{
	char *t;
	t=MM_TAlloc(strlen(s)+1);
	strcpy(t, s);
	return(t);
}
