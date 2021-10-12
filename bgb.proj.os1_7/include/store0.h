#define PP_MAXPAGES	1024
#define PP_NORMAL	256
#define PP_LOWER	16
#define PP_PAGESIZE	4096

#define SWIZ_MAXMAPPED	16384

int PerPage_Init();
int PerPage_Refill();
void *PerPage_Alloc();
int PerPage_Free(void *page);

int Swizzler_Init();
int Swizzler_LoadPage(void *page);
void *Swizzler_ReadyPage(int pageid);

int Store_Init();
int Store_ReadInPage(void *page, int pageid);

int *Store_Cons();
int *Store_Object(int size);
