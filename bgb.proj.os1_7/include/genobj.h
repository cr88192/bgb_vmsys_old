typedef struct GenObject_s {
int head;	/* type, flags, size */
}GenObject;

typedef struct obj_type_s {
struct obj_type_s *next;
int num;
char *name;
int (*destroy)(GenObject *obj);
GenObject *(*print)(GenObject *obj);
}obj_type;

int GenObj_Init();
GenObject *GenObj_Print(GenObject *p);
GenObject *GenObj_StructNew(char *form, ...);
GenObject *GenObj_NewString(char *s);
