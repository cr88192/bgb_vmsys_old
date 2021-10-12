#define MEM_BLOCKSIZE	(1<<20)

typedef struct memblock_s {
struct memblock_s *next;
struct memalloc_s *first;
void *data;
int size;
}memblock;

typedef struct memalloc_s {
struct memalloc_s *next, *prev;
memblock *block;
void *data;
int offset, size; /* offset is start of memalloc, size includes memalloc */
int flags, usecount;
}memalloc;

#define MEMALLOC_FLAG_TEMP	1

#define MM_HEAP_DEFBS	4096

typedef struct memheapraw_s {
struct memheapraw_s *next;
void *data;
int size;
}memheapraw;

typedef struct memheapblock_s {
struct memheapblock_s *next;
}memheapblock;

typedef struct memheap_s {
struct memheap_s *next, *prev;

memheapblock *first, *cur;
int blocksize, used;
int	total, blocks;
}memheap;

int MM_Init();
int MM_Print();
int MM_Clean();

memblock *MM_NewBlock(int size);
memalloc *MM_Alloc(int size);
int MM_Free(memalloc *m);

void *MM_PAlloc(int size);
int MM_PFree(void *p);
int MM_PGrab(void *p);
int MM_PRelease(void *p);
void *MM_TAlloc(int size);
void *MM_RAlloc(int size);

memheap *MM_NewHeap(int bsize);
void *MM_AllocHeap(memheap *heap, int size);
int MM_DestroyHeap(memheap *heap);

char *MM_Pstrdup(char *s);
char *MM_Hstrdup(char *s, memheap *h);
char *MM_Tstrdup(char *s);
