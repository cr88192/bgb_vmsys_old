#include <general.h>

unsigned long swapbe(unsigned long l)
{
	unsigned long i;
	byte *p;
	p=(byte *)&l;
	i=(*p++<<24)+(*p++<<16)+(*p++<<8)+(*p++);
	return(i);
}

unsigned long ntohl(unsigned long i)
{
	return(swapbe(i));
}

unsigned long htonl(unsigned long i)
{
	return(swapbe(i));
}
