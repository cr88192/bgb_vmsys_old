/*
this will handle general GenObjects
this is too deeply tied into the mm... I generally need to define the GenObject system anyways.

GenObjects will have a 4 byte header, the low 9 bits will be a type, the high 16 a size.

raw: raw data, like that achieved by MM2_PAlloc/kalloc exept that it is collected

struct: will have a pointer to a string
	this string will consist of byte pairs, the first the type, the second the access
	first:
		'u': pointer to data
		'p': pointer to collected data (!p&3), p&3=1 then int
	second:
		'r': read-only member
		'w': read/write member
		'R': read-only array
		'W': read/write array
		arrays will have a member count followed by that many members of the given type.

the idea:
GenObjects are like those of scheme. they are reasonably basic, and may
reference each other. more complex GenObjects are built out of simpler ones.
an GenObject may be read or written to a possibly textual representation
(but this may not be the rule, ie: a graphic). I will need to move read/print
stuff elsewhere.
*/

#include <general.h>

obj_type *gct_root=NULL;
int gct_last=1;

GenObject *string_print(GenObject *p);
GenObject *struct_print(GenObject *p);

obj_type *GenObj_NewType(char *name);

GenObject *string_null, *string_undefined;

int GenObj_Init()
{
	obj_type *type;
	kprint("Init GenObj\n");

	type=GenObj_NewType("raw");

	type=GenObj_NewType("string");
	type->print=&string_print;

	type=GenObj_NewType("struct");
	type->print=&struct_print;

	string_null=GenObj_NewString("#<null>");
	string_undefined=GenObj_NewString("#<undefined>");
}

obj_type *GenObj_NewType(char *name)
{
	obj_type *tmp;
	tmp=MM2_PAlloc(sizeof(obj_type));
	tmp->num=gct_last++;
	tmp->name=kstrdup(name);
	tmp->next=gct_root;
	gct_root=tmp;
	return(tmp);
}

obj_type *GenObj_LookupTypeNum(int num)
{
	obj_type *cur;
	cur=gct_root;

//	kprint("lookupnum %d\n", num);

	while(cur)
	{
		if(cur->num==num)return(cur);
		cur=cur->next;
	}
	return(NULL);
}

obj_type *GenObj_LookupTypeName(char *name)
{
	obj_type *cur;
	cur=gct_root;
	while(cur)
	{
		if(!strcmp(cur->name, name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

void *GenObj_GetData(GenObject *o)
{
	return((void *)(o+1));
}

GenObject *GenObj_Print(GenObject *p)
{
	obj_type *type;

	if(!p)return(string_null);

	type=GenObj_LookupTypeNum(p->head&511);
	if(type)if(type->print)return(type->print(p));
	return(string_undefined);
}

GenObject *GenObj_CreateGeneral(int size, char *tname)
{
	obj_type *type;
	GenObject *t;

	type=GenObj_LookupTypeName(tname);
	if(!type)return(NULL);
	t=MMGC_PAlloc(size+4);
	t->head=type->num+(size<<16);
	return(t);
}

int ref2int(int ref)
{
	int i;
	i=ref>>2;
	if(i&0x40000000)i|=0xC0000000;
	return(i);
}

GenObject *string_print(GenObject *p)
{
	GenObject *s;

	s=GenObj_CreateGeneral(strlen(GenObj_GetData(p))+3, "string");
	kprints(GenObj_GetData(s), "\"%s\"", GenObj_GetData(p));
	return(s);
}

GenObject *struct_print(GenObject *p)
{
	char *s, *s2, *s3;
	GenObject *o1, *o2, *o3;
	int *t;
	int cnt;

	t=GenObj_GetData(p);
	s=*(char **)t;
	t++;

	o1=GenObj_CreateGeneral(1024, "string");
	s2=GenObj_GetData(o1);

	s2=kprints(s2, "(");

	while(*s)
	{
		cnt=1;
		if(s[1]=='W' || s[1]=='R')
		{
			cnt=*t;
			t++;
		}
		for(;cnt; cnt--)switch(*s)
		{
		case 'p':
			if((*t&3)==0)s2=kprints(s2, "%s ", GenObj_GetData(GenObj_Print(*(void **)t)));
			if((*t&3)==1)s2=kprints(s2, "%d ", ref2int(*t));
			t++;
			break;
		default:
			t++;
			break;
		}
		s+=2;
	}
	s2=kprints(s2, ")");
	s2=GenObj_GetData(o1);

	o2=GenObj_CreateGeneral(strlen(s2)+1, "string");

	s3=GenObj_GetData(o2);
	strcpy(s3, s2);

	return(o2);
}

GenObject *GenObj_StructNew(char *form, ...)
{
	int *t, *t2, *t3, c, cnt;
	char *s;
	GenObject *o1;

	t=(int *)&form;
	t++;
	s=form;

	c=0;
	while(*s)
	{
		cnt=1;
		if(s[1]=='W' || s[1]=='R')
		{
			cnt=*t;
			t++;
			c++;
		}
		for(;cnt; cnt--)
		{
			t++;
			c++;
			break;
		}
		s+=2;
	}

	t=(int *)&form;
	t++;
	s=form;

	o1=GenObj_CreateGeneral((c+9)*sizeof(int), "struct");
	t2=GenObj_GetData(o1);
	*t2=(int)form;
	t3=t2+1;

	memcpy(t3, t, c*sizeof(int));

	return(o1);
}

GenObject *GenObj_NewString(char *s)
{
	char *s2;
	GenObject *o1;

	o1=GenObj_CreateGeneral(strlen(s)+1, "string");
	if(!o1)
	{
		kprint("couldn't alloc.\n");
		return(NULL);
	}

	s2=GenObj_GetData(o1);
	strcpy(s2, s);
	return(o1);
}
