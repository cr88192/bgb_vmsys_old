#ifndef __KPFH_H__
#define __KPFH_H__

#define PROT_READ	1
#define PROT_WRITE	2
#define PROT_EXEC	4
#define PROT_NONE	0

#define MAP_FIXED	1
#define MAP_SHARED	2
#define MAP_PRIVATE	4
#define MAP_ANONYMOUS	8

#define MAP_FORCE	8	/* with map fixed: use area even if other stuff is there, anything in the area will be merged in */

typedef struct KPFHandler_T {
struct KPFHandler_T *next, *prev;
int (*pf_proc)(int addr, struct KPFHandler_T *ctx);
int (*release_proc)(int page, struct KPFHandler_T *ctx);
int (*munmap_proc)(void *addr, int length, struct KPFHandler_T *ctx);
int (*msync_proc)(void *addr, int length, int flags, struct KPFHandler_T *ctx);
int (*mprotect_proc)(void *addr, int length, int prot, struct KPFHandler_T *ctx);
int start;
int len;
void *data;
}KPFHandler;

KPFHandler *KPFH_CreateContext(int start, int len, void *data);
int KPFH_HandleEvent(int addr);
int KPFH_RequestRelease(int page);
int KPFH_DestroyContext(KPFHandler *ctx);

void *KPFH_BasicMMap(void *addr, int length, int prot, int flags, VFILE *fd, int offs);
int KPFH_Munmap(void *start, int length);
int KPFH_Msync(void *start, int length, int flags);
int KPFH_Mprotect(void *start, int length, int prot);

#endif
