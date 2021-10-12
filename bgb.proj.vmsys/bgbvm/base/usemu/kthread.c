#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <general.h>

typedef struct {
pthread_t pthread;
pthread_mutex_t *mutex;
}threaddata;

typedef struct {
kthread *thread;
int (*func)(void *data);
void *data;
}ktdata;

kthread *idle_thread, *current_thread;
kthread *rthread_list=NULL;

static pthread_key_t key_curthread;

int kthread_init()
{
	kprint("kthread init.\n");

	pthread_key_create(&key_curthread, NULL);
}

void *kthread_pt_entry(ktdata *kt)
{
	threaddata *td;

	td=kt->thread->context;
	pthread_mutex_lock(td->mutex);
	pthread_mutex_unlock(td->mutex);

	pthread_setspecific(key_curthread, kt->thread);

//	Con_Reset();

	kt->func(kt->data);
	free(kt);
	return(NULL);
}

kthread *kthread_spawn(int flags, int (*func)(void *data), void *data)
{
	kthread *tmp;
	threaddata *tmpdata;
	ktdata *ktdat;
	void *stack;

	pthread_t *pthread;
	pthread_mutex_t *mutex;
	pthread_attr_t *attr;

	tmp=malloc(sizeof(kthread)+sizeof(threaddata));
	tmpdata=(threaddata *)(tmp+1);
	tmp->context=tmpdata;

	tmp->rnext=rthread_list;
	rthread_list=tmp;

	attr=malloc(sizeof(pthread_attr_t));
	pthread_attr_init(attr);

	stack=malloc(1<<14);
	tmp->stackbottom=stack;
	tmp->stacktop=stack+(1<<14);
	tmp->tld=stack+(1<<14)-1024;

	current_thread=pthread_getspecific(key_curthread);
	if(current_thread)memcpy(tmp->tld, current_thread->tld, 1024);

//	pthread_attr_setstack(attr, tmp->stacktop-1024, (1<<14)-1024);

//	kprint("%X %X\n", tmp->stacktop, tmp->stackbottom);

	mutex=malloc(sizeof(pthread_mutex_t));

	tmpdata->mutex=mutex;

	ktdat=malloc(sizeof(ktdata));
	ktdat->thread=tmp;
	ktdat->func=func;
	ktdat->data=data;

	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(mutex);

	pthread_create(&tmpdata->pthread, attr, &kthread_pt_entry, ktdat);

	free(attr);

	return(tmp);
}

int kthread_start(kthread *thread, int prio)
{
	threaddata *td;

//	kprint("%X %X\n", thread->stacktop, thread->stackbottom);

	td=thread->context;
	pthread_mutex_unlock(td->mutex);

	return(0);
}

int kthread_destroy(kthread *thread)
{
	threaddata *td;
	void *buf;

	td=thread->context;
	pthread_cancel(td->pthread);
	pthread_join(td->pthread, &buf);

	free(td);
	free(thread);

	return(0);
}

int kusleep(int usecs)
{
	usleep(usecs);
}

int kthread_blocked()
{
}

int kthread_dumpthread(kthread *thread)
{
}

int kthread_set_priority(kthread *thread, int prio)
{
}

kmutex *kmutex_new()
{
	kmutex *tmp;
	tmp=kalloc(sizeof(kmutex));

	tmp->lock=0;
	return(tmp);
}

int kmutex_destroy(kmutex *mutex)
{
	kfree(mutex);
}

int kmutex_lock(kmutex *mutex)
{
	int i;

	i=1<<20;

	while(mutex->lock)kthread_blocked(); //while locked
//	if(!i)panic("deadlock.\n");

	mutex->lock++; //try lock

	if(mutex->lock!=1) //possibly beaten to it
	{
		if(mutex->lock)mutex->lock--;
		kthread_blocked();
		return(kmutex_lock(mutex));
	}
	return(0);
}

int kmutex_reslock(kmutex *mutex)
{
	mutex->lock++; //try lock

	while(mutex->lock>1)kthread_blocked(); //while locked

	if(mutex->lock!=1) //possibly beaten to it
	{
		if(mutex->lock)mutex->lock--;
		kthread_blocked();
		return(kmutex_lock(mutex));
	}
	return(0);
}

int kmutex_unlock(kmutex *mutex)
{
	if(mutex->lock)mutex->lock--;
	return(0);
}

int kthread_lastkey;

int kthread_newkey()
{
	return(kthread_lastkey++);
}

void *kthread_getlocal(int key)
{
	kthread *thread;
	void *tmp;

	thread=pthread_getspecific(key_curthread);
	if(!thread)return(NULL);

	tmp=thread->tld[key];

//	if(tmp)Text_WriteString("thread ok\n");

	return(tmp);
}

int kthread_setlocal(int key, void *value)
{
	kthread *thread;

	thread=pthread_getspecific(key_curthread);
	if(!thread)return(0);

//	Text_WriteString("set tld ok");
	thread->tld[key]=value;

	return(0);
}
