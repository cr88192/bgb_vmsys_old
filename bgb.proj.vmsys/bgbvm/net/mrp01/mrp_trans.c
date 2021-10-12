/*
MRP Transport Layer
 */

#include <general.h>
#include <net/mrp01.h>

int MRPTrans_WriteUByte(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=0;
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int MRPTrans_WriteSByte(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=8;
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int MRPTrans_WriteUShort(VFILE *fd, int v)
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

int MRPTrans_WriteSShort(VFILE *fd, int v)
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

int MRPTrans_WriteULong(VFILE *fd, int v)
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

int MRPTrans_WriteSLong(VFILE *fd, int v)
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

int MRPTrans_WriteUInt(VFILE *fd, int v)
{
	if(v<256)return(MRPTrans_WriteUByte(fd, v));
	if(v<65536)return(MRPTrans_WriteUShort(fd, v));
	return(MRPTrans_WriteULong(fd, v));
}

int MRPTrans_WriteSInt(VFILE *fd, int v)
{
	int r;

	if(v>0)r=v;
		else r=0-v;

	if(r<127)return(MRPTrans_WriteSByte(fd, v));
	if(r<32767)return(MRPTrans_WriteSShort(fd, v));
	return(MRPTrans_WriteSLong(fd, v));
}

int MRPTrans_WriteFloat(VFILE *fd, float f)
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

int MRPTrans_WriteDouble(VFILE *fd, double f)
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

int MRPTrans_ReadULong(VFILE *fd)
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

int MRPTrans_ReadSLong(VFILE *fd)
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

int MRPTrans_WriteOpcode(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=1+((v<<4)&0xF0);
	*s++=(v>>4)&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

byte *MRPTrans_WriteVLI(byte *s, int i)
{
	byte buf[10];
	byte *t;

	t=buf;
	*t++=i&0x7f;
	i>>=7;

	while(i)
	{
		*t++=(i&0x7f)|0x80;
		i>>=7;
	}
	while(t-->buf)*s++=*t;
	return(s);
}

int MRPTrans_WriteString(VFILE *fd, char *t)
{
	char *buf;
	char *s;
	int l;

	l=strlen(t);

//	buf=kalloc(((l+1)*2)+10);
	buf=kralloc((l+1)+10);

	s=buf;
//	*s++=(3<<3)+2;
	*s++=(6<<3)+2;

//	s=MRPTrans_WriteVLI(s, l*2);
	s=MRPTrans_WriteVLI(s, l);

	strcpy(s, t);
	s+=l;

//	kprint("write string \"%s\"\n", t);

//	while(*t)
//	{
//		*s++=*t++;
//		*s++=0;
//	}

	vfwrite(buf, 1, s-buf, fd);

//	kfree(buf);

	return(0);
}


int MRPTrans_WriteStringU2(VFILE *fd, u2 *t)
{
	char *buf;
	char *s;
	u2 *t2;
	int i, j;

	t2=t;
	i=0;
	while(*t2++)i++;

	for(j=0; j<i; j++)if(t[j]>127)break;

	if(i==j)
	{
		buf=kralloc(i+1);
		s=buf;
		while(*t)*s++=*t++;
		*s++=0;

		i=MRPTrans_WriteString(fd, buf);
//		kfree(buf);

		return(i);
	}

	buf=kralloc(((i+1)*2)+10);

	s=buf;
	*s++=(3<<3)+2;

	s=MRPTrans_WriteVLI(s, i*2);

	t2=t;
	while(*t2)
	{
		*s++=*t2>>8;
		*s++=*t2&0xff;
		t2++;
	}

	vfwrite(buf, 1, s-buf, fd);
//	kfree(buf);

	return(0);
}

int MRPTrans_WriteData(VFILE *fd, byte *t, int len, int enc)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=(1<<3)+2;
	s=MRPTrans_WriteVLI(s, len+1);
	*s++=enc;

	vfwrite(buf, 1, s-buf, fd);
	vfwrite(t, 1, len, fd); //data can be sent in multiple chunks

	return(0);
}

int MRPTrans_WriteSymbol(VFILE *fd, char *t)
{
	char *buf;
	char *s;
	int l;

	l=strlen(t);

	buf=kralloc(((l+1)*2)+10);

	s=buf;
//	*s++=(2<<3)+2;
	*s++=(5<<3)+2;

//	s=MRPTrans_WriteVLI(s, l*2);
	s=MRPTrans_WriteVLI(s, l);

//	strcpy(s, t);

//	kprint("write string \"%s\"\n", t);

	while(*t)
	{
		*s++=*t++;
//		*s++=0;
	}

	vfwrite(buf, 1, s-buf, fd);

//	kfree(buf);

	return(0);
}

int MRPTrans_WriteWidenum(VFILE *fd, u2 *t, int l)
{
	char *buf;
	char *s;
	u2 *t2;
	int i;

	buf=kralloc(((l+1)*2)+10);

	s=buf;
	*s++=(4<<3)+2;

	s=MRPTrans_WriteVLI(s, l*2);

	t2=t;
	while(*t2)
	{
		*s++=*t2&0xff;
		*s++=*t2>>8;
		t2++;
	}

	vfwrite(buf, 1, s-buf, fd);
//	kfree(buf);

	return(0);
}

int MRPTrans_WriteConst(VFILE *fd, int v)
{
	char buf[8];
	char *s;

	s=buf;
	*s++=(3<<3);
	*s++=v&255;
	vfwrite(buf, 1, 2, fd);
	return(0);
}

int MRPTrans_WriteGuid(VFILE *fd, VGUID *guid)
{
	MRPTrans_WriteData(fd, guid, 16, MRPVAL_DATA_BYTEVECTOR);
	return(0);
}
