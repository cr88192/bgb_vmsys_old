#include <general.h>

extern int core_init();
extern int reboot();

int PELoad_StartApp(char *name, char **argv, char **env);

int main_loop_break, idle_loop_break;
int main_kill;

int child_loops;

char **_env;

kmutex *vm_lock;

int test_thread(void *data)
{
	while(1)
	{
		kusleep(1000000);
		kprint(data);
	}
	return(0);
}

int main_inner()
{
	kthread *th1, *th2, *th3;
	VFILE *fd;

	char *sh_argv[8];
	char *sh_env[8];

	kprint("shell init.\n");

//	if(!checkarg("--nogui"))

//	Render_Init();
//	TySock_Init();
	NET_Init();

//	Interp_DefinePrimative("kterm", sertst, 0);

//	Interp_DefinePrimative("mstat", &MM2_Print, 0);

//	kprint("load scripts.\n");

//	Interp_Load(STRING("bgb_init.lb"));

//	if(!checkarg("--nogui"))
//		Interp_Load(STRING("gui-0.lb"));

//	if(!checkarg("--nostore"))
//	{
//		MMGC3_RestoreImage();
//		Interp_HandleRestore();
//	}

//	MMGC3_RestoreImage();
//	Interp_HandleRestore();

	kprint("ok1.\n");

	vm_lock=kmutex_new();
	child_loops=0;

	fd=NULL;
//	fd=vffopen("/devices/serial/0", "r+t");

//	th3=kthread_spawn(0, &main_loop2, fd);
//	kthread_start(th3, PRIORITY_NORMAL);
//	kthread_dumpthread(th3);

//	th1=kthread_spawn(0, &main_loop, NULL);
//	kthread_start(th1, PRIORITY_NORMAL);
//	kthread_dumpthread(th1);

//	if(fd)
//	{
//		th2=kthread_spawn(0, &main_loop, fd);
//		kthread_start(th2, PRIORITY_NORMAL);
//	}

	sh_argv[0]="/root/app0.exe";
	sh_argv[1]=NULL;

	sh_env[0]=NULL;

//	PELoad_LoadImage("/root/app0.exe");
	PELoad_StartApp("apps/app0.exe", sh_argv, sh_env);
	child_loops++;

	kthread_set_priority(idle_thread, PRIORITY_IDLE);
	kthread_blocked();	//allow other threads to run
	kusleep(10000);

	main_loop_break=0;
	idle_loop_break=0;

	while(!idle_loop_break && child_loops)sys_halt();

	kprint("KM1\n");
//	Interp_DeInit();
	kprint("KM2\n");
//	Store_DeInit();

//	MMGC3_StoreAll();

//	while(1);
	reboot();
}

int k_main(int argc, char **argv, char **env)
{
	_env=env;

	core_init();
	main_inner();
}
