#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *inf,*outf;
	int port,reg,value,c;
	inf=fopen(argv[1],"rb");
	outf=fopen(argv[2],"wt");
//	fprintf(outf,"#include <os1/kernel/gfx_disp/twkuser.h>\n\n");
	fprintf(outf,"/* this file was auto generated */\n\n");
	fprintf(outf,
	"struct {\n"
	"unsigned short port;\n"
	"unsigned char reg;\n"
	"unsigned char value;\n} %s[] =\n{\n",argv[3]);
	c=0;
	while(!feof(inf))
	{
		if(c)fprintf(outf,",\n");
		c=1;
		port=fgetc(inf);
		if(port!=EOF)
		{
			port+=fgetc(inf)<<8;
			reg=getc(inf);
			value=getc(inf);
		}
		else
		{
			port=0;
			reg=0;
			value=0;
		}
		fprintf(outf,"\t{0x%04X,0x%02X,0x%02X}",port,reg,value);
	}
	fprintf(outf,"\n};\n");
}