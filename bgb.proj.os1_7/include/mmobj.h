#ifndef __MMOBJ_H__
#define __MMOBJ_H__

#define OBJ_INT			1
#define OBJ_FLOAT		2
#define OBJ_STRING		3
#define OBJ_UVI			4
#define OBJ_SYMBOL		5
#define OBJ_FUNCTION	6

int MMObj_Init();
int MMObj_NewBlock();
int MMObj_AllocWords(int num);
int MMObj_FreeWords(int start, int len);
int MMObj_MarkObjectMap(int num);
unsigned long *MMObj_GetWordPointer(int start);
int MMObj_NewObject(int type, int size);
int MMObj_NewStringS(char *s);
char *MMObj_GetString(int num);
void *MMObj_GetObjPointer(int num, int type);
int MMObj_GetObjType(int num);

#endif
