#include <general.h>

FILE *pdlib_image_fd;

char *pdlib_image_types[256];

void *pdlib_image_objptrs[4096];
int pdlib_image_objs;
int pdlib_image_objpos;

void *pdlib_image_strptrs[4096];
int pdlib_image_strings;
int pdlib_image_strpos;

char *pdlib_image_names[256];
void *pdlib_image_namedobjs[256];

extern PDLIB_ObjType *pdlib_objtypes;

int PDLIB_Image_StoreTypes()
{
	PDLIB_ObjType *cur;
	int i;

	i=0;
	cur=pdlib_objtypes;
	while(cur)
	{
		fputc(1, pdlib_image_fd);
		fputc(0, pdlib_image_fd);

		PDLIB_Image_WriteString(cur->name);
		PDLIB_Image_WriteString(cur->form);
		pdlib_image_types[i++]=cur->name;

		cur=cur->next;
	}
	return(0);
}

int PDLIB_Image_GetType(char *ty)
{
	int i;

	for(i=0; i<256; i++)
		if(pdlib_image_types[i])
			if(!strcmp(ty, pdlib_image_types[i]))
				return(i);
	return(-1);
}

int PDLIB_Image_WriteShort(short v)
{
	fputc((v>>8)&0xff, pdlib_image_fd);
	fputc((v&0xff), pdlib_image_fd);

	return(0);
}

int PDLIB_Image_WriteLong(long v)
{
	fputc((v>>24)&0xff, pdlib_image_fd);
	fputc((v>>16)&0xff, pdlib_image_fd);
	fputc((v>>8)&0xff, pdlib_image_fd);
	fputc((v&0xff), pdlib_image_fd);

	return(0);
}

int PDLIB_Image_WriteString(char *str)
{
	int i;

	i=strlen(str);

	fputc((i>>8)&0xff, pdlib_image_fd);
	fputc((i&0xff), pdlib_image_fd);
	fwrite(str, 1, i, pdlib_image_fd);

	return(0);
}

int PDLIB_Image_GetObj(void *p)
{
	int i;

	if(!p)return(-1);

	for(i=0; i<pdlib_image_objs; i++)
		if(pdlib_image_objptrs[i]==p)return(i);
	pdlib_image_objptrs[pdlib_image_objs++]=p;
	return(i);
}

int PDLIB_Image_GetString(char *s)
{
	int i;

	if(!s)return(-1);

	for(i=0; i<pdlib_image_strings; i++)
		if(!strcmp(pdlib_image_strptrs[i], s))return(i);
	pdlib_image_strptrs[pdlib_image_strings++]=s;
	return(i);
}

void *PDLIB_Image_WriteType(char *ty, void *obj, int count)
{
	int i, j;
	void *p;

	p=obj;
	for(i=0; i<count; i++)
	{
		if(ty[0]=='*')
		{
			j=PDLIB_Image_GetObj(*(void **)p);
			PDLIB_Image_WriteLong(j);
			p+=sizeof(void *);
		}else
		{
			if(!strcmp(ty, "char") || !strcmp(ty, "byte"))
			{
				fputc(*(char *)p, pdlib_image_fd);
				p++;
			}
			if(!strcmp(ty, "short"))
			{
				PDLIB_Image_WriteShort(*(short *)p);
				p+=sizeof(short);
			}
			if(!strcmp(ty, "int"))
			{
				PDLIB_Image_WriteLong(*(int *)p);
				p+=sizeof(int);
			}
			if(!strcmp(ty, "long"))
			{
				PDLIB_Image_WriteLong(*(long *)p);
				p+=sizeof(long);
			}
			if(!strcmp(ty, "float"))
			{
				PDLIB_Image_WriteLong(*(int *)p);
				p+=sizeof(float);
			}
			if(!strcmp(ty, "string"))
			{
				j=PDLIB_Image_GetString(*(char **)p);
				PDLIB_Image_WriteLong(j);
				p+=sizeof(char *);
			}
		}
	}
	return(p);
}

