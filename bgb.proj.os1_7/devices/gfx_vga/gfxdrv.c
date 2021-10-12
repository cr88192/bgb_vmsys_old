#include <general.h>
#include <graphics/render.h>

extern unsigned char *VGA_ScreenBuf;

int gfxdev_plane_sz;
byte *gfxdev_plane_r;
byte *gfxdev_plane_g;
byte *gfxdev_plane_b;
byte *gfxdev_plane_i;

int GfxDrv_FillSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k, l;
	int nw;

//	kprint("GfxDrv_FillSquare: (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h, r, g, b, a);

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

//	kprint("GfxDrv_FillSquare: (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h, r, g, b, a);

	a=0;
	if(r>127)a=1;
	if(g>127)a=1;
	if(b>127)a=1;

	k=7-(x&7);
	j=(1<<k)-1;
	l=(x>>3)+(y*80);

	nw=w-k;

	if(r)for(i=0; i<h; i++)
		gfxdev_plane_r[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_r[l+(i*80)]&=~j;
	if(g)for(i=0; i<h; i++)
		gfxdev_plane_g[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_g[l+(i*80)]&=~j;
	if(b)for(i=0; i<h; i++)
		gfxdev_plane_b[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_b[l+(i*80)]&=~j;
	if(a)for(i=0; i<h; i++)
		gfxdev_plane_i[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_i[l+(i*80)]&=~j;

	l+=nw>>3;
	k=7-(nw&7);
	j=~((1<<k)-1);

	if(r)for(i=0; i<h; i++)
		gfxdev_plane_r[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_r[l+(i*80)]&=~j;
	if(g)for(i=0; i<h; i++)
		gfxdev_plane_g[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_g[l+(i*80)]&=~j;
	if(b)for(i=0; i<h; i++)
		gfxdev_plane_b[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_b[l+(i*80)]&=~j;
	if(a)for(i=0; i<h; i++)
		gfxdev_plane_i[l+(i*80)]|=j;
		else for(i=0; i<h; i++)
			gfxdev_plane_i[l+(i*80)]&=~j;

	for(i=0; i<h; i++)
	{
		l=((x+7)>>3)+((i+y)*80);

		j=w>>3;
		k=l;
		if(r)memset(gfxdev_plane_r+l, 0xff, j);
			else memset(gfxdev_plane_r+l, 0, j);
		if(g)memset(gfxdev_plane_g+l, 0xff, j);
			else memset(gfxdev_plane_g+l, 0, j);
		if(b)memset(gfxdev_plane_b+l, 0xff, j);
			else memset(gfxdev_plane_b+l, 0, j);
		if(a)memset(gfxdev_plane_i+l, 0xff, j);
			else memset(gfxdev_plane_i+l, 0, j);
	}

//	kprint("GfxDrv_FillSquare: done.\n");

	return(0);
}

int GfxDrv_DrawImgPL(
	int x, int y, int w, int h,
	int ix, int iy,
	byte *img, //image, 8bpp, RGBIA000
	int xs, int ys)
{
	int i, j, k, l, m, n;
	int p;

//	kprint("GfxDrv_FillSquare: (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h, r, g, b, a);

	if(x<0)
	{
		ix-=x;
		w+=x;
		x=0;
	}
	if(y<0)
	{
		iy-=y;
		h+=y;
		y=0;
	}
	if(x>=640)return(0);
	if(y>=480)return(0);
	if(ix>=xs)return(0);
	if(iy>=ys)return(0);

	if((x+w)>640)w-=(x+w)-640;
	if((y+h)>480)h-=(y+h)-480;
	if((ix+w)>xs)w-=(ix+w)-xs;
	if((iy+h)>ys)h-=(iy+h)-ys;

	if(w<=0)return(0);
	if(h<=0)return(0);

//	kprint("GfxDrv_FillSquare: (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h, r, g, b, a);

	for(i=0; i<h; i++)
	{
		n=(i+y)*80;
		p=((i+iy)*xs)+ix;
		for(j=0; j<w; j++)
		{
//			k=img[((i+iy)*xs)+(j+ix)];
			k=img[p++];
			if(!(k&16))continue;

			l=n+((x+j)>>3);
//			m=1<<((x+j)&7);
			m=128>>((x+j)&7);

			//+(n*80)
			if(k&1)gfxdev_plane_r[l]|=m;
				else gfxdev_plane_r[l]&=~m;
			if(k&2)gfxdev_plane_g[l]|=m;
				else gfxdev_plane_g[l]&=~m;
			if(k&4)gfxdev_plane_b[l]|=m;
				else gfxdev_plane_b[l]&=~m;
			if(k&8)gfxdev_plane_i[l]|=m;
				else gfxdev_plane_i[l]&=~m;
		}
	}

//	kprint("GfxDrv_FillSquare: done.\n");

	return(0);
}

//resample and convert RGBA32 -> RGBIA8
int GfxDrv_ConvImgPL(byte *ib, int iw, int ih, byte *ob, int ow, int oh)
{
	int i, j, k;
	int x, y;
	int r, g, b, a;

	for(i=0; i<oh; i++)
		for(j=0; j<ow; j++)
	{
		x=(j*iw)/ow;
		y=(i*ih)/oh;

		k=((y*iw)+x)*4;
		r=ib[k+0];
		g=ib[k+1];
		b=ib[k+2];
		a=ib[k+3];
		if(a>127)
		{
			k=16;
			if(r>63)k|=1;
			if(g>63)k|=2;
			if(b>63)k|=4;
			if((r|g|b)>127)k|=8;
		}else k=0;

		ob[(i*ow)+j]=k;
	}

	return(0);
}

int GfxDrv_DrawImg(
	int x, int y, int w, int h,
	int ix, int iy, int iw, int ih,
	byte *img, //image, RGBA32
	int xs, int ys)
{
	int tx, ty;
	int tw, th;
	byte *tb;

	tx=(ix*w)/iw;
	ty=(iy*h)/ih;
//	tw=(xs*w)/iw;
//	th=(ys*h)/ih;
	tw=w;
	th=h;

	tb=kalloc(tw*th);

	GfxDrv_ConvImgPL(img, xs, ys, tb, tw, th);
//	memset(tb, 0x11, tw*th);

	GfxDrv_DrawImgPL(x, y, w, h, tx, ty, tb, tw, th);
	kfree(tb);

	return(0);
}

#if 0
int GfxDrv_DrawCell(byte *cell, int cw, int ch, int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k, l, m;
	int px, py, sx, sy;
	int aw;

//	kprint("draw cell\n");

	if(!w)return(0);
	if(!h)return(0);

	a=0;
	if(r>127)a=1;
	if(g>127)a=1;
	if(b>127)a=1;

	px=0;
	py=0;
	sx=(cw<<24)/w;
	sy=(ch<<24)/h;

	for(i=0; i<h; i++)
	{
		if((i+y)<0)continue;
		if((i+y)>=480)continue;
		for(j=0; j<w; j++)
		{
			if((j+x)<0)continue;
			if((j+x)>=640)continue;

			k=GfxDev_GetCellBit(cell, cw, ch, (px+(1<<23))>>24, (py+(1<<23))>>24, w, h);

			l=((i+y)*80)+((j+x)>>3);
			m=128>>((j+x)&7);
			if(k)
			{
				if(r)gfxdev_plane_r[l]|=m;
					else gfxdev_plane_r[l]&=~m;
				if(g)gfxdev_plane_g[l]|=m;
					else gfxdev_plane_g[l]&=~m;
				if(b)gfxdev_plane_b[l]|=m;
					else gfxdev_plane_b[l]&=~m;
				if(a)gfxdev_plane_i[l]|=m;
					else gfxdev_plane_i[l]&=~m;
			}
			px+=sx;
		}
		py+=sy;
		px=0;
	}
//	kprint("draw cell: ok\n");
}
#endif

int GfxDrv_BeginDrawing()
{
	memset(gfxdev_plane_r, 0, gfxdev_plane_sz);
	memset(gfxdev_plane_g, 0, gfxdev_plane_sz);
	memset(gfxdev_plane_b, 0, gfxdev_plane_sz);
	memset(gfxdev_plane_i, 0, gfxdev_plane_sz);
}

int GfxDrv_EndDrawing()
{
	int i, j, k, c;
	byte *src_r, *src_g, *src_b, *src_i;
	byte *dst;

//	kprint("frame end\n");

	src_r=gfxdev_plane_r;
	src_g=gfxdev_plane_g;
	src_b=gfxdev_plane_b;
	src_i=gfxdev_plane_i;
	dst=VGA_ScreenBuf;

	VGA_SetPlane(3);
	memcpy(dst, src_i, 80*480);
	VGA_SetPlane(2);
	memcpy(dst, src_r, 80*480);
	VGA_SetPlane(1);
	memcpy(dst, src_g, 80*480);
	VGA_SetPlane(0);
	memcpy(dst, src_b, 80*480);

//	kprint("frame end: ok\n");
}

int GfxDrv_Start()
{
	GFX_Init();
	gfxdev_plane_sz=(640*480)/8;
	gfxdev_plane_r=kalloc(gfxdev_plane_sz);
	gfxdev_plane_g=kalloc(gfxdev_plane_sz);
	gfxdev_plane_b=kalloc(gfxdev_plane_sz);
	gfxdev_plane_i=kalloc(gfxdev_plane_sz);
}

int GfxDrv_Init()
{
}
