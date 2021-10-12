#include <general.h>
#include <pdnet.h>

char **httpnode_mime_exts;
char **httpnode_mime_types;

char *httpnode_mime_inittypes[]=
{
	"htm",	"text/html",
	"html",	"text/html",
	"txt",	"text/plain",
	"gif",	"image/gif",
	"png",	"image/png",
	"jpg",	"image/jpeg",
	"jpeg",	"image/jpeg",
	NULL,	NULL
};

char httpnode_mimetable[64]=
	"ABCDEFGHIJKLMNOP"
	"QRSTUVWXYZabcdef"
	"ghijklmnopqrstuv"
	"wxyz0123456789+/";

int HttpNode_EncodeMime(byte *o, byte *i, int sz)
{
	unsigned long v;
	int osz, j;

	osz=0;
	while(sz)
	{
		v=(i[0]<<16)+(i[1]<<8)+i[2];

		j=(sz*4)/3;
		if(j>0)o[0]=httpnode_mimetable[(v>>18)&0x3f];
		if(j>1)o[1]=httpnode_mimetable[(v>>12)&0x3f];
		if(j>2)o[2]=httpnode_mimetable[(v>>6)&0x3f];
		if(j>3)o[3]=httpnode_mimetable[v&0x3f];

		i+=3;
		o+=4;

		j=(sz<3)?sz:3;
		sz-=j;
		osz+=(j*4)/3;
	}

	return(osz);
}

static int mime_conv(int v)
{
	int i;
	for(i=0; i<64; i++)
		if(httpnode_mimetable[i]==v)
			return(i);
	return(0);
}

int HttpNode_DecodeMime(byte *o, byte *i, int sz)
{
	unsigned long v;
	int osz, j;

	osz=0;
	while(sz)
	{
		v=mime_conv(i[0])<<18;
		if(sz>1)v+=mime_conv(i[1])<<12;
		if(sz>2)v+=mime_conv(i[2])<<6;
		if(sz>3)v+=mime_conv(i[3]);

		o[0]=(v>>16)&0xff;
		o[1]=(v>>8)&0xff;
		o[2]=v&0xff;

		i+=4;
		o+=3;

		j=(sz<4)?sz:4;
		sz-=j;
		osz+=(j*3)/4;
	}

	return(osz);
}

char *HttpNode_MimeFromExt(char *ext)
{
	int i;

	kprint("mime from ext %s\n", ext);

	for(i=0; httpnode_mime_exts[i]; i++)
	{
		if(!strcmp(httpnode_mime_exts[i], ext))
			return(httpnode_mime_types[i]);
	}
	return("application/unknown");
}

char *HttpNode_MimeFromName(char *name)
{
	char *s, *t;
	char buf[10];

	s=name+strlen(name);
	while((s>name) && (*s!='.'))s--;
	s++;

	t=buf;
	while(*s)*t++=*s++;
	*t++=0;

	s=HttpNode_MimeFromExt(buf);
	return(s);
}

int HttpNode_MimeInit()
{
	VFILE *fd;
	int i;
	char *s1, *s2;
	char buf1[256], buf2[64], buf3[64];

	kprint("Init MIME Types DB.\n");

	httpnode_mime_exts=kalloc(256*sizeof(char *));
	httpnode_mime_types=kalloc(256*sizeof(char *));

	fd=vffopen("mime.txt", "rt");
	if(!fd)
	{
		for(i=0; httpnode_mime_inittypes[i*2]; i++)
		{
			s1=httpnode_mime_inittypes[i*2];
			s2=httpnode_mime_inittypes[i*2+1];
			httpnode_mime_exts[i]=kstrdup(s1);
			httpnode_mime_types[i]=kstrdup(s2);
		}

		fd=vffopen("mime.txt", "wt");

		for(i=0; httpnode_mime_inittypes[i*2]; i++)
		{
			s1=httpnode_mime_inittypes[i*2];
			s2=httpnode_mime_inittypes[i*2+1];
			kprints(buf1, "%s\t%s\n", s1, s2);
			vfwrite(buf1, 1, strlen(buf1), fd);
		}

		vfclose(fd);
	}else
	{
		i=0;
		while(!vfeof(fd))
		{
			memset(buf1, 0, 256);
			vfgets(buf1, 255, fd);
			if(!buf1[0] || (buf1[0]=='\n'))continue;

//			sscanf(buf1, "%s %s", buf2, buf3);
			s1=buf1;
			while(*s1 && (*s1<=' '))s1++;

			s2=buf2;
			while(*s1 && (*s1>' '))*s2++=*s1++;

			while(*s1 && (*s1<=' '))s1++;

			s2=buf3;
			while(*s1 && (*s1>' '))*s2++=*s1++;

			httpnode_mime_exts[i]=kstrdup(buf2);
			httpnode_mime_types[i]=kstrdup(buf3);
			i++;
		}
		httpnode_mime_exts[i]=NULL;
		httpnode_mime_types[i]=NULL;

		vfclose(fd);
	}

	return(0);
}
