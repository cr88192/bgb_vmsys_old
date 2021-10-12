#include <general.h>

extern struct reg_driver_t *drv_root;

int devfsd_readdir(long *buf, char **fields, long *key, VDIR *dir)
{
	struct reg_driver_t *cur;

	if(!dir->data)return(0);
	if(*key==-1)return(0);
	if(!*key)cur=dir->data;
		else cur=(struct reg_driver_t *)*key;

//	strcpy(buf, cur->name);
	buf[0]=kstrdup(cur->name);
	fields[0]="$name";
	fields[1]=NULL;

//	dir->data=cur->next;
	*key=(long)cur->next;
	if(!*key)*key=-1;
//	if(!cur)return(0);

	return(1);
}

VDIR *devfs_opend_r(struct reg_driver_t *dir, char *name, VMOUNT *mnt)
{
	struct reg_driver_t *cur;
	VDIR *tmp;
	char *s, *t;

	if(*name=='/')name++;
	s=name;
	if(*s=='/')s++;
	while(*s && (*s!='/'))s++;
	if((int)s-(int)name)
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		cur=dir->first;
		while(cur)
		{
			if(!strcmp(cur->name, t))
			{
				kfree(t);
				return(devfs_opend_r(cur, s+1, mnt));
			}
			cur=cur->next;
		}
	}

	tmp=kalloc(sizeof(VDIR));
	tmp->close=&kfree;
	tmp->readdir=&devfsd_readdir;
	tmp->data=dir->first;

	return(tmp);
}

VDIR *devfs_opend(char *name, VMOUNT *mnt)
{
	struct reg_driver_t *cur;
	VDIR *tmp;
	char *s, *t;

	if(*name=='/')name++;
	s=name;
	if(*s=='/')s++;
	while(*s && (*s!='/'))s++;
	if((int)s-(int)name)
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		kprint("recurse: %s\n", t);

		cur=drv_root->first;
		while(cur)
		{
			if(!strcmp(cur->name, t))
			{
				kfree(t);
				return(devfs_opend_r(cur, s+1, mnt));
			}
			cur=cur->next;
		}
		kprint("not found\n");
	}

	kprint("flat\n");

	tmp=kalloc(sizeof(VDIR));
	tmp->close=&kfree;
	tmp->readdir=&devfsd_readdir;
	tmp->data=drv_root->first;

	return(tmp);
}

VFILE *devfs_openf(char *name, char *fl, VMOUNT *mnt)
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

//	kprint("devfs_openf: %s %s\n", dev[0], dev[1]);
#endif

	return(Driver_OpenStream(s));
}

VMOUNT *devfs_mount(char **options)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));
	tmp->unmount=&kfree;
	tmp->openf=&devfs_openf;
	tmp->opend=&devfs_opend;
	return(tmp);
}

int devfs_init()
{
	Vfs_RegisterType("devfs", &devfs_mount);
	return(0);
}
