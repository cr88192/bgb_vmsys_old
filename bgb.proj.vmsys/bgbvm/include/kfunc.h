#ifndef __KFUNC_H__
#define __KFUNC_H__

#ifndef NULL
#define NULL ((void *)0)
#endif

/* arguments for kmmap */
#define KPROT_READ	1
#define KPROT_WRITE	2
#define KPROT_EXEC	4
#define KPROT_NONE	0

#define KMAP_FIXED	1
#define KMAP_SHARED	2
#define KMAP_PRIVATE	4
#define KMAP_ANONYMOUS	8

#define KMAP_FORCE	8	/* with map fixed: use area even if other stuff is there, anything in the area will be merged in */


#define kva_list	void **
#define kva_start(lst, s)	lst=(void **)&s
#define kva_end(s)
#define kva_arg(lst, t)		(*(t *)((lst)++))

int kprint(char *s, ...);
int kvprint(char *s, kva_list lst);
int panic(char *s);

int printltohs(char *str, long l, int n);
int kgets(char *str, char **t);

void *kalloc(int size);
int kfree(void *ptr);
void *kgalloc(int size);
void *kpgalloc(int size);
void *kpgcons();
void *kralloc(int size);

char *kstrdup(char *s);
char *kgstrdup(char *s);
char *kprints(char *d, char *s, ...);
char *kvprints(char *d, char *s, void **lst);

//void *kmmap(void *addr, int length, int prot, int flags, VFILE *fd, int offs);
int kmunmap(void *start, int length);
int kmsync(void *start, int length, int flags);

#endif
