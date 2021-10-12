typedef struct r_image_s {
int width;
int height;
unsigned short *data;
}r_image;

typedef struct r_console_s {
r_image *image;
int x, y, xs, ys;
u2 bgc, fgc;
}r_console;

r_image *RImage_NewImage(int w, int h);
int RImage_RenderCell(r_image *img, int x, int y, byte *cellbuf, int cellnum, u2 c);
r_console *RImage_NewConsole(int xs, int ys);
int RImage_ScrollUp(r_image *img, int lines, u2 fill);

int RConsole_WChar(r_console *con, int c);
int RConsole_WString(r_console *con, u2 *s);
