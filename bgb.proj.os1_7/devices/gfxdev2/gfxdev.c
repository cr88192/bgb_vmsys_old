/*
stripped down, removing all the scaling/translation/font/... stuff.
this will be a basic driver, everything before held in the driver will be
moved to the gui core.
this will use a more efficient message format (for encode/decode anyways),
and will make more use of the fact that it is being used from local process.
only a single message will be sent per operation, and it will have a fixed
header: {short tag; short length;}, length is included both for pad and
because it would allow the possibility of remote vid driver access, and
because it is needed for user to fetch values.

 */

#include <general.h>
#include <graphics/render.h>

VFILE *gfx_device=NULL;
long *gfx_stack, gfx_stackpos;

byte *gfxdev_outbuf;	//information to be returned from some commands
int gfxdev_outbuf_pos;

int GfxDev_WriteSLong(long v)
{
	void *p;

	p=gfxdev_outbuf+gfxdev_outbuf_pos;
	*(short *)p=GFXOP2_INTEGER;
	p+=sizeof(short);
	*(short *)p=sizeof(long);
	p+=sizeof(short);

	*(long *)p=v;
	p+=sizeof(long);

	gfxdev_outbuf_pos=((int)p)-((int)gfxdev_outbuf);
	return(0);
}

char *GfxDev_Uni2Asc(u2 *s)
{
	char *t;
	int i, j;

	for(i=0; s[i]; i++);

	t=kalloc(i);
	for(j=0; j<(i+1); j++)t[j]=s[j];

	return(t);
}

int gfxdev_write(void *buf, int len, VFILE *fd)
{
	short tag, mlen;
	void *buf2;
	void *p1, *p2;
	long l;
	long *st;

	tag=*(short *)buf;
	mlen=*(short *)(buf+2);
	buf2=buf+4;

	if(mlen!=(len-4))
	{
		kprint("GfxDev: bad length message\n");
		return(-1);
	}

	switch(tag)
	{
	case GFXOP2_NOP:
		break;
	case GFXOP2_INTEGER:
		gfx_stack[gfx_stackpos++]=*(long *)buf2;
		break;
	case GFXOP2_STRING:
		p1=kalloc(mlen+1);
		memset(p1, 0, mlen+1);
		strncpy(p1, buf2, mlen);
		gfx_stack[gfx_stackpos++]=(long)p1;
		break;
	case GFXOP2_DATAGLOB:
		l=*(long *)buf2;
		buf2+=sizeof(long);
		p1=*(void **)buf2;
		p2=kalloc(l);
		memcpy(p2, p1, l);

		gfx_stack[gfx_stackpos++]=(long)p2;
		break;

	case GFXOP2_BEGINDRAWING:
		GfxDrv_BeginDrawing();
		break;

	case GFXOP2_ENDDRAWING:
		GfxDrv_EndDrawing();
		break;

	case GFXOP2_POPRET:
		gfx_stackpos--;
		st=gfx_stack+gfx_stackpos;
		gfxdev_outbuf_pos=0;
		GfxDev_WriteSLong(st[0]);
		break;

	case GFXOP2_FILLSQUARE:
		gfx_stackpos-=8;
		st=gfx_stack+gfx_stackpos;

		if(st[2]<0)
		{
			st[0]+=st[2];
			st[2]=0-st[2];
		}
		if(st[3]<0)
		{
			st[1]+=st[3];
			st[3]=0-st[3];
		}

		GfxDrv_FillSquare(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7]);
		break;

	case GFXOP2_DRAWIMAGE:
		gfx_stackpos-=7;
		st=gfx_stack+gfx_stackpos;

		if(st[2]<0)
		{
			st[0]+=st[2];
			st[2]=0-st[2];
		}
		if(st[3]<0)
		{
			st[1]+=st[3];
			st[3]=0-st[3];
		}

		GfxDrv_DrawImg(st[0], st[1], st[2], st[3],
			0, 0, st[5], st[6],
			st[4], st[5], st[6]);
		break;

	default:
		kprint("GfxDev: Unknown message %d\n", tag);
		return(-1);
		break;
	}
	return(0);
}

int gfxdev_read(void *buf, int len, VFILE *fd)
{
	if(len>gfxdev_outbuf_pos)len=gfxdev_outbuf_pos;
	memcpy(buf, gfxdev_outbuf, len);
	memcpy(gfxdev_outbuf, gfxdev_outbuf+len, 1024-len);
	gfxdev_outbuf_pos-=len;
	return(len);
}

VFILE *gfxdev_open(char *name, void *data)
{
	VFILE *tmp;
	int i;
	byte *buf;

	tmp=gfx_device;
	if(!tmp)
	{
		GfxDrv_Start();

		tmp=vfnew();
		tmp->write_proc=gfxdev_write;
		tmp->read_proc=gfxdev_read;
		gfx_device=tmp;

		gfx_stack=kalloc(1024*sizeof(long));
		gfx_stackpos=8;
		
		gfxdev_outbuf=kalloc(1024);
		gfxdev_outbuf_pos=0;
	}
	return(tmp);
}

int Gfxdev_Init()
{
	Driver_RegisterStream("gfxdev", &gfxdev_open, NULL);
	GfxDrv_Init();
}
