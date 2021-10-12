#include <pdlib.h>
#include <pdnet.h>

int main()
{
	VFILE *ifd, *sock;
	VADDR *addr;
	byte *buf;
	char buf2[256];
	int i;

	ObjType_Init();

	Var_Init();
	Var_LoadConfig("tst3.cfg");

	NET_Init();
	HttpNode_Init();
	XmlRpc_Init();

	addr=NET_Str2Addr("127.0.0.1:80", PROTO_IPV4TCP);
	sock=TCP_OpenConnect(addr);

	ifd=vffopen("req0.txt", "rb");
	buf=vf_bufferin(ifd);
	vfwrite(buf, 1, strlen(buf), sock);

	while(1)
	{
		i=vfread(buf2, 1, 255, sock);
		if(i<0)break;

		buf2[i]=0;
		kprint("%s", buf2);
		usleep(1000);
	}

	while(1)
	{
		NET_Poll();
		usleep(1000);
	}

	return(0);
}
