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

int circbuf_size(circbuf *buf)
{
	int i;

	if(buf->start<=buf->end)
		i=buf->end-buf->start;
		else i=(4096-buf->end)+buf->start;

	return(i);
}

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

int pipe_ioctls(VFILE *fd, void **arg)
{
	char *s;
	s=*arg;
	if(!strcmp(s, "get-size"))
	{
		*(int *)arg[1]=circbuf_size(fd->buffer);
		return(0);
	}
	return(-1);
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

	t1->write_proc=pipe_write;
	t1->read_proc=pipe_read;
	t1->inready_proc=pipe_inready;
	t1->ioctls_proc=pipe_ioctls;

	t2->write_proc=pipe_write;
	t2->read_proc=pipe_read;
	t2->inready_proc=pipe_inready;
	t2->ioctls_proc=pipe_ioctls;

	return(0);
}
