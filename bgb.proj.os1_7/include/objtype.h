#ifndef __OBJTYPE_H__
#define __OBJTYPE_H__

typedef struct PDLIB_ObjType_s PDLIB_ObjType;
typedef struct PDLIB_ObjInfo_s PDLIB_ObjInfo;

struct PDLIB_ObjType_s {
PDLIB_ObjType *next;
char *name;
char *form;
int size;
};

struct PDLIB_ObjInfo_s {
PDLIB_ObjType *type;
int size;
};


/*
form will be a string defining the structure of the object, it will consist
of a list of ents, each with the form: "tag[:name];"

each tag will be a string, either:
"<type>" or "*<type>" (pointers).
"<cnt><type>" will allow arrays, also "<cnt>*<type>" allows an array of
pointers.

tags:
string: pointer to character data;
int: int value;
long: long value;
float: float value;
<defined obj type>: that type of obj.

types will be required to be properly aligned.
 */

int ObjType_FormSize(char *form);
PDLIB_ObjType *ObjType_NewType(char *name, char *form);
PDLIB_ObjType *ObjType_FindType(char *type);
void *ObjType_New(char *type, int size);
PDLIB_ObjType *ObjType_GetType(void *p);
int ObjType_GetSize(void *p);
int ObjType_Init();

#endif
