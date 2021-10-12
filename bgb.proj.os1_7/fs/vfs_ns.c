#include <general.h>

VFSNAMESPACE *vfsns_root;

VFSNAMESPACE *VFSNS_New(char *name)
{
	VFSNAMESPACE *tmp;

	tmp=kalloc(sizeof(VFSNAMESPACE));
	tmp->name=kstrdup(name);

	tmp->next=vfsns_root;
	if(vfsns_root)
		vfsns_root->prev=tmp;
	vfsns_root=tmp;

	return(tmp);
}

char *VFSNS_GetScheme(char *name)
{
	char *s;
	int i;

	s=name;
	while(*s &&
		(((*s>='a') && (*s<='z')) ||
		((*s>='A') && (*s<='Z')) ||
		((*s>='0') && (*s<='9')) ||
		(*s=='+') || (*s=='-') || (*s=='.')))
			s++;
	if(*s!=':')return(NULL);

	i=s-name;
	if(i>15)return(NULL);

	s=kralloc(i+1);
	memset(s, 0, i+1);
	strncpy(s, name, i);
	return(s);
}

VFSNAMESPACE *VFSNS_LookupScheme(char *s)
{
	VFSNAMESPACE *cur;

	cur=vfsns_root;
	while(cur)
	{
		if(!stricmp(s, cur->name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

VFILE *VFSNS_OpenFile(char *name, char *fl)
{
	char *s;
	VFSNAMESPACE *ns;

	s=VFSNS_GetScheme(name);
	if(!s)return(NULL);

	ns=VFSNS_LookupScheme(s);
	if(!ns)return(NULL);

	s=name+(strlen(s)+1);
	return(ns->openf(s, fl, ns));
}

VDIR *VFSNS_OpenDir(char *name, char *fl)
{
	char *s;
	VFSNAMESPACE *ns;

	s=VFSNS_GetScheme(name);
	if(!s)return(NULL);

	ns=VFSNS_LookupScheme(s);
	if(!ns)return(NULL);

	s=name+(strlen(s)+1);
	return(ns->opend(s, ns));
}

VFILE *vfsns_file_openf(char *name, char *fl, VFSNAMESPACE *ns)
{
	return(VPath_OpenFile(name, fl));
}

VDIR *vfsns_file_opend(char *name, VFSNAMESPACE *ns)
{
	return(VPath_OpenDir(name));
}

int VFSNS_Init()
{
	VFSNAMESPACE *ns;

	kprint("VFSNS_Init\n");
	vfsns_root=NULL;

	ns=VFSNS_New("file");
	ns->openf=&vfsns_file_openf;
	ns->opend=&vfsns_file_opend;

	return(0);
}
