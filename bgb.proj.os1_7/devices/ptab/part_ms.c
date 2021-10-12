#include <general.h>

typedef struct pdef_t {
struct pdef_t *next;
char *name;
VFILE *dev;
int start, len; /* sector address */
byte type, flag;
}pdef;

typedef struct {
byte flag;
byte shead;
byte strk[2];
byte type;
byte ehead;
byte etrk[2];
byte linstart[4];
byte linlen[4];
}ptent;

typedef struct {
char buf[446];
ptent ent[4];
}ptab;

pdef *partms_root;

static int read_u32_le(byte *b)
{
	return(b[0]+(b[1]<<8)+(b[2]<<16)+(b[3]<<24));
}

VFILE *partms_open(char *name, void *data)
{
	u8 start, len;

//	kprint("part_ms: open \"%s\"\n", name);

	pdef *cur;
	cur=partms_root;
	while(cur)
	{
		if(!stricmp(name, cur->name))break;
		cur=cur->next;
	}

	start[0]=cur->start<<9;
	start[1]=cur->start>>23;
	len[0]=cur->len<<9;
	len[1]=cur->len>>23;
	return(vf_clip(cur->dev, start, len));
}

int PartMS_ProcessDev(VFILE *vfd, char *base, int idx)
{
	ptab ptbuf;
	int i;
	char tn[16];
	pdef *pd;

	vfseek(vfd, 0, 0);
//	read_block(0, &ptbuf, 1);
	vfread(&ptbuf, 1, 512, vfd);

	kprint("%s: ", base);

	for(i=0; i<4; i++)
	{
//		kprint("p%d: %s S(C:%d H:%d S:%d) E(C:%d H:%d S:%d)\n", i, ptbuf.ent[i].flag?"A":"-",
//			ptbuf.ent[i].strk[0]>>6+ptbuf.ent[i].strk[1]<<2, ptbuf.ent[i].shead, ptbuf.ent[i].strk[0]&0x3f,
//			ptbuf.ent[i].etrk[0]>>6+ptbuf.ent[i].etrk[1]<<2, ptbuf.ent[i].ehead, ptbuf.ent[i].etrk[0]&0x3f
//			);
//		ata_part_table[0][i].type=ptbuf.ent[i].type;
//		ata_part_table[0][i].fl=ptbuf.ent[i].flag;
//		ata_part_table[0][i].start=read_u32_le(ptbuf.ent[i].linstart);
//		ata_part_table[0][i].length=read_u32_le(ptbuf.ent[i].linlen);

		if(read_u32_le(ptbuf.ent[i].linlen))
		{
			kprints(tn, "%s/%d", base, idx+i);

			pd=kalloc(sizeof(pdef));
			pd->name=kstrdup(tn);
			pd->dev=vfd;
			pd->start=read_u32_le(ptbuf.ent[i].linstart);
			pd->len=read_u32_le(ptbuf.ent[i].linlen);
			pd->type=ptbuf.ent[i].type;
			pd->flag=ptbuf.ent[i].flag;
			pd->next=partms_root;
			partms_root=pd;

			Driver_RegisterStream(tn, &partms_open, NULL);

			kprint("%s(%d %d) ", tn, pd->type, pd->len);
		}
	}
	kprint("\n");
	return(i);
}
