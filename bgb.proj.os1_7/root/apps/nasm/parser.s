	.file	"parser.c"
	.text
	.align 32
_reg_flags:
	.long	0
	.long	2101249
	.long	2166785
	.long	2166786
	.long	2101249
	.long	2101249
	.long	2101250
	.long	2101250
	.long	2101249
	.long	2232321
	.long	135270404
	.long	135270404
	.long	135270404
	.long	135270404
	.long	135270404
	.long	135270404
	.long	135270404
	.long	135270404
	.long	17305602
	.long	2232322
	.long	2101249
	.long	2101250
	.long	2363393
	.long	269488132
	.long	269488132
	.long	269488132
	.long	269488132
	.long	269488132
	.long	269488132
	.long	269488132
	.long	269488132
	.long	34082818
	.long	2363394
	.long	2166788
	.long	2101252
	.long	2101252
	.long	2232324
	.long	2101252
	.long	2363396
	.long	34082818
	.long	2101252
	.long	2101252
	.long	67637250
	.long	67637250
	.long	2101256
	.long	2101256
	.long	2101256
	.long	2101256
	.long	2101256
	.long	2101256
	.long	2101256
	.long	2101256
	.long	134746114
	.long	134746114
	.long	2101250
	.long	2101250
	.long	34082818
	.long	16779264
	.long	16777216
	.long	16777216
	.long	16777216
	.long	16777216
	.long	16777216
	.long	16777216
	.long	16777216
	.long	537923588
	.long	537923588
	.long	537923588
	.long	537923588
	.long	537923588
	.long	537923588
	.long	537923588
	.long	537923588
	.long	2101264
	.long	2101264
	.long	2101264
	.long	2101264
	.long	2101264
	.long	2101264
	.long	2101264
	.long	2101264
	.align 2
.globl _parser_global_info
	.def	_parser_global_info;	.scl	2;	.type	32;	.endef
_parser_global_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, _outfmt
	movl	12(%ebp), %eax
	movl	%eax, _location
	popl	%ebp
	ret
	.align 32
LC0:
	.ascii "label or instruction expected at start of line\0"
	.align 32
LC1:
	.ascii "label alone on a line without a colon might be in error\0"
	.align 32
LC2:
	.ascii "non-constant argument supplied to TIMES\0"
LC3:
	.ascii "TIMES value %d is negative\0"
	.align 32
LC4:
	.ascii "instruction has more than %d prefixes\0"
LC5:
	.ascii "parser: instruction expected\0"
	.align 32
LC6:
	.ascii "floating-point constant encountered in `D%c' instruction\0"
	.align 32
LC7:
	.ascii "operand %d: expression is not simple or relocatable\0"
	.align 32
LC8:
	.ascii "comma expected after operand %d\0"
LC9:
	.ascii "`incbin' expects a file name\0"
LC10:
	.ascii "`incbin': second parameter is\0"
LC12:
	.ascii "`incbin': third parameter is\0"
LC11:
	.ascii " non-numeric\0"
	.align 32
LC13:
	.ascii "`incbin': more than three parameters\0"
	.align 32
LC14:
	.ascii "no operand for data declaration\0"
	.align 32
LC15:
	.ascii "invalid operand size specification\0"
	.align 32
LC16:
	.ascii "invalid size specification in effective address\0"
	.align 32
LC17:
	.ascii "invalid use of FAR operand specifier\0"
LC18:
	.ascii "invalid segment override\0"
LC19:
	.ascii "parser: expecting ]\0"
LC20:
	.ascii "comma or end of line expected\0"
	.align 32
LC25:
	.ascii "beroset-p-650-invalid effective address\0"
	.align 32
LC28:
	.ascii "register size specification ignored\0"
	.align 32
LC21:
	.ascii "beroset-p-592-invalid effective address\0"
	.align 32
LC22:
	.ascii "beroset-p-603-invalid effective address\0"
	.align 32
LC23:
	.ascii "beroset-p-630-invalid effective address\0"
	.align 32
LC24:
	.ascii "beroset-p-637-invalid effective address\0"
	.align 32
LC26:
	.ascii "beroset-p-663-invalid effective address\0"
