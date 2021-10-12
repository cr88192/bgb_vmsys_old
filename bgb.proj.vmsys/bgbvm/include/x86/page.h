#ifndef __PAGE_H__
#define __PAGE_H__

#define PAGE_SHIFT		12
#define PAGE_TRYRELEASE	256

int Page_Init();
int Page_Lock(int first,int num);
int Page_Unlock(int first,int num);
int Page_Alloc(int num);

int Paging_MoveIfPresentEnd(int page);
int Paging_AddPageEnd(int page);
int Paging_RemovePageStack(int page);
int Paging_UpdatePageStack();
int Paging_TryRelease();
int Paging_ReleasePages(int count);
int Paging_AllocRelease();

int Address_GetCurrent();
int Address_MapPage(int local, int page);
int Address_MapRange(int virtual, int physical, int count);
int Address_MapRangeNF(int virtual, int physical, int count);
int Address_GetPage(int local);

int Address_FindRegion(int pages);
int Address_ReserveRegion(int reg, int pages);
int Address_FreeRegion(int start, int len);
int Address_AllocRegion(int start, int len);
int Address_UnallocRegion(int start, int len);
int Address_CheckRegionFree(int start, int len);

#endif
