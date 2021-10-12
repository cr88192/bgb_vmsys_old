#ifndef __GFXOPCODES_H__
#define __GFXOPCODES_H__

#define GFXOP_NOP			0
#define GFXOP_BEGINDRAWING	1
#define GFXOP_ENDDRAWING	2
#define GFXOP_POPRET		3

#define GFXOP_FILLSQUARE	16	//x y w h r g b a
#define	GFXOP_SHOW			17	//(string text)
#define GFXOP_MOVETO		18	//x y
#define GFXOP_FONTSIZE		19	//sz_x sz_y
#define GFXOP_TEXTCOLOR		20	//r g b a
#define GFXOP_SETFONT		21	//(string name)

#define GFXOP_TRANSLATE		32	//x y
#define GFXOP_SCALE			33	//(S8.24 x) (S8.24 y)
#define GFXOP_SETRANGE		34	//left right bottom top
#define GFXOP_PUSHMATRIX	35	//
#define GFXOP_POPMATRIX		36	//

#define GFXOP_TRANS2D		37	//x y
#define GFXOP_RTRANS2D		38	//x y

#endif
