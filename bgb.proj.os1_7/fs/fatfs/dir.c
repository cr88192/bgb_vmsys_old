#include <general.h>
#include <buffer.h>
#include <fs/vfat.h>

/* convert base and ext into name */
static void vfat_dename(char *out, char *base, char *ext)
{
	int i;
	i=8;
	while((*base!=' ')&&(i>0))
	{
		*out=*base;
		if((*out>='A')&&(*out<='Z'))*out=*out-'A'+'a';
		out++;
		base++;
		i--;
	}
	if(ext[0]!=' ')
	{
		*out='.';
		out++;
		i=3;
		while((*ext!=' ')&&(i>0))
		{
			*out=*ext;
			if((*out>='A')&&(*out<='Z'))*out=*out-'A'+'a';
			out++;
			ext++;
			i--;
		}
	}
	*out=0;
	out++;
}

/* convert name to base and ext */
static void vfat_cname(char *name, char *base, char *ext)
{
	int i;
	i=8;
	while((*name!='.')&&(i>0)&&*name)
	{
		*base=*name;
		if((*base>='a')&&(*base<='z'))*base=*base-'a'+'A';
		base++;
		name++;
		i--;
	}
	while(i>0)
	{
		*base=' ';
		base++;
		i--;
	}
	if(*name=='.')
	{
		name++;
		i=3;
		while(*name&&(i>0))
		{
			*ext=*name;
			if((*ext>='a')&&(*ext<='z'))*ext=*ext-'a'+'A';
			ext++;
			name++;
			i--;
		}
		while(i>0)
		{
			*ext=' ';
			ext++;
			i--;
		}
	}
	else
	{
		ext[0]=' ';
		ext[1]=' ';
		ext[2]=' ';
	}
}

int vfat_is83(char *name)
{
	int i;

	i=8;
	while((*name!='.') && (i>0) && *name)
	{
		name++;
		i--;
	}
	if(*name && (*name!='.'))return(0);

	if(*name == '.')name++;

	i=3;
	while((*name!='.') && (i>0) && *name)
	{
		name++;
		i--;
	}
	if(*name)return(0);

	return(1);
}

int vfat_gen83(char *name, int idx, char *base, char *ext)
{
	char *s, *t;
	int i;
	static const char *hextab="0123456789ABCDEF";

	s=name;
	while(*s && *s!='.')s++;
	while(*s=='.')
	{
		t=ext;
		i=3;
		while((*s!='.') && (i>0) && *s)
		{
			*t++=*s++;
			i--;
		}
		while((*s!='.') && *s)s++;
	}

	t=base;
	*s++='~';
	*s++=hextab[(idx>>16)&0xf];
	*s++=hextab[(idx>>12)&0xf];
	*s++=hextab[(idx>>8)&0xf];
	*s++=hextab[(idx>>4)&0xf];
	*s++=hextab[(idx>>0)&0xf];
	*s++=' ';
	*s++=' ';

	return(0);
}


vfat_fs_dirent *fatfs_lookup(char *name, vfat_dirbuf *db)
{
	int i, j;
	char nbase[12], tmp[256];
	u2 lfnbuf[256];

	memset(lfnbuf, 255, 512);

	vfat_cname(name, nbase, &nbase[8]);
	for(i=0; i<db->len<<(db->sbi->sector_bits-5); i++)
	{
		if(db->buf[i].de.name[0] && !(db->buf[i].de.attr&0xE)) /* ignore hidden, system, and volume ents*/
		{
			if(lfnbuf[0]!=0xFFFF)
			{
				memset(tmp, 0, 256);
				for(j=0; (j<256) && (lfnbuf[j]!=0xffff); j++)tmp[j]=lfnbuf[j];
//				kprint("fat lookup: read lfn \"%s\"\n", tmp);
			}else
				vfat_dename(tmp, db->buf[i].de.name, db->buf[i].de.ext);

			if(!strcmp(name, tmp))return(&db->buf[i]);
//			if(!strncmp(nbase, db->buf[i].de.name, 11))return(&db->buf[i]);
			memset(lfnbuf, 255, 512);
		}

		if(db->buf[i].lfn.attr==0xF) /* lfn slot */
		{
			j=(db->buf[i].lfn.index&63)-1;
			if(((j+1)*13)<255)
			{
				memcpy(&lfnbuf[j*13], db->buf[i].lfn.chars0, 10);
				memcpy(&lfnbuf[(j*13)+5], db->buf[i].lfn.chars1, 12);
				memcpy(&lfnbuf[(j*13)+11], db->buf[i].lfn.chars2, 4);
			}
		}
	}
	return(NULL);
}

