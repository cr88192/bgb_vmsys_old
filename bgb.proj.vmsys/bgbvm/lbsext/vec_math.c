#include <scmcc.h>

#include <math.h>

elem VecMath_WrapVec(double *v)
{
	elem t;
	t=VECTOR_NEW(3);
	VECTOR_SET(t, 0, FLONUM(v[0]));
	VECTOR_SET(t, 1, FLONUM(v[1]));
	VECTOR_SET(t, 2, FLONUM(v[2]));

	return(t);
}

elem VecMath_VecAdd(elem lst)
{
	elem cur, t;
	int i, l;
	double s;

	cur=lst;
	l=VECTOR_LEN(CAR(cur));
	t=VECTOR_NEW(l);

	for(i=0; i<l; i++)VECTOR_SET(t, i, FLONUM(0));

	while(cur!=MISC_EOL)
	{
		for(i=0; i<l; i++)
		{
			s=VECTOR_REFF(t, i) + VECTOR_REFF(CAR(cur), i);
			VECTOR_SET(t, i, FLONUM(s));
		}
		cur=CDR(cur);
	}

	return(t);
}

elem VecMath_VecSub(elem lst)
{
	elem cur, t;
	int i, l;
	double s;

	cur=lst;
	l=VECTOR_LEN(CAR(cur));
	t=VECTOR_NEW(l);

	for(i=0; i<l; i++)VECTOR_SET(t, i, FLONUM(0));

	if(CDR(cur)!=MISC_EOL)
	{
		for(i=0; i<l; i++)
		{
			s=VECTOR_REFF(CAR(cur), i);
			VECTOR_SET(t, i, FLONUM(s));
		}
		cur=CDR(cur);
	}

	while(cur!=MISC_EOL)
	{
		for(i=0; i<l; i++)
		{
			s=VECTOR_REFF(t, i) - VECTOR_REFF(CAR(cur), i);
			VECTOR_SET(t, i, FLONUM(s));
		}
		cur=CDR(cur);
	}

	return(t);
}

elem VecMath_VecScale(elem a, elem b)
{
	elem t;
	double s;
	int i, l;

	l=VECTOR_LEN(a);
//	t=VECTOR_NEWT(l, VECTOR_F64);
	t=VECTOR_NEW(l);

	s=TOFLOAT(b);

	for(i=0; i<l; i++)
		VECTOR_SET(t, i,
			FLONUM(VECTOR_REFF(a, i) * s));

	return(t);
}

elem VecMath_VecLen(elem a)
{
	double s;
	int i, l;

	l=VECTOR_LEN(a);

	s=0;

	for(i=0; i<l; i++)
		s += VECTOR_REFF(a, i) * VECTOR_REFF(a, i);

	return(FLONUM(sqrt(s)));
}

elem VecMath_VecLen2(elem a)
{
	double s;
	int i, l;

	l=VECTOR_LEN(a);

	s=0;

	for(i=0; i<l; i++)
		s += VECTOR_REFF(a, i) * VECTOR_REFF(a, i);

	return(FLONUM(s));
}

elem VecMath_VecDot(elem a, elem b)
{
	double s;
	int i, l;

	l=VECTOR_LEN(a);

	s=0;

	for(i=0; i<l; i++)
		s += VECTOR_REFF(a, i) * VECTOR_REFF(b, i);

	return(FLONUM(s));
}

elem VecMath_VecNorm(elem a)
{
	elem t;
	double s;
	int i, l;

	l=VECTOR_LEN(a);
//	t=VECTOR_NEWT(l, VECTOR_F64);
	t=VECTOR_NEW(l);

	s=0;

	for(i=0; i<l; i++)
		s += VECTOR_REFF(a, i) * VECTOR_REFF(a, i);

	s=sqrt(s);

	if(s==0)s=1;

	for(i=0; i<l; i++)
		VECTOR_SET(t, i,
			FLONUM(VECTOR_REFF(a, i) / s));

	return(t);
}

