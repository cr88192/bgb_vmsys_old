#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

byte *buffer_in;
byte *buffer_out;

int Error(char *s, ...)
{
	va_list lst;
	va_start(lst, s);
	vprintf(s, lst);
	va_end(lst);

	exit(0);
}

void grab_up();
void grab_ft();
void grab_bk();
void grab_lf();
void grab_rt();

int main(int argc, char *argv[])
{
	FILE *f;
	char name[64];

	if(argc<2)Error("usage: skytool <targa_src_path+base>\n");
	sprintf(name, "%s.tga", argv[1]);
	f=fopen(name, "rb");
	if(!f)Error("can't open %s\n", name);
	LoadTGA(f);
	if(targa_header.width!=768)Error("input image needs to be 768x768x24\n");
	if(targa_header.height!=768)Error("input image needs to be 768x768x24\n");
	buffer_in=targa_rgba;
	buffer_out=malloc(256*256*4);
	targa_rgba=buffer_out;
	targa_header.width=256;
	targa_header.height=256;

	grab_up();
	sprintf(name, "%sup.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);

	memset(buffer_out, 0, 256*256*4);
	grab_ft();
	sprintf(name, "%sft.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);

	memset(buffer_out, 0, 256*256*4);
	grab_bk();
	sprintf(name, "%sbk.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);

	memset(buffer_out, 0, 256*256*4);
	grab_lf();
	sprintf(name, "%slf.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);

	memset(buffer_out, 0, 256*256*4);
	grab_rt();
	sprintf(name, "%srt.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);

	memset(buffer_out, 0, 256*256*4);
	sprintf(name, "%sdn.tga", argv[1]);
	f=fopen(name, "wb");
	if(!f)Error("can't open %s\n", name);
	StoreTGA(f,0);
}
