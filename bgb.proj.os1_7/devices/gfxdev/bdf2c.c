#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *in, *out;
	char buf[256];
	int i, j;

	in=fopen(argv[1], "rt");
	out=fopen(argv[2], "wt");

	i=0;
	j=0x20;
	fprintf(out, "unsigned char %s[]={\n", argv[3]);
	while(!feof(in))
	{
		fgets(buf, 255, in);

		if(strlen(buf)==3)
		{
			if(i && (i!=8))fprintf(out, ", ");
			buf[2]=0;
			fprintf(out, "0x%s", buf);
			i++;
			if(i==8)
			{
				fprintf(out, ",\n");
			}
			if(i==16)
			{
				fprintf(out, ", /* 0x%02X */\n\n", j);
				i=0;
				j++;
			}
		}
	}
	fprintf(out, "};\n");
}
