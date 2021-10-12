#include <general.h>

/*
RFC 792
*/

extern unsigned int ipv4_addr;

int ICMPv4_EchoReply(int to, byte *msg, int sz)
{
	byte *dg, *buf;

	dg=IPV4_NewDatagram(sz, 1, to);
	buf=IPV4_DatagramBody(dg);

	memcpy(buf, msg, sz);
	buf[0]=0;	//echo reply
	buf[1]=0;	//0
	*(short *)(buf+2)=0;
	*(short *)(buf+2)=IPV4_ComputeChecksum(buf, sz);

	IPV4_SendDatagram(dg);
	return(0);
}

int ICMPv4_HandleMessage(byte *msg, int sz, int from)
{
	switch(*msg)
	{
	case 0:
		kprint("ICMP: Echo Reply\n");
		break;
	case 3:
		kprint("ICMP: Dest Unreachable (code=%d)\n", msg[1]);
		break;
	case 4:
		kprint("ICMP: Source Quence\n");
		break;
	case 5:
		kprint("ICMP: Redirect (code=%d, addr=%X)\n",
			msg[1], ntohl(*(long *)(msg+4)));
		break;
	case 8:
		kprint("ICMP: Echo\n");
		ICMPv4_EchoReply(from, msg, sz);
		break;
	case 11:
		kprint("ICMP: Time Exeeded (code=%d)\n", msg[1]);
		break;
	case 12:
		kprint("ICMP: Parameter Problem (code=%d, parameter=%d)\n",
			msg[1], msg[2]);
		break;
	case 13:
		kprint("ICMP: Timestamp\n");
		break;
	case 14:
		kprint("ICMP: Timestamp Reply\n");
		break;
	default:
		kprint("ICMP: Unknown ICMP Message (type=%d)\n", *msg);
		break;
	}
	return(0);
}
