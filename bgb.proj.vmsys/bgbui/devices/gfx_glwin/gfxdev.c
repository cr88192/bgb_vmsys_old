#include <general.h>
#include <graphics/render.h>

#include <GL/GL.h>

VFILE *gfx_device, *gfx_other;
int *gfx_stack, gfx_stackpos;
double *gfx_stackf;

extern unsigned char font_8x8_32_96[96*8];
extern unsigned char koi8r_8x16[];


byte *gfxdev_outbuf;	//information to be returned from some commands
int gfxdev_outbuf_pos;

// conceptually the point will be an integer 1/72' (~0.3mm) this will allow about 941.5 x 941.5 miles plane space
// I am considering using 8.24 fixed point math (which may require assembler).

//int gfxdev_matrix[16]; /* 4x4 translation */

int gfxdev_cursor_x;
int gfxdev_cursor_y;

int gfxdev_textsize_x;
int gfxdev_textsize_y;

int gfxdev_textcolor_r;
int gfxdev_textcolor_g;
int gfxdev_textcolor_b;
int gfxdev_textcolor_a;

float gfxdev_vecbuf[12]; //x y z s t r g b a
float gfxdev_matbuf[16];

int gfxdev_lastlight=0;

int GfxDev_Translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
	return(0);
}

int GfxDev_Scale(float x, float y, float z)
{
	glScalef(x, y, z);
	return(0);
}

