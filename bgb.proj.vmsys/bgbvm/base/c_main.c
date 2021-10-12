#include <general.h>

extern int sys_init();
extern int Devices_Init();

void *MM2_CAlloc(int sz);

int core_init()
{
	sys_init();

	kprint("init vm.\n");
	SKVM_Init();
	LBSExt_Init();

	KCon_Init();
	Driver_Init();

	DevicesVM_Init();

//	kprint("P1\n");

	KCon_Reset();

//	kprint("P2\n");

	VPath_Init();
//	VPathVM_Init();

//	kprint("Console should be up now...\n");
//	while(1);

//	GenObj_Init();

//	MM2_CAlloc(16);

}