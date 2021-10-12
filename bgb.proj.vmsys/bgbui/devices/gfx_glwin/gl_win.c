/*
Copyright (C) 2003 Brendan G Bohannon

based on gl_vidnt.c:
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include <general.h>
#include <graphics/render.h>
//#include "keys.h"

#include <windows.h>
#include <commctrl.h>

#include <GL/GL.h>

HWND	mainwindow, dibwindow;
HGLRC	baseRC;
HDC		maindc;

int		DIBWidth, DIBHeight;
RECT		WindowRect;
DWORD		WindowStyle, ExWindowStyle;

HWND WINAPI InitializeWindow (HINSTANCE hInstance, int nCmdShow);

RECT		window_rect;

extern HINSTANCE	global_hInstance;
extern int		global_nCmdShow;
extern int		main_kill;

int window_center_x, window_center_y;
int window_mouse_buttons;

int window_width, window_height;

int GfxDrv_FillSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
//	kprint("coords (%d %d) (%d %d) (%d %d %d %d)\n", x, y, w, h,
//		r, g, b, a);

	glDisable (GL_TEXTURE_2D);
//	glDisable (GL_CULL_FACE);
	glDisable (GL_ALPHA_TEST);

	glColor4f (r/255.0, g/255.0, b/255.0, a/255.0);

	glBegin (GL_POLYGON);

	glVertex2f(x, y+h);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y+h);

	glEnd();

//	glEnable (GL_TEXTURE_2D);
//	glEnable (GL_CULL_FACE);
}

int Draw_SetSolid_2D(float aspect, int xo, int yo, int xs, int ys);
int Draw_SetSolid2_2D(float aspect, float size, float org[3], float angles[3], int xo, int yo, int xs, int ys);

void GfxDrv_BeginDrawing ()
{
	/* int *x, int *y, int *width, int *height */
	MSG	msg;

	float org[3];

	org[0]=0;
	org[1]=0;
	org[2]=0;

//	printf("begin\n");

	while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
	{
	      	TranslateMessage (&msg);
	      	DispatchMessage (&msg);
	}

//	*x = *y = 0;
//	*width = WindowRect.right - WindowRect.left;
//	*height = WindowRect.bottom - WindowRect.top;

	glViewport (0, 0, 800, 600);

	glClearColor (0, 0, 0, 1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	Draw_SetSolid_2D(4.0/3.0, 0, 0, 800, 600);
	Draw_SetSolid2_2D(4.0/3.0, 1000, org, org, 0, 0, 800, 600);
}


void GfxDrv_EndDrawing (void)
{
//	printf("end\n");

	glFinish();
	SwapBuffers(maindc);
}

int GfxDrv_DrawCell(byte *cell, int cw, int ch, int x, int y, int w, int h, int r, int g, int b, int a)
{
}


void GfxDrv_CenterWindow(HWND hWndCenter, int width, int height, BOOL lefttopjustify)
{
    RECT    rect;
    int     CenterX, CenterY;

	CenterX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	CenterY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	if (CenterX > CenterY*2)
		CenterX >>= 1;	// dual screens
	CenterX = (CenterX < 0) ? 0: CenterX;
	CenterY = (CenterY < 0) ? 0: CenterY;
	SetWindowPos (hWndCenter, NULL, CenterX, CenterY, 0, 0,
			SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);

	window_center_x = CenterX + (width/2);
	window_center_y = CenterY + (height/2);

	window_width=width;
	window_height=height;
}

int GfxDrv_VID_SetWindowedMode ()
{
	HDC	hdc;
	int	lastmodestate, width, height;
	RECT	rect;
	MSG	msg;

	WindowRect.top = WindowRect.left = 0;

	WindowRect.right = 800;
	WindowRect.bottom = 600;

	DIBWidth = 800;
	DIBHeight = 600;

	WindowStyle = WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU |
				  WS_MINIMIZEBOX;
	ExWindowStyle = 0;

	rect = WindowRect;
	AdjustWindowRectEx(&rect, WindowStyle, FALSE, 0);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// Create the DIB window
	dibwindow = CreateWindowEx (
		 ExWindowStyle,
		 "bgbui",
		 "BGB UI",
		 WindowStyle,
		 rect.left, rect.top,
		 width,
		 height,
		 NULL,
		 NULL,
		 global_hInstance,
		 NULL);

	if (!dibwindow)
		panic ("Couldn't create DIB window");

	// Center and show the DIB window
	GfxDrv_CenterWindow(dibwindow, WindowRect.right - WindowRect.left,
				 WindowRect.bottom - WindowRect.top, 0);

	ShowWindow (dibwindow, SW_SHOWDEFAULT);
	UpdateWindow (dibwindow);

// because we have set the background brush for the window to NULL
// (to avoid flickering when re-sizing the window on the desktop),
// we clear the window to black when created, otherwise it will be
// empty while Quake starts up.
	hdc = GetDC(dibwindow);
	PatBlt(hdc,0,0,WindowRect.right,WindowRect.bottom,BLACKNESS);
	ReleaseDC(dibwindow, hdc);

	mainwindow = dibwindow;

//	SendMessage (mainwindow, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
//	SendMessage (mainwindow, WM_SETICON, (WPARAM)FALSE, (LPARAM)hIcon);


	while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	Sleep (100);

	SetWindowPos (mainwindow, HWND_TOP, 0, 0, 0, 0,
				  SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW |
				  SWP_NOCOPYBITS);

	SetForegroundWindow (mainwindow);


	return -1;
}

