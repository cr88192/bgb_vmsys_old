#include <general.h>

extern unsigned char *VGA_ScreenBuf;
extern unsigned int VGA_xbytes;
int is_graphics,draw_console;
unsigned char *palette;

extern struct reg G360x480x256;
extern struct reg G320x240x256;
extern struct reg G640x480x16;
extern unsigned char palette_color;
extern unsigned char palette_grey;
extern unsigned char font_8x8_32_96[96*8];
extern unsigned char *cc15to8;

extern int VGA_DrawCell(int x,int y,unsigned char *cell,unsigned char clr);

int GFX_SubmitBuffer(u2 *buf)
{
	int i, j, k, c;
	u2 *src;
	byte *dst;

		VGA_SetPlane(2-i);
//		for(j=0; j<80; j++)for(k=0; k<240; k++)
//			VGA_ScreenBuf[(k*80)+j]=buf[(k*320)+((j*4)+i)] &0xff;

	src=buf;
	dst=VGA_ScreenBuf;

	for(i=0; i<80*480; i++)
	{
		VGA_SetPlane(3);
		*dst=0xff;

		VGA_SetPlane(2);
		c=0;
		c|=((src[0]>>4)&1)<<7;
		c|=((src[1]>>4)&1)<<6;
		c|=((src[2]>>4)&1)<<5;
		c|=((src[3]>>4)&1)<<4;
		c|=((src[4]>>4)&1)<<3;
		c|=((src[5]>>4)&1)<<2;
		c|=((src[6]>>4)&1)<<1;
		c|=((src[7]>>4)&1)<<0;
		*dst=c;

		VGA_SetPlane(1);
		c=0;
		c|=((src[0]>>9)&1)<<7;
		c|=((src[1]>>9)&1)<<6;
		c|=((src[2]>>9)&1)<<5;
		c|=((src[3]>>9)&1)<<4;
		c|=((src[4]>>9)&1)<<3;
		c|=((src[5]>>9)&1)<<2;
		c|=((src[6]>>9)&1)<<1;
		c|=((src[7]>>9)&1)<<0;
		*dst=c;

		VGA_SetPlane(0);
		c=0;
		c|=((src[0]>>14)&1)<<7;
		c|=((src[1]>>14)&1)<<6;
		c|=((src[2]>>14)&1)<<5;
		c|=((src[3]>>14)&1)<<4;
		c|=((src[4]>>14)&1)<<3;
		c|=((src[5]>>14)&1)<<2;
		c|=((src[6]>>14)&1)<<1;
		c|=((src[7]>>14)&1)<<0;
		*dst=c;

		dst++;
		src+=8;
	}
	return(0);
}

#if 0
extern char *text_buffer;
extern int text_xs;
extern int text_ys;
extern int text_x;
extern int text_y;
extern int text_color;
extern int time_msec_count;

int t_cursor_think(struct event_t *cur)
{
	int t;
	unsigned char blk[8];

	if(!draw_console)return(-1);
	
	blk[0]=0xff;
	blk[1]=0xff;
	blk[2]=0xff;
	blk[3]=0xff;
	blk[4]=0xff;
	blk[5]=0xff;
	blk[6]=0xff;
	blk[7]=0xff;
	
	t=time_msec_count/250;
	VGA_DrawCell(text_x,text_y,(unsigned char *)&blk,0x80);
	if(t%2)VGA_DrawCell(text_x,text_y,(unsigned char *)&blk,0x0);

	return(0);
}
#endif

int GFX_Init()
{
	int i;
	VGA_ScreenBuf=(unsigned char *)0xA0000;
	VGA_xbytes=640/8;

//	palette=&palette_grey;
//	CCT_GenCCT();
	
	outRegArrayZ(&G640x480x16);
//	VGA_setPalette256(&palette_grey);

	is_graphics=1;
	draw_console=1;

#if 0	
	text_buffer=malloc(2400);
	text_xs=40;
	text_ys=30;
	text_x=0;
	text_y=0;
	text_color=0;
	for(i=0;i<(40*30*2);i++)text_buffer[i]=' ';
#endif

	outportw(0x3c4,0x0f02);
	for(i=0;i<(80*480);i++)VGA_ScreenBuf[i]=0xff;

//	for(i=0;i<40;i++)VGA_DrawCell(i,0,(unsigned char *)&font_8x8_32_96[i*8],0);
//	for(i=0;i<40;i++)VGA_DrawCell(i,1,(unsigned char *)&font_8x8_32_96[(i+40)*8],0);
	
//	TEV_AddProc(&t_cursor_think,0.25,1);
//	GFX_Text2GFX();
}

#if 0
int GFX_Text2GFX()
{
	int i,v,t;
	unsigned char blk[8];
	
	if(!is_graphics||!draw_console)return(-1);
	
	blk[0]=0xff;
	blk[1]=0xff;
	blk[2]=0xff;
	blk[3]=0xff;
	blk[4]=0xff;
	blk[5]=0xff;
	blk[6]=0xff;
	blk[7]=0xff;
	
	for(i=0;i<30;i++)for(v=0;v<40;v++)
	{
		VGA_DrawCell(v,i,(unsigned char *)&blk,0x80);
		VGA_DrawCell(v,i,
			(unsigned char *)&font_8x8_32_96[(text_buffer[((i*40)+
			v)*2]-' ')*8],0);
		
	}
}
#endif
