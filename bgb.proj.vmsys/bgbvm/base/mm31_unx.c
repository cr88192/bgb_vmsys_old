/*
low level and store bits of memory3_1.

chunks 0/1 are reserved for chunk header.
this involves:
map; string table; and all inward/outward references.

strings will be allowed a compact representation, packed end to end in the table.
these will have the pascal style encoding.
these may be indexed by longrefs with the lowest addr bit 1.
the first byte will indicate the string type:
Sname, symbol
Iname, import (name)
X<ref>name, export, ref is a reference to the exported object

strings with a length of 0 will be a null string, string 0 is such a string.
a null string is also used to terminate the string table.

2002-11-09:
lower 12 bits of flags to be used as chunk index.
next 12 currently reserved.
upper 8 are flags.

 */
#include <general.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

byte *mmgc3_storemap;
int mmgc3_storesize;
VFILE *mmgc3_storeimg;

char **mmgc3_boundnames;
void **mmgc3_boundaddrs;

int *mmgc3_boundstpos;
int mmgc3_boundstend;
char *mmgc3_boundstrtab;


mem3chunk *MMGC3_NewChunk(int size)
{
	mem3chunk *tmp;

	int mapsize, ms2, i;

	if(size<MINCHKSZ)size=MINCHKSZ;
	size=1<<log2up(size);

//	sa_print("%d\n", log2up(size));

	tmp=malloc(size);
	memset(tmp, 0, size);
	tmp->size_rover=log2up(size)<<27;

	mapsize=size>>4;
//	ms2=(mapsize>>3)+(sizeof(mem3chunk)>>3);
	ms2=(sizeof(mem3chunk)+7)>>3;
	for(i=0; i<ms2; i++)MMGC3_ChunkSetEnt(tmp, i, 3);

	return(tmp);
}

mem3bigobj *MMGC3_BigObj(int size)
{
	mem3bigobj *tmp;

	int i, j;

//	if(size<MINCHKSZ)size=MINCHKSZ;
//	size=1<<log2up(size);

	size=((sizeof(mem3bigobj)+7)&(~7))+size;
	size=(size+4095)&(~4095);

//	sa_print("%d\n", log2up(size));

//	tmp=kalloc(size);
//	tmp=(mem3chunk *)(Address_AllocRegion(0, size>>PAGE_SHIFT)<<12);
	tmp=malloc(size);

	memset(tmp, 0, size);
	tmp->size=size;

	return(tmp);
}


#if 0

static void MMGC3_PerPage_HandleSIGSEGV(int sig, siginfo_t *inf, void *data)
{
	int page, stat, spage, schk, size, mapsize;
	mem3chunk *chk;
	byte *map;

	if(inf->si_code==SEGV_ACCERR)
	{
		page=(int)inf->si_addr&(~(GCPAGESIZE-1));
		fprintf(stderr, "try handle %p.\n", page);
//		if(!Swizzler_LoadPage((void *)page))return;

		chk=
			(mem3chunk *)MMGC3_LocateChunk(
			(void *)page);
//			NULL;

		if(!chk)
		{
			kprint("SIGSEGV: no chunk.\n");
			abort();
		}

//		mprotect((void *)page, GCPAGESIZE, PROT_READ|PROT_WRITE|PROT_EXEC);

		spage=(page-(int)chk)/GCPAGESIZE;
		schk=chk->flags&0xfff;

		size=1<<(chk->size_rover>>27);
		mapsize=size>>4;
		map=(byte *)chk+(size-mapsize);

		MMGC3_LoadPage(chk, spage);
/*
		vfseek(mmgc3_storeimg, (schk<<18)+(spage<<12), 0);
		vfread((void *)page, 1, 4096, mmgc3_storeimg);
*/

//		Store_ReadInPage(page, 0);

		kprint("ok.\n");

		return;
	}
	fprintf(stderr, "SIGSEGV %08X\n", inf->si_addr);
	abort();
}

#endif

#if 1
mem3chunk *MMGC3_LoadChunk(int num)
{
	mem3chunk *cur, *data;
	byte *map;
	int mapsize, i;

	cur=mmgc3_usedchunks;
	while(cur)
	{
		if((cur->flags&0xfff)==num)return(cur);
		cur=cur->next;
	}

	if(!MMGC3_MapGetEnt(mmgc3_storemap, num))
	{
		kprint("MMGC3_LoadChunk, invalid chunk %d.\n", num);
		return(NULL);
	}

#if 1
	cur=malloc(MINCHKSZ);
	kprint("MMGC3_LoadChunk, %d %X.\n", num, cur);

//	mprotect(cur, MINCHKSZ, PROT_READ|PROT_WRITE|PROT_EXEC);
	vfseek(mmgc3_storeimg, num<<18, 0);
	vfread(cur, 1, MINCHKSZ, mmgc3_storeimg);
	mapsize=1<<18;
	mapsize-=mapsize>>4;

	data=mmgc3_usedchunks;

	cur->prev=NULL;
//	cur->flags=(cur->flags&(~0xfff))|num;

	cur->flags|=MMGC3_NOCONS; //don't want allocation happening into persistent chunks...

	cur->next=data;
	if(data)data->prev=cur;
	mmgc3_usedchunks=cur;
//	cur->size_rover=18<<27;

//	MMGC3_LoadPage(cur, 0);

//	cur->size_rover=18<<27;

//	cur->prev=NULL;
//	cur->flags=(cur->flags&(~0xfff))|num|MMGC3_NOCONS;
//	cur->next=data;

	for(i=0; i<(mapsize>>12); i++)MMGC3_LoadPage(cur, i);

	return(cur);
#else

	cur=mmap(NULL, MINCHKSZ, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	kprint("MMGC3_LoadChunk, %p.\n", cur);

//	mprotect(cur, GCPAGESIZE, PROT_READ|PROT_WRITE|PROT_EXEC);
	mapsize=1<<(18-4);
//	mprotect(cur, mapsize, PROT_READ|PROT_WRITE|PROT_EXEC);

	mprotect(cur, GCPAGESIZE, PROT_READ|PROT_WRITE|PROT_EXEC);
	vfseek(mmgc3_storeimg, num<<18, 0);
	vfread(cur, 1, GCPAGESIZE, mmgc3_storeimg);

	map=(void *)cur+(MINCHKSZ-mapsize);
	mprotect(map, mapsize, PROT_READ|PROT_WRITE|PROT_EXEC);
	vfseek(mmgc3_storeimg, (num<<18)+(MINCHKSZ-mapsize), 0);
	vfread(map, 1, mapsize, mmgc3_storeimg);

	data=mmgc3_usedchunks;

	cur->prev=NULL;
	cur->flags=(cur->flags&(~0xfff))|num;
	cur->next=data;
	if(data)data->prev=cur;
	mmgc3_usedchunks=cur;
	cur->size_rover=18<<27;

	MMGC3_LoadPage(cur, 0);

	cur->prev=NULL;
	cur->flags=(cur->flags&(~0xfff))|num;
	cur->next=data;

	cur->size_rover=18<<27;

	kprint("MMGC3_LoadChunk: OK\n");

	return(cur);
#endif
}
#endif

int MMGC3_InitStore2()
{
//	struct sigaction sa;

//	sa.sa_sigaction=&MMGC3_PerPage_HandleSIGSEGV;
//	sa.sa_flags=SA_SIGINFO;
//	sigaction(SIGSEGV, &sa, NULL);
}
