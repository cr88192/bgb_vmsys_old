//#include <general.h>
//#include <graphics/render.h>

#include <GL/GL.h>
#include <math.h>

//extern int leftcoords;

#define DRAWPARMS_SOLID	1
int drawparms;
//teximage *conchars, *conback;

//extern vec4f color_white, color_black;
typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef float vec4f[4];
typedef float vec16[16];

int screen_xorg, screen_yorg;
int screen_xsize, screen_ysize;
vec2 screen_org;
float screen_xpsize, screen_ypsize;

vec2 clip_min, clip_max;
static int clip_stack[256], clip_stackpos;
vec2 view_min, view_max;
static int view_stack[256], view_stackpos;


int Draw_PushClip()
{
	clip_stack[clip_stackpos++]=clip_min[0];
	clip_stack[clip_stackpos++]=clip_min[1];
	clip_stack[clip_stackpos++]=clip_max[0];
	clip_stack[clip_stackpos++]=clip_max[1];
	return(0);
}

int Draw_PopClip()
{
	clip_max[1]=clip_stack[--clip_stackpos];
	clip_max[0]=clip_stack[--clip_stackpos];
	clip_min[1]=clip_stack[--clip_stackpos];
	clip_min[0]=clip_stack[--clip_stackpos];

	glScissor (clip_min[0], clip_min[1], clip_max[0]-clip_min[0], clip_max[1]-clip_min[1]);

	return(0);
}