void GfxDrv_GL_Init (void)
{
#if 0
	gl_vendor = glGetString (GL_VENDOR);
	Con_Printf ("GL_VENDOR: %s\n", gl_vendor);
	gl_renderer = glGetString (GL_RENDERER);
	Con_Printf ("GL_RENDERER: %s\n", gl_renderer);

	gl_version = glGetString (GL_VERSION);
	Con_Printf ("GL_VERSION: %s\n", gl_version);
	gl_extensions = glGetString (GL_EXTENSIONS);
	Con_Printf ("GL_EXTENSIONS: %s\n", gl_extensions);
#endif

//	Con_Printf ("%s %s\n", gl_renderer, gl_version);

//	CheckTextureExtensions ();
//	CheckMultiTextureExtensions ();

	glClearColor (1,0,0,0);
	glCullFace(GL_FRONT);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.666);

	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel (GL_FLAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

#if 0
	CheckArrayExtensions ();

	glEnable (GL_VERTEX_ARRAY_EXT);
	glEnable (GL_TEXTURE_COORD_ARRAY_EXT);
	glVertexPointerEXT (3, GL_FLOAT, 0, 0, &glv.x);
	glTexCoordPointerEXT (2, GL_FLOAT, 0, 0, &glv.s);
	glColorPointerEXT (3, GL_FLOAT, 0, 0, &glv.r);
#endif
}


void GfxDrv_AppActivate(BOOL fActive, BOOL minimize);

void	GfxDrv_VID_Shutdown (void)
{
   	HGLRC hRC;
   	HDC	  hDC;

	hRC = wglGetCurrentContext();
    	hDC = wglGetCurrentDC();

    	wglMakeCurrent(NULL, NULL);

    	if (hRC)
    	    wglDeleteContext(hRC);

	if (hDC && dibwindow)
		ReleaseDC(dibwindow, hDC);

	if (maindc && dibwindow)
		ReleaseDC (dibwindow, maindc);

	GfxDrv_AppActivate(0, 0);
}

BOOL GfxDrv_bSetupPixelFormat(HDC hDC)
{
    static PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
	1,				// version number
	PFD_DRAW_TO_WINDOW 		// support window
	|  PFD_SUPPORT_OPENGL 	// support OpenGL
	|  PFD_DOUBLEBUFFER ,	// double buffered
	PFD_TYPE_RGBA,			// RGBA type
	24,				// 24-bit color depth
	0, 0, 0, 0, 0, 0,		// color bits ignored
	0,				// no alpha buffer
	0,				// shift bit ignored
	0,				// no accumulation buffer
	0, 0, 0, 0, 			// accum bits ignored
	32,				// 32-bit z-buffer	
	0,				// no stencil buffer
	0,				// no auxiliary buffer
	PFD_MAIN_PLANE,			// main layer
	0,				// reserved
	0, 0, 0				// layer masks ignored
    };
    int pixelformat;

    if ( (pixelformat = ChoosePixelFormat(hDC, &pfd)) == 0 )
    {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE)
    {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
}



static byte        scantokey[128] = 
					{ 
//  0           1       2       3       4       5       6       7 
//  8           9       A       B       C       D       E       F 
	0  ,    27,     '1',    '2',    '3',    '4',    '5',    '6', 
	'7',    '8',    '9',    '0',    '-',    '=',    K_BACKSPACE, 9, // 0 
	'q',    'w',    'e',    'r',    't',    'y',    'u',    'i', 
	'o',    'p',    '[',    ']',    13 ,    K_CTRL,'a',  's',      // 1 
	'd',    'f',    'g',    'h',    'j',    'k',    'l',    ';', 
	'\'' ,    '`',    K_SHIFT,'\\',  'z',    'x',    'c',    'v',      // 2 
	'b',    'n',    'm',    ',',    '.',    '/',    K_SHIFT,'*', 
	K_ALT,' ',   0  ,    K_F1, K_F2, K_F3, K_F4, K_F5,   // 3 
	K_F6, K_F7, K_F8, K_F9, K_F10, K_PAUSE  ,    0  , K_HOME, 
	K_UPARROW,K_PGUP,'-',K_LEFTARROW,'5',K_RIGHTARROW,'+',K_END, //4 
	K_DOWNARROW,K_PGDN,K_INS,K_DEL,0,0,             0,              K_F11, 
	K_F12,0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0,        // 5 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0, 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0,        // 6 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0, 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0         // 7 
					}; 

