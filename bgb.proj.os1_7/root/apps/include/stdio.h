#ifndef __OS1_STDIO_H__
#define __OS1_STDIO_H__

#ifndef NULL
#define NULL ((void *)0)
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef long size_t;

typedef struct {
int fd;
}FILE;

FILE *stdin;
FILE *stdout;
FILE *stderr;
int errno;

void *malloc(int size);
int free(void *p);

FILE *fdopen(int fd, char *mode);
FILE *fopen(char *name, char *mode);
int fread(void *buf, int l1, int l2, FILE *fd);
int fwrite(void *buf, int l1, int l2, FILE *fd);
long fseek(FILE *fd, long offs, int rel);
int fclose(FILE *fd);

int fgetc(FILE *fd);
char *fgets(char *s, int n, FILE *fd);

#endif
