#include <kfunc.h>
//#include <os1/kernel/text.h>
//#include <os1/kernel/clock.h>
//#include <os1/kernel/page.h>
//#include <os1/kernel/fs.h>
//#include <os1/kernel/io.h>

#include <general.h>

short k_codeseg;
short k_dataseg;
extern int irq_mask;

int sys_init()
{
	Text_Init();
	Text_WriteString("SYS_Init\n");

	Page_Init(); //page manager
	InitDescs(); //setup gdt and idt, needs page manager
	TS_Init(); //setup tasks, needs descs and paging

//	MM3_Init(); //memory manager, needs page manager
	MM2_Init(); //memory manager, needs page manager
//	while(1);

//	MMGC3_Init();

//	while(1);

	kthread_init();

	outportb(0x3F2,0);
	k_codeseg=8;
	k_dataseg=16;
	
	irq_mask=0xFFFB;

	Clock_Init();
 	TEV_Init(); /* timed events, needs clock */
}

int reboot()
{
	kprint("rebooting...\n");
	outportb(0x64, 0xfc);
	while(1);
	return(0);
}

//int printf(const char *s, ...)
//{
//	kprint(s);
//}

//void *malloc(int sz)
//{
//	return(NULL);
//}

int sys_isbooted()
{
	return(-1);
}

int sys_halt()
{
	asm("hlt\n");
}

int abort()
{
	panic("abort called.\n");
	while(1);
}

int sprintf(char *s, char *f, ...)
{
	kva_list l;
	kva_start(l, f);

	kvprints(s, f, l);
	kva_end(l);
	return(0);
}

int atoi(char *s)
{
	return(katoi(s));
}

VFILE *vffopen(char *s, char *a)
{
	char buf[256], *t;
	VFILE *vfd;

	t=VFSNS_GetScheme(s);
	if(t)
	{
		vfd=VFSNS_OpenFile(t, a);
		return(vfd);
	}

	vfd=VPath_OpenFile(s, a);
	if(vfd)return(vfd);

	strcpy(buf, "/root/");
	strcat(buf, s);
	vfd=VPath_OpenFile(buf, a);
	if(vfd)return(vfd);

	strcpy(buf, "/shroot/");
	strcat(buf, s);
	vfd=VPath_OpenFile(buf, a);
	if(vfd)return(vfd);

	return(NULL);
}

void mcount()
{
}
