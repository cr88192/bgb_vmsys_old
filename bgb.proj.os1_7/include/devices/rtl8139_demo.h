#define	ULONG	unsigned long
#define BOOLEAN	int
#define	TRUE	1
#define	FALSE	0
//#define NULL	0

typedef enum _TSDSTATUS{
	TSDSTATUS_0,
	TSDSTATUS_OWN,
        TSDSTATUS_TOK,
        TSDSTATUS_BOTH
}TSDSTATUS;

typedef	struct _TX_DESCRIPTOR{
	unsigned char  *OriginalBufferAddress;	//only used to work around
						//dword alignment problem	
	unsigned char  *buffer;		//virtual address
	unsigned long	PhysicalAddress;//physical address
	unsigned short	PacketLength;
}TX_DESCRIPTOR, *PTX_DESCRIPTOR;

typedef struct _BufferList{
	unsigned char 		*Buffer;
	unsigned short		BufferLength;
	struct _BufferList      *Next;
}BufferList,*PBufferList;

typedef struct _PACKET{
	unsigned char	BufferCount;
	unsigned short	PacketLength;
	BufferList	Buffers;
}PACKET,*PPACKET;

#if 0
	unsigned	ROK : 1;
	unsigned        FAE : 1;
	unsigned	CRC : 1;
	unsigned	LONG: 1;
	unsigned	RUNT: 1;
	unsigned	ISE : 1;
	unsigned	reserved : 7;
	unsigned	BAR : 1;
	unsigned	PAM : 1;
	unsigned	MAR : 1;
#endif

typedef struct _PACKETHEADER{
	unsigned short	flags;
	unsigned short	PacketLength;
}PACKETHEADER,*PPACKETHEADER;

int	SendPacket(	PPACKET Packet );
void    ReadPacket(	PPACKET	RxPacket );
BOOLEAN LoadDriver();
BOOLEAN UnloadDriver();
