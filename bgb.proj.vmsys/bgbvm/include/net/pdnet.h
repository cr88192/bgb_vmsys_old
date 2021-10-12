#ifndef __PDLIB_NET_H__
#define __PDLIB_NET_H__

typedef struct {
byte data1[4];
byte data2[2];
byte data3[2];
byte data4[8];
}VGUID;

#include <net/http.h>
#include <net/sxrpc.h>
#include <net/parse.h>
#include <net/rpcapi2.h>
#include <net/meta0.h>
#include <net/mrpt02.h>

#endif
