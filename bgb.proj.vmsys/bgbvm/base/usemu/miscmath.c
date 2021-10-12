#include <general.h>

int mul_824(u4 a, u4 b)
{
	u2 r[4];
	u4 o;
	int s;

	s=0;

	if((int)a<0)
	{
		a=0-a;
		s^=1;
	}
	if((int)b<0)
	{
		b=0-b;
		s^=1;
	}

//	kprint("mul_824 %d %d\n", a, b);

	o=(a&0xffff)*(b&0xffff);
	r[0]=o&0xffff;
	o>>=16;
	o+=(a&0xffff)*((b>>16)&0xffff);
	o+=((a>>16)&0xffff)*(b&0xffff);
	r[1]=o&0xffff;

	o>>=16;
	o+=((a>>16)&0xffff)*((b>>16)&0xffff);
	r[2]=o&0xffff;
	r[3]=(o>>16)&0xffff;

//	kprint("mul_824 %d %d %d %d\n", r[0], r[1], r[2], r[3]);

	r[0]=(r[1]>>8)+((r[2]<<8)&0xff00);
	r[1]=(r[2]>>8)+((r[3]<<8)&0xff00);

//	kprint("mul_824 %d %d\n", r[0], r[1]);

	o=(u4)r[0]+((u4)r[1]<<16);

	if(s)o=0-o;

//	kprint("mul_824 %d\n", o);

	return((int)o);
}

int div_824(u4 a, u4 b)
{
	u4 c, s;

	c=0;
	s=1<<24;
	while(s & b)
	{
		while(a>b)
		{
			c+=s;
			a-=b;
		}
		b>>=8;
		s>>=8;
	}
	return(c);
}

int matmult_824(u4 *a, int ah, int aw,  u4 *b, int bh, int bw,  u4 *c)
{
	int i, j, k;

	if(aw!=bh)return(-1);

	for(i=0; i<(ah*bw); i++)c[i]=0;
	for(i=0; i<ah; i++)
		for(j=0; j<bw; j++)
			for(k=0; k<aw; k++)
				c[(j*bw)+k]+=mul_824(a[(j*aw)+i], b[(i*bw)+k]);
	return(0);
}

int gfx_ortho_824(u4 *c, int left, int right, int bottom, int top, int near, int far)
{
	int i, sx, sy, sz, tx, ty, tz;

	for(i=0; i<16; i++)c[i]=0;
	for(i=0; i<4; i++)c[(i*4)+i]=1<<24;

	sx=(2<<24)/(right-left);
	sy=(2<<24)/(top-bottom);
	sz=(-2<<24)/(far-near);

	tx=(right+left)/(right-left);
	ty=(top+bottom)/(top-bottom);
	tz=(far+near)/(far-near);

	c[0]=sx;
	c[5]=sy;
	c[10]=sz;

	c[3]=tx;
	c[7]=ty;
	c[11]=tz;

	return(0);
}

int mul_248(u4 a, u4 b)
{
	u2 r[4];
	u4 o;
	int s;

	s=0;

	if((int)a<0)
	{
		a=0-a;
		s^=1;
	}
	if((int)b<0)
	{
		b=0-b;
		s^=1;
	}

//	kprint("mul_824 %d %d\n", a, b);

	o=(a&0xffff)*(b&0xffff);
	r[0]=o&0xffff;
	o>>=16;
	o+=(a&0xffff)*((b>>16)&0xffff);
	o+=((a>>16)&0xffff)*(b&0xffff);
	r[1]=o&0xffff;

	o>>=16;
	o+=((a>>16)&0xffff)*((b>>16)&0xffff);
	r[2]=o&0xffff;
	r[3]=(o>>16)&0xffff;

//	kprint("mul_824 %d %d %d %d\n", r[0], r[1], r[2], r[3]);

	r[0]=(r[0]>>8)+((r[1]<<8)&0xff00);
	r[1]=(r[1]>>8)+((r[2]<<8)&0xff00);

//	kprint("mul_824 %d %d\n", r[0], r[1]);

	o=(u4)r[0]+((u4)r[1]<<16);

	if(s)o=0-o;

//	kprint("mul_824 %d\n", o);

	return((int)o);
}
