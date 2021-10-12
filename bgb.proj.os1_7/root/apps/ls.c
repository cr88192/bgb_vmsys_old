#include <dirent.h>

int main(int argc, char **argv, char **env)
{
	DIR *dir;
	struct dirent *de;

	dir=opendir(argv[1]);
	if(!dir)
	{
		printf("%s: bad path '%s'\n", argv[0], argv[1]);
		return(-1);
	}
	while(1)
	{
		de=readdir(dir);
		if(!de)break;

		printf("%s\n", de->d_name);
	}
	closedir(dir);
	return(0);
}
