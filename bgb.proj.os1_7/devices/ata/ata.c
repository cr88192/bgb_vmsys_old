/*
   ata will be interrupt driven.
   on an interrupt the handler will finish the request and setup the
     next request.

	FIXME: make not a pos, make detect drives and not assume lba
 */

#include <general.h>

#include <x86/io.h>
#include <x86/kpfh.h>

#include <devices/ata.h>
#include <devices/ata_req.h>

struct {
char type; /* 0=none, 1=ata, 2=atapi */
char flags; /* none */
char sel; /* 0=master, 1=slave */
struct chs_t def;
long total; /* heads*sectors*tracks */
short addr;
}ide_bus_info[4];

struct {
unsigned char fl;
//unsigned char shead;
//unsigned short sst;
unsigned char type;
//unsigned char ehead;
//unsigned short est;
unsigned long start;
unsigned long length;
}ata_part_table[4][20]; /* 4 drives, each w 4 base and 16 extended */

void ata_isr();
void (*ata_handler)();

struct req_t *ata_current_req;
struct req_t *ata_req_list;

void inportsw(unsigned short *buf,int len,int port)
{
	while(len--)*buf++=inportw(port);
}

void outportsw(unsigned short *buf,int len,int port)
{
	while(len--)outportw(port,*buf++);
}

static int ata_ready(int addr)
{
	int cnt;
	cnt=1024;
	while((cnt--)&&((inportb(addr+ATA_REG_STAT)&(ATA_STAT_BUSY|ATA_STAT_READY))!=ATA_STAT_READY));
	return(cnt);
}

static int ata_busy(int addr)
{
	int cnt;
	cnt=10000;
	while((cnt--)&&(inportb(addr+ATA_REG_STAT)&ATA_STAT_BUSY));
	return(!cnt);
}

int ata_status(int addr)
{
	int stat, err;
	stat=inportb(addr+ATA_REG_STAT);
//	kprint("ata: %d\n", stat);
	if(stat&1)
	{
		err=inportb(addr+ATA_REG_ERR);
		kprint("ata error: %d %d\n", stat, err);
	}
	return((err<<8)+stat);
}

int ata_reset(int addr)
{
//	outportb(add+ATA_REG_CMD, )
}

static int ata_cmd_chs(int c,int h,int s,int cnt,int cmd,int drv)
{
	int addr,hreg;

	addr=ide_bus_info[drv].addr;
	hreg=ide_bus_info[drv].sel<<4|0xA0|(h&0x0F);

	if(!ata_ready(addr))
	{
		kprint("ata: not ready.\n");
		return(-1);
	}

	outportb(addr+ATA_REG_CNT,cnt);
	outportb(addr+ATA_REG_SECT,s);
	outportb(addr+ATA_REG_LOCYL,c&0xFF);
	outportb(addr+ATA_REG_HICYL,(c>>8)&0xFF);
	outportb(addr+ATA_REG_DRVHD,hreg);
	outportb(addr+ATA_REG_CMD,cmd);
}

static int ata_cmd_lba(int blk,int cnt,int cmd,int drv)
{
	int addr,hreg;

	addr=ide_bus_info[drv].addr;
	hreg=ide_bus_info[drv].sel<<4|0xE0;

//	ata_status(addr);
	if(!ata_ready(addr))
	{
		kprint("ata: not ready.\n");
		return(-1);
	}

//	outportb(addr+ATA_REG_CMD, ATA_CMD_NOP);
//	if(!ata_ready(addr))
//	{
//		kprint("ata: not ready.\n");
//		return(-1);
//	}

	outportb(addr+ATA_REG_CNT,cnt);
	outportb(addr+ATA_REG_SECT,blk&0xFF);
	outportb(addr+ATA_REG_LOCYL,(blk>>8)&0xFF);
	outportb(addr+ATA_REG_HICYL,(blk>>16)&0xFF);
	hreg|=(blk>>24)&0x0F;
	outportb(addr+ATA_REG_DRVHD,hreg);
	outportb(addr+ATA_REG_CMD,cmd);

//	ata_status(addr);
}

static int ata_cmd_basic(int cmd,int drv)
{
	int addr,hreg;

	addr=ide_bus_info[drv].addr;
	hreg=ide_bus_info[drv].sel<<4|0xA0;

	if(!ata_ready(addr))
	{
		kprint("ata: not ready.\n");
		return(-1);
	}

	outportb(addr+ATA_REG_DRVHD,hreg);
	outportb(addr+ATA_REG_CMD,cmd);
}

