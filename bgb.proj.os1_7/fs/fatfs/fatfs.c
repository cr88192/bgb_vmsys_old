//#define DPRINT

#include <general.h>
#include <buffer.h>
#include <fs/vfat.h>

//typedef unsigned short ushort;
//typedef unsigned long ulong;

VFILE *fatfs_openf(char *name, char *fl, VMOUNT *mnt);
VDIR *fatfs_opend(char *name, VMOUNT *mnt);
VFILE *fatfs_sl_opensl(int idx, char *fl, VMOUNT *mnt);
int fatfs_sl_createsl(char *type, struct VMOUNT_T *dir);

ushort read_word(byte *var)
{
	return(var[0]+(var[1]<<8));
}

ulong read_dword(byte *var)
{
	return(var[0]+(var[1]<<8)+(var[2]<<16)+(var[3]<<24));
}

int write_word(byte *var, ushort v)
{
	var[0]=v&0xff;
	var[1]=(v>>8)&0xff;
	return(0);
}

int write_dword(byte *var, ulong v)
{
	var[0]=v&0xff;
	var[1]=(v>>8)&0xff;
	var[2]=(v>>16)&0xff;
	var[3]=(v>>24)&0xff;
	return(0);
}

int log2(int n)
{
	int i;
	for(i=0; n>1; i++)n>>=1;
	return(i);
}

int vfat_update_sbi(vfat_sb_info *sbi)
{
	vfat_dirbuf *db;

	db=sbi->first;
	while(db)
	{
		fatfs_storedir(db);
		db=db->next;
	}

	if(sbi->fat_dirty)
	{
		vfwrites(sbi->fat, sbi->fat_start<<sbi->sector_bits,
			sbi->fat_size<<sbi->sector_bits, sbi->dev);
	}
	return(0);
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
	fatfs_sl_init();
	return(0);
}
