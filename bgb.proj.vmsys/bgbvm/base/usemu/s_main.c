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
//	usleep(1000);
}

int reboot()
{
	exit(0);
}

int stricmp(char *s, char *t)
{
	return(strcasecmp(s, t));
}

VFILE *vffopen(char *s, char *a)
{
	char buf[256];
	VFILE *vfd;

	vfd=VPath_OpenFile(s, a);
	if(vfd)return(vfd);

	strcpy(buf, "/root/");
	strcat(buf, s);
	vfd=VPath_OpenFile(buf, a);
	return(vfd);

//	return(NULL);
}

VDIR *vfopendir(char *s)
{
	char buf[256];
	VDIR *vfd;

	vfd=VPath_OpenDir(s);
	if(vfd)return(vfd);

	strcpy(buf, "/root/");
	strcat(buf, s);
	vfd=VPath_OpenDir(buf);
	return(vfd);

//	return(NULL);
}
