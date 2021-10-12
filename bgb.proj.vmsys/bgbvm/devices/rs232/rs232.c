#include <general.h>
#include <x86/io.h>
#include <x86/desc.h>
#include <x86/irq.h>

int rs232_nums[4]={0, 1, 2, 3};

int rs232_ports[4]={0x3f8, 0x2f8, 0x3e8, 0x2e8};

#if 0
typedef struct {
byte *data;
int start, end;
}circbuf;
#endif

circbuf *rs232_inbuf[4];
circbuf *rs232_outbuf[4];

#if 0
circbuf *circbuf_new()
{
	circbuf *tmp;
	tmp=kalloc(sizeof(circbuf));
	tmp->data=kalloc(4096);
	tmp->start=0;
	tmp->end=0;
}

int circbuf_add(circbuf *buf, int v)
{
	buf->data[buf->end++]=v;
	buf->end&=0xfff;
	if(buf->start==buf->end)
	{
		buf->end--;
		return(-1);
	}
	buf->end&=0xfff;
	return(0);
}

int circbuf_get(circbuf *buf)
{
	int v;
	if(buf->start==buf->end)return(-1);
	v=buf->data[buf->start++];
	buf->start&=0xfff;
	return(v);
}

int circbuf_emptyp(circbuf *buf)
{
	if(buf->start==buf->end)return(1);
	return(0);
}
#endif


int rs232_setbaud(int port, int baud)
{
	int div, s;
	switch(baud)
	{
	case 115200:
		div=0x01;
		break;
	case 57600:
		div=0x02;
		break;
	case 38400:
		div=0x03;
		break;
	case 28800:
		div=0x04;
		break;
	case 19200:
		div=0x06;
		break;
	case 9600:
		div=0x0c;
		break;
	case 4800:
		div=0x18;
		break;
	case 2400:
		div=0x30;
		break;
	case 1200:
		div=0x60;
		break;
	case 300:
		div=0x180;
		break;
	default:
		div=0x0c;
		break;
	}
	outportb(port+3, 0x80);

	outportb(port+0, div);
	outportb(port+1, 0);

	outportb(port+3, 0x03);

	return(0);
}

int rs232_initdef(int port)
{
	char *s;

	outportb(port+1, 0x00);	//disable ints

	rs232_setbaud(port, 57600); //9600

	outportb(port+3, 3);	//8 data bits, 1 stop bits, non-parity
	outportb(port+2, 0xc7);	//fifo, 14byte, clear trans, clear recv, enable
	outportb(port+4, 0x0b);	//dtr, rts, out2
	outportb(port+1, 0x0d);	//0x0d, int on data recieved, modem or line status change

	inportb(port);	//read
}

int rs232_handler()
{
	int i, j, k;

//	kprint("rs232 int.\n");

	for(i=0; i<4; i++)
	{
		j=inportb(rs232_ports[i]+2); //interrupt id
		while(!(j&1))
		{
			switch((j>>1)&3)
			{
			case 0:
//				kprint("modem status.\n");
				j=inportb(rs232_ports[i]+6); //modem status
				break;
			case 1:	//transmitter empty
//				kprint("transmitter empty.\n");
				if(!circbuf_emptyp(rs232_outbuf[i])) //data in output buffer?
				{
					outportb(rs232_ports[i], circbuf_get(rs232_outbuf[i]));
				}else
				{
					j=inportb(rs232_ports[i]+1); //int enable reg
					j&=~2;	//clear transmit empty int
					outportb(rs232_ports[i]+1, j);
				}
				break;
			case 2:	//char available
				k=inportb(rs232_ports[i]);
				circbuf_add(rs232_inbuf[i], k);

//				kprint("rs232 %d, got %d\n", i, k);
				break;
			case 3:
				j=inportb(rs232_ports[i]+5); //line status
				kprint("rs232 %d error %X.\n", i, j);
				break;
			default:
				break;
			}
			j=inportb(rs232_ports[i]+2); //interrupt id
		}
	}
}


