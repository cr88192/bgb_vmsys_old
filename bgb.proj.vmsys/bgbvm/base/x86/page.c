#include <kfunc.h>
#include <x86/page.h>

static unsigned char page_array[16384]; /* 512MB */
static unsigned char page_low[32];
int mem_pages;

int Paging_Setup();

int Page_Init()
{
	int i;
	kprint("init page manager (%dMiB RAM)...\n", mem_pages>>8);
	for(i=0;i<16384;i++)page_array[i]=0;
//	mem_pages=16384; /* FIXME: make not assume 64MB */
	Page_Lock(0,256); /* lock <1M */
	Paging_Setup();
}

int Page_Lock(int first,int num)
{
	int i,tmp;

//	kprint("locking pages: ");
//	Text_WriteLong(first);
//	kprint(" to ");
//	Text_WriteLong(first+num);
//	kprint("\n");
	
	for(i=0;i<num;i++)
	{
		tmp=first+i;
		page_array[tmp/8]|=1<<(tmp%8);
	}
	return(0);
}

int Page_Unlock(int first,int num)
{
	int i,tmp;

//	kprint("unlocking pages: ");
//	Text_WriteLong(first);
//	kprint(" to ");
//	Text_WriteLong(first+num);
//	kprint("\n");

	for(i=0;i<num;i++)
	{
		tmp=first+i;
		page_array[tmp/8]&=~(1<<(tmp%8));
	}
	return(0);
}

int Page_Alloc(int num)
{
	int i,v;
	v=0;
	for(i=0;i<mem_pages;i++)
	{
		if(! (page_array[i/8]& (1<< (i%8) ) ) )
			for(v=0;v<num;v++)
		{
			if(page_array[(i+v)/8] & (1<<((i+v)%8)) )
				break;
		}
		if(v>=num)
		{
			Page_Lock(i,num);
			return(i);
		}
	}
	return(0);
}

int Page_TotalLocked()
{
	int i,v;
	v=0;
	for(i=0;i<mem_pages;i++)if(page_array[i/8]&(1<<(i%8)))v++;
	return(v);
}

// cpu level stuff

#define PAGE_AREA	0xFFC00000
#define PAGE_PDE	0xFFFFF000
#define PAGE_AREA2	0xFF800000
#define PAGE_PDE2	0xFFBFF000

unsigned int kernel_page_table;

extern void Paging_SetUpCR3();
extern int Paging_GetCR3();
extern void Paging_SetCR3(int page);
extern void Paging_FlushCR3();
extern void Paging_FlushAddr();

int *page_stack, page_stack_end; /* page stack going from least to most recently used */

int Paging_Setup()
{
	unsigned int *ptab;
	int i;
	
	kprint("setting up page tables.\n");
	
	kernel_page_table=Page_Alloc(1+(mem_pages>>10));
	ptab=(unsigned int *)(kernel_page_table<<12);
	for(i=0;i<1024;i++)ptab[i]=0;
	for(i=0;i<(mem_pages/1024);i++)ptab[i]=((kernel_page_table+i+1)<<12)|3;
	for(i=0;i<mem_pages;i++)ptab[i+1024]=(i<<12)|3;
	ptab[1023]=(kernel_page_table<<12)|3;
	ptab[1024]=2;

	Paging_SetUpCR3();

	page_stack=(int *)(Page_Alloc(mem_pages>>10)<<12);
	page_stack_end=0;
}

int Paging_MoveIfPresentEnd(int page)
{
	int i, j;
	for(i=0; i<page_stack_end; i++)if((page_stack[i]&(~4095))==page)
	{
		j=page_stack[i];
		memcpy(page_stack, page_stack+1, (page_stack_end-i)*4);
		page_stack[page_stack_end-1]=j;
		return(0);
	}
}

int Paging_AddPageEnd(int page)
{
	int i, j;
//	kprint("Paging_AddPageEnd: M0\n");
	for(i=0; i<page_stack_end; i++)if((page_stack[i]&(~4095))==page)
	{
		j=page_stack[i];
		memcpy(page_stack+i, page_stack+i+1, (page_stack_end-i)*4);
		page_stack[page_stack_end-1]=j;
		return(0);
	}
	page_stack[page_stack_end++]=page;
	return(0);
}

