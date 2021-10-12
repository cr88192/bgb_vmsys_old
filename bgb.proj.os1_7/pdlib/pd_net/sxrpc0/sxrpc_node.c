/*
type encoding/decoding, message passing, ...
 */

#include <pdlib.h>
#include <pdnet.h>

SXRPC_Con *sxrpc_curcon;
//elem sxrpc_export_names;
//elem sxrpc_export_values;

//elem sxrpc_return_contids;
//elem sxrpc_return_values;


NetParse_Node *SXRPC_FindKey(NetParse_Node *first, char *key)
{
	NetParse_Node *cur;

	cur=first;
	while(cur)
	{
		if(cur->key)
			if(!strcmp(cur->key, key))
				return(cur);
		cur=cur->next;
	}
	return(NULL);
}

#if 0

int SXRPC_AddReturn(int contid, elem value)
{
//	sxrpc_return_contids=CONS(FIXNUM(contid), sxrpc_return_contids);
//	sxrpc_return_values=CONS(value, sxrpc_return_values);

	return(0);
}

//elem SXRPC_FetchReturn();

elem SXRPC_DecodeMap(NetParse_Node *first)
{
	NetParse_Node *cur;
	elem t, var, val;

	t=TyObj_CloneNull();

	cur=first;
	while(cur)
	{
		var=SYM(cur->text);
		val=SXRPC_DecodeType(cur->next);
		TyObj_SetSlot(t, var, val);

		cur=cur->next;
		cur=cur->next;
	}

	return(t);
}

elem SXRPC_DecodeArray(NetParse_Node *first)
{
	NetParse_Node *cur;
	elem t, x;

	x=MISC_EOL;
	cur=first;
	while(cur)
	{
		t=SXRPC_DecodeType(cur);
		x=CONS(t, x);
		cur=cur->next;
	}
	x=TyFcn_NReverse(x);

	return(x);
}

VADDR *SXRPC_DecodeHostname(char *name)
{
	VADDR *tmp;
	if(name[0]=='[')
	{
		tmp=NET_Str2Addr(name, PROTO_IPV6TCP);
		return(tmp);
	}
	if((name[0]>='0') && (name[0]<='9'))
	{
		tmp=NET_Str2Addr(name, PROTO_IPV4TCP);
		return(tmp);
	}

	tmp=NET_LookupHost2(name, PROTO_IPV6);
	if(tmp)return(tmp);
	tmp=NET_LookupHost(name);
	return(tmp);
}

elem SXRPC_DecodeLink(char *str)
{
	VADDR *addr;
	SXRPC_Link *link;

	char protocol[16];
	char host[32];
	char name[64];
	char s_name[64];

	char *s, *t;


	protocol[0]=0;
	host[0]=0;
	name[0]=0;
	s_name[0]=0;

	t=name;
	s=str;
	while(*s)
	{
		if(*s=='!')
		{
			t=protocol;
			s++;
			continue;
		}
		if(*s=='@')
		{
			t=host;
			s++;
			continue;
		}
		if(*s=='#')
		{
			t=name;
			s++;
			continue;
		}
		if(*s=='$')
		{
			t=s_name;
			s++;
			continue;
		}
		if(*s=='%')break;
		if(*s=='^')break;
		if(*s=='&')break;

		*t++=*s++;
		*t=0;
	}

	if(host[0])
	{
		addr=SXRPC_DecodeHostname(host);

		link=TypeX_Alloc("sxrpc-link", sizeof(SXRPC_Link));

		if(protocol[0])
			link->proto=kstrdup(protocol);
			else link->proto=kstrdup("sxrpc");

		link->host=addr;
		if((name[0]>='0') && (name[0]<='9'))link->objid=atoi(name);
			else link->name=kstrdup(name);

		return(TypeX_GetReference(link));
	}

	if(name[0])
	{
		if((name[0]>='0') && (name[0]<='9'))
			return(MRP_Import(atoi(name)));

		return(SXRPC_FindHandler(name));
	}

	if(s_name[0] && sxrpc_curcon)
	{
		addr=kmemdup(sxrpc_curcon->addr);

		link=TypeX_Alloc("sxrpc-link", sizeof(SXRPC_Link));
		link->proto=kstrdup("sxrpc");
		link->host=addr;
		if((name[0]>='0') && (name[0]<='9'))link->objid=atoi(s_name);
			else link->name=kstrdup(s_name);

		return(TypeX_GetReference(link));
	}

	kprint("SXRPC_DecodeLink: Invalid Link '%s'\n", str);
	return(MISC_UNDEFINED);
}

