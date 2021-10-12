#include <pdlib.h>
#include <pdnet.h>

Meta0_PortInfo *mrpt_inf;

MRPT_TagInfo **mrpt_tags;

int MRPT_SizeVLI(int v)
{
	int i, j;

	i=v;
	j=0;

	while((i && (i!=-1)) || !j)
	{
		j++;
		i>>=7;
	}
	return(j);
}

int MRPT_WriteBaseTag(Meta0_Con *con, int num, int len, byte *v)
{
	byte buf[16];
	byte *s, *t;

	s=buf;
	t=s;

	t=mrpt_write_vli(t, num);
	t=mrpt_write_vli(t, len);

	kprint("MRPT_WriteBaseTag: %d %d, %X %X\n", num, len, s[0], s[1]);

	vfwrite(s, 1, t-s, con->sock);
	if(len)vfwrite(v, 1, len, con->sock);

	return(0);
}

int MRPT_WriteNegStr(Meta0_Con *con, char *str)
{
	MRPT_WriteBaseTag(con, 1, strlen(str), str);
	return(0);
}

int MRPT_WriteTagInfo(Meta0_Con *con, MRPT_TagInfo *tag)
{
	byte buf[256];
	byte *s;

	s=buf;

	*s++=(tag->flags>>8)&0xff;
	*s++=tag->flags&0xff;

	*s++=(tag->tag>>8)&0xff;
	*s++=tag->tag&0xff;

	*s++=tag->len;
	*s++=tag->class;

	*s++=0;
	*s++=0;

	strcpy(s, tag->name);
	s+=strlen(tag->name);

	MRPT_WriteBaseTag(con, 2, s-buf, buf);

	return(0);
}

int MRPT_WriteTag(Meta0_Con *con, MRPT_TagInfo *tag, int len, byte *v)
{
	byte buf[16];
	byte *s, *t;

	s=buf;
	t=s;

	t=mrpt_write_vli(t, tag->tag);
	if(!(tag->flags&MRPT_FLAG_FIXEDLENGTH))
	{
		t=mrpt_write_vli(t, len);
	}else
	{
		if(len && (len!=tag->len))
			kprint("MRPT_WriteTag: incorrect length for "
				"fixed-length tag '%s'\n", tag->name);
		len=tag->len;
	}

	vfwrite(t, 1, t-s, con->sock);
	if(len)vfwrite(v, 1, len, con->sock);

	return(0);
}

int MRPT_EncodeTag(Meta0_Con *con, MRPT_TagInfo *tag, int *sz, byte **v)
{
	byte buf[16];
	byte *s, *t;
	int len;

	len=*sz;

	if(tag->flags&MRPT_FLAG_FIXEDLENGTH)
	{
		if(len && (len!=tag->len))
			kprint("MRPT_WriteTag: incorrect length for "
				"fixed-length tag '%s'\n", tag->name);
		len=tag->len;
	}

	s=kalloc(len+16);
	t=s;

	t=mrpt_write_vli(t, tag->tag);
	if(!(tag->flags&MRPT_FLAG_FIXEDLENGTH))
	{
		t=mrpt_write_vli(t, len);
	}

	memcpy(t, *v, len);

	*sz=(t-s)+len;
	*v=s;

	return(0);
}

MRPT_TagInfo *MRPT_DeclareTag(char *name, int flags, int len, int class)
{
	int i;
	MRPT_TagInfo *ti;

	for(i=32; i<MRPT_MAX_TAGS; i++)
		if(mrpt_tags[i])
	{
		ti=mrpt_tags[i];
		if(!strcmp(ti->name, name))
		{
			if((ti->flags!=flags) || (ti->len!=len))
			{
				kprint("MRPT_DeclareTag: incompatible "
					"redefinition of tag '%s'\n",
					ti->name);
				return(NULL);
			}
			kprint("MRPT_DeclareTag: redefinition of tag '%s'\n",
				ti->name);
			return(ti);
		}
	}else
	{
		kprint("MRPT_DeclareTag: Define tag '%s' %d\n", name, i);

		ti=kalloc(sizeof(MRPT_TagInfo));
		ti->name=kstrdup(name);
		ti->tag=i;

		ti->flags=flags;
		ti->len=len;
		ti->class=class;

		mrpt_tags[i]=ti;
		return(ti);
	}
	kprint("MRPT_DeclareTag: failed to define tag '%s'\n", name);
	return(NULL);
}

MRPT_TagInfo *MRPT_LookupTag(char *name)
{
	int i;
	MRPT_TagInfo *ti;

	for(i=0; i<MRPT_MAX_TAGS; i++)if(mrpt_tags[i])
	{
		ti=mrpt_tags[i];
		if(!strcmp(ti->name, name))
			return(ti);
	}
	return(NULL);
}

Meta0_Con *MRPT_Connect(char *host)
{
	Meta0_Con *con;
	VADDR *addr;
	MRPT_ConInfo *ri;
	int i;

	addr=NET_DecodeHostname(host);
	if(!addr)
	{
		kprint("MRPT: Unknown host %s\n", host);
		return(NULL);
	}
	switch(addr->proto)
	{
	case PROTO_IPV4:
	case PROTO_IPV4UDP:
	case PROTO_IPV4TCP:
		if(!addr->ipv4.port)
			addr->ipv4.port=htons(7938);
		break;
	case PROTO_IPV6:
	case PROTO_IPV6UDP:
	case PROTO_IPV6TCP:
		if(!addr->ipv6.port)
			addr->ipv6.port=htons(7938);
		break;
	default:
		break;
	}

	con=Meta0_Connect(mrpt_inf, addr);

	if(!con)
	{
		kprint("MRPT: Connection failed.\n");
		return(-1);
	}

	ri=kalloc(sizeof(MRPT_ConInfo));
	con->data=ri;

	ri->flags=0;
	ri->tags=kalloc(MRPT_MAX_TAGS*sizeof(MRPT_TagInfo *));
	memset(ri->tags, 0, MRPT_MAX_TAGS*sizeof(MRPT_TagInfo *));

	MRPT_WriteNegStr(con, "?MRPT");

	for(i=0; i<MRPT_MAX_TAGS; i++)
		if(mrpt_tags[i])
	{
		MRPT_WriteTagInfo(con, mrpt_tags[i]);
	}

	return(con);
}

int MRPT_HandleMessage(Meta0_Con *con, MRPT_TLV *tlv)
{
	kprint("MRPT_HandleMessage:: ");
	MRPT_DumpTLV(tlv);
	kprint("\n");
}