void *PDLIB_Image_WriteObj(PDLIB_ObjType *ty, void *obj, int size)
{
	char *s, *t;
	char tbuf[16];
	int c;
	PDLIB_ObjType *ty2;
	void *p, *pe;

	s=ty->form;
	p=obj;
	pe=obj+size;

	while(*s && (p<pe))
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

		if(!tbuf[0])break;

		if(*s=='+')
		{
			while(p && (p<pe))
			{
				p=PDLIB_Image_WriteType(tbuf, p, 1);
			}
			break;
		}
		p=PDLIB_Image_WriteType(tbuf, p, c);
	}
	return(p);
}

int PDLIB_Image_StoreStrings()
{
	while(pdlib_image_strpos<pdlib_image_strings)
	{
		fputc(3, pdlib_image_fd);
		fputc(0, pdlib_image_fd);

		PDLIB_Image_WriteString(
			pdlib_image_strptrs[pdlib_image_strpos++]);

//		if(!strcmp(pdlib_image_strptrs[i], s))return(i);
	}
	return(0);
}

int PDLIB_Image_StoreObjs()
{
	PDLIB_ObjType *ty;
	int i;
	void *p;

	while(pdlib_image_objpos<pdlib_image_objs)
	{
		fputc(2, pdlib_image_fd);
		fputc(0, pdlib_image_fd);

		p=pdlib_image_objptrs[pdlib_image_objpos];
		ty=ObjType_GetType(p);
		i=PDLIB_Image_GetType(ty->name);
		PDLIB_Image_WriteShort(i);
		i=ObjType_GetSize(p);

		PDLIB_Image_WriteLong(i);

		PDLIB_Image_WriteObj(ty, p, i);

		pdlib_image_objpos++;

//		PDLIB_Image_WriteString(
//			pdlib_image_strptrs[pdlib_image_strpos++]);

//		if(!strcmp(pdlib_image_strptrs[i], s))return(i);
	}
	return(0);
}

int PDLIB_Image_NameObj(char *name, void *ptr)
{
	int i;

	for(i=0; i<256; i++)if(pdlib_image_names[i])
		if(!strcmp(pdlib_image_names[i], name))
	{
		pdlib_image_namedobjs[i]=ptr;
		return(i);
	}
	for(i=0; i<256; i++)if(!pdlib_image_names[i])
	{
		pdlib_image_names[i]=strdup(name);
		pdlib_image_namedobjs[i]=ptr;
		return(i);
	}
	return(-1);
}

void *PDLIB_Image_FetchName(char *name)
{
	int i;

	for(i=0; i<256; i++)if(pdlib_image_names[i])
		if(!strcmp(pdlib_image_names[i], name))
			return(pdlib_image_namedobjs[i]);
	return(NULL);
}

int PDLIB_Image_StoreNames()
{
	int i, j;

	for(i=0; i<256; i++)if(pdlib_image_names[i])
	{
		fputc(4, pdlib_image_fd);
		fputc(0, pdlib_image_fd);

		PDLIB_Image_WriteString(pdlib_image_names[i]);
		j=PDLIB_Image_GetObj(pdlib_image_namedobjs[i]);
		PDLIB_Image_WriteLong(j);
	}
	return(0);
}

int PDLIB_StoreImage(char *name)
{
	pdlib_image_fd=fopen(name, "w+b");

	memset(pdlib_image_types, 0, 256);

	pdlib_image_objs=0;
	pdlib_image_objpos=0;

	pdlib_image_strings=0;
	pdlib_image_strpos=0;

	kprint("types\n");
	PDLIB_Image_StoreTypes();
	kprint("names\n");
	PDLIB_Image_StoreNames();
	kprint("objs\n");
	PDLIB_Image_StoreObjs();
	kprint("strings\n");
	PDLIB_Image_StoreStrings();
	kprint("ok\n");

	fclose(pdlib_image_fd);

	return(0);
}
