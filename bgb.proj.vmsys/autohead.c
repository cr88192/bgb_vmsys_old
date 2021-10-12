#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int symchar(int c)
{
	if((c>='a') && (c<='z'))return(1);
	if((c>='A') && (c<='Z'))return(1);
	if((c>='0') && (c<='9'))return(1);
	if(c=='_')return(1);
	return(0);
}

int main(int argc, char *argv[])
{
	int i, l;
	FILE *fd;
	char buf[256];
	char *s;

	for(i=1; i<argc; i++)
	{
		fd=fopen(argv[i], "rt");
		printf("//%s\r\n", argv[i]);
		l=0;
		while(!feof(fd))
		{
			memset(buf, 0, 256);
			fgets(buf, 255, fd);
			l++;

			s=buf;
			while(*s && (*s!='\n'))s++;
			if(*s=='\n')*s=0;
			s=buf;

			if(!strncmp(s, "//AH:", 5))
			{
				fprintf(stderr, "//AH tag %s %d\n",
					argv[i], l);
				s+=5;
				while(*s && (*s<=' '))s++;
				if(!strcmp(s, "skip"))break;
			}

			if(*s<=' ')continue;
			while(symchar(*s))s++;
			while(*s && (*s<=' '))s++;
			if(!*s || (*s=='('))continue;
			if(*s=='*')s++;
			while(*s && symchar(*s))s++;
			if(*s=='(')
			{
				while(*s && (*s!='/'))s++;
				if(!strncmp(s, "//AH:", 5))
				{
					fprintf(stderr, "//AH tag %s %d\n",
						argv[i], l);
					s+=5;
					while(*s && (*s<=' '))s++;
					if(!strcmp(s, "ignore"))continue;
				}
				printf("%s;\r\n", buf);
			}
		}
		fclose(fd);
	}
	return(0);
}
