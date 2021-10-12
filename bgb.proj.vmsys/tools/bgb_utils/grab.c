#include <math.h>

typedef unsigned char byte;

byte *buffer_in;
byte *buffer_out;

#if 1 //old algo, ok, distorts

void grab_up()
{
	int i, j;
	int x1, y1, x2, y2;
	for(i=0;i<256;i++)for(j=0;j<256;j++)
	{
		x1=j+256;
		y1=i+256;
		x2=j;
		y2=i;
		buffer_out[((y2*256)+x2)*4+0]=buffer_in[((y1*768)+x1)*4+0];
		buffer_out[((y2*256)+x2)*4+1]=buffer_in[((y1*768)+x1)*4+1];
		buffer_out[((y2*256)+x2)*4+2]=buffer_in[((y1*768)+x1)*4+2];
	}
}

void grab_rt()
{
	int i, j;
	int x1, y1;
	int width, offs;
	float scale;
	int dc;

	dc=0;
	for(i=0;i<256;i++)for(j=0;j<256;j++)
	{
		width=768-(2*i);
		scale=(width-dc)/256.0;
		offs=i;

		x1=(j*scale)+offs;
		y1=i;

		buffer_out[((i*256)+j)*4+0]=buffer_in[((y1*768)+x1)*4+0];
		buffer_out[((i*256)+j)*4+1]=buffer_in[((y1*768)+x1)*4+1];
		buffer_out[((i*256)+j)*4+2]=buffer_in[((y1*768)+x1)*4+2];
	}
}

void grab_lf()
{
	int i, j;
	int x1, y1;

	int width, offs;
	float scale;
	int dc;

	dc=0;
	for(i=0;i<256;i++)for(j=0;j<256;j++)
	{
		width=768-(2*i);
		scale=(width-dc)/256.0;
		offs=i;

		x1=(j*scale)+offs;
		x1=767-x1;
		y1=767-i;

		buffer_out[((i*256)+j)*4+0]=buffer_in[((y1*768)+x1)*4+0];
		buffer_out[((i*256)+j)*4+1]=buffer_in[((y1*768)+x1)*4+1];
		buffer_out[((i*256)+j)*4+2]=buffer_in[((y1*768)+x1)*4+2];
	}
}

void grab_ft()
{
	int i, j;
	int x1, y1;
	int width, offs;
	float scale;
	int dc;

	dc=0;
	for(i=0;i<256;i++)for(j=0;j<256;j++)
	{
		width=768-(2*i);
		scale=(width-dc)/256.0;
		offs=i;

		x1=767-i;
		y1=(j*scale)+offs;

		buffer_out[((i*256)+j)*4+0]=buffer_in[((y1*768)+x1)*4+0];
		buffer_out[((i*256)+j)*4+1]=buffer_in[((y1*768)+x1)*4+1];
		buffer_out[((i*256)+j)*4+2]=buffer_in[((y1*768)+x1)*4+2];
	}
}

void grab_bk()
{
	int i, j;
	int x1, y1;
	int width, offs;
	float scale;
	int dc;

	dc=0;
	for(i=0;i<256;i++)for(j=0;j<256;j++)
	{
		width=768-(2*i);
		scale=(width-dc)/256.0;
		offs=i;

		x1=i;
		y1=(j*scale)+offs;
		y1=767-y1;

		buffer_out[((i*256)+j)*4+0]=buffer_in[((y1*768)+x1)*4+0];
		buffer_out[((i*256)+j)*4+1]=buffer_in[((y1*768)+x1)*4+1];
		buffer_out[((i*256)+j)*4+2]=buffer_in[((y1*768)+x1)*4+2];
	}
}

#endif
