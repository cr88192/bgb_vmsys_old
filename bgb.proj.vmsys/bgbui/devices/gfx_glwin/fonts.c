#include <general.h>
#include <graphics/render.h>

#include <GL/GL.h>

typedef struct fontfrag_s {
struct fontfrag_s *next, *prev; //in parent font
struct fontinfo_s *parent;
int base;	//base character

byte usemap[8];
byte *buffer;
int texnum;
}fontfrag;

typedef struct fontinfo_s {
struct fontinfo_s *next;	//next in the list of fonts
struct fontinfo_s *chain;	//font to try if needed chars are not present
char *name;

byte *buf;
int w, h;
int s, e;
fontfrag *frag;
}fontinfo;

fontinfo *font_root, *font_cur;
fontfrag *font_freefrags;

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

int GfxFont_GetCellBit(byte *cell, int w, int h, int x, int y, int rw, int rh)
{
	int i, j, k;

	x=(float)x*((float)w)/((float)rw);
	y=(float)y*((float)h)/((float)rh);

	if(x>=w)x=w-1;
	if(y>=h)y=h-1;

	i=(y*w)+x;
	j=i&7;
	i>>=3;

	k=cell[i];

#if 0
	if((rh<16) && (h==16))
	{
		i&=0xe;
		k=cell[i]|cell[i+1];
	}else k=cell[i];
#endif

	return((k>>(7-j))&1);
}

int GfxFont_RenderCell(fontinfo *font, fontfrag *frag, int c)
{
	byte *cell;
	int f, y, x;
	int i, j, k;
	int cw, ch;
	int bw, bh;
	int p;

	f=c/64;

	y=(c/8)&7;
	x=c&7;

	cell=GfxFont_FetchChar(font, c, &cw, &ch);
	if(!cell)
	{
//		kprint("render cell: fail %d\n", c);
		frag->usemap[y]|=(1<<x);
		return(-1);
	}

	bw=font->w;
	bh=font->h;
//	bw=16;
//	bh=16;

//	kprint("render cell: %d %d:%d (%d %d) (%d %d)\n", c, x, y, bw, bh, cw, ch);

//	memset(frag->buffer, 255, bw*bh*64*4);

	for(i=0; i<bh; i++)for(j=0; j<bw; j++)
	{
		p=(((y*bh)+(bh-i))*(bw*8))+((x*bw)+j);
		k=GfxFont_GetCellBit(cell, cw, ch, j, i, bw, bh);
//		k=1;
		if(k)
		{
			frag->buffer[(p*4)+0]=255;
			frag->buffer[(p*4)+1]=255;
			frag->buffer[(p*4)+2]=255;
			frag->buffer[(p*4)+3]=255;
		}else
		{
			frag->buffer[(p*4)+0]=0;
			frag->buffer[(p*4)+1]=0;
			frag->buffer[(p*4)+2]=0;
			frag->buffer[(p*4)+3]=0;
		}
	}

	frag->usemap[y]|=(1<<x);

#if 0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frag->texnum);
	glTexImage2D (GL_TEXTURE_2D, 0, 4, 8*bw, 8*bh, 0, GL_RGBA, GL_UNSIGNED_BYTE, frag->buffer);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	return(0);
}

fontfrag *GfxFont_FetchFrag(fontinfo *font, int c)
{
	fontfrag *cur;
	int f, y, x;
	int i;

	f=c/64;
	y=(c/8)&7;
	x=c&7;

	cur=font->frag;
	while(cur)
	{
		if(f==cur->base)break;
		cur=cur->next;
	}
	if(!cur)
	{
		kprint("new frag\n");
		cur=kalloc(sizeof(fontfrag));
//		cur->buffer=kalloc(font->w*font->h*64*4);
		cur->buffer=kalloc(16*16*64*4);
		cur->base=c/64;
		cur->texnum=Tex_AllocTexnum();

		memset(cur->buffer, 0, 16*16*64*4);
		memset(cur->usemap, 0, 8);

		cur->parent=font;
		cur->next=font->frag;
		font->frag=cur;
	}

	if(!(cur->usemap[y]&(1<<x)))
	{
		GfxFont_RenderCell(font, cur, c);

#if 1
		for(i=0; i<64; i++)
		{
			x=i&7;
			y=i>>3;

			if(!(cur->usemap[y]&(1<<x)))
				GfxFont_RenderCell(font, cur, (cur->base<<6)+i /* c */);
		}
#endif

#if 0
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cur->texnum);
		glTexImage2D (GL_TEXTURE_2D, 0, 4, 8*font->w, 8*font->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, cur->buffer);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
		Tex_LoadTexture2(8*font->w, 8*font->h, cur->buffer, 2, cur->texnum, 0);
	}

	return(cur);
}

int GfxFont_DrawChar(int c, int x, int y, int w, int h, int r, int g, int b, int a)
{
	byte *cell;
	int cw, ch, n;
	float s1, t1, s2, t2;
	fontfrag *frag;

//	kprint("draw char %d (%d %d) (%d %d)\n", c, x, y, w, h);

	frag=GfxFont_FetchFrag(font_cur, c);

	glDisable (GL_CULL_FACE);
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frag->texnum);

//	glEnable (GL_BLEND);
//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	glShadeModel (GL_SMOOTH);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	n=c&63;

	s1=(n%8)/8.0;
	t1=(n/8)/8.0;
	s2=(n%8+1)/8.0;
	t2=(n/8+1)/8.0;

//	s1=0;
//	t1=1;
//	s2=1;
//	t2=0;

//	glColor4f(1, 0, 0, 1);
	glColor4f(r/255.0, g/255.0, b/255.0, a/255.0);

	glBegin(GL_QUADS);
	glTexCoord2f(s1, t1);
	glVertex2f(x, y);

	glTexCoord2f(s1, t2);
	glVertex2f(x, y+h);

	glTexCoord2f(s2, t2);
	glVertex2f(x+w, y+h);

	glTexCoord2f(s2, t1);
	glVertex2f(x+w, y);
	glEnd();

	glDisable (GL_TEXTURE_2D);

//	kprint("draw char %d\n", c);

//	cell=GfxFont_FetchChar(font_cur, c, &cw, &ch);
//	if(cell)GfxDrv_DrawCell(cell, cw, ch, x, y, w, h, r, g, b, a);
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
	fontinfo *f, *f2;

	font_root=NULL;
	font_cur=NULL;

	GfxFont_Register("fixed", font_8x8_32_96, 8, 8,  32, 127);
	GfxFont_Register("koi8-r", koi8r_8x16, 8, 16, 32, 255);
	GfxFont_Register("cp866", cp866_8x16, 8, 16, 32, 255);

	GfxFont_Register("mouse", mouse_16x16, 16, 16, 32, 32);

//	GfxFont_LoadFont("unicode", "etl16.bfn");
	GfxFont_LoadFont("bgb0", "bgb0.bfn");
	GfxFont_LoadFont("unicode", "unifont.bfn");

//	f=GfxFont_FindFont("fixed");
//	f2=GfxFont_FindFont("unicode");
//	f->chain=f2;

	return(0);
}
