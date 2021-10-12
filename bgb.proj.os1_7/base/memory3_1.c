/*
this will be intended to be a new mm.

current plan: a roving bitmap allocator. this will make use of the "chunk",
which will have a fixed size bitmap and data area.

this will maintain a sorted chunks list, which will have the oldest and most
touched (not including current chunk) lists at the front, these will be the
heighest cannidates for gc.

this will be a precise gc, which will specifically work on tagged references.

misc: make mark/sweep or copy collector?
idea for copy: I can choose some of the "most stable" chunks, and evacuate the contents
of the chunk being collected into that one. the chunk will still be viewed as
stable, new stable chunks will be grabbed if the first fills.

once a chunk is evacuated it will be put on the free chunk list. when a chunk is
filled it will be placed on the list of chunks, and a new chunk will be grabbed
from the free list (triggering an evacuation of the most unstable chunk).

problem with copy: have to be able to effectively locate references to an object.

bitmap: 4bits/cell: 2 mark, 2 type.
0=free
1=cons
2=obj head
3=body

map includes head, mapsize=size>>4, with the first (mapsize>>3)+(headsize>>3) set to 3.

possibility2:
precise chunk/cell based mark/sweep collector.
this will have chunks, similarly sorted by stability. the most "unstable" chunks
will be collected first, then the stability level will be increased.
choosing a new chunk for allocations will be based on the occupancy of the chunk,
the most empty chunks will be chosen, or a new chunk will be created if the most
empty chunk contains more than a certain amount (after trying to gc).

2002-10-21:
just use general precise mark/sweep for now.
hitting end of chunk list triggers a new chunk, gc, and jump to start of list.

mark colors:
0(0)=white
1(4)=grey
2(8)=black
- 3(c)=extra black (escapes 1 gc pass, clear marks sets black).

2002-10-25:
idea: attempt a limited store. currently work on swizzling out chunks.
next try to swizzle in chunks, and work on symbolically referring to in memory structures/store exports.
references could be stored relative to the start of the store image, thus allowing the image to be up to 4GiB.
currently use low 12 bits of flags for store chunk, and work by conceptually "mapping out" the chunks. any chunk not yet
mapped is mapped when the referring chunk is being stored. a bitmap could be maintained in chunk 0 to identify
the state of various chunks in the image, this could use 4 bit fields, even though little information needs to be storred
right now.

2002-10-30:
considering moving map to end of chunk. had written lots of hand notes relating to store structure...

2003-01-05:
use color 3 as conservative black.
considering adding spans and using these (instead of directly using the bitmap) for allocation. may add (as noted)
conservative collection and may thus try to make this main mm.
 */

#include <general.h>

mem3chunk *mmgc3_usedchunks;
mem3chunk *mmgc3_freechunks;

mem3chunk *mmgc3_conschunk;

mem3bigobj *mmgc3_bigobjs;

int mmgc3_used, mmgc3_total, mmgc3_free, mmgc3_freed;
int mmgc3_trigger, mmgc3_lastgc;

elem *mmgc3_root[GCROOTS];
char *mmgc3_rootname[GCROOTS];

elem *mmgc3_markstack;
int mmgc3_markpos;

extern int __data_start, __bss_start, _end;

kmutex *mmgc3_lock;

int MMGC3_ChunkGetEnt(mem3chunk *chk, int ent)
{
	byte *map;
	int size, mapsize;

	size=1<<(chk->size_rover>>27);
	mapsize=size>>4;
	map=((byte *)chk)+(size-mapsize);
//	map=(byte *)(chk+1);

	return((ent&1)?(map[ent>>1]&15):(map[ent>>1]>>4));
}

int MMGC3_ChunkSetEnt(mem3chunk *chk, int ent, int val)
{
	byte *map;
	int size, mapsize;

	size=1<<(chk->size_rover>>27);
	mapsize=size>>4;
	map=((byte *)chk)+(size-mapsize);
//	map=(byte *)(chk+1);

//	if((MMGC3_ChunkGetEnt(chk, ent)&3) && ((MMGC3_ChunkGetEnt(chk, ent)&3)!=(val&3)) && (val&3))
//		sa_print("MMGC3: pedantic set error %d %d.\n", MMGC3_ChunkGetEnt(chk, ent), val);

	if(ent&1)
		map[ent>>1]=(map[ent>>1]&0xF0)+val;
		else map[ent>>1]=(map[ent>>1]&0x0F)+(val<<4);
	return(0);
}

