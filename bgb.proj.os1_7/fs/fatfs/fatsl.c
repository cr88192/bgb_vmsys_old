#include <general.h>
#include <fs/vfat.h>

int vfat_gen83sl(int idx, int type, char *base, char *ext)
{
	char *s, *t;
	int i;
	static const char *b32tab="0123456789ABCDEFGHIJKLMNOPQRSTUV";

	t=base;
	*s++='#';
	*s++=b32tab[(idx>>30)&0x1f];
	*s++=b32tab[(idx>>25)&0x1f];
	*s++=b32tab[(idx>>20)&0x1f];
	*s++=b32tab[(idx>>15)&0x1f];
	*s++=b32tab[(idx>>10)&0x1f];
	*s++=b32tab[(idx>>5)&0x1f];
	*s++=b32tab[(idx>>0)&0x1f];
//	*s++=b32tab[fork&0x1f];
//	*s++=b32tab[forks&0x1f];

	t=ext;
	*s++=b32tab[(type>>10)&0x1f];
	*s++=b32tab[(type>>5)&0x1f];
	*s++=b32tab[(type>>0)&0x1f];

	return(0);
}

int vfat_dec83sl(int *idx, int *type, char *base, char *ext)
{
	int i, j, k;
	char *s;

	if(*base!='#')return(-1);

	s=base;
	s++;

	j=0;
	for(i=0; i<7; i++)
	{
		k=-1;
		if((*s>='0') && (*s<='9'))k=*s-'0';
		if((*s>='A') && (*s<='V'))k=*s-'A'+10;
		if(k<0)return(-1);
		j=(j<<5)+k;
		s++;
	}
	*idx=j;

//	if((*s>='0') && (*s<='9'))k=*s-'0';
//	if((*s>='A') && (*s<='V'))k=*s-'A'+10;
//	s++;
//	*fork=k;

//	if((*s>='0') && (*s<='9'))k=*s-'0';
//	if((*s>='A') && (*s<='V'))k=*s-'A'+10;
//	s++;
//	*forks=k;

	s=ext;

	j=0;
	for(i=0; i<3; i++)
	{
		k=-1;
		if((*s>='0') && (*s<='9'))k=*s-'0';
		if((*s>='A') && (*s<='V'))k=*s-'A'+10;
		if(k<0)return(-1);
		j=(j<<5)+k;
		s++;
	}
//	*class=j;
	*type=j;

//	if((*s>='0') && (*s<='9'))k=*s-'0';
//	if((*s>='A') && (*s<='V'))k=*s-'A'+10;
//	s++;
//	*type=k;

	return(0);
}

vfat_fs_dirent *fatfs_lookup_sl(int idx, vfat_dirbuf *db)
{
	int i, j;
	vfat_fs_dirent *de;

	int num, type;

	if(idx>=(db->len<<(db->sbi->sector_bits-5)))
		return(NULL);

	de=&db->buf[idx];

	i=vfat_dec83sl(&num, &type, de->de.name, de->de.ext);
	if(i<0)return(NULL);
	if(num!=idx)return(NULL);

	return(de);
}

int fatfs_create_sl(int type, vfat_dirbuf *db)
{
	int i, j;
	vfat_fs_dirent *de;

	j=0;
	for(i=0; i<db->len<<(db->sbi->sector_bits-5); i++)
		if(!db->buf[i].de.name[0] || (db->buf[i].de.name[0]==0xE5))
	{
		de=&db->buf[i];
		memset(de, 0, 32);
		vfat_gen83sl(i, type, de->de.name, de->de.ext);

		vfat_update_sbi(db->sbi);
		return(i);
	}

	kprint("fatfs-sl: failed create\n");
	return(-1);
}

VFILE *fatfs_sl_openf_r(
	char *name, int idx, char *fl,
	vfat_dirbuf *dir, vfat_sb_info *sbi)
{
	vfat_fs_dirent *de;
	vfat_dirbuf *db;
	char *s, *t;
	vfat_filebuf *fb;
	VFILE *fd;
	int i;

	while(*name=='/')name++;
	if(*name)
	{
		s=name;
		while(*s && (*s!='/'))s++;

		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		de=fatfs_lookup(t, dir);
		if(!de)
		{
			kprint("fatfs: can't find dir \"%s\"\n", t);
			return(NULL);
		}
		if(!(de->de.attr&VFAT_FLAG_D))
		{
			kprint("fatfs-sl: attempt to use file as dir.\n");
			return(NULL);
		}
		db=fatfs_loaddir(read_word(de->de.base), sbi);

		return(fatfs_sl_openf_r(s+1, idx, fl, db, sbi));
	}

	de=fatfs_lookup_sl(idx, dir);
	if(!de)
	{
		kprint("fatfs-sl: invalid obj at idx %d\n", idx);
		return(NULL);
	}
	if(de->de.attr&VFAT_FLAG_D)
	{
		kprint("fatfs-sl: attempt to use dir as file.\n");
		return(NULL);
	}

	fb=fatfs_openfd(sbi, dir, de);

	fd=fatfs_wrapfb(fb);

	return(fd);
}

