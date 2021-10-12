#include <general.h>
#include <graphics/render.h>

#include <stdlib.h>

/* matrix functions */

int MatNF_MatMult(float *a, int ah, int aw, float *b, int bh, int bw, float *c)
{
	int i, j, k;

	if(aw!=bh)return(-1);

	for(i=0; i<(ah*bw); i++)c[i]=0;
	for(i=0; i<ah; i++)
		for(j=0; j<bw; j++)
		for(k=0; k<aw; k++)
		c[j*bw+k]+=a[j*aw+i]*b[i*bw+k];
	return(0);
}

int MatNF_MatMultVector(float *a, float *b, float *c, int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		c[i*n+j]=a[i*n+j]*b[j];
	return(0);
}

int MatNF_MatMultScaler(float *a, float b, float *c, int n)
{
	int i;
	for(i=0; i<(n*n); i++)c[i]=a[i]*b;
	return(0);
}

int MatNF_ResizeMatrix(float *a, int ah, int aw, float *b, int bh, int bw)
{
	int i, j;
	for(i=0; i<bh; i++)for(j=0; j<bw; j++)
		if(a && i<ah && j<aw)b[i*bw+j]=a[i*aw+j];
			else b[i*bw+j]=((bh==bw) && (i==j))?1:0;
	return(0);
}

int MatNF_FillIdentity(float *a, int n)
{
	int i;
	for(i=0; i<(n*n); i++)a[i]=0;
	for(i=0; i<n; i++)a[(i*n)+i]=1;
	return(0);
}

int MatNF_Copy(float *a, float *b, int h, int w)
{
	int i;
	for(i=0;i<(h*w);i++)b[i]=a[i];
	return(0);
}

int Vec16F_RotateMatrix(float *amat, float *angles, float *bmat)
{
	vec16f tmat;
	float sx, sy, sz, cx, cy, cz;
	MatNF_FillIdentity(tmat, 4);

	sx=sin(angles[0]*(M_PI/180.0));
	sy=sin(angles[1]*(M_PI/180.0));
	sz=sin(angles[2]*(M_PI/180.0));
	cx=cos(angles[0]*(M_PI/180.0));
	cy=cos(angles[1]*(M_PI/180.0));
	cz=cos(angles[2]*(M_PI/180.0));

	tmat[0]=cy*cz;
	tmat[1]=cy*sz;
	tmat[2]=-sy;

	tmat[4]=sx*sy*cz-cx*sz;
	tmat[5]=sx*sy*sz+cx*cz;
	tmat[6]=sx*cy;

	tmat[8]=cx*sy*cz+sx*sz;
	tmat[9]=cx*sy*sz-sx*cz;
	tmat[10]=cx*cy;

	MatNF_MatMult(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

void MatNF_GetLowerMatrix(float *a, float *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[i*n+j]=(i<j)?0:a[i*n+j];
}

void MatNF_GetUpperMatrix(float *a, float *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[i*n+j]=(i>j)?0:a[i*n+j];
}

int Vec16F_TranslateMatrix(vec16f amat, vec3f pos, vec16f bmat)
{
	vec16f tmat;
	MatNF_FillIdentity(tmat, 4);
	tmat[3]=pos[0];
	tmat[7]=pos[1];
	tmat[11]=pos[2];
	MatNF_MatMult(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

/* swap ordering, matrices to/from gl */
int MatNF_SwapOrder(float *a, float *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[(i*n)+j]=a[(j*n)+i];
	return(0);
}

int MatNF_Inverse(float *a, float *b, int n)
{
	static float a2buf[8*8*2], a3buf[16];
	float *a2p[8], *a3p;
	int i, j;

	VecNF_Zero(a2buf, n*n*2);
	VecNF_Zero(b, n*n);
	for(i=0; i<n; i++)a2p[i]=&a2buf[i*n*2];
	for(i=0; i<n; i++)VecNF_Copy(&a[i*n], a2p[i], n);
	for(i=0; i<n; i++)a2p[i][i+n]=1.0;

	for(i=0; i<n; i++)
	{
//		MatNF_Dump(a2buf, n, 2*n);
//		printf("\n");
		if(a2p[i][i]==0) /* search for a new pivot in a lower row */
		{
			for(j=n-1; j>i; j--)if(a2p[j][i]!=0)
			{
				a3p=a2p[i];
				a2p[i]=a2p[j];
				a2p[j]=a3p;
			}
			if(a2p[i][i]==0)return(-1); /* no pivot */
		}
		VecNF_Scale(a2p[i], 1/a2p[i][i], a2p[i], 2*n);
		for(j=0; j<n; j++)if(i!=j)
		{
			VecNF_Scale(a2p[i], -a2p[j][i], a3buf, 2*n);
			VecNF_Add(a3buf, a2p[j], a2p[j], 2*n);
		}
	}

//	MatNF_Dump(a2buf, n, 2*n);
//	printf("\n");

	for(i=0; i<n; i++)VecNF_Copy(&a2p[i][n], &b[i*n], n);
	return(0);
}

/* vector functions */
int VecNF_Copy(float *a, float *b, int n)
{
	int i;
	for(i=0;i<n;i++)b[i]=a[i];
	return(0);
}

int VecNF_ResizeVector(float *a, int an, float *b, int bn)
{
	int i;
	for(i=0;i<bn;i++)b[i]=((i>=an)?0:a[i]);
	return(0);
}

float VecNF_DotProduct(float *a, float *b, int n)
{
	int i;
	float t;
	t=0;
	for(i=0; i<n; i++)t+=a[i]*b[i];
	return(t);
}

static inline float _VecNF_Len2(float *a, int n)
{
	int i;
	float t;

	for(i=0, t=0; i<n; i++)t+=a[i]*a[i];
	return(t);
}

float VecNF_Length(float *a, int n)
{
	return(sqrt(_VecNF_Len2(a, n)));
}

float VecNF_Normalize(float *a, float *b, int n)
{
	int i;
	float t;
	t=sqrt(_VecNF_Len2(a, n));
	if(t==0)t=1;
	
	for(i=0; i<n; i++)b[i]=a[i]/t;
	return(t);
}

void VecNF_Add(float *a, float *b, float *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]+b[i];
}

void VecNF_Subtract(float *a, float *b, float *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]-b[i];
}

void VecNF_Scale(float *a, float b, float *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]*b;
}

void VecNF_ScaleAdd(float *a, float b, float *c, float *d, int n)
{
	int i;
	for(i=0; i<n; i++)d[i]=a[i]*b+c[i];
}

void VecNF_Zero(float *a, int n)
{
	int i;
	for(i=0; i<n; i++)a[i]=0;
}

void VecNF_Const(float *a, float b, int n)
{
	int i;
	for(i=0; i<n; i++)a[i]=b;
}

void Vec3F_CrossProduct(const vec3f v1, const vec3f v2, vec3f cross)
{
	cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	cross[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
}
