/*
basic protocol.
 */

#include <pdlib.h>
#include <pdnet.h>

VFILE *sxrpc_sock;
int sxrpc_port;

SXRPC_Con *sxrpc_cons[256];

SXRPC_Con *SXRPC_NewCon()
{
	SXRPC_Con *con;
	int i;

	for(i=0; i<256; i++)if(!sxrpc_cons[i])
	{
		con=kalloc(sizeof(SXRPC_Con));
		sxrpc_cons[i]=con;
		con->num=i;
		return(con);
	}
	return(NULL);
}

SXRPC_Con *SXRPC_Connect(VADDR *addr)
{
	SXRPC_Con *con;
	VFILE *sock;

	sock=TCP_OpenConnect(addr);
	if(!sock)return(NULL);

	con=SXRPC_NewCon();
	con->sock=sock;
	con->addr=kmemdup(addr, sizeof(VADDR));

	kprintvf(con->sock, "(SXRPC 0.1)\n");

	return(con);
}

SXRPC_Con *SXRPC_FindCon(VADDR *addr)
{
	int i;

	for(i=0; i<256; i++)
		if(sxrpc_cons[i])
			if(NET_AddrEqual(sxrpc_cons[i]->addr, addr))
				return(sxrpc_cons[i]);
	return(NULL);
}

int SXRPC_HandleExpr(SXRPC_Con *con, NetParse_Node *exp)
{
	char *buf, *s;

	buf=kralloc(16384);

	s=NetParse_SX_PrintExpr(buf, exp);
	*s++=0;

	kprint("%s\n", buf);

	if(!strcmp(exp->key, "SXRPC"))
	{
		if(!strcmp(exp->first->text, "0.1"))
		{
			kprintvf(con->sock, "(OK)\n");
			return(0);
		}
		kprintvf(con->sock, "(REJECT bad-version 0.1)\n");
		return(0);
	}
	if(!strcmp(exp->key, "REJECT"))
	{
		con->state=SXRPC_CLOSE;
		return(0);
	}
	if(!strcmp(exp->key, "OK"))
	{
		con->state=SXRPC_CONNECTED;
		return(0);
	}

	if(!strcmp(exp->key, "pass"))
	{
//		SXRPC_HandlePass(con, exp);
		return(0);
	}

	return(0);
}

int SXRPC_HandleConnection(SXRPC_Con *con)
{
	int sz, i;
	char *obuf, *s, *t;
	char mbuf[1024], *tbuf[16];
	NetParse_Node *exp;

	if(!con->buf)
	{
		con->buf=kalloc(16384);
		con->end=con->buf;
	}

	while(1)
	{
		sz=vfread(con->end, 1, 16384-(con->end-con->buf), con->sock);
		if(sz<0)break;
		con->end+=sz;
		*con->end=0;
//		kprint("%s", con->buf);
		if(!(con->end-con->buf))break;

		i=con->end-con->buf;
		s=con->buf;

		t=s;
		exp=NetParse_SX_ParseExpr(&t);
		if(exp)
		{
			SXRPC_HandleExpr(con, exp);
			s=t;
		}

		if(s!=con->buf)
		{
			t=con->buf;
			while(s<con->end)*t++=*s++;
			con->end=t;
		}else break;
	}
	if((sz==-1) || (con->state==SXRPC_CLOSE))
	{
		vfclose(con->sock);
		sxrpc_cons[con->num]=NULL;
		if(con->buf)kfree(con->buf);
		kfree(con);
	}

	return(0);
}

int SXRPC_Poll()
{
	VADDR addr;
	int i;
	VFILE *newsock;
//	elem t, cur;
	SXRPC_Con *con;

	int stime;

	if(!sxrpc_sock)return(-1);

//	stime=Sys_TimeMS();

	while(1)
	{
		vfioctls(sxrpc_sock, "accept", &newsock, &addr);
		if(!newsock)break;

		kprint("SXRPC: recieved connection\n");

		con=SXRPC_NewCon();
		con->sock=newsock;
		con->addr=kmemdup(&addr, sizeof(VADDR));

		kprintvf(con->sock, "(SXRPC 0.1)\n");
	}

	for(i=0; i<256; i++)if(sxrpc_cons[i])
		SXRPC_HandleConnection(sxrpc_cons[i]);

	return(0);
}

int SXRPC_Init()
{
	VADDR *addr;

	sxrpc_sock=NULL;
	sxrpc_port=7936;
	while(!sxrpc_sock && (sxrpc_port<7952))
	{
		sxrpc_sock=TCP_OpenListen(sxrpc_port);
		if(!sxrpc_sock)sxrpc_port++;
	}
	if(sxrpc_sock)
	{
		kprint("SXRPC: port opened %d\n", sxrpc_port);
	}else
	{
		kprint("SXRPC: fail open host port\n");

	}

//	if(sxrpc_port!=7936)
//	{
//		addr=NET_LookupHost("localhost");
//		addr->ipv4.port=htons((short)7936);
//		SXRPC_Connect(addr);
//		kfree(addr);
//	}

//	SXRPC_LBS_Init();

	return(0);
}
