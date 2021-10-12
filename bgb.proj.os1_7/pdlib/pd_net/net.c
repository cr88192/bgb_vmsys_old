#include <pdlib.h>
#include <pdnet.h>

int NET_AddrEqual(VADDR *a, VADDR *b)
{
	if(!a || !b)return(0);
	if(a->proto != b->proto)return(0);
	switch(a->proto)
	{
	case PROTO_IPV4UDP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port && b->ipv4.port)
			if(a->ipv4.port != b->ipv4.port)
			return(0);
		break;
	case PROTO_IPV4TCP:
		if(a->ipv4.addr != b->ipv4.addr)return(0);
		if(a->ipv4.port && b->ipv4.port)
			if(a->ipv4.port != b->ipv4.port)
			return(0);
		break;
	default:
		return(0);
		break;
	}
	return(1);
}

int NET_Poll()
{
	Meta0_Poll();
	NETAPI_Poll();

//	HttpNode_Poll();
	SXRPC_Poll();

	return(0);
}

int NET_Init()
{

	NET_InitLow();
	Meta0_Init();
	NETAPI_Init();

//	HttpNode_Init();
	SXRPC_Init();

	return(0);
}
