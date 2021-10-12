#include <general.h>
#include <graphics/render.h>

#include <stdlib.h>

/* matrix functions */

int MatN_MatMult(double *a, int ah, int aw, double *b, int bh, int bw, double *c)
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

int MatN_MatMultVector(double *a, double *b, double *c, int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		c[i*n+j]=a[i*n+j]*b[j];
	return(0);
}

int MatN_MatMultScaler(double *a, double b, double *c, int n)
{
	int i;
	for(i=0; i<(n*n); i++)c[i]=a[i]*b;
	return(0);
}

int MatN_ResizeMatrix(double *a, int ah, int aw, double *b, int bh, int bw)
{
	int i, j;
	for(i=0; i<bh; i++)for(j=0; j<bw; j++)
		if(a && i<ah && j<aw)b[i*bw+j]=a[i*aw+j];
			else b[i*bw+j]=((bh==bw) && (i==j))?1:0;
	return(0);
}

int MatN_FillIdentity(double *a, int n)
{
	int i;
	for(i=0; i<(n*n); i++)a[i]=0;
	for(i=0; i<n; i++)a[(i*n)+i]=1;
	return(0);
}

int MatN_Copy(double *a, double *b, int h, int w)
{
	int i;
	for(i=0;i<(h*w);i++)b[i]=a[i];
	return(0);
}

