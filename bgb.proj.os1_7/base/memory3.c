/*
plans are to implement a simple buddy allocator, the intent is that other
(higher level) memory managers will allocate from this, and this will be
responsible for triggering gc's. thus sub-mm's are to be registered with
this.

older:
blocks will be chained in the free lists, however when allocated the whole
block may be used for data, and all the block handling data will be held in
the block reference, thus the block reference needs to be kept in order to
free a given block.
block references will have the lower 8 bits reserved, of that the upper 18
bits will be the block location (a 16KiB granularity), next down will be 5
bits indicating the block size (with 0 being 4GiB), and 1 bit reserved.

I can't really seem to use this in userspace as it is alignment dependant...
idea will be to emulate for userspace, and use this on real kernels...

rewrote:
made to work in userspace but really a messier desgin. it makes use of a node
tree to manage space.
references will be pointers or possibly locatives (though these may be provided
by an external interface...). if this used mapping then it could be considered
possible to use a space larger than physical ram, however at present this is
not mapping so blocks will have to exist in ram...

idea: maybe use zero pages for uninitialized/mapped pages, these will be read
only so trying to write to them will force them to be coppied. in this way all
the zero pages can be the same page. asking that unused data be zeroed then it
would be possible to scan over memory and compress zero pages...

*/

#include <general.h>
//#include <x86/page.h>

#define USED	((void *)(-1))

typedef struct MM3_Node_S {
void *data;
struct MM3_Node_S *next, *left, *right; /* left, right: NULL=unused, (void *)(-1)=data */
}MM3_Node;

typedef struct MM3_NodeHead_S {
MM3_Node *data;
struct MM3_NodeHead_S *next;
int nodes, resv;
}MM3_NodeHead;

/* node sizes refer to the child blocks, and not the total data of the node... */
MM3_Node *mm3_node_list[23];	//0: 4G 2G 1G 512M		4: 256M 128M 64M 32M
								//8: 16M 8M 4M 2M		12: 1M 512K 256K 128K 
								//16: 64K 32K 16K 8K	20: 4K 2K 1K
MM3_NodeHead *mm3_headroot;
int mm3_freenodes, mm3_noallocnodes;

static MM3_NodeHead nhbuf[64];

extern int mem_pages;

MM3_Node *MM3_AllocNode();
void *MM3_PAllocBlock(int size);

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

int MM3_Init()
{
	MM3_Node *tmp;
	int sz;

	memset(&nhbuf, 0, 1024);
	mm3_headroot=(MM3_NodeHead *)&nhbuf;
	mm3_headroot->data=(MM3_Node *)(mm3_headroot+1);
	mm3_headroot->next=NULL;
	mm3_headroot->nodes=63;
	mm3_freenodes=63;

	tmp=MM3_AllocNode();
	if(!sys_isbooted())
	{
		tmp->data=(void *)malloc(16<<20);
		mm3_node_list[9]=tmp;
	}else
	{
		/* data at 32MiB mark at 2 16MiB pages */
		sz=log2up(mem_pages<<11);
//		tmp->data=(void *)0x1000000;
//		mm3_node_list[8]=tmp;
		tmp->data=(void *)(1<<sz);
		mm3_node_list[33-sz]=tmp;
	}
	return(0);
}

int MM3_AllocMoreNodes()
{
	MM3_NodeHead *tmp;

	if(mm3_noallocnodes)return(0);
	mm3_noallocnodes=1;

	tmp=MM3_PAllocBlock(20);
	tmp->next=mm3_headroot;
	mm3_headroot=tmp;

	mm3_noallocnodes=0;

	tmp->data=(MM3_Node *)(tmp+1);
	tmp->nodes=255;
	mm3_freenodes+=255;

	return(-1);
}

MM3_Node *MM3_AllocNode()
{
	MM3_NodeHead *head;
	int i;

	if(mm3_freenodes<32)MM3_AllocMoreNodes();

	head=mm3_headroot;
	while(head)
	{
		for(i=0; i<head->nodes; i++)
			if(!head->data[i].data)
		{
			head->data[i].next=NULL;
			head->data[i].left=NULL;
			head->data[i].right=NULL;

			mm3_freenodes--;

			return(&head->data[i]);
		}
		head=head->next;
	}
	return(NULL);
}