static byte        shiftscantokey[128] = 
					{ 
//  0           1       2       3       4       5       6       7 
//  8           9       A       B       C       D       E       F 
	0  ,    27,     '!',    '@',    '#',    '$',    '%',    '^', 
	'&',    '*',    '(',    ')',    '_',    '+',    K_BACKSPACE, 9, // 0 
	'Q',    'W',    'E',    'R',    'T',    'Y',    'U',    'I', 
	'O',    'P',    '{',    '}',    13 ,    K_CTRL,'A',  'S',      // 1 
	'D',    'F',    'G',    'H',    'J',    'K',    'L',    ':', 
	'"' ,    '~',    K_SHIFT,'|',  'Z',    'X',    'C',    'V',      // 2 
	'B',    'N',    'M',    '<',    '>',    '?',    K_SHIFT,'*', 
	K_ALT,' ',   0  ,    K_F1, K_F2, K_F3, K_F4, K_F5,   // 3 
	K_F6, K_F7, K_F8, K_F9, K_F10, K_PAUSE  ,    0  , K_HOME, 
	K_UPARROW,K_PGUP,'_',K_LEFTARROW,'%',K_RIGHTARROW,'+',K_END, //4 
	K_DOWNARROW,K_PGDN,K_INS,K_DEL,0,0,             0,              K_F11, 
	K_F12,0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0,        // 5 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0, 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0,        // 6 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0, 
	0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0  ,    0         // 7 
					}; 

int GfxDrv_MapKey (int key)
{
	key = (key>>16)&255;
	if (key > 127)
		return 0;
	if (scantokey[key] == 0)
		kprint("key 0x%02x has no translation\n", key);
	return scantokey[key];
}

/*
===================================================================

MAIN WINDOW

===================================================================
*/

/*
================
ClearAllStates
================
*/
void GfxDrv_ClearAllStates (void)
{
	int		i;
	
// send an up event for each key, to make sure the server clears them all
	for (i=0 ; i<256 ; i++)
	{
//		Key_Event (i, 0);
	}

//	Key_ClearStates ();
//	IN_ClearStates ();
}

void GfxDrv_AppActivate(BOOL fActive, BOOL minimize)
{
	MSG msg;
	HDC			hdc;
	int			i, t;
	static int	sound_active;

//	ActiveApp = fActive;
//	Minimized = minimize;

#if 0
// enable/disable sound on focus gain/loss
	if (!ActiveApp && sound_active)
	{
		S_BlockSound ();
		sound_active = 0;
	}
	else if (ActiveApp && !sound_active)
	{
		S_UnblockSound ();
		sound_active = -1;
	}
#endif

#if 0
	if (fActive)
	{
		if (modestate == MS_FULLDIB)
		{
			IN_ActivateMouse ();
			IN_HideMouse ();
			if (vid_canalttab && vid_wassuspended) {
				vid_wassuspended = 0;
				ChangeDisplaySettings (&gdevmode, CDS_FULLSCREEN);
				ShowWindow(mainwindow, SW_SHOWNORMAL);
			}
		}
		else if ((modestate == MS_WINDOWED) && _windowed_mouse.value && key_dest == key_game)
		{
			IN_ActivateMouse ();
			IN_HideMouse ();
		}
	}
#endif

#if 0
	if (!fActive)
	{
		if (modestate == MS_FULLDIB)
		{
			IN_DeactivateMouse ();
			IN_ShowMouse ();
			if (vid_canalttab) { 
				ChangeDisplaySettings (NULL, 0);
				vid_wassuspended = -1;
			}
		}
		else if ((modestate == MS_WINDOWED) && _windowed_mouse.value)
		{
			IN_DeactivateMouse ();
			IN_ShowMouse ();
		}
	}
#endif
}


