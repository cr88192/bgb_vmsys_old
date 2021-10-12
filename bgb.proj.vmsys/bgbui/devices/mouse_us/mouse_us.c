#include <general.h>
#include <graphics/render.h>

#include <windows.h>

int	mouse_lx, mouse_ly, mouse_lb;
POINT	mouse_pos;

extern int window_center_x, window_center_y;
extern int window_mouse_buttons;


int mouse_read(void *buf, int len, VFILE *fd)
{
	int x, y, b;
	mouseinfo *mi;

	mi=buf;

	GetCursorPos (&mouse_pos);
//	SetCursorPos (window_center_x, window_center_y);
	x=mouse_pos.x-window_center_x;
	y=mouse_pos.y-window_center_y;

	b=window_mouse_buttons;

//	if((x-window_center_x)<=-400)x=window_center_x-400;
//	if((x-window_center_x)>=400)x=window_center_x+400;
//	if((y-window_center_y)<=-300)y=window_center_y-300;
//	if((y-window_center_y)>=300)y=window_center_y+300;

	if ((x<=-400) || (x>=400) || (y<=-300) || (y>=300))
	{
		x=mouse_lx;
		y=mouse_ly;
//		b=mouse_lb;
	}


//	kprint("mouse: %d %d %d\n", x, y, b);

//	Window_GetMousePos(gfx_screen, &x, &y, &b);

	mi->dx=x-mouse_lx;
	mi->dy=y-mouse_ly;
	mouse_lx=x;
	mouse_ly=y;
	mouse_lb=b;

	mi->flags=b&7;

	return(8);
}

int mouse_write(void *buf, int len, VFILE *fd)
{
	int x, y, b;
	mouseinfo *mi;

	mi=buf;

	x=window_center_x+mi->dx;
	y=window_center_y+mi->dy;

	SetCursorPos (x, y);
	mouse_lx = mi->dx;
	mouse_ly = mi->dy;

	return(len);
}

VFILE *mouse_open(char *name, void *data)
{
	VFILE *tmp;

//	if(!gfx_screen)return(NULL);

	tmp=vfnew();
	tmp->read_proc=mouse_read;
	tmp->write_proc=mouse_write;

	SetCursorPos (window_center_x, window_center_y);
	mouse_lx = 0;
	mouse_ly = 0;
	mouse_lb = 0;

	return(tmp);
}

int Mouse_Init()
{
	Driver_RegisterStream("mouse", &mouse_open, NULL);
}