LC27:
	.ascii "invalid operand type\0"
	.align 2
.globl _parse_line
	.def	_parse_line;	.scl	2;	.type	32;	.endef
_parse_line:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	16(%ebp), %edi
	movl	20(%ebp), %ebx
	movl	$0, 192(%edi)
	movl	%ebx, _error
	call	_stdscan_reset
	movl	12(%ebp), %eax
	movl	%eax, _stdscan_bufptr
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	movl	$0, (%edi)
	movl	$0, 180(%edi)
	movl	$0, 32(%edi)
	cmpl	$0, _i
	je	L283
	cmpl	$256, _i
	je	L252
	cmpl	$259, _i
	je	L4
	cmpl	$264, _i
	je	L4
	cmpl	$258, _i
	jne	L5
	movl	_tokval+4, %eax
	movl	_reg_flags(,%eax,4), %eax
	notl	%eax
	testl	$528386, %eax
	je	L4
L5:
	movl	$1, (%esp)
	movl	$LC0, 4(%esp)
	jmp	L284
L4:
	cmpl	$256, _i
	jne	L6
L252:
	movl	_tokval+12, %eax
	movl	%eax, (%edi)
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	cmpl	$58, %eax
	jne	L7
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	jmp	L8
L7:
	cmpl	$0, _i
	jne	L8
	movl	$832, (%esp)
	movl	$LC1, 4(%esp)
	call	*_error
L8:
	cmpl	$259, _i
	jne	L11
	cmpl	$119, _tokval+4
	je	L6
L11:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	cmpl	$0, _in_abs_seg
	jne	L12
	movl	_location, %eax
	movl	(%eax), %eax
	jmp	L13
L12:
	movl	_abs_seg, %eax
L13:
	movl	%eax, 4(%esp)
	movl	_location, %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$1, 16(%esp)
	movl	$0, 20(%esp)
	movl	_outfmt, %eax
	movl	%eax, 24(%esp)
	movl	%ebx, 28(%esp)
	call	*28(%ebp)
L6:
	cmpl	$0, _i
	je	L283
	movl	$0, 20(%edi)
	jmp	L285
L265:
	movl	_tokval+4, %eax
	movl	_reg_flags(,%eax,4), %eax
	notl	%eax
	testl	$528386, %eax
	jne	L16
	cmpl	$264, _i
	jne	L19
L253:
	cmpl	$91, _tokval+4
	jne	L19
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	movl	$_tokval, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass0, %eax
	movl	%eax, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	*24(%ebp)
	movl	%eax, %ebx
	movl	_tokval, %eax
	movl	%eax, _i
	testl	%ebx, %ebx
	je	L283
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L21
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*_error
L285:
	movl	$1, 188(%edi)
	jmp	L15
L21:
	movl	4(%ebx), %eax
	movl	%eax, 188(%edi)
	cmpl	$0, 4(%ebx)
	jns	L15
	movl	$1, (%esp)
	movl	$LC3, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$0, 188(%edi)
	jmp	L15
L19:
	cmpl	$4, 20(%edi)
	jne	L25
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	movl	$4, 8(%esp)
	call	*_error
	jmp	L26
L25:
	movl	20(%edi), %eax
	movl	_tokval+4, %edx
	movl	%edx, 4(%edi,%eax,4)
	incl	%eax
	movl	%eax, 20(%edi)
L26:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
L15:
	cmpl	$264, _i
	je	L253
	cmpl	$258, _i
	je	L265
L16:
	cmpl	$259, _i
	je	L28
	cmpl	$0, 20(%edi)
	jle	L29
	cmpl	$0, _i
	jne	L29
	movl	$472, 24(%edi)
	movl	$1, 32(%edi)
	movl	$8192, 36(%edi)
	movl	$0, 68(%edi)
	movl	$-1, 72(%edi)
	movl	$-1, 64(%edi)
	jmp	L233
L29:
	movl	$1, (%esp)
	movl	$LC5, 4(%esp)
	jmp	L284
