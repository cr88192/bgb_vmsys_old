#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
int sig;		//0
short arch;		//4
short sections;		//6
int time;		//8
int ofs_symtab;		//12
int num_symbols;	//16
short len_opthead;	//20
short flags;		//22
}PE_BaseHead;		//24 bytes

typedef struct {
short arch;		//0
short sections;		//2
int time;		//4
int ofs_symtab;		//8
int num_symbols;	//12
short len_opthead;	//16
short flags;		//18
}PE_CoffHead;		//20 bytes

typedef struct {
short magic;		//0
char link_major;	//2
char link_minor;	//3
int len_code;		//4
int len_data;		//8
int len_bss;		//12
int vma_entry;		//16
int vma_code;		//20
int vma_data;		//24
int vma_base;		//28
int sec_align;		//32
int sec_fdalign;	//36
short os_major;		//40
short os_minor;		//42
short img_major;	//44
short img_minor;	//46
short sys_major;	//48
short sys_minor;	//50
int resv1;		//52
int len_image;		//56
int len_headers;	//60
int crc_fd;		//64
short sys_ui;		//68
short dll_flags;	//70
int stack_size;		//72
int stack_initial;	//76
int heap_size;		//80
int heap_initial;	//84
int ldr_flags;		//88
int num_rvaents;	//92

int rva_ofs_expdir;	//96
int rva_len_expdir;
int rva_ofs_impdir;
int rva_len_impdir;

int rva_ofs_rsrcdir;
int rva_len_rsrcdir;
int rva_ofs_excpdir;
int rva_len_excpdir;
int rva_ofs_secdir;
int rva_len_secdir;
int rva_ofs_rectab;
int rva_len_rectab;
int rva_ofs_dbgdir;
int rva_len_dbgdir;
int rva_ofs_archdata;
int rva_len_archdata;
int rva_ofs_gp;
int rva_len_gp;
int rva_ofs_tlsdir;
int rva_len_tlsdir;
int rva_ofs_cfgdir;
int rva_len_cfgdir;
int rva_ofs_biddir;
int rva_len_biddir;
int rva_ofs_iat;
int rva_len_iat;
int rva_ofs_dlid;
int rva_len_dlid;
int rva_ofs_comdesc;
int rva_len_comdesc;
int rva_ofs_null;
int rva_len_null;
}PE_OptHead;

typedef struct {
char name[8];	//0
int vma_size;	//8
int vma_addr;	//12
int fd_size;	//16
int fd_offs;	//20
int rec_offs;	//24
int line_offs;	//28
short rec_num;	//32
short line_num;	//34
int chars;	//36
}PE_SecHead;	//40 bytes

typedef struct {
union {
	char name[8];
	struct {
		unsigned int zeros;
		unsigned int offset;
	} e;
} e;
unsigned int value;
short secnum;
unsigned short type;
unsigned char class;
unsigned char num_aux;
}PE_Symbol;

int rd_w(FILE *fd, int ofs)
{
	int i;

	fseek(fd, ofs, 0);
	i=fgetc(fd);
	i+=fgetc(fd)<<8;

	return(i);
}

int rd_d(FILE *fd, int ofs)
{
	int i;

	fseek(fd, ofs, 0);
	i=fgetc(fd);
	i+=fgetc(fd)<<8;
	i+=fgetc(fd)<<16;
	i+=fgetc(fd)<<24;

	return(i);
}

int main(int argc, char *argv[])
{
	FILE *fd;
	int i, j, k, l, n;
	short m;

	PE_CoffHead bh;
	PE_OptHead oh;
	PE_SecHead sh;
	PE_Symbol *symtab;
	PE_Symbol *sym;
	char *strtab;

	fd=fopen(argv[1], "rb");

	memset(&oh, 0, sizeof(PE_OptHead));

	i=rd_w(fd, 0);
	if(i!=0x5A4D)
	{
		printf("NO MZ Tag\n");
//		return(-1);
		fseek(fd, 0, 0);
		fread(&bh, 1, 20, fd);
	}else
	{
		printf("MZ Tag\n");

		i=rd_d(fd, 0x3C);
		printf("head %d\n", i);

//		fseek(fd, i, 0);

		i=rd_d(fd, i);
		printf("sig %.4s\n", &i);
		fread(&bh, 1, 20, fd);
	}
//	printf("sig %d\n", bh.sig);

	printf("arch %d\n", bh.arch);
	printf("secs %d\n", bh.sections);
	printf("time %d\n", bh.time);
	printf("symt %d\n", bh.ofs_symtab);
	printf("syms %d\n", bh.num_symbols);
	printf("opth %d\n", bh.len_opthead);
	printf("flag %X\n", bh.flags);
	printf("\n");
	fread(&oh, 1, bh.len_opthead, fd);

	printf("base %X\n", oh.vma_base);
	printf("entry %X\n", oh.vma_entry+oh.vma_base);

	printf("rectab %X %d\n", oh.rva_ofs_rectab, oh.rva_len_rectab);
	printf("\n");


	for(i=0; i<bh.sections; i++)
	{
		fread(&sh, 1, 40, fd);
		printf("%.8s\n", sh.name);
		printf("%X\t", sh.vma_addr+oh.vma_base);
		printf("%X\n", sh.vma_size);

		printf("%X\t", sh.fd_offs);
		printf("%X\n", sh.fd_size);

		printf("%X\t", sh.rec_offs);
		printf("%d\n", sh.rec_num);

		printf("%X\t", sh.line_offs);
		printf("%d\n", sh.line_num);

		printf("flag %X\n\n", sh.chars);

		if(!strncmp(sh.name, ".reloc", 8))
		{
			oh.rva_ofs_rectab=sh.fd_offs;
			oh.rva_len_rectab=sh.fd_size;
		}
	}

	fseek(fd, bh.ofs_symtab, 0);
	symtab=malloc(bh.num_symbols*18);
	fread(symtab, 1, bh.num_symbols*18, fd);
	fread(&i, 1, 4, fd);
	strtab=malloc(i);
	memset(strtab, 0, i);
	fread(strtab+4, 1, i-4, fd);

	if (0)
		for(i=0; i<bh.num_symbols; i++)
	{
		sym=((void *)symtab)+(i*18);
		if(!sym->class)continue;

		if(!sym->e.e.zeros)
		{
			printf("%s\t", strtab+sym->e.e.offset);
		}else
		{
			printf("%.8s\t", sym->e.name);
		}
		printf("%d %d %d %d\n",
			sym->value, sym->secnum, sym->type, sym->class);
	}

	printf("rectab %X %d\n", oh.rva_ofs_rectab, oh.rva_len_rectab);

	fseek(fd, oh.rva_ofs_rectab, 0);
	i=oh.rva_len_rectab;
	if(1)	
		while(i>0)
	{
		fread(&j, 1, 4, fd);
		fread(&k, 1, 4, fd);

		printf("rec %X(%X) %d\n", j, j+oh.vma_base, k);
		l=k-8;
		while(l>0)
		{
			fread(&m, 1, 2, fd);
//			printf(" %d %d", (m>>12)&0xf, m&0xfff);
			n=j+oh.vma_base+(m&0xfff);
//			printf("%X ", n);

			l-=2;
		}
//		printf("\n");
		i-=k+8;
	}
}
