#include "bgfrender.h"

bgftexinfo_t *tex_stack[16];
int tex_stackpos;

float dot(vec3 a, vec3 b)
{
	return((a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2]));
}

float proj(vec3 pt, vec3 pl)
{
	float h;

	h=dot(pt, pl);
	pt[0]=pt[0]-(h*pl[0]);
	pt[1]=pt[1]-(h*pl[1]);
	pt[2]=pt[2]-(h*pl[2]);

	return(h);
}

int cross (vec3 v1, vec3 v2, vec3 v3)
{
	v3[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
	v3[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
	v3[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);

	return(0);
}

int ptadj(vec3 pt, vec3 dir, vec3 org, vec3 d)
{
	vec3 x, y;
	int i;

	for(i=0; i<3; i++)
	{
		x[0]=0;
		x[1]=0;
		x[2]=0;
		x[i]=1;
		if(proj(x, dir)<1)break;
	}
	cross(x, dir, y);

	d[0]=(pt[0]*x[0])+(pt[1]*y[0])+(pt[2]*dir[0])+org[0];
	d[1]=(pt[0]*x[1])+(pt[1]*y[1])+(pt[2]*dir[1])+org[1];
	d[2]=(pt[0]*x[2])+(pt[1]*y[2])+(pt[2]*dir[2])+org[2];

	return(0);
}

int vecz(vec3 v)
{
	if(fabs(v[0]+v[1]+v[2])<0.0001)return(1);
	return(0);
}

//mat mult column major float
int MatN_MatMultf(float *a, int ah, int aw, float *b, int bh, int bw, float *c)
{
	int i, j, k;

	if(aw!=bh)return(-1);

	for(i=0; i<(ah*bw); i++)c[i]=0;
	for(i=0; i<ah; i++)
		for(j=0; j<bw; j++)
		for(k=0; k<aw; k++)
		c[j+(bw*k)]+=a[j+(aw*i)]*b[i+(bw*k)];
	return(0);
}

int MatN_FillIdentityf(float *a, int n)
{
	int i;
	for(i=0; i<(n*n); i++)a[i]=0;
	for(i=0; i<n; i++)a[(i*n)+i]=1;
	return(0);
}

int Vec16_RotateMatrixf(float *amat, float *angles, float *bmat)
{
	float tmat[16];
	float sx, sy, sz, cx, cy, cz;
	MatN_FillIdentityf(tmat, 4);

	sx=sin(angles[0]*(M_PI/180.0));
	sy=sin(angles[1]*(M_PI/180.0));
	sz=sin(angles[2]*(M_PI/180.0));
	cx=cos(angles[0]*(M_PI/180.0));
	cy=cos(angles[1]*(M_PI/180.0));
	cz=cos(angles[2]*(M_PI/180.0));

	tmat[0]=cy*cz;
	tmat[4]=cy*sz;
	tmat[8]=-sy;

	tmat[1]=sx*sy*cz-cx*sz;
	tmat[5]=sx*sy*sz+cx*cz;
	tmat[9]=sx*cy;

	tmat[2]=cx*sy*cz+sx*sz;
	tmat[6]=cx*sy*sz-sx*cz;
	tmat[10]=cx*cy;

	MatN_MatMultf(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

int Vec16_TranslateMatrixf(float *amat, float *ofs, float *bmat)
{
	float tmat[16];

	MatN_FillIdentityf(tmat, 4);

	tmat[12]=ofs[0];
	tmat[13]=ofs[1];
	tmat[14]=ofs[2];

	MatN_MatMultf(amat, 4, 4, tmat, 4, 4, bmat);
	return(0);
}

int MatN_MatMultVectorf(float *a, float *b, float *c, int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		c[i+(n*j)]=a[i+(n*j)]*b[j];
	return(0);
}

int MatN_Copyf(float *a, float *b, int h, int w)
{
	int i;
	for(i=0;i<(h*w);i++)b[i]=a[i];
	return(0);
}

bgftexinfo_t *Render_SelectTextureR(bgftexinfo_t *tex, vec3 n)
{
	bgftexinfo_t *best, *cur, *t;
	float bf, f;

	cur=tex;
	best=NULL;
	bf=-1;

	if(vecz(cur->norm) && (!cur->first))return(cur);
		//non-planar textures win by default

//	kprint("(seltex ");

	while(cur)
	{
		if(cur->first)
			t=Render_SelectTextureR(cur->first, n);
			else t=cur;
		f=dot(t->norm, n);
		f=((f<0)?0:f)+fabs(f);

		if(f>bf)
		{
			best=t;
			bf=f;
		}

		cur=cur->next;
	}
//	kprint(")");

	return(best);
}

bgftexinfo_t *Render_SelectTexture(vec3 n)
{
	bgftexinfo_t *t;

	if(!tex_stackpos)return(NULL);

	t=Render_SelectTextureR(tex_stack[tex_stackpos-1], n);
//	printf("sel tex, num %d\n", t->num);

	return(t);
}
int Render_MapST(bgftexinfo_t *t, vec3 p, vec2 st)
{
	if(vecz(t->norm))
		return(-1);

	st[0]=(dot(p, t->right)-dot(t->org, t->right))/t->scale_s;
	st[1]=(dot(p, t->up)-dot(t->org, t->up))/t->scale_t;
	return(0);
}

int Render_Cylinder(piece_t *p)
{
	int i;
	float r, g, b;

	float a1, x1, y1;
	float a2, x2, y2;
	float s1, s2;
	vec3 pt, pt2;
	vec2 st;

	bgftexinfo_t *tex;

	glEnable(GL_TEXTURE_2D);
//	Draw_Bind(texture[p->skin].num);

	for(i=0; i<16; i++)
	{
		a1=((M_PI*2)/16)*i;
		s1=(1.0/16.0)*i;
		x1=sin(a1);
		y1=cos(a1);

		a2=((M_PI*2)/16)*(i+1);
		s2=(1.0/16.0)*(i+1);
		x2=sin(a2);
		y2=cos(a2);

		pt[0]=(x1+x2)/2;
		pt[1]=(y1+y2)/2;
		pt[2]=0;
		pt2[0]=pt2[1]=pt2[2]=0;
		ptadj(pt, p->dir, pt2, pt2);

		tex=Render_SelectTexture(pt2);
		Draw_Bind(tex->num);

		glBegin(GL_POLYGON);

		pt[0]=x1*p->trad;
		pt[1]=y1*p->trad;
		pt[2]=p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s1;
		st[1]=0;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=x2*p->trad;
		pt[1]=y2*p->trad;
		pt[2]=p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);

		st[0]=s2;
		st[1]=0;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=x2*p->brad;
		pt[1]=y2*p->brad;
		pt[2]=-p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s2;
		st[1]=1;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=x1*p->brad;
		pt[1]=y1*p->brad;
		pt[2]=-p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s1;
		st[1]=1;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		glEnd();
	}
//	glEnd();

	return(0);
}

int Render_Sphere(piece_t *p)
{
	int i, j;
	float r, g, b;

	int horz, vert;

	float a1, a2, a3, a4;
	vec3 pt, pt1, pt2, pt3, pt4;
	float s1, s2, s3, s4;
	float t1, t2, t3, t4;
	float h1, h2, h3, h4;
	int ip, jp;
	vec2 st;
	bgftexinfo_t *tex;

//	printf("sphere %f\n", p->trad);

	glEnable(GL_TEXTURE_2D);
//	Draw_Bind(texture[p->skin].num);

//	glBegin(GL_QUADS);

	horz=16;
	vert=8;

	if(p->hmap)
	{
		horz=p->hmapwidth;
		vert=p->hmapheight;
	}

	for(i=0; i<horz; i++) //16
		for(j=0; j<vert; j++) //8
	{
		a1=((M_PI*2)/horz)*i;
		a2=((M_PI*2)/horz)*(i+1);
		a3=((M_PI*2)/horz)*j;
		a4=((M_PI*2)/horz)*(j+1);

		h1=p->trad;
		h2=p->trad;
		h3=p->trad;
		h4=p->trad;

		if(p->hmap)
		{
//			printf("hmap %d %d\n", horz, vert);

			ip=i+1;
			if(ip>=horz)ip=0;
			jp=j+1;
			if(jp>=vert)jp=0;

			h1=(p->trad*(1-p->hmapbias))+
				(p->hmap[(j*horz+i)*4]*
				p->hmapscale*p->hmapbias);
			h2=(p->trad*(1-p->hmapbias))+
				(p->hmap[(jp*horz+i)*4]*
				p->hmapscale*p->hmapbias);
			h3=(p->trad*(1-p->hmapbias))+
				(p->hmap[(jp*horz+ip)*4]*
				p->hmapscale*p->hmapbias);
			h4=(p->trad*(1-p->hmapbias))+
				(p->hmap[(j*horz+ip)*4]*
				p->hmapscale*p->hmapbias);
		}
		pt1[0]=sin(a3)*sin(a1)*h1;
		pt1[1]=sin(a3)*cos(a1)*h1;
		pt1[2]=cos(a3)*h1;
		s1=(-1.0/horz)*i;
		t1=(-1.0/vert)*j;

		pt2[0]=sin(a4)*sin(a1)*h2;
		pt2[1]=sin(a4)*cos(a1)*h2;
		pt2[2]=cos(a4)*h2;
		s2=(-1.0/horz)*i;
		t2=(-1.0/vert)*(j+1);

		pt3[0]=sin(a4)*sin(a2)*h3;
		pt3[1]=sin(a4)*cos(a2)*h3;
		pt3[2]=cos(a4)*h3;
		s3=(-1.0/horz)*(i+1);
		t3=(-1.0/vert)*(j+1);

		pt4[0]=sin(a3)*sin(a2)*h4;
		pt4[1]=sin(a3)*cos(a2)*h4;
		pt4[2]=cos(a3)*h4;
		s4=(-1.0/horz)*(i+1);
		t4=(-1.0/vert)*j;

		pt[0]=(pt1[0]+pt2[0]+pt3[0]+pt4[0])/4;
		pt[1]=(pt1[1]+pt2[1]+pt3[1]+pt4[1])/4;
		pt[2]=(pt1[2]+pt2[2]+pt3[2]+pt4[2])/4;
		tex=Render_SelectTexture(pt);
		Draw_Bind(tex->num);

		pt1[0]+=p->org[0];
		pt1[1]+=p->org[1];
		pt1[2]+=p->org[2];

		pt2[0]+=p->org[0];
		pt2[1]+=p->org[1];
		pt2[2]+=p->org[2];

		pt3[0]+=p->org[0];
		pt3[1]+=p->org[1];
		pt3[2]+=p->org[2];

		pt4[0]+=p->org[0];
		pt4[1]+=p->org[1];
		pt4[2]+=p->org[2];

		glBegin(GL_POLYGON);

		r=0.5+(sin(pt1[0])*0.5);
		g=0.5+(sin(pt1[1])*0.5);
		b=0.5+(sin(pt1[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s1;
		st[1]=t1;
		Render_MapST(tex, pt1, st);
		glTexCoord2fv(st);
//		glTexCoord2f(s1, t1);
		glVertex3fv(pt1);

		r=0.5+(sin(pt2[0])*0.5);
		g=0.5+(sin(pt2[1])*0.5);
		b=0.5+(sin(pt2[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s2;
		st[1]=t2;
		Render_MapST(tex, pt2, st);
		glTexCoord2fv(st);
//		glTexCoord2f(s2, t2);
		glVertex3fv(pt2);

		r=0.5+(sin(pt3[0])*0.5);
		g=0.5+(sin(pt3[1])*0.5);
		b=0.5+(sin(pt3[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s3;
		st[1]=t3;
		Render_MapST(tex, pt3, st);
		glTexCoord2fv(st);
//		glTexCoord2f(s3, t3);
		glVertex3fv(pt3);

		r=0.5+(sin(pt4[0])*0.5);
		g=0.5+(sin(pt4[1])*0.5);
		b=0.5+(sin(pt4[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=s4;
		st[1]=t4;
		Render_MapST(tex, pt4, st);
		glTexCoord2fv(st);
//		glTexCoord2f(s4, t4);
		glVertex3fv(pt4);

		glEnd();
	}
//	glEnd();

	return(0);
}

int Render_Cube(piece_t *p)
{
	int i;
	float r, g, b;

	float vtxa[8*3];
	static int vtxb[6*4]=
	{
		1, 3, 2, 0,
		4, 6, 7, 5,
		5, 7, 3, 1,
		0, 2, 6, 4,
		5, 1, 0, 4,
		3, 7, 6, 2
	};
	static float vtna[6*4]=
	{
		0, 0, 1,
		0, 0, -1,
		-1, 0, 0,
		1, 0, 0,
		0, 1, 0,
		0, -1, 0
	};

	float *pt1, *pt2, *pt3, *pt4;
	bgftexinfo_t *tex;
	vec2 st;

	for(i=0; i<8; i++)
	{
		vtxa[i*3+0]=p->min[0];
		vtxa[i*3+1]=p->min[1];
		vtxa[i*3+2]=p->min[2];
		if(i&1)vtxa[i*3+0]=p->max[0];
		if(i&2)vtxa[i*3+1]=p->max[1];
		if(i&4)vtxa[i*3+2]=p->max[2];

		vtxa[i*3+0]+=p->org[0];
		vtxa[i*3+1]+=p->org[1];
		vtxa[i*3+2]+=p->org[2];
	}

	glEnable(GL_TEXTURE_2D);

	for(i=0; i<6; i++)
	{
		pt1=vtxa+(vtxb[i*4+0]*3);
		pt2=vtxa+(vtxb[i*4+1]*3);
		pt3=vtxa+(vtxb[i*4+2]*3);
		pt4=vtxa+(vtxb[i*4+3]*3);

		tex=Render_SelectTexture(&vtna[i*3]);
		Draw_Bind(tex->num);

		glBegin(GL_POLYGON);

		r=0.5+(sin(pt1[0])*0.5);
		g=0.5+(sin(pt1[1])*0.5);
		b=0.5+(sin(pt1[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=0;
		st[1]=1;
		Render_MapST(tex, pt1, st);
		glTexCoord2fv(st);
		glVertex3fv(pt1);

		r=0.5+(sin(pt2[0])*0.5);
		g=0.5+(sin(pt2[1])*0.5);
		b=0.5+(sin(pt2[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=0;
		st[1]=0;
		Render_MapST(tex, pt2, st);
		glTexCoord2fv(st);
		glVertex3fv(pt2);

		r=0.5+(sin(pt3[0])*0.5);
		g=0.5+(sin(pt3[1])*0.5);
		b=0.5+(sin(pt3[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=1;
		st[1]=0;
		Render_MapST(tex, pt3, st);
		glTexCoord2fv(st);
		glVertex3fv(pt3);

		r=0.5+(sin(pt4[0])*0.5);
		g=0.5+(sin(pt4[1])*0.5);
		b=0.5+(sin(pt4[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=1;
		st[1]=1;
		Render_MapST(tex, pt4, st);
		glTexCoord2fv(st);
		glVertex3fv(pt4);

		glEnd();
	}

	return(0);
}

int Render_Mesh(piece_t *p)
{
	int i, j;
	float *v0, *v1, *v2;
	float r, g, b;

	for(i=0; i<p->numpolys; i++)
	{
		j=p->firstpoly+i;
		v0=vecbuf+(polybuf[(j*4)+0]*6)+(p->firstvert*6);
		v1=vecbuf+(polybuf[(j*4)+1]*6)+(p->firstvert*6);
		v2=vecbuf+(polybuf[(j*4)+2]*6)+(p->firstvert*6);

		glBegin(GL_POLYGON);

		r=0.5+(sin(v0[0])*0.5);
		g=0.5+(sin(v0[1])*0.5);
		b=0.5+(sin(v0[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glVertex3fv(v0);

		r=0.5+(sin(v1[0])*0.5);
		g=0.5+(sin(v1[1])*0.5);
		b=0.5+(sin(v1[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glVertex3fv(v1);

		r=0.5+(sin(v2[0])*0.5);
		g=0.5+(sin(v2[1])*0.5);
		b=0.5+(sin(v2[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glVertex3fv(v2);
		glEnd();
	}
	return(0);
}

int Render_Disk(piece_t *p)
{
	int i;
	float r, g, b;

	float a1, x1, y1;
	float a2, x2, y2;
	vec3 pt, pt2;

	bgftexinfo_t *tex;
	vec2 st;

	glEnable(GL_TEXTURE_2D);
//	Draw_Bind(texture[p->skin].num);

	tex=Render_SelectTexture(p->dir);
	Draw_Bind(tex->num);

	glBegin(GL_TRIANGLE_FAN);

	r=0.5+(sin(p->org[0])*0.5);
	g=0.5+(sin(p->org[1])*0.5);
	b=0.5+(sin(p->org[2])*0.5);
//	glColor4f(r, g, b, 1.0);
	st[0]=0.5;
	st[1]=0.5;
	Render_MapST(tex, p->org, st);
	glTexCoord2fv(st);
//	glTexCoord2f(0.5, 0.5);
	glVertex3fv(p->org);

	for(i=0; i<16; i++)
	{
		a1=-((M_PI*2)/16)*i;
		x1=sin(a1);
		y1=cos(a1);

		a2=-((M_PI*2)/16)*(i+1);
		x2=sin(a2);
		y2=cos(a2);

		pt[0]=x1*p->trad;
		pt[1]=y1*p->trad;
		pt[2]=0;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=1-(x1+1)*0.5;
		st[1]=(y1+1)*0.5;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
//		glTexCoord2f(1-(x1+1)*0.5, (y1+1)*0.5);
		glVertex3fv(pt);

		pt[0]=x2*p->trad;
		pt[1]=y2*p->trad;
		pt[2]=0;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		st[0]=1-(x2+1)*0.5;
		st[1]=(y2+1)*0.5;
		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
//		glTexCoord2f(1-(x2+1)*0.5, (y2+1)*0.5);
		glVertex3fv(pt);
	}
	glEnd();

	return(0);
}

int Render_Diplane(piece_t *p)
{
	int i, j, ip, jp;
	int horz, vert;
	float h1, h2, h3, h4;
	float xs, ys;
	vec3 pt;
	vec2 st;
	bgftexinfo_t *tex;

	glEnable(GL_TEXTURE_2D);

	horz=p->hmapwidth;
	vert=p->hmapheight;

	pt[0]=0;
	pt[1]=0;
	pt[2]=1;
	tex=Render_SelectTexture(pt);
	Draw_Bind(tex->num);

	xs=p->trad/horz;
	ys=p->trad/vert;

	for(i=0; i<vert-1; i++)
		for(j=0; j<horz-1; j++)
	{
		ip=i+1;
		jp=j+1;
		h1=p->hmap[(i*horz+j)*4]*p->hmapscale;
		h2=p->hmap[(ip*horz+j)*4]*p->hmapscale;
		h3=p->hmap[(ip*horz+jp)*4]*p->hmapscale;
		h4=p->hmap[(i*horz+jp)*4]*p->hmapscale;

		if((h1+h2+h3+h4)<(p->hmapscale*16))continue;

		glBegin(GL_POLYGON);

		pt[0]=j*xs+p->org[0]-(p->trad/2);
		pt[1]=i*ys+p->org[1]-(p->trad/2);
		pt[2]=h1+p->org[2];
		st[0]=j*(1.0/horz);
		st[1]=i*(1.0/vert);
//		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=j*xs+p->org[0]-(p->trad/2);
		pt[1]=ip*ys+p->org[1]-(p->trad/2);
		pt[2]=h2+p->org[2];
		st[0]=j*(1.0/horz);
		st[1]=ip*(1.0/vert);
//		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=jp*xs+p->org[0]-(p->trad/2);
		pt[1]=ip*ys+p->org[1]-(p->trad/2);
		pt[2]=h3+p->org[2];
		st[0]=jp*(1.0/horz);
		st[1]=ip*(1.0/vert);
//		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		pt[0]=jp*xs+p->org[0]-(p->trad/2);
		pt[1]=i*ys+p->org[1]-(p->trad/2);
		pt[2]=h4+p->org[2];
		st[0]=jp*(1.0/horz);
		st[1]=i*(1.0/vert);
//		Render_MapST(tex, pt, st);
		glTexCoord2fv(st);
		glVertex3fv(pt);

		glEnd();
	}
}

int Render_Piece(piece_t *p)
{
	piece_t *c;

//	return(0);

//	printf("piece\n");
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(p->transform);

	if(p->skin)
		tex_stack[tex_stackpos++]=p->skin;

	switch(p->type)
	{
	case PIECE_MESH:
		Render_Mesh(p);
		break;
	case PIECE_CUBE:
		Render_Cube(p);
		break;
	case PIECE_CYLINDER:
		Render_Cylinder(p);
		break;
	case PIECE_SPHERE:
		Render_Sphere(p);
		break;
	case PIECE_DISK:
		Render_Disk(p);
		break;
	case PIECE_DIPLANE:
		Render_Diplane(p);
		break;
	default:
		break;
	}

	c=p->first;

	while(c)
	{
		Render_Piece(c);
		c=c->next;
	}

	if(p->skin)
		tex_stackpos--;

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

//	printf("ok\n");

	return(0);
}

int Render_Bone(bone_t *b)
{
	bone_t *c;

//	printf("bone %s\n", b->name);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef (b->org[v_frame*3+0],  b->org[v_frame*3+1],  b->org[v_frame*3+2]);

	glRotatef (b->ang[v_frame*3+0],  1, 0, 0);
	glRotatef (b->ang[v_frame*3+1],  0, 1, 0);
	glRotatef (b->ang[v_frame*3+2],  0, 0, 1);

	if(b->piece)
	{
		Render_Piece(b->piece);
	}

	c=b->first;
	while(c)
	{
		Render_Bone(c);
		c=c->next;
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

//	printf("ok\n");

	return(0);
}

int Render_BgfModinfo(bgfmodinfo_t *inf, int frame)
{
	bone_t *bcur;
	piece_t *pcur;

	v_frame=frame;

	bcur=inf->bones;
	while(bcur)
	{
		Render_Bone(bcur);
		bcur=bcur->next;
	}

	if(inf->bones)return(0);

	pcur=inf->pieces;
	while(pcur)
	{
		Render_Piece(pcur);
		pcur=pcur->next;
	}
	return(0);
}
