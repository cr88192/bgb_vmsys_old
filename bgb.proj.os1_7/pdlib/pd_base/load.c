#include <pdlib.h>

PDLIB_ObjType *pdlib_load_types[256];
int pdlib_load_numtypes;

char *pdlib_load_strings[4096];
int pdlib_load_numstrings;

void *pdlib_load_objs[4096];
int pdlib_load_numobjs;

char *pdlib_load_names[256];
int pdlib_load_namedobjs[256];
int pdlib_load_numnames;

extern PDLIB_ObjType *pdlib_objtypes;

int pdlib_le=1;

int PDLIB_SwapShort(int v)
{
	if(pdlib_le)v=((v>>8)&0xff)+((v&0xff)<<8);
	return(v);
}

int PDLIB_SwapLong(int v)
{
	int i;

	i=v;
	if(pdlib_le)
	{
		i=v&0xff;
		i=(i<<8)+((v>>8)&0xff);
		i=(i<<8)+((v>>16)&0xff);
		i=(i<<8)+((v>>24)&0xff);
	}
	return(i);
}

char *PDLIB_ReadString(FILE *fd)
{
	int i;
	char *s;

	i=fgetc(fd);
	i=(i<<8)+fgetc(fd);

	s=malloc(i+1);
	fread(s, 1, i, fd);

	return(s);
}

int PDLIB_ReadShort(FILE *fd)
{
	int i;

	i=fgetc(fd);
	i=(i<<8)+fgetc(fd);

	return(i);
}

int PDLIB_ReadLong(FILE *fd)
{
	int i;

	i=fgetc(fd);
	i=(i<<8)+fgetc(fd);
	i=(i<<8)+fgetc(fd);
	i=(i<<8)+fgetc(fd);

	return(i);
}

void *PDLIB_Load_DecodeType(char *ty, void *obj, int count)
{
	int i, j;
	void *p;

	p=obj;
	for(i=0; i<count; i++)
	{
		if(ty[0]=='*')
		{
			j=PDLIB_SwapLong(*(long *)p);
			*(void **)p=pdlib_load_objs[j];
			p+=sizeof(void *);
		}else
		{
			if(!strcmp(ty, "char") || !strcmp(ty, "byte"))
			{
				p++;
			}
			if(!strcmp(ty, "short"))
			{
				*(short *)p=PDLIB_SwapShort(*(short *)p);
				p+=sizeof(short);
			}
			if(!strcmp(ty, "int"))
			{
				*(int *)p=PDLIB_SwapLong(*(int *)p);
				p+=sizeof(int);
			}
			if(!strcmp(ty, "long"))
			{
				*(long *)p=PDLIB_SwapLong(*(long *)p);
				p+=sizeof(long);
			}
			if(!strcmp(ty, "float"))
			{
				*(long *)p=PDLIB_SwapLong(*(long *)p);
				p+=sizeof(float);
			}
			if(!strcmp(ty, "string"))
			{
				*(char **)p=pdlib_load_strings[*(int *)p];
				p+=sizeof(char *);
			}
		}
	}
	return(p);
}

void *PDLIB_Load_DecodeObj(PDLIB_ObjType *ty, void *obj, int size)
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
				p=PDLIB_Load_DecodeType(tbuf, p, 1);
			}
			break;
		}
		p=PDLIB_Load_DecodeType(tbuf, p, c);
	}
	return(p);
}

int PDLIB_Load_DecodeObjs()
{
	PDLIB_ObjType *ty;
	int i, j;
	void *p;

	for(i=0; i<pdlib_load_numobjs; i++)
	{
		p=pdlib_load_objs[i];
		ty=ObjType_GetType(p);
		j=ObjType_GetSize(p);

		PDLIB_Load_DecodeObj(ty, p, j);
	}
	return(0);
}

int PDLIB_LoadImage(char *name)
{
	FILE *fd;
	int i, j, k;
	char *s1, *s2;
	PDLIB_ObjType *ty;

	pdlib_load_numtypes=0;
	pdlib_load_numstrings=0;
	pdlib_load_numobjs=0;

	fd=fopen(name, "rb");

	while(!feof(fd))
	{
		i=fgetc(fd);
		if(i==-1)break;
		switch(i)
		{
		case 1:
			fgetc(fd);
			s1=PDLIB_ReadString(fd);
			s2=PDLIB_ReadString(fd);
			ty=ObjType_NewType(s1, s2);
			pdlib_load_types[pdlib_load_numtypes++]=ty;
			break;
		case 2:
			fgetc(fd);
			j=PDLIB_ReadShort(fd);
			k=PDLIB_ReadLong(fd);
			s1=ObjType_New(pdlib_load_types[j]->name, k);
			fread(s1, 1, k, fd);
			pdlib_load_objs[pdlib_load_numobjs++]=s1;
			break;
		case 3:
			fgetc(fd);
			s1=PDLIB_ReadString(fd);
			pdlib_load_strings[pdlib_load_numstrings++]=s1;
			break;
		case 4:
			fgetc(fd);
			s1=PDLIB_ReadString(fd);
			j=PDLIB_ReadLong(fd);

			pdlib_load_names[pdlib_load_numnames]=s1;
			pdlib_load_namedobjs[pdlib_load_numnames]=j;
			pdlib_load_numnames++;

//			PDLIB_Image_NameObj(s1, pdlib_load_objs[j]);
			break;
		default:
			kprint("PDLIB_LoadImage: inv type %d\n", i);
			return(-1);
			break;
		}
	}

	fclose(fd);

	PDLIB_Load_DecodeObjs();

	for(i=0; i<pdlib_load_numnames; i++)
	{
		s1=pdlib_load_names[i];
		j=pdlib_load_namedobjs[i];
		PDLIB_Image_NameObj(s1, pdlib_load_objs[j]);
	}

	return(0);
}
