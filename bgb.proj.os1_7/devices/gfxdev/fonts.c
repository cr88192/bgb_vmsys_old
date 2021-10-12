#include <general.h>
#include <graphics/render.h>

typedef struct fontinfo_s {
struct fontinfo_s *next;	//next in the list of fonts
struct fontinfo_s *chain;	//font to try if needed chars are not present
char *name;

byte *buf;
int w, h;
int s, e;
}fontinfo;

fontinfo *font_root, *font_cur;

extern unsigned char font_8x8_32_96[96*8];
extern unsigned char koi8r_8x16[];
extern unsigned char cp866_8x16[];

byte mouse_16x16[32]={
0x00, 0x07,		/* 0000000000000111 */
0x00, 0x0F,		/* 0000000000001111 */
0x00, 0x1F,		/* 0000000000011111 */
0x00, 0x3E,		/* 0000000000111110 */
0x80, 0x7C,		/* 1000000001111100 */
0xC0, 0xF8,		/* 1100000011111000 */
0xE1, 0xF0,		/* 1110000111110000 */
0xF3, 0xE0,		/* 1111001111100000 */
0xFF, 0xC0,		/* 1111111111000000 */
0xFF, 0x80,		/* 1111111110000000 */
0xFF, 0x00,		/* 1111111100000000 */
0xFF, 0x00,		/* 1111111100000000 */
0xFF, 0x80,		/* 1111111110000000 */
0xFF, 0xC0,		/* 1111111111000000 */
0xFF, 0xE0,		/* 1111111111100000 */
0xFF, 0xF0,		/* 1111111111110000 */

};

int GfxFont_Register(char *name, char *buf, int w, int h, int s, int e)
{
	fontinfo *tmp;

	tmp=kalloc(sizeof(fontinfo));
	tmp->name=kstrdup(name);
	tmp->buf=buf;
	tmp->w=w;
	tmp->h=h;
	tmp->s=s;
	tmp->e=e;

	tmp->next=font_root;
	font_root=tmp;

	return(0);
}

fontinfo *GfxFont_FindFont(char *name)
{
	fontinfo *cur;

	cur=font_root;
	while(cur)
	{
		if(!strcmp(cur->name, name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

byte *GfxFont_FetchChar(fontinfo *font, int c, int *w, int *h)
{
	fontinfo *cur;
	int i;

	cur=font;
	while(cur)
	{
		if((c>=cur->s) && (c<=cur->e))
		{
			*w=cur->w;
			*h=cur->h;
			i=c-cur->s;
			i=i*((cur->w*cur->h)/8);

//			kprint("fetched char %s, %d, %d\n", cur->name, c, i);

			return(cur->buf+i);
		}
//		kprint("didn't find char %d\n", c);
		cur=cur->chain;
	}
	return(NULL);
}

int GfxFont_DrawChar(int c, int x, int y, int w, int h, int r, int g, int b, int a)
{
	byte *cell;
	int cw, ch;

//	kprint("draw char %d\n", c);

	cell=GfxFont_FetchChar(font_cur, c, &cw, &ch);
	if(cell)GfxDrv_DrawCell(cell, cw, ch, x, y, w, h, r, g, b, a);
}

int GfxFont_SetFont(char *name)
{
	fontinfo *font;

	font=GfxFont_FindFont(name);
	if(font)font_cur=font;
		else kprint("no font '%s'\n", name);
}

int GfxFont_LoadFont(char *name, char *fname)
{
	VFILE *fd;
	fontinfo *tmp, *cur;
	byte *buf;
	int s, e;
	int cw, ch;

	fd=vffopen(fname, "rb");
	cur=NULL;

	s=vfgetc(fd);
	s+=vfgetc(fd)<<8;

	e=vfgetc(fd);
	e+=vfgetc(fd)<<8;

	if(s==0xBF00)
	{
		buf=kalloc(16);
		vfread(buf, 1, e, fd);
		cw=buf[1];
		ch=buf[2];
	}else
	{
		kprint("no header\n");
		return(-1);
	}

	while(1)
	{
		s=vfgetc(fd);
		s+=vfgetc(fd)<<8;

		e=vfgetc(fd);
		e+=vfgetc(fd)<<8;

		if(!s && !e)break;

//		kprint("chunk %d-%d\n", s, e);

		buf=kalloc(((e-s)+1)*((cw*ch)/8));
		vfread(buf, (e-s)+1, ((cw*ch)/8), fd);

		tmp=kalloc(sizeof(fontinfo));
		tmp->name=kstrdup(name);
		tmp->buf=buf;
		tmp->w=cw;
		tmp->h=ch;
		tmp->s=s;
		tmp->e=e;

		tmp->chain=cur;
		cur=tmp;
	}
	if(cur)
	{
		cur->next=font_root;
		font_root=cur;
	}
	return(0);
}

int GfxFont_Init()
{
	font_root=NULL;
	font_cur=NULL;

	GfxFont_Register("fixed", font_8x8_32_96, 8, 8,  32, 127);
	GfxFont_Register("koi8-r", koi8r_8x16, 8, 16, 32, 255);
	GfxFont_Register("cp866", cp866_8x16, 8, 16, 32, 255);

	GfxFont_Register("mouse", mouse_16x16, 16, 16, 32, 32);

	GfxFont_LoadFont("unicode", "etl16.bfn");
	GfxFont_LoadFont("bgb0", "bgb0.bfn");
//	GfxFont_LoadFont("unicode", "merge3.bfn");
}
