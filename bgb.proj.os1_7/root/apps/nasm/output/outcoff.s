	.file	"outcoff.c"
	.text
	.align 2
	.def	_coff_win32_init;	.scl	3;	.type	32;	.endef
_coff_win32_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$1, _win32
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_coff_gen_init
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_coff_std_init;	.scl	3;	.type	32;	.endef
_coff_std_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, _win32
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_coff_gen_init
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_coff_gen_init;	.scl	3;	.type	32;	.endef
_coff_gen_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, _coffp
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	$0, _sects
	movl	$0, _sectlen
	movl	$0, _nsects
	movl	$28, (%esp)
	call	_saa_init
	movl	%eax, _syms
	movl	$0, _nsyms
	call	_raa_init
	movl	%eax, _bsym
	call	_raa_init
	movl	%eax, _symval
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _strs
	movl	$0, _strslen
	call	_seg_alloc
	movl	%eax, _def_seg
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_coff_cleanup;	.scl	3;	.type	32;	.endef
_coff_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	call	_coff_write
	movl	_coffp, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L16
L14:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, (%eax)
	je	L9
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_saa_free
L9:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 16(%eax)
	je	L18
L13:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %edx
	movl	16(%edx), %ecx
	movl	(%ecx), %eax
	movl	%eax, 16(%edx)
	movl	%ecx, (%esp)
	call	_nasm_free
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, 16(%eax)
	jne	L13
L18:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L14
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
	movl	_symval, %eax
	movl	%eax, (%esp)
	call	_raa_free
	movl	_strs, %eax
	movl	%eax, (%esp)
	call	_saa_free
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
LC0:
	.ascii ".text\0"
	.align 2
	.def	_coff_make_section;	.scl	3;	.type	32;	.endef
_coff_make_section:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	$48, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	cmpl	$0, _win32
	je	L21
	cmpl	$-1070595968, %esi
	jmp	L27
L21:
	cmpl	$128, %esi
L27:
	je	L20
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, (%ebx)
	jmp	L23
L20:
	movl	$0, (%ebx)
L23:
	movl	$0, 16(%ebx)
	leal	16(%ebx), %eax
	movl	%eax, 20(%ebx)
	movl	$0, 4(%ebx)
	movl	$0, 8(%ebx)
	movl	%edi, (%esp)
	movl	$LC0, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L24
	movl	_def_seg, %eax
	jmp	L28
L24:
	call	_seg_alloc
L28:
	movl	%eax, 12(%ebx)
	leal	28(%ebx), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	movl	$8, 8(%esp)
	call	_strncpy
	movb	$0, 36(%ebx)
	movl	%esi, 24(%ebx)
	movl	_nsects, %eax
	cmpl	_sectlen, %eax
	jl	L26
	movl	_sects, %eax
	movl	%eax, (%esp)
	movl	_sectlen, %eax
	addl	$32, %eax
	movl	%eax, _sectlen
	sall	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _sects
L26:
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
	.align 32
LC1:
	.ascii "COFF section names limited to 8 characters: truncating\0"
LC2:
	.ascii "code\0"
LC3:
	.ascii "text\0"
LC4:
	.ascii "data\0"
LC5:
	.ascii "rdata\0"
	.align 32
LC6:
	.ascii "standard COFF does not support read-only data sections\0"
LC7:
	.ascii "bss\0"
LC8:
	.ascii "info\0"
	.align 32
LC9:
	.ascii "standard COFF does not support informational sections\0"
LC10:
	.ascii "align=\0"
	.align 32
LC11:
	.ascii "standard COFF does not support section alignment specification\0"
LC12:
	.ascii "0123456789\0"
	.align 32
LC13:
	.ascii "argument to `align' is not numeric\0"
	.align 32
LC14:
	.ascii "argument to `align' is not a power of two\0"
	.align 32
LC15:
	.ascii "Win32 cannot align sections to better than 64-byte boundaries\0"
LC16:
	.ascii ".data\0"
LC17:
	.ascii ".rdata\0"
LC18:
	.ascii ".bss\0"
	.align 32
LC19:
	.ascii "section attributes ignored on redeclaration of section `%s'\0"
	.align 2
	.def	_coff_section_names;	.scl	3;	.type	32;	.endef
_coff_section_names:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$-1, -16(%ebp)
	movl	$0, -20(%ebp)
	cmpl	$0, 8(%ebp)
	jne	L31
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	movl	_def_seg, %eax
	jmp	L29