int MM3_SplitBlock(int size)
{
	MM3_Node *cur;

//	kprint("MM3_SplitBlock, size=%d\n", size);

	if(mm3_node_list[size])
	{
		cur=mm3_node_list[size];
		while(cur)
		{
			if(!cur->left)
			{
				cur->left=USED; /* protect in case node blocks created */
				cur->left=MM3_AllocNode();
				cur->left->data=cur->data;
				cur->left->next=mm3_node_list[size+1];
				mm3_node_list[size+1]=cur->left;
				return(-1);
			}
			if(!cur->right)
			{
				cur->right=USED;
				cur->right=MM3_AllocNode();
				cur->right->data=cur->data+(1<<(32-size));
				cur->right->next=mm3_node_list[size+1];
				mm3_node_list[size+1]=cur->right;
				return(-1);
			}
			cur=cur->next;
		}
	}
	if(size>0)if(MM3_SplitBlock(size-1))return(MM3_SplitBlock(size));
	return(0);
}

void *MM3_PAllocBlock(int size)
{
	MM3_Node *cur;

//	kprint("MM3_PAlloc, size=%d\n", size);

	if(mm3_node_list[size])
	{
		cur=mm3_node_list[size];
		while(cur)
		{
			if(!cur->left)
			{
				cur->left=USED;
				return(cur->data);
			}
			if(!cur->right)
			{
				cur->right=USED;
				return(cur->data+(1<<(32-size)));
			}
			cur=cur->next;
		}
	}
	if(size>0)if(MM3_SplitBlock(size-1))return(MM3_PAllocBlock(size));
	return(NULL);
}

/* free node if parent can be allocated and node cleared */
int MM3_FreeNode(MM3_Node *node, int size)
{
	MM3_Node *cur;
	cur=mm3_node_list[size-1];
	while(cur)
	{
		if(cur->left==node)
		{
			cur->left=NULL;
			node->data=NULL;
			mm3_freenodes++;
			return(-1);
		}
		if(cur->right==node)
		{
			cur->right=NULL;
			node->data=NULL;
			mm3_freenodes++;
			return(-1);
		}
		cur=cur->next;
	}
	return(0);
}

int MM3_PFreeBlock(void *block)
{
	MM3_Node *cur, *prev;
	int i, ec;

	ec=0;
	for(i=0; i<23; i++)
	{
		prev=NULL;
		cur=mm3_node_list[i];
		while(cur)
		{
			if((cur->left==USED) && (cur->data==block))
			{
				cur->left=NULL;
				ec=1;
			}
			if((cur->right==USED) && ((cur->data+(1<<(32-i)))==block))
			{
				cur->right=NULL;
				ec=1;
			}
			if((cur->left==NULL) && (cur->right==NULL))
				if(MM3_FreeNode(cur, i))
				if(prev)prev->next=cur->next;
					else mm3_node_list[i]=cur->next;

			if(ec)return(-1);
			prev=cur;
			cur=cur->next;
		}
	}
	return(0);
}

void *MM3_AllocBlock(int size)
{
	int sz;
	void *p;

	sz=32-log2up(size);
//	kprint("sz=%d\n", size);
	if(sz>=23)return(NULL);
	p=MM3_PAllocBlock(sz);
	return(p);
}

int MM3_Print()
{
	MM3_Node *cur;
	int i, nc, cnc, ubc, fbc, usc, fsc;

	usc=0;
	fsc=0;
	for(i=0; i<23; i++)if(mm3_node_list[i])
	{
		ubc=0;
		fbc=0;
		nc=0;
		cnc=0;
		cur=mm3_node_list[i];
		while(cur)
		{
			if(cur->left==NULL)fbc++;
				else if(cur->left==USED)ubc++;
				else cnc++;
			if(cur->right==NULL)fbc++;
				else if(cur->right==USED)ubc++;
				else cnc++;
			nc++;
			cur=cur->next;
		}
		usc+=ubc<<(32-i);
		fsc+=fbc<<(32-i);
		kprint("%d node(s), %d child(ren), blocks are %dKiB, %d block(s) used, %d free\n",
			nc, cnc, 1<<(22-i), ubc, fbc);
	}
	kprint("%dKiB used, %dKiB free\n", usc>>10, fsc>>10);
}



