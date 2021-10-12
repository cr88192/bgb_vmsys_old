#ifndef __PDLIB_NET_H__
#define __PDLIB_NET_H__

#define PROJNAME	"BGB-OS1"
#define PROJVER		"0.6"

typedef struct {
byte data1[4];
byte data2[2];
byte data3[2];
byte data4[8];
}VGUID;

#include <pdnet/http.h>
#include <pdnet/parse.h>
#include <pdnet/rpcapi2.h>
#include <pdnet/meta0.h>

#endif
