/*
kpfh will handle page faults and mmap like objects, in case of a pagefault
handlers will be called which correspond to that region until one returns 1.

handlers are to return 1 if they handled the event or 0 otherwise.
*/

#include <general.h>
#include <x86/page.h>
#include <x86/kpfh.h>

KPFHandler *kpfh_root=NULL;

KPFHandler *KPFH_CreateContext(int start, int len, void *data)
{
	KPFHandler *tmp;
	tmp=kalloc(sizeof(KPFHandler));
	tmp->next=kpfh_root;
	if(tmp->next)tmp->next->prev=tmp;
	tmp->prev=NULL;
	kpfh_root=tmp;

	tmp->start=start;
	tmp->len=len;
	tmp->data=data;

	return(tmp);
}

int KPFH_DestroyContext(KPFHandler *ctx)
{
	if(ctx->next)ctx->next->prev=ctx->prev;
	if(ctx->prev)ctx->prev->next=ctx->next;
		else kpfh_root=ctx->next;
	return(0);
}

int KPFH_HandleEvent(int addr)
{
	int stat;
	KPFHandler *cur;

//	kprint("pf handler<%X>.\n", addr);

	stat=0;
	cur=kpfh_root;
	while(cur)
	{
		if((addr>>12)>=cur->start && (addr>>12)<(cur->start+cur->len))
			if(cur->pf_proc)stat|=cur->pf_proc(addr, cur);
		if(stat)break;
		cur=cur->next;
	}
//	kprint("pfh %d\n", stat);
	if(!stat)kprint("unknown pf at %X.\n", addr);

	return(stat);
}

int KPFH_RequestRelease(int page)
{
	KPFHandler *cur;

	cur=kpfh_root;
	while(cur)
	{
		if(page>cur->start && page<(cur->start+cur->len))
			if(cur->release_proc)
			return(cur->release_proc(page, cur));
		cur=cur->next;
	}
	return(0);
}

/*
 * MMAP
 */

typedef struct {
VFILE *fd;
int base, offs;
int prot;
}kpfh_mmapinfo;

int kpfh_mmap_handler(int addr, struct KPFHandler_T *ctx)
{
	kpfh_mmapinfo *inf;
	int roffs;

	inf=ctx->data;

	if(!inf->prot&PROT_READ)return(0); /* mapping doesn't allow read */
	roffs=Address_GetPage(addr>>12);
	if(roffs&1 && !roffs&2)return(0); /* mapping is read only */

	Address_AllocRegion(addr>>12, 1);

	roffs=(((addr>>12)-inf->base)<<12)+inf->offs;
	if(inf->fd)
	{
		vfseek(inf->fd, roffs, 0);
		vfread((void *)(addr&(~4095)), 1, 4096, inf->fd);
	}
//	kprint("kpfh_mmap_handler: handled.\n");

	if(!(inf->prot&PROT_WRITE))
	{
		roffs=Address_GetPage(addr>>12);
		roffs-=2;
		Address_SetPage(addr>>12, roffs);
	}

	return(1);
}

int kpfh_mmap_release(int page, struct KPFHandler_T *ctx)
{
	kpfh_mmapinfo *inf;
	int roffs, i;

	inf=ctx->data;

	i=Address_GetPage(page);

	if(i&64)
	{
		roffs=((page-inf->base)<<12)+inf->offs;
		if(inf->fd)
		{
			vfseek(inf->fd, roffs, 0);
			vfwrite((void *)(page<<12), 1, 4096, inf->fd);
		}
		i&=~64;
		Address_MapPage(page, i);
	}

	Address_UnallocRegion(page, 1);

	return(1);
}

int kpfh_mmap_munmap(void *addr, int len, struct KPFHandler_T *ctx)
{
	kpfh_mmapinfo *inf;
	int roffs, i, j, page;

	inf=ctx->data;

	for(i=0; i<(len+4095)>>12; i++)
	{
		page=((int)addr>>12)+i;
		j=Address_GetPage(page);

		if(j&64 && inf->fd)
		{
			roffs=((page-inf->base)<<12)+inf->offs;
			vfseek(inf->fd, roffs, 0);
			vfwrite((void *)(page<<12), 1, 4096, inf->fd);
			j&=~64;
			Address_MapPage(page, j);
		}

		Address_UnallocRegion(page, 1);
	}
	page=((int)addr>>12)+i;
	Address_FreeRegion(page, (len+4095)>>12);

	KPFH_DestroyContext(ctx);

	return(1);
}

