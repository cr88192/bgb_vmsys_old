	.file	"outas86.c"
	.text
	.align 2
	.def	_as86_init;	.scl	3;	.type	32;	.endef
_as86_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, _as86fp
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _stext
	movl	$0, _stext+4
	movl	$0, _stext+24
	movl	$0, _stext+20
	movl	$_stext+20, _stext+28
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _sdata
	movl	$0, _sdata+24
	movl	$0, _sdata+20
	movl	$_sdata+20, _sdata+28
	movl	$0, _sdata+8
	movl	$0, _sdata+4
	movl	$0, _sdata+12
	movl	$0, _stext+8
	movl	$0, _stext+4
	movl	$0, _stext+12
	movl	$0, _bsslen
	call	_seg_alloc
	movl	%eax, _stext+16
	call	_seg_alloc
	movl	%eax, _sdata+16
	call	_seg_alloc
	movl	%eax, _bssindex
	movl	$16, (%esp)
	call	_saa_init
	movl	%eax, _syms
	movl	$0, _nsyms
	call	_raa_init
	movl	%eax, _bsym
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _strs
	movl	$0, _strslen
	movl	$_as86_module, (%esp)
	call	_as86_add_string
	leave
	ret
	.align 2
	.def	_as86_cleanup;	.scl	3;	.type	32;	.endef
_as86_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	_as86_write
	movl	_as86fp, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	_stext, %eax
	movl	%eax, (%esp)
	call	_saa_free
	cmpl	$0, _stext+20
	je	L12
L6:
	movl	_stext+20, %edx
	movl	(%edx), %eax
	movl	%eax, _stext+20
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _stext+20
	jne	L6
L12:
	movl	_sdata, %eax
	movl	%eax, (%esp)
	call	_saa_free
	cmpl	$0, _sdata+20
	je	L14
L10:
	movl	_sdata+20, %edx
	movl	(%edx), %eax
	movl	%eax, _sdata+20
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _sdata+20
	jne	L10
L14:
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
LC0:
	.ascii ".text\0"
LC1:
	.ascii ".data\0"
LC2:
	.ascii ".bss\0"
	.align 2
	.def	_as86_section_names;	.scl	3;	.type	32;	.endef
_as86_section_names:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	jne	L17
	movl	16(%ebp), %eax
	movl	$16, (%eax)
	jmp	L24
L17:
	movl	%ebx, (%esp)
	movl	$LC0, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L18
L24:
	movl	_stext+16, %edx
	jmp	L15
L18:
	movl	%ebx, (%esp)
	movl	$LC1, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L20
	movl	_sdata+16, %edx
	jmp	L15
L20:
	movl	%ebx, (%esp)
	movl	$LC2, 4(%esp)
	call	_strcmp
	movl	$-1, %edx
	testl	%eax, %eax
	jne	L15
	movl	_bssindex, %edx
L15:
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_as86_add_string;	.scl	3;	.type	32;	.endef
_as86_add_string:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	_strslen, %esi
	movl	%ebx, (%esp)
	call	_strlen
	movl	%eax, %edi
	movl	_strs, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	leal	1(%edi), %eax
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movl	%edi, %eax
	addl	_strslen, %eax
	incl	%eax
	movl	%eax, _strslen
	movl	%esi, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC3:
	.ascii "as86 format does not support any special symbol types\0"
	.align 32
LC4:
	.ascii "unrecognised special symbol `%s'\0"
	.align 2
	.def	_as86_deflabel;	.scl	3;	.type	32;	.endef
_as86_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	cmpl	$0, 24(%ebp)
	je	L27
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	call	*_error
L27:
	cmpb	$46, (%esi)
	jne	L28
	cmpb	$46, 1(%esi)
	jne	L28
	cmpb	$64, 2(%esi)
	je	L28
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	movl	%esi, 8(%esp)
	call	*_error
	jmp	L26
L28:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_wstruct
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_as86_add_string
	movl	%eax, (%ebx)
	movl	$0, 4(%ebx)
	cmpl	$-1, %edi
	jne	L29
	movl	$16, 4(%ebx)
	jmp	L40
L29:
	cmpl	_stext+16, %edi
	jne	L31
L40:
	movl	$0, 8(%ebx)
	jmp	L30
L31:
	cmpl	_sdata+16, %edi
	jne	L33
	movl	$3, 8(%ebx)
	jmp	L30
L33:
	cmpl	_bssindex, %edi
	jne	L35
	movl	$4, 8(%ebx)
	jmp	L30
