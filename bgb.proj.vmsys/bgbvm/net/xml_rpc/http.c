#include <general.h>
#include <net/xml_rpc.h>

VFILE *httpnode_sock;
int httpnode_port;

HTTP_Con *httpnode_cons[256];

char httpnode_mimetable[64]=
	"ABCDEFGHIJKLMNOP"
	"QRSTUVWXYZabcdef"
	"ghijklmnopqrstuv"
	"wxyz0123456789+/";

int HttpNode_EncodeMime(byte *o, byte *i, int sz)
{
	unsigned long v;
	int osz, j;

	osz=0;
	while(sz)
	{
		v=(i[0]<<16)+(i[1]<<8)+i[2];

		j=(sz*4)/3;
		if(i>0)o[0]=httpnode_mimetable[(v>>18)&0x3f];
		if(i>1)o[1]=httpnode_mimetable[(v>>12)&0x3f];
		if(i>2)o[2]=httpnode_mimetable[(v>>6)&0x3f];
		if(i>3)o[3]=httpnode_mimetable[v&0x3f];

		i+=3;
		o+=4;

		j=(sz<3)?sz:3;
		sz-=j;
		osz+=(j*4)/3;
	}

	return(osz);
}

static int mime_conv(int v)
{
	int i;
	for(i=0; i<64; i++)
		if(httpnode_mimetable[i]==v)
			return(i);
	return(0);
}

int HttpNode_DecodeMime(byte *o, byte *i, int sz)
{
	unsigned long v;
	int osz, j;

	osz=0;
	while(sz)
	{
		v=mime_conv(i[0])<<18;
		if(sz>1)v+=mime_conv(i[1])<<12;
		if(sz>2)v+=mime_conv(i[2])<<6;
		if(sz>3)v+=mime_conv(i[3]);

		o[0]=(v>>16)&0xff;
		o[1]=(v>>8)&0xff;
		o[2]=v&0xff;

		i+=4;
		o+=3;

		j=(sz<4)?sz:4;
		sz-=j;
		osz+=(j*3)/4;
	}

	return(osz);
}

HTTP_Con *HttpNode_NewCon()
{
	HTTP_Con *con;
	int i;

	for(i=0; i<256; i++)if(!httpnode_cons[i])
	{
		con=kalloc(sizeof(HTTP_Con));
		httpnode_cons[i]=con;
		con->num=i;
		return(con);
	}
	return(NULL);
}

int HttpNode_SendContents(HTTP_Con *con, byte *type, byte *msg, int len)
{
	int sz, i;
	char *obuf, *s, *t;
	char *tbuf[16];

	kprint("send response\n");

	obuf=kalloc(1024);
	s=obuf;
	s=kprints(s, "HTTP/1.0 200 OK\n");
	s=kprints(s, "Server: SYS-BGB/0.1\n");
	s=kprints(s, "MIME-Version: 1.0\n");
	s=kprints(s, "Content-Type: %s\n", type);
	s=kprints(s, "Content-Length: %d\n", len);
	s=kprints(s, "\n");

	vfwrite(obuf, 1, s-obuf, con->sock);
	vfwrite(msg, 1, len, con->sock);

	return(0);
}

int HttpNode_SendResponse(HTTP_Con *con, byte *msg, int len)
{
	HttpNode_SendContents(con, "text/xml", msg, len);

	return(0);
}