vfat_fs_dirent *fatfs_get_dirent(char *name, vfat_dirbuf *db)
{
	int i, j, k;
	int rq;
	char nbase[12], tmp[256];
	u2 lfnbuf[256];
	vfat_fs_dirent *de;

	de=fatfs_lookup(name, db);
	if(de)return(de);

	kprint("fatfs: need create dirent '%s'\n", name);

	if(vfat_is83(name))
	{
		kprint("fatfs: shortname\n");
		for(i=0; i<db->len<<(db->sbi->sector_bits-5); i++)
			if(!db->buf[i].de.name[0] ||
				(db->buf[i].de.name[0]==0xE5))
		{
			memset(&db->buf[i], 0, 32);
			vfat_cname(name, db->buf[i].de.name, db->buf[i].de.ext);
			vfat_update_sbi(db->sbi);

			return(&db->buf[i]);
		}
		kprint("fatfs: failed create\n");
		return(NULL);
	}

	rq=(strlen(name)+12)/13;
	rq++;

	j=0;
	for(i=0; i<db->len<<(db->sbi->sector_bits-5); i++)
	{
		if(db->buf[i].de.name[0] &&
			(db->buf[i].de.name[0]!=0xE5))j=i;
		if((i-j)>=rq)break;
	}

	memset(lfnbuf, 255, 512);
	for(i=0; name[i]; i++)lfnbuf[i]=name[i];

	if((i-j)>=rq)
	{
		for(i=0; i<(rq-1); i++)
		{
			memset(&db->buf[i+j], 0, 32);
			db->buf[i+j].lfn.index=i+0x41;
			db->buf[i+j].lfn.attr==0xF;
			memcpy(db->buf[i+j].lfn.chars0, &lfnbuf[i*13], 10);
			memcpy(db->buf[i+j].lfn.chars1, &lfnbuf[(i*13)+5], 12);
			memcpy(db->buf[i+j].lfn.chars2, &lfnbuf[(i*13)+11], 4);
		}
		memset(&db->buf[i+j], 0, 32);
		vfat_gen83(name, i+j, db->buf[i+j].de.name, db->buf[i+j].de.ext);

		vfat_update_sbi(db->sbi);
		return(&db->buf[i+j]);
	}
	kprint("fatfs: failed create\n");
	return(NULL);
}

vfat_dirbuf *fatfs_readroot(vfat_sb_info *sbi)
{
	vfat_fs_dirent *deb;
	vfat_dirbuf *db;
	int l;

	if(sbi->fat_bits!=32)
	{
		deb=kalloc(sizeof(vfat_fs_dirent)*read_word(sbi->sb.fat.rootentries));
//		vfseek(sbi->dev, sbi->root_start<<sbi->sector_bits, 0);
//		vfread(deb, read_word(sbi->sb.fat.rootentries), 32, sbi->dev);
		vfreads(deb, sbi->root_start<<sbi->sector_bits,
			read_word(sbi->sb.fat.rootentries)*32, sbi->dev);

		db=kalloc(sizeof(vfat_dirbuf));
		db->sbi=sbi;
		db->buf=deb;
		db->len=read_word(sbi->sb.fat.rootentries)>>(sbi->sector_bits-5);

		db->dirty=kalloc(db->len);

		if(sbi->first)
		{
			db->next=sbi->first;
			sbi->first=db;
		}else sbi->first=db;
	}else
	{
		deb=(vfat_fs_dirent *)fatfs_loadchain(read_dword(sbi->sb.fat32.root_chain), &l, sbi);

		kprint("fat32: load root: %d clusters.\n", l);

		db=kalloc(sizeof(vfat_dirbuf));
		db->sbi=sbi;
		db->buf=deb;
		db->len=(sbi->sb.fat.clustersize*l)>>sbi->sector_bits;
		db->id=read_dword(sbi->sb.fat32.root_chain);

		db->dirty=kalloc(db->len);

		if(sbi->first)
		{
			db->next=sbi->first;
			sbi->first=db;
		}else sbi->first=db;
	}
	return(db);
}