L35:
	orl	$64, 4(%ebx)
	movl	$15, 8(%ebx)
L30:
	cmpl	$2, 20(%ebp)
	jne	L37
	movl	$3, 8(%ebx)
L37:
	cmpl	$0, 20(%ebp)
	je	L38
	movl	4(%ebx), %eax
	testl	$64, %eax
	jne	L38
	orl	$128, %eax
	movl	%eax, 4(%ebx)
L38:
	movl	16(%ebp), %eax
	movl	%eax, 12(%ebx)
	cmpl	$-1, %edi
	je	L39
	cmpl	_stext+16, %edi
	je	L39
	cmpl	_sdata+16, %edi
	je	L39
	cmpl	_bssindex, %edi
	je	L39
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	movl	_nsyms, %eax
	movl	%eax, 8(%esp)
	call	_raa_write
	movl	%eax, _bsym
L39:
	incl	_nsyms
L26:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_as86_add_piece;	.scl	3;	.type	32;	.endef
_as86_add_piece:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	24(%ebp), %edi
	addl	%edi, 12(%esi)
	cmpl	$0, 12(%ebp)
	jne	L42
	cmpl	$0, 24(%esi)
	je	L42
	movl	24(%esi), %eax
	cmpl	$0, 4(%eax)
	jne	L42
	addl	%edi, 16(%eax)
	jmp	L41
L42:
	movl	28(%esi), %ebx
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, 24(%esi)
	movl	%eax, %ebx
	movl	%eax, 28(%esi)
	movl	$0, (%eax)
	movl	12(%ebp), %eax
	movl	%eax, 4(%ebx)
	movl	16(%ebp), %eax
	movl	%eax, 8(%ebx)
	movl	%edi, 16(%ebx)
	movl	28(%ebp), %eax
	movl	%eax, 20(%ebx)
	cmpl	$1, 12(%ebp)
	jne	L41
	movl	20(%ebp), %eax
	cmpl	_stext+16, %eax
	jne	L43
	movl	$0, 12(%ebx)
	jmp	L41
L43:
	cmpl	$1, 12(%ebp)
	jne	L41
	movl	20(%ebp), %eax
	cmpl	_sdata+16, %eax
	jne	L45
	movl	$3, 12(%ebx)
	jmp	L41
L45:
	cmpl	$1, 12(%ebp)
	jne	L41
	movl	20(%ebp), %eax
	cmpl	_bssindex, %eax
	jne	L47
	movl	$4, 12(%ebx)
	jmp	L41
L47:
	cmpl	$1, 12(%ebp)
	jne	L41
	movl	_bsym, %eax
	movl	%eax, (%esp)
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_raa_read
	movl	%eax, 12(%ebx)
	movl	$2, 4(%ebx)
L41:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC5:
	.ascii "WRT not supported by as86 output format\0"
	.align 32
LC6:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC7:
	.ascii "attempt to assemble code in segment %d: defaulting to `.text'\0"
	.align 32
LC8:
	.ascii "attempt to initialise memory in the BSS section: ignored\0"
	.align 32
LC9:
	.ascii "uninitialised space declared in %s section: zeroing\0"
LC10:
	.ascii "code\0"
LC11:
	.ascii "data\0"
	.align 32
LC12:
	.ascii "OUT_RAWDATA with other than NO_SEG\0"
LC14:
	.ascii "intra-segment OUT_REL2ADR\0"
LC15:
	.ascii "intra-segment OUT_REL4ADR\0"
	.align 32
LC13:
	.ascii "as86 format does not support segment base references\0"
	.align 2
	.def	_as86_out;	.scl	3;	.type	32;	.endef
_as86_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	%ebx, %edi
	andl	$268435455, %edi
	cmpl	$-1, 24(%ebp)
	je	L51
	movl	$1, (%esp)
	movl	$LC5, 4(%esp)
	call	*_error
L51:
	andl	$-268435456, %ebx
	cmpl	$-1, %esi
	jne	L52
	cmpl	$1073741824, %ebx
	je	L50
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	jmp	L100
L52:
	cmpl	_stext+16, %esi
	je	L96
	cmpl	_sdata+16, %esi
	jne	L56
	movl	$_sdata, -20(%ebp)
	jmp	L55
L56:
	cmpl	_bssindex, %esi
	jne	L58
	movl	$0, -20(%ebp)
	jmp	L55
L58:
	movl	$0, (%esp)
	movl	$LC7, 4(%esp)
	movl	%esi, 8(%esp)
	call	*_error
