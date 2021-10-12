#include <general.h>


struct ramfs_field_t {
struct ramfs_field_t *next;

char *name;
long data;
};

struct ramfs_node_t {
struct ramfs_node_t *next, *prev, *up;
struct ramfs_node_t *first;
struct ramfs_field_t *field;
};

extern struct reg_driver_t *drv_root;

int ramfsd_readdir(long *buf, char **fields, long *key, VDIR *dir)
{
	struct ramfs_node_t *cur;
	struct ramfs_field_t *fcur;
	int i;

	if(!dir->data)return(0);
	if(*key==-1)return(0);
	if(!*key)cur=dir->data;
		else cur=(struct reg_driver_t *)*key;

	fcur=cur->field;
	i=0;

	while(fcur)
	{
		switch(fcur->name[0])
		{
		case '$':
			buf[i]=kstrdup((char *)fcur->data);
			break;
		default:
			buf[i]=fcur->data;
			break;
		}
		fields[i]=fcur->name;

		i++;
		fcur=fcur->next;
	}
	fields[i]=NULL;

	*key=(long)cur->next;
	if(!*key)*key=-1;

	return(1);
}

char *ramfs_field_gets(ramfs_node_t *ent, char *name)
{
	ramfs_field *cur;

	cur=ent->field;
	while(cur)
	{
		if(!strcmp(cur->name, name))return((char *)cur->data);
		cur=cur->next;
	}
	return(NULL);
}

VDIR *ramfs_opend_r(struct ramfs_node_t *dir, char *name, VMOUNT *mnt)
{
	struct ramfs_node_t *cur;
	struct ramfs_field_t *fcur;

	VDIR *tmp;
	char *s, *t;

	if(*name=='/')name++;

	if(*name=='(')
	{
	}

	s=name;
	while(*s && (*s!='/'))s++;
	if((int)s-(int)name)
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		cur=dir->first;
		while(cur)
		{
			if(!strcmp(ramfs_field_gets(cur, "$name"), t))
			{
				kfree(t);
				return(ramfs_opend_r(cur, s+1, mnt));
			}
			cur=cur->next;
		}
	}

	tmp=kalloc(sizeof(VDIR));
	tmp->close=&kfree;
	tmp->readdir=&ramfsd_readdir;
	tmp->data=dir->first;

	return(tmp);
}

VDIR *ramfs_opend(char *name, VMOUNT *mnt)
{
}

VFILE *ramfs_openf(char *name, char *fl, VMOUNT *mnt)
{
	char *s;

	s=name;
	while(*s=='/')s++;

#if 0
	t=dev[0];
	while(*s && *s!=':')*t++=*s++;
	*t++=0;

	t=dev[1];
	if(*s==':')
	{
		s++;
		while(*s)*t++=*s++;
	}
	*t++=0;
//	s=Parse_Token(s, dev[0]);
//	s=Parse_Token(s, dev[1]); /* seperator */
//	s=Parse_Token(s, dev[1]);

//	kprint("ramfs_openf: %s %s\n", dev[0], dev[1]);
#endif

	return(Driver_OpenStream(s));
}

VMOUNT *ramfs_mount(char **options)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));
	tmp->unmount=&kfree;
	tmp->openf=&ramfs_openf;
	tmp->opend=&ramfs_opend;
	return(tmp);
}

int ramfs_init()
{
	Vfs_RegisterType("ramfs", &ramfs_mount);
	return(0);
}
