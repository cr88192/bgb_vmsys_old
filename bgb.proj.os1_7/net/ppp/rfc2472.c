#include <general.h>
#include <net/ppp.h>

int PPP_DecodeIPV6(ppp_ctx *ctx, byte *buf)
{
	kprint("IPV6 datagram\n");
}

int PPP_SendIPV6CP(ppp_ctx *ctx, int code, int id, int len, byte *data)
{
	byte *buf, *s;

	buf=kalloc(4096);
	s=buf;

	*s++=0x80;
	*s++=0x57;

	*s++=code;
	*s++=id;
	*s++=(len+4)>>8;
	*s++=(len+4)&0xff;
	memcpy(s, data, len);

	PPP_SendFrame(ctx, buf, len+6);
	kfree(buf);
}

int PPP_DecodeIPV6CP(ppp_ctx *ctx, byte *buf)
{
	int code, id, len;
	int i;
	byte *s, *t, *u;
	byte buf2[1024], buf3[1024];

	static int crej=0;

	kprint("PPP_DecodeIPV6CP\n");

	code=buf[0];
	id=buf[1];
	len=(buf[2]<<8)+buf[3];
	s=buf+4;

	kprint("(code %d) ", code);
	switch(code)
	{
	case 1: //config-request
		t=buf2;
		u=buf3;

//		if(0)
		while((s-buf)<len)
		{
			kprint("(option %d %X) \n", s[0], s);
			switch(s[0])
			{
			case 1: //interface-identifier
				kprint("PPP_DecodeIPV6CP: no interface identifier\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			case 2: //ipv6 compression
				kprint("PPP_DecodeIPV6CP: no ip header compression\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;

			default:
				kprint("PPP_DecodeIPV6CP: unknown option %d\n", s[0]);
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			}
		}
		if(u>buf3)
		{
			PPP_SendIPV6CP(ctx, LCP_CONF_REJECT, id, (int)(u-buf3), buf3);
			break;
		}
		if(t>buf2)
		{
			PPP_SendIPV6CP(ctx, LCP_CONF_NAK, id, (int)(t-buf2), buf2);
			break;
		}
		PPP_SendIPV6CP(ctx, LCP_CONF_ACK, id, len-4, buf+4);
		break;
	case 2: //config-ack
		break;
	case 3: //config-nak
		break;
	case 4: //config-reject
		break;
	case 5: //term-request
		PPP_SendIPV6CP(ctx, LCP_TERM_ACK, id, 0, buf+4);
		break;
	case 6: //term-ack
		break;
	case 7: //code-reject
		break;
	default:
		kprint("PPP_DecodeLCP: unknown code %d\n", code);
		i=len;
		if((i+4)>ctx->peer_mru)i=ctx->peer_mru;
		PPP_SendIPV6CP(ctx, LCP_CODE_REJECT, (crej++)&0xff, i, buf);
		break;
	}
}
