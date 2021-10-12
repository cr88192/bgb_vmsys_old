#include <general.h>

byte *mmgc3_storemap;
int mmgc3_storesize;
VFILE *mmgc3_storeimg;

char **mmgc3_boundnames;
void **mmgc3_boundaddrs;

int *mmgc3_boundstpos;
int mmgc3_boundstend;
char *mmgc3_boundstrtab;

int MMGC3_BindNameAddr(char *name, void *addr)
{
	int i;
	for(i=0; i<GCMAXBINDS; i++)
		if(!mmgc3_boundnames[i])
	{
		mmgc3_boundnames[i]=name;
		mmgc3_boundaddrs[i]=addr;
		return(0);
	}
	sa_error("MMGC3_BindNameAddr: too many binds\n");
	return(-1);
}

char *MMGC3_LookupNameAddr(void *addr)
{
	int i;
	for(i=0; i<GCMAXBINDS; i++)
		if(mmgc3_boundaddrs[i]==addr)
	{
		return(mmgc3_boundnames[i]);
	}
	return(NULL);
}

void *MMGC3_LookupAddrName(char *name)
{
	int i;
	for(i=0; i<GCMAXBINDS; i++)
		if(!strcmp(mmgc3_boundnames[i], name))
	{
		return(mmgc3_boundaddrs[i]);
	}
	return(NULL);
}

int MMGC3_LookupStPosAddr(void *addr)
{
	int i;
	for(i=0; i<GCMAXBINDS; i++)
		if(mmgc3_boundaddrs[i]==addr)
	{
		if(!mmgc3_boundstpos[i])
		{
			mmgc3_boundstpos[i]=mmgc3_boundstend;
			mmgc3_boundstrtab[mmgc3_boundstend++]=strlen(mmgc3_boundnames[i])+1;
			mmgc3_boundstrtab[mmgc3_boundstend++]='I';
			strcpy(mmgc3_boundstrtab+mmgc3_boundstend, mmgc3_boundnames[i]);
			mmgc3_boundstend+=strlen(mmgc3_boundnames[i]);
		}
		return(mmgc3_boundstpos[i]);
	}
	return(0);
}

int MMGC3_LookupStPosSym(elem sym)
{
	int i;
	char *name;

	name=ELEM_TOSYMBOL(sym);

	for(i=0; i<GCMAXBINDS; i++)
		if(mmgc3_boundnames[i])
		if(!strcmp(mmgc3_boundnames[i], name) && !mmgc3_boundaddrs[i] && mmgc3_boundstpos[i])
	{
		return(mmgc3_boundstpos[i]);
	}
	for(i=0; i<GCMAXBINDS; i++)
		if(!mmgc3_boundnames[i])
	{
		mmgc3_boundnames[i]=kstrdup(name);
		mmgc3_boundstpos[i]=mmgc3_boundstend;

		mmgc3_boundstrtab[mmgc3_boundstend++]=strlen(mmgc3_boundnames[i])+1;
		mmgc3_boundstrtab[mmgc3_boundstend++]='S';
		strcpy(mmgc3_boundstrtab+mmgc3_boundstend, mmgc3_boundnames[i]);
		mmgc3_boundstend+=strlen(mmgc3_boundnames[i]);
		return(mmgc3_boundstpos[i]);
	}

	return(0);
}


int log2up(int v)
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

int MMGC3_MapGetEnt(byte *map, int ent)
{
	return((ent&1)?(map[ent>>1]&15):(map[ent>>1]>>4));
}

int MMGC3_MapSetEnt(byte *map, int ent, int val)
{
	if(ent&1)
		map[ent>>1]=(map[ent>>1]&0xF0)+val;
		else map[ent>>1]=(map[ent>>1]&0x0F)+(val<<4);
	return(0);
}

int MMGC3_MapChunk(mem3chunk *chk)
{
	int i;
	if(chk->flags&0xfff)return(chk->flags&0xfff);
	for(i=1; i<mmgc3_storesize; i++)
		if(!MMGC3_MapGetEnt(mmgc3_storemap, i))
	{
		kprint("map chunk %d\n", i);
		MMGC3_MapSetEnt(mmgc3_storemap, i, 1);
		chk->flags|=i;
		MMGC3_StoreChunk(chk);
		return(i);
	}
	return(0);
}

