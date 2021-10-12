#include <pdlib.h>
#include <pdnet.h>

int main()
{
	VFILE *ifd, *sock;
	VADDR *addr;
	byte *buf;
	char buf2[256];
	int i;
	Meta0_Con *con;
	MRPT_TLV *tlv, *tlv2;
	char *s;

	ObjType_Init();

	Var_Init();
	Var_LoadConfig("tst3.cfg");

	NET_Init();
	HttpNode_Init();
	XmlRpc_Init();

	MRPT_Init();

	con=MRPT_Connect("127.0.0.1");

	tlv=MRPT_NewTLVCompound("mrpt/array");

	s="hello...";
	tlv2=MRPT_NewTLVPrimitive("mrpt/string", strlen(s)+1);
	strcpy(tlv2->data, s);
	MRPT_AddTLVMember(tlv, tlv2);

	tlv2=MRPT_NewTLVPrimitive("mrpt/integer", 4);
	*(int *)tlv2->data=htonl(1234);
	MRPT_AddTLVMember(tlv, tlv2);

	MRPT_SendTLV(con, tlv);

//	kprint("%d\n", sizeof(long long));

	while(1)
	{
		NET_Poll();
		usleep(1000);
	}

	return(0);
}
