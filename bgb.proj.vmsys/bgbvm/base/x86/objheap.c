/* problem here: there are 2 mms, this is good for small objects, other for larger ones */
/* this one will be bound to the gc, the other wont */
/* solution: use a singular mm */
#include <general.h>
#include <x86/page.h>

#define HEAPBASE	0x20000000	/* 512MiB */
#define HEAPLIM		(1<<15)	/* cells, 512MiB in 8B cells */
#define MMOBJ_SHIFT	9	/* there are 512 cells/page */

byte *mmobj_heapmap; /* 4KiB, can map 512MiB */
byte **mmobj_maps;

/* map: 4096 bytes, 32768 bits, 8 bytes cell, 1 map refers 256KiB */
/* each map refers to 64 pages, each page is 64 bytes in map */
/* there are 512 cells/page */

int MMObj_Init()
{
	mmobj_heapmap=(byte *)(Page_Alloc(1)<<12);
	memset(mmobj_heapmap, 0, 4096);
	mmobj_maps=(byte **)(Page_Alloc(1)<<12); /* 1024 maps, each maps 256KiB, only first 512 used */
	memset(mmobj_maps, 0, 4096);
}

int MMObj_NewBlock()
{
	int i, j, k;
	i=BitArray2_AllocBit(mmobj_heapmap, HEAPLIM);
	j=Page_Alloc(1);
	if(i<0)return(-1);
	if(j<0)return(-1);
	k=Address_GetCurrent();
	Address_MapPage(k, (HEAPBASE>>12)+i, j);

	if(!mmobj_maps[i>>6])
	{
		mmobj_maps[i>>6]=(byte *)(Page_Alloc(1)<<12);
		memset(mmobj_maps[i>>6], 0, 4096);
	}

}

int MMObj_AllocWords(int num)
{
	int i, j;
	int small[3], run[2];

	small[0]=0;
	small[2]=0;
	small[1]=num;

	for(i=1; i<16384; i++)if(BitArray2_GetBit(mmobj_heapmap, i))
	{
		run[0]=0;
		run[1]=num;
		j=BitArray2_FindShortestRun(mmobj_maps[i>>6]+((i&63)<<6), 512, run);
		if(!j)
		{
			if(run[1]<small[1])
			{
				small[0]=run[0];
				small[1]=run[0];
				small[2]=i;
			}
		}
	}
	if(small[2])
	{
		BitArray2_SetRun(mmobj_maps[small[2]>>6]+((small[2]&63)<<6), small);
		j=(small[2]<<MMOBJ_SHIFT)+small[0];
		return(j);
	}

	small[0]=0;
	small[1]=num;
	small[2]=MMObj_NewBlock();
	if(!small[2])small[0]++;
	BitArray2_SetRun(mmobj_maps[small[2]>>6]+((small[2]&63)<<6), small);
	j=(small[2]<<MMOBJ_SHIFT)+small[0];
	if(!j)j++;
	return(j);

//	return(0);
}

int MMObj_FreeWords(int start, int len)
{
	int blk, cell[2];

	blk=start>>MMOBJ_SHIFT;
	cell[0]=start&((1<<MMOBJ_SHIFT)-1);
	cell[1]=len;
	BitArray2_ClearRun(mmobj_maps[blk>>6]+((blk&63)<<6), cell);
	return(0);
}

int MMObj_MarkObjectMap(int num)
{
	int blk, pos;

	blk=num>>MMOBJ_SHIFT;
	pos=num&((1<<MMOBJ_SHIFT)-1);
	BitArray2_SetBit(mmobj_maps[blk>>6]+((blk&63)<<6), pos);
	return(0);
}

unsigned long *MMObj_GetWordPointer(int start)
{
//	int blk, pos;

//	blk=start>>MMOBJ_SHIFT;
//	pos=start&((1<<MMOBJ_SHIFT)-1);
//	return(&mmobj_heap[blk][pos]);
	return((unsigned long *)(HEAPBASE+(start<<3)));
}

int MMObj_NewObject(int type, int size)
{
	int i;
	unsigned long *t;

	i=MMObj_AllocWords(((size+3)/4)+1);
	if(!i)
	{
		kprint("couldn't alloc.\n");
		return(0);
	}
	t=MMObj_GetWordPointer(i);
	if(!t)
	{
		kprint("couldn't get pointer.\n");
		return(0);
	}
	*t=type+(size<<8);
	return(i);
}

int MMObj_NewStringS(char *s)
{
	int i, j;
	unsigned long *t;

	i=(strlen(s)+4)>>2;
	j=MMObj_AllocWords(i+1);
	if(!j)
	{
		kprint("couldn't alloc.\n");
		return(0);
	}
	t=MMObj_GetWordPointer(j);
	if(!t)
	{
		kprint("couldn't get pointer.\n");
		return(0);
	}
	*t=OBJ_STRING+(strlen(s)<<8);
	t++;
	strcpy((char *)t, s);

	MMObj_MarkObjectMap(j);

	return(j);
}

char *MMObj_GetString(int num)
{
	unsigned long *t;

	t=MMObj_GetWordPointer(num);
	if((*t&127)!=OBJ_STRING)return(NULL);
	t++;
	return((char *)t);
}

void *MMObj_GetObjPointer(int num, int type)
{
	unsigned long *t;

	t=MMObj_GetWordPointer(num);
	if((*t&127)!=type)return(NULL);
	t++;
	return((char *)t);
}

int MMObj_GetObjType(int num)
{
	unsigned long *t;

	t=MMObj_GetWordPointer(num);
	return(*t&127);
}
