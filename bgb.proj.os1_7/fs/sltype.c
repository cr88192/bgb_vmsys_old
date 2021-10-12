#include <general.h>

VFS_SLTYPE *sltype_root;

int SLType_Init()
{
	sltype_root=NULL;
}

VFS_SLTYPE *SLType_Lookup(char *name)
{
	VFS_SLTYPE *cur;

	cur=sltype_root;
	while(cur)
	{
		if(!strcmp(cur->name, name))
			return(cur);
		cur=cur->next;
	}
	return(NULL);
}

VFS_SLTYPE *SLType_Create(char *name)
{
	VFS_SLTYPE *tmp;

	tmp=SLType_Lookup(name);
	if(tmp)return(tmp);

	tmp=kalloc(sizeof(VFS_SLTYPE));
	tmp->name=kstrdup(name);
	tmp->next=sltype_root;
	sltype_root=tmp;

	return(tmp);
}
