#include <general.h>
#include <buffer.h>
#include <fs/vfat.h>

//typedef unsigned short ushort;
//typedef unsigned long ulong;

typedef struct vfat_sb_info_t {
vfat_fs_sb sb;
VFILE *dev;
byte *fat;
struct vfat_dirbuf_t *root;
struct vfat_dirbuf_t *first;
int root_start;
int data_start;
int sector_bits;
int fat_size;
int fat_start;
int fat_bits;

int fat_rover;
int clusters;

}vfat_sb_info;

typedef struct vfat_dirbuf_t {
struct vfat_dirbuf_t *next, *prev;
struct vfat_sb_info_t *sbi;
vfat_fs_dirent *buf;

byte *dirty;
int len; /* length of directory(blocks) */
int ucnt;
int id; /* chain id of dir */
}vfat_dirbuf;

typedef struct vfat_dirinfo_t {
vfat_dirbuf *db;
int pos;
}vfat_dirinfo;

typedef struct vfat_filebuf_t {
vfat_sb_info *sbi;
long base;
long size;
long cur;	/* current block in fat */
long apos;	/* byte position in file */
byte eof;
}vfat_filebuf;

static u2 read_word(byte *var)
{
	return(var[0]+(var[1]<<8));
}

static u4 read_dword(byte *var)
{
	return(var[0]+(var[1]<<8)+(var[2]<<16)+(var[3]<<24));
}

static int vfat_readfatent12(int num, byte *fat)
{
	int base,tmp;
	base=(num*3)/2;
	tmp=fat[base]+(fat[base+1]<<8);
	if(num&1)tmp>>=4;
	tmp&=0xFFF;
	return(tmp);
}

static int vfat_readfatent16(int num, byte *fat)
{
	int base,tmp;
	base=num*2;
	tmp=fat[base]+(fat[base+1]<<8);
	return(tmp);
}

static int vfat_readfatent32(int num, byte *fat)
{
	int base,tmp;
	base=num*4;
	tmp=fat[base]+(fat[base+1]<<8)+(fat[base+2]<<16)+(fat[base+3]<<24);
	return(tmp);
}

static int vfat_readfatent(int num, vfat_sb_info *sbi)
{
	int tmp, base;
	byte *fat;

	fat=sbi->fat;
	switch(sbi->fat_bits)
	{
	case 12:
		base=(num*3)/2;
		tmp=fat[base]+(fat[base+1]<<8);
		if(num&1)tmp>>=4;
		tmp&=0xFFF;
		break;
	case 16:
		base=num*2;
		tmp=fat[base]+(fat[base+1]<<8);
		break;
	case 32:
		tmp=fat[base]+(fat[base+1]<<8)+(fat[base+2]<<16)+(fat[base+3]<<24);
		break;
	default:
		kprint("fatfs: invalid fat bits.\n");
		tmp=0;
		break;
	}

/*	if(sbi->fat_bits==12)blk=vfat_readfatent12(num,sbi->fat);
		else if(sbi->fat_bits==16)blk=vfat_readfatent16(num,sbi->fat);
		else if(sbi->fat_bits==32)blk=vfat_readfatent32(num,sbi->fat);
		else kprint("fatfs: invalid fat bits.\n"); */

	return(tmp);
}

static int vfat_writefatent(int num, int value, vfat_sb_info *sbi)
{
	int tmp, base;
	byte *fat;

	fat=sbi->fat;
	switch(sbi->fat_bits)
	{
	case 12:
		base=(num*3)/2;
		tmp=fat[base]+(fat[base+1]<<8);
		if(num&1)tmp&=0x000F;
			else tmp&=0xF000;
		if(num&1)tmp|=value<<4;
			else tmp|=value;
		fat[base]=tmp&0xff;
		fat[base+1]=(tmp>>8)&0xff;
		break;
	case 16:
		base=num*2;
		fat[base]=value&0xff;
		fat[base+1]=(value>>8)&0xff;
		break;
	case 32:
		base=num*4;
		fat[base]=value&0xff;
		fat[base+1]=(value>>8)&0xff;
		fat[base+2]=(value>>16)&0xff;
		fat[base+3]=(value>>24)&0xff;
		break;
	default:
		kprint("fatfs: invalid fat bits.\n");
		tmp=0;
		break;
	}

	return(0);
}

