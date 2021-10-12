int text_x,text_y;
int text_xs,text_ys;
int text_color;
char *text_buffer;

int text_sr_top, text_sr_bottom;

int text_inited=0;

static char rchar; /* used for bold character detection */
//extern int is_graphics;

int Text_Init()
{
	if(text_inited)return(0);
	text_inited=1;

	/* assuming here */
	text_buffer=(char *)0xB8000;
	text_xs=80;
	text_ys=25;
	text_x=*((char *)0x450);
	text_y=*((char *)0x451);
	text_color=7;
	rchar=-1;

	text_sr_top=0;
	text_sr_bottom=text_ys;
	
//	is_graphics=0;
}

int Text_ScrollUp()
{
	Text_ScrollUpP(text_sr_top, text_sr_bottom-text_sr_top);

#if 0
	int i,v;
	for(i=0;i<text_ys;i++)for(v=0;v<text_xs;v++)
	{
		text_buffer[((i*text_xs)+v)*2]=
			text_buffer[(((i+1)*text_xs)+v)*2];
		text_buffer[((i*text_xs)+v)*2+1]=
			text_buffer[(((i+1)*text_xs)+v)*2+1];
	}
	for(v=0;v<text_xs;v++)
	{
		text_buffer[(((text_ys-1)*text_xs)+v)*2]=' ';
		text_buffer[(((text_ys-1)*text_xs)+v)*2+1]=7;
	}
#endif
}

int Text_ScrollUpP(int y, int h)
{
	int i,v;
	for(i=y;i<(y+h);i++)for(v=0;v<text_xs;v++)
	{
		text_buffer[((i*text_xs)+v)*2]=
			text_buffer[(((i+1)*text_xs)+v)*2];
		text_buffer[((i*text_xs)+v)*2+1]=
			text_buffer[(((i+1)*text_xs)+v)*2+1];
	}
	for(v=0;v<text_xs;v++)
	{
		text_buffer[((((y+h)-1)*text_xs)+v)*2]=' ';
		text_buffer[((((y+h)-1)*text_xs)+v)*2+1]=7;
	}
}

int Text_ScrollDown()
{
	Text_ScrollDownP(text_sr_top, text_sr_bottom-text_sr_top);

#if 0
	int i,v;
	for(i=0;i<text_ys;i++)for(v=0;v<text_xs;v++)
	{
		text_buffer[(((text_ys-i)*text_xs)+v)*2]=
			text_buffer[(((text_ys-(i+1))*text_xs)+v)*2];
		text_buffer[(((text_ys-i)*text_xs)+v)*2+1]=
			text_buffer[(((text_ys-(i+1))*text_xs)+v)*2+1];
	}
	for(v=0;v<text_xs;v++)
	{
		text_buffer[v*2]=' ';
		text_buffer[v*2+1]=7;
	}
#endif
}

int Text_ScrollDownP(int y, int h)
{
	int i, v;
	for(i=0;i<h;i++)for(v=0;v<text_xs;v++)
	{
		text_buffer[((((y+h)-i)*text_xs)+v)*2]=
			text_buffer[((((y+h)-(i+1))*text_xs)+v)*2];
		text_buffer[((((y+h)-i)*text_xs)+v)*2+1]=
			text_buffer[((((y+h)-(i+1))*text_xs)+v)*2+1];
	}
	for(v=0;v<text_xs;v++)
	{
		text_buffer[((y*text_xs)+v)*2]=' ';
		text_buffer[((y*text_xs)+v)*2+1]=7;
	}
}

int text_ansi, text_ansi2;
int ansi_stack[16], ansi_stackpos, ansi_arg;

int ansi_curstack[8][2], ansi_curstackpos;

