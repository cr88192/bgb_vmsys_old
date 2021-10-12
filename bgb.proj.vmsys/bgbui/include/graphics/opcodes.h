#ifndef __GFXOPCODES_H__
#define __GFXOPCODES_H__

#define GFXOP_NOP		0	//
#define GFXOP_BEGINDRAWING	1	//
#define GFXOP_ENDDRAWING	2	//
#define GFXOP_POPRET		3	// -> int
#define GFXOP_POPRETF		4	// -> float
#define GFXOP_MARK		5	//mark stack pos

#define GFXOP_FILLSQUARE	16	//x y w h r g b a
#define GFXOP_SHOW		17	//(string text)
#define GFXOP_MOVETO		18	//x y
#define GFXOP_FONTSIZE		19	//sz_x sz_y
#define GFXOP_TEXTCOLOR		20	//r g b a
#define GFXOP_SETFONT		21	//(string name)

#define GFXOP_TRANSLATE		32	//x y
#define GFXOP_SCALE		33	//(S8.24 x) (S8.24 y)
#define GFXOP_SETRANGE		34	//left right bottom top
#define GFXOP_PUSHMATRIX	35	//
#define GFXOP_POPMATRIX		36	//

#define GFXOP_TRANS2D		37	//drop, x y
#define GFXOP_RTRANS2D		38	//drop, x y
#define GFXOP_PUSHCLIP		39	//
#define GFXOP_POPCLIP		40	//
#define GFXOP_SETCLIP2		41	//x y x2 y2

#define GFXOP_TRANSLATE3	48	//x y z
#define GFXOP_SCALE3		49	//x y z
#define GFXOP_ROT3		50	//Nx Ny Nz angle
#define GFXOP_PERSPECTIVE	51	//fovx fovy
#define GFXOP_TEXTURE		52	//data num width height enc -> num
					//num: 0=alloc num, result is num
					//-> num: 0=error, else texnum
					//enc: 1=rgba32

#define GFXOP_BINDTEX		53	//texnum
#define GFXOP_UNBINDTEX		54	//

#define GFXOP_BEGIN		56	//type
#define GFXOP_END		57	//type

#define GFXOP_POINT		58	//
#define GFXOP_VEC3		59	//x y z
#define GFXOP_STCOORDS		60	//s t
#define GFXOP_COLOR		61	//r g b a

#define GFXOP_MATRIX		62	//a11 ... a14 a21 ... a44
#define GFXOP_MATMULT		63	//matrix

#define GFXOP_ADDLIGHT		64	//-> index, allocs light, pointbuffer
					//settings
#define GFXOP_DROPLIGHT		65	//index, drops the light

#define GFXVAR_RAW	0

#define GFXVAR_POLYGON	16
#define GFXVAR_RGBA32	32

#endif
