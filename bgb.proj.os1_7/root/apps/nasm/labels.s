	.file	"labels.c"
	.data
	.align 4
_initialised:
	.long	0
.globl _lprefix
_lprefix:
	.byte	0
	.space 9
.globl _lpostfix
_lpostfix:
	.byte	0
	.space 9
	.text
LC0:
	.ascii "\0"
	.align 2
	.def	_find_label;	.scl	3;	.type	32;	.endef
_find_label:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$0, %edi
	cmpl	$0, _tasm_compatible_mode
	je	L3
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	je	L5
	cmpb	$64, (%eax)
	jne	L2
L5:
	movl	8(%ebp), %eax
	jmp	L31
L3:
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L2
L31:
	cmpb	$46, 1(%eax)
	je	L2
	movl	_prevlabel, %eax
	movl	%eax, -16(%ebp)
	jmp	L6
L2:
	movl	$LC0, -16(%ebp)
L6:
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %esi
	movl	-16(%ebp), %edx
	cmpb	$0, (%edx)
	je	L26
L10:
	movsbl	(%edx),%eax
	addl	%eax, %edi
	incl	%edx
	cmpb	$0, (%edx)
	jne	L10
L26:
	movl	8(%ebp), %edx
	cmpb	$0, (%edx)
	je	L28
L14:
	movsbl	(%edx),%eax
	addl	%eax, %edi
	incl	%edx
	cmpb	$0, (%edx)
	jne	L14
L28:
	movl	$-580400985, %eax
	imull	%edi
	leal	(%edx,%edi), %edx
	sarl	$5, %edx
	movl	%edi, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	leal	(%edx,%edx,8), %eax
	leal	(%edx,%eax,4), %eax
	subl	%eax, %edi
	movl	_ltab(,%edi,4), %ebx
	cmpl	$-3, (%ebx)
	je	L16
L21:
	cmpl	$-2, (%ebx)
	jne	L18
	movl	8(%ebx), %ebx
	testl	%ebx, %ebx
	je	L16
L18:
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_strncmp
	testl	%eax, %eax
	jne	L20
	movl	%esi, %eax
	addl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L30
L20:
	addl	$24, %ebx
	cmpl	$-3, (%ebx)
	jne	L21
L16:
	cmpl	$0, 12(%ebp)
	je	L22
	movl	$_lfree, %esi
	movl	(%esi,%edi,4), %ebx
	cmpl	$-2, (%ebx)
	jne	L23
	movl	$768, (%esp)
	call	_nasm_malloc
	movl	%eax, 8(%ebx)
	movl	(%esi,%edi,4), %eax
	movl	8(%eax), %eax
	movl	%eax, (%esi,%edi,4)
	movl	%eax, (%esp)
	call	_init_block
L23:
	movl	$_lfree, %ebx
	movl	(%ebx,%edi,4), %eax
	movl	$-4, (%eax)
	movl	(%ebx,%edi,4), %esi
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_perm_copy
	movl	%eax, 8(%esi)
	movl	(%ebx,%edi,4), %eax
	movl	$0, 12(%eax)
	movl	(%ebx,%edi,4), %eax
	movl	$0, 16(%eax)
	movl	(%ebx,%edi,4), %edx
	leal	24(%edx), %eax
	movl	%eax, (%ebx,%edi,4)
	movl	%edx, %eax
	jmp	L1
L30:
	movl	%ebx, %eax
	jmp	L1
L22:
	movl	$0, %eax
L1:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _lookup_label
	.def	_lookup_label;	.scl	2;	.type	32;	.endef
_lookup_label:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _initialised
	je	L34
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_find_label
	movl	%eax, %ecx
	testl	%eax, %eax
	je	L34
	testb	$1, 16(%eax)
	je	L34
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	4(%ecx), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	$1, %eax
	jmp	L32
L34:
	movl	$0, %eax
L32:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _is_extern
	.def	_is_extern;	.scl	2;	.type	32;	.endef
_is_extern:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _initialised
	je	L38
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_find_label
	testl	%eax, %eax
	je	L38
	testb	$4, 16(%eax)
	je	L38
	movl	$1, %eax
	jmp	L36
L38:
	movl	$0, %eax
L36:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC1:
	.ascii "can't find label `%s' on pass two\0"
LC2:
	.ascii "%s%s%s\0"
	.align 2
.globl _redefine_label
	.def	_redefine_label;	.scl	2;	.type	32;	.endef
