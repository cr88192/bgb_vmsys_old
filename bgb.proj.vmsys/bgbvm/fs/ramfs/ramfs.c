#include <general.h>
#include <buffer.h>

int ramfsd_readdir(long *buf, char **fields, long *key, VDIR *dir)
{
	dirobj *obj, *obj2;

	obj=dir->data;
	if(!obj->data)return(0);
	obj2=obj->data;
//		else obj2=(dirobj *)*key;

//	strcpy(buf, obj2->name);
	buf[0]=kstrdup(obj2->name);
	fields[0]="$name";
	fields[1]=NULL;

	obj->data=obj2->next;
	*key=(long)obj2->next;

	return(1);
}

dirobj *ramfs_lookupn(dirobj *lst, char *name)
{
	dirobj *cur;
	cur=lst->first;
	while(cur)
	{
		if(!strcmp(cur->name, name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

dirobj *ramfs_trace(dirobj *lst, char *name)
{
	dirobj *obj;
	char tokbuf[4][64], *s;

	if(!lst)return(NULL);

	s=name;
	while(*s=='/')s++;

	s=Parse_Token(name, tokbuf[0]);
	if(!tokbuf[0][0])return(lst); /* hack: if can't get next part of name return this */
//	kprint("ramfs: nothack.\n");

	s=Parse_Token(s, tokbuf[1]);
	obj=ramfs_lookupn(lst, tokbuf[0]);
	while(obj && (tokbuf[1][0]=='/'))
	{
		s=Parse_Token(s, tokbuf[0]);
		if(!tokbuf[0])break; /* extra '/' */
		s=Parse_Token(s, tokbuf[1]);
		obj=ramfs_lookupn(obj, tokbuf[0]);
	}
	return(obj);
}

int ramfs_closed(VDIR *dir)
{
	kfree(dir->data);
	kfree(dir);
	return(0);
}

int ramfs_mkdir(char *name, VDIR *dir)
{
	dirobj *obj, *obj2;

//	kprint("ramfs: mkdir %s\n", name);

	obj2=dir->data;
	obj=kalloc(sizeof(dirobj));
	obj->name=kstrdup(name);
	obj->next=obj2->first->first;
	obj2->first->first=obj;
}

VDIR *ramfs_opend(char *name, VMOUNT *mnt)
{
	VDIR *tmp;
	dirobj *obj, *hdl;

//	kprint("ramfs: lookup \"%s\"\n", name);

	obj=ramfs_trace(mnt->data, name);

	if(!obj)return(NULL);

//	kprint("ok.\n");

	hdl=kalloc(sizeof(dirobj));
	hdl->first=obj;
	hdl->data=obj->first;

	tmp=kalloc(sizeof(VDIR));
	tmp->readdir=&ramfsd_readdir;
	tmp->close=&ramfs_closed;
	tmp->mkdir=&ramfs_mkdir;
	tmp->data=hdl;
	return(tmp);
}

VFILE *ramfs_openf(char *name, char *fl, VMOUNT *mnt)
{
	dirobj *obj;
	obj=ramfs_trace(mnt->data, name);

	if(!obj)return(NULL);
//	if(obj->data)return(vf_wrap_buffer(obj->data));
//	if(*fl=='w')
//	{
//		obj->data=Buffer_New();
//		return(vf_wrap_buffer(obj->data));
//	}
	return(NULL);
}

VMOUNT *ramfs_mount(char **options)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));
	tmp->data=kalloc(sizeof(dirobj));
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