#if 0

void *mm3_free_list[18]; //0: 4G 2G 1G 512M 4: 256M 128M 64M 32M 8: 16M 8M 4M 2M 12: 1M 512K 256K 128K 16: 64K 32K 16K

void *MM3_PAllocBlock(int size)
{
	void *t;
	if(mm3_free_list[size])
	{
		t=mm3_free_list[size];
		mm3_free_list[size]=*(void **)t;
		return(t);
	}else if(size>0)
	{
		t=MM3_PAllocBlock(size-1);
		if(!t)return(NULL);

		mm3_free_list[size]=t+(1<<(32-size));
		*(void **)mm3_free_list[size]=NULL;
		return(t);
	}
	return(NULL);
}

int MM3_BlockInList(void *block, void *list)
{
	while(list)
	{
		if(list==block)return(-1);
		list=*(void **)list;
	}
	return(0);
}

int MM3_PFreeBlock(void *block, int size)
{
	void *t;

	/* determine if buddy is also free */
	t=(void *)((unsigned int)block^(1<<(32-size)));
	if(MM3_BlockInList(t, mm3_free_list[size]))
	{
		/* if so merge and add up the list */
		t=(void *)((unsigned int)block&(~(1<<(32-size))));
		*(void **)t=mm3_free_list[size-1];
		mm3_free_list[size-1]=t;
		return(0);
	}

	/* otherwise free normally */
	*(void **)block=mm3_free_list[size];
	mm3_free_list[size]=block;
	return(0);
}

int MM3_PRemoveBlock(void *ptr, int size)
{
	void *t, *lst;

	/* see if on free list */
	if(MM3_BlockInList(ptr, mm3_free_list[size]))
	{
		/* if so then remove */
		if(mm3_free_list[size]!=ptr)
		{
			lst=mm3_free_list[size];
			while(lst)
			{
				if(*(void **)lst==ptr)
				{
					*(void **)lst=*(void **)ptr;
					return(0);
				}
				lst=*(void **)lst;
			}
		}else mm3_free_list[size]=*(void **)t;
	}else
	{
		/* otherwise try to remove parent */
		t=(void *)((unsigned int)ptr&(~(1<<(32-size))));
		if(!MM3_PRemoveBlock(t, size-1))
		{
			/* if was able to remove parent of this block, then re-add buddy */
			t=(void *)((unsigned int)ptr^(1<<(32-size)));
			MM3_PFreeBlock(t, size);
			return(0);
		}
	}
	/* couldn't remove, ie: not in free lists */
	return(-1);
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

/* secret adgenda: reference encoding was really a plan to use interpreter values... */
elem MM3_AllocBlock(int size)
{
	int sz;
	void *p;

	sz=32-log2up(size);
	if(sz>=18)return(MISC_NULL);
	p=MM3_PAllocBlock(sz);
	return((elem)p| (sz<<9)| MISCT_MEMBLOCK);
}

int MM3_FreeBlock(elem ref)
{
	void *p;
	int sz;

	p=(void *)(ref&(~0x3FFF));
	sz=(ref>>9)&31;
	return(MM3_PFreeBlock(p, sz));
}

int MM3_Print()
{
	int i, j;
	void *p;

	for(i=0; i<18; i++)if(mm3_free_list[i])
	{
		j=0;
		p=mm3_free_list[i];
		while(p)
		{
			j++;
			p=*(void **)p;
		}
		kprint("%d block(s) of %dKiB\n", j, 1<<(22-i));
	}
	return(0);
}

int MM3_Init()
{
	int i;

	kprint("MM3 Init.\n");
//	kprint("%d\n", log2up((1<<16)));

	for(i=0; i<18; i++)mm3_free_list[i]=NULL;
//#ifndef X86_BOOT
//	mm3_free_list[10]=malloc(4<<20);
//	memset(mm3_free_list[10], 0, 4);
//#endif
}

#endif