elem VecMath_VecCross(elem a, elem b)
{
	elem t;
	double s;
	int i, l;

	double v1[3], v2[3], v3[3];

	l=VECTOR_LEN(a);
//	t=VECTOR_NEWT(l, VECTOR_F64);
	t=VECTOR_NEW(l);

	if(l!=3)return(MISC_NULL);

	for(i=0; i<l; i++)
		v1[i] = VECTOR_REFF(a, i);

	for(i=0; i<l; i++)
		v2[i] = VECTOR_REFF(b, i);

	v3[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	v3[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	v3[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);

	for(i=0; i<l; i++)
		VECTOR_SET(t, i,
			FLONUM(v3[i]));

	return(t);
}

int VecMath_MatrixP(elem a)
{
	int i, l;

	if(!ELEM_VECTORP(a))return(MISC_FALSE);

	l=VECTOR_LEN(a);
	for(i=0; i<l; i++)
		if(!ELEM_VECTORP(VECTOR_REF(a, i)))return(MISC_FALSE);

	return(MISC_TRUE);
}

int VecMath_Vector1P(elem a)
{
	int i, l;

	if(!ELEM_VECTORP(a))return(MISC_FALSE);

	l=VECTOR_LEN(a);
	for(i=0; i<l; i++)
		if(ELEM_VECTORP(VECTOR_REF(a, i)))return(MISC_FALSE);

	return(MISC_TRUE);
}

elem VecMath_MatPack(double *a, int h, int w)
{
	int i, j;
	elem s, t;


//	sa_print("mat pack %d %d\n", w, h);

	s=VECTOR_NEW(h);

	for(i=0; i<h; i++)
	{
		t=VECTOR_NEW(w);
		VECTOR_SET(s, i, t);

		for(j=0; j<w; j++)
		{
			VECTOR_SET(t, j, FLONUM(a[(i*w)+j]));
		}
	}

	return(s);
}

int VecMath_MatUnpack(elem a, double *b, int *h, int *w)
{
	int i, j, m, n;
	elem t;

	m=VECTOR_LEN(a);
	n=VECTOR_LEN(VECTOR_REF(a, 0));

	*h=m;
	*w=n;

	for(i=0; i<m; i++)
	{
		t=VECTOR_REF(a, i);
		for(j=0; j<n; j++)
		{
			b[(i*n)+j]=VECTOR_REFF(t, j);
		}
	}

	sa_print("mat unpacked %d %d\n", n, m);

	return(0);
}

static inline int MatMult(double *a, int ah, int aw, double *b, int bh, int bw, double *c)
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

static inline int MatMultVector(double *a, double *b, double *c, int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		c[i*n+j]=a[i*n+j]*b[j];
	return(0);
}

static inline int MatMultScaler(double *a, double b, double *c, int n)
{
	int i;
	for(i=0; i<(n*n); i++)c[i]=a[i]*b;
	return(0);
}

elem VecMath_MatMult(elem a, elem b)
{
	double ma[8*8], mb[8*8], mc[8*8];
	int maw, mah, mbw, mbh;
	int i;
	double x;
	elem t;

	if(b==MISC_EOL)return(a);

	b=VecMath_MatMult(CAR(b), CDR(b));

	if((VecMath_MatrixP(a)==MISC_TRUE) &&
		(VecMath_MatrixP(b)==MISC_TRUE))
	{
		VecMath_MatUnpack(a, ma, &mah, &maw);
		VecMath_MatUnpack(b, mb, &mbh, &mbw);
		MatMult(ma, mah, maw, mb, mbh, mbw, mc);
		t=VecMath_MatPack(mc, mah, mbw);
		return(t);
	}
	if((VecMath_MatrixP(a)==MISC_TRUE) &&
		!ELEM_VECTORP(b))
	{
		VecMath_MatUnpack(a, ma, &mah, &maw);
		x=TOFLOAT(b);

		for(i=0; i<(mah*maw); i++)
		{
			ma[i]*=x;
		}

		t=VecMath_MatPack(ma, mah, maw);
		return(t);
	}
	if(!ELEM_VECTORP(a) && !ELEM_VECTORP(b))
	{
		t=FLONUM(TOFLOAT(a)*TOFLOAT(b));
		return(t);
	}
}

#if 1
static int Inverse(double *a, double *b, int n)
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

elem VecMath_MatInv(elem a)
{
	double ma[8*8], mb[8*8];
	int aw, ah;
	int i;
	double x;
	elem t;

	VecMath_MatUnpack(a, ma, &ah, &aw);

	if(ah != aw)return(NULL);

	Inverse(ma, mb, ah);

	t=VecMath_MatPack(mb, ah, aw);
	return(t);
}
#endif

elem VecMath_VecForward(elem ang)
{
	double a[3], s[3], c[3];
	double v[3];

	a[0]=VECTOR_REFF(ang, 0)*M_PI/180.0;
	a[1]=VECTOR_REFF(ang, 1)*M_PI/180.0;
	a[2]=VECTOR_REFF(ang, 2)*M_PI/180.0;

	s[0]=sin(a[0]);
	c[0]=cos(a[0]);
	s[1]=sin(a[1]);
	c[1]=cos(a[1]);
	s[2]=sin(a[2]);
	c[2]=cos(a[2]);

	v[0]=s[1]*c[0];
	v[1]=-s[0];
	v[2]=-c[1]*c[0];

	return(VecMath_WrapVec(v));
}

elem VecMath_VecRight(elem ang)
{
	double a[3], s[3], c[3];
	double v[3];

	a[0]=VECTOR_REFF(ang, 0);
	a[1]=VECTOR_REFF(ang, 1);
	a[2]=VECTOR_REFF(ang, 2);

	s[0]=sin((a[0]*M_PI)/180.0);
	c[0]=cos((a[0]*M_PI)/180.0);
	s[1]=sin((a[1]*M_PI)/180.0);
	c[1]=cos((a[1]*M_PI)/180.0);
	s[2]=sin((a[2]*M_PI)/180.0);
	c[2]=cos((a[2]*M_PI)/180.0);

	v[0]=c[1];
	v[1]=0;
	v[2]=s[1];

	return(VecMath_WrapVec(v));
}

elem VecMath_VecUp(elem ang)
{
	double a[3], s[3], c[3];
	double v[3];

	a[0]=VECTOR_REFF(ang, 0);
	a[1]=VECTOR_REFF(ang, 1);
	a[2]=VECTOR_REFF(ang, 2);

	s[0]=sin((a[0]*M_PI)/180.0);
	c[0]=cos((a[0]*M_PI)/180.0);
	s[1]=sin((a[1]*M_PI)/180.0);
	c[1]=cos((a[1]*M_PI)/180.0);
	s[2]=sin((a[2]*M_PI)/180.0);
	c[2]=cos((a[2]*M_PI)/180.0);

	v[0]=s[1]*s[0];
	v[1]=c[0];
	v[2]=-c[1]*s[0];

	return(VecMath_WrapVec(v));
}

int VecMath_Init()
{
	Interp_DefinePrimative("vec+",		&VecMath_VecAdd,	-1);
	Interp_DefinePrimative("vec-",		&VecMath_VecSub,	-1);
	Interp_DefinePrimative("vec*",		&VecMath_VecScale,	2);
	Interp_DefinePrimative("veclen",	&VecMath_VecLen,	1);
	Interp_DefinePrimative("veclen2",	&VecMath_VecLen2,	1);
	Interp_DefinePrimative("vecdot",	&VecMath_VecDot,	2);
	Interp_DefinePrimative("vecnorm",	&VecMath_VecNorm,	1);

	Interp_DefinePrimative("vec-forward",	&VecMath_VecForward,	1);
	Interp_DefinePrimative("vec-right",	&VecMath_VecRight,	1);
	Interp_DefinePrimative("vec-up",	&VecMath_VecUp,		1);

	Interp_DefinePrimative("mat*",		&VecMath_MatMult,	-2);
	Interp_DefinePrimative("matinv",	&VecMath_MatInv,	1);
}
