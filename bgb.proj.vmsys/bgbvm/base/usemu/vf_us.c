#include <general.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

/* FILE */

static int file_read_proc(void *buf, int len, VFILE *fd)
{
//	return(fread(buf, 1, len, fd->buffer));
	return(read(*(int *)fd->buffer, buf, len));
}

static int file_write_proc(void *buf, int len, VFILE *fd)
{
//	return(fwrite(buf, 1, len, fd->buffer));
	return(write(*(int *)fd->buffer, buf, len));
}

static int file_seek_proc(VFILE *fd, int pos, int rel)
{
//	return(fseek(fd->buffer, pos, rel));
	return(lseek(*(int *)fd->buffer, pos, rel));
}

static int file_tell_proc(VFILE *fd)
{
//	return(ftell(fd->buffer));
	return(lseek(*(int *)fd->buffer, 0, 1));
}

static int file_close_proc(VFILE *fd)
{
//	fclose(fd->buffer);
	close(*(int *)fd->buffer);
	free(fd);
	return(0);
}

static int file_eof_proc(VFILE *fd)
{
	char b, c;
	c=read(*(int *)fd->buffer, &b, 1);
	if(!c)return(-1);
	lseek(*(int *)fd->buffer, -1, 1);
	return(0);
}

static int file_flush_proc(VFILE *fd)
{
//	return(fflush(fd->buffer));
	return(fsync(*(int *)fd->buffer));
}

static void *file_mmap_proc(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	void *tmp;
//	return(fflush(fd->buffer));

	prot=PROT_READ|PROT_WRITE|PROT_EXEC;
	flags=MAP_SHARED;

//	kprint("%X %d %d\n", addr, length, offs);

	tmp=mmap(addr, length, prot, flags, *(int *)fd->buffer, offs);
	if(tmp==(void *)(-1))
	{
		perror(NULL);
		tmp=NULL;
	}
	return(tmp);
}

static int file_munmap_proc(void *addr, int size, VFILE *fd)
{
//	return(fflush(fd->buffer));
	return(munmap(addr, size));
}

VFILE *vf_wrap_fd(int fd)
{
	VFILE *tmp;

//	tmp=malloc(sizeof(VFILE)+sizeof(int));
//	memset(tmp, 0, sizeof(VFILE));
	tmp=vfnew();

	tmp->read_proc=&file_read_proc;
	tmp->write_proc=&file_write_proc;
	tmp->seek_proc=&file_seek_proc;
	tmp->tell_proc=&file_tell_proc;
	tmp->close_proc=&file_close_proc;
	tmp->eof_proc=&file_eof_proc;
	tmp->flush_proc=&file_flush_proc;
	tmp->mmap_proc=&file_mmap_proc;
//	tmp->munmap_proc=&file_munmap_proc;
	tmp->buffer=tmp+1;
	*(int *)tmp->buffer=fd;
	return(tmp);
}

VFILE *vffopen_us(char *name, char *access)
{
//	FILE *fd;
	int fd;
	VFILE *vfd;

//	fd=fopen(name, access);
	fd=open(name, O_RDWR|O_CREAT, 438);

	if(fd<0)return(NULL);
	vfd=vf_wrap_fd(fd);
	return(vfd);
}

VFILE *vffopen(char *s, char *a)
{
	char buf[256];
	VFILE *vfd;

	vfd=VPath_OpenFile(s, a);
	if(vfd)return(vfd);

	strcpy(buf, "/root/");
	strcat(buf, s);
	vfd=VPath_OpenFile(buf, a);
	return(vfd);

//	return(VPath_OpenFile(s, a));
}
