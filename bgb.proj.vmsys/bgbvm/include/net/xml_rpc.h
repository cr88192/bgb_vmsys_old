#ifndef __XML_RPC_H__
#define __XML_RPC_H__

typedef struct {
VFILE *sock;
int num;
byte *buf, *end;

int state;
byte *rbuf, *erbuf;
int rlen;

char req[1024];
}HTTP_Con;

#define HTTPSTATE_REQ	0
#define HTTPSTATE_GET	1
#define HTTPSTATE_POST	2
#define HTTPSTATE_RECD	3
#define HTTPSTATE_CLOSE	4

#endif