int kpfh_mmap_msync(void *addr, int len, int flags, struct KPFHandler_T *ctx)
{
	kpfh_mmapinfo *inf;
	int roffs, i, j, page;

	inf=ctx->data;

	for(i=0; i<(len+4095)>>12; i++)
	{
		page=((int)addr>>12)+i;
		j=Address_GetPage(page);

		if(j&64 && inf->fd)
		{
			roffs=((page-inf->base)<<12)+inf->offs;
			vfseek(inf->fd, roffs, 0);
			vfwrite((void *)(page<<12), 1, 4096, inf->fd);
			j&=~64;
			Address_SetPage(page, j);
		}
	}

	return(1);
}

int kpfh_mmap_mprotect(void *addr, int len, int prot, struct KPFHandler_T *ctx)
{
	kpfh_mmapinfo *inf;
	int roffs, i, j, page;

	inf=ctx->data;

	inf->prot=prot;

	for(i=0; i<(len+4095)>>12; i++)
	{
		page=((int)addr>>12)+i;
		j=Address_GetPage(page);
		if(j>>12)
		{
			if(!prot&PROT_READ)j&=~1;
			if(!prot&PROT_WRITE && j&1)j&=~2;
		}
		Address_SetPage(page, j);
	}

	return(1);
}

void *KPFH_BasicMMap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	int space, pages;
	kpfh_mmapinfo *tmp;
	KPFHandler *hdl;

	pages=(length+1023)>>12;
	if(addr || (flags&MAP_FIXED))
	{
		if(!Address_CheckRegionFree((int)addr>>12, pages) && !(flags&MAP_FORCE))
			return(NULL);
		space=(int)addr>>12;
	}else space=Address_ReserveRegion(0, pages);
	if(!space)return(NULL);

	tmp=kalloc(sizeof(kpfh_mmapinfo));
	tmp->fd=fd;
	tmp->base=space;
	tmp->offs=offs;
	tmp->prot=prot;

	hdl=KPFH_CreateContext(space, pages, tmp);
	hdl->release_proc=&kpfh_mmap_release;
	hdl->pf_proc=&kpfh_mmap_handler;
	hdl->munmap_proc=&kpfh_mmap_munmap;
	hdl->msync_proc=&kpfh_mmap_msync;

//	hdl->data=tmp;

//	tmp->mapdata=hdl;

	return((void *)(space<<12));
}

int KPFH_Munmap(void *start, int length)
{
	KPFHandler *cur;

	cur=kpfh_root;
	while(cur)
	{
		if(((int)start>>12)==cur->start)
			if(cur->munmap_proc)
			return(cur->munmap_proc(start, length, cur));
		cur=cur->next;
	}
	return(0);
}

int KPFH_Msync(void *start, int length, int flags)
{
	KPFHandler *cur;

	cur=kpfh_root;
	while(cur)
	{
		if(((int)start>>12)==cur->start)
			if(cur->msync_proc)
			return(cur->msync_proc(start, length, flags, cur));
		cur=cur->next;
	}
	return(0);
}

int KPFH_Mprotect(void *start, int length, int prot)
{
	KPFHandler *cur;

	cur=kpfh_root;
	while(cur)
	{
		if(((int)start>>12)==cur->start)
			if(cur->msync_proc)
			return(cur->mprotect_proc(start, length, prot, cur));
		cur=cur->next;
	}
	return(0);
}

int KPFH_Alloc(int size)
{
	void *tmp;

//	tmp=mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_ANONYMOUS, 0, offs);
//	tmp=KPFH_BasicMMap(NULL, size, KPROT_READ|KPROT_WRITE, 0, NULL, 0);
	tmp=(void *)(Address_AllocRegion(0, size>>PAGE_SHIFT)<<12);

	if(!tmp || (tmp==((void *)-1)))
	{
		panic("KPFH_Alloc: failed.\n");
		abort();
	}
	return(tmp);
}