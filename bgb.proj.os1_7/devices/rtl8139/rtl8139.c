#include <general.h>
#include <devices/rtl8139.h>
#include <devices/rtl8139_demo.h>

typedef struct PacketBuf_s PacketBuf;

struct PacketBuf_s {
PacketBuf *next;
int len;
void *buffer;
};

int	INTR;

void InitHardware();
void InitSoftware();
void TxInterruptHandler();
int RxInterruptHandler();

//Transmit variables
#define TX_SW_BUFFER_NUM	4
TX_DESCRIPTOR	TxDesc[TX_SW_BUFFER_NUM];
unsigned char	TxHwSetupPtr;
unsigned char	TxHwFinishPtr;
unsigned char	TxHwFreeDesc;

//Receive variables
unsigned char	*RxBuffer,*RxBufferOriginal;
unsigned long	RxBufferPhysicalAddress;
unsigned int	RxReadPtrOffset;
PPACKET		pLeadingReadPacket;	//should be a link list
unsigned long	PacketReceivedGood = 0;
unsigned long	ByteReceived = 0;

#define	RX_BUFFER_SIZE		16*1024
#define RX_MAX_PACKET_LENGTH	1600
#define RX_MIN_PACKET_LENGTH	64
#define	RX_READ_POINTER_MASK	0x3FFC

unsigned int	IOBase,Irq;
unsigned char *Buffer;
unsigned int	PhysicalAddrBuffer;

PacketBuf *rtl8139_first;
PacketBuf *rtl8139_last;
int rtl8139_listen;

PacketBuf *rtl8139_outfirst;
PacketBuf *rtl8139_outlast;
int rtl8139_sendactive;
byte rtl8139_mac[8];

void ShowStatistics()
{
	kprint("Packet Received:: %u",PacketReceivedGood);
	kprint("Byte   Received:: %9lu",ByteReceived);
}

int FindIOIRQ(unsigned int *IOBase,unsigned int *IRQ)
{
	unsigned int i,j,PciData,BaseAddr,Interrupt;
	for(i=0;i<32;i++)
	{
		j=0x80000000+(i<<11);
		outportd(0xcf8,j);
		PciData=inportd(0xcfc);
//		if(PciData==0x813910ec)
		if(PciData==0x13001186)
		{
			outportd(0xcf8,j+0x10);
			*IOBase=inportd(0xcfc);
			*IOBase &= 0xfffffff0;
			outportd(0xcf8,j+0x3c);
			*IRQ=inportd(0xcfc);
			*IRQ &= 0xff;
			return -1;
		}
	}
	return 0;
}


int ComputeInterrupt(int IrqNumber)
{
//	if(IrqNumber <=8) return IrqNumber+8;
//	else		  return IrqNumber+0x68;
	return(0x20+IrqNumber);
}

/////////////////////////////////////////////////////////////////////////
//Our Interrupt Service Routine (ISR)
/////////////////////////////////////////////////////////////////////////
void NewFunction(void)
{
	unsigned int curISR;
//	disable();	// == _asm cli

//	kprint("RTL8139: Int\n");

	curISR = inportw(IOBase + ISR);
	if( (curISR & R39_INTERRUPT_MASK) != 0)
	{
		do
		{
			if(curISR & ISR_PUN)
			{
//		 		ProcessLingChange();	//should write this code someday
				outportw(IOBase + ISR , ISR_PUN);
			}
			if(curISR & ISR_TOK)
			{
				TxInterruptHandler();
				outportw(IOBase + ISR, ISR_TOK);
			}
			if(curISR & ISR_TER)
			{
				outportb(IOBase + TCR , TCR_CLRABT);
				outportw(IOBase + ISR , ISR_TER);
			}
			if( curISR & (ISR_ROK|ISR_RER|ISR_RXOVW|ISR_FIFOOVW) )
			{
				if(curISR & ISR_ROK)
				{
					RxInterruptHandler();
				}
				outportw(IOBase + ISR, ISR_ROK | ISR_RER |ISR_RXOVW | ISR_FIFOOVW);
			}
			curISR = inportw(IOBase + ISR);
		}while( (curISR & R39_INTERRUPT_MASK) != 0);
//	_asm int 3;
//_asm	mov	 al,020h
//_asm	out	 0a0h,al		 //;issue EOI to 2nd 8259
//_asm	out	 20h,al		  //;Issue EOI to 1nd 8259
		outportb(0xa0, 0x20);
		outportb(0x20, 0x20);
	}
	else
	{//not our interrupt, should call original interrupt service routine.
	 // OldFunction();
	}
//	enable();	// == _asm sti
}

