#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *infd, *outfd;
	char lbuf[256], tokbuf[16][16];
	char *s, *t;
	int cvec, i, j, k;

	infd=fopen(argv[1], "rt");
	outfd=fopen(argv[2], "wt");

	while(!feof(infd))
	{
		lbuf[0]=0;
		fgets(lbuf, 255, infd);
		s=lbuf;
		for(i=0; i<16; i++)
		{
			while(*s && (*s<=' '))s++;
			t=tokbuf[i];
			while(*s>' ')*t++=*s++;
			*t++=0;
		}
		if(!strcmp(tokbuf[0], "F"))
		{
			fprintf(outfd, "%s %s %s\t%s %s %s\t%s %s %s\t0xFFFFFF\n",
				tokbuf[1], tokbuf[2], tokbuf[3],
				tokbuf[4], tokbuf[5], tokbuf[6],
				tokbuf[7], tokbuf[8], tokbuf[9]);
		}
	}
}
