#include <pdlib.h>

int main()
{
	VFILE *sock;
	byte *buf;
	VADDR addr;
	int i;

	ObjType_Init();

	Var_Init();
	Var_LoadConfig("tst1.cfg");

	NET_Init();
	HttpNode_Init();

	sock=UDP_OpenSocket(54321);
	if(!sock)
	{
		kprint("open socket failed\n");
		return(-1);
	}

	buf=kalloc(4096);

	while(1)
	{
		NET_Poll();
		i=vfget(buf, 4096, &addr, sock);
		if(i>=0)
		{
			kprint("got %d byte packet from %s\n",
				i, NET_Addr2Str(&addr));
			vfsend(sock, &addr, buf, i, 0); //bounce
		}
		usleep(100);
	}

	return(0);
}
