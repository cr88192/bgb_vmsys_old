	.file	"outaout.c"
	.text
	.align 2
	.def	_aoutg_init;	.scl	3;	.type	32;	.endef
_aoutg_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, _aoutfp
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	20(%ebp), %eax
	movl	%eax, _evaluate
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _stext
	movl	$0, _stext+20
	movl	$_stext+20, _stext+24
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _sdata
	movl	$0, _sdata+20
	movl	$_sdata+20, _sdata+24
	movl	$0, _sbss+4
	movl	$0, _sdata+8
	movl	$0, _sdata+4
	movl	$0, _stext+8
	movl	$0, _stext+4
	movl	$0, _sdata+12
	movl	$0, _stext+12
	movl	$0, _sbss+28
	movl	$0, _sdata+28
	movl	$0, _stext+28
	call	_seg_alloc
	movl	%eax, _stext+16
	call	_seg_alloc
	movl	%eax, _sdata+16
	call	_seg_alloc
	movl	%eax, _sbss+16
	movl	$0, _sbss+32
	movl	$0, _sdata+32
	movl	$0, _stext+32
	movl	$36, (%esp)
	call	_saa_init
	movl	%eax, _syms
	movl	$0, _nsyms
	call	_raa_init
	movl	%eax, _bsym
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _strs
	movl	$0, _strslen
	movl	$0, _fwds
	leave
	ret
	.align 2
	.def	_aout_init;	.scl	3;	.type	32;	.endef
_aout_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$0, _bsd
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_aoutg_init
	movl	$-1, _aout_sym_sect
	movl	$-1, _aout_plt_sect
	movl	$-1, _aout_got_sect
	movl	$-1, _aout_gotoff_sect
	movl	$-1, _aout_gotpc_sect
	movl	%ebp, %esp
	popl	%ebp
	ret
LC0:
	.ascii "..gotpc\0"
LC1:
	.ascii "..gotoff\0"
LC2:
	.ascii "..got\0"
LC3:
	.ascii "..plt\0"
LC4:
	.ascii "..sym\0"
	.align 2
	.def	_aoutb_init;	.scl	3;	.type	32;	.endef
_aoutb_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	16(%ebp), %ebx
	movl	$1, _bsd
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_aoutg_init
	movl	$0, _is_pic
	call	_seg_alloc
	movl	%eax, _aout_gotpc_sect
	movl	$LC0, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_aoutb, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _aout_gotoff_sect
	movl	$LC1, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_aoutb, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _aout_got_sect
	movl	$LC2, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_aoutb, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _aout_plt_sect
	movl	$LC3, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_aoutb, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	call	_seg_alloc
	movl	%eax, _aout_sym_sect
	movl	$LC4, (%esp)
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_aoutb, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*%ebx
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_aout_cleanup;	.scl	3;	.type	32;	.endef
_aout_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	_aout_pad_sections
	movl	$_stext, (%esp)
	call	_aout_fixup_relocs
	movl	$_sdata, (%esp)
	call	_aout_fixup_relocs
	call	_aout_write
	movl	_aoutfp, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	_stext, %eax
	movl	%eax, (%esp)
	call	_saa_free
	cmpl	$0, _stext+20
	je	L14
L8:
	movl	_stext+20, %edx
	movl	(%edx), %eax
	movl	%eax, _stext+20
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _stext+20
	jne	L8
L14:
	movl	_sdata, %eax
	movl	%eax, (%esp)
	call	_saa_free
	cmpl	$0, _sdata+20
	je	L16
L12:
	movl	_sdata+20, %edx
	movl	(%edx), %eax
	movl	%eax, _sdata+20
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _sdata+20
	jne	L12
L16:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_free
	movl	_bsym, %eax
	movl	%eax, (%esp)
	call	_raa_free
	movl	_strs, %eax
	movl	%eax, (%esp)
	call	_saa_free
	leave
	ret
LC5:
	.ascii ".text\0"
LC6:
	.ascii ".data\0"
LC7:
	.ascii ".bss\0"
	.align 2
	.def	_aout_section_names;	.scl	3;	.type	32;	.endef
_aout_section_names:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	jne	L19
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	jmp	L26
L19:
	movl	%ebx, (%esp)
	movl	$LC5, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L20
L26:
	movl	_stext+16, %edx
	jmp	L17
