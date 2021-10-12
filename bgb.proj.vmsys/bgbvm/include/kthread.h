#define PRIORITY_IDLE	0
#define PRIORITY_NORMAL	16

typedef struct kthread_t {
void *context; /* pthread data or stack */
struct kthread_t *next;
/* previous data */
struct kthread_t *rnext; /* list of all threads on system */
void *stacktop, *stackbottom; /* upper and lower extents of stack */
void **tld;	/* thread local data */

int flags;
int sleep_ticks;
short prio;			/* current priority of thread */
short prio_boost;	/* value to add when prio hits 0 */
}kthread;

typedef struct {
int lock;
}kmutex;

kthread *idle_thread, *current_thread;
kthread *rthread_list;

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
