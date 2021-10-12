#include <pdlib.h>
#include <pdnet.h>

int xmlrpc_get(HTTP_Resource *rsrc, HTTP_Con *con, char **type, char **data, int *len)
{
	*type=kstrdup("text/plain");
	*data=kstrdup("PDLIB: XML-RPC: GET Unsuported\n");
	*len=strlen(*data);
	return(403);
}

int xmlrpc_post(HTTP_Resource *rsrc, HTTP_Con *con, char **type, char **data, int *len)
{
	char *s, *t;
	char *fcn;

	char **argn;
	long *args;
	int i;
	void *l;
	char tbuf[256];

	NetParse_Node *exp, *cur, *n, *n2;


	s=*data;
	exp=NetParse_XML_ParseExpr(&s);

	if(exp)if(exp->key)if(!strcmp(exp->key, "?xml"))
		exp=NetParse_XML_ParseExpr(&s);

	if(!exp)
	{
		*type=kstrdup("text/plain");
		*data=kstrdup("PDLIB: XML-RPC: Parsed invalid request\n");
		*len=strlen(*data);
		return(403);
	}
	if(!exp->key)
	{
		*type=kstrdup("text/plain");
		*data=kstrdup("PDLIB: XML-RPC: Parsed invalid request\n");
		*len=strlen(*data);
		return(403);
	}

	if(!strcmp(exp->key, "methodCall"))
	{
		args=kalloc(8*sizeof(void *));
		i=0;

		n=NetParse_FindKey(exp->first, "methodName");
		fcn=n->first->text;

		n=NetParse_FindKey(exp->first, "params");
		cur=n->first;
		while(cur)
		{
			args[i]=XmlRpc_DecodeValue(cur->first);
			i++;
			cur=cur->next;
		}
		args[i++]=NULL;

		kprint("XML-RPC: Call '%s'\n", fcn);

		l=NET_CallExport(fcn, args);

		if(!l)
		{
			sprintf(tbuf, "PDLIB: XML-RPC: No Function '%s'\n", fcn);

			*type=kstrdup("text/plain");
			*data=kstrdup(tbuf);
			*len=strlen(*data);
			return(403);
		}

		n=XmlRpc_EncodeValue(l);

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("value");
		n->first=n2;

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("param");
		n->first=n2;

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("params");
		n->first=n2;

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("methodResponse");
		n->first=n2;

		s=kalloc(16384);
		t=s;
		t=kprints(t, "<?xml version=\"1.0\"?>\n");
//		t=kprints(t, "<!-- test -->\n");
		t=NetParse_XML_PrintExpr(t, n);
		t=kprints(t, "\n");

		kprint("XML-RPC: send %s\n", s);

		*type=kstrdup("text/xml");
		*data=s;
		*len=strlen(s);
		return(200);
	}

	sprintf(tbuf, "PDLIB: XML-RPC: Unknown request type '%s'\n", exp->key);

	*type=kstrdup("text/plain");
	*data=kstrdup(tbuf);
	*len=strlen(*data);
	return(403);
}

int xmlrpc_head(HTTP_Resource *rsrc, HTTP_Con *con, char **type, int *len)
{
	*type=kstrdup("text/plain");
//	*data=kstrdup("PDLIB: XML-RPC: HEAD Unsuported\n");
//	*len=strlen(*data);
	*len=0;

	return(403);
}

