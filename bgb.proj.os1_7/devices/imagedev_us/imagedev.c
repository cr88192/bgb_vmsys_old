#include <general.h>

static VFILE *imgdev_open(char *name, char *unit)
{
	VFILE *tmp;
	tmp=vffopen("storeimg.img", "r+b");
	return(tmp);
}

int Imagedev_Init()
{
	Driver_RegisterStream("imagedev", &imgdev_open);
}
