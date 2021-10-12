#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <os1/gui.h>

typedef struct TargaHeader_s {
	unsigned char 	id_length, ctype, itype;
	unsigned short	cindex, clength;
	unsigned char	csize;
	unsigned short	x_origin, y_origin, width, height;
	unsigned char	bpp, attributes;
} TargaHeader;

int gui_con;

int GuiCl_WaitInteger()
{
	int class, size;
	void *buf;
	int i;

	buf=malloc(256);
	while(1)
	{
		size=256;
		i=msg_get_message(gui_con, &class, &size, buf);
		if((i==-1) && size) //oversized
		{
			msg_get_message(gui_con, &class, &size, NULL);
			usleep(100);
			continue;
		}
		if(i==-1) //no message
		{
			usleep(100);
			continue;
		}

		switch(class)
		{
		case GUI_INTEGER:
			i=(int)(*(long *)buf);
			free(buf);
			return(i);
			break;
		default:
			free(buf);
			return(-1);
			break;
		}
	}
	return(-1);
}

int GuiCl_NewSurface(int x, int y)
{
	long lb[2];

	lb[0]=x;
	lb[1]=y;
	msg_send_message(gui_con, GUI_NEWSURF, 2*sizeof(long), lb);

	msg_send_message(gui_con, GUI_POPRET, 0, NULL);
	return(GuiCl_WaitInteger());
}

int GuiCl_SetSurface(int num, int x, int y, int w, int h)
{
	long lb[5];

	lb[0]=num;
	lb[1]=x;
	lb[2]=y;
	lb[3]=w;
	lb[4]=h;
	msg_send_message(gui_con, GUI_SETSURFSZ, 5*sizeof(long), lb);

	return(0);
}

int GuiCl_ShowSurface(int id)
{
	long lb[2];

	lb[0]=id;
	lb[1]=0;
	msg_send_message(gui_con, GUI_SHOWSURF, 1*sizeof(long), lb);

	return(0);
}

int GuiCl_SendData(int sz, void *buf)
{
	msg_send_message(gui_con, GUI_DATA, sz, buf);
	return(0);
}

int GuiCl_FillSurface(int id, void *buf, int sz)
{
	long lb[2];

	msg_send_message(gui_con, GUI_DATA, sz, buf);

	lb[0]=id;
	lb[1]=0;
	msg_send_message(gui_con, GUI_FILLSURF, 1*sizeof(long), lb);

	return(0);
}

unsigned char *Img_ReadTGA(FILE *fd, int *w, int *h)
{
	TargaHeader head;
	int pixlin, i;
	unsigned char *dest, *src, *buf, *obuf, r, g, b, a;

	head.id_length=fgetc(fd);
	head.ctype=fgetc(fd);
	head.itype=fgetc(fd);
	head.cindex=fgetc(fd)+(fgetc(fd)<<8);
	head.clength=fgetc(fd)+(fgetc(fd)<<8);
	head.csize=fgetc(fd);
	head.x_origin=fgetc(fd)+(fgetc(fd)<<8);
	head.y_origin=fgetc(fd)+(fgetc(fd)<<8);
	head.width=fgetc(fd)+(fgetc(fd)<<8);
	head.height=fgetc(fd)+(fgetc(fd)<<8);
	head.bpp=fgetc(fd);
	head.attributes=fgetc(fd);

	if((head.itype!=2) || ((head.bpp!=32) && (head.bpp!=24)) || (head.ctype!=0))
	{
		printf("Img_LoadTGA: only RGB(24)/RGBA(32) uncompressed images supported.\n");
		printf("   bpp: %d, type: %d\n", head.bpp, head.ctype);
		return(NULL);
	}

	fseek(fd, head.id_length, 1); /* skip comment */

	pixlin=head.width*head.height;
	obuf=malloc(pixlin*4);
	dest=obuf;

	buf=malloc(pixlin*(head.bpp>>3));
	fread(buf, 1, pixlin*(head.bpp>>3), fd);
	src=buf;

	for(i=0; i<pixlin; i++)
	{
		b=*src++;
		g=*src++;
		r=*src++;
		if(head.bpp==32)
			a=*src++;
			else a=255;
		*dest++=r;
		*dest++=g;
		*dest++=b;
		*dest++=a;
	}
	free(buf);

	if(!(head.attributes&32))
	{
		dest=malloc(pixlin*4);
		for(i=0; i<head.height; i++)
			memcpy(&dest[i*head.width*4], &obuf[(head.height-(i+1))*head.width*4], head.width*4);
		memcpy(obuf, dest, pixlin*4);
		free(dest);
	}

	*w=head.width;
	*h=head.height;
	return(obuf);
}

