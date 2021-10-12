//#include <general.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>
#include <GL/GL.h>
#include <render/keys.h>

#include <scmcc.h>

//the coding of this is horrid...

typedef float vec3[3];

int main_kill;

char *_argv[64];
int _argc;

HINSTANCE	global_hInstance;
int			global_nCmdShow;

unsigned char keybuf[32];


float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

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

piece_t piece[256];
int pieces;

bone_t bone[256];
int bones;

texinfo_t texture[256];
int textures;

int cvec;
int sw, sh;

vec3 v_origin, v_angles;
int v_frame;


int Draw_SetPerspective_3D(float aspect, int fov, vec3 org, vec3 angles, int xo, int yo, int xs, int ys);

int checkarg(char *s)
{
	int i;
	for(i=1; i<_argc; i++)if(!strcmp(_argv[i], s))return(i);
	return(0);
}

int kprint(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);
}

int panic(char *s, ...)
{
	va_list lst;

	printf("panic: ");
	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);
	abort();
}

static int fl=0;

int Key_Event(int key, int state)
{
//	printf("key %s '%c'\n", state?"press":"release", key);

	if(state)keybuf[key/8]|=1<<(key&7);
		else keybuf[key/8]&=~(1<<(key&7));

	fl=0;
}

int Key_Check(int key)
{
	return(keybuf[key/8]&(1<<(key&7)));
}

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

	Draw_SetPerspective_3D(4.0/3.0, 90, org, org, 0, 0, 640, 480);

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

int mod_findpiece(char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed pieces
//	printf("find %s\n", name);
	for(i=0; i<pieces; i++)
	{
//		printf("p %s\n", piece[i].name);
		if(!strcmp(name, piece[i].name))return(i);
	}
//	printf("fail\n");
	return(-1);
}

int mod_findbone(int par, char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed bones

	if(par==-1)par=0;
	i=bone[par].first;

	for(i=0; i<bones; i++)
		if(!strcmp(name, bone[i].name))return(i);
//	while(i!=-1)
//	{
//		if(!strcmp(name, bone[i].name))return(i);
//		i=bone[i].next;
//	}
	return(-1);
}

int mod_findskin(char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed skins

	printf("find %s\n", name);

	for(i=0; i<textures; i++)
	{
		printf("s %s\n", texture[i].name);
		if(!strcmp(name, texture[i].name))return(i);
	}
	printf("fail\n");
	return(-1);
}

int bone_ref=-1;
int piece_ref=-1;

int mod_decode(elem obj)
{
	elem cur;
	int i, j, w, h;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("bgf2alias: non-list parsed top level\n");
	}

