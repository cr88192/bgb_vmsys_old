#ifndef __VFILE_H__
#define __VFILE_H__

#define PROTO_IPV4	(1<<8)
#define	PROTO_IPV6	(2<<8)
#define PROTO_TCP	1
#define	PROTO_UDP	2

#define PROTO_UNDEFINED	0
#define PROTO_IPV4UDP	(PROTO_IPV4|PROTO_UDP)
#define PROTO_IPV4TCP	(PROTO_IPV4|PROTO_TCP)
#define PROTO_IPV6UDP	(PROTO_IPV6|PROTO_UDP)
#define PROTO_IPV6TCP	(PROTO_IPV6|PROTO_TCP)

/* these may be loaded in the lower 8 flag bits for send and similar */
#define PROTO_PF_UNDEFINED	0

#define PROTO_PF_IPV4		4
#define PROTO_PF_TCP		6
#define PROTO_PF_UDP		17

#define PROTO_PF_IPV6		41
#define PROTO_PF_IPV6ROUTE	43
#define PROTO_PF_IPV6FRAG	44
#define PROTO_PF_IPV6ICMP	58
#define PROTO_PF_IPV6NONXT	59
#define PROTO_PF_IPV6OPTS	60

typedef union VADDR_u VADDR;

union VADDR_u {
	int proto;

	struct {
	int proto;
	int flags; /* lower 8 bits=netmask count */
	unsigned short port;
	unsigned long addr;
	}ipv4;

	struct {
	int proto;
	int flags; /* lower 8 bits=netmask count */
	unsigned short port;
	byte addr[16];
	}ipv6;
};

typedef struct circbuf_t {
struct circbuf_t *other;
byte *data;
int start, end;
}circbuf;

typedef struct VFILE_T VFILE;

typedef struct VFNOTIFY_S {
struct VFNOTIFY_S *next, *prev;
VFILE *owner;
int (*func)(VFILE *fd, int cond);
int flags;	//0-15: state changes to notice, 16=once then remove
}VFNOTIFY;

#define VFN_INREADY	1
#define VFN_CANWRITE	2

typedef int vf_int_cb(VFILE *fd, int stat, void *data);

struct VFILE_T {
int (*read_proc)(void *buf, int len, VFILE *fd);
int (*write_proc)(void *buf, int len, VFILE *fd);
int (*seek_proc)(VFILE *fd, int adr, int rel);
int (*lseek_proc)(VFILE *fd, s8 adr, s8 ret, int rel);
int (*tell_proc)(VFILE *fd);
int (*ltell_proc)(VFILE *fd, s8 ret);
int (*close_proc)(VFILE *fd);
int (*eof_proc)(VFILE *fd);
int (*flush_proc)(VFILE *fd);
int (*inready_proc)(VFILE *fd);
int (*ioctl_proc)(VFILE *fd, int req, char *argp);
int (*ioctls_proc)(VFILE *fd, void **arg);
void *(*mmap_proc)(void *addr, int length, int prot, int flags, VFILE *fd, int offs);
//int (*munmap_proc)(void *start, int length, VFILE *fd);
//int (*msync_proc)(void *start, int length, int flags, VFILE *fd);

int (*sread_proc)(void *buf, s8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);
int (*swrite_proc)(void *buf, s8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);

int (*send_proc)(VFILE *sock, VADDR *target, void *msg, int len, int flags); /* used in the same bent way as read/write */
int (*get_proc)(void *buf, int sz, VADDR *from, VFILE *sock);

u8 s_pos;	//for seeking read/write, allow emulation of normal read/write on async devs

void *buffer;	//data used by creator to allow storing other data.
void *userdata;	//user data, can be attached to files possibly to ease open file management

kmutex *iolock;

//void *mapdata; /* for use by mmap in cases it is external */
VFILE *chain, *ch_prev; /* used by things that recieve this vfile, ch_prev used for putting in lists */
VFILE *c_next, *c_prev; /* used by the creator */

VFNOTIFY *notify;
};

int vfsread(void *buf, u4 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);
int vfswrite(void *buf, u4 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);
int vfreads(void *buf, u4 pos, int len, VFILE *fd);
int vfwrites(void *buf, u4 pos, int len, VFILE *fd);
int vflread(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);
int vflwrite(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data);

int vfread(void *buf, int s1, int s2, VFILE *fd);
int vfwrite(void *buf, int s1, int s2, VFILE *fd);
int vfseek(VFILE *fd, int pos, int rel);
int vflseek(VFILE *fd, s8 pos, s8 ret, int rel);
int vftell(VFILE *fd);
int vfgetc(VFILE *fd);
int vfputc(int v, VFILE *fd);
int vfclose(VFILE *fd);
int vfeof(VFILE *fd);
int vfflush(VFILE *fd);
int vfinready(VFILE *fd);
char *vfgets(char *s, int n, VFILE *fd);

int vfioctls(VFILE *fd, ...);
void *vfmmap(void *addr, int length, int prot, int flags, VFILE *fd, int offs);
//int vfmunmap(void *start, int length, VFILE *fd);
//int vfmsync(void *start, int length, int flags, VFILE *fd);

//VFILE *vf_wrap_file(FILE *fd);
VFILE *vffopen(char *name, char *access);

byte *vf_bufferin(VFILE *fd);

VFILE *vf_clip(VFILE *fd, u8 start, u8 length);

VFILE *vfnew();
int vfdestroy(VFILE *fd);

int vfsend(VFILE *sock, VADDR *target, void *msg, int len, int flags);
int vfget(void *buf, int sz, VADDR *from, VFILE *sock);

#endif

