#include <general.h>
#include <graphics/render.h>

VFILE *gfx_device;
int *gfx_stack, gfx_stackpos;
extern unsigned char font_8x8_32_96[96*8];
extern unsigned char koi8r_8x16[];


byte *gfxdev_outbuf;	//information to be returned from some commands
int gfxdev_outbuf_pos;

// conceptually the point will be an integer 1/72' (~0.3mm) this will allow about 941.5 x 941.5 miles plane space
// I am considering using 8.24 fixed point math (which may require assembler).

int gfxdev_matrix[16]; /* 4x4 translation */

int gfxdev_cursor_x;
int gfxdev_cursor_y;

int gfxdev_textsize_x;
int gfxdev_textsize_y;

int gfxdev_textcolor_r;
int gfxdev_textcolor_g;
int gfxdev_textcolor_b;
int gfxdev_textcolor_a;

int GfxDev_SetMatDef()
{
	int s, t;

	s=(480<<20)/792;
	s<<=4;

	t=mul_824(s, 12);

	gfxdev_textsize_x=t;
	gfxdev_textsize_y=t;

	gfxdev_textcolor_r=255;
	gfxdev_textcolor_g=255;
	gfxdev_textcolor_b=255;
	gfxdev_textcolor_a=255;

	gfxdev_matrix[0]=s;
	gfxdev_matrix[1]=0;
	gfxdev_matrix[2]=0;
	gfxdev_matrix[3]=0;

	gfxdev_matrix[4]=0;
	gfxdev_matrix[5]=-s;
	gfxdev_matrix[6]=0;
	gfxdev_matrix[7]=480;

	gfxdev_matrix[8]=0;
	gfxdev_matrix[9]=0;
	gfxdev_matrix[10]=1<<24;
	gfxdev_matrix[11]=0;

	gfxdev_matrix[12]=0;
	gfxdev_matrix[13]=0;
	gfxdev_matrix[14]=0;
	gfxdev_matrix[15]=1<<24;

	return(0);
}

int GfxDev_SetMatOrtho(int left, int right, int bottom, int top)
{
	int mat[16], mat2[16];
	int i;

	for(i=0; i<16; i++)gfxdev_matrix[i]=0;

	gfxdev_matrix[0]=320<<20;
	gfxdev_matrix[1]=0;
	gfxdev_matrix[2]=0;
	gfxdev_matrix[3]=320;

	gfxdev_matrix[4]=0;
	gfxdev_matrix[5]=-240<<20;
	gfxdev_matrix[6]=0;
	gfxdev_matrix[7]=240;

	gfxdev_matrix[8]=0;
	gfxdev_matrix[9]=0;
	gfxdev_matrix[10]=1<<24;
	gfxdev_matrix[11]=0;

	gfxdev_matrix[12]=0;
	gfxdev_matrix[13]=0;
	gfxdev_matrix[14]=0;
	gfxdev_matrix[15]=1<<24;

	gfx_ortho_824(mat, left, right, bottom, top, 1, 2);
	matmult_824(gfxdev_matrix, 4, 4,  mat, 4, 4, mat2);

	mat2[0]<<=4;
	mat2[5]<<=4;

//	mat2[3]+=320;
//	mat2[7]+=240;

	for(i=0; i<16; i++)gfxdev_matrix[i]=mat2[i];

	return(0);
}

int GfxDev_TransVec2D(int *vec)
{
	vec[0]=mul_824(vec[0], gfxdev_matrix[0])+mul_824(vec[1], gfxdev_matrix[4])+gfxdev_matrix[3];
	vec[1]=mul_824(vec[0], gfxdev_matrix[1])+mul_824(vec[1], gfxdev_matrix[5])+gfxdev_matrix[7];
	return(0);
}

int GfxDev_PTransVec2D(int *vec)
{
	vec[0]=mul_824(vec[0], gfxdev_matrix[0])+mul_824(vec[1], gfxdev_matrix[4]);
	vec[1]=mul_824(vec[0], gfxdev_matrix[1])+mul_824(vec[1], gfxdev_matrix[5]);
	return(0);
}

int GfxDev_RTransVec2D(int *vec)
{
	int l;

	vec[0]-=gfxdev_matrix[3];
	vec[1]-=gfxdev_matrix[7];

	vec[0]+=320;
	vec[1]+=240;

//	kprint("tvec %d %d\n", vec[0], vec[1]);

//	l=mul_824(gfxdev_matrix[0], gfxdev_matrix[0]);
//	vec[0]=mul_824(vec[0], gfxdev_matrix[0]);
//	kprint("dx %d %d\n", vec[0], l);
//	vec[0]=(vec[0]<<20)/(l>>4);
	vec[0]=(vec[0]<<20)/(gfxdev_matrix[0]>>4);

//	l=mul_824(gfxdev_matrix[5], gfxdev_matrix[5]);
//	vec[1]=mul_824(vec[1], gfxdev_matrix[5]);
//	kprint("dy %d %d\n", vec[1], l);
//	vec[1]=(vec[1]<<20)/(l>>4);
	vec[1]=(vec[1]<<20)/(gfxdev_matrix[5]>>4);

//	kprint("tvec2 %d %d\n", vec[0], vec[1]);

	return(0);
}


