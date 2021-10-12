#ifndef __OBJ3D_H__
#define __OBJ3D_H__

#define OBJ3D_NONE	0
#define OBJ3D_UNION	1
#define OBJ3D_MESH	2
#define OBJ3D_CUBE	3
#define OBJ3D_CYLINDER	4
#define OBJ3D_SPHERE	5
#define OBJ3D_DISK	6
#define OBJ3D_DIPLANE	7
#define OBJ3D_SPRITE	8

#define OBJ3D_STUB	31

typedef struct {
int type;
elem name;
elem texture;
elem mirrors;
vec3 min, max;
float radius, rad_top, rad_bottom;
float height;

vec3 front;
//I will drop origin/orientation, stuff will be transformed
double transform[16];
}Obj3D_Primitive;

typedef struct {
elem name;
elem first;
elem texture;
elem mirrors;
double transform[16];
}Obj3D_Group;

typedef struct {
elem name;
int num;
int width, height;

vec3f org;
vec3f norm;
vec3f up;
vec3f right;
float scale_s, scale_t;
}Obj3D_TexInfo;

typedef struct {
elem name;
elem frames;
elem mirrors;
float radius;
float height;

vec3 origin;
vec3 front;

int frame;
}Obj3D_Sprite;

#endif