vfat_dirbuf *fatfs_loaddir(int chain, vfat_sb_info *sbi)
{
	vfat_fs_dirent *deb;
	vfat_dirbuf *db;
	int l;

	db=sbi->first;
	while(db)
	{
		if(db->id==chain)return(db);
		db=db->next;
	}

	if(!chain)
		return(fatfs_readroot(sbi));

	deb=(vfat_fs_dirent *)fatfs_loadchain(chain, &l, sbi);

	kprint("fatfs: load dir %d: %d clusters.\n", chain, l);

	db=kalloc(sizeof(vfat_dirbuf));
	db->sbi=sbi;
	db->buf=deb;
//	db->len=sbi->sb.fat.clustersize*l;
	db->len=l;
	db->id=chain;

	db->dirty=kalloc(l);

	if(sbi->first)
	{
		db->next=sbi->first;
		sbi->first=db;
	}else sbi->first=db;

	return(db);
}

int fatfs_storedir(vfat_dirbuf *db)
{
	vfat_sb_info *sbi;

	sbi=db->sbi;

	if((sbi->fat_bits!=32) && !db->id)
	{
		vfseek(sbi->dev, sbi->root_start<<sbi->sector_bits, 0);
		vfwrite(db->buf, read_word(sbi->sb.fat.rootentries), 32, sbi->dev);
		return(0);
	}

//	fatfs_updatechain(db->buf, db->dirty, db->id, db->len, sbi);
	fatfs_storechain(db->buf, db->id, db->len, sbi);

//	kprint("fatfs: load dir %d: %d clusters.\n", chain, l);
	return(0);
}

int fatfsd_readdir(long *buf, char **fields, long *key, VDIR *dir)
{
	vfat_dirinfo *di;
	char tmp[256];
	u2 lfnbuf[256];
	int i;

	di=dir->data;
	di->pos=*key;

	memset(lfnbuf, 255, 512);

	while(di->pos<(di->db->len<<4))
	{
//		if(!di->db->buf[di->pos].name[0])break;

		if(di->db->buf[di->pos].de.name[0] && !(di->db->buf[di->pos].de.attr&0xE)) /* ignore hidden, system, and volume ents*/
		{
			if(lfnbuf[0]!=0xFFFF)
			{
				memset(tmp, 0, 256);
				for(i=0; (i<256) && (lfnbuf[i]!=0xffff); i++)tmp[i]=lfnbuf[i];
//				kprint("read lfn \"%s\"\n", tmp);
			}else
				vfat_dename(tmp, di->db->buf[di->pos].de.name, di->db->buf[di->pos].de.ext);

			buf[0]=(long)kstrdup(tmp);
			buf[1]=read_dword(di->db->buf[di->pos].de.size);
			fields[0]="$name";
			fields[1]="%size";
			fields[2]=NULL;

			di->pos++;
			*key=di->pos;
			return(1);
		}

		if(di->db->buf[di->pos].lfn.attr==0xF) /* lfn slot */
		{
			i=(di->db->buf[di->pos].lfn.index&63)-1;
			if(((i+1)*13)<255)
			{
				memcpy(&lfnbuf[i*13], di->db->buf[di->pos].lfn.chars0, 10);
				memcpy(&lfnbuf[(i*13)+5], di->db->buf[di->pos].lfn.chars1, 12);
				memcpy(&lfnbuf[(i*13)+11], di->db->buf[di->pos].lfn.chars2, 4);
			}
		}
		di->pos++;
	}

	*key=0;
	return(0);
}

