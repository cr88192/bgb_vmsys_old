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

int main_kill;

char *_argv[64];
int _argc;

byte keybuf[32];

HINSTANCE	global_hInstance;
int			global_nCmdShow;

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
static int fl=0;

int Key_Event(int key, int state)
{
//	printf("key %s '%c'\n", state?"press":"release", key);

	if(state)keybuf[key/8]|=1<<(key&7);
		else keybuf[key/8]&=~(1<<(key&7));

	fl=0;
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char buf[256], *s, *t;
	int i, j, x, y, w, h;
	FILE *infd;
	char *fbuf, *fcur;
	elem obj;
	int store;

	static int last;

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
	DevicesUI_Init();
	Render_Init();
//	TySock_Init();
	NET_Init();
//	HttpNode_Init();

	Interp_Load(STRING("scripts/e_init.lbs"));
	Interp_Load(STRING("scripts/e_gui.lbs"));
//	Interp_Load(STRING("scripts/e_net.lbs"));
//	Interp_Load(STRING("scripts/e_world.lbs"));

	store=0;

	if(checkarg("--store"))store=1;
	if(checkarg("--segment"))
	{
		i=checkarg("--segment");
		MMGC3_SetStoreImage(_argv[i+1]);
		store=1;
	}

	if(store)
		MMGC3_RestoreImage();
	Interp_HandleRestore();
	MRP_HandleRestore();

	while(!main_kill)
	{
		if((Sys_TimeMS()-last)<33)
		{
			kusleep(5000);
			continue;
		}
		last=Sys_TimeMS();

//		vfread(keybuf, 1, 32, render_keymap_dev);

//		GfxDrv_BeginDrawing();

		NET_Poll();
//		HttpNode_Poll();

		Interp_RunQuantum(100);

		Render_Frame();

//		GfxDrv_EndDrawing();
	}

	MMGC3_StoreAll();
	SKVM_DeInit();
}
