#include <general.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>

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

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char buf[256], *s, *t;
	int i, j, x, y, w, h;
	FILE *infd;
	char *fbuf, *fcur;
	elem obj;

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
	Render_Init();
//	TySock_Init();
	MRP_Init();

	Interp_Load(STRING("scripts/e_init.lb"));
//	Interp_Load(STRING("scripts/gui-0.lb"));
//	Interp_Load(STRING("scripts/e_net.lbs"));

//	MMGC3_RestoreImage();
	Interp_HandleRestore();

	while(!main_kill)
	{
		if((Sys_TimeMS()-last)<10)
		{
			kusleep(5000);
			continue;
		}
		last=Sys_TimeMS();

//		vfread(keybuf, 1, 32, render_keymap_dev);

//		GfxDrv_BeginDrawing();

		MRP_Poll();

		Interp_RunQuantum(100);

		Render_Frame();

//		GfxDrv_EndDrawing();
	}

	MMGC3_StoreAll();
	SKVM_DeInit();
}
