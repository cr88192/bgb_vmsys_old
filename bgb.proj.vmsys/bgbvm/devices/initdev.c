#include <general.h>

extern int Condev_Init();
extern int FDC_Init();
extern int ATA_Init();
extern int Gfxdev_Init();
extern int Imagedev_Init();

static int (*inits[])()={
&Condev_Init,
&FDC_Init,
NULL
};

int DevicesVM_Init()
{
	int i;

//	for(i=0; *inits[i]; i++)inits[i]();
	Condev_Init();
	FDC_Init();
	ATA_Init();
//	Gfxdev_Init();
//	Imagedev_Init();
	Serial_Init();
//	Mouse_Init();

	return(0);
}
