#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *in;
	int s, e, i, j;
	char buf[256];
	int w, h;

	j=0;
	in=fopen(argv[1], "rb");
	while(1)
	{
		s=fgetc(in);
		s+=fgetc(in)<<8;

		e=fgetc(in);
		e+=fgetc(in)<<8;

		if(s==0xBF00)
		{
			fread(buf, 1, e, in);
			w=buf[1];
			h=buf[2];
			printf("head %dx%d\n", w, h);
			continue;
		}

		if(!s && !e)break;

		printf("chunk %d-%d\n", s, e);
		for(i=0; i<((e-s)+1); i++)fread(buf, 1, ((w*h)/8), in);
		j+=(e-s)+1;
	}
	printf("total %d\n", j);
}
