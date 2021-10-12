#include <pdlib.h>
#include <pdnet.h>

PDLIB_Var *var_root;

int Var_Init()
{
	kprint("Vars Init.\n");

	return(0);
}

PDLIB_Var *Var_Lookup(char *name)
{
	PDLIB_Var *cur;
	for(cur=var_root; cur; cur=cur->next)
		if(!strcmp(name, cur->name))return(cur);
	return(NULL);
}

PDLIB_Var *Var_Create(char *name)
{
	PDLIB_Var *tmp;
	tmp=malloc(sizeof(PDLIB_Var));
	tmp->name=malloc(strlen(name)+1);
	strcpy(tmp->name, name);
	tmp->vallen=16;
	tmp->value=malloc(tmp->vallen);

	tmp->next=var_root;
	var_root=tmp;

	return(tmp);
}

PDLIB_Var *Var_SetString(char *name, char *value)
{
	PDLIB_Var *tmp;
	tmp=Var_Lookup(name);
	if(tmp)
	{
		if(tmp->vallen<(strlen(value)+1))
		{
			while(tmp->vallen<(strlen(value)+1))tmp->vallen<<=1;
			tmp->value=malloc(tmp->vallen);
		}
		strcpy(tmp->value, value);
		tmp->dvalue=atof(value);
	}else
	{
		tmp=malloc(sizeof(PDLIB_Var));
		tmp->name=malloc(strlen(name)+1);
		strcpy(tmp->name, name);
		tmp->vallen=1;
		while(tmp->vallen<(strlen(value)+1))tmp->vallen<<=1;
		tmp->value=malloc(tmp->vallen);
		strcpy(tmp->value, value);
		tmp->dvalue=atof(value);

		tmp->next=var_root;
		var_root=tmp;
	}
	return(tmp);
}

char *Var_GetString(char *name)
{
	PDLIB_Var *v;
	v=Var_Lookup(name);
	if(!v)return(NULL);

	return(v->value);
}

float Var_GetValue(char *name)
{
	PDLIB_Var *v;
	v=Var_Lookup(name);
	if(!v)return(0);

//	kprint("var %s %f\n", name, v->dvalue);

	return(v->dvalue);
}

int Var_ParseConfig(VFILE *fd)
{
	char str[256], *s, name[32], eq[16], val[256], val2[256];
	int line;
	PDLIB_Var *v;

	line=1;
	kprint("parseconfig.\n");
	while(!vfeof(fd))
	{
		memset(str, 0, 255);
		vfgets(str, 255, fd);
		if(str[0]=='#')continue;
		if(str[0]==';')continue;
		if(str[0]=='\n')continue;
		if(!str[0])continue;

		sscanf(str, "%s %s\n", name, val);
		Var_SetString(name, val);

#if 0
		s=Parse_Token(str, name);
		if(!s)continue;
		s=Parse_Token(s, eq);
		if(eq[0]=='=')
		{
			s=Parse_Token(s, val);
			Var_SetString(name, val);
		}else if((eq[0]=='<' || eq[0]=='>') && eq[1]=='=')
		{
			v=Var_Lookup(name);
			s=Parse_Token(s, val);
			if(eq[0]=='<')
			{
				strcpy(val2, val);
				strcat(val2, v->value);
			}else
			{
				strcpy(val2, v->value);
				strcat(val2, val);
			}
			Var_SetString(name, val2);
		}else Con_Printf("Var_ParseConfig: %d: parse error.\n", line);
#endif
		line++;
	}
}

int Var_LoadConfig(char *name)
{
	VFILE *fd;

	fd=vffopen(name, "rt");
	if(!fd)
	{
		kprint("Var_LoadConfig: no file '%s'\n", name);
		return(-1);
	}

	return(Var_ParseConfig(fd));
}
