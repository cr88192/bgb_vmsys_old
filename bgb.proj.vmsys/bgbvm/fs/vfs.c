#include <general.h>

VFSTYPE *vfstype_root;

int Vfs_Init()
{
	vfstype_root=NULL;

	devfs_init();
	ramfs_init();
	fatfs_init();
	dirfs_init();
}

int Vfs_RegisterType(char *name, VMOUNT *(*mount)(char **options))
{
	VFSTYPE *tmp;
	tmp=kalloc(sizeof(VFSTYPE));

	tmp->name=kstrdup(name);
	tmp->mount=mount;

	if(vfstype_root)vfstype_root->prev=tmp;
	tmp->next=vfstype_root;
	vfstype_root=tmp;
}

VFSTYPE *Vfs_LookupType(char *type)
{
	VFSTYPE *cur;
	cur=vfstype_root;
	while(cur)
	{
		if(!strcmp(cur->name, type))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

int Vfs_Mount(char *path, char *type, char **options)
{
	VFSTYPE *typ;
	VMOUNT *mnt;
	typ=Vfs_LookupType(type);
	if(!typ)
	{
		kprint("Vfs_Mount: unknown fs type \"%s\"\n", type);
		return(-1);
	}
	mnt=typ->mount(options);
	if(!mnt)
	{
		kprint("Vfs_Mount: could not mount\n");
		return(-1);
	}
	VMount_RegisterMount(mnt, path);
	return(0);
}