/* main window procedure */
LONG WINAPI GfxDrv_MainWndProc (
    HWND    hWnd,
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
    LONG    lRet = 1;
	int		fwKeys, xPos, yPos, fActive, fMinimized, temp;
	extern unsigned int uiWheelMessage;

//	if ( uMsg == uiWheelMessage )
//		uMsg = WM_MOUSEWHEEL;

//	printf("msg %d\n", uMsg);

    switch (uMsg)
    {
//		case WM_KILLFOCUS:
//			if (modestate == MS_FULLDIB)
//				ShowWindow(mainwindow, SW_SHOWMINNOACTIVE);
//			break;

		case WM_CREATE:
			break;

		case WM_MOVE:
			xPos = (int) LOWORD(lParam);
			yPos = (int) HIWORD(lParam);

			window_center_x=xPos+(window_width/2);
			window_center_y=yPos+(window_height/2);

			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			GfxDev_Key_Event (GfxDrv_MapKey(lParam), -1);
			break;
			
		case WM_KEYUP:
		case WM_SYSKEYUP:
			GfxDev_Key_Event (GfxDrv_MapKey(lParam), 0);
			break;

		case WM_SYSCHAR:
		// keep Alt-Space from happening
			break;

	// this is complicated because Win32 seems to pack multiple mouse events into
	// one update sometimes, so we always check all states and look for events
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:
			temp = 0;

			if (wParam & MK_LBUTTON)
				temp |= 1;

			if (wParam & MK_RBUTTON)
				temp |= 4;

			if (wParam & MK_MBUTTON)
				temp |= 2;

			window_mouse_buttons = temp;
//			IN_MouseEvent (temp);

			break;

		// JACK: This is the mouse wheel with the Intellimouse
		// Its delta is either positive or neg, and we generate the proper
		// Event.
//		case WM_MOUSEWHEEL: 
//			if ((short) HIWORD(wParam) > 0) {
//				Key_Event(K_MWHEELUP, -1);
//				Key_Event(K_MWHEELUP, 0);
//			} else {
//				Key_Event(K_MWHEELDOWN, -1);
//				Key_Event(K_MWHEELDOWN, 0);
//			}
//			break;

    	case WM_SIZE:
            break;

   	    case WM_CLOSE:
//			if (MessageBox (mainwindow, "Are you sure you want to quit?", "Confirm Exit",
//						MB_YESNO | MB_SETFOREGROUND | MB_ICONQUESTION) == IDYES)
//			{
				main_kill = 1;
//			}

	        break;

		case WM_ACTIVATE:
			fActive = LOWORD(wParam);
			fMinimized = (BOOL) HIWORD(wParam);
			GfxDrv_AppActivate(!(fActive == WA_INACTIVE), fMinimized);

		// fix the leftover Alt from any Alt-Tab or the like that switched us away
//			ClearAllStates ();

			break;

   	    case WM_DESTROY:
        {
			if (dibwindow)
				DestroyWindow (dibwindow);

            PostQuitMessage (0);
        }
        break;

//		case MM_MCINOTIFY:
//            lRet = CDAudio_MessageHandler (hWnd, uMsg, wParam, lParam);
//			break;

    	default:
            /* pass all unhandled messages to DefWindowProc */
            lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }

    /* return 1 if handled message, 0 if not */
    return lRet;
}

void GfxDrv_VID_InitDIB (HINSTANCE hInstance)
{
	WNDCLASS		wc;
	HDC				hdc;
	int				i;

	/* Register the frame class */
    wc.style         = 0;
    wc.lpfnWndProc   = (WNDPROC)GfxDrv_MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = 0;
    wc.hCursor       = LoadCursor (NULL,IDC_ARROW);
	wc.hbrBackground = NULL;
    wc.lpszMenuName  = 0;
    wc.lpszClassName = "bgbui";

    if (!RegisterClass (&wc) )
		panic ("Couldn't register window class");
}

void	GfxDrv_Start ()
{
	int		i, existingmode;
	int		basenummodes, width, height, bpp, findbpp, done;
	byte	*ptmp;
	char	gldir[256];
	HDC		hdc;
	DEVMODE	devmode;

	memset(&devmode, 0, sizeof(devmode));

//	hIcon = LoadIcon (global_hInstance, MAKEINTRESOURCE (IDI_ICON2));

//	InitCommonControls();

	GfxDrv_VID_InitDIB (global_hInstance);
//	basenummodes = nummodes = 1;

//	VID_InitFullDIB (global_hInstance);

//	if (COM_CheckParm("-window"))
	if (1)
	{
		hdc = GetDC (NULL);

		if (GetDeviceCaps(hdc, RASTERCAPS) & RC_PALETTE)
		{
			panic ("Can't run in non-RGB mode");
		}

		ReleaseDC (NULL, hdc);
	}

//	vid_initialized = -1;

//	DestroyWindow (hwnd_dialog);

//	VID_SetMode (0, palette);
	GfxDrv_VID_SetWindowedMode ();

    maindc = GetDC(mainwindow);
	GfxDrv_bSetupPixelFormat(maindc);

    baseRC = wglCreateContext( maindc );
	if (!baseRC)
		panic ("Could not initialize GL (wglCreateContext failed).\n\nMake sure you in are 65535 color mode, and try running -window.");

    if (!wglMakeCurrent( maindc, baseRC ))
		panic ("wglMakeCurrent failed");

	GfxDrv_GL_Init ();
}

int GfxDrv_Init()
{
}
