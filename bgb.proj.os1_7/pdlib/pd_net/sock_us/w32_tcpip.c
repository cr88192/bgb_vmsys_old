//#define NODELAY
//#define BUFFER
//#define CONF_USEIPV6

#include <pdlib.h>
#include <pdnet.h>

#include <windows.h>

#ifdef CONF_USEIPV6
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <winsock.h>
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif

typedef struct {
int sock;
int cnt;
byte *buf, *bufe;
}tcp_buf;

static byte in6_addr_any[16]=
	{0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0};
static byte in6_addr_loopback[16]=
	{0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1};

int __TCP_OpenSocket (int port)
{
	int newsocket;
	struct sockaddr_in address;
//	int t=1;

	if ((newsocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		return -1;

//	ioctlsocket (newsocket, FIONBIO, &t);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if( bind (newsocket, (void *)&address, sizeof(address)) == -1)
		return(-1);

	return(newsocket);
}

#ifdef CONF_USEIPV6

int __TCP_OpenSocket_IPv6 (int port)
{
	int newsocket;
	struct sockaddr_in6 address;
//	int t=1;

	if ((newsocket = socket (PF_INET6, SOCK_STREAM, IPPROTO_TCP)) == -1)
		return -1;

//	ioctlsocket (newsocket, FIONBIO, &t);

	address.sin6_family = AF_INET6;
	memcpy(&address.sin6_addr, &in6_addr_any, 16);
	address.sin6_port = htons(port);
	if( bind (newsocket, (void *)&address, sizeof(address)) == -1)
		return(-1);

	return(newsocket);
}

#endif

int TCP_GetSocketAddr(int socket, VADDR *addrbuf)
{
	union {
		struct sockaddr addru;
		struct sockaddr_in address4;
#ifdef CONF_USEIPV6
		struct sockaddr_in6 address6;
		struct sockaddr_storage address_gen;
#endif
	}address;

	int s;

	addrbuf->proto=0;

	s=sizeof(address);
	if(getsockname(socket, (struct sockaddr *)&address, &s))return(-1);

	switch(address.addru.sa_family)
	{
	case AF_INET:
		addrbuf->proto=PROTO_IPV4TCP;
		addrbuf->ipv4.port=ntohs(address.address4.sin_port);
		addrbuf->ipv4.addr=ntohl(address.address4.sin_addr.s_addr);
		break;
#ifdef CONF_USEIPV6
	case AF_INET6:
		addrbuf->proto=PROTO_IPV6TCP;
		addrbuf->ipv6.port=ntohs(address.address6.sin6_port);
		memcpy(addrbuf->ipv6.addr, &address.address6.sin6_addr, 16);
		break;
#endif
	default:
		break;
	}
	return(0);
}

/* VFILE interface */
VFILE *TCP_WrapSocket(int sock);

int tcpsock_read(void *buf, int sz, VFILE *sock)
{
	int fhnd, stat;
	tcp_buf *inf;

//	printf("try get message.\n");

//	fhnd=*(int *)sock->buffer;
	inf=sock->buffer;

	sz=recv(inf->sock, buf, sz, 0);

	if(sz==-1)
	{
		stat=WSAGetLastError();
		switch(stat)
		{
		case WSAEWOULDBLOCK:
			sz=0;
			break;
		case WSAECONNRESET:
		case WSAECONNABORTED:
			kprint("TCP: Read: connection reset\n");
			break;
		default:
			kprint("TCP: Read: error %d\n", stat);
			break;
		}
	}
	return(sz);
}

int tcpsock_write(void *msg, int len, VFILE *sock)
{
	int i, stat;
	tcp_buf *inf;

//	kprint("TCP: write %d\n", len);

	inf=sock->buffer;

	inf->cnt+=len;

#ifdef BUFFER
	i=inf->bufe-inf->buf;
	if((i+len)<4096)
	{
		memcpy(inf->bufe, msg, len);
		inf->bufe+=len;
		return(len);
	}

	i=inf->bufe-inf->buf;
	if(i)send(inf->sock, inf->buf, i, 0);
#endif
	inf->bufe=inf->buf;

	i=send(inf->sock, msg, len, 0);

//		if(i==SOCKET_ERROR)kprint("TCP: write error %d on %d\n",
//			WSAGetLastError(), *(int *)sock->buffer);

	if(i==-1)
	{
		stat=WSAGetLastError();
		switch(stat)
		{
		case WSAEWOULDBLOCK:
			break;
		case WSAECONNRESET:
			kprint("TCP: Write: connection reset\n");
			return(-1);
			break;
		default:
			kprint("TCP: Write: error %d\n", stat);
			return(-1);
			break;
		}
	}
	return(i);
}

int tcpsock_flush(VFILE *sock)
{
	tcp_buf *inf;
	int i;
	int stat;

	inf=sock->buffer;

	i=inf->bufe-inf->buf;
	if(i)
	{
		i=send(inf->sock, inf->buf, i, 0);
		inf->bufe=inf->buf;

//		kprint("TCP flush: %d bytes t:%d\n", inf->cnt, Sys_TimeMS());
		inf->cnt=0;
	}

	if(i==-1)
	{
		stat=WSAGetLastError();
		switch(stat)
		{
		case WSAEWOULDBLOCK:
			break;
		case WSAECONNRESET:
			kprint("TCP: Write: connection reset\n");
			return(-1);
			break;
		default:
			kprint("TCP: Write: error %d\n", stat);
			return(-1);
			break;
		}
	}
	return(i);
}

int tcpsock_ioctls(VFILE *fd, void **arg)
{
	char *s;
	int sock;
	union {
		struct sockaddr addru;
		struct sockaddr_in address4;
#ifdef CONF_USEIPV6
		struct sockaddr_in6 address6;
#endif
	}address;
	int sz, stat, t;
	fd_set rfds;
	struct timeval tv;
	VADDR *addrbuf;

	s=*arg;
	if(!strcmp(s, "accept"))
	{
//		kprint("TCP: accept\n");

		sz=sizeof(address);
		sock=accept(*(int *)fd->buffer, (struct sockaddr *)&address, &sz);


		if(sock==INVALID_SOCKET)
		{
			*(VFILE **)arg[1]=NULL;
			return(0);
		}

		kprint("TCP: new con, sock %d\n", sock);

		addrbuf=(VADDR *)arg[2];

		switch(address.addru.sa_family)
		{
		case AF_INET:
			addrbuf->proto=PROTO_IPV4TCP;
			addrbuf->ipv4.port=address.address4.sin_port;
			addrbuf->ipv4.addr=address.address4.sin_addr.s_addr;
			break;
#ifdef CONF_USEIPV6
		case AF_INET6:
			addrbuf->proto=PROTO_IPV6TCP;
			addrbuf->ipv6.port=address.address6.sin6_port;
			memcpy(addrbuf->ipv6.addr, &address.address6.sin6_addr, 16);
			break;
#endif
		default:
			break;
		}

		*(VFILE **)arg[1]=TCP_WrapSocket(sock);
		return(0);
	}

	if(!strcmp(s, "can-write?"))
	{
		FD_ZERO(&rfds);
		FD_SET(*(int *)fd->buffer, &rfds);
		tv.tv_sec=*(int *)arg[1];
		tv.tv_usec=0;

		stat=select(1, &rfds, NULL, NULL, &tv);

		if(!stat)
		{
			*(int *)arg[1]=0; //false
			return(0);
		}
		*(int *)arg[1]=-1;
		return(0);
	}

	return(-1);
}

int tcpsock_close(VFILE *sock)
{
	int fhnd, stat;

//	printf("try get message.\n");

	fhnd=*(int *)sock->buffer;

	closesocket(fhnd);
	kfree(sock);

	return(0);
}


VADDR *tcpsock_getaddr(VFILE *sock)
{
	VADDR *tmp;
	tmp=kalloc(sizeof(VADDR));
	if(TCP_GetSocketAddr(*(int *)sock->buffer, tmp))
	{
		kfree(tmp);
		tmp=NULL;
	}
	return(tmp);
}

static tcp_buf tcp_slot[1024];
static int tcp_slots=0;

VFILE *TCP_WrapSocket(int sock)
{
	VFILE *tmp;
	tcp_buf *hnd;
	int t, i;

	t=1;
	ioctlsocket (sock, FIONBIO, &t);
#ifdef NODELAY
	t=-1;
	i=setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &t, sizeof(int));
#endif

	if(i==SOCKET_ERROR)kprint("TCP: NODELAY: %d on %d\n",
		WSAGetLastError(), sock);

	tmp=vfnew();
	hnd=&tcp_slot[tcp_slots++];
	tmp->buffer=hnd;
	hnd->sock=sock;
	hnd->buf=kalloc(4096);
	hnd->bufe=hnd->buf;

	tmp->read_proc=&tcpsock_read;
	tmp->write_proc=&tcpsock_write;
	tmp->ioctls_proc=&tcpsock_ioctls;
	tmp->flush_proc=&tcpsock_flush;
	tmp->close_proc=&tcpsock_close;

	return(tmp);
}

VFILE *TCP_OpenSocket(int port)
{
	VFILE *tmp;
	tcp_buf *hnd;
	int sock;
	int t=1;
	int i;

	sock=__TCP_OpenSocket(port);
	if(sock==-1)
	{
		kprint("socket creation error.\n");
		return(NULL);
	}

	ioctlsocket(sock, FIONBIO, &t);

#ifdef NODELAY
	t=-1;
	i=setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &t, sizeof(int));
#endif

	if(i==SOCKET_ERROR)kprint("TCP: NODELAY: %d on %d\n",
		WSAGetLastError(), sock);

	tmp=vfnew();
	hnd=&tcp_slot[tcp_slots++];
	tmp->buffer=hnd;
	hnd->sock=sock;
	hnd->buf=kalloc(4096);
	hnd->bufe=hnd->buf;

	tmp->read_proc=&tcpsock_read;
	tmp->write_proc=&tcpsock_write;
	tmp->ioctls_proc=&tcpsock_ioctls;
	tmp->flush_proc=&tcpsock_flush;
	tmp->close_proc=&tcpsock_close;

	return(tmp);
}

