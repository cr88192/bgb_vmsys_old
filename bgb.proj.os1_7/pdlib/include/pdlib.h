#ifndef __PDLIB_H__
#define __PDLIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROJNAME
#define PROJNAME "PDLIB"
#endif

#ifndef PROJVER
#define PROJVER "0.1"
#endif

typedef unsigned char byte;

typedef unsigned short u2;
typedef signed short s2;

typedef unsigned long u4;
typedef signed long s4;

typedef unsigned long u8[2];
typedef signed long s8[2];


#include <pdbase/memory2.h>
#include <pdbase/objtype.h>
#include <pdbase/image.h>

#include <pdbase/vfile.h>

int kprint(char *s, ...);

#endif
