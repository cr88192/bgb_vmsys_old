#include <general.h>
//#include <render/gldef.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <gfxdev/window.h>
#include <gfxdev/keys.h>

#include <X11/keysym.h>
#include <X11/cursorfont.h>

#include <X11/extensions/xf86dga.h>
#include <X11/extensions/xf86vmode.h>

#define KEY_MASK (KeyPressMask | KeyReleaseMask)
#define MOUSE_MASK (ButtonPressMask | ButtonReleaseMask | \
		    PointerMotionMask | ButtonMotionMask )
#define X_MASK (KEY_MASK | MOUSE_MASK | VisibilityChangeMask | StructureNotifyMask )

struct windowdata_s {
/* both */
int			isglx;
Window		win;
int			mx, my, mb;

/* GLX */
GLXContext	ctx;

/* non-GLX */
GC			gc;
XImage		*img;
byte		*buf;
int			pixsz;
int			linesz;

/* misc */
byte keymap[32];
};

Display *x_disp;
Window root;
XVisualInfo *visinfo;
int scrnum;

int win_init = 0;

int mouse_x, mouse_y;
int win_x, win_y;

displaywindow *win_active, *win_root;
int (*key_handler[16])(displaywindow *wnd, int key);

int Window_Init()
{
	int attrib[] = {
		GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE, 1,
		None
	};

	printf("Window Init.\n");

	if (!(x_disp = XOpenDisplay(NULL))) {
		fprintf(stderr, "Error couldn't open the X display\n");
		return(-1);
	}

	scrnum = DefaultScreen(x_disp);
	root = RootWindow(x_disp, scrnum);

	visinfo = glXChooseVisual(x_disp, scrnum, attrib);
	if (!visinfo) {
		fprintf(stderr, "couldn't get appropriate visual\n");
		return(-1);
	}

//	XAutoRepeatOff(x_disp);

	win_init=1;

	win_active = NULL;
	win_root = NULL;

	return(0);
}

displaywindow *Window_NewWindow(int width, int height)
{
	displaywindow *tmp;
	struct windowdata_s *tmpd;
	GLXContext ctx;

	XSetWindowAttributes attr;
	unsigned long mask;
	Window win;

	if(!win_init)
	{
		printf("X support not inited.\n");
		return(NULL);
	}

	tmp=kalloc(sizeof(displaywindow)+sizeof(struct windowdata_s));
	tmpd=(struct windowdata_s *)(tmp+1);
	tmp->viddata=tmpd;

	tmp->width=width;
	tmp->height=height;

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(x_disp, root, visinfo->visual, AllocNone);
	attr.event_mask = X_MASK;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	win = XCreateWindow(x_disp, root, 0, 0, width, height,
						0, visinfo->depth, InputOutput,
						visinfo->visual, mask, &attr);
	XMapWindow(x_disp, win);

	tmpd->win = win;

	XFlush(x_disp);

	ctx = glXCreateContext(x_disp, visinfo, NULL, True);

	tmpd->ctx = ctx;

	glXMakeCurrent(x_disp, win, ctx);

	tmpd->isglx=1;

	win_active = tmp;
	if(win_root) win_root->prev = tmp;
	tmp->next = win_root;
	win_root = tmp;

	return(tmp);
}

displaywindow *Window_NewWindow_NOGL(int width, int height)
{
	displaywindow *tmp;
	struct windowdata_s *tmpd;

	XSetWindowAttributes attr;
	unsigned long mask;
	Window win;

	XGCValues xgcvalues;
	int valuemask, i;
	XEvent event;

	if(!win_init)
	{
		printf("X support not inited.\n");
		return(NULL);
	}

	tmp=kalloc(sizeof(displaywindow)+sizeof(struct windowdata_s));
	tmpd=(struct windowdata_s *)(tmp+1);
	tmp->viddata=tmpd;

	tmp->width=width;
	tmp->height=height;

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(x_disp, root, visinfo->visual, AllocNone);
	attr.event_mask = X_MASK;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	win = XCreateWindow(x_disp, root, 0, 0, width, height,
						0, visinfo->depth, InputOutput,
						visinfo->visual, mask, &attr);

	tmpd->win = win;

	valuemask = GCGraphicsExposures;
	xgcvalues.graphics_exposures = False;
	tmpd->gc = XCreateGC(x_disp, win, valuemask, &xgcvalues);

	XMapWindow(x_disp, win);

	/* wait for window ready */
/*	while (1)
	{
		XNextEvent(x_disp, &event);
		if (event.type == Expose && !event.xexpose.count)
			break;
	} */

	i = visinfo->depth / 8;
	if (i == 3) i = 4;
	tmpd->pixsz = i;
	tmpd->linesz = (width*i+7)&(~7);
	tmpd->buf = malloc(tmpd->linesz * height);
	tmpd->img = XCreateImage(x_disp, visinfo->visual, visinfo->depth, ZPixmap, 0, tmpd->buf, width, height, 32, 0);

	XFlush(x_disp);

	printf("created window nongl: w=%d h=%d depth=%d\n", width, height, visinfo->depth);

	tmpd->isglx=0;

	win_active = tmp;
	if(win_root) win_root->prev = tmp;
	tmp->next = win_root;
	win_root = tmp;

	return(tmp);
}

