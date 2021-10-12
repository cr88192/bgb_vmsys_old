#ifndef __OS1_GUI_H__
#define __OS1_GUI_H__

#define GUI_SVKEY	"volatile/system/gui-addr"

#define GUI_POPRET	((0<<18)+1)	// num -> (num)
#define GUI_INTEGER	((0<<18)+2)	//(long)
#define GUI_STRING	((0<<18)+3)	//(string)
#define GUI_DATA	((0<<18)+4)	//(data)

#define GUI_NEWSURF	((1<<18)+1)	//(xs ys)
#define GUI_SETSURFSZ	((1<<18)+2)	//(num x y w h)
#define GUI_ADDSURF	((1<<18)+3)	//(surf par)
#define GUI_SHOWSURF	((1<<18)+4)	//(surf)
#define GUI_HIDESURF	((1<<18)+5)	//(surf)
#define GUI_DROPSURF	((1<<18)+6)	//(surf)
#define GUI_FILLSURF	((1<<18)+7)	//(surf) data

#endif
