#include <general.h>

int Vec3_MakeVectorPerpendicular(vec3 n, vec3 v, vec3 d)
{
	double f;
	vec3 t;

	f=VecN_DotProduct(n, v, 3);
	VecN_Scale(n, f, t, 3);
	VecN_Subtract(v, t, d, 3);

	return(0);
}

int Vec3_MovePointOutOfSpace(vec3 s, vec16 m, vec3 d)
{
	int i, j;
	for(i=0; i<3; i++)
	{
		d[i]=0;
		for(j=0; j<3; j++)d[i]+=s[i]*m[j*4+i];
		d[i]+=m[i*4+3];
	}
	return(0);
}

int Vec3_MovePointIntoSpace(vec3 s, vec16 m, vec3 d)
{
	int i, j;
	double l;

	for(i=0; i<3; i++)
	{
		l=0;
		for(j=0; j<3; j++)l+=m[i*4+j]*m[i*4+j];

		d[i]=0;
		for(j=0; j<3; j++)d[i]+=((s[j]-m[j*4+3])*m[i*4+j])/l;
	}
	return(0);
}

/* POLYGON */
int Poly_FigureRegion(double *vert, int sz, double *dst, int n, double th)
{
	int i;
	vec3 o, x, y, z, p, q, r;
	double a;

	VecN_Copy(vert, o, 3);
	VecN_Subtract(vert+sz, o, x, 3);
	VecN_Normalize(x, x, 3);

	for(i=2; i<n; i++)
		if(VecN_Length(vert+i*sz, 3)-VecN_DotProduct(vert+i*sz, x, 3))
	{
		VecN_Subtract(vert+(i*sz), o, y, 3);
		VecN_Scale(x, VecN_DotProduct(x, y, 3), p, 3);
		VecN_Subtract(y, p, y, 3);
		VecN_Normalize(y, y, 3);
		break;
	}
	Vec3_CrossProduct(x, y, z);

	printf("%f %f %f  %f %f %f  %f %f %f\n", x[0], x[1], x[2], y[0], y[1], y[2], z[0], z[1], z[2]);

	for(i=0; i<n; i++)
	{
		VecN_Subtract(vert+((i<n?i+1:0)*sz), vert+(i*sz), p, 3);
		VecN_Normalize(p, p, 3);
		Vec3_CrossProduct(p, z, q);
		VecN_Copy(q, dst+(i*4), 3);
		a=VecN_DotProduct(vert+(i*sz), p, 3)-VecN_DotProduct(o, p, 3);
		VecN_Scale(p, a, r, 3);
		VecN_Subtract(vert+(i*sz), r, r, 3);
		dst[(i*4)+3]=VecN_DotProduct(r, q, 3);
	}

	if(th)
	{
		VecN_Copy(z, dst+(i*4), 3);
		dst[(i*4)+3]=VecN_DotProduct(o, z, 3)+(th/2);
		i++;

		VecN_Scale(z, -1, dst+(i*4), 3);
		dst[(i*4)+3]=VecN_DotProduct(o, dst+(i*4), 3)+(th/2);
	}

	return(0);
}

int Poly_PointInRegion(vec3 point, double *clips, int n)
{
	int i;
	for(i=0; i<n; i++)
		if(VecN_DotProduct(point, clips+(i*4), 3)>clips[(i*4)+3])return(0);
	return(-1);
}

int Poly_LineInRegion(vec3 start, vec3 end, double *clips, int n)
{
	int i;
	vec3 p1, p2, p, dir;
	double a;

	VecN_Copy(start, p1, 3);
	VecN_Copy(end, p2, 3);

	VecN_Subtract(p2, p1, dir, 3);
	VecN_Normalize(dir, dir, 3);

	for(i=0; i<n; i++)
	{
		if(VecN_DotProduct(p1, clips+(i*4), 3)>clips[(i*4)+3] &&
			VecN_DotProduct(p2, clips+(i*4), 3)>clips[(i*4)+3])return(0);

		if(VecN_DotProduct(p1, clips+(i*4), 3)<clips[(i*4)+3] &&
			VecN_DotProduct(p2, clips+(i*4), 3)<clips[(i*4)+3])continue;

		if(VecN_DotProduct(p1, clips+(i*4), 3)>clips[(i*4)+3])
		{
			a=VecN_DotProduct(p1, clips+(i*4), 3)-clips[(i*4)+3];
			VecN_Scale(dir, a, p, 3);
			VecN_Add(p1, p, p1, 3);

			if(VecN_DotProduct(p1, dir, 3)>VecN_DotProduct(p2, dir, 3))return(0);
		}

		if(VecN_DotProduct(p2, clips+(i*4), 3)>clips[(i*4)+3])
		{
			a=VecN_DotProduct(p2, clips+(i*4), 3)-clips[(i*4)+3];
			VecN_Scale(dir, a, p, 3);
			VecN_Subtract(p2, p, p2, 3);

			if(VecN_DotProduct(p1, dir, 3)>VecN_DotProduct(p2, dir, 3))return(0);
		}
	}
//		if(VecN_DotProduct(point, clips+(i*4), 3)>clips[(i*4)+3])return(0);
	return(-1);
}

