#if 0
typedef struct mem2block_s {
struct mem2block_s *next;
int size; /* size lower 24, flags upper 8 */
}mem2block; /* this structure is directly followed by the data */

#define MEM2BLOCK_USED		0x01000000	/* set if in used list, clear otherwise*/
#define MEM2BLOCK_COLLECT	0x02000000	/* set if this is collected */
#define	MEM2BLOCK_NEWCHUNK	0x04000000	/* marks the first block in a new chunk, avoids unsafe coalescing */

#define MEM2BLOCK_MARK		0x80000000	/* set by gc when marking */
#define MEM2BLOCK_SIZEMASK	0x00FFFFFF
#define MEM2BLOCK_FLAGMASK	0xFF000000

#else
typedef struct mem2block_s {
struct mem2block_s *lnext, *lprev; /* next in prev in list */
struct mem2block_s *jnext, *jprev; /* next/prev that may be joined with */
int size;
int flags; /* upper 8 bits used for obj tag */
}mem2block; /* this structure is directly followed by the data */


#define MEM2BLOCK_USED		1	/* set if in used list, clear otherwise*/
#define MEM2BLOCK_COLLECT	2	/* set if this is collected */
//#define MEM2BLOCK_CELLS		4	/* set if this contains cells */
#define	MEM2BLOCK_NEWCHUNK	4	/* marks the first block in a new chunk, avoids unsafe coalescing */

#define MEM2BLOCK_LOCK		32	/* set if this object is not to be collected/moved */
#define MEM2BLOCK_MARK		64	/* set by gc when marking */
#define MEM2BLOCK_TAGGED	128	/* on destruction look for and invoke matching destructor */

#define MEM2BLOCK_UPPER		0x12345600
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
void *MM2_CAlloc(int sz);

void *MM_PAlloc(int size);
int MM_PFree(void *p);
int MM_Print();
int MM_Init();

#endif

int MMGC_Init();
int MMGC_Enter(int (*mainfunc)());

int MM2_GetSize(void *p);
int MMGC_MarkObject(void *p);
int MMGC_AddRoot(void *ptr);
int MMGC_RemoveRoot(void *ptr);
int MMGC_MarkAll();
int MMGC_ScanStack();
int MMGC_ScanRange(int *p, int cnt);
int MMGC_Sweep();
int MMGC_ClearMarks();
int MMGC_Collect();
int MMGC_Print();

int MMGC_AllocTag();
int MMGC_FreeTag(int num);
int MMGC_SetDestructor(int tag, int (*proc)(void *p));
int MMGC_ClearDestructor(int tag);

void *MMGC_PAlloc(int size);
int MMGC_MakeTagged(void *p, int tag);