int HttpNode_SendDir(HTTP_Con *con, char *name)
{
	VDIR *dir;
	long key, lkey;

	long buf[16];
	char *cols[16];
	int i;

	char *obuf, *s;

	kprint("send dir\n");

	dir=vfopendir(name);

	if(!dir)
	{
		kprint("dir %s\n", name);
		HttpNode_Send404(con, "text/html", NULL, 0);
		return(0);
	}

	obuf=kalloc(16384);
	s=obuf;

	s=kprints(s, "<html><body>\n");

	key=0;
	while(1)
	{
		lkey=VDir_DupKey(dir, key);
		i=VDir_ReadDir(buf, cols, &key, dir);
		if(!i)break;
		if(!lkey)
		{
			s=kprints(s, "(");
			for(i=0; i<16 && cols[i]; i++)
			{
				if(i)s=kprints(s, " ");
				s=kprints(s, "%s", cols[i]);
			}
			s=kprints(s, ")<br><br>\n");
		}

		s=kprints(s, "(");
		for(i=0; i<16 && cols[i]; i++)
		{
			if(i)s=kprints(s, " ");
			if(!strcmp(cols[i], "$name"))
			{
				s=kprints(s, "<a href=\"");
				s=kprints(s, "%s%s\">", name, buf[i]);
				s=kprints(s, "%s", buf[i]);
				s=kprints(s, "</a>");
			}else
			{
				if(cols[i][0]=='$')s=kprints(s, "%s", buf[i]);
				if(cols[i][0]=='%')s=kprints(s, "%d", buf[i]);
			}
		}
		s=kprints(s, ")<br>\n");
	}

	s=kprints(s, "</body></html>\n");

	kprint("send dir: ok %d\n", s-obuf);

	HttpNode_SendContents(con, "text/html", obuf, s-obuf);
	con->state=HTTPSTATE_CLOSE;

	kfree(obuf);

	return(0);
}

int HttpNode_SendPage(HTTP_Con *con)
{
	int sz, i;
	char *buf, *s, *t;
	VDIR *dir;

	kprint("send page\n");

	s=kralloc(strlen(con->req)+25);
	strcpy(s, con->req);
	if(s[strlen(s)-1]=='/')strcat(s, "index.html");

	buf=sa_loadfile(s, &sz);

	if(!buf)
	{
		s=con->req;
		if(s[strlen(s)-1]=='/')
		{
			HttpNode_SendDir(con, con->req);
			return(0);
		}
		HttpNode_Send404(con, "text/html", NULL, 0);
		return(0);
	}

/*
	s=buf;
	s=kprints(s, "\n");
	s=kprints(s, "<html><body>\n");
	s=kprints(s, "hello!<br>sv time=%d<br>\n", Sys_TimeMS());
	s=kprints(s, "</body></html>\n");

	sz=s-buf;
*/
//	sz=strlen(buf);
	HttpNode_SendContents(con, "text/html", buf, sz);
	con->state=HTTPSTATE_CLOSE;

	return(0);
}

int HttpNode_Send404(HTTP_Con *con, byte *type, byte *msg, int len)
{
	int sz, i;
	char *obuf, *s, *t;
	char *tbuf[16];

	kprint("send 404\n");

	obuf=kalloc(1024);

	s=obuf;
	s=kprints(s, "HTTP/1.0 404 Not Found\n");
	s=kprints(s, "Server: SYS/BGB\n");
//	s=kprints(s, "MIME-Version: 1.0\n");
//	s=kprints(s, "Content-Type: %s\n", type);
	s=kprints(s, "Content-Length: %d\n", 0);
	s=kprints(s, "Connection: close\n");
	s=kprints(s, "\n");

	vfwrite(obuf, 1, s-obuf, con->sock);
//	vfwrite(msg, 1, len, con->sock);

	con->state=HTTPSTATE_CLOSE;
/*
	vfclose(con->sock);
	httpnode_cons[con->num]=NULL;
	if(con->buf)kfree(con->buf);
	kfree(con);
*/

	return(0);
}

