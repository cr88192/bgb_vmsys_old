#ifndef __DESC_H__
#define __DESC_H__

int InitDescs();
int NewIntISR(void (*handler)(), int vec, int fl);

int FindFreeGDTEntry();
void DeleteGDTEntry(int num);
int NewGDTEntry(int num, int base, int size, int flags);

#define GDT_TYPE_RO	0	//data, read only
#define GDT_TYPE_ROA	1	//data, read only, acessed
#define GDT_TYPE_RW	2	//data, read/write
#define GDT_TYPE_RWA	3	//data, read/write, accessed
#define GDT_TYPE_ROE	4	//data, read only, expand down
#define GDT_TYPE_ROEA	5	//data, read only, expand down, accessed
#define GDT_TYPE_RWE	6	//data, read/write, expand down
#define GDT_TYPE_RWEA	7	//data, read/write, expand down, accessed
#define GDT_TYPE_XO	8	//code, exectue only
#define GDT_TYPE_XOA	9	//code, execute only, acessed
#define GDT_TYPE_XR	10	//code, execute/read
#define GDT_TYPE_XRA	11	//code, execute/read, accessed
#define GDT_TYPE_XOC	12	//code, execute only, conforming
#define GDT_TYPE_XOCA	13	//code, execute only, conforming, accessed
#define GDT_TYPE_XRC	14	//code, execute/read, conforming
#define GDT_TYPE_XRCA	15	//code, execute/read, conforming, accessed

#define GDT_TYPE_DATA	GDT_TYPE_RW	//data, generic
#define GDT_TYPE_CODE	GDT_TYPE_XR	//code, generic
#define GDT_TYPE_CODE_C	GDT_TYPE_XRC	//code, conforming

#define GDT_FLAG_S	16	//if set entry is code/data, else system
#define GDT_FLAG_P	128	//set if entry exists
#define GDT_FLAG_DB	1024	//if set segment is 32 bit
#define GDT_FLAG_G	2048	//if set limit granularity is 4KB

#define GDT_CODE_FLAGS	(GDT_FLAG_S|GDT_FLAG_P|GDT_FLAG_DB|GDT_FLAG_G)
#define GDT_DATA_FLAGS	GDT_CODE_FLAGS

#define GDT_STYPE_TSS16A	1
#define	GDT_STYPE_LDT		2
#define GDT_STYPE_TSS16B	3
#define GDT_STYPE_CALL16	4
#define GDT_STYPE_TASKGATE	5
#define	GDT_STYPE_INT16		6
#define GDT_STYPE_TRAP16	7
#define GDT_STYPE_TSS32A	9
#define GDT_STYPE_TSS32B	11
#define GDT_STYPE_CALL32	12
#define	GDT_STYPE_INT32		14
#define GDT_STYPE_TRAP32	15

#define GDT_STYPE_TSS		GDT_STYPE_TSS32A
#define GDT_STYPE_FLAGS		(GDT_FLAG_P)

#define GDT_FLAG_DPL0		0x0000
#define GDT_FLAG_DPL1		0x2000
#define GDT_FLAG_DPL2		0x4000
#define GDT_FLAG_DPL3		0x6000

#endif
