#include <general.h>

#ifndef __VFAT_FS_H__
#define __VFAT_FS_H__

struct vfat_sb_common {
byte _resv1[3];
char sysid[8];
byte sectorsize[2];
byte clustersize;
byte reservedsectors[2];
byte fats;
byte rootentries[2];
byte totalsectors[2];
byte media;
byte fatsize[2];
byte tracksize[2];
byte heads[2];
byte hidden[4];
byte totalsectors2[4];
};

struct vfat16_fs_sb {
byte _resv1[3];
char sysid[8];
byte sectorsize[2];
byte clustersize;
byte reservedsectors[2];
byte fats;
byte rootentries[2];
byte totalsectors[2];
byte media;
byte fatsize[2];
byte tracksize[2];
byte heads[2];
byte hidden[4];
byte totalsectors2[4];
byte drive;
byte _resv2;
byte signature;
byte serial[4];
char volume[11];
char fstag[8];
byte _free[450];
};

struct vfat32_fs_sb {
byte _resv1[3];
char sysid[8];
byte sectorsize[2];
byte clustersize;
byte reservedsectors[2];
byte fats;
byte rootentries[2];
byte totalsectors[2];
byte media;
byte fatsize[2];
byte tracksize[2];
byte heads[2];
byte hidden[4];
byte totalsectors2[4];
//start of fat32 added fields
byte fatsize2[4];
byte flags[2];
byte version[2];
byte root_chain[4];
byte info_sector[2];
byte backup_boot[2];
byte _resv3[12];
//end
byte drive;
byte _resv2;
byte signature;
byte serial[4];
char volume[11];
char fstag[8];
byte _free[422];
};

typedef union {
struct vfat_sb_common fat;
struct vfat16_fs_sb fat16;
struct vfat32_fs_sb fat32;
}vfat_fs_sb;


struct vfat_fs_file_dirent {
char name[8];
char ext[3];
byte attr;
/* win95+ */
byte lcase;
byte ctime_ms;
byte ctime[2];
byte cdate[2];
byte adate[2];
byte base_high[2];	//win95 fat32
/* dos */
byte time[2];
byte date[2];
byte base[2];
byte size[4];
};

struct vfat_fs_lfn_dirent {
byte index;
byte chars0[10];
byte attr;
byte _resv0;
byte crc;
byte chars1[12];
byte _resv1[2];
byte chars2[4];
};

typedef union {
struct vfat_fs_file_dirent de;
struct vfat_fs_lfn_dirent lfn;
}vfat_fs_dirent;

#define VFAT_FLAG_R 1	//read only
#define VFAT_FLAG_S 2	//system(no use, even on dos?)
#define VFAT_FLAG_H 4	//hidden
#define VFAT_FLAG_V 8	//volume(dos 1.x, 2.x, 3.x)
#define VFAT_FLAG_D 16	//directory(dos 2.x+)
#define VFAT_FLAG_A 32	//archived(wtf?)

#endif
