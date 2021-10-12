#include <general.h>
#include <buffer.h>
#include <fs/vfat.h>

int vfat_readfatent12(int num, byte *fat)
{
	int base,tmp;
	base=(num*3)/2;
	tmp=fat[base]+(fat[base+1]<<8);
	if(num&1)tmp>>=4;
	tmp&=0xFFF;
	return(tmp);
}

int vfat_readfatent16(int num, byte *fat)
{
	int base,tmp;
	base=num*2;
	tmp=fat[base]+(fat[base+1]<<8);
	return(tmp);
}

int vfat_readfatent32(int num, byte *fat)
{
	int base,tmp;
	base=num*4;
	tmp=fat[base]+(fat[base+1]<<8)+(fat[base+2]<<16)+(fat[base+3]<<24);
	return(tmp);
}

int vfat_readfatent(int num, vfat_sb_info *sbi)
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

int vfat_writefatent(int num, int value, vfat_sb_info *sbi)
{
	int tmp, base;
	byte *fat;

	sbi->fat_dirty=1;

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

int vfat_allocblock(vfat_sb_info *sbi)
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

//byte *fatfs_blkbuf;
//int fatfs_blknum, fatfs_blklen;
//vfat_sb_info *fatfs_last_sbi;

int vfat_readblock(void *buf, int num, vfat_sb_info *sbi)
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

	KDPRINT("fatfs: readblock 1.\n");

	blk=((num-2)*sbi->sb.fat.clustersize)+sbi->data_start;
//	blk=(num-2)+sbi->data_start;
//	blk_read(buf,blk,2,sbi->dev);
//	vfseek(sbi->dev, blk<<sbi->sector_bits, 0);
//	vfread(buf, sbi->sb.fat.clustersize<<sbi->sector_bits, 1, sbi->dev);

	KDPRINT("fatfs: readblock 2.\n");

//	vfreads(buf, blk<<sbi->sector_bits, sbi->sb.fat.clustersize<<sbi->sector_bits, sbi->dev);
	vfseek(sbi->dev, blk<<sbi->sector_bits, 0);
	KDPRINT("fatfs: readblock 3.\n");
	vfread(buf, sbi->sb.fat.clustersize<<sbi->sector_bits, 1, sbi->dev);

	KDPRINT("fatfs: readblock 4.\n");

//	if(sbi->fat_bits==12)blk=vfat_readfatent12(num,sbi->fat);
//		else if(sbi->fat_bits==16)blk=vfat_readfatent16(num,sbi->fat);
//		else if(sbi->fat_bits==32)blk=vfat_readfatent32(num,sbi->fat);
//		else kprint("fatfs: invalid fat bits.\n");

	blk=vfat_readfatent(num, sbi);

//	kprint("cluster %d, next %d.\n", num, blk);
	KDPRINT("fatfs: readblock 5.\n");

	return(blk);
}

int vfat_writeblock(void *buf, int num, vfat_sb_info *sbi)
{
	int blk;

	blk=((num-2)*sbi->sb.fat.clustersize)+sbi->data_start;
	vfwrites(buf, blk<<sbi->sector_bits, sbi->sb.fat.clustersize<<sbi->sector_bits, sbi->dev);
	blk=vfat_readfatent(num, sbi);

	return(blk);
}

byte *fatfs_loadchain(int num, int *l, vfat_sb_info *sbi)
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

int fatfs_storechain(byte *buf, int num, int l, vfat_sb_info *sbi)
{
	int len, i, j, eof, clsz;
	byte *s;

	if(sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(sbi->fat_bits==16)eof=0xFFF8;
		else if(sbi->fat_bits==12)eof=0xFF8;

	if(!l)return(-1);

	clsz=sbi->sb.fat.clustersize<<sbi->sector_bits;
	buf=kalloc(len*clsz);

	s=buf;
	i=num;
	while(l>=0)
	{
//		kprint("fatfs: body.\n");

		j=vfat_writeblock(s, i, sbi);
		if(j==eof)
		{
			j=vfat_allocblock(sbi);
			vfat_writefatent(i, j, sbi);
		}
		i=j;
		s+=clsz;
		l--;
	}

	return(0);
}

int fatfs_updatechain(byte *buf, byte *dirty, int num, int l, vfat_sb_info *sbi)
{
	int len, i, j, eof, clsz;
	byte *s;

	if(sbi->fat_bits==32)eof=0xFFFFFF8;
		else if(sbi->fat_bits==16)eof=0xFFF8;
		else if(sbi->fat_bits==12)eof=0xFF8;

	if(!l)return(-1);

	clsz=sbi->sb.fat.clustersize<<sbi->sector_bits;
	buf=kalloc(len*clsz);

	s=buf;
	i=num;
	while(l>=0)
	{
//		kprint("fatfs: body.\n");

		if(*dirty)
			j=vfat_writeblock(s, i, sbi);
			else j=vfat_readfatent(i, sbi);
		if(j==eof)
		{
			j=vfat_allocblock(sbi);
			vfat_writefatent(i, j, sbi);
		}
		i=j;
		s+=clsz;
		l--;
		dirty++;
	}

	return(0);
}