L31:
	movl	8(%ebp), %ebx
	jmp	L32
L36:
	incl	%ebx
L32:
	cmpb	$0, (%ebx)
	je	L37
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L36
	cmpb	$0, (%ebx)
	je	L37
	movb	$0, (%ebx)
	incl	%ebx
L37:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	cmpl	$8, %eax
	jle	L38
	movl	$0, (%esp)
	movl	$LC1, 4(%esp)
	call	*_error
	movl	8(%ebp), %edx
	movb	$0, 8(%edx)
L38:
	movl	$0, %edi
	jmp	L39
L43:
	incl	%ebx
L39:
	cmpb	$0, (%ebx)
	je	L135
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L43
	cmpb	$0, (%ebx)
	je	L135
L107:
	movl	%ebx, %esi
	jmp	L47
L51:
	incl	%ebx
L47:
	cmpb	$0, (%ebx)
	je	L54
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L51
	cmpb	$0, (%ebx)
	je	L54
	movb	$0, (%ebx)
L57:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L54
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L57
L54:
	movl	%esi, (%esp)
	movl	$LC2, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L59
	movl	%esi, (%esp)
	movl	$LC3, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L58
L59:
	cmpl	$0, _win32
	je	L60
	movl	$1615855648, %edi
	jmp	L44
L60:
	movl	$32, %edi
	jmp	L44
L58:
	movl	%esi, (%esp)
	movl	$LC4, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L63
	cmpl	$0, _win32
	je	L64
	movl	$-1070596032, %edi
	jmp	L44
L64:
	movl	$64, %edi
	jmp	L44
L63:
	movl	%esi, (%esp)
	movl	$LC5, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L67
	cmpl	$0, _win32
	je	L72
	movl	$1077936192, %edi
	jmp	L44
L72:
	movl	$64, %edi
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	jmp	L138
L67:
	movl	%esi, (%esp)
	movl	$LC7, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L75
	cmpl	$0, _win32
	je	L76
	movl	$-1070595968, %edi
	jmp	L44
L76:
	movl	$128, %edi
	jmp	L44
L75:
	movl	%esi, (%esp)
	movl	$LC8, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L79
	cmpl	$0, _win32
	je	L82
	movl	$1051136, %edi
	jmp	L44
L82:
	movl	$64, %edi
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	jmp	L138
L79:
	movl	%esi, (%esp)
	movl	$LC10, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L44
	cmpl	$0, _win32
	jne	L86
	movl	$1, (%esp)
	movl	$LC11, 4(%esp)
	jmp	L138
L86:
	leal	6(%esi), %eax
	movl	%eax, (%esp)
	movl	$LC12, 4(%esp)
	call	_strspn
	cmpb	$0, 6(%eax,%esi)
	je	L88
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
	jmp	L138
L88:
	leal	6(%esi), %eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, %edx
	testl	%eax, %eax
	je	L91
	leal	-1(%eax), %eax
	testl	%edx, %eax
	je	L90
L91:
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	jmp	L138
L90:
	cmpl	$64, %edx
	jbe	L93
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
L138:
	call	*_error
	jmp	L44
L93:
	movl	$-15728641, -16(%ebp)
	movl	$1048576, -20(%ebp)
	cmpl	$1, %edx
	je	L44
	movl	$2097152, -20(%ebp)
	cmpl	$2, %edx
	je	L44
	movl	$3145728, -20(%ebp)
	cmpl	$4, %edx
	je	L44
	movl	$4194304, -20(%ebp)
	cmpl	$8, %edx
	je	L44
	cmpl	$16, %edx
	je	L103
	cmpl	$32, %edx
	setne	%al
	movzbl	%al, %eax
	decl	%eax
	andl	$-1048576, %eax
	addl	$7340032, %eax
	movl	%eax, -20(%ebp)
	jmp	L44
L103:
	movl	$5242880, -20(%ebp)
L44:
	cmpb	$0, (%ebx)
	jne	L107
L135:
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L109
L113:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	addl	$28, %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L109
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L113
L109:
	cmpl	_nsects, %ebx
	jne	L114
	testl	%edi, %edi
	jne	L115
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC16, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L116
	cmpl	$0, _win32
	je	L121
	movl	$-1070596032, %edi
	jmp	L115
L116:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC17, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L120
	cmpl	$0, _win32
	je	L121
	movl	$1077936192, %edi
	jmp	L115
