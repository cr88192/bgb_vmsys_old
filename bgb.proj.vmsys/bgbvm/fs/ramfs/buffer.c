#include <general.h>
#include <buffer.h>

/* create a new empty buffer */
Buffer *Buffer_New()
{
	Buffer *tmp;
	tmp=kalloc(sizeof(Buffer));
	memset(tmp, 0, sizeof(Buffer));
	tmp->buffers=(byte **)kalloc(BUFMAXNUM*sizeof(byte *));
	memset((void *)tmp->buffers, 0, BUFMAXNUM*sizeof(byte *));
	return(tmp);
}

/* destroy a buffer */
int Buffer_Destroy(Buffer *buffer)
{
	int i;
	if(buffer->on_destroy)i=buffer->on_destroy(buffer);
	if(i<0)return(i);

	for(i=0;i<BUFMAXNUM;i++)if(buffer->buffers[i])
		kfree(buffer->buffers[i]);
	kfree(buffer);
	return(0);
}

/* write byte to buffer, allocating more space if needed */
void Buffer_WriteByte(Buffer *buffer, byte v)
{
	int bufnum, bufpos;
	bufnum=buffer->pos/BUFBLKSZ;
	bufpos=buffer->pos%BUFBLKSZ;

	if(bufnum>=BUFMAXNUM)return;

	if(!buffer->buffers[bufnum])
		buffer->buffers[bufnum]=kalloc(BUFBLKSZ);
	buffer->buffers[bufnum][bufpos]=v;
	buffer->pos++;
	if(buffer->pos>buffer->size)buffer->size=buffer->pos;
}

/* write some bytes into a buffer */
void Buffer_WriteBytes(Buffer *buffer, byte *buf, int len)
{
	while(len--)
		Buffer_WriteByte(buffer, *buf++);
}

#if 0

/* write short to buffer (wrote as be) */
void Buffer_WriteShort(Buffer *buffer, u2 v)
{
	u2 v2;
	v2=htons(v);
	Buffer_WriteBytes(buffer, (byte *)&v2, 2);
}

/* write long to buffer (wrote as be) */
void Buffer_WriteLong(Buffer *buffer, u4 v)
{
	u4 v2;
	v2=htonl(v);
	Buffer_WriteBytes(buffer, (byte *)&v2, 4);
}

#endif

//#ifndef NOLONGLONG
#if 0
/* write long long to buffer (wrote as be) */
void Buffer_WriteDLong(Buffer *buffer, u8 v)
{
	u8 v2;
	v2=swapdlong(v);
	Buffer_WriteBytes(buffer, (byte *)&v2, 8);
}
#endif

/* write a string to buffer */
void Buffer_WriteString(Buffer *buffer, char *s)
{
	Buffer_WriteByte(buffer, strlen(s));
	while(*s)
	{
		Buffer_WriteByte(buffer, *s);
		s++;
	}
}

/* generate a combined form of the buffer */
byte *Buffer_GetCopy(Buffer *buffer)
{
	byte *tmp, *t2;
	int blk, sz;
	tmp=kalloc(buffer->size);
	t2=tmp;
	blk=0;
	sz=buffer->size;
	while(sz>BUFBLKSZ)
	{
		memset(t2, 0, BUFBLKSZ); /* in case of hole */
		if(buffer->buffers[blk])
			memcpy(t2, buffer->buffers[blk], BUFBLKSZ);
		blk++;
		sz-=BUFBLKSZ;
		t2+=BUFBLKSZ;
	}
	memset(t2, 0, sz);
	if(buffer->buffers[blk])memcpy(t2, buffer->buffers[blk], sz);
	return(tmp);
}

int Buffer_GetPos(Buffer *buf)
{
	return(buf->pos);
}

int Buffer_GetLength(Buffer *buf)
{
	return(buf->size);
}

int Buffer_Seek(Buffer *buf, int adr, int rel)
{
	switch(rel)
	{
		case 0:
			buf->pos=adr;
			break;
		case 1:
			buf->pos+=adr;
			break;
		case 2:
			buf->pos=buf->size+adr;
			break;
		default:
			break;
	}
	return(0);
}

