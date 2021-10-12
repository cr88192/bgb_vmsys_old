#include <pdlib.h>
#include <pdnet.h>

int MRPT_SizeTLV(MRPT_TLV *tlv)
{
	MRPT_TagInfo *ti;
	MRPT_TLV *cur;
	int i, j, k;

	i=0;
	ti=tlv->tag;
	if(!(ti->flags&MRPT_FLAG_COMPOUND))
	{
		i+=MRPT_SizeVLI(ti->tag);

		j=tlv->len;
		if(ti->flags&MRPT_FLAG_FIXEDLENGTH)
		{
			if(tlv->len!=ti->len)
			{
				kprint("MRPT_SizeTLV: Fixed-Length tag "
					"size mismatch '%s'\n", ti->name);
				return(0);
			}
			j=ti->len;
		}else i+=MRPT_SizeVLI(tlv->len);

		i+=j;

		return(i);
	}

	j=0;
	cur=tlv->first;
	while(cur)
	{
		k=MRPT_SizeTLV(cur);
		if(!k)return(k);
		j+=k;
		cur=cur->next;
	}

#if 0
	if((ti->flags&MRPT_FLAG_FIXEDLENGTH) && (j!=ti->len))
	{
		kprint("MRPT_SizeTLV: Compound Fixed-Length tag "
			"size mismatch '%s'\n", ti->name);
		return(0);
	}
#endif
	if(ti->flags&MRPT_FLAG_FIXEDLENGTH)
	{
		kprint("MRPT_SizeTLV: Disallowed Encoding: "
			"Compound Fixed-Length tag '%s'\n", ti->name);
		return(0);
	}

	i=0;
	i+=MRPT_SizeVLI(ti->tag);
	i+=MRPT_SizeVLI(j);
	i+=j;

	return(i);
}

byte *MRPT_EncodeTLV(byte *s, MRPT_TLV *tlv)
{
	MRPT_TagInfo *ti;
	MRPT_TLV *cur;
	int i, j;

	ti=tlv->tag;
	if(!(ti->flags&MRPT_FLAG_COMPOUND))
	{
		s=mrpt_write_vli(s, ti->tag);
		if(!(ti->flags&MRPT_FLAG_FIXEDLENGTH))
		{
			s=mrpt_write_vli(s, tlv->len);
		}
		memcpy(s, tlv->data, tlv->len);
		s+=tlv->len;
		return(s);
	}
	
	i=0;
	cur=tlv->first;
	while(cur)
	{
		j=MRPT_SizeTLV(cur);
		if(!j)
		{
			kprint("MRPT_EncodeTLV: Structural Error.\n");
			return(NULL);
		}
		i+=j;
		cur=cur->next;
	}

	s=mrpt_write_vli(s, ti->tag);
	s=mrpt_write_vli(s, i);

	cur=tlv->first;
	while(cur)
	{
		s=MRPT_EncodeTLV(s, cur);
		if(!s)return(NULL);
		cur=cur->next;
	}

	return(s);
}

int MRPT_SendTLV(Meta0_Con *con, MRPT_TLV *tlv)
{
	byte *buf, *s;
	int i;

	i=MRPT_SizeTLV(tlv);
	if(!i)
	{
		kprint("MRPT_SendTLV: Structural Error.\n");
		return(-1);
	}
	buf=kalloc(i);
	s=MRPT_EncodeTLV(buf, tlv);
	if(!s)
	{
		kprint("MRPT_SendTLV: Encode Error.\n");
		return(-1);
	}
	vfwrite(buf, 1, i, con->sock);
	kfree(buf);

	return(0);
}

MRPT_TLV *MRPT_NewTLVPrimitive(char *name, int size)
{
	MRPT_TLV *tlv;
	MRPT_TagInfo *ti;

	ti=MRPT_LookupTag(name);
	if(!ti)
	{
		kprint("MRPT_NewTLVPrimitive: Undefined tag '%s'\n", name);
		return(NULL);
	}

	if(ti->flags&MRPT_FLAG_FIXEDLENGTH)
	{
		if(size && (size!=ti->len))
		{
			kprint("MRPT_NewTLVPrimitive: Bad Size for "
				"fixed length tag '%s'\n", name);
		}
		size=ti->len;
	}

	tlv=kalloc(sizeof(MRPT_TLV));

	tlv->next=NULL;
	tlv->first=NULL;

	tlv->tag=ti;
	tlv->len=size;
	tlv->data=kalloc(size);

	return(tlv);
}

MRPT_TLV *MRPT_NewTLVCompound(char *name)
{
	MRPT_TLV *tlv;
	MRPT_TagInfo *ti;

	ti=MRPT_LookupTag(name);
	if(!ti)
	{
		kprint("MRPT_NewTLVPrimitive: Undefined tag '%s'\n", name);
		return(NULL);
	}

	tlv=kalloc(sizeof(MRPT_TLV));

	tlv->next=NULL;
	tlv->first=NULL;

	tlv->tag=ti;
	tlv->len=0;
	tlv->data=NULL;

	return(tlv);
}

int MRPT_AddTLVMember(MRPT_TLV *tlv, MRPT_TLV *obj)
{
	MRPT_TLV *cur;

	if(!tlv->first)
	{
		tlv->first=obj;
		return(0);
	}

	cur=tlv->first;
	while(cur->next)cur=cur->next;
	cur->next=obj;
	return(0);
}

int MRPT_DumpTLV(MRPT_TLV *tlv)
{
	MRPT_TagInfo *ti;
	MRPT_TLV *cur;
	int i, j;
	char buf[256];

	ti=tlv->tag;
	if(ti->flags&MRPT_FLAG_COMPOUND)
	{
		kprint("{%s", ti->name);

		cur=tlv->first;
		while(cur)
		{
			kprint(" ");
			MRPT_DumpTLV(cur);
			cur=cur->next;
		}

		kprint("}");
		return(0);
	}

	kprint("%s:", ti->name);
	switch(ti->class)
	{
	case MRPT_CLASS_RAW:
		kprint("<raw>");
		break;

	case MRPT_CLASS_STRING:
		memset(buf, 0, 256);
		memcpy(buf, tlv->data, tlv->len);
		kprint("'%s'", buf);
		break;
	case MRPT_CLASS_INTEGER:
		j=0;
		if(tlv->data[0]&0x80)j=-1;
		for(i=0; i<tlv->len; i++)
			j=(j<<8)+tlv->data[i];
		kprint("%d", j);
		break;

	default:
		kprint("<unknown>");
		break;
	}
	return(0);
}
