#include <general.h>

extern unsigned char *VGA_ScreenBuf;
extern int VGA_xbytes;

extern void Unchained256_SetPlane(int pl);

void VGA_getPalette256(unsigned char *palette)
{
	int c;
	outportb(0x3c7, 0);
	for (c=0; c<768; c++)
		palette[c] = inportb(0x3c9)<<2;
}

void VGA_setPalette256(unsigned char *palette)
{
	int c;
	outportb(0x3c8, 0);
	for (c=0; c<768; c++)
		outportb(0x3c9, palette[c]>>2);
}

/* a cell is an 8x8 1bpp square, drawn with clr for 1, noeff for 0 */
int VGA_DrawCell(int x,int y,unsigned char *cell,unsigned char clr)
{
	int i,v;
	for(i=0;i<8;i++)
	{
		for(v=0;v<4;v++)
		{
			VGA_SetPlane(v);
			if(cell[i]&(0x80>>v))
				VGA_ScreenBuf[((y*8+i)*VGA_xbytes)+x*2]=clr;
			if(cell[i]&(0x08>>v))
				VGA_ScreenBuf[((y*8+i)*VGA_xbytes)+x*2+1]=
				clr;
		}
	}
}

/* draws a GUI cell, same as before exept: x/y are pixels, 0=clr2 */
int VGA_DrawCell2(int x,int y,unsigned char *cell,unsigned char clr,
	unsigned char clr2)
{
	int i,v,x2;
	for(i=0;i<8;i++)
	{
		for(v=0;v<8;v++)
		{
			VGA_SetPlane((v+x)&3);
			x2=(x+v)/4;
			if(cell[i]&(0x80>>v))
			{
				VGA_ScreenBuf[(i+y)*VGA_xbytes+x2]=clr;
			}else
			{
				VGA_ScreenBuf[(i+y)*VGA_xbytes+x2]=clr2;
			}
		}
	}
}