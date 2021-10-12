#include <general.h>

int add_u8(u8 c, u8 a, u8 b)
{
	u2 a2[4], b2[4], c2[4];
	u4 o;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	b2[0]=b[0]&0xffff;
	b2[1]=(b[0]>>16)&0xffff;
	b2[2]=b[1]&0xffff;
	b2[3]=(b[1]>>16)&0xffff;

	o=(u4)a2[0]+(u4)b2[0];
	c2[0]=o&0xffff;
	o=(u4)a2[1]+(u4)b2[1]+(o>>16);
	c2[1]=o&0xffff;
	o=(u4)a2[2]+(u4)b2[2]+(o>>16);
	c2[2]=o&0xffff;
	o=(u4)a2[3]+(u4)b2[3]+(o>>16);
	c2[3]=o&0xffff;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}

int sub_u8(u8 c, u8 a, u8 b)
{
	u2 a2[4], b2[4], c2[4];
	s4 o;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	b2[0]=b[0]&0xffff;
	b2[1]=(b[0]>>16)&0xffff;
	b2[2]=b[1]&0xffff;
	b2[3]=(b[1]>>16)&0xffff;

	o=(u4)a2[0]-(u4)b2[0];
	c2[0]=o&0xffff;
	o=(u4)a2[1]-(u4)b2[1]+(o>>16);
	c2[1]=o&0xffff;
	o=(u4)a2[2]-(u4)b2[2]+(o>>16);
	c2[2]=o&0xffff;
	o=(u4)a2[3]-(u4)b2[3]+(o>>16);
	c2[3]=o&0xffff;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}

int mul_u8(u8 c, u8 a, u8 b)
{
	u2 a2[4], b2[4], c2[4];
	u4 o;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	b2[0]=b[0]&0xffff;
	b2[1]=(b[0]>>16)&0xffff;
	b2[2]=b[1]&0xffff;
	b2[3]=(b[1]>>16)&0xffff;

	o=(u4)a2[0]*(u4)b2[0];
	c2[0]=o&0xffff;
	o=(u4)a2[1]*(u4)b2[0]+(o>>16);
	c2[1]=o&0xffff;
	o=(u4)a2[2]*(u4)b2[0]+(o>>16);
	c2[2]=o&0xffff;
	o=(u4)a2[3]*(u4)b2[0]+(o>>16);
	c2[3]=o&0xffff;

	o=(u4)a2[0]*(u4)b2[1]+c2[1];
	c2[1]=o&0xffff;
	o=(u4)a2[1]*(u4)b2[1]+c2[2]+(o>>16);
	c2[2]=o&0xffff;
	o=(u4)a2[2]*(u4)b2[1]+c2[3]+(o>>16);
	c2[3]=o&0xffff;

	o=(u4)a2[0]*(u4)b2[2]+c2[2];
	c2[2]=o&0xffff;
	o=(u4)a2[1]*(u4)b2[2]+c2[3]+(o>>16);
	c2[3]=o&0xffff;

	o=(u4)a2[0]*(u4)b2[3]+c2[3];
	c2[3]=o&0xffff;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}

int cmp_u8(u8 a, u8 b)
{
	if(a[1]>b[1])return(1);
	if(a[1]<b[1])return(-1);

	if(a[0]>b[0])return(1);
	if(a[0]<b[0])return(-1);

	return(0);
}

int div_u8(u8 c, u8 a, u8 b)
{
	u8 a2;

	a2[0]=a[0];
	a2[1]=a[1];
	c[0]=0;
	c[1]=0;

	while(cmp_u8(a2, b)==1)
	{
		sub_u8(a2, a2, b);
		c[0]++;
		if(!c[0])c[1]++;
	}
	return(0);
}

int shr_u8(u8 c, u8 a, int b)
{
	u2 a2[4], c2[4];
	u4 o;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	a2[0]=(b<64)?a2[0+(b>>4)]:0;
	a2[1]=(b<48)?a2[1+(b>>4)]:0;
	a2[2]=(b<32)?a2[2+(b>>4)]:0;
	a2[3]=(b<16)?a2[3]:0;

	b&=15;
	o=(a2[3]<<16)>>b;
	c2[3]=o>>16;
	o=(a2[2]<<16)>>b+((o&0xffff)<<16);
	c2[2]=o>>16;
	o=(a2[1]<<16)>>b+((o&0xffff)<<16);
	c2[1]=o>>16;
	o=(a2[0]<<16)>>b+((o&0xffff)<<16);
	c2[0]=o>>16;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}

