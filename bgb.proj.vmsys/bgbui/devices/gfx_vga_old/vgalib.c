#include <general.h>

unsigned char *VGA_ScreenBuf;
int VGA_xbytes;

/*
 *	Planar16
 */

void Planar16_SP(int xr, int yr, int vxr)
{
	outportw(0x3ce, 0x0f01);					// enable set/reset
}

void Planar16_putPixel(int x, int y, int c)
{
	unsigned char *pos;
	outportw(0x3ce, 0x00 | (c<<8));		// set/reset to select color
	outportw(0x3ce, 0x08 | 0x8000>>(x&7));	// bit mask to select bit
	*pos = VGA_ScreenBuf+y*VGA_xbytes+(x>>3);
	*pos = *pos;
}

/*
 *	Unchained256
 */

void Unchained256_putPixel(int x, int y, int c)
{
	outportw(0x3c4, 0x02 | 0x0100<<(x&3));
	VGA_ScreenBuf[y*VGA_xbytes+(x>>2)] = c;
}

void VGA_SetPlane(int pl)
{
	outportw(0x3c4, 0x02 | 0x0100<<(pl&3));
}
