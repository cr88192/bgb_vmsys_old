#ifndef __T_EVENT_H__
#define __T_EVENT_H__

struct event_t {
struct event_t *next,*prev;
float delay; /* delay, seconds */
float remtm; /* time left */
int flags;
int (*cproc)(struct event_t *);
};

#define EVENT_FL_RESPAWN 1

int TEV_Init();
int TEV_AddProc(int (*proc)(struct event_t *),float delay,int flags);

#endif