elem SXRPC_DecodeType(NetParse_Node *exp)
{
	int i;
	double f;

	if(!strcmp(exp->key, "int"))
	{
		i=atoi(exp->first->text);
		return(FIXNUM(i));
	}

	if(!strcmp(exp->key, "float"))
	{
		f=atof(exp->first->text);
		return(FLONUM(f));
	}
	if(!strcmp(exp->key, "string"))
	{
		return(STRING(exp->first->text));
	}
	if(!strcmp(exp->key, "map"))
	{
		return(SXRPC_DecodeMap(exp->first));
	}
	if(!strcmp(exp->key, "array"))
	{
		return(SXRPC_DecodeArray(exp->first));
	}
	if(!strcmp(exp->key, "link"))
	{
		return(SXRPC_DecodeLink(exp->text));
	}

	if(!strcmp(exp->key, "true"))
		return(MISC_TRUE);
	if(!strcmp(exp->key, "false"))
		return(MISC_FALSE);
	if(!strcmp(exp->key, "null"))
		return(MISC_NULL);

	return(MISC_NULL);
}

char *SXRPC_EncodeLink(SXRPC_Link *link)
{
	char buf[256];
	char *s;
	char *t;

	s=buf;

	if(!MRP_AddrEqual(link->host, sxrpc_curcon->addr))
	{
		s=kprints(s, "!%s", link->proto);

		t=NET_Addr2Str(link->host);
		s=kprints(s, "@%s", t);
	}
	if(link->objid)s=kprints(s, "#%d", link->objid);
	if(link->name)s=kprints(s, "#%s", link->name);

	return(krstrdup(buf));
}

NetParse_Node *SXRPC_EncodeArray(elem lst)
{
	elem cur;
	NetParse_Node *n, *f;

	f=NULL;

	cur=lst;
	while(ELEM_CONSP(cur))
	{
		n=SXRPC_EncodeValue(CAR(cur));
		f=NetParse_AddNodeEnd(f, n);

		cur=CDR(cur);
	}

	n=NetParse_NewNode();
	n->key=kstrdup("array");
	n->first=f;

	return(n);
}

NetParse_Node *SXRPC_EncodeStruct(elem obj)
{
	elem lst, cur;
	elem t, t2, x;

	NetParse_Node *n, *f;

	f=NULL;

	lst=TyObj_SlotNames(obj);
	cur=lst;
	while(ELEM_CONSP(cur))
	{
		n=NetParse_NewNode();
		n->text=kstrdup(ELEM_TOSYMBOL(CAR(cur)));
		f=NetParse_AddNodeEnd(f, n);

		t=TyObj_GetSlot(obj, CAR(cur));
		n=SXRPC_EncodeValue(t);
		f=NetParse_AddNodeEnd(f, n);

		cur=CDR(cur);
	}

	n=NetParse_NewNode();
	n->key=kstrdup("struct");
	n->first=f;

	return(n);
}

NetParse_Node *SXRPC_EncodeDate(elem obj)
{
	char buf[18];
	int i, a[6];

	NetParse_Node *n, *f;

	for(i=0; i<6; i++)a[i]=TOINT(LIST_REF(obj, i+1));
	sprintf(buf, "%04d%02d%02dT%02d:%02d:%02d",
		a[0], a[1], a[2], a[3], a[4], a[5]);

	f=NetParse_NewNode();
	f->text=kstrdup(buf);

	n=NetParse_NewNode();
	n->key=kstrdup("time");
	n->first=f;

	return(n);
}