int HttpNode_HandleLine(HTTP_Con *con, char *lb)
{
	int sz, i;
	char *obuf, *s, *t;
	char **tbuf;

	tbuf=kralloc(16*sizeof(char *));
	for(i=0; i<16; i++)tbuf[i]=kralloc(64);

	kprint("line: '%s'\n", lb);

	s=lb;
	i=0;
	while(*s)
	{
//		kprint(" a %d\n", i);
		t=tbuf[i++];
		while(*s>' ')*t++=*s++;
		*t++=0;
		while(*s && (*s<=' '))s++;
	}

//	kprint(" b\n");

	if(!*tbuf[0])
	{
		switch(con->state)
		{
		case HTTPSTATE_GET:
			con->state=0;
			HttpNode_SendPage(con);
			break;
		case HTTPSTATE_POST:
			con->state=HTTPSTATE_RECD;
			con->rbuf=kalloc(con->rlen);
			con->erbuf=con->rbuf;
			break;
		default:
			con->state=0;
			break;
		}
		return(0);
	}

//	kprint(" c\n");

	if(!stricmp(tbuf[0], "GET"))
	{
		con->state=HTTPSTATE_GET;
		strcpy(con->req, tbuf[1]);
	}
	if(!stricmp(tbuf[0], "POST"))
	{
		con->state=HTTPSTATE_POST;
	}
	if(!stricmp(tbuf[0], "Content-Length:"))
	{
		con->rlen=atoi(tbuf[1]);
	}

//	kprint(" d\n");
	return(0);
}

int HttpNode_HandleMessage(HTTP_Con *con, char *msg)
{
//	kprint("message: %s", msg);
	XmlRpc_HandleMessage(con, msg);
	return(0);
}

int HttpNode_HandleConnection(HTTP_Con *con)
{
	int sz, i;
	char *obuf, *s, *t;
	char mbuf[1024], *tbuf[16];

	if(!con->buf)
	{
		con->buf=kalloc(16384);
		con->end=con->buf;
	}

	while(1)
	{
		sz=vfread(con->end, 1, 16484, con->sock);
		if(sz<0)break;
		con->end+=sz;
//		kprint("%s", con->buf);
		if(!(con->end-con->buf))break;

		i=con->end-con->buf;
		if((con->state==HTTPSTATE_RECD) && con->rlen)
		{
			sz=(con->rlen<i)?con->rlen:i;
			memcpy(con->erbuf, con->buf, sz);
			con->erbuf+=sz;
			con->rlen-=sz;

			s=con->buf+sz;
			t=con->buf;
			while(s<con->end)*t++=*s++;
			con->end=t;

			if(!con->rlen)
			{
				con->state=0;
				HttpNode_HandleMessage(con, con->rbuf);
				kfree(con->rbuf);
			}

			continue;
		}

		s=con->buf;
		t=mbuf;
		while(*s && (*s!='\r') && (*s!='\n'))*t++=*s++;
		*t++=0;

		if((*s!='\r') && (*s!='\n'))continue;

		if(*s=='\r')s++;
		if(*s=='\n')s++;

		t=con->buf;
		while(s<con->end)*t++=*s++;
		con->end=t;

		HttpNode_HandleLine(con, mbuf);
	}
	if((sz==-1) || (con->state==HTTPSTATE_CLOSE))
	{
		vfclose(con->sock);
		httpnode_cons[con->num]=NULL;
		if(con->buf)kfree(con->buf);
		kfree(con);
	}

	return(0);
}

int HttpNode_Poll()
{
	VADDR addr;
	int i;
	VFILE *newsock;
	elem t, cur;
	HTTP_Con *con;

	int stime;

	if(!httpnode_sock)return(-1);

	stime=Sys_TimeMS();

	while(1)
	{
		vfioctls(httpnode_sock, "accept", &newsock, &addr);
		if(!newsock)break;

		kprint("HTTP: recieved connection\n");

		con=HttpNode_NewCon();
		con->sock=newsock;
	}

	for(i=0; i<256; i++)if(httpnode_cons[i])
		HttpNode_HandleConnection(httpnode_cons[i]);

	return(0);
}

int HttpNode_Init()
{
	httpnode_sock=NULL;
	if(!httpnode_sock)
	{
		httpnode_port=80;
		httpnode_sock=TCP_OpenListen(httpnode_port);
	}
	if(!httpnode_sock)
	{
		httpnode_port=8080;
		httpnode_sock=TCP_OpenListen(httpnode_port);
	}
	if(!httpnode_sock)
	{
		httpnode_port=7936;
		httpnode_sock=TCP_OpenListen(httpnode_port);
	}
	if(httpnode_sock)
	{
		kprint("HTTP: port opened %d\n", httpnode_port);
	}else
	{
		kprint("HTTP: fail open host port\n");
	}
}