int GfxDev_Translate(int x, int y)
{
	int mat[16], mat2[16];
	int i;

	for(i=0; i<16; i++)mat[i]=0;

	mat[0]=1<<24;
	mat[3]=x;
	mat[5]=1<<24;
	mat[7]=y;
	mat[10]=1<<24;
	mat[11]=0;
	mat[15]=1<<24;

	matmult_824(gfxdev_matrix, 4, 4, mat, 4, 4, mat2);

	for(i=0; i<16; i++)gfxdev_matrix[i]=mat2[i];

	return(0);
}

int GfxDev_Scale(int x, int y)
{
	int mat[16], mat2[16];
	int i;

	for(i=0; i<16; i++)mat[i]=0;

	mat[0]=x;
	mat[5]=y;
	mat[10]=1<<24;
	mat[15]=1<<24;

	matmult_824(gfxdev_matrix, 4, 4, mat, 4, 4, mat2);

	for(i=0; i<16; i++)gfxdev_matrix[i]=mat2[i];

	return(0);
}

int GfxDev_GetCellBit(byte *cell, int w, int h, int x, int y, int rw, int rh)
{
	int i, j, k;

	if(x>=w)x=w-1;
	if(y>=h)y=h-1;

	i=(y*w)+x;
	j=i&7;
	i>>=3;

	k=cell[i];

#if 0
	if((rh<16) && (h==16))
	{
		i&=0xe;
		k=cell[i]|cell[i+1];
	}else k=cell[i];
#endif

	return((k>>(7-j))&1);
}

int GfxDev_WriteUByte(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=0;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
	return(0);
}

int GfxDev_WriteSByte(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=8;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
	return(0);
}

int GfxDev_WriteUShort(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=64;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>8)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
	return(0);
}

int GfxDev_WriteSShort(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=64+8;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>8)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
	return(0);
}

int GfxDev_WriteULong(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=128;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>24)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>16)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>8)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
	return(0);
}

int GfxDev_WriteSLong(int v)
{
	gfxdev_outbuf[gfxdev_outbuf_pos++]=128+8;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>24)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>16)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=(v>>8)&255;
	gfxdev_outbuf[gfxdev_outbuf_pos++]=v&255;
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

int GfxFont_DrawChar(int c, int x, int y, int w, int h, int r, int g, int b, int a);

int gfxdev_opcode(int op, byte *s)
{
	int *st;
	byte *t, *t2;
	u2 *tu;
	int i;

	switch(op)
	{
	case GFXOP_NOP:
		break;
	case GFXOP_BEGINDRAWING:
		GfxDev_SetMatDef();
		GfxFont_SetFont("fixed");
		GfxDrv_BeginDrawing();
		break;

	case GFXOP_ENDDRAWING:
		GfxDrv_EndDrawing();
		break;

	case GFXOP_POPRET:
		gfx_stackpos--;
		st=gfx_stack+gfx_stackpos;
		gfxdev_outbuf_pos=0;
		GfxDev_WriteSLong(st[0]);
		break;

	case GFXOP_FILLSQUARE:
		gfx_stackpos-=8;
		st=gfx_stack+gfx_stackpos;

//		kprint("in coords (%d %d) (%d %d)\n", st[0], st[1], st[2], st[3]);
		GfxDev_TransVec2D(st);
		GfxDev_PTransVec2D(st+2);

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

//		kprint("out coords (%d %d) (%d %d)\n", st[0], st[1], st[2], st[3]);

		GfxDrv_FillSquare(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7]);
		break;

	case GFXOP_MOVETO:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;

//		kprint("in coords (%d %d) (%d %d)\n", st[0], st[1], st[2], st[3]);
		GfxDev_TransVec2D(st);
		gfxdev_cursor_x=st[0];
		gfxdev_cursor_y=st[1];
		break;

	case GFXOP_SHOW:
		gfx_stackpos--;
		st=gfx_stack+gfx_stackpos;
		tu=(u2 *)st[0];
		while(*tu)
		{
			GfxFont_DrawChar((int)*tu&0xffff, gfxdev_cursor_x,
				gfxdev_cursor_y-gfxdev_textsize_y,
				gfxdev_textsize_x, gfxdev_textsize_y,
				gfxdev_textcolor_r, gfxdev_textcolor_g,
				gfxdev_textcolor_b, gfxdev_textcolor_a);
			gfxdev_cursor_x+=gfxdev_textsize_x;

//			GfxDrv_DrawCell(koi8r_8x16+(((int)*tu-32)*16), 8, 16, //font_8x8_32_96
//				gfxdev_cursor_x, gfxdev_cursor_y-gfxdev_textsize_y,
//				gfxdev_textsize_x, gfxdev_textsize_y,
//				gfxdev_textcolor_r, gfxdev_textcolor_g,
//				gfxdev_textcolor_b, gfxdev_textcolor_a);
//			gfxdev_cursor_x+=gfxdev_textsize_x;

			tu++;
		}
		break;

	case GFXOP_FONTSIZE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;

		i=mul_824(gfxdev_matrix[0], st[0]);
		gfxdev_textsize_x=i;

		i=mul_824(-gfxdev_matrix[5], st[1]);
		gfxdev_textsize_y=i;
		break;

	case GFXOP_TEXTCOLOR:
		gfx_stackpos-=4;
		st=gfx_stack+gfx_stackpos;
		gfxdev_textcolor_r=st[0];
		gfxdev_textcolor_g=st[1];
		gfxdev_textcolor_b=st[2];
		gfxdev_textcolor_a=st[3];
		break;

	case GFXOP_SETFONT:
		gfx_stackpos--;
		st=gfx_stack+gfx_stackpos;
		tu=(u2 *)st[0];
		t=kalloc(64);
		t2=t;
		while(*tu)*t2++=*tu++;
		*t2++=0;

		GfxFont_SetFont(t);
		break;

	case GFXOP_TRANS2D:
		st=gfx_stack+gfx_stackpos-2;
		GfxDev_TransVec2D(st);
//		kprint("coords %d %d\n", st[0], st[1]);
		break;

	case GFXOP_RTRANS2D:
		st=gfx_stack+gfx_stackpos-2;
		GfxDev_RTransVec2D(st);
//		kprint("coords %d %d\n", st[0], st[1]);
		break;

	case GFXOP_TRANSLATE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;
		GfxDev_Translate(st[0], st[1]);
		break;

	case GFXOP_SCALE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;
		GfxDev_Scale(st[0], st[1]);
		break;

	case GFXOP_SETRANGE:
		gfx_stackpos-=4;
		st=gfx_stack+gfx_stackpos;
		GfxDev_SetMatOrtho(st[0], st[1], st[2], st[3]);
		break;

	case GFXOP_PUSHMATRIX:
		st=gfx_stack+gfx_stackpos;
		gfx_stackpos+=16;
		for(i=0; i<16; i++)st[i]=gfxdev_matrix[i];
		break;

	case GFXOP_POPMATRIX:
		gfx_stackpos-=16;
		st=gfx_stack+gfx_stackpos;
		for(i=0; i<16; i++)gfxdev_matrix[i]=st[i];
		break;

	default:
		kprint("GfxDev: unknown opcode %d.\n", op);
		return(-1);
		break;
	}
	return(0);
}

