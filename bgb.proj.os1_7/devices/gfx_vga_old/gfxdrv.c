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

	kprint("GfxDrv_FillSquare: (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h, r, g, b, a);

	for(i=0; i<h; i++)
	{
		k=7-(x&7);
		l=x>>3;
		for(j=0; j<k; j++)
		{
			if(r)gfxdev_plane_r[((i+y)*80)+l]|=128>>j;
			if(g)gfxdev_plane_g[((i+y)*80)+l]|=128>>j;
			if(b)gfxdev_plane_b[((i+y)*80)+l]|=128>>j;
			gfxdev_plane_i[((i+y)*80)+j+l]|=128>>j;
		}
		if(k)l++;
		k=(w-k)>>3;
		for(j=0; j<k; j++)
		{
			if(r)gfxdev_plane_r[((i+y)*80)+j+l]=0xff;
			if(g)gfxdev_plane_g[((i+y)*80)+j+l]=0xff;
			if(b)gfxdev_plane_b[((i+y)*80)+j+l]=0xff;
			gfxdev_plane_i[((i+y)*80)+j+l]=0xff;
		}
		l+=k;
		k=7-((x+w)&7);
//		l=(x+w)>>3;
		for(j=0; j<k; j++)
		{
			if(r)gfxdev_plane_r[((i+y)*80)+l]|=128>>j;
			if(g)gfxdev_plane_g[((i+y)*80)+l]|=128>>j;
			if(b)gfxdev_plane_b[((i+y)*80)+l]|=128>>j;
			gfxdev_plane_i[((i+y)*80)+l]|=128>>j;
		}
	}

	return(0);
}

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

	src_r=gfxdev_plane_r;
	src_g=gfxdev_plane_g;
	src_b=gfxdev_plane_b;
	src_i=gfxdev_plane_i;
	dst=VGA_ScreenBuf;

/*
	for(i=0; i<80*480; i++)
	{
		VGA_SetPlane(3);
		*dst=*src_i++;

		VGA_SetPlane(2);
		*dst=*src_r++;

		VGA_SetPlane(1);
		*dst=*src_g++;

		VGA_SetPlane(0);
		*dst=*src_b++;

		dst++;
	} */

	VGA_SetPlane(3);
	memcpy(dst, src_i, 80*480);
	VGA_SetPlane(2);
	memcpy(dst, src_r, 80*480);
	VGA_SetPlane(1);
	memcpy(dst, src_g, 80*480);
	VGA_SetPlane(0);
	memcpy(dst, src_b, 80*480);
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