mem3chunk *MMGC3_LocateMappedChunk(elem ref)
{
	mem3chunk *cur;
	int cells, i, j, num;
	elem *t;

	num=ref>>18;

	cur=mmgc3_usedchunks;
	while(cur)
	{
		if((cur->flags&0xfff)==num)
		{
//			kprint("MMGC3_LocateMappedChunk %d.\n", num);
			return(cur);
		}
		cur=cur->next;
	}
	return(NULL);
}

elem MMGC3_SwizRefOut(elem obj)
{
	mem3chunk *cur;
	void *p;
	int i, j;
	elem t;

	if(((obj&7)!=TYPE_CONS) && ((obj&7)!=TYPE_OBJECT))return(obj);

	p=(void *)(obj&(~7));

	cur=MMGC3_LocateChunk(p);
	if(!cur)
	{
		sa_error("MMGC3_SwizRefOut: no chunk (%X \"%04s\").\n", p, &obj);
		return(MISC_UNDEFINED);
	}

	if(ELEM_SYMBOLP(obj))
	{
		i=MMGC3_LookupStPosSym(obj);
		t=(i<<3)+TYPE_LONGREF;
		return(t);
	}

	i=MMGC3_GetIndex(cur, (void *)obj);
	j=MMGC3_MapChunk(cur);
	if(!j)
	{
		kprint("map chunk failed.\n");
	}

//	if(j==2)sa_print("swizout: %d %d\n", j, i);

	t=(j<<18)+(i<<3)+(obj&7);
//	if(j==2)sa_print("swizout: %d %d -> %X\n", j, i, t);
	return(t);
}

elem MMGC3_SwizRefIn(elem obj)
{
	mem3chunk *cur;
	void *p;
	int i, j;
	elem t;
	char *s, *s2;

	if(((obj&7)!=TYPE_CONS) && ((obj&7)!=TYPE_OBJECT) && ((obj&7)!=TYPE_LONGREF))return(obj);

	if((obj&7)==TYPE_LONGREF)
	{
		i=obj>>3;
		s=mmgc3_boundstrtab+i;
		switch(s[1])
		{
		case 'S':
			s2=kralloc(*s);
			memset(s2, 0, *s);
			strncpy(s2, s+2, *s-1);
			t=SYM(s2);
			break;
		case 'I':
			s2=kralloc(*s);
			memset(s2, 0, *s);
			strncpy(s2, s+2, *s-1);
			t=(elem)MMGC3_LookupAddrName(s2);
			break;
		default:
			t=MISC_UNDEFINED;
			break;
		}
		return(t);
	}

	cur=MMGC3_LocateMappedChunk(obj);
	if(!cur)cur=MMGC3_LoadChunk(obj>>18);
	if(!cur)
	{
		sa_error("MMGC3_SwizRefIn: no chunk %d.\n", obj>>18);
		return(MISC_UNDEFINED);
	}

	i=obj&(MINCHKSZ-1);

//	sa_print("MMGC3_SwizRefIn: %X -> %d %d\n", obj, obj>>18, i>>3);
	if(((MMGC3_ChunkGetEnt(cur, i>>3)&3)!=1) && ((MMGC3_ChunkGetEnt(cur, i>>3)&3)!=2))
		sa_print("\tinvalid cell %d (%d %d)\n", MMGC3_ChunkGetEnt(cur, i>>3), obj>>18, i);

	t=((elem)cur)+i;
	return(t);
}

int MMGC3_StoreChunk(mem3chunk *chk)
{
	int cells, i, j, h;
	elem obj, *t, *buf;

	i=MMGC3_MapChunk(chk);

	cells=1<<(((chk->size_rover)>>27)-3);
	cells-=cells>>4;

	buf=kalloc(1<<18);
	memcpy(buf, chk, 1<<18);

	for(i=0; i<cells; i++)if(MMGC3_ChunkGetEnt(chk, i)!=3)break;
	for(; i<cells; i++)
	{
		j=MMGC3_ChunkGetEnt(chk, i);

		if((j&3)==1)
		{
			t=((elem *)chk)+(i<<1);
			buf[i*2]=MMGC3_SwizRefOut(t[0]);
			buf[(i*2)+1]=MMGC3_SwizRefOut(t[1]);
		}else if((j&3)==2)
		{
			t=((elem *)buf)+(i<<1);
//			cells=1<<(((chk->size_rover)>>27)-3);
			obj=ELEM_FROMOBJECT(t);

			switch(t[0]&255)
			{
			case OBJECT_VECTOR:
				j=(t[0]>>8)&255;
				if((j==VECTOR_ELEMENT) || ((j>=32) && (j<48)))
				{
					h=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
//					if(j==34)kprint("vec type %d, len %d, addr %p.\n", j, h, t);
					for(j=0; j<h; j++)
						t[j+1]=MMGC3_SwizRefOut(t[j+1]);
				}else kprint("unknown vec type %d\n", j);
				break;
			case OBJECT_FUNCTION:
				j=MMGC3_LookupStPosAddr(t[1]);
				t[1]=(j<<3)+TYPE_LONGREF;
				break;
			case OBJECT_SYNTAX:
				j=MMGC3_LookupStPosAddr(t[1]);
				t[1]=(j<<3)+TYPE_LONGREF;
				break;
			default:
//				sa_print("#<obj-type %d>", buf[0]&255);
				break;
			}
		}else
		{
//			kprint("(cell %d %d) ", i, j);
//			return(-1);
		}
	}

	i=MMGC3_MapChunk(chk);
	vfseek(mmgc3_storeimg, i<<18, 0);
	vfwrite(buf, 1, 1<<18, mmgc3_storeimg);
	return(0);
}

