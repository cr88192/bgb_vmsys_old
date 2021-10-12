	.file	"eval.c"
	.data
	.align 4
_tempexprs:
	.long	0
	.align 4
_tempexprs_size:
	.long	0
	.text
	.align 2
.globl _eval_cleanup
	.def	_eval_cleanup;	.scl	2;	.type	32;	.endef
_eval_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _ntempexprs
	je	L7
L5:
	movl	_ntempexprs, %eax
	decl	%eax
	movl	%eax, _ntempexprs
	movl	_tempexprs, %edx
	movl	(%edx,%eax,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	cmpl	$0, _ntempexprs
	jne	L5
L7:
	movl	_tempexprs, %eax
	movl	%eax, (%esp)
	call	_nasm_free
	leave
	ret
	.align 2
	.def	_begintemp;	.scl	3;	.type	32;	.endef
_begintemp:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, _tempexpr
	movl	$0, _ntempexpr
	movl	$0, _tempexpr_size
	popl	%ebp
	ret
	.align 2
	.def	_addtotemp;	.scl	3;	.type	32;	.endef
_addtotemp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_ntempexpr, %eax
	cmpl	_tempexpr_size, %eax
	jl	L15
L13:
	movl	_tempexpr_size, %eax
	addl	$8, %eax
	movl	%eax, _tempexpr_size
	movl	_tempexpr, %edx
	movl	%edx, (%esp)
	sall	$3, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _tempexpr
	movl	_ntempexpr, %eax
	cmpl	_tempexpr_size, %eax
	jge	L13
L15:
	movl	8(%ebp), %ecx
	movl	_ntempexpr, %edx
	movl	_tempexpr, %eax
	movl	%ecx, (%eax,%edx,8)
	movl	12(%ebp), %ecx
	movl	_ntempexpr, %edx
	movl	_tempexpr, %eax
	movl	%ecx, 4(%eax,%edx,8)
	incl	_ntempexpr
	leave
	ret
	.align 2
	.def	_finishtemp;	.scl	3;	.type	32;	.endef
_finishtemp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, (%esp)
	movl	$0, 4(%esp)
	call	_addtotemp
	movl	_ntempexprs, %eax
	cmpl	_tempexprs_size, %eax
	jl	L22
L20:
	movl	_tempexprs_size, %eax
	subl	$-128, %eax
	movl	%eax, _tempexprs_size
	movl	_tempexprs, %edx
	movl	%edx, (%esp)
	sall	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _tempexprs
	movl	_ntempexprs, %eax
	cmpl	_tempexprs_size, %eax
	jge	L20
L22:
	movl	_tempexpr, %eax
	movl	_ntempexprs, %ecx
	movl	_tempexprs, %edx
	movl	%eax, (%edx,%ecx,4)
	incl	_ntempexprs
	leave
	ret
	.align 2
	.def	_add_vectors;	.scl	3;	.type	32;	.endef
_add_vectors:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	$0, %edi
	movl	%esi, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	jne	L25
	movl	%ebx, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	je	L24
L25:
	movl	$1, %edi
L24:
	call	_begintemp
	cmpl	$0, (%esi)
	je	L38
	cmpl	$0, (%ebx)
	je	L27
	cmpl	$1073741951, (%esi)
	jg	L27
	cmpl	$1073741951, (%ebx)
	jg	L27
L36:
	movl	(%esi), %eax
	cmpl	(%ebx), %eax
	jle	L30
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	movl	(%ebx), %eax
	jmp	L50
L30:
	movl	(%esi), %eax
	cmpl	(%ebx), %eax
	jge	L32
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	movl	(%esi), %eax
	addl	$8, %esi
	jmp	L31
L32:
	movl	4(%esi), %eax
	movl	%eax, %edx
	addl	4(%ebx), %edx
	je	L34
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_addtotemp
L34:
	movl	(%esi), %eax
	addl	$8, %esi
L50:
	addl	$8, %ebx
L31:
	cmpl	$125, %eax
	je	L43
	cmpl	$0, (%esi)
	je	L38
	cmpl	$0, (%ebx)
	je	L27
	cmpl	$1073741951, (%esi)
	jg	L27
	cmpl	$1073741951, (%ebx)
	jle	L36
L27:
	cmpl	$0, (%esi)
	je	L38
	testl	%edi, %edi
	jne	L41
	cmpl	$1073741951, (%esi)
	jg	L38
L41:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	addl	$8, %esi
	cmpl	$0, (%esi)
	je	L38
	testl	%edi, %edi
	jne	L41
	cmpl	$1073741951, (%esi)
	jle	L41
L38:
	cmpl	$0, (%ebx)
	je	L43
	testl	%edi, %edi
	jne	L46
	cmpl	$1073741951, (%ebx)
	jg	L43
L46:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	addl	$8, %ebx
	cmpl	$0, (%ebx)
	je	L43
	testl	%edi, %edi
	jne	L46
	cmpl	$1073741951, (%ebx)
	jle	L46
L43:
	call	_finishtemp
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_scalar_mult;	.scl	3;	.type	32;	.endef
_scalar_mult:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	movl	%ebx, %edx
	cmpl	$0, (%ebx)
	je	L53
	cmpl	$1073741951, (%ebx)
	jg	L53
L57:
	movl	%esi, %eax
	imull	4(%edx), %eax
	movl	%eax, 4(%edx)
	cmpl	$0, _hint
	je	L56
	movl	_hint, %ecx
	cmpl	$1, 4(%ecx)
	jne	L56
	movl	(%edx), %eax
	cmpl	(%ecx), %eax
	jne	L56
	testl	%edi, %edi
	je	L56
	movl	$2, 4(%ecx)
L56:
	addl	$8, %edx
	cmpl	$0, (%edx)
	je	L53
	cmpl	$1073741951, (%edx)
	jle	L57
L53:
	movl	$0, (%edx)
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_scalarvect;	.scl	3;	.type	32;	.endef
_scalarvect:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	_begintemp
	movl	$126, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	call	_finishtemp
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_unknown_expr;	.scl	3;	.type	32;	.endef
_unknown_expr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	_begintemp
	movl	$125, (%esp)
	movl	$1, 4(%esp)
	call	_addtotemp
	call	_finishtemp
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC0:
	.ascii "cannot apply SEG to a non-relocatable value\0"
	.align 32
LC1:
	.ascii "SEG applied to something which is already a segment base\0"
	.align 2
	.def	_segment_part;	.scl	3;	.type	32;	.endef
_segment_part:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_is_unknown
	testl	%eax, %eax
	je	L62
	call	_unknown_expr
	jmp	L61
L62:
	movl	%ebx, (%esp)
	call	_is_reloc
	testl	%eax, %eax
	je	L73
	movl	%ebx, (%esp)
	call	_reloc_seg
	cmpl	$-1, %eax
	jne	L64
L73:
	movl	$1, (%esp)
	movl	$LC0, 4(%esp)
	jmp	L72
L64:
	testl	$1073741824, %eax
	je	L66
	andl	$-1073741825, %eax
	movl	%eax, (%esp)
	call	_scalarvect
	jmp	L61
L66:
	testl	$1, %eax
	je	L68
	movl	$1, (%esp)
	movl	$LC1, 4(%esp)
L72:
	call	*_error
	movl	$0, %eax
	jmp	L61
L68:
	incl	%eax
	movl	%eax, (%esp)
	movl	_outfmt, %eax
	call	*44(%eax)
	movl	%eax, %ebx
	call	_begintemp
	movl	$125, %eax
	cmpl	$-1, %ebx
	je	L71
	leal	128(%ebx), %eax
L71:
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_addtotemp
	call	_finishtemp
L61:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC2:
	.ascii "`|' operator may only be applied to scalar values\0"
	.align 2
	.def	_rexp0;	.scl	3;	.type	32;	.endef
_rexp0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_rexp1
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L74
	jmp	L75
L91:
	movl	$0, %eax
	jmp	L74
L75:
	cmpl	$273, _i
	jne	L90
L88:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_rexp1
	movl	%eax, %esi
	testl	%eax, %eax
	je	L91
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L82
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L81
L82:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L80
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L80
L81:
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*_error
L80:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L84
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L83
L84:
	call	_unknown_expr
	jmp	L92
L83:
	movl	$0, -16(%ebp)
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	jne	L87
	movl	%esi, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	je	L86
L87:
	movl	$1, -16(%ebp)
L86:
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_scalarvect
L92:
	movl	%eax, %ebx
	cmpl	$273, _i
	je	L88
L90:
	movl	%ebx, %eax
L74:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC3:
	.ascii "`^' operator may only be applied to scalar values\0"
	.align 2
	.def	_rexp1;	.scl	3;	.type	32;	.endef
_rexp1:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_rexp2
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L93
	jmp	L94
L110:
	movl	$0, %eax
	jmp	L93
L94:
	cmpl	$274, _i
	jne	L109
L107:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_rexp2
	movl	%eax, %esi
	testl	%eax, %eax
	je	L110
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L101
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L100
L101:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L99
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L99
L100:
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	call	*_error
L99:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L103
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L102
L103:
	call	_unknown_expr
	jmp	L111
L102:
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%ebx, %edx
	testl	%eax, %eax
	jne	L106
	xorl	$1, %edx
L106:
	movl	%edx, (%esp)
	call	_scalarvect
L111:
	movl	%eax, %ebx
	cmpl	$274, _i
	je	L107
L109:
	movl	%ebx, %eax
L93:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC4:
	.ascii "`&' operator may only be applied to scalar values\0"
	.align 2
	.def	_rexp2;	.scl	3;	.type	32;	.endef
_rexp2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_rexp3
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L112
	jmp	L113
L128:
	movl	$0, %eax
	jmp	L112
L113:
	cmpl	$272, _i
	jne	L127
L125:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_rexp3
	movl	%eax, %esi
	testl	%eax, %eax
	je	L128
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L120
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L119
L120:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L118
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L118
L119:
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L118:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L122
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L121
L122:
	call	_unknown_expr
	jmp	L129
L121:
	movl	$0, -16(%ebp)
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	je	L124
	movl	%esi, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	je	L124
	movl	$1, -16(%ebp)
L124:
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_scalarvect
L129:
	movl	%eax, %ebx
	cmpl	$272, _i
	je	L125
L127:
	movl	%ebx, %eax
L112:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC5:
	.ascii "`%s': operands differ by a non-scalar\0"
LC9:
	.ascii "<=\0"
LC8:
	.ascii "<\0"
LC6:
	.ascii ">=\0"
LC7:
	.ascii ">\0"
	.align 2
	.def	_rexp3;	.scl	3;	.type	32;	.endef
_rexp3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_expr0
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L130
	jmp	L131
L169:
	movl	$0, %eax
	jmp	L130
L131:
	movl	_i, %eax
	subl	$60, %eax
	cmpl	$2, %eax
	jbe	L166
	cmpl	$271, _i
	je	L166
	cmpl	$270, _i
	je	L166
	cmpl	$269, _i
	jne	L168
L166:
	movl	_i, %esi
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_expr0
	testl	%eax, %eax
	je	L169
	movl	%eax, (%esp)
	movl	$-1, 4(%esp)
	movl	$0, 8(%esp)
	call	_scalar_mult
	movl	%ebx, (%esp)
	movl	%eax, 4(%esp)
	call	_add_vectors
	movl	%eax, %ebx
	cmpl	$61, %esi
	je	L138
	cmpl	$271, %esi
	jne	L144
L138:
	movl	%ebx, (%esp)
	call	_is_unknown
	movl	$-1, %edx
	testl	%eax, %eax
	jne	L136
	movl	%ebx, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	je	L142
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	je	L141
L142:
	cmpl	$271, %esi
	jmp	L173
L141:
	cmpl	$61, %esi
L173:
	sete	%al
	jmp	L170
L144:
	movl	%eax, (%esp)
	call	_is_unknown
	movl	$-1, %edx
	testl	%eax, %eax
	jne	L136
	movl	%ebx, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	jne	L147
	movl	$1, (%esp)
	movl	$LC5, 4(%esp)
	movl	$LC9, %eax
	cmpl	$270, %esi
	je	L149
	movl	$LC8, %eax
	cmpl	$60, %esi
	je	L149
	movl	$LC6, %eax
	cmpl	$269, %esi
	je	L149
	movl	$LC7, %eax
L149:
	movl	%eax, 8(%esp)
	call	*_error
	movl	$0, %edx
	jmp	L136
L147:
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	jne	L155
	leal	-269(%esi), %edx
	cmpl	$1, %edx
	setbe	%al
L170:
	movzbl	%al, %edx
	jmp	L136
L155:
	testl	%eax, %eax
	jle	L157
	movl	$0, %edx
	cmpl	$269, %esi
	je	L162
	cmpl	$62, %esi
	jmp	L171
L157:
	movl	$0, %edx
	cmpl	$270, %esi
	je	L162
	cmpl	$60, %esi
L171:
	jne	L136
L162:
	movl	$1, %edx
L136:
	cmpl	$-1, %edx
	jne	L164
	call	_unknown_expr
	jmp	L172
L164:
	movl	%edx, (%esp)
	call	_scalarvect
L172:
	movl	%eax, %ebx
	movl	_i, %eax
	subl	$60, %eax
	cmpl	$2, %eax
	jbe	L166
	cmpl	$271, _i
	je	L166
	cmpl	$270, _i
	je	L166
	cmpl	$269, _i
	je	L166
L168:
	movl	%ebx, %eax
L130:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_expr0;	.scl	3;	.type	32;	.endef
_expr0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_expr1
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L174
	jmp	L175
L189:
	movl	$0, %eax
	jmp	L174
L175:
	cmpl	$124, _i
	jne	L188
L186:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_expr1
	movl	%eax, %esi
	testl	%eax, %eax
	je	L189
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L182
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L181
L182:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L180
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L180
L181:
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*_error
L180:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L184
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L183
L184:
	call	_unknown_expr
	jmp	L190
L183:
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	orl	%ebx, %eax
	movl	%eax, (%esp)
	call	_scalarvect
L190:
	movl	%eax, %ebx
	cmpl	$124, _i
	je	L186
L188:
	movl	%ebx, %eax
L174:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_expr1;	.scl	3;	.type	32;	.endef
_expr1:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_expr2
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L191
	jmp	L192
L206:
	movl	$0, %eax
	jmp	L191
L192:
	cmpl	$94, _i
	jne	L205
L203:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_expr2
	movl	%eax, %esi
	testl	%eax, %eax
	je	L206
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L199
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L198
L199:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L197
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L197
L198:
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	call	*_error
L197:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L201
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L200
L201:
	call	_unknown_expr
	jmp	L207
L200:
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	xorl	%ebx, %eax
	movl	%eax, (%esp)
	call	_scalarvect
L207:
	movl	%eax, %ebx
	cmpl	$94, _i
	je	L203
L205:
	movl	%ebx, %eax
L191:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_expr2;	.scl	3;	.type	32;	.endef
_expr2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_expr3
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L208
	jmp	L209
L223:
	movl	$0, %eax
	jmp	L208
L209:
	cmpl	$38, _i
	jne	L222
L220:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_expr3
	movl	%eax, %esi
	testl	%eax, %eax
	je	L223
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L216
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L215
L216:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L214
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L214
L215:
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L214:
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L218
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L217
L218:
	call	_unknown_expr
	jmp	L224
L217:
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	andl	%ebx, %eax
	movl	%eax, (%esp)
	call	_scalarvect
L224:
	movl	%eax, %ebx
	cmpl	$38, _i
	je	L220
L222:
	movl	%ebx, %eax
L208:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC10:
	.ascii "shift operator may only be applied to scalar values\0"
	.align 2
	.def	_expr3;	.scl	3;	.type	32;	.endef
_expr3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_expr4
	movl	%eax, %esi
	movl	$0, %eax
	testl	%esi, %esi
	je	L225
	jmp	L226
L246:
	movl	$0, %eax
	jmp	L225
L226:
	movl	_i, %eax
	movl	%eax, %edx
	subl	$265, %eax
	cmpl	$1, %eax
	ja	L245
L243:
	movl	%edx, %edi
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_expr4
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L246
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L233
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L232
L233:
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L231
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L231
L232:
	movl	$1, (%esp)
	movl	$LC10, 4(%esp)
	call	*_error
	jmp	L227
L231:
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L236
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L235
L236:
	call	_unknown_expr
	jmp	L248
L235:
	cmpl	$265, %edi
	je	L239
	cmpl	$266, %edi
	je	L240
	jmp	L227
L239:
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %esi
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, %ecx
	movl	%esi, %eax
	sall	%cl, %eax
	jmp	L247
L240:
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %esi
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, %ecx
	movl	%esi, %eax
	shrl	%cl, %eax
L247:
	movl	%eax, (%esp)
	call	_scalarvect
L248:
	movl	%eax, %esi
L227:
	movl	_i, %edx
	leal	-265(%edx), %eax
	cmpl	$1, %eax
	jbe	L243
L245:
	movl	%esi, %eax
L225:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_expr4;	.scl	3;	.type	32;	.endef
_expr4:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	%edi, (%esp)
	call	_expr5
	movl	%eax, %esi
	movl	$0, %edx
	testl	%eax, %eax
	je	L249
	cmpl	$43, _i
	je	L260
	cmpl	$45, _i
	jne	L262
L260:
	movl	_i, %ebx
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%edi, (%esp)
	call	_expr5
	movl	$0, %edx
	testl	%eax, %eax
	je	L249
	cmpl	$43, %ebx
	je	L264
	cmpl	$45, %ebx
	jne	L251
	movl	%eax, (%esp)
	movl	$-1, 4(%esp)
	movl	$0, 8(%esp)
	call	_scalar_mult
L264:
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	_add_vectors
	movl	%eax, %esi
L251:
	cmpl	$43, _i
	je	L260
	cmpl	$45, _i
	je	L260
L262:
	movl	%esi, %edx
L249:
	movl	%edx, %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC12:
	.ascii "division by zero\0"
	.align 32
LC11:
	.ascii "division operator may only be applied to scalar values\0"
	.align 32
LC13:
	.ascii "unable to multiply two non-scalar objects\0"
	.align 2
	.def	_expr5;	.scl	3;	.type	32;	.endef
_expr5:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_expr6
	movl	%eax, %edi
	movl	$0, %eax
	testl	%edi, %edi
	je	L265
	jmp	L266
L306:
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
	jmp	L312
L266:
	cmpl	$42, _i
	je	L302
	cmpl	$47, _i
	je	L302
	cmpl	$37, _i
	je	L302
	cmpl	$267, _i
	je	L302
	cmpl	$268, _i
	jne	L304
L302:
	movl	_i, %ebx
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	8(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_expr6
	movl	%eax, %esi
	movl	$0, %eax
	testl	%esi, %esi
	je	L265
	cmpl	$42, %ebx
	je	L274
	movl	%edi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L273
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L272
L273:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L271
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L271
L272:
	movl	$1, (%esp)
	movl	$LC11, 4(%esp)
	jmp	L312
L271:
	cmpl	$42, %ebx
	je	L274
	movl	%esi, (%esp)
	call	_is_unknown
	testl	%eax, %eax
	jne	L274
	movl	%esi, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	je	L306
L274:
	cmpl	$47, %ebx
	je	L283
	cmpl	$47, %ebx
	jg	L301
	cmpl	$37, %ebx
	je	L287
	cmpl	$42, %ebx
	je	L276
	jmp	L267
L301:
	cmpl	$267, %ebx
	je	L291
	cmpl	$268, %ebx
	je	L295
	jmp	L267
L276:
	movl	%edi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	je	L277
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%esi, (%esp)
	jmp	L308
L277:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	je	L279
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%edi, (%esp)
L308:
	movl	%eax, 4(%esp)
	movl	$1, 8(%esp)
	call	_scalar_mult
	jmp	L307
L279:
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L281
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
L281:
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
L312:
	call	*_error
	movl	$0, %eax
	jmp	L265
L283:
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %edx
	movl	%ebx, %eax
	movl	%edx, %ecx
	movl	$0, %edx
	divl	%ecx
	jmp	L311
L287:
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %edx
	movl	%ebx, %eax
	movl	%edx, %ecx
	movl	$0, %edx
	divl	%ecx
	jmp	L310
L291:
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %edx
	movl	%ebx, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
L311:
	movl	%eax, (%esp)
	jmp	L309
L295:
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	jne	L297
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L296
L297:
	call	_unknown_expr
	jmp	L307
L296:
	movl	%edi, (%esp)
	call	_reloc_value
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, %edx
	movl	%ebx, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
L310:
	movl	%edx, (%esp)
L309:
	call	_scalarvect
L307:
	movl	%eax, %edi
L267:
	cmpl	$42, _i
	je	L302
	cmpl	$47, _i
	je	L302
	cmpl	$37, _i
	je	L302
	cmpl	$267, _i
	je	L302
	cmpl	$268, _i
	je	L302
L304:
	movl	%edi, %eax
L265:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC14:
	.ascii "`~' operator may only be applied to scalar values\0"
	.align 32
LC15:
	.ascii "unable to determine segment base\0"
LC16:
	.ascii "expecting `)'\0"
	.align 32
LC17:
	.ascii "%s not supported in preprocess-only mode\0"
LC18:
	.ascii "`$'\0"
LC19:
	.ascii "`$$'\0"
LC20:
	.ascii "symbol references\0"
LC21:
	.ascii "symbol `%s' undefined\0"
	.align 32
LC22:
	.ascii "symbol `%s' not defined before use\0"
LC23:
	.ascii "expression syntax error\0"
	.align 2
	.def	_expr6;	.scl	3;	.type	32;	.endef
_expr6:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	cmpl	$45, _i
	jne	L314
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	_expr6
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L313
	movl	%ebx, (%esp)
	movl	$-1, 4(%esp)
	movl	$0, 8(%esp)
	call	_scalar_mult
	jmp	L313
L314:
	cmpl	$43, _i
	jne	L317
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	_expr6
	jmp	L313
L317:
	cmpl	$126, _i
	jne	L319
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	_expr6
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L313
	movl	%ebx, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L321
	call	_unknown_expr
	jmp	L313
L321:
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L322
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	jmp	L373
L322:
	movl	%ebx, (%esp)
	call	_reloc_value
	notl	%eax
	movl	%eax, (%esp)
	call	_scalarvect
	jmp	L313
L319:
	cmpl	$275, _i
	jne	L325
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	_expr6
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L313
	movl	%ebx, (%esp)
	call	_segment_part
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L313
	movl	%ebx, (%esp)
	call	_is_unknown
	testl	%eax, %eax
	je	L372
	testl	%esi, %esi
	je	L372
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
	jmp	L373
L325:
	cmpl	$40, _i
	jne	L330
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	*_bexpr
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L313
	cmpl	$41, _i
	je	L332
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	jmp	L373
L332:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
L372:
	movl	%ebx, %eax
	jmp	L313
L330:
	movl	_i, %eax
	subl	$256, %eax
	cmpl	$2, %eax
	jbe	L335
	cmpl	$261, _i
	je	L335
	cmpl	$262, _i
	jne	L334
L335:
	call	_begintemp
	movl	_i, %eax
	subl	$256, %eax
	cmpl	$6, %eax
	ja	L336
	jmp	*L366(,%eax,4)
	.align 4
	.align 4
L366:
	.long	L342
	.long	L337
	.long	L338
	.long	L336
	.long	L336
	.long	L342
	.long	L342
L337:
	movl	$126, (%esp)
	movl	_tokval, %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	jmp	L370
L338:
	movl	_tokval, %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_addtotemp
	cmpl	$0, _hint
	je	L336
	movl	_hint, %edx
	cmpl	$0, 4(%edx)
	jne	L336
	movl	_tokval, %eax
	movl	4(%eax), %eax
	movl	%eax, (%edx)
	movl	_hint, %eax
	movl	$1, 4(%eax)
	jmp	L336
L342:
	movl	_location, %eax
	cmpl	$0, 8(%eax)
	jne	L343
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	cmpl	$256, _i
	je	L344
	cmpl	$261, _i
	jne	L346
	movl	$LC18, %eax
	jmp	L345
L346:
	movl	$LC19, %eax
	jmp	L345
L344:
	movl	$LC20, %eax
L345:
	movl	%eax, 8(%esp)
	call	*_error
	movl	$125, (%esp)
	jmp	L369
L343:
	movl	$126, %ebx
	cmpl	$262, _i
	jne	L348
	cmpl	$0, _in_abs_seg
	jne	L349
	movl	_location, %eax
	movl	(%eax), %eax
	jmp	L350
L349:
	movl	_abs_seg, %eax
L350:
	movl	%eax, -12(%ebp)
	movl	$0, -16(%ebp)
	jmp	L351
L348:
	cmpl	$261, _i
	jne	L352
	cmpl	$0, _in_abs_seg
	jne	L353
	movl	_location, %eax
	movl	(%eax), %eax
	jmp	L354
L353:
	movl	_abs_seg, %eax
L354:
	movl	%eax, -12(%ebp)
	cmpl	$0, _in_abs_seg
	jne	L355
	movl	_location, %eax
	movl	4(%eax), %eax
	jmp	L356
L355:
	movl	_abs_offset, %eax
L356:
	movl	%eax, -16(%ebp)
	jmp	L351
L352:
	movl	_tokval, %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_labelfunc
	testl	%eax, %eax
	jne	L358
	cmpl	$2, %esi
	jne	L359
	movl	$1, (%esp)
	movl	$LC21, 4(%esp)
	jmp	L374
L359:
	cmpl	$1, %esi
	jne	L361
	movl	$1, (%esp)
	movl	$LC22, 4(%esp)
L374:
	movl	_tokval, %eax
	movl	12(%eax), %eax
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L371
L361:
	cmpl	$0, _opflags
	je	L363
	movl	_opflags, %eax
	orl	$1, (%eax)
L363:
	movl	$125, %ebx
	movl	$-1, -12(%ebp)
	movl	$1, -16(%ebp)
L358:
	cmpl	$0, _opflags
	je	L351
	movl	_tokval, %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
	call	_is_extern
	testl	%eax, %eax
	je	L351
	movl	_opflags, %eax
	orl	$2, (%eax)
L351:
	movl	%ebx, (%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_addtotemp
	cmpl	$-1, -12(%ebp)
	je	L336
	movl	-12(%ebp), %eax
	subl	$-128, %eax
	movl	%eax, (%esp)
L369:
	movl	$1, 4(%esp)
L370:
	call	_addtotemp
L336:
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	call	_finishtemp
	jmp	L313
L334:
	movl	$1, (%esp)
	movl	$LC23, 4(%esp)
L373:
	call	*_error
L371:
	movl	$0, %eax
L313:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _eval_global_info
	.def	_eval_global_info;	.scl	2;	.type	32;	.endef
_eval_global_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, _outfmt
	movl	12(%ebp), %eax
	movl	%eax, _labelfunc
	movl	16(%ebp), %eax
	movl	%eax, _location
	popl	%ebp
	ret
	.align 32
LC24:
	.ascii "invalid right-hand operand to WRT\0"
	.align 2
.globl _evaluate
	.def	_evaluate;	.scl	2;	.type	32;	.endef
_evaluate:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	24(%ebp), %esi
	movl	32(%ebp), %eax
	movl	$0, %edi
	movl	%eax, _hint
	testl	%eax, %eax
	je	L377
	movl	$0, 4(%eax)
L377:
	testl	$256, %esi
	je	L378
	andl	$-257, %esi
	movl	$_rexp0, _bexpr
	jmp	L379
L378:
	movl	$_expr0, _bexpr
L379:
	movl	%ebx, _scan
	movl	%ecx, _scpriv
	movl	%edx, _tokval
	movl	28(%ebp), %eax
	movl	%eax, _error
	movl	20(%ebp), %eax
	movl	%eax, _opflags
	cmpl	$-1, (%edx)
	jne	L380
	movl	%ecx, (%esp)
	movl	%edx, 4(%esp)
	call	*%ebx
	jmp	L398
L380:
	movl	_tokval, %eax
	movl	(%eax), %eax
L398:
	movl	%eax, _i
	cmpl	$0, _ntempexprs
	je	L397
L385:
	movl	_ntempexprs, %eax
	decl	%eax
	movl	%eax, _ntempexprs
	movl	_tempexprs, %edx
	movl	(%edx,%eax,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	cmpl	$0, _ntempexprs
	jne	L385
L397:
	movl	%esi, (%esp)
	call	*_bexpr
	movl	%eax, %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L376
	cmpl	$276, _i
	jne	L387
	movl	_scpriv, %eax
	movl	%eax, (%esp)
	movl	_tokval, %eax
	movl	%eax, 4(%esp)
	call	*_scan
	movl	%eax, _i
	movl	%esi, (%esp)
	call	_expr6
	movl	%eax, %edi
	movl	$0, %eax
	testl	%edi, %edi
	je	L376
L387:
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	call	_scalar_mult
	movl	%eax, %ebx
	testl	%edi, %edi
	je	L389
	movl	%edi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L390
	call	_unknown_expr
	jmp	L391
L390:
	call	_begintemp
	movl	%edi, (%esp)
	call	_is_reloc
	testl	%eax, %eax
	je	L399
	movl	%edi, (%esp)
	call	_reloc_seg
	cmpl	$-1, %eax
	jne	L393
	movl	%edi, (%esp)
	call	_reloc_value
	orl	$1073741824, %eax
	jmp	L394
L393:
	testl	$1073741824, %eax
	jne	L394
	testl	$1, %eax
	jne	L394
	testl	%esi, %esi
	je	L394
L399:
	movl	$1, (%esp)
	movl	$LC24, 4(%esp)
	call	*_error
	movl	$0, %eax
	jmp	L376
L394:
	movl	$127, (%esp)
	movl	%eax, 4(%esp)
	call	_addtotemp
	call	_finishtemp
L391:
	movl	%ebx, (%esp)
	movl	%eax, 4(%esp)
	call	_add_vectors
	movl	%eax, %ebx
L389:
	movl	%ebx, %eax
L376:
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
.lcomm _scan,16
.lcomm _error,16
.lcomm _labelfunc,16
.lcomm _outfmt,16
.lcomm _ntempexprs,16
.lcomm _tempexpr,16
.lcomm _ntempexpr,16
.lcomm _tempexpr_size,16
.lcomm _tokval,16
.lcomm _i,16
.lcomm _scpriv,16
.lcomm _location,16
.lcomm _opflags,16
.lcomm _hint,16
.lcomm _bexpr,16
	.def	_is_extern;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_just_unknown;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_reloc_seg;	.scl	2;	.type	32;	.endef
	.def	_is_reloc;	.scl	2;	.type	32;	.endef
	.def	_is_unknown;	.scl	2;	.type	32;	.endef
	.def	_is_really_simple;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