//////////////////////////////////////////////////////////////////////////
//Initialization part
//////////////////////////////////////////////////////////////////////////
void InitHardware()
{
	int i, j;

	outportb(IOBase + CR, CR_RST);			  //reset
	outportb(IOBase + CR, CR_RE + CR_TE);		//enable Tx/Rx
	outportd(IOBase + TCR, 	TCR_IFG0	|
				TCR_IFG1	|
				TCR_MXDMA2 |
				TCR_MXDMA1);

	outportd(IOBase + RCR, 	RCR_RBLEN0 |
				RCR_MXDMA2 |
				RCR_MXDMA1 |
				RCR_AB		|
				RCR_AM	 |
				RCR_APM );
	outportd(IOBase + RBSTART , RxBufferPhysicalAddress);
	outportw(IOBase + IMR, R39_INTERRUPT_MASK);//enable interrupt


	i=inportd(IOBase+IDR0);
	kprint("IDR0 %X\n", i);

	for(i=0; i<6; i++)
	{
		j=inportb(IOBase+IDR0+i);
		rtl8139_mac[i]=j;
	}
	kprint("RTL8139: MAC=%s\n", Mac2Str(rtl8139_mac));
}

void InitSoftware()
{
	unsigned int	Offset,Segment,Delta,i;
	unsigned char *tmpBuffer;
//Init Tx Variables
	TxHwSetupPtr = 0;
	TxHwFinishPtr	= 0;
	TxHwFreeDesc = TX_SW_BUFFER_NUM;
//initialize TX descriptor
	for(i=0;i<TX_SW_BUFFER_NUM;i++)
	{	//allocate memory
		Buffer=(unsigned char *)kalloc_phys( 1600 / sizeof(int) );
		TxDesc[i].OriginalBufferAddress = Buffer;
		Offset=(int)Buffer;
		//align to DWORD
		if( Offset & 0x3 )
		{
			Delta = 4 - (Offset & 0x3);
			Offset = Offset + Delta;
			Buffer = Buffer + Delta;
		}
		TxDesc[i].buffer = Buffer;
		PhysicalAddrBuffer = Offset;
		TxDesc[i].PhysicalAddress = PhysicalAddrBuffer;
//		TxDesc[i].DescriptorStatus = TXDESC_INIT;
	}
//Init Rx Buffer
	RxBufferOriginal =
	tmpBuffer	 = (unsigned char *)kalloc_phys( RX_BUFFER_SIZE + 2000 );
	Offset=(int)tmpBuffer;
	//align to DWORD
	if( Offset & 0x3 )
	{
		Delta = 4 - (Offset & 0x3);
		Offset = Offset + Delta;
		tmpBuffer = tmpBuffer + Delta;
	}
	RxBuffer = tmpBuffer;
	RxBufferPhysicalAddress = Offset;
//Init Rx Variable
	RxReadPtrOffset = 0;
}

//////////////////////////////////////////////////////////////////////////
//Transmit part
//////////////////////////////////////////////////////////////////////////
unsigned char NextDesc(unsigned char CurrentDescriptor)
{
//	(CurrentDescriptor == TX_SW_BUFFER_NUM-1) ? 0 : (1 + CurrentDescriptor);
	if(CurrentDescriptor == TX_SW_BUFFER_NUM-1)
	{
		return  0;
	}
	else
	{
		return ( 1 + CurrentDescriptor);
	}
}

