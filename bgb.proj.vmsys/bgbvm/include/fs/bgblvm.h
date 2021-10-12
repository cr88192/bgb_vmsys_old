#define BGBLVM_TAG				"BGBLVM"
#define BGBLVM_VERSION_MAJOR	0
#define BGBLVM_VERSION_MINOR	0

#define BGBLVM_DEF_SECTOR_BITS	9
#define BGBLVM_DEF_EXTENT_BITS	7

typedef struct bgblvm_sb_t {
byte tag[6];		//"BGBLVM"
byte ver[2];		//version, major/minor
//8 bytes
byte sizes;			//&7=sector bits-9 (allowing up to 16), >>3&31=extent size
					//(sectors)
byte lvlst_len;		//length of list of volumes (sectors)
byte map_len[2];	//length of the volume map (sectors)
byte extents[4];	//how many extents are in this partition
//16 bytes
byte name[16];		//short name of this partition (may be a string or guid)
//32 bytes
byte _resv[256-32];
byte names[112][16];	//device names
}bgblvm_sb;

typedef struct bgblvm_extent_ref_t {
byte extent[4];		//data extent or node of extent tree
byte _resv[2];		//reserved, set to 0
byte p_index;		//index into partitions list for extent
byte height;		//height of tree, 0=data, 1=single indirection, 2=double, ...
//8
}bgblvm_extent_ref;

typedef struct bgblvm_lvlst_ent_t {
byte flag[2];		//0x00=free, 0x01-0xFF will be dos style types, 0x100=generic used, 0x101-0x1FF map to slots in name list, 0x200-0xFFFF reserved
byte _resv0[2];
byte length[4];		//logical length of volume (extents)
//8
bgblvm_extent_ref extent;	//data extent or root of extent tree
//16
char name[48];
//64
}bgblvm_lvlst_ent;
