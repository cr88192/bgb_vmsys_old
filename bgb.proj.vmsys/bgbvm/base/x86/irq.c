#include <x86/io.h>

int irq_mask;

int enable_irq(int irq)
{
	if(irq>15)return;
	irq_mask&=~(1<<irq);
	outportb(0x21,irq_mask&0xFF);
	outportb(0xA1,(irq_mask>>8)&0xFF);
}

int disable_irq(int irq)
{
	if(irq>15)return;
	irq_mask|=1<<irq;
	outportb(0x21,irq_mask&0xFF);
	outportb(0xA1,(irq_mask>>8)&0xFF);
}