unsigned char CheckTSDStatus(unsigned char Desc)
{
	unsigned int		Offset = Desc << 2;
	unsigned int		tmpTSD;

	tmpTSD=inportd(IOBase + TSD0 + Offset);
	switch ( tmpTSD & (TSD_OWN | TSD_TOK) )
	{
	case (TSD_OWN | TSD_TOK):	  	return 	TSDSTATUS_BOTH;
	case (TSD_TOK) 		:		return  TSDSTATUS_TOK;
	case (TSD_OWN) 		:		return  TSDSTATUS_OWN;
	case 0 			:	return  TSDSTATUS_0;
	}
	return 0;
}



void IssueCMD(unsigned char descriptor)
{
	unsigned long offset = descriptor << 2;
	outportd(IOBase + TSAD0 + offset, TxDesc[TxHwSetupPtr].PhysicalAddress);
	outportd(IOBase + TSD0 + offset , TxDesc[TxHwSetupPtr].PacketLength);
}

unsigned int CopyFromPacketToBuffer(PPACKET pPacket, unsigned char *pBuffer)
{
	unsigned char	bufferCount;
	unsigned int    offset = 0;
	PBufferList	pBufList;
	for(pBufList=&(pPacket->Buffers) , bufferCount = 0;
		bufferCount < pPacket->BufferCount;
		bufferCount++)
	{
		memcpy(pBuffer+offset , pBufList->Buffer , pBufList->BufferLength);
		offset += pBufList->BufferLength;
		pBufList = pBufList->Next;
	}
	return offset;
}

int SendPacket(PPACKET pPacket)
{
//	disable();
	if( TxHwFreeDesc>0  )
	{
		TxDesc[TxHwSetupPtr].PacketLength=
			CopyFromPacketToBuffer( pPacket , TxDesc[TxHwSetupPtr].buffer);
		IssueCMD(TxHwSetupPtr);
		TxHwSetupPtr = NextDesc(TxHwSetupPtr);
		TxHwFreeDesc--;
//		enable();
		return -1;//success
	}
	else
	{
//		enable();
		return 0;//out of resource
	}
}

int RTL8139_SendPacket(void *buf, int sz)
{
//	disable();
	PacketBuf *pb;

	if( TxHwFreeDesc>0  )
	{
		TxDesc[TxHwSetupPtr].PacketLength=sz;
		memcpy(TxDesc[TxHwSetupPtr].buffer, buf, sz);
		IssueCMD(TxHwSetupPtr);
		TxHwSetupPtr = NextDesc(TxHwSetupPtr);
		TxHwFreeDesc--;

//		enable();
		return -1;//success
	}
	else
	{
//		enable();

		pb=kalloc(sizeof(PacketBuf));
		pb->len=sz;
		pb->buffer=kalloc(sz);
		memcpy(pb->buffer, buf, sz);

		if(rtl8139_outfirst)
		{
			rtl8139_outlast->next=buf;
			rtl8139_outlast=pb;
		}else
		{
			rtl8139_outfirst=pb;
			rtl8139_outlast=pb;
		}

		return 0;//out of resource
	}
}

