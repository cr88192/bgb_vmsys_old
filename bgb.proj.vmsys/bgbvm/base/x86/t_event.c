/*
	timed events
*/

#include <x86/t_event.h>
#include <kfunc.h>

struct event_t *tev_root;

static struct event_t ev_root; /* real root */
static int tev_busy; /* if 1 then don't work */
static int tev_started;

void tev_think()
{
	struct event_t *cur;

	if(tev_busy)return;
	if(tev_started!=-1)return;

	tev_busy=1;
	cur=tev_root->next;
	while(cur)
	{
		cur->remtm-=0.01;
		if(cur->remtm<=0)
		{
			cur->cproc(cur);
			if(cur->flags&1)
			{
				cur->remtm=cur->delay;
			}
			else
			{
				if(cur->prev)cur->prev->next=cur->next;
				if(cur->next)cur->next->prev=cur->prev;
			}
		}
		cur=cur->next;
	}
	tev_busy=0;
}

int TEV_Init()
{
	kprint("timed events init.\n");
	tev_root=&ev_root;
	ev_root.next=NULL;
	ev_root.prev=NULL;
	ev_root.delay=0;
	ev_root.remtm=0;
	ev_root.flags=0;
	ev_root.cproc=NULL;
	tev_busy=0;
	tev_started=-1;
}

int TEV_AddProc(int(*proc)(struct event_t *),float delay,int flags)
{
	struct event_t *cur;
	cur=tev_root;
	while(cur->next)cur=cur->next;
	cur->next=kalloc(sizeof(struct event_t));
	cur->next->next=NULL;
	cur->next->prev=cur;
	cur->next->delay=delay;
	cur->next->remtm=delay;
	cur->next->flags=flags;
	cur->next->cproc=proc;
}