void blk2chs(struct chs_t *dst,int blk,struct chs_t *def)
{
	dst->sector=blk%def->sector+1;
	dst->head=(blk/def->sector)%def->head;
	dst->cylinder=blk/(def->sector*def->head);
}

void __ata_uint()
{
	kprint("ATA: unexpected irq\n");
}

void __ata_read()
{
//	kprint("  ata read int.\n");

	inportsw(ata_current_req->buf,256,
		ide_bus_info[ata_current_req->drv].addr+ATA_REG_DATA);
	ata_current_req->flags|=1;
	ata_handler=&__ata_uint;
}

void __ata_write()
{
//	kprint("  ata write int.\n");
//	inportb(ide_bus_info[ata_current_req->drv].addr+ATA_REG_STAT);
	ata_status(ide_bus_info[ata_current_req->drv].addr);

	return;

	outportsw(ata_current_req->buf,256,
		ide_bus_info[ata_current_req->drv].addr+ATA_REG_DATA);
	ata_current_req->flags|=1;
	ata_handler=&__ata_uint;
}


/* FIXME: this code skips over the whole request setup
   this code is also blocking, so will be less efficient.
   assumes device lba capable.
 */
static struct req_t tmp_req;
static byte tmp_buf[512];

void ata_do_read(void *buffer,int blk,int drv)
{
//	kprint("ata_do_read: %d %d\n", blk, drv);

//	if(!ata_ready())

	ata_current_req=&tmp_req;
	tmp_req.buf=buffer;
	tmp_req.drv=drv;
	tmp_req.next=((void *)0);
	tmp_req.flags=0;

	ata_handler=&__ata_read;
	ata_cmd_lba(blk,1,ATA_CMD_RD,drv); /* assumes lba capable drive */
//	ata_cmd_chs(0,0,1,1,ATA_CMD_RD,drv); /* assumes lba capable drive */
	while(!tmp_req.flags);
//	kprint("  read.\n");
}

void ata_do_write(void *buffer, int blk, int drv)
{
	int i, addr, try;

//	kprint("ata_do_write: %d %d\n", blk, drv);

	ata_current_req=&tmp_req;
	tmp_req.buf=buffer;
	tmp_req.drv=drv;
	tmp_req.next=((void *)0);
	tmp_req.flags=0;

	try=5;

	while(try--)
	{
		if(ata_busy(addr))
		{
//			kprint("drive busy.\n");
			for(i=0; i<5; i++)sys_halt();
			continue;
		}
		ata_handler=&__ata_write;
		ata_cmd_lba(blk, 1, ATA_CMD_WR, drv); /* assumes lba capable drive */

		addr=ide_bus_info[drv].addr;

		for(i=4096; i>0; i--)if(inportb(addr+ATA_REG_STAT)&ATA_STAT_DRQ)break;
		if(i<=0)
		{
//			kprint("ATA: write failed, no drq.\n");
			outportb(addr+ATA_REG_CMD, ATA_CMD_RESET);
			for(i=0; i<5; i++)sys_halt();
			if(ata_busy(addr))
			{
				kprint("reset failed.\n");
				break;
			}
			ata_handler=&__ata_read;
			ata_cmd_chs(0, 0, 1, 1, ATA_CMD_ID, drv); /* assumes lba capable drive */
			if(ata_busy(addr))
			{
				kprint("identify failed.\n");
				break;
			}
			
			continue;
		}

		outportsw(buffer, 256, addr+ATA_REG_DATA);
//		kprint("success.\n");
		break;
	}
	if(!try)
		kprint("write failed.\n");
}

void ata_identify_drive(int drv)
{
	int c;
	short buffer[256];

	ata_handler=&__ata_read;
	ata_current_req=&tmp_req;
	tmp_req.buf=&buffer;
	tmp_req.drv=drv;
	tmp_req.next=((void *)0);
	tmp_req.flags=0;
	ata_cmd_basic(ATA_CMD_ID, drv);
	c=1<<20;
	while(!tmp_req.flags && c--);
	ide_bus_info[drv].type=0;
	if(c<=0)return;
	ide_bus_info[drv].type=1;
	kprint("ata%d exists (%s sz=%d).\n", drv, &buffer[27], buffer[60]+(buffer[61]<<16));
}

