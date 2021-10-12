#include <general.h>
#include <windows.h>

int main_kill;

char *_argv[64];
int _argc;

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
	int i, x, y, w, h;

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
			_argv[_argc++]=kstrdup(buf);
		}
	}

	core_init();

//	VID_Init();

	Render_Init();
//	TySock_Init();

	kprint("load scripts.\n");

	Interp_Load(STRING("bgb_init.lb"));
	Interp_Load(STRING("gui-0.lb"));

//	if(!checkarg("--nostore"))
//	{
//		MMGC3_RestoreImage();
//		Interp_HandleRestore();
//	}

//	MMGC3_RestoreImage();
	Interp_HandleRestore();

	kprint("ok1.\n");

	s=buf;
	kprint("# ");
	while(!main_kill)
	{
//		kprint("# ");
//		Rendercore_Frame();
//		if(!kgets(buf, &s))
		fgets(buf, 255, stdin);
		if(1)
		{
			s=buf;
			if(*s)
			{
//				kprint(s);
//				kmutex_reslock(vm_lock);
				t=Interp_EvalStringTop(s);
				TyFcn_DumpElem(t);
				kprint("\n");
//				kmutex_unlock(vm_lock);
			}
			kprint("# ");
		}
//		Con_SubmitCommand(cb);
//		MM2_ObjAlloc(1024, 1);
//		MMGC_Collect();
//		Rendercore_Frame();
//		Heap0_Commit();

		Render_Frame();

//		GL_BeginRendering(&x, &y, &w, &h);
//		glClear();
//		GL_EndRendering();
//		TySock_HandleInput();
	}

}
