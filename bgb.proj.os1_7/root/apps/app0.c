#include <stdio.h>

char *con_gets(char *s, int n)
{
	char *is;
	int c;
	c=-1;

	is=s;

	while(c!='\n')
	{
		while(!finready(stdin));
		c=fgetc(stdin);
		if(c<0)return(NULL);

//		fputc(c, stdout);

		if(c==0x08)
		{
			if(s>is)
			{
				fputc(c, stdout);
				s--;
			}
		}else
		{
			fputc(c, stdout);
			*s++=c;
		}
		*s=0;

		if((s-is)>=n)return(is);
	}

	return(is);
}

int main(int argc, char **argv, char **env)
{
	char buf[256], buf2[64], *tb[16];
	char *s, *t;
	int i, j;
//	syscall(SYSCALL_PRINT, "this is a test\n");
//	syscall(SYSCALL_PRINT, "this is another test\n");
	printf("BGB Shell App\n");
//	printf("print str %s\n", "{test}");
//	printf("print num %d\n", 1234);
//	printf("print %s %s %s\n", "{test}", "{test2}", "{test3}");

	printf("Called as %s with %d arg(s)\n", argv[0], argc);
	printf("\tArgs:");
	for(i=0; argv[i]; i++)
		printf(" '%s'", argv[i]);
	printf("\n");
	printf("\tEnv:");
	for(i=0; env[i]; i++)
		printf(" '%s'", env[i]);
	printf("\n");

	while(1)
	{
		printf("$ ");
		con_gets(buf, 255);

		s=buf;
		i=0;
		while(*s)
		{
			while(*s && (*s<=' '))s++;
			if(!*s)continue;

			t=buf2;
			while(*s && (*s>' '))*t++=*s++;
			*t++=0;
			tb[i++]=strdup(buf2);
		}
		tb[i]=NULL;
		if(!i)continue;

		printf("cmd '%s'", tb[0]);
		for(j=1; j<i; j++)printf(" '%s'", tb[j]);
		printf("\n");

		execute(tb[0], tb, env);
//		while(!finready(stdin));
//		while(finready(stdin))fgetc(stdin);
	}
}
