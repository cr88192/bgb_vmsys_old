//#include <general.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>
#include <GL/GL.h>
//#include <render/keys.h>
#include <general.h>
#include <graphics/render.h>

//the coding of this is horrid...

//typedef float vec3[3];

int main_kill;

unsigned char keybuf[32];


extern float *vecbuf;
extern int vecs, frames, polys;
extern char framenames[256][16];
extern int *polybuf;

typedef struct {
char name[16];
int first, next;

int type; //0=mesh, 1=cube, 2=cylinder, 3=sphere
vec3 min, max;
vec3 org, dir;
float trad, brad, h;

int skin;

//mesh data
int firstvert;
int numverts;

int firstpoly;
int numpolys;
}piece_t;

typedef struct {
char name[16];
float org[64*3];
float ang[64*3];
int piece;
int first, next;
}bone_t;

typedef struct {
char name[16];
int num;
int width, height;
}texinfo_t;

extern piece_t piece[256];
extern int pieces;

extern bone_t bone[256];
extern int bones;

extern texinfo_t texture[256];
extern int textures;

extern int cvec;
extern int sw, sh;

extern vec3 v_origin, v_angles;
extern int v_frame;

extern int fl;

int Draw_SetPerspective_3D(float aspect, int fov, vec3 org, vec3 angles, int xo, int yo, int xs, int ys);

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
}