_redefine_label:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	call	_find_label
	movl	%eax, %esi
	testl	%eax, %eax
	jne	L41
	movl	$3, (%esp)
	movl	$LC1, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*36(%ebp)
L41:
	cmpl	$0, _tasm_compatible_mode
	je	L43
	cmpb	$46, (%ebx)
	je	L58
	cmpb	$64, (%ebx)
	jmp	L60
L43:
	cmpb	$46, (%ebx)
L60:
	jne	L44
L58:
	cmpb	$46, 1(%ebx)
	jne	L42
L44:
	cmpl	$0, _tasm_compatible_mode
	je	L47
	cmpb	$46, (%ebx)
	je	L42
	cmpb	$64, (%ebx)
	jmp	L59
L47:
	cmpb	$46, (%ebx)
L59:
	je	L42
	cmpl	$0, 20(%esi)
	je	L42
	movl	8(%esi), %eax
	movl	%eax, _prevlabel
L42:
	movl	_global_offset_changed, %eax
	movl	16(%ebp), %edx
	cmpl	%edx, 4(%esi)
	je	L49
	orl	$1, %eax
L49:
	movl	%eax, _global_offset_changed
	movl	16(%ebp), %eax
	movl	%eax, 4(%esi)
	cmpl	$1, _pass0
	jne	L40
	movl	16(%esi), %eax
	movl	%eax, %edi
	shrl	%edi
	andl	$1, %edi
	je	L51
	movl	$_lprefix, (%esp)
	call	_strlen
	movl	%eax, %ebx
	movl	8(%esi), %eax
	movl	%eax, (%esp)
	call	_strlen
	addl	%eax, %ebx
	movl	$_lpostfix, (%esp)
	call	_strlen
	leal	1(%eax,%ebx), %ebx
	movl	%ebx, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	$LC2, 4(%esp)
	movl	$_lprefix, 8(%esp)
	movl	8(%esi), %eax
	movl	%eax, 12(%esp)
	movl	$_lpostfix, 16(%esp)
	call	_sprintf
	movl	%ebx, (%esp)
	jmp	L63
L51:
	movl	16(%esi), %eax
	andl	$6, %eax
	cmpl	$4, %eax
	je	L40
	movl	8(%esi), %eax
	movl	%eax, (%esp)
L63:
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L56
	movl	12(%esi), %eax
L56:
	movl	%eax, 16(%esp)
	movl	32(%ebp), %edx
	call	*36(%edx)
	movl	32(%ebp), %eax
	movl	16(%eax), %edx
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L57
	movl	12(%esi), %eax
L57:
	movl	%eax, 16(%esp)
	call	*16(%edx)
L40:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC3:
	.ascii "symbol `%s' redefined\0"
	.align 32
LC4:
	.ascii "attempt to define a local label before any non-local labels\0"
	.align 2
.globl _define_label
	.def	_define_label;	.scl	2;	.type	32;	.endef
_define_label:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ebx
	movl	24(%ebp), %edi
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	call	_find_label
	movl	%eax, %esi
	testb	$1, 16(%eax)
	je	L65
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*36(%ebp)
	jmp	L64
L65:
	movl	16(%eax), %edx
	movl	%edx, %eax
	orl	$1, %eax
	movl	%eax, 16(%esi)
	cmpl	$0, 28(%ebp)
	je	L66
	movl	%edx, %eax
	orl	$5, %eax
	movl	%eax, 16(%esi)
L66:
	cmpl	$0, _tasm_compatible_mode
	je	L68
	cmpb	$46, (%ebx)
	je	L67
	cmpb	$64, (%ebx)
	jmp	L87
L68:
	cmpb	$46, (%ebx)
L87:
	je	L67
	testl	%edi, %edi
	je	L67
	movl	8(%esi), %eax
	movl	%eax, _prevlabel
	jmp	L70
L67:
	cmpl	$0, _tasm_compatible_mode
	je	L72
	cmpb	$46, (%ebx)
	je	L88
	cmpb	$64, (%ebx)
	jmp	L90
L72:
	cmpb	$46, (%ebx)
L90:
	jne	L70
L88:
	cmpb	$46, 1(%ebx)
	je	L70
	movl	_prevlabel, %eax
	cmpb	$0, (%eax)
	jne	L70
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	call	*36(%ebp)
L70:
	movl	12(%ebp), %eax
	movl	%eax, (%esi)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esi)
	movl	$0, %eax
	cmpl	$0, _tasm_compatible_mode
	je	L76
	cmpb	$46, (%ebx)
	je	L75
	cmpb	$64, (%ebx)
	jmp	L89