elem MMGC3_Cons()
{
//	mem3chunk *cur;
	int cells, i, j;
	elem tmp;
	byte *map;
	int size, mapsize;


	if(mmgc3_lock)kmutex_lock(mmgc3_lock);

	if(!mmgc3_conschunk)
	{
		mmgc3_conschunk=MMGC3_NewChunk(MINCHKSZ);
		mmgc3_conschunk->next=mmgc3_usedchunks;
		mmgc3_usedchunks=mmgc3_conschunk;
	}

//	cells=(mmgc3_conschunk->size)>>3;
	cells=1<<(((mmgc3_conschunk->size_rover)>>27)-3);
	cells-=cells>>4;

	size=1<<(mmgc3_conschunk->size_rover>>27);
	mapsize=size>>4;
	map=((byte *)mmgc3_conschunk)+(size-mapsize);

//	return((ent&1)?(map[ent>>1]&15):(map[ent>>1]>>4));

	for(i=(mmgc3_conschunk->size_rover&0xfffff); i<cells; i++)
//		if(!MMGC3_ChunkGetEnt(mmgc3_conschunk, i))
		if(!((i&1)?(map[i>>1]&15):(map[i>>1]>>4)))
	{
		mmgc3_conschunk->size_rover&=~0xfffff;
		mmgc3_conschunk->size_rover|=i+1;
		mmgc3_used++;

		MMGC3_ChunkSetEnt(mmgc3_conschunk, i, 1+4); //+0x4
		tmp=(int)mmgc3_conschunk+(i<<3)+TYPE_CONS;

//		cur=MMGC3_LocateChunk(tmp);
//		i=MMGC3_GetIndex(cur, tmp);
//		j=MMGC3_ChunkGetEnt(cur, i);
//		if((j&3)!=1)sa_error("MMGC3_Cons: tag\n");

		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
		return(tmp);
	}

	while(mmgc3_conschunk->next)
	{
		if(!(mmgc3_conschunk->next->flags&MMGC3_NOCONS))break;
		mmgc3_conschunk=mmgc3_conschunk->next;
	}

	if(mmgc3_conschunk->next)
	{
		mmgc3_conschunk=mmgc3_conschunk->next;
		mmgc3_conschunk->size_rover&=0xfff00000;

//		sa_print("chk: %p\n", mmgc3_conschunk);
		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);

		return(MMGC3_Cons());
	}else
	{
		if(!mmgc3_trigger)
		{
			MMGC3_Collect();
			mmgc3_trigger=1;
			mmgc3_conschunk=mmgc3_usedchunks;
			while(mmgc3_conschunk)
			{
				if(!(mmgc3_conschunk->flags&MMGC3_NOCONS))break;
				mmgc3_conschunk=mmgc3_conschunk->next;
			}
			if(mmgc3_conschunk)
			{
				mmgc3_conschunk->size_rover&=0xfff00000;
				if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
				tmp=MMGC3_Cons();
				mmgc3_trigger=0;
				return(tmp);
			}
		}
		mmgc3_trigger=0;
		kprint("MMGC3: chunk\n");

		mmgc3_conschunk=MMGC3_NewChunk(MINCHKSZ);
		mmgc3_conschunk->next=mmgc3_usedchunks;
		mmgc3_usedchunks=mmgc3_conschunk;
		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
		return(MMGC3_Cons());
	}

	if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
	return(MISC_UNDEFINED);
}

elem MMGC3_CObject(int size)
{
//	mem3chunk *cur;
	mem3bigobj *bobj;

	int cells, req, i, j, b;
	elem tmp;

	if(mmgc3_lock)kmutex_lock(mmgc3_lock);

	bobj=MMGC3_BigObj(size);
	if(mmgc3_bigobjs)
	{
		bobj->next=mmgc3_bigobjs;
		mmgc3_bigobjs->prev=bobj;
		mmgc3_bigobjs=bobj;
	}else mmgc3_bigobjs=bobj;

	i=(sizeof(mem3bigobj)+7)&(~7);
	tmp=(int)bobj+i+TYPE_OBJECT;

	if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
	return(tmp);
}

