#include <general.h>

byte con_inbuf[32];
int con_inpos;

extern byte keyboard_keymask[32];
//extern int keyboard_nokeybuf;
int con_nocondev;

int condev_write(void *buf, int len, VFILE *fd)
{
	char *s;
	int i;

	if(con_nocondev)return(0);

	s=buf;
	for(i=0; i<len; i++)
		Text_WChar(s[i]);
	return(len);
}

int condev_read(void *buf, int len, VFILE *fd)
{
	int i, j;
	char *s;

	if(con_nocondev)return(0);

	s=buf;
	i=len;
	while(i)
	{
		if(!con_inpos)
		{
			j=getch();
			if(!j)
			{
				j=getch();
				switch(j)
				{
				case 0x48:	//up
					con_inbuf[con_inpos++]='A';
					con_inbuf[con_inpos++]='[';
					con_inbuf[con_inpos++]=0x1B;
					break;
				case 0x50:
					con_inbuf[con_inpos++]='B';
					con_inbuf[con_inpos++]='[';
					con_inbuf[con_inpos++]=0x1B;
					break;
				case 0x4D:
					con_inbuf[con_inpos++]='C';
					con_inbuf[con_inpos++]='[';
					con_inbuf[con_inpos++]=0x1B;
					break;
				case 0x4B:
					con_inbuf[con_inpos++]='D';
					con_inbuf[con_inpos++]='[';
					con_inbuf[con_inpos++]=0x1B;
					break;

				default:
					break;
				}
				continue;
			}else *s++=j;
		}else *s++=con_inbuf[--con_inpos];
		i--;
	}
	return(len);
}

int condev_inready(VFILE *fd)
{
	if(con_nocondev)return(0);
	if(kbhit() | con_inpos)return(1);
	return(0);
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
	memcpy(buf, keyboard_keymask, 32);
	return(32);
}

VFILE *keymap_open(char *name, void *data)
{
	VFILE *tmp;
	tmp=vfnew();
//	tmp->write_proc=condev_write;
	tmp->read_proc=keymap_read;
//	tmp->inready_proc=condev_inready;

//	keyboard_nokeybuf++;

	return(tmp);
}

int keyb_read(void *buf, int len, VFILE *fd)
{
	int i, j;
	char *s;
	static int l=-1;

	s=buf;
	i=len;
	while(i)
	{
		if(l<0)
		{
			j=getch();
			*s++=j;
			l=0;
			i--;
		}else
		{
			*s++=l;
			i--;
			l=-1;
		}
	}
	return(len);
}

int keyb_inready(VFILE *fd)
{
	if(kbhit())return(1);
	return(0);
}

int keyb_close(VFILE *fd)
{
	if(con_nocondev)con_nocondev--;
	vfdestroy(fd);
}

VFILE *keyb_open(char *name, void *data)
{
	VFILE *tmp;
	tmp=vfnew();
	tmp->read_proc=keyb_read;
	tmp->inready_proc=keyb_inready;
	tmp->close_proc=keyb_close;

	con_nocondev++;

	return(tmp);
}

int Condev_Init()
{
	Text_Init();
//	kprint("M1\n");
	Init_Keyboard();
//	kprint("M2\n");
	Driver_RegisterStream("console", &condev_open, NULL);

	Driver_RegisterStream("keyboard", &keyb_open, NULL);
	Driver_RegisterStream("keyboard/keymap", &keymap_open, NULL);
//	kprint("M3\n");
}
