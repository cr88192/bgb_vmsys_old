#include <general.h>

int VDir_ReadDir(long *buf, char **fields, long *key, VDIR *dir)
{
	if(dir->readdir)return(dir->readdir(buf, fields, key, dir));

	return(0);
}

int VDir_ReadDir2(char **names, void **values, long *key, VDIR *dir)
{
	if(dir->readdir2)return(dir->readdir2(names, values, key, dir));

	return(0);
}

int VDir_MkDir(char *name, VDIR *dir)
{
	if(dir->mkdir)return(dir->mkdir(name, dir));
	return(-1);
}

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
