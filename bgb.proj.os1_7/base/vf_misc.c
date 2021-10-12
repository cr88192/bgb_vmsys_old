#include <general.h>

circbuf *circbuf_new()
{
	circbuf *tmp;
	tmp=kalloc(sizeof(circbuf));
	tmp->data=kalloc(4096);
	tmp->start=0;
	tmp->end=0;
}

int circbuf_add(circbuf *buf, int v)
{
	buf->data[buf->end++]=v;
	buf->end&=0xfff;
	if(buf->start==buf->end)
	{
		buf->end--;
		return(-1);
	}
	buf->end&=0xfff;
	return(0);
}

int circbuf_get(circbuf *buf)
{
	int v;
	if(buf->start==buf->end)return(-1);
	v=buf->data[buf->start++];
	buf->start&=0xfff;
	return(v);
}

int circbuf_emptyp(circbuf *buf)
{
	if(buf->start==buf->end)return(1);
	return(0);
}

// pipes

int pipe_write(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;
	circbuf *cbuf;

	cbuf=fd->buffer;
	cbuf=cbuf->other;

	s=buf;
	for(i=0; i<len; i++)
		while(circbuf_add(cbuf, s[i]))kthread_blocked();

	return(i);
}

int pipe_read(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;
	circbuf *cbuf;

	cbuf=fd->buffer;

	s=buf;
	for(i=0; i<len; i++)
	{
		j=-1;
		while(1)
		{
			j=circbuf_get(cbuf);
			if(j>=0)break;
			kthread_blocked();
		}
		s[i]=j;
	}

	return(i);
}

int pipe_inready(VFILE *fd)
{
	int i, j;
	circbuf *cbuf;

	cbuf=fd->buffer;

	if(!circbuf_emptyp(cbuf))
		return(1);
	return(0);
}

int vfpipe(VFILE **a, VFILE **b)
{
	circbuf *cb1, *cb2;
	VFILE *t1, *t2;

	t1=vfnew();
	t2=vfnew();
	*a=t1;
	*b=t2;

	cb1=circbuf_new();
	cb2=circbuf_new();
	cb1->other=cb2;
	cb2->other=cb1;

	t1->buffer=cb1;
	t2->buffer=cb2;

	t1->write_proc=&pipe_write;
	t1->read_proc=&pipe_read;
	t1->inready_proc=&pipe_inready;

	t2->write_proc=&pipe_write;
	t2->read_proc=&pipe_read;
	t2->inready_proc=&pipe_inready;

	return(0);
}

//string buffer files

struct sbuf_fd_info_s {
void *buf;
int sz;
int offs;
};

int sbuf_write(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;
	struct sbuf_fd_info_s *inf;

	inf=fd->buffer;

	i=inf->sz-inf->offs;
	if(len<i)i=len;
	memcpy(inf->buf+inf->offs, buf, i);

	return(i);
}

int sbuf_read(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;
	struct sbuf_fd_info_s *inf;

	inf=fd->buffer;

	i=inf->sz-inf->offs;
	if(len<i)i=len;
	memcpy(buf, inf->buf+inf->offs, i);

	return(i);
}

int sbuf_inready(VFILE *fd)
{
	int i, j;
	return(1);
}

int sbuf_eof(VFILE *fd)
{
	int i, j;
	struct sbuf_fd_info_s *inf;

	inf=fd->buffer;

	if(inf->offs>=inf->sz)return(1);
	return(0);
}

int sbuf_seek(VFILE *fd, int offs, int rel)
{
	int i, j;
	struct sbuf_fd_info_s *inf;

	inf=fd->buffer;

	switch(rel)
	{
	case 0:
		inf->offs=offs;
		break;
	case 1:
		inf->offs+=offs;
		break;
	case 2:
		inf->offs=inf->sz+offs;
		break;
	default:
		break;
	}

	return(inf->offs);
}

VFILE *vf_wrap_buf(void *s, int sz)
{
	VFILE *tmp;
	struct sbuf_fd_info_s *inf;

	tmp=vfnew();

	inf=kalloc(sizeof(struct sbuf_fd_info_s));
	inf->buf=kmemdup(s, sz);
	inf->sz=sz;
	inf->offs=0;

	tmp->buffer=inf;

	tmp->write_proc=&sbuf_write;
	tmp->read_proc=&sbuf_read;
	tmp->inready_proc=&sbuf_inready;
	tmp->eof_proc=&sbuf_eof;
	tmp->seek_proc=&sbuf_seek;

	return(tmp);
}

VFILE *vf_wrap_string(char *s)
{
	return(vf_wrap_buf(s, strlen(s)));
}

//misc calls

int vfaccept(VFILE *fd, VFILE **rfd, VADDR *addr)
{
	struct {
	VFILE *fd;
	VADDR *addr;
	}acc;

	acc.fd=NULL;
	acc.addr=addr;
	vfioctl(fd, IOCTL_ACCEPT, &acc);
	*rfd=acc.fd;

	return(0);
}
