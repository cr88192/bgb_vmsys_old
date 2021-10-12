#include <kfunc.h>
#include <x86/tss.h>
#include <x86/page.h>
#include <x86/desc.h>

extern unsigned long *gdt;

int TS_Init()
{
	void *stack_ptr; /* MUST BE FIRST */
	int ktss,ktsse;
	int esp0;
	struct tss32_t *tssp;
	char hs[11];

	kprint("init task manager.\n");

	ktss=Page_Alloc(1);
	ktsse=FindFreeGDTEntry();
	if(!ktsse)panic("can't alloc gdt entry.\n");
//	Text_WriteLong(ktsse);
	NewGDTEntry(ktsse,ktss<<12,0x67,GDT_STYPE_TSS|GDT_STYPE_FLAGS);
	tssp=(struct tss32_t *)(ktss<<12);
	memset(tssp,0,4096);

	esp0=Page_Alloc(4);
	tssp->ss0=0x10;
	tssp->esp0=(esp0<<12)+16384;

//	kprint("GDT: ");
//	printltohs(&hs,gdt[ktsse>>2],8);
//	kprint(hs);
//	kprint(", ");
//	printltohs(&hs,gdt[(ktsse>>2)+1],8);
//	kprint(hs);
//	kprint("\n");

	StartKernelTSS(ktsse, tssp);

	kprint("kernel task started.\n");
}

void TS_DumpTaskState(struct tss32_t *tss)
{
	char hs[11];

	kprint("EAX: ");
	printltohs(hs,tss->regs.d.eax,8);
	kprint(hs);
	kprint("  ");

	kprint("ECX: ");
	printltohs(hs,tss->regs.d.ecx,8);
	kprint(hs);
	kprint("  ");

	kprint("EDX: ");
	printltohs(hs,tss->regs.d.edx,8);
	kprint(hs);
	kprint("  ");

	kprint("EBX: ");
	printltohs(hs,tss->regs.d.ebx,8);
	kprint(hs);
	kprint("\n");

	kprint("ESP: ");
	printltohs(hs,tss->regs.d.esp,8);
	kprint(hs);
	kprint("  ");

	kprint("EBP: ");
	printltohs(hs,tss->regs.d.ebp,8);
	kprint(hs);
	kprint("  ");

	kprint("ESI: ");
	printltohs(hs,tss->regs.d.esi,8);
	kprint(hs);
	kprint("  ");

	kprint("EDI: ");
	printltohs(hs,tss->regs.d.edi,8);
	kprint(hs);
	kprint("\n");
	
	kprint("ES: ");
	printltohs(hs,tss->es,4);
	kprint(hs);
	kprint("  ");

	kprint("CS: ");
	printltohs(hs,tss->cs,4);
	kprint(hs);
	kprint("  ");

	kprint("SS: ");
	printltohs(hs,tss->ss,4);
	kprint(hs);
	kprint("  ");

	kprint("DS: ");
	printltohs(hs,tss->ds,4);
	kprint(hs);
	kprint("  ");

	kprint("FS: ");
	printltohs(hs,tss->fs,4);
	kprint(hs);
	kprint("  ");

	kprint("GS: ");
	printltohs(hs,tss->gs,4);
	kprint(hs);
	kprint("\n");

	kprint("CS:EIP:   ");
	printltohs(hs,tss->cs,4);
	kprint(hs);
	kprint(":");
	printltohs(hs,tss->eip,8);
	kprint(hs);
	kprint("\n");

	kprint("SS0:ESP0: ");
	printltohs(hs,tss->ss0,4);
	kprint(hs);
	kprint(":");
	printltohs(hs,tss->esp0,8);
	kprint(hs);
	kprint("\n");

	kprint("SS1:ESP1: ");
	printltohs(hs,tss->ss1,4);
	kprint(hs);
	kprint(":");
	printltohs(hs,tss->esp1,8);
	kprint(hs);
	kprint("\n");

	kprint("SS2:ESP2: ");
	printltohs(hs,tss->ss2,4);
	kprint(hs);
	kprint(":");
	printltohs(hs,tss->esp2,8);
	kprint(hs);
	kprint("\n");
}
