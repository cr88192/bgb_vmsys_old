#include <stdio.h>
#include <string.h>

#ifndef __OS1_STDLIB_H__
#define __OS1_STDLIB_H__

typedef struct ldiv_s {
long quot;
long rem;
}ldiv_t;

extern char **environ;

char *getenv(char *name);
void *realloc(void *p, int size);
ldiv_t ldiv(long n, long d);

#endif
