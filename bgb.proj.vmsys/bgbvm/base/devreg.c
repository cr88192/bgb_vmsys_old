#include <general.h>

struct reg_driver_t *drv_root=NULL;
elem drv_env;

int Driver_Init()
{
	int i;

	kprint("Drivers Initialized...\n");
	drv_root=kalloc(sizeof(struct reg_driver_t));

	return(0);
}

int Driver_RegisterStreamR(struct reg_driver_t *dir, char *name, VFILE *(open_proc)(char *name, void *data), void *data)
{
	struct reg_driver_t *cur, *tmp;
	char *s, *t;

	s=name;
	while(*s && (*s!='/'))s++;
	if(*s=='/')
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		cur=dir->first;
		if(!cur)
		{
			cur=kalloc(sizeof(struct reg_driver_t));
			dir->first=cur;
			cur->name=t;
			return(Driver_RegisterStreamR(cur, s+1, open_proc, data));
		}

		while(1)
		{
			if(!strcmp(cur->name, t))
			{
				kfree(t);
				return(Driver_RegisterStreamR(cur, s+1, open_proc, data));
			}
			if(!cur->next)break;
			cur=cur->next;
		}
		cur->next=kalloc(sizeof(struct reg_driver_t));
		cur->next->up=dir;
		cur->next->prev=cur;
		cur=cur->next;
		cur->name=t;
		return(Driver_RegisterStreamR(cur, s+1, open_proc, data));
	}

	cur=dir->first;
	while(cur)
	{
		if(!strcmp(cur->name, name))
		{
			if(cur->open_stream)
				kprint("devreg: registered \"%s\" multiple times.\n", name);
			cur->data=data;
			cur->open_stream=open_proc;
			return(0);
		}
		cur=cur->next;
	}

	tmp=kalloc(sizeof(struct reg_driver_t));
	tmp->name=kstrdup(name);
	tmp->data=data;
	tmp->open_stream=open_proc;

	if(dir->first)
	{
		cur=dir->first;
		while(cur->next)cur=cur->next;
		cur->next=tmp;
		tmp->prev=cur;
	}else dir->first=tmp;
	return(0);
}

int Driver_RegisterStream(char *name, VFILE *(open_proc)(char *name, void *data), void *data)
{
	return(Driver_RegisterStreamR(drv_root, name, open_proc, data));
}

struct reg_driver_t *Driver_FindR(struct reg_driver_t *dir, char *name)
{
	struct reg_driver_t *cur;
	char *s, *t;

	s=name;
	while(*s && (*s!='/') && (*s!=':'))s++;
	if(*s=='/')
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		cur=dir->first;
		while(cur)
		{
			if(!strcmp(cur->name, t))
			{
				kfree(t);
				return(Driver_FindR(cur, s+1));
			}
			cur=cur->next;
		}
	}

	if(*s==':')
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		cur=dir->first;
		while(cur)
		{
			if(!strcmp(cur->name,t))
			{
				kfree(t);
				return(cur);
			}
			cur=cur->next;
		}
	}

	cur=dir->first;
	while(cur)
	{
		if(!strcmp(cur->name,name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

struct reg_driver_t *Driver_Find(char *name)
{
	return(Driver_FindR(drv_root, name));
}

int Driver_Print()
{
	struct reg_driver_t *cur;
	cur=drv_root;
	while(cur)
	{
		kprint("%s\n", cur->name);
		cur=cur->next;
	}
	return(0);
}

VFILE *Driver_OpenStream(char *name)
{
	struct reg_driver_t *drv;
	
//	kprint("check device %s\n", name);
	drv=Driver_Find(name);
	if(!drv)
	{
//		kprint("no device %s\n", name);
		return(NULL);
	}
	return(drv->open_stream(name, drv->data));
}

#if 0
elem DriverScm_DeviceList()
{
	struct reg_driver_t *cur;
	elem lst;

	lst=MISC_EOL;
	cur=drv_root;
	while(cur)
	{
		lst=CONS(SYM(cur->name), lst);
		cur=cur->next;
	}
	return(lst);
}

elem DriverScm_OpenDevice(elem name)
{
	VFILE *vfd;
	vfd=Driver_OpenStream(ELEM_TOSYMBOL(name), NULL);
	if(!vfd)return(MISC_NULL);
	return(TyPort_WrapVFILE(vfd));
}

elem DriverScm_CreateDriverEnv()
{
	struct reg_driver_t *cur;
	elem fcn;

	drv_env=Namespace_CreateEmptyEnv();

	cur=drv_root;
	while(cur)
	{
		fcn=MISC_NULL;
		Namespace_CreateEnvBinding(drv_env, SYM(cur->name), fcn);
		cur=cur->next;
	}
	return(MISC_UNDEFINED);
}
#endif
