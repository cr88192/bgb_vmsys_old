#ifndef __META0_H__
#define __META0_H__

typedef struct Meta0_PortInfo_s Meta0_PortInfo;
typedef struct Meta0_Con_s Meta0_Con;

struct Meta0_PortInfo_s {
VFILE *sock;
int port;
char *name;

int num;

int (*new_con)(Meta0_Con *con);
int (*input)(Meta0_Con *con);
int (*closed)(Meta0_Con *con);
};

struct Meta0_Con_s {
VFILE *sock;
VADDR *addr;	//initial recieved addr, port may change

Meta0_PortInfo *info;
void *data;

int num;
byte *buf, *end;
};

#endif