//	frames=0;


	if(CAR(obj) == SYM("cube"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=1;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;

		pieces++;
		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;
	}

	if(CAR(obj) == SYM("sphere"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=3;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;

		pieces++;

		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;
	}

	if(CAR(obj) == SYM("cylinder"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=2;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;
		pieces++;

		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;

	}

	if(CAR(obj) == SYM("skin"))
	{
		i=mod_findskin(ELEM_TOSYMBOL(CADR(obj)));
		if(i==-1)
		{
			j=Tex_LoadFile(ELEM_TOSTRING(CADDR(obj)), &w, &h);
			i=textures++;
			strcpy(texture[i].name, ELEM_TOSYMBOL(CADR(obj)));
			texture[i].num=j;
			texture[i].width=w;
			texture[i].height=h;
		}
		if(piece_ref != -1)
		{
			piece[piece_ref].skin=i;
		}
	}
	if(CAR(obj) == SYM("min"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].min[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].min[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].min[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("max"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].max[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].max[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].max[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("dir"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].dir[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].dir[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].dir[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("radius-top"))
	{
		piece[piece_ref].trad=TOFLOAT(CADR(obj));		
	}
	if(CAR(obj) == SYM("radius-bottom"))
	{
		piece[piece_ref].brad=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("radius"))
	{
		piece[piece_ref].trad=TOFLOAT(CADR(obj));		
		piece[piece_ref].brad=TOFLOAT(CADR(obj));		
	}
	if(CAR(obj) == SYM("height"))
	{
		piece[piece_ref].h=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("org"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].org[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].org[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].org[2]=TOFLOAT(CADDDR(obj));
		}
		if(bone_ref != -1)
		{
			bone[bone_ref].org[frames*3+0]=TOFLOAT(CADR(obj));
			bone[bone_ref].org[frames*3+1]=TOFLOAT(CADDR(obj));
			bone[bone_ref].org[frames*3+2]=TOFLOAT(CADDDR(obj));
			if(!frames)for(i=1; i<64; i++)
			{
				bone[bone_ref].org[i*3+0]=bone[bone_ref].org[0];
				bone[bone_ref].org[i*3+1]=bone[bone_ref].org[1];
				bone[bone_ref].org[i*3+2]=bone[bone_ref].org[2];
			}
		}
	}

	if(CAR(obj) == SYM("angle"))
	{
		bone[bone_ref].ang[frames*3+0]=TOFLOAT(CADR(obj));
		bone[bone_ref].ang[frames*3+1]=TOFLOAT(CADDR(obj));
		bone[bone_ref].ang[frames*3+2]=TOFLOAT(CADDDR(obj));

		if(!frames)for(i=1; i<64; i++)
		{
			bone[bone_ref].ang[i*3+0]=bone[bone_ref].ang[0];
			bone[bone_ref].ang[i*3+1]=bone[bone_ref].ang[1];
			bone[bone_ref].ang[i*3+2]=bone[bone_ref].ang[2];
		}
	}

	if(CAR(obj) == SYM("bone"))
	{
		j=-1;

//		i=0;
//		if(bone_ref != -1)i=bone_ref;

		if(CADR(obj) != MISC_NULL)
			j=mod_findbone(0, ELEM_TOSYMBOL(CADR(obj)));

		if(j == -1)
		{
			if(CADR(obj) != MISC_NULL)
				strcpy(bone[bones].name, ELEM_TOSYMBOL(CADR(obj)));
			bone[bones].first=-1;
			bone[bones].next=-1;
			bone[bones].piece=-1;
			bones++;
			j=bones-1;

			printf("bone %d %s\n", j, bone[j].name);

			if(bone_ref != -1)
			{
				bone[j].next=bone[bone_ref].first;
				bone[bone_ref].first=bones-1;
			}
		}

		i=bone_ref;
		bone_ref=j;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		bone_ref=i;
	}

	if(CAR(obj) == SYM("piece"))
	{
		printf("piece\n");
		if(CDDR(obj) != MISC_EOL)
		{
			if(CADR(obj) != MISC_NULL)
				strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
			piece[pieces].first=-1;
			piece[pieces].next=-1;

			printf("piece def %s\n", piece[pieces].name);

			if(piece_ref != -1)
			{
				piece[pieces].next=piece[piece_ref].first;
				piece[piece_ref].first=pieces;
			}

			piece[pieces].firstvert=cvec;
			piece[pieces].firstpoly=polys;

			j=pieces;
			pieces++;

			i=piece_ref;
			piece_ref = j;

			cur=CDDR(obj);
			while(cur!=MISC_EOL)
			{
				mod_decode (CAR(cur));
				cur=CDR(cur);
			}
			piece_ref=i;

			piece[j].numverts=cvec-piece[j].firstvert;
			piece[j].numpolys=polys-piece[j].firstpoly;
		}
		if(bone_ref != -1)
		{
			printf("piece bone ref %d\n", bone_ref);
			bone[bone_ref].piece=
				mod_findpiece(ELEM_TOSYMBOL(CADR(obj)));
		}
	}

	if(CAR(obj) == SYM("frameset"))
	{
		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("frame"))
	{
		strcpy(framenames[frames], ELEM_TOSYMBOL(CADR(obj)));
//		printf("%s\n", framenames[frames-1]);

		if(!vecs)vecs=LENGTH(CDDR(obj));

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		frames++;
	}
	if(CAR(obj) == SYM("vertices"))
	{
		vecs=TOINT(LENGTH(CDR(obj)));
//		sprintf(framenames[frames++], "frame%d", frames);

		cur=CDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
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
			mod_decode (CAR(cur));
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

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char buf[256], *s, *t;
	int i, j, x, y, w, h;
	FILE *infd;
	char *fbuf, *fcur;
	elem obj;

	global_hInstance = hInstance;
	global_nCmdShow = nCmdShow;

	_argv[0]="";
	_argc=1;

	s=lpCmdLine;
	while(*s)
	{
		while(*s && (*s<=' '))s++;
		if(*s)
		{
			t=buf;
			while((*s>' '))*t++=*s++;
			*t++=0;
			_argv[_argc++]=strdup(buf);
		}
	}

	SKVM_Init();
	GfxDrv_Init();
	GfxDrv_Start();
	Tex_Init2();


	vecbuf=malloc(256*1024*sizeof(float)*6);
	polybuf=malloc(4096*3*sizeof(int));

	vecs=0;
	frames=0;
	cvec=0;
	polys=0;

	pieces=0;
	bones=0;

	textures=0;

	sw=320;
	sh=200;

//basic grid skin
	memset(buf, 0, 256);
	for(i=0; i<64; i++)
		buf[i*4+3]=255;

	for(i=0; i<4; i++)for(j=0; j<4; j++)if((i+j)&1)
	{
		memset(buf+((i*2)*32)+(j*8), 255, 8);
		memset(buf+((i*2+1)*32)+(j*8), 255, 8);
	}
	strcpy(texture[0].name, "nulltex");
	texture[0].num=Tex_LoadTexture(8, 8, buf, 0);
	texture[0].width=8;
	texture[0].height=8;
	textures=1;


	infd=fopen(_argv[1], "rb");

	fseek(infd, 0, 2);
	i=ftell(infd);
	fbuf=malloc(i+16);
	memset(fbuf, 0, i+16);
	fseek(infd, 0, 0);
	fread(fbuf, 1, i, infd);


	fcur=fbuf;

	while(*fcur)
	{
		s=fcur;
		obj=ScmParse_Line(&fcur, 0);
		fcur=ScmParse_EatWhite(fcur);
		if(obj==MISC_UNDEFINED)break;

		mod_decode (obj);
	}
	free(fbuf);

	main_kill=0;

	v_origin[0]=0;
	v_origin[1]=0;
	v_origin[2]=64;

	v_angles[0]=0;
	v_angles[1]=0;
	v_angles[2]=0;

	v_angles[0]=90;

	while(!main_kill)
	{
		GfxDrv_BeginDrawing();

		Render_Model();

		GfxDrv_EndDrawing();
	}

	SKVM_DeInit();
}
