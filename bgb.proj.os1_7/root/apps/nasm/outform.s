	.file	"outform.c"
.globl _drivers
	.data
	.align 32
_drivers:
	.long	_of_bin
	.long	_of_aout
	.long	_of_aoutb
	.long	_of_coff
	.long	_of_elf
	.long	_of_as86
	.long	_of_obj
	.long	_of_win32
	.long	_of_rdf2
	.long	_of_ieee
	.long	0
	.align 4
_ndrivers:
	.long	0
	.text
	.align 2
.globl _ofmt_find
	.def	_ofmt_find;	.scl	2;	.type	32;	.endef
_ofmt_find:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	$0, %ebx
	cmpl	_ndrivers, %ebx
	jge	L9
	movl	$_drivers, %esi
L7:
	movl	%edi, (%esp)
	movl	(%esi,%ebx,4), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L4
	movl	(%esi,%ebx,4), %eax
	jmp	L1
L4:
	incl	%ebx
	cmpl	_ndrivers, %ebx
	jl	L7
L9:
	movl	$0, %eax
L1:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _dfmt_find
	.def	_dfmt_find;	.scl	2;	.type	32;	.endef
_dfmt_find:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	12(%ebp), %esi
	movl	8(%ebp), %eax
	movl	12(%eax), %ebx
	cmpl	$0, (%ebx)
	je	L17
L15:
	movl	%esi, (%esp)
	movl	(%ebx), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L14
	movl	(%ebx), %eax
	jmp	L10
L14:
	addl	$4, %ebx
	cmpl	$0, (%ebx)
	jne	L15
L17:
	movl	$0, %eax
L10:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
LC0:
	.ascii "  %c %-10s%s\12\0"
	.align 2
.globl _ofmt_list
	.def	_ofmt_list;	.scl	2;	.type	32;	.endef
_ofmt_list:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	$0, %ebx
	cmpl	_ndrivers, %ebx
	jge	L27
L25:
	movl	%esi, (%esp)
	movl	$LC0, 4(%esp)
	cmpl	%edi, _drivers(,%ebx,4)
	jne	L23
	movl	$42, %eax
	jmp	L24
L23:
	movl	$32, %eax
L24:
	movl	%eax, 8(%esp)
	movl	_drivers(,%ebx,4), %eax
	movl	4(%eax), %edx
	movl	%edx, 12(%esp)
	movl	(%eax), %eax
	movl	%eax, 16(%esp)
	call	_fprintf
	incl	%ebx
	cmpl	_ndrivers, %ebx
	jl	L25
L27:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _dfmt_list
	.def	_dfmt_list;	.scl	2;	.type	32;	.endef
_dfmt_list:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	12(%esi), %ebx
	cmpl	$0, (%ebx)
	je	L36
L34:
	movl	%edi, (%esp)
	movl	$LC0, 4(%esp)
	movl	(%ebx), %eax
	cmpl	16(%esi), %eax
	jne	L32
	movl	$42, %eax
	jmp	L33
L32:
	movl	$32, %eax
L33:
	movl	%eax, 8(%esp)
	movl	(%ebx), %eax
	movl	4(%eax), %eax
	movl	%eax, 12(%esp)
	movl	(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, 16(%esp)
	call	_fprintf
	addl	$4, %ebx
	cmpl	$0, (%ebx)
	jne	L34
L36:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC1:
	.ascii "No output drivers given at compile time\0"
	.align 2
.globl _ofmt_register
	.def	_ofmt_register;	.scl	2;	.type	32;	.endef
_ofmt_register:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, _ndrivers
	cmpl	$0, _drivers
	je	L45
	movl	$_drivers, %edx
	movl	$0, %eax
L42:
	incl	%eax
	cmpl	$0, (%edx,%eax,4)
	jne	L42
	movl	%eax, _ndrivers
L45:
	cmpl	$0, _ndrivers
	jne	L43
	movl	$19, (%esp)
	movl	$LC1, 4(%esp)
	call	*8(%ebp)
L43:
	movl	$_of_bin, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
