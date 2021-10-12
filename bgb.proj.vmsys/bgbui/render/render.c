#include <general.h>
#include <graphics/render.h>
#include <graphics/gfxapi.h>

extern int (*condev_printhook)(char *s);
int UICon_Print(char *s);

VFILE *render_screen;
VFILE *render_keyboard, *render_keymap_dev;
VFILE *render_mouse;

byte render_keymap[32];
int render_keybuf[64], render_keybuf_pos;

float render_zoom, render_origin[2];

int render_mouse_pos[2], render_mouse_b;
vec2 render_mouse_origin;

int *render_stack;
int render_stackpos;

float *render_fstack;
int render_fstackpos;

int render_gridtex;
int render_3dmode;
int render_3dmouse;

float render3d_angles[2];
float render3d_origin[3];

int Render_Init()
{
	char tex[16*16*4];
	int i, j, k, l;

	kprint("Render Init.\n");

	render_screen=vffopen("/devices/gfxdev", "r+b");
	render_keyboard=vffopen("/devices/keyboard", "r+b");
	render_keymap_dev=vffopen("/devices/keyboard/keymap", "r+b");
	render_mouse=vffopen("/devices/mouse", "r+b");

	render_zoom=0.25;

	render_stack=kalloc(1024*sizeof(int));
	render_stackpos=0;

	render_fstack=kalloc(1024*sizeof(float));
	render_fstackpos=0;

	ObjSK_Init();
	Render3D_Init();
	Obj3D_Init();

	memset(tex, 255, 16*16*4);
	for(i=0; i<4; i++)for(j=0; j<4; j++)
	{
		if((i+j)&1)
			for(k=0; k<4; k++)for(l=0; l<4; l++)
		{
			tex[((i*16*4)+(j*4)+(k*16)+l)*4+0]=0;
			tex[((i*16*4)+(j*4)+(k*16)+l)*4+1]=0;
			tex[((i*16*4)+(j*4)+(k*16)+l)*4+2]=0;
		}
	}
	render_gridtex=
		GfxApi_Texture(render_screen, tex, 0, 16, 16, GFXVAR_RGBA32);

	kprint("gridtex %d\n", render_gridtex);

//	condev_printhook=&UICon_Print;
	Condev_SetPrintHook(&UICon_Print);

	UICon_Print("UICON\n");
//	BGF_Init();
}

int Render_PollKey(int key)
{
	if(key<0 || key>255)return(0);
	if(render_keymap[key/8]&(1<<(key&7)))return(1);
	return(0);
}

int Render_Translate(float x, float y)
{
	GfxApi_Translate(render_screen, x, y);

	render_mouse_origin[0]-=x;
	render_mouse_origin[1]-=y;
	return(0);
}

int Render_Scale(float x, float y)
{
	GfxApi_Scale(render_screen, x, y);
	return(0);
}

int Render_PushClip()
{
	return(0);
}

int Render_PopClip()
{
	return(0);
}

int Render_SetClip(vec2 m, vec2 n)
{
	return(0);
}

int Render_PushState()
{
	GfxApi_PushMatrix(render_screen);
	Render_PushClip();

	render_fstack[render_fstackpos++]=render_mouse_origin[0];
	render_fstack[render_fstackpos++]=render_mouse_origin[1];
	return(0);
}

int Render_PopState()
{
	render_mouse_origin[1]=render_fstack[--render_fstackpos];
	render_mouse_origin[0]=render_fstack[--render_fstackpos];

	Render_PopClip();
	GfxApi_PopMatrix(render_screen);
	return(0);
}