VFILE *TCP_OpenListen(int port)
{
	VFILE *tmp;
	tcp_buf *hnd;
	int sock;
	int t=1;
	int i;

	sock=__TCP_OpenSocket(port);
	if(sock==-1)
	{
		kprint("socket creation error.\n");
		return(NULL);
	}

	listen(sock, 5);

	ioctlsocket (sock, FIONBIO, &t);

#ifdef NODELAY
	t=-1;
	i=setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &t, sizeof(int));
#endif
	if(i==SOCKET_ERROR)kprint("TCP: NODELAY: %d on %d\n",
		WSAGetLastError(), sock);

	tmp=vfnew();
	hnd=&tcp_slot[tcp_slots++];
	tmp->buffer=hnd;
	hnd->sock=sock;
	hnd->buf=kalloc(4096);
	hnd->bufe=hnd->buf;

	tmp->read_proc=&tcpsock_read;
	tmp->write_proc=&tcpsock_write;
	tmp->ioctls_proc=&tcpsock_ioctls;
	tmp->flush_proc=&tcpsock_flush;
	tmp->close_proc=&tcpsock_close;

	return(tmp);
}

#ifdef CONF_USEIPV6
VFILE *TCP_OpenListen_IPv6(int port)
{
	VFILE *tmp;
	tcp_buf *hnd;
	int sock;
	int t=1;
	int i;

	sock=__TCP_OpenSocket_IPv6(port);
	if(sock==-1)
	{
		kprint("socket creation error.\n");
		return(NULL);
	}

	listen(sock, 5);

	return(TCP_WrapSocket(sock));
}
#endif