int Paging_RemovePageStack(int page)
{
	int i, j;
	for(i=0; i<page_stack_end; i++)if((page_stack[i]&(~4095))==page)
	{
		memcpy(page_stack, page_stack+1, (page_stack_end-i)*4);
		page_stack_end--;
		return(0);
	}
	return(0);
}

int Paging_UpdatePageStack()
{
	int i, j;
	for(i=0; i<page_stack_end;)
	{
		j=Address_GetPage(page_stack[i]>>12);
		if((j&33)==33)
		{
			Paging_AddPageEnd(page_stack[i]&(~4095));
			j&=~32;
			Address_MapPage(page_stack[i]>>12, j);
			continue;
		}
		i++;
	}
	return(0);
}

int Paging_TryRelease()
{
	int i;

	i=0;
	while(i<page_stack_end)
	{
		if(KPFH_RequestRelease(page_stack[i]>>12))
			return(1);
		i++;
	}
	return(0);
}

int Paging_ReleasePages(int count)
{
	/* don't optimize: stack changed by release */
	for(;count;count--)if(!Paging_TryRelease())return(count);
	return(0);
}

int Paging_AllocRelease()
{
	int i;
	i=Page_Alloc(1);
	memset((void *)(i<<12), 0, 4096);
	if(!i)
		Paging_ReleasePages(PAGE_TRYRELEASE);
	i=Page_Alloc(1);
	memset((void *)(i<<12), 0, 4096);
	return(i);
}

int Address_GetCurrent()
{
	return(Paging_GetCR3());
}

int Address_MapPage(int local, int page)
{
	unsigned int *ptab, *ltab;
	int high;

//	ptab=(unsigned int *)PAGE_PDE;
//	ptab[1022]=(space<<12)|3;
//	Paging_FlushCR3();

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	high=local>>10;
	if(!ptab[high])
	{
		ptab[high]=(Paging_AllocRelease(1)<<12)|3;
		Paging_FlushCR3();
	}
	ltab=(unsigned int *)PAGE_AREA;
	ltab[local]=(page<<12)|3;

	Paging_FlushCR3();

	return(0);
}

int Address_MapPageNF(int local, int page)
{
	unsigned int *ptab, *ltab;
	int high;

//	ptab=(unsigned int *)PAGE_PDE;
//	ptab[1022]=(space<<12)|3;
//	Paging_FlushCR3();

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	high=local>>10;
	if(!ptab[high])
	{
		ptab[high]=(Paging_AllocRelease(1)<<12)|3;
		Paging_FlushCR3();
	}
	ltab=(unsigned int *)PAGE_AREA;
	ltab[local]=(page<<12)|3;

//	Paging_FlushCR3();

	return(0);
}

int Address_MapRange(int virtual, int physical, int count)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;
//	for(i=0; i<count; i++)Address_MapPage(space, virtual+i, physical+i);

//	ptab=(unsigned int *)PAGE_PDE;
//	ptab[1022]=(space<<12)|3;
//	Paging_FlushCR3();

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	for(i=0; i<count; i++)
	{
		high=(virtual+i)>>10;
		if(!ptab[high])
		{
			ptab[high]=(Paging_AllocRelease()<<12)|3;
			Paging_FlushCR3();
		}
		ltab[virtual+i]=((physical+i)<<12)|3;
	}

	Paging_FlushCR3();

	return(0);
}

int Address_MapRangeNF(int virtual, int physical, int count)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;
//	for(i=0; i<count; i++)Address_MapPage(space, virtual+i, physical+i);

//	ptab=(unsigned int *)PAGE_PDE;
//	ptab[1022]=(space<<12)|3;
//	Paging_FlushCR3();

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	for(i=0; i<count; i++)
	{
		high=(virtual+i)>>10;
		if(!ptab[high])
		{
			ptab[high]=(Paging_AllocRelease()<<12)|3;
			Paging_FlushCR3();
		}
		ltab[virtual+i]=((physical+i)<<12)|3;
	}

//	Paging_FlushCR3();

	return(0);
}

int Address_GetPage(int local)
{
	unsigned int *ptab, *ltab;
	int high;

	high=local>>10;
	ptab=(unsigned int *)PAGE_PDE;
	if(!ptab[high])return(0);
	ltab=(unsigned int *)PAGE_AREA;

	return(ltab[local]);
}

