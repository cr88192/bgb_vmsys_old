	.file	"outrdf2.c"
	.text
LC0:
	.ascii "RDOFF2\0"
	.data
	.align 4
_RDOFF2Id:
	.long	LC0
	.text
LC1:
	.ascii "null\0"
LC2:
	.ascii "text\0"
LC3:
	.ascii "code\0"
LC4:
	.ascii "data\0"
LC5:
	.ascii "comment\0"
LC6:
	.ascii "lcomment\0"
LC7:
	.ascii "pcomment\0"
LC8:
	.ascii "symdebug\0"
LC9:
	.ascii "linedebug\0"
	.data
	.align 32
_segmenttypes:
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.align 32
_segmenttypenumbers:
	.long	0
	.long	1
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.text
LC10:
	.ascii ".text\0"
LC11:
	.ascii ".data\0"
LC12:
	.ascii ".bss\0"
	.align 32
LC13:
	.ascii "rdf segment numbers not allocated as expected (%d,%d,%d)\0"
	.align 2
	.def	_rdf2_init;	.scl	3;	.type	32;	.endef
_rdf2_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	$LC10, _segments
	movl	$0, _segments+4
	movw	$1, _segments+8
	movw	$0, _segments+10
	movl	$0, _segments+12
	movl	$LC11, _segments+16
	movl	$1, _segments+20
	movw	$2, _segments+24
	movw	$0, _segments+26
	movl	$0, _segments+28
	movl	$LC12, _segments+32
	movl	$2, _segments+36
	movw	$-1, _segments+40
	movw	$0, _segments+42
	movl	$0, _segments+44
	movl	$3, _nsegments
	movl	8(%ebp), %eax
	movl	%eax, _ofile
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _seg
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _seg+4
	movl	$0, _seg+8
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _header
	call	_seg_alloc
	movl	%eax, %ebx
	call	_seg_alloc
	movl	%eax, %esi
	call	_seg_alloc
	testl	%ebx, %ebx
	jne	L3
	cmpl	$2, %esi
	jne	L3
	cmpl	$4, %eax
	je	L2
L3:
	movl	$3, (%esp)
	movl	$LC13, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	%esi, 12(%esp)
	movl	%eax, 16(%esp)
	call	*_error
L2:
	movl	$0, _bsslength
	movl	$0, _headerlength
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC14:
	.ascii "value following comma must be numeric\0"
	.align 32
LC15:
	.ascii "unrecognised RDF segment type (%s)\0"
	.align 32
LC16:
	.ascii "segment attributes specified on redeclaration of segment\0"
	.align 32
LC17:
	.ascii "new segment declared without type code\0"
	.align 32
LC18:
	.ascii "reached compiled-in maximum segment limit (%d)\0"
	.align 32
LC19:
	.ascii "seg_alloc() returned odd number\0"
	.align 2
	.def	_rdf2_section_names;	.scl	3;	.type	32;	.endef
_rdf2_section_names:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	$-1, %edi
	movl	$0, -20(%ebp)
	testl	%esi, %esi
	jne	L5
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	movl	$0, %eax
	jmp	L4
L42:
	movl	-16(%ebp), %eax
	movl	_segmenttypenumbers(,%eax,4), %edi
	jmp	L21
L5:
	movl	%esi, %ebx
	jmp	L6
L10:
	incl	%ebx
L6:
	cmpb	$0, (%ebx)
	je	L17
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L10
	cmpb	$0, (%ebx)
	je	L17
L16:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L17
	movl	$80, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L16
	cmpb	$0, (%ebx)
	je	L17
	movl	%ebx, (%esp)
	movl	$44, 4(%esp)
	call	_strchr
	testl	%eax, %eax
	je	L18
	movb	$0, (%eax)
	incl	%eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -20(%ebp)
	cmpl	$0, -16(%ebp)
	je	L18
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	call	*_error
	movl	$0, -20(%ebp)
L18:
	movl	$0, -16(%ebp)
	cmpl	$8, -16(%ebp)
	jg	L21
