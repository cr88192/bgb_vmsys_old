#ifndef __GFX_CONTEXT_H__
#define __GFX_CONTEXT_H__

typedef unsigned int GColor;	/* 24 bit rgba, r is in low order bits */
typedef int GVec[2];
typedef int GRect[4];

typedef struct gfx_image_t GImage;
typedef struct gfx_context_t GSurface;
typedef struct gfx_object_t GObject;

struct gfx_image_t {
void *data;
GVec size;
char type;
char flags;
};

struct gfx_context_t {
int (*draw_image)(GSurface *self, GRect dst, GImage *img, GRect src);
GImage *(*read_image)(GSurface *self, GRect sz);

int (*set_pen)(GSurface *self, GColor clr);
int (*set_penbg)(GSurface *self, GColor clr);
int (*plot_pixel)(GSurface *self, GVec pos);
int (*fill_rect)(GSurface *self, GRect reg);

void (*query)(GSurface *self, GRect clip, char *bpp, char *type,
	char *abits);
void (*destroy)(GSurface *self);
void *ptr; /* used by functions */
int pen, penbg;

};

struct gfx_object_t {
GObject *next;
GObject *prev;
GObject *first;
GObject *owner;

GRect org; /* origin/size */
GVec pan; /* scrolled pos of context */
GSurface *context;
};

#define GFX_TYPE_LOCAL		0 /* whatever type, only to be used by gui */
#define GFX_TYPE_PALETTE8	1 /* palettized color, 8bits/pixel, linear */
#define GFX_TYPE_GREY8		2 /* greyscale, 8bits/pixel, linear */
#define GFX_TYPE_RGB24		3 /* rgb color, 24bits/pixel, linear */
#define GFX_TYPE_16COLOR	4 /* 16 color, 4bits/pixel, linear */
#define GFX_TYPE_RGB15		5 /* rgb color, 15bits/pixel+1bit alpha, linear */

#define GFX_FLAG_ALPHA		1 /* alpha(translucency) factor */

#endif