L121:
	movl	$64, %edi
	jmp	L115
L120:
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC18, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L124
	cmpl	$0, _win32
	je	L125
	movl	$-1070595968, %edi
	jmp	L115
L125:
	movl	$128, %edi
	jmp	L115
L124:
	cmpl	$0, _win32
	je	L128
	movl	$1615855648, %edi
	jmp	L115
L128:
	movl	$32, %edi
L115:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_coff_make_section
	movl	%eax, %ebx
	testl	%edi, %edi
	je	L130
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	%edi, 24(%eax)
L130:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	-16(%ebp), %edx
	andl	%edx, 24(%eax)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	-20(%ebp), %edx
	orl	%edx, 24(%eax)
	jmp	L131
L114:
	cmpl	$1, 12(%ebp)
	jne	L131
	testl	%edi, %edi
	je	L131
	movl	$0, (%esp)
	movl	$LC19, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_error
L131:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	12(%eax), %eax
L29:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC20:
	.ascii "binary format does not support any special symbol types\0"
	.align 32
LC21:
	.ascii "unrecognised special symbol `%s'\0"
	.align 2
	.def	_coff_deflabel;	.scl	3;	.type	32;	.endef
_coff_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	_strslen, %esi
	addl	$4, %esi
	cmpl	$0, 24(%ebp)
	je	L140
	movl	$1, (%esp)
	movl	$LC20, 4(%esp)
	call	*_error
L140:
	cmpb	$46, (%edi)
	jne	L141
	cmpb	$46, 1(%edi)
	jne	L141
	cmpb	$64, 2(%edi)
	je	L141
	movl	$1, (%esp)
	movl	$LC21, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_error
	jmp	L139
L141:
	movl	%edi, (%esp)
	call	_strlen
	cmpl	$8, %eax
	jle	L142
	movl	%edi, (%esp)
	call	_strlen
	incl	%eax
	movl	_strs, %edx
	movl	%edx, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movl	%edi, (%esp)
	call	_strlen
	addl	_strslen, %eax
	incl	%eax
	movl	%eax, _strslen
	jmp	L143
L142:
	movl	$-1, %esi
L143:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_wstruct
	movl	%eax, %ebx
	movl	%esi, 12(%eax)
	cmpl	$-1, %esi
	jne	L144
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcpy
L144:
	cmpl	$0, 20(%ebp)
	setne	%al
	movzbl	%al, %eax
	movl	%eax, 20(%ebx)
	cmpl	$-1, 12(%ebp)
	jne	L145
	movl	$-1, 16(%ebx)
	jmp	L146
L163:
	leal	1(%edx), %eax
	movl	%eax, 16(%ebx)
	jmp	L148
L145:
	movl	$0, 16(%ebx)
	movl	$0, %edx
	cmpl	_nsects, %edx
	jge	L148
	movl	_sects, %ecx
L152:
	movl	(%ecx,%edx,4), %eax
	movl	12(%ebp), %esi
	cmpl	12(%eax), %esi
	je	L163
	incl	%edx
	cmpl	_nsects, %edx
	jl	L152
L148:
	cmpl	$0, 16(%ebx)
	jne	L146
	movl	$1, 20(%ebx)
L146:
	cmpl	$2, 20(%ebp)
	je	L164
	cmpl	$0, 16(%ebx)
	je	L156
L164:
	movl	16(%ebp), %eax
	jmp	L157
L156:
	movl	$0, %eax
L157:
	movl	%eax, 24(%ebx)
	cmpl	$0, 16(%ebx)
	jne	L158
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %esi
	movl	%esi, 4(%esp)
	movl	_nsyms, %eax
	movl	%eax, 8(%esp)
	call	_raa_write
	movl	%eax, _bsym
L158:
	cmpl	$-1, 12(%ebp)
	je	L159
	movl	_symval, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	cmpl	$0, 16(%ebx)
	jne	L160
	movl	24(%ebx), %eax
	jmp	L161
L160:
	movl	$0, %eax
L161:
	movl	%eax, 8(%esp)
	call	_raa_write
	movl	%eax, _symval
L159:
	incl	_nsyms
L139:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_coff_add_reloc;	.scl	3;	.type	32;	.endef
_coff_add_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	20(%esi), %ebx
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, %ebx
	movl	%eax, 20(%esi)
	movl	$0, (%eax)
	movl	4(%esi), %eax
	movl	%eax, 4(%ebx)
	cmpl	$-1, %edi
	jne	L166
	movl	$0, 8(%ebx)
	movl	$1, 12(%ebx)
	jmp	L167