L20:
	movl	%ebx, (%esp)
	movl	$LC6, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L22
	movl	_sdata+16, %edx
	jmp	L17
L22:
	movl	%ebx, (%esp)
	movl	$LC7, 4(%esp)
	call	_strcmp
	movl	$-1, %edx
	testl	%eax, %eax
	jne	L17
	movl	_sbss+16, %edx
L17:
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC8:
	.ascii "unrecognised special symbol `%s'\0"
	.align 32
LC9:
	.ascii "cannot use relocatable expression as symbol size\0"
LC10:
	.ascii " \0"
LC11:
	.ascii "function\0"
LC12:
	.ascii "data\0"
LC13:
	.ascii "object\0"
	.align 32
LC14:
	.ascii "unrecognised symbol type `%.*s'\0"
	.align 32
LC15:
	.ascii "Linux a.out does not support symbol size information\0"
	.align 32
LC16:
	.ascii "no special symbol features supported here\0"
	.align 2
	.def	_aout_deflabel;	.scl	3;	.type	32;	.endef
_aout_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	20(%ebp), %esi
	movl	_strslen, %edi
	addl	$4, %edi
	movl	$0, -64(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L28
	cmpb	$46, 1(%eax)
	jne	L28
	cmpb	$64, 2(%eax)
	je	L28
	movl	%eax, (%esp)
	movl	$LC0, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L27
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC1, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L27
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC2, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L27
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC3, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L27
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC4, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L27
	movl	$1, (%esp)
	movl	$LC8, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, 8(%esp)
	call	*_error
	jmp	L27
L28:
	cmpl	$3, %esi
	jne	L30
	movl	$_fwds, %esi
	cmpl	$0, _fwds
	je	L27
L49:
	movl	(%esi), %eax
	movl	28(%eax), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	movl	24(%ebp), %ebx
	testl	%eax, %eax
	je	L36
	jmp	L33
L40:
	incl	%ebx
L36:
	cmpb	$0, (%ebx)
	je	L42
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L40
	jmp	L41
L45:
	incl	%ebx
L41:
	cmpb	$0, (%ebx)
	je	L42
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L45
L42:
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
	je	L46
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L47
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	call	*_error
	jmp	L46
L47:
	movl	(%esi), %ebx
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, 12(%ebx)
L46:
	movl	(%esi), %eax
	movl	28(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%esi), %eax
	movl	24(%eax), %eax
	movl	%eax, (%esi)
	jmp	L27
L33:
	movl	(%esi), %eax
	leal	24(%eax), %esi
	cmpl	$0, 24(%eax)
	je	L27
	jmp	L49
L30:
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
	movl	%edi, (%eax)
	testl	%esi, %esi
	setne	%al
	movzbl	%al, %eax
	movl	%eax, 4(%ebx)
	movl	12(%ebp), %edx
	movl	%edx, 16(%ebx)
	cmpl	$-1, %edx
	jne	L50
	orl	$2, %eax
	movl	%eax, 4(%ebx)
	jmp	L51
L50:
	movl	12(%ebp), %eax
	cmpl	_stext+16, %eax
	jne	L52
	orl	$4, 4(%ebx)
	testl	%esi, %esi
	je	L53
	movl	_stext+28, %eax
	movl	%eax, 20(%ebx)
	movl	%ebx, _stext+28
	jmp	L51
L53:
	cmpl	$0, _stext+32
	jne	L51
	movl	%ebx, _stext+32
	jmp	L51
L52:
	movl	12(%ebp), %edx
	cmpl	_sdata+16, %edx
	jne	L57
	orl	$6, 4(%ebx)
	testl	%esi, %esi
	je	L58
	movl	_sdata+28, %eax
	movl	%eax, 20(%ebx)
	movl	%ebx, _sdata+28
	jmp	L51
L58:
	cmpl	$0, _sdata+32
	jne	L51
	movl	%ebx, _sdata+32
	jmp	L51
L57:
	movl	12(%ebp), %eax
	cmpl	_sbss+16, %eax
	jne	L62
	orl	$8, 4(%ebx)
	testl	%esi, %esi
	je	L63
	movl	_sbss+28, %eax
	movl	%eax, 20(%ebx)
	movl	%ebx, _sbss+28
	jmp	L51
L63:
	cmpl	$0, _sbss+32
	jne	L51
	movl	%ebx, _sbss+32
	jmp	L51
L62:
	movl	$1, 4(%ebx)
L51:
	cmpl	$2, %esi
	jne	L67
	movl	16(%ebp), %edx
	movl	%edx, 8(%ebx)
	jmp	L68
L67:
	cmpl	$1, 4(%ebx)
	je	L69
	movl	16(%ebp), %eax
	jmp	L70
L69:
	movl	$0, %eax
L70:
	movl	%eax, 8(%ebx)
L68:
	testl	%esi, %esi
	je	L71
	cmpl	$1, 4(%ebx)
	je	L71
	cmpl	$0, 24(%ebp)
	je	L71
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC10, 4(%esp)
	call	_strcspn
	movl	%eax, %esi
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC11, 4(%esp)
	movl	%eax, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L73
	orl	$512, 4(%ebx)
	jmp	L74
L73:
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC12, 4(%esp)
	movl	%esi, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	je	L76
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC13, 4(%esp)
	movl	%esi, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L75
L76:
	orl	$256, 4(%ebx)
	jmp	L74
L75:
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	movl	%esi, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	call	*_error
L74:
	movl	24(%ebp), %edx
	cmpb	$0, (%esi,%edx)
	je	L78
	movl	$0, -60(%ebp)
	movl	_stdscan_bufptr, %edi
	cmpl	$0, _bsd
	jne	L81
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
	jmp	L95
L85:
	incl	%esi
L81:
	movl	24(%ebp), %eax
	cmpb	$0, (%esi,%eax)
	je	L82
	movsbl	(%esi,%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L85
L82:
	orl	$16384, 4(%ebx)
	call	_stdscan_reset
	movl	24(%ebp), %eax
	addl	%esi, %eax
	movl	%eax, _stdscan_bufptr
	movl	$-1, -56(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-56(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-60(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$0, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	cmpl	$0, -60(%ebp)
	je	L86
	movl	_fwds, %eax
	movl	%eax, 24(%ebx)
	movl	%ebx, _fwds
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	call	_nasm_strdup
	movl	%eax, 28(%ebx)
	jmp	L80
L86:
	testl	%eax, %eax
	je	L80
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L89
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
L95:
	call	*_error
	jmp	L80
L89:
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, 12(%ebx)
L80:
	movl	%edi, _stdscan_bufptr
L78:
	movl	$1, -64(%ebp)
L71:
	cmpl	$-1, 12(%ebp)
	je	L91
	movl	12(%ebp), %eax
	cmpl	_stext+16, %eax
	je	L91
	cmpl	_sdata+16, %eax
	je	L91
	cmpl	_sbss+16, %eax
	je	L91
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	_nsyms, %eax
	movl	%eax, 8(%esp)
	call	_raa_write
	movl	%eax, _bsym
L91:
	movl	_nsyms, %eax
	movl	%eax, 32(%ebx)
	movl	_nsyms, %edx
	leal	1(%edx), %eax
	movl	%eax, _nsyms
	testb	$64, 5(%ebx)
	je	L92
	leal	2(%edx), %eax
	movl	%eax, _nsyms
L92:
	cmpl	$0, 24(%ebp)
	je	L27
	cmpl	$0, -64(%ebp)
	jne	L27
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	call	*_error
L27:
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_aout_add_reloc;	.scl	3;	.type	32;	.endef
_aout_add_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	24(%edi), %ebx
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, %ebx
	movl	%eax, 24(%edi)
	movl	$0, (%eax)
	movl	4(%edi), %eax
	movl	%eax, 4(%ebx)
	movl	$-2, %eax
	cmpl	$-1, %esi
	je	L98
	cmpl	_stext+16, %esi
	je	L99
	cmpl	_sdata+16, %esi
	je	L101
	cmpl	_sbss+16, %esi
	je	L103
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_raa_read
	jmp	L98
L103:
	movl	$-8, %eax
	jmp	L98
L101:
	movl	$-6, %eax
	jmp	L98
L99:
	movl	$-4, %eax
L98:
	movl	%eax, 8(%ebx)
	movl	16(%ebp), %eax
	movl	%eax, 16(%ebx)
	cmpl	$0, 8(%ebx)
	js	L105
	movl	16(%ebp), %eax
	orl	$8, %eax
	movl	%eax, 16(%ebx)
L105:
	movl	20(%ebp), %eax
	movl	%eax, 12(%ebx)
	incl	12(%edi)
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC17:
	.ascii "unable to find a suitable global symbol for this reference\0"
	.align 2
	.def	_aout_add_gsym_reloc;	.scl	3;	.type	32;	.endef
_aout_add_gsym_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	12(%ebp), %edx
	movl	16(%ebp), %edi
	movl	28(%ebp), %ecx
	movl	$0, %eax
	cmpl	_stext+16, %edx
	jne	L107
	movl	_stext+28, %eax
	jmp	L108
L107:
	cmpl	_sdata+16, %edx
	jne	L109
	movl	_sdata+28, %eax
	jmp	L108
L109:
	cmpl	_sbss+16, %edx
	jne	L108
	movl	_sbss+28, %eax
L108:
	testl	%eax, %eax
	jne	L112
	testl	%ecx, %ecx
	je	L113
	testl	%edi, %edi
	je	L113
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_error
	jmp	L114
L113:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	24(%ebp), %ecx
	movl	%ecx, 12(%esp)
	call	_aout_add_reloc
L114:
	movl	%edi, %eax
	jmp	L106
L112:
	testl	%ecx, %ecx
	je	L115
	movl	%eax, %esi
	testl	%eax, %eax
	je	L133
L121:
	cmpl	%edi, 8(%esi)
	je	L122
	movl	20(%esi), %esi
	testl	%esi, %esi
	je	L133
	jmp	L121
L115:
	movl	$0, %esi
	movl	%eax, %edx
	testl	%eax, %eax
	je	L122
L129:
	cmpl	%edi, 8(%edx)
	jg	L125
	testl	%esi, %esi
	je	L128
	movl	8(%edx), %eax
	cmpl	8(%esi), %eax
	jle	L125
L128:
	movl	%edx, %esi
L125:
	movl	20(%edx), %edx
	testl	%edx, %edx
	jne	L129
L122:
	testl	%esi, %esi
	jne	L130
L133:
	testl	%ecx, %ecx
	je	L130
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_error
	movl	$0, %eax
	jmp	L106
L130:
	movl	8(%ebp), %eax
	movl	24(%eax), %ebx
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	8(%ebp), %edx
	movl	%eax, 24(%edx)
	movl	$0, (%eax)
	movl	8(%ebp), %ecx
	movl	4(%ecx), %edx
	movl	%edx, 4(%eax)
	movl	32(%esi), %edx
	movl	%edx, 8(%eax)
	movl	20(%ebp), %edx
	orl	$8, %edx
	movl	%edx, 16(%eax)
	movl	24(%ebp), %edx
	movl	%edx, 12(%eax)
	incl	12(%ecx)
	movl	%edi, %eax
	subl	8(%esi), %eax
L106:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC18:
	.ascii "`..gotoff' relocations require a non-global symbol in the section\0"
	.align 2
	.def	_aout_add_gotoff_reloc;	.scl	3;	.type	32;	.endef
_aout_add_gotoff_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	12(%ebp), %eax
	movl	$0, %edi
	cmpl	_stext+16, %eax
	jne	L135
	movl	_stext+32, %edi
	jmp	L136
L135:
	cmpl	_sdata+16, %eax
	jne	L137
	movl	_sdata+32, %edi
	jmp	L136
L137:
	cmpl	_sbss+16, %eax
	jne	L136
	movl	_sbss+32, %edi
L136:
	testl	%edi, %edi
	jne	L140
	movl	$1, (%esp)
	movl	$LC18, 4(%esp)
	call	*_error
L140:
	movl	24(%esi), %ebx
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, 24(%esi)
	movl	$0, (%eax)
	movl	4(%esi), %edx
	movl	%edx, 4(%eax)
	movl	32(%edi), %edx
	movl	%edx, 8(%eax)
	movl	$16, 16(%eax)
	movl	20(%ebp), %edx
	movl	%edx, 12(%eax)
	incl	12(%esi)
	movl	16(%ebp), %eax
	subl	8(%edi), %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC19:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC20:
	.ascii "attempt to assemble code in segment %d: defaulting to `.text'\0"
	.align 32
LC21:
	.ascii "attempt to initialise memory in the BSS section: ignored\0"
	.align 32
LC22:
	.ascii "uninitialised space declared in %s section: zeroing\0"
LC23:
	.ascii "code\0"
	.align 32
LC24:
	.ascii "OUT_RAWDATA with other than NO_SEG\0"
	.align 32
LC25:
	.ascii "a.out format does not support segment base references\0"
	.align 32
LC26:
	.ascii "Linux a.out format does not support any use of WRT\0"
	.align 32
LC27:
	.ascii "a.out format cannot produce non-PC-relative PLT references\0"
	.align 32
LC28:
	.ascii "a.out format does not support this use of WRT\0"
LC29:
	.ascii "intra-segment OUT_REL2ADR\0"
	.align 32
LC30:
	.ascii "a.out format cannot produce PC-relative GOT references\0"
LC31:
	.ascii "intra-segment OUT_REL4ADR\0"
	.align 2
	.def	_aout_out;	.scl	3;	.type	32;	.endef
_aout_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	20(%ebp), %edi
	movl	%ebx, %eax
	andl	$268435455, %eax
	movl	%eax, -24(%ebp)
	andl	$-268435456, %ebx
	cmpl	$-1, %esi
	jne	L142
	cmpl	$1073741824, %ebx
	je	L141
	movl	$1, (%esp)
	movl	$LC19, 4(%esp)
	call	*_error
	jmp	L141
L142:
	cmpl	_stext+16, %esi
	je	L228
	cmpl	_sdata+16, %esi
	jne	L146
	movl	$_sdata, -20(%ebp)
	jmp	L145
L146:
	cmpl	_sbss+16, %esi
	jne	L148
	movl	$0, -20(%ebp)
	jmp	L145
L148:
	movl	$0, (%esp)
	movl	$LC20, 4(%esp)
	movl	%esi, 8(%esp)
	call	*_error
L228:
	movl	$_stext, -20(%ebp)
L145:
	cmpl	$0, -20(%ebp)
	jne	L150
	cmpl	$1073741824, %ebx
	je	L227
	movl	$0, (%esp)
	movl	$LC21, 4(%esp)
	call	*_error
	cmpl	$536870912, %ebx
	jne	L151
	movl	$2, -24(%ebp)
	jmp	L155
L151:
	cmpl	$805306368, %ebx
	jne	L155
	movl	$4, -24(%ebp)
	jmp	L155
L150:
	cmpl	$1073741824, %ebx
	jne	L154
L227:
	cmpl	$0, -20(%ebp)
	je	L155
	movl	$0, (%esp)
	movl	$LC22, 4(%esp)
	cmpl	_stext+16, %esi
	jne	L156
	movl	$LC23, %eax
	jmp	L157
L156:
	movl	$LC12, %eax
L157:
	movl	%eax, 8(%esp)
	call	*_error
	movl	-20(%ebp), %esi
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	jmp	L239
L155:
	movl	-24(%ebp), %ecx
	addl	%ecx, _sbss+4
	jmp	L141
L154:
	testl	%ebx, %ebx
	jne	L160
	cmpl	$-1, %edi
	je	L161
	movl	$3, (%esp)
	movl	$LC24, 4(%esp)
	call	*_error
L161:
	movl	-20(%ebp), %esi
	movl	%esi, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-24(%ebp), %ecx
	movl	%ecx, 8(%esp)
	jmp	L238
L160:
	cmpl	$268435456, %ebx
	jne	L163
	movl	12(%ebp), %eax
	movl	(%eax), %esi
	cmpl	$-1, %edi
	je	L164
	testl	$1, %edi
	je	L165
	movl	$1, (%esp)
	movl	$LC25, 4(%esp)
	jmp	L229
L165:
	cmpl	$-1, 24(%ebp)
	jne	L167
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	$0, 8(%esp)
	jmp	L232
L167:
	cmpl	$0, _bsd
	jne	L169
	movl	$1, (%esp)
	movl	$LC26, 4(%esp)
	jmp	L229
L169:
	movl	_aout_gotpc_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L171
	movl	$64, _is_pic
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	$1, 8(%esp)
L232:
	movl	-24(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_aout_add_reloc
	jmp	L164
L171:
	movl	_aout_gotoff_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L173
	movl	$64, _is_pic
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	%esi, 8(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_aout_add_gotoff_reloc
	jmp	L231
L173:
	movl	_aout_got_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L175
	movl	$64, _is_pic
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	%esi, 8(%esp)
	movl	$16, 12(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	$1, 20(%esp)
	jmp	L230
L175:
	movl	_aout_sym_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L177
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	%esi, 8(%esp)
	movl	$0, 12(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	$0, 20(%esp)
L230:
	call	_aout_add_gsym_reloc
L231:
	movl	%eax, %esi
	jmp	L164
L177:
	movl	_aout_plt_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L179
	movl	$64, _is_pic
	movl	$1, (%esp)
	movl	$LC27, 4(%esp)
	jmp	L229
L179:
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
L229:
	call	*_error
L164:
	leal	-16(%ebp), %ebx
	cmpl	$2, -24(%ebp)
	jne	L181
	movl	%esi, %ecx
	movb	%cl, -16(%ebp)
	movl	%esi, %eax
	sarl	$8, %eax
	jmp	L233
L181:
	movl	%esi, %eax
	movb	%al, (%ebx)
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
L233:
	movb	%al, 1(%ebx)
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
L239:
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	jmp	L238
L163:
	cmpl	$536870912, %ebx
	jne	L192
	cmpl	%esi, %edi
	jne	L193
	movl	$3, (%esp)
	movl	$LC29, 4(%esp)
	call	*_error
L193:
	cmpl	$-1, %edi
	je	L194
	testl	$1, %edi
	je	L194
	movl	$1, (%esp)
	movl	$LC25, 4(%esp)
	jmp	L234
L194:
	cmpl	$-1, 24(%ebp)
	jne	L196
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	$1, 8(%esp)
	jmp	L235
L196:
	cmpl	$0, _bsd
	jne	L198
	movl	$1, (%esp)
	movl	$LC26, 4(%esp)
	jmp	L234
L198:
	movl	_aout_plt_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L200
	movl	$64, _is_pic
	movl	-20(%ebp), %esi
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	movl	$33, 8(%esp)
L235:
	movl	$2, 12(%esp)
	call	_aout_add_reloc
	jmp	L195
L200:
	movl	_aout_gotpc_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L203
	movl	_aout_gotoff_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L203
	movl	_aout_got_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L202
L203:
	movl	$1, (%esp)
	movl	$LC30, 4(%esp)
	jmp	L234
L202:
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
L234:
	call	*_error
L195:
	leal	-16(%ebp), %ebx
	movzbl	-24(%ebp), %edx
	movl	-20(%ebp), %eax
	addb	4(%eax), %dl
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	subb	%dl, %al
	movb	%al, -16(%ebp)
	movl	-24(%ebp), %edx
	movl	-20(%ebp), %esi
	addl	4(%esi), %edx
	movl	12(%ebp), %esi
	movl	(%esi), %eax
	subl	%edx, %eax
	shrl	$8, %eax
	movb	%al, 1(%ebx)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$2, 8(%esp)
	jmp	L238
L192:
	cmpl	$805306368, %ebx
	jne	L141
	cmpl	%esi, %edi
	jne	L210
	movl	$3, (%esp)
	movl	$LC31, 4(%esp)
	call	*_error
L210:
	cmpl	$-1, %edi
	je	L211
	testl	$1, %edi
	je	L211
	movl	$1, (%esp)
	movl	$LC25, 4(%esp)
	jmp	L236
L211:
	cmpl	$-1, 24(%ebp)
	jne	L213
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%edi, 4(%esp)
	movl	$1, 8(%esp)
	jmp	L237
L213:
	cmpl	$0, _bsd
	jne	L215
	movl	$1, (%esp)
	movl	$LC26, 4(%esp)
	jmp	L236
L215:
	movl	_aout_plt_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L217
	movl	$64, _is_pic
	movl	-20(%ebp), %esi
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	movl	$33, 8(%esp)
L237:
	movl	$4, 12(%esp)
	call	_aout_add_reloc
	jmp	L212
L217:
	movl	_aout_gotpc_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L220
	movl	_aout_gotoff_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	je	L220
	movl	_aout_got_sect, %eax
	incl	%eax
	cmpl	%eax, 24(%ebp)
	jne	L219
L220:
	movl	$1, (%esp)
	movl	$LC30, 4(%esp)
	jmp	L236
L219:
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
L236:
	call	*_error
L212:
	leal	-16(%ebp), %ebx
	movzbl	-24(%ebp), %edx
	movl	-20(%ebp), %eax
	addb	4(%eax), %dl
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	subb	%dl, %al
	movl	%ebx, %ecx
	movb	%al, -16(%ebp)
	incl	%ebx
	movl	-24(%ebp), %edx
	movl	-20(%ebp), %esi
	addl	4(%esi), %edx
	movl	12(%ebp), %esi
	movl	(%esi), %eax
	subl	%edx, %eax
	shrl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	-24(%ebp), %edx
	movl	-20(%ebp), %eax
	addl	4(%eax), %edx
	movl	(%esi), %eax
	subl	%edx, %eax
	shrl	$16, %eax
	movb	%al, (%ebx)
	movl	-24(%ebp), %edx
	movl	-20(%ebp), %esi
	addl	4(%esi), %edx
	movl	12(%ebp), %esi
	movl	(%esi), %eax
	subl	%edx, %eax
	shrl	$24, %eax
	movb	%al, 1(%ebx)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	movl	$4, 8(%esp)
L238:
	call	_aout_sect_write
L141:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.data
_pad.0:
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.text
	.align 2
	.def	_aout_pad_sections;	.scl	3;	.type	32;	.endef
_aout_pad_sections:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$_stext, (%esp)
	movl	$_pad.0, 4(%esp)
	movl	_stext+4, %eax
	negl	%eax
	andl	$3, %eax
	movl	%eax, 8(%esp)
	call	_aout_sect_write
	movl	$_sdata, (%esp)
	movl	$_pad.0, 4(%esp)
	movl	_sdata+4, %eax
	negl	%eax
	andl	$3, %eax
	movl	%eax, 8(%esp)
	call	_aout_sect_write
	movl	_sbss+4, %eax
	addl	$3, %eax
	andl	$-4, %eax
	movl	%eax, _sbss+4
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_aout_fixup_relocs;	.scl	3;	.type	32;	.endef
_aout_fixup_relocs:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
	movl	(%esi), %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	20(%esi), %ebx
	testl	%ebx, %ebx
	je	L265
L263:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_saa_fread
	leal	-12(%ebp), %ecx
	movzbl	-12(%ebp), %edx
	cmpl	$1, 12(%ebx)
	jle	L246
	movzbl	1(%ecx), %eax
	sall	$8, %eax
	addl	%eax, %edx
	cmpl	$4, 12(%ebx)
	jne	L246
	movzbl	2(%ecx), %eax
	sall	$16, %eax
	addl	%eax, %edx
	movzbl	3(%ecx), %eax
	sall	$24, %eax
	addl	%eax, %edx
L246:
	cmpl	$-6, 8(%ebx)
	jne	L248
	addl	_stext+4, %edx
	jmp	L249
L248:
	cmpl	$-8, 8(%ebx)
	jne	L249
	movl	_stext+4, %eax
	addl	_sdata+4, %eax
	addl	%eax, %edx
L249:
	cmpl	$4, 12(%ebx)
	jne	L251
	movb	%dl, (%ecx)
	incl	%ecx
	movl	%edx, %eax
	sarl	$8, %eax
	movb	%al, (%ecx)
	incl	%ecx
	movl	%edx, %eax
	sarl	$16, %eax
	movb	%al, (%ecx)
	movl	%edx, %eax
	sarl	$24, %eax
	jmp	L266
L251:
	cmpl	$2, 12(%ebx)
	jne	L258
	movb	%dl, (%ecx)
	movl	%edx, %eax
	sarl	$8, %eax
L266:
	movb	%al, 1(%ecx)
	jmp	L257
L258:
	movb	%dl, (%ecx)
L257:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_saa_fwrite
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L263
L265:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_aout_write;	.scl	3;	.type	32;	.endef
_aout_write:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _bsd
	je	L268
	movl	_is_pic, %eax
	orl	$117540352, %eax
	jmp	L269
L268:
	movl	$6553863, %eax
L269:
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_stext+4, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_sdata+4, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_sbss+4, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_nsyms, %eax
	leal	(%eax,%eax,2), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_stext+12, %eax
	sall	$3, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_sdata+12, %eax
	sall	$3, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_stext, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	_sdata, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	_stext+20, %eax
	movl	%eax, (%esp)
	call	_aout_write_relocs
	movl	_sdata+20, %eax
	movl	%eax, (%esp)
	call	_aout_write_relocs
	call	_aout_write_syms
	movl	_strslen, %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_strs, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	leave
	ret
	.align 2
	.def	_aout_write_relocs;	.scl	3;	.type	32;	.endef
_aout_write_relocs:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	je	L282
L280:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	cmpl	$0, 8(%ebx)
	js	L274
	movl	8(%ebx), %edx
	jmp	L275
L274:
	movl	8(%ebx), %eax
	movl	%eax, %edx
	negl	%edx
L275:
	movl	16(%ebx), %eax
	sall	$24, %eax
	orl	%eax, %edx
	cmpl	$1, 12(%ebx)
	je	L277
	cmpl	$2, 12(%ebx)
	jne	L278
	orl	$33554432, %edx
	jmp	L277
L278:
	orl	$67108864, %edx
L277:
	movl	%edx, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L280
L282:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_aout_write_syms;	.scl	3;	.type	32;	.endef
_aout_write_syms:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	$0, %esi
	cmpl	_nsyms, %esi
	jae	L293
L291:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %ebx
	movl	(%eax), %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	4(%ebx), %eax
	andl	$-16385, %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	4(%ebx), %eax
	andl	$14, %eax
	cmpl	$6, %eax
	jne	L288
	movl	8(%ebx), %eax
	addl	_stext+4, %eax
	movl	%eax, 8(%ebx)
L288:
	movl	4(%ebx), %eax
	andl	$14, %eax
	cmpl	$8, %eax
	jne	L289
	movl	_stext+4, %eax
	addl	_sdata+4, %eax
	addl	%eax, 8(%ebx)
L289:
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	testb	$64, 5(%ebx)
	je	L286
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$13, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	12(%ebx), %eax
	movl	%eax, (%esp)
	movl	_aoutfp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	incl	%esi
L286:
	incl	%esi
	cmpl	_nsyms, %esi
	jb	L291
L293:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_aout_sect_write;	.scl	3;	.type	32;	.endef
_aout_sect_write:
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
	.def	_aout_segbase;	.scl	3;	.type	32;	.endef
_aout_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.align 2
	.def	_aout_directive;	.scl	3;	.type	32;	.endef
_aout_directive:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
LC32:
	.ascii ".o\0"
	.align 2
	.def	_aout_filename;	.scl	3;	.type	32;	.endef
_aout_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC32, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC33:
	.ascii "%define __SECT__ [section .text]\0"
LC34:
	.ascii "%macro __NASM_CDecl__ 1\0"
LC35:
	.ascii "%endmacro\0"
	.data
	.align 4
_aout_stdmac:
	.long	LC33
	.long	LC34
	.long	LC35
	.long	0
	.text
	.align 2
	.def	_aout_set_info;	.scl	3;	.type	32;	.endef
_aout_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
.globl _of_aout
LC36:
	.ascii "Linux a.out object files\0"
LC37:
	.ascii "aout\0"
	.data
	.align 32
_of_aout:
	.long	LC36
	.long	LC37
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_aout_stdmac
	.long	_aout_init
	.long	_aout_set_info
	.long	_aout_out
	.long	_aout_deflabel
	.long	_aout_section_names
	.long	_aout_segbase
	.long	_aout_directive
	.long	_aout_filename
	.long	_aout_cleanup
.globl _of_aoutb
	.text
	.align 32
LC38:
	.ascii "NetBSD/FreeBSD a.out object files\0"
LC39:
	.ascii "aoutb\0"
	.data
	.align 32
_of_aoutb:
	.long	LC38
	.long	LC39
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_aout_stdmac
	.long	_aoutb_init
	.long	_aout_set_info
	.long	_aout_out
	.long	_aout_deflabel
	.long	_aout_section_names
	.long	_aout_segbase
	.long	_aout_directive
	.long	_aout_filename
	.long	_aout_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _stext,48
.lcomm _sdata,48
.lcomm _sbss,48
.lcomm _syms,16
.lcomm _nsyms,16
.lcomm _bsym,16
.lcomm _strs,16
.lcomm _strslen,16
.lcomm _fwds,16
.lcomm _aoutfp,16
.lcomm _error,16
.lcomm _evaluate,16
.lcomm _bsd,16
.lcomm _is_pic,16
.lcomm _aout_gotpc_sect,16
.lcomm _aout_gotoff_sect,16
.lcomm _aout_got_sect,16
.lcomm _aout_plt_sect,16
.lcomm _aout_sym_sect,16
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
	.def	_saa_fwrite;	.scl	2;	.type	32;	.endef
	.def	_saa_fread;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_raa_read;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_raa_write;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_raa_free;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_raa_init;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
