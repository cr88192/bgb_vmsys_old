#include <general.h>

int PCIBus_Scan()
{
	int i, j, k;
	int base;
	int PciData,BaseAddr,Interrupt;

	for(i=0; i<32; i++)
	{
		base=0x80000000+(i<<11);
		outportd(0xcf8,base);
		k=inportd(0xcfc);
		if(k==-1)continue;

		kprint("PCI: slot=%d vendor=%X device=%X\n",
			i, k&0xffff, (k>>16)&0xffff);
		for(j=0; j<6; j++)
		{
			outportd(0xcf8,base+0x10+(j*4));
			k=inportd(0xcfc);
			if(!k)continue;
			if(k&1)
				kprint("\tIO: 0x%X\n", k&(~3));
				else kprint("\tMEM: 0x%X\n", k&(~15));
		}

#if 0
		if(PciData==0x813910ec)
		{
			outportd(0xcf8,j+0x10);
			*IOBase=inportd(0xcfc);
			*IOBase &= 0xfffffff0;
			outportd(0xcf8,j+0x3c);
			*IRQ=inportd(0xcfc);
			*IRQ &= 0xff;
			return TRUE;
		}
#endif
	}
//	while(1);

	return(0);
}

#if 0
int FindIOIRQ(int id, unsigned long *IOBase, unsigned long *IRQ)
{
	ULONG i,j,PciData,BaseAddr,Interrupt;
	for(i=0;i<32;i++)
	{
		j=0x80000000+(i<<11);
		outportd(0xcf8,j);
		PciData=inportd(0xcfc);
		kprint("PCI: slot=%d id=%X\n", )
		if(PciData==0x813910ec)
		{
			outportd(0xcf8,j+0x10);
			*IOBase=inportd(0xcfc);
			*IOBase &= 0xfffffff0;
			outportd(0xcf8,j+0x3c);
			*IRQ=inportd(0xcfc);
			*IRQ &= 0xff;
			return TRUE;
		}
	}
	return FALSE;
}
#endif

int PCIBus_Init()
{
	kprint("PCI Init\n");
	PCIBus_Scan();
	return(0);
}
