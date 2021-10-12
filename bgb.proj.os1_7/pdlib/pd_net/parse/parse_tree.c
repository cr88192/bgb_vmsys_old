#include <pdlib.h>
#include <pdnet.h>

NetParse_Node *NetParse_NewNode()
{
	NetParse_Node *tmp;

	tmp=kalloc(sizeof(NetParse_Node));
	tmp->next=NULL;
	tmp->key=NULL;
	tmp->text=NULL;
	tmp->attr=NULL;
	tmp->first=NULL;

	return(tmp);
}

NetParse_Node *NetParse_AddNodeEnd(NetParse_Node *first, NetParse_Node *node)
{
	NetParse_Node *cur;

	if(!first)return(node);

	cur=first;
	while(cur->next)cur=cur->next;
	cur->next=node;

	return(first);
}

int NetParse_FreeAttr(NetParse_Attr *attr)
{
	if(attr->next)NetParse_FreeAttr(attr->next);
	if(attr->key)kfree(attr->key);
	if(attr->value)kfree(attr->value);
	kfree(attr);

	return(0);
}

int NetParse_FreeNode(NetParse_Node *node)
{
	NetParse_Node *cur, *next;

	cur=node;
	while(cur)
	{
		next=cur->next;

		if(cur->key)kfree(cur->key);
		if(cur->text)kfree(cur->text);
		if(cur->attr)NetParse_FreeAttr(cur->attr);
		if(cur->first)NetParse_FreeNode(cur->first);
		kfree(cur);

		cur=next;
	}

	return(0);
}

NetParse_Node *NetParse_FindKey(NetParse_Node *first, char *key)
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