elem MMGC3_Object(int size)
{
//	mem3chunk *cur;
	mem3bigobj *bobj;

	int cells, req, i, j, b;
	elem tmp;
	byte *map;
	int csize, mapsize;

	if(mmgc3_lock)kmutex_lock(mmgc3_lock);

	if(size>16384)
	{
		bobj=MMGC3_BigObj(size);
		if(mmgc3_bigobjs)
		{
			bobj->next=mmgc3_bigobjs;
			mmgc3_bigobjs->prev=bobj;
			mmgc3_bigobjs=bobj;
		}else mmgc3_bigobjs=bobj;

		i=(sizeof(mem3bigobj)+7)&(~7);
		tmp=(int)bobj+i+TYPE_OBJECT;

		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
		return(tmp);
	}

	if(!mmgc3_conschunk)
	{
		mmgc3_conschunk=MMGC3_NewChunk(MINCHKSZ);
		mmgc3_conschunk->next=mmgc3_usedchunks;
		mmgc3_usedchunks=mmgc3_conschunk;
	}

//	cells=(mmgc3_conschunk->size)>>3;
	cells=1<<(((mmgc3_conschunk->size_rover)>>27)-3);
	cells-=cells>>4;
	req=(size+7)>>3;

	csize=1<<(mmgc3_conschunk->size_rover>>27);
	mapsize=csize>>4;
	map=((byte *)mmgc3_conschunk)+(csize-mapsize);

	for(i=(mmgc3_conschunk->size_rover&0xfffff); i<cells; i++)
//		if(!MMGC3_ChunkGetEnt(mmgc3_conschunk, i))
		if(!((i&1)?(map[i>>1]&15):(map[i>>1]>>4)))
	{
//		for(j=0; j<req; j++)if(MMGC3_ChunkGetEnt(mmgc3_conschunk, i+j) || ((i+j)>=cells))break;
		for(j=0; j<req; j++)if((((i+j)&1)?(map[(i+j)>>1]&15):(map[(i+j)>>1]>>4)) || ((i+j)>=cells))break;
		if(j>=req)
		{
			mmgc3_conschunk->size_rover&=~0xfffff;
			mmgc3_conschunk->size_rover|=i+req;
			mmgc3_used+=req;

			MMGC3_ChunkSetEnt(mmgc3_conschunk, i, 2+0x4);
			for(j=1; j<req; j++)MMGC3_ChunkSetEnt(mmgc3_conschunk, i+j, 3+4); //+0x4
//			MMGC3_ChunkSetEnt(mmgc3_conschunk, i, 0);
//			MMGC3_ChunkSetEnt(mmgc3_conschunk, i, 2+0x4);
			tmp=(int)mmgc3_conschunk+(i<<3)+TYPE_OBJECT;

//			cur=MMGC3_LocateChunk(tmp);
//			i=MMGC3_GetIndex(cur, tmp);
//			j=MMGC3_ChunkGetEnt(cur, i);
//			if((j&3)!=2)sa_error("MMGC3_Object: tag\n");

			if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
			return(tmp);
		}else i+=j;
	}

	while(mmgc3_conschunk->next)
	{
		if(!(mmgc3_conschunk->next->flags&MMGC3_NOCONS))break;
		mmgc3_conschunk=mmgc3_conschunk->next;
	}

	if(mmgc3_conschunk->next)
	{
		mmgc3_conschunk=mmgc3_conschunk->next;
		mmgc3_conschunk->size_rover&=0xfff00000;

		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
		return(MMGC3_Object(size));
	}else
	{
		if(!mmgc3_trigger)
		{
			MMGC3_Collect();
			mmgc3_trigger=1;
			mmgc3_conschunk=mmgc3_usedchunks;
			while(mmgc3_conschunk)
			{
				if(!(mmgc3_conschunk->flags&MMGC3_NOCONS))break;
				mmgc3_conschunk=mmgc3_conschunk->next;
			}
			if(mmgc3_conschunk)
			{
				mmgc3_conschunk->size_rover&=0xfff00000;
				if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
				tmp=MMGC3_Object(size);
				mmgc3_trigger=0;
				return(tmp);
			}

//			mmgc3_conschunk->size_rover&=0xfff00000;
//			tmp=MMGC3_Object(size);
//			mmgc3_trigger=0;
//			return(tmp);
		}
		mmgc3_trigger=0;
		kprint("MMGC3: chunk\n");

		mmgc3_conschunk=MMGC3_NewChunk(MINCHKSZ);
		mmgc3_conschunk->next=mmgc3_usedchunks;
		if(mmgc3_usedchunks)mmgc3_usedchunks->prev=mmgc3_conschunk;
		mmgc3_usedchunks=mmgc3_conschunk;
		if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
		return(MMGC3_Object(size));
	}

	if(mmgc3_lock)kmutex_unlock(mmgc3_lock);
	return(MISC_UNDEFINED);
}

