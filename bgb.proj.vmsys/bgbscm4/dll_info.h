#ifndef __DLLINFO_H__
#define __DLLINFO_H__

typedef struct {
void *(*alloc)(int size);
void *(*cons)();
elem (*multicons)(int num, elem lst);
void *(*malloc)(int size);
int (*free)(void *buf);
int (*abort)();
int (*fatal)(char *s, va_list lst);
int (*error)(char *s, va_list lst);
int (*print)(char *s, va_list lst);
int (*atoi)(char *s);
char *(*itoa)(int i);
char *(*prints)(char *t, char *s, va_list lst);
char *(*loadfile)(char *name, int *sz);
int (*AddRoot)(elem *r);
int (*AddNamedRoot)(char *name, elem *r);
int (*BindNameAddr)(char *name, void *r);
int (*PushRoot)(elem *r);
int (*PopRoots)(int n);
int (*TimeMS)();
int (*TimeDUS)();
elem (*Quit)();

}BGBSCM_Info;

#endif
