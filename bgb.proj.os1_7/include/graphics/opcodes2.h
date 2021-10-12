#ifndef __GFXOPCODES2_H__
#define __GFXOPCODES2_H__

#define GFXOP2_NOP		0
#define GFXOP2_INTEGER		1	//int32
#define GFXOP2_STRING		2	//string, ascii
#define GFXOP2_DATAGLOB		3	//glob of data, has: a size, a pointer

#define GFXOP2_BEGINDRAWING	16
#define GFXOP2_ENDDRAWING	17
#define GFXOP2_POPRET		18

#define GFXOP2_FILLSQUARE	19	//x y w h r g b a
#define GFXOP2_DRAWIMAGE	20	//x y w h data xs ys

#endif