int Vec16_RotateMatrix(double *amat, double *angles, double *bmat)
{
	vec16d tmat;
	double sx, sy, sz, cx, cy, cz;
	MatN_FillIdentity(tmat, 4);

	sx=sin(angles[0]*(M_PI/180.0));
	sy=sin(angles[1]*(M_PI/180.0));
	sz=sin(angles[2]*(M_PI/180.0));
	cx=cos(angles[0]*(M_PI/180.0));
	cy=cos(angles[1]*(M_PI/180.0));
	cz=cos(angles[2]*(M_PI/180.0));

//	tmp[1]=point[1]*cx-point[2]*sx;
//	tmp[2]=point[1]*sx+point[2]*cx;
//
//	tmp[2]=point[2]*cy-point[0]*sy;
//	tmp[0]=point[2]*sy+point[0]*cy;
//
//	tmp[0]=point[0]*cz-point[1]*sz;
//	tmp[1]=point[0]*sz+point[1]*cz;
//
//  tmp[0]=((point[1]*sx+point[2]*cx)*sy+point[0]*cy)*cz-(point[1]*cx-point[2]*sx)*sz;
//  tmp[1]=((point[1]*sx+point[2]*cx)*sy+point[0]*cy)*sz+(point[1]*cx-point[2]*sx)*cz;
//  tmp[2]=(point[1]*sx+point[2]*cx)*cy-point[0]*sy;
//  tmp[2]=(point[0]*sz+point[1]*cz)*sx+(point[2]*cy-(point[0]*cz-point[1]*sz)*sy)*cx;
//
//
//	tmp[1]=point[1]*cx-point[2]*sx;
//	tmp[2]=point[1]*sx+point[2]*cx;
//
//	tmp[2]=(point[1]*sx+point[2]*cx)*cy-point[0]*sy;
//	tmp[0]=(point[1]*sx+point[2]*cx)*sy+point[0]*cy;
//
//	tmp[0]=((point[1]*sx+point[2]*cx)*sy+point[0]*cy)*cz-(point[1]*cx-point[2]*sx)*sz;
//	tmp[1]=((point[1]*sx+point[2]*cx)*sy+point[0]*cy)*sz+(point[1]*cx-point[2]*sx)*cz;
//	tmp[2]=(point[1]*sx+point[2]*cx)*cy-point[0]*sy;

	tmat[0]=cy*cz;
	tmat[1]=cy*sz;
	tmat[2]=-sy;

//	VecN_Normalize(tmat, tmat, 3);

	tmat[4]=sx*sy*cz-cx*sz;
	tmat[5]=sx*sy*sz+cx*cz;
	tmat[6]=sx*cy;

//	VecN_Normalize(&tmat[4], &tmat[4], 3);

	tmat[8]=cx*sy*cz+sx*sz;
	tmat[9]=cx*sy*sz-sx*cz;
	tmat[10]=cx*cy;

//	VecN_Normalize(&tmat[8], &tmat[8], 3);

	MatN_MatMult(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

void MatN_GetLowerMatrix(double *a, double *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[i*n+j]=(i<j)?0:a[i*n+j];
}

void MatN_GetUpperMatrix(double *a, double *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[i*n+j]=(i>j)?0:a[i*n+j];
}

int Vec16_TranslateMatrix(vec16d amat, vec3d pos, vec16d bmat)
{
	vec16d tmat;
	MatN_FillIdentity(tmat, 4);
	tmat[3]=pos[0];
	tmat[7]=pos[1];
	tmat[11]=pos[2];
	MatN_MatMult(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

/* swap ordering, matrices to/from gl */
int MatN_SwapOrder(double *a, double *b, int n)
{
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)b[(i*n)+j]=a[(j*n)+i];
	return(0);
}

int MatN_Inverse(double *a, double *b, int n)
{
	static double a2buf[8*8*2], a3buf[16];
	double *a2p[8], *a3p;
	int i, j;

	VecN_Zero(a2buf, n*n*2);
	VecN_Zero(b, n*n);
	for(i=0; i<n; i++)a2p[i]=&a2buf[i*n*2];
	for(i=0; i<n; i++)VecN_Copy(&a[i*n], a2p[i], n);
	for(i=0; i<n; i++)a2p[i][i+n]=1.0;

	for(i=0; i<n; i++)
	{
//		MatN_Dump(a2buf, n, 2*n);
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
		VecN_Scale(a2p[i], 1/a2p[i][i], a2p[i], 2*n);
		for(j=0; j<n; j++)if(i!=j)
		{
			VecN_Scale(a2p[i], -a2p[j][i], a3buf, 2*n);
			VecN_Add(a3buf, a2p[j], a2p[j], 2*n);
		}
	}

//	MatN_Dump(a2buf, n, 2*n);
//	printf("\n");

	for(i=0; i<n; i++)VecN_Copy(&a2p[i][n], &b[i*n], n);
	return(0);
}

/* vector functions */
int VecN_Copy(double *a, double *b, int n)
{
	int i;
	for(i=0;i<n;i++)b[i]=a[i];
	return(0);
}

int VecN_ResizeVector(double *a, int an, double *b, int bn)
{
	int i;
	for(i=0;i<bn;i++)b[i]=((i>=an)?0:a[i]);
	return(0);
}

double VecN_DotProduct(double *a, double *b, int n)
{
	int i;
	double t;
	t=0;
	for(i=0; i<n; i++)t+=a[i]*b[i];
	return(t);
}

static inline double _VecN_Len2(double *a, int n)
{
	int i;
	double t;

	for(i=0, t=0; i<n; i++)t+=a[i]*a[i];
	return(t);
}

double VecN_Length(double *a, int n)
{
	return(sqrt(_VecN_Len2(a, n)));
}

double VecN_Normalize(double *a, double *b, int n)
{
	int i;
	double t;
	t=sqrt(_VecN_Len2(a, n));
	if(t==0)t=1;
	
	for(i=0; i<n; i++)b[i]=a[i]/t;
	return(t);
}

void VecN_Add(double *a, double *b, double *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]+b[i];
}

void VecN_Subtract(double *a, double *b, double *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]-b[i];
}

void VecN_Scale(double *a, double b, double *c, int n)
{
	int i;
	for(i=0; i<n; i++)c[i]=a[i]*b;
}

void VecN_ScaleAdd(double *a, double b, double *c, double *d, int n)
{
	int i;
	for(i=0; i<n; i++)d[i]=a[i]*b+c[i];
}

void VecN_Zero(double *a, int n)
{
	int i;
	for(i=0; i<n; i++)a[i]=0;
}

void VecN_Const(double *a, double b, int n)
{
	int i;
	for(i=0; i<n; i++)a[i]=b;
}

void Vec3_CrossProduct (const vec3d v1, const vec3d v2, vec3d cross)
{
	cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	cross[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
}

/* functions to try for camera handling */

void Vec3_ToSphericalCoords(vec3d a, vec3d b)
{
	vec3d a2;

	VecN_Normalize(a, a2, 3);

	b[0]=VecN_Length(a, 3);
	b[1]=atan2(a2[1], a2[0]);
	b[2]=acos(a2[2]);
}

void Vec3_FromSphericalCoords(vec3d a, vec3d b)
{
	b[0]=a[0]*sin(a[2])*cos(a[1]);
	b[1]=a[0]*sin(a[2])*sin(a[1]);
	b[2]=a[0]*cos(a[2]);
}

void Vec16_InvertAngles(vec16d amat, vec16d bmat)
{
	vec3d v;

	MatN_Copy(amat, bmat, 4, 4);

	Vec3_ToSphericalCoords(&amat[0], v);
	v[0]=-v[0];
//	v[1]=-v[1];
//	v[2]=-v[2];
	Vec3_FromSphericalCoords(v, &bmat[0]);

	Vec3_ToSphericalCoords(&amat[4], v);
	v[0]=-v[0];
//	v[1]=-v[1];
//	v[2]=-v[2];
	Vec3_FromSphericalCoords(v, &bmat[4]);

	Vec3_ToSphericalCoords(&amat[8], v);
	v[0]=-v[0];
//	v[1]=-v[1];
//	v[2]=-v[2];
	Vec3_FromSphericalCoords(v, &bmat[8]);

	bmat[3]=-amat[3];
	bmat[7]=-amat[7];
	bmat[11]=-amat[11];
}

void Vec3_RotatePoint(vec3d p, const vec3d angles)
{
	double		angle;
	double		sx, sy, sz, cx, cy, cz;
	vec3		tmp, point;
	
	angle = angles[0] * (M_PI/180);
	sx = sin(angle);
	cx = cos(angle);
	angle = angles[1] * (M_PI/180);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[2] * (M_PI/180);
	sz = sin(angle);
	cz = cos(angle);

	point[0]=p[0];
	point[1]=p[1];
	point[2]=p[2];

	tmp[1]=point[1]*cx-point[2]*sx;
	tmp[2]=point[1]*sx+point[2]*cx;
	point[1]=tmp[1];
	point[2]=tmp[2];

	tmp[2]=point[2]*cy-point[0]*sy;
	tmp[0]=point[2]*sy+point[0]*cy;
	point[2]=tmp[2];
	point[0]=tmp[0];

	tmp[0]=point[0]*cz-point[1]*sz;
	tmp[1]=point[0]*sz+point[1]*cz;
	point[0]=tmp[0];
	point[1]=tmp[1];

	p[0]=point[0];
	p[1]=point[1];
	p[2]=point[2];
}

void Vec3_CalcAngleVectors (const vec3d angles, vec3d forward, vec3d right, vec3d up)
{
	forward[0]=0;
	forward[1]=0;
	forward[2]=1;
	Vec3_RotatePoint(forward, angles);

	right[0]=1;
	right[1]=0;
	right[2]=0;
	Vec3_RotatePoint(right, angles);

	up[0]=0;
	up[1]=1;
	up[2]=0;
	Vec3_RotatePoint(up, angles);
}

/* misc */
double Scaler_Random() /* random number, 0 to 1 */
{
	double tmp;
	tmp=(1.0*rand())/RAND_MAX;
	return(tmp);
}

double Scaler_SignRandom() /* -1 to 1 */
{
	double tmp;
	tmp=((2.0*rand())/RAND_MAX)-1.0;
	return(tmp);
}
