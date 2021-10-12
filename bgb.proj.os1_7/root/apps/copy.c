#include <stdio.h>

int main(int argc, char *argv[], char *env)
{
	FILE *ifd;
	FILE *ofd;
	char *buf;
	int i;

	ifd=fopen(argv[1], "rb");
	ofd=fopen(argv[2], "wb");

	printf("copy '%s'->'%s'\n", argv[1], argv[2]);

	i=fseek(ifd, 0, 2);
	fseek(ifd, 0, 0);
	buf=malloc(i);

	printf("file is %d bytes\n", i);

	fread(buf, 1, i, ifd);
	fwrite(buf, 1, i, ofd);

	fclose(ifd);
	fclose(ofd);

	return(0);
}
