#ifndef __PDNET_VAR_H__
#define __PDNET_VAR_H__

typedef struct PDLIB_Var_s {
struct PDLIB_Var_s *next;
char *name;
char *value, vallen;
double dvalue;
void (*onchange)(struct PDLIB_Var_s *v);
}PDLIB_Var;

typedef PDLIB_Var Var;
typedef PDLIB_Var var;

int Var_Init();
PDLIB_Var *Var_Lookup(char *name);
PDLIB_Var *Var_Create(char *name);
PDLIB_Var *Var_SetString(char *name, char *value);
char *Var_GetString(char *name);
float Var_GetValue(char *name);

#endif
