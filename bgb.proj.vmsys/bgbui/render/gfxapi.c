#include <general.h>
#include <graphics/render.h>

int GfxApi_WriteUByte(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=0;
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int GfxApi_WriteSByte(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=8;
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int GfxApi_WriteUShort(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=64;
	*s++=(v>>8)&255;
	*s++=v&255;
	vfwrite(buf, 1, 3, fd);
	return(0);
}

int GfxApi_WriteSShort(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=64+8;
	*s++=(v>>8)&255;
	*s++=v&255;
	vfwrite(buf, 1, 3, fd);
	return(0);
}

int GfxApi_WriteULong(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=128;
	*s++=(v>>24)&255;
	*s++=(v>>16)&255;
	*s++=(v>>8)&255;
	*s++=v&255;
	vfwrite(buf, 1, 5, fd);
	return(0);
}

int GfxApi_WriteSLong(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=128+8;
	*s++=(v>>24)&255;
	*s++=(v>>16)&255;
	*s++=(v>>8)&255;
	*s++=v&255;
	vfwrite(buf, 1, 5, fd);
	return(0);
}

int GfxApi_WriteUInt(VFILE *fd, int v)
{
	if(v<256)return(GfxApi_WriteUByte(fd, v));
	if(v<65536)return(GfxApi_WriteUShort(fd, v));
	return(GfxApi_WriteULong(fd, v));
}

int GfxApi_WriteSInt(VFILE *fd, int v)
{
	int r;

	if(v>0)r=v;
		else r=0-v;

	if(r<127)return(GfxApi_WriteSByte(fd, v));
	if(r<32767)return(GfxApi_WriteSShort(fd, v));
	return(GfxApi_WriteSLong(fd, v));
}

int GfxApi_WriteFloat(VFILE *fd, float f)
{
	char buf[8];
	char *s;
	int v;

	v=*(int *)&f;

	s=buf;
	*s++=128+16;
	*s++=(v>>24)&255;
	*s++=(v>>16)&255;
	*s++=(v>>8)&255;
	*s++=v&255;
	vfwrite(buf, 1, 5, fd);
	return(0);
}

int GfxApi_WriteDouble(VFILE *fd, double f)
{
	char buf[16];
	char *s;
	int v[2];

	v[0]=((int *)&f)[0];
	v[1]=((int *)&f)[1];

	s=buf;
	*s++=192+16;

	*s++=(v[0]>>24)&255;
	*s++=(v[0]>>16)&255;
	*s++=(v[0]>>8)&255;
	*s++=v[0]&255;

	*s++=(v[1]>>24)&255;
	*s++=(v[1]>>16)&255;
	*s++=(v[1]>>8)&255;
	*s++=v[1]&255;

	vfwrite(buf, 1, 9, fd);
	return(0);
}

int GfxApi_ReadULong(VFILE *fd)
{
	char buf[8];
	byte *s;

//	*s++=128;
//	*s++=(v>>24)&255;
//	*s++=(v>>16)&255;
//	*s++=(v>>8)&255;
//	*s++=v&255;

	vfread(buf, 1, 5, fd);
	s=buf;
	return((s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4]);
}

int GfxApi_ReadSLong(VFILE *fd)
{
	char buf[8];
	byte *s;

//	s=buf;
//	*s++=128+8;
//	*s++=(v>>24)&255;
//	*s++=(v>>16)&255;
//	*s++=(v>>8)&255;
//	*s++=v&255;
//	vfwrite(buf, 1, 5, fd);
//	return(0);

	vfread(buf, 1, 5, fd);
	s=buf;
	return((s[1]<<24)+(s[2]<<16)+(s[3]<<8)+s[4]);
}

int GfxApi_WriteOpcode(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=1+((v<<4)&0xF0);
	*s++=(v>>4)&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int GfxApi_WriteString(VFILE *fd, char *t)
{
	char *buf;
	char *s;
	int l;

	l=strlen(t);

	buf=kralloc(((l+1)*2)+3);

	s=buf;
	*s++=(3<<3)+2;

	*s++=(l>>8)&0xff;
	*s++=l&0xff;

//	strcpy(s, t);

//	kprint("write string \"%s\"\n", t);

	while(*t)
	{
		*s++=*t++;
		*s++=0;
	}

	vfwrite(buf, 1, (l*2)+3, fd);

//	kfree(buf);

	return(0);
}


int GfxApi_WriteStringU2(VFILE *fd, u2 *t)
{
	char *buf;
	char *s;
	u2 *t2;
	int i;

	t2=t;
	i=0;
	while(*t2++)i++;

	buf=kralloc(((i+1)*2)+3);

	s=buf;
	*s++=(3<<3)+2;

	*s++=(i>>8)&0xff;
	*s++=i&0xff;
//	strcpy(s, t);

//	kprint("write string \"%s\"\n", t);

	t2=t;
	while(*t2)
	{
		*s++=*t2&0xff;
		*s++=*t2>>8;
		t2++;
	}

	vfwrite(buf, 1, (i*2)+3, fd);
//	kfree(buf);

	return(0);
}

int GfxApi_WriteData(VFILE *fd, byte *t, int len, int enc)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=(1<<3)+2;
	*s++=enc;

	*s++=(len>>24)&255;
	*s++=(len>>16)&255;
	*s++=(len>>8)&255;
	*s++=len&255;

	vfwrite(buf, 1, 6, fd);
	vfwrite(t, 1, len, fd); //data can be sent in multiple chunks

	return(0);
}

int GfxApi_WriteSymbol(VFILE *fd, char *t)
{
	char buf[256];
	char *s;
	int l;

	s=buf;
	*s++=(2<<3)+2;

	l=strlen(t);
//	*s++=(l>>8)&0xff;
	*s++=l&0xff;

//	strcpy(s, t);

//	kprint("write string \"%s\"\n", t);

	while(*t)
	{
		*s++=*t++;
//		*s++=0;
	}

	vfwrite(buf, 1, l+2, fd);
	return(0);
}

int GfxApi_WriteParam(VFILE *fd, char *t)
{
	char buf[256];
	char *s;
	int l;

	s=buf;
	*s++=(4<<3)+2;

	l=strlen(t);
	*s++=(l>>8)&0xff;
	*s++=l&0xff;

	strcpy(s, t);
	s+=l;

//	kprint("write param \"%s\"\n", t);

	vfwrite(buf, 1, l+3, fd);
	return(0);
}

int GfxApi_WriteConst(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=(4<<3);
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

//
// compound types and commands
//

int GfxApi_WriteVertex3fv(VFILE *fd, float *v)
{
	GfxApi_WriteFloat(fd, v[0]);
	GfxApi_WriteFloat(fd, v[1]);
	GfxApi_WriteFloat(fd, v[2]);
}


int GfxApi_FillSquare(VFILE *fd, int x, int y, int w, int h, int r, int g, int b, int a)
{
	GfxApi_WriteSLong(fd, x);
	GfxApi_WriteSLong(fd, y);
	GfxApi_WriteSLong(fd, w);
	GfxApi_WriteSLong(fd, h);
	GfxApi_WriteUByte(fd, r);
	GfxApi_WriteUByte(fd, g);
	GfxApi_WriteUByte(fd, b);
	GfxApi_WriteUByte(fd, a);

	GfxApi_WriteOpcode(fd, GFXOP_FILLSQUARE);

	return(0);
}

int GfxApi_MoveTo(VFILE *fd, int x, int y)
{
	GfxApi_WriteSLong(fd, x);
	GfxApi_WriteSLong(fd, y);
	GfxApi_WriteOpcode(fd, GFXOP_MOVETO);
	return(0);
}

int GfxApi_Show(VFILE *fd, char *s)
{
	GfxApi_WriteString(fd, s);
	GfxApi_WriteOpcode(fd, GFXOP_SHOW);
	return(0);
}

int GfxApi_ShowU2(VFILE *fd, u2 *s)
{
	GfxApi_WriteStringU2(fd, s);
	GfxApi_WriteOpcode(fd, GFXOP_SHOW);
	return(0);
}

int GfxApi_FontSize(VFILE *fd, int sz)
{
	GfxApi_WriteSLong(fd, sz/2);
	GfxApi_WriteSLong(fd, sz);
	GfxApi_WriteOpcode(fd, GFXOP_FONTSIZE);
	return(0);
}

int GfxApi_FontSize2(VFILE *fd, int xsz, int ysz)
{
	GfxApi_WriteSLong(fd, xsz);
	GfxApi_WriteSLong(fd, ysz);
	GfxApi_WriteOpcode(fd, GFXOP_FONTSIZE);
	return(0);
}

int GfxApi_TextColor(VFILE *fd, int r, int g, int b, int a)
{
	GfxApi_WriteSLong(fd, r);
	GfxApi_WriteSLong(fd, g);
	GfxApi_WriteSLong(fd, b);
	GfxApi_WriteSLong(fd, a);
	GfxApi_WriteOpcode(fd, GFXOP_TEXTCOLOR);
	return(0);
}

int GfxApi_SetFont(VFILE *fd, char *s)
{
	GfxApi_WriteString(fd, s);
	GfxApi_WriteOpcode(fd, GFXOP_SETFONT);
	return(0);
}

int GfxApi_ConvCoords(VFILE *fd, int x, int y, int *rx, int *ry)
{
	GfxApi_WriteSLong(fd, x);
	GfxApi_WriteSLong(fd, y);
	GfxApi_WriteOpcode(fd, GFXOP_RTRANS2D);
	GfxApi_WriteOpcode(fd, GFXOP_POPRET);
	*ry=GfxApi_ReadSLong(fd);
	GfxApi_WriteOpcode(fd, GFXOP_POPRET);
	*rx=GfxApi_ReadSLong(fd);

	return(0);
}

int GfxApi_Translate(VFILE *fd, int x, int y)
{
	GfxApi_WriteSLong(fd, x);
	GfxApi_WriteSLong(fd, y);
	GfxApi_WriteOpcode(fd, GFXOP_TRANSLATE);
	return(0);
}

int GfxApi_Scale(VFILE *fd, float x, float y)
{
	GfxApi_WriteSLong(fd, x*(1<<24));
	GfxApi_WriteSLong(fd, y*(1<<24));
	GfxApi_WriteOpcode(fd, GFXOP_SCALE);
	return(0);
}

int GfxApi_SetRange(VFILE *fd, int left, int right, int bottom, int top)
{
	GfxApi_WriteSLong(fd, left);
	GfxApi_WriteSLong(fd, right);
	GfxApi_WriteSLong(fd, bottom);
	GfxApi_WriteSLong(fd, top);
	GfxApi_WriteOpcode(fd, GFXOP_SETRANGE);
	return(0);
}

int GfxApi_PushMatrix(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_PUSHMATRIX);
	return(0);
}

int GfxApi_PopMatrix(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_POPMATRIX);
	return(0);
}

int GfxApi_BeginDrawing(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_BEGINDRAWING);
	return(0);
}

