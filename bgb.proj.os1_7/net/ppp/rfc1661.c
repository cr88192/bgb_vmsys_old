#include <general.h>
#include <net/ppp.h>

int PPP_SendLCP(ppp_ctx *ctx, int code, int id, int len, byte *data)
{
	byte *buf, *s;

	buf=kalloc(4096);
	s=buf;

	*s++=0xc0;
	*s++=0x21;

	*s++=code;
	*s++=id;
	*s++=(len+4)>>8;
	*s++=(len+4)&0xff;
	memcpy(s, data, len);

	PPP_SendFrame(ctx, buf, len+6);
	kfree(buf);
}

int PPP_DecodeLCP(ppp_ctx *ctx, byte *buf)
{
	int code, id, len;
	int i;
	byte *s, *t, *u;
	byte buf2[1024], buf3[1024];

	static int crej=0;

	kprint("PPP_DecodeLCP\n");

	code=buf[0];
	id=buf[1];
	len=(buf[2]<<8)+buf[3];
	s=buf+4;

	kprint("(code %d, id %d, len %d) ", code, id, len);
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
			case 0:
				kprint("0 loop error\n");
				len=-1;
				break;

			case 1: //mru
				i=(s[2]<<8)+s[3];
				if(i>3500)
				{
					kprint("PPP_DecodeLCP: peer tried mru %d\n", i);
					*t++=1;
					*t++=4;
					*t++=3500>>8;
					*t++=3500&0xff;
				}
				s+=s[1];
				break;
			case 3: //no authentication
				kprint("PPP_DecodeLCP: no authentication\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			case 4: //no quality checks
				kprint("PPP_DecodeLCP: no quality checks\n");
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			case 5: //magic number
				s+=s[1];
				break;
			case 7: //compress protocol field
				s+=s[1];
				break;
			case 8: //compress address/control field
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;

			default:
				kprint("PPP_DecodeLCP: unknown option %d\n", s[0]);
				memcpy(u, s, s[1]);
				u+=s[1];
				s+=s[1];
				break;
			}
		}
		if(u>buf3)
		{
			PPP_SendLCP(ctx, LCP_CONF_REJECT, id, (int)(u-buf3), buf3);
			break;
		}
		if(t>buf2)
		{
			PPP_SendLCP(ctx, LCP_CONF_NAK, id, (int)(t-buf2), buf2);
			break;
		}
		PPP_SendLCP(ctx, LCP_CONF_ACK, id, len-4, buf+4);
		break;
	case 2: //config-ack
		break;
	case 3: //config-nak
		break;
	case 4: //config-reject
		break;
	case 5: //term-request
		PPP_SendLCP(ctx, LCP_TERM_ACK, id, 0, buf+4);
		break;
	case 6: //term-ack
		break;
	case 7: //code-reject
		break;
	case 8: //protocol-reject
		break;
	case 9: //echo-request
		PPP_SendLCP(ctx, LCP_ECHO_REP, id, 0, buf+4);
		break;
	case 10: //echo-reply
		break;
	case 11: //discard-request
		break;
	default:
		kprint("PPP_DecodeLCP: unknown code %d\n", code);
		i=len;
		if((i+4)>ctx->peer_mru)i=ctx->peer_mru;
		PPP_SendLCP(ctx, LCP_CODE_REJECT, (crej++)&0xff, i, buf);
		break;
	}
}

int PPP_DecodeFrame(ppp_ctx *ctx, byte *frame, int size)
{
	byte *s;
	int p, i;

	static int prej=0;

	kprint("PPP_DecodeFrame %d bytes\n", size);

	s=frame;
	p=*s++;
	if(!(p&1))p=(p<<8)+(*s++);

	switch(p)
	{
	case 0x21:	//rfc1332: ip
		PPP_DecodeIP(ctx, s);
		break;
	case 0x2d:	//rfc1332: compressed tcp
		break;
	case 0x2f:	//rfc1332: uncompressed tcp, protocol replaced by slot
		PPP_DecodeTCP(ctx, s);
		break;

	case 0x57:	//rfc2472: ipv6
		PPP_DecodeIPV6(ctx, s);
		break;

	case 0x8021:	//rfc1332: ipcp
		PPP_DecodeIPCP(ctx, s);
		break;
	case 0x8057:	//rfc2472: ipv6cp
		PPP_DecodeIPV6CP(ctx, s);
		break;
	case 0xc021:
		PPP_DecodeLCP(ctx, s);
		break;
	default:
		kprint("PPP_DecodeFrame: unknown protocol %d.\n", p);
		i=size;
		if((i+4)>ctx->peer_mru)i=ctx->peer_mru;
		PPP_SendLCP(ctx, LCP_PROT_REJECT, (prej++)&0xff, i, frame);
		break;
	}
	return(0);
}
