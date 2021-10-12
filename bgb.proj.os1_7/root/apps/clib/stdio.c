#include <unistd.h>
#include <stdio.h>
#include <errno.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

int errno;

FILE *fdopen(int fd, char *mode)
{
	FILE *tmp;

	if(fd<0)return(NULL);

	tmp=malloc(sizeof(FILE));
	tmp->fd=fd;

	return(tmp);
}

FILE *fopen(char *name, char *mode)
{
	FILE *tmp;
	int fd;

	fd=kopen(name, mode);
	return(fdopen(fd, mode));
}

int fread(void *buf, int l1, int l2, FILE *fd)
{
	return(read(fd->fd, buf, l1*l2));
}

int fwrite(void *buf, int l1, int l2, FILE *fd)
{
	return(write(fd->fd, buf, l1*l2));
}

long fseek(FILE *fd, long offs, int rel)
{
	return(lseek(fd->fd, offs, rel));
}

int fclose(FILE *fd)
{
	close(fd->fd);
	free(fd);
	return(0);
}

int feof(FILE *fd)
{
	return(eof(fd->fd));
}

int finready(FILE *fd)
{
	return(inready(fd->fd));
}

int fsendto(FILE *fd, void *addr, void *msg, int len, int flags)
{
	return(ksendto(fd->fd, addr, msg, len, flags));
}

int frecvfrom(void *buf, int sz, void *addr, FILE *fd)
{
	return(krecvfrom(buf, sz, addr, fd->fd));
}

FILE *faccept(FILE *fd, void *addr)
{
	int i;

	i=kaccept(fd->fd, addr);
	return(fdopen(i, "r+b"));
}

int fflush(FILE *fd)
{
}

long ftell(FILE *fd)
{
	return(fseek(fd, 0, SEEK_CUR));
}

int fgetc(FILE *fd)
{
	unsigned char c;

	if(feof(fd))return(-1);

	fread(&c, 1, 1, fd);
	return(c);
}

int fputc(int ch, FILE *fd)
{
	unsigned char c;

	c=ch;
	fwrite(&c, 1, 1, fd);
	return(c);
}

int getc()
{
	return(fgetc(stdin));
}

int putc(int c)
{
	return(fputc(c, stdin));
}

char *fgets(char *s, int n, FILE *fd)
{
	char *is;
	int c;
	c=-1;

	is=s;

	while(c!='\n')
	{
		c=fgetc(fd);
		if(c<0)return(NULL);

		fputc(c, stdout);

		if(c==0x08)s--;
			else *s++=c;
		*s=0;

		if((s-is)>=n)return(is);
	}

	return(is);
}

int fputs(const char *s, FILE *fp)
{
	while(*s)fputc(*s++, fp);
	return(0);
}

int puts(const char *s)
{
	fputs(s, stdout);
}

int remove(char *name)
{
	//delete name
	return(-1);
}