int GfxApi_EndDrawing(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_ENDDRAWING);
	return(0);
}

int GfxApi_PushClip(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_PUSHCLIP);
	return(0);
}

int GfxApi_PopClip(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_POPCLIP);
	return(0);
}

int GfxApi_SetClip(VFILE *fd, float x1, float y1, float x2, float y2)
{
	GfxApi_WriteFloat(fd, x1);
	GfxApi_WriteFloat(fd, y1);
	GfxApi_WriteFloat(fd, x2);
	GfxApi_WriteFloat(fd, y2);
	GfxApi_WriteOpcode(fd, GFXOP_SETCLIP2);
	return(0);
}

int GfxApi_Translate3(VFILE *fd, float x, float y, float z)
{
	GfxApi_WriteFloat(fd, x);
	GfxApi_WriteFloat(fd, y);
	GfxApi_WriteFloat(fd, z);
	GfxApi_WriteOpcode(fd, GFXOP_TRANSLATE3);
	return(0);
}

int GfxApi_Scale3(VFILE *fd, float x, float y, float z)
{
	GfxApi_WriteFloat(fd, x);
	GfxApi_WriteFloat(fd, y);
	GfxApi_WriteFloat(fd, z);
	GfxApi_WriteOpcode(fd, GFXOP_SCALE3);
	return(0);
}

