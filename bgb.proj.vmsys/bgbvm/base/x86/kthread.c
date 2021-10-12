#include <general.h>

kthread *active_list;
kthread *sleep_list;
kthread *inactive_list;

kthread *current_thread=NULL, *idle_thread=NULL;
kthread *rthread_list=NULL;

static kthread idled_thread;
static int last_ticks;

extern int time_system_ticks;

int kthread_init()
{
	kprint("kthread init.\n");

	sleep_list=NULL;
	current_thread=&idled_thread;
	idle_thread=current_thread;
	active_list=idle_thread;
	inactive_list=NULL;

	idle_thread->next=NULL;
	idle_thread->prio=16;
	idle_thread->prio_boost=16;

	idle_thread->stacktop=(void *)0x8000;
	idle_thread->stackbottom=(void *)0x6000;
	idle_thread->tld=(void **)0x7C00;

	memset(idle_thread->tld, 0, 1024);
}

kthread *kthread_insert_active(kthread *thread)
{
	kthread *cur;

#if 0
	cur=active_list;
	if(!cur)
	{
//		kprint("first\n");
		thread->next=active_list;
		active_list=thread;
	}else
	{
//		kprint("end\n");
		while(cur->next)cur=cur->next;
		cur->next=thread;
		thread->next=NULL;
	}
	return(0);
#endif

//	kprint("insert");

	if(active_list)
	{
		cur=active_list;
		while(cur->prio>=thread->prio)
		{
			if(!cur->next)break;
			cur=cur->next;
//			kprint(".");
		}
		thread->next=cur->next;
		cur->next=thread;

//		kprint("\n");
		return(cur);
	}else
	{
		thread->next=active_list;
		active_list=thread;
//		kprint(" same\n");
	}
	return(NULL);
}

int kthread_schedule()
{
	static int sleep_ticks=0;
	kthread *cur, *last;
	int rticks;

	active_list=current_thread->next;
	current_thread->prio--;
	if(current_thread->prio<=0)current_thread->prio=current_thread->prio_boost;

	kthread_insert_active(current_thread);

	rticks=time_system_ticks-last_ticks;
	last_ticks=time_system_ticks;
	if(sleep_ticks<=0)
	{
		last=NULL;
		cur=sleep_list;
		while(cur)
		{
			cur->sleep_ticks-=rticks;
			if(cur->sleep_ticks<=0)
			{
				if(last)last->next=cur->next;
					else sleep_list=cur->next;
				kthread_insert_active(cur);
			}
			cur=cur->next;
		}
		sleep_ticks=10;
	}else sleep_ticks-=rticks;

	current_thread=active_list;
	return(0);
}

int kthread_terminate()
{
	active_list=current_thread->next;

	current_thread->next=inactive_list;
	inactive_list=current_thread;

	current_thread=active_list;

	return(0);
}

int kthread_ll_thread(kthread *thread, int (*entry)(void *data), void *data);

kthread *kthread_spawn(int flags, int (*func)(void *data), void *data)
{
	kthread *tmp;
	int *stack;

	tmp=kalloc(sizeof(kthread));

	stack=kalloc(1<<14);
	if(!stack)
	{
		kprint("could not alloc stack.\n");
		return(NULL);
	}
//	tmp->context=stack+(1<<12)-256;

	tmp->stackbottom=stack;
	tmp->stacktop=tmp->stackbottom+(1<<14);
	tmp->tld=tmp->stacktop-1024;

	tmp->context=tmp->tld;

	memcpy(tmp->tld, current_thread->tld, 1024);

	tmp->rnext=rthread_list;
	rthread_list=tmp;

//	kprint("ll creator.\n");

	kthread_ll_thread(tmp, func, data);

//	kprint("thread created.\n");
	return(tmp);
}

/* int kthread_start(kthread *thread, int prio)
{
} */

int kthread_dumpthread(kthread *thread)
{
	int *stack;

	if(!thread)return(0);

	stack=thread->context;

//	kprint("stack: %X\t", stack);
	kprint("EFLAGS: %X\tCS:EIP %X:%X\n", stack[10], stack[9], stack[8]);

	kprint("EAX: %X\t", stack[7]);
	kprint("ECX: %X\t", stack[6]);
	kprint("EDX: %X\t", stack[5]);
	kprint("EBX: %X\n", stack[4]);
	kprint("ESP: %X\t", stack[3]);
	kprint("EBP: %X\t", stack[2]);
	kprint("ESI: %X\t", stack[1]);
	kprint("EDI: %X\n", stack[0]);
}

int kthread_destroy(kthread *thread)
{
	kfree(thread->context);
	kfree(thread);
}

int kthread_ll_endquantum();

int kusleep(int usecs)
{
	int init_ticks;

	init_ticks=time_system_ticks;
	while((time_system_ticks-init_ticks)<(usecs/10000))
		kthread_ll_endquantum();
	return(0);
}

int kthread_blocked()
{
	kthread_ll_endquantum();
	return(0);
}

int kthread_set_priority(kthread *thread, int prio)
{
	thread->prio=prio;
	return(0);
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
	while(mutex->lock)kthread_blocked(); //while locked
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


int kthread_lastkey=0;

int kthread_newkey()
{
	return(kthread_lastkey++);
}

void *kthread_getlocal(int key)
{
	if(!current_thread)return(NULL);
	return(current_thread->tld[key]);
}

int kthread_setlocal(int key, void *value)
{
	if(!current_thread)return(-1);
	current_thread->tld[key]=value;
	return(0);
}
