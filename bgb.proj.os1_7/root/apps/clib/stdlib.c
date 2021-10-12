#include <stdlib.h>
#include <time.h>

ldiv_t ldiv(long n, long d)
{
	ldiv_t ld;

	ld.quot=n/d;
	ld.rem=n%d;

	return(ld);
}

time_t time(time_t *t)
{
	if(t)*t=-1;
	return(-1);
}

struct tm *localtime(time_t *t)
{
	struct tm *tmp;

	tmp=malloc(sizeof(struct tm));
	memset(tmp, 0, sizeof(struct tm));
	return(tmp);
}
