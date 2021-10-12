#include <general.h>
#include <graphics/render.h>


int mouse_read(void *buf, int len, VFILE *fd)
{
	int x, y, i, j;
	static int b;
	mouseinfo *mi;

	mi=buf;

	mi->dx=0;
	mi->dy=0;
	mi->flags=0;

//	return(0);

	x=0;
	y=0;
	i=5;
	while(vfinready(fd->buffer))
	{
		kprint("mouse input\n");
		j=vfgetc(fd->buffer);
		if(j&64)
		{
			mi->dx+=x;
			mi->dy+=y;

			i=0;
			b=0;
			if(j&32)b|=1;
			if(j&16)b|=2;

			kprint("move %d %d %d\n", x, y, b);

			x=(j&3)<<6;
			y=(j&0xc)<<4;
		}else switch(i)
		{
		case 1:
			x|=j;
			if(x&128)x|=~255;
			break;
		case 2:
			y|=j;
			if(y&128)y|=~255;
			break;
		case 3:
			if(j&32)b|=4;
			break;
		}
		i++;
	}

	mi->flags=b;

//	kprint("mouse delta %d %d %d\n", mi->dx, mi->dy, b);

	return(8);
}

VFILE *mouse_open(char *name, void *data)
{
	VFILE *tmp;

//	if(!gfx_screen)return(NULL);

	tmp=vfnew();
	tmp->read_proc=mouse_read;

	tmp->buffer=data;

	return(tmp);
}

int Mouse_Init()
{
	VFILE *fd;

	kprint("Mouse_Init\n");

	fd=Driver_OpenStream("serial/1");
	if(!fd)
	{
		panic("failed open serial.\n");
	}
	vfioctls(fd, "set-baud", 1200);
	vfioctls(fd, "set-mode", "7N2");

	Driver_RegisterStream("mouse", &mouse_open, fd);
}
