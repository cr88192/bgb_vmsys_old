#include <general.h>

extern VMOUNT *devfs_mount(char **options);
VMOUNT *ramfs_mount(char **options);
VMOUNT *fatfs_mount(char **options);

int VPath_Init()
{
	var *v;
	VMOUNT *vd;
	char *opts[8];

	kprint("VPath init.\n");
//	vdir_root=NULL;
//	vfstype_root=NULL;

	VMount_Init();
	Vfs_Init();
	VFSNS_Init();

//	vd=vdd_open_dir("/");
//	vd->name=kalloc(12);
//	strcpy(vd->name, "/sysroot/");
//	if(vdir_root)vdir_root->prev=vd;
//	vd->next=vdir_root;
//	vdir_root=vd;
//	Vfs_RegisterType("devfs", &devfs_mount);
//	Vfs_RegisterType("ramfs", &ramfs_mount);
//	Vfs_RegisterType("fatfs", &fatfs_mount);

//	Vfs_Mount("/", "ramfs", NULL);

	Vfs_Mount("/", 			"ramfs", NULL);
	VPath_MkDir("/devices");
	VPath_MkDir("/root");
	VPath_MkDir("/ata0.1");

	Vfs_Mount("/devices",	"devfs", NULL);

	opts[0]="/devices/floppy";
	opts[1]=NULL;
	Vfs_Mount("/root",		"fatfs", opts);

	opts[0]="/devices/ata/0/1";
	opts[1]=NULL;
	Vfs_Mount("/ata0.1",	"fatfs", opts);

//	opts[0]="192.168.1.100:50000";
//	opts[1]=NULL;
//	VPath_Mount("/shroot",	"bshfs", opts);

//	kalloc(6*1024);

//	v=Var_Lookup("VPathMounts");
//	if(v)VPath_LoadMounts(v->value);
}


VFILE *VPath_OpenFile(char *name, char *fl)
{
	VFILE *vfd;
	VMOUNT *vd;
	char name2[256], tname[256], w;

	w=(fl[0]=='w')?1:0;

	if(name[0]!='/')
	{
		name2[0]='/';
		strcpy(&name2[1], name);
	}else strcpy(name2, name);

//	strcpy(name2, name);
//	kprint("VPath: Attempt open \"%s\"\n", name2);

	VMount_ClearMarks();

	for(vd=VMount_ChooseBest(name2, w); vd; vd=VMount_ChooseBest(name2, w))
	{
//		kprint("VPath_OpenFile: check \"%s\"\n", vd->name);
		strcpy(tname, &name2[strlen(vd->name)]);
		vfd=VMount_Open(vd, tname, fl);
		if(vfd)return(vfd);
	}
//	kprint("vpath: couldn't open \"%s\"\n", name);
	return(NULL);
}

VDIR *VPath_OpenDir(char *name)
{
	VMOUNT *vd;
	VDIR *tmp;
	char name2[256], tname[256];

	if(name[0]!='/')
	{
		name2[0]='/';
		strcpy(&name2[1], name);
	}else strcpy(name2, name);

//	strcpy(name2, name);
//	kprint("VPath: Attempt open %s\n", name2);

	VMount_ClearMarks();

	for(vd=VMount_ChooseBest(name2, 0); vd; vd=VMount_ChooseBest(name2, 0))
	{
//		kprint("VPath_OpenFile: check %s\n", vd->name);
		strcpy(tname, &name2[strlen(vd->name)]);
		tmp=VMount_OpenDir(vd, tname);
		if(tmp)return(tmp);
	}
	kprint("vpath: couldn't open %s\n", name);
	return(NULL);
}

int VPath_MkDir(char *name)
{
	static char buf[256], *s;
	VDIR *tmp;

	//check if allready exists
//	tmp=VPath_OpenDir(name);
	tmp=NULL;
	if(tmp)
	{
		VDir_CloseDir(tmp);
		return(0);
	}

	//split parent and child names
	strcpy(buf, name);
	s=buf+strlen(buf);
	while(*s!='/')s--;
	*s++=0;

	//get parent dir
	if(buf[0])
	{
		tmp=VPath_OpenDir(buf);
		if(!tmp) //try creating parent if can't open
		{
//			VPath_MkDir(buf);
//			tmp=VPath_OpenDir(buf);
		}
	}else tmp=VPath_OpenDir("/");

	if(!tmp)return(-1);
	VDir_MkDir(s, tmp);
	return(0);
}

int VPath_Mount(char *dir, char *type, char **opts)
{
	int i;

	i=VPath_MkDir(dir);
	if(i<0)
	{
		kprint("VPath_Mount: Failed create mount point '%s'\n", dir);
		return(-1);
	}
	i=Vfs_Mount(dir, type, opts);
	if(i<0)
	{
		kprint("VPath_Mount: Failed mount to '%s'\n", dir);
		return(-1);
	}
	return(0);
}

int VPath_Unmount(char *name)
{
	VMOUNT *mnt;

	mnt=VMount_LookupMount(name);
	if(!mnt)return(-1);
	VMount_Unmount(mnt);
	return(0);
}
