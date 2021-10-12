#include <general.h>
#include <gfxdev/render.h>

static VFILE *gfx_device;
static int gfxdev_offs;
static byte *gfxdev_buf;
static int gfx_width, gfx_height;

GSurface *gfx_surface;

int GFX_SubmitBuffer(u2 *buf);

int gsurf_drawimage(GSurface *self, GRect dst, GImage *img, GRect src)
{
	GVec dim;
	dim[0]=gfx_width;
	dim[1]=gfx_height;

	switch(img->type)
	{
	case GFX_TYPE_RGB15:
//		ImgFcn_Transfer16(img->data, img->size, src, (short *)gfxdev_buf, dim, dst);
//		Window_EndDrawing();
		GFX_SubmitBuffer(gfxdev_buf);
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
	if(pos[0]<0 || pos[0]>gfx_width)return(-1);
	if(pos[1]<0 || pos[1]>gfx_height)return(-1);
	gfxdev_buf[(pos[1]*gfx_width)+pos[0]]=self->pen;
	return(0);
}

int gfxdev_write(void *buf, int len, VFILE *fd)
{
	int i;
	short j;
	memcpy(gfxdev_buf+gfxdev_offs, buf, len);
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
//	Window_EndDrawing();
	GFX_SubmitBuffer(gfxdev_buf);
	return(0);
}

int gfxdev_ioctls(VFILE *fd, void **arg)
{
	char *s;
	s=*arg;
	if(!strcmp(s, "get-width"))
	{
		*(int *)arg[1]=gfx_width;
		return(0);
	}
	if(!strcmp(s, "get-height"))
	{
		*(int *)arg[1]=gfx_height;
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

int GfxDrv_Init()
{
	GFX_Init();
}

#if 0
VFILE *gfxdev_open(char *name, char *unit)
{
	VFILE *tmp;

	tmp=gfx_device;
	if(!tmp)
	{
		GFX_Init();

		gfxdev_offs=0;
		gfxdev_buf=kalloc(640*480*2);

		gfx_width=640;
		gfx_height=480;

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

int Gfxdev_Init()
{
	Driver_RegisterStream("gfxdev", &gfxdev_open);
}
#endif