#ifndef __TSS_H__
#define __TSS_H__

struct tss32_t {
unsigned long prev;

unsigned long esp0;
unsigned long ss0;
unsigned long esp1;
unsigned long ss1;
unsigned long esp2;
unsigned long ss2;

unsigned long cr3;
unsigned long eip;
unsigned long eflags;

union {
	struct {
	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;
	unsigned long esp;
	unsigned long ebp;
	unsigned long esi;
	unsigned long edi;
	}d;
}regs;
unsigned long es;
unsigned long cs;
unsigned long ss;
unsigned long ds;
unsigned long fs;
unsigned long gs;
unsigned long ldt;
unsigned short flags;
unsigned short iomapadr;
};

void GrabTSS(struct tss32_t *tss);
void StartKernelTSS(int num, struct tss32_t *tss);

#endif
