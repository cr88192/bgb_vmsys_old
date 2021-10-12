#include <general.h>

int mem_pages;

int sys_init()
{
//	MM3_Init();
//	MM2_Init();
	MMGC3_Init();

	kthread_init();
}

int sys_isbooted()
{
	return(0);
}

int sys_halt()
{
	usleep(1000);
}

int reboot()
{
	exit(0);
}

int stricmp(char *s, char *t)
{
	return(strcasecmp(s, t));
}