static int vfat_allocblock(vfat_sb_info *sbi)
{
	int i;

	for(i=0; i<sbi->clusters; i++)
		if(!vfat_readfatent(i, sbi))
	{
		vfat_writefatent(i, 0xFFFFFF8, sbi);
		return(i);
	}
	return(0);
}

//static byte *fatfs_blkbuf;
//static int fatfs_blknum, fatfs_blklen;
//static vfat_sb_info *fatfs_last_sbi;

static int vfat_readblock(void *buf, int num, vfat_sb_info *sbi)
{
	int blk;

/*
	if(!fatfs_blkbuf | (fatfs_blklen<(sbi->sb.fat.clustersize<<sbi->sector_bits)))
	{
		if(fatfs_blkbuf)kfree(fatfs_blkbuf);
		fatfs_blkbuf=kalloc(sbi->sb.fat.clustersize<<sbi->sector_bits);
		fatfs_blknum=-1;
		fatfs_blklen=sbi->sb.fat.clustersize<<sbi->sector_bits;
		fatfs_last_sbi=NULL;
	}
	if((num==fatfs_blknum) &&) */

	blk=((num-2)*sbi->sb.fat.clustersize)+sbi->data_start;
//	blk=(num-2)+sbi->data_start;
//	blk_read(buf,blk,2,sbi->dev);
//	vfseek(sbi->dev, blk<<sbi->sector_bits, 0);
//	vfread(buf, sbi->sb.fat.clustersize<<sbi->sector_bits, 1, sbi->dev);

	vfreads(buf, blk<<sbi->sector_bits, sbi->sb.fat.clustersize<<sbi->sector_bits, sbi->dev);

//	if(sbi->fat_bits==12)blk=vfat_readfatent12(num,sbi->fat);
//		else if(sbi->fat_bits==16)blk=vfat_readfatent16(num,sbi->fat);
//		else if(sbi->fat_bits==32)blk=vfat_readfatent32(num,sbi->fat);
//		else kprint("fatfs: invalid fat bits.\n");

	blk=vfat_readfatent(num, sbi);

//	kprint("cluster %d, next %d.\n", num, blk);

	return(blk);
}

static int vfat_writeblock(void *buf, int num, vfat_sb_info *sbi)
{
	int blk;

	blk=((num-2)*sbi->sb.fat.clustersize)+sbi->data_start;
	vfwrites(buf, blk<<sbi->sector_bits, sbi->sb.fat.clustersize<<sbi->sector_bits, sbi->dev);
	blk=vfat_readfatent(num, sbi);

	return(blk);
}

static byte *fatfs_loadchain(int num, int *l, vfat_sb_info *sbi)
{
	int len, i, eof, clsz;
	byte *buf, *s;

	if(sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(sbi->fat_bits==16)eof=0xFFF8;
		else if(sbi->fat_bits==12)eof=0xFF8;

	len=0;
	i=num;
	while(i)
	{
		i=vfat_readfatent(i, sbi);
		len++;
		if(i>=eof)break;
	}
	*l=len;

	if(!len)return(NULL);

	clsz=sbi->sb.fat.clustersize<<sbi->sector_bits;
	buf=kalloc(len*clsz);

	s=buf;
	i=num;
	while(len)
	{
//		kprint("fatfs: body.\n");

		i=vfat_readblock(s, i, sbi);
		s+=clsz;
		len--;
	}

	return(buf);
}

static int fatfs_readfile(void *buf, int len, vfat_filebuf *fb)
{
	byte *blkbuf;
	int offs, clsz, j, n, k;

	if(fb->eof)return(0);
	len=((len+fb->apos)>fb->size)?(fb->size-fb->apos):len;

	clsz=fb->sbi->sb.fat.clustersize<<fb->sbi->sector_bits;
	blkbuf=kalloc(clsz);

	fb->cur=fb->base;
	j=fb->apos;
	while(j>=clsz)
	{
		fb->cur=vfat_readfatent(fb->cur, fb->sbi);
		j-=clsz;
	}

	k=0;

//	kprint("fatfs: read.\n");

	offs=fb->apos%clsz;
	if(offs)
	{
//		kprint("fatfs: unalign.\n");

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);

		j=(len<(clsz-offs))?len:(clsz-offs);
		memcpy(buf, blkbuf+offs, j);
		buf+=j;
		len-=j;
		fb->apos+=j;
		offs+=j;
		k+=j;
		if(offs>=clsz)fb->cur=n;
	}
	while(len>=clsz)
	{
//		kprint("fatfs: body.\n");

		fb->cur=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(buf, blkbuf, clsz);
		buf+=clsz;
		len-=clsz;
		fb->apos+=clsz;
		k+=clsz;
	}
	if(len)
	{
//		kprint("fatfs: end.\n");
		offs=fb->apos%clsz;

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(buf, blkbuf, len);
		buf+=len;
		k+=len;
		fb->apos+=len;
		offs+=len;
		if(offs>=clsz)fb->cur=n;
		len-=len;
	}

	if(fb->apos>=fb->size)fb->eof=1;

	kfree(blkbuf);

	return(k);
}

