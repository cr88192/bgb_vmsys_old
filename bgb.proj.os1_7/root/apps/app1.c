#include <stdio.h>
#include <os1/addr.h>

int main(int argc, char **argv, char **env)
{
	FILE *sock;
	VADDR addr;
	char *msg="this is a test\n";
	char *buf;
	int i;

	printf("BGB Net App 1\n");

	sock=fopen("/devices/ipv4/udp?port=54321", "r+b");

	addr.proto=PROTO_IPV4UDP;
	addr.ipv4.addr=0x6401A8C0; //0xC0A80164;
	addr.ipv4.port=0x31D4;
	fsendto(sock, &addr, msg, strlen(msg), 0);
	buf=malloc(4096);

	while(1)
	{
		i=frecvfrom(buf, 4096, &addr, sock);
		if(i>=0)
		{
			printf("got %d byte packet\n", i);
		}
	}
}