int Text_WAnsi2(char c)
{
	int i;

	if((c>='0') && (c<='9'))
	{
		ansi_arg=(ansi_arg*10)+(c-'0');
		return(0);
	}
	if(c==';')
	{
		ansi_stack[ansi_stackpos++]=ansi_arg;
		ansi_arg=0;
		return(0);
	}

	switch (c)
	{
	case 'A':	//up
		if(!ansi_arg)ansi_arg=1;
		text_y-=ansi_arg;
		if(text_y<0)text_y=0;
		break;

	case 'e':	//cursor down
	case 'B':	//down
		if(!ansi_arg)ansi_arg=1;
		text_y+=ansi_arg;
		if(text_y>=text_ys)text_y=text_ys-1;
		break;
	case 'C':	//right
		if(!ansi_arg)ansi_arg=1;
		text_x+=ansi_arg;
		if(text_x>=text_xs)text_x=text_xs-1;
		break;
	case 'D':	//left
		if(!ansi_arg)ansi_arg=1;
		text_x-=ansi_arg;
		if(text_x<0)text_x=0;
		break;

	case 'f':	//'row;columnf': set active pos, or 'f' move active home
	case 'H':	//'row;columnH': move, or 'H' move home
		ansi_stack[ansi_stackpos++]=ansi_arg;
		if(ansi_stackpos==2)Text_SetPos(ansi_stack[1]-1, text_sr_top+ansi_stack[0]-1);
			else Text_SetPos(0, text_sr_top);
		break;

	case 'J':	//clear screen
		switch(ansi_arg)
		{
		case 0:
			for(i=((text_y*text_xs)+text_x); i<(text_xs*text_sr_bottom); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		case 1:
			for(i=(text_xs*text_sr_top); i<=((text_y*text_xs)+text_x); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		case 2:
			for(i=(text_xs*text_sr_top); i<(text_xs*text_sr_bottom); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		default:
			break;
		}
		break;

	case 'K':	//clear line
		switch(ansi_arg)
		{
		case 0:
			for(i=(text_y*text_xs)+text_x; i<((text_y*text_xs)+text_xs); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		case 1:
			for(i=(text_y*text_xs); i<=((text_y*text_xs)+text_x); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		case 2:
			for(i=(text_y*text_xs); i<((text_y*text_xs)+text_xs); i++)
			{
				text_buffer[i*2]=' ';
				text_buffer[i*2+1]=7;
			}
			break;
		default:
			break;
		}
		break;

	case 'L':	//insert lines
		if(!ansi_arg)ansi_arg=1;
		for(i=0; i<ansi_arg; i++)
			Text_ScrollDownP(text_y, text_sr_bottom-text_y);
		break;
	case 'M':	//delete lines
		if(!ansi_arg)ansi_arg=1;
		for(i=0; i<ansi_arg; i++)
			Text_ScrollUpP(text_y, text_sr_bottom-text_y);
		break;

	case 'd':	//move to row
		if(!ansi_arg)ansi_arg=1;
		text_y=ansi_arg-1;
		break;

	case '`':	//move to row
		if(!ansi_arg)ansi_arg=1;
		text_x=ansi_arg-1;
		break;

	case 'h':	//set mode
		break;
	case 'l':	//unset mode
		break;

	case 'm':	//attributes
		ansi_stack[ansi_stackpos++]=ansi_arg;
		for(i=0; i<ansi_stackpos; i++)
			switch(ansi_stack[i])
		{
		case 0:
			text_color=7;
			break;
		case 1:
			text_color|=0x8;
			break;
		case 5:
			text_color|=0x80;
			break;
		case 7:
			text_color&=~0x77;
			text_color|=0x70;
			break;

		case 30: //fg black
			text_color&=~0x07;
			text_color|=0x00;
			break;
		case 31: //fg red
			text_color&=~0x07;
			text_color|=0x04;
			break;
		case 32: //fg green
			text_color&=~0x07;
			text_color|=0x02;
			break;
		case 33: //fg yellow
			text_color&=~0x07;
			text_color|=0x06;
			break;
		case 34: //fg blue
			text_color&=~0x07;
			text_color|=0x01;
			break;
		case 35: //fg magenta
			text_color&=~0x07;
			text_color|=0x05;
			break;
		case 36: //fg cyan
			text_color&=~0x07;
			text_color|=0x03;
			break;
		case 37: //fg white
			text_color&=~0x07;
			text_color|=0x07;
			break;

		case 40: //bg black
			text_color&=~0x70;
			text_color|=0x00;
			break;
		case 41: //bg red
			text_color&=~0x70;
			text_color|=0x40;
			break;
		case 42: //bg green
			text_color&=~0x70;
			text_color|=0x20;
			break;
		case 43: //bg yellow
			text_color&=~0x70;
			text_color|=0x60;
			break;
		case 44: //bg blue
			text_color&=~0x70;
			text_color|=0x10;
			break;
		case 45: //bg magenta
			text_color&=~0x70;
			text_color|=0x50;
			break;
		case 46: //bg cyan
			text_color&=~0x70;
			text_color|=0x30;
			break;
		case 47: //bg white
			text_color&=~0x70;
			text_color|=0x70;
			break;

		default:
			break;
		}
		break;

	case 'r':	//set scroll region
		ansi_stack[ansi_stackpos++]=ansi_arg;

		text_sr_top=ansi_stack[0]-1;
		text_sr_bottom=ansi_stack[1]-1;
		break;

	case 's':	//save cursor position
		ansi_curstack[ansi_curstackpos][0]=text_x;
		ansi_curstack[ansi_curstackpos][1]=text_y;
		ansi_curstackpos++;
		break;
	case 'u':	//restore cursor position
		ansi_curstackpos--;
		text_x=ansi_curstack[ansi_curstackpos][0];
		text_y=ansi_curstack[ansi_curstackpos][1];
		break;

	default:
//		text_ansi=0;
//		text_ansi2=0;
//		kprint("\nunknown [ ansi code %c\n", c);

		break;
	}

	Text_SetCur(text_x, text_y);
	text_ansi=0;
	text_ansi2=0;
	return(0);
}

int Text_WAnsi(char c)
{
	int i;

	if(text_ansi2)return(Text_WAnsi2(c));

	if(c=='[')
	{
		ansi_stackpos=0;
		text_ansi2=1;
		ansi_arg=0;
		return(0);
	}

	switch (c)
	{
	case 'D':	//down
		text_y++;
		if(text_y>=text_ys)
		{
			Text_ScrollUp();
			text_y=text_ys-1;
		}
		break;
	case 'E':	//down left
		text_x=0;
		text_y++;
		if(text_y>=text_ys)
		{
			Text_ScrollUp();
			text_y=text_ys-1;
		}
		break;
	case 'M':	//up
		text_y--;
		if(text_y<0)
		{
			Text_ScrollDown();
			text_y=0;
		}
		break;

	case 'c':	//reset all
		for(i=0; i<(text_xs*text_ys); i++)
		{
			text_buffer[i*2]=' ';
			text_buffer[i*2+1]=7;
		}
		Text_SetPos(0, 0);
		text_color=7;
		break;

	default:
//		text_ansi=0;
//		text_ansi2=0;
//		kprint("\nunknown non-[ ansi code %c\n", c);
		break;
	}

	Text_SetCur(text_x, text_y);
	text_ansi=0;
	text_ansi2=0;
	return(0);
}

int Text_WChar(char c)
{
	if(text_ansi)return(Text_WAnsi(c));

	if(c<' ')
	{
		switch(c)
		{
		case 0x1B:
			text_ansi=1;
			break;

		case 0x0D:
			text_x=0;
			break;
			
		case 0x0A:
			text_y++;
			text_x=0;
			if(text_y>=(text_ys-1))
			{
				Text_ScrollUp();
				text_y--;
			}
			break;
			
		case 0x08:
			text_x--;
			if(text_x<0)text_x=0;
			rchar=text_buffer[((text_y*text_xs)+text_x)*2];
			text_buffer[((text_y*text_xs)+text_x)*2]=' ';
			break;

		case '\t':
			text_x+=8;
			text_x&=~7;
			break;

		default:
			break;
		}
	}
	else
	{
		text_buffer[((text_y*text_xs)+text_x)*2]=c;
		text_buffer[((text_y*text_xs)+text_x)*2+1]=text_color;
		if(c==rchar)text_buffer[((text_y*text_xs)+text_x)*2+1]|=8;
		rchar=-1;
		text_x++;

		if(text_x>=text_xs)
		{
			text_x=0;
			text_y++;
			if(text_y>=text_ys)
			{
				Text_ScrollUp();
				text_y--;
			}
		}
	}
	Text_SetCur(text_x, text_y);
}

int Text_WriteString(char *s)
{
	int p;
	while(*s)
	{
		Text_WChar(*s);
		s++;
	}
	/* move hardware cursor pos */
	p=text_y*text_xs+text_x;
	outportb(0x3D4,0x0F);
	outportb(0x3D5,p&0xFF);
	outportb(0x3D4,0x0E);
	outportb(0x3D5,p>>8);

//	*((char *)0x450)=text_x;
//	*((char *)0x451)=text_y;
}

int Text_SetPos(int x,int y)
{
	int p;

	text_x=x;
	text_y=y;
//	if(!is_graphics)
	if(1)
	{
		p=text_y*text_xs+text_x;
		outportb(0x3D4,0x0F);
		outportb(0x3D5,p&0xFF);
		outportb(0x3D4,0x0E);
		outportb(0x3D5,p>>8);
	}

//	*((char *)0x450)=text_x;
//	*((char *)0x451)=text_y;
}

int Text_SetCur(int x,int y)
{
	int p;

//	if(!is_graphics)
	if(1)
	{
		p=text_y*text_xs+text_x;
		outportb(0x3D4,0x0F);
		outportb(0x3D5,p&0xFF);
		outportb(0x3D4,0x0E);
		outportb(0x3D5,(p>>8)&0xFF);
	}
//	*((char *)0x450)=text_x;
//	*((char *)0x451)=text_y;
}

int Text_WriteLong(long p)
{
	char stk[11],pos,sign;
	pos=0;
	sign=0;
	if(p<0)
	{
		p=(~p)+1;
		sign=1;
	}
	if(!p)
	{
		stk[pos]='0';
		pos++;
	}
	while(p)
	{
		stk[pos]='0'+(p%10);
		pos++;
		p/=10;
	}
	if(sign)
	{
		stk[pos]='-';
		pos++;
	}
	while(pos)
	{
		pos--;
		Text_WChar(stk[pos]);
	}
//	Text_SetPos(text_x,text_y);
}

int Text_WriteLongN(long p,int n)
{
	char stk[11],pos,sign;
	pos=0;
	sign=0;
	if(p<0)
	{
		p=(~p)+1;
		sign=1;
	}
	for(pos=0;pos<n;pos++)
	{
		stk[pos]='0'+(p%10);
		p/=10;
	}
	while(pos)
	{
		pos--;
		Text_WChar(stk[pos]);
	}
}
