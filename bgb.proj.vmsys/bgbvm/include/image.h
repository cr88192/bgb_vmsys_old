/*
2003-08-19:
store and load images.
images will work by having a tag byte and a byte which is presently reserved,
followed by tag specific data.

string {
u2 len;
byte data[len];
};

0: unused

1: typedef
{
byte tag;
byte _resv;
string name;
string def;
}

2: struct
{
byte tag;
byte _resv;
u2 type;
u4 len;
byte data[len];
}

3: string
{
byte tag;
byte _resv;
string s;
}

4: namedobj
{
byte tag;
byte _resv;
string s;
u4 idx;
}

all numbers will be big-endian.
pointers will be encoded as indices.

 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

FILE *pdlib_image_fd;

char *pdlib_image_types[256];

void *pdlib_image_objptrs[4096];
int pdlib_image_objs;
int pdlib_image_objpos;

void *pdlib_image_strptrs[4096];
int pdlib_image_strings;
int pdlib_image_strpos;

char *pdlib_image_names[256];
void *pdlib_image_namedobjs[256];

extern PDLIB_ObjType *pdlib_objtypes;

int PDLIB_Image_StoreTypes();
int PDLIB_Image_GetType(char *ty);
int PDLIB_Image_WriteShort(short v);
int PDLIB_Image_WriteLong(long v);
int PDLIB_Image_WriteString(char *str);
int PDLIB_Image_GetObj(void *p);
int PDLIB_Image_GetString(char *s);
void *PDLIB_Image_WriteType(char *ty, void *obj, int count);
void *PDLIB_Image_WriteObj(PDLIB_ObjType *ty, void *obj, int size);
int PDLIB_Image_StoreStrings();
int PDLIB_Image_StoreObjs();
int PDLIB_Image_NameObj(char *name, void *ptr);
int PDLIB_Image_StoreNames();
int PDLIB_StoreImage(char *name);

char *PDLIB_ReadString(FILE *fd);
int PDLIB_ReadShort(FILE *fd);
int PDLIB_ReadLong(FILE *fd);
int PDLIB_LoadImage(char *name);

#endif
