#include <general.h>

PDLIB_ObjType *pdlib_objtypes=NULL;

int ObjType_FormSize(char *form)
{
	char *s, *t;
	char tbuf[16];
	int sz, b, c;
	PDLIB_ObjType *ty;

	sz=0;
	s=form;

	while(*s)
	{
		c=1;
		while(1)
		{
			t=tbuf;
			while(*s && (*s>='0') && (*s<='9'))*t++=*s++;
			*t++=0;
			if(tbuf[0])c*=atoi(tbuf);
			if(*s!=',')break;
		}

		t=tbuf;
		while(*s && (*s!=':') && (*s!=';') && (*s!='+'))*t++=*s++;
		*t++=0;

		while(*s && (*s!=';') && (*s!='+'))s++;
		if(*s==';')s++;

		if(*s=='+')return(sz); //terminal not included in size


		if(tbuf[0]=='*')b=sizeof(void *);
			else
		{
			b=0;
			if(!strcmp(tbuf, "char"))b=1;
			if(!strcmp(tbuf, "byte"))b=1;
			if(!strcmp(tbuf, "sbyte"))b=1;
			if(!strcmp(tbuf, "short"))b=sizeof(short);
			if(!strcmp(tbuf, "ushort"))b=sizeof(short);
			if(!strcmp(tbuf, "int"))b=sizeof(int);
			if(!strcmp(tbuf, "uint"))b=sizeof(int);
			if(!strcmp(tbuf, "long"))b=sizeof(long);
			if(!strcmp(tbuf, "ulong"))b=sizeof(long);
			if(!strcmp(tbuf, "float"))b=sizeof(float);
			if(!strcmp(tbuf, "double"))b=sizeof(double);
			if(!strcmp(tbuf, "string"))b=sizeof(char *);
			if(!b)
			{
				ty=ObjType_FindType(tbuf);
				if(ty)b=ty->size;
			}

			if(!b)
			{
				kprint("ObjType_FormSize: unknown type '%s'\n", tbuf);
				return(0);
			}
		}
		if(sz%b)
		{
			kprint("ObjType_FormSize: alignment error\n");
			return(0);
		}
		sz+=b*c;
	}
	return(sz);
}

PDLIB_ObjType *ObjType_NewType(char *name, char *form)
{
	PDLIB_ObjType *tmp;

	tmp=ObjType_FindType(name);
	if(tmp)
	{
		if(strcmp(form, tmp->form))
		{
			kprint("ObjType_NewType: mismatched redefinition "
				"of type '%s'.\n", name);
			return(NULL);
		}else return(tmp);
	}

	tmp=kalloc(sizeof(PDLIB_ObjType));
	tmp->name=kstrdup(name);
	tmp->form=kstrdup(form);
	tmp->size=ObjType_FormSize(form);

	tmp->next=pdlib_objtypes;
	pdlib_objtypes=tmp;

	kprint("type: %s form: '%s' size: %d\n", name, form, tmp->size);

	return(tmp);
}

PDLIB_ObjType *ObjType_FindType(char *type)
{
	PDLIB_ObjType *cur;

	cur=pdlib_objtypes;
	while(cur)
	{
		if(!strcmp(type, cur->name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

void *ObjType_New(char *type, int size)
{
	PDLIB_ObjType *ty;
	PDLIB_ObjInfo *inf;
	void *tmp;
	int sz;

	ty=ObjType_FindType(type);
	if(!ty)
	{
		kprint("ObjType_New: unknown type '%s'\n", type);
		return(NULL);
	}
	if(!size)size=ty->size;

	if(size<ty->size)
	{
		kprint("ObjType_New: size too small %d<'%s':%d\n",
			size, type, ty->size);
		return(NULL);
	}

	sz=size+sizeof(PDLIB_ObjInfo);
	inf=kalloc(sz);
	tmp=((void *)inf)+sizeof(PDLIB_ObjInfo);
	memset(tmp, 0, size);

	inf->type=ty;
	inf->size=size;

	return(tmp);
}

PDLIB_ObjType *ObjType_GetType(void *p)
{
	PDLIB_ObjInfo *inf;

//	inf=MM2_GetBase(p);
	inf=p-sizeof(PDLIB_ObjInfo);

	return(inf->type);
}

char *ObjType_GetTypeName(void *p)
{
	PDLIB_ObjInfo *inf;

//	inf=MM2_GetBase(p);
	inf=p-sizeof(PDLIB_ObjInfo);

	return(inf->type->name);
}

int ObjType_GetSize(void *p)
{
	PDLIB_ObjInfo *inf;

//	inf=MM2_GetBase(p);
	inf=p-sizeof(PDLIB_ObjInfo);

	return(inf->size);
}

int ObjType_Init()
{
	pdlib_objtypes=NULL;

	ObjType_NewType("string", "*char;");

	return(0);
}
