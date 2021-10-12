typedef struct dirobj_s {
struct dirobj_s *next, *prev;
int head; /* type- low 9, flags- 9-15, size 16-31 */
char *name;
VADDR *addr;
void *data;
struct dirobj_s *first;
}dirobj;

typedef struct VDIR_T {
int (*readdir)(long *buf, char **fields, long *key, struct VDIR_T *dir);
int (*readdir2)(char **names, void **values, long *key, struct VDIR_T *dir);
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
VFILE *(*open_sl)(int idx, char *fl, struct VMOUNT_T *dir);
int (*create_sl)(char *type, struct VMOUNT_T *dir);
}VMOUNT;

typedef struct VFSTYPE_T {
struct VFSTYPE_T *next, *prev;
char *name;
VMOUNT *(*mount)(char **options);
int (*format)(char **options);
}VFSTYPE;

typedef struct VFS_SLTYPE_T {
struct VFS_SLTYPE_T *next, *prev;
char *name;
VDIR *(*opend)(int idx, struct VMOUNT_T *mnt);
}VFS_SLTYPE;

typedef struct VFSNAMESPACE_T {
struct VFSNAMESPACE_T *next, *prev;

char *name;
void *data;

VFILE *(*openf)(char *name, char *fl, struct VFSNAMESPACE_T *ns);
VDIR *(*opend)(char *name, struct VFSNAMESPACE_T *ns);
}VFSNAMESPACE;

VMOUNT *VMount_ChooseBest(char *path, int w);
VFILE *VMount_Open(VMOUNT *vd, char *name, char *fl);
VDIR *VMount_OpenDir(VMOUNT *vd, char *name);


VFILE *VPath_OpenFile(char *name, char *fl);
int VPath_Init();
int VPath_PrintMounts();

VDIR *VPath_OpenDir(char *name);
int VPath_MkDir(char *name);

int VDir_ReadDir(long *buf, char **fields, long *key, VDIR *dir);
int VDir_ReadDir2(char **names, void **values, long *key, VDIR *dir);
int VDir_CloseDir(VDIR *dir);
int VDir_MkDir(char *name, VDIR *dir);

int VMount_RegisterMount(VMOUNT *vd, char *path);
int VMount_Unmount(VMOUNT *mount);

VFSTYPE *Vfs_RegisterType(char *name, VMOUNT *(*mount)(char **options));
VFSTYPE *Vfs_LookupType(char *type);
int Vfs_Mount(char *path, char *type, char **options);
