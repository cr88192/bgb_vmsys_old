#ifndef __BGBMRP01_H__
#define __BGBMRP01_H__

#define MRPOP_NOP	0x00	//
#define MRPOP_POP	0x01	//a ->
#define MRPOP_MARK	0x02	// -> MARK
#define MRPOP_CONS	0x03	//a b -> (a . b)
#define MRPOP_LIST	0x04	//MARK ... -> (...)
#define MRPOP_LISTI	0x05	//MARK a... b -> (a... . b)
#define MRPOP_VECTOR	0x06	//MARK ... -> #(...)
#define MRPOP_INVOP	0x07	//a ->
#define MRPOP_INVTYPE	0x08	//a ->
#define MRPOP_REQATTR	0x09	//name ->
#define MRPOP_REPATTR	0x0A	//name value ->
#define MRPOP_LOOKUP	0x0B	//name -> value
#define MRPOP_BIND	0x0C	//name value ->
#define MRPOP_PING	0x0D	//->
#define MRPOP_PONG	0x0E	//->


#define MRPOP_ADDR	0x20	//addr port type -> ADDR
				//type: 1=ipv4udp, 2=ipv4tcp

#define MRPOP_GUID	0x21	//guid -> ADDR

#define MRPOP_YREF	0x22	//refnum -> obj
#define MRPOP_RREF	0x23	//refnum type -> LREF
#define MRPOP_LREF	0x24	//ADDR refnum type -> LREF
#define MRPOP_DISPATCH	0x25	//msg (LREF from) refnum cont, sends RETURN
#define MRPOP_SETTER	0x26	//setter cont-id
#define MRPOP_RETURN	0x27	//value cont-id
#define MRPOP_POPRET	0x28	//a cont ->
#define MRPOP_DROPREF	0x29	//a ->

#define MRPOP_SEARCH	0x2A	//dst src cont ttl ->
#define MRPOP_FOUND	0x2B	//src cont dst ttl ->

#define MRPOP_STUB	0x40	//a ->
#define MRPOP_MIRROR	0x41	//refnum cont ->, sends RETURN w/flat version
#define MRPOP_NOTIFY	0x42	//to from ->
#define MRPOP_NOTIFYA	0x43	//to from ->
#define MRPOP_NOTIFYDEL	0x44	//to from ->
#define MRPOP_DELTA	0x45	//obj pattern value stamp ->
#define MRPOP_DELTA2	0x46	//stamp pairs to from ->
#define MRPOP_TYFLAT	0x47	//flat type -> obj
#define MRPOP_TYSTUB	0x48	//mirrors type -> obj, rsrc-id type -> obj

#define MRPVAL_MISC	0x0
#define MRPVAL_CHAR	0x1
#define MRPVAL_STACK	0x2

#define MRPVAL_FALSE	0x10
#define MRPVAL_TRUE	0x20
#define MRPVAL_NULL	0x30
#define MRPVAL_EOL	0x40

#define MRPVAL_IPV4UDP	1
#define MRPVAL_IPV4TCP	2

//data type
#define MRPVAL_DATA_RAW		(0<<3)
#define MRPVAL_DATA_BYTEVECTOR	(1<<3)
#define MRPVAL_DATA_BLOCK	(2<<3)

#define MRPVAL_DATA_DEFLATERAW	1

//RREF/LREF type, low 3 bits type:
#define MRPVAL_TYPE_OBJECT	1	//next 6 bits object type
#define MRPVAL_TYPE_CONS	2

#define MRPVAL_TYPE_CLOSURE	((1<<3)|1)
#define MRPVAL_TYPE_ENV		((2<<3)|1) //environment
#define MRPVAL_TYPE_ENVOBJ	((3<<3)|1) //object
#define MRPVAL_TYPE_CONTEXT	((4<<3)|1) //interpreter context/thread
#define MRPVAL_TYPE_FUNCTION	((5<<3)|1)
#define MRPVAL_TYPE_GENERAL_BI	((6<<3)|1)

typedef struct {
byte data1[4];
byte data2[2];
byte data3[2];
byte data4[8];
}VGUID;

#define MRP_MAXCONS 64
#define MRP_FINDBUF 128

typedef struct {
elem con;
int pid;
int type;
}MRP_LongRef;

typedef struct {
VGUID guid;
char name[64];
VADDR addr;
int state; //0=unused, 1=connecting, 2=connected, 3=disconnected

elem stack_elem;
elem *stack;
int stackpos, mark;

VFILE *sock;
byte *buffer, *bufend;

int rlen, renc; //remaining data to recieve, encoding
byte *rbuf, *erbuf; //recieve buffer and end recieve buf

int conlast;	//time of last connection attempt

int lastdelta;	//time of last delta
elem deltas;	//list of deltas

int pong;	//set to 0 if pong recieved
}MRP_Connection;


typedef struct {
VGUID guid;
int id;
MRP_Connection *con;
}MRP_FindBuf;


VFILE *TCP_OpenListen(int port);
VFILE *TCP_OpenConnect(VADDR *targ);

int NET_CreateGuid(VGUID *buf);
int NET_GuidEqualP(VGUID *a, VGUID *b);
char *NET_Guid2String(VGUID *guid);
char *NET_String2Guid(VGUID *guid, char *s);

#include <net/mrp_trans.h>

#endif