Buffer *Buffer_Load(VFILE *fd, u4 size)
{
	Buffer *tmp;
	byte *buf;
	int bufnum;

	tmp=Buffer_New();
	bufnum=0;
	while(size>0)
	{
		buf=kalloc(BUFBLKSZ);
		vfread(buf, 1, BUFBLKSZ<size?BUFBLKSZ:size, fd);
		tmp->buffers[bufnum]=buf;
		bufnum++;
		tmp->pos+=BUFBLKSZ<size?BUFBLKSZ:size;
		size-=BUFBLKSZ<size?BUFBLKSZ:size;
	}
	tmp->size=tmp->pos;
	return(tmp);
}

int Buffer_Store(VFILE *fd, Buffer *buf)
{
	u4 size;
	int tsz, bufnum;

	bufnum=0;
	size=buf->size;
	while(size>0)
	{
		tsz=BUFBLKSZ<size?BUFBLKSZ:size;
		vfwrite(buf->buffers[bufnum], 1, tsz, fd);
		bufnum++;
		size-=tsz;
	}
	return(0);
}

/* VFILE interface */

static int vf_read_buffer(void *buf2, int len, VFILE *fd)
{
	Buffer *buffer;
	int bufnum, bufpos, tsz, olen;
	byte *buf;

	buf=(byte *)buf2;
	buffer=fd->buffer;
	bufnum=buffer->pos/BUFBLKSZ;
	bufpos=buffer->pos%BUFBLKSZ;
	olen=len;
	while(len>0)
	{
		if(buffer->pos>=buffer->size)break;
		tsz=(len<(BUFBLKSZ-bufpos)?len:(BUFBLKSZ-bufpos));
		tsz=(tsz<(buffer->size-buffer->pos))?tsz:
			(buffer->size-buffer->pos);
		memcpy(buf, (void *)((int)buffer->buffers[bufnum]+bufpos),
			tsz);
		len-=tsz;
		bufpos+=tsz;
		buf+=tsz;
		buffer->pos+=tsz;
		if(bufpos>=BUFBLKSZ)
		{
			bufnum++;
			bufpos=0;
		}
	}
	return(olen-len);
}

static int vf_write_buffer(void *buf2, int len, VFILE *fd)
{
	Buffer *buffer;
	int bufnum, bufpos, tsz, olen;
	byte *buf;

	buf=(byte *)buf2;
	buffer=fd->buffer;
	bufnum=buffer->pos/BUFBLKSZ;
	bufpos=buffer->pos%BUFBLKSZ;
	olen=len;
	while(len>0)
	{
		if(!buffer->buffers[bufnum])
		{
			buffer->buffers[bufnum]=kalloc(BUFBLKSZ);
			memset(buffer->buffers[bufnum], 0, BUFBLKSZ);
		}
		tsz=(len<(BUFBLKSZ-bufpos)?len:(BUFBLKSZ-bufpos));
		memcpy((void *)((int)buffer->buffers[bufnum]+bufpos), buf,
			tsz);
		len-=tsz;
		bufpos+=tsz;
		buf+=tsz;
		buffer->pos+=tsz;
		if(bufpos>=BUFBLKSZ)
		{
			bufnum++;
			bufpos=0;
		}
	}
	if(buffer->pos>buffer->size)buffer->size=buffer->pos;
	return(olen-len);
}

static int vf_seek_buffer(VFILE *fd, int pos, int rel)
{
	return(Buffer_Seek(fd->buffer, pos, rel));
}

static int vf_tell_buffer(VFILE *fd)
{
	return(Buffer_GetPos(fd->buffer));
}

static int vf_close_buffer(VFILE *fd)
{
	return(Buffer_Destroy(fd->buffer));
}

static int vf_eof_buffer(VFILE *fd)
{
	Buffer *buffer;
	buffer=fd->buffer;
	if(buffer->pos<buffer->size)return(0);
	return(1);
}

VFILE *vf_wrap_buffer(Buffer *buf)
{
	VFILE *tmp;
	tmp=kalloc(sizeof(VFILE));
	memset(tmp, 0, sizeof(VFILE));
	tmp->read_proc=&vf_read_buffer;
	tmp->write_proc=&vf_write_buffer;
	tmp->seek_proc=&vf_seek_buffer;
	tmp->tell_proc=&vf_tell_buffer;
	tmp->close_proc=&vf_close_buffer;
	tmp->eof_proc=&vf_eof_buffer;
	tmp->buffer=buf;
	return(tmp);
}