mem3chunk *MMGC3_LocateChunk(void *p)
{
	mem3chunk *cur;
	int size;
	cur=mmgc3_usedchunks;
	while(cur)
	{
		size=1<<((cur->size_rover)>>27);
		size-=size>>4;	//remove bitmap

		if((p>(void *)cur) && (p<(((void *)cur)+size)))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

int MMGC3_GetIndex(mem3chunk *chk, void *p)
{
	int i;
	i=(int)(p-(void *)chk);
	return(i>>3);
}

elem MMGC3_GetReference(void *p)
{
	mem3chunk *cur;
	int i, j;
	elem tmp;

	cur=MMGC3_LocateChunk(p);
	if(!cur)return(MISC_UNDEFINED);
	i=MMGC3_GetIndex(cur, p);
	j=MMGC3_ChunkGetEnt(cur, i);

	while(((j&3)==3) && (i>=0))		//in the case of conservative objs reference may be into object body...
	{
		i--;
		j=MMGC3_ChunkGetEnt(cur, i);
	}

	tmp=(int)((elem *)cur+(i<<1))+TYPE_OBJECT;
	return(tmp);
}

void *MMGC3_GetCData(elem t)
{
	elem *s;

	s=(elem *)(t&(~7));
	return(s+2);
}

int MMGC3_Sweep()
{
	mem3chunk *cur;
	int cells, i, j;
	elem *t;

	byte *map;
	int size, mapsize;

//	return((ent&1)?(map[ent>>1]&15):(map[ent>>1]>>4));

	cur=mmgc3_usedchunks;
	while(cur)
	{
		cells=1<<(((cur->size_rover)>>27)-3);
		cells-=cells>>4;

		size=1<<(cur->size_rover>>27);
		mapsize=size>>4;
		map=((byte *)cur)+(size-mapsize);

//		for(i=0; i<cells; i++)if(MMGC3_ChunkGetEnt(cur, i)!=3)break;
		for(i=0; i<cells; i++)if(((i&1)?(map[i>>1]&15):(map[i>>1]>>4))!=3)break;
		for(; i<cells; i++)
		{
//			j=MMGC3_ChunkGetEnt(cur, i);
			j=((i&1)?(map[i>>1]&15):(map[i>>1]>>4));
			if(!(j&0xc) && !(cur->flags&MMGC3_NOCONS))
			{
				if(j)
				{
//					MMGC3_ChunkSetEnt(cur, i, 0);		//release white
					if(i&1)
						map[i>>1]=(map[i>>1]&0xF0);
						else map[i>>1]=(map[i>>1]&0x0F);

					/* EXPENSIVE: clear to make dumps more readable... */
//					t=(elem *)cur+(i<<1);
//					t[0]=0;
//					t[1]=0;

					mmgc3_freed++;
				}else mmgc3_free++;
			}else mmgc3_used++;
			if((j&0xc)==0x4) //MMGC3_ChunkSetEnt(cur, i, j&3);	//grey->white
				if(i&1)
					map[i>>1]=(map[i>>1]&0xF0)+(j&3);
					else map[i>>1]=(map[i>>1]&0x0F)+((j&3)<<4);
			if((j&0xc)==0x8) //MMGC3_ChunkSetEnt(cur, i, j&3);		//black->white
				if(i&1)
					map[i>>1]=(map[i>>1]&0xF0)+(j&3);
					else map[i>>1]=(map[i>>1]&0x0F)+((j&3)<<4);
//			if((j&0xc)==0xc)MMGC3_ChunkSetEnt(cur, i, j&3);	//extra black->white
		}

		mmgc3_total+=1<<((cur->size_rover)>>27);
		cur=cur->next;
	}
}

int MMGC3_TraceElem(elem obj)
{
	mem3chunk *cur;
	int i, j, cells, h;
	elem *t;
	void *p;

	if(((obj&7)!=TYPE_CONS) && ((obj&7)!=TYPE_OBJECT)) //sa_print("MMGC3_TraceElem: questionable.\n");
		return(0);

	p=(void *)(obj&(~7));

	cur=MMGC3_LocateChunk(p);
	if(!cur)return(-1);
	i=MMGC3_GetIndex(cur, p);
	j=MMGC3_ChunkGetEnt(cur, i);
	if((j&0xc)==8)return(0);
	if((j&3)==1)
	{
		t=(elem *)cur+(i<<1);
		MMGC3_TraceElem(t[0]);
		MMGC3_TraceElem(t[1]);
		MMGC3_ChunkSetEnt(cur, i, (j&3)+8);
	}else if((j&3)==2)
	{
		t=(elem *)cur+(i<<1);
//		cells=(cur->size)>>3;
		cells=1<<(((cur->size_rover)>>27)-3);
		cells-=cells>>4;
		h=1;

#if 1
		h=1;
		for(; i<cells; i++)
		{
			j=MMGC3_ChunkGetEnt(cur, i);
			if(((j&3)!=3) && !h)break;
			MMGC3_ChunkSetEnt(cur, i, (j&3)+8);
			h=0;
		}

		switch(t[0]&255)
		{
		case OBJECT_VECTOR:
			if((((t[0]>>8)&255)==VECTOR_ELEMENT) || ((((t[0]>>8)&255)>=32) && (((t[0]>>8)&255)<48)))
			{
				h=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
				for(i=0; i<h; i++)
					MMGC3_TraceElem(t[i+1]);
//					MMGC3_TraceElem(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(i)));
			}
			break;
		default:
//			sa_print("#<obj-type %d>", buf[0]&255);
			break;
		}
#else
		for(; i<cells; i++)
		{
			j=MMGC3_ChunkGetEnt(cur, i);
			if(((j&3)!=3) && !h)break;
			MMGC3_ChunkSetEnt(cur, i, (j&3)+8);
			h=0;
			MMGC3_TraceElem(t[0]);
			MMGC3_TraceElem(t[1]);
			t++;
			t++;
		}
#endif
	}else
	{
		kprint("(cell %d %d) ", i, j);
		return(-1);
	}
	return(0);
}

int MMGC3_TraceElemCons(elem obj)
{
	mem3chunk *cur;
	int i, j, cells, h;
	elem *t;
	void *p;

	p=(void *)(obj&(~7));

	cur=MMGC3_LocateChunk(p);
	if(!cur)return(-1);
	i=MMGC3_GetIndex(cur, p);
	j=MMGC3_ChunkGetEnt(cur, i);

	while(((j&3)==3) && (i>=0))		//in the case of conservative objs reference may be into object body...
	{
		i--;
		j=MMGC3_ChunkGetEnt(cur, i);
	}

	if((j&0xc)==0x8)return(0);
	if((j&0xc)==0xc)return(0);
	if((j&3)==1)
	{
		t=(elem *)cur+(i<<1);
//		MMGC3_TraceElem(t[0]);
//		MMGC3_TraceElem(t[1]);
		mmgc3_markstack[mmgc3_markpos++]=t[0];
		mmgc3_markstack[mmgc3_markpos++]=t[1];

		MMGC3_ChunkSetEnt(cur, i, (j&3)+0xc);
	}else if((j&3)==2)
	{
		t=(elem *)cur+(i<<1);
//		cells=(cur->size)>>3;
		cells=1<<(((cur->size_rover)>>27)-3);
		cells-=cells>>4;

		obj=(elem)t+TYPE_OBJECT;

		h=1;
		for(; i<cells; i++)
		{
			j=MMGC3_ChunkGetEnt(cur, i);
			if(((j&3)!=3) && !h)break;
			MMGC3_ChunkSetEnt(cur, i, (j&3)+0xc);
			h=0;
		}

		switch(t[0]&255)
		{
		case OBJECT_VECTOR:
			if((((t[0]>>8)&255)==VECTOR_ELEMENT) || ((((t[0]>>8)&255)>=32) && (((t[0]>>8)&255)<48)))
			{
				h=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
				for(i=0; i<h; i++)
				{
					if((mmgc3_markpos+1)>=GCMARKSTACK)
						sa_fatal("MMGC3_MarkStack: mark stack overflow\n");
					mmgc3_markstack[mmgc3_markpos++]=t[i+1];
//					MMGC3_TraceElem(t[i+1]);
				}
			}
			break;
		case OBJECT_CDATA:
			j=ELEM_TOFIXNUM(t[1]);
			for(i=0; i<(j/ELEM_SZ); i++)
				MMGC3_TraceElemCons(t[i+2]);
			break;
		default:
//			sa_print("#<obj-type %d>", buf[0]&255);
			break;
		}
	}else
	{
//		kprint("(consgc, cell %d %d) ", i, j);
		return(-1);
	}
	return(0);
}

int MMGC3_TraceStack()
{
	mem3chunk *cur;
	int i, j, cells, h;
	elem *t, obj;
	void *p;

//	if(((obj&7)!=TYPE_CONS) && ((obj&7)!=TYPE_OBJECT)) //sa_print("MMGC3_TraceElem: questionable.\n");
//		return(0);

	while(mmgc3_markpos>0)
	{
		mmgc3_markpos--;
		obj=mmgc3_markstack[mmgc3_markpos];
		p=(void *)(obj&(~7));

		if(((obj&7)!=TYPE_CONS) && ((obj&7)!=TYPE_OBJECT))continue;

		cur=MMGC3_LocateChunk(p);
		if(!cur)
		{
			sa_print("nochunk, %p\n", p);
			continue;
		}

		i=MMGC3_GetIndex(cur, p);
		j=MMGC3_ChunkGetEnt(cur, i);
		if((j&0xc)==8)continue;

		if((j&3)==1)
		{
			t=(elem *)cur+(i<<1);
			if((mmgc3_markpos+2)>=GCMARKSTACK)
				sa_fatal("MMGC3_MarkStack: mark stack overflow\n");
			mmgc3_markstack[mmgc3_markpos++]=t[0];
			mmgc3_markstack[mmgc3_markpos++]=t[1];
			MMGC3_ChunkSetEnt(cur, i, (j&3)+8);
		}else if((j&3)==2)
		{
			t=(elem *)cur+(i<<1);
//			cells=(cur->size)>>3;
			cells=1<<(((cur->size_rover)>>27)-3);
			cells-=cells>>4;
			h=1;

			h=1;
			for(; i<cells; i++)
			{
				j=MMGC3_ChunkGetEnt(cur, i);
				if(((j&3)!=3) && !h)break;
				MMGC3_ChunkSetEnt(cur, i, (j&3)+8);
				h=0;
			}

			switch(t[0]&255)
			{
			case OBJECT_VECTOR:
				if((((t[0]>>8)&255)==VECTOR_ELEMENT) || ((((t[0]>>8)&255)>=32) && (((t[0]>>8)&255)<48)))
				{
					h=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
					for(i=0; i<h; i++)
						if((mmgc3_markpos+1)>=GCMARKSTACK)
							sa_fatal("MMGC3_MarkStack: mark stack overflow\n");
							else mmgc3_markstack[mmgc3_markpos++]=t[i+1];
//						MMGC3_TraceElem(TyFcn_VectorRef(obj, ELEM_FROMFIXNUM(i)));
				}
				break;
			case OBJECT_CDATA:
				j=ELEM_TOFIXNUM(t[1]);
				for(i=0; i<(j/ELEM_SZ); i++)
					MMGC3_TraceElemCons(t[i+2]);
				break;
			default:
//				sa_print("#<obj-type %d>", buf[0]&255);
				break;
			}
		}else
		{
			kprint("(cell %d %d) ", i, j);
//			return(-1);
		}
	}
	return(0);
}

int MMGC3_TraceRoots()
{
	elem t;
	int i;
	mmgc3_markpos=0;

	for(i=0; i<GCROOTS; i++)if(mmgc3_root[i])
	{
//		MMGC3_TraceElem(*mmgc3_root[i]);
		if((mmgc3_markpos+1)>=GCMARKSTACK)
			sa_fatal("MMGC3_MarkStack: mark stack overflow\n");
		t=*mmgc3_root[i];
		mmgc3_markstack[mmgc3_markpos++]=t;
	}
}

int MMGC3_ScanRange(int *p, int cnt)
{
	int i;
	for(i=0; i<cnt; i++)
		MMGC3_TraceElemCons((void *)p[i]);
	return(0);
}

int MMGC3_ScanStacks()
{
	kthread *cur;
	cur=rthread_list;
	while(cur)
	{
//		kprint("%X %X\n", cur->stacktop, cur->stackbottom);
		MMGC3_ScanRange(cur->stackbottom, ((int)cur->stacktop - (int)cur->stackbottom)/4);
		cur=cur->rnext;
	}
}

int MMGC3_Collect()
{
	int t, s;

//	return(0);

	mmgc3_used=0;
	mmgc3_free=0;
	mmgc3_freed=0;
	mmgc3_total=0;

	t=Sys_TimeMS();
//	MMGC3_ClearMarks();

	MMGC3_TraceRoots();
	MMGC3_ScanStacks();
//	MMGC3_ScanRange(&__data_start, ((int)&__bss_start-(int)&__data_start)/sizeof(void *));
//	MMGC3_ScanRange(&__bss_start, ((int)&_end-(int)&__bss_start)/sizeof(void *));

	MMGC3_TraceStack();
	MMGC3_Sweep();

//	MMGC3_TraceRoots();
//	MMGC3_Sweep();
	s=mmgc3_used+mmgc3_free+mmgc3_freed;
	kprint("\tused:%d free:%d+%d totals:%d=%d took:%dms last:%dms\n", mmgc3_used<<3, mmgc3_free<<3, mmgc3_freed<<3, s<<3, mmgc3_total,
		Sys_TimeMS()-t, t-mmgc3_lastgc);
	mmgc3_lastgc=t;

//	MMGC3_StoreAll();
}

int MMGC3_AddRoot(elem *p)
{
	int i;
	for(i=0; i<GCROOTS; i++)if(!mmgc3_root[i])
	{
		mmgc3_root[i]=p;
		mmgc3_rootname[i]=NULL;
		return(i);
	}
	kprint("MMGC3: no free roots.\n");
	return(-1);
}

int MMGC3_AddNamedRoot(elem *p, char *n)
{
	int i;
	for(i=0; i<GCROOTS; i++)if(!mmgc3_root[i])
	{
		mmgc3_root[i]=p;
		mmgc3_rootname[i]=n;
		return(i);
	}
	kprint("MMGC3: no free roots.\n");
	return(-1);
}

int MMGC3_SetNamedRoot(char *n, elem v)
{
	int i;
	for(i=0; i<GCROOTS; i++)if(mmgc3_rootname[i])
	{
		kprint("\"%s\" \"%s\"\n", n, mmgc3_rootname[i]);
		if(!strcmp(n, mmgc3_rootname[i]))
		{
			*mmgc3_root[i]=v;
			return(i);
		}
	}
	kprint("MMGC3: root \"%s\" not found.\n", n);
	return(-1);
}

int MMGC3_Used()
{
	return(mmgc3_used<<3);
}

int MMGC3_Total()
{
	return(mmgc3_total);
}

//void *KPFH_BasicMMap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)


int MMGC3_Init()
{
	int i;

	kprint("MMGC3_Init\n");

//	kprint("%X %X\n", &__bss_start, &_end);

	mmgc3_usedchunks=NULL;
	mmgc3_freechunks=NULL;
	mmgc3_conschunk=NULL;
	mmgc3_used=0;
	memset(mmgc3_root, 0, GCROOTS*sizeof(elem *));
	memset(mmgc3_rootname, 0, GCROOTS*sizeof(char *));

	i=8192/256; //8MiB initial
//	i=65536/256; //64MiB initial
//	i=262144/256; //64MiB initial

	while(i--)
	{
		mmgc3_conschunk=MMGC3_NewChunk(MINCHKSZ);
		mmgc3_conschunk->next=mmgc3_usedchunks;
		mmgc3_usedchunks=mmgc3_conschunk;
	}

//	mmgc3_markstack=kalloc(GCMARKSTACK*ELEM_SZ);
//	mmgc3_markstack=KPFH_BasicMMap(NULL, GCMARKSTACK*ELEM_SZ, KPROT_READ|KPROT_WRITE, 0, NULL, 0);
	mmgc3_markstack=KPFH_Alloc(GCMARKSTACK*ELEM_SZ);

	if(mmgc3_markstack==((elem *)-1))panic("mark stack alloc failed.\n");
	if(!mmgc3_markstack)panic("mark stack alloc failed.\n");
	mmgc3_markpos=0;

	MMGC3_InitStore();

//	mmgc3_lock=kmutex_new();
}
