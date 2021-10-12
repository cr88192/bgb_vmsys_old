/*
interpreter glue.
 */

#include <general.h>
#include <net/sxrpc.h>

elem sxrpc_export_names;
elem sxrpc_export_values;

elem sxrpc_return_contids;
elem sxrpc_return_values;

elem SXRPC_FindHandler(char *name)
{
	elem cur1, cur2;
	char *s;

	cur1=sxrpc_export_names;
	cur2=sxrpc_export_values;

	while(ELEM_CONSP(cur1))
	{
		if(ELEM_STRINGP(CAR(cur1)))
			s=ELEM_TOSTRING(CAR(cur1));
		if(ELEM_SYMBOLP(CAR(cur1)))
			s=ELEM_TOSYMBOL(CAR(cur1));

		if(!stricmp(s, name))return(CAR(cur2));

		cur1=CDR(cur1);
		cur2=CDR(cur2);
	}
	return(MISC_UNDEFINED);
}

elem SXRPC_URL2Link(elem url)
{
	char *str;
	char *s, *t;
	char base[16];
	elem t2;

	str=ELEM_TOSTRING(url);

	s=str;
	t=base;
	while(*s && (*s!=':'))*t++=*s++;
	*t++=0;
	if(*s==':')s++;

	t2=MISC_NULL;
	if(!stricmp(base, "sxrpc"))
		t2=SXRPC_DecodeLink(s);

	return(t2);
}

elem SXRPC_ExportHandler(elem name, elem value)
{
	sxrpc_export_names=CONS(name, sxrpc_export_names);
	sxrpc_export_values=CONS(value, sxrpc_export_values);

	return(MISC_NULL);
}

elem SXRPC_PassLinkElem(elem link, elem args)
{
	SXRPC_PassLink(TypeX_Data(link), args);
}

int SXRPC_LBS_Init()
{
	sxrpc_export_names=MISC_EOL;
	sxrpc_export_values=MISC_EOL;

	sxrpc_return_contids=MISC_EOL;
	sxrpc_return_values=MISC_EOL;

	SAGC_AddRoot(&sxrpc_export_names);
	SAGC_AddRoot(&sxrpc_export_values);

	SAGC_AddRoot(&sxrpc_return_contids);
	SAGC_AddRoot(&sxrpc_return_values);

	Interp_DefinePrimative("url->link",	&SXRPC_URL2Link, 1);
	Interp_DefinePrimative("sxrpc-handler",	&SXRPC_ExportHandler, 2);
	Interp_DefinePrimative("pass-link",	&SXRPC_PassLinkElem, -2);
}
