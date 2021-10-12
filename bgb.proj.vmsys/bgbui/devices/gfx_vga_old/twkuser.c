#include <general.h>
#include <gfxdev/twkuser.h>

/*
    readyVgaRegs() does the initialization to make the VGA ready to
	accept any combination of configuration register settings.

	This involves enabling writes to index 0 to 7 of the CRT controller
	(port 0x3d4), by clearing the most significant bit (bit 7) of index
	0x11.
*/

void readyVgaRegs(void)
{
	int v;
	outportb(0x3d4,0x11);
    v = inportb(0x3d5) & 0x7f;
	outportb(0x3d4,0x11);
	outportb(0x3d5,v);
}

/*
	outReg sets a single register according to the contents of the
	passed Register structure.
*/

void outReg(Register r)
{
	switch (r.port)
	{
		/* First handle special cases: */

		case ATTRCON_ADDR:
			inportb(STATUS_ADDR);  		/* reset read/write flip-flop */
			outportb(ATTRCON_ADDR, r.index | 0x20);
										/* ensure VGA output is enabled */
			outportb(ATTRCON_ADDR, r.value);
			break;

		case MISC_ADDR:
		case VGAENABLE_ADDR:
			outportb(r.port, r.value);	/*	directly to the port */
			break;

		case SEQ_ADDR:
		case GRACON_ADDR:
		case CRTC_ADDR:
		default:						/* This is the default method: */
			outportb(r.port, r.index);	/*	index to port			   */
			outportb(r.port+1, r.value);/*	value to port+1 		   */
			break;
	}
}


/*
	outRegArray sets n registers according to the array pointed to by r.
	First, indexes 0-7 of the CRT controller are enabled for writing.
*/

void outRegArray(Register *r, int n)
{
	readyVgaRegs();
	while (n--)
		outReg(*r++);
}

/*
	same as outRegArray exept a null port terminates this list.
*/

void outRegArrayZ(Register *r)
{
	readyVgaRegs();
	while(r->port)
	{
		outReg(*r++);
	}
}
