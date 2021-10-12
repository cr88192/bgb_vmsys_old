#include <general.h>

/* basic vfile io ops */

static int toggle_cb(VFILE *fd, int stat, int *data)
{
	*data=stat;
	return(0);
}

int vfread(void *buf, int s1, int s2, VFILE *fd)
{
	int stat;
	u8 r;

	if(fd->read_proc)
	{
		kmutex_lock(fd->iolock);
		stat=fd->read_proc(buf, s1*s2, fd);
		kmutex_unlock(fd->iolock);
		return(stat);
	}

	if(fd->sread_proc)
	{
		kmutex_lock(fd->iolock);
		stat=-1;
		fd->sread_proc(buf, fd->s_pos, s1*s2, fd, &toggle_cb, (void *)&stat);
		while(stat==-1);
		r[0]=stat;
		r[1]=0;
		add_u8(fd->s_pos, fd->s_pos, r);

		kmutex_unlock(fd->iolock);
		return(stat);
	}

	return(0);
}

int vfwrite(void *buf, int s1, int s2, VFILE *fd)
{
	int stat;
	u8 r;

	if(fd->write_proc)
	{
		kmutex_lock(fd->iolock);
		stat=fd->write_proc(buf, s1*s2, fd);
		kmutex_unlock(fd->iolock);
		return(stat);
	}

	if(fd->swrite_proc)
	{
		kmutex_lock(fd->iolock);
		stat=-1;
		fd->swrite_proc(buf, fd->s_pos, s1*s2, fd, &toggle_cb, (void *)&stat);
		while(stat==-1);
		r[0]=stat;
		r[1]=0;
		add_u8(fd->s_pos, fd->s_pos, r);

		kmutex_unlock(fd->iolock);
		return(stat);
	}
	return(0);
}

int vfseek(VFILE *fd, int pos, int rel)
{
	s8 adr;
	u8 ret;
	int i;

	if(fd->seek_proc)
	{
		kmutex_lock(fd->iolock);
		i=fd->seek_proc(fd, pos, rel);
		kmutex_unlock(fd->iolock);
		return(i);
	}

	/* try to emulate with 64 bit version... */
	adr[0]=pos;
	adr[1]=(pos<0)?-1:0;
	if(fd->lseek_proc)
	{
		kmutex_lock(fd->iolock);
		fd->lseek_proc(fd, adr, ret, rel);
		kmutex_unlock(fd->iolock);
		return(ret[0]);
	}

	if(fd->sread_proc || fd->swrite_proc)
	{
		switch(rel)
		{
			case 0:
				fd->s_pos[0]=adr[0];
				fd->s_pos[1]=adr[1];
				break;
			case 1:
				add_u8(fd->s_pos, fd->s_pos, adr);
				break;
			default:
				return(-1);
				break;
		}
		return(fd->s_pos[0]);
	}
	return(-1);
}

int vflseek(VFILE *fd, s8 pos, s8 ret, int rel)
{
	int i;

	if(fd->lseek_proc)
	{
		kmutex_lock(fd->iolock);
		i=fd->lseek_proc(fd, pos, ret, rel);
		kmutex_unlock(fd->iolock);
		return(i);
	}
	/* emulate using vfseek */
	ret[0]=0;
	ret[1]=0;

	if((pos[1]>0)||(pos[1]<-1))
	{
		kprint("vflseek emulation: range.\n");
		return(-1);
	}

	if(fd->seek_proc)
	{
		kmutex_lock(fd->iolock);
		fd->seek_proc(fd, pos[0], rel);
		ret[0]=i;
		kmutex_unlock(fd->iolock);
		return(0);
	}

	if(fd->sread_proc || fd->swrite_proc)
	{
		switch(rel)
		{
			case 0:
				fd->s_pos[0]=pos[0];
				fd->s_pos[1]=pos[1];
				break;
			case 1:
				add_u8(fd->s_pos, fd->s_pos, pos);
				break;
			default:
				return(-1);
				break;
		}
		return(fd->s_pos[0]);
	}
	return(-1);
}