L76:
	cmpb	$46, (%ebx)
L89:
	je	L75
	testl	%edi, %edi
	je	L75
	movl	$1, %eax
L75:
	movl	%eax, 20(%esi)
	cmpl	$1, _pass0
	je	L79
	testl	%edi, %edi
	jne	L64
	cmpl	$0, 28(%ebp)
	jne	L64
	testl	$1, 12(%ebp)
	je	L64
L79:
	movl	16(%esi), %eax
	movl	%eax, %edi
	shrl	%edi
	andl	$1, %edi
	je	L80
	movl	$_lprefix, (%esp)
	call	_strlen
	movl	%eax, %ebx
	movl	8(%esi), %eax
	movl	%eax, (%esp)
	call	_strlen
	addl	%eax, %ebx
	movl	$_lpostfix, (%esp)
	call	_strlen
	leal	1(%eax,%ebx), %ebx
	movl	%ebx, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	$LC2, 4(%esp)
	movl	$_lprefix, 8(%esp)
	movl	8(%esi), %eax
	movl	%eax, 12(%esp)
	movl	$_lpostfix, 16(%esp)
	call	_sprintf
	movl	%ebx, (%esp)
	jmp	L93
L80:
	movl	16(%esi), %eax
	andl	$6, %eax
	cmpl	$4, %eax
	je	L64
	movl	8(%esi), %eax
	movl	%eax, (%esp)
L93:
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L85
	movl	12(%esi), %eax
L85:
	movl	%eax, 16(%esp)
	movl	32(%ebp), %eax
	call	*36(%eax)
	movl	32(%ebp), %eax
	movl	16(%eax), %edx
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L86
	movl	12(%esi), %eax
L86:
	movl	%eax, 16(%esp)
	call	*16(%edx)
L64:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC5:
	.ascii "attempt to define a local label as a common variable\0"
	.align 2
.globl _define_common
	.def	_define_common;	.scl	2;	.type	32;	.endef
_define_common:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	%esi, (%esp)
	movl	$1, 4(%esp)
	call	_find_label
	movl	%eax, %ebx
	testb	$1, 16(%eax)
	je	L95
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	movl	%esi, 8(%esp)
	call	*28(%ebp)
	jmp	L94
L95:
	orl	$1, 16(%eax)
	cmpl	$0, _tasm_compatible_mode
	je	L97
	cmpb	$46, (%esi)
	je	L96
	cmpb	$64, (%esi)
	jmp	L102
L97:
	cmpb	$46, (%esi)
L102:
	je	L96
	movl	8(%ebx), %eax
	movl	%eax, _prevlabel
	jmp	L99
L96:
	movl	$1, (%esp)
	movl	$LC5, 4(%esp)
	call	*28(%ebp)
L99:
	movl	%edi, (%ebx)
	movl	$0, 4(%ebx)
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$2, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L100
	movl	12(%ebx), %eax
L100:
	movl	%eax, 16(%esp)
	movl	24(%ebp), %eax
	call	*36(%eax)
	movl	24(%ebp), %eax
	movl	16(%eax), %edx
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$2, 12(%esp)
	movl	20(%ebp), %eax
	testl	%eax, %eax
	jne	L101
	movl	12(%ebx), %eax
L101:
	movl	%eax, 16(%esp)
	call	*16(%edx)
L94:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC6:
	.ascii "attempt to declare local symbol `%s' as global\0"
	.align 2
.globl _declare_as_global
	.def	_declare_as_global;	.scl	2;	.type	32;	.endef
_declare_as_global:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %esi
	cmpl	$0, _tasm_compatible_mode
	je	L105
	cmpb	$46, (%eax)
	je	L119
	cmpb	$64, (%eax)
	jmp	L120
L105:
	cmpb	$46, (%eax)
L120:
	jne	L104
L119:
	cmpb	$46, 1(%eax)
	je	L104
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	movl	%eax, 8(%esp)
	call	*16(%ebp)
	jmp	L103
L104:
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_find_label
	movl	%eax, %ebx
	movl	16(%eax), %eax
	andl	$3, %eax
	cmpl	$1, %eax
	je	L103
	cmpl	$1, %eax
	jg	L103
	testl	%eax, %eax
	jne	L103
	movl	$2, 16(%ebx)
	testl	%esi, %esi
	je	L110
	movl	%esi, (%esp)
	movl	$LC0, 4(%esp)
	call	_perm_copy
	jmp	L111
