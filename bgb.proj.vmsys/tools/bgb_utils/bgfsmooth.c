#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float vec3_t[3];
typedef unsigned char byte;

float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

float *dvecbuf;
int dvecs, dpolys;
int *dpolybuf;

void Vec3_CrossProduct (float *v1, float *v2, float *cross)
{
	cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	cross[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
}

static inline float _VecN_Len2(float *a, int n)
{
	int i;
	float t;

	for(i=0, t=0; i<n; i++)t+=a[i]*a[i];
	return(t);
}

float VecN_Normalize(float *a, float *b, int n)
{
	int i;
	float t;
	t=sqrt(_VecN_Len2(a, n));
	if(t==0)t=1;
	
	for(i=0; i<n; i++)b[i]=a[i]/t;
	return(t);
}

int main(int argc, char *argv[])
{
	FILE *infd, *outfd;
	char lbuf[256], tokbuf[16][16];
	char *s, *t;
	int cvec, i, j, k;
	int sw, sh;
	float *v1, *v2, *v3;
	vec3_t vec1, vec2, vec3;
	float l1, l2;

	float min[3], max[3];
	float org[3], scale[3];

	infd=fopen(argv[1], "rt");
	outfd=fopen(argv[2], "wt");

	vecbuf=malloc(256*1024*sizeof(float)*6);
	polybuf=malloc(4096*3*sizeof(int));

	dvecbuf=malloc(256*1024*sizeof(float)*6);
	dpolybuf=malloc(4096*3*sizeof(int));

	vecs=0;
	frames=0;
	cvec=0;
	polys=0;

	dvecs=0;
	dpolys=0;

	sw=320;
	sh=200;

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
	printf("in: vecs %d, frames %d, polys %d\n", vecs, frames, polys);

	dvecs=vecs;

	//fragment tris in center
	printf("fragmenting\n");
	for(i=0; i<polys; i++)
	{
		dpolybuf[(dpolys*4)+0]=polybuf[(i*4)+0];
		dpolybuf[(dpolys*4)+1]=polybuf[(i*4)+1];
		dpolybuf[(dpolys*4)+2]=dvecs;
		dpolys++;

		dpolybuf[(dpolys*4)+0]=polybuf[(i*4)+1];
		dpolybuf[(dpolys*4)+1]=polybuf[(i*4)+2];
		dpolybuf[(dpolys*4)+2]=dvecs;
		dpolys++;

		dpolybuf[(dpolys*4)+0]=polybuf[(i*4)+2];
		dpolybuf[(dpolys*4)+1]=polybuf[(i*4)+0];
		dpolybuf[(dpolys*4)+2]=dvecs;
		dpolys++;

		dvecs++;
	}

	printf("calculating new vecs\n");
	for(i=0; i<frames; i++)
	{
		for(j=0; j<vecs*6; j++)
			dvecbuf[(i*dvecs*6)+j]=vecbuf[(i*vecs*6)+j];
		k=vecs;
		for(j=0; j<polys; j++)
		{
			v1=vecbuf+((polybuf[(j*4)+0]+(i*vecs))*6);
			v2=vecbuf+((polybuf[(j*4)+1]+(i*vecs))*6);
			v3=vecbuf+((polybuf[(j*4)+2]+(i*vecs))*6);
			dvecbuf[(i*dvecs*6)+(k*6)+0]=(v1[0]+v2[0]+v3[0])/3.0;
			dvecbuf[(i*dvecs*6)+(k*6)+1]=(v1[1]+v2[1]+v3[1])/3.0;
			dvecbuf[(i*dvecs*6)+(k*6)+2]=(v1[2]+v2[2]+v3[2])/3.0;

			vec1[0]=v1[0]-v2[0];
			vec1[1]=v1[1]-v2[1];
			vec1[2]=v1[2]-v2[2];

			vec2[0]=v3[0]-v2[0];
			vec2[1]=v3[1]-v2[1];
			vec2[2]=v3[2]-v2[2];

			l1=VecN_Normalize(vec1, vec1, 3);
			l2=VecN_Normalize(vec2, vec2, 3);
			Vec3_CrossProduct(vec1, vec2, vec3);

//			dvecbuf[(i*dvecs*6)+(k*6)+0]+=vec3[0];
//			dvecbuf[(i*dvecs*6)+(k*6)+1]+=vec3[1];
//			dvecbuf[(i*dvecs*6)+(k*6)+2]+=vec3[2];

			//get into normal position to avoid screwup
			if(v1[5]==2)v1[3]-=sw/2;
			if(v2[5]==2)v2[3]-=sw/2;
			if(v3[5]==2)v3[3]-=sw/2;
			dvecbuf[(i*dvecs*6)+(k*6)+3]=(v1[3]+v2[3]+v3[3])/3.0;
			dvecbuf[(i*dvecs*6)+(k*6)+4]=(v1[4]+v2[4]+v3[4])/3.0;
			if(v1[5]==2)v1[3]+=sw/2;
			if(v2[5]==2)v2[3]+=sw/2;
			if(v3[5]==2)v3[3]+=sw/2;

			if((v1[5]==0) || (v2[5]==0) || (v3[5]==0))
			{
				dvecbuf[(i*dvecs*6)+(k*6)+5]=0;
			}
			if((v1[5]==2) || (v2[5]==2) || (v3[5]==2))
			{
				dvecbuf[(i*dvecs*6)+(k*6)+5]=2;
				dvecbuf[(i*dvecs*6)+(k*6)+3]+=sw/2;
			}
			k++;
		}
	}

	printf("smoothing\n");
	for(i=0; i<frames; i++)
	{
		for(j=0; j<dpolys; j++)
		{
			v1=dvecbuf+((dpolybuf[(j*4)+0]+(i*dvecs))*6);
			v2=dvecbuf+((dpolybuf[(j*4)+1]+(i*dvecs))*6);
			v3=dvecbuf+((dpolybuf[(j*4)+2]+(i*dvecs))*6);

			vec1[0]=(v1[0]+v2[0])/2;
			vec1[1]=(v1[1]+v2[1])/2;
			vec1[2]=(v1[2]+v2[2])/2;

			v1[0]+=(vec1[0]-v1[0])/4.0;
			v1[1]+=(vec1[1]-v1[1])/4.0;
			v1[2]+=(vec1[2]-v1[2])/4.0;

			v2[0]+=(vec1[0]-v2[0])/4.0;
			v2[1]+=(vec1[1]-v2[1])/4.0;
			v2[2]+=(vec1[2]-v2[2])/4.0;
#if 0
			vec1[0]=(v1[0]+v2[0]+v3[0])/3;
			vec1[1]=(v1[1]+v2[1]+v3[1])/3;
			vec1[2]=(v1[2]+v2[2]+v3[2])/3;

			v1[0]-=(vec1[0]-v1[0])/4.0;
			v1[1]-=(vec1[1]-v1[1])/4.0;
			v1[2]-=(vec1[2]-v1[2])/4.0;

			v2[0]-=(vec1[0]-v2[0])/4.0;
			v2[1]-=(vec1[1]-v2[1])/4.0;
			v2[2]-=(vec1[2]-v2[2])/4.0;

			v3[0]-=(vec1[0]-v3[0])/4.0;
			v3[1]-=(vec1[1]-v3[1])/4.0;
			v3[2]-=(vec1[2]-v3[2])/4.0;
#endif
		}
	}

	printf("out: vecs %d, frames %d, polys %d\n", dvecs, frames, dpolys);

	fprintf(outfd, "KEY skinwidth %d\n", sw);
	fprintf(outfd, "KEY skinheight %d\n", sh);

	fprintf(outfd, "BEGIN FRAMESET - %d\n", -dvecs);
	for(i=0; i<frames; i++)
	{
		fprintf(outfd, "BEGIN FRAME %s\n", framenames[i]);
		for(j=0; j<dvecs; j++)
		{
			fprintf(outfd, "VERTEX XYZSTs %f %f %f\t%d %d %d\n",
				dvecbuf[(((i*dvecs)+j)*6)+0],
				dvecbuf[(((i*dvecs)+j)*6)+1],
				dvecbuf[(((i*dvecs)+j)*6)+2],
				(int)dvecbuf[(((i*dvecs)+j)*6)+3],
				(int)dvecbuf[(((i*dvecs)+j)*6)+4],
				(int)dvecbuf[(((i*dvecs)+j)*6)+5]);
		}
		fprintf(outfd, "END\n");
	}
	fprintf(outfd, "END\n");

	for(i=0; i<dpolys; i++)
	{
		fprintf(outfd, "POLYIDX 3 %d %d %d -\n",
			dpolybuf[(i*4)+0], dpolybuf[(i*4)+1],
			dpolybuf[(i*4)+2]);
	}
}
