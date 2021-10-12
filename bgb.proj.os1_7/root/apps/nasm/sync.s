	.file	"sync.c"
	.text
	.align 32
LC0:
	.ascii "ndisasm: not enough memory for sync array\12\0"
	.align 2
.globl _init_sync
	.def	_init_sync;	.scl	2;	.type	32;	.endef
_init_sync:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$32776, (%esp)
	call	_malloc
	movl	%eax, _synx
	testl	%eax, %eax
	jne	L2
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC0, 4(%esp)
	call	_fprintf
	movl	$1, (%esp)
	call	_exit
L2:
	movl	$0, _nsynx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _add_sync
	.def	_add_sync;	.scl	2;	.type	32;	.endef
_add_sync:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	cmpl	$4096, _nsynx
	je	L3
	movl	_nsynx, %ecx
	incl	%ecx
	movl	%ecx, _nsynx
	movl	8(%ebp), %edx
	movl	_synx, %eax
	movl	%edx, (%eax,%ecx,8)
	movl	12(%ebp), %ecx
	movl	_nsynx, %edx
	movl	_synx, %eax
	movl	%ecx, 4(%eax,%edx,8)
	movl	_nsynx, %edi
	cmpl	$1, %edi
	jle	L3
L10:
	movl	%edi, %eax
	shrl	$31, %eax
	leal	(%eax,%edi), %eax
	movl	%eax, %ebx
	sarl	%ebx
	movl	_synx, %esi
	movl	(%esi,%ebx,8), %eax
	cmpl	(%esi,%edi,8), %eax
	jbe	L7
	movl	(%esi,%ebx,8), %eax
	movl	4(%esi,%ebx,8), %edx
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
	movl	(%esi,%edi,8), %eax
	movl	4(%esi,%edi,8), %edx
	movl	%eax, (%esi,%ebx,8)
	movl	%edx, 4(%esi,%ebx,8)
	movl	_synx, %ecx
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, (%ecx,%edi,8)
	movl	%edx, 4(%ecx,%edi,8)
L7:
	movl	%edi, %eax
	shrl	$31, %eax
	leal	(%eax,%edi), %eax
	movl	%eax, %edi
	sarl	%edi
	cmpl	$1, %edi
	jg	L10
L3:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _next_sync
	.def	_next_sync;	.scl	2;	.type	32;	.endef
_next_sync:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	cmpl	$0, _nsynx
	jle	L27
	movl	_synx, %edx
	movl	%edx, %ecx
	movl	8(%edx), %eax
	addl	12(%edx), %eax
	cmpl	8(%ebp), %eax
	ja	L14
L26:
	movl	_nsynx, %ebx
	movl	(%ecx,%ebx,8), %esi
	movl	4(%ecx,%ebx,8), %edi
	movl	8(%ecx), %eax
	movl	12(%ecx), %edx
	movl	%eax, (%ecx,%ebx,8)
	movl	%edx, 4(%ecx,%ebx,8)
	movl	_synx, %eax
	movl	%esi, 8(%eax)
	movl	%edi, 12(%eax)
	decl	_nsynx
	movl	$1, -20(%ebp)
	cmpl	$1, _nsynx
	jle	L13
L25:
	movl	-20(%ebp), %ebx
	addl	%ebx, %ebx
	movl	_synx, %edx
	movl	(%edx,%ebx,8), %eax
	movl	-20(%ebp), %ecx
	cmpl	(%edx,%ecx,8), %eax
	jae	L20
	leal	1(%ebx), %eax
	cmpl	_nsynx, %eax
	jg	L21
	movl	8(%edx,%ebx,8), %eax
	cmpl	(%edx,%ebx,8), %eax
	jbe	L20
L21:
	movl	_synx, %eax
	movl	(%eax,%ebx,8), %esi
	movl	4(%eax,%ebx,8), %edi
	movl	-20(%ebp), %ecx
	movl	(%eax,%ecx,8), %edx
	movl	4(%eax,%ecx,8), %ecx
	movl	%edx, (%eax,%ebx,8)
	movl	%ecx, 4(%eax,%ebx,8)
	movl	_synx, %eax
	movl	-20(%ebp), %edx
	movl	%esi, (%eax,%edx,8)
	movl	%edi, 4(%eax,%edx,8)
	movl	%ebx, -20(%ebp)
	jmp	L17
L20:
	leal	1(%ebx), %ecx
	movl	%ecx, -24(%ebp)
	cmpl	_nsynx, %ecx
	jg	L13
	movl	_synx, %ecx
	movl	8(%ecx,%ebx,8), %eax
	movl	-20(%ebp), %edx
	cmpl	(%ecx,%edx,8), %eax
	jae	L13
	movl	8(%ecx,%ebx,8), %esi
	movl	12(%ecx,%ebx,8), %edi
	movl	(%ecx,%edx,8), %eax
	movl	4(%ecx,%edx,8), %edx
	movl	%eax, 8(%ecx,%ebx,8)
	movl	%edx, 12(%ecx,%ebx,8)
	movl	_synx, %eax
	movl	-20(%ebp), %ecx
	movl	%esi, (%eax,%ecx,8)
	movl	%edi, 4(%eax,%ecx,8)
	movl	-24(%ebp), %eax
	movl	%eax, -20(%ebp)
L17:
	movl	-20(%ebp), %eax
	addl	%eax, %eax
	cmpl	_nsynx, %eax
	jle	L25
L13:
	cmpl	$0, _nsynx
	jle	L27
	movl	_synx, %ecx
	movl	8(%ecx), %eax
	addl	12(%ecx), %eax
	cmpl	8(%ebp), %eax
	jbe	L26
L14:
	cmpl	$0, _nsynx
	jle	L27
	cmpl	$0, 12(%ebp)
	je	L28
	movl	_synx, %eax
	movl	12(%eax), %eax
	movl	12(%ebp), %edx
	movl	%eax, (%edx)
L28:
	movl	_synx, %eax
	movl	8(%eax), %eax
	jmp	L12
L27:
	cmpl	$0, 12(%ebp)
	je	L30
	movl	12(%ebp), %ecx
	movl	$0, (%ecx)
L30:
	movl	$2147483647, %eax
L12:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _synx,16
.lcomm _nsynx,16
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
