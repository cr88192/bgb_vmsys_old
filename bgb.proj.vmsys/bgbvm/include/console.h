#define DEBUG_ERROR		25
#define	DEBUG_WARNING	50
#define DEBUG_NOTE		75

typedef struct ConsoleCommand_S {
struct ConsoleCommand_S *next;
char *name;
char *descr;
void *data;
int (*handler)(char *s, void *d);
}ConsoleCommand;

VFILE *kstdin, *kstdout;

//int Con_Printf(char *s, ...);
//int Con_DPrintf(int level, char *s, ...);
int Con_VPrintf(char *s, void **lst);
int Con_VSPrintf(char *d, char *s, void **p);

int Con_GetString(char *buf, char **t);

//int Con_Init();
int Con_Reset();

int Con_RegisterCommand(char *name, int (*proc)(char *s, void *d), void *data, char *descr);
int Con_ExecuteCommand(char *s);

//int Cmd_Init();
