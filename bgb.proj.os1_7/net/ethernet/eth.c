#include <general.h>

VFILE *ethernet_fd;
byte ethernet_mac[8];

char *Ethernet_Mac2Str(byte *mac)
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

char *Ethernet_Type2Str(int ty)
{
	char *s;

	switch(ty)
	{
	case 0x0800:
		s="IP";
		break;
	case 0x0806:
		s="ARP";
		break;
	case 0x8035:
		s="Reverse ARP";
		break;
	case 0x809B:
		s="Appletalk";
		break;
	case 0x8137:
		s="IPX";
		break;
	default:
		s="Unknown";
		break;
	}
	return(s);
}

int Ethernet_Send(byte *mac, int ty, void *data, int sz)
{
	byte *buf;

	buf=kalloc(sz+14);
	memcpy(buf+0, mac, 6);
	memcpy(buf+6, ethernet_mac, 6);
	*(short *)(buf+12)=ntohs(ty);
	if(data)memcpy(buf+14, data, sz);

	vfsend(ethernet_fd, NULL, buf, sz+14, 0);
	kfree(buf);
	return(0);
}

int Ethernet_Poll()
{
	static byte *msgbuf=NULL;
	VADDR addr;
	int sz;
	int ty;

	if(!vfinready(ethernet_fd))
		return(-1);

	if(!msgbuf)msgbuf=kalloc(4096);

	sz=vfget(msgbuf, 4096, &addr, ethernet_fd);
//	kprint("Ethernet: got %d byte packet\n", sz);
	ty=ntohs(*(short *)(msgbuf+12));

//	kprint("To: %s From: %s Type: %d(%s)\n",
//		Ethernet_Mac2Str(msgbuf),
//		Ethernet_Mac2Str(msgbuf+6),
//		ty, Ethernet_Type2Str(ty));

	switch(ty)
	{
	case 0x0800:
		IPV4_HandleDatagram(msgbuf+14, sz-14);
		break;
	case 0x0806:
		ARP_HandlePacket(msgbuf+14, sz-14);
		break;
	default:
		break;
	}
	return(0);
}

int Ethernet_Loop(void *data)
{

	kprint("Ethernet: Poll Thread Started\n");

//	Ethernet_Send(ethernet_mac, 0, NULL, 48);

	while(1)
	{
		if(!ethernet_fd)break;
		if(!vfinready(ethernet_fd))
		{
			kthread_blocked();
			continue;
		}
		Ethernet_Poll();
	}
	kprint("Ethernet: Poll Thread Died\n");
}

int Ethernet_SvcLoop(void *data)
{

	kprint("Ethernet: Service Thread Started\n");

	while(1)
	{
#if 0
		if(!ethernet_fd)break;
		if(!vfinready(ethernet_fd))
		{
			kthread_blocked();
			continue;
		}
#endif
		Meta0_Poll();
		NETAPI_Poll();
		kthread_blocked();
	}
	kprint("Ethernet: Service Thread Died\n");
}

int Ethernet_Init()
{
	kthread *th;

	kprint("Init Ethernet Iface\n");
	ethernet_fd=vffopen("/devices/ethernet/0", "r+b");

	if(!ethernet_fd)
	{
		kprint("Ethernet: failed open ethernet device\n");
		return(-1);
	}
//	vfioctls(ethernet_fd, "get-mac", ethernet_mac);
	vfioctl(ethernet_fd, IOCTL_GETMAC, ethernet_mac);
	kprint("\tMAC=%s\n", Ethernet_Mac2Str(ethernet_mac));

	IPV4_Init();

	th=kthread_spawn(0, &Ethernet_Loop, NULL);
	kthread_start(th, PRIORITY_NORMAL);

	th=kthread_spawn(0, &Ethernet_SvcLoop, NULL);
	kthread_start(th, PRIORITY_NORMAL);

	return(0);
}
