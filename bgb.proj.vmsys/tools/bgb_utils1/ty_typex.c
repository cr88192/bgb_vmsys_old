#include <scmcc.h>

typexinfo *typex_root;

elem TyFcn_TypeX(elem sym, int sz, void *buf)
{
	elem *t;
	t=sa_alloc((2*ELEM_SZ) + sz);
	t[0]=OBJECT_TYPEX | (sz<<16);
	t[1]=(elem)TypeX_GetInfo(ELEM_TOSYMBOL(sym));
	memcpy(t+2, buf, sz);
	return(ELEM_FROMOBJECT(t));
}

void *TypeX_Alloc(char *type, int sz)
{
	elem *t;
	t=sa_alloc((2*ELEM_SZ) + sz);
	t[0]=OBJECT_TYPEX | (sz<<16);
	t[1]=(elem)TypeX_GetInfo(type);
	memset(t+2, 0, sz);
	return(t+2);
}

elem TypeX_Sym(elem obj)
{
	elem *t;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];
	return(SYM(ti->name));
}

elem TypeX_Func(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->apply)return(MISC_UNDEFINED);

	return(TyFcn_Function(ti->apply, -2));
}

void *TypeX_Data(elem obj)
{
	elem *t;
	t=ELEM_TOOBJECT(obj);
	return((void *)(t+2));
}

int TypeX_Mark(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->mark)return(-1);

	ti->mark(obj);

	return(0);
}

typexinfo *TypeX_Lookup(char *name)
{
	typexinfo *cur;

	cur=typex_root;
	while(cur)
	{
		if(!strcmp(cur->name, name))
			return(cur);
		cur=cur->next;
	}
	return(NULL);
}

typexinfo *TypeX_GetInfo(char *name)
{
	typexinfo *tmp;

	tmp=TypeX_Lookup(name);
	if(tmp)return(tmp);

	SYM(name); //ensure cached

	tmp=sa_malloc(sizeof(typexinfo));
	tmp->next=typex_root;
	tmp->prev=NULL;
	tmp->name=sa_strdup(name);

	typex_root=tmp;

	return(tmp);
}

int TypeX_Init()
{
	typex_root=NULL;
}