int MMGC3_StoreAll()
{
	mem3chunk *cur;
	int i;
	elem t;

	if(!mmgc3_storeimg)return(-1);

	kprint("MMGC3_StoreAll\n");

	cur=mmgc3_usedchunks;
	while(cur)
	{
		if(cur->flags&0xfff)
			MMGC3_StoreChunk(cur);
		cur=cur->next;
	}

	for(i=0; i<GCROOTS; i++)if(mmgc3_rootname[i])
	{
		t=*mmgc3_root[i];
		kprint("outref: %X -> ", t);
		t=MMGC3_SwizRefOut(t);
		kprint("%X\n", t);

		mmgc3_boundstrtab[mmgc3_boundstend++]=strlen(mmgc3_rootname[i])+5;
		mmgc3_boundstrtab[mmgc3_boundstend++]='X';

		mmgc3_boundstrtab[mmgc3_boundstend++]=t&0xff;
		mmgc3_boundstrtab[mmgc3_boundstend++]=(t>>8)&0xff;
		mmgc3_boundstrtab[mmgc3_boundstend++]=(t>>16)&0xff;
		mmgc3_boundstrtab[mmgc3_boundstend++]=(t>>24)&0xff;

		strcpy(mmgc3_boundstrtab+mmgc3_boundstend, mmgc3_rootname[i]);
		mmgc3_boundstend+=strlen(mmgc3_rootname[i]);
	}

	vfseek(mmgc3_storeimg, 0, 0);
	vfwrite(mmgc3_storemap, 1, 2048, mmgc3_storeimg);
	vfwrite(mmgc3_boundstrtab, 1, GCSTSIZE, mmgc3_storeimg);

	kprint("MMGC3_StoreAll: OK\n");
}

int MMGC3_LoadPage(mem3chunk *chk, int page)
{
	int cells, i, j, h, b;
	elem obj, *t, *buf;
	void *p;

	p=((void *)chk)+(page<<12);

//	mprotect(p, GCPAGESIZE, PROT_READ|PROT_WRITE|PROT_EXEC);

	i=chk->flags&0xfff;

//	sa_print("load page: %d %d\n", i, page);
	if(page)
	{
		vfseek(mmgc3_storeimg, (i<<18)+(page<<12), 0);
		vfread(p, 1, GCPAGESIZE, mmgc3_storeimg);
	}else
	{
		vfseek(mmgc3_storeimg, (i<<18)+(page<<12)+sizeof(mem3chunk), 0);
		vfread(p+sizeof(mem3chunk), 1, GCPAGESIZE-sizeof(mem3chunk), mmgc3_storeimg);
	}
	cells=1<<9;
	b=page<<9;

	buf=p;

	for(i=0; i<cells; i++)if(MMGC3_ChunkGetEnt(chk, i+b)!=3)break;
	for(; i<cells; i++)
	{
		j=MMGC3_ChunkGetEnt(chk, i+b);

		if((j&3)==1)
		{
			t=((elem *)p)+(i<<1);
			buf[i*2]=MMGC3_SwizRefIn(t[0]);
			buf[(i*2)+1]=MMGC3_SwizRefIn(t[1]);
		}else if((j&3)==2)
		{
			t=((elem *)p)+(i<<1);
//			cells=1<<(((chk->size_rover)>>27)-3);
			obj=ELEM_FROMOBJECT(t);

			switch(t[0]&255)
			{
			case OBJECT_VECTOR:
				if((((t[0]>>8)&255)==VECTOR_ELEMENT) || ((((t[0]>>8)&255)>=32) && (((t[0]>>8)&255)<48)))
				{
					h=ELEM_TOFIXNUM(TyFcn_VectorLength(obj));
					for(j=0; j<h; j++)
						t[j+1]=MMGC3_SwizRefIn(t[j+1]);
				}
				break;
			case OBJECT_FUNCTION:
				t[1]=MMGC3_SwizRefIn(t[1]);
				break;
			case OBJECT_SYNTAX:
				t[1]=MMGC3_SwizRefIn(t[1]);
				break;
			default:
//				sa_print("#<obj-type %d>", buf[0]&255);
				break;
			}
		}else
		{
//			kprint("(cell %d %d) ", i, j);
//			return(-1);
		}
	}
	return(0);
}

