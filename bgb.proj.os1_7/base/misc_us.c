#include <general.h>

#include <stdio.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

double realtime;

double Sys_Time()
{
	struct timeval	tp;
	struct timezone tzp; 
	static int      secbase; 

	gettimeofday(&tp, &tzp);  

	if (!secbase)
		secbase = tp.tv_sec;

	return ((tp.tv_sec - secbase) + tp.tv_usec/1000000.0);
}

int Sys_TimeMS()
{
	struct timeval	tp;
	struct timezone tzp; 
	static int      secbase; 

	gettimeofday(&tp, &tzp);  

	if (!secbase)
		secbase = tp.tv_sec;

	return (((tp.tv_sec - secbase)*1000) + tp.tv_usec/1000);
}

int Sys_TimeDUS()
{
	struct timeval	tp;
	struct timezone tzp; 
	static int      secbase, usecbase, delta; 

	gettimeofday(&tp, &tzp);  

	if (!secbase)
	{
		secbase = tp.tv_sec;
		usecbase = tp.tv_usec;
	}

	delta=((tp.tv_sec - secbase)*1000000) + (tp.tv_usec-usecbase);
	secbase = tp.tv_sec;
	usecbase = tp.tv_usec;

	return (delta);
}

int Sys_Sleep(int us)
{
	usleep(us);
	return(0);
}

int Sys_OpenShell()
{
	fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);
}

char *Sys_ReadLine()
{
    static char text[256];
    static int     len;
	int i;
	for(i=1; i;)
	{
		i=fread(&text[len], 1, 1, stdin);
		len+=i;
		if(text[len-1]=='\n')
		{
			text[len]=0;
			len=0;
			return(text);
		}
	}
	return(NULL);
}

unsigned long Sys_Fork(int (*func)(void *data), void *data)
{
	pid_t pid;
	pid=fork();
	if(!pid)
	{
		pid=func(data);
		exit(pid);
	}
	return(pid);
}

int Sys_ProcExited(unsigned long pid)
{
	int s;
	s=waitpid(pid, NULL, WNOHANG);
	if(s>0)return(1);
	return(0);
}

/* this will need to be emulated on win32 */
int Sys_NewPipe(int hnd[2])
{
	return(pipe(hnd));
}

int Sys_ClosePipe(int hnd)
{
	close(hnd);
	return(0);
}

extern char **_env;

VFILE *Sys_Popen2(char *command)
{
	pid_t pid;
	int p_read[2];
	int p_write[2];
	char *argv[4];
	VFILE *tmp;

	pipe(p_read);
	pipe(p_write);

	kprint("popen2 enter\n");

	pid=fork();
	if(!pid)
	{
		printf("popen2 child\n");
		dup2(p_write[0], 0);	//stdin comes from write pipe
		dup2(p_read[1], 1);		//stdout goes to read pipe

//		close(p_read[0]);
//		close(p_read[1]);
//		close(p_write[0]);
//		close(p_write[1]);

		argv[0]="/bin/sh";
		argv[1]="-c";
		argv[2]=command;
		argv[3]=NULL;
		execve("/bin/sh", argv, _env);
		exit(127);
	}

//	close(p_read[1]);
//	close(p_write[0]);

	tmp=vf_wrap_fhnd2(p_read[0], p_write[1]);

	kprint("popen2 exit\n");

	return(tmp);
}

/* a few override functions */
static int file_write_proc(void *buf, int len, VFILE *fd)
{
	int s;
	s=fwrite(buf, 1, len, fd->buffer);
	fflush(fd->buffer);
	return(s);
}

static int file_inready_proc(VFILE *fd)
{
	int fhnd;
	fd_set rfds;
	struct timeval tv;

	fhnd=fileno(fd->buffer);

	FD_ZERO(&rfds);
	FD_SET(fhnd, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;

	return(select(1, &rfds, NULL, NULL, &tv));
}

VFILE *SysVF_OpenPipe(int hnd, int w)
{
	FILE *fd;
	VFILE *vfd;
	fd=fdopen(hnd, w?"wb":"rb");
	if(!fd)return(NULL);
	vfd=vf_wrap_file(fd);
	vfd->write_proc=&file_write_proc;
	vfd->inready_proc=&file_inready_proc;
	return(vfd);
}

#if 0

/* VFILE interface for sockets, pipes, ... */

int fd_read_proc(void *buf, int len, VFILE *fd)
{
	return(read(*(int *)fd->buffer, buf, len));
}

int fd_write_proc(void *buf, int len, VFILE *fd)
{
	return(write(*(int *)fd->buffer, buf, len));
}

int fd_seek_proc(VFILE *fd, int adr, int rel)
{
	return(lseek(*(int *)fd->buffer, adr, rel));
}

static int fd_tell_proc(VFILE *fd)
{
	return(lseek(*(int *)fd->buffer, 0, SEEK_CUR));
}

static int fd_close_proc(VFILE *fd)
{
	close(*(int *)fd->buffer);
	kfree(fd);
	return(0);
}

static int fd_eof_proc(VFILE *fd)
{
	FILE *fdh;
	int s;
	fdh=fdopen(*(int *)fd->buffer, "r");
	s=feof(fdh);
	fclose(fdh);
	return(s); /* FIXME: I don't know how to determine this better */
}

static int fd_flush_proc(VFILE *fd)
{
//	close(*(int *)fd->buffer);
//	MM_PFree(fd);
	return(0);
}

static int fd_inready(VFILE *fd)
{
}

VFILE *vf_wrap_fhnd(int hnd)
{
	VFILE *tmp;
	int *fhnd;
	tmp=kalloc(sizeof(VFILE)+sizeof(int));
	tmp->buffer=tmp+1;
	fhnd=tmp->buffer;
	*fhnd=hnd;

	tmp->read_proc=&fd_read_proc;
	tmp->write_proc=&fd_write_proc;
	tmp->seek_proc=&fd_seek_proc;
	tmp->tell_proc=&fd_tell_proc;
	tmp->close_proc=&fd_close_proc;
	tmp->eof_proc=&fd_eof_proc;
	tmp->flush_proc=&fd_flush_proc;
	
	return(tmp);
}

#endif

int fd2_read_proc(void *buf, int len, VFILE *fd)
{
	return(read(*(int *)fd->buffer, buf, len));
}

int fd2_write_proc(void *buf, int len, VFILE *fd)
{
	return(write(((int *)fd->buffer)[1], buf, len));
}

static int fd2_close_proc(VFILE *fd)
{
	close(((int *)fd->buffer)[0]);
	close(((int *)fd->buffer)[1]);
	kfree(fd);
	return(0);
}

VFILE *vf_wrap_fhnd2(int rfd, int wfd)
{
	VFILE *tmp;
	int *fhnd;

	tmp=vfnew();
	tmp->buffer=kalloc(2*sizeof(int));
	fhnd=tmp->buffer;

	fhnd[0]=rfd;
	fhnd[1]=wfd;

	tmp->read_proc=&fd2_read_proc;
	tmp->write_proc=&fd2_write_proc;
	tmp->close_proc=&fd2_close_proc;

	return(tmp);
}

int Sys_Printf(char *s)
{
	printf(s);
}

int Sys_Init()
{
	Sys_OpenShell();
}