int Window_Destroy(displaywindow *wnd)
{
	struct windowdata_s *tmpd;
	tmpd=wnd->viddata;
	if(tmpd->isglx)
	{
		glXDestroyContext(x_disp, tmpd->ctx);
		XDestroyWindow(x_disp, tmpd->win);
	}else
	{
		XDestroyImage(tmpd->img);
		XFreeGC(x_disp, tmpd->gc);
		XDestroyWindow(x_disp, tmpd->win);
	}
	if(wnd->next)wnd->next->prev=wnd->prev;
	if(wnd->prev)wnd->prev->next=wnd->next;
		else win_root=wnd->next;
	kfree(wnd);
	return(0);
}

int Window_DeInit()
{
	displaywindow *wcur, *wcur2;

	printf("Window DeInitialize.\n");

	XAutoRepeatOn(x_disp);

	wcur=win_root;
	while(wcur)
	{
		wcur2=wcur->next;
		Window_Destroy(wcur);
		wcur=wcur2;
	}
	XCloseDisplay(x_disp);
	win_init = 0;
	return(0);
}

int Window_SetWindow(displaywindow *wind)
{
	struct windowdata_s *tmpd;

	win_active=wind;
	tmpd=wind->viddata;

	if(tmpd->isglx)
	{
		glXMakeCurrent(x_disp, tmpd->win, tmpd->ctx);

		glClearColor (1, 1, 1, 1);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glCullFace (GL_FRONT_AND_BACK);
	}
}

static void HandleEvents(void);

