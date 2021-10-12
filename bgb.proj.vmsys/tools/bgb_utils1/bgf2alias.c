#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <scmcc.h>

#define ALIAS_VERSION	6
#define IDPOLYHEADER	(('O'<<24)+('P'<<16)+('D'<<8)+'I')

typedef float vec3_t[3];
typedef unsigned char byte;
typedef enum {ST_SYNC=0, ST_RAND } synctype_t;

typedef struct {
	int			ident;
	int			version;
	vec3_t		scale;
	vec3_t		scale_origin;
	float		boundingradius;
	vec3_t		eyeposition;
	int			numskins;
	int			skinwidth;
	int			skinheight;
	int			numverts;
	int			numtris;
	int			numframes;
	synctype_t	synctype;
	int			flags;
	float		size;
} mdl_t;

float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

int cvec;
int sw, sh;

elem recdecode(elem obj)
{
	elem cur;

//	printf("rdec %s\n", ELEM_TOSYMBOL(CAR(obj)));

	if(CAR(obj) == SYM("frameset"))
	{
		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			recdecode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("frame"))
	{
		strcpy(framenames[frames++], ELEM_TOSYMBOL(CADR(obj)));
//		printf("%s\n", framenames[frames-1]);

		if(!vecs)vecs=LENGTH(CDDR(obj));

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			recdecode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("vertices"))
	{
		vecs=TOINT(LENGTH(CDR(obj)));
		sprintf(framenames[frames++], "frame%d", frames);

		cur=CDR(obj);
		while(cur!=MISC_EOL)
		{
			recdecode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("vertex"))
	{
		vecbuf[(cvec*6)+0]=TOFLOAT(CADR(obj));
		vecbuf[(cvec*6)+1]=TOFLOAT(CADDR(obj));
		vecbuf[(cvec*6)+2]=TOFLOAT(CADDDR(obj));

//		vecbuf[(cvec*6)+3]=atof(tokbuf[5]);
//		vecbuf[(cvec*6)+4]=atof(tokbuf[6]);
//		vecbuf[(cvec*6)+5]=atof(tokbuf[7]);

		cur=CDDDDR(obj);
		while(cur!=MISC_EOL)
		{
			recdecode (CAR(cur));
			cur=CDR(cur);
		}

		cvec++;
	}
	if(CAR(obj) == SYM("st"))
	{
		vecbuf[(cvec*6)+3]=TOFLOAT(CADR(obj));
		vecbuf[(cvec*6)+4]=TOFLOAT(CADDR(obj));
	}
	if(CAR(obj) == SYM("seam"))
	{
		vecbuf[(cvec*6)+5]=TOFLOAT(CADR(obj));
	}

	if(CAR(obj) == SYM("polyidx"))
	{
		polybuf[(polys*4)+0]=TOINT(CAR(CADR(obj)));
		polybuf[(polys*4)+1]=TOINT(CADR(CADR(obj)));
		polybuf[(polys*4)+2]=TOINT(CADDR(CADR(obj)));

//		polybuf[(polys*4)+0]=atoi(tokbuf[2]);
//		polybuf[(polys*4)+1]=atoi(tokbuf[3]);
//		polybuf[(polys*4)+2]=atoi(tokbuf[4]);
//		polybuf[(polys*4)+3]=atoi(tokbuf[6]);
		polys++;
	}
	if(CAR(obj) == SYM("key"))
	{
		if(CADR(obj) == SYM("skinwidth"))
		{
			sw=TOINT(CADDR(obj));
		}
		if(CADR(obj) == SYM("skinheight"))
		{
			sh=TOINT(CADDR(obj));
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *infd, *outfd;
	char *s, *t;
	int i, j, k;

	char *fbuf, *fcur;

	float min[3], max[3];
	float org[3], scale[3];

	mdl_t	modeltemp;

	elem	obj;

	SKVM_Init();

	infd=fopen(argv[1], "rb");
	outfd=fopen(argv[2], "wb");

	fseek(infd, 0, 2);
	i=ftell(infd);
	fbuf=malloc(i+16);
	memset(fbuf, 0, i+16);
	fseek(infd, 0, 0);
	fread(fbuf, 1, i, infd);

	vecbuf=malloc(256*1024*sizeof(float)*6);
	polybuf=malloc(4096*3*sizeof(int));

	vecs=0;
	frames=0;
	cvec=0;
	polys=0;

	sw=320;
	sh=200;

#if 0
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
			if(!strcmp(tokbuf[1], "VERTICES"))
			{
				vecs=atoi(tokbuf[2]);
				if(vecs<0)vecs=0-vecs;
				sprintf(tokbuf[15], "frame%d", frames);
				strcpy(framenames[frames++], tokbuf[15]);
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
		if(!strcmp(tokbuf[0], "KEY"))
		{
			if(!strcmp(tokbuf[1], "skinwidth"))
			{
				sw=atoi(tokbuf[2]);
			}
			if(!strcmp(tokbuf[1], "skinheight"))
			{
				sh=atoi(tokbuf[2]);
			}
		}
	}
#endif

	fcur=fbuf;

	while(*fcur)
	{
		s=fcur;
		obj=ScmParse_Line(&fcur, 0);
		fcur=ScmParse_EatWhite(fcur);
		if(obj==MISC_UNDEFINED)break;

		if(!ELEM_CONSP(obj))
		{
			s[256]=0;
			printf("i %s\n", s);
			sa_print("parsed '");
			TyFcn_DumpElem(obj);
			sa_print("'\n");
			sa_fatal ("bgf2alias: non-list parsed top level\n");
		}
		recdecode (obj);
	}
	free(fbuf);

	printf("vecs %d, frames %d, polys %d\n", vecs, frames, polys);

	min[0]=99999;
	min[1]=99999;
	min[2]=99999;
	max[0]=-99999;
	max[1]=-99999;
	max[2]=-99999;

	for(i=0; i<(vecs*frames); i++)
	{
		if(vecbuf[(i*6)+0]<min[0])min[0]=vecbuf[(i*6)+0];
		if(vecbuf[(i*6)+0]>max[0])max[0]=vecbuf[(i*6)+0];
		if(vecbuf[(i*6)+1]<min[1])min[1]=vecbuf[(i*6)+1];
		if(vecbuf[(i*6)+1]>max[1])max[1]=vecbuf[(i*6)+1];
		if(vecbuf[(i*6)+2]<min[2])min[2]=vecbuf[(i*6)+2];
		if(vecbuf[(i*6)+2]>max[2])max[2]=vecbuf[(i*6)+2];
	}
	scale[0]=(max[0]-min[0])/255.0;
	scale[1]=(max[1]-min[1])/255.0;
	scale[2]=(max[2]-min[2])/255.0;
	org[0]=min[0];
	org[1]=min[1];
	org[2]=min[2];

	modeltemp.ident = IDPOLYHEADER;
	modeltemp.version = ALIAS_VERSION;
	modeltemp.boundingradius = 0;

	for (i=0 ; i<3 ; i++)
	{
		modeltemp.scale[i] = scale[i];
		modeltemp.scale_origin[i] = org[i];
		modeltemp.eyeposition[i] = 0;
	}

	modeltemp.flags = 0;
	modeltemp.numskins = 1;
	modeltemp.skinwidth = sw;
	modeltemp.skinheight = sh;
	modeltemp.numverts = vecs;
	modeltemp.numtris = polys;
	modeltemp.numframes = frames;
	modeltemp.synctype = 0;
	modeltemp.size = 0;

	fwrite(&modeltemp, 1, sizeof(mdl_t), outfd);

	j=0;
	fwrite(&j, 1, 4, outfd);
	for(i=0; i<(sw*sh)/4; i++)fwrite(&j, 1, 4, outfd);

	for(i=0; i<vecs; i++)
	{
		j=0;
		if(vecbuf[(i*6)+5]==1)j=32;
		fwrite(&j, 1, 4, outfd);

		j=vecbuf[(i*6)+3];
		fwrite(&j, 1, 4, outfd);
		j=vecbuf[(i*6)+4];
		fwrite(&j, 1, 4, outfd);
	}

	for(i=0; i<polys; i++)
	{
		k=0; //assume back face
		//front vertices flag front face
		j=polybuf[(i*4)+0];
		if(!vecbuf[(j*6)+5])k=1;
		j=polybuf[(i*4)+1];
		if(!vecbuf[(j*6)+5])k=1;
		j=polybuf[(i*4)+2];
		if(!vecbuf[(j*6)+5])k=1;

		fwrite(&k, 1, 4, outfd);

		j=polybuf[(i*4)+0];
		fwrite(&j, 1, 4, outfd);
		j=polybuf[(i*4)+1];
		fwrite(&j, 1, 4, outfd);
		j=polybuf[(i*4)+2];
		fwrite(&j, 1, 4, outfd);
	}

	for(i=0; i<frames; i++)
	{
		j=0;
		fwrite(&j, 1, 4, outfd);

		fputc(0, outfd);
		fputc(0, outfd);
		fputc(0, outfd);
		fputc(0, outfd);

		fputc(255, outfd);
		fputc(255, outfd);
		fputc(255, outfd);
		fputc(0, outfd);

		fwrite(framenames[i], 1, 16, outfd);

		for(j=0; j<vecs; j++)
		{
			k=(vecbuf[(((i*vecs)+j)*6)+0]-org[0])/scale[0];
			fputc(k, outfd);
			k=(vecbuf[(((i*vecs)+j)*6)+1]-org[1])/scale[1];
			fputc(k, outfd);
			k=(vecbuf[(((i*vecs)+j)*6)+2]-org[2])/scale[2];
			fputc(k, outfd);
			fputc(0, outfd);
		}
	}

	SKVM_DeInit();
}