int GfxApi_Rotate3(VFILE *fd, float x, float y, float z, float a)
{
	GfxApi_WriteFloat(fd, x);
	GfxApi_WriteFloat(fd, y);
	GfxApi_WriteFloat(fd, z);
	GfxApi_WriteFloat(fd, a);
	GfxApi_WriteOpcode(fd, GFXOP_ROT3);
	return(0);
}

int GfxApi_Perspective(VFILE *fd, int fovx, int fovy)
{
	GfxApi_WriteSInt(fd, fovx);
	GfxApi_WriteSInt(fd, fovy);
	GfxApi_WriteOpcode(fd, GFXOP_PERSPECTIVE);
	return(0);
}

int GfxApi_Color(VFILE *fd, float r, float g, float b, float a)
{
	GfxApi_WriteFloat(fd, r);
	GfxApi_WriteFloat(fd, g);
	GfxApi_WriteFloat(fd, b);
	GfxApi_WriteFloat(fd, a);
	GfxApi_WriteOpcode(fd, GFXOP_COLOR);
	return(0);
}

int GfxApi_Vec3(VFILE *fd, float x, float y, float z)
{
	GfxApi_WriteFloat(fd, x);
	GfxApi_WriteFloat(fd, y);
	GfxApi_WriteFloat(fd, z);
	GfxApi_WriteOpcode(fd, GFXOP_VEC3);
	return(0);
}

