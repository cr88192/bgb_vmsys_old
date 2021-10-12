/*
BGB Message Relay Protocol

make network interface a stack machine (like vid driver).
it will handle directing messages to remote pids and will dispatch
incomming messages to appropriate pids.

an incomming pid will have the full route info to get it back to the
source. each socket will also have an associated pid to handle all
undirected messages (maybe).
I could also use a ports-like system to handle directing undirected
messages to appropriate handlers (each port could have a name, and the
messages could be directed at that name).

encoding:
multibyte values will be in big-endian order.

when the stream is in command mode a byte will be read and interpreted:
cmd&7:
0: number
	(cmd>>3)&7
		0=unsigned
		1=signed
		2=float
		3=widenum, 128-1024 bit
		4=misc/const

	(cmd>>6)&3
		0=1 byte/u128
		1=2 byte/u128
		2=4 byte/u128
		3=8 byte/u128

	misc:
		low 4 bits type, rest data.
		0: misc constants
			0x10=false
			0x20=true
			0x30=null
			0x40=eol
		1: characters

1: command
	2 bytes, upper 4 bits and next byte (forming upper 8 of opcode)

2: object
	object has upper 5 bits as a type. this is followed by data
		relating to the the object.
	1: data object
		followed by byte encoding and 32 bit length.
		data may be broken into multiple writes.
	2: symbol
		contains a byte length and so many bytes of data.
	3: string
		contains a short length and so many shorts of data.
	4: negotiation
		contains a short length and so many bytes of data.
		"keyword" or "var=value"
	5: binary command
		contains a short opcode, a short length, and so many bytes of
		data.
		these are not to be directed at the interpreter, rather they
		are related to network features. these are also not to effect
		the future behavior of the net stack/opcodes.
		unknown binary commands are to be ignored, space is divided:
			0-4095: mrp
			4096-32767: implementation
			32768-65535: possible user/implementation

opcodes:
I will start at 0x100 (avoiding clashes with vid protocol space).

*/

#ifndef __BGBMRP_H__
#define __BGBMRP_H__
#include <graphics/opcodes.h>

#define MRPOP_CONS	0x100	//a b -> (a . b)
#define MRPOP_RCONS	0x101	//a b -> (b . a)
#define MRPOP_LIST	0x102	//MARK ... -> (...)
#define MRPOP_LISTI	0x103	//MARK a... b -> (a... . b)
#define MRPOP_VECTOR	0x104	//MARK ... -> #(...)
#define MRPOP_BYTEVEC	0x105	//data-object len -> byte-vector, deprecated

#define MRPOP_ADDR	0x108	//addr port type -> ADDR
				//type: 1=ipv4udp, 2=ipv4tcp

#define MRPOP_RREF	0x109	//refnum type -> LREF
#define MRPOP_LREF	0x10A	//ADDR refnum type -> LREF

#define MRPOP_DISPATCH	0x10B	//msg (LREF from) refnum
#define MRPOP_RDISPATCH	0x10C	//msg (LREF from) refnum cont, sends RETURN
#define MRPOP_SETTER	0x10D	//setter cont-id
#define MRPOP_RETURN	0x10E	//value cont-id

#define MRPOP_YREF	0x10F	//refnum -> obj
#define MRPOP_COPY	0x110	//refnum cont -> sends RETURN w/flat version
#define MRPOP_FLAT	0x111	//flat-obj -> obj
#define MRPOP_BEGINFLAT	0x112	//marks beginning of flat obj


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

#endif