VFILE *fatfs_sl_opensl(int idx, char *fl, VMOUNT *mnt)
{
	vfat_sb_info *sbi;
	vfat_fs_dirent *de;
	vfat_filebuf *fb;
	VFILE *fd;
	char *s;

	sbi=mnt->data;

	if(!sbi->root)sbi->root=fatfs_readroot(sbi);

	return(fatfs_sl_openf_r("slvol", idx, fl, sbi->root, sbi));
}

int fatfs_sl_createsl(char *type, VMOUNT *mnt)
{
	vfat_sb_info *sbi;
	int i, j;

	sbi=mnt->data;
	for(i=1; i<sbi->slinfo->typecnt; i++)
		if(!strcmp(type, sbi->slinfo->types[i].name))
	{
		j=fatfs_create_sl(i, sbi->slinfo->dir);
		return(j);
	}
	for(i=1; i<sbi->slinfo->typecnt; i++)
		if(!sbi->slinfo->types[i].name[0])
	{
		memset(&sbi->slinfo->types[i], 0, 64);
		strcpy(sbi->slinfo->types[i].name, type);
		write_dword(sbi->slinfo->types[i].usecnt, -1);

		j=fatfs_create_sl(i, sbi->slinfo->dir);
		return(j);
	}

//	if(i>=16384)return(-1);
	if(i>=sbi->slinfo->typemax)return(-1);
	sbi->slinfo->typecnt++;

	memset(&sbi->slinfo->types[i], 0, 64);
	strcpy(sbi->slinfo->types[i].name, type);
	write_dword(sbi->slinfo->types[i].usecnt, -1);

	j=fatfs_create_sl(i, sbi->slinfo->dir);
	return(j);
}

VFILE *fatfs_sl_openf(char *name, char *fl, VMOUNT *mnt)
{
	while(*name=='/')name++;
	if((name[0]=='_') && (name[1]=='/'))
	{
		name+=2;
		while(*name=='/')name++;
		return(fatfs_openf(name, fl, mnt));
	}
	return(NULL);
}

VDIR *fatfs_sl_opend(char *name, VMOUNT *mnt)
{
	while(*name=='/')name++;
	if((name[0]=='_') && (name[1]=='/'))
	{
		name+=2;
		while(*name=='/')name++;
		return(fatfs_opend(name, mnt));
	}
	return(NULL);
}

VMOUNT *fatfs_sl_mount(char **options)
{
	VMOUNT *tmp;
	vfat_sb_info *sbi;
	fatsl_info *sli;
	VFILE *fd;

	char lb[256];
	char *s;
	int i, j, k;
	fatsl_typehead tyhd;

	tmp=fatfs_mount(options);
	if(!tmp)return(tmp);
	sbi=tmp->data;

	sli=kalloc(sizeof(fatsl_info));
	sbi->slinfo=sli;

	fd=tmp->openf("@slinfo.txt", "rt", tmp);
	if(!fd)
	{
		tmp->unmount(tmp);
		return(NULL);
	}

	while(!vfeof(fd))
	{
		memset(lb, 0, 256);
		vfgets(lb, 255, fd);
		s=lb;
		if(!strncmp(lb, "E ", 2))
		{
			s+=2;
			j=0;
			while(*s>' ')
			{
				k=-1;
				if((*s>='0') && (*s<='9'))k=*s-'0';
				if((*s>='A') && (*s<='V'))k=*s-'A'+10;
				if(k<0)break;
				j=(j<<5)+k;
				s++;
			}
			sli->entry_idx=j;
			while(*s<=' ')s++;
		}
		if(!strncmp(lb, "P ", 2))
		{
			s+=2;
			j=0;
			while(*s>' ')
			{
				k=-1;
				if((*s>='0') && (*s<='9'))k=*s-'0';
				if((*s>='A') && (*s<='V'))k=*s-'A'+10;
				if(k<0)break;
				j=(j<<5)+k;
				s++;
			}
			sli->endpack_idx=j;
			while(*s<=' ')s++;
		}
		if(!strncmp(lb, "O ", 2))
		{
			s+=2;
			j=0;
			while(*s>' ')
			{
				k=-1;
				if((*s>='0') && (*s<='9'))k=*s-'0';
				if((*s>='A') && (*s<='V'))k=*s-'A'+10;
				if(k<0)break;
				j=(j<<5)+k;
				s++;
			}
			sli->types_idx=j;
			while(*s<=' ')s++;
		}
	}
	vfclose(fd);

	fd=fatfs_sl_opensl(sli->types_idx, "rb", tmp);
	vfread(&tyhd, 1, 64, fd);

	i=read_dword(tyhd.cnt);
	sli->typecnt=i;
	if(i<1024)i=1024;
		else i+512;
	sli->typemax=i;
	sli->types=kalloc(i*64);

	vfread(sli->types, 64, sli->typecnt, fd);
	vfclose(fd);

	tmp->open_sl=&fatfs_sl_opensl;
	tmp->create_sl=&fatfs_sl_createsl;

	tmp->openf=&fatfs_sl_openf;
	tmp->opend=&fatfs_sl_opend;

	return(tmp);
}

int fatfs_sl_init()
{
	Vfs_RegisterType("fatsl", &fatfs_sl_mount);
	return(0);
}
