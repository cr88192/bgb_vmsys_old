#define PRIORITY_IDLE	0
#define PRIORITY_NORMAL	16

#define PRIORITY_UBER	256

typedef struct kmessage_t kmessage;
typedef struct kprocess_t kprocess;
typedef struct kthread_t kthread;

struct kmessage_t {
kmessage *next;
int conid;
int class;
int size;
void *buffer;
};

struct kprocess_t {
kprocess *next;
int pid;
int cr3;
kthread *first;			/* first thread in process */
char *name;

kmessage *msg_first, *msg_last;
};

struct kthread_t {
void *context;			/* pthread data or stack, ring 0 */
kthread *next;			/* next in terms of scheduler */
int cr3;			/* cr3 for thread (aka: page tables) */
/* end of assembler bits */
kprocess *process;
/* previous data */
kthread *rnext;			/* list of all threads on system */
kthread *pnext;			/* list of all threads in process */
void *stacktop, *stackbottom;	/* upper and lower extents of ring 0 stack */
void **tld;			/* thread local data */

int flags;
int sleep_ticks;
short prio;			/* current priority of thread */
short prio_boost;		/* value to add when prio hits 0 */
};

typedef struct {
int lock;
}kmutex;

kthread *idle_thread, *current_thread;
kthread *rthread_list;
kprocess *current_process;

kthread *kthread_spawn(int flags, int (*func)(void *data), void *data);
int kthread_start(kthread *thread, int prio);
int kthread_destroy(kthread *thread);
int kusleep(int usecs);
int kthread_dumpthread(kthread *thread);
int kthread_set_priority(kthread *thread, int prio);

kmutex *kmutex_new();
int kmutex_destroy(kmutex *mutex);
int kmutex_lock(kmutex *mutex);
int kmutex_unlock(kmutex *mutex);

int kthread_newkey();
void *kthread_getlocal(int key);
int kthread_setlocal(int key, void *value);