int Address_SetPage(int local, int page)
{
	unsigned int *ptab, *ltab;
	int high;

	ptab=(unsigned int *)PAGE_PDE;
	high=local>>10;
	if(!ptab[high])
	{
		ptab[high]=(Paging_AllocRelease(1)<<12)|3;
		Paging_FlushCR3();
	}
	ltab=(unsigned int *)PAGE_AREA;
	ltab[local]=page;

	Paging_FlushCR3();

	return(0);
}

int Address_FindRegion(int pages)
{
	unsigned int *ptab, *ltab;
	int high;
	int j, i, c, s;

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	c=0;
	for(i=0; i<1024*4096; i++)
	{
		high=i>>10;
		if(!ptab[high])
		{
//			ptab[high]=(Paging_AllocRelease()<<12)|3;
//			Paging_FlushCR3();
			if(!s)s=i;
			i+=1024-(i&1023);
			c+=1024-(i&1023);
			if(c>=pages)return(s);
		}else if(ltab[i])
		{
			c=0;
			s=0;
		}else
		{
			if(!s)s=i;
			c++;
		}
		if(c>=pages)return(s);
	}
	return(0);
}

int Address_ReserveRegion(int reg, int pages)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;

	if(!reg)reg=Address_FindRegion(pages);
	if(!reg)return(0);

//	ptab=(unsigned int *)(space<<12);
	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	for(i=0; i<pages; i++)
	{
		high=(reg+i)>>10;
		if(!ptab[high])
		{
			ptab[high]=(Paging_AllocRelease()<<12)|3;
			Paging_FlushCR3();
		}
		ltab[reg+i]=2;
	}
	Paging_FlushCR3();

	return(reg);
}

int Address_FreeRegion(int start, int len)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;

	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	for(i=0; i<len; i++)
	{
		high=(start+i)>>10;
		if(!ptab[high])
		{
			i+=1024-((start+i)&1023);
			continue;
		}
		if(ltab[start+i]>>12)
		{
			Page_Unlock(ltab[start+i]>>12, 1);
			Paging_RemovePageStack(ltab[start+i]&(~4095));
		}
		ltab[start+i]=0;
	}
	Paging_FlushCR3();
	return(0);
}

int Address_AllocRegion(int start, int len)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;

//	kprint("Address_AllocRegion: M0\n");

	if(!start)start=Address_FindRegion(len);
	if(!start)return(0);

	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

//	kprint("Address_AllocRegion: M1\n");

	for(i=0; i<len; i++)
	{
		high=(start+i)>>10;
		if(!ptab[high])
		{
//			kprint("Address_AllocRegion: N0\n");
			ptab[high]=(Paging_AllocRelease()<<12)|3;
			Paging_FlushCR3();
//			kprint("Address_AllocRegion: N1\n");
		}
		if(!(ltab[start+i]&1))
		{
//			kprint("Address_AllocRegion: A0\n");
			if(ltab[start+i]>>12) /* allocated, read only */
			{
				ltab[start+i]|=1;
			}else
			{
				ltab[start+i]=(Paging_AllocRelease()<<12)|3;
				Paging_AddPageEnd(ltab[start+i]&(~4095));
			}
//			kprint("Address_AllocRegion: A1\n");
		}
	}
	Paging_FlushCR3();

//	kprint("Address_AllocRegion: M2\n");

	return(start);
}

int Address_UnallocRegion(int start, int len)
{
	unsigned int *ptab, *ltab;
	int high;
	int i;

	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	for(i=0; i<len; i++)
	{
		high=(start+i)>>10;
		if(!ptab[high])
		{
			ptab[high]=(Paging_AllocRelease()<<12)|3;
			Paging_FlushCR3();
		}
		if(ltab[start+i]&1)
		{
			Page_Unlock(ltab[start+i]>>12, 1);
			Paging_RemovePageStack(ltab[start+i]&(~4095));
		}
		ltab[start+i]=2;
	}
	Paging_FlushCR3();

	return(0);
}

int Address_CheckRegionFree(int start, int len)
{
	unsigned int *ptab, *ltab;
	int high;
	int i, s;

	ptab=(unsigned int *)PAGE_PDE;
	ltab=(unsigned int *)PAGE_AREA;

	s=0;
	for(i=0; i<len; i++)
	{
		high=(start+i)>>10;
		if(!ptab[high])
		{
			i+=1024-((start+i)&1023);
			continue;
		}
		if(ltab[start+i])s|=1;
	}
	return(!s);
}