L110:
	movl	$0, %eax
L111:
	movl	%eax, 12(%ebx)
L103:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _init_labels
	.def	_init_labels;	.scl	2;	.type	32;	.endef
_init_labels:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	$0, %ebx
	movl	$_ltab, %edi
	movl	%edi, %esi
L127:
	movl	$768, (%esp)
	call	_nasm_malloc
	movl	%eax, (%edi,%ebx,4)
	testl	%eax, %eax
	je	L131
	movl	(%esi,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_init_block
	movl	(%esi,%ebx,4), %eax
	movl	%eax, _lfree(,%ebx,4)
	incl	%ebx
	cmpl	$36, %ebx
	jle	L127
	movl	$4108, (%esp)
	call	_nasm_malloc
	movl	%eax, _perm_tail
	movl	%eax, _perm_head
	testl	%eax, %eax
	jne	L128
L131:
	movl	$-1, %eax
	jmp	L121
L128:
	movl	_perm_head, %eax
	movl	$0, (%eax)
	movl	_perm_head, %eax
	movl	$4096, 4(%eax)
	movl	_perm_head, %eax
	movl	$0, 8(%eax)
	movl	$LC0, _prevlabel
	movl	$1, _initialised
	movl	$0, %eax
L121:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _cleanup_labels
	.def	_cleanup_labels;	.scl	2;	.type	32;	.endef
_cleanup_labels:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	$0, _initialised
	movl	$0, %esi
L145:
	movl	_ltab(,%esi,4), %eax
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L153
L144:
	cmpl	$-2, (%ebx)
	je	L155
L143:
	addl	$24, %ebx
	cmpl	$-2, (%ebx)
	jne	L143
L155:
	movl	8(%ebx), %ebx
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, %eax
	testl	%ebx, %ebx
	jne	L144
L153:
	incl	%esi
	cmpl	$36, %esi
	jle	L145
	cmpl	$0, _perm_head
	je	L157
L149:
	movl	_perm_head, %eax
	movl	%eax, _perm_tail
	movl	(%eax), %edx
	movl	%edx, _perm_head
	movl	%eax, (%esp)
	call	_nasm_free
	cmpl	$0, _perm_head
	jne	L149
L157:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_init_block;	.scl	3;	.type	32;	.endef
_init_block:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	$0, %edx
L163:
	leal	(%edx,%edx,2), %eax
	movl	$-3, (%ecx,%eax,8)
	incl	%edx
	cmpl	$30, %edx
	jle	L163
	movl	$-2, 744(%ecx)
	movl	$0, 752(%ecx)
	popl	%ebp
	ret
	.align 2
	.def	_perm_copy;	.scl	3;	.type	32;	.endef
_perm_copy:
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
	leal	1(%eax,%ebx), %ebx
	movl	_perm_tail, %eax
	movl	%eax, -16(%ebp)
	movl	4(%eax), %eax
	movl	-16(%ebp), %edx
	subl	8(%edx), %eax
	cmpl	%ebx, %eax
	jge	L167
	movl	$4108, (%esp)
	call	_nasm_malloc
	movl	-16(%ebp), %edx
	movl	%eax, (%edx)
	movl	_perm_tail, %eax
	movl	(%eax), %eax
	movl	%eax, _perm_tail
	movl	$0, (%eax)
	movl	_perm_tail, %eax
	movl	$4096, 4(%eax)
	movl	_perm_tail, %eax
	movl	$0, 8(%eax)
L167:
	movl	_perm_tail, %eax
	movl	%eax, %ecx
	addl	8(%eax), %ecx
	addl	$12, %ecx
	movl	%ecx, %ebx
	movzbl	(%esi), %eax
	movb	%al, (%ecx)
	incl	%esi
	testb	%al, %al
	je	L172
L171:
	incl	%ecx
	movzbl	(%esi), %eax
	movb	%al, (%ecx)
	incl	%esi
	testb	%al, %al
	jne	L171
L172:
	movzbl	(%edi), %eax
	movb	%al, (%ecx)
	incl	%edi
	incl	%ecx
	testb	%al, %al
	jne	L172
	movl	_perm_tail, %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	subl	$12, %eax
	movl	%eax, 8(%edx)
	movl	%ebx, %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _ltab,160
.lcomm _lfree,160
.lcomm _perm_head,16
.lcomm _perm_tail,16
.lcomm _prevlabel,16
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_strncmp;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
