#include <general.h>

#include <stdio.h>

#include <gfxdev/render.h>

//#include <gfxdev/window.h>
//#include <gfxdev/keys.h>

displaywindow *gfx_screen;
VFILE *gfx_device;
int gfxdev_offs;
byte *gfxdev_buf;
GSurface *gfx_surface;

int gsurf_drawimage(GSurface *self, GRect dst, GImage *img, GRect src)
{
	GVec dim;
	dim[0]=gfx_screen->width;
	dim[1]=gfx_screen->height;

	switch(img->type)
	{
	case GFX_TYPE_RGB15:
//		ImgFcn_Transfer16(img->data, img->size, src, (short *)gfxdev_buf, dim, dst);
		Window_EndDrawing();
		break;
	default:
		break;
	}
}

static int rc_rgb2pel16(int r, int g, int b)
{
	return(((b&0xF8)>>3)+((g&0xF8)<<2)+((r&0xF8)<<7));
}

static int gc_rgb2pel16(GColor c)
{
	int r, g, b;
	r=c&255;
	g=(c>>8)&255;
	b=(c>>16)&255;
	return(((b&0xF8)>>3)+((g&0xF8)<<2)+((r&0xF8)<<7));
}

int gsurf_setpen(GSurface *self, GColor clr)
{
	self->pen=gc_rgb2pel16(clr);
	return(0);
}

int gsurf_setpenbg(GSurface *self, GColor clr)
{
	self->penbg=gc_rgb2pel16(clr);
	return(0);
}

int gsurf_plotpixel(GSurface *self, GVec pos)
{
	if(pos[0]<0 || pos[0]>gfx_screen->width)return(-1);
	if(pos[1]<0 || pos[1]>gfx_screen->height)return(-1);
	gfxdev_buf[(pos[1]*gfx_screen->width)+pos[0]]=self->pen;
	return(0);
}

int gfxdev_write(void *buf, int len, VFILE *fd)
{
	int i;
	short j;
//	memcpy(gfxdev_buf+gfxdev_offs, buf, len);
	for(i=0; i<(len/2); i++)
	{
		j=*(unsigned short *)(buf+(i*2));
		j=((j&0x7FE0)<<1)+(j&0x1F);
		*(short *)(gfxdev_buf+(gfxdev_offs+(i*2)))=j;
	}
	gfxdev_offs+=len;
	return(len);
}

int gfxdev_read(void *buf, int len, VFILE *fd)
{
	memcpy(buf, gfxdev_buf+gfxdev_offs, len);
	gfxdev_offs+=len;
	return(len);
}

int gfxdev_seek(VFILE *fd, int pos, int rel)
{
	gfxdev_offs=pos;
	return(pos);
}

int gfxdev_flush(VFILE *fd)
{
	Window_EndDrawing();
	return(0);
}

int gfxdev_ioctls(VFILE *fd, void **arg)
{
	char *s;
	s=*arg;
	if(!strcmp(s, "get-width"))
	{
		*(int *)arg[1]=gfx_screen->width;
		return(0);
	}
	if(!strcmp(s, "get-height"))
	{
		*(int *)arg[1]=gfx_screen->height;
		return(0);
	}
	if(!strcmp(s, "get-bits"))
	{
		*(int *)arg[1]=16;
		return(0);
	}
	if(!strcmp(s, "get-surface"))
	{
		*(GSurface **)arg[1]=gfx_surface;
		return(0);
	}
	return(-1);
}

VFILE *gfxdev_open(char *name, char *unit)
{
	VFILE *tmp;
	int i;
	byte *buf;

	tmp=gfx_device;
	if(!tmp)
	{
		Window_Init();
		gfx_screen=Window_NewWindow_NOGL(640, 480);
		Window_SetWindow(gfx_screen);
		Window_BeginDrawing();

		buf=Window_GetWindowBuffer(gfx_screen);
//		memset(buf, 255, 640*480*2);
		gfxdev_buf=buf;
		gfxdev_offs=0;

		Window_EndDrawing();

		tmp=vfnew();
		tmp->write_proc=gfxdev_write;
		tmp->read_proc=gfxdev_read;
		tmp->seek_proc=gfxdev_seek;
		tmp->flush_proc=gfxdev_flush;
		tmp->ioctls_proc=gfxdev_ioctls;
		gfx_device=tmp;

		gfx_surface=kalloc(sizeof(GSurface));
		gfx_surface->draw_image=gsurf_drawimage;
		gfx_surface->set_pen=gsurf_setpen;
		gfx_surface->set_penbg=gsurf_setpenbg;
		gfx_surface->plot_pixel=gsurf_plotpixel;
	}
	return(tmp);
}

byte *Window_GetWindowBuffer(displaywindow *wind);

int Gfxdev_Init()
{
	Driver_RegisterStream("gfxdev", &gfxdev_open);
}