int fatfsd_readdir2(char **names, void **values, long *key, VDIR *dir)
{
	vfat_dirinfo *di;
	char tmp[256];
	u2 lfnbuf[256];
	int i;

	di=dir->data;
	di->pos=*key;

	memset(lfnbuf, 255, 512);

	while(di->pos<(di->db->len<<4))
	{
//		if(!di->db->buf[di->pos].name[0])break;

		if(di->db->buf[di->pos].de.name[0] && !(di->db->buf[di->pos].de.attr&0xE)) /* ignore hidden, system, and volume ents*/
		{
			if(lfnbuf[0]!=0xFFFF)
			{
				memset(tmp, 0, 256);
				for(i=0; (i<256) && (lfnbuf[i]!=0xffff); i++)tmp[i]=lfnbuf[i];
//				kprint("read lfn \"%s\"\n", tmp);
			}else
				vfat_dename(tmp, di->db->buf[di->pos].de.name, di->db->buf[di->pos].de.ext);

			names[0]="name";
			values[0]=NetVal_WrapStr(tmp);
			names[1]="size";
			values[1]=NetVal_WrapInt(
				read_dword(di->db->buf[di->pos].de.size));
			names[2]=NULL;
			values[2]=NULL;

			di->pos++;
			*key=di->pos;
			return(1);
		}

		if(di->db->buf[di->pos].lfn.attr==0xF) /* lfn slot */
		{
			i=(di->db->buf[di->pos].lfn.index&63)-1;
			if(((i+1)*13)<255)
			{
				memcpy(&lfnbuf[i*13], di->db->buf[di->pos].lfn.chars0, 10);
				memcpy(&lfnbuf[(i*13)+5], di->db->buf[di->pos].lfn.chars1, 12);
				memcpy(&lfnbuf[(i*13)+11], di->db->buf[di->pos].lfn.chars2, 4);
			}
		}
		di->pos++;
	}

	*key=0;
	return(0);
}

int fatfs_closed(VDIR *dir)
{
	kfree(dir->data);
	kfree(dir);
	return(0);
}

VDIR *fatfs_opend_r(char *name, vfat_dirbuf *dir, vfat_sb_info *sbi)
{
	vfat_fs_dirent *de;
	vfat_dirbuf *db;
	vfat_dirinfo *di;
	char *s, *t;
	VDIR *tmp;

	while(*name=='/')name++;
	s=name;
	while(*s && (*s!='/'))s++;
	if((int)s-(int)name)
	{
		t=kalloc(((int)s-(int)name)+1);
		strncpy(t, name, ((int)s-(int)name));

		kprint("opend: attempt enter \"%s\"\n", t);

		de=fatfs_lookup(t, dir);
		if(!de)
		{
			kprint("fatfs: can't find dir \"%s\"\n", t);
			return(NULL);
		}
		if(!(de->de.attr&VFAT_FLAG_D))
		{
			kprint("fatfs: attempt to use file as dir.\n");
			return(NULL);
		}
		db=fatfs_loaddir(read_word(de->de.base), sbi);

		return(fatfs_opend_r(s+1, db, sbi));
	}

	di=kalloc(sizeof(vfat_dirinfo));
	di->db=dir;
	di->pos=0;

	tmp=kalloc(sizeof(VDIR));
	tmp->readdir=&fatfsd_readdir;
	tmp->readdir2=&fatfsd_readdir2;
	tmp->close=&fatfs_closed;
//	tmp->mkdir=&fatfs_mkdir;
	tmp->data=di;
	return(tmp);
}

VDIR *fatfs_opend(char *name, VMOUNT *mnt)
{
	VDIR *tmp;
	vfat_sb_info *sbi;
	vfat_dirinfo *di;
	char *s;

	s=name;
	while(*s=='/')s++;

	sbi=mnt->data;

	if(!sbi->root)sbi->root=fatfs_readroot(sbi);

	return(fatfs_opend_r(s, sbi->root, sbi));
}