L28:
	movl	_tokval+4, %eax
	movl	%eax, 24(%edi)
	movl	_tokval+8, %eax
	movl	%eax, 28(%edi)
	cmpl	$472, 24(%edi)
	je	L32
	cmpl	$476, 24(%edi)
	je	L32
	cmpl	$473, 24(%edi)
	je	L32
	cmpl	$474, 24(%edi)
	je	L32
	cmpl	$475, 24(%edi)
	je	L32
	cmpl	$119, 24(%edi)
	je	L32
	cmpl	$233, 24(%edi)
	jne	L31
L32:
	movl	_pass0, %eax
	jmp	L267
L31:
	cmpl	$2, 8(%ebp)
	sete	%al
	movzbl	%al, %eax
	addl	%eax, %eax
L267:
	movl	%eax, -32(%ebp)
	cmpl	$106, 24(%edi)
	je	L37
	cmpl	$116, 24(%edi)
	je	L37
	cmpl	$107, 24(%edi)
	je	L37
	cmpl	$114, 24(%edi)
	je	L37
	cmpl	$115, 24(%edi)
	je	L37
	cmpl	$233, 24(%edi)
	jne	L36
L37:
	leal	180(%edi), %edx
	movl	%edx, -36(%ebp)
	movl	$0, -40(%ebp)
	movl	$0, 184(%edi)
L67:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	testl	%eax, %eax
	je	L39
	movl	-36(%ebp), %ebx
	movl	$28, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, %esi
	movl	%eax, -36(%ebp)
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	incl	-40(%ebp)
	cmpl	$257, _i
	jne	L42
	cmpl	$0, _tokval+12
	je	L42
	call	_is_comma_next
	testl	%eax, %eax
	je	L42
	movl	$1, 4(%esi)
	movl	_tokval+12, %eax
	movl	%eax, 8(%esi)
	movl	_tokval+8, %eax
	movl	%eax, 12(%esi)
	jmp	L58
L42:
	cmpl	$277, _i
	jne	L45
	call	_is_comma_next
	testl	%eax, %eax
	jne	L44
L45:
	cmpl	$45, _i
	jne	L43
L44:
	movl	$1, -44(%ebp)
	cmpl	$45, _i
	jne	L46
	movl	_stdscan_bufptr, %eax
	movl	%eax, -48(%ebp)
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	movl	$-1, -44(%ebp)
	cmpl	$277, %eax
	jne	L48
	call	_is_comma_next
	testl	%eax, %eax
	jne	L46
L48:
	movl	-48(%ebp), %edx
	movl	%edx, _stdscan_bufptr
	movl	$45, _tokval
	movl	$45, _i
L46:
	cmpl	$277, _i
	jne	L43
	movl	$1, 4(%esi)
	movl	$1, 184(%edi)
	cmpl	$107, 24(%edi)
	jne	L50
	movl	$4, 12(%esi)
	jmp	L51
L50:
	cmpl	$114, 24(%edi)
	jne	L52
	movl	$8, 12(%esi)
	jmp	L51
L52:
	cmpl	$115, 24(%edi)
	jne	L54
	movl	$10, 12(%esi)
	jmp	L51
L54:
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	cmpl	$116, 24(%edi)
	jne	L56
	movl	$87, %eax
	jmp	L57
L56:
	movl	$66, %eax
L57:
	movl	%eax, 8(%esp)
	call	*_error
	movl	$0, 12(%esi)