NET_Reference *xmlrpc_decode_url(char *s)
{
	NET_Reference *ref;
	HTTP_RefInfo *ri;
	char *t;
	char buf[1024];
	VADDR *addr;

	ref=ObjType_New("netref_t", 0);

	ri=kalloc(sizeof(HTTP_RefInfo));
	ref->refinfo=ri;

	while(*s=='/')s++;
	t=buf;
	while(*s!='/')*t++=*s++;
	*t++=0;

	addr=NET_DecodeHostname(buf);
	if(!addr)
	{
		kprint("HTTP: Unknown host %s\n", buf);
		kfree(ri);
		kfree(ref);
		return(NULL);
	}
	switch(addr->proto)
	{
	case PROTO_IPV4:
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		if(!addr->ipv4.port)
			addr->ipv4.port=htons(80);
		break;
	case PROTO_IPV6:
	case PROTO_IPV6UDP:
	case PROTO_IPV6TCP:
		if(!addr->ipv6.port)
			addr->ipv6.port=htons(80);
		break;
	default:
		break;
	}

	ri->addr=addr;
	ri->host=kstrdup(buf);

	t=buf;
	while(*s && (*s!='?'))*t++=*s++;
	*t++=0;
	ri->req=kstrdup(buf);

	if(*s=='?')s++;

	t=buf;
	while(*s)*t++=*s++;
	*t++=0;
	ri->ext=kstrdup(buf);

	return(ref);
}

char *xmlrpc_encode_url(NET_Reference *ref)
{
	HTTP_RefInfo *ri;
	char *s;
	char buf[1024];

	ri=ref->refinfo;
	sprintf(buf, "xml-rpc://%s%s?%s", ri->host, ri->req, ri->ext);
	s=kstrdup(buf);

	return(s);
}

void *xmlrpc_rpc_call(NET_Reference *ref, void **args)
{
	HTTP_RefInfo *ri;
	NetParse_Node *exp, *cur, *n, *n2, *lst;
	char *s, *t;
	int i;
	void *p;

	kprint("XML-RPC: call\n");

	ri=ref->refinfo;

	lst=NULL;
	for(i=0; args[i]; i++)
	{
		n=XmlRpc_EncodeValue(args[i]);

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("value");
		n->first=n2;

		n2=n;
		n=NetParse_NewNode();
		n->key=kstrdup("param");
		n->first=n2;

		lst=NetParse_AddNodeEnd(lst, n);
	}

	n2=n;
	n=NetParse_NewNode();
	n->key=kstrdup("params");
	n->first=lst;

	exp=n;

	n=NetParse_NewNode();
	n->text=kstrdup(ri->ext);

	n2=n;
	n=NetParse_NewNode();
	n->key=kstrdup("methodName");
	n->first=n2;
	n->next=exp;


	n2=n;
	n=NetParse_NewNode();
	n->key=kstrdup("methodCall");
	n->first=n2;

	s=kalloc(16384);
	t=s;
	t=kprints(t, "<?xml version=\"1.0\"?>\n");
	t=NetParse_XML_PrintExpr(t, n);
	t=kprints(t, "\n");

	t=HttpNode_Post(ref, "text/xml", s, strlen(s));
	kfree(s);

	kprint("XML-RPC: got %s\n", t);

	s=t;
	exp=NetParse_XML_ParseExpr(&t);

	if(exp)if(exp->key)if(!strcmp(exp->key, "?xml"))
		exp=NetParse_XML_ParseExpr(&t);

	if(!exp)
	{
		kprint("PDLIB: XML-RPC: Parsed invalid response\n");
		return(NULL);
	}
	if(!exp->key)
	{
		kprint("PDLIB: XML-RPC: Parsed invalid response\n");
		return(NULL);
	}

	if(!strcmp(exp->key, "methodResponse"))
	{
		n=NetParse_FindKey(exp->first, "params");
		cur=n->first;
		p=XmlRpc_DecodeValue(cur->first);
		return(p);
	}

	return(NULL);
}

int XmlRpc_Init()
{
	HTTP_Resource *rsrc;
	NET_Interface *iface;

	kprint("XML-RPC: Init\n");
	rsrc=HttpNode_NewResource("/RPC2");
	rsrc->get=&xmlrpc_get;
	rsrc->post=&xmlrpc_post;
	rsrc->head=&xmlrpc_head;

	iface=NET_CreateInterface("xml-rpc");
	iface->decode_url=&xmlrpc_decode_url;
	iface->encode_url=&xmlrpc_encode_url;
	iface->rpc_call=&xmlrpc_rpc_call;

	Verify_Init();

	return(0);
}
