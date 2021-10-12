//#if 0
#ifndef X86_BOOT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef __GENERAL_H__
#define __GENERAL_H__

#ifndef BYTE_DEFINED
#define BYTE_DEFINED
typedef unsigned char byte;

#endif

#ifndef PROJNAME
#define PROJNAME "BGB-SYS"
#endif

#ifndef PROJVER
#define PROJVER "0.1"
#endif


typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned int u8[2]; /* low-high */
typedef unsigned long long u8s; /* low-high */

typedef signed short s2;
typedef signed int s4;
typedef signed int s8[2]; /* low-high, 2's complement */
typedef signed long long s8s; /* low-high */

//typedef unsigned short ushort;
//typedef signed short sshort;

//typedef unsigned long ulong;
//typedef signed long slong;

#ifndef NULL
#define NULL ((void *)0)
#endif

#include <scmcc.h>

#include <memory2.h>
#include <memory3_1.h>

#include <kthread.h>

#include <vfile.h>
#include <console.h>
#include <vars.h>

#include <vpath.h>
#include <parse.h>

#include <bitarray2.h>

#include <kfunc.h>
#include <devreg.h>

//#include <genobj.h>

#include <scmcc.h>
#include <store0.h>

#include <objtype.h>
#include <image.h>

int add_u8(u8 c, u8 a, u8 b);
int sub_u8(u8 c, u8 a, u8 b);
int mul_u8(u8 c, u8 a, u8 b);
int div_u8(u8 c, u8 a, u8 b);

int cmp_u8(u8 a, u8 b);
int shr_u8(u8 c, u8 a, int b);
int shl_u8(u8 c, u8 a, int b);

int add_s8(s8 c, s8 a, s8 b);
int sub_s8(s8 c, s8 a, s8 b);
int mul_s8(s8 c, s8 a, s8 b);
int div_s8(s8 c, s8 a, s8 b);

int neg_s8(s8 c, s8 a);
int abs_s8(u8 c, s8 a);
int cmp_s8(s8 a, s8 b);
int shr_s8(s8 c, s8 a, int b);
int shl_s8(s8 c, s8 a, int b);

int copy_u8(u8 c, u8 a);
int copy_s8(s8 c, s8 a);

#endif
