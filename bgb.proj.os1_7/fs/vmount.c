#include <general.h>

VMOUNT *vdir_root;

int VMount_Init()
{
	vdir_root=NULL;
}

/* chooses the best path for something
   it is determined by the path with the closest base match or one with a higher priority
   this does however ignore those that don't match
   both a read and write priority are used, this is to offer some control over where files are grabbed
     from or sent to
   marks are used to eliminate possibilities that have been used allready, thus before a search it will
     be neccessary to clear marks
 */
VMOUNT *VMount_ChooseBest(char *path, int w)
{
	VMOUNT *cur, *best;

//	kprint("lookup: \"%s\"\n", path);
	best=NULL;
	cur=vdir_root;

	while(cur)
	{
//		kprint("VMount_ChooseBest: try 1 \"%s\"\n", cur->name);
		if(!cur->mark)
			if(!strncmp(cur->name, path, strlen(cur->name)))
		{
			if(best) /* check if a better match */
			{
				if(strlen(cur->name)>strlen(best->name))
				{
					if(w)
					{
						if(cur->wprio>=best->wprio)best=cur;
					}else if(cur->rprio>=best->rprio)best=cur;
				}else if(w)
				{
					if(cur->wprio>best->wprio)best=cur;
				}else if(cur->rprio>best->rprio)best=cur;
			}else best=cur; /* first match */
		}
		cur=cur->next;
	}
//	if(!best)kprint("VDir_ChooseBest: no match.\n");
	if(best)best->mark=1;
	return(best);
}

int VMount_ClearMarks()
{
	VMOUNT *cur;
	cur=vdir_root;
	while(cur)
	{
		cur->mark=0;
		cur=cur->next;
	}
}

VFILE *VMount_Open(VMOUNT *vd, char *name, char *fl)
{
	if(vd->openf)return(vd->openf(name, fl, vd));
	return(NULL);
}

VDIR *VMount_OpenDir(VMOUNT *vd, char *name)
{
	if(vd->opend)return(vd->opend(name, vd));
	return(NULL);
}

VFILE *VMount_OpenSL(VMOUNT *vd, int idx, char *fl)
{
	if(vd->open_sl)return(vd->open_sl(idx, fl, vd));
	return(NULL);
}

int VMount_CreateSL(VMOUNT *vd, char *type)
{
	if(vd->create_sl)return(vd->create_sl(type, vd));
	return(-1);
}

int VMount_LoadMounts(char *name)
{
	VFILE *fd;
	char lbuf[256], dest[64], src[256], type[16], tmp[16];
	char *s;
	VMOUNT *vd;

	kprint("VPath_LoadMounts: loading %s\n", name);

	fd=VPath_OpenFile(name, "rt");
	if(!fd)
	{
		kprint("VPath_LoadMounts: can't open %s\n", name);
		return(0);
	}
	while(!vfeof(fd))
	{
		vfgets(lbuf, 255, fd);
		s=Parse_TokenS(lbuf, dest);
		if(!dest[0])continue;
		if(!strcmp(dest, "/"))strcpy(dest, "");
		s=Parse_TokenS(s, src);
		if(!src[0])continue;
		s=Parse_Token(s, type);
		if(!type[0])continue;

//		vd=vdd_open_dir(src);
		vd->name=kalloc(strlen(dest)+1);
		strcpy(vd->name, dest);		
		if(vdir_root)vdir_root->prev=vd;
		vd->next=vdir_root;
		vdir_root=vd;

		s=Parse_Token(s, tmp);
//		if(tmp[0])vd->rprio=atoi(tmp);
		s=Parse_Token(s, tmp);
//		if(tmp[0])vd->wprio=atoi(tmp);

		if(tmp[0])vd->rprio=100;
		if(tmp[0])vd->wprio=100;
	}
	vfclose(fd);
	return(1);
}

int VMount_RegisterMount(VMOUNT *vd, char *path)
{
	vd->name=kstrdup(path);

	if(vdir_root)vdir_root->prev=vd;
	vd->next=vdir_root;
	vdir_root=vd;
	return(0);
}

int VMount_PrintMounts()
{
	VMOUNT *cur;
	cur=vdir_root;
	while(cur)
	{
		kprint("Mount: %s\n", cur->name);
		cur=cur->next;
	}
}

VMOUNT *VMount_LookupMount(char *name)
{
	VMOUNT *cur;
	cur=vdir_root;
	while(cur)
	{
		if(!strcmp(name, cur->name))
			return(cur);
		cur=cur->next;
	}
	return(NULL);
}

int VMount_Unmount(VMOUNT *mount)
{
	if(mount->unmount)return(mount->unmount(mount));
	return(-1);
}


#if 0
/* system directories */

VFILE *vdd_open(char *name, char *fl, VMOUNT *dir)
{
	char tname[256], i;
//	FILE *fd;
	VFILE *vfd;

	strcpy(tname, dir->data);
	i=strlen(tname);
//	strcat(tname, "/");
	strcat(tname, name);
//	for(;tname[i];i++)if(tname[i]=='/')tname[i]=CONF_PATHSEP;

//	kprint("dir: attempt open %s\n", tname);

//	fd=fopen(tname, fl);
//	if(!fd)
//	{
//		printf("vpath: can't open %s\n", name);
		return(NULL);
//	}
//	vfd=vf_wrap_file(fd);

//	return(vfd);
}

int vdd_d_readdir(char *buf, VDIR *dir)
{
//	struct dirent *de;

//	de=readdir(dir->data);
//	if(!de)return(-1);
//	strcpy(buf, de->d_name);
	return(0);
}

int vdd_d_close(VDIR *dir)
{
//	closedir(dir->data);
	kfree(dir);
}

VDIR *vdd_opendir(char *name, VMOUNT *dir)
{
	char tname[256], i;
	VFILE *vfd;
//	DIR *pth;
	VDIR *tmp;

	strcpy(tname, dir->data);
	i=strlen(tname);
//	strcat(tname, "/");
	strcat(tname, name);
//	for(;tname[i];i++)if(tname[i]=='/')tname[i]=CONF_PATHSEP;

//	kprint("dir: attempt open %s\n", tname);

//	pth=opendir(tname);
//	if(!pth)
//	{
//		printf("vpath: can't open dir %s\n", name);
		return(NULL);
//	}
	tmp=kalloc(sizeof(VDIR));
//	tmp->data=pth;
//	tmp->readdir=&vdd_d_readdir;
	tmp->close=&vdd_d_close;

	return(tmp);
}

VMOUNT *vdd_open_dir(char *name)
{
	VMOUNT *tmp;
	tmp=kalloc(sizeof(VMOUNT));
	tmp->data=kalloc(strlen(name)+1);
	strcpy(tmp->data, name);
	tmp->openf=&vdd_open;
	tmp->opend=&vdd_opendir;
	return(tmp);
}
#endif
