#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *vecbuf;
int vecs;

int *tribuf;
int tris;

float min[3], max[3];

int aeq(float a, float b)
{
	if(fabs(a-b)<0.01)return(1);
	return(0);
}

int findvec(float *vec)
{
	int i;
	for(i=0; i<vecs; i++)
		if(aeq(vecbuf[(i*6)+0], vec[0]) &&
		aeq(vecbuf[(i*6)+1], vec[1]) &&
		aeq(vecbuf[(i*6)+2], vec[2]))
			return(i);

	vecbuf[(vecs*6)+0]=vec[0];
	vecbuf[(vecs*6)+1]=vec[1];
	vecbuf[(vecs*6)+2]=vec[2];

	vecs++;

	if(vec[0]<min[0])min[0]=vec[0];
	if(vec[0]>max[0])max[0]=vec[0];
	if(vec[1]<min[1])min[1]=vec[1];
	if(vec[1]>max[1])max[1]=vec[1];
	if(vec[2]<min[2])min[2]=vec[2];
	if(vec[2]>max[2])max[2]=vec[2];

	return(vecs-1);
}

float VecN_DotProduct(float *a, float *b, int n)
{
	int i;
	float t;
	t=0;
	for(i=0; i<n; i++)t+=a[i]*b[i];
	return(t);
}

void Vec3_CrossProduct (float *v1, float *v2, float *cross)
{
	cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	cross[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
}


int main(int argc, char *argv[])
{
	FILE *infd;
	FILE *outfd;
	char lbuf[256], tokbuf[16][16];
	char *s, *t;
	int i, j, k;
	float vec[3], vec1[3], vec2[3], sx, sy;
	float *v1, *v2, *v3;

	int px, py, pz, sp, ps, pt;
	float oxs, oys, ozs;

	if(argc<2)
	{
		printf("use: %s in.tri out.bgf [opts...]\n");
		printf("-xzy	swap y and z coords on input\n");
		printf("-px	use x as skinning plane\n");
		printf("-py	use y as skinning plane\n");
		printf("-pz	use z as skinning plane\n");
		printf("-sx v	scale input x by v\n");
		printf("-sy v	scale input y by v\n");
		printf("-sz v	scale input z by v\n");
		return(-1);
	}

	infd=fopen(argv[1], "rt");
	outfd=fopen(argv[2], "wt");

	px=0;
	py=1;
	pz=2;
	oxs=1.0;
	oys=1.0;
	ozs=1.0;
	ps=0;
	pt=1;
	sp=2;

	for(i=0; i<argc; i++)
	{
		if(!strcmp(argv[i], "-xzy"))
		{
			py=2;
			pz=1;
		}
		if(!strcmp(argv[i], "-px"))
		{
			sp=0;
			ps=1;
			pt=2;
		}
		if(!strcmp(argv[i], "-py"))
		{
			sp=1;
			ps=0;
			pt=2;
		}
		if(!strcmp(argv[i], "-pz"))
		{
			sp=2;
			ps=0;
			pt=1;
		}
		if(!strcmp(argv[i], "-sx"))oxs=atof(argv[i+1]);
		if(!strcmp(argv[i], "-sy"))oys=atof(argv[i+1]);
		if(!strcmp(argv[i], "-sz"))ozs=atof(argv[i+1]);
	}

	vecbuf=malloc(4096*6*sizeof(float));
	vecs=0;

	tribuf=malloc(4096*3*sizeof(int));
	tris=0;

	//load the tris and bind equal vertices
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
		if(!tokbuf[0][0])break;

		vec[px]=atof(tokbuf[0])*oxs;
		vec[py]=atof(tokbuf[1])*oys;
		vec[pz]=atof(tokbuf[2])*ozs;

		i=findvec(vec);
		tribuf[(tris*3)+0]=i;

		vec[px]=atof(tokbuf[3])*oys;
		vec[py]=atof(tokbuf[4])*oys;
		vec[pz]=atof(tokbuf[5])*oys;

		i=findvec(vec);
		tribuf[(tris*3)+1]=i;

		vec[px]=atof(tokbuf[6])*ozs;
		vec[py]=atof(tokbuf[7])*ozs;
		vec[pz]=atof(tokbuf[8])*ozs;

		i=findvec(vec);
		tribuf[(tris*3)+2]=i;

		tris++;
	}

	for(i=0; i<tris; i++)
	{
		//1-2, 3-2, cross
		j=tribuf[(i*3)+0];
		v1=vecbuf+j*6;
		j=tribuf[(i*3)+1];
		v2=vecbuf+j*6;
		j=tribuf[(i*3)+2];
		v3=vecbuf+j*6;

		vec[0]=v1[0]-v2[0];
		vec[1]=v1[1]-v2[1];
		vec[2]=v1[2]-v2[2];

		vec1[0]=v3[0]-v2[0];
		vec1[1]=v3[1]-v2[1];
		vec1[2]=v3[2]-v2[2];

		Vec3_CrossProduct(vec, vec1, vec2);

		if(vec2[sp]>0)
		{
			if(v1[5]==0)v1[5]=3;
			if(v1[5]==1)v1[5]=2;
			if(v2[5]==0)v2[5]=3;
			if(v2[5]==1)v2[5]=2;
			if(v3[5]==0)v3[5]=3;
			if(v3[5]==1)v3[5]=2;
		}else
		{
			if(v1[5]==0)v1[5]=1;
			if(v1[5]==3)v1[5]=2;
			if(v2[5]==0)v2[5]=1;
			if(v2[5]==3)v2[5]=2;
			if(v3[5]==0)v3[5]=1;
			if(v3[5]==3)v3[5]=2;
		}
	}

	//figure st coords based on x y plane
	sx=160/(max[ps]-min[ps]);
	sy=200/(max[pt]-min[pt]);
	for(i=0; i<vecs; i++)
	{
		vecbuf[(i*6)+3]=(vecbuf[(i*6)+ps]-min[ps])*sx;
		vecbuf[(i*6)+4]=199-(vecbuf[(i*6)+pt]-min[pt])*sy;
		if(vecbuf[(i*6)+5]==3)vecbuf[(i*6)+3]+=160;
	}

	fprintf(outfd, "KEY skinwidth %d\n", 320);
	fprintf(outfd, "KEY skinheight %d\n", 200);

	fprintf(outfd, "BEGIN VERTICES %d\n", -vecs);
	for(i=0; i<vecs; i++)
	{
		fprintf(outfd, "VERTEX XYZSTs %f %f %f\t%d %d %d\n",
			vecbuf[(i*6)+0], vecbuf[(i*6)+1], vecbuf[(i*6)+2],
			(int)vecbuf[(i*6)+3], (int)vecbuf[(i*6)+4],
			(int)vecbuf[(i*6)+5]-1);
	}
	fprintf(outfd, "END\n");

	for(i=0; i<tris; i++)
	{
		fprintf(outfd, "POLYIDX 3 %d %d %d -\n",
			tribuf[(i*3)+0], tribuf[(i*3)+1], tribuf[(i*3)+2]);
	}
}
