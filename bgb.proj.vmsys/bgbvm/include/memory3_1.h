#define MINCHKSZ	(1<<18)
#define GCROOTS		(1<<8)
#define GCMAXBINDS	(1<<12)
#define GCSTSIZE	(1<<16)
#define GCPAGESIZE	(1<<12)

#define GCMARKSTACK	(1<<18)
#define GCCMARKSTACK	(1<<18)

#define GCROOTSTACK	(1<<8)

typedef struct mem3chunk_s {
int size_rover; //upper 5 bits size, lower 27 rover
int flags;	//lower 24 reserved, lower 12 chunk index, upper 8 flags
struct mem3chunk_s *next, *prev;
}mem3chunk;

typedef struct mem3bigobj_s {
int _resv;
int size;
struct mem3bigobj_s *next, *prev;
}mem3bigobj;

#define MMGC3_NOCONS	1<<24
#define MMGC3_EVACUATE	2<<24

mem3chunk *mmgc3_usedchunks;
mem3chunk *mmgc3_freechunks;

mem3chunk *mmgc3_conschunk;

int mmgc3_used, mmgc3_total, mmgc3_free, mmgc3_freed;
int mmgc3_trigger, mmgc3_lastgc;

elem *mmgc3_root[GCROOTS];
char *mmgc3_rootname[GCROOTS];

elem *mmgc3_markstack;
int mmgc3_markpos;

int log2up(int v);
mem3chunk *MMGC3_LocateChunk(void *p);

void *MMGC3_GetCData(elem t);
