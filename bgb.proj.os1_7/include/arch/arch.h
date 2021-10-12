#ifndef __ARCH_H__
#define __ARCH_H__

typedef unsigned char byte;

typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned int u8[2]; /* low-high */

typedef signed short s2;
typedef signed int s4;
typedef signed int s8[2]; /* low-high, 2's complement */

typedef unsigned long ulong;
typedef signed long slong;

typedef unsigned short ushort;
typedef signed short sshort;

#ifndef NULL
#define NULL ((void *)0)
#endif

static inline unsigned short htons(unsigned short v)
{
	return(((v>>8)&0xff)+((v&0xff)<<8));
}

static inline unsigned short ntohs(unsigned short v)
{
	return(((v>>8)&0xff)+((v&0xff)<<8));
}

static inline unsigned long htonl(unsigned long v)
{
	return(((v>>24)&0xff)+((v>>8)&0xff00)+((v&0xff00)<<8)+((v&0xff)<<24));
}

static inline unsigned long ntohl(unsigned long v)
{
	return(((v>>24)&0xff)+((v>>8)&0xff00)+((v&0xff00)<<8)+((v&0xff)<<24));
}

#endif
