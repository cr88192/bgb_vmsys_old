typedef struct mem2block_s {
struct mem2block_s *lnext, *lprev; /* next in prev in list */
struct mem2block_s *jnext, *jprev; /* next/prev that may be joined with */
int size;
int flags; /* upper 8 bits used for ref count */
}mem2block; /* this structure is directly followed by the data */


#define MEM2BLOCK_USED		1	/* set if in used list, clear otherwise*/
#define MEM2BLOCK_COLLECT	2	/* set if this is collected */
//#define MEM2BLOCK_CELLS		4	/* set if this contains cells */
#define	MEM2BLOCK_NEWCHUNK	4	/* marks the first block in a new chunk, avoids unsafe coalescing */

#define MEM2BLOCK_LOCK		32	/* set if this object is not to be collected/moved */
#define MEM2BLOCK_MARK		64	/* set by gc when marking */
#define MEM2BLOCK_TAGGED	128	/* on destruction look for and invoke matching destructor */

#define MEM2BLOCK_SIZEMASK	0xFFFFFF

extern mem2block *used_list, *free_list;

int MM2_Init();
int MM2_InitLow();
mem2block *MM2_NewBlock(int size);

mem2block *MM2_InsertBlock(mem2block *list, mem2block *block);
mem2block *MM2_UnlinkBlock(mem2block *list, mem2block *block);
mem2block *MM2_SearchFirst(mem2block *list, int size);
int MM2_Split(mem2block *block, int size);
mem2block *MM2_Alloc(int size);
int MM2_Free(mem2block *block);
int MM2_ListSpace(mem2block *list, int fl, int mask);
int MM2_Print();
void *MM2_GetData(mem2block *block, int slot);
mem2block *MM2_AllocCellBlock(int cells);
mem2block *MM2_AllocCells(mem2block *list, int size, int *c);
void *MM2_PAlloc(int size);
int MM2_PFree(void *p);
int MM2_GetSize(void *p);