static int fatfs_writefile(void *buf, int len, vfat_filebuf *fb)
{
	byte *blkbuf;
	int offs, clsz, j, n, k, eof;

//	if(fb->eof)return(0);
	len=((len+fb->apos)>fb->size)?(fb->size-fb->apos):len;

	clsz=fb->sbi->sb.fat.clustersize<<fb->sbi->sector_bits;
	blkbuf=kalloc(clsz);

	if(fb->sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(fb->sbi->fat_bits==16)eof=0xFFF8;
		else if(fb->sbi->fat_bits==12)eof=0xFF8;

	fb->cur=fb->base;
	j=fb->apos;
	while(j>=clsz)
	{
		n=vfat_readfatent(fb->cur, fb->sbi);
		j-=clsz;

		if(n==eof)
			n=vfat_allocblock(fb->sbi);
		if(!n)
		{
			kprint("fatfs: disk full.\n");
			return(0);
		}
		fb->cur=n;
	}


	k=0;

//	kprint("fatfs: read.\n");

	offs=fb->apos%clsz;
	if(offs)
	{
//		kprint("fatfs: unalign.\n");

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);

		j=(len<(clsz-offs))?len:(clsz-offs);
//		memcpy(buf, blkbuf+offs, j);
		memcpy(blkbuf+offs, buf, j);
		vfat_writeblock(blkbuf, fb->cur, fb->sbi);

		buf+=j;
		len-=j;
		fb->apos+=j;
		if(fb->apos>fb->size)fb->size=fb->apos;
		offs+=j;
		k+=j;
		if(offs>=clsz)
		{
			if(n==eof)
				n=vfat_allocblock(fb->sbi);
			if(!n)
			{
				kprint("fatfs: disk full.\n");
				return(k);
			}
			fb->cur=n;
		}
	}
	while(len>=clsz)
	{
//		kprint("fatfs: body.\n");

//		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(blkbuf, buf, clsz);
		n=vfat_writeblock(blkbuf, fb->cur, fb->sbi);
		buf+=clsz;
		len-=clsz;
		fb->apos+=clsz;
		if(fb->apos>fb->size)fb->size=fb->apos;
		k+=clsz;

		if(n==eof)
			n=vfat_allocblock(fb->sbi);
		if(!n)
		{
			kprint("fatfs: disk full.\n");
			return(k);
		}
		fb->cur=n;
	}
	if(len)
	{
//		kprint("fatfs: end.\n");
		offs=fb->apos%clsz;

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(blkbuf, buf, len);
		vfat_writeblock(blkbuf, fb->cur, fb->sbi);

		buf+=len;
		k+=len;
		fb->apos+=len;
		if(fb->apos>fb->size)fb->size=fb->apos;
		offs+=len;
		if(offs>=clsz)fb->cur=n;
		len-=len;
	}

//	if(fb->apos>=fb->size)fb->eof=1;

	kfree(blkbuf);

	return(k);
}

int fatfs_fb_read(void *buf, int len, VFILE *fd)
{
	return(fatfs_readfile(buf, len, fd->buffer));
}

int fatfs_fb_write(void *buf, int len, VFILE *fd)
{
	return(fatfs_writefile(buf, len, fd->buffer));
}

int fatfs_fb_seek(VFILE *fd, int adr, int rel)
{
	vfat_filebuf *fb;
	fb=fd->buffer;
	switch(rel)
	{
	case 0:
		fb->apos=adr;
		break;
	case 1:
		fb->apos+=adr;
		break;
	case 2:
		fb->apos=fb->size+adr;
		break;
	}
	return(fb->apos);
}