void TxInterruptHandler()
{
	PacketBuf *pb;

//	kprint("TX ISR\n");
	while( (CheckTSDStatus(TxHwFinishPtr) == TSDSTATUS_BOTH	) &&
		(TxHwFreeDesc < 4 )	)
	{
	//can Release this buffer now

		TxHwFinishPtr = NextDesc(TxHwFinishPtr);
		TxHwFreeDesc++;

		if(rtl8139_outfirst)
		{
			pb=rtl8139_outfirst;
			rtl8139_outfirst=pb->next;

			RTL8139_SendPacket(pb->buffer, pb->len);
			kfree(pb->buffer);
			kfree(pb);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Start of Rx Path
////////////////////////////////////////////////////////////////////////

//void ReadPacket(PPACKET RxPacket)
//{
//	pLeadingReadPacket = RxPacket;
//}

char *Mac2Str(byte *mac)
{
	int i, j, k;
	char *buf;

	buf=kralloc(16);

	for(i=0; i<6; i++)
	{
		j=mac[i];

		k=(j>>4)&0xf;
		if(k<10)k=k+'0';
			else k=k-10+'A';
		buf[(i*2)]=k;

		k=j&0xf;
		if(k<10)k=k+'0';
			else k=k-10+'A';
		buf[(i*2)+1]=k;

		buf[(i*2)+2]=0;
	}

	return(buf);
}

void CopyPacket(unsigned char *pIncomePacket, unsigned int PktLength)
{
	PacketBuf *buf;

//	kprint("RX Packet %d bytes\n", PktLength);
//	kprint("To: %s From: %s Type: %d\n",
//		Mac2Str(pIncomePacket),
//		Mac2Str(pIncomePacket+6),
//		ntohs(*(short *)(pIncomePacket+12)));

	if(!rtl8139_listen)return;

	buf=kalloc(sizeof(PacketBuf));
	buf->len=PktLength;
	buf->buffer=kalloc(PktLength);
	memcpy(buf->buffer, pIncomePacket , PktLength);

	if(rtl8139_first)
	{
		rtl8139_last->next=buf;
		rtl8139_last=buf;
	}else
	{
		rtl8139_first=buf;
		rtl8139_last=buf;
	}

#if 0
	if( (pLeadingReadPacket != NULL) &&
		(pLeadingReadPacket->PacketLength == 0)  )
	{
		memcpy(pLeadingReadPacket->Buffers.Buffer , pIncomePacket , PktLength);
		pLeadingReadPacket->PacketLength = PktLength;
	}
#endif

}

int PacketOK(PPACKETHEADER pPktHdr)
{
//	int BadPacket = pPktHdr->RUNT ||
//			pPktHdr->LONG ||
//			pPktHdr->CRC  ||
//			pPktHdr->FAE;
	int BadPacket = (pPktHdr->flags & RxStatus_RUNT) ||
			(pPktHdr->flags & RxStatus_LONG) ||
			(pPktHdr->flags & RxStatus_CRC) ||
			(pPktHdr->flags & RxStatus_FAE);

	if( (!BadPacket) &&
		(pPktHdr->flags & RxStatus_ROK))
	{
		if ( (pPktHdr->PacketLength > RX_MAX_PACKET_LENGTH ) ||
			(pPktHdr->PacketLength < RX_MIN_PACKET_LENGTH )	)
		{
			return(0);
		}
		PacketReceivedGood++;
		ByteReceived += pPktHdr->PacketLength;
		return -1 ;
	}
	else
	{
		return 0;
	}
}

int RxInterruptHandler()
{
	unsigned char  TmpCMD;
	unsigned int	PktLength;
	unsigned char  *pIncomePacket, *RxReadPtr;
	PPACKETHEADER  pPacketHeader;

//	kprint("RX ISR\n");

	while (1)
	{
		TmpCMD = inportb(IOBase + CR);
		if (TmpCMD & CR_BUFE)
		{
			break;
		}

		do
		{
			RxReadPtr	  = RxBuffer + RxReadPtrOffset;
			pPacketHeader = (PPACKETHEADER)  RxReadPtr;
			pIncomePacket = RxReadPtr + 4;
			PktLength	  = pPacketHeader->PacketLength;	//this length include CRC
			if ( PacketOK( pPacketHeader ) )
			{
				if ( (RxReadPtrOffset + PktLength) > RX_BUFFER_SIZE )
				{	  //wrap around to end of RxBuffer
//_asm int 3;
					memcpy( RxBuffer + RX_BUFFER_SIZE ,	RxBuffer,
						(RxReadPtrOffset + PktLength - RX_BUFFER_SIZE)  );
				}
				//copy the packet out here
				CopyPacket(pIncomePacket,PktLength - 4);//don't copy 4 bytes CRC

				//update Read Pointer
				RxReadPtrOffset = (RxReadPtrOffset + PktLength + 4 + 3) & RX_READ_POINTER_MASK;
				//4:for header length(PktLength include 4 bytes CRC)
				//3:for dword alignment
				outportw( IOBase + CAPR, RxReadPtrOffset - 0x10);	//-4:avoid overflow
			}
			else
			{
//				ResetRx();
				break;
			}
			TmpCMD = inportb(IOBase + CR);
		} while (!(TmpCMD & CR_BUFE));
	}
	return (-1);			  //Done
}

void RTL8139_ISR();

asm (
   ".globl _RTL8139_ISR        \n"
   "_RTL8139_ISR:              \n"
   "   pusha               \n" /* Save all registers               */
//   "   pushw %ds           \n" /* Set up the data segment          */
//   "   pushw %es           \n"
//   "   pushw %ss           \n" /* Note that ss is always valid     */
//   "   pushw %ss           \n"
//   "   popw %ds            \n"
//   "   popw %es            \n"
   "                       \n"
   "   call _NewFunction   \n"
   "                       \n"
//   "   popw %es            \n"
//   "   popw %ds            \n" /* Restore registers                */
   "   popa                \n"
   "   iret                \n" /* Exit interrupt                   */
);

/////////////////////////////////////////////////////////////////////////
//Load / Unload
/////////////////////////////////////////////////////////////////////////
int LoadDriver()
{
	int	i, INTR;

	i=FindIOIRQ( &IOBase , &Irq );
	if(!i)
	{
		kprint("RTL8139: Failed to locate device\n");
		return(-1);
	}
	kprint("RTL8139: IO=%X, IRQ=%d\n", IOBase, Irq);

	INTR = ComputeInterrupt( Irq );
//	OldFunction = getvect( INTR );
//hook interrupt vector
//	disable();
//	setvect(INTR,NewFunction);
	NewIntISR(&RTL8139_ISR, INTR, 0);
	enable_irq(Irq);
//	enable();
//initialize chip
	InitSoftware();
	InitHardware();

	return 0;
}

int UnloadDriver()
{
//	disable();
//	setvect(INTR,OldFunction);
//	enable();
	return -1;
}

///////////////////////////////////////////////////////////////////////////
// End Of Demo driver
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//	Start of Test Program (only for demo)
///////////////////////////////////////////////////////////////////////////

#if 0

PPACKET BuildPacket()
{
	int i;
	PPACKET tmpPacket = (PPACKET) malloc(sizeof(PACKET));
	tmpPacket->BufferCount  = 1;
	tmpPacket->PacketLength = 64;
	tmpPacket->Buffers.Buffer = (unsigned char *) malloc(2000);
	tmpPacket->Buffers.Next	= NULL;
	tmpPacket->Buffers.BufferLength = 64;
	for(i=0;i<12;i++)
	{
		tmpPacket->Buffers.Buffer[i] = 0xff;
	}
	for(i=12;i<2000;i++)
	{
		tmpPacket->Buffers.Buffer[i] = i & 0xff;
	}
	return	tmpPacket;
}

PPACKET PreparePacket()
{
	PPACKET tmpPacket = (PPACKET) malloc(sizeof(PACKET));
	tmpPacket->BufferCount  = 1;
	tmpPacket->PacketLength = 0;
	tmpPacket->Buffers.Buffer = (unsigned char *) malloc(2000);
	tmpPacket->Buffers.Next	= NULL;
	tmpPacket->Buffers.BufferLength = 0;
	return	tmpPacket;
}

void
ShowPacket(PPACKET pPacket)
{
	unsigned char *PktBuf	= pPacket->Buffers.Buffer;
	unsigned int  i,PktLength = pPacket->PacketLength;
	clrscr();
	ShowStatistics();
	printf("Packet Length = %d\n",PktLength);
	for(i=0;i<PktLength;i++)
	{
	printf("%02X ",PktBuf[i]);
	if( (i&0xf) == 0xf )
	{
		printf("  %4X\n", (i&0xfffffff0) );
	}
	if( (i&0xff) == 0xff )
	{
		getchar();
		clrscr();
	}
	}

}

int Send()
{
	PPACKET	pTestPacket;
	int	i;

// Send Test
	pTestPacket = BuildPacket();
	for(i=0;i<2000;i++)
	{
		pTestPacket->PacketLength=pTestPacket->Buffers.BufferLength = 64 + (i%1430);
		while( !SendPacket(pTestPacket) )
		{
		};
//		delay(5);
	}
	return -1;
}

void Receive()
{
	PPACKET	pTestPacket;
	int	i;

//Read Test
	pTestPacket = PreparePacket();
	ReadPacket(pTestPacket);
	do
	{
/*	while(pTestPacket->PacketLength == 0)
	{
	}
//	ShowPacket(pTestPacket);*/
	ShowStatistics();
	pTestPacket->PacketLength = 0;
	}while(!kbhit());
}

main()
{
	clrscr();
		directvideo = 1;
	LoadDriver();
	Send();
//	Receive();
	UnloadDriver();
	return 0;
}

#endif

int rtl8139_write(void *buf, int len, VFILE *fd)
{
	return(-1);
}

int rtl8139_read(void *buf, int len, VFILE *fd)
{
	return(-1);
}

int rtl8139_get(void *buf, int sz, VADDR *from, VFILE *sock)
{
	int i;
	PacketBuf *p;

	if(!rtl8139_first)return(-1);

	p=rtl8139_first;
	rtl8139_first=rtl8139_first->next;

	i=p->len;
	if(sz<i)i=sz;

	memcpy(buf, p->buffer, i);
	kfree(p->buffer);
	kfree(p);

	return(i);
}

int rtl8139_send(VFILE *sock, VADDR *target, void *msg, int len, int flags)
{
	if(len<14)return(-1);

	if(len<60)len=60;
	RTL8139_SendPacket(msg, len);

	return(len);
}

int rtl8139_inready(VFILE *fd)
{
	if(rtl8139_first)return(1);

	return(0);
}

int rtl8139_ioctls(VFILE *fd, void **arg)
{
	char *s, *t;
	int i, j;

	s=*arg;
	if(!strcmp(s, "get-mac"))
	{
		t=(char *)arg[1];
		for(i=0; i<6; i++)
			t[i]=rtl8139_mac[i];
		return(0);
	}
	if(!strcmp(s, "set-mac"))
	{
		t=(char *)arg[1];

		j=*(int *)t;
		outportd(IOBase+IDR0, j);
		j=*(int *)(t+4);
		outportd(IOBase+IDR0+4, j);

		return(0);
	}
	if(!strcmp(s, "reset-mac"))
	{
		t=rtl8139_mac;

		j=*(int *)t;
		outportd(IOBase+IDR0, j);
		j=*(int *)(t+4);
		outportd(IOBase+IDR0+4, j);
	}

	return(-1);
}

int rtl8139_ioctl(VFILE *fd, int req, void *argp)
{
	char *s, *t;
	int i, j;

	switch(req&0xffff)
	{
	case IOCTL_GETMAC:
		t=(char *)argp;
		for(i=0; i<6; i++)
			t[i]=rtl8139_mac[i];
		break;

	case IOCTL_SETMAC:
		t=(char *)argp;

		j=*(int *)t;
		outportd(IOBase+IDR0, j);
		j=*(int *)(t+4);
		outportd(IOBase+IDR0+4, j);
		break;

	case IOCTL_RESETMAC:
		t=rtl8139_mac;

		j=*(int *)t;
		outportd(IOBase+IDR0, j);
		j=*(int *)(t+4);
		outportd(IOBase+IDR0+4, j);
		break;

	default:
		return(-1);
		break;
	}

	return(0);
}

VFILE *rtl8139_open(char *name, void *data)
{
	VFILE *tmp;

	rtl8139_listen++;

	tmp=vfnew();
	tmp->buffer=data;

	tmp->read_proc=rtl8139_read;
	tmp->write_proc=rtl8139_write;
	tmp->get_proc=rtl8139_get;
	tmp->send_proc=rtl8139_send;
	tmp->inready_proc=rtl8139_inready;
	tmp->ioctl_proc=rtl8139_ioctl;
	tmp->ioctls_proc=rtl8139_ioctls;

	return(tmp);
}

int RTL8139_Init()
{
	kprint("RTL8139 Init\n");

	rtl8139_first=NULL;
	rtl8139_last=NULL;
	rtl8139_listen=0;
	rtl8139_outfirst=NULL;
	rtl8139_outlast=NULL;

	LoadDriver();

	Driver_RegisterStream("ethernet/0", &rtl8139_open, NULL);

//	while(1);
	return(0);
}
