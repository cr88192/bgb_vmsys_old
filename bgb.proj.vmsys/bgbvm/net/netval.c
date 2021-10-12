/*
objective:
create code for managing net-related dynamic types.
make use of pdlib type system as base.
 */

#include <general.h>
#include <net/pdnet.h>

void *NetVal_WrapInt(int i)
{
	int *p;

	p=ObjType_New("int_t", 0);
	*p=i;

	return((void *)p);
}

void *NetVal_WrapStr(char *s)
{
	char *t;

	t=ObjType_New("string_t", strlen(s)+1);
	strcpy(t, s);

	return(t);
}

void *NetVal_WrapFloat(double f)
{
	double *p;

	p=ObjType_New("float_t", 0);
	*p=f;

	return((void *)p);
}

void *NetVal_WrapArray(void *a)
{
	void **ip, **op;
	int i;

	ip=(void **)a;
	for(i=0; ip[i]; i++);

	op=ObjType_New("array_t", (i+1)*sizeof(void *));
	for(i=0; ip[i]; i++)op[i]=ip[i];
	op[i++]=NULL;

	return((void *)op);
}

int NetVal_Init()
{
	ObjType_NewType("int_t", "int;");
	ObjType_NewType("float_t", "double;");
	ObjType_NewType("bool_t", "int;");
	ObjType_NewType("string_t", "char+");
	ObjType_NewType("date_t",
		"2byte:Y;byte:M;byte:D;"
		"byte:h;byte:m;byte:s;");
	ObjType_NewType("data_t", "byte+");

	ObjType_NewType("array_t", "*struct+");
	ObjType_NewType("d_array_t", "*array_t;");
	ObjType_NewType("d_struct_t", "*array_t:names;*array_t:values;");

	ObjType_NewType("netref_t", "int;int;int;");

	return(1);
}