int shl_u8(u8 c, u8 a, int b)
{
	u2 a2[4], c2[4];
	u4 o;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	a2[3]=(b<64)?a2[3-(b>>4)]:0;
	a2[2]=(b<48)?a2[2-(b>>4)]:0;
	a2[1]=(b<32)?a2[1-(b>>4)]:0;
	a2[0]=(b<16)?a2[0]:0;

	b&=15;
	o=a2[0]<<b;
	c2[0]=o&0xffff;
	o=a2[1]<<b+(o>>16);
	c2[1]=o&0xffff;
	o=a2[2]<<b+(o>>16);
	c2[2]=o&0xffff;
	o=a2[3]<<b+(o>>16);
	c2[3]=o&0xffff;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}


int add_s8(s8 c, s8 a, s8 b)
{
	return(add_u8((u4 *)c, (u4 *)a, (u4 *)b));
}

int sub_s8(s8 c, s8 a, s8 b)
{
	return(sub_u8((u4 *)c, (u4 *)a, (u4 *)b));
}

int neg_s8(s8 c, s8 a)
{
	c[0]=0-a[0];
	c[1]=0-a[1];
	return(0);
}

int abs_s8(u8 c, s8 a)
{
	if(a[1]<0)
	{
		c[0]=0-a[0];
		c[1]=0-a[1];
	}else
	{
		c[0]=a[0];
		c[1]=a[1];
	}
	return(0);
}

int mul_s8(s8 c, s8 a, s8 b)
{
	u8 a2, b2;
	int sa, sb;

	sa=a[1]<0?1:0;
	sb=b[1]<0?1:0;
	abs_s8(a2, a);
	abs_s8(b2, b);

	mul_u8((u4 *)c, a2, b2);
	if(sa^sb)neg_s8(c, c);
	return(0);
}

int div_s8(s8 c, s8 a, s8 b)
{
	u8 a2, b2;
	int sa, sb;

	sa=a[1]<0?1:0;
	sb=b[1]<0?1:0;
	abs_s8(a2, a);
	abs_s8(b2, b);

	div_u8((u4 *)c, a2, b2);
	if(sa^sb)neg_s8(c, c);
	return(0);
}

int cmp_s8(s8 a, s8 b)
{
	if(a[1]>b[1])return(1);
	if(a[1]<b[1])return(-1);

	if((u4)a[0]>(u4)b[0])return(1);
	if((u4)a[0]<(u4)b[0])return(-1);

	return(0);
}

int shr_s8(s8 c, s8 a, int b)
{
	u2 a2[4], c2[4];
	u4 o;
	int s;

	if(a[1]<0)s=1;
		else s=0;

	a2[0]=a[0]&0xffff;
	a2[1]=(a[0]>>16)&0xffff;
	a2[2]=a[1]&0xffff;
	a2[3]=(a[1]>>16)&0xffff;

	a2[0]=(b<64)?a2[0+(b>>4)]:s?0xffff:0;
	a2[1]=(b<48)?a2[1+(b>>4)]:s?0xffff:0;
	a2[2]=(b<32)?a2[2+(b>>4)]:s?0xffff:0;
	a2[3]=(b<16)?a2[3]:s?0xffff:0;

	b&=15;
	o=(a2[3]<<16)>>b+(s?0xffff0000:0);
	c2[3]=o>>16;
	o=(a2[2]<<16)>>b+((o&0xffff)<<16);
	c2[2]=o>>16;
	o=(a2[1]<<16)>>b+((o&0xffff)<<16);
	c2[1]=o>>16;
	o=(a2[0]<<16)>>b+((o&0xffff)<<16);
	c2[0]=o>>16;

	c[0]=c2[0]+(c2[1]<<16);
	c[1]=c2[2]+(c2[3]<<16);

	return(0);
}

int shl_s8(s8 c, s8 a, int b)
{
	return(shl_u8((u4 *)c, (u4 *)a, b));
}

int copy_u8(u8 c, u8 a)
{
	c[0]=a[0];
	c[1]=a[1];
	return(0);
}

int copy_s8(s8 c, s8 a)
{
	c[0]=a[0];
	c[1]=a[1];
	return(0);
}
