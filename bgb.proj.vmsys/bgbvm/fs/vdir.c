#include <general.h>

/*
int VDir_ReadDir(char *buf, VDIR *dir)
{
	long inf[16];
	char **fields[16];

	if(dir->readdir)return(dir->readdir(buf, dir));
	if(dir->r_readdir)
	{
		dir->r_readdir(inf, fields, key, dir)
	}
	return(-1);
}
*/

int VDir_ReadDir(long *buf, char **fields, long *key, VDIR *dir)
{
//	char tmp[256];

	if(dir->readdir)return(dir->readdir(buf, fields, key, dir));

/*	if(dir->readdir)
	{
		dir->readdir(tmp, dir);

		fields[0]="$name";
		fields[1]=NULL;
		buf[0]=kstrdup(tmp);
		return(0);
	} */

	return(0);
}

int VDir_MkDir(char *name, VDIR *dir)
{
	if(dir->mkdir)return(dir->mkdir(name, dir));
	return(-1);
}

#if 0
dirobj *VDir_ReadDirObj(VDIR *dir)
{
	if(dir->readdirobj)return(dir->readdirobj(dir));
	return(NULL);
}
#endif

int VDir_CloseDir(VDIR *dir)
{
	if(dir->close)return(dir->close(dir));
	return(-1);
}

VFILE *VDir_Open(char *name, char *fl, VDIR *dir)
{
	if(dir->openf)return(dir->openf(name, fl, dir));
	return(NULL);
}

VDIR *VDir_OpenDir(char *name, VDIR *dir)
{
	if(dir->opend)return(dir->opend(name, dir));
	return(NULL);
}


long VDir_DupKey(VDIR *dir, long key)
{
	if(dir->dupkey)return(dir->dupkey(key, dir));
	return(key); /* if using keys and fs does not support dup, they are probably int keys */
}

int VDir_DropKey(VDIR *dir, long key)
{
	if(dir->dropkey)return(dir->dropkey(key, dir));
	return(0);
}

int VDir_DeleteKey(VDIR *dir, long key)
{
	if(dir->deletekey)return(dir->deletekey(key, dir));
	return(-1);
}

long VDir_Insert(long *buf, char **fields, VDIR *dir)
{
	if(dir->insert)return(dir->insert(buf, fields, dir));
	return(-1);
}

VFILE *VDir_OpenKey(long key, char *fl, VDIR *dir)
{
	if(dir->openfk)return(dir->openfk(key, fl, dir));
	return(NULL);
}

VDIR *VDir_OpenDirKey(long key, VDIR *dir)
{
	if(dir->opendk)return(dir->opendk(key, dir));
	return(NULL);
}

#if 0
dirobj *VDir_LookupObjAddr(VDIR *dir, VADDR *addr)
{
	if(dir->lookupdirobjaddr)return(dir->lookupdirobjaddr(dir, addr));
	return(NULL);
}

dirobj *VDir_LookupObjName(VDIR *dir, char *name)
{
	if(dir->lookupdirobjname)return(dir->lookupdirobjname(dir, name));
	return(NULL);
}

dirobj *VDir_CreateObjAddr(VDIR *dir, VADDR *addr)
{
	if(dir->createdirobjaddr)return(dir->createdirobjaddr(dir, addr));
	return(NULL);
}

dirobj *VDir_CreateObjName(VDIR *dir, char *name)
{
	if(dir->createdirobjname)return(dir->createdirobjname(dir, name));
	return(NULL);
}
#endif
