#include <general.h>

extern int sys_init();
extern int Devices_Init();

void *MM2_CAlloc(int sz);

int core_init()
{
	sys_init();

//	kprint("init vm.\n");
//	SKVM_Init();

	Con_Init();
	Driver_Init();

	Devices_Init();

//	kprint("P1\n");

	Con_Reset();

//	kprint("P2\n");

	VPath_Init();
//	VPathVM_Init();

//	kprint("Console should be up now...\n");
//	while(1);

//	GenObj_Init();

//	MM2_CAlloc(16);

	syscall_init();
	PELoad_Init();
}