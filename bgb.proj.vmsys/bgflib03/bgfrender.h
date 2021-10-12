#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>
#include <GL/GL.h>
#include <general.h>
#include <graphics/render.h>

#ifndef __BGFRENDER_H__
#define __BGFRENDER_H__

#define PIECE_NONE	0
#define PIECE_UNION	1
#define PIECE_MESH	2
#define PIECE_CUBE	3
#define PIECE_CYLINDER	4
#define PIECE_SPHERE	5
#define PIECE_DISK	6
#define PIECE_DIPLANE	7	//height map front, possible map back

typedef struct piece_s {
struct piece_s *first, *next;
char name[16];

int type;
vec3 min, max;
vec3 org, dir;
float trad, brad, h;

float transform[16]; //transformation, column major

struct bgftexinfo_s *skin;

byte *hmap; //front
byte *hmap2; //back (DIPLANE)
int hmapwidth, hmapheight;
float hmapbias, hmapscale;

//mesh data
int firstvert;
int numverts;

int firstpoly;
int numpolys;
}piece_t;


typedef struct bone_s {
struct bone_s *first, *next;
char name[16];

float org[64*3];
float ang[64*3];
piece_t *piece;
}bone_t;

typedef struct bgftexinfo_s {
struct bgftexinfo_s *next, *first;
char name[16];
int num;
int width, height;

vec3 org;
vec3 norm;
vec3 up;
vec3 right;
float scale_s, scale_t;
}bgftexinfo_t;

typedef struct bgfmodinfo_s {
struct bgfmodinfo_s *next;
bone_t *bones;
piece_t *pieces;
bgftexinfo_t *textures;
}bgfmodinfo_t;

extern float *vecbuf;
extern int vecs, frames, polys;
extern char framenames[256][16];
extern int *polybuf;


extern piece_t piece[256];
extern int pieces;

extern bone_t bone[256];
extern int bones;

extern bgftexinfo_t texture[256];
extern int textures;

extern int cvec;
extern int sw, sh;

extern vec3 v_origin, v_angles;
extern int v_frame;

extern int fl;

int Draw_SetPerspective_3D(float aspect, int fov, vec3 org, vec3 angles, int xo, int yo, int xs, int ys);
int Draw_Bind(int texnum);
int Key_Check(int keynum);
bgftexinfo_t *mod_findskin(char *name);
int sa_fatal(char *s, ...);

int Tex_LoadFile(char *n, int *w, int *h);

float dot(vec3 a, vec3 b);
float proj(vec3 pt, vec3 pl);
int cross (vec3 v1, vec3 v2, vec3 v3);
int ptadj(vec3 pt, vec3 dir, vec3 org, vec3 d);
int vecz(vec3 v);
int MatN_MatMultf(float *a, int ah, int aw, float *b, int bh, int bw, float *c);
int MatN_FillIdentityf(float *a, int n);
int Vec16_RotateMatrixf(float *amat, float *angles, float *bmat);
int Vec16_TranslateMatrixf(float *amat, float *ofs, float *bmat);
int MatN_MatMultVectorf(float *a, float *b, float *c, int n);
int MatN_Copyf(float *a, float *b, int h, int w);

extern int main_kill;

extern unsigned char keybuf[32];

int BGFLB_Init();
piece_t *BGF_NewPiece();
bone_t *BGF_NewBone();
bgftexinfo_t *BGF_NewTexture();
bgfmodinfo_t *BGF_NewModel();


#endif