elem MMGC3_TrashImage()
{
	byte *buf;
	int i;

	if(!mmgc3_storeimg)return(MISC_NULL);

	vfseek(mmgc3_storeimg, 0, 0);

	buf=kalloc(65536);
	for(i=0; i<4; i++)vfwrites(buf, i*65536, 65536, mmgc3_storeimg);

	kfree(buf);
	vfclose(mmgc3_storeimg);
	mmgc3_storeimg=NULL;

	return(MISC_NULL);
}

elem MMGC3_StoreOff()
{
	if(!mmgc3_storeimg)return(MISC_NULL);

	vfclose(mmgc3_storeimg);
	mmgc3_storeimg=NULL;

	return(MISC_NULL);
}

int MMGC3_RestoreImage()
{
	char *s, *s2;
	byte *u;
	elem t, v;

	kprint("MMGC3: RestoreImage\n");

	Interp_DefinePrimative("store-trash-image",	&MMGC3_TrashImage,	0);
	Interp_DefinePrimative("store-off",			&MMGC3_StoreOff,	0);

	mmgc3_storeimg=vffopen("/ata0.1/store.img", "r+b");
	if(!mmgc3_storeimg)mmgc3_storeimg=vffopen("/ata0.1/store.img", "w+b");
	if(!mmgc3_storeimg)return(-1);

//	return(0);

	vfseek(mmgc3_storeimg, 0, 0);
	vfread(mmgc3_storemap, 1, 2048, mmgc3_storeimg);
	vfread(mmgc3_boundstrtab, 1, GCSTSIZE, mmgc3_storeimg);

	mmgc3_storemap[0]=0x11;

	s=mmgc3_boundstrtab;
	s++;

	while(*s)
	{
//		kprint(".");
//		fputc(s[1], stdout);
		switch(s[1])
		{
		case 'X':
			u=s;
			t=u[2]+(u[3]<<8)+(u[4]<<16)+(u[5]<<24);
			v=MMGC3_SwizRefIn(t);

			kprint("inref: %X -> %X\n", t, v);
			t=v;

			s2=kralloc(*s-4);
			memset(s2, 0, *s-4);
			strncpy(s2, s+6, *s-5);

//			kprint("set-named-root: %s\n", s2);
			MMGC3_SetNamedRoot(s2, t);
//			kfree(s2);
			break;
		default:
//			kprint(".");
//			fputc(s[1], stdout);
			break;
		}
		s+=*s+1;
	}
//	fputc('\n', stdout);
}

int MMGC3_InitStore()
{
//	struct sigaction sa;

//	sa.sa_sigaction=&MMGC3_PerPage_HandleSIGSEGV;
//	sa.sa_flags=SA_SIGINFO;
//	sigaction(SIGSEGV, &sa, NULL);

	kprint("MMGC3_InitStore\n");

	MMGC3_InitStore2();

	mmgc3_boundnames=kalloc(GCMAXBINDS*sizeof(char *));
	mmgc3_boundaddrs=kalloc(GCMAXBINDS*sizeof(void *));
	memset(mmgc3_boundnames, 0, GCMAXBINDS*sizeof(char *));
	memset(mmgc3_boundaddrs, 0, GCMAXBINDS*sizeof(void *));

	mmgc3_boundstpos=kalloc(GCMAXBINDS*sizeof(int));
	mmgc3_boundstrtab=kalloc(GCSTSIZE);
	memset(mmgc3_boundstpos, 0, GCMAXBINDS*sizeof(int));
	memset(mmgc3_boundstrtab, 0, GCSTSIZE);
	mmgc3_boundstend=1; //leave initial null string


	mmgc3_storemap=kalloc(2048);
	memset(mmgc3_storemap, 0, 2048);
	mmgc3_storemap[0]=0x11;

	mmgc3_storesize=4096;

}