NetParse_Node *SXRPC_EncodeValue(elem val)
{
	char buf[64];
	NetParse_Node *n, *f;
	char *s, *s2;
	int i;

	if(ELEM_STRINGP(val))
	{
		f=NetParse_NewNode();
		f->text=kstrdup(ELEM_TOSTRING(val));

		n=NetParse_NewNode();
		n->key=kstrdup("string");
		n->first=f;

		return(n);
	}
	if(ELEM_FIXNUMP(val))
	{
		sprintf(buf, "%d", TOINT(val));

		f=NetParse_NewNode();
		f->text=kstrdup(buf);

		n=NetParse_NewNode();
		n->key=kstrdup("string");
		n->first=f;

		return(n);
	}
	if(ELEM_FLONUMP(val))
	{
		sprintf(buf, "%g", TOFLOAT(val));

		f=NetParse_NewNode();
		f->text=kstrdup(buf);

		n=NetParse_NewNode();
		n->key=kstrdup("float");
		n->first=f;

		return(n);
	}

	if(ELEM_CONSP(val))
	{
		if(CAR(val)==SYM("date-time:"))
		{
			n=SXRPC_EncodeDate(val);
			return(n);
		}

		n=SXRPC_EncodeArray(val);
		return(n);
	}

	if(ELEM_ENVOBJP(val))
	{
		n=SXRPC_EncodeStruct(val);
		return(n);
	}

	if(ELEM_BYTEVECTORP(val))
	{
		s=TyFcn_ByteVectorBody(val);
		i=VECTOR_LEN(val);
		s2=kalloc(((i*4)/3)+5);
		HttpNode_EncodeMime(s2, s, i);

		kprint("send mime %d->%d\n", i, (i*4)/3);

		f=NetParse_NewNode();
		f->text=s2;

		n=NetParse_NewNode();
		n->key=kstrdup("base64");
		n->first=f;

		return(n);
	}

	if(val==MISC_TRUE)
	{
		n=NetParse_NewNode();
		n->key=kstrdup("true");
		return(n);
	}
	if(val==MISC_FALSE)
	{
		n=NetParse_NewNode();
		n->key=kstrdup("false");
		return(n);
	}

	if(val==MISC_NULL)
	{
		n=NetParse_NewNode();
		n->key=kstrdup("null");
		return(n);
	}

	n=NetParse_NewNode();
	n->key=kstrdup("null");
	return(n);
}

NetParse_Node *SXRPC_EncodeArgs(elem lst)
{
	elem cur;
	NetParse_Node *n, *f;

	f=NULL;

	cur=lst;
	while(ELEM_CONSP(cur))
	{
		n=SXRPC_EncodeValue(CAR(cur));
		f=NetParse_AddNodeEnd(f, n);

		cur=CDR(cur);
	}

	n=NetParse_NewNode();
	n->key=kstrdup("args");
	n->first=f;

	return(n);
}

int SXRPC_HandlePass(SXRPC_Con *con, NetParse_Node *exp)
{
	elem fcn, args;
	NetParse_Node *n;

	sxrpc_curcon=con;
	fcn=SXRPC_DecodeLink(exp->first->text);
	if(fcn==MISC_UNDEFINED)
	{
		kprintvf(con->sock, "(error bad-proc \"%s\")\n",
			exp->first->text);
		return(0);
	}

	n=SXRPC_FindKey(exp->first, "args");
	if(n)args=SXRPC_DecodeArray(n->first);
		else args=MISC_EOL;
	NetParse_FreeNode(exp);

	Interp_ApplyCtxSafe(Interp_NewCtx(), fcn, args);

	sxrpc_curcon=NULL;

	return(0);
}

int SXRPC_PassLink(SXRPC_Link *link, elem args)
{
	NetParse_Node *n;
	char *s, *t;

	SXRPC_Con *con;

	con=SXRPC_FindCon(link->host);
	if(!con)con=SXRPC_Connect(link->host);
	if(!con)
	{
		kprint("SXRPC_PassLink: connection failed\n");
		return(-1);
	}

	s=kralloc(1024);
	t=s;

	sxrpc_curcon=con;

	n=SXRPC_EncodeArgs(args);
	t=NetParse_SX_PrintExpr(t, n);
	NetParse_FreeNode(n);

	kprintvf(con->sock, "(pass \"%s\" %s)\n",
		SXRPC_EncodeLink(link), s);

	sxrpc_curcon=NULL;

	return(0);
}
#endif
