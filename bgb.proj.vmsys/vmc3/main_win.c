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

elem MF_Quit()
{
	main_kill=1;
	return(MISC_NULL);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char buf[256], *s, *t;
	int i, x, y, w, h;
	int store;

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

	Sys_OpenShell();
	core_init();
	DevicesUI_Init();
//	Render_Init();

	NET_Init();
//	TySock_Init();
//	MRP_Init();
//	HttpNode_Init();


	kprint("load scripts.\n");

	Interp_Load(STRING("scripts/e_init.lbs"));
//	Interp_Load(STRING("scripts/e_gui.lbs"));
//	Interp_Load(STRING("scripts/e_net.lbs"));

	Interp_DefinePrimative("quit",		&MF_Quit,		0);

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

	kprint("# ");
	s=buf;
	while(!main_kill)
	{
//		kprint("# ");
//		fgets(buf, 255, stdin);
		s=Sys_ReadLine();

//		s=buf;
		if(s)
		{
			t=Interp_EvalStringTop(s);
			TyFcn_DumpElem(t);
			kprint("\n");
			kprint("# ");
		}

		NET_Poll();
//		MRP_Poll();
//		HttpNode_Poll();
		Interp_RunQuantum(100);
	}

	MMGC3_StoreAll();
	SKVM_DeInit();
}
