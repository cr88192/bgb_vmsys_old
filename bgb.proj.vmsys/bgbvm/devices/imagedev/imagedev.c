#include <general.h>

static VFILE *imgdev_open(char *name, char *unit)
{
//	VFILE *tmp;
//	tmp=vffopen("heapimg.img", "r+b");
	return(NULL);
}

int Imagedev_Init()
{
	Driver_RegisterStream("imagedev", &imgdev_open);
}
