#include <os1/syscalls.h>

int kopen(char *name, char *opts)
{
	int stat;
	stat=syscall(SYSCALL_OPEN, name, opts);
	return(stat);
}

int read(int fd, void *buf, long len)
{
	int stat;
	stat=syscall(SYSCALL_READ, fd, buf, len);
	return(stat);
}

int write(int fd, void *buf, long len)
{
	int stat;
	stat=syscall(SYSCALL_WRITE, fd, buf, len);
	return(stat);
}

long lseek(int fd, long offs, int rel)
{
	int stat;
	stat=syscall(SYSCALL_LSEEK, fd, offs, rel);
	return(stat);
}

int close(int fd)
{
	int stat;
	stat=syscall(SYSCALL_CLOSE, fd);
	return(stat);
}

int eof(int fd)
{
	int stat;
	stat=syscall(SYSCALL_EOF, fd);
	return(stat);
}

int inready(int fd)
{
	int stat;
	stat=syscall(SYSCALL_INREADY, fd);
	return(stat);
}

int ioctl(int fd, int req, void *argp)
{
	int stat;
	stat=syscall(SYSCALL_IOCTL, fd, req, argp);
	return(stat);
}

int ksendto(int fd, void *addr, void *msg, int len, int flags)
{
	int stat;
	stat=syscall(SYSCALL_SENDTO, fd, addr, msg, len, flags);
	return(stat);
}

int krecvfrom(void *msg, int len, void *addr, int fd)
{
	int stat;
	stat=syscall(SYSCALL_RECVFROM, msg, len, addr, fd);
	return(stat);
}

int kaccept(int fd, void *addr)
{
	int stat;
	stat=syscall(SYSCALL_ACCEPT, fd, addr);
	return(stat);
}

void *moremem(int size)
{
	void *stat;
	stat=(void *)syscall(SYSCALL_MOREMEM, size);
	return(stat);
}

int execute(char *prog, char **argv, char **env)
{
	int stat;
	stat=syscall(SYSCALL_EXECUTE, prog, argv, env);
	return(stat);
}

int send_message(int domain, int pid, int conid, int class, int size, void *body)
{
	int stat;
	stat=syscall(SYSCALL_SENDMSG, domain, pid, conid, class, size, body);
	return(stat);
}

int recieve_message(int conid, int *class, int *size, void *buffer)
{
	int stat;
	stat=syscall(SYSCALL_RECVMSG, conid, class, size, buffer);
	return(stat);
}

int kvar_set(char *var, char *val)
{
	int stat;
	stat=syscall(SYSCALL_SETKVAR, var, val);
	return(stat);
}

int kvar_get(char *var, char *val)
{
	int stat;
	stat=syscall(SYSCALL_GETKVAR, var, val);
	return(stat);
}

int getpid()
{
	int stat;
	stat=syscall(SYSCALL_GETPID);
	return(stat);
}

int getmsticks()
{
	int stat;
	stat=syscall(SYSCALL_GETMSTICKS);
	return(stat);
}

int usleep(int us)
{
	int stat;
	stat=syscall(SYSCALL_USLEEP, us);
	return(stat);
}


int kmount(char *path, char *type, char **opts)
{
	int stat;
	stat=syscall(SYSCALL_MOUNT, path, type, opts);
	return(stat);
}

int kumount(char *path)
{
	int stat;
	stat=syscall(SYSCALL_UMOUNT, path);
	return(stat);
}

int krreaddir(
	int dir, long *key,
	int cnt, char **types, char **names, void **values,
	int len, void *buffer)
{
	int stat;
	stat=syscall(SYSCALL_RREADDIR,
		dir, key,
		cnt, types, names, values,
		len, buffer);
	return(stat);
}

int kopendir(char *name)
{
	int stat;
	stat=syscall(SYSCALL_OPENDIR, name);
	return(stat);
}

int kclosedir(int dir)
{
	int stat;
	stat=syscall(SYSCALL_CLOSEDIR, dir);
	return(stat);
}
