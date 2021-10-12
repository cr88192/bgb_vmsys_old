typedef struct dirobj_s {
struct dirobj_s *next, *prev;
int head; /* type- low 9, flags- 9-15, size 16-31 */
char *name;
VADDR *addr;
void *data;
struct dirobj_s *first;
}dirobj;

typedef struct VDIR_T {
//dirobj *(*readdirobj)(struct VDIR_T *dir);
//int (*readdir)(char *buf, struct VDIR_T *dir);

int (*readdir)(long *buf, char **fields, long *key, struct VDIR_T *dir);
long (*dupkey)(long key, struct VDIR_T *dir);
int (*dropkey)(long key, struct VDIR_T *dir);

int (*close)(struct VDIR_T *dir);
int (*mkdir)(char *name, struct VDIR_T *dir);

VFILE *(*openf)(char *name, char *fl, struct VDIR_T *dir);
struct VDIR_T *(*opend)(char *name, struct VDIR_T *dir);
VFILE *(*openfk)(long key, char *fl, struct VDIR_T *dir);
struct VDIR_T *(*opendk)(long key, struct VDIR_T *dir);

long (*insert)(long *buf, char **fields, struct VDIR_T *dir);
int (*deletekey)(long key, struct VDIR_T *dir);

//dirobj *(*lookupdirobjaddr)(struct VDIR_T *dir, VADDR *addr);
//dirobj *(*lookupdirobjname)(struct VDIR_T *dir, char *name);
//dirobj *(*createdirobjaddr)(struct VDIR_T *dir, VADDR *addr);
//dirobj *(*createdirobjname)(struct VDIR_T *dir, char *name);
//int (*send)(struct VDIR_T *space, VADDR *target, void *msg, int len, int flags); /* used in the same bent way as read/write */

void *data;
void *userdata;
}VDIR;

typedef struct VMOUNT_T {
struct VMOUNT_T *next, *prev;
char *name;
int rprio, wprio, mark;
void *data;
VFILE *(*openf)(char *name, char *fl, struct VMOUNT_T *dir);
VDIR *(*opend)(char *name, struct VMOUNT_T *dir);
int (*unmount)(struct VMOUNT_T *dir);
}VMOUNT;

typedef struct VFSTYPE_T {
struct VFSTYPE_T *next, *prev;
char *name;
VMOUNT *(*mount)(char **options);
}VFSTYPE;

VMOUNT *VMount_ChooseBest(char *path, int w);
VFILE *VMount_Open(VMOUNT *vd, char *name, char *fl);
VDIR *VMount_OpenDir(VMOUNT *vd, char *name);


VFILE *VPath_OpenFile(char *name, char *fl);
int VPath_Init();
int VPath_PrintMounts();

VDIR *VPath_OpenDir(char *name);
int VPath_MkDir(char *name);

//int VDir_ReadDir(char *buf, VDIR *dir);
int VDir_ReadDir(long *buf, char **fields, long *key, VDIR *dir);
int VDir_CloseDir(VDIR *dir);
int VDir_MkDir(char *name, VDIR *dir);

//int VDir_RReadDir(long *buf, char **fields, VDIR *dir);

#if 0
dirobj *VDir_ReadDirObj(VDIR *dir);
//VFILE *VDir_Open(char *name, char *fl, VDIR *dir);
//VFILE *VDir_OpenDir(char *name, VDIR *dir);
dirobj *VDir_LookupObjAddr(VDIR *dir, VADDR *addr);
dirobj *VDir_LookupObjName(VDIR *dir, char *name);
dirobj *VDir_CreateObjAddr(VDIR *dir, VADDR *addr);
dirobj *VDir_CreateObjName(VDIR *dir, char *name);
#endif

int VPath_RegisterMount(VMOUNT *vd, char *path);
int VPath_Unmount(VMOUNT *mount);

int Vfs_RegisterType(char *name, VMOUNT *(*mount)(char **options));
VFSTYPE *Vfs_LookupType(char *type);
int Vfs_Mount(char *path, char *type, char **options);