L25:
	movl	%ebx, (%esp)
	movl	-16(%ebp), %eax
	movl	_segmenttypes(,%eax,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L42
	incl	-16(%ebp)
	cmpl	$8, -16(%ebp)
	jle	L25
L21:
	cmpl	$-1, %edi
	jne	L17
	movl	%ebx, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, %edi
	cmpl	$0, -16(%ebp)
	je	L17
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_error
	movl	$3, %edi
L17:
	movl	$0, -16(%ebp)
	movl	$0, %eax
	movl	%eax, %edx
	cmpl	_nsegments, %eax
	jge	L41
L35:
	movl	%esi, (%esp)
	movl	%edx, %eax
	sall	$4, %eax
	movl	_segments(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L30
	cmpl	$-1, %edi
	jne	L34
	cmpl	$0, -20(%ebp)
	je	L33
L34:
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	call	*_error
L33:
	movl	-16(%ebp), %eax
	sall	$4, %eax
	movl	_segments+4(%eax), %eax
	addl	%eax, %eax
	jmp	L4
L30:
	incl	-16(%ebp)
	movl	-16(%ebp), %edx
	cmpl	_nsegments, %edx
	jl	L35
L41:
	cmpl	$-1, %edi
	jne	L36
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_error
	movl	$3, %edi
L36:
	cmpl	$64, _nsegments
	jne	L37
	movl	$2, (%esp)
	movl	$LC18, 4(%esp)
	movl	$64, 8(%esp)
	call	*_error
	movl	$-1, %eax
	jmp	L4
L37:
	movl	_nsegments, %ebx
	sall	$4, %ebx
	movl	%esi, (%esp)
	call	_nasm_strdup
	movl	%eax, _segments(%ebx)
	call	_seg_alloc
	movl	%eax, -16(%ebp)
	testb	$1, -16(%ebp)
	je	L38
	movl	$3, (%esp)
	movl	$LC19, 4(%esp)
	call	*_error
L38:
	movl	_nsegments, %ebx
	movl	%ebx, %edx
	sall	$4, %edx
	movl	-16(%ebp), %eax
	sarl	%eax
	movl	%eax, _segments+4(%edx)
	movw	%di, _segments+8(%edx)
	movl	-20(%ebp), %eax
	movw	%ax, _segments+10(%edx)
	movl	$0, _segments+12(%edx)
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, _seg(,%ebx,4)
	movl	-16(%ebp), %eax
L4:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_write_reloc_rec;	.scl	3;	.type	32;	.endef
_write_reloc_rec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	cmpw	$-1, 10(%esi)
	je	L44
	movzwl	10(%esi), %eax
	andl	$1, %eax
	testw	%ax, %ax
	je	L44
	movb	$6, (%esi)
L44:
	movzwl	10(%esi), %eax
	shrl	%eax
	movw	%ax, 10(%esi)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	2(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	-12(%ebp), %edx
	movzbl	4(%esi), %eax
	movl	%edx, %ebx
	movb	%al, -12(%ebp)
	incl	%edx
	movl	4(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	6(%esi),%eax
	movb	%al, (%edx)
	movsbl	7(%esi),%eax
	movb	%al, 1(%edx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$4, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	8(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movzbl	10(%esi), %eax
	movb	%al, -12(%ebp)
	movzbl	11(%esi), %eax
	movb	%al, 1(%ebx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$2, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%esi), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_write_export_rec;	.scl	3;	.type	32;	.endef
_write_export_rec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	shrb	3(%ebx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	2(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	3(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	-12(%ebp), %edx
	movzbl	4(%ebx), %eax
	movl	%edx, %ecx
	movb	%al, -12(%ebp)
	incl	%edx
	movl	4(%ebx), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	6(%ebx),%eax
	movb	%al, (%edx)
	movsbl	7(%ebx),%eax
	movb	%al, 1(%edx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	movl	$4, 8(%esp)
	call	_saa_wbytes
	leal	8(%ebx), %esi
	movl	%esi, (%esp)
	call	_strlen
	incl	%eax
	movl	_header, %edx
	movl	%edx, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%ebx), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_write_import_rec;	.scl	3;	.type	32;	.endef
_write_import_rec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	movzwl	2(%ebx), %eax
	shrl	%eax
	movw	%ax, 2(%ebx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	-12(%ebp), %edx
	movzbl	2(%ebx), %eax
	movb	%al, -12(%ebp)
	movzbl	3(%ebx), %eax
	movb	%al, 1(%edx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	movl	$2, 8(%esp)
	call	_saa_wbytes
	leal	4(%ebx), %esi
	movl	%esi, (%esp)
	call	_strlen
	incl	%eax
	movl	_header, %edx
	movl	%edx, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%ebx), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_write_bss_rec;	.scl	3;	.type	32;	.endef
_write_bss_rec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	-8(%ebp), %edx
	movzbl	4(%ebx), %eax
	movl	%edx, %ecx
	movb	%al, -8(%ebp)
	incl	%edx
	movl	4(%ebx), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	6(%ebx),%eax
	movb	%al, (%edx)
	movsbl	7(%ebx),%eax
	movb	%al, 1(%edx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	movl	$4, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%ebx), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_write_common_rec;	.scl	3;	.type	32;	.endef
_write_common_rec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	movzwl	2(%esi), %eax
	shrl	%eax
	movw	%ax, 2(%esi)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	-12(%ebp), %edx
	movzbl	2(%esi), %eax
	movl	%edx, %ebx
	movb	%al, -12(%ebp)
	movzbl	3(%esi), %eax
	movb	%al, 1(%edx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	movl	$2, 8(%esp)
	call	_saa_wbytes
	movzbl	4(%esi), %eax
	movb	%al, -12(%ebp)
	movl	4(%esi), %eax
	sarl	$8, %eax
	movb	%al, 1(%ebx)
	movswl	6(%esi),%eax
	movb	%al, 2(%ebx)
	movsbl	7(%esi),%eax
	movb	%al, 3(%ebx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$4, 8(%esp)
	call	_saa_wbytes
	movzbl	8(%esi), %eax
	movb	%al, -12(%ebp)
	movzbl	9(%esi), %eax
	movb	%al, 1(%ebx)
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$2, 8(%esp)
	call	_saa_wbytes
	leal	10(%esi), %ebx
	movl	%ebx, (%esp)
	call	_strlen
	incl	%eax
	movl	_header, %edx
	movl	%edx, (%esp)
	movl	%ebx, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%esi), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_write_dllmod_rec;	.scl	3;	.type	32;	.endef
_write_dllmod_rec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	movl	_header, %eax
	movl	%eax, (%esp)
	leal	1(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_saa_wbytes
	leal	2(%ebx), %esi
	movl	%esi, (%esp)
	call	_strlen
	incl	%eax
	movl	_header, %edx
	movl	%edx, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	call	_saa_wbytes
	movzbl	1(%ebx), %eax
	addl	_headerlength, %eax
	addl	$2, %eax
	movl	%eax, _headerlength
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.data
	.align 4
_farsym.0:
	.long	0
.lcomm _i.1,16
	.text
	.align 32
LC20:
	.ascii "alignment constraint `%s' is not a valid number\0"
	.align 32
LC21:
	.ascii "alignment constraint `%s' is not a power of two\0"
LC22:
	.ascii "export\0"
LC23:
	.ascii "far\0"
LC24:
	.ascii "near\0"
LC25:
	.ascii "proc\0"
LC26:
	.ascii "function\0"
LC27:
	.ascii "object\0"
LC28:
	.ascii "unrecognised symbol type `%s'\0"
	.align 32
LC29:
	.ascii "unrecognised special symbol `%s'\0"
	.align 2
	.def	_rdf2_deflabel;	.scl	3;	.type	32;	.endef
_rdf2_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$188, %esp
	movl	20(%ebp), %edi
	movl	24(%ebp), %esi
	movb	$0, -173(%ebp)
	cmpl	$2, %edi
	jne	L83
	movb	$10, -168(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -164(%ebp)
	movl	12(%ebp), %eax
	movw	%ax, -166(%ebp)
	leal	-158(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$32, 8(%esp)
	call	_strncpy
	movb	$0, -126(%ebp)
	movl	%ebx, (%esp)
	call	_strlen
	addb	$9, %al
	movb	%al, -167(%ebp)
	movw	$0, -160(%ebp)
	testl	%esi, %esi
	je	L84
	movl	%esi, (%esp)
	leal	-172(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movw	%ax, -160(%ebp)
	cmpl	$0, -172(%ebp)
	je	L85
	movl	$1, (%esp)
	movl	$LC20, 4(%esp)
	jmp	L126
L85:
	movzwl	-160(%ebp), %eax
	leal	-1(%eax), %edx
	orl	%eax, %edx
	leal	-1(%eax,%eax), %eax
	cmpl	%eax, %edx
	je	L84
	movl	$1, (%esp)
	movl	$LC21, 4(%esp)
L126:
	movl	%esi, 8(%esp)
	call	*_error
L84:
	leal	-168(%ebp), %eax
	movl	%eax, (%esp)
	call	_write_common_rec
L83:
	cmpl	$1, %edi
	jne	L82
	testl	%esi, %esi
	je	L89
	cmpb	$32, (%esi)
	je	L93
	cmpb	$9, (%esi)
	jne	L123
L93:
	incl	%esi
	cmpb	$32, (%esi)
	je	L93
	cmpb	$9, (%esi)
	je	L93
L123:
	movl	%esi, (%esp)
	movl	$LC22, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L94
	addl	$6, %esi
	orb	$4, -173(%ebp)
L94:
	cmpb	$0, (%esi)
	je	L89
	jmp	L96
L99:
	incl	%esi
L96:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L99
	movl	%esi, (%esp)
	movl	$LC23, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L100
	movl	$1, _farsym.0
	jmp	L89
L100:
	movl	%esi, (%esp)
	movl	$LC24, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L102
	movl	$0, _farsym.0
	jmp	L89
L102:
	movl	%esi, (%esp)
	movl	$LC25, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L105
	movl	%esi, (%esp)
	movl	$LC26, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L104
L105:
	orb	$2, -173(%ebp)
	jmp	L89
L104:
	movl	%esi, (%esp)
	movl	$LC4, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L108
	movl	%esi, (%esp)
	movl	$LC27, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L107
L108:
	orb	$1, -173(%ebp)
	jmp	L89
L107:
	movl	$1, (%esp)
	movl	$LC28, 4(%esp)
	movl	%esi, 8(%esp)
	call	*_error
L89:
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L110
	cmpb	$46, 1(%eax)
	jne	L110
	cmpb	$64, 2(%eax)
	je	L110
	movl	$1, (%esp)
	movl	$LC29, 4(%esp)
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L82
L110:
	movl	$0, _i.1
	cmpl	$0, _nsegments
	jle	L112
	movl	12(%ebp), %ebx
	sarl	%ebx
	movl	$0, %edx
	movl	_nsegments, %ecx
L116:
	movl	%edx, %eax
	sall	$4, %eax
	cmpl	%ebx, _segments+4(%eax)
	je	L125
	leal	1(%edx), %eax
	movl	%eax, %edx
	cmpl	%ecx, %eax
	jl	L116
L125:
	movl	%edx, _i.1
L112:
	movl	_i.1, %eax
	cmpl	_nsegments, %eax
	jl	L117
	cmpl	$0, _farsym.0
	je	L118
	movb	$7, -120(%ebp)
	jmp	L119
L118:
	movb	$2, -120(%ebp)
L119:
	movl	12(%ebp), %eax
	movw	%ax, -118(%ebp)
	leal	-120(%ebp), %esi
	leal	-116(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$32, 8(%esp)
	call	_strncpy
	movb	$0, -84(%ebp)
	movl	%ebx, (%esp)
	call	_strlen
	addb	$3, %al
	movb	%al, -119(%ebp)
	movl	%esi, (%esp)
	call	_write_import_rec
	jmp	L82
L117:
	testl	%edi, %edi
	je	L82
	movb	$3, -72(%ebp)
	movzbl	-173(%ebp), %eax
	movb	%al, -70(%ebp)
	movzbl	12(%ebp), %eax
	movb	%al, -69(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -68(%ebp)
	leal	-72(%ebp), %esi
	leal	-64(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$32, 8(%esp)
	call	_strncpy
	movb	$0, -32(%ebp)
	movl	%ebx, (%esp)
	call	_strlen
	addb	$7, %al
	movb	%al, -71(%ebp)
	movl	%esi, (%esp)
	call	_write_export_rec
L82:
	addl	$188, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC30:
	.ascii "can't find segment %d\0"
	.align 2
	.def	_membufwrite;	.scl	3;	.type	32;	.endef
_membufwrite:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	movl	$0, %ebx
	cmpl	_nsegments, %ebx
	jge	L129
	movl	_nsegments, %edx
L133:
	movl	%ebx, %eax
	sall	$4, %eax
	cmpl	%ecx, _segments+4(%eax)
	je	L129
	incl	%ebx
	cmpl	%edx, %ebx
	jl	L133
L129:
	cmpl	_nsegments, %ebx
	jne	L134
	movl	$3, (%esp)
	movl	$LC30, 4(%esp)
	movl	%ecx, 8(%esp)
	call	*_error
L134:
	testl	%edi, %edi
	jns	L135
	leal	-16(%ebp), %edx
	cmpl	$-2, %edi
	jne	L136
	movzbl	(%esi), %eax
	movb	%al, -16(%ebp)
	movsbl	1(%esi),%eax
	jmp	L147
L136:
	movzbl	(%esi), %eax
	movb	%al, (%edx)
	incl	%edx
	movl	(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	2(%esi),%eax
	movb	%al, (%edx)
	movsbl	3(%esi),%eax
L147:
	movb	%al, 1(%edx)
	leal	-16(%ebp), %esi
	negl	%edi
L135:
	movl	%ebx, %eax
	sall	$4, %eax
	addl	%edi, _segments+12(%eax)
	movl	_seg(,%ebx,4), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	call	_saa_wbytes
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_getsegmentlength;	.scl	3;	.type	32;	.endef
_getsegmentlength:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ecx
	movl	$0, %ebx
	cmpl	_nsegments, %ebx
	jge	L150
	movl	_nsegments, %edx
L154:
	movl	%ebx, %eax
	sall	$4, %eax
	cmpl	%ecx, _segments+4(%eax)
	je	L150
	incl	%ebx
	cmpl	%edx, %ebx
	jl	L154
L150:
	cmpl	_nsegments, %ebx
	jne	L155
	movl	$3, (%esp)
	movl	$LC30, 4(%esp)
	movl	%ecx, 8(%esp)
	call	*_error
L155:
	movl	%ebx, %eax
	sall	$4, %eax
	movl	_segments+12(%eax), %eax
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 32
LC31:
	.ascii "attempt to assemble code in ABSOLUTE space\0"
	.align 32
LC32:
	.ascii "specified segment not supported by rdf output format\0"
	.align 32
LC33:
	.ascii "WRT not supported by rdf output format\0"
	.align 32
LC34:
	.ascii "BSS segments may not be initialised\0"
	.align 32
LC35:
	.ascii "OUT_RAWDATA with other than NO_SEG\0"
LC36:
	.ascii "intra-segment OUT_REL2ADR\0"
LC37:
	.ascii "intra-segment OUT_REL4ADR\0"
	.align 32
LC38:
	.ascii "erm... 4 byte segment base ref?\0"
	.align 2
	.def	_rdf2_out;	.scl	3;	.type	32;	.endef
_rdf2_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	%ebx, %edi
	andl	$268435455, %edi
	cmpl	$-1, %esi
	jne	L158
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	je	L157
	movl	$1, (%esp)
	movl	$LC31, 4(%esp)
	jmp	L210
L158:
	sarl	%esi
	movl	$0, %edx
	cmpl	_nsegments, %edx
	jge	L205
L165:
	movl	%edx, %eax
	sall	$4, %eax
	cmpl	%esi, _segments+4(%eax)
	je	L161
	incl	%edx
	cmpl	_nsegments, %edx
	jl	L165
	jmp	L205
L161:
	cmpl	_nsegments, %edx
	jl	L166
L205:
	movl	$1, (%esp)
	movl	$LC32, 4(%esp)
L210:
	call	*_error
	jmp	L157
L166:
	cmpl	$-1, 24(%ebp)
	je	L167
	movl	$1, (%esp)
	movl	$LC33, 4(%esp)
	call	*_error
L167:
	andl	$-268435456, %ebx
	cmpl	$2, %esi
	jne	L168
	cmpl	$1073741824, %ebx
	je	L206
	movl	$1, (%esp)
	movl	$LC34, 4(%esp)
	call	*_error
	cmpl	$536870912, %ebx
	setne	%al
	movzbl	%al, %edi
	leal	2(%edi,%edi), %edi
	movl	$1073741824, %ebx
L168:
	cmpl	$1073741824, %ebx
	jne	L171
L206:
	cmpl	$2, %esi
	jne	L172
	addl	%edi, _bsslength
	jmp	L157
L172:
	decl	%edi
	cmpl	$-1, %edi
	je	L157
	leal	-44(%ebp), %ebx
L177:
	movl	%esi, (%esp)
	movl	%ebx, 4(%esp)
	movl	$1, 8(%esp)
	call	_membufwrite
	decl	%edi
	cmpl	$-1, %edi
	je	L157
	jmp	L177
L171:
	testl	%ebx, %ebx
	jne	L179
	cmpl	$-1, 20(%ebp)
	je	L180
	movl	$3, (%esp)
	movl	$LC35, 4(%esp)
	call	*_error
L180:
	movl	%esi, (%esp)
	movl	12(%ebp), %eax
	jmp	L211
L179:
	cmpl	$268435456, %ebx
	jne	L182
	cmpl	$-1, 20(%ebp)
	je	L183
	movb	$1, -40(%ebp)
	movb	$8, -39(%ebp)
	movl	%esi, %edx
	movb	%dl, -38(%ebp)
	movl	%esi, (%esp)
	call	_getsegmentlength
	movl	%eax, -36(%ebp)
	movl	%edi, %ecx
	movb	%cl, -32(%ebp)
	movl	20(%ebp), %eax
	movw	%ax, -30(%ebp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_write_reloc_rec
L183:
	leal	-44(%ebp), %edx
	cmpl	$2, %edi
	jne	L184
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	movb	%al, -44(%ebp)
	movl	(%ecx), %eax
	sarl	$8, %eax
	jmp	L207
L184:
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	movb	%al, (%edx)
	incl	%edx
	movl	(%ecx), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	2(%ecx),%eax
	movb	%al, (%edx)
	movsbl	3(%ecx),%eax
L207:
	movb	%al, 1(%edx)
	movl	%esi, (%esp)
	leal	-44(%ebp), %eax
L211:
	movl	%eax, 4(%esp)
	movl	%edi, 8(%esp)
	jmp	L209
L182:
	cmpl	$536870912, %ebx
	jne	L195
	cmpl	%esi, 20(%ebp)
	jne	L196
	movl	$3, (%esp)
	movl	$LC36, 4(%esp)
	call	*_error
L196:
	movb	$8, -39(%ebp)
	movl	%esi, (%esp)
	call	_getsegmentlength
	movl	%eax, -36(%ebp)
	movb	$2, -32(%ebp)
	movl	20(%ebp), %eax
	movw	%ax, -30(%ebp)
	cmpl	$-1, 20(%ebp)
	je	L197
	testl	$1, 20(%ebp)
	je	L197
	movb	$6, -40(%ebp)
	movl	%esi, %edx
	movb	%dl, -38(%ebp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_write_reloc_rec
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	jmp	L208
L197:
	movb	$1, -40(%ebp)
	movl	%esi, %eax
	addb	$64, %al
	movb	%al, -38(%ebp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_write_reloc_rec
	movl	%edi, %edx
	addl	-36(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	subl	%edx, %eax
L208:
	movl	%eax, -36(%ebp)
	movl	%esi, (%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$-2, 8(%esp)
	jmp	L209
L195:
	cmpl	$805306368, %ebx
	jne	L157
	cmpl	%esi, 20(%ebp)
	jne	L201
	movl	$3, (%esp)
	movl	$LC37, 4(%esp)
	call	*_error
L201:
	cmpl	$-1, 20(%ebp)
	je	L202
	testl	$1, 20(%ebp)
	je	L202
	movl	$3, (%esp)
	movl	$LC38, 4(%esp)
	call	*_error
L202:
	movb	$1, -40(%ebp)
	movl	%esi, %eax
	addb	$64, %al
	movb	%al, -38(%ebp)
	movl	%esi, (%esp)
	call	_getsegmentlength
	movl	%eax, -36(%ebp)
	movb	$4, -32(%ebp)
	movl	20(%ebp), %eax
	movw	%ax, -30(%ebp)
	movb	$8, -39(%ebp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_write_reloc_rec
	movl	%edi, %edx
	addl	-36(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	(%ecx), %eax
	subl	%edx, %eax
	movl	%eax, -36(%ebp)
	movl	%esi, (%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$-4, 8(%esp)
L209:
	call	_membufwrite
L157:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_rdf2_cleanup;	.scl	3;	.type	32;	.endef
_rdf2_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	_RDOFF2Id, %eax
	movl	%eax, (%esp)
	movl	$6, 4(%esp)
	movl	$1, 8(%esp)
	movl	_ofile, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	cmpl	$0, _bsslength
	je	L213
	andl	$-256, -24(%ebp)
	orl	$5, -24(%ebp)
	leal	-24(%ebp), %eax
	movl	_bsslength, %edx
	movl	%edx, 4(%eax)
	movb	$4, 1(%eax)
	movl	%eax, (%esp)
	call	_write_bss_rec
L213:
	movl	_headerlength, %edx
	addl	$4, %edx
	movl	$0, %esi
	cmpl	_nsegments, %esi
	jge	L227
	movl	_nsegments, %ecx
L219:
	cmpl	$2, %esi
	je	L216
	movl	%esi, %eax
	sall	$4, %eax
	addl	_segments+12(%eax), %edx
	leal	10(%edx), %edx
L216:
	incl	%esi
	cmpl	%ecx, %esi
	jl	L219
L227:
	addl	$10, %edx
	movl	%edx, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_headerlength, %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	_header, %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	_header, %eax
	movl	%eax, (%esp)
	call	_saa_free
	movl	$0, %esi
	cmpl	_nsegments, %esi
	jge	L229
	movl	$_seg, %edi
L225:
	cmpl	$2, %esi
	je	L222
	movl	%esi, %ebx
	sall	$4, %ebx
	movzwl	_segments+8(%ebx), %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_segments+4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movzwl	_segments+10(%ebx), %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_segments+12(%ebx), %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	(%edi,%esi,4), %eax
	movl	%eax, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
	movl	(%edi,%esi,4), %eax
	movl	%eax, (%esp)
	call	_saa_free
L222:
	incl	%esi
	cmpl	_nsegments, %esi
	jl	L225
L229:
	movl	$0, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwritelong
	movl	$0, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	movl	_ofile, %eax
	movl	%eax, (%esp)
	call	_fclose
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_rdf2_segbase;	.scl	3;	.type	32;	.endef
_rdf2_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
LC39:
	.ascii "library\0"
LC40:
	.ascii "module\0"
	.align 2
	.def	_rdf2_directive;	.scl	3;	.type	32;	.endef
_rdf2_directive:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edi
	movl	16(%ebp), %esi
	movl	%ebx, (%esp)
	movl	$LC39, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L232
	cmpl	$1, %esi
	jne	L235
	movb	$4, -168(%ebp)
	jmp	L236
L232:
	movl	%ebx, (%esp)
	movl	$LC40, 4(%esp)
	call	_strcmp
	movl	$0, %edx
	testl	%eax, %eax
	jne	L231
	cmpl	$1, %esi
	jne	L235
	movb	$8, -168(%ebp)
L236:
	movl	%edi, (%esp)
	call	_strlen
	incb	%al
	movb	%al, -167(%ebp)
	leal	-168(%ebp), %ebx
	leal	-166(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	call	_write_dllmod_rec
L235:
	movl	$1, %edx
L231:
	movl	%edx, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC41:
	.ascii ".rdf\0"
	.align 2
	.def	_rdf2_filename;	.scl	3;	.type	32;	.endef
_rdf2_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC41, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC42:
	.ascii "%define __SECT__ [section .text]\0"
LC43:
	.ascii "%imacro library 1+.nolist\0"
LC44:
	.ascii "[library %1]\0"
LC45:
	.ascii "%endmacro\0"
LC46:
	.ascii "%imacro module 1+.nolist\0"
LC47:
	.ascii "[module %1]\0"
LC48:
	.ascii "%macro __NASM_CDecl__ 1\0"
	.data
	.align 32
_rdf2_stdmac:
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC45
	.long	LC48
	.long	LC45
	.long	0
	.text
	.align 2
	.def	_rdf2_set_info;	.scl	3;	.type	32;	.endef
_rdf2_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
.globl _of_rdf2
	.align 32
LC49:
	.ascii "Relocatable Dynamic Object File Format v2.0\0"
LC50:
	.ascii "rdf\0"
	.data
	.align 32
_of_rdf2:
	.long	LC49
	.long	LC50
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_rdf2_stdmac
	.long	_rdf2_init
	.long	_rdf2_set_info
	.long	_rdf2_out
	.long	_rdf2_deflabel
	.long	_rdf2_section_names
	.long	_rdf2_segbase
	.long	_rdf2_directive
	.long	_rdf2_filename
	.long	_rdf2_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _seg,256
.lcomm _header,16
.lcomm _ofile,16
.lcomm _error,16
.lcomm _segments,1024
.lcomm _nsegments,16
.lcomm _bsslength,16
.lcomm _headerlength,16
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_strchr;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
