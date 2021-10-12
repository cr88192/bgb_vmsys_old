#include <general.h>
#include <graphics/render.h>

displaywindow *gfx_screen;
byte *gfxdev_buf;

int GfxDrv_FillSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k;
	int aw;

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

	aw=255-a;

	for(i=0; i<h; i++)
	{
		k=(((i+y)*640)+x)*4;
		for(j=0; j<w; j++)
		{
//			gfxdev_buf[((((i+y)*640)+j+x)*4)+0]=((b*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+0]*aw))>>8;
//			gfxdev_buf[((((i+y)*640)+j+x)*4)+1]=((g*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+1]*aw))>>8;
//			gfxdev_buf[((((i+y)*640)+j+x)*4)+2]=((r*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+2]*aw))>>8;

//			gfxdev_buf[k+0]=((b*a)+(gfxdev_buf[k+0]*aw))>>8;
//			gfxdev_buf[k+1]=((g*a)+(gfxdev_buf[k+1]*aw))>>8;
//			gfxdev_buf[k+2]=((r*a)+(gfxdev_buf[k+2]*aw))>>8;

			gfxdev_buf[k++]=b;
			gfxdev_buf[k++]=g;
			gfxdev_buf[k++]=r;
			k++;
		}
	}

	return(0);
}

int GfxDrv_BeginDrawing()
{
	Window_BeginDrawing();
	memset(gfxdev_buf, 0, 640*480*4);
}

int GfxDrv_EndDrawing()
{
	Window_EndDrawing();
}

int GfxDrv_DrawCell(byte *cell, int cw, int ch, int x, int y, int w, int h, int r, int g, int b, int a)
{
	int i, j, k;
	int px, py, sx, sy;
	int aw;

	if(!w)return(0);
	if(!h)return(0);

	px=0;
	py=0;
	sx=(cw<<24)/w;
	sy=(ch<<24)/h;

	aw=255-a;

	for(i=0; i<h; i++)
	{
		if((i+y)<0)continue;
		if((i+y)>=480)continue;
		for(j=0; j<w; j++)
		{
			if((j+x)<0)continue;
			if((j+x)>=640)continue;

			k=GfxDev_GetCellBit(cell, cw, ch, (px+(1<<23))>>24, (py+(1<<23))>>24, w, h);
			if(k)
			{
				gfxdev_buf[((((i+y)*640)+j+x)*4)+0]=((b*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+0]*aw))>>8;
				gfxdev_buf[((((i+y)*640)+j+x)*4)+1]=((g*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+1]*aw))>>8;
				gfxdev_buf[((((i+y)*640)+j+x)*4)+2]=((r*a)+(gfxdev_buf[((((i+y)*640)+j+x)*4)+2]*aw))>>8;
			}
			px+=sx;
		}
		py+=sy;
		px=0;
	}
}

int GfxDrv_Start()
{
	gfx_screen=Window_NewWindow_NOGL(640, 480);
	Window_SetWindow(gfx_screen);

	Window_BeginDrawing();
	gfxdev_buf=Window_GetWindowBuffer(gfx_screen);
	Window_EndDrawing();
}

int GfxDrv_Init()
{
	Window_Init();
}