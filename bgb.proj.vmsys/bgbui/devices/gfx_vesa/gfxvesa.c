#include <general.h>
#include <x86/page.h>
#include <x86/kpfh.h>

#define PMID	0x44494D50
#define VESA	0x41534556

#define	MISC_CALLRMFUNC		0
#define VESA_GETINFO		1	// VesaInfo *()
#define VESA_GETMODEINFO	2	// ModeInfo *()
#define VESA_SETMODE		3	// void (int mode)
#define VESA_GETMODE		4	// int ()
#define VESA_SETBANK		5	// void (int bank)
#define VESA_SETPALETTE		6	// void (int bank)

#define VESA_BLITSCREEN		7	// void (void *buf, int banks, int banksz)


typedef struct {
byte id[4];
byte ver[2];
byte far_oemname[4];
byte caps[4];
byte far_modelist[4];
byte vidmem[2];

byte _resv[492];
}VesaInfo;

typedef struct {
byte mode_attrib[2];	//1&=mode supported, 4&=tty supported, 8&=color, 16&=graphics, 32&=non-vga
byte wina_attrib;		//1&=windowed, 2&=readable, 4&=writable
byte winb_attrib;
byte banksize[2];		//size of a bank
byte winsize[2];		//size of the vga area
byte wina_seg[2];		//where window A is at
byte winb_seg[2];		//where window B is at
byte far_win_func[4];	//faster bank function, same call as normal
byte scanline_sz[2];	//how wide each scanline is

byte xsize[2];			//size of screen
byte ysize[2];
byte char_xsize;
byte char_ysize;
byte num_planes;		//number of vga/color planes
byte bpp;				//full number of bits in a pixel
byte num_banks;			//number of banks in this resolution
byte mem_model;			//0=text, 1=cga, 2=hercules, 3=planar, 4=packed pixel, 5=non-chain 256, 6=direct color, 7=yuv
byte banksize_2;		//?
byte image_planes;		//how many image pages can fit in vidmem
byte _resv1;

byte redmask_size;		//the size/position of color components
byte redmask_pos;
byte greenmask_size;
byte greenmask_pos;
byte bluemask_size;
byte bluemask_pos;
byte rsvdmask_size;
byte rsvdmask_pos;
byte color_attrib;		//1&=can change color ramp, 2&=can use reserved component bits

}ModeInfo;

int *setup_exptab;
int (*call_rm)(int fcn, ...);

int gfxvesa_width, gfxvesa_height, gfxvesa_pixelsz, gfxvesa_banksz, gfxvesa_linesz, gfxvesa_banks, gfxvesa_winsz, gfxvesa_modenum;

byte *gfxvesa_scrbuf;

byte gfxvesa_palette[1024];

static int get_word(byte *b)
{
	return(b[0]+(b[1]<<8));
}

static void *get_farptr(byte *b)
{
	return((b[0]+(b[1]<<8))+((b[2]+(b[3]<<8))<<4));
}

static int rc_rgb2pel16(int r, int g, int b)
{
	return(((b&0xF8)>>3)+((g&0xF8)<<2)+((r&0xF8)<<7));
}

static int rc_rgb2pel8(int r, int g, int b)
{
	return(((b&0xC0)>>1)+((g&0xE0)>>3)+((r&0xC0)>>6));
}

int gfxvesa_pf_handler(int addr, KPFHandler *ctx)
{
	int roffs, dp, dl;
	int i;

	dp=(int)ctx->data;
	dl=640*480*2;

	Address_ReserveRegion(dp>>12, (dl+1023)>>12);

	roffs=addr-dp;
	i=roffs/gfxvesa_banksz;
	call_rm(setup_exptab[VESA_SETBANK], i);

	i=dp+(i*gfxvesa_banksz);
	i>>=12;

	Address_MapRange(i, 0xA0, gfxvesa_banksz>>12);

	return(1);
}

byte *GfxVesa_GetLFB()
{
	int space, pages;
	KPFHandler *hdl;

	pages=((640*480*2)+1023)>>12;
	space=Address_ReserveRegion(0, pages);
	if(!space)return(NULL);

	hdl=KPFH_CreateContext(space, pages, (void *)(space<<12));

	hdl->pf_proc=&gfxvesa_pf_handler;

	return(hdl->data);
}

int GfxDrv_FillSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k, c;
	int aw;
	byte *buf;

	if(x<0)
	{
		w+=x;
		x=0;
	}
	if(y<0)
	{
		h+=y;
		y=0;
	}
	if(x>=640)return(0);
	if(y>=480)return(0);

	if((x+w)>640)w-=(x+w)-640;
	if((y+h)>480)h-=(y+h)-480;

	if(w<=0)return(0);
	if(h<=0)return(0);

	c=rc_rgb2pel8(r, g, b);
	buf=gfxvesa_scrbuf;

	for(i=0; i<h; i++)
	{
		k=((i+y)*640)+x;
		j=w;
//		for(j=0; j<w; j++)
		while(j--)
		{
//			buf[((i+y)*640)+j+x]=c;
			buf[k++]=c;
		}
	}

	return(0);
}

int GfxDrv_BeginDrawing()
{
	memset(gfxvesa_scrbuf, 0, 640*480);
}

int GfxDrv_EndDrawing()
{
//	call_rm(setup_exptab[VESA_BLITSCREEN], gfxvesa_scrbuf, gfxvesa_banks, gfxvesa_banksz);
}