L178:
	leal	(%edx,%edx), %eax
	movl	%eax, 8(%ebx)
	movl	$0, 12(%ebx)
	jmp	L169
L166:
	movl	$2, 12(%ebx)
	movl	$0, %edx
	cmpl	_nsects, %edx
	jge	L169
	movl	_sects, %ecx
L173:
	movl	(%ecx,%edx,4), %eax
	cmpl	12(%eax), %edi
	je	L178
	incl	%edx
	cmpl	_nsects, %edx
	jl	L173
L169:
	cmpl	$2, 12(%ebx)
	jne	L167
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_raa_read
	movl	%eax, 8(%ebx)
L167:
	movl	16(%ebp), %eax
	movl	%eax, 16(%ebx)
	incl	8(%esi)
	cmpl	$2, 12(%ebx)
	jne	L175
	cmpl	$0, _win32
	jne	L175
	movl	_symval, %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_raa_read
	jmp	L165
L175:
	movl	$0, %eax
L165:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC22:
	.ascii "WRT not supported by COFF output formats\0"
	.align 32
LC23:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC24:
	.ascii "strange segment conditions in COFF driver\0"
	.align 32
LC25:
	.ascii "attempt to initialise memory in BSS section `%s': ignored\0"
	.align 32
LC26:
	.ascii "uninitialised space declared in non-BSS section `%s': zeroing\0"
	.align 32
LC27:
	.ascii "OUT_RAWDATA with other than NO_SEG\0"
	.align 32
LC28:
	.ascii "COFF format does not support non-32-bit relocations\0"
	.align 32
LC29:
	.ascii "COFF format does not support WRT types\0"
	.align 32
LC30:
	.ascii "COFF format does not support segment base references\0"
	.align 32
LC31:
	.ascii "COFF format does not support 16-bit relocations\0"
LC32:
	.ascii "intra-segment OUT_REL4ADR\0"
	.align 32
LC33:
	.ascii "Win32 COFF does not correctly support relative references to absolute addresses\0"
	.align 2
	.def	_coff_out;	.scl	3;	.type	32;	.endef
_coff_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %edi
	movl	16(%ebp), %ebx
	movl	%ebx, %eax
	andl	$268435455, %eax
	movl	%eax, -24(%ebp)
	cmpl	$-1, 24(%ebp)
	je	L180
	movl	$-1, 24(%ebp)
	movl	$1, (%esp)
	movl	$LC22, 4(%esp)
	call	*_error
L180:
	andl	$-268435456, %ebx
	cmpl	$-1, %edi
	jne	L181
	cmpl	$1073741824, %ebx
	je	L179
	movl	$1, (%esp)
	movl	$LC23, 4(%esp)
	jmp	L246
L243:
	movl	%eax, %esi
	jmp	L184
L181:
	movl	$0, %esi
	movl	$0, %edx
	cmpl	_nsects, %esi
	jge	L184
	movl	_sects, %ecx
L188:
	movl	(%ecx,%edx,4), %eax
	cmpl	12(%eax), %edi
	je	L243
	incl	%edx
	cmpl	_nsects, %edx
	jl	L188
L184:
	testl	%esi, %esi
	jne	L189
	movl	$LC0, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_coff_section_names
	cmpl	%eax, %edi
	je	L190
	movl	$3, (%esp)
	movl	$LC24, 4(%esp)
	call	*_error
	jmp	L189
L190:
	movl	_sects, %edx
	movl	_nsects, %eax
	movl	-4(%edx,%eax,4), %esi
