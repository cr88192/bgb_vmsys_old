#include <pdlib.h>
#include <pdnet.h>

Meta0_PortInfo *mrpt_inf;

MRPT_TagInfo **mrpt_tags;


int mrpt_read_vli(byte **s, byte *e)
{
	int i;
	byte *t;

	t=*s;
	i=0;
	while(1)
	{
		if(t>=e)return(-1);
		i=(i<<7)+(*t&0x7f);
		if(!(*t&0x80))
		{
			t++;
			break;
		}
		t++;
	}

	*s=t;
	return(i);
}

byte *mrpt_write_vli(byte *s, int v)
{
	int i;
	byte *t, *e;
	byte buf[10];

	t=buf+10;
	e=t;

	i=v;
	while((i && (i!=-1)) || (t==e))
	{
		t--;
		*t=i&0x7f;
		if((e-t)>1)*t|=0x80;
		i>>=7;
	}

	while(t<e)*s++=*t++;

	return(s);
}

int mrpt_newcon(Meta0_Con *con)
{
	MRPT_ConInfo *ri;
	int i;

	kprint("MRPT Recieve Connection\n");

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

	return(0);
}

int mrpt_closed(Meta0_Con *con)
{
	MRPT_ConInfo *ri;

	ri=con->data;
	return(0);
}

MRPT_TLV *mrpt_decode(Meta0_Con *con, int tag, byte *buf, byte *end)
{
	byte *s, *t, *e, *t2, *t3;
	int i, j;
	MRPT_ConInfo *ri;
	MRPT_TLV *tlv, *lst, *le;
	MRPT_TagInfo *ti;

	s=buf;
	t=s;
	e=end;

	ri=con->data;
	lst=NULL;
	le=NULL;

	ti=ri->tags[tag];
	if(!(ti->flags&MRPT_FLAG_COMPOUND))
	{
		tlv=kalloc(sizeof(MRPT_TLV));

		tlv->next=NULL;
		tlv->first=NULL;
		tlv->tag=ti;
		tlv->len=end-buf;
		tlv->data=buf;

		return(tlv);
	}

	while(1)
	{
		if(t>=e)break;

		t2=t;
		i=mrpt_read_vli(&t2, e);
		if(t==t2)break;
		t=t2;

		ti=ri->tags[i];
		if(!ti)
		{
			kprint("MRPT: Undeclared tag %d\n", i);
			return(NULL);
		}

		if(!(ti->flags&MRPT_FLAG_FIXEDLENGTH))
		{
			j=mrpt_read_vli(&t2, e);
			if(t==t2)break;
			t=t2;
		}else j=ti->len;

		if(j)
		{
			t3=kalloc(j);
			memcpy(t3, t, j);

			t+=j;

			tlv=mrpt_decode(con, i, t3, t3+j);

			if(!lst)
			{
				lst=tlv;
				le=tlv;
			}else
			{
				le->next=tlv;
				le=tlv;
			}
		}else
		{
			//handle
			tlv=kalloc(sizeof(MRPT_TLV));
			tlv->next=NULL;
			tlv->first=NULL;
			tlv->tag=ti;
			tlv->len=0;
			tlv->data=NULL;

			if(!lst)
			{
				lst=tlv;
				le=tlv;
			}else
			{
				le->next=tlv;
				le=tlv;
			}
		}
	}

	kfree(buf);

	ti=ri->tags[tag];
	tlv=kalloc(sizeof(MRPT_TLV));

	tlv->next=NULL;
	tlv->first=lst;
	tlv->tag=ti;
	tlv->len=0;
	tlv->data=NULL;

	return(tlv);
}

int mrpt_handle_neg_req(Meta0_Con *con, char *var)
{
	if(!strcmp(var, "MRPT"))
	{
		MRPT_WriteNegStr(con, "=MRPT 0.2.2");
	}

	return(0);
}

int mrpt_handle_neg_dec(Meta0_Con *con, char *var)
{
	return(0);
}

int mrpt_handle_negstr(Meta0_Con *con, char *str)
{
	char tb[16][64];
	char *s, *t;
	int i;

	s=str+1;
	i=0;

	kprint("MRPT_HandleNegStr: Recieved '%s'\n", str);

	while(*s)
	{
		while(*s && (*s<=' '))s++;
		if(!*s)break;

		t=tb[i];
		while(*s && (*s>' '))*t++=*s++;
		*t++=0;
		i++;
	}

	switch(*str)
	{
	case '?':
		mrpt_handle_neg_req(con, tb[0]);
		break;
	case '=':
		mrpt_handle_neg_dec(con, tb[0]);
		break;
	case 'E':
		kprint("MRPT_HandleNegStr: Recieved Error '%s'\n", str);
		break;

	default:
		break;
	}

	return(0);
}

