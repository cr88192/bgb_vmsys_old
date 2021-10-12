#ifndef __BUFFER_H__
#define __BUFFER_H__

#define BUFBLKSZ 4096
#define BUFMAXNUM 1024

typedef struct Buffer_T Buffer;

struct Buffer_T {
byte **buffers;
int (*on_destroy)(Buffer *buf);
void *special;
int size;
int pos;

VFILE *chfd; /* little hack to avoid having to write similar code for files */
char *name; /* buffer name, section name in case of assembly */
};

Buffer *Buffer_New();

int Buffer_Destroy(Buffer *buffer);
void Buffer_WriteByte(Buffer *buffer, byte v);
void Buffer_WriteBytes(Buffer *buffer, byte *buf, int len);
void Buffer_WriteShort(Buffer *buffer, u2 v);
void Buffer_WriteLong(Buffer *buffer, u4 v);
void Buffer_WriteString(Buffer *buffer, char *s);
byte *Buffer_GetCopy(Buffer *buffer);

int Buffer_GetPos(Buffer *buf);
int Buffer_GetLength(Buffer *buf);
int Buffer_Seek(Buffer *buf, int adr, int rel);

int Buffer_Store(VFILE *fd, Buffer *buf);
Buffer *Buffer_Load(VFILE *fd, u4 size);

Buffer *Buffer_Deflate(Buffer *buf);
Buffer *Buffer_Inflate(Buffer *buf);

VFILE *vf_wrap_buffer(Buffer *buf);

#endif
