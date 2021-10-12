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

int WriteInt32(FILE *f, int v)
{
	fputc(v&0xff, f);
	fputc((v>>8)&0xff, f);
	fputc((v>>16)&0xff, f);
	fputc((v>>24)&0xff, f);
}

int main(int argc, char *argv[])
{
	FILE *infd, *outfd;

	infd=fopen(argv[1], "rb");
	outfd=fopen(argv[2], "wb");
	LoadTGA(infd);
	WriteInt32(outfd, targa_header.width);
	WriteInt32(outfd, targa_header.height);
	fwrite("P32\0", 1, 4, outfd);
	fwrite(targa_rgba, 4, targa_header.width*targa_header.height, outfd);
}