typedef struct displaywindow_s {
struct displaywindow_s *next, *prev;

int width, height;
void *viddata; /* data for whatever the video driver is */
}displaywindow;

int Window_Init();
displaywindow *Window_NewWindow(int width, int height);
int Window_SetWindow(displaywindow *wind);
int Window_BeginDrawing();
int Window_EndDrawing();
int Window_GetMousePos(displaywindow *wind, int *mx, int *my, int *mb);
displaywindow *Window_NewWindow_NOGL(int width, int height);
int Window_Destroy(displaywindow *wnd);
int Window_DeInit();
int Window_PollKey(displaywindow *wnd, int key);

int Window_RegisterKeyHandler(int (*handler)(displaywindow *wnd, int key));
int Window_RemoveKeyHandler(int hnd);
