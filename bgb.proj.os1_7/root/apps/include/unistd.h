#ifndef __OS1_UNISTD_H__
#define __OS1_UNISTD_H__

int read(int fd, void *buf, long len);
int write(int fd, void *buf, long len);
long lseek(int fd, long offs, int rel);
int close(int fd);
int eof(int fd);

#endif
