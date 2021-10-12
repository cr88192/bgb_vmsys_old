#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

int main(int argc, char *argv[])
{
	FILE *infd, *outfd;
	char lbuf[256], tokbuf[16][16];
	char *s, *t;
	int cvec, i, j, k;

	infd=fopen(argv[1], "rt");

	vecbuf=malloc(256*1024*sizeof(float)*6);
	polybuf=malloc(4096*3*sizeof(int));

	vecs=0;
	frames=0;
	cvec=0;
	polys=0;

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
		if(!strcmp(tokbuf[0], "BEGIN"))
		{
			if(!strcmp(tokbuf[1], "FRAMESET"))
			{
				vecs=atoi(tokbuf[3]);
				if(vecs<0)vecs=0-vecs;
			}
			if(!strcmp(tokbuf[1], "FRAME"))
			{
				strcpy(framenames[frames++], tokbuf[2]);
			}
		}
		if(!strcmp(tokbuf[0], "VERTEX"))
		{
			vecbuf[(cvec*6)+0]=atof(tokbuf[2]);
			vecbuf[(cvec*6)+1]=atof(tokbuf[3]);
			vecbuf[(cvec*6)+2]=atof(tokbuf[4]);

			vecbuf[(cvec*6)+3]=atof(tokbuf[5]);
			vecbuf[(cvec*6)+4]=atof(tokbuf[6]);
			vecbuf[(cvec*6)+5]=atof(tokbuf[7]);
			cvec++;
		}

		if(!strcmp(tokbuf[0], "POLYIDX"))
		{
			polybuf[(polys*4)+0]=atoi(tokbuf[2]);
			polybuf[(polys*4)+1]=atoi(tokbuf[3]);
			polybuf[(polys*4)+2]=atoi(tokbuf[4]);
			polybuf[(polys*4)+3]=atoi(tokbuf[6]);
			polys++;
		}
	}
	printf("vecs %d, frames %d, polys %d\n", vecs, frames, polys);
	for(i=0; i<frames; i++)
	{
		sprintf(lbuf, "%s_%s.tri", argv[2], framenames[i]);
		outfd=fopen(lbuf, "wt");
		for(j=0; j<polys; j++)
		{
			k=polybuf[(j*4)+0];
			fprintf(outfd, "%f %f %f  ",
				vecbuf[(((i*vecs)+k)*6)+0],
				vecbuf[(((i*vecs)+k)*6)+1],
				vecbuf[(((i*vecs)+k)*6)+2]);
			k=polybuf[(j*4)+1];
			fprintf(outfd, "%f %f %f  ",
				vecbuf[(((i*vecs)+k)*6)+0],
				vecbuf[(((i*vecs)+k)*6)+1],
				vecbuf[(((i*vecs)+k)*6)+2]);
			k=polybuf[(j*4)+2];
			fprintf(outfd, "%f %f %f  ",
				vecbuf[(((i*vecs)+k)*6)+0],
				vecbuf[(((i*vecs)+k)*6)+1],
				vecbuf[(((i*vecs)+k)*6)+2]);
			fprintf(outfd, "0xCBCBCB\n");
		}
		fclose(outfd);
	}
}
