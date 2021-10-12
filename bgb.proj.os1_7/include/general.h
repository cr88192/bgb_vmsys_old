#ifndef X86_BOOT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <arch/arch.h>
#include <os1/ioctls.h>

#include <memory2.h>

#include <kthread.h>

#include <vfile.h>
#include <console.h>
#include <vars.h>

#include <vpath.h>
#include <parse.h>

#include <bitarray2.h>

#include <kfunc.h>
#include <devreg.h>

#include <objtype.h>

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