/*
cmd&7:
0: number
	(cmd>>3)&7
		0=unsigned
		1=signed
	(cmd>>6)&3
		0=1 byte
		1=2 byte
		2=4 byte
1: command
	2 bytes, upper 4 bits and next byte (forming upper 8 of opcode)

2: object
	object has upper 5 bits as a type. this is followed by data relating to the the object.
	1: string
		string contains a byte length and so many bytes data.
*/

int gfxdev_write(void *buf, int len, VFILE *fd)
{
	byte *s, *e, *t;
	u2 *su, *tu, *tu2;
	int sg, st, i;

	s=buf;
	e=s+len;

	while(s<e)
	{
		switch(*s&3)
		{
		case 0:
			sg=(*s>>3)&7;
			switch((*s>>6)&3)
			{
			case 0:
				if(sg)st=((signed char *)s)[1];
					else st=((unsigned char *)s)[1];
				s+=2;
				break;
			case 1:
				st=(s[1]<<8)+s[2];
				if(sg && (st>32767))st|=~0xFFFF;
				s+=3;
				break;
			case 2:
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				if(sg && (st>(1<<31)))st|=~0xFFFFFFFF;
				s+=5;
				break;
			case 3:
				kprint("GfxDev: number parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			gfx_stack[gfx_stackpos++]=st;
			break;
		case 1:
			st=((s[0]>>4)&15)+(s[1]<<4);
			s+=2;
			if(gfxdev_opcode(st, s)<0)return((int)s-(int)buf);
			break;
		case 2:
			switch((*s>>3)&31)
			{
			case 1:
				tu=kalloc((s[1]*2)+2);
//				strncpy(t, s+2, s[1]);

				i=s[1];
				su=(u2 *)(s+2);
				tu2=tu;
				while(i--)*tu2++=*su++;
				*tu2++=0;
				s+=(s[1]*2)+2;
				gfx_stack[gfx_stackpos++]=(int)tu;
//				kprint("parsed string \"%s\"\n", GfxDev_Uni2Asc(tu));
				break;
			default:
				kprint("GfxDev: object parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			break;
		default:
			kprint("GfxDev: cmd parse error.\n");
			return((int)s-(int)buf);
			break;
		}
	}
	return(len);
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
		GfxFont_Init();

		tmp=vfnew();
		tmp->write_proc=gfxdev_write;
		tmp->read_proc=gfxdev_read;
//		tmp->seek_proc=gfxdev_seek;
//		tmp->flush_proc=gfxdev_flush;
//		tmp->ioctls_proc=gfxdev_ioctls;
		gfx_device=tmp;

		gfx_stack=kalloc(1024*sizeof(int));
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

	mul_824(1, -1<<23);
	mul_824(256, -1<<23);
	mul_824(-1, 1<<23);
	mul_824(-256, 1<<23);

	mul_824(-256, -1<<23);
}
