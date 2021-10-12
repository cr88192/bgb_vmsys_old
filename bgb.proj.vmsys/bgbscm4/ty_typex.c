#include <scmcc.h>

typexinfo *typex_root;

elem TyFcn_TypeX(elem sym, int sz, void *buf)
{
	elem *t;
	t=sa_alloc((2*ELEM_SZ) + sz);
	t[0]=OBJECT_TYPEX | (sz<<16);
	t[1]=(elem)TypeX_GetInfo(ELEM_TOSYMBOL(sym));
	if(buf)memcpy(t+2, buf, sz);
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

elem TypeX_GetReference(void *p)
{
	elem *s;
	elem t;

	s=p;
	s-=2;

	t=ELEM_FROMOBJECT(s);

	if(!ELEM_TYPEXP(t))sa_fatal("TypeX_GetReference: type check\n");

	return(t);
}

elem TypeX_Apply(elem obj, elem args)
{
	elem *t;
	elem t2;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->apply)return(MISC_UNDEFINED);

	t2=ti->apply(obj, args);

	return(0);
}

int TypeX_Mark(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

//	kprint("typex mark %s\n", ti->name);

	if(!ti->mark)return(-1);

//	return(-1);

	ti->mark(obj);

	return(0);
}

int TypeX_SwizIn(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

//	kprint("typex swizin %s\n", ti->name);

	if(!ti->swizin)return(-1);
	ti->swizin(obj);

	return(0);
}

int TypeX_SwizOut(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

//	kprint("typex swizout %s\n", ti->name);

	if(!ti->swizout)return(-1);
	ti->swizout(obj);

	return(0);
}

int TypeX_Print(elem obj, typrint_info *inf)
{
	elem *t;
	typexinfo *ti;
	elem t2;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->print)
	{
		if(ti->flatten)
		{
			t2=ti->flatten(obj);

			if(inf)
			{
				inf->end=sa_prints(inf->end, "#x{%s ",
					ti->name);
				TyPrint_Elem(t2, inf);
				inf->end=sa_prints(inf->end, "}");
			}else
			{
				sa_print("#x{%s ", ti->name, obj);
				TyFcn_DumpElem(t2);
				sa_print("}");
			}
		}

		if(inf)
			inf->end=sa_prints(inf->end, "#<typex %s %X>",
				ti->name, obj);
			else sa_print("#<typex %s %X>", ti->name, obj);
		return(0);
	}

	ti->print(obj, inf);

	return(0);
}

int TypeX_Free(elem obj)
{
	elem *t;
	typexinfo *ti;
	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->free)return(-1);

	ti->free(obj);

	return(0);
}

elem TypeX_Flatten(elem obj)
{
	elem *t, x;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->flatten)return(MISC_UNDEFINED);
	x=ti->flatten(obj);

	return(x);
}

elem TypeX_UnFlatten(elem type, elem def)
{
	elem x;
	typexinfo *ti;

	ti=TypeX_GetInfo(ELEM_TOSYMBOL(type));

	if(!ti->unflatten)return(MISC_UNDEFINED);
	x=ti->unflatten(def);

	return(x);
}

elem TypeX_Mirrors(elem obj)
{
	elem *t, x;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->mirrors)return(MISC_UNDEFINED);
	x=ti->mirrors(obj);

	return(x);
}

elem TypeX_Stub(elem type, elem mirrors)
{
	elem x;
	typexinfo *ti;

	ti=TypeX_GetInfo(ELEM_TOSYMBOL(type));

	if(!ti->stub)return(MISC_UNDEFINED);
	x=ti->stub(mirrors);

	return(x);
}

int TypeX_Notify(elem obj, elem other, elem state)
{
	elem *t;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->notify)return(-1);
	ti->notify(obj, other, state);

	return(0);
}

int TypeX_Delta(elem obj, elem var, elem val)
{
	elem *t;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->delta)return(-1);
	ti->delta(obj, var, val);

	return(0);
}

elem TypeX_EvalSingle(elem obj, elem ctx)
{
	elem *t, x;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->evalsingle)return(MISC_UNDEFINED);
	x=ti->evalsingle(obj, ctx);

	return(x);
}

elem TypeX_EvalMulti(elem obj, elem ref, elem ctx)
{
	elem *t, x;
	typexinfo *ti;

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];

	if(!ti->evalmulti)return(MISC_UNDEFINED);
	x=ti->evalmulti(obj, ref, ctx);

	return(x);
}


int TypeX_TypeP(elem obj, char *type)
{
	elem *t;
	typexinfo *ti;

	if(!ELEM_TYPEXP(obj))return(0);

	t=ELEM_TOOBJECT(obj);
	ti=(typexinfo *)t[1];
	return(!strcmp(type, ti->name));
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
	memset(tmp, 0, sizeof(typexinfo));

//	kprint("typex %s %X\n", name, tmp);

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
