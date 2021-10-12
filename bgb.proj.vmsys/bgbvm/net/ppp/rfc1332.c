#include <general.h>
#include <net/ppp.h>

int PPP_DecodeIP(ppp_ctx *ctx, byte *buf)
{
	kprint("IP datagram\n");
}

int PPP_DecodeTCP(ppp_ctx *ctx, byte *buf)
{
	kprint("TCP datagram\n");
}

int PPP_SendIPCP(ppp_ctx *ctx, int code, int id, int len, byte *data)
{
	byte *buf, *s;

	buf=kalloc(4096);
	s=buf;

	*s++=0x80;
	*s++=0x21;

	*s++=code;
	*s++=id;
	*s++=(len+4)>>8;
	*s++=(len+4)&0xff;
	memcpy(s, data, len);

	PPP_SendFrame(ctx, buf, len+6);
	kfree(buf);
}

int PPP_DecodeIPCP(ppp_ctx *ctx, byte *buf)
{
	int code, id, len;
	int i;
	byte *s, *t, *u;
	byte buf2[1024], buf3[1024];

	static int crej=0;

	kprint("PPP_DecodeIPCP\n");

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
			case 1: //ip-addresses
				kprint("PPP_DecodeIPCP: no ip addresses\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			case 2: //no authentication
				kprint("PPP_DecodeIPCP: no ip header compression\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			case 3: //ip address
				kprint("PPP_DecodeIPCP: no ip address\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;

			default:
				kprint("PPP_DecodeIPCP: unknown option %d\n", s[0]);
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			}
		}
		if(u>buf3)
		{
			PPP_SendIPCP(ctx, LCP_CONF_REJECT, id, (int)(u-buf3), buf3);
			break;
		}
		if(t>buf2)
		{
			PPP_SendIPCP(ctx, LCP_CONF_NAK, id, (int)(t-buf2), buf2);
			break;
		}
		PPP_SendIPCP(ctx, LCP_CONF_ACK, id, len-4, buf+4);
		break;
	case 2: //config-ack
		break;
	case 3: //config-nak
		break;
	case 4: //config-reject
		break;
	case 5: //term-request
		PPP_SendIPCP(ctx, LCP_TERM_ACK, id, 0, buf+4);
		break;
	case 6: //term-ack
		break;
	case 7: //code-reject
		break;
	default:
		kprint("PPP_DecodeIPCP: unknown code %d\n", code);
		i=len;
		if((i+4)>ctx->peer_mru)i=ctx->peer_mru;
		PPP_SendIPCP(ctx, LCP_CODE_REJECT, (crej++)&0xff, i, buf);
		break;
	}
}