int serial_write(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;

//	asm("cli\n");

	s=buf;
	i=*(int *)fd->buffer;
	for(j=0; j<len; j++)
		while(circbuf_add(rs232_outbuf[i], s[j]))kthread_blocked();

	//enable transmit buffer empty int
	k=inportb(rs232_ports[i]+1); //int enable reg
	k|=2;
	outportb(rs232_ports[i]+1, k);

//	asm("sti\n");

	return(j);
}

int serial_read(void *buf, int len, VFILE *fd)
{
	int i, j, k;
	byte *s;

//	asm("cli\n");

	s=buf;
	i=*(int *)fd->buffer;
	for(j=0; j<len; j++)
	{
		k=-1;
		while(1)
		{
			k=circbuf_get(rs232_inbuf[i]);
			if(k>=0)break;
			kthread_blocked();
		}
		s[j]=k;
	}

//	asm("sti\n");

	return(j);
}

int serial_inready(VFILE *fd)
{
	int i, j;

	i=*(int *)fd->buffer;
	if(!circbuf_emptyp(rs232_inbuf[i]))
	{
//		kprint("serial_inready: y\n");
		return(1);
	}
//	kprint("serial_inready: n\n");
//	kprint("N");
	return(0);
}

int serial_ioctls(VFILE *fd, void **arg)
{
	char *s, *t;
	int i, j;

	i=*(int *)fd->buffer;

	s=*arg;
	if(!strcmp(s, "set-baud"))
	{
		j=(int)arg[1];
		kprint("rs232 %d: set baud %d\n", i, j);
		rs232_setbaud(rs232_ports[i], j);
		return(0);
	}
	if(!strcmp(s, "set-mode"))
	{
		t=(char *)arg[1];
		j=0;
		switch(t[0])
		{
		case '8':
			j|=0x03;
			break;
		case '7':
			j|=0x02;
			break;
		case '6':
			j|=0x01;
			break;
		case '5':
			j|=0x00;
			break;
		default:	//default 8
			j|=0x03;
			break;
		}
		switch(t[1])
		{
		case 'O':
			j|=0x08;
			break;
		case 'E':
			j|=0x18;
			break;
		default:
			break;
		}
		switch(t[2])
		{
		case '2':
			j|=0x04;
			break;
		defualt:
			break;
		}

		outportb(rs232_ports[i]+3, j);	//line control reg
	}

	return(-1);
}


VFILE *serial_open(char *name, void *data)
{
	VFILE *tmp;

	tmp=vfnew();
	tmp->buffer=data;

	tmp->write_proc=serial_write;
	tmp->read_proc=serial_read;
	tmp->inready_proc=serial_inready;
	tmp->ioctls_proc=serial_ioctls;

	return(tmp);
}

extern int rs232_isr();

int Serial_Init()
{
	int i;
	VFILE *vfd;

	kprint("serial init.\n");

	for(i=0; i<4; i++)
	{
		rs232_inbuf[i]=circbuf_new();
		rs232_outbuf[i]=circbuf_new();

		rs232_initdef(rs232_ports[i]);
	}

//	rs232_initdef(rs232_ports[0]);

	NewIntISR(&rs232_isr,0x23,0);
	enable_irq(3);
	NewIntISR(&rs232_isr,0x24,0);
	enable_irq(4);

	Driver_RegisterStream("serial/0", &serial_open, &rs232_nums[0]);
	Driver_RegisterStream("serial/1", &serial_open, &rs232_nums[1]);
	Driver_RegisterStream("serial/2", &serial_open, &rs232_nums[2]);
	Driver_RegisterStream("serial/3", &serial_open, &rs232_nums[3]);

//	vfd=serial_open("serial/0", &rs232_nums[0]);
//	vfwrite("kernel test\n\n", 1, 13, vfd);
}
