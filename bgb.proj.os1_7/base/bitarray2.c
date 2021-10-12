#include <general.h>

int BitArray2_SetBit(byte *buf, int bit)
{
	buf[bit/8]|=(128>>(bit%8));
	return(0);
}

int BitArray2_ClearBit(byte *buf, int bit)
{
	buf[bit/8]&=~(128>>(bit%8));
	return(0);
}

int BitArray2_GetBit(byte *buf, int bit)
{
	return(buf[bit/8]&(128>>(bit%8)));
}

/* find first run long enough for span, modifies span to reflect
found run */
int BitArray2_FindRun(byte *buf, int sz, int *span)
{
	int i, j;
	i=span[0];
	while(i<sz)
	{
		while(BitArray2_GetBit(buf, i) && (i<sz))i++;
		if(i>=sz)return(-1);
		j=i;
		while(!BitArray2_GetBit(buf, j) && (j<sz))j++;

		if(j-i>span[1])
		{
			span[0]=i;
			span[1]=j-i;
			return(0);
		}
		i=j;
	}
	return(-1);
}

int BitArray2_FindShortestRun(byte *buf, int sz, int *span)
{
	int ptr[2], small[2];
	int j, st;
	ptr[0]=span[0];
	ptr[1]=span[1];
	j=0;
	st=0;
	while(j==0)
	{
		j=BitArray2_FindRun(buf, sz, ptr);
		if(j<0)continue;
		if(ptr[1]<small[1])
		{
			st=1;
			small[0]=ptr[0];
			small[1]=ptr[1];
		}
		ptr[0]+=ptr[1];
		ptr[1]=span[1];
	}
	if(st)
	{
		span[0]=small[0];
		span[1]=small[1];
		return(0);
	}
	return(-1);
}

int BitArray2_SetRun(byte *buf, int *span)
{
	int i;
	for(i=span[0]; i<span[0]+span[1]; i++)
		BitArray2_SetBit(buf, i);
	return(0);
}

int BitArray2_ClearRun(byte *buf, int *span)
{
	int i;
	for(i=span[0]; i<span[0]+span[1]; i++)
		BitArray2_ClearBit(buf, i);
	return(0);
}

int BitArray2_Used(byte *buf, int sz)
{
	int i, j;
	j=0;
	for(i=0; i<sz; i++)if(BitArray2_GetBit(buf, i))j++;
	return(j);
}

int BitArray2_AllocBit(byte *buf, int sz)
{
	int i;
	for(i=0; i<sz; i++)if(!BitArray2_GetBit(buf, i))
	{
		BitArray2_SetBit(buf, i);
		return(i);
	}
	return(-1);
}

int BitArray2_AllocClosestBit(byte *buf, int sz, int bit)
{
	int i, v;
	for(i=0;i<sz;i++)
	{
		v=bit+i;
		if((v>=0)&&(v<sz))if(!BitArray2_GetBit(buf, v))
		{
			BitArray2_SetBit(buf, v);
			return(v);
		}
		v=bit-i;
		if((v>=0)&&(v<sz))if(!BitArray2_GetBit(buf, v))
		{
			BitArray2_SetBit(buf, v);
			return(v);
		}
	}
	return(-1);
}
