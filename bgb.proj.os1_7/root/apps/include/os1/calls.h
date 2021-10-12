#ifndef __OS1_CALLS_H__
#define __OS1_CALLS_H__

int kopen(char *name, char *opts);
int read(int fd, void *buf, long len);
int write(int fd, void *buf, long len);
long lseek(int fd, long offs, int rel);
int close(int fd);
int eof(int fd);
void *moremem(int size);
int execute(char *prog, char **argv, char **env);

#endif
