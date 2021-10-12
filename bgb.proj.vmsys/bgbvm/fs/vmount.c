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

int VMount_Unmount(VMOUNT *mount)
{
	if(mount->unmount)return(mount->unmount(mount));
	return(-1);
}
