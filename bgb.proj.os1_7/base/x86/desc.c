#include <x86/desc.h>

unsigned long *gdt;
unsigned long *idt;
int gdt_ents;
int idt_ents;

extern void Desc_Setup();
extern void Desc_Get(unsigned long **gdt, unsigned long **idt);
extern void cpu_int0();
extern void cpu_int1();
extern void cpu_int2();
extern void cpu_int3();
extern void cpu_int4();
extern void cpu_int5();
extern void cpu_int6();
extern void cpu_int7();
extern void cpu_int8();
extern void cpu_int9();
extern void cpu_int10();
extern void cpu_int11();
extern void cpu_int12();
extern void cpu_int13();
extern void cpu_int14();
extern void cpu_int15();
extern void cpu_int16();
extern void cpu_int17();
extern void cpu_int18();

void Null_ISR();
void NullC_ISR();

asm (
".globl _Null_ISR\n"
"_Null_ISR:\n"
"iret\n"
"\n"
".globl _NullC_ISR\n"
"_NullC_ISR:\n"
"popl %eax\n"
"iret\n"
);

int InitDescs()
{
	int i;
	unsigned long *old_gdt,*old_idt;

	kprint("Setting up GDT and IDT...\n");
//	idt=(unsigned long *)0xF800;
//	old_gdt=(unsigned long *)0xFA00;
//	for(i=0;i<64;i++)NewIntISR(&Null_ISR,i,0);
//	memset((void *)((int)gdt+32),0,188*8);
	Desc_Get(&old_gdt, &old_idt);

//	idt=(unsigned long *)(Page_Alloc(1)<<12);
//	if(!idt)panic("can't alloc IDT.\n");
//	memset(idt,0,2048);
//	gdt=(unsigned long *)(Page_Alloc(16)<<12);
//	if(!gdt)panic("can't alloc GDT.\n");
//	memset(gdt,0,65536);

	gdt=old_gdt;
	idt=old_idt;

//	for(i=0;i<32;i++)gdt[i]=old_gdt[i];

	for(i=0;i<64;i++)NewIntISR(&Null_ISR,i,0);
	
	NewIntISR(cpu_int0,0,0);
	NewIntISR(cpu_int1,1,0);
	NewIntISR(cpu_int2,2,0);
	NewIntISR(cpu_int3,3,0);
	NewIntISR(cpu_int4,4,0);
	NewIntISR(cpu_int5,5,0);
	NewIntISR(cpu_int6,6,0);
	NewIntISR(cpu_int7,7,0);
	NewIntISR(cpu_int8,8,0);
	NewIntISR(cpu_int9,9,0);
	NewIntISR(cpu_int10,10,0);
	NewIntISR(cpu_int11,11,0);
	NewIntISR(cpu_int12,12,0);
	NewIntISR(cpu_int13,13,0);
	NewIntISR(cpu_int14,14,0);
	NewIntISR(cpu_int15,15,0);
	NewIntISR(cpu_int16,16,0);
	NewIntISR(cpu_int17,17,0);
	NewIntISR(cpu_int18,18,0);

	gdt_ents=192;
	idt_ents=64;
	
	Desc_Setup();
	
	asm("sti\n"); //enable interrupts
}


/* IDT code */
int NewIntISR(void (*handler)(), int vec, int fl)
{
	unsigned long ptr;
	ptr=(long)handler;
	idt[vec*2]=0x00080000;
	idt[vec*2]+=ptr&0xFFFF;
	idt[vec*2+1]=0x8E00^fl;
	idt[vec*2+1]+=ptr&0xFFFF0000;
}

/* GDT */
int FindFreeGDTEntry()
{
	int i;
	for(i=1;i<gdt_ents;i++)
	{
		if(!(gdt[i*2+1]&0x8000))return(i<<3);
		if(!gdt[i*2] && !gdt[i*2+1])return(i<<3);
	}
	return(0);
}

void DeleteGDTEntry(int num)
{
	if(num&4)return; /* not gdt */
	
	gdt[num>>2]=0;
	gdt[num>>2+1]=0;
}

int NewGDTEntry(int num, int base, int size, int flags)
{
	if(num&4)return(0);

	gdt[num>>2]=(size&0xFFFF)|((base&0xFFFF)<<16);
	gdt[(num>>2)+1]=
		((base&0xFF0000)>>16) |
		((flags&0xFF)<<8) |
		(size&0xF0000) |
		((flags&0xF00)<<12) |
		(base&0xFF000000);
	return(num);
}