int GfxDev_SetPerspective_3D(int fovx, int fovy)
{
	GLdouble xmin, xmax, ymin, ymax, dst;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

	dst=0.1;

	xmax = dst*tan(fovx*(M_PI/360.0));
	xmin = -xmax;

	ymax = dst*tan(fovy*(M_PI/360.0));
	ymin = -ymax;

	glFrustum  (xmin, xmax, ymin, ymax, dst, 100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

//	glFrustum  (xmin, xmax, ymin, ymax, dst, 100000);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

//	glEnable (GL_CULL_FACE);
//	glCullFace (GL_FRONT);
//	glFrontFace (GL_CCW);

//	glDisable(GL_SCISSOR_TEST);

//	glDisable (GL_CULL_FACE);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor4f (0,0,0,1);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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

int GfxDev_Key_Event(int k, int s)
{
//	Key_Event(k, s);
	keyb_handler(NULL, k, s);
}

int gfxdev_opcode(int op, byte *s)
{
	int *st;
	double *stf;
	byte *t, *t2;
	u2 *tu;
	int i, bx, by;
	float pt[4];

	switch(op)
	{
	case GFXOP_NOP:
		break;
	case GFXOP_BEGINDRAWING:
//		GfxDev_SetMatDef();
		GfxFont_SetFont("fixed");
		GfxDrv_BeginDrawing();
		if(gfxdev_lastlight>1)
		{
			for(i=0; i<gfxdev_lastlight; i++)
				glDisable(GL_LIGHT0+i);
			glDisable(GL_LIGHTING);
			gfxdev_lastlight=1;
		}
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

#if 0
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
#endif

		GfxDrv_FillSquare(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7]);
		break;

	case GFXOP_MOVETO:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;

//		kprint("in coords (%d %d) (%d %d)\n", st[0], st[1], st[2], st[3]);
//		GfxDev_TransVec2D(st);
		gfxdev_cursor_x=st[0];
		gfxdev_cursor_y=st[1];
		break;

	case GFXOP_SHOW:
		gfx_stackpos--;
		st=gfx_stack+gfx_stackpos;
		tu=(u2 *)st[0];

		bx=gfxdev_cursor_x;
		by=gfxdev_cursor_y;

		while(*tu)
		{
			if(*tu<' ')switch(*tu)
			{
			case '\n':
				gfxdev_cursor_x=bx;
				gfxdev_cursor_y-=gfxdev_textsize_y;
				break;
			default:
				break;
			}else
			{
				GfxFont_DrawChar((int)*tu&0xffff,
					gfxdev_cursor_x, gfxdev_cursor_y,
					gfxdev_textsize_x, gfxdev_textsize_y,
					gfxdev_textcolor_r, gfxdev_textcolor_g,
					gfxdev_textcolor_b, gfxdev_textcolor_a);
				gfxdev_cursor_x+=gfxdev_textsize_x;
			}
			tu++;
		}
		kfree((void *)st[0]);
		break;

	case GFXOP_FONTSIZE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;

		i=st[0];
//		i=mul_824(gfxdev_matrix[0], st[0]);
		gfxdev_textsize_x=i;

		i=st[1];
//		i=mul_824(-gfxdev_matrix[5], st[1]);
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
		kfree(t);
		kfree((void *)st[0]);
		break;

	case GFXOP_TRANSLATE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;
		GfxDev_Translate(st[0], st[1], 0);
		break;

	case GFXOP_SCALE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;
		GfxDev_Scale(st[0]/16777216.0, st[1]/16777216.0, 0);
		break;

	case GFXOP_SETRANGE:
		gfx_stackpos-=4;
		st=gfx_stack+gfx_stackpos;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(st[0], st[1], st[2], st[3], -9999, 9999);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;

	case GFXOP_PUSHMATRIX:
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		break;

	case GFXOP_POPMATRIX:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

		break;

	case GFXOP_PUSHCLIP:
//		Draw_PushClip();
		break;

	case GFXOP_POPCLIP:
//		Draw_PopClip();
		break;

	case GFXOP_SETCLIP2:
		gfx_stackpos-=2;
		stf=gfx_stackf+gfx_stackpos;
//		Draw_SetClip(stf[0], stf[1]);
		break;

	case GFXOP_TRANSLATE3:
		gfx_stackpos-=3;
		stf=gfx_stackf+gfx_stackpos;
		GfxDev_Translate(stf[0], stf[1], stf[2]);
		break;

	case GFXOP_SCALE3:
		gfx_stackpos-=3;
		stf=gfx_stackf+gfx_stackpos;
		GfxDev_Scale(stf[0], stf[1], stf[2]);
		break;

	case GFXOP_ROT3:
		gfx_stackpos-=4;
		stf=gfx_stackf+gfx_stackpos;
		glRotated(stf[3], stf[0], stf[1], stf[2]);
		break;

	case GFXOP_PERSPECTIVE:
		gfx_stackpos-=2;
		st=gfx_stack+gfx_stackpos;

		GfxDev_SetPerspective_3D(st[0], st[1]);

		break;

	case GFXOP_VEC3:
		gfx_stackpos-=3;
		stf=gfx_stackf+gfx_stackpos;

//		printf("v %f %f %f\n", stf[0], stf[1], stf[2]);
		gfxdev_vecbuf[0]=stf[0];
		gfxdev_vecbuf[1]=stf[1];
		gfxdev_vecbuf[2]=stf[2];
		break;

	case GFXOP_STCOORDS:
		gfx_stackpos-=2;
		stf=gfx_stackf+gfx_stackpos;
		gfxdev_vecbuf[3]=stf[0];
		gfxdev_vecbuf[4]=stf[1];
		break;

	case GFXOP_COLOR:
		gfx_stackpos-=4;
		stf=gfx_stackf+gfx_stackpos;

//		printf("c %f %f %f %f\n", stf[0], stf[1], stf[2], stf[3]);

		gfxdev_vecbuf[5]=stf[0]/255.0;
		gfxdev_vecbuf[6]=stf[1]/255.0;
		gfxdev_vecbuf[7]=stf[2]/255.0;
		gfxdev_vecbuf[8]=stf[3]/255.0;
		break;

	case GFXOP_POINT:
//		printf("point\n");
		glColor4f(gfxdev_vecbuf[5], gfxdev_vecbuf[6],
			gfxdev_vecbuf[7], gfxdev_vecbuf[8]);
		glTexCoord2f(gfxdev_vecbuf[3], gfxdev_vecbuf[4]);
		glVertex3f(gfxdev_vecbuf[0], gfxdev_vecbuf[1],
			gfxdev_vecbuf[2]);
		break;

	case GFXOP_BEGIN:
		gfx_stackpos-=1;
		st=gfx_stack+gfx_stackpos;
//		printf("begin\n");
		switch(st[0])
		{
		case GFXVAR_POLYGON:
//			glDisable(GL_TEXTURE_2D);
			glBegin(GL_POLYGON);
			break;
		default:
			break;
		}
		break;

	case GFXOP_END:
		gfx_stackpos-=1;
		st=gfx_stack+gfx_stackpos;
//		printf("end\n");
		switch(st[0])
		{
		case GFXVAR_POLYGON:
			glEnd();
			break;
		default:
			break;
		}
		break;

	case GFXOP_TEXTURE:
		gfx_stackpos-=5;
		st=gfx_stack+gfx_stackpos;
		i=Tex_LoadTexture2(st[2], st[3], st[0], 1, st[1], st[4]);
		kfree((void *)st[0]);

		st[0]=i;
		gfx_stackpos++;
		break;

	case GFXOP_BINDTEX:
		gfx_stackpos-=1;
		st=gfx_stack+gfx_stackpos;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, st[0]);
		break;

	case GFXOP_UNBINDTEX:
		glDisable(GL_TEXTURE_2D);
		break;

	case GFXOP_MATRIX:
		gfx_stackpos-=16;
		stf=gfx_stackf+gfx_stackpos;

		for(i=0; i<4; i++)
		{
			gfxdev_matbuf[(i*4)+0]=stf[(0*4)+i];
			gfxdev_matbuf[(i*4)+1]=stf[(1*4)+i];
			gfxdev_matbuf[(i*4)+2]=stf[(2*4)+i];
			gfxdev_matbuf[(i*4)+3]=stf[(3*4)+i];
		}
		break;

	case GFXOP_MATMULT:
		glMultMatrixf(gfxdev_matbuf);
		break;

	case GFXOP_ADDLIGHT:
		i=gfxdev_lastlight++;

//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		pt[0]=gfxdev_vecbuf[0];
		pt[1]=gfxdev_vecbuf[1];
		pt[2]=gfxdev_vecbuf[2];
		pt[3]=1;
		glLightfv(GL_LIGHT0+i, GL_POSITION, pt);

		pt[0]=gfxdev_vecbuf[5];
		pt[1]=gfxdev_vecbuf[6];
		pt[2]=gfxdev_vecbuf[7];
		pt[3]=1;
		glLightfv(GL_LIGHT0+i, GL_DIFFUSE, pt);

//		glLightf(GL_LIGHT0+i, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT0+i, GL_QUADRATIC_ATTENUATION,
			1/gfxdev_vecbuf[8]);

		glEnable(GL_LIGHT0+i);

//		glColor4f(gfxdev_vecbuf[5], gfxdev_vecbuf[6],
//			gfxdev_vecbuf[7], gfxdev_vecbuf[8]);
//		glTexCoord2f(gfxdev_vecbuf[3], gfxdev_vecbuf[4]);
//		glVertex3f(gfxdev_vecbuf[0], gfxdev_vecbuf[1],
//			gfxdev_vecbuf[2]);

		st=gfx_stack+gfx_stackpos;
		st[0]=i;
		gfx_stackpos++;

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
		2=float
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
	2: data object
		followed by byte encoding and 32 bit length.
		data may be broken into multiple writes.
*/

int gfxdev_write(void *buf, int len, VFILE *fd)
{
	byte *s, *e, *t;
	u2 *su, *tu, *tu2;
	int sg, st, st2[2], i;
	double stf;

	static int rlen, renc; //remaining data to recieve, encoding
	static byte *rbuf, *erbuf; //recieve buffer and end recieve buf

	s=buf;
	e=s+len;

	while(s<e)
	{

		if(rlen)
		{
			st=e-s;
			i=(st<rlen)?st:rlen;
			memcpy(erbuf, s, i);
			s+=i;
			erbuf+=i;
			rlen-=i;

			if(!rlen)
				gfx_stack[gfx_stackpos++]=(int)rbuf;
			continue;
		}

		switch(*s&3)
		{
		case 0:
			sg=(*s>>3)&7;
			if((sg==0) || (sg==1))
				switch((*s>>6)&3)
			{
			case 0:
				if(sg)st=((signed char *)s)[1];
					else st=((unsigned char *)s)[1];
				stf=st;
				s+=2;
				break;
			case 1:
				st=(s[1]<<8)+s[2];
				if(sg && (st>32767))st|=~0xFFFF;
				stf=st;
				s+=3;
				break;
			case 2:
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				if(sg && (st>(1<<31)))st|=~0xFFFFFFFF;
				stf=st;
				s+=5;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			if(sg==2)switch((*s>>6)&3)
			{
			case 2:
				st=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				stf=*(float *)&st;
				st=stf;
				s+=5;
				break;
			case 3:
				st2[1]=(s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4];
				st2[0]=(s[5]<<24)+(s[6]<<16)+(s[7]<<8)+s[8];
				stf=*(double *)&st2;
				st=stf;
				s+=9;
				break;
			default:
				kprint("GfxDev: number parse error.\n");
				return((int)s-(int)buf);
				break;
			}
			gfx_stack[gfx_stackpos]=st;
			gfx_stackf[gfx_stackpos++]=stf;
			break;
		case 1:
			st=((s[0]>>4)&15)+(s[1]<<4);
			s+=2;
			if(gfxdev_opcode(st, s)<0)return((int)s-(int)buf);
			break;
		case 2:
			switch((*s>>3)&31)
			{
			case 3:
				st=(s[1]<<8)+s[2];

				tu=kalloc((st*2)+2);
//				strncpy(t, s+2, s[1]);

				su=(u2 *)(s+3);
				tu2=tu;
				i=st;
				while(i--)*tu2++=*su++;
				*tu2++=0;
				s+=(st*2)+3;
				gfx_stack[gfx_stackpos++]=(int)tu;
//				kprint("parsed string \"%s\"\n", GfxDev_Uni2Asc(tu));
				break;

			case 1:
				renc=s[1];
				st=(s[2]<<24)+(s[3]<<16)+(s[4]<<8)+s[5];
				rlen=st;
				rbuf=kalloc(rlen);
				erbuf=rbuf;
				s+=6;
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
	VFILE *tmp, *tmp2;
	int i;
	byte *buf;

	tmp=gfx_device;
	if(!tmp)
	{
		GfxDrv_Start();
		GfxFont_Init();

//		tmp=vfnew();
		vfpipe(&tmp, &tmp2);

		tmp->write_proc=gfxdev_write;
		tmp->read_proc=gfxdev_read;
//		tmp->seek_proc=gfxdev_seek;
//		tmp->flush_proc=gfxdev_flush;
//		tmp->ioctls_proc=gfxdev_ioctls;
		gfx_device=tmp;
		gfx_other=tmp2;

		gfx_stack=kalloc(1024*sizeof(int));
		gfx_stackf=kalloc(1024*sizeof(double));
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
	Tex_Init2();

	mul_824(1, -1<<23);
	mul_824(256, -1<<23);
	mul_824(-1, 1<<23);
	mul_824(-256, 1<<23);

	mul_824(-256, -1<<23);
}
