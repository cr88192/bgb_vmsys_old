	.file	"app0.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
LC0:
	.ascii "this is a test\12\0"
LC1:
	.ascii "this is another test\12\0"
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	call	__alloca
	call	___main
	movl	$1, (%esp)
	movl	$LC0, 4(%esp)
	call	_syscall
	movl	$1, (%esp)
	movl	$LC1, 4(%esp)
	call	_syscall
L2:
	jmp	L2
	.def	_syscall;	.scl	2;	.type	32;	.endef