int GfxApi_TexCoord2(VFILE *fd, float s, float t)
{
	GfxApi_WriteFloat(fd, s);
	GfxApi_WriteFloat(fd, t);
	GfxApi_WriteOpcode(fd, GFXOP_STCOORDS);
	return(0);
}

int GfxApi_Point(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_POINT);
	return(0);
}

int GfxApi_Begin(VFILE *fd, int t)
{
	GfxApi_WriteSInt(fd, t);
	GfxApi_WriteOpcode(fd, GFXOP_BEGIN);
	return(0);
}

int GfxApi_End(VFILE *fd, int t)
{
	GfxApi_WriteSInt(fd, t);
	GfxApi_WriteOpcode(fd, GFXOP_END);
	return(0);
}

int GfxApi_BindTex(VFILE *fd, int t)
{
	GfxApi_WriteSInt(fd, t);
	GfxApi_WriteOpcode(fd, GFXOP_BINDTEX);
	return(0);
}

int GfxApi_UnbindTex(VFILE *fd)
{
	GfxApi_WriteOpcode(fd, GFXOP_UNBINDTEX);
	return(0);
}

int GfxApi_Texture(VFILE *fd, byte *data, int num, int w, int h, int enc)
{
	int t;

	GfxApi_WriteData(fd, data, w*h*4, GFXVAR_RAW);
	GfxApi_WriteSInt(fd, num);
	GfxApi_WriteSInt(fd, w);
	GfxApi_WriteSInt(fd, h);
	GfxApi_WriteSInt(fd, enc);
	GfxApi_WriteOpcode(fd, GFXOP_TEXTURE);

	GfxApi_WriteOpcode(fd, GFXOP_POPRET);
	t=GfxApi_ReadSLong(fd);

	return(t);
}

int GfxApi_TransformMatrix(VFILE *fd, float *mat)
{
	int i;

	for(i=0; i<16; i++)
		GfxApi_WriteFloat(fd, mat[i]);

	GfxApi_WriteOpcode(fd, GFXOP_MATRIX);

	GfxApi_WriteOpcode(fd, GFXOP_MATMULT);

	return(0);
}

int GfxApi_TransformMatrixd(VFILE *fd, double *mat)
{
	int i;

	for(i=0; i<16; i++)
		GfxApi_WriteFloat(fd, mat[i]);

	GfxApi_WriteOpcode(fd, GFXOP_MATRIX);

	GfxApi_WriteOpcode(fd, GFXOP_MATMULT);

	return(0);
}

int GfxApi_Light(VFILE *fd)
{
	int t;

	GfxApi_WriteOpcode(fd, GFXOP_ADDLIGHT);

	GfxApi_WriteOpcode(fd, GFXOP_POPRET);
	t=GfxApi_ReadSLong(fd);

	return(t);
}
