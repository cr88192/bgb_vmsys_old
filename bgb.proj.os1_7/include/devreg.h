struct reg_driver_t {
struct reg_driver_t *next, *prev, *up;
struct reg_driver_t *first;

char *name;
void *data;
VFILE *(*open_stream)(char *name, void *data);
int flags;
};

struct reg_driver_t *Driver_Find(char *name);
VFILE *Driver_OpenStream(char *name);
int Driver_RegisterStream(char *name, VFILE *(open_proc)(char *name, void *data), void *data);