int vfsread(void *buf, u4 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	s8 adr, adr2;
	int s;

	adr[0]=pos;
	adr[1]=(pos<0)?-1:0;

	if(fd->sread_proc)
	{
		kmutex_lock(fd->iolock);
		s=fd->sread_proc(buf, adr, len, fd, cb, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
//	vflseek(fd, adr, adr, 0);
//	if(fd->read_proc)return(fd->read_proc(buf, len, fd));

	if(fd->read_proc)
	{
		vflseek(fd, adr, adr2, 0);
//		vfseek(fd, pos, 0);

		kmutex_lock(fd->iolock);
		s=fd->read_proc(buf, len, fd);
		cb(fd, s, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
	return(0);
}

int vfswrite(void *buf, u4 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	s8 adr, adr2;
	int s;

	adr[0]=pos;
	adr[1]=(pos<0)?-1:0;

	if(fd->swrite_proc)
	{
		kmutex_lock(fd->iolock);
		s=fd->swrite_proc(buf, adr, len, fd, cb, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
//	vflseek(fd, adr, adr, 0);
//	if(fd->write_proc)return(fd->write_proc(buf, len, fd));

	if(fd->write_proc)
	{
		vflseek(fd, adr, adr2, 0);
//		vfseek(fd, pos, 0);

		kmutex_lock(fd->iolock);
		s=fd->write_proc(buf, len, fd);
		cb(fd, s, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
	return(0);
}

int vfreads(void *buf, u4 pos, int len, VFILE *fd)
{
	int stat;
	u8 r;

	stat=-1;
	vfsread(buf, pos, len, fd, &toggle_cb, &stat);
	while(stat==-1);
	return(stat);
}

int vfwrites(void *buf, u4 pos, int len, VFILE *fd)
{
	int stat;
	u8 r;

	stat=-1;
	vfswrite(buf, pos, len, fd, &toggle_cb, &stat);
	while(stat==-1);
	return(stat);
}

int vflread(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	u8 r;
	int s;

	if(fd->sread_proc)
	{
		kmutex_lock(fd->iolock);
		s=fd->sread_proc(buf, pos, len, fd, cb, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}

	if(fd->read_proc)
	{
		vflseek(fd, pos, r, 0);

		kmutex_lock(fd->iolock);
		s=fd->read_proc(buf, len, fd);
		cb(fd, s, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
	return(0);
}

int vflwrite(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	u8 r;
	int s;

	if(fd->swrite_proc)
	{
		kmutex_lock(fd->iolock);
		s=fd->swrite_proc(buf, pos, len, fd, cb, data);
		kmutex_unlock(fd->iolock);
		return(s);
	}

	if(fd->write_proc)
	{
		vflseek(fd, pos, r, 0);

		kmutex_lock(fd->iolock);
		s=fd->write_proc(buf, len, fd);
		cb(fd, s, data);

		kmutex_unlock(fd->iolock);
		return(s);
	}
	return(0);
}

int vftell(VFILE *fd)
{
	if(fd->tell_proc)return(fd->tell_proc(fd));

	if(fd->sread_proc || fd->swrite_proc)return(fd->s_pos[0]);

	return(0);
}

int vfgetc(VFILE *fd)
{
	byte tmp;
	if(!vfread(&tmp, 1, 1, fd))return(-1);
	return(tmp);
}

int vfputc(int val, VFILE *fd)
{
	byte tmp;
	tmp=val;
	return(vfwrite(&tmp, 1, 1, fd));
}

int vfclose(VFILE *fd)
{
	if(fd->close_proc)return(fd->close_proc(fd));
	return(0);
}

int vfeof(VFILE *fd)
{
	if(fd->eof_proc)return(fd->eof_proc(fd));
	return(0);
}

int vfflush(VFILE *fd)
{
	if(fd->flush_proc)return(fd->flush_proc(fd));
	return(0);
}

int vfinready(VFILE *fd)
{
	int s;
	if(fd->inready_proc)
	{
		kmutex_lock(fd->iolock);
		s=fd->inready_proc(fd);
		kmutex_unlock(fd->iolock);
		return(s);
	}
	return(!vfeof(fd)); /* otherwise assume input ready unless eof */
}

int vfioctl(VFILE *fd, int req, char *argp)
{
	if(fd->ioctl_proc)return(fd->ioctl_proc(fd, req, argp));
	return(-1);
}

int vfioctls(VFILE *fd, ...)
{
	void **lst;

	lst=(void **)&fd;
	lst++;
	if(fd->ioctls_proc)return(fd->ioctls_proc(fd, lst));
	return(-1);
}

void *vfmmap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	if(fd->mmap_proc)return(fd->mmap_proc(addr, length, prot, flags, fd, offs));
	return(NULL); /* makes more sense than (void *)(-1) */
}

#if 0
int vfmunmap(void *start, int length, VFILE *fd)
{
	if(fd->munmap_proc)return(fd->munmap_proc(start, length, fd));
	return(-1);
}

int vfmsync(void *start, int length, int flags, VFILE *fd)
{
	if(fd->msync_proc)return(fd->msync_proc(start, length, flags, fd));
	return(-1);
}
#endif

int vfsend(VFILE *sock, VADDR *target, void *msg, int len, int flags)
{
	if(sock->send_proc)return(sock->send_proc(sock, target, msg, len, flags));
	return(-1);
}

int vfget(void *buf, int sz, VADDR *from, VFILE *sock)
{
	if(sock->get_proc)return(sock->get_proc(buf, sz, from, sock));
	return(-1);
}

#if 1
/* vfa-functions */
int vfaread(void *buf, int s1, int s2, VFILE *fd)
{
	if(fd->chain)return(vfread(buf, s1, s2, fd->chain));
	return(0);
}

int vfawrite(void *buf, int s1, int s2, VFILE *fd)
{
	if(fd->chain)return(vfwrite(buf, s1, s2, fd->chain));
	return(0);
}

int vfaseek(VFILE *fd, int pos, int rel)
{
	if(fd->chain)return(vfseek(fd->chain, pos, rel));
	return(0);
}

int vfatell(VFILE *fd)
{
	if(fd->chain)return(vftell(fd->chain));
	return(0);
}

int vfagetc(VFILE *fd)
{
	if(fd->chain)return(vfgetc(fd->chain));
	return(0);
}

int vfaputc(int v, VFILE *fd)
{
	if(fd->chain)return(vfputc(v, fd->chain));
	return(0);
}

int vfaclose(VFILE *fd)
{
	if(fd->chain)return(vfclose(fd->chain));
	return(0);
}

int vfaeof(VFILE *fd)
{
	if(fd->chain)return(vfeof(fd->chain));
	return(0);
}

int vfaflush(VFILE *fd)
{
	if(fd->chain)return(vfflush(fd->chain));
	return(0);
}

int vfainready(VFILE *fd)
{
	if(fd->chain)return(vfinready(fd->chain));
	return(0);
}

char *vfagets(char *s, int n, VFILE *fd)
{
	if(fd->chain)return(vfgets(s, n, fd->chain));
	return(0);
}

#endif

VFNOTIFY *vfaddnotify(VFILE *fd, int (*func)(VFILE *fd), int flags)
{
	VFNOTIFY *tmp;

	tmp=kalloc(sizeof(VFNOTIFY));
	tmp->func=func;
	tmp->flags=flags;

	tmp->next=fd->notify;
	if(fd->notify)fd->notify->prev=tmp;
	tmp->owner=fd;
	fd->notify=tmp;

	return(tmp);
}

int vfnotify(VFILE *fd, int cond)
{
	VFNOTIFY *cur;

	cur=fd->notify;
	while(cur)
	{
		if(cur->flags && (cur->flags&cond))
			cur->func(fd, cond);
		cur=cur->next;
	}

	return(0);
}

/* misc vfile ops */

VFILE *vfnew()
{
	VFILE *tmp;
	tmp=kalloc(sizeof(VFILE));
	tmp->close_proc=vfdestroy;

	tmp->iolock=kmutex_new();

	return(tmp);
}

int vfdestroy(VFILE *fd)
{
	kfree(fd);
	return(0);
}

char *vfgets(char *s, int n, VFILE *fd)
{
	int i, c;
	char *st;

	st=s;
	i=1;
	while(!vfeof(fd) && i<n)
	{
		c=vfgetc(fd);
		if(c=='\r')continue;
		*s++=c;
		if(c=='\n')break;
		i++;
	}
	*s++=0;
	return(st);
}

/* misc */
byte *vf_bufferin(VFILE *fd)
{
	byte *tmp;
	int size;
	vfseek(fd, 0, 2);
	size=vftell(fd);
	vfseek(fd, 0, 0);
	tmp=kalloc(size+1);
	vfread(tmp, 1, size, fd);
	return(tmp);
}

/* file clippings */
typedef struct {
VFILE *fd;
u8 start, len, pos;
}vfclipping;

int clip_sread(void *buf, s8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	int i;
	vfclipping *clip;
	u8 b, c;

	clip=fd->buffer;
	add_u8(b, clip->start, pos);
	i=vflread(buf, b, len, clip->fd, cb, data);
	return(i);
}

int clip_swrite(void *buf, s8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	int i;
	vfclipping *clip;
	u8 b, c;

	clip=fd->buffer;
	add_u8(b, clip->start, pos);
	i=vflwrite(buf, b, len, clip->fd, cb, data);
	return(i);
}

int clip_read(void *buf, int l, VFILE *fd)
{
	int i;
	vfclipping *clip;
	u8 b, c;

	clip=fd->buffer;

	add_u8(b, clip->start, clip->pos);
	i=vflseek(clip->fd, b, c, 0);

	i=vfread(buf, 1, l, clip->fd);

	b[0]=i;
	b[1]=0;
	add_u8(c, clip->pos, b);
	copy_u8(clip->pos, c);

//	vftell(fd);
	return(i);
}

int clip_write(void *buf, int l, VFILE *fd)
{
	int i;
	vfclipping *clip;
	u8 b, c;

	clip=fd->buffer;

	add_u8(b, clip->start, clip->pos);
	i=vflseek(clip->fd, b, c, 0);

	i=vfwrite(buf, 1, l, clip->fd);

	b[0]=i;
	b[1]=0;
	add_u8(c, clip->pos, b);
	copy_u8(clip->pos, c);

//	vftell(fd);
	return(i);
}

int clip_lseek(VFILE *fd, s8 pos, s8 ret, int rel)
{
	u8 b;
	int i;
	vfclipping *clip;

	clip=fd->buffer;

	switch(rel)
	{
	case 0:
		add_u8(b, clip->start, pos);
		if(cmp_u8(pos, clip->len)==1)return(-1);
		copy_u8(clip->pos, pos);
		i=vflseek(clip->fd, b, ret, 0);
		sub_u8(ret, ret, clip->start);
		break;
	case 1:
		add_s8(b, clip->pos, pos);
		if(cmp_u8(b, clip->len)==1)return(-1);
		copy_u8(clip->pos, b);
		add_u8(b, clip->start, b);
		i=vflseek(clip->fd, b, ret, 0);
		sub_u8(ret, ret, clip->start);
		break;
	case 2:
		add_s8(b, clip->len, pos);
		if(cmp_u8(b, clip->len)==1)return(-1);
		copy_u8(clip->pos, b);
		add_u8(b, clip->start, b);
		i=vflseek(clip->fd, b, ret, 0);
		sub_u8(ret, ret, clip->start);
		break;
	default:
		i=-1;
		break;
	}
	return(i);
}

int clip_tell(VFILE *fd)
{
	u8 b;
	int i;
	vfclipping *clip;

	clip=fd->buffer;

	b[0]=0;
	b[1]=0;
//	vflseek(clip->fd, b, b, 1);
//	sub_u8(b, b, clip->start);
//	copy_u8(clip->pos, b);
	return(clip->pos[0]);
}

int clip_close(VFILE *fd)
{
	kfree(fd->buffer);
	kfree(fd);
	return(0);
}

int clip_eof(VFILE *fd)
{
	int i;
	vfclipping *clip;

	clip=fd->buffer;
	i=cmp_u8(clip->pos, clip->len);
	if(i>=0)return(1);
	return(0);
}

int clip_flush(VFILE *fd)
{
	vfclipping *clip;

	clip=fd->buffer;
	return(vfflush(clip->fd));
}

int clip_inready(VFILE *fd)
{
	vfclipping *clip;

	clip=fd->buffer;
	return(vfinready(clip->fd));
}

int clip_ioctl(VFILE *fd, int req, void *argp)
{
	vfclipping *clip;

	clip=fd->buffer;
	return(vfioctl(clip->fd, req, argp));
}

int clip_ioctls(VFILE *fd, void **argp)
{
	vfclipping *clip;

	clip=fd->buffer;
	return(vfioctls(clip->fd, argp));
}

void *clip_mmap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	int roffs;
	vfclipping *clip;

	clip=fd->buffer;
	roffs=offs+clip->start[0];
	return(vfmmap(addr, length, prot, flags, clip->fd, roffs));
}

/* int clip_munmap(void *addr, int length, VFILE *fd)
{
	vfclipping *clip;

	clip=fd->buffer;
	return(vfmunmap(addr, length, clip->fd));
} */

VFILE *vf_clip(VFILE *fd, u8 start, u8 length)
{
	VFILE *tmp;
	vfclipping *clip;

	tmp=vfnew();
	clip=kalloc(sizeof(vfclipping));
	clip->fd=fd;
	copy_u8(clip->start, start);
	copy_u8(clip->len, length);
	tmp->buffer=clip;

	tmp->sread_proc=&clip_sread;
	tmp->swrite_proc=&clip_swrite;

//	tmp->read_proc=&clip_read;
//	tmp->write_proc=&clip_write;
//	tmp->lseek_proc=&clip_lseek;
//	tmp->tell_proc=&clip_tell;
	tmp->eof_proc=&clip_eof;

	tmp->flush_proc=&clip_flush;
	tmp->inready_proc=&clip_inready;
	tmp->ioctl_proc=&clip_ioctl;
	tmp->ioctls_proc=&clip_ioctls;

	tmp->mmap_proc=&clip_mmap;
//	tmp->munmap_proc=&clip_munmap;

	return(tmp);
}

#if 0
/* FILE */

static int file_read_proc(void *buf, int len, VFILE *fd)
{
	return(fread(buf, 1, len, fd->buffer));
}

static int file_write_proc(void *buf, int len, VFILE *fd)
{
	return(fwrite(buf, 1, len, fd->buffer));
}

static int file_seek_proc(VFILE *fd, int pos, int rel)
{
	return(fseek(fd->buffer, pos, rel));
}

static int file_tell_proc(VFILE *fd)
{
	return(ftell(fd->buffer));
}

static int file_close_proc(VFILE *fd)
{
	fclose(fd->buffer);
	free(fd);
	return(0);
}

static int file_eof_proc(VFILE *fd)
{
	return(feof(fd->buffer));
}

static int file_flush_proc(VFILE *fd)
{
	return(fflush(fd->buffer));
}

VFILE *vf_wrap_file(FILE *fd)
{
	VFILE *tmp;
	tmp=malloc(sizeof(VFILE));
	memset(tmp, 0, sizeof(VFILE));
	tmp->read_proc=&file_read_proc;
	tmp->write_proc=&file_write_proc;
	tmp->seek_proc=&file_seek_proc;
	tmp->tell_proc=&file_tell_proc;
	tmp->close_proc=&file_close_proc;
	tmp->eof_proc=&file_eof_proc;
	tmp->flush_proc=&file_flush_proc;
	tmp->buffer=fd;
	return(tmp);
}

VFILE *vffopen(char *name, char *access)
{
	FILE *fd;
	VFILE *vfd;

	fd=fopen(name, access);
	if(!fd)return(NULL);
	vfd=vf_wrap_file(fd);
	return(vfd);
}

#endif