int fatfs_fb_tell(VFILE *fd)
{
	vfat_filebuf *fb;
	fb=fd->buffer;
	return(fb->apos);
}

int fatfs_fb_eof(VFILE *fd)
{
	vfat_filebuf *fb;
	fb=fd->buffer;
	return(fb->eof);
}

int fatfs_fb_close(VFILE *fd)
{
	kfree(fd->buffer);
	kfree(fd);
	return(0);
}

VFILE *fatfs_wrapfb(vfat_filebuf *fb)
{
	VFILE *fd;
	fd=vfnew();
	fd->buffer=fb;
	fd->read_proc=&fatfs_fb_read;
	fd->write_proc=&fatfs_fb_write;
	fd->seek_proc=&fatfs_fb_seek;
	fd->tell_proc=&fatfs_fb_tell;
	fd->eof_proc=&fatfs_fb_eof;
	fd->close_proc=&fatfs_fb_close;
	return(fd);
}

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

vfat_filebuf *fatfs_openfd(vfat_sb_info *sbi, vfat_fs_dirent *de)
{
	vfat_filebuf *fb;
	fb=kalloc(sizeof(vfat_filebuf));
	fb->sbi=sbi;
	fb->base=read_word(de->de.base);
	fb->size=read_dword(de->de.size);
	fb->cur=fb->base;
	fb->apos=0;
	fb->eof=0;

//	kprint("%s %d %d %d\n", de->de.name, fb->base, fb->size, fb->cur);

	return(fb);
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

	deb=fatfs_loadchain(chain, &l, sbi);

	kprint("fatfs: load dir %d: %d clusters.\n", chain, l);

	db=kalloc(sizeof(vfat_dirbuf));
	db->sbi=sbi;
	db->buf=deb;
	db->len=sbi->sb.fat.clustersize*l;
	db->id=chain;

	if(sbi->first)
	{
		db->next=sbi->first;
		sbi->first=db;
	}else sbi->first=db;

	return(db);
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

		if(sbi->first)
		{
			db->next=sbi->first;
			sbi->first=db;
		}else sbi->first=db;
	}else
	{
		deb=fatfs_loadchain(read_dword(sbi->sb.fat32.root_chain), &l, sbi);

		kprint("fat32: load root: %d clusters.\n", l);

		db=kalloc(sizeof(vfat_dirbuf));
		db->sbi=sbi;
		db->buf=deb;
		db->len=sbi->sb.fat.clustersize*l;
		db->id=read_dword(sbi->sb.fat32.root_chain);

		if(sbi->first)
		{
			db->next=sbi->first;
			sbi->first=db;
		}else sbi->first=db;
	}
	return(db);
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

VFILE *fatfs_openf_r(char *name, vfat_dirbuf *dir, vfat_sb_info *sbi)
{
	vfat_fs_dirent *de;
	vfat_dirbuf *db;
	char *s, *t;
	vfat_filebuf *fb;
	VFILE *fd;

	while(*name=='/')name++;
	s=name;
	while(*s && (*s!='/'))s++;
	if(*s=='/')
	{
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
			kprint("fatfs: attempt to use file as dir.\n");
			return(NULL);
		}
		db=fatfs_loaddir(read_word(de->de.base), sbi);

		return(fatfs_openf_r(s+1, db, sbi));
	}

	de=fatfs_lookup(name, dir);
	if(!de)
	{
		kprint("fatfs: can't find file \"%s\"\n", name);
		return(NULL);
	}
	if(de->de.attr&VFAT_FLAG_D)
	{
		kprint("fatfs: attempt to use dir as file.\n");
		return(NULL);
	}

	fb=fatfs_openfd(sbi, de);

	fd=fatfs_wrapfb(fb);

	return(fd);
}

VFILE *fatfs_openf(char *name, char *fl, VMOUNT *mnt)
{
	vfat_sb_info *sbi;
	vfat_fs_dirent *de;
	vfat_filebuf *fb;
	VFILE *fd;
	char *s;

	s=name;
	while(*s=='/')s++;

	sbi=mnt->data;

	if(!sbi->root)sbi->root=fatfs_readroot(sbi);

	return(fatfs_openf_r(s, sbi->root, sbi));
}

