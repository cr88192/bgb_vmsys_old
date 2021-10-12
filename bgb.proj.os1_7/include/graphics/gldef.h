#include <GL/gl.h>

typedef struct gltexinfo_s {
int texnum;
float s, t, s2, t2;
}gltexinfo;

int Tex_AllocTexnum();
int Tex_FreeTexnum(int n);
int Tex_AllocBlock(int *x, int *y, int *b);
int Tex_Resample(byte *src, int iw, int ih, byte *dst, int ow, int oh);
teximage *Tex_LoadTexture(int w, int h, byte *buf, int calcmip);
teximage *Tex_FromTexturefile(texturefile *tf);

int Tex_Init();