L189:
	cmpl	$0, (%esi)
	jne	L192
	cmpl	$1073741824, %ebx
	je	L241
	movl	$0, (%esp)
	movl	$LC25, 4(%esp)
	leal	28(%esi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	cmpl	$536870912, %ebx
	jne	L193
	movl	$2, -24(%ebp)
	jmp	L197
L193:
	cmpl	$805306368, %ebx
	jne	L197
	movl	$4, -24(%ebp)
	jmp	L197
L192:
	cmpl	$1073741824, %ebx
	jne	L196
L241:
	cmpl	$0, (%esi)
	je	L197
	movl	$0, (%esp)
	movl	$LC26, 4(%esp)
	leal	28(%esi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	jmp	L249
L197:
	movl	-24(%ebp), %edx
	addl	%edx, 4(%esi)
	jmp	L179
L196:
	testl	%ebx, %ebx
	jne	L200
	cmpl	$-1, 20(%ebp)
	je	L201
	movl	$3, (%esp)
	movl	$LC27, 4(%esp)
	call	*_error
L201:
	movl	%esi, (%esp)
	movl	12(%ebp), %edi
	movl	%edi, 4(%esp)
	jmp	L249
L200:
	cmpl	$268435456, %ebx
	jne	L203
	cmpl	$4, -24(%ebp)
	je	L204
	cmpl	$-1, 20(%ebp)
	jne	L205
	cmpl	$-1, 24(%ebp)
	je	L204
L205:
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
	jmp	L246
L204:
	movl	$0, %ebx
	cmpl	$-1, 20(%ebp)
	jne	L208
	cmpl	$-1, 24(%ebp)
	je	L207
	jmp	L242
L208:
	cmpl	$-1, 24(%ebp)
	je	L209
L242:
	movl	$1, (%esp)
	movl	$LC29, 4(%esp)
	jmp	L244
L209:
	testl	$1, 20(%ebp)
	je	L211
	movl	$1, (%esp)
	movl	$LC30, 4(%esp)
L244:
	call	*_error
	jmp	L207
L211:
	movl	%esi, (%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	call	_coff_add_reloc
	movl	%eax, %ebx
L207:
	leal	-20(%ebp), %ecx
	movl	12(%ebp), %edi
	movzbl	(%edi), %eax
	addb	%bl, %al
	movl	%ecx, %edx
	movb	%al, -20(%ebp)
	incl	%ecx
	movl	%ebx, %eax
	addl	(%edi), %eax
	sarl	$8, %eax
	movb	%al, (%ecx)
	incl	%ecx
	movl	%ebx, %eax
	addl	(%edi), %eax
	sarl	$16, %eax
	movb	%al, (%ecx)
	movl	%ebx, %eax
	addl	(%edi), %eax
	sarl	$24, %eax
	movb	%al, 1(%ecx)
	movl	%esi, (%esp)
	movl	%edx, 4(%esp)
L249:
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	jmp	L247
L203:
	cmpl	$536870912, %ebx
	jne	L219
	movl	$1, (%esp)
	movl	$LC31, 4(%esp)
	jmp	L246
L219:
	cmpl	$805306368, %ebx
	jne	L179
	cmpl	%edi, 20(%ebp)
	jne	L222
	movl	$3, (%esp)
	movl	$LC32, 4(%esp)
	jmp	L246
L222:
	cmpl	$-1, 20(%ebp)
	jne	L224
	cmpl	$0, _win32
	je	L224
	movl	$1, (%esp)
	movl	$LC33, 4(%esp)
L246:
	call	*_error
	jmp	L179
L224:
	movl	$0, %ebx
	cmpl	$-1, 20(%ebp)
	je	L226
	testl	$1, 20(%ebp)
	je	L226
	movl	$1, (%esp)
	movl	$LC30, 4(%esp)
	call	*_error
	jmp	L227
L226:
	movl	%esi, (%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$1, 8(%esp)
	call	_coff_add_reloc
	movl	%eax, %ebx
L227:
	leal	-20(%ebp), %ecx
	cmpl	$0, _win32
	je	L228
	movl	12(%ebp), %edi
	movzbl	(%edi), %eax
	subb	-24(%ebp), %al
	addb	%bl, %al
	addb	$4, %al
	movb	%al, -20(%ebp)
	incl	%ecx
	movl	(%edi), %eax
	subl	-24(%ebp), %eax
	leal	4(%ebx,%eax), %eax
	sarl	$8, %eax
	movb	%al, (%ecx)
	incl	%ecx
	movl	(%edi), %eax
	subl	-24(%ebp), %eax
	leal	4(%ebx,%eax), %eax
	sarl	$16, %eax
	movb	%al, (%ecx)
	movl	(%edi), %eax
	subl	-24(%ebp), %eax
	leal	4(%ebx,%eax), %eax
	sarl	$24, %eax
	jmp	L245
L228:
	movzbl	-24(%ebp), %edx
	addb	4(%esi), %dl
	movl	12(%ebp), %edi
	movzbl	(%edi), %eax
	subb	%dl, %al
	addb	%bl, %al
	movb	%al, (%ecx)
	incl	%ecx
	movl	-24(%ebp), %edx
	addl	4(%esi), %edx
	movl	(%edi), %eax
	subl	%edx, %eax
	addl	%ebx, %eax
	shrl	$8, %eax
	movb	%al, (%ecx)
	incl	%ecx
	movl	-24(%ebp), %edx
	addl	4(%esi), %edx
	movl	(%edi), %eax
	subl	%edx, %eax
	addl	%ebx, %eax
	shrl	$16, %eax
	movb	%al, (%ecx)
	movl	-24(%ebp), %edx
	addl	4(%esi), %edx
	movl	(%edi), %eax
	subl	%edx, %eax
	addl	%ebx, %eax
	shrl	$24, %eax
L245:
	movb	%al, 1(%ecx)
	movl	%esi, (%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$4, 8(%esp)
L247:
	call	_coff_sect_write
L179:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_coff_sect_write;	.scl	3;	.type	32;	.endef
_coff_sect_write:
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
	.data
	.align 4
_Exports:
	.long	0
	.text
LC34:
	.ascii ".drectve\0"
	.align 2
.globl _AddExport
	.def	_AddExport;	.scl	2;	.type	32;	.endef
_AddExport:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	_Exports, %ebx
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%edi, (%esp)
	call	_strlen
	movl	%eax, 4(%esi)
	movl	$0, (%esi)
	incl	%eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 8(%esi)
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcpy
	testl	%ebx, %ebx
	jne	L252
	movl	$0, %edi
	cmpl	_nsects, %ebx
	jge	L254
L258:
	movl	$LC34, (%esp)
	movl	_sects, %eax
	movl	(%eax,%edi,4), %eax
	addl	$28, %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L254
	incl	%edi
	cmpl	_nsects, %edi
	jl	L258
L254:
	cmpl	_nsects, %edi
	jne	L259
	movl	$LC34, (%esp)
	movl	$1051136, 4(%esp)
	call	_coff_make_section
	movl	_sects, %edx
	movl	(%edx,%eax,4), %eax
	jmp	L270
L259:
	movl	_sects, %eax
	movl	(%eax,%edi,4), %eax
L270:
	movl	%eax, _directive_sec
	movl	%esi, _Exports
	jmp	L251
L252:
	cmpl	$0, (%ebx)
	je	L269
L266:
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L251
	movl	(%ebx), %ebx
	cmpl	$0, (%ebx)
	jne	L266
L269:
	movl	%esi, (%ebx)
L251:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC35:
	.ascii "-export:%s \0"
	.align 2
.globl _BuildExportTable
	.def	_BuildExportTable;	.scl	2;	.type	32;	.endef
_BuildExportTable:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$272, %esp
	movl	_Exports, %ebx
	testl	%ebx, %ebx
	je	L271
	leal	-264(%ebp), %esi
L276:
	movl	%esi, (%esp)
	movl	$LC35, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	movl	_directive_sec, %edx
	movl	%edx, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	call	_coff_sect_write
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L276
	movl	_Exports, %esi
	movl	%esi, %ebx
	testl	%esi, %esi
	je	L284
L280:
	movl	(%ebx), %esi
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	%esi, %ebx
	testl	%esi, %esi
	jne	L280
L284:
	movl	$0, _Exports
L271:
	addl	$272, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
LC36:
	.ascii "export\0"
	.align 32
LC37:
	.ascii "`export' directive requires export name\0"
	.align 32
LC38:
	.ascii "unrecognised export qualifier `%s'\0"
	.align 2
	.def	_coff_directives;	.scl	3;	.type	32;	.endef
_coff_directives:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC36, 4(%esp)
	call	_strcmp
	movl	$0, %edx
	testl	%eax, %eax
	jne	L285
	movl	$1, %edx
	cmpl	$2, 16(%ebp)
	je	L285
	movl	12(%ebp), %esi
	movl	%esi, %ebx
	jmp	L288
L292:
	incl	%ebx
L288:
	cmpb	$0, (%ebx)
	je	L289
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L292
L289:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L293
	movb	$0, (%ebx)
L298:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L293
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L298
L293:
	cmpb	$0, (%esi)
	jne	L299
	movl	$1, (%esp)
	movl	$LC37, 4(%esp)
	call	*_error
	jmp	L301
L299:
	cmpb	$0, (%ebx)
	je	L300
	movl	$1, (%esp)
	movl	$LC38, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_error
	jmp	L301
L300:
	movl	%esi, (%esp)
	call	_AddExport
L301:
	movl	$1, %edx
L285:
	movl	%edx, %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_coff_write;	.scl	3;	.type	32;	.endef
_coff_write:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	call	_BuildExportTable
	movl	_nsects, %eax
	leal	(%eax,%eax,4), %eax
	leal	20(,%eax,8), %esi
	movl	$3, _initsym
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L324
L309:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, (%eax)
	je	L307
	movl	%esi, 40(%eax)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	addl	4(%eax), %esi
	movl	%esi, 44(%eax)
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	8(%eax), %eax
	leal	(%eax,%eax,4), %eax
	leal	(%esi,%eax,2), %esi
	jmp	L308
L307:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	$0, 44(%eax)
	movl	$0, 40(%eax)
L308:
	addl	$2, _initsym
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L309
L324:
	movl	$332, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_nsects, %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	call	_time
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	%esi, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_nsyms, %eax
	addl	_initsym, %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	cmpl	$0, _win32
	jne	L310
	movl	$260, %eax
	jmp	L311
L310:
	movl	$0, %eax
L311:
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, %esi
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L328
L316:
	movl	_sects, %edx
	movl	(%edx,%ebx,4), %eax
	addl	$28, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	40(%eax), %eax
	movl	%eax, 12(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	44(%eax), %eax
	movl	%eax, 16(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	8(%eax), %eax
	movl	%eax, 20(%esp)
	movl	(%edx,%ebx,4), %eax
	movl	24(%eax), %eax
	movl	%eax, 24(%esp)
	call	_coff_section_header
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	addl	4(%eax), %esi
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L316
	movl	$0, %ebx
	cmpl	_nsects, %ebx
	jge	L328
L322:
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	cmpl	$0, (%eax)
	je	L319
	movl	(%eax), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	_sects, %eax
	movl	(%eax,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_coff_write_relocs
L319:
	incl	%ebx
	cmpl	_nsects, %ebx
	jl	L322
L328:
	call	_coff_write_symbols
	movl	_strslen, %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_strs, %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_coff_section_header;	.scl	3;	.type	32;	.endef
_coff_section_header:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$8, 8(%esp)
	call	_memset
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$8, 8(%esp)
	call	_strncpy
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$8, 4(%esp)
	movl	$1, 8(%esp)
	movl	_coffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	20(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	28(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	32(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	leave
	ret
	.align 2
	.def	_coff_write_relocs;	.scl	3;	.type	32;	.endef
_coff_write_relocs:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %eax
	movl	16(%eax), %ebx
	testl	%ebx, %ebx
	je	L344
L342:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	8(%ebx), %eax
	cmpl	$2, 12(%ebx)
	je	L335
	cmpl	$1, 12(%ebx)
	jne	L337
	addl	_initsym, %eax
	decl	%eax
	jmp	L336
L337:
	cmpl	$0, 12(%ebx)
	jne	L336
	addl	$2, %eax
	jmp	L336
L335:
	addl	_initsym, %eax
L336:
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	cmpl	$0, 16(%ebx)
	je	L340
	movl	$20, %eax
	jmp	L341
L340:
	movl	$6, %eax
L341:
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L342
L344:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_coff_symbol;	.scl	3;	.type	32;	.endef
_coff_symbol:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	je	L346
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$8, 8(%esp)
	call	_memset
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$8, 8(%esp)
	call	_strncpy
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	$8, 4(%esp)
	movl	$1, 8(%esp)
	movl	_coffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	jmp	L347
L346:
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
L347:
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	20(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	movl	28(%ebp), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
LC39:
	.ascii ".file\0"
LC40:
	.ascii ".absolut\0"
	.align 2
	.def	_coff_write_symbols;	.scl	3;	.type	32;	.endef
_coff_write_symbols:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$64, %esp
	movl	$LC39, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	$-2, 12(%esp)
	movl	$103, 16(%esp)
	movl	$1, 20(%esp)
	call	_coff_symbol
	leal	-40(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	movl	$18, 8(%esp)
	call	_memset
	movl	%ebx, (%esp)
	movl	$_coff_infile, 4(%esp)
	movl	$18, 8(%esp)
	call	_strncpy
	movl	%ebx, (%esp)
	movl	$18, 4(%esp)
	movl	$1, 8(%esp)
	movl	_coffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	movl	$18, 8(%esp)
	call	_memset
	movl	$0, %esi
	cmpl	_nsects, %esi
	jae	L364
L353:
	movl	_sects, %eax
	movl	(%eax,%esi,4), %eax
	addl	$28, %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	leal	1(%esi), %ebx
	movl	%ebx, 12(%esp)
	movl	$3, 16(%esp)
	movl	$1, 20(%esp)
	call	_coff_symbol
	movl	_sects, %eax
	movl	(%eax,%esi,4), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_sects, %eax
	movl	(%eax,%esi,4), %eax
	movl	8(%eax), %eax
	movl	%eax, (%esp)
	movl	_coffp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$12, 4(%esp)
	movl	$1, 8(%esp)
	movl	_coffp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	movl	%ebx, %esi
	cmpl	_nsects, %ebx
	jb	L353
L364:
	movl	$LC40, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	$-1, 12(%esp)
	movl	$3, 16(%esp)
	movl	$0, 20(%esp)
	call	_coff_symbol
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	$0, %esi
	cmpl	_nsyms, %esi
	jae	L366
L362:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %edx
	cmpl	$-1, 12(%eax)
	je	L359
	movl	$0, %eax
L359:
	movl	%eax, (%esp)
	movl	12(%edx), %eax
	movl	%eax, 4(%esp)
	movl	24(%edx), %eax
	movl	%eax, 8(%esp)
	movl	16(%edx), %eax
	movl	%eax, 12(%esp)
	cmpl	$0, 20(%edx)
	je	L360
	movl	$2, %eax
	jmp	L361
L360:
	movl	$3, %eax
L361:
	movl	%eax, 16(%esp)
	movl	$0, 20(%esp)
	call	_coff_symbol
	incl	%esi
	cmpl	_nsyms, %esi
	jb	L362
L366:
	addl	$64, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_coff_segbase;	.scl	3;	.type	32;	.endef
_coff_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
LC41:
	.ascii ".o\0"
	.align 2
	.def	_coff_std_filename;	.scl	3;	.type	32;	.endef
_coff_std_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	$_coff_infile, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC41, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
LC42:
	.ascii ".obj\0"
	.align 2
	.def	_coff_win32_filename;	.scl	3;	.type	32;	.endef
_coff_win32_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	$_coff_infile, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC42, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC43:
	.ascii "%define __SECT__ [section .text]\0"
LC44:
	.ascii "%macro __NASM_CDecl__ 1\0"
LC45:
	.ascii "%endmacro\0"
LC46:
	.ascii "%imacro export 1+.nolist\0"
LC47:
	.ascii "[export %1]\0"
	.data
	.align 4
_coff_stdmac:
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC45
	.long	0
	.text
	.align 2
	.def	_coff_set_info;	.scl	3;	.type	32;	.endef
_coff_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
.globl _of_coff
	.align 32
LC48:
	.ascii "COFF (i386) object files (e.g. DJGPP for DOS)\0"
LC49:
	.ascii "coff\0"
	.data
	.align 32
_of_coff:
	.long	LC48
	.long	LC49
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_coff_stdmac
	.long	_coff_std_init
	.long	_coff_set_info
	.long	_coff_out
	.long	_coff_deflabel
	.long	_coff_section_names
	.long	_coff_segbase
	.long	_coff_directives
	.long	_coff_std_filename
	.long	_coff_cleanup
.globl _of_win32
	.text
	.align 32
LC50:
	.ascii "Microsoft Win32 (i386) object files\0"
LC51:
	.ascii "win32\0"
	.data
	.align 32
_of_win32:
	.long	LC50
	.long	LC51
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_coff_stdmac
	.long	_coff_win32_init
	.long	_coff_set_info
	.long	_coff_out
	.long	_coff_deflabel
	.long	_coff_section_names
	.long	_coff_segbase
	.long	_coff_directives
	.long	_coff_win32_filename
	.long	_coff_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _win32,16
.lcomm _coffp,16
.lcomm _error,16
.lcomm _coff_infile,256
.lcomm _sects,16
.lcomm _nsects,16
.lcomm _sectlen,16
.lcomm _syms,16
.lcomm _nsyms,16
.lcomm _def_seg,16
.lcomm _initsym,16
.lcomm _bsym,16
.lcomm _symval,16
.lcomm _strs,16
.lcomm _strslen,16
.lcomm _directive_sec,16
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_time;	.scl	2;	.type	32;	.endef
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_raa_read;	.scl	2;	.type	32;	.endef
	.def	_raa_write;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
	.def	_strspn;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_raa_free;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_raa_init;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
