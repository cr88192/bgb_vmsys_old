typedef struct var_s {
struct var_s *next;
char *name;
char *value, vallen;
double dvalue;
void (*onchange)(struct var_s *v);
}var;

int Var_Init();
var *Var_Lookup(char *name);
var *Var_Create(char *name);
var *Var_SetString(char *name, char *value);