char *strerror(int num)
{
	char *s;
	switch(num)
	{
		case EPERM:	s="Not super-user"; break;
		case ENOENT:	s="No such file or directory"; break;
		case ESRCH:	s="No such process"; break;
		case EINTR:	s="Interrupted system call"; break;
		case EIO:	s="I/O error"; break;
		case ENXIO:	s="No such device or address"; break;
		case E2BIG:	s="Arg list too long"; break;
		case ENOEXEC:	s="Exec format error"; break;
		case EBADF:	s="Bad file number"; break;
		case ECHILD:	s="No children"; break;
		case EAGAIN:	s="No more processes"; break;
		case ENOMEM:	s="Not enough core"; break;
		case EACCES:	s="Permission denied"; break;
		case EFAULT:	s="Bad address"; break;
		case ENOTBLK:	s="Block device required"; break;
		case EBUSY:	s="Mount device busy"; break;
		case EEXIST:	s="File exists"; break;
		case EXDEV:	s="Cross-device link"; break;
		case ENODEV:	s="No such device"; break;
		case ENOTDIR:	s="Not a directory"; break;
		case EISDIR:	s="Is a directory"; break;
		case EINVAL:	s="Invalid argument"; break;
		case ENFILE:	s="Too many open files in system"; break;
		case EMFILE:	s="Too many open files"; break;
		case ENOTTY:	s="Not a typewriter"; break;
		case ETXTBSY:	s="Text file busy"; break;
		case EFBIG:	s="File too large"; break;
		case ENOSPC:	s="No space left on device"; break;
		case ESPIPE:	s="Illegal seek"; break;
		case EROFS:	s="Read only file system"; break;
		case EMLINK:	s="Too many links"; break;
		case EPIPE:	s="Broken pipe"; break;
		case EDOM:	s="Math arg out of domain of func"; break;
		case ERANGE:	s="Math result not representable"; break;
		case ENOMSG:	s="No message of desired type"; break;
		case EIDRM:	s="Identifier removed"; break;
		case ECHRNG:	s="Channel number out of range"; break;
		case EL2NSYNC:	s="Level 2 not synchronized"; break;
		case EL3HLT:	s="Level 3 halted"; break;
		case EL3RST:	s="Level 3 reset"; break;
		case ELNRNG:	s="Link number out of range"; break;
		case EUNATCH:	s="Protocol driver not attached"; break;
		case ENOCSI:	s="No CSI structure available"; break;
		case EL2HLT:	s="Level 2 halted"; break;
		case EDEADLK:	s="Deadlock condition"; break;
		case ENOLCK:	s="No record locks available"; break;
		case EBADE:	s="Invalid exchange"; break;
		case EBADR:	s="Invalid request descriptor"; break;
		case EXFULL:	s="Exchange full"; break;
		case ENOANO:	s="No anode"; break;
		case EBADRQC:	s="Invalid request code"; break;
		case EBADSLT:	s="Invalid slot"; break;
		case EDEADLOCK:	s="File locking deadlock error"; break;
		case EBFONT:	s="Bad font file fmt"; break;
		case ENOSTR:	s="Device not a stream"; break;
		case ENODATA:	s="No data (for no delay io)"; break;
		case ETIME:	s="Timer expired"; break;
		case ENOSR:	s="Out of streams resources"; break;
		case ENONET:	s="Machine is not on the network"; break;
		case ENOPKG:	s="Package not installed"; break;
		case EREMOTE:	s="The object is remote"; break;
		case ENOLINK:	s="The link has been severed"; break;
		case EADV:	s="Advertise error"; break;
		case ESRMNT:	s="Srmount error"; break;
		case ECOMM:	s="Communication error on send"; break;
		case EPROTO:	s="Protocol error"; break;
		case EMULTIHOP:	s="Multihop attempted"; break;
		case ELBIN:	s="Inode is remote (not really error)"; break;
		case EDOTDOT:	s="Cross mount point (not really error)"; break;
		case EBADMSG:	s="Trying to read unreadable message"; break;
		case EFTYPE:	s="Inappropriate file type or format"; break;
		case ENOTUNIQ:	s="Given log. name not unique"; break;
		case EBADFD:	s="f.d. invalid for this operation"; break;
		case EREMCHG:	s="Remote address changed"; break;
		case ELIBACC:	s="Can't access a needed shared lib"; break;
		case ELIBBAD:	s="Accessing a corrupted shared lib"; break;
		case ELIBSCN:	s=".lib section in a.out corrupted"; break;
		case ELIBMAX:	s="Attempting to link in too many libs"; break;
		case ELIBEXEC:	s="Attempting to exec a shared library"; break;
		case ENOSYS:	s="Function not implemented"; break;
		case ENMFILE:	s="No more files"; break;
		case ENOTEMPTY:	s="Directory not empty"; break;
		case ENAMETOOLONG:	s="File or path name too long"; break;
		case ELOOP:	s="Too many symbolic links"; break;
		case EOPNOTSUPP:	s="Operation not supported on transport endpoint"; break;
		case EPFNOSUPPORT:	s="Protocol family not supported"; break;
		case ECONNRESET:	s="Connection reset by peer"; break;
		case ENOBUFS:	s="No buffer space available"; break;
		case EAFNOSUPPORT:	s="Address family not supported by protocol family"; break;
		case EPROTOTYPE:	s="Protocol wrong type for socket"; break;
		case ENOTSOCK:	s="Socket operation on non-socket"; break;
		case ENOPROTOOPT:	s="Protocol not available"; break;
		case ESHUTDOWN:	s="Can't send after socket shutdown"; break;
		case ECONNREFUSED:	s="Connection refused"; break;
		case EADDRINUSE	:	s="Address already in use"; break;
		case ECONNABORTED:	s="Connection aborted"; break;
		case ENETUNREACH:	s="Network is unreachable"; break;
		case ENETDOWN:	s="Network interface is not configured"; break;
		case ETIMEDOUT:	s="Connection timed out"; break;
		case EHOSTDOWN:	s="Host is down"; break;
		case EHOSTUNREACH:	s="Host is unreachable"; break;
		case EINPROGRESS:	s="Connection already in progress"; break;
		case EALREADY:	s="Socket already connected"; break;
		case EDESTADDRREQ:	s="Destination address required"; break;
		case EMSGSIZE:	s="Message too long"; break;
		case EPROTONOSUPPORT:	s="Unknown protocol"; break;
		case ESOCKTNOSUPPORT:	s="Socket type not supported"; break;
		case EADDRNOTAVAIL:	s="Address not available"; break;
		case EISCONN:	s="Socket is already connected"; break;
		case ENOTCONN:	s="Socket is not connected"; break;
		case ENOTSUP:	s="Not supported"; break;
		case ENOMEDIUM:	s="No medium (in tape drive)"; break;
		case ENOSHARE:	s="No such host or network path"; break;
		case ECASECLASH:	s="Filename exists with different case"; break;
		case EOVERFLOW:	s="Value too large for defined data type"; break;

		default:
			s="";
			break;
	}
	return(s);
}

int perror(char *prefix)
{
	fprintf(stderr, "%s: %s\n", prefix, strerror(errno));
	return(0);
}

int __stdio_init()
{
	__malloc_init();

	stdin=fdopen(0, "r");
	stdout=fdopen(1, "w");
	stderr=fdopen(2, "w");
}
