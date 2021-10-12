#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int total, file, i;
	FILE *fd;
	char buf[1024];

	total=0;
	for(i=1; i<argc; i++)
	{
		file=0;
		fd=fopen(argv[i], "rt");
		if(!fd)continue;
		while(fgets(buf, 1023, fd))file++;
		fclose(fd);
		printf("%s %d\n", argv[i], file);
		total+=file;
	}
	printf("total %d\n", total);
}