int Window_BeginDrawing()
{
	struct windowdata_s *tmpd;
	tmpd=win_active->viddata;

	HandleEvents();

//	printf("%d %d\n", mouse_x, mouse_y);

	if(tmpd->isglx)
	{
		glViewport (0, 0, win_active->width, win_active->height);

		glClearColor (1, 1, 1, 1);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

int Window_EndDrawing()
{
	struct windowdata_s *tmpd;
	tmpd=win_active->viddata;

	if(tmpd->isglx)
	{
		glFlush();
		glXSwapBuffers(x_disp, tmpd->win);
	}
	else
	{
		XPutImage(x_disp, tmpd->win, tmpd->gc, tmpd->img, 0, 0, 0, 0, win_active->width, win_active->height);
		XSync(x_disp, False);
	}
}

int Window_RegisterKeyHandler(int (*handler)(displaywindow *wnd, int key))
{
	int i;
	for(i=0; i<16; i++)if(!key_handler[i])
	{
		key_handler[i]=handler;
		return(i);
	}
	return(-1);
}

int Window_RemoveKeyHandler(int hnd)
{
	key_handler[hnd]=NULL;
	return(0);
}

byte *Window_GetKeyMap(displaywindow *wnd)
{
	struct windowdata_s *tmpd;
	tmpd=wnd->viddata;
	return(tmpd->keymap);
}

static int SendKeyToHandlers(displaywindow *wnd, int key)
{
	int i;

//	printf("key: %d\n", key);

	for(i=0; i<16; i++)if(key_handler[i])
		key_handler[i](wnd, key);
	return(0);
}

static int HandleKeyEvent(XKeyEvent *ev, displaywindow *wnd, int press)
{
	int key;
	char buf[64];
	KeySym keysym;
	struct windowdata_s *tmpd;

	tmpd=wnd->viddata;

	key = 0;

	XLookupString(ev, buf, sizeof buf, &keysym, 0);

	switch(keysym)
	{
		case XK_KP_Page_Up:	 
		case XK_Page_Up:	 key = K_PGUP; break;

		case XK_KP_Page_Down: 
		case XK_Page_Down:	 key = K_PGDN; break;

		case XK_KP_Home: 
		case XK_Home:	 key = K_HOME; break;

		case XK_KP_End:  
		case XK_End:	 key = K_END; break;

		case XK_KP_Left: 
		case XK_Left:	 key = K_LEFTARROW; break;

		case XK_KP_Right: 
		case XK_Right:	key = K_RIGHTARROW;		break;

		case XK_KP_Down: 
		case XK_Down:	 key = K_DOWNARROW; break;

		case XK_KP_Up:   
		case XK_Up:		 key = K_UPARROW;	 break;

		case XK_Escape: key = K_ESCAPE;		break;

		case XK_KP_Enter: 
		case XK_Return: key = K_ENTER;		 break;

		case XK_Tab:		key = K_TAB;			 break;

		case XK_F1:		 key = K_F1;				break;

		case XK_F2:		 key = K_F2;				break;

		case XK_F3:		 key = K_F3;				break;

		case XK_F4:		 key = K_F4;				break;

		case XK_F5:		 key = K_F5;				break;

		case XK_F6:		 key = K_F6;				break;

		case XK_F7:		 key = K_F7;				break;

		case XK_F8:		 key = K_F8;				break;

		case XK_F9:		 key = K_F9;				break;

		case XK_F10:		key = K_F10;			 break;

		case XK_F11:		key = K_F11;			 break;

		case XK_F12:		key = K_F12;			 break;

		case XK_BackSpace: key = K_BACKSPACE; break;

		case XK_KP_Delete: 
		case XK_Delete: key = K_DEL; break;

		case XK_Shift_L:
		case XK_Shift_R:	key = K_SHIFT;		break;

		case XK_Execute: 
		case XK_Control_L: 
		case XK_Control_R:	key = K_CTRL;		 break;

		case XK_Alt_L:	
		case XK_Meta_L: 
		case XK_Alt_R:	
		case XK_Meta_R: key = K_ALT;			break;

		case XK_KP_Begin: key = '5';	break;

		case XK_KP_Insert: 
		case XK_Insert:key = K_INS; break;

		case XK_KP_Multiply: key = '*'; break;
		case XK_KP_Add:  key = '+'; break;
		case XK_KP_Subtract: key = '-'; break;
		case XK_KP_Divide: key = '/'; break;

		default:
			key = *(unsigned char*)buf;
			if (key >= 'A' && key <= 'Z')
				key = key - 'A' + 'a';
			break;
	} 

	if(press)
		tmpd->keymap[key/8]|=1<<(key%8);
		else tmpd->keymap[key/8]&=~(1<<(key%8));

	if(press && (key<128))SendKeyToHandlers(wnd, key);

	return key;
}

static void HandleEvents(void)
{
	XEvent event;
	KeySym ks;
	int b;
	struct windowdata_s *tmpd;
	displaywindow *wcur, *targwin;

	if (!x_disp)
		return;

	while (XPending(x_disp))
	{
		XNextEvent(x_disp, &event);

		/* figure where this goes */
		wcur=win_root;
		while(wcur)
		{
			tmpd=wcur->viddata;
			if(tmpd->win == event.xany.window)
				targwin=wcur;
			else
			{
				tmpd->mx=-1;
				tmpd->my=-1;
				tmpd->mb=0;
			}
			wcur=wcur->next;
		}
		tmpd=targwin->viddata;

		switch (event.type)
		{
		case KeyPress:
			HandleKeyEvent(&event.xkey, targwin, 1);
			break;

		case KeyRelease:
			HandleKeyEvent(&event.xkey, targwin, 0);
			break;

		case MotionNotify:
			tmpd->mx = event.xmotion.x;
			tmpd->my = event.xmotion.y;
//			printf("mouse: %d: %d %d\n", tmpd->win, tmpd->mx, tmpd->my);
			break;

		case ButtonPress:
			b=-1;
			if (event.xbutton.button == 1)
				b = 0;
			else if (event.xbutton.button == 2)
				b = 2;
			else if (event.xbutton.button == 3)
				b = 1;
//			if (b>=0)
//				Key_Event(K_MOUSE1 + b, true);

			tmpd->mb |= 1<<b;
			break;

		case ButtonRelease:
			b=-1;
			if (event.xbutton.button == 1)
				b = 0;
			else if (event.xbutton.button == 2)
				b = 2;
			else if (event.xbutton.button == 3)
				b = 1;
//			if (b>=0)
//				Key_Event(K_MOUSE1 + b, false);
			tmpd->mb &= ~(1<<b);
			break;

		case CreateNotify :
			win_x = event.xcreatewindow.x;
			win_y = event.xcreatewindow.y;
			break;

		case ConfigureNotify :
			win_x = event.xconfigure.x;
			win_y = event.xconfigure.y;
			break;
		}
	}
}

int Window_GetMousePos(displaywindow *wind, int *mx, int *my, int *mb)
{
	struct windowdata_s *tmpd;
	tmpd=wind->viddata;

	*mx=tmpd->mx;
	*my=tmpd->my;
	*mb=tmpd->mb;
	if(*mx==-1)return(-1);
	return(0);
}

int Window_PollKey(displaywindow *wnd, int key)
{
	struct windowdata_s *tmpd;
	tmpd=wnd->viddata;

	return(tmpd->keymap[key/8]&(1<<(key%8)));
}

byte *Window_GetWindowBuffer(displaywindow *wind)
{
	struct windowdata_s *tmpd;

	win_active=wind;
	tmpd=wind->viddata;
	return(tmpd->buf);
}

int Window_DrawFromBuf(int x, int y, int w, int h, int bx, int by, int bw, int bh, displaywindow *wnd, byte *buf)
{
	struct windowdata_s *tmpd;
	byte *scrbuf, *ibuf, *obuf;
	int i, j;

	tmpd=wnd->viddata;
	if(tmpd->isglx)return(-1);
	scrbuf=Window_GetWindowBuffer(wnd);

	for(i=0; i<h; i++)
	{
		ibuf=buf+((i*w)*4);
		obuf=scrbuf+((i+y)*tmpd->linesz)+(x*tmpd->pixsz);
		for(j=0; j<w; j++)
		{
			*obuf++=*ibuf++;
			*obuf++=*ibuf++;
			*obuf++=*ibuf++;
			ibuf++;
			obuf++;
		}
	}
}