int mrpt_handle_declare(Meta0_Con *con, byte *buf, byte *end)
{
	MRPT_TagInfo *ti;
	char *n;
	int i;
	char tb[64];
	MRPT_ConInfo *ri;

	ri=con->data;

	i=(end-buf)-8;
	n=kalloc(i+1);
	memcpy(n, buf+8, i);
	n[i]=0;

	ti=kalloc(sizeof(MRPT_TagInfo));
	ti->name=n;

	ti->flags=(buf[0]<<8)+buf[1];
	ti->tag=(buf[2]<<8)+buf[3];
	ti->len=buf[4];
	ti->class=buf[5];

	kprint("MRPT_HandleDeclare: %s %d %d %d %d\n", ti->name,
		ti->flags, ti->tag, ti->len, ti->class);

	if(ri->tags[ti->tag])
	{
		kprint("MRPT_HandleDeclare: Redefine tag %d, '%s'->'%s'\n",
			ti->tag, ri->tags[ti->tag]->name, ti->name);

		sprintf(tb, "Etag-redef %d Unexpectedly "
			"redefined tag '%s'->'%s'",
			ti->tag, ri->tags[ti->tag]->name, ti->name);
		MRPT_WriteNegStr(con, tb);

		return(-1);
	}

	ri->tags[ti->tag]=ti;

	return(0);
}

int mrpt_handle_basetag(Meta0_Con *con, int tag, byte *buf, byte *end)
{
	byte tb[256];
	int i;

	kprint("MRPT_HandleBaseTag: %d\n", tag);

	switch(tag)
	{
	case 0:
		return(-1);
		break;

	case 1:
		memcpy(tb, buf, end-buf);
		tb[end-buf]=0;

		mrpt_handle_negstr(con, tb);
		break;

	case 2:
		i=mrpt_handle_declare(con, buf, end);
		return(i);
		break;

	default:
		return(-1);
		break;
	}
	return(0);
}

int mrpt_input(Meta0_Con *con)
{
	byte *s, *t, *e, *t2, *t3;
	int i, j;
	MRPT_ConInfo *ri;
	MRPT_TLV *tlv;
	MRPT_TagInfo *ti;

	s=con->buf;
	t=s;
	e=con->end;

	ri=con->data;

	kprint("MRPT_Input\n");

	while(1)
	{
		if(t>=e)break;

		if(ri->rlen)
		{
			kprint("mrpt022: data\n");
			i=e-t;
			if(!i)return(t-s);

			kprint("  %d/%d\n", i, ri->rlen);

			if(ri->rlen<i)i=ri->rlen;
			memcpy(ri->erbuf, t, i);
			ri->erbuf+=i;
			ri->rlen-=i;
			t+=i;

			if(!ri->rlen)
			{
				kprint("MRPT: Message, tag %d\n", ri->rtag);
				if(ri->rtag<32)
				{
					i=mrpt_handle_basetag(con, ri->rtag,
						ri->rbuf, ri->erbuf);

					if(i<0)return(-1);

					ri->rbuf=NULL;

					continue;
				}

				tlv=mrpt_decode(con, ri->rtag, ri->rbuf,
					ri->erbuf);
				ri->rbuf=NULL;

				MRPT_HandleMessage(con, tlv);

				continue;
			}

			continue;
		}



		t2=t;
		t3=t;
		i=mrpt_read_vli(&t3, e);
		if(t3==t2)break;
		t2=t3;

		if(!i)
		{
			kprint("MRPT: Invalid tag %d\n", i);
			return(-1);
		}

		if(i<32)
		{
			j=mrpt_read_vli(&t3, e);
			if(t3==t2)break;
			t2=t3;

			ri->rtag=i;
			ri->rlen=j;
			ri->rbuf=kalloc(j);
			ri->erbuf=ri->rbuf;

			t=t2;
			continue;
		}

		ri->rtag=i;
		ti=ri->tags[i];
		if(!ti)
		{
			kprint("MRPT: Undeclared tag %d\n", i);
			return(-1);
		}

		if(!(ti->flags&2))
		{
			j=mrpt_read_vli(&t3, e);
			if(t3==t2)break;
			t2=t3;
		}else j=ti->len;

		if(j)
		{
			ri->rlen=j;
			ri->rbuf=kalloc(j);
			ri->erbuf=ri->rbuf;

			t=t2;
		}else
		{
			t=t2;

			//handle
		}
	}

	return(t-s);
}

int MRPT_Init()
{
	mrpt_inf=Meta0_CreatePort(7938, "mrpt-trans-node");
	mrpt_inf->new_con=&mrpt_newcon;
	mrpt_inf->closed=&mrpt_closed;
	mrpt_inf->input=&mrpt_input;

	mrpt_tags=kalloc(MRPT_MAX_TAGS*sizeof(MRPT_TagInfo *));
	memset(mrpt_tags, 0, MRPT_MAX_TAGS*sizeof(MRPT_TagInfo *));

	MRPT_DeclareTag("mrpt/integer", 0, 0, MRPT_CLASS_INTEGER);
	MRPT_DeclareTag("mrpt/string", 0, 0, MRPT_CLASS_STRING);
	MRPT_DeclareTag("mrpt/array", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);

	return(0);
}
