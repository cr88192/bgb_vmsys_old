#include <stdio.h>
#include <os1/addr.h>

int main(int argc, char **argv, char **env)
{
	FILE *sock, *sock2;
	VADDR addr;
	char *msg="this is a test\n";
	char *buf;
	int i;

	printf("BGB Net App 1\n");

	sock=fopen("/devices/ipv4/tcp/listen?port=54321", "r+b");

//	addr.proto=PROTO_IPV4UDP;
//	addr.ipv4.addr=0x6401A8C0; //0xC0A80164;
//	addr.ipv4.port=0x31D4;
//	fsendto(sock, &addr, msg, strlen(msg), 0);

	buf=malloc(4096);

	while(1)
	{
		sock2=faccept(sock, &addr);
		if(sock2)
		{
			printf("Connection Accepted\n");
			break;
		}
		usleep(10000);
	}

	while(1)
	{
		memset(buf, 0, 4096);

		i=0;
		i=fread(buf, 1, 4096, sock2);
		if(i>0)
		{
			printf("Read %d bytes '%s'\n", i, buf);

			i=fwrite(buf, 1, i, sock2);
			printf("Wrote %d bytes\n", i);
		}
		usleep(10000);

//		i=frecvfrom(buf, 4096, &addr, sock);
//		if(i>=0)
//		{
//			printf("got %d byte packet\n", i);
//		}
	}
}
