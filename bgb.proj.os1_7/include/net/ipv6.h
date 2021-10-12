typedef struct ipv6_routent_t {
struct ipv6_routent_t *next, *prev;
VADDR *this;
VFILE *vfd;
}ipv6_routent;

typedef struct {
byte ver_class_flow[4]; // version 4 bits, class 8 bits, flow label 20 bits
byte payload_length[2];	//size of datagram, not including main header
byte next_header;		//type of next header (ipv4 protocol)
byte hop_limit;			//how many hops remain for this packet
//8
byte source_addr[16];
//24
byte dest_addr[16];
//40
}ipv6_header;