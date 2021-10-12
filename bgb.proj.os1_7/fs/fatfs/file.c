#include <general.h>
#include <buffer.h>
#include <fs/vfat.h>

static int fatfs_readfile(void *buf, int len, vfat_filebuf *fb)
{
	byte *blkbuf;
	int offs, clsz, j, n, k;
	int eof;

	if(fb->sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(fb->sbi->fat_bits==16)eof=0xFFF8;
		else if(fb->sbi->fat_bits==12)eof=0xFF8;

	if(fb->apos>=fb->size)fb->eof=1;
	if(fb->eof)return(0);

	len=((len+fb->apos)>fb->size)?(fb->size-fb->apos):len;

	clsz=fb->sbi->sb.fat.clustersize<<fb->sbi->sector_bits;
	blkbuf=kralloc(clsz);

	fb->cur=fb->base;
	j=fb->apos;
	while(j>=clsz)
	{
		if(fb->cur==eof)
		{
			fb->eof=1;
			return(0);
		}
		fb->cur=vfat_readfatent(fb->cur, fb->sbi);
		j-=clsz;
	}

	k=0;

	KDPRINT("fatfs: read.\n");

	offs=fb->apos%clsz;
	if(offs)
	{
		KDPRINT("fatfs: unalign.\n");

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
		KDPRINT("fatfs: body.\n");

		fb->cur=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(buf, blkbuf, clsz);
		buf+=clsz;
		len-=clsz;
		fb->apos+=clsz;
		k+=clsz;
	}
	if(len)
	{
		KDPRINT("fatfs: end.\n");
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

//	kfree(blkbuf);

	KDPRINT("fatfs: ret\n");

	return(k);
}

static int fatfs_writefile(void *buf, int len, vfat_filebuf *fb)
{
	byte *blkbuf;
	int offs, clsz, j, n, k, eof;
	int df, ds;

//	if(fb->eof)return(0);
//	len=((len+fb->apos)>fb->size)?(fb->size-fb->apos):len;

	clsz=fb->sbi->sb.fat.clustersize<<fb->sbi->sector_bits;
	blkbuf=kralloc(clsz);

	if(fb->sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(fb->sbi->fat_bits==16)eof=0xFFF8;
		else if(fb->sbi->fat_bits==12)eof=0xFF8;

	df=0;
	ds=0;

	if(!fb->base)
	{
		fb->base=vfat_allocblock(fb->sbi);
		write_word(fb->de->de.base, fb->base);
		ds=1;
	}
	fb->cur=fb->base;
	j=fb->apos;
	while(j>=clsz)
	{
		n=vfat_readfatent(fb->cur, fb->sbi);
		j-=clsz;

		if(n==eof)
		{
			n=vfat_allocblock(fb->sbi);
			vfat_writefatent(fb->cur, n, fb->sbi);
			df=1;
		}
		if(!n)
		{
			kprint("fatfs: disk full.\n");
			return(0);
		}
		fb->cur=n;
	}


	k=0;

	offs=fb->apos%clsz;

//	kprint("fatfs: write %d bytes.\n", len);

	if(offs)
	{
//		kprint("fatfs: w-unalign.\n");

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);

		j=(len<(clsz-offs))?len:(clsz-offs);
//		memcpy(buf, blkbuf+offs, j);
		memcpy(blkbuf+offs, buf, j);
		vfat_writeblock(blkbuf, fb->cur, fb->sbi);

		buf+=j;
		len-=j;
		fb->apos+=j;
		if(fb->apos>fb->size)
		{
			fb->size=fb->apos;
			ds=1;
		}
		offs+=j;
		k+=j;
		if(offs>=clsz)
		{
			if(n==eof)
			{
				n=vfat_allocblock(fb->sbi);
				vfat_writefatent(fb->cur, n, fb->sbi);
				df=1;
			}
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
//		kprint("fatfs: w-body.\n");

//		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(blkbuf, buf, clsz);
		n=vfat_writeblock(blkbuf, fb->cur, fb->sbi);
		buf+=clsz;
		len-=clsz;
		fb->apos+=clsz;
		if(fb->apos>fb->size)
		{
			fb->size=fb->apos;
			ds=1;
		}
		k+=clsz;

		if(n==eof)
		{
			n=vfat_allocblock(fb->sbi);
			vfat_writefatent(fb->cur, n, fb->sbi);
			df=1;
		}
		if(!n)
		{
			kprint("fatfs: disk full.\n");
			return(k);
		}
		fb->cur=n;
	}
	if(len)
	{
//		kprint("fatfs: w-end.\n");
		offs=fb->apos%clsz;

		n=vfat_readblock(blkbuf, fb->cur, fb->sbi);
		memcpy(blkbuf, buf, len);
		vfat_writeblock(blkbuf, fb->cur, fb->sbi);

		buf+=len;
		k+=len;
		fb->apos+=len;
		if(fb->apos>fb->size)
		{
			fb->size=fb->apos;
			ds=1;
		}
		offs+=len;
		if(offs>=clsz)fb->cur=n;
		len-=len;
	}

//	if(fb->apos>=fb->size)fb->eof=1;

//	kprint("fatfs: w-ok.\n");

	write_dword(fb->de->de.size, fb->size);
	vfat_update_sbi(fb->sbi);

//	kfree(blkbuf);

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

vfat_filebuf *fatfs_openfd(vfat_sb_info *sbi, vfat_dirbuf *db, vfat_fs_dirent *de)
{
	vfat_filebuf *fb;
	fb=kalloc(sizeof(vfat_filebuf));
	fb->sbi=sbi;
	fb->base=read_word(de->de.base);
	fb->size=read_dword(de->de.size);
	fb->cur=fb->base;
	fb->apos=0;
	fb->eof=0;

	fb->db=db;
	fb->de=de;

//	kprint("%s %d %d %d\n", de->de.name, fb->base, fb->size, fb->cur);

	return(fb);
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

VFILE *fatfs_openf_r(char *name, char *attr, vfat_dirbuf *dir, vfat_sb_info *sbi)
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

		return(fatfs_openf_r(s+1, attr, db, sbi));
	}

	if(*attr=='w')
		de=fatfs_get_dirent(name, dir);
		else de=fatfs_lookup(name, dir);
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

	fb=fatfs_openfd(sbi, dir, de);

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

	return(fatfs_openf_r(s, fl, sbi->root, sbi));
}
