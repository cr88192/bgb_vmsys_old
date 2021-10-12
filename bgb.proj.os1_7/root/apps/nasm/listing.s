	.file	"listing.c"
	.data
_xdigit:
	.ascii "0123456789ABCDEF\0"
	.text
LC0:
	.ascii "%6ld \0"
LC1:
	.ascii "%08lX %-*s\0"
LC2:
	.ascii "%*s\0"
LC3:
	.ascii "\0"
LC4:
	.ascii "%s<%d>\0"
LC5:
	.ascii " \0"
LC6:
	.ascii "    \0"
LC7:
	.ascii " %s\0"
	.align 2
	.def	_list_emit;	.scl	3;	.type	32;	.endef
_list_emit:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, _listlinep
	jne	L2
	cmpb	$0, _listdata
	je	L1
L2:
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC0, 4(%esp)
	movl	_listlineno, %eax
	incl	%eax
	movl	%eax, _listlineno
	movl	%eax, 8(%esp)
	call	_fprintf
	cmpb	$0, _listdata
	je	L3
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC1, 4(%esp)
	movl	_listoffset, %eax
	movl	%eax, 8(%esp)
	movl	$19, 12(%esp)
	movl	$_listdata, 16(%esp)
	call	_fprintf
	jmp	L4
L3:
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC2, 4(%esp)
	movl	$28, 8(%esp)
	movl	$LC3, 12(%esp)
	call	_fprintf
L4:
	cmpl	$0, _listlevel_e
	je	L5
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC4, 4(%esp)
	cmpl	$9, _listlevel
	jg	L6
	movl	$LC5, %eax
	jmp	L7
L6:
	movl	$LC3, %eax
L7:
	movl	%eax, 8(%esp)
	movl	_listlevel_e, %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	jmp	L8
L5:
	cmpl	$0, _listlinep
	je	L10
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC6, 4(%esp)
	call	_fprintf
L8:
	cmpl	$0, _listlinep
	je	L10
	movl	_listfp, %eax
	movl	%eax, (%esp)
	movl	$LC7, 4(%esp)
	movl	$_listline, 8(%esp)
	call	_fprintf
L10:
	movl	$10, (%esp)
	movl	_listfp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	movl	$0, _listlinep
	movb	$0, _listdata
L1:
	movl	%ebp, %esp
	popl	%ebp
	ret
LC8:
	.ascii "w\0"
	.align 32
LC9:
	.ascii "unable to open listing file `%s'\0"
	.align 2
	.def	_list_init;	.scl	3;	.type	32;	.endef
_list_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC8, 4(%esp)
	call	_fopen
	movl	%eax, _listfp
	testl	%eax, %eax
	jne	L12
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*12(%ebp)
	jmp	L11
L12:
	movb	$0, _listline
	movl	$0, _listlineno
	movl	$1, _listp
	movl	$0, _listlevel
	movl	$0, _suppress
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, _mistack
	movl	$0, (%eax)
	movl	_mistack, %eax
	movl	$0, 4(%eax)
	movl	_mistack, %eax
	movl	$1, 8(%eax)
L11:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_list_cleanup;	.scl	3;	.type	32;	.endef
_list_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _listp
	je	L13
	cmpl	$0, _mistack
	je	L20
L18:
	movl	_mistack, %edx
	movl	(%edx), %eax
	movl	%eax, _mistack
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _mistack
	jne	L18
L20:
	call	_list_emit
	movl	_listfp, %eax
	movl	%eax, (%esp)
	call	_fclose
L13:
	movl	%ebp, %esp
	popl	%ebp
	ret
LC10:
	.ascii "-\0"
	.align 2
	.def	_list_out;	.scl	3;	.type	32;	.endef
_list_out:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	12(%ebp), %esi
	movl	$_listdata, (%esp)
	call	_strlen
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_strlen
	leal	(%eax,%ebx), %eax
	cmpl	$18, %eax
	jle	L22
	movl	$_listdata, (%esp)
	movl	$LC10, 4(%esp)
	call	_strcat
	call	_list_emit
L22:
	cmpb	$0, _listdata
	jne	L23
	movl	8(%ebp), %eax
	movl	%eax, _listoffset
L23:
	movl	$_listdata, (%esp)
	movl	%esi, 4(%esp)
	call	_strcat
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC11:
	.ascii "<res %08lX>\0"
	.align 2
	.def	_list_output;	.scl	3;	.type	32;	.endef
