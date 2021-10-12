#include <general.h>

unsigned char *cc15to8;
extern unsigned char *palette;

int CCT_FindColor(int r,int g,int b)
{
	int rd,gd,bd,d;
	int cd,cc,i;
	cd=769;
	cc=0;
	for(i=0;i<256;i++)
	{
		rd=(int)palette[i*3]-r;
		gd=(int)palette[i*3+1]-g;
		bd=(int)palette[i*3+2]-b;
		if(rd<0)rd=0-rd;
		if(gd<0)gd=0-gd;
		if(bd<0)bd=0-bd;
		d=rd+gd+bd;
		if(d<cd)
		{
			cd=d;
			cc=i;
		}
	}
	return(cc);
}

void CCT_GenCCT()
{
	int r,g,b;
	kprint("<          >\r<");
	for(b=0;b<32;b++)for(g=0;g<32;g++)for(r=0;r<32;r++)
	{
		cc15to8[(b*1024)+(g*32)+r]=CCT_FindColor(r*8,g*8,b*8);
		if(!(((b*1024)+(g*32)+r)%3277))kprint(".");
	}
	kprint("\n");
}

int CCT_Init()
{
	kprint("Color conversion table init.\n");
	cc15to8=kalloc(32768);
	CCT_GenCCT();
}
