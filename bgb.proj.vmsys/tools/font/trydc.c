#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fd;
	int i, j, k;

	fd=fopen(argv[1], "rb");
	i=0;

	while(1)
	{
		j=fgetc(fd);
		if(j<0)break;
		if(j==0x7f)
		{
			k=fgetc(fd);
			fgetc(fd);
			i+=k;
			continue;
		}else if(j==0x7e)
		{
			k=fgetc(fd);
			k+=fgetc(fd)<<8;
			fgetc(fd);
			i+=k;
		}
		i++;
	}
	printf("%d\n", i);
}
