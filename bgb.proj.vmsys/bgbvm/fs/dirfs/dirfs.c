#include <general.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

/* FILE */

static int file_read_proc(void *buf, int len, VFILE *fd)
{
	return(fread(buf, 1, len, fd->buffer));
}

static int file_write_proc(void *buf, int len, VFILE *fd)
{
	return(fwrite(buf, 1, len, fd->buffer));
}

static int file_seek_proc(VFILE *fd, int pos, int rel)
{
	return(fseek(fd->buffer, pos, rel));
}

static int file_tell_proc(VFILE *fd)
{
	return(ftell((FILE *)fd->buffer));
}

static int file_close_proc(VFILE *fd)
{
	fclose((FILE *)fd->buffer);
	kfree(fd);
	return(0);
}

static int file_eof_proc(VFILE *fd)
{
	return(feof((FILE *)fd->buffer));
}

static int file_flush_proc(VFILE *fd)
{
	return(fflush((FILE *)fd->buffer));
}

VFILE *vf_wrap_file(FILE *fd)
{
	VFILE *tmp;

//	tmp=malloc(sizeof(VFILE));
//	memset(tmp, 0, sizeof(VFILE));
	tmp=vfnew();

	tmp->read_proc=&file_read_proc;
	tmp->write_proc=&file_write_proc;
	tmp->seek_proc=&file_seek_proc;
	tmp->tell_proc=&file_tell_proc;
	tmp->close_proc=&file_close_proc;
	tmp->eof_proc=&file_eof_proc;
	tmp->flush_proc=&file_flush_proc;
	tmp->buffer=fd;
	return(tmp);
}

#if 0
VFILE *vffopen(char *name, char *access)
{
	FILE *fd;
	VFILE *vfd;

	fd=fopen(name, access);
	if(!fd)return(NULL);
	vfd=vf_wrap_file(fd);
	return(vfd);
}
#endif

/* system directories */

VFILE *vdd_open(char *name, char *fl, VMOUNT *dir)
{
	char tname[256], i;
	FILE *fd;
	VFILE *vfd;

	if(!*name)return(NULL);

	strcpy(tname, dir->data);
	i=strlen(tname);
//	strcat(tname, "/");
	strcat(tname, name);
//	for(;tname[i];i++)if(tname[i]=='/')tname[i]=CONF_PATHSEP;

	kprint("dir: attempt open %s\n", tname);

	fd=fopen(tname, fl);
	if(!fd)
	{
		kprint("dirfs: can't open %s\n", tname);
		return(NULL);
	}
	vfd=vf_wrap_file(fd);

	return(vfd);
}

#if 1
int vdd_d_readdir(long *buf, char **fields, long *key, VDIR *dir)
{
	struct dirent *de;

	de=readdir(dir->data);
	if(!de)return(0);

	buf[0]=kstrdup(de->d_name);
	fields[0]="$name";
	fields[1]=NULL;

	*key=1;

	return(1);
}
#endif

int vdd_d_close(VDIR *dir)
{
	closedir(dir->data);
	kfree(dir);
}

VDIR *vdd_opendir(char *name, VMOUNT *dir)
{
	char tname[256], i;
	VFILE *vfd;
	DIR *pth;
	VDIR *tmp;

//	return(NULL);

	strcpy(tname, dir->data);
	i=strlen(tname);
//	strcat(tname, "/");
	strcat(tname, name);
//	for(;tname[i];i++)if(tname[i]=='/')tname[i]=CONF_PATHSEP;

	kprint("dirfs: attempt open dir %s\n", tname);

	pth=opendir(tname);
	if(!pth)
	{
		printf("dirfs: can't open dir %s\n", tname);
		return(NULL);
	}
	tmp=kalloc(sizeof(VDIR));
	tmp->data=pth;
	tmp->readdir=&vdd_d_readdir;
	tmp->close=&vdd_d_close;

	return(tmp);
}

#if 0
VMOUNT *vdd_open_dir(char *name)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));
	tmp->data=kalloc(strlen(name)+1);
	strcpy(tmp->data, name);
	tmp->openf=&vdd_open;
	tmp->opend=&vdd_opendir;
	return(tmp);
}
#endif

VMOUNT *dirfs_mount(char **options)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));

	tmp->data=kalloc(strlen(options[0])+1);
	strcpy(tmp->data, options[0]);

	tmp->unmount=&kfree;
	tmp->openf=&vdd_open;
	tmp->opend=&vdd_opendir;
	return(tmp);
}

int dirfs_init()
{
	Vfs_RegisterType("dirfs", &dirfs_mount);
	return(0);
}
