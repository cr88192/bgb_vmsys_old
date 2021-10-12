#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned char byte;

typedef struct _TargaHeader {
	unsigned char 	id_length, colormap_type, image_type;
	unsigned short	colormap_index, colormap_length;
	unsigned char	colormap_size;
	unsigned short	x_origin, y_origin, width, height;
	unsigned char	pixel_size, attributes;
} TargaHeader;


TargaHeader		targa_header;
byte			*targa_rgba;

void LoadTGA (FILE *fin);
void StoreTGA (FILE *fout, int al);

int Error(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);

	exit(0);
}

int main(int argc, char *argv[])
{
	byte *buf, *buf2;
	byte pal[768];
	FILE *fd;
	int xs, ys, nh, i, j;

	fd=fopen("palette.lmp", "rb");
	if(!fd)Error("can't open palette\n");
	fread(&pal, 1, 768, fd);
	fclose(fd);

	for(i=0;i<768;i++)
	{
		j=pal[i]+96;
		if(j>255)j=255;
		pal[i]=j;
	}
	nh=255;

	fd=fopen(argv[1], "rb");
	if(!fd)Error("can't open in\n");
	if(argc==5)
	{
		xs=atoi(argv[3]);
		ys=atoi(argv[4]);
		nh=0;
	}else
	{
		fread(&xs, 1, 4, fd);
		fread(&ys, 1, 4, fd);
		if(xs<0)Error("invalid x size %d\n", xs);
		if(xs>1024)Error("invalid x size %d\n", xs);
		if(ys<0)Error("invalid y size %d\n", ys);
		if(ys>1024)Error("invalid y size %d\n", ys);
	}

	printf("%d %d %d\n", argc, xs, ys);
	buf=malloc(xs*ys);
	buf2=malloc(xs*ys*4);

	fread(buf, xs, ys, fd);
	fclose(fd);
	for(i=0; i<xs*ys; i++)
	{
		buf2[i*4]=pal[buf[i]*3];
		buf2[i*4+1]=pal[buf[i]*3+1];
		buf2[i*4+2]=pal[buf[i]*3+2];
		buf2[i*4+3]=(buf[i]==nh)?0:255;
	}
	free(buf);
	buf=malloc(xs*ys*4);
	for(i=0;i<ys;i++)
		memcpy(buf+(i*xs*4), buf2+((ys-i-1)*xs*4), xs*4);

	fd=fopen(argv[2], "wb");
	if(!fd)Error("can't open out\n");

	targa_rgba=buf;
	targa_header.width=xs;
	targa_header.height=ys;

	StoreTGA(fd, 1);
}