VFILE *TCP_OpenConnect(VADDR *targ)
{
	VFILE *tmp;
	tcp_buf *hnd;
	int sock, stat;
	int t=1;
	int i;

	struct sockaddr_in name4;
#ifdef CONF_USEIPV6
	struct sockaddr_in6 name6;
#endif

	sock=__TCP_OpenSocket(0);
	if(sock==-1)
	{
		kprint("socket creation error.\n");
		return(NULL);
	}

	stat=SOCKET_ERROR;

	if((targ->proto==PROTO_IPV4UDP) || (targ->proto==PROTO_IPV4TCP))
	{
		kprint("connect ipv4 %s\n", NET_Addr2Str(targ));

		name4.sin_family = AF_INET;
		name4.sin_addr.s_addr = targ->ipv4.addr;
		name4.sin_port = targ->ipv4.port;

		stat=connect(sock, (struct sockaddr *)&name4, sizeof(name4));
	}
#ifdef CONF_USEIPV6
	else if((targ->proto==PROTO_IPV6UDP) ||
		(targ->proto==PROTO_IPV6TCP))
	{
		kprint("connect ipv6 %s\n", NET_Addr2Str(targ));

		name6.sin6_family = AF_INET6;
		memcpy(&name6.sin6_addr, targ->ipv6.addr, 16);
		name6.sin6_port = targ->ipv6.port;

		stat=connect(sock, (struct sockaddr *)&name6, sizeof(name6));
	}
#endif

	if(stat == SOCKET_ERROR)
	{
		kprint("socket connect fail %d.\n", WSAGetLastError());
		closesocket(sock);
		return(NULL);
	}

	ioctlsocket (sock, FIONBIO, &t);

#ifdef NODELAY
	t=-1;
	i=setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &t, sizeof(int));
#endif

	if(i==SOCKET_ERROR)kprint("TCP: NODELAY: %d on %d\n",
		WSAGetLastError(), sock);

	tmp=vfnew();
	hnd=&tcp_slot[tcp_slots++];
	tmp->buffer=hnd;
	hnd->sock=sock;
	hnd->buf=kalloc(4096);
	hnd->bufe=hnd->buf;

	tmp->read_proc=&tcpsock_read;
	tmp->write_proc=&tcpsock_write;
	tmp->ioctls_proc=&tcpsock_ioctls;
	tmp->flush_proc=&tcpsock_flush;
	tmp->close_proc=&tcpsock_close;

	return(tmp);
}