int Render_Cylinder(piece_t *p)
{
	int i, j;
	float *v0, *v1, *v2;
	float r, g, b;

	float a1, x1, y1;
	float a2, x2, y2;
	float s1, s2;
	vec3 pt, pt2;

	glEnable(GL_TEXTURE_2D);
	Draw_Bind(texture[p->skin].num);

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

		glBegin(GL_POLYGON);

		pt[0]=x1*p->trad;
		pt[1]=y1*p->trad;
		pt[2]=p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s1, 0);
		glVertex3fv(pt);

		pt[0]=x2*p->trad;
		pt[1]=y2*p->trad;
		pt[2]=p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s2, 0);
		glVertex3fv(pt);

		pt[0]=x2*p->brad;
		pt[1]=y2*p->brad;
		pt[2]=-p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s2, 1);
		glVertex3fv(pt);

		pt[0]=x1*p->brad;
		pt[1]=y1*p->brad;
		pt[2]=-p->h/2;
		ptadj(pt, p->dir, p->org, pt2);
		pt[0]=pt2[0]; pt[1]=pt2[1]; pt[2]=pt2[2];
		r=0.5+(sin(pt[0])*0.5);
		g=0.5+(sin(pt[1])*0.5);
		b=0.5+(sin(pt[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s1, 1);
		glVertex3fv(pt);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	return(0);
}

int Render_Sphere(piece_t *p)
{
	int i, j;
	float r, g, b;

	float a1, a2, a3, a4;
	vec3 pt1, pt2, pt3, pt4;
	float s1, s2, s3, s4;
	float t1, t2, t3, t4;

	glEnable(GL_TEXTURE_2D);
	Draw_Bind(texture[p->skin].num);

	for(i=0; i<16; i++)
		for(j=0; j<8; j++)
	{
		a1=((M_PI*2)/16)*i;
		a2=((M_PI*2)/16)*(i+1);
		a3=((M_PI*2)/16)*j;
		a4=((M_PI*2)/16)*(j+1);

		pt1[0]=sin(a3)*sin(a1)*p->trad;
		pt1[1]=sin(a3)*cos(a1)*p->trad;
		pt1[2]=cos(a3)*p->trad;
		s1=(1.0/16.0)*i;
		t1=(-1.0/8.0)*j;

		pt2[0]=sin(a4)*sin(a1)*p->trad;
		pt2[1]=sin(a4)*cos(a1)*p->trad;
		pt2[2]=cos(a4)*p->trad;
		s2=(1.0/16.0)*i;
		t2=(-1.0/8.0)*(j+1);

		pt3[0]=sin(a4)*sin(a2)*p->trad;
		pt3[1]=sin(a4)*cos(a2)*p->trad;
		pt3[2]=cos(a4)*p->trad;
		s3=(1.0/16.0)*(i+1);
		t3=(-1.0/8.0)*(j+1);

		pt4[0]=sin(a3)*sin(a2)*p->trad;
		pt4[1]=sin(a3)*cos(a2)*p->trad;
		pt4[2]=cos(a3)*p->trad;
		s4=(1.0/16.0)*(i+1);
		t4=(-1.0/8.0)*j;

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
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s1, t1);
		glVertex3fv(pt1);

		r=0.5+(sin(pt2[0])*0.5);
		g=0.5+(sin(pt2[1])*0.5);
		b=0.5+(sin(pt2[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s2, t2);
		glVertex3fv(pt2);

		r=0.5+(sin(pt3[0])*0.5);
		g=0.5+(sin(pt3[1])*0.5);
		b=0.5+(sin(pt3[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s3, t3);
		glVertex3fv(pt3);

		r=0.5+(sin(pt4[0])*0.5);
		g=0.5+(sin(pt4[1])*0.5);
		b=0.5+(sin(pt4[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(s4, t4);
		glVertex3fv(pt4);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	return(0);
}

int Render_Diamond(piece_t *p)
{
	int i, j;
	float r, g, b;

	float a1, a2, a3, a4;
	vec3 pt1, pt2, pt3, pt4;

	for(i=0; i<4; i++)
		for(j=0; j<3; j++)
	{
		a1=((M_PI*2)/4)*i;
		a2=((M_PI*2)/4)*(i+1);
		a3=((M_PI*2)/4)*j;
		a4=((M_PI*2)/4)*(j+1);

		pt1[0]=sin(a3)*sin(a1)*p->trad;
		pt1[1]=sin(a3)*cos(a1)*p->trad;
		pt1[2]=cos(a3)*p->trad;

		pt2[0]=sin(a4)*sin(a1)*p->trad;
		pt2[1]=sin(a4)*cos(a1)*p->trad;
		pt2[2]=cos(a4)*p->trad;

		pt3[0]=sin(a4)*sin(a2)*p->trad;
		pt3[1]=sin(a4)*cos(a2)*p->trad;
		pt3[2]=cos(a4)*p->trad;

		pt4[0]=sin(a3)*sin(a2)*p->trad;
		pt4[1]=sin(a3)*cos(a2)*p->trad;
		pt4[2]=cos(a3)*p->trad;

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
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt1);

		r=0.5+(sin(pt2[0])*0.5);
		g=0.5+(sin(pt2[1])*0.5);
		b=0.5+(sin(pt2[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt2);

		r=0.5+(sin(pt3[0])*0.5);
		g=0.5+(sin(pt3[1])*0.5);
		b=0.5+(sin(pt3[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt3);

		r=0.5+(sin(pt4[0])*0.5);
		g=0.5+(sin(pt4[1])*0.5);
		b=0.5+(sin(pt4[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt4);

		glEnd();
	}

	return(0);
}

int Render_Cube(piece_t *p)
{
	int i, j;
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

	float *pt1, *pt2, *pt3, *pt4;

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


	for(i=0; i<6; i++)
	{
		pt1=vtxa+(vtxb[i*4+0]*3);
		pt2=vtxa+(vtxb[i*4+1]*3);
		pt3=vtxa+(vtxb[i*4+2]*3);
		pt4=vtxa+(vtxb[i*4+3]*3);

		glBegin(GL_POLYGON);

		r=0.5+(sin(pt1[0])*0.5);
		g=0.5+(sin(pt1[1])*0.5);
		b=0.5+(sin(pt1[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt1);

		r=0.5+(sin(pt2[0])*0.5);
		g=0.5+(sin(pt2[1])*0.5);
		b=0.5+(sin(pt2[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt2);

		r=0.5+(sin(pt3[0])*0.5);
		g=0.5+(sin(pt3[1])*0.5);
		b=0.5+(sin(pt3[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt3);

		r=0.5+(sin(pt4[0])*0.5);
		g=0.5+(sin(pt4[1])*0.5);
		b=0.5+(sin(pt4[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(pt4);

		glEnd();
	}
}

int Render_Mesh(piece_t *p)
{
	int i, j;
	float *v0, *v1, *v2;
	float r, g, b;

	float a1, x1, y1;
	float a2, x2, y2;
	vec3 pt, pt2;

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
		glColor4f(r, g, b, 1.0);
		glVertex3fv(v0);

		r=0.5+(sin(v1[0])*0.5);
		g=0.5+(sin(v1[1])*0.5);
		b=0.5+(sin(v1[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(v1);

		r=0.5+(sin(v2[0])*0.5);
		g=0.5+(sin(v2[1])*0.5);
		b=0.5+(sin(v2[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glVertex3fv(v2);
		glEnd();
	}
	return(0);
}

int Render_Piece(piece_t *p)
{
	piece_t *c;

//	printf("piece\n");

	switch(p->type)
	{
	case 0:
		Render_Mesh(p);
		break;
	case 1:
		Render_Cube(p);
		break;
	case 2:
		Render_Cylinder(p);
		break;
	case 3:
		Render_Sphere(p);
		break;
	default:
		break;
	}

//	printf("ok\n");

	if(p->first == -1)return(0);
	c=&piece[p->first];

	while(1)
	{
		Render_Piece(c);
		if(c->next == -1)break;
		c=&piece[c->next];
	}
	return(0);
}

int Render_Bone(bone_t *b)
{
	int c;

//	printf("bone\n");

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef (b->org[v_frame*3+0],  b->org[v_frame*3+1],  b->org[v_frame*3+2]);

	glRotatef (b->ang[v_frame*3+0],  1, 0, 0);
	glRotatef (b->ang[v_frame*3+1],  0, 1, 0);
	glRotatef (b->ang[v_frame*3+2],  0, 0, 1);

	if(b->piece != -1)
	{
		Render_Piece(&piece[b->piece]);
	}

	c=b->first;
	while(c!=-1)
	{
		Render_Bone(&bone[c]);
		c=bone[c].next;
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

//	printf("ok\n");
}

int Render_Model()
{
	float org[3], ang[3];
	int i;
	float *v0, *v1, *v2;
	float r, g, b;

	org[0]=0;
	org[1]=0;
	org[2]=0;

	if(Key_Check(K_LEFTARROW))v_angles[2]-=1;
	if(Key_Check(K_RIGHTARROW))v_angles[2]+=1;
	if(Key_Check(K_UPARROW))v_angles[0]-=1;
	if(Key_Check(K_DOWNARROW))v_angles[0]+=1;
	if(Key_Check(K_DEL))v_origin[2]-=1;
	if(Key_Check(K_END))v_origin[2]+=1;

	if(Key_Check(','))
	{
		if(!fl)
			v_frame-=1;
		fl=1;
	}else if(Key_Check('.'))
	{
		if(!fl)
			v_frame+=1;
		fl=1;
	}else fl=0;

//	if(v_frame>=frames)v_frame=frames-1;
//	if(v_frame<0)v_frame=0;

	if(v_frame>=frames)v_frame=0;
	if(v_frame<0)v_frame=frames-1;

//	printf("frame %d %s\n", v_frame, framenames[v_frame]);

//	v_frame=0;

	Draw_SetPerspective_3D(4.0/3.0, 90, org, org, 0, 0, 800, 600);

	glTranslatef (-v_origin[0],  -v_origin[1],  -v_origin[2]);

	glRotatef (-v_angles[0],  1, 0, 0);
	glRotatef (-v_angles[1],  0, 1, 0);
	glRotatef (-v_angles[2],  0, 0, 1);

	glDisable(GL_TEXTURE_2D);
//	glDisable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	if(bones)
		return(Render_Bone(&bone[0]));
	if(pieces)
	{
		for(i=0; i<pieces; i++)
			Render_Piece(&piece[i]);
		return(0);
	}

//	printf("polys %d\n", polys);

	i=mod_findskin("skin0");
	if(i==-1)
	{
		printf("no skin\n");
		i=0;
	}
	glEnable(GL_TEXTURE_2D);
	Draw_Bind(texture[i].num);
	printf("%d\n", texture[i].num);

	for(i=0; i<polys; i++)
	{
		v0=vecbuf+(polybuf[(i*4)+0]*6)+(v_frame*vecs*6);
		v1=vecbuf+(polybuf[(i*4)+1]*6)+(v_frame*vecs*6);
		v2=vecbuf+(polybuf[(i*4)+2]*6)+(v_frame*vecs*6);

		glBegin(GL_POLYGON);

		r=0.5+(sin(v0[0])*0.5);
		g=0.5+(sin(v0[1])*0.5);
		b=0.5+(sin(v0[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v0[3]/sw, v0[4]/sh);
		glVertex3fv(v0);

		r=0.5+(sin(v1[0])*0.5);
		g=0.5+(sin(v1[1])*0.5);
		b=0.5+(sin(v1[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v1[3]/sw, v1[4]/sh);
		glVertex3fv(v1);

		r=0.5+(sin(v2[0])*0.5);
		g=0.5+(sin(v2[1])*0.5);
		b=0.5+(sin(v2[2])*0.5);
		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v2[3]/sw, v2[4]/sh);
		glVertex3fv(v2);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}
