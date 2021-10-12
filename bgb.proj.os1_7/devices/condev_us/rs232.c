#include <general.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>

int ser_char;

int serial_write(void *buf, int len, VFILE *fd)
{
	fwrite(buf, 1, len, fd->buffer);
//	write(*(int *)fd->buffer, buf, len);
	return(len);
}

int serial_read(void *buf, int len, VFILE *fd)
{
	int i;
//	fread(buf, 1, len, fd->buffer);
//	read(*(int *)fd->buffer, buf, len);

	i=0;
	if(ser_char>=0)
	{
		*(char *)buf=ser_char;
		ser_char=-1;
		buf++;
		len--;
		i++;
	}
	if(len>0)i+=fread(buf, 1, len, fd->buffer);
	return(i);

//	return(len);
}

int serial_inready(VFILE *fd)
{
	int i;

	if(ser_char>=0)return(1);
	i=fread(&ser_char, 1, 1, fd->buffer);
	if(i)return(1);

	ser_char=-1;
	return(0);

#if 0
	int fhnd, stat;
	fd_set rfds;
	struct timeval tv;

	fhnd=*(int *)fd->buffer;

	FD_ZERO(&rfds);
	FD_SET(fhnd, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;

	stat=select(1, &rfds, NULL, NULL, &tv);

//	stat=1;
	if(stat)return(-1);


//	if(kbhit())return(1);
//	if(!con_inbuf)con_inbuf=Sys_ReadLine();
//	if(con_inbuf)return(-1);
	return(0);
#endif
}

VFILE *Sys_Popen2(char *command);

VFILE *serial_open(char *name, void *data)
{
	VFILE *tmp;

	return(NULL);

//	tmp=Sys_Popen2("pppd passive notty");
//	if(!tmp)
//	{
//		kprint("serial_open: popen2 failed.\n");
//	}
//	return(tmp);

	tmp=vfnew();
	tmp->buffer=data;

	tmp->write_proc=serial_write;
	tmp->read_proc=serial_read;
	tmp->inready_proc=serial_inready;

	return(tmp);
}

int Serial_Init()
{
//	static int hnds[4];
	FILE *fd;

//	fd=fopen("/dev/ttyS1", "r+b");
	Driver_RegisterStream("serial/0", &serial_open, fd);

//	return(0);

//	hnds[0]=open("/dev/ttyS0", O_RDWR);
//	hnds[1]=open("/dev/ttyS1", O_RDWR);
//	hnds[2]=open("/dev/ttyS2", O_RDWR);
//	hnds[3]=open("/dev/ttyS3", O_RDWR);

//	if(hnds[0]>0)Driver_RegisterStream("serial/0", &serial_open, &hnds[0]);
//	if(hnds[1]>0)Driver_RegisterStream("serial/1", &serial_open, &hnds[1]);
//	if(hnds[2]>0)Driver_RegisterStream("serial/2", &serial_open, &hnds[2]);
//	if(hnds[3]>0)Driver_RegisterStream("serial/3", &serial_open, &hnds[3]);
}
