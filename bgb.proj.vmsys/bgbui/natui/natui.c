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

int win_init = 0;

int mouse_x, mouse_y;
int win_x, win_y;

displaywindow *win_active, *win_root;
int (*key_handler[16])(displaywindow *wnd, int key);

int Window_Init()
{
}

displaywindow *Window_NewWindow(int width, int height)
{
}

displaywindow *Window_NewWindow_NOGL(int width, int height)
{
}

int Window_Destroy(displaywindow *wnd)
{
}

int Window_DeInit()
{
}

int Window_SetWindow(displaywindow *wind)
{
}

static void HandleEvents(void);

int Window_BeginDrawing()
{
}

int Window_EndDrawing()
{
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
}

int Window_DrawFromBuf(int x, int y, int w, int h, int bx, int by, int bw, int bh, displaywindow *wnd, byte *buf)
{
}
