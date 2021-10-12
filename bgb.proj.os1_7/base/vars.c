#include <general.h>

var *var_root;

int Var_Init()
{
	Con_Printf("Vars Init.\n");

	return(0);
}

var *Var_Lookup(char *name)
{
	var *cur;
	for(cur=var_root; cur; cur=cur->next)
		if(!strcmp(name, cur->name))return(cur);
	return(NULL);
}

var *Var_Create(char *name)
{
	var *tmp;
	tmp=kalloc(sizeof(var));
	tmp->name=kalloc(strlen(name)+1);
	strcpy(tmp->name, name);
	tmp->vallen=16;
	tmp->value=kalloc(tmp->vallen);

	tmp->next=var_root;
	var_root=tmp;

	return(tmp);
}

var *Var_SetString(char *name, char *value)
{
	var *tmp;
	tmp=Var_Lookup(name);
	if(tmp)
	{
		if(tmp->vallen<(strlen(value)+1))
		{
			while(tmp->vallen<(strlen(value)+1))tmp->vallen<<=1;
			tmp->value=kalloc(tmp->vallen);
		}
		strcpy(tmp->value, value);
//		tmp->dvalue=atof(value);
	}else
	{
		tmp=kalloc(sizeof(var));
		tmp->name=kalloc(strlen(name)+1);
		strcpy(tmp->name, name);
		tmp->vallen=1;
		while(tmp->vallen<(strlen(value)+1))tmp->vallen<<=1;
		tmp->value=kalloc(tmp->vallen);
		strcpy(tmp->value, value);
//		tmp->dvalue=atof(value);

		tmp->next=var_root;
		var_root=tmp;
	}
	return(tmp);
}

char *Var_GetString(char *name)
{
	var *tmp;
	tmp=Var_Lookup(name);
	if(tmp)return(tmp->value);
	return(NULL);
}

int Var_GetValue(char *name)
{
	var *tmp;
	tmp=Var_Lookup(name);
	if(tmp)return(katoi(tmp->value));
	return(0);
}

#if 0
int Var_ParseConfig(VFILE *fd)
{
	char str[256], *s, name[32], eq[16], val[256], val2[256];
	int line;
	var *v;

	line=1;
	Con_Printf("parseconfig.\n");
	while(!vfeof(fd))
	{
		vfgets(str, 255, fd);
		if(str[0]=='#')continue;
		if(str[0]==';')continue;
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
		line++;
	}
}
#endif
