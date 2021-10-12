#include <math.h>

typedef double	vec2d[2];
typedef double	vec3d[3];
typedef double	vec4d[4];
typedef double	vec5d[5];
typedef double	vec6d[6];
typedef double	vec9d[9];	/* normals, etc */
typedef double	vec12d[12];	/* XYZSTRGBAij- */
typedef double	vec15d[15];	/* OBBs, vec9, vec3, vec3 */
typedef double	vec16d[16];	/* 4x4 matrices, etc. */

typedef float	vec2f[2];
typedef float	vec3f[3];
typedef float	vec4f[4];
typedef float	vec6f[6];	/* bboxes */
typedef float	vec16f[16];	/* 4x4 matrices */

/* mathlib */
int MatN_MatMult(double *a, int ah, int aw, double *b, int bh, int bw, double *c);
int MatN_MatMultVector(double *a, double *b, double *c, int n);
int MatN_MatMultScaler(double *a, double b, double *c, int n);

int MatN_ResizeMatrix(double *a, int ah, int aw, double *b, int bh, int bw);
int MatN_FillIdentity(double *a, int n);
int MatN_Copy(double *a, double *b, int h, int w);

void MatN_GetLowerMatrix(double *a, double *b, int n);
void MatN_GetUpperMatrix(double *a, double *b, int n);

int MatN_SwapOrder(double *a, double *b, int n);
int MatN_Inverse(double *a, double *b, int n);

int Vec16_RotateMatrix(double *amat, double *angles, double *bmat);
int Vec16_TranslateMatrix(vec16d amat, vec3d pos, vec16d bmat);
void Vec16_InvertAngles(vec16d amat, vec16d bmat);

int VecN_Copy(double *a, double *b, int n);
int VecN_ResizeVector(double *a, int an, double *b, int bn);
double VecN_DotProduct(double *a, double *b, int n);
double VecN_Length(double *a, int n);
double VecN_Normalize(double *a, double *b, int n);
void VecN_Add(double *a, double *b, double *c, int n);
void VecN_Subtract(double *a, double *b, double *c, int n);
void VecN_Scale(double *a, double b, double *c, int n);
void VecN_ScaleAdd(double *a, double b, double *c, double *d, int n);
void VecN_Zero(double *a, int n);
void VecN_Const(double *a, double b, int n);

void Vec3_CrossProduct (const vec3d v1, const vec3d v2, vec3d cross);
void Vec3_ToSphericalCoords(vec3d a, vec3d b);
void Vec3_FromSphericalCoords(vec3d a, vec3d b);

void Vec3_RotatePoint(vec3d p, const vec3d angles);
void Vec3_CalcAngleVectors (const vec3d angles, vec3d forward, vec3d right, vec3d up);

double Scaler_Random(); /* random number, 0 to 1 */
double Scaler_SignRandom(); /* -1 to 1 */

/* mathlibf.h */
int MatNF_MatMult(float *a, int ah, int aw, float *b, int bh, int bw, float *c);
int MatNF_MatMultVector(float *a, float *b, float *c, int n);
int MatNF_MatMultScaler(float *a, float b, float *c, int n);
int MatNF_ResizeMatrix(float *a, int ah, int aw, float *b, int bh, int bw);
int MatNF_FillIdentity(float *a, int n);
int MatNF_Copy(float *a, float *b, int h, int w);
void MatNF_GetLowerMatrix(float *a, float *b, int n);
void MatNF_GetUpperMatrix(float *a, float *b, int n);
int MatNF_SwapOrder(float *a, float *b, int n);
int MatNF_Inverse(float *a, float *b, int n);
int Vec16F_RotateMatrix(float *amat, float *angles, float *bmat);
int Vec16F_TranslateMatrix(vec16f amat, vec3f pos, vec16f bmat);
void Vec16F_InvertAngles(vec16f amat, vec16f bmat);

int VecNF_Copy(float *a, float *b, int n);
int VecNF_ResizeVector(float *a, int an, float *b, int bn);
float VecNF_DotProduct(float *a, float *b, int n);
float VecNF_Length(float *a, int n);
float VecNF_Normalize(float *a, float *b, int n);
void VecNF_Add(float *a, float *b, float *c, int n);
void VecNF_Subtract(float *a, float *b, float *c, int n);
void VecNF_Scale(float *a, float b, float *c, int n);
void VecNF_ScaleAdd(float *a, float b, float *c, float *d, int n);
void VecNF_Zero(float *a, int n);
void VecNF_Const(float *a, float b, int n);

void Vec3F_CrossProduct (const vec3f v1, const vec3f v2, vec3f cross);

/* collide.c */
int Vec3_MakeVectorPerpendicular(vec3d n, vec3d v, vec3d d);
int Vec3_MovePointOutOfSpace(vec3d s, vec16d m, vec3d d);
int Vec3_MovePointIntoSpace(vec3d s, vec16d m, vec3d d);
int Poly_FigureRegion(double *vert, int sz, double *dst, int n, double th);
int Poly_PointInRegion(vec3d point, double *clips, int n);
int Poly_LineInRegion(vec3d start, vec3d end, double *clips, int n);
//int Obb_FillList(vec16d amat, BBox *obb, double *lst);
int Obb_CheckOverlap(vec9d amat, double *alst, int na, double *blst, int nb);
//int Obb_CheckCollision(
//	vec16d amat, vec16d admat, BBox *aobb,
//	vec16d bmat, vec16d bdmat, BBox *bobb);
//int Obb_CheckCollisionLine(
//	vec16d amat, vec16d admat, BBox *aobb, vec3d src, vec3d dst);
