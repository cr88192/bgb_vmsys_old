#include <general.h>
#include <graphics/render.h>

#include <stdio.h>

#include <sys/types.h>

static char *con_inbuf=NULL;
static char con_char=-1;

byte con_keybuf[64];
byte con_keybuf_pos;
int con_keyb_hnd=0;

extern displaywindow *gfx_screen;

int keyb_map_us[128]={
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
};

int keyb_map_ru_yasherty[128]={
0x000, 0x001, 0x002, 0x003, 0x004, 0x005, 0x006, 0x007,
0x008, 0x009, 0x00A, 0x00B, 0x00C, 0x00D, 0x00E, 0x00F,
0x010, 0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017,
0x018, 0x019, 0x01A, 0x01B, 0x01C, 0x01D, 0x01E, 0x01F,

0x020, 0x024, 0x022, 0x42D, 0x401, 0x42A, 0x42E, 0x027, /*   ! " # $ % & ' */
0x02A, 0x025, 0x419, 0x02B, 0x02C, 0x02D, 0x02E, 0x02F, /* ( ) * + , - . / */
0x030, 0x031, 0x449, 0x44D, 0x451, 0x44A, 0x44C, 0x44E,	/* 0 1 2 3 4 5 6 7 */
0x439, 0x039, 0x03A, 0x03B, 0x03C, 0x03D, 0x03E, 0x03F, /* 8 9 : ; < = > ? */

0x429, 0x410, 0x411, 0x426, 0x414, 0x415, 0x424, 0x413, /* @ A B C D E F G */
0x427, 0x418, 0x416, 0x41A, 0x41B, 0x41C, 0x41D, 0x41E, /* H I J K L M N O */
0x41F, 0x42F, 0x420, 0x421, 0x422, 0x423, 0x412, 0x428, /* P Q R S T U V W */
0x425, 0x42B, 0x417, 0x05B, 0x05C, 0x05D, 0x42C, 0x05F, /* X Y Z [ \ ] ^ _ */

0x023, 0x430, 0x431, 0x446, 0x434, 0x435, 0x444, 0x433, /* ` a b c d e f g */
0x447, 0x438, 0x436, 0x43A, 0x43B, 0x43C, 0x43D, 0x43E, /* h i j k l m n o */
0x43F, 0x44F, 0x440, 0x441, 0x442, 0x443, 0x432, 0x448, /* p q r s t u v w */
0x445, 0x44B, 0x437, 0x026, 0x07C, 0x040, 0x07E, 0x07F  /* x y z { | } ~   */
};

int condev_write(void *buf, int len, VFILE *fd)
{
	fwrite(buf, 1, len, stdout);
	fflush(stdout);
}

int condev_read(void *buf, int len, VFILE *fd)
{
	int i;
/*	if(!con_inbuf)con_inbuf=Sys_ReadLine();
	if(con_inbuf)
	{
		for(i=0; (i<len) && *con_inbuf; i++)
			*(char *)buf++=*con_inbuf++;

		if(!*con_inbuf)con_inbuf=Sys_ReadLine();
		return(i);
	} */

	i=0;
	if(con_char>=0)
	{
		*(char *)buf=con_char;
		con_char=-1;
		buf++;
		len--;
		i++;
	}
	if(len>0)i+=fread(buf, 1, len, stdin);
	return(i);
}

int Text_WriteString(char *s)
{
	printf(s);
}

int condev_inready(VFILE *fd)
{
	int i;

	if(con_char>=0)return(1);
	i=fread(&con_char, 1, 1, stdin);
	if(i)return(1);

	con_char=-1;
	return(0);

#if 0
	int fhnd, stat;
	fd_set rfds;
	struct timeval tv;

	fhnd=0;

	FD_ZERO(&rfds);
	FD_SET(fhnd, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;

	stat=select(1, &rfds, NULL, NULL, &tv);

	stat=1;
	if(stat)return(-1);


//	if(kbhit())return(1);
//	if(!con_inbuf)con_inbuf=Sys_ReadLine();
//	if(con_inbuf)return(-1);
	return(0);
#endif
}

VFILE *condev_open(char *name, void *data)
{
	VFILE *tmp;
	tmp=vfnew();
	tmp->write_proc=condev_write;
	tmp->read_proc=condev_read;
	tmp->inready_proc=condev_inready;
	return(tmp);
}

int keymap_read(void *buf, int len, VFILE *fd)
{
	byte *keymap;

	keymap=Window_GetKeyMap(gfx_screen);

	memcpy(buf, keymap, 32);
	return(32);
}

int keymap_close(VFILE *fd)
{
	vfdestroy(fd);
}

VFILE *keymap_open(char *name, void *data)
{
	VFILE *tmp;

	if(!gfx_screen)return(NULL);

	tmp=vfnew();
//	tmp->write_proc=condev_write;
	tmp->read_proc=keymap_read;
//	tmp->inready_proc=condev_inready;

	return(tmp);
}

static int chkmap(byte *map, int bit)
{
	if(map[bit/8]&(1<<(bit%8)))return(1);
	return(0);
}

#if 0
	if(key>=0x10000)
	{
		con_keybuf[con_keybuf_pos++]=0xF0|(key>>18);
		con_keybuf[con_keybuf_pos++]=0x80|(key>>12)&0x3F;
		con_keybuf[con_keybuf_pos++]=0x80|(key>>6)&0x3F;
		con_keybuf[con_keybuf_pos++]=0x80|key&0x3F;
	}else if(key>=0x800)
	{
		con_keybuf[con_keybuf_pos++]=0xE0|(key>>12);
		con_keybuf[con_keybuf_pos++]=0x80|(key>>6)&0x3F;
		con_keybuf[con_keybuf_pos++]=0x80|key&0x3F;
	}else if(key>=0x80)
	{
		con_keybuf[con_keybuf_pos++]=0xC0|(key>>6);
		con_keybuf[con_keybuf_pos++]=0x80|key&0x3F;
	}else con_keybuf[con_keybuf_pos++]=key;
#endif

int keyb_handler(displaywindow *wnd, int key)
{
	byte *keymap;

	keymap=Window_GetKeyMap(gfx_screen);

	if(chkmap(keymap, K_SHIFT))key=key-'a'+'A';
//	key=keyb_map_us[key];
	key=keyb_map_ru_yasherty[key];

	con_keybuf[con_keybuf_pos++]=key>>8;
	con_keybuf[con_keybuf_pos++]=key&0xff;

	return(0);
}

int keyb_read(void *buf, int len, VFILE *fd)
{
	int i, j;
	char *s;

	s=buf;
	i=len;
	while(i)
	{
		if(con_keybuf_pos)
		{
			*s++=con_keybuf[0];
			for(j=0; j<63; j++)con_keybuf[j]=con_keybuf[j+1];
			con_keybuf_pos--;
			i--;
		}else kthread_blocked();
	}
	return(len);
}

int keyb_inready(VFILE *fd)
{
	if(con_keybuf_pos)return(1);
	return(0);
}

VFILE *keyb_open(char *name, void *data)
{
	VFILE *tmp;

	if(!gfx_screen)return(NULL);
	if(!con_keyb_hnd)con_keyb_hnd=Window_RegisterKeyHandler(&keyb_handler)+1;

	tmp=vfnew();
	tmp->read_proc=keyb_read;
	tmp->inready_proc=keyb_inready;

	return(tmp);
}

int Condev_Init()
{
	Driver_RegisterStream("console", &condev_open, NULL);

	Driver_RegisterStream("keyboard", &keyb_open, NULL);
	Driver_RegisterStream("keyboard/keymap", &keymap_open, NULL);
}