int read_block(int blk, void *buf, int cnt)
{
	while(cnt)
	{
		ata_do_read(buf, blk, 0);
		buf+=512;
		cnt--;
		blk++;
	}
	return(0);
}

int write_block(int blk, void *buf, int cnt)
{
	while(cnt)
	{
		ata_do_write(buf, blk, 0);
		buf+=512;
		cnt--;
		blk++;
	}
	return(0);
}

int ATA_Init2()
{
	int i;

	kprint("ATA init.\n");
	ide_bus_info[0].type=1;
	ide_bus_info[0].flags=0;
	ide_bus_info[0].sel=0;
	ide_bus_info[0].addr=0x1f0;

	/* assume max possible size */
	ide_bus_info[0].def.head=16;
	ide_bus_info[0].def.sector=63;
	ide_bus_info[0].def.cylinder=65535;
	ide_bus_info[0].total=16*63*65535;

	ide_bus_info[1].type=1;
	ide_bus_info[1].flags=0;
	ide_bus_info[1].sel=1;
	ide_bus_info[1].addr=0x1f0;

	ide_bus_info[2].type=1;
	ide_bus_info[2].flags=0;
	ide_bus_info[2].sel=0;
	ide_bus_info[2].addr=0x170;

	ide_bus_info[3].type=1;
	ide_bus_info[3].flags=0;
	ide_bus_info[3].sel=1;
	ide_bus_info[3].addr=0x170;

	ata_handler=&__ata_uint;
	
	NewIntISR(&ata_isr,0x20+14,0);
	enable_irq(14);
	NewIntISR(&ata_isr,0x20+15,0);
	enable_irq(15);

	for(i=0; i<4; i++)
		ata_identify_drive(i);
	
	ata_handler=&__ata_uint;
}

static int ata_offs_block, ata_offs_frag;
int atabufloc;
static byte atabuf[512];

/* FIXME: abstract to buffer cache */

static int ata_sreadlin(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	int ilen, sz;

	int block, frag;

	ilen=len;

	block=(pos[0]>>9)+((pos[1]&511)<<(32-9));
	frag=pos[0]&511;

//	kprint("ata_sread: %d.%d %d\n", block, frag, len);

	/* doesn't start on block boundary */
	if(frag)
	{
		if(block!=atabufloc)
		{
			read_block(block, atabuf, 1);
			atabufloc=block;
		}
		sz=512-frag;
		memcpy(buf, atabuf+frag, sz);
		buf+=sz;
		len-=sz;
		frag=0;
		block++;
	}

	sz=len>>9;
	read_block(block, buf, sz);
	len-=sz<<9;
	block+=sz;
	buf+=sz<<9;

	/* doesn't end on block boundary */
	if(len)
	{
		if(block!=atabufloc)
		{
			read_block(block, atabuf, 1);
			atabufloc=block;
		}
		memcpy(buf, atabuf, len);
		buf+=len;
		len-=len;
		frag+=len;
	}

	cb(fd, ilen, data);
	return(0);
}

static int ata_swritelin(void *buf, u8 pos, int len, VFILE *fd, vf_int_cb *cb, void *data)
{
	int ilen, sz;

	int block, frag;

	ilen=len;

	block=(pos[0]>>9)+((pos[1]&511)<<(32-9));
	frag=pos[0]&511;

//	kprint("ata_swrite: %d.%d %d\n", block, frag, len);

	/* doesn't start on block boundary */
	if(frag)
	{
		if(block!=atabufloc)
		{
			read_block(block, atabuf, 1);
			atabufloc=block;
		}
		sz=512-frag;
		memcpy(atabuf+frag, buf, sz);
		buf+=sz;
		len-=sz;
		frag=0;
		block++;
	}

	sz=len>>9;
	write_block(block, buf, sz);
	len-=sz<<9;
	block+=sz;
	buf+=sz<<9;

	/* doesn't end on block boundary */
	if(len)
	{
		if(block!=atabufloc)
		{
			read_block(block, atabuf, 1);
			atabufloc=block;
		}
		memcpy(atabuf, buf, len);
		buf+=len;
		len-=len;
		frag+=len;
	}

	cb(fd, ilen, data);
	return(0);
}

