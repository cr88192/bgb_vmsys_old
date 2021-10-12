#include <general.h>

extern unsigned char *VGA_ScreenBuf;
extern unsigned int VGA_xbytes;
int is_graphics,draw_console;

extern struct reg G640x480x16;

extern int VGA_DrawCell(int x,int y,unsigned char *cell,unsigned char clr);

int GFX_Init()
{
	int i;
	VGA_ScreenBuf=(unsigned char *)0xA0000;
	VGA_xbytes=640/8;

	outRegArrayZ(&G640x480x16);

	is_graphics=1;
	draw_console=1;

	outportw(0x3c4,0x0f02);
	for(i=0;i<(80*480);i++)VGA_ScreenBuf[i]=0xff;
}
