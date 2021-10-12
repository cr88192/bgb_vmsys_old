#include <math.h>

typedef double	vec2[2];
typedef double	vec3[3];
typedef double	vec4[4];
typedef double	vec5[5];
typedef double	vec6[6];
typedef double	vec9[9];	/* normals, etc */
typedef double	vec12[12];	/* XYZSTRGBAij- */
typedef double	vec15[15];	/* OBBs, vec9, vec3, vec3 */
typedef double	vec16[16];	/* 4x4 matrices, etc. */

typedef float	vec2f[2];
typedef float	vec3f[3];
typedef float	vec4f[4];
typedef float	vec6f[6];	/* bboxes */

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
int Vec16_TranslateMatrix(vec16 amat, vec3 pos, vec16 bmat);
void Vec16_InvertAngles(vec16 amat, vec16 bmat);

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

void Vec3_CrossProduct (const vec3 v1, const vec3 v2, vec3 cross);
void Vec3_ToSphericalCoords(vec3 a, vec3 b);
void Vec3_FromSphericalCoords(vec3 a, vec3 b);

void Vec3_RotatePoint(vec3 p, const vec3 angles);
void Vec3_CalcAngleVectors (const vec3 angles, vec3 forward, vec3 right, vec3 up);

double Scaler_Random(); /* random number, 0 to 1 */
double Scaler_SignRandom(); /* -1 to 1 */

/* collide.c */
int Vec3_MakeVectorPerpendicular(vec3 n, vec3 v, vec3 d);
int Vec3_MovePointOutOfSpace(vec3 s, vec16 m, vec3 d);
int Vec3_MovePointIntoSpace(vec3 s, vec16 m, vec3 d);
int Poly_FigureRegion(double *vert, int sz, double *dst, int n, double th);
int Poly_PointInRegion(vec3 point, double *clips, int n);
int Poly_LineInRegion(vec3 start, vec3 end, double *clips, int n);
//int Obb_FillList(vec16 amat, BBox *obb, double *lst);
int Obb_CheckOverlap(vec9 amat, double *alst, int na, double *blst, int nb);
//int Obb_CheckCollision(
//	vec16 amat, vec16 admat, BBox *aobb,
//	vec16 bmat, vec16 bdmat, BBox *bobb);
//int Obb_CheckCollisionLine(
//	vec16 amat, vec16 admat, BBox *aobb, vec3 src, vec3 dst);
