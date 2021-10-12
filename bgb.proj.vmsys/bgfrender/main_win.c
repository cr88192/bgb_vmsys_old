#include "bgfrender.h"

int main_kill;

char *_argv[64];
int _argc;

HINSTANCE	global_hInstance;
int			global_nCmdShow;

unsigned char keybuf[32];

vec3 v_origin, v_angles;
int v_frame;

extern bgftexinfo_t *tex_stack[16];
extern int tex_stackpos;

VFILE *render_screen;
VFILE *render_keyboard, *render_keymap_dev;
VFILE *render_mouse;

byte render_keymap[32];
int render_keybuf[64], render_keybuf_pos;

extern bone_t *mod_bones;
extern piece_t *mod_pieces;
extern bgftexinfo_t *mod_textures;

bgfmodinfo_t *render_model;

int RenderBgf_Init()
{
//	render_screen=vffopen("/devices/gfxdev", "r+b");
//	render_keyboard=vffopen("/devices/keyboard", "r+b");
//	render_keymap_dev=vffopen("/devices/keyboard/keymap", "r+b");
//	render_mouse=vffopen("/devices/mouse", "r+b");

	Render_Init();

//	render_zoom=1<<8;

//	ObjSK_Init();
	BGF_Init();
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
	return(render_keymap[key/8]&(1<<(key&7)));
}

int Render_Model()
{
	float org[3], pt[4];
	int i;
	float *v0, *v1, *v2;
	float r, g, b;

	bone_t *bcur;
	piece_t *pcur;
	bgftexinfo_t *ti;

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

//	return(0);

	Draw_SetPerspective_3D(4.0/3.0, 90, org, org, 0, 0, 800, 600);

//	return(0);

	glTranslatef (-v_origin[0],  -v_origin[1],  -v_origin[2]);

//	return(0);

	glRotatef (-v_angles[0],  1, 0, 0);
	glRotatef (-v_angles[1],  0, 1, 0);
	glRotatef (-v_angles[2],  0, 0, 1);


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_LIGHTING);

	pt[0]=v_origin[0];
	pt[1]=v_origin[1];
	pt[2]=v_origin[2];
	pt[3]=1;
	glLightfv(GL_LIGHT0, GL_POSITION, pt);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1/1000.0);

	glEnable(GL_LIGHT0);

//	pt[0]=0.5;
//	pt[1]=0.5;
//	pt[2]=0.5;
//	pt[3]=0;
//	glMaterialfv(GL_FRONT, GL_SPECULAR, pt);
//	glMaterialf(GL_FRONT, GL_SHININESS, 0.5);

	tex_stackpos=0;

	mod_bones=render_model->bones;
	mod_pieces=render_model->pieces;
	mod_textures=render_model->textures;

	if(mod_bones)
//	if(0)
	{
//		Render_Bone(mod_bones);
		bcur=mod_bones;
		while(bcur)
		{
			Render_Bone(bcur);
			bcur=bcur->next;
		}
		glDisable(GL_LIGHTING);

		glDisable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		return(0);
	}
	if(mod_pieces)
	{
//		for(i=0; i<pieces; i++)
//			Render_Piece(&piece[i]);
		pcur=mod_pieces;
		while(pcur)
		{
			Render_Piece(pcur);
			pcur=pcur->next;
		}

		glDisable(GL_LIGHTING);
		return(0);
	}

//	printf("polys %d\n", polys);

	ti=mod_findskin("skin0");
	if(!ti)
	{
		printf("no skin\n");
		ti=mod_textures;
	}
	glEnable(GL_TEXTURE_2D);
	Draw_Bind(ti->num);
	printf("%d\n", ti->num);

	for(i=0; i<polys; i++)
	{
		v0=vecbuf+(polybuf[(i*4)+0]*6)+(v_frame*vecs*6);
		v1=vecbuf+(polybuf[(i*4)+1]*6)+(v_frame*vecs*6);
		v2=vecbuf+(polybuf[(i*4)+2]*6)+(v_frame*vecs*6);

		glBegin(GL_POLYGON);

		r=0.5+(sin(v0[0])*0.5);
		g=0.5+(sin(v0[1])*0.5);
		b=0.5+(sin(v0[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v0[3]/sw, v0[4]/sh);
		glVertex3fv(v0);

		r=0.5+(sin(v1[0])*0.5);
		g=0.5+(sin(v1[1])*0.5);
		b=0.5+(sin(v1[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v1[3]/sw, v1[4]/sh);
		glVertex3fv(v1);

		r=0.5+(sin(v2[0])*0.5);
		g=0.5+(sin(v2[1])*0.5);
		b=0.5+(sin(v2[2])*0.5);
//		glColor4f(r, g, b, 1.0);
		glTexCoord2f(v2[3]/sw, v2[4]/sh);
		glVertex3fv(v2);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	return(0);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char buf[256], *s, *t;
	int i, j, x, y, w, h;
	FILE *infd;
	char *fbuf, *fcur;
	elem obj;
	bgftexinfo_t *ti;
	bgfmodinfo_t *mi;

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

	SKVM_Init();
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

//	pieces=0;
//	bones=0;

//	textures=0;

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
	ti=BGF_NewTexture();
	strcpy(ti->name, "nulltex");
	ti->num=Tex_LoadTexture(8, 8, buf, 0);
	ti->width=8;
	ti->height=8;
	//textures=1;
	mod_textures=ti;


	infd=fopen(_argv[1], "rb");

	fseek(infd, 0, 2);
	i=ftell(infd);
	fbuf=malloc(i+16);
	memset(fbuf, 0, i+16);
	fseek(infd, 0, 0);
	fread(fbuf, 1, i, infd);


#if 0
	fcur=fbuf;

	while(*fcur)
	{
		s=fcur;
		obj=ScmParse_Line(&fcur, 0);
		fcur=ScmParse_EatWhite(fcur);
		if(obj==MISC_UNDEFINED)break;

		mod_decode (obj);
	}
#endif

	mi=BGF_LoadModel(fbuf);
	free(fbuf);

	render_model=mi;

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
//		printf("frame start\n");
		vfread(render_keymap, 1, 32, render_keymap_dev);

		while(vfinready(render_keyboard))
		{
			i=vfgetc(render_keyboard)<<8;
			i+=vfgetc(render_keyboard);

			render_keybuf[render_keybuf_pos++]=i;
		}

//		UICon_Think();

//		GfxDrv_BeginDrawing();
		GfxApi_BeginDrawing(render_screen);

		glClearColor (0.25, 0.25, 0.25, 1);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		UICon_Draw();

		Render_Model();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);


//		Render_FrameSL();

		GfxApi_EndDrawing(render_screen);
//		GfxDrv_EndDrawing();

//		printf("frame end\n");
	}

	SKVM_DeInit();
}
