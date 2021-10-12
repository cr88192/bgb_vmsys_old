#ifndef __PDLIB_NET_H__
#define __PDLIB_NET_H__

typedef struct {
byte data1[4];
byte data2[2];
byte data3[2];
byte data4[8];
}VGUID;

#include <pdnet/vars.h>

#include <pdnet/http.h>
#include <pdnet/sxrpc.h>
#include <pdnet/parse.h>
#include <pdnet/rpcapi2.h>
#include <pdnet/meta0.h>
#include <pdnet/mrpt022.h>

#endif