static int ata_writelin(void *buf, int len, VFILE *fd)
{
	int ilen, sz;

	ilen=len;

	/* doesn't start on block boundary */
	if(ata_offs_frag)
	{
		if(ata_offs_block!=atabufloc)
		{
			read_block(ata_offs_block, atabuf, 1);
			atabufloc=ata_offs_block;
		}
		sz=512-ata_offs_frag;
		memcpy(atabuf+ata_offs_frag, buf, sz);
		buf+=sz;
		len-=sz;
		ata_offs_frag=0;
		ata_offs_block++;
		write_block(atabufloc, atabuf, 1);
	}

	sz=len>>9;
	write_block(ata_offs_block, buf, sz);
	len-=sz<<9;
	ata_offs_block+=sz;
	buf+=sz<<9;

	/* doesn't end on block boundary */
	if(len)
	{
		if(ata_offs_block!=atabufloc)
		{
			read_block(ata_offs_block, atabuf, 1);
			atabufloc=ata_offs_block;
		}
		memcpy(atabuf, buf, len);
		buf+=len;
		len-=len;
		ata_offs_frag+=len;
		write_block(atabufloc, atabuf, 1);
	}

	return(ilen);
}

static int ata_readlin(void *buf, int len, VFILE *fd)
{
	int ilen, sz;

	ilen=len;

//	kprint("ata_read: %d %d\n", vftell(fd), len);

	/* doesn't start on block boundary */
	if(ata_offs_frag)
	{
		if(ata_offs_block!=atabufloc)
		{
			read_block(ata_offs_block, atabuf, 1);
			atabufloc=ata_offs_block;
		}
		sz=512-ata_offs_frag;
		memcpy(buf, atabuf+ata_offs_frag, sz);
		buf+=sz;
		len-=sz;
		ata_offs_frag=0;
		ata_offs_block++;
	}

	sz=len>>9;
	read_block(ata_offs_block, buf, sz);
	len-=sz<<9;
	ata_offs_block+=sz;
	buf+=sz<<9;

	/* doesn't end on block boundary */
	if(len)
	{
		if(ata_offs_block!=atabufloc)
		{
			read_block(ata_offs_block, atabuf, 1);
			atabufloc=ata_offs_block;
		}
		memcpy(buf, atabuf, len);
		buf+=len;
		len-=len;
		ata_offs_frag+=len;
	}
	return(ilen);
}

static int ata_seeklin(VFILE *fd, int adr, int rel)
{
	switch(rel)
	{
	case 0:
		ata_offs_frag=adr&511;
		ata_offs_block=adr>>9;
		break;
	case 1:
		ata_offs_frag+=adr;
		ata_offs_block+=ata_offs_frag>>9;
		ata_offs_frag&=511;
		break;
	default:
		kprint("ATA: Invalid Seek.\n");
		break;
	}
	return((ata_offs_block<<9)+ata_offs_frag);
}

static int ata_lseeklin(VFILE *fd, u8 adr, u8 ret, int rel)
{
	int block, frag;

	frag=adr[0]&511;
	shr_u8(ret, adr, 9);
	block=(s4)ret[0];

	switch(rel)
	{
	case 0:
		ata_offs_frag=frag;
		ata_offs_block=block;
		break;
	case 1:
		ata_offs_frag+=frag;
		ata_offs_block+=block+(ata_offs_frag>>9);
		ata_offs_frag&=511;
		break;
	default:
		kprint("ATA: Invalid Seek.\n");
		break;
	}
	ret[0]=(ata_offs_block<<9)+ata_offs_frag;
	ret[1]=ata_offs_block>>23;

	return(0);
}

static int ata_telllin(VFILE *fd)
{
	return((ata_offs_block<<9)+ata_offs_frag);
}

static VFILE *ata_open(char *name, void *data)
{
	VFILE *tmp;
	tmp=vfnew();

	tmp->swrite_proc=ata_swritelin;
	tmp->sread_proc=ata_sreadlin;

//	tmp->write_proc=ata_writelin;
//	tmp->read_proc=ata_readlin;
//	tmp->seek_proc=ata_seeklin;
//	tmp->lseek_proc=ata_lseeklin;
//	tmp->tell_proc=ata_telllin;

	tmp->mmap_proc=&KPFH_BasicMMap;

	return(tmp);
}

int PartMS_ProcessDev(VFILE *vfd, char *base, int idx);

int ATA_Init()
{
	VFILE *fd;

	ATA_Init2();

	Driver_RegisterStream("ata/0", &ata_open, NULL);

	fd=ata_open(NULL, NULL);
	PartMS_ProcessDev(fd, "ata/0", 1);
}
