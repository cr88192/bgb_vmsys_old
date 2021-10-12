#ifndef __ATA_REQ_H__
#define __ATA_REQ_H__

struct req_t {
struct req_t *next;
int cmd;
int blk;
int drv;
int flags;
void *buf;
};

struct chs_t {
int cylinder;
int head;
int sector;
};

#define REQ_CMD_READ 1
#define REQ_CMD_WRITE 2

#define REQ_FL_DONE 1

#endif
