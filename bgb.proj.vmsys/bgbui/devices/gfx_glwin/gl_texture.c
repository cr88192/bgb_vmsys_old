#include <general.h>
//#include <graphics/render.h>

#include <GL/GL.h>
#include <math.h>
#include <scmcc.h>

//typedef unsigned char byte;

//allows small textures to be grouped into bigger ones
#define TEXBLOCKS	4
byte texblock[TEXBLOCKS*256*256*4], texblockfl[TEXBLOCKS*4*4];
int texblocknum[TEXBLOCKS];

#define MAX_GLTEXTURES 16384
unsigned char texturebm[MAX_GLTEXTURES/8];
int lasttexture;
short tex_width[MAX_GLTEXTURES], tex_height[MAX_GLTEXTURES];

elem gl_texfilter_var=MISC_NULL;

struct
{
	char *name;
	int	min, mag;
} texmodes[] = {
	{"GL_NEAREST", GL_NEAREST, GL_NEAREST},
	{"GL_LINEAR", GL_LINEAR, GL_LINEAR},
	{"GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST},
	{"GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR},
	{"GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST},
	{"GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR},
	{NULL, 0, 0}
};

int Tex_GetModeinfo(int *min, int *mag)
{
	int i;

	*min=GL_NEAREST;
	*mag=GL_NEAREST;

	for(i=0; i<6; i++)if(!strcmp(ELEM_TOSTRING(gl_texfilter_var), texmodes[i].name))
	{
		*min=texmodes[i].min;
		*mag=texmodes[i].mag;
	}
	return(0);
}

int Tex_Init2()
{
	printf("GL_Textures Init.\n");
	MMGC3_AddRoot(&gl_texfilter_var);
//	gl_texfilter_var=Var_SetString("gl_texfilter", "GL_LINEAR_MIPMAP_LINEAR");
	gl_texfilter_var=STRING("GL_LINEAR_MIPMAP_LINEAR");
//	gl_texfilter_var=STRING("GL_NEAREST");

	memset(texblockfl, 0, TEXBLOCKS*16);
//	memset(texturebm, 0, MAX_GLTEXTURES/8);
	lasttexture=1;
	return(0);
}

int Tex_AllocTexnum()
{
	int i;
	i=lasttexture+1;
	while(1)
	{
		if(!(texturebm[i>>3]&(1<<(i&7))))
		{
			texturebm[i>>3]|=1<<(i&7);
			lasttexture=i;
			return(i);
		}
		i++;
		if(i==lasttexture)
			return(-1);
	}
}

int Tex_FreeTexnum(int n)
{
	texturebm[n>>3]&=~(1<<(n&7));
	return(0);
}

int Tex_MarkTexnum(int n)
{
	texturebm[n>>3]|=(1<<(n&7));
	return(0);
}

int Tex_AllocBlock(int *x, int *y, int *b)
{
	int i, j, k;
	for(i=0; i<TEXBLOCKS; i++)
		for(j=0; j<4; j++)
			for(k=0; k<4; k++)
	{
		if(!texblockfl[(i*16)+(j*4)+k])
		{
			*x=k;
			*y=j;
			*b=i;
			return(0);
		}
	}
	return(-1);
}

int Tex_Resample(byte *src, int iw, int ih, byte *dst, int ow, int oh)
{
	int i, j, ix, iy;
	for(i=0; i<oh; i++)
	{
		iy=((float)ih/(float)oh)*i;
		for(j=0; j<ow; j++)
		{
			ix=((float)iw/(float)ow)*j;
			dst[(i*ow+j)*4+0]=src[(iy*iw+ix)*4+0];
			dst[(i*ow+j)*4+1]=src[(iy*iw+ix)*4+1];
			dst[(i*ow+j)*4+2]=src[(iy*iw+ix)*4+2];
			dst[(i*ow+j)*4+3]=src[(iy*iw+ix)*4+3];
		}
	}
	return(0);
}

int Tex_HalfSample(byte *src, int w, int h)
{
	int i, j, w2, h2, i2, j2;

	w2=w>>1;
	h2=h>>1;
	for(i=0;i<h2; i++)
		for(j=0; j<w2; j++)
	{
		i2=i<<1;
		j2=j<<1;
		src[((i*w2+j)<<2)+0]=
			(src[((i2*w+j2)<<2)+0]+		src[((i2*w+(j2+1))<<2)+0]+
			src[(((i2+1)*w+j2)<<2)+0]+	src[(((i2+1)*w+(j2+1))<<2)+0])>>2;

		src[((i*w2+j)<<2)+1]=
			(src[((i2*w+j2)<<2)+1]+		src[((i2*w+(j2+1))<<2)+1]+
			src[(((i2+1)*w+j2)<<2)+1]+	src[(((i2+1)*w+(j2+1))<<2)+1])>>2;

		src[((i*w2+j)<<2)+2]=
			(src[((i2*w+j2)<<2)+2]+		src[((i2*w+(j2+1))<<2)+2]+
			src[(((i2+1)*w+j2)<<2)+2]+	src[(((i2+1)*w+(j2+1))<<2)+2])>>2;

		src[((i*w2+j)<<2)+3]=
			(src[((i2*w+j2)<<2)+3]+		src[((i2*w+(j2+1))<<2)+3]+
			src[(((i2+1)*w+j2)<<2)+3]+	src[(((i2+1)*w+(j2+1))<<2)+3])>>2;
	}
}

int Tex_HalfSample2(byte *src, int w, int h)
{
	int i, j, w2, h2, i2, j2;

	w2=w>>1;
	h2=h>>1;
	for(i=0;i<h2; i++)
		for(j=0; j<w2; j++)
	{
		i2=i<<1;
		j2=j<<1;
		src[((i*w2+j)<<2)+0]=
			(src[((i2*w+j2)<<2)+0]+		src[((i2*w+(j2+1))<<2)+0]+
			src[(((i2+1)*w+j2)<<2)+0]+	src[(((i2+1)*w+(j2+1))<<2)+0]);

		src[((i*w2+j)<<2)+1]=
			(src[((i2*w+j2)<<2)+1]+		src[((i2*w+(j2+1))<<2)+1]+
			src[(((i2+1)*w+j2)<<2)+1]+	src[(((i2+1)*w+(j2+1))<<2)+1]);

		src[((i*w2+j)<<2)+2]=
			(src[((i2*w+j2)<<2)+2]+		src[((i2*w+(j2+1))<<2)+2]+
			src[(((i2+1)*w+j2)<<2)+2]+	src[(((i2+1)*w+(j2+1))<<2)+2]);

		src[((i*w2+j)<<2)+3]=
			(src[((i2*w+j2)<<2)+3]+		src[((i2*w+(j2+1))<<2)+3]+
			src[(((i2+1)*w+j2)<<2)+3]+	src[(((i2+1)*w+(j2+1))<<2)+3]);
	}
}

int Tex_LoadTexture(int w, int h, byte *buf, int calcmip)
{
	static byte resampbuf[2048*2048*4];
	int tw, th, tl;
	int min, mag;
	int num;

	tw=1;
	th=1;
	while((tw<<1)<=w)tw<<=1;
	while((th<<1)<=h)th<<=1;
	if(tw<w && (tw<<1)>w)tw<<=1;
	if(th<h && (th<<1)>h)th<<=1;
//	if(tw>256)tw=256;
//	if(th>256)th=256;

	if(tw<th)tw=th;
	if(th<tw)th=tw;

	if((w!=tw) || (h!=th))Tex_Resample(buf, w, h, resampbuf, tw, th);
		else memcpy(resampbuf, buf, w*h*4);

	num=Tex_AllocTexnum();
	tex_width[num]=w;
	tex_height[num]=h;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, num);

	glTexImage2D (GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);

	if(!calcmip)
	{
//		printf("tex: nonmip\n");
//		glTexImage2D (GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);
		Tex_GetModeinfo(&min, &mag);

//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}else
	{
//		printf("tex: mipmap\n");
		tl=0;
		while(tw>1 && th>1)
		{
			Tex_HalfSample(resampbuf, tw, th);
			tw>>=1;
			th>>=1;
			tl++;
			glTexImage2D (GL_TEXTURE_2D, tl, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);
		}

		Tex_GetModeinfo(&min, &mag);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	return(num);
}

int Tex_LoadTexture2(int w, int h, byte *buf, int mip, int rnum, int enc)
{
//	static byte resampbuf[2048*2048*4];
	byte *resampbuf;
	int tw, th, tl;
	int min, mag;
	int num;

	resampbuf=malloc(2048*2048*4);

	tw=1;
	th=1;
	while((tw<<1)<=w)tw<<=1;
	while((th<<1)<=h)th<<=1;
	if(tw<w && (tw<<1)>w)tw<<=1;
	if(th<h && (th<<1)>h)th<<=1;

	if(tw<th)tw=th;
	if(th<tw)th=tw;

#if 0
	if(mip==2)
	{
		tw<<=1;
		th<<=1;
	}
#endif

	if((w!=tw) || (h!=th))Tex_Resample(buf, w, h, resampbuf, tw, th);
		else memcpy(resampbuf, buf, w*h*4);

	num=rnum;
	if(!num)num=Tex_AllocTexnum();

	tex_width[num]=w;
	tex_height[num]=h;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, num);

	glTexImage2D (GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);

	if(!mip)
	{
//		printf("tex: nonmip\n");
		glTexImage2D (GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);
		Tex_GetModeinfo(&min, &mag);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}else if(mip==2)
	{
		tl=0;
		while(tw>1 && th>1)
		{
			Tex_HalfSample2(resampbuf, tw, th);
			tw>>=1;
			th>>=1;
			tl++;
			glTexImage2D (GL_TEXTURE_2D, tl, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);
		}

		Tex_GetModeinfo(&min, &mag);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}else
	{
//		printf("tex: mipmap\n");
		tl=0;
		while(tw>1 && th>1)
		{
			Tex_HalfSample(resampbuf, tw, th);
			tw>>=1;
			th>>=1;
			tl++;
			glTexImage2D (GL_TEXTURE_2D, tl, 4, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, resampbuf);
		}

		Tex_GetModeinfo(&min, &mag);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}

	free(resampbuf);

	return(num);
}

#if 0
teximage *Tex_FromTexturefile(texturefile *tf)
{
	return(Tex_LoadTexture(tf->width, tf->height, tf->buffer, 1));
}

int Tex_Screenshot(char *name)
{
	VFILE *fd;
	texturefile *tmp;
	int width, height, pixlin;

	width=640;
	height=480;

	pixlin=width*height;
	tmp=kgalloc(sizeof(texturefile)+(pixlin*4));
	tmp->width=width;
	tmp->height=height;
	tmp->type=TF_TYPE_RGBA;
	tmp->buffer=(byte *)(tmp+1);
	tmp->palette=NULL;

	glFinish();
	glReadPixels (0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, tmp->buffer); 

	fd=vffopen(name, "wb");

	Img_StoreTGA(fd, tmp);
}
#endif

typedef struct TargaHeader_s {
	unsigned char 	id_length, ctype, itype;
	unsigned short	cindex, clength;
	unsigned char	csize;
	unsigned short	x_origin, y_origin, width, height;
	unsigned char	bpp, attributes;
} TargaHeader;

byte *Img_LoadTGA(VFILE *fd, int *w, int *h)
{
	TargaHeader head;
	int pixlin, i;
	byte *dest, *src, *buf, *obuf, r, g, b, a;

	head.id_length=vfgetc(fd);
	head.ctype=vfgetc(fd);
	head.itype=vfgetc(fd);
	head.cindex=vfgetc(fd)+(vfgetc(fd)<<8);
	head.clength=vfgetc(fd)+(vfgetc(fd)<<8);
	head.csize=vfgetc(fd);
	head.x_origin=vfgetc(fd)+(vfgetc(fd)<<8);
	head.y_origin=vfgetc(fd)+(vfgetc(fd)<<8);
	head.width=vfgetc(fd)+(vfgetc(fd)<<8);
	head.height=vfgetc(fd)+(vfgetc(fd)<<8);
	head.bpp=vfgetc(fd);
	head.attributes=vfgetc(fd);

	if((head.itype!=2) || ((head.bpp!=32) && (head.bpp!=24)) || (head.ctype!=0))
	{
		kprint("Img_LoadTGA: only RGB(24)/RGBA(32) uncompressed images supported.\n");
		kprint("   bpp: %d, type: %d\n", head.bpp, head.ctype);
		return(NULL);
	}

	vfseek(fd, head.id_length, 1); /* skip comment */

	pixlin=head.width*head.height;
	obuf=malloc(pixlin*4);
	dest=obuf;

	buf=malloc(pixlin*(head.bpp>>3));
	vfread(buf, 1, pixlin*(head.bpp>>3), fd);
	src=buf;

	for(i=0; i<pixlin; i++)
	{
		b=*src++;
		g=*src++;
		r=*src++;
		if(head.bpp==32)
			a=*src++;
			else a=255;
		*dest++=r;
		*dest++=g;
		*dest++=b;
		*dest++=a;
	}
	free(buf);

	if(head.attributes&32)
	{
		dest=malloc(pixlin*4);
		for(i=0; i<head.height; i++)
			memcpy(&dest[i*head.width*4], &obuf[(head.height-(i+1))*head.width*4], head.width*4);
		memcpy(obuf, dest, pixlin*4);
		free(dest);
	}

	*w=head.width;
	*h=head.height;
	return(obuf);
}

int Img_StoreTGA(VFILE *fd, byte *buf, int w, int h)
{
	TargaHeader head;
	int i;
	byte *s;

	head.id_length=0;
	head.ctype=0;
	head.itype=2;
	head.cindex=0;
	head.clength=0;
	head.csize=0;
	head.x_origin=0;
	head.y_origin=0;
	head.width=w;
	head.height=h;
	head.bpp=24;
	head.attributes=0;

	vfputc(head.id_length, fd);
	vfputc(head.ctype, fd);
	vfputc(head.itype, fd);

	vfputc(head.cindex, fd);
	vfputc(head.cindex>>8, fd);
	vfputc(head.clength, fd);
	vfputc(head.clength>>8, fd);

	vfputc(head.csize, fd);

	vfputc(head.x_origin, fd);
	vfputc(head.x_origin>>8, fd);
	vfputc(head.y_origin, fd);
	vfputc(head.y_origin>>8, fd);

	vfputc(head.width, fd);
	vfputc(head.width>>8, fd);
	vfputc(head.height, fd);
	vfputc(head.height>>8, fd);

	vfputc(head.bpp, fd);
	vfputc(head.attributes, fd);

//	vfwrite(buf, w*4, h, fd);

	s=buf;
	for(i=0; i<w*h; i++)
	{
		vfputc(s[2], fd);
		vfputc(s[1], fd);
		vfputc(s[0], fd);
		s+=4;
	}

	return(0);
}

int Tex_LoadFile(char *name, int *w, int *h)
{
	VFILE *fd;
	byte *buf;
	int n;

	if(gl_texfilter_var==MISC_NULL)
		Tex_Init2();

	fd=vffopen(name, "rb");
	if(!fd)return(-1);

	printf("load tga %s\n", name);

	buf=Img_LoadTGA(fd, w, h);
	vfclose(fd);

	n=Tex_LoadTexture(*w, *h, buf, 1);
	free(buf);

	printf("loaded %d %d %d\n", n, *w, *h);

	return(n);
}

byte *Tex_LoadFileRaw(char *name, int *w, int *h)
{
	VFILE *fd;
	byte *buf;

	fd=vffopen(name, "rb");
	if(!fd)return(NULL);

	printf("load tga raw %s\n", name);

	buf=Img_LoadTGA(fd, w, h);
	vfclose(fd);

	return(buf);
}

int Tex_Screenshot(char *name)
{
	VFILE *fd;
	int width, height, pixlin;
	byte *buf;

	width=800;
	height=600;

	pixlin=width*height;
	buf=malloc(pixlin*4);

	glFinish();
	glReadPixels (0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf); 

	fd=vffopen(name, "wb");

	Img_StoreTGA(fd, buf, width, height);
	free(buf);

	return(0);
}

int Tex_DoScreenshot()
{
	static int num=0;
	char buf[64];

	sprintf(buf, "shot%d.tga", num++);

	kprint("screenshot to %s\n", buf);

	Tex_Screenshot(buf);

	return(0);
}