L96:
	movl	$_stext, -20(%ebp)
L55:
	cmpl	$0, -20(%ebp)
	jne	L60
	cmpl	$1073741824, %ebx
	je	L95
	movl	$0, (%esp)
	movl	$LC8, 4(%esp)
	call	*_error
	cmpl	$536870912, %ebx
	jne	L61
	movl	$2, %edi
	jmp	L65
L61:
	cmpl	$805306368, %ebx
	jne	L65
	movl	$4, %edi
	jmp	L65
L60:
	cmpl	$1073741824, %ebx
	jne	L64
L95:
	cmpl	$0, -20(%ebp)
	je	L65
	movl	$0, (%esp)
	movl	$LC9, 4(%esp)
	cmpl	_stext+16, %esi
	jne	L66
	movl	$LC10, %eax
	jmp	L67
L66:
	movl	$LC11, %eax
L67:
	movl	%eax, 8(%esp)
	call	*_error
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	jmp	L104
L65:
	addl	%edi, _bsslen
	jmp	L50
L64:
	testl	%ebx, %ebx
	jne	L70
	cmpl	$-1, 20(%ebp)
	je	L71
	movl	$3, (%esp)
	movl	$LC12, 4(%esp)
	call	*_error
L71:
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	jmp	L104
L70:
	cmpl	$268435456, %ebx
	jne	L73
	cmpl	$-1, 20(%ebp)
	je	L74
	testl	$1, 20(%ebp)
	jne	L98
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	movl	-20(%ebp), %edx
	movl	%edx, (%esp)
	movl	$1, 4(%esp)
	movl	%eax, 8(%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 12(%esp)
	jmp	L103
L74:
	movl	12(%ebp), %edx
	movzbl	(%edx), %eax
	movb	%al, -16(%ebp)
	leal	-15(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	2(%ecx),%eax
	movb	%al, (%edx)
	movsbl	3(%ecx),%eax
	movb	%al, 1(%edx)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
L104:
	movl	%edi, 8(%esp)
	call	_as86_sect_write
	movl	-20(%ebp), %edx
	movl	%edx, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
L103:
	movl	%edi, 16(%esp)
	movl	$0, 20(%esp)
	jmp	L99
L73:
	cmpl	$536870912, %ebx
	jne	L84
	cmpl	%esi, 20(%ebp)
	jne	L85
	movl	$3, (%esp)
	movl	$LC14, 4(%esp)
	call	*_error
L85:
	cmpl	$-1, 20(%ebp)
	je	L50
	testl	$1, 20(%ebp)
	jne	L98
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	movl	-20(%ebp), %edx
	movl	%edx, (%esp)
	movl	$1, 4(%esp)
	subl	%edi, %eax
	addl	$2, %eax
	movl	%eax, 8(%esp)
	movl	20(%ebp), %ecx
	movl	%ecx, 12(%esp)
	movl	$2, 16(%esp)
	jmp	L97
L84:
	cmpl	$805306368, %ebx
	jne	L50
	cmpl	%esi, 20(%ebp)
	jne	L91
	movl	$3, (%esp)
	movl	$LC15, 4(%esp)
	call	*_error
L91:
	cmpl	$-1, 20(%ebp)
	je	L50
	testl	$1, 20(%ebp)
	je	L93
L98:
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
L100:
	call	*_error
	jmp	L50
L93:
	movl	12(%ebp), %edx
	movl	(%edx), %eax
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	$1, 4(%esp)
	subl	%edi, %eax
	addl	$4, %eax
	movl	%eax, 8(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$4, 16(%esp)
L97:
	movl	$1, 20(%esp)
L99:
	call	_as86_add_piece
L50:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_as86_write;	.scl	3;	.type	32;	.endef
_as86_write:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	$0, %edi
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	$0, %esi
	cmpl	_nsyms, %esi
	jae	L140
L117:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %edx
	cmpl	$4, 8(%eax)
	jne	L110
	movl	$3, 8(%eax)
	movl	12(%eax), %eax
	addl	_sdata+12, %eax
	movl	%eax, 12(%edx)
L110:
	movl	4(%edx), %eax
	orl	8(%edx), %eax
	movl	%eax, 4(%edx)
	cmpl	$0, 12(%edx)
	jne	L111
	addl	$4, %edi
	jmp	L108
L111:
	cmpl	$255, 12(%edx)
	ja	L113
	orl	$16384, 4(%edx)
	addl	$5, %edi
	jmp	L108
L113:
	cmpl	$65535, 12(%edx)
	ja	L115
	orl	$32768, 4(%edx)
	addl	$6, %edi
	jmp	L108
L115:
	orl	$49152, 4(%edx)
	addl	$8, %edi
L108:
	incl	%esi
	cmpl	_nsyms, %esi
	jb	L117
L140:
	movl	$0, %esi
	movl	$0, %ebx
	cmpl	$65535, _stext+12
	jbe	L118
	movl	$50331648, %esi
	movl	$4, %ebx
	jmp	L119
L118:
	orl	$33554432, %esi
	addl	$2, %ebx
L119:
	cmpl	$65535, _sdata+12
	jbe	L120
	orl	$-1073741824, %esi
	addl	$4, %ebx
	jmp	L121
L120:
	orl	$-2147483648, %esi
	addl	$2, %ebx
L121:
	movl	$100003, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$42, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	leal	(%ebx,%edi), %eax
	addl	_strslen, %eax
	addl	$27, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_stext+12, %eax
	addl	_sdata+12, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_strslen, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$0, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	$1431655765, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	%esi, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	testl	$16777216, %esi
	je	L122
	movl	_stext+12, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	jmp	L123
L122:
	movl	_stext+12, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
L123:
	testl	$1073741824, %esi
	je	L124
	movl	_sdata+12, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	jmp	L125
L124:
	movl	_sdata+12, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
L125:
	movl	_nsyms, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	$0, %esi
	cmpl	_nsyms, %esi
	jae	L142
L138:
	movl	_syms, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, %ebx
	movl	(%eax), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	4(%ebx), %eax
	andl	$49152, %eax
	cmpl	$16384, %eax
	je	L132
	cmpl	$16384, %eax
	jle	L128
	cmpl	$32768, %eax
	je	L133
	cmpl	$49152, %eax
	je	L134
	jmp	L128
L132:
	movl	12(%ebx), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	jmp	L128
L133:
	movl	12(%ebx), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	jmp	L128
L134:
	movl	12(%ebx), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
L128:
	incl	%esi
	cmpl	_nsyms, %esi
	jb	L138
L142:
	movl	_strs, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	$-1, _as86_reloc_size
	movl	$_stext, (%esp)
	movl	$0, 4(%esp)
	call	_as86_write_section
	movl	$_sdata, (%esp)
	movl	$3, 4(%esp)
	call	_as86_write_section
	movl	$0, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC16:
	.ascii "bizarre relocation size %d\0"
	.align 2
	.def	_as86_set_rsize;	.scl	3;	.type	32;	.endef
_as86_set_rsize:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	cmpl	%eax, _as86_reloc_size
	je	L143
	movl	%eax, _as86_reloc_size
	cmpl	$2, %eax
	je	L147
	cmpl	$2, %eax
	jg	L151
	cmpl	$1, %eax
	je	L146
	jmp	L149
L151:
	cmpl	$4, %eax
	je	L148
	jmp	L149
L146:
	movl	$1, (%esp)
	jmp	L152
L147:
	movl	$2, (%esp)
	jmp	L152
L148:
	movl	$3, (%esp)
L152:
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	jmp	L143
L149:
	movl	$3, (%esp)
	movl	$LC16, 4(%esp)
	movl	%eax, 8(%esp)
	call	*_error
L143:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_as86_write_section;	.scl	3;	.type	32;	.endef
_as86_write_section:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	12(%ebp), %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	8(%ebp), %eax
	movl	20(%eax), %edi
	testl	%edi, %edi
	je	L196
L194:
	movl	4(%edi), %eax
	cmpl	$1, %eax
	je	L165
	cmpl	$1, %eax
	jg	L193
	testl	%eax, %eax
	je	L159
	jmp	L156
L193:
	cmpl	$2, %eax
	je	L171
	jmp	L156
L159:
	movl	16(%edi), %esi
L160:
	movl	%esi, %ebx
	cmpl	$64, %esi
	jle	L163
	movl	$64, %ebx
L163:
	movl	%ebx, %eax
	andl	$63, %eax
	orl	$64, %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	%eax, (%esp)
	leal	-88(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_saa_rnbytes
	leal	-88(%ebp), %edx
	movl	%edx, (%esp)
	movl	$1, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	_as86fp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	subl	%ebx, %esi
	testl	%esi, %esi
	jle	L156
	jmp	L160
L165:
	cmpl	$4, 12(%edi)
	jne	L166
	movl	$3, 12(%edi)
	movl	8(%edi), %eax
	addl	_sdata+12, %eax
	movl	%eax, 8(%edi)
L166:
	movl	16(%edi), %eax
	movl	%eax, (%esp)
	call	_as86_set_rsize
	movl	12(%edi), %eax
	cmpl	$0, 20(%edi)
	je	L167
	orl	$160, %eax
	jmp	L168
L167:
	orl	$128, %eax
L168:
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	cmpl	$2, _as86_reloc_size
	je	L186
	jmp	L187
L171:
	movl	16(%edi), %eax
	movl	%eax, (%esp)
	call	_as86_set_rsize
	movl	8(%edi), %ebx
	cmpl	$65535, %ebx
	jbe	L172
	movl	$3, %ebx
	jmp	L173
L172:
	cmpl	$255, %ebx
	jbe	L174
	movl	$2, %ebx
	jmp	L173
L174:
	testl	%ebx, %ebx
	setne	%al
	movzbl	%al, %ebx
L173:
	cmpl	$0, 20(%edi)
	je	L178
	movl	$224, %eax
	jmp	L179
L178:
	movl	$192, %eax
L179:
	orl	%ebx, %eax
	cmpl	$255, 12(%edi)
	jle	L180
	orl	$4, %eax
L180:
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	cmpl	$255, 12(%edi)
	jle	L181
	movl	12(%edi), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	jmp	L182
L181:
	movl	12(%edi), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
L182:
	cmpl	$1, %ebx
	je	L185
	cmpl	$1, %ebx
	jle	L156
	cmpl	$2, %ebx
	je	L186
	cmpl	$3, %ebx
	je	L187
	jmp	L156
L185:
	movl	8(%edi), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	jmp	L156
L186:
	movl	8(%edi), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	jmp	L156
L187:
	movl	8(%edi), %eax
	movl	%eax, (%esp)
	movl	_as86fp, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
L156:
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L194
L196:
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_as86_sect_write;	.scl	3;	.type	32;	.endef
_as86_sect_write:
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
	.def	_as86_segbase;	.scl	3;	.type	32;	.endef
_as86_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.align 2
	.def	_as86_directive;	.scl	3;	.type	32;	.endef
_as86_directive:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
LC17:
	.ascii ".o\0"
	.align 2
	.def	_as86_filename;	.scl	3;	.type	32;	.endef
_as86_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	%esi, (%esp)
	movl	$46, 4(%esp)
	call	_strrchr
	testl	%eax, %eax
	je	L201
	movl	$_as86_module, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, %ebx
	subl	%esi, %ebx
	movl	%ebx, 8(%esp)
	call	_strncpy
	movb	$0, _as86_module(%ebx)
	jmp	L202
L201:
	movl	$_as86_module, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
L202:
	movl	%esi, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC17, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC18:
	.ascii "%define __SECT__ [section .text]\0"
LC19:
	.ascii "%macro __NASM_CDecl__ 1\0"
LC20:
	.ascii "%endmacro\0"
	.data
	.align 4
_as86_stdmac:
	.long	LC18
	.long	LC19
	.long	LC20
	.long	0
	.text
	.align 2
	.def	_as86_set_info;	.scl	3;	.type	32;	.endef
_as86_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.align 2
.globl _as86_linenumber
	.def	_as86_linenumber;	.scl	2;	.type	32;	.endef
_as86_linenumber:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _of_as86
	.align 32
LC21:
	.ascii "Linux as86 (bin86 version 0.3) object files\0"
LC22:
	.ascii "as86\0"
	.data
	.align 32
_of_as86:
	.long	LC21
	.long	LC22
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_as86_stdmac
	.long	_as86_init
	.long	_as86_set_info
	.long	_as86_out
	.long	_as86_deflabel
	.long	_as86_section_names
	.long	_as86_segbase
	.long	_as86_directive
	.long	_as86_filename
	.long	_as86_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _as86_module,256
.lcomm _stext,32
.lcomm _sdata,32
.lcomm _bsslen,16
.lcomm _bssindex,16
.lcomm _syms,16
.lcomm _nsyms,16
.lcomm _bsym,16
.lcomm _strs,16
.lcomm _strslen,16
.lcomm _as86_reloc_size,16
.lcomm _as86fp,16
.lcomm _error,16
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_strrchr;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_saa_rnbytes;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_raa_read;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_raa_write;	.scl	2;	.type	32;	.endef
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_raa_free;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_raa_init;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
