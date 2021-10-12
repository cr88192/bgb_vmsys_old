#ifndef __GFXAPI_H__
#define __GFXAPI_H__

int GfxApi_WriteUByte(VFILE *fd, int v);
int GfxApi_WriteSByte(VFILE *fd, int v);
int GfxApi_WriteUShort(VFILE *fd, int v);
int GfxApi_WriteSShort(VFILE *fd, int v);
int GfxApi_WriteULong(VFILE *fd, int v);
int GfxApi_WriteSLong(VFILE *fd, int v);

int GfxApi_WriteUInt(VFILE *fd, int v);
int GfxApi_WriteSInt(VFILE *fd, int v);

int GfxApi_WriteFloat(VFILE *fd, float f);
int GfxApi_WriteDouble(VFILE *fd, double f);

int GfxApi_ReadULong(VFILE *fd);
int GfxApi_ReadSLong(VFILE *fd);

int GfxApi_WriteOpcode(VFILE *fd, int v);
int GfxApi_WriteString(VFILE *fd, char *t);
int GfxApi_WriteStringU2(VFILE *fd, u2 *t);

int GfxApi_WriteSymbol(VFILE *fd, char *t);
int GfxApi_WriteParam(VFILE *fd, char *t);

int GfxApi_WriteConst(VFILE *fd, int v);


int GfxApi_WriteVertex3f(VFILE *fd, double x, double y, double z);
int GfxApi_WriteVertex3fv(VFILE *fd, float *v);
int GfxApi_WriteVertex3dv(VFILE *fd, double *v);

int GfxApi_FillSquare(VFILE *fd, int x, int y, int w, int h, int r, int g, int b, int a);
int GfxApi_MoveTo(VFILE *fd, int x, int y);
int GfxApi_Show(VFILE *fd, char *s);
int GfxApi_ShowU2(VFILE *fd, u2 *s);
int GfxApi_FontSize(VFILE *fd, int sz);
int GfxApi_FontSize2(VFILE *fd, int xsz, int ysz);
int GfxApi_TextColor(VFILE *fd, int r, int g, int b, int a);
int GfxApi_SetFont(VFILE *fd, char *s);
int GfxApi_Translate(VFILE *fd, int x, int y);
int GfxApi_Scale(VFILE *fd, float x, float y);
int GfxApi_SetRange(VFILE *fd, int left, int right, int bottom, int top);
int GfxApi_PushMatrix(VFILE *fd);
int GfxApi_PopMatrix(VFILE *fd);
int GfxApi_BeginDrawing(VFILE *fd);
int GfxApi_EndDrawing(VFILE *fd);

int GfxApi_PushClip(VFILE *fd);
int GfxApi_PopClip(VFILE *fd);
int GfxApi_SetClip(VFILE *fd, float x1, float y1, float x2, float y2);
int GfxApi_Translate3(VFILE *fd, float x, float y, float z);
int GfxApi_Scale3(VFILE *fd, float x, float y, float z);
int GfxApi_Rotate3(VFILE *fd, float x, float y, float z, float a);
int GfxApi_Perspective(VFILE *fd, int fovx, int fovy);
int GfxApi_Color(VFILE *fd, float r, float g, float b, float a);
int GfxApi_Vec3(VFILE *fd, float x, float y, float z);
int GfxApi_TexCoord2(VFILE *fd, float s, float t);

int GfxApi_Begin(VFILE *fd, int t);
int GfxApi_End(VFILE *fd, int t);

int GfxApi_BindTex(VFILE *fd, int t);
int GfxApi_UnbindTex(VFILE *fd);
int GfxApi_Texture(VFILE *fd, byte *data, int num, int w, int h, int enc);
int GfxApi_TransformMatrix(VFILE *fd, float *mat);
int GfxApi_TransformMatrixd(VFILE *fd, double *mat);

#endif
