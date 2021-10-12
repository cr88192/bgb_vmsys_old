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

VFILE *render_screen;
VFILE *render_keyboard, *render_keymap_dev;
VFILE *render_mouse;

int RenderBgf_Init()
{
	render_screen=vffopen("/devices/gfxdev", "r+b");
	render_keyboard=vffopen("/devices/keyboard", "r+b");
	render_keymap_dev=vffopen("/devices/keyboard/keymap", "r+b");
	render_mouse=vffopen("/devices/mouse", "r+b");

//	render_zoom=1<<8;

//	ObjSK_Init();
}

int checkarg(char *s)
{
	int i;
	for(i=1; i<_argc; i++)if(!strcmp(_argv[i], s))return(i);
	return(0);
}

#if 0
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
#endif

int fl=0;

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
			_argv[_argc++]=(char *)strdup(buf);
		}
	}

	core_init();

//	SKVM_Init();
//	GfxDrv_Init();
//	GfxDrv_Start();
	RenderBgf_Init();
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
		vfread(keybuf, 1, 32, render_keymap_dev);

		GfxDrv_BeginDrawing();

		Render_Model();

		GfxDrv_EndDrawing();
	}

	SKVM_DeInit();
}
