#include <pdlib.h>

int main()
{
	ObjType_Init();

	Var_Init();
	Var_LoadConfig("tst1.cfg");

	NET_Init();
	HttpNode_Init();

	while(1)
	{
		NET_Poll();
		usleep(100);
	}

	return(0);
}