L51:
	movl	%esi, (%esp)
	movl	12(%esi), %eax
	addl	$28, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, %esi
	movl	%eax, -36(%ebp)
	movl	%eax, (%ebx)
	leal	28(%eax), %eax
	movl	%eax, 8(%esi)
	cmpl	$3, 12(%esi)
	jle	L59
	movl	_tokval+12, %eax
	movl	%eax, (%esp)
	movl	-44(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, 8(%esp)
	movl	12(%esi), %eax
	movl	%eax, 12(%esp)
	movl	_error, %eax
	movl	%eax, 16(%esp)
	call	_float_const
	testl	%eax, %eax
	jne	L58
L59:
	movl	$0, 4(%esi)
L58:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	jmp	L67
L43:
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	movl	$_tokval, 8(%esp)
	movl	$0, 12(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	*24(%ebp)
	movl	%eax, %ebx
	movl	_tokval, %eax
	movl	%eax, _i
	testl	%ebx, %ebx
	je	L283
	movl	%ebx, (%esp)
	call	_is_unknown
	testl	%eax, %eax
	je	L61
	movl	$2, 4(%esi)
	movl	$0, 20(%esi)
	movl	$-1, 24(%esi)
	movl	$-1, 16(%esi)
	jmp	L62
L61:
	movl	%ebx, (%esp)
	call	_is_reloc
	testl	%eax, %eax
	je	L63
	movl	$2, 4(%esi)
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, 20(%esi)
	movl	%ebx, (%esp)
	call	_reloc_seg
	movl	%eax, 16(%esi)
	movl	%ebx, (%esp)
	call	_reloc_wrt
	movl	%eax, 24(%esi)
	jmp	L62
L63:
	movl	$1, (%esp)
	movl	$LC7, 4(%esp)
	movl	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_error
L62:
	cmpl	$0, _i
	je	L39
	cmpl	$44, _i
	je	L67
	movl	$1, (%esp)
	movl	$LC8, 4(%esp)
	movl	-40(%ebp), %edx
	movl	%edx, 8(%esp)
	jmp	L286
L39:
	cmpl	$233, 24(%edi)
	jne	L68
	cmpl	$0, 180(%edi)
	je	L70
	movl	180(%edi), %eax
	cmpl	$1, 4(%eax)
	je	L69
L70:
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	jmp	L284
L69:
	movl	180(%edi), %eax
	cmpl	$0, (%eax)
	je	L72
	movl	(%eax), %eax
	cmpl	$2, 4(%eax)
	je	L72
	movl	$1, (%esp)
	movl	$LC10, 4(%esp)
	jmp	L268
L72:
	movl	180(%edi), %eax
	cmpl	$0, (%eax)
	je	L74
	movl	(%eax), %eax
	cmpl	$0, (%eax)
	je	L74
	movl	(%eax), %eax
	cmpl	$2, 4(%eax)
	je	L74
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
L268:
	movl	$LC11, 8(%esp)
L286:
	call	*_error
	jmp	L283
L74:
	movl	180(%edi), %eax
	cmpl	$0, (%eax)
	je	L233
	movl	(%eax), %eax
	cmpl	$0, (%eax)
	je	L233
	movl	(%eax), %eax
	cmpl	$0, (%eax)
	je	L233
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
	jmp	L284
L68:
	cmpl	$0, -40(%ebp)
	jne	L79
	movl	$64, (%esp)
	movl	$LC14, 4(%esp)
	call	*_error
	jmp	L233
L79:
	movl	-40(%ebp), %eax
	movl	%eax, 32(%edi)
	jmp	L233
L36:
	movl	$0, -28(%ebp)
L228:
	movl	$0, %esi
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	leal	(%edi,%eax), %ebx
	movl	$0, 40(%ebx)
	movl	$0, 76(%ebx)
	movl	$0, 80(%ebx)
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	testl	%eax, %eax
	je	L82
	movl	$0, 36(%ebx)
	cmpl	$263, _i
	jne	L244
L108:
	cmpl	$11, _tokval+4
	ja	L106
	movl	_tokval+4, %eax
	jmp	*L107(,%eax,4)
	.align 4
	.align 4
L107:
	.long	L90
	.long	L95
	.long	L103
	.long	L95
	.long	L104
	.long	L106
	.long	L97
	.long	L105
	.long	L102
	.long	L101
	.long	L99
	.long	L92
L90:
	testl	%esi, %esi
	jne	L100
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$1, 36(%edi,%eax)
	jmp	L100
L92:
	testl	%esi, %esi
	jne	L100
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$2, 36(%edi,%eax)
	jmp	L100
L95:
	testl	%esi, %esi
	jne	L100
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$4, 36(%edi,%eax)
	jmp	L100
L97:
	testl	%esi, %esi
	jne	L100
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$8, 36(%edi,%eax)
	jmp	L100
L99:
	testl	%esi, %esi
	jne	L100
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$16, 36(%edi,%eax)
L100:
	movl	$1, %esi
	jmp	L89
L101:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$256, 36(%edi,%eax)
	jmp	L89
L102:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$1024, 36(%edi,%eax)
	jmp	L89
L103:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$32, 36(%edi,%eax)
	jmp	L89
L104:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$64, 36(%edi,%eax)
	jmp	L89
L105:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$128, 36(%edi,%eax)
	jmp	L89
L106:
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
	call	*_error
L89:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	cmpl	$263, %eax
	je	L108
L244:
	cmpl	$91, _i
	je	L110
	cmpl	$38, _i
	jne	L109
L110:
	movl	$1, -52(%ebp)
	cmpl	$91, _i
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -56(%ebp)
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	cmpl	$263, %eax
	jne	L131
	cmpl	$0, _tasm_compatible_mode
	je	L112
	cmpl	$11, _tokval+4
	ja	L120
	movl	_tokval+4, %eax
	jmp	*L121(,%eax,4)
	.align 4
	.align 4
L121:
	.long	L114
	.long	L117
	.long	L120
	.long	L117
	.long	L120
	.long	L120
	.long	L118
	.long	L120
	.long	L120
	.long	L120
	.long	L119
	.long	L115
L114:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$1, 36(%edi,%eax)
	jmp	L122
L115:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$2, 36(%edi,%eax)
	jmp	L122
L117:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$4, 36(%edi,%eax)
	jmp	L122
L118:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$8, 36(%edi,%eax)
	jmp	L122
L119:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$16, 36(%edi,%eax)
	jmp	L122
L120:
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
	jmp	L271
L112:
	cmpl	$11, _tokval+4
	ja	L129
	movl	_tokval+4, %eax
	jmp	*L130(,%eax,4)
	.align 4
	.align 4
L130:
	.long	L125
	.long	L128
	.long	L129
	.long	L128
	.long	L129
	.long	L124
	.long	L129
	.long	L129
	.long	L129
	.long	L129
	.long	L129
	.long	L126
L124:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$4, 76(%edi,%eax)
	jmp	L122
L125:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$1, 76(%edi,%eax)
	jmp	L122
L126:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	$16, 40(%eax)
	jmp	L270
L128:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	$32, 40(%eax)
L270:
	orl	$2, 76(%eax)
	jmp	L122
L129:
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
L271:
	call	*_error
L122:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	jmp	L131
L109:
	movl	$0, -52(%ebp)
	movl	$0, -56(%ebp)
L131:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	testb	$32, 36(%edi,%eax)
	je	L132
	cmpl	$0, -52(%ebp)
	jne	L132
	cmpl	$250, 24(%edi)
	je	L132
	cmpl	$26, 24(%edi)
	je	L132
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_error
L132:
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	movl	$_tokval, 8(%esp)
	movl	-28(%ebp), %eax
	leal	(%eax,%eax,2), %ebx
	sall	$4, %ebx
	leal	(%ebx,%edi), %ebx
	leal	80(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 24(%esp)
	call	*24(%ebp)
	movl	%eax, %esi
	movl	_tokval, %eax
	movl	%eax, _i
	testb	$1, 80(%ebx)
	je	L133
	movl	$1, 192(%edi)
L133:
	testl	%esi, %esi
	je	L283
	cmpl	$58, _i
	jne	L135
	cmpl	$0, -52(%ebp)
	je	L151
	cmpl	$0, 8(%esi)
	jne	L137
	cmpl	$1, 4(%esi)
	jne	L137
	movl	(%esi), %eax
	movl	_reg_flags(,%eax,4), %eax
	notl	%eax
	testl	$528386, %eax
	je	L136
L137:
	movl	$1, (%esp)
	movl	$LC18, 4(%esp)
	call	*_error
	jmp	L138
L136:
	cmpl	$4, 20(%edi)
	jne	L139
	movl	$1, (%esp)
	movl	$LC4, 4(%esp)
	movl	$4, 8(%esp)
	call	*_error
	jmp	L138
L139:
	movl	20(%edi), %eax
	movl	(%esi), %edx
	movl	%edx, 4(%edi,%eax,4)
	incl	%eax
	movl	%eax, 20(%edi)
L138:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	cmpl	$263, %eax
	jne	L141
	movl	_tokval+4, %eax
	cmpl	$3, %eax
	je	L145
	cmpl	$3, %eax
	jg	L148
	cmpl	$1, %eax
	je	L145
	jmp	L146
L148:
	cmpl	$11, %eax
	jne	L146
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	$16, 40(%edi,%eax)
	jmp	L142
L145:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	$32, 40(%edi,%eax)
	jmp	L142
L146:
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	call	*_error
L142:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
L141:
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	movl	$_tokval, 8(%esp)
	movl	-28(%ebp), %eax
	leal	(%eax,%eax,2), %ebx
	sall	$4, %ebx
	leal	(%ebx,%edi), %ebx
	leal	80(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 24(%esp)
	call	*24(%ebp)
	movl	%eax, %esi
	movl	_tokval, %eax
	movl	%eax, _i
	testb	$1, 80(%ebx)
	je	L149
	movl	$1, 192(%edi)
L149:
	testl	%esi, %esi
	je	L283
L135:
	cmpl	$0, -52(%ebp)
	je	L151
	cmpl	$0, -56(%ebp)
	je	L151
	cmpl	$93, _i
	je	L152
	movl	$1, (%esp)
	movl	$LC19, 4(%esp)
	call	*_error
L153:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	testl	%eax, %eax
	je	L159
	cmpl	$44, %eax
	jne	L153
	jmp	L159
L152:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	jmp	L159
L151:
	cmpl	$0, _i
	je	L160
	cmpl	$44, _i
	je	L160
	cmpl	$58, _i
	je	L254
	movl	$1, (%esp)
	movl	$LC20, 4(%esp)
	call	*_error
L161:
	movl	$0, (%esp)
	movl	$_tokval, 4(%esp)
	call	_stdscan
	movl	%eax, _i
	testl	%eax, %eax
	je	L159
	cmpl	$44, %eax
	jne	L161
	jmp	L159
L160:
	cmpl	$58, _i
	jne	L159
L254:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$512, 36(%edi,%eax)
L159:
	cmpl	$0, -52(%ebp)
	je	L168
	movl	%esi, %ecx
	movl	$-1, -60(%ebp)
	movl	$-1, %ebx
	movl	$0, -64(%ebp)
	movl	$0, -68(%ebp)
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	-24(%ebp), %edx
	movl	%edx, 56(%eax)
	movl	-20(%ebp), %edx
	movl	%edx, 60(%eax)
	cmpl	$0, (%esi)
	je	L177
	cmpl	$124, (%esi)
	jg	L169
	cmpl	$1, 4(%esi)
	jne	L170
	movl	(%esi), %ebx
	jmp	L171
L170:
	movl	(%esi), %eax
	movl	%eax, -60(%ebp)
	movl	4(%esi), %edx
	movl	%edx, -64(%ebp)
L171:
	addl	$8, %ecx
L169:
	cmpl	$0, (%ecx)
	je	L177
	cmpl	$124, (%ecx)
	jg	L172
	cmpl	$-1, %ebx
	je	L173
	movl	(%ecx), %eax
	movl	%eax, -60(%ebp)
	movl	4(%ecx), %edx
	movl	%edx, -64(%ebp)
	jmp	L174
L173:
	cmpl	$1, 4(%ecx)
	jne	L259
	movl	(%ecx), %ebx
L174:
	addl	$8, %ecx
L172:
	cmpl	$0, (%ecx)
	je	L177
	cmpl	$124, (%ecx)
	jle	L260
	cmpl	$125, (%ecx)
	jne	L180
	movl	$0, -68(%ebp)
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	$-1, 72(%eax)
	movl	$-1, 64(%eax)
	cmpl	$0, (%ecx)
	je	L205
L184:
	addl	$8, %ecx
	cmpl	$0, (%ecx)
	je	L205
	jmp	L184
L180:
	cmpl	$126, (%ecx)
	jne	L186
	movl	4(%ecx), %eax
	movl	%eax, -68(%ebp)
	addl	$8, %ecx
L186:
	cmpl	$127, (%ecx)
	jne	L187
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	4(%ecx), %edx
	movl	%edx, 72(%edi,%eax)
	addl	$8, %ecx
	jmp	L188
L187:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	$-1, 72(%edi,%eax)
L188:
	cmpl	$0, (%ecx)
	je	L196
	cmpl	$127, (%ecx)
	jle	L261
	cmpl	$0, (%ecx)
	je	L196
	cmpl	$0, 4(%ecx)
	jne	L191
L194:
	addl	$8, %ecx
	cmpl	$0, (%ecx)
	je	L196
	cmpl	$0, 4(%ecx)
	je	L194
L191:
	cmpl	$0, (%ecx)
	je	L196
	cmpl	$1, 4(%ecx)
	jne	L262
	cmpl	$0, (%ecx)
	je	L196
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	(%ecx), %edx
	addl	$-128, %edx
	movl	%edx, 64(%edi,%eax)
	addl	$8, %ecx
	jmp	L197
L196:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	$-1, 64(%edi,%eax)
L197:
	cmpl	$0, (%ecx)
	je	L205
	cmpl	$0, 4(%ecx)
	jne	L199
L202:
	addl	$8, %ecx
	cmpl	$0, (%ecx)
	je	L205
	cmpl	$0, 4(%ecx)
	je	L202
L199:
	cmpl	$0, (%ecx)
	je	L205
	movl	$1, (%esp)
	movl	$LC25, 4(%esp)
	jmp	L284
L177:
	movl	$0, -68(%ebp)
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	$-1, 72(%eax)
	movl	$-1, 64(%eax)
	cmpl	$0, (%ecx)
	jne	L263
L205:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$2113536, 36(%edi,%eax)
	cmpl	$-1, %ebx
	jne	L206
	cmpl	$-1, -60(%ebp)
	je	L207
	cmpl	$0, -64(%ebp)
	jne	L206
L207:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	orl	$6307840, 36(%edi,%eax)
L206:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	%ebx, 44(%eax)
	movl	-60(%ebp), %edx
	movl	%edx, 48(%eax)
	movl	-64(%ebp), %edx
	movl	%edx, 52(%eax)
	movl	-68(%ebp), %edx
	movl	%edx, 68(%eax)
	jmp	L83
L168:
	movl	%esi, (%esp)
	call	_is_just_unknown
	testl	%eax, %eax
	je	L209
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	orl	$8192, 36(%eax)
	movl	$0, 68(%eax)
	movl	$-1, 64(%eax)
	movl	$-1, 72(%eax)
	jmp	L83
L209:
	movl	%esi, (%esp)
	call	_is_reloc
	testl	%eax, %eax
	je	L211
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	leal	(%edi,%eax), %ebx
	orl	$8192, 36(%ebx)
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, 68(%ebx)
	movl	%esi, (%esp)
	call	_reloc_seg
	movl	%eax, 64(%ebx)
	movl	%esi, (%esp)
	call	_reloc_wrt
	movl	%eax, 72(%ebx)
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	je	L83
	movl	%esi, (%esp)
	call	_reloc_value
	cmpl	$1, %eax
	jne	L213
	orl	$8396800, 36(%ebx)
L213:
	cmpl	$0, _optimizing
	js	L83
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	leal	(%edi,%eax), %ebx
	testb	$4, 37(%ebx)
	jne	L83
	movl	%esi, (%esp)
	call	_reloc_value
	cmpl	$-128, %eax
	jl	L83
	movl	%esi, (%esp)
	call	_reloc_value
	cmpl	$127, %eax
	jg	L83
	orl	$1073750016, 36(%ebx)
	jmp	L83
L211:
	cmpl	$125, (%esi)
	jg	L264
	cmpl	$1, 4(%esi)
	jne	L264
	movl	$1, _i
	cmpl	$0, 8(%esi)
	je	L249
L224:
	movl	_i, %eax
	cmpl	$0, 4(%esi,%eax,8)
	jne	L264
	incl	%eax
	movl	%eax, _i
	cmpl	$0, (%esi,%eax,8)
	jne	L224
L249:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	36(%edi,%eax), %eax
	testl	$-257, %eax
	je	L225
	andl	$255, %eax
	movl	%eax, _i
	jmp	L226
L225:
	movl	$0, _i
L226:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	movl	36(%eax), %edx
	andl	$256, %edx
	orl	$4096, %edx
	movl	%edx, 36(%eax)
	movl	(%esi), %ecx
	orl	_reg_flags(,%ecx,4), %edx
	movl	%edx, %ecx
	movl	%edx, 36(%eax)
	movl	(%esi), %edx
	movl	%edx, 44(%eax)
	cmpl	$0, _i
	je	L83
	movzbl	%cl,%eax
	cmpl	_i, %eax
	je	L83
	movl	$64, (%esp)
	movl	$LC28, 4(%esp)
	call	*_error
L83:
	incl	-28(%ebp)
	cmpl	$2, -28(%ebp)
	jle	L228
L82:
	movl	-28(%ebp), %eax
	movl	%eax, 32(%edi)
	cmpl	$2, %eax
	jg	L251
L232:
	movl	-28(%ebp), %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	$0, 36(%edi,%eax)
	incl	%edx
	movl	%edx, -28(%ebp)
	cmpl	$2, %edx
	jle	L232
L251:
	movl	24(%edi), %eax
	cmpl	$474, %eax
	je	L236
	cmpl	$474, %eax
	jg	L240
	cmpl	$473, %eax
	je	L235
	jmp	L233
L240:
	cmpl	$475, %eax
	je	L237
	cmpl	$476, %eax
	jne	L233
	movl	$472, 24(%edi)
	sall	68(%edi)
	jmp	L233
L235:
	movl	$472, 24(%edi)
	sall	$2, 68(%edi)
	jmp	L233
L236:
	movl	$472, 24(%edi)
	sall	$3, 68(%edi)
	jmp	L233
L259:
	movl	$1, (%esp)
	movl	$LC21, 4(%esp)
	jmp	L284
L260:
	movl	$1, (%esp)
	movl	$LC22, 4(%esp)
	jmp	L284
L261:
	movl	$1, (%esp)
	movl	$LC23, 4(%esp)
	jmp	L284
L262:
	movl	$1, (%esp)
	movl	$LC24, 4(%esp)
	jmp	L284
L263:
	movl	$1, (%esp)
	movl	$LC26, 4(%esp)
	jmp	L284
L264:
	movl	$1, (%esp)
	movl	$LC27, 4(%esp)
L284:
	call	*_error
L283:
	movl	$-1, 24(%edi)
	jmp	L233
L237:
	movl	$472, 24(%edi)
	movl	68(%edi), %eax
	leal	(%eax,%eax,4), %eax
	addl	%eax, %eax
	movl	%eax, 68(%edi)
L233:
	movl	%edi, %eax
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_is_comma_next;	.scl	3;	.type	32;	.endef
_is_comma_next:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -4(%ebp)
	movl	_stdscan_bufptr, %ebx
	movl	$0, (%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_stdscan
	movl	%ebx, _stdscan_bufptr
	movl	$0, %edx
	cmpl	$44, %eax
	je	L289
	cmpl	$59, %eax
	je	L289
	testl	%eax, %eax
	jne	L288
L289:
	movl	$1, %edx
L288:
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _cleanup_insn
	.def	_cleanup_insn;	.scl	2;	.type	32;	.endef
_cleanup_insn:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %ebx
	cmpl	$0, 180(%ebx)
	je	L296
L294:
	movl	180(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, 180(%ebx)
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, 180(%ebx)
	jne	L294
L296:
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _i,16
.lcomm _tokval,16
.lcomm _error,16
.lcomm _outfmt,16
.lcomm _location,16
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_is_just_unknown;	.scl	2;	.type	32;	.endef
	.def	_reloc_wrt;	.scl	2;	.type	32;	.endef
	.def	_reloc_seg;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_reloc;	.scl	2;	.type	32;	.endef
	.def	_is_unknown;	.scl	2;	.type	32;	.endef
	.def	_float_const;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