_list_output:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$120, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	12(%ebp), %eax
	movl	16(%ebp), %ebx
	cmpl	$0, _listp
	je	L24
	cmpl	$0, _suppress
	jne	L24
	cmpl	$0, _user_nolist
	jne	L24
	movl	%ebx, %esi
	andl	$268435455, %esi
	andl	$-268435456, %ebx
	jne	L27
	movl	%eax, %ebx
	decl	%esi
	cmpl	$-1, %esi
	je	L24
L31:
	movzbl	(%ebx), %edx
	movb	%dl, %al
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -40(%ebp)
	movl	%edx, %eax
	andl	$15, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -39(%ebp)
	movb	$0, -38(%ebp)
	movl	%edi, (%esp)
	incl	%edi
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_list_out
	incl	%ebx
	decl	%esi
	cmpl	$-1, %esi
	je	L24
	jmp	L31
L27:
	cmpl	$268435456, %ebx
	jne	L33
	movl	(%eax), %edx
	leal	-92(%ebp), %ebx
	cmpl	$4, %esi
	jne	L34
	movb	$91, -40(%ebp)
	movb	$93, -31(%ebp)
	movb	$0, -30(%ebp)
	movl	%ebx, %ecx
	movb	%dl, -92(%ebp)
	incl	%ebx
	movl	%edx, %eax
	shrl	$8, %eax
	movb	%al, (%ebx)
	incl	%ebx
	movl	%edx, %eax
	shrl	$16, %eax
	movb	%al, (%ebx)
	movl	%edx, %eax
	shrl	$24, %eax
	movb	%al, 1(%ebx)
	movzbl	-92(%ebp), %edx
	movb	%dl, %al
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -39(%ebp)
	movl	%edx, %eax
	andl	$15, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -38(%ebp)
	movzbl	1(%ecx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -37(%ebp)
	movzbl	1(%ecx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -36(%ebp)
	movzbl	2(%ecx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -35(%ebp)
	movzbl	2(%ecx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -34(%ebp)
	movzbl	3(%ecx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -33(%ebp)
	movzbl	3(%ecx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -32(%ebp)
	jmp	L61
L34:
	movb	$91, -40(%ebp)
	movb	$93, -35(%ebp)
	movb	$0, -34(%ebp)
	movb	%dl, (%ebx)
	movl	%edx, %eax
	shrl	$8, %eax
	movb	%al, 1(%ebx)
	movzbl	-92(%ebp), %edx
	movb	%dl, %al
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -39(%ebp)
	movl	%edx, %eax
	andl	$15, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -38(%ebp)
	leal	-92(%ebp), %edx
	movzbl	1(%edx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -37(%ebp)
	movzbl	1(%edx), %eax
	jmp	L63
L33:
	cmpl	$536870912, %ebx
	jne	L45
	movl	(%eax), %eax
	leal	-96(%ebp), %edx
	movb	$40, -40(%ebp)
	movb	$41, -35(%ebp)
	movb	$0, -34(%ebp)
	movl	%edx, %ecx
	movb	%al, -96(%ebp)
	shrl	$8, %eax
	movb	%al, 1(%edx)
	movzbl	-96(%ebp), %edx
	movb	%dl, %al
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -39(%ebp)
	movl	%edx, %eax
	andl	$15, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -38(%ebp)
	movzbl	1(%ecx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -37(%ebp)
	movzbl	1(%ecx), %eax
L63:
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -36(%ebp)
L61:
	movl	%edi, (%esp)
	leal	-40(%ebp), %eax
	jmp	L62
L45:
	cmpl	$805306368, %ebx
	jne	L50
	movl	(%eax), %ecx
	leal	-100(%ebp), %eax
	movb	$40, -56(%ebp)
	movb	$41, -47(%ebp)
	movb	$0, -46(%ebp)
	movl	%eax, %ebx
	movb	%cl, -100(%ebp)
	incl	%eax
	movl	%ecx, %edx
	shrl	$8, %edx
	movb	%dl, (%eax)
	incl	%eax
	movl	%ecx, %edx
	shrl	$16, %edx
	movb	%dl, (%eax)
	shrl	$24, %ecx
	movb	%cl, 1(%eax)
	movzbl	-100(%ebp), %edx
	movb	%dl, %al
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -55(%ebp)
	movl	%edx, %eax
	andl	$15, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -54(%ebp)
	movzbl	1(%ebx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -53(%ebp)
	movzbl	1(%ebx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -52(%ebp)
	movzbl	2(%ebx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -51(%ebp)
	movzbl	2(%ebx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -50(%ebp)
	movzbl	3(%ebx), %eax
	shrb	$4, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -49(%ebp)
	movzbl	3(%ebx), %eax
	andb	$15, %al
	movzbl	%al, %eax
	movzbl	_xdigit(%eax), %eax
	movb	%al, -48(%ebp)
	movl	%edi, (%esp)
	leal	-56(%ebp), %eax
L62:
	movl	%eax, 4(%esp)
	jmp	L59
L50:
	cmpl	$1073741824, %ebx
	jne	L24
	leal	-88(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC11, 4(%esp)
	movl	%esi, 8(%esp)
	call	_sprintf
	movl	%edi, (%esp)
	movl	%ebx, 4(%esp)
L59:
	call	_list_out
L24:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_list_line;	.scl	3;	.type	32;	.endef
_list_line:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, _listp
	je	L64
	cmpl	$0, _user_nolist
	je	L66
	incl	_listlineno
	jmp	L64
L66:
	cmpl	$0, _mistack
	je	L67
	movl	_mistack, %edx
	cmpl	$0, 8(%edx)
	je	L67
	cmpl	$1, 8(%ebp)
	je	L64
	movl	(%edx), %eax
	movl	%eax, _mistack
	movl	%edx, (%esp)
	call	_nasm_free
L67:
	call	_list_emit
	movl	$1, _listlinep
	movl	$_listline, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$215, 8(%esp)
	call	_strncpy
	movb	$0, _listline+215
	movl	_listlevel, %eax
	movl	%eax, _listlevel_e
L64:
	movl	%ebp, %esp
	popl	%ebp
	ret
LC12:
	.ascii "<incbin>\0"
LC13:
	.ascii "<rept>\0"
	.align 2
	.def	_list_uplevel;	.scl	3;	.type	32;	.endef
_list_uplevel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %edx
	cmpl	$0, _listp
	je	L70
	leal	-4(%edx), %eax
	cmpl	$1, %eax
	ja	L72
	cmpl	$4, %edx
	jne	L73
	movl	_suppress, %eax
	orl	$1, %eax
	jmp	L74
L73:
	movl	_suppress, %eax
	orl	$2, %eax
L74:
	movl	%eax, _suppress
	movl	_listoffset, %eax
	movl	%eax, (%esp)
	movl	$LC12, %eax
	cmpl	$4, %edx
	je	L76
	movl	$LC13, %eax
L76:
	movl	%eax, 4(%esp)
	call	_list_out
	jmp	L70
L72:
	incl	_listlevel
	cmpl	$0, _mistack
	je	L77
	movl	_mistack, %eax
	cmpl	$0, 8(%eax)
	je	L77
	cmpl	$3, %edx
	jne	L77
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_mistack, %edx
	movl	%edx, (%eax)
	movl	_listlevel, %edx
	movl	%edx, 4(%eax)
	movl	$0, 8(%eax)
	jmp	L80
L77:
	cmpl	$2, %edx
	jne	L70
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_mistack, %edx
	movl	%edx, (%eax)
	movl	_listlevel, %edx
	movl	%edx, 4(%eax)
	movl	$1, 8(%eax)
L80:
	movl	%eax, _mistack
L70:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_list_downlevel;	.scl	3;	.type	32;	.endef
_list_downlevel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %edx
	cmpl	$0, _listp
	je	L81
	leal	-4(%edx), %eax
	cmpl	$1, %eax
	ja	L83
	cmpl	$4, %edx
	jne	L84
	movl	_suppress, %eax
	andl	$-2, %eax
	jmp	L85
L84:
	movl	_suppress, %eax
	andl	$-3, %eax
L85:
	movl	%eax, _suppress
	jmp	L81
L83:
	decl	_listlevel
	cmpl	$0, _mistack
	je	L81
	movl	_mistack, %eax
	movl	%eax, %edx
	movl	4(%eax), %eax
	cmpl	_listlevel, %eax
	jle	L81
L90:
	movl	(%edx), %eax
	movl	%eax, _mistack
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _mistack
	je	L81
	movl	_mistack, %edx
	movl	4(%edx), %eax
	cmpl	_listlevel, %eax
	jg	L90
L81:
	movl	%ebp, %esp
	popl	%ebp
	ret
.globl _nasmlist
	.data
	.align 4
_nasmlist:
	.long	_list_init
	.long	_list_cleanup
	.long	_list_output
	.long	_list_line
	.long	_list_uplevel
	.long	_list_downlevel
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _mistack,16
.lcomm _listline,224
.lcomm _listlinep,16
.lcomm _listdata,80
.lcomm _listoffset,16
.lcomm _listlineno,16
.lcomm _listp,16
.lcomm _suppress,16
.lcomm _listlevel,16
.lcomm _listlevel_e,16
.lcomm _listfp,16
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_strcat;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
