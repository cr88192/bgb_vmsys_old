#include <general.h>

VFILE *fdc_open(char *name, void *data)
{
	VFILE *tmp;
//	tmp=vffopen_us("/dev/fd0", "r+b");
	return(tmp);
}

int FDC_Init()
{
//	Driver_RegisterStream("floppy", &fdc_open, NULL);
}

VFILE *hdfd;

VFILE *ata_open(char *name, void *data)
{
	return(hdfd);
}

int ATA_Init()
{
//	Driver_RegisterStream("ata/0", &ata_open, NULL);

//	hdfd=vffopen_us("hdimg", "r+b");
//	PartMS_ProcessDev(hdfd, "ata/0", 1);
}
