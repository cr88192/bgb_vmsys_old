#include <stdio.h>
#include <dirent.h>

DIR *opendir(char *path)
{
	DIR *tmp;
	int fd;

	fd=kopendir(path);
	if(fd<0)return(NULL);

	tmp=malloc(sizeof(DIR));
	tmp->fd=fd;
	tmp->key=0;
	tmp->eod=0;

	return(tmp);
}

int closedir(DIR *dir)
{
	kclosedir(dir->fd);
	free(dir);
}

off_t telldir(DIR *dir)
{
	return(dir->key);
}

struct dirent *readdir(DIR *dir)
{
	char *names[16];
	char *types[16];
	void *values[16];
	void *buf;
	int i;

	if(dir->eod)return(NULL);

	buf=malloc(4096);
	i=krreaddir(dir->fd, &dir->key,
		16, types, names, values,
		4096, buf);

	if(i!=1)
	{
		dir->eod=1;
		free(buf);
		return(NULL);
	}

	strcpy(dir->de.d_name, values[0]);
	free(buf);

	return(&dir->de);
}

int seekdir(DIR *dir, off_t offs)
{
	dir->key=offs;
	dir->eod=0;
	return(0);
}

int rewinddir(DIR *dir)
{
	dir->key=0;
	dir->eod=0;
	return(0);
}

static void *rreaddir_dup(void *o, char *ty)
{
	void *p;

	if(!o)return(NULL);
	if(!strcmp(ty, "int_t"))
	{
		p=malloc(sizeof(int));
		*(int *)p=*(int *)o;
		return(p);
	}
	if(!strcmp(ty, "bool_t"))
	{
		p=malloc(sizeof(int));
		*(int *)p=*(int *)o;
		return(p);
	}
	if(!strcmp(ty, "string_t"))
	{
		p=strdup(o);
		return(p);
	}
	return(NULL);
}

int rreaddir(DIR *dir, int cnt, char **types, char **names, void **values)
{
	void *buf;
	int i;

	if(dir->eod)return(NULL);

	buf=malloc(4096);
	i=krreaddir(dir->fd, &dir->key,
		cnt, types, names, values,
		4096, buf);

	if(i!=1)
	{
		dir->eod=1;
		free(buf);
		return(-1);
	}

	for(i=0; names[i] && (i<cnt); i++)
	{
		types[i]=strdup(types[i]);
		names[i]=strdup(names[i]);
		values[i]=rreaddir_dup(values[i], types[i]);
	}
	free(buf);

	return(0);
}
