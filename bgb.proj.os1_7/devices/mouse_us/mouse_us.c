#include <general.h>
#include <graphics/render.h>

extern displaywindow *gfx_screen;

int mouse_lx=320, mouse_ly=240;

int mouse_read(void *buf, int len, VFILE *fd)
{
	int x, y, b;
	mouseinfo *mi;

	mi=buf;

	Window_GetMousePos(gfx_screen, &x, &y, &b);
	mi->dx=x-mouse_lx;
	mi->dy=y-mouse_ly;
	mouse_lx=x;
	mouse_ly=y;

	mi->flags=b&7;

	return(8);
}

VFILE *mouse_open(char *name, void *data)
{
	VFILE *tmp;

	if(!gfx_screen)return(NULL);

	tmp=vfnew();
	tmp->read_proc=mouse_read;

	return(tmp);
}

int Mouse_Init()
{
	Driver_RegisterStream("mouse", &mouse_open, NULL);
}
