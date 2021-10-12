#ifndef __PDLIB_RPCAPI_H__
#define __PDLIB_RPCAPI_H__

typedef struct NET_Export_s NET_Export;
typedef struct NET_Interface_s NET_Interface;
typedef struct NET_Reference_s NET_Reference;

typedef struct NET_Array_s NET_Array;
typedef struct NET_Struct_s NET_Struct;

struct NET_Export_s {
NET_Export *next;
char *name;
void *(*func)();
};



struct NET_Interface_s {
NET_Interface *next;
char *name;	//protocol name
NET_Reference *(*decode_url)(char *s);
char *(*encode_url)(NET_Reference *ref);
void *(*rpc_call)(NET_Reference *ref, void **args);
int (*poll)();
void *(*fetch)(NET_Reference *ref);
};

struct NET_Reference_s {
NET_Interface *iface;
void *nodeinfo;
void *refinfo;
};

struct NET_Array_s {
void **values;
};

struct NET_Struct_s {
char **names;
void **values;
};

void *NetVal_WrapInt(int i);
void *NetVal_WrapStr(char *s);
void *NetVal_WrapFloat(double f);
void *NetVal_WrapArray(void *a);

#endif
