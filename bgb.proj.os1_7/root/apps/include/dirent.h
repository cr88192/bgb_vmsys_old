#ifndef __OS1_DIRENT_H__
#define __OS1_DIRENT_H__

#define NAME_MAX	256

typedef long off_t;

struct dirent {
char d_name[NAME_MAX];
};

typedef struct {
int fd;
int eod;
long key;

struct dirent de;
}DIR;

#endif