int Render_Frame()
{
	int w, h;
	int i, j;
	static int ltime;
	static int klatch;
	mouseinfo mi;
	vec2 md;
	u2 cursor[4];

	vfread(render_keymap, 1, 32, render_keymap_dev);
	render_keybuf_pos=0;

	while(vfinready(render_keyboard))
	{
		i=vfgetc(render_keyboard)<<8;
		i+=vfgetc(render_keyboard);

		render_keybuf[render_keybuf_pos++]=i;

//		kprint("render: got char '%c'(%d)\n", i, i);
	}

	render_keybuf[render_keybuf_pos]=0;

	UICon_Think();

	GfxApi_BeginDrawing(render_screen);

	GfxApi_SetRange(render_screen, -100, 100, -75, 75);

	if(Render_PollKey(K_F2) && ((Sys_TimeMS()-klatch)>250))
	{
		klatch=Sys_TimeMS();
		render_3dmode=!render_3dmode;

		if(!render_3dmode)
		{
			//CHEAP: centers mouse when leaving 3d mode
			mi.dx=0;
			mi.dy=0;
			vfwrite(&mi, 1, sizeof(mi), render_mouse);

			render_mouse_pos[0]=0;
			render_mouse_pos[1]=0;

			render_mouse_origin[0]=render_origin[0];
			render_mouse_origin[1]=render_origin[1];
		}else render_3dmouse=1;
	}

	if(render_3dmode)
	{
//		vfread(&mi, 1, sizeof(mi), render_mouse);

		Render3D_Frame();

		UICon_Draw();

		if(Render_PollKey(K_F10) && ((Sys_TimeMS()-klatch)>1000))
		{
			klatch=Sys_TimeMS();
			Tex_DoScreenshot();
		}

		GfxApi_EndDrawing(render_screen);

		return(0);
	}

	w=render_zoom*1024;
	h=render_zoom*768;

	GfxApi_SetRange(render_screen, -w, w, -h, h);
	GfxApi_Translate(render_screen, -render_origin[0], -render_origin[1]);


	vfread(&mi, 1, sizeof(mi), render_mouse);

	if(!(mi.flags&(MOUSE_MIDDLE|MOUSE_RIGHT)))
	{
		render_mouse_pos[0]+=mi.dx;
		render_mouse_pos[1]+=mi.dy;
		render_mouse_b=mi.flags;

		if(render_mouse_pos[0]<=-400)render_mouse_pos[0]=-400+1;
		if(render_mouse_pos[1]<=-300)render_mouse_pos[1]=-300+1;
		if(render_mouse_pos[0]>=400)render_mouse_pos[0]=400-1;
		if(render_mouse_pos[1]>=300)render_mouse_pos[1]=300-1;

		render_mouse_origin[0]=((render_mouse_pos[0]*w)/400.0)+render_origin[0];
		render_mouse_origin[1]=-((render_mouse_pos[1]*h)/300.0)+render_origin[1];

		md[0]=render_mouse_origin[0]-render_origin[0];
		md[1]=render_mouse_origin[1]-render_origin[1];
	}else if(mi.flags&MOUSE_MIDDLE)
	{
		i=256-(mi.dy*2);

//		render_zoom=mul_248(render_zoom, i);
		render_zoom=render_zoom*(i/256.0);
//		if(render_zoom<16)render_zoom=16;
		if(render_zoom<0.01)render_zoom=0.01;

//		md[0]=mul_248(md[0], i);
//		md[1]=mul_248(md[1], i);

//		mi.dx=(md[0]*400)/w;
//		mi.dy=(md[1]*300)/h;
		mi.dx=0;
		mi.dy=0;
		vfwrite(&mi, 1, sizeof(mi), render_mouse);

		//CHEAP: just centers mouse when zooming
		render_mouse_pos[0]=0;
		render_mouse_pos[1]=0;

		render_mouse_origin[0]=render_origin[0];
		render_mouse_origin[1]=render_origin[1];


//		render_mouse_origin[0]=md[0]+render_origin[0];
//		render_mouse_origin[1]=md[1]+render_origin[1];

//		i=mi.dy*2;
//		if(i)
//		{
//			render_origin[0]+=md[0]/mul_248(16, i);
//			render_origin[1]+=md[1]/mul_248(16, i);
//		}
	}else if(mi.flags&MOUSE_RIGHT)
	{
		render_origin[0]=-((mi.dx*w)/400.0)+render_origin[0];
		render_origin[1]=((mi.dy*h)/300.0)+render_origin[1];

		mi.dx=0;
		mi.dy=0;
		vfwrite(&mi, 1, sizeof(mi), render_mouse);

		render_mouse_pos[0]=0;
		render_mouse_pos[1]=0;

		render_mouse_origin[0]=render_origin[0];
		render_mouse_origin[1]=render_origin[1];
	}

	if(Render_PollKey(K_DEL))
	{
//		render_zoom=mul_248(render_zoom, 0xF0);
//		if(render_zoom<16)render_zoom=16;
		render_zoom*=0.9;
		if(render_zoom<0.01)render_zoom=0.01;

		render_origin[0]+=md[0]/10;
		render_origin[1]+=md[1]/10;

//		cam2d_origin[0]+=md[0]*0.1;
//		cam2d_origin[1]+=md[1]*0.1;
	}
	if(Render_PollKey(K_END))
	{
//		render_zoom=mul_248(render_zoom, 0x110);
//		if(render_zoom>(1<<30))render_zoom=1<<30;
		render_zoom*=1.1;
		if(render_zoom>(1<<30))render_zoom=1<<30;

		render_origin[0]-=md[0]/10;
		render_origin[1]-=md[1]/10;

//		cam2d_zoom*=1.1;
//		cam2d_origin[0]-=md[0]*0.1;
//		cam2d_origin[1]-=md[1]*0.1;
	}

	if(Render_PollKey(K_HOME))
	{
		render_origin[0]=0;
		render_origin[1]=0;
		render_zoom=1;
	}

	if(!ltime)ltime=Sys_TimeMS();
	i=ltime;
	j=Sys_TimeMS();
	ltime=Sys_TimeMS();

//	i=mul_248(render_zoom, j-i);
	i=(j-i)*render_zoom;
	if(Render_PollKey(K_UPARROW))render_origin[1]+=i;
	if(Render_PollKey(K_DOWNARROW))render_origin[1]-=i;

	if(Render_PollKey(K_LEFTARROW))render_origin[0]-=i;
	if(Render_PollKey(K_RIGHTARROW))render_origin[0]+=i;


#if 0
//	GfxApi_Translate(render_screen, 306, 396);
//	GfxApi_Scale(render_screen, 1<<23, 1<<23);

	w=mul_248(render_zoom, 512);
	h=mul_248(render_zoom, 384);

	GfxApi_SetRange(render_screen, -w, w, -h, h);
	GfxApi_Translate(render_screen, render_origin[0], render_origin[1]);

//	GfxApi_Scale(render_screen, render_zoom, render_zoom);

	GfxApi_FillSquare(render_screen, 0, 0, 612, 792, 255, 0, 0, 255);

	GfxApi_MoveTo(render_screen, 0, 396);
	GfxApi_FontSize(render_screen, 24);
	GfxApi_TextColor(render_screen, 0, 255, 0, 255);
	GfxApi_Show(render_screen, "this is a test");

	GfxApi_Show(render_screen, render_keybuf);
#endif

//	GfxApi_SetFont(render_screen, "bgb0");
//	GfxApi_MoveTo(render_screen, 0, 0);
//	GfxApi_FontSize(render_screen, 48);

//	GfxApi_TextColor(render_screen, 0, 255, 0, 255);
//	GfxApi_Show(render_screen, "[]S ]S X TEST");

//	GfxApi_SetFont(render_screen, "unicode");
	GfxApi_SetFont(render_screen, "fixed");
	GfxApi_FontSize(render_screen, 12);

	ObjSK_Frame();

	GfxApi_SetFont(render_screen, "fixed");
	GfxApi_FontSize(render_screen, 12);

	UICon_Draw();

//	kprint("mouse-org2 %d %d %d\n", render_mouse_origin[0], render_mouse_origin[1], render_mouse_b);

	GfxApi_MoveTo(render_screen, render_mouse_origin[0], render_mouse_origin[1]);
	GfxApi_SetFont(render_screen, "mouse");
//	i=mul_248(render_zoom, 48);
	i=48*render_zoom;
	GfxApi_FontSize2(render_screen, i, i);
//	GfxApi_Show(render_screen, "\xCD\xD9\xDB\xC9");
	GfxApi_TextColor(render_screen, 255, 255, 255, 255);
	GfxApi_Show(render_screen, " ");
//	GfxApi_Show(render_screen, " ");


	if(Render_PollKey(K_F10) && ((Sys_TimeMS()-klatch)>1000))
	{
		klatch=Sys_TimeMS();
		Tex_DoScreenshot();
	}

	GfxApi_EndDrawing(render_screen);

	return(0);
}
