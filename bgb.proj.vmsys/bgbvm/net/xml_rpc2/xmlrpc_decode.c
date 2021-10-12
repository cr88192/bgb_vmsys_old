#include <general.h>
#include <net/pdnet.h>

void *XmlRpc_DecodeMember(NetParse_Node *exp, char **name)
{
	NetParse_Node *n;
	void *p;

	n=NetParse_FindKey(exp->first, "name");
	*name=kstrdup(n->first->text);

	n=NetParse_FindKey(exp->first, "value");
	p=XmlRpc_DecodeValue(n);

	return(p);
}

void *XmlRpc_DecodeStruct(NetParse_Node *exp)
{
	NET_Struct *ns;
	NetParse_Node *cur;
	char **names;
	void **values;
	int i;

	names=kalloc(1024*sizeof(char *));
	values=kalloc(1024*sizeof(void *));
	i=0;

	cur=exp->first;
	while(cur)
	{
		if(!strcmp(cur->key, "member"))
		{
			values[i]=XmlRpc_DecodeMember(cur, &names[i]);
			i++;
		}
		cur=cur->next;
	}
	names[i]=NULL;
	values[i]=NULL;

//	ns=kalloc(sizeof(NET_Struct));
	ns=ObjType_New("d_struct_t", 0);

//	ns->names=kalloc((i+1)*sizeof(char *));
//	ns->values=kalloc((i+1)*sizeof(void *));

	ns->names=ObjType_New("array_t", (i+1)*sizeof(char *));
	ns->values=ObjType_New("array_t", (i+1)*sizeof(void *));

	memcpy(ns->names, names, (i+1)*sizeof(char *));
	memcpy(ns->values, values, (i+1)*sizeof(void *));

	return(ns);
}

void *XmlRpc_DecodeArray(NetParse_Node *exp)
{
	NET_Array *ns;
	NetParse_Node *cur;
	void **values;
	int i;

	values=kalloc(1024*sizeof(void *));
	i=0;

	cur=exp->first;

	if(cur->key)if(!strcmp(cur->key, "data"))cur=cur->first;

	while(cur)
	{
		values[i]=XmlRpc_DecodeValue(cur->first);
		i++;
		cur=cur->next;
	}
	values[i]=NULL;

//	ns=kalloc(sizeof(NET_Array));
	ns=ObjType_New("d_array_t", 0);

//	ns->types=kalloc((i+1)*sizeof(char *));
//	ns->values=kalloc((i+1)*sizeof(long));

	ns->values=ObjType_New("array_t", (i+1)*sizeof(void *));

	memcpy(ns->values, values, (i+1)*sizeof(void *));

	return(ns);
}

void *XmlRpc_DecodeValue(NetParse_Node *exp)
{
	char *s, *t, *b;
	int i, j;
	void *p;

	if(exp->text)
	{
		s=ObjType_New("string_t", strlen(exp->text)+1);
		strcpy(s, exp->text);
		return(s);
	}

	if(!strcmp(exp->key, "value"))
		return(XmlRpc_DecodeValue(exp->first));

	if(!strcmp(exp->key, "param"))
		return(XmlRpc_DecodeValue(exp->first));

	if(!strcmp(exp->key, "int"))
	{
		p=ObjType_New("int_t", 0);
		*(int *)p=atoi(exp->first->text);
		return(p);
	}
	if(!strcmp(exp->key, "i4"))
	{
		p=ObjType_New("int_t", 0);
		*(int *)p=atoi(exp->first->text);
		return(p);
	}

	if(!strcmp(exp->key, "bool"))
	{
		p=ObjType_New("bool_t", 0);
		*(int *)p=atoi(exp->first->text);
		return(p);
	}

	if(!strcmp(exp->key, "boolean"))
	{
		p=ObjType_New("bool_t", 0);
		*(int *)p=atoi(exp->first->text);
		return(p);
	}

	if(!strcmp(exp->key, "string"))
	{
		s=ObjType_New("string_t", strlen(exp->first->text)+1);
		strcpy(s, exp->first->text);
		return(s);
	}

	if(!strcmp(exp->key, "double"))
	{
		p=ObjType_New("float_t", 0);
		*(double *)p=atof(exp->first->text);
		return(p);
	}

	if(!strcmp(exp->key, "dateTime.iso8601"))
	{
//		b=kalloc(8);
		b=ObjType_New("date_t", 0);
		s=exp->first->text;
		t=b;

		i=((s[0]-'0')*1000)+((s[1]-'0')*100)+((s[2]-'0')*10)+(s[3]-'0');
		*t++=i>>8;
		*t++=i&0xff;
		s+=4;

		i=2;
		while(i--)
		{
			*t++=((s[0]-'0')*10)+(s[1]-'0');
			s+=2;
		}
		i=3;
		while(i--)
		{
			s++;
			*t++=((s[0]-'0')*10)+(s[1]-'0');
			s+=2;
		}
		return(b);
	}

	if(!strcmp(exp->key, "base64"))
	{
		s=exp->first->text;
		i=strlen(s);
		j=(i*3)/4;
//		b=kalloc(j+sizeof(long));
		b=ObjType_New("data_t", j);
//		*(long *)b=j;
//		t=b+sizeof(long);
		t=b;

		kprint("recv mime %d->%d\n", i, j);

		HttpNode_DecodeMime(t, s, i);

		return(b);
	}

	if(!strcmp(exp->key, "array"))
	{
		return(XmlRpc_DecodeArray(exp));
	}

	if(!strcmp(exp->key, "struct"))
	{
		return(XmlRpc_DecodeStruct(exp));
	}

	kprint("XML-RPC: Decode: Unknown type tag '%s'\n", exp->key);
	return(NULL);
}