int Draw_SetClip(vec2 min, vec2 max)
{
	vec2 min2, max2;

//	kprint("clip: (%g %g)-(%g %g)\n", min[0], min[1], max[0], max[1]);

	min2[0]=(min[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	min2[1]=(min[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);
	max2[0]=(max[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	max2[1]=(max[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);

//	kprint("clip: (%g %g)-(%g %g)\n", min2[0], min2[1], max2[0], max2[1]);

	if(min2[0]>clip_max[0] || max2[0]<clip_min[0] || min2[1]>clip_max[1] || max2[1]<clip_min[1])
	{
		clip_min[0]=0;
		clip_min[1]=0;
		clip_max[0]=0;
		clip_max[1]=0;
		return(-1);
	}
	clip_min[0]=(min2[0]>clip_min[0])?min2[0]:clip_min[0];
	clip_min[1]=(min2[1]>clip_min[1])?min2[1]:clip_min[1];
	clip_max[0]=(max2[0]<clip_max[0])?max2[0]:clip_max[0];
	clip_max[1]=(max2[1]<clip_max[1])?max2[1]:clip_max[1];

//	kprint("clip: (%g %g)-(%g %g)\n", clip_min[0], clip_min[1], clip_max[0], clip_max[1]);

	glScissor (clip_min[0], clip_min[1], clip_max[0]-clip_min[0], clip_max[1]-clip_min[1]);

	return(0);
}

int Draw_PushView()
{
	Draw_PushClip();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	view_stack[view_stackpos++]=view_min[0];
	view_stack[view_stackpos++]=view_min[1];
	view_stack[view_stackpos++]=view_max[0];
	view_stack[view_stackpos++]=view_max[1];
	return(0);
}

int Draw_PopView()
{
	view_max[1]=view_stack[--view_stackpos];
	view_max[0]=view_stack[--view_stackpos];
	view_min[1]=view_stack[--view_stackpos];
	view_min[0]=view_stack[--view_stackpos];

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glViewport (view_min[0], view_min[1], view_max[0]-view_min[0], view_max[1]-view_min[1]);

	Draw_PopClip();

	return(0);
}

int Draw_SetView(vec2 min, vec2 max)
{
	vec2 min2, max2;

//	kprint("clip: (%g %g)-(%g %g)\n", min[0], min[1], max[0], max[1]);

	min2[0]=(min[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	min2[1]=(min[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);
	max2[0]=(max[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	max2[1]=(max[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);

//	kprint("clip: (%g %g)-(%g %g)\n", min2[0], min2[1], max2[0], max2[1]);

	if(min2[0]>view_max[0] || max2[0]<view_min[0] || min2[1]>view_max[1] || max2[1]<view_min[1])
	{
		view_min[0]=0;
		view_min[1]=0;
		view_max[0]=0;
		view_max[1]=0;
		return(-1);
	}
	view_min[0]=(min2[0]>view_min[0])?min2[0]:view_min[0];
	view_min[1]=(min2[1]>view_min[1])?min2[1]:view_min[1];
	view_max[0]=(max2[0]<view_max[0])?max2[0]:view_max[0];
	view_max[1]=(max2[1]<view_max[1])?max2[1]:view_max[1];

//	kprint("clip: (%g %g)-(%g %g)\n", clip_min[0], clip_min[1], clip_max[0], clip_max[1]);

	glScissor (view_min[0], view_min[1], view_max[0]-view_min[0], view_max[1]-view_min[1]);
	glViewport (view_min[0], view_min[1], view_max[0]-view_min[0], view_max[1]-view_min[1]);

//	glViewport (min2[0], min2[1], max2[0]-min2[0], max2[1]-min2[1]);

	return(0);
}

int Draw_GetView(vec2 min, vec2 max)
{
	min[0]=view_min[0];
	min[1]=view_min[1];
	max[0]=view_max[0];
	max[1]=view_max[1];
	return(0);
}

int Draw_GetView2(vec2 min, vec2 max)
{
	min[0]=(min[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	min[1]=(min[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);
	max[0]=(max[0]-screen_org[0])*(screen_xsize/screen_xpsize)+(screen_xsize*0.5);
	max[1]=(max[1]-screen_org[1])*(screen_ysize/screen_ypsize)+(screen_ysize*0.5);

	return(0);
}

int Draw_SetSolid_2D(float aspect, int xo, int yo, int xs, int ys)
{
//	if(drawparms==DRAWPARMS_SOLID)return(0);
//	drawparms=DRAWPARMS_SOLID;

	glViewport (xo, yo, xs, ys);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();
//	glOrtho (0, w, h, 0, -99999, 99999);
//	glOrtho (0, w, 0, h, -99999, 99999);
//	glOrtho (-1000, 1000, -750, 750, -99999, 99999);
	glOrtho (-1000, 1000, -1000/aspect, 1000/aspect, -99999, 99999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glDisable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor4f (1,1,1,1);
}

int Draw_SetSolid2_2D(float aspect, float size, vec3 org, vec3 angles, int xo, int yo, int xs, int ys)
{
	int h2;

//	printf("%g %g %g\n", org[0], org[1], org[2]);
	h2=size/aspect;

	screen_xorg=xo;
	screen_yorg=yo;
	screen_xsize=xs;
	screen_ysize=ys;

	screen_org[0]=org[0];
	screen_org[1]=org[1];

	screen_xpsize=size*2;
	screen_ypsize=h2*2;

	clip_min[0]=xo;
	clip_min[1]=yo;
	clip_max[0]=xs;
	clip_max[1]=ys;

	clip_stackpos=0;

	view_min[0]=xo;
	view_min[1]=yo;
	view_max[0]=xs;
	view_max[1]=ys;

	view_stackpos=0;

	glViewport (xo, yo, xs, ys);
	glScissor (xo, yo, xs, ys);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

	glOrtho  (-size, size, -h2, h2, -999999999, 999999999);

	glRotatef (-angles[2],  0, 0, 1);
	glRotatef (-angles[0],  1, 0, 0);
	glRotatef (-angles[1],  0, 1, 0);
	glTranslated (-org[0],  -org[1],  -org[2]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glDisable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//	glEnable(GL_STENCIL_TEST);
	glEnable(GL_SCISSOR_TEST);

	glColor4f (1,1,1,1);
}


int Draw_SetOrtho_3D(float aspect, int size, vec3 org, vec3 angles, int x, int y, int w, int h)
{
	int h2;

	glViewport (x, y, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

	h2=size/aspect;
	glOrtho  (-size, size, -h2, h2, -999999999, 999999999);

//	if(leftcoords)
	glScalef(1, 1, -1);

	glRotatef (-angles[2],  0, 0, 1);
	glRotatef (-angles[0],  1, 0, 0);
	glRotatef (-angles[1],  0, 1, 0);
	glTranslatef (-org[0],  -org[1],  -org[2]);

	glDisable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable (GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor4f (0,0,0,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
}

#if 0
extern vec3 mouseorg, mousevec;

int Draw_OrthoGrid(int osize, int gstep, vec3 org, vec3 angles)
{
	vec3	forward, right, up, gorg, gvec, evec;
	vec4	color;
	int		i, j, sym;

//	if(!gstep)
//	gstep=1;
//	while((osize/gstep)>16)gstep<<=1;

	Vec3_CalcAngleVectors(angles, forward, right, up);

	forward[0]=0;
	forward[1]=0;
	if(leftcoords)
		forward[2]=1;
		else forward[2]=-1;

	glColor4f(0, 0, 0, 0.5);

	glBegin(GL_LINES);

	Vec3_MultiplyAdd(org, forward, -1*gstep*2, gorg);
	glVertex3dv(org);
	glVertex3dv(gorg);

	Vec3_MultiplyAdd(org, up, gstep, gvec);
	Vec3_MultiplyAdd(gvec, forward, -gstep, gvec);
	glVertex3dv(org);
	glVertex3dv(gvec);

	Vec3_MultiplyAdd(org, up, -gstep, gvec);
	Vec3_MultiplyAdd(gvec, forward, -gstep, gvec);
	glVertex3dv(org);
	glVertex3dv(gvec);

	Vec3_MultiplyAdd(org, right, gstep, gvec);
	Vec3_MultiplyAdd(gvec, forward, -gstep, gvec);
	glVertex3dv(org);
	glVertex3dv(gvec);

	Vec3_MultiplyAdd(org, right, -gstep, gvec);
	Vec3_MultiplyAdd(gvec, forward, -gstep, gvec);
	glVertex3dv(org);
	glVertex3dv(gvec);

	glEnd();

#if 0 /* origin cross */
	glColor4f(1, 0, 0, 0.5);

	glBegin(GL_LINES);

	glVertex3f(-osize/2, 0, 0);
	glVertex3f(osize/2, 0, 0);

	glVertex3f(0, -osize/2, 0);
	glVertex3f(0, osize/2, 0);

	glVertex3f(0, 0, -osize/2);
	glVertex3f(0, 0, osize/2);
	glEnd();
#endif

#if 0 /* mouse cross */
	glColor4f(0, 0, 1, 0.5);

	glBegin(GL_LINES);

	glVertex3f(mouseorg[0]-osize/8, mouseorg[1], mouseorg[2]);
	glVertex3f(mouseorg[0]+osize/8, mouseorg[1], mouseorg[2]);

	glVertex3f(mouseorg[0], mouseorg[1]-osize/8, mouseorg[2]);
	glVertex3f(mouseorg[0], mouseorg[1]+osize/8, mouseorg[2]);

	glVertex3f(mouseorg[0], mouseorg[1], mouseorg[2]-osize/8);
	glVertex3f(mouseorg[0], mouseorg[1], mouseorg[2]+osize/8);

	glColor4f(0, 1, 0, 0.5);

	glVertex3dv(mouseorg);
	Vec3_MultiplyAdd(mouseorg, mousevec, osize/4, gvec);
	glVertex3dv(gvec);
	glEnd();
#endif

	Vec3_CalcAngleVectors(angles, forward, right, up);

	sym=3; /* 0; */
	if(fabs(forward[0])>fabs(forward[1]) && fabs(forward[0])>fabs(forward[2]))sym=1; /* YZ */
	if(fabs(forward[1])>fabs(forward[0]) && fabs(forward[1])>fabs(forward[2]))sym=2; /* XZ */
	if(fabs(forward[2])>fabs(forward[0]) && fabs(forward[2])>fabs(forward[1]))sym=3; /* XY */
	if(!sym)printf("symetry unaligned.\n");

	gorg[0]=org[0];
	gorg[1]=org[1];
	gorg[2]=org[2];
	if(sym==2 || sym==3)gorg[0]=org[0]-osize*2;
	if(sym==1 || sym==3)gorg[1]=org[1]-osize*2;
	if(sym==1 || sym==2)gorg[2]=org[2]-osize*2;
	gorg[0]=(int)gorg[0]-((int)gorg[0]%gstep);
	gorg[1]=(int)gorg[1]-((int)gorg[1]%gstep);
	gorg[2]=(int)gorg[2]-((int)gorg[2]%gstep);

	glColor4f(0.5, 0.5, 0.5, 0.25);

	gvec[0]=gorg[0];
	gvec[1]=gorg[1];
	gvec[2]=gorg[2];

	glBegin(GL_LINES);

	for(i=0;i<((osize*4)/gstep); i++)
	{
		evec[0]=gvec[0];
		evec[1]=gvec[1];
		evec[2]=gvec[2];

		if(sym==1)evec[1]+=osize*4;
		if(sym==2)evec[0]+=osize*4;
		if(sym==3)evec[0]+=osize*4;

		glVertex3dv(gvec);
		glVertex3dv(evec);

		if(sym==1)gvec[2]+=gstep;
		if(sym==2)gvec[2]+=gstep;
		if(sym==3)gvec[1]+=gstep;
	}
	glEnd();

	gvec[0]=gorg[0];
	gvec[1]=gorg[1];
	gvec[2]=gorg[2];

	glBegin(GL_LINES);
	for(i=0;i<((osize*4)/gstep); i++)
	{
		evec[0]=gvec[0];
		evec[1]=gvec[1];
		evec[2]=gvec[2];

		if(sym==1)evec[2]+=osize*4;
		if(sym==2)evec[2]+=osize*4;
		if(sym==3)evec[1]+=osize*4;

		glVertex3dv(gvec);
		glVertex3dv(evec);

		if(sym==1)gvec[1]+=gstep;
		if(sym==2)gvec[0]+=gstep;
		if(sym==3)gvec[0]+=gstep;
	}
	glEnd();

	return(0);
}

#endif

int Draw_SetPerspective_3D(float aspect, int fov, vec3 org, vec3 angles, int xo, int yo, int xs, int ys)
{
	GLdouble xmin, xmax, ymin, ymax, dst;
	vec16 pos2;

	glViewport (xo, yo, xs, ys);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

//	if(leftcoords)

	dst=0.1;

	xmax = dst*tan(fov*(M_PI/360.0));
	xmin = -xmax;

	ymin = xmin/aspect;
	ymax = xmax/aspect;

	glFrustum  (xmin, xmax, ymin, ymax, dst, 100000);

//	glScalef(1, 1, -1);

	glRotatef (-angles[2],  0, 0, 1);
	glRotatef (-angles[0],  1, 0, 0);
	glRotatef (-angles[1],  0, 1, 0);
	glTranslatef (-org[0],  -org[1],  -org[2]);

//	MatN_SwapOrder(pos, pos2, 4);
//	glMultMatrixd(pos2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glEnable (GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable (GL_CULL_FACE);
	glCullFace (GL_FRONT);
	glFrontFace (GL_CCW);

	glDisable(GL_SCISSOR_TEST);

//	glDisable (GL_CULL_FACE);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor4f (0,0,0,1);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int Draw_Square(int x, int y, int w, int h)
{
	glBegin(GL_QUADS);
	glVertex2f(x,	y);
	glVertex2f(x+w,	y);
	glVertex2f(x+w,	y+h);
	glVertex2f(x,	y+h);
	glEnd();
}

int Draw_FillSquare(int x, int y, int w, int h, vec4f c)
{
	glDisable(GL_TEXTURE_2D);

	glColor4fv(c);

	glBegin(GL_QUADS);
	glVertex2f(x,	y);
	glVertex2f(x,	y+h);
	glVertex2f(x+w,	y+h);
	glVertex2f(x+w,	y);
	glEnd();

	glEnable(GL_TEXTURE_2D);
}

int Draw_Bind(int num)
{
	glBindTexture(GL_TEXTURE_2D, num);
}

#if 0
int Draw_Picture(int x, int y, int w, int h, teximage *tex)
{
	gltexinfo *inf;

	inf=tex->data;

	glBindTexture(GL_TEXTURE_2D, inf->texnum);

	glBegin(GL_QUADS);
	glTexCoord2f(inf->s, inf->t);
	glVertex2f(x, y);
	glTexCoord2f(inf->s, inf->t2);
	glVertex2f(x, y+h);
	glTexCoord2f(inf->s2, inf->t2);
	glVertex2f(x+w, y+h);
	glTexCoord2f(inf->s2, inf->t);
	glVertex2f(x+w, y);
	glEnd();
}

int Draw_PictureCrop(int x, int y, int w, int h, int cx, int cy, int cw, int ch, teximage *tex)
{
	gltexinfo *inf;
	float ns, nt, ns2, nt2;

	inf=tex->data;

	ns=cx;
	nt=cy;
	ns=cx+cw;
	nt=cx+ch;

	ns=ns/tex->width;
	nt=nt/tex->height;
	ns2=ns2/tex->width;
	nt2=nt2/tex->height;

//	ns=nt=0;
//	ns2=nt2=1;

	ns=(inf->s2-inf->s)*ns;
	nt=(inf->t2-inf->t)*nt;
	ns2=(inf->s2-inf->s)*ns2;
	nt2=(inf->t2-inf->t)*nt2;

//	ns=0-ns;
//	ns2=0-ns2;

	glBindTexture(GL_TEXTURE_2D, inf->texnum);

	glBegin(GL_QUADS);
	glTexCoord2f(ns, nt);
	glVertex2f(x, y);
	glTexCoord2f(ns, nt2);
	glVertex2f(x, y+h);
	glTexCoord2f(ns2, nt2);
	glVertex2f(x+w, y+h);
	glTexCoord2f(ns2, nt);
	glVertex2f(x+w, y);
	glEnd();
}

int Draw_Character(int x, int y, int w, int h, vec4f c, int ch)
{
//	Draw_PictureCrop(x, y, w, h, (ch%16)*8, (ch/16)*8, 8, 8, conchars);

	gltexinfo *inf;
	float s, t, s2, t2;

	inf=conchars->data;

	glBindTexture(GL_TEXTURE_2D, inf->texnum);

	s=(ch%16)/16.0;
	t2=1-(ch/16)/16.0;
	s2=(ch%16+1)/16.0;
	t=1-(ch/16+1)/16.0;

//	s=t=0;
//	s2=t2=1;

//	glColor4f(1, 1, 1, 1);
	glColor4fv(c);

	glBegin(GL_QUADS);
	glTexCoord2f(s, t);
	glVertex2f(x, y);
	glTexCoord2f(s, t2);
	glVertex2f(x, y+h);
	glTexCoord2f(s2, t2);
	glVertex2f(x+w, y+h);
	glTexCoord2f(s2, t);
	glVertex2f(x+w, y);
	glEnd();
}

int Draw_String(int x, int y, int n, char *s)
{
	while(*s)
	{
		Draw_Character(x, y, n, n, color_white, *s);
		x+=n;
		s++;
	}
}

int Draw_Bind(teximage *tex)
{
	gltexinfo *inf;

	inf=tex->data;
	glBindTexture(GL_TEXTURE_2D, inf->texnum);
}

#endif

#if 0
int Draw_Init()
{
	kprint("Draw Init.\n");
//	MMGC_AddRoot(&conchars);
//	MMGC_AddRoot(&conback);

//	conchars=Tex_GetTeximage_NoMip("misc/conchars.tga");
//	conback=Tex_GetTeximage_NoMip("misc/conback.tga");
}
#endif