int GfxDrv_DrawCell(byte *cell, int cw, int ch, int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k;
	int px, py, sx, sy;
	int aw, c;
	byte *buf;

	px=0;
	py=0;
	sx=(cw<<24)/w;
	sy=(ch<<24)/h;

	aw=255-a;
	c=rc_rgb2pel8(r, g, b);
	buf=gfxvesa_scrbuf;

	for(i=0; i<h; i++)
	{
		if((i+y)<0)continue;
		if((i+y)>=480)continue;
		for(j=0; j<w; j++)
		{
			if((j+x)<0)continue;
			if((j+x)>=640)continue;

			k=GfxDev_GetCellBit(cell, cw, ch, (px+(1<<23))>>24, (py+(1<<23))>>24);
			if(k)
			{
//				gfxdev_buf[((((i+y)*640)+j+x)*4)+0]=((b*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+0]*aw))>>8;
//				gfxdev_buf[((((i+y)*640)+j+x)*4)+1]=((g*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+1]*aw))>>8;
//				gfxdev_buf[((((i+y)*640)+j+x)*4)+2]=((r*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+2]*aw))>>8;

				buf[((i+y)*640)+j+x]=c;
			}
			px+=sx;
		}
		py+=sy;
		px=0;
	}
}

int GfxDrv_Start()
{
	ModeInfo *mode;

	byte *gfxbuf;
	int i, j;

	gfxvesa_modenum=0x101;

	mode=(ModeInfo *)call_rm(setup_exptab[VESA_GETMODEINFO], gfxvesa_modenum);
	gfxvesa_width=get_word(mode->xsize);
	gfxvesa_height=get_word(mode->ysize);
	gfxvesa_pixelsz=(mode->bpp+7)>>3;
	gfxvesa_banksz=get_word(mode->banksize)*1024;
	gfxvesa_linesz=get_word(mode->scanline_sz);
	gfxvesa_winsz=get_word(mode->winsize)*1024;

	gfxvesa_banks=(gfxvesa_height*gfxvesa_linesz+(gfxvesa_banksz-1))/gfxvesa_banksz;

//	gfxvesa_scrbuf=kalloc(gfxvesa_height*gfxvesa_linesz);
//	gfxvesa_scrbuf=(byte *)(Page_Alloc((gfxvesa_height*gfxvesa_linesz+4095)>>12)<<12);

//	Address_MapRange(0xE0000, 0xE0000, 0x4000);
//	gfxvesa_scrbuf=0xE0000000;

	gfxvesa_scrbuf=GfxVesa_GetLFB();

	kprint("vesa: banksz=%d, winsz=%d, banks=%d\n", gfxvesa_banksz, gfxvesa_winsz, gfxvesa_banks);

	call_rm(setup_exptab[VESA_SETMODE], gfxvesa_modenum);

//	for(i=0; i<128; i++)
//	{
//		gfxvesa_palette[(i*4)+3]=0;
//		gfxvesa_palette[(i*4)+2]=(i&3)<<4;
//		gfxvesa_palette[(i*4)+1]=(i&0x1c)<<1;
//		gfxvesa_palette[(i*4)+0]=(i&0x60)>>1;
//	}
//	i=(int)(&gfxvesa_palette);
//	j=i>>4;
//	j=(j<<16)+(i&0xF);
//	call_rm(setup_exptab[VESA_SETPALETTE], j);

//	memset(gfxvesa_scrbuf, 255, gfxvesa_height*gfxvesa_linesz);
	memset(gfxvesa_scrbuf, 0, gfxvesa_height*gfxvesa_linesz);

//	call_rm(setup_exptab[VESA_BLITSCREEN], gfxvesa_scrbuf, gfxvesa_banks, gfxvesa_banksz);

//	gfxbuf=(byte *)0xA0000;
//	for(i=0; i<gfxvesa_banks; i++)
//	{
//		call_rm(setup_exptab[VESA_SETBANK], i);
//		memcpy(gfxbuf, gfxvesa_scrbuf+(i*gfxvesa_banksz), gfxvesa_banksz);
//	}
}

int GfxDrv_Init()
{
	int *s;
	int i;
	VesaInfo *info;
	ModeInfo *mode;
	u2 *sa;

	kprint("init vesa.\n");

	s=(int *)0xC0000;
	for(i=0; i<8192; i++)
	{
		if(s[i]==PMID)
		{
			kprint("VESA: PMID found.\n");
			break;
		}
	}
	kprint("vesa getinfo.\n");
//	vesall_getinfo();
	setup_exptab=(int *)0xF600;

	call_rm=(void *)setup_exptab[0];

	info=(VesaInfo *)call_rm(setup_exptab[VESA_GETINFO]);
	s=(int *)info;

//	kprint("\treturned\n");

//	s=(int *)0x4000;
	if(s[0]==VESA)
	{
		kprint("vesa: info function success.\n");

		kprint("vesa version: %d.%d\n", info->ver[1], info->ver[0]);
		kprint("vesa oem: %s\n", get_farptr(info->far_oemname));
		kprint("vesa vidmem: %dKiB\n", get_word(info->vidmem)*64);

		kprint("vesa modelist: ");
		sa=get_farptr(info->far_modelist);
		while(*sa!=0xFFFF)
		{
			//kprint("%X ", *sa);
//			mode=(ModeInfo *)call_rm(setup_exptab[VESA_GETMODEINFO], *sa);

//			kprint("mode %d: %dx%dx%dbpp\n", *sa, get_word(mode->xsize), get_word(mode->ysize), mode->bpp);

			sa++;
		}
		kprint("\n");
	}
}