int Img_WriteTGA(FILE *fd, unsigned char *buf, int w, int h)
{
	TargaHeader head;
	int i;
	unsigned char *s;

	head.id_length=0;
	head.ctype=0;
	head.itype=2;
	head.cindex=0;
	head.clength=0;
	head.csize=0;
	head.x_origin=0;
	head.y_origin=0;
	head.width=w;
	head.height=h;
	head.bpp=24;
	head.attributes=0;

	fputc(head.id_length, fd);
	fputc(head.ctype, fd);
	fputc(head.itype, fd);

	fputc(head.cindex, fd);
	fputc(head.cindex>>8, fd);
	fputc(head.clength, fd);
	fputc(head.clength>>8, fd);

	fputc(head.csize, fd);

	fputc(head.x_origin, fd);
	fputc(head.x_origin>>8, fd);
	fputc(head.y_origin, fd);
	fputc(head.y_origin>>8, fd);

	fputc(head.width, fd);
	fputc(head.width>>8, fd);
	fputc(head.height, fd);
	fputc(head.height>>8, fd);

	fputc(head.bpp, fd);
	fputc(head.attributes, fd);

//	vfwrite(buf, w*4, h, fd);

	s=buf;
	for(i=0; i<w*h; i++)
	{
		fputc(s[2], fd);
		fputc(s[1], fd);
		fputc(s[0], fd);
		s+=4;
	}

	return(0);
}

unsigned char *Img_LoadTGA(char *name, int *w, int *h)
{
	FILE *fd;

	fd=fopen(name, "rb");
	return(Img_ReadTGA(fd, w, h));
}

int GuiCl_HandleEvents()
{
	int class, size, max;
	int i, j;
	void *buf, *buf2;

	buf=malloc(256);
	max=256;

	while(1)
	{
		size=max;

		j=msg_get_message(gui_con, &class, &size, buf);
		if((j==-1) && (size<=0))break;
		if((j==-1) && (size>0))
		{
			free(buf);
			buf=malloc(size);
			max=size;
			j=msg_get_message(gui_con, &class, &size, buf);
		}
		switch(class)
		{
		default:
			break;
		}
	}
	free(buf);
}

int main(int argc, char *argv[], char *env[])
{
	char buf[64];
	int dom, pid, cid;
	int i, j;
	char *ib;
	int xs, ys;

	printf("gapp started.\n");

	kvar_get(GUI_SVKEY, buf);
	printf("gui string '%s'\n", buf);

	dom=-1;
	pid=-1;
	cid=-1;
	sscanf(buf, "%d:%d:%d", &dom, &pid, &cid);
	printf("gui addr %d:%d:%d\n", dom, pid, cid);

	gui_con=msg_connect(dom, pid, cid);
	if(gui_con<0)printf("connect failed\n");

	ib=Img_LoadTGA("logo0.tga", &xs, &ys);

	i=GuiCl_NewSurface(xs, ys);
	GuiCl_SetSurface(i, 320-128, 240-128, 256, 256);
	GuiCl_ShowSurface(i);

#if 0
	ib=malloc(xs*ys*4);
	for(j=0; j<64*64; j++)
	{
		ib[(j*4)+0]=0;
		ib[(j*4)+1]=255;
		ib[(j*4)+2]=0;
		ib[(j*4)+3]=255;
	}
	for(j=0; j<64; j++)
	{
		ib[(((j*64)+j)*4)+0]=255;
		ib[(((j*64)+j)*4)+1]=0;
		ib[(((j*64)+j)*4)+2]=0;
		ib[(((j*64)+j)*4)+3]=255;
	}
#endif
	GuiCl_FillSurface(i, ib, xs*ys*4);

	while(1)
	{
	}

	return(0);
}
