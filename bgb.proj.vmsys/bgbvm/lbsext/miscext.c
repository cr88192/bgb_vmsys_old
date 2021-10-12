#include <general.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

elem MiscExt_Random(elem num)
{
	double f;
	f=(1.0*rand())/RAND_MAX*TOINT(num);
	return(FIXNUM((int)f));
}

int MiscExt_Init()
{
	Interp_DefinePrimative("random",	&MiscExt_Random,	1);
	return(0);
}