#if 0
/* for region/region it will probably useful to make use that planes will
typically originate as polys an cases of sector/sector collision, thus it will
make sense to do poly/region comparisons, at this scale obbs probably make more
sense */

/* OBB */

int Obb_FillList(vec16 amat, BBox *obb, double *lst)
{
	vec16 tmat, atmat;
	int i;
	double *vf;
	vec3 tf;

	vf=lst;
	MatN_ResizeMatrix(obb->normals, 3, 3, atmat, 4, 4);
	MatN_MatMult(amat, 4, 4, atmat, 4, 4, tmat);
	for(i=0; i<8; i++)
	{
		if(i&1)tf[0]=obb->max[0];
			else tf[0]=obb->min[0];
		if(i&2)tf[1]=obb->max[1];
			else tf[1]=obb->min[1];
		if(i&4)tf[2]=obb->max[2];
			else tf[2]=obb->min[2];
		Vec3_MovePointOutOfSpace(tf, tmat, vf);
		vf+=3;
	}
	return(i);
}

int Obb_CheckOverlap(vec9 amat, double *alst, int na, double *blst, int nb)
{
	vec4	ext;
	int		i, j;
	double	t;

	ext[0]=999999999;
	ext[1]=-999999999;
	ext[2]=999999999;
	ext[3]=-999999999;
	for(j=0; j<3; j++)for(i=0; i<na; i++)
	{
		t=VecN_DotProduct(&amat[j*3], &alst[i*3], 3);
		if(t<ext[0])ext[0]=t;
		if(t>ext[1])ext[1]=t;
	}
	for(j=0; j<3; j++)for(i=0; i<nb; i++)
	{
		t=VecN_DotProduct(&amat[j*3], &blst[i*3], 3);
		if(t<ext[2])ext[2]=t;
		if(t>ext[3])ext[3]=t;
	}
	if(ext[1]<ext[2])return(1);
	if(ext[3]<ext[0])return(1);
	return(0);
}

int Obb_CheckCollision(
	vec16 amat, vec16 admat, BBox *aobb,
	vec16 bmat, vec16 bdmat, BBox *bobb)
{
	double	avecl[16*3], bvecl[16*3];
	vec9	tmat, atmat;

	Obb_FillList(amat, aobb, &avecl[0]);
	Obb_FillList(admat, aobb, &avecl[8*3]);

	Obb_FillList(bmat, bobb, &bvecl[0]);
	Obb_FillList(bdmat, bobb, &bvecl[8*3]);

	MatN_ResizeMatrix(amat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, aobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, avecl, 16, bvecl, 16))return(0);

	MatN_ResizeMatrix(admat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, aobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, avecl, 16, bvecl, 16))return(0);

	MatN_ResizeMatrix(bmat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, bobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, avecl, 16, bvecl, 16))return(0);

	MatN_ResizeMatrix(bdmat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, bobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, avecl, 16, bvecl, 16))return(0);

	return(1);
}

int Obb_CheckCollisionLine(
	vec16 amat, vec16 admat, BBox *aobb, vec3 src, vec3 dst)
{
	double	vecl[16*3], linep[6];
	vec9	tmat, atmat;
	vec3	d;

	Obb_FillList(amat, aobb, &vecl[0]);
	Obb_FillList(admat, aobb, &vecl[8*3]);

	VecN_Copy(src, linep, 3);
	VecN_Copy(dst, &linep[3], 3);

	VecN_Subtract(dst, src, d, 3);
	VecN_Normalize(d, d, 3);

	MatN_ResizeMatrix(amat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, aobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, vecl, 16, linep, 2))return(0);

	MatN_ResizeMatrix(admat, 4, 4, atmat, 3, 3);
	MatN_MatMult(atmat, 3, 3, aobb->normals, 3, 3, tmat);
	if(Obb_CheckOverlap(tmat, vecl, 16, linep, 2))return(0);

	Vec3_CrossProduct(&atmat[0], d, &tmat[0]);
	Vec3_CrossProduct(&atmat[3], d, &tmat[3]);
	Vec3_CrossProduct(&atmat[6], d, &tmat[6]);
	if(Obb_CheckOverlap(tmat, vecl, 16, linep, 2))return(0);

	return(1);
}
#endif
