	.file	"outelf.c"
	.text
_align_str:
	.ascii "\0"
	.space 15
	.data
	.align 4
_stabslines:
	.long	0
	.align 4
_stabs_immcall:
	.long	0
	.align 4
_currentline:
	.long	0
	.align 4
_numlinestabs:
	.long	0
	.align 4
_stabs_filename:
	.long	0
	.align 4
_stabbuf:
	.long	0
	.align 4
_stabstrbuf:
	.long	0
	.align 4
_stabrelbuf:
	.long	0
	.text
LC0:
	.ascii "\0\0"
LC1:
	.ascii "\0"
LC2:
	.ascii "..gotpc\0"
LC3:
	.ascii "..gotoff\0"
LC4:
	.ascii "..got\0"
LC5:
	.ascii "..plt\0"
LC6:
	.ascii "..sym\0"
	.align 2
	.def	_elf_init;	.scl	3;	.type	32;	.endef
_elf_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	16(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, _elffp
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	20(%ebp), %eax
	movl	%eax, _evaluate
	movl	$0, _sects
	movl	$0, _sectlen
	movl	$0, _nsects
	movl	$36, (%esp)
	call	_saa_init
	movl	%eax, _syms
	movl	$0, _nglobs
	movl	$0, _nlocals
	call	_raa_init
	movl	%eax, _bsym
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _strs
	movl	%eax, (%esp)
	movl	$LC0, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	$_elf_module, (%esp)
	call	_strlen
	incl	%eax
	movl	_strs, %edx
	movl	%edx, (%esp)
	movl	$_elf_module, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movl	$_elf_module, (%esp)
	call	_strlen
	addl	$2, %eax
	movl	%eax, _strslen
	movl	$0, _shstrtab
	movl	$0, _shstrtabsize
	movl	$0, _shstrtablen
	movl	$LC1, (%esp)
	movl	$LC1, 4(%esp)
	call	_add_sectname
	movl	$0, _fwds
	call	_seg_alloc
	movl	%eax, _elf_gotpc_sect
	movl	$LC2, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_elf, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _elf_gotoff_sect
	movl	$LC3, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_elf, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _elf_got_sect
	movl	$LC4, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_elf, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _elf_plt_sect
	movl	$LC5, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_elf, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _elf_sym_sect
	movl	$LC6, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_elf, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _def_seg
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_elf_cleanup;	.scl	3;	.type	32;	.endef
_elf_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	call	_elf_write
	movl	_elffp, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L16
L13:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$8, 20(%eax)
	je	L7
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_saa_free
L7:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 44(%eax)
	je	L8
	movl	36(%eax), %eax
	movl	%eax, (%esp)
	call	_saa_free
L8:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 44(%eax)
	je	L18
L12:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %edx
	movl	44(%edx), %ecx
	movl	(%ecx), %eax
	movl	%eax, 44(%edx)
	movl	%ecx, (%esp)
	call	_nasm_free
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 44(%eax)
	jne	L12
L18:
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L13
L16:
	movl	_sects, %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_free
	movl	_bsym, %eax
	movl	%eax, (%esp)
	call	_raa_free
	movl	_strs, %eax
	movl	%eax, (%esp)
	call	_saa_free
	cmpl	$0, _of_elf+16
	je	L2
	movl	_of_elf+16, %eax
	call	*32(%eax)
L2:
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_add_sectname;	.scl	3;	.type	32;	.endef
_add_sectname:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	%esi, (%esp)
	call	_strlen
	movl	%eax, %ebx
	movl	%edi, (%esp)
	call	_strlen
	addl	%eax, %ebx
	movl	%ebx, %eax
	addl	_shstrtablen, %eax
	incl	%eax
	cmpl	_shstrtabsize, %eax
	jle	L25
L23:
	movl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	_shstrtabsize, %eax
	addl	$256, %eax
	movl	%eax, _shstrtabsize
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _shstrtab
	movl	%ebx, %eax
	addl	_shstrtablen, %eax
	incl	%eax
	cmpl	_shstrtabsize, %eax
	jg	L23
L25:
	movl	_shstrtab, %eax
	addl	_shstrtablen, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	_shstrtab, %eax
	addl	_shstrtablen, %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcat
	movl	%ebx, %eax
	addl	_shstrtablen, %eax
	incl	%eax
	movl	%eax, _shstrtablen
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC7:
	.ascii ".text\0"
	.align 2
	.def	_elf_make_section;	.scl	3;	.type	32;	.endef
_elf_make_section:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	$56, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	cmpl	$8, %edi
	je	L27
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, (%ebx)
L27:
	movl	$0, 44(%ebx)
	leal	44(%ebx), %eax
	movl	%eax, 48(%ebx)
	movl	$0, 8(%ebx)
	movl	$0, 4(%ebx)
	movl	$0, 12(%ebx)
	movl	%esi, (%esp)
	movl	$LC7, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L28
	movl	_def_seg, %eax
	jmp	L31
L28:
	call	_seg_alloc
L31:
	movl	%eax, 16(%ebx)
	movl	$LC1, (%esp)
	movl	%esi, 4(%esp)
	call	_add_sectname
	movl	%esi, (%esp)
	call	_strlen
	incl	%eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 32(%ebx)
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	%edi, 20(%ebx)
	movl	16(%ebp), %eax
	movl	%eax, 28(%ebx)
	movl	20(%ebp), %eax
	movl	%eax, 24(%ebx)
	movl	$0, 52(%ebx)
	movl	_nsects, %eax
	cmpl	_sectlen, %eax
	jl	L30
	movl	_sects, %eax
	movl	%eax, (%esp)
	movl	_sectlen, %eax
	addl	$32, %eax
	movl	%eax, _sectlen
	sall	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _sects
L30:
	movl	_nsects, %edx
	movl	_sects, %eax
	movl	%ebx, (%eax,%edx,4)
	movl	_nsects, %eax
	leal	1(%eax), %edx
	movl	%edx, _nsects
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC8:
	.ascii "align=\0"
	.align 32
LC9:
	.ascii "section alignment %d is not a power of two\0"
LC10:
	.ascii "alloc\0"
LC11:
	.ascii "noalloc\0"
LC12:
	.ascii "exec\0"
LC13:
	.ascii "noexec\0"
LC14:
	.ascii "write\0"
LC15:
	.ascii "nowrite\0"
LC16:
	.ascii "progbits\0"
LC17:
	.ascii "nobits\0"
LC18:
	.ascii ".comment\0"
LC19:
	.ascii ".shstrtab\0"
LC20:
	.ascii ".symtab\0"
LC21:
	.ascii ".strtab\0"
	.align 32
LC22:
	.ascii "attempt to redefine reserved sectionname `%s'\0"
LC23:
	.ascii ".rodata\0"
LC24:
	.ascii ".data\0"
LC25:
	.ascii ".bss\0"
	.align 32
LC26:
	.ascii "section attributes ignored on redeclaration of section `%s'\0"
	.align 2
	.def	_elf_section_names;	.scl	3;	.type	32;	.endef
_elf_section_names:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %edi
	testl	%edi, %edi
	jne	L33
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	movl	_def_seg, %eax
	jmp	L32
L33:
	movl	%edi, %ebx
	jmp	L34
L38:
	incl	%ebx
L34:
	cmpb	$0, (%ebx)
	je	L39
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L38
	cmpb	$0, (%ebx)
	je	L39
	movb	$0, (%ebx)
	incl	%ebx
L39:
	movl	$0, -28(%ebp)
	movl	$0, -24(%ebp)
	movl	$0, -20(%ebp)
	movl	$0, -16(%ebp)
	jmp	L40
L44:
	incl	%ebx
L40:
	cmpb	$0, (%ebx)
	je	L103
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L44
	cmpb	$0, (%ebx)
	je	L103
L78:
	movl	%ebx, %esi
	jmp	L48
L52:
	incl	%ebx
L48:
	cmpb	$0, (%ebx)
	je	L55
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L52
	cmpb	$0, (%ebx)
	je	L55
	movb	$0, (%ebx)
L58:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L55
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L58
L55:
	movl	%esi, (%esp)
	movl	$LC8, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L59
	leal	6(%esi), %eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, -28(%ebp)
	testl	%eax, %eax
	jne	L60
	movl	$1, -28(%ebp)
L60:
	movl	-28(%ebp), %eax
	decl	%eax
	testl	%eax, -28(%ebp)
	je	L45
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$1, -28(%ebp)
	jmp	L45
L59:
	movl	%esi, (%esp)
	movl	$LC10, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L63
	orl	$2, -16(%ebp)
	orl	$2, -20(%ebp)
	jmp	L45
L63:
	movl	%esi, (%esp)
	movl	$LC11, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L65
	orl	$2, -16(%ebp)
	andl	$-3, -20(%ebp)
	jmp	L45
L65:
	movl	%esi, (%esp)
	movl	$LC12, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L67
	orl	$4, -16(%ebp)
	orl	$4, -20(%ebp)
	jmp	L45
L67:
	movl	%esi, (%esp)
	movl	$LC13, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L69
	orl	$4, -16(%ebp)
	andl	$-5, -20(%ebp)
	jmp	L45
L69:
	movl	%esi, (%esp)
	movl	$LC14, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L71
	orl	$1, -16(%ebp)
	orl	$1, -20(%ebp)
	jmp	L45
L71:
	movl	%esi, (%esp)
	movl	$LC15, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L73
	orl	$1, -16(%ebp)
	andl	$-2, -20(%ebp)
	jmp	L45
L73:
	movl	%esi, (%esp)
	movl	$LC16, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L75
	movl	$1, -24(%ebp)
	jmp	L45
L75:
	movl	%esi, (%esp)
	movl	$LC17, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L45
	movl	$8, -24(%ebp)
L45:
	cmpb	$0, (%ebx)
	jne	L78
L103:
	movl	%edi, (%esp)
	movl	$LC18, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L80
	movl	%edi, (%esp)
	movl	$LC19, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L80
	movl	%edi, (%esp)
	movl	$LC20, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L80
	movl	%edi, (%esp)
	movl	$LC21, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L79
L80:
	movl	$1, (%esp)
	movl	$LC22, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_error
	movl	$-1, %eax
	jmp	L32
L79:
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L82
L86:
	movl	%edi, (%esp)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	32(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L82
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L86
L82:
	cmpl	_nsects, %ebx
	jne	L87
	movl	%edi, (%esp)
	movl	$LC7, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L88
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	movl	$6, 8(%esp)
	movl	$16, 12(%esp)
	jmp	L105
L88:
	movl	%edi, (%esp)
	movl	$LC23, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L90
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	movl	$2, 8(%esp)
	jmp	L107
L90:
	movl	%edi, (%esp)
	movl	$LC24, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L92
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	jmp	L108
L92:
	movl	%edi, (%esp)
	movl	$LC25, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L94
	movl	%edi, (%esp)
	movl	$8, 4(%esp)
L108:
	movl	$3, 8(%esp)
L107:
	movl	$4, 12(%esp)
	jmp	L105
L94:
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	movl	$2, 8(%esp)
	movl	$1, 12(%esp)
L105:
	call	_elf_make_section
	movl	%eax, %ebx
	cmpl	$0, -24(%ebp)
	je	L96
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	-24(%ebp), %edx
	movl	%edx, 20(%eax)
L96:
	cmpl	$0, -28(%ebp)
	je	L97
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 24(%eax)
L97:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %edx
	movl	-16(%ebp), %eax
	notl	%eax
	andl	%eax, 28(%edx)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	-20(%ebp), %edx
	orl	%edx, 28(%eax)
	jmp	L98
L87:
	cmpl	$1, 12(%ebp)
	jne	L98
	cmpl	$0, -24(%ebp)
	jne	L101
	cmpl	$0, -28(%ebp)
	jne	L101
	cmpl	$0, -16(%ebp)
	je	L98
L101:
	movl	$0, (%esp)
	movl	$LC26, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_error
L98:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	16(%eax), %eax
L32:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC27:
	.ascii "unrecognised special symbol `%s'\0"
	.align 32
LC28:
	.ascii "cannot use relocatable expression as symbol size\0"
	.align 32
LC29:
	.ascii "strange segment conditions in ELF driver\0"
	.align 32
LC30:
	.ascii "alignment constraint `%s' is not a valid number\0"
	.align 32
LC31:
	.ascii "alignment constraint `%s' is not a power of two\0"
LC32:
	.ascii " \0"
LC33:
	.ascii "function\0"
LC34:
	.ascii "data\0"
LC35:
	.ascii "object\0"
	.align 32
LC36:
	.ascii "unrecognised symbol type `%.*s'\0"
	.align 32
LC37:
	.ascii "no special symbol features supported here\0"
	.align 2
	.def	_elf_deflabel;	.scl	3;	.type	32;	.endef
_elf_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	20(%ebp), %edi
	movl	_strslen, %esi
	movl	$0, -72(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L110
	cmpb	$46, 1(%eax)
	jne	L110
	cmpb	$64, 2(%eax)
	je	L110
	movl	%eax, (%esp)
	movl	$LC2, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC3, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	movl	8(%ebp), %esi
	movl	%esi, (%esp)
	movl	$LC4, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	movl	%esi, (%esp)
	movl	$LC5, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	movl	%esi, (%esp)
	movl	$LC6, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	movl	$1, (%esp)
	movl	$LC27, 4(%esp)
	movl	%esi, 8(%esp)
	call	*_error
	jmp	L109
L110:
	cmpl	$3, %edi
	jne	L112
	movl	$_fwds, %esi
	cmpl	$0, _fwds
	je	L109
L131:
	movl	(%esi), %eax
	movl	32(%eax), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	movl	24(%ebp), %ebx
	testl	%eax, %eax
	je	L118
	jmp	L115
L122:
	incl	%ebx
L118:
	cmpb	$0, (%ebx)
	je	L124
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L122
	jmp	L123
L127:
	incl	%ebx
L123:
	cmpb	$0, (%ebx)
	je	L124
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L127
L124:
	call	_stdscan_reset
	movl	%ebx, _stdscan_bufptr
	movl	$-1, -40(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$1, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %edi
	testl	%eax, %eax
	je	L128
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L129
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
	call	*_error
	jmp	L128
L129:
	movl	(%esi), %ebx
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, 16(%ebx)
L128:
	movl	(%esi), %eax
	movl	32(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%esi), %eax
	movl	28(%eax), %eax
	movl	%eax, (%esi)
	jmp	L109
L115:
	movl	(%esi), %eax
	leal	28(%eax), %esi
	cmpl	$0, 28(%eax)
	je	L109
	jmp	L131
L112:
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	call	_strlen
	incl	%eax
	movl	_strs, %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	addl	_strslen, %eax
	incl	%eax
	movl	%eax, _strslen
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_wstruct
	movl	%eax, %ebx
	movl	%esi, (%eax)
	testl	%edi, %edi
	setne	%al
	movzbl	%al, %eax
	decl	%eax
	andl	$-16, %eax
	addl	$16, %eax
	movl	%eax, 8(%ebx)
	movl	$0, 16(%ebx)
	cmpl	$-1, 12(%ebp)
	jne	L134
	movl	$65521, 4(%ebx)
	jmp	L135
L134:
	movl	$0, 4(%ebx)
	cmpl	$0, _nsects
	jne	L136
	movl	12(%ebp), %edx
	cmpl	_def_seg, %edx
	jne	L136
	movl	$LC7, (%esp)
	movl	$2, 4(%esp)
	leal	-60(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_elf_section_names
	cmpl	%eax, 12(%ebp)
	je	L137
	movl	$3, (%esp)
	movl	$LC29, 4(%esp)
	call	*_error
L137:
	movl	_nsects, %eax
	jmp	L180
L179:
	leal	1(%edx), %eax
L180:
	movl	%eax, 4(%ebx)
	jmp	L135
L136:
	movl	$0, %edx
	cmpl	_nsects, %edx
	jge	L135
	movl	_sects, %ecx
L144:
	movl	(%ecx,%edx,4), %eax
	movl	12(%ebp), %esi
	cmpl	16(%eax), %esi
	je	L179
	incl	%edx
	cmpl	_nsects, %edx
	jl	L144
L135:
	cmpl	$2, %edi
	jne	L145
	movl	16(%ebp), %eax
	movl	%eax, 16(%ebx)
	movl	$0, 12(%ebx)
	movl	$65522, 4(%ebx)
	cmpl	$0, 24(%ebp)
	je	L146
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	leal	-64(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 12(%ebx)
	cmpl	$0, -64(%ebp)
	je	L147
	movl	$1, (%esp)
	movl	$LC30, 4(%esp)
	movl	24(%ebp), %esi
	movl	%esi, 8(%esp)
	jmp	L181
L147:
	movl	12(%ebx), %eax
	leal	-1(%eax), %edx
	orl	%eax, %edx
	leal	-1(%eax,%eax), %eax
	cmpl	%eax, %edx
	je	L146
	movl	$1, (%esp)
	movl	$LC31, 4(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 8(%esp)
L181:
	call	*_error
L146:
	movl	$1, -72(%ebp)
	jmp	L150
L145:
	cmpl	$0, 4(%ebx)
	je	L151
	movl	16(%ebp), %eax
	jmp	L152
L151:
	movl	$0, %eax
L152:
	movl	%eax, 12(%ebx)
L150:
	cmpl	$16, 8(%ebx)
	jne	L153
	cmpl	$0, 4(%ebx)
	je	L155
	cmpl	$65522, 4(%ebx)
	jne	L154
L155:
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	_nglobs, %eax
	movl	%eax, 8(%esp)
	call	_raa_write
	movl	%eax, _bsym
	jmp	L156
L154:
	cmpl	$65521, 4(%ebx)
	je	L156
	movl	4(%ebx), %eax
	sall	$2, %eax
	movl	%eax, %edx
	addl	_sects, %edx
	movl	-4(%edx), %edx
	movl	52(%edx), %edx
	movl	%edx, 24(%ebx)
	addl	_sects, %eax
	movl	-4(%eax), %eax
	movl	%ebx, 52(%eax)
	cmpl	$0, 24(%ebp)
	je	L156
	movl	24(%ebp), %esi
	movl	%esi, (%esp)
	movl	$LC32, 4(%esp)
	call	_strcspn
	movl	%eax, %esi
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC33, 4(%esp)
	movl	%esi, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L159
	orl	$2, 8(%ebx)
	jmp	L160
L159:
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC34, 4(%esp)
	movl	%esi, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	je	L162
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC35, 4(%esp)
	movl	%esi, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L161
L162:
	orl	$1, 8(%ebx)
	jmp	L160
L161:
	movl	$1, (%esp)
	movl	$LC36, 4(%esp)
	movl	%esi, 8(%esp)
	movl	24(%ebp), %edx
	movl	%edx, 12(%esp)
	call	*_error
L160:
	movl	24(%ebp), %eax
	cmpb	$0, (%esi,%eax)
	je	L164
	movl	$0, -68(%ebp)
	movl	_stdscan_bufptr, %edi
	jmp	L165
L169:
	incl	%esi
L165:
	movl	24(%ebp), %edx
	cmpb	$0, (%esi,%edx)
	je	L166
	movsbl	(%esi,%edx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L169
L166:
	call	_stdscan_reset
	movl	24(%ebp), %eax
	addl	%esi, %eax
	movl	%eax, _stdscan_bufptr
	movl	$-1, -56(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-56(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-68(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	cmpl	$0, -68(%ebp)
	je	L170
	movl	_fwds, %eax
	movl	%eax, 28(%ebx)
	movl	%ebx, _fwds
	movl	8(%ebp), %esi
	movl	%esi, (%esp)
	call	_nasm_strdup
	movl	%eax, 32(%ebx)
	jmp	L171
L170:
	testl	%eax, %eax
	je	L171
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L173
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
	call	*_error
	jmp	L171
L173:
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, 16(%ebx)
L171:
	movl	%edi, _stdscan_bufptr
L164:
	movl	$1, -72(%ebp)
L156:
	movl	_nglobs, %eax
	movl	%eax, 20(%ebx)
	incl	_nglobs
	jmp	L175
L153:
	incl	_nlocals
L175:
	cmpl	$0, 24(%ebp)
	je	L109
	cmpl	$0, -72(%ebp)
	jne	L109
	movl	$1, (%esp)
	movl	$LC37, 4(%esp)
	call	*_error
L109:
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_add_reloc;	.scl	3;	.type	32;	.endef
_elf_add_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	48(%edi), %ebx
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, %ebx
	movl	%eax, 48(%edi)
	movl	$0, (%eax)
	movl	4(%edi), %eax
	movl	%eax, 4(%ebx)
	cmpl	$-1, %esi
	jne	L183
	movl	$2, 8(%ebx)
	jmp	L184
L183:
	movl	$0, 8(%ebx)
	movl	$0, %edx
	cmpl	_nsects, %edx
	jge	L193
L190:
	movl	_sects, %eax
	movl	(%eax,%edx,4), %eax
	cmpl	16(%eax), %esi
	jne	L187
	leal	3(%edx), %eax
	movl	%eax, 8(%ebx)
L187:
	incl	%edx
	cmpl	_nsects, %edx
	jl	L190
L193:
	cmpl	$0, 8(%ebx)
	jne	L184
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_raa_read
	addl	$16, %eax
	movl	%eax, 8(%ebx)
L184:
	movl	16(%ebp), %eax
	movl	%eax, 12(%ebx)
	incl	12(%edi)
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC38:
	.ascii "unable to find a suitable global symbol for this reference\0"
	.align 2
	.def	_elf_add_gsym_reloc;	.scl	3;	.type	32;	.endef
_elf_add_gsym_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	movl	$0, %ebx
	movl	$0, %edx
	cmpl	_nsects, %ebx
	jge	L196
	movl	_sects, %ecx
L200:
	movl	(%ecx,%edx,4), %eax
	cmpl	16(%eax), %esi
	je	L224
	incl	%edx
	cmpl	_nsects, %edx
	jl	L200
L196:
	testl	%ebx, %ebx
	jne	L201
	cmpl	$0, 24(%ebp)
	je	L202
	testl	%edi, %edi
	je	L202
	movl	$1, (%esp)
	movl	$LC38, 4(%esp)
	call	*_error
	jmp	L203
L224:
	movl	%eax, %ebx
	jmp	L196
L202:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 8(%esp)
	call	_elf_add_reloc
L203:
	movl	%edi, %eax
	jmp	L194
L201:
	cmpl	$0, 24(%ebp)
	je	L204
	movl	52(%ebx), %esi
	testl	%esi, %esi
	je	L223
L210:
	cmpl	%edi, 12(%esi)
	je	L211
	movl	24(%esi), %esi
	testl	%esi, %esi
	je	L223
	jmp	L210
L204:
	movl	$0, %esi
	movl	52(%ebx), %edx
	testl	%edx, %edx
	je	L211
L218:
	cmpl	%edi, 12(%edx)
	jg	L214
	testl	%esi, %esi
	je	L217
	movl	12(%edx), %eax
	cmpl	12(%esi), %eax
	jle	L214
L217:
	movl	%edx, %esi
L214:
	movl	24(%edx), %edx
	testl	%edx, %edx
	jne	L218
L211:
	testl	%esi, %esi
	jne	L219
L223:
	cmpl	$0, 24(%ebp)
	je	L219
	movl	$1, (%esp)
	movl	$LC38, 4(%esp)
	call	*_error
	movl	$0, %eax
	jmp	L194
L219:
	movl	8(%ebp), %ecx
	movl	48(%ecx), %ebx
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	8(%ebp), %edx
	movl	%eax, 48(%edx)
	movl	$0, (%eax)
	movl	8(%ebp), %ecx
	movl	4(%ecx), %edx
	movl	%edx, 4(%eax)
	movl	20(%esi), %edx
	addl	$16, %edx
	movl	%edx, 8(%eax)
	movl	20(%ebp), %edx
	movl	%edx, 12(%eax)
	incl	12(%ecx)
	movl	%edi, %eax
	subl	12(%esi), %eax
L194:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.lcomm _sinfo.0,16
	.align 32
LC39:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC40:
	.ascii "attempt to initialise memory in BSS section `%s': ignored\0"
	.align 32
LC41:
	.ascii "uninitialised space declared in non-BSS section `%s': zeroing\0"
	.align 32
LC42:
	.ascii "OUT_RAWDATA with other than NO_SEG\0"
	.align 32
LC43:
	.ascii "ELF format does not support segment base references\0"
	.align 32
LC44:
	.ascii "ELF format cannot produce non-PC-relative PLT references\0"
	.align 32
LC45:
	.ascii "ELF format does not support this use of WRT\0"
	.align 32
LC46:
	.ascii "16-bit relocations in ELF is a GNU extension\0"
	.align 32
LC47:
	.ascii "Unsupported non-32-bit ELF relocation\0"
LC48:
	.ascii "intra-segment OUT_REL2ADR\0"
LC49:
	.ascii "intra-segment OUT_REL4ADR\0"
	.align 32
LC50:
	.ascii "ELF format cannot produce PC-relative GOT references\0"
	.align 2
	.def	_elf_out;	.scl	3;	.type	32;	.endef
_elf_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %edi
	movl	16(%ebp), %esi
	movl	%esi, %eax
	andl	$268435455, %eax
	movl	%eax, -28(%ebp)
	andl	$-268435456, %esi
	cmpl	$-1, %edi
	jne	L226
	cmpl	$1073741824, %esi
	je	L225
	movl	$1, (%esp)
	movl	$LC39, 4(%esp)
	call	*_error
	jmp	L225
L309:
	movl	%eax, -24(%ebp)
	jmp	L229
L226:
	movl	$0, -24(%ebp)
	movl	$0, %ebx
	movl	$0, %edx
	cmpl	_nsects, %edx
	jge	L229
	movl	_sects, %edx
L233:
	movl	(%edx,%ebx,4), %eax
	cmpl	16(%eax), %edi
	je	L309
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L233
L229:
	cmpl	$0, -24(%ebp)
	jne	L234
	movl	$LC7, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_elf_section_names
	cmpl	%eax, %edi
	je	L235
	movl	$3, (%esp)
	movl	$LC29, 4(%esp)
	call	*_error
	jmp	L234
L235:
	movl	_nsects, %edx
	movl	_sects, %eax
	movl	-4(%eax,%edx,4), %eax
	movl	%eax, -24(%ebp)
	leal	-1(%edx), %ebx
L234:
	cmpl	$0, _of_elf+16
	je	L237
	movl	-24(%ebp), %ecx
	movl	4(%ecx), %eax
	movl	%eax, _sinfo.0
	movl	%ebx, _sinfo.0+4
	movl	32(%ecx), %eax
	movl	%eax, _sinfo.0+8
	movl	$64, (%esp)
	movl	$_sinfo.0, 4(%esp)
	movl	_of_elf+16, %eax
	call	*28(%eax)
L237:
	movl	-24(%ebp), %eax
	cmpl	$8, 20(%eax)
	jne	L238
	cmpl	$1073741824, %esi
	je	L308
	movl	$0, (%esp)
	movl	$LC40, 4(%esp)
	movl	32(%eax), %eax
	movl	%eax, 8(%esp)
	call	*_error
	cmpl	$536870912, %esi
	jne	L239
	movl	$2, -28(%ebp)
	jmp	L240
L239:
	cmpl	$805306368, %esi
	jne	L240
	movl	$4, -28(%ebp)
L240:
	movl	-28(%ebp), %ecx
	movl	-24(%ebp), %eax
	addl	%ecx, 4(%eax)
	jmp	L225
L238:
	cmpl	$1073741824, %esi
	jne	L242
L308:
	movl	-24(%ebp), %edx
	cmpl	$1, 20(%edx)
	jne	L243
	movl	$0, (%esp)
	movl	$LC41, 4(%esp)
	movl	32(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	-24(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	$0, 4(%esp)
	jmp	L319
L243:
	movl	-28(%ebp), %edx
	movl	-24(%ebp), %ecx
	addl	%edx, 4(%ecx)
	jmp	L225
L242:
	testl	%esi, %esi
	jne	L246
	cmpl	$-1, 20(%ebp)
	je	L247
	movl	$3, (%esp)
	movl	$LC42, 4(%esp)
	call	*_error
L247:
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	-28(%ebp), %ecx
	movl	%ecx, 8(%esp)
	jmp	L318
L246:
	cmpl	$268435456, %esi
	jne	L249
	movl	$0, %edi
	movl	12(%ebp), %eax
	movl	(%eax), %esi
	cmpl	$-1, 20(%ebp)
	je	L250
	testl	$1, 20(%ebp)
	je	L251
	movl	$1, (%esp)
	movl	$LC43, 4(%esp)
	jmp	L310
L251:
	cmpl	$-1, 24(%ebp)
	jne	L253
	cmpl	$2, -28(%ebp)
	jne	L254
	movl	$1, %edi
	movl	-24(%ebp), %edx
	movl	%edx, (%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$20, 8(%esp)
	jmp	L313
L254:
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$1, 8(%esp)
	jmp	L313
L253:
	movl	_elf_gotpc_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L257
	movl	-24(%ebp), %ecx
	addl	4(%ecx), %esi
	movl	%ecx, (%esp)
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$10, 8(%esp)
	jmp	L313
L257:
	movl	_elf_gotoff_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L259
	movl	-24(%ebp), %edx
	movl	%edx, (%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$9, 8(%esp)
L313:
	call	_elf_add_reloc
	jmp	L250
L259:
	movl	_elf_got_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L261
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	$3, 12(%esp)
	movl	$1, 16(%esp)
	jmp	L312
L261:
	movl	_elf_sym_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L263
	cmpl	$2, -28(%ebp)
	jne	L264
	movl	$1, %edi
	movl	-24(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	movl	$20, 12(%esp)
	jmp	L311
L264:
	movl	-24(%ebp), %edx
	movl	%edx, (%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	$1, 12(%esp)
L311:
	movl	$0, 16(%esp)
L312:
	call	_elf_add_gsym_reloc
	movl	%eax, %esi
	jmp	L250
L263:
	movl	_elf_plt_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L267
	movl	$1, (%esp)
	movl	$LC44, 4(%esp)
	jmp	L310
L267:
	movl	$1, (%esp)
	movl	$LC45, 4(%esp)
L310:
	call	*_error
L250:
	leal	-20(%ebp), %ebx
	testl	%edi, %edi
	je	L269
	movl	$1280, (%esp)
	movl	$LC46, 4(%esp)
	call	*_error
	movl	%esi, %eax
	movb	%al, -20(%ebp)
	movl	%esi, %eax
	sarl	$8, %eax
	jmp	L314
L269:
	cmpl	$4, -28(%ebp)
	je	L274
	cmpl	$-1, 20(%ebp)
	je	L274
	movl	$1, (%esp)
	movl	$LC47, 4(%esp)
	call	*_error
L274:
	movl	%esi, %edx
	movb	%dl, (%ebx)
	incl	%ebx
	movl	%esi, %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	%esi, %eax
	sarl	$16, %eax
	movb	%al, (%ebx)
	movl	%esi, %eax
	sarl	$24, %eax
L314:
	movb	%al, 1(%ebx)
	movl	-24(%ebp), %ecx
	movl	%ecx, (%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
L319:
	movl	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	jmp	L318
L249:
	cmpl	$536870912, %esi
	jne	L281
	cmpl	%edi, 20(%ebp)
	jne	L282
	movl	$3, (%esp)
	movl	$LC48, 4(%esp)
	call	*_error
L282:
	cmpl	$-1, 20(%ebp)
	je	L283
	testl	$1, 20(%ebp)
	je	L283
	movl	$1, (%esp)
	movl	$LC43, 4(%esp)
	jmp	L315
L283:
	cmpl	$-1, 24(%ebp)
	jne	L285
	movl	$1280, (%esp)
	movl	$LC46, 4(%esp)
	call	*_error
	movl	-24(%ebp), %edx
	movl	%edx, (%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$21, 8(%esp)
	call	_elf_add_reloc
	jmp	L284
L285:
	movl	$1, (%esp)
	movl	$LC47, 4(%esp)
L315:
	call	*_error
L284:
	leal	-20(%ebp), %ebx
	movl	12(%ebp), %edx
	movzbl	(%edx), %eax
	subb	-28(%ebp), %al
	movb	%al, -20(%ebp)
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	subl	-28(%ebp), %eax
	sarl	$8, %eax
	movb	%al, 1(%ebx)
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$2, 8(%esp)
	jmp	L318
L281:
	cmpl	$805306368, %esi
	jne	L225
	cmpl	%edi, 20(%ebp)
	jne	L292
	movl	$3, (%esp)
	movl	$LC49, 4(%esp)
	call	*_error
L292:
	cmpl	$-1, 20(%ebp)
	je	L293
	testl	$1, 20(%ebp)
	je	L293
	movl	$1, (%esp)
	movl	$LC43, 4(%esp)
	jmp	L316
L293:
	cmpl	$-1, 24(%ebp)
	jne	L295
	movl	-24(%ebp), %edx
	movl	%edx, (%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$2, 8(%esp)
	jmp	L317
L295:
	movl	_elf_plt_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L297
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$4, 8(%esp)
L317:
	call	_elf_add_reloc
	jmp	L294
L297:
	movl	_elf_gotpc_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L300
	movl	_elf_gotoff_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L300
	movl	_elf_got_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L299
L300:
	movl	$1, (%esp)
	movl	$LC50, 4(%esp)
	jmp	L316
L299:
	movl	$1, (%esp)
	movl	$LC45, 4(%esp)
L316:
	call	*_error
L294:
	leal	-20(%ebp), %ebx
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	subb	-28(%ebp), %al
	movl	%ebx, %edx
	movb	%al, -20(%ebp)
	incl	%ebx
	movl	(%ecx), %eax
	subl	-28(%ebp), %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	(%ecx), %eax
	subl	-28(%ebp), %eax
	sarl	$16, %eax
	movb	%al, (%ebx)
	movl	(%ecx), %eax
	subl	-28(%ebp), %eax
	sarl	$24, %eax
	movb	%al, 1(%ebx)
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	movl	$4, 8(%esp)
L318:
	call	_elf_sect_write
L225:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC51:
	.ascii ".rel\0"
LC52:
	.ascii ".stab\0"
LC53:
	.ascii ".stabstr\0"
LC54:
	.ascii "The Netwide Assembler %s\0"
LC55:
	.ascii "0.98.38\0"
LC56:
	.ascii "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\0"
	.align 2
	.def	_elf_write;	.scl	3;	.type	32;	.endef
_elf_write:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$156, %esp
	cmpl	$_df_stabs, _of_elf+16
	jne	L321
	movl	$8, -100(%ebp)
	jmp	L322
L321:
	movl	$5, -100(%ebp)
L322:
	movl	$LC1, (%esp)
	movl	$LC18, 4(%esp)
	call	_add_sectname
	movl	$LC1, (%esp)
	movl	$LC19, 4(%esp)
	call	_add_sectname
	movl	$LC1, (%esp)
	movl	$LC20, 4(%esp)
	call	_add_sectname
	movl	$LC1, (%esp)
	movl	$LC21, 4(%esp)
	call	_add_sectname
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L352
L328:
	incl	-100(%ebp)
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %eax
	cmpl	$0, 44(%eax)
	je	L325
	incl	-100(%ebp)
	movl	$LC51, (%esp)
	movl	(%edx,%ebx,4), %eax
	movl	32(%eax), %eax
	movl	%eax, 4(%esp)
	call	_add_sectname
L325:
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L328
L352:
	cmpl	$_df_stabs, _of_elf+16
	jne	L329
	movl	$LC1, (%esp)
	movl	$LC52, 4(%esp)
	call	_add_sectname
	movl	$LC1, (%esp)
	movl	$LC53, 4(%esp)
	call	_add_sectname
	movl	$LC51, (%esp)
	movl	$LC52, 4(%esp)
	call	_add_sectname
L329:
	movb	$0, -88(%ebp)
	leal	-87(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC54, 4(%esp)
	movl	$LC55, 8(%esp)
	call	_sprintf
	movl	%eax, -108(%ebp)
	addl	$2, -108(%ebp)
	movl	$LC56, (%esp)
	movl	$16, 4(%esp)
	movl	$1, 8(%esp)
	movl	_elffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	movl	$1, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$3, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$1, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$64, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$52, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$40, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_nsects, %eax
	addl	$2, %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	leal	-96(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_elf_build_symtab
	movl	%eax, -112(%ebp)
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L354
L335:
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %esi
	cmpl	$0, 44(%esi)
	je	L332
	leal	40(%esi), %eax
	movl	%eax, (%esp)
	movl	(%edx,%ebx,4), %eax
	movl	44(%eax), %eax
	movl	%eax, 4(%esp)
	call	_elf_build_reltab
	movl	%eax, 36(%esi)
L332:
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L335
L354:
	movl	-100(%ebp), %edx
	leal	(%edx,%edx,4), %eax
	sall	$3, %eax
	leal	64(%eax), %edx
	addl	$79, %eax
	andl	$-16, %eax
	subl	%edx, %eax
	movl	%eax, -104(%ebp)
	addl	%eax, %edx
	movl	%edx, _elf_foffs
	movl	$0, _elf_nsect
	movl	_nsects, %eax
	leal	(%eax,%eax,2), %eax
	leal	120(,%eax,8), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, _elf_sects
	movl	$0, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	$0, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	movl	$1, %edi
	movl	_shstrtab, %esi
	incl	%esi
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L356
L342:
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %eax
	movl	20(%eax), %eax
	movl	%eax, 4(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	28(%eax), %eax
	movl	%eax, 8(%esp)
	movl	(%edx,%ebx,4), %eax
	cmpl	$1, 20(%eax)
	jne	L340
	movl	(%eax), %eax
	jmp	L341
L340:
	movl	$0, %eax
L341:
	movl	%eax, 12(%esp)
	movl	$1, 16(%esp)
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %eax
	movl	4(%eax), %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	24(%eax), %eax
	movl	%eax, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	incl	%edi
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L342
L356:
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	leal	-88(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	-108(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	$1, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	incl	%edi
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	_shstrtab, %edx
	movl	%esi, %eax
	subl	%edx, %eax
	movl	%eax, (%esp)
	movl	$3, 4(%esp)
	movl	$0, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$0, 16(%esp)
	movl	_shstrtablen, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	$1, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	incl	%edi
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$2, 4(%esp)
	movl	$0, 8(%esp)
	movl	-112(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	$1, 16(%esp)
	movl	-92(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	_nsects, %eax
	addl	$4, %eax
	movl	%eax, 24(%esp)
	movl	-96(%ebp), %eax
	movl	%eax, 28(%esp)
	movl	$4, 32(%esp)
	movl	$16, 36(%esp)
	call	_elf_section_header
	movl	%edi, _symtabsection
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$3, 4(%esp)
	movl	$0, 8(%esp)
	movl	_strs, %eax
	movl	%eax, 12(%esp)
	movl	$1, 16(%esp)
	movl	_strslen, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	$1, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L358
L348:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 44(%eax)
	je	L345
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$9, 4(%esp)
	movl	$0, 8(%esp)
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %eax
	movl	36(%eax), %eax
	movl	%eax, 12(%esp)
	movl	$1, 16(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	40(%eax), %eax
	movl	%eax, 20(%esp)
	movl	_nsects, %eax
	addl	$3, %eax
	movl	%eax, 24(%esp)
	leal	1(%ebx), %eax
	movl	%eax, 28(%esp)
	movl	$4, 32(%esp)
	movl	$8, 36(%esp)
	call	_elf_section_header
L345:
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L348
L358:
	cmpl	$_df_stabs, _of_elf+16
	jne	L349
	call	_stabs_generate
	cmpl	$0, _stabbuf
	je	L349
	cmpl	$0, _stabstrbuf
	je	L349
	cmpl	$0, _stabrelbuf
	je	L349
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	movl	_stabbuf, %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	_stablen, %eax
	movl	%eax, 20(%esp)
	movl	-100(%ebp), %eax
	subl	$2, %eax
	movl	%eax, 24(%esp)
	movl	$0, 28(%esp)
	movl	$4, 32(%esp)
	movl	$12, 36(%esp)
	call	_elf_section_header
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$3, 4(%esp)
	movl	$0, 8(%esp)
	movl	_stabstrbuf, %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	_stabstrlen, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	movl	$4, 32(%esp)
	movl	$0, 36(%esp)
	call	_elf_section_header
	movl	%esi, (%esp)
	call	_strlen
	leal	1(%eax,%esi), %esi
	movl	%esi, %eax
	subl	_shstrtab, %eax
	movl	%eax, (%esp)
	movl	$9, 4(%esp)
	movl	$0, 8(%esp)
	movl	_stabrelbuf, %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	_stabrellen, %eax
	movl	%eax, 20(%esp)
	movl	_symtabsection, %eax
	movl	%eax, 24(%esp)
	movl	-100(%ebp), %eax
	subl	$3, %eax
	movl	%eax, 28(%esp)
	movl	$4, 32(%esp)
	movl	$8, 36(%esp)
	call	_elf_section_header
L349:
	movl	$_align_str, (%esp)
	movl	-104(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	movl	_elffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	call	_elf_write_sections
	movl	_elf_sects, %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-112(%ebp), %edx
	movl	%edx, (%esp)
	call	_saa_free
	addl	$156, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_build_symtab;	.scl	3;	.type	32;	.endef
_elf_build_symtab:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, -44(%ebp)
	movl	$0, (%esi)
	movl	$0, (%edi)
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$16, 8(%esp)
	call	_saa_wbytes
	addl	$16, (%edi)
	incl	(%esi)
	leal	-40(%ebp), %eax
	movb	$1, -40(%ebp)
	movb	$0, -39(%ebp)
	movb	$0, -38(%ebp)
	movb	$0, -37(%ebp)
	movb	$0, -36(%ebp)
	movb	$0, -35(%ebp)
	movb	$0, -34(%ebp)
	movb	$0, -33(%ebp)
	movb	$0, -32(%ebp)
	movb	$0, -31(%ebp)
	movb	$0, -30(%ebp)
	movb	$0, -29(%ebp)
	movb	$4, -28(%ebp)
	movb	$0, -27(%ebp)
	movb	$-15, -26(%ebp)
	movb	$-1, -25(%ebp)
	movl	-44(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	call	_saa_wbytes
	addl	$16, (%edi)
	incl	(%esi)
	movl	$1, %ebx
	movl	_nsects, %eax
	incl	%eax
	cmpl	%eax, %ebx
	jg	L464
L410:
	movb	$0, -40(%ebp)
	movb	$0, -39(%ebp)
	movb	$0, -38(%ebp)
	movb	$0, -37(%ebp)
	movb	$0, -36(%ebp)
	movb	$0, -35(%ebp)
	movb	$0, -34(%ebp)
	movb	$0, -33(%ebp)
	movb	$0, -32(%ebp)
	movb	$0, -31(%ebp)
	movb	$0, -30(%ebp)
	movb	$0, -29(%ebp)
	movb	$3, -28(%ebp)
	movb	$0, -27(%ebp)
	leal	-26(%ebp), %ecx
	leal	-25(%ebp), %eax
	movb	$-15, %dl
	cmpl	$1, %ebx
	je	L406
	movb	%bl, %dl
	decb	%dl
L406:
	movb	%dl, (%ecx)
	movl	%eax, %edx
	cmpl	$1, %ebx
	je	L408
	leal	-1(%ebx), %eax
	shrl	$8, %eax
	jmp	L409
L408:
	movb	$-1, %al
L409:
	movb	%al, (%edx)
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	call	_saa_wbytes
	addl	$16, (%edi)
	incl	(%esi)
	incl	%ebx
	movl	_nsects, %eax
	incl	%eax
	cmpl	%eax, %ebx
	jle	L410
L464:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	jmp	L411
L436:
	testb	$16, 8(%edx)
	jne	L411
	movzbl	(%edx), %eax
	movb	%al, -40(%ebp)
	movl	(%edx), %eax
	sarl	$8, %eax
	movb	%al, -39(%ebp)
	movswl	2(%edx),%eax
	movb	%al, -38(%ebp)
	movsbl	3(%edx),%eax
	movb	%al, -37(%ebp)
	movzbl	12(%edx), %eax
	movb	%al, -36(%ebp)
	movl	12(%edx), %eax
	sarl	$8, %eax
	movb	%al, -35(%ebp)
	movswl	14(%edx),%eax
	movb	%al, -34(%ebp)
	movsbl	15(%edx),%eax
	movb	%al, -33(%ebp)
	movzbl	16(%edx), %eax
	movb	%al, -32(%ebp)
	movl	16(%edx), %eax
	sarl	$8, %eax
	movb	%al, -31(%ebp)
	movswl	18(%edx),%eax
	movb	%al, -30(%ebp)
	movsbl	19(%edx),%eax
	movb	%al, -29(%ebp)
	movzbl	8(%edx), %eax
	movb	%al, -28(%ebp)
	movl	8(%edx), %eax
	sarl	$8, %eax
	movb	%al, -27(%ebp)
	movzbl	4(%edx), %eax
	movb	%al, -26(%ebp)
	movl	4(%edx), %eax
	sarl	$8, %eax
	movb	%al, -25(%ebp)
	movl	-44(%ebp), %edx
	movl	%edx, (%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	call	_saa_wbytes
	addl	$16, (%edi)
	incl	(%esi)
L411:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %edx
	testl	%eax, %eax
	jne	L436
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	jmp	L437
L462:
	testb	$16, 8(%edx)
	je	L437
	movzbl	(%edx), %eax
	movb	%al, -40(%ebp)
	movl	(%edx), %eax
	sarl	$8, %eax
	movb	%al, -39(%ebp)
	movswl	2(%edx),%eax
	movb	%al, -38(%ebp)
	movsbl	3(%edx),%eax
	movb	%al, -37(%ebp)
	movzbl	12(%edx), %eax
	movb	%al, -36(%ebp)
	movl	12(%edx), %eax
	sarl	$8, %eax
	movb	%al, -35(%ebp)
	movswl	14(%edx),%eax
	movb	%al, -34(%ebp)
	movsbl	15(%edx),%eax
	movb	%al, -33(%ebp)
	movzbl	16(%edx), %eax
	movb	%al, -32(%ebp)
	movl	16(%edx), %eax
	sarl	$8, %eax
	movb	%al, -31(%ebp)
	movswl	18(%edx),%eax
	movb	%al, -30(%ebp)
	movsbl	19(%edx),%eax
	movb	%al, -29(%ebp)
	movzbl	8(%edx), %eax
	movb	%al, -28(%ebp)
	movl	8(%edx), %eax
	sarl	$8, %eax
	movb	%al, -27(%ebp)
	movzbl	4(%edx), %eax
	movb	%al, -26(%ebp)
	movl	4(%edx), %eax
	sarl	$8, %eax
	movb	%al, -25(%ebp)
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	call	_saa_wbytes
	addl	$16, (%edi)
L437:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %edx
	testl	%eax, %eax
	jne	L462
	movl	-44(%ebp), %eax
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_build_reltab;	.scl	3;	.type	32;	.endef
_elf_build_reltab:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	$0, %eax
	testl	%esi, %esi
	je	L465
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, -28(%ebp)
	movl	$0, (%edi)
	testl	%esi, %esi
	je	L483
L481:
	movl	8(%esi), %ecx
	cmpl	$15, %ecx
	jle	L470
	movl	_nsects, %eax
	addl	_nlocals, %eax
	leal	-13(%eax,%ecx), %ecx
L470:
	leal	-24(%ebp), %edx
	movzbl	4(%esi), %eax
	movl	%edx, %ebx
	movb	%al, -24(%ebp)
	incl	%edx
	movl	4(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	6(%esi),%eax
	movb	%al, (%edx)
	incl	%edx
	movsbl	7(%esi),%eax
	movb	%al, (%edx)
	incl	%edx
	sall	$8, %ecx
	movzbl	12(%esi), %eax
	addb	%cl, %al
	movb	%al, (%edx)
	incl	%edx
	movl	%ecx, %eax
	addl	12(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movl	%ecx, %eax
	addl	12(%esi), %eax
	sarl	$16, %eax
	movb	%al, (%edx)
	addl	12(%esi), %ecx
	sarl	$24, %ecx
	movb	%cl, 1(%edx)
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$8, 8(%esp)
	call	_saa_wbytes
	addl	$8, (%edi)
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L481
L483:
	movl	-28(%ebp), %eax
L465:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_section_header;	.scl	3;	.type	32;	.endef
_elf_section_header:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	12(%ebp), %ebx
	movl	20(%ebp), %edi
	movl	28(%ebp), %esi
	movl	_elf_nsect, %eax
	leal	(%eax,%eax,2), %eax
	movl	_elf_sects, %edx
	movl	%edi, (%edx,%eax,4)
	movl	_elf_nsect, %eax
	leal	(%eax,%eax,2), %eax
	movl	_elf_sects, %edx
	movl	%esi, 4(%edx,%eax,4)
	movl	_elf_nsect, %eax
	leal	(%eax,%eax,2), %eax
	movl	24(%ebp), %ecx
	movl	_elf_sects, %edx
	movl	%ecx, 8(%edx,%eax,4)
	incl	_elf_nsect
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	%ebx, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L486
	movl	_elf_foffs, %eax
L486:
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	%esi, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	testl	%edi, %edi
	je	L487
	leal	15(%esi), %eax
	andl	$-16, %eax
	addl	%eax, _elf_foffs
L487:
	movl	32(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	36(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	40(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	44(%ebp), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_write_sections;	.scl	3;	.type	32;	.endef
_elf_write_sections:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$0, %esi
	cmpl	_elf_nsect, %esi
	jge	L498
L496:
	movl	_elf_sects, %ecx
	leal	(%esi,%esi,2), %eax
	leal	0(,%eax,4), %edx
	cmpl	$0, (%ecx,%edx)
	je	L491
	movl	4(%ecx,%edx), %ebx
	leal	15(%ebx), %eax
	andl	$-16, %eax
	movl	%eax, %edi
	subl	%ebx, %edi
	cmpl	$0, 8(%ecx,%edx)
	je	L494
	movl	(%ecx,%edx), %eax
	movl	%eax, (%esp)
	movl	_elffp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	jmp	L495
L494:
	leal	(%esi,%esi,2), %edx
	movl	_elf_sects, %eax
	movl	(%eax,%edx,4), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	movl	_elffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
L495:
	movl	$_align_str, (%esp)
	movl	%edi, 4(%esp)
	movl	$1, 8(%esp)
	movl	_elffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
L491:
	incl	%esi
	cmpl	_elf_nsect, %esi
	jl	L496
L498:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_elf_sect_write;	.scl	3;	.type	32;	.endef
_elf_sect_write:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	16(%ebp), %esi
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_saa_wbytes
	addl	%esi, 4(%ebx)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_elf_segbase;	.scl	3;	.type	32;	.endef
_elf_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.align 2
	.def	_elf_directive;	.scl	3;	.type	32;	.endef
_elf_directive:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
LC57:
	.ascii ".o\0"
	.align 2
	.def	_elf_filename;	.scl	3;	.type	32;	.endef
_elf_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	$_elf_module, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC57, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC58:
	.ascii "%define __SECT__ [section .text]\0"
LC59:
	.ascii "%macro __NASM_CDecl__ 1\0"
LC60:
	.ascii "%define $_%1 $%1\0"
LC61:
	.ascii "%endmacro\0"
	.data
	.align 4
_elf_stdmac:
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	0
	.text
	.align 2
	.def	_elf_set_info;	.scl	3;	.type	32;	.endef
_elf_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.align 32
LC62:
	.ascii "ELF32 (i386) stabs debug format for Linux\0"
LC63:
	.ascii "stabs\0"
	.data
	.align 32
_df_stabs:
	.long	LC62
	.long	LC63
	.long	_stabs_init
	.long	_stabs_linenum
	.long	_stabs_deflabel
	.long	_stabs_directive
	.long	_stabs_typevalue
	.long	_stabs_output
	.long	_stabs_cleanup
.globl _elf_debugs_arr
	.align 4
_elf_debugs_arr:
	.long	_df_stabs
	.long	0
.globl _of_elf
	.text
	.align 32
LC64:
	.ascii "ELF32 (i386) object files (e.g. Linux)\0"
LC65:
	.ascii "elf\0"
	.data
	.align 32
_of_elf:
	.long	LC64
	.long	LC65
	.long	0
	.long	_elf_debugs_arr
	.long	_null_debug_form
	.long	_elf_stdmac
	.long	_elf_init
	.long	_elf_set_info
	.long	_elf_out
	.long	_elf_deflabel
	.long	_elf_section_names
	.long	_elf_segbase
	.long	_elf_directive
	.long	_elf_filename
	.long	_elf_cleanup
	.text
	.align 2
.globl _stabs_init
	.def	_stabs_init;	.scl	2;	.type	32;	.endef
_stabs_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _stabs_linenum
	.def	_stabs_linenum;	.scl	2;	.type	32;	.endef
_stabs_linenum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	cmpl	$0, _stabs_filename
	je	L509
	movl	_stabs_filename, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L507
L509:
	movl	%ebx, (%esp)
	call	_strlen
	incl	%eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, _stabs_filename
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
L507:
	movl	$1, _stabs_immcall
	movl	12(%ebp), %eax
	movl	%eax, _currentline
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _stabs_deflabel
	.def	_stabs_deflabel;	.scl	2;	.type	32;	.endef
_stabs_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _stabs_directive
	.def	_stabs_directive;	.scl	2;	.type	32;	.endef
_stabs_directive:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _stabs_typevalue
	.def	_stabs_typevalue;	.scl	2;	.type	32;	.endef
_stabs_typevalue:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _stabs_output
	.def	_stabs_output;	.scl	2;	.type	32;	.endef
_stabs_output:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	12(%ebp), %ebx
	cmpl	$64, 8(%ebp)
	jne	L514
	cmpl	$0, _stabs_immcall
	je	L514
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC7, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L513
	incl	_numlinestabs
	movl	$28, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	(%ebx), %eax
	movl	%eax, (%edx)
	movl	4(%ebx), %eax
	movl	%eax, 4(%edx)
	movl	8(%ebx), %eax
	movl	%eax, 8(%edx)
	movl	_currentline, %eax
	movl	%eax, 12(%edx)
	movl	_stabs_filename, %eax
	movl	%eax, 16(%edx)
	movl	$0, 20(%edx)
	cmpl	$0, _stabslines
	je	L517
	movl	_stabslines, %eax
	movl	24(%eax), %eax
	movl	%edx, 20(%eax)
	movl	_stabslines, %eax
	movl	%edx, 24(%eax)
	jmp	L514
L517:
	movl	%edx, _stabslines
	movl	%edx, 24(%edx)
L514:
	movl	$0, _stabs_immcall
L513:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _stabs_generate
	.def	_stabs_generate;	.scl	2;	.type	32;	.endef
_stabs_generate:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	_stabslines, %eax
	movl	%eax, -48(%ebp)
	movl	_numlinestabs, %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, -40(%ebp)
	movl	$0, %edi
	cmpl	$0, _numlinestabs
	jle	L661
L524:
	movl	-40(%ebp), %edx
	movl	$0, (%edx,%edi,4)
	incl	%edi
	cmpl	_numlinestabs, %edi
	jl	L524
L661:
	movl	$0, -16(%ebp)
	cmpl	$0, -48(%ebp)
	je	L663
L537:
	cmpl	$0, -16(%ebp)
	jne	L528
	movl	-48(%ebp), %ecx
	movl	16(%ecx), %eax
	movl	-40(%ebp), %edx
	movl	%eax, (%edx)
	movl	$1, -16(%ebp)
	jmp	L529
L528:
	movl	$0, %edi
	cmpl	-16(%ebp), %edi
	jge	L673
L535:
	movl	-40(%ebp), %ecx
	movl	(%ecx,%edi,4), %eax
	movl	%eax, (%esp)
	movl	-48(%ebp), %edx
	movl	16(%edx), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L531
	incl	%edi
	cmpl	-16(%ebp), %edi
	jl	L535
	jmp	L673
L531:
	cmpl	-16(%ebp), %edi
	jl	L529
L673:
	movl	-48(%ebp), %ecx
	movl	16(%ecx), %eax
	movl	-40(%ebp), %edx
	movl	%eax, (%edx,%edi,4)
	incl	-16(%ebp)
L529:
	movl	-48(%ebp), %ecx
	movl	20(%ecx), %ecx
	movl	%ecx, -48(%ebp)
	testl	%ecx, %ecx
	jne	L537
L663:
	movl	$1, %ebx
	movl	-16(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, -44(%ebp)
	movl	$0, %edi
	cmpl	-16(%ebp), %edi
	jge	L666
L542:
	movl	-44(%ebp), %eax
	movl	%ebx, (%eax,%edi,4)
	movl	-40(%ebp), %edx
	movl	(%edx,%edi,4), %eax
	movl	%eax, (%esp)
	call	_strlen
	leal	1(%eax,%ebx), %ebx
	incl	%edi
	cmpl	-16(%ebp), %edi
	jl	L542
L666:
	movl	$0, -24(%ebp)
	movl	$0, %edi
	cmpl	-16(%ebp), %edi
	jge	L544
L548:
	movl	-40(%ebp), %ecx
	movl	(%ecx,%edi,4), %eax
	movl	%eax, (%esp)
	movl	$_elf_module, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L545
	movl	%edi, -24(%ebp)
	jmp	L544
L545:
	incl	%edi
	cmpl	-16(%ebp), %edi
	jl	L548
L544:
	movl	_numlinestabs, %eax
	leal	(%eax,%eax,2), %eax
	leal	36(,%eax,8), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, -28(%ebp)
	movl	%ebx, (%esp)
	call	_nasm_malloc
	movl	%eax, -32(%ebp)
	movl	_numlinestabs, %eax
	leal	(%eax,%eax,4), %eax
	sall	$3, %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, -36(%ebp)
	movl	%eax, %esi
	movl	$0, %edi
	cmpl	-16(%ebp), %edi
	jge	L669
L553:
	movl	-32(%ebp), %eax
	movl	-44(%ebp), %edx
	addl	(%edx,%edi,4), %eax
	movl	%eax, (%esp)
	movl	-40(%ebp), %ecx
	movl	(%ecx,%edi,4), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	incl	%edi
	cmpl	-16(%ebp), %edi
	jl	L553
L669:
	movl	-32(%ebp), %eax
	movb	$0, (%eax)
	movl	%ebx, _stabstrlen
	movl	-44(%ebp), %edx
	movzbl	(%edx), %eax
	movl	-28(%ebp), %ecx
	movb	%al, (%ecx)
	movl	(%edx), %eax
	sarl	$8, %eax
	movb	%al, 1(%ecx)
	movswl	2(%edx),%eax
	movb	%al, 2(%ecx)
	movsbl	3(%edx),%eax
	movb	%al, 3(%ecx)
	movb	$0, 4(%ecx)
	movb	$0, 5(%ecx)
	movb	$0, 6(%ecx)
	movb	$0, 7(%ecx)
	movl	-40(%ebp), %edx
	movl	(%edx), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	-28(%ebp), %ecx
	movb	%al, 8(%ecx)
	movl	-40(%ebp), %edx
	movl	(%edx), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	call	_strlen
	sarl	$8, %eax
	movl	-28(%ebp), %ecx
	movb	%al, 9(%ecx)
	movl	-40(%ebp), %edx
	movl	(%edx), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	call	_strlen
	sarl	$16, %eax
	movl	-28(%ebp), %ecx
	movb	%al, 10(%ecx)
	movl	-40(%ebp), %edx
	movl	(%edx), %eax
	addl	$12, %eax
	movl	%eax, (%esp)
	movl	%ecx, %ebx
	addl	$12, %ebx
	call	_strlen
	sarl	$24, %eax
	movl	-28(%ebp), %ecx
	movb	%al, 11(%ecx)
	movl	_stabslines, %eax
	movl	%eax, -48(%ebp)
	movl	$0, -20(%ebp)
	testl	%eax, %eax
	je	L671
	movl	-24(%ebp), %edx
	movl	-44(%ebp), %ecx
	movzbl	(%ecx,%edx,4), %eax
	movl	-28(%ebp), %edx
	movb	%al, 12(%edx)
	movl	-24(%ebp), %edx
	movl	(%ecx,%edx,4), %eax
	sarl	$8, %eax
	movl	-28(%ebp), %ecx
	movb	%al, 13(%ecx)
	movl	-44(%ebp), %ecx
	movswl	2(%ecx,%edx,4),%eax
	movl	-28(%ebp), %edx
	movb	%al, 14(%edx)
	movl	-24(%ebp), %edx
	movsbl	3(%ecx,%edx,4),%eax
	movl	-28(%ebp), %ecx
	movb	%al, 15(%ecx)
	movb	$100, 16(%ecx)
	movb	$0, 17(%ecx)
	movb	$0, 18(%ecx)
	movb	$0, 19(%ecx)
	movb	$0, 20(%ecx)
	movb	$0, 21(%ecx)
	movb	$0, 22(%ecx)
	movb	$0, 23(%ecx)
	movb	$20, (%esi)
	incl	%esi
	leal	24(%ecx), %ebx
	movb	$0, (%esi)
	incl	%esi
	movb	$0, (%esi)
	incl	%esi
	movb	$0, (%esi)
	incl	%esi
	movb	$1, (%esi)
	incl	%esi
	movl	-48(%ebp), %edx
	movl	4(%edx), %eax
	addl	$3, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%edx), %eax
	addl	$3, %eax
	shrl	$8, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%edx), %eax
	addl	$3, %eax
	shrl	$16, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	$1, -20(%ebp)
	movl	-24(%ebp), %edi
L659:
	movl	-40(%ebp), %ecx
	movl	(%ecx,%edi,4), %eax
	movl	%eax, (%esp)
	movl	-48(%ebp), %edx
	movl	16(%edx), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L600
	movl	$0, %edi
	cmpl	-16(%ebp), %edi
	jge	L602
L606:
	movl	-40(%ebp), %ecx
	movl	(%ecx,%edi,4), %eax
	movl	%eax, (%esp)
	movl	-48(%ebp), %edx
	movl	16(%edx), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L602
	incl	%edi
	cmpl	-16(%ebp), %edi
	jl	L606
L602:
	movl	-44(%ebp), %ecx
	movzbl	(%ecx,%edi,4), %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	(%ecx,%edi,4), %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movswl	2(%ecx,%edi,4),%eax
	movb	%al, (%ebx)
	incl	%ebx
	movsbl	3(%ecx,%edi,4),%eax
	movb	%al, (%ebx)
	incl	%ebx
	movb	$-124, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movl	-48(%ebp), %edx
	movzbl	(%edx), %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	(%edx), %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movswl	2(%edx),%eax
	movb	%al, (%ebx)
	incl	%ebx
	movsbl	3(%edx),%eax
	movb	%al, (%ebx)
	incl	%ebx
	incl	-20(%ebp)
	movb	%bl, %al
	subb	-28(%ebp), %al
	subb	$4, %al
	movb	%al, (%esi)
	incl	%esi
	movl	%ebx, %eax
	subl	-28(%ebp), %eax
	subl	$4, %eax
	movl	%eax, %edx
	sarl	$8, %edx
	movb	%dl, (%esi)
	incl	%esi
	movl	%eax, %edx
	sarl	$16, %edx
	movb	%dl, (%esi)
	incl	%esi
	sarl	$24, %eax
	movb	%al, (%esi)
	incl	%esi
	movb	$1, (%esi)
	incl	%esi
	movl	-48(%ebp), %ecx
	movl	4(%ecx), %eax
	addl	$3, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%ecx), %eax
	addl	$3, %eax
	shrl	$8, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%ecx), %eax
	addl	$3, %eax
	shrl	$16, %eax
	movb	%al, (%esi)
	incl	%esi
L600:
	movb	$0, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movb	$68, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	incl	%ebx
	movl	-48(%ebp), %edx
	movzbl	12(%edx), %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	12(%edx), %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movzbl	(%edx), %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	(%edx), %eax
	sarl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movswl	2(%edx),%eax
	movb	%al, (%ebx)
	incl	%ebx
	movsbl	3(%edx),%eax
	movb	%al, (%ebx)
	incl	%ebx
	incl	-20(%ebp)
	movb	%bl, %al
	subb	-28(%ebp), %al
	subb	$4, %al
	movb	%al, (%esi)
	incl	%esi
	movl	%ebx, %eax
	subl	-28(%ebp), %eax
	subl	$4, %eax
	movl	%eax, %edx
	sarl	$8, %edx
	movb	%dl, (%esi)
	incl	%esi
	movl	%eax, %edx
	sarl	$16, %edx
	movb	%dl, (%esi)
	incl	%esi
	sarl	$24, %eax
	movb	%al, (%esi)
	incl	%esi
	movb	$1, (%esi)
	incl	%esi
	movl	-48(%ebp), %ecx
	movl	4(%ecx), %eax
	addl	$3, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%ecx), %eax
	addl	$3, %eax
	shrl	$8, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	4(%ecx), %eax
	addl	$3, %eax
	shrl	$16, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	20(%ecx), %eax
	movl	%eax, -48(%ebp)
	testl	%eax, %eax
	jne	L659
L671:
	movl	-20(%ebp), %ecx
	movl	-28(%ebp), %edx
	movw	%cx, 6(%edx)
	movl	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-44(%ebp), %edx
	movl	%edx, (%esp)
	call	_nasm_free
	movl	%ebx, %eax
	subl	-28(%ebp), %eax
	movl	%eax, _stablen
	movl	%esi, %eax
	subl	-36(%ebp), %eax
	movl	%eax, _stabrellen
	movl	-36(%ebp), %ecx
	movl	%ecx, _stabrelbuf
	movl	-28(%ebp), %eax
	movl	%eax, _stabbuf
	movl	-32(%ebp), %edx
	movl	%edx, _stabstrbuf
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _stabs_cleanup
	.def	_stabs_cleanup;	.scl	2;	.type	32;	.endef
_stabs_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	cmpl	$0, _stabslines
	je	L674
	movl	_stabslines, %ebx
	je	L684
L679:
	movl	%ebx, %eax
	movl	20(%ebx), %ebx
	movl	%eax, (%esp)
	call	_nasm_free
	testl	%ebx, %ebx
	jne	L679
L684:
	cmpl	$0, _stabbuf
	je	L680
	movl	_stabbuf, %eax
	movl	%eax, (%esp)
	call	_nasm_free
L680:
	cmpl	$0, _stabrelbuf
	je	L681
	movl	_stabrelbuf, %eax
	movl	%eax, (%esp)
	call	_nasm_free
L681:
	cmpl	$0, _stabstrbuf
	je	L674
	movl	_stabstrbuf, %eax
	movl	%eax, (%esp)
	call	_nasm_free
L674:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _sects,16
.lcomm _nsects,16
.lcomm _sectlen,16
.lcomm _shstrtab,16
.lcomm _shstrtablen,16
.lcomm _shstrtabsize,16
.lcomm _syms,16
.lcomm _nlocals,16
.lcomm _nglobs,16
.lcomm _def_seg,16
.lcomm _bsym,16
.lcomm _strs,16
.lcomm _strslen,16
.lcomm _elffp,16
.lcomm _error,16
.lcomm _evaluate,16
.lcomm _fwds,16
.lcomm _elf_module,256
.lcomm _elf_sects,16
.lcomm _elf_nsect,16
.lcomm _elf_foffs,16
.lcomm _symtabsection,16
.lcomm _stablen,16
.lcomm _stabstrlen,16
.lcomm _stabrellen,16
.lcomm _elf_gotpc_sect,16
.lcomm _elf_gotoff_sect,16
.lcomm _elf_got_sect,16
.lcomm _elf_plt_sect,16
.lcomm _elf_sym_sect,16
	.def	_stabs_cleanup;	.scl	2;	.type	32;	.endef
	.def	_stabs_output;	.scl	2;	.type	32;	.endef
	.def	_stabs_typevalue;	.scl	2;	.type	32;	.endef
	.def	_stabs_directive;	.scl	2;	.type	32;	.endef
	.def	_stabs_deflabel;	.scl	2;	.type	32;	.endef
	.def	_stabs_linenum;	.scl	2;	.type	32;	.endef
	.def	_stabs_init;	.scl	2;	.type	32;	.endef
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_stabs_generate;	.scl	2;	.type	32;	.endef
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_raa_read;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_raa_write;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strcat;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_raa_free;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_raa_init;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
