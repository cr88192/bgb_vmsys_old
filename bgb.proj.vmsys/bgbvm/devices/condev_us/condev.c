#include <general.h>
#include <graphics/render.h>

#include <stdio.h>

#include <sys/types.h>

static char *con_inbuf=NULL;
static char con_char=-1;

//int con_keyb_hnd=0;

//extern displaywindow *gfx_screen;

int (*condev_printhook)(char *s);

int Condev_SetPrintHook(int (*hook)(char *s))
{
	condev_printhook=hook;
	return(0);
}

int condev_write(void *buf, int len, VFILE *fd)
{
	fwrite(buf, 1, len, stdout);
	fflush(stdout);

	if(condev_printhook)condev_printhook(buf);
//	UICon_Print(buf);

//	Con_Printf("%s", buf);
	return(len);
}

int condev_read(void *buf, int len, VFILE *fd)
{
	int i;
/*	if(!con_inbuf)con_inbuf=Sys_ReadLine();
	if(con_inbuf)
	{
		for(i=0; (i<len) && *con_inbuf; i++)
			*(char *)buf++=*con_inbuf++;

		if(!*con_inbuf)con_inbuf=Sys_ReadLine();
		return(i);
	} */

	i=0;
	if(con_char>=0)
	{
		*(char *)buf=con_char;
		con_char=-1;
		buf++;
		len--;
		i++;
	}
	if(len>0)i+=fread(buf, 1, len, stdin);
	return(i);
}

int Text_WriteString(char *s)
{
	printf(s);
	if(condev_printhook)condev_printhook(s);
//	UICon_Print(s);
//	Con_Printf("%s", s);
}

int condev_inready(VFILE *fd)
{
	int i;

	if(con_char>=0)return(1);
	i=fread(&con_char, 1, 1, stdin);
	if(i)return(1);

	con_char=-1;
	return(0);

#if 0
	int fhnd, stat;
	fd_set rfds;
	struct timeval tv;

	fhnd=0;

	FD_ZERO(&rfds);
	FD_SET(fhnd, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;

	stat=select(1, &rfds, NULL, NULL, &tv);

	stat=1;
	if(stat)return(-1);


//	if(kbhit())return(1);
//	if(!con_inbuf)con_inbuf=Sys_ReadLine();
//	if(con_inbuf)return(-1);
	return(0);
#endif
}

VFILE *condev_open(char *name, void *data)
{
	VFILE *tmp;
	tmp=vfnew();
	tmp->write_proc=condev_write;
	tmp->read_proc=condev_read;
	tmp->inready_proc=condev_inready;
	return(tmp);
}

int Condev_Init()
{
	Driver_RegisterStream("console", &condev_open, NULL);

	condev_printhook=NULL;
}