int log2(int n)
{
	int i;
	for(i=0; n>1; i++)n>>=1;
	return(i);
}

vfat_sb_info *vfat_get_sbi(VFILE *fd)
{
	vfat_sb_info *sbi;
	vfat_fs_sb *lsb;
	int i;

	sbi=kalloc(sizeof(vfat_sb_info));
	lsb=&sbi->sb;

//	vfseek(fd, 0, 0);
	vfreads(lsb, 0, 512, fd);

	sbi->fat_bits=0;
	if(!strncmp(lsb->fat16.fstag, "FAT12", 5))sbi->fat_bits=12;
	if(!strncmp(lsb->fat16.fstag, "FAT16", 5))sbi->fat_bits=16;
	if(!strncmp(lsb->fat32.fstag, "FAT32", 5))sbi->fat_bits=32;

//	if(strncmp(lsb->fstag, "FAT12", 5) && strncmp(lsb->fstag, "FAT16", 5))
	if(!sbi->fat_bits)
	{
		kprint("not fat.\n");
		kfree(sbi);
		return(NULL);
	}

	sbi->sector_bits=log2(read_word(lsb->fat.sectorsize));

	sbi->fat_size=read_word(lsb->fat.fatsize);
	if(!sbi->fat_size)sbi->fat_size=read_dword(lsb->fat32.fatsize2);
	sbi->fat_start=read_word(lsb->fat.reservedsectors);

	if(sbi->fat_bits!=32)
	{
		sbi->root_start=sbi->fat_start+(lsb->fat.fats*sbi->fat_size);
		sbi->data_start=sbi->root_start+(read_word(lsb->fat.rootentries)>>(sbi->sector_bits-5));
	}else
	{
		sbi->root_start=0;
		sbi->data_start=sbi->fat_start+(lsb->fat.fats*sbi->fat_size);
	}

	i=read_word(lsb->fat.totalsectors);
	if(!i)i=read_dword(lsb->fat.totalsectors2);
	sbi->clusters=(i-sbi->data_start)/lsb->fat.clustersize;

	kprint("fat: sec_bits=%d fat_size=%d fat_start=%d fat_bits=%d root_start=%d\n"
		"        data_start=%d fats=%d hidden=%d clusters=%d\n",
		sbi->sector_bits, sbi->fat_size, sbi->fat_start, sbi->fat_bits, sbi->root_start, sbi->data_start,
		lsb->fat.fats, read_word(lsb->fat.hidden), sbi->clusters);

	/* allocate fat with some space at end for dirty map */
	sbi->fat=kalloc((sbi->fat_size+1)<<sbi->sector_bits);

//	blk_read(sbi->fat, sbi->fat_start, sbi->fat_size, dev);
//	vfseek(fd, sbi->fat_start<<sbi->sector_bits, 0);
//	vfread(sbi->fat, sbi->fat_size<<sbi->sector_bits, 1, fd);

	vfreads(sbi->fat, sbi->fat_start<<sbi->sector_bits,
		sbi->fat_size<<sbi->sector_bits, fd);

	sbi->root=NULL;
	sbi->first=NULL;
	sbi->dev=fd;

	return(sbi);
}

VMOUNT *fatfs_mount(char **options)
{
	VMOUNT *tmp;
	VFILE *dev;
	vfat_sb_info *sbi;

//	dev=VPath_OpenFile("/devices/floppy", "rb");
//	dev=Driver_OpenStream("floppy", "");

	dev=VPath_OpenFile(options[0], "rb");
	if(!dev)
	{
		kprint("fatfs: can't open dev \"%s\".\n", options[0]);
		return(NULL);
	}

	sbi=vfat_get_sbi(dev);
	if(!sbi)
	{
		kprint("fatfs: invalid sb on dev \"%s\".\n", options[0]);
//		vfclose(dev);
		return(NULL);
	}

	tmp=kalloc(sizeof(VMOUNT));
	tmp->data=sbi;
	tmp->unmount=&kfree;
	tmp->openf=&fatfs_openf;
	tmp->opend=&fatfs_opend;
	return(tmp);
}

int fatfs_init()
{
	Vfs_RegisterType("fatfs", &fatfs_mount);
	return(0);
}
