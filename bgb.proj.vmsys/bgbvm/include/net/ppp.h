#define LCP_CONF_REQ	1
#define	LCP_CONF_ACK	2
#define LCP_CONF_NAK	3
#define LCP_CONF_REJECT	4
#define LCP_TERM_REQ	5
#define LCP_TERM_ACK	6
#define LCP_CODE_REJECT	7
#define LCP_PROT_REJECT	8
#define LCP_ECHO_REQ	9
#define LCP_ECHO_REP	10
#define LCP_DUMP_REQ	11

typedef struct {
VFILE *fd;
int peer_mru;

int lcp_up; //set after lcp configuration established
int ip_up;	//set after ip is up
int ipv6_up;
}ppp_ctx;

