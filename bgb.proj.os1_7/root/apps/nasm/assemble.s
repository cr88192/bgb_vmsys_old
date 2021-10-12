	.file	"assemble.c"
	.data
	.align 4
_lineno.0:
	.long	0
	.align 4
_lnfname.1:
	.long	0
	.text
	.align 2
	.def	_out;	.scl	3;	.type	32;	.endef
_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	20(%ebp), %ebx
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$268435456, %eax
	jne	L2
	cmpl	$-1, 24(%ebp)
	jne	L22
	cmpl	$-1, 28(%ebp)
	jne	L22
	leal	-16(%ebp), %edi
	movl	%ebx, %eax
	andl	$268435455, %eax
	cmpl	$4, %eax
	jne	L6
	movzbl	(%esi), %eax
	movl	%edi, %edx
	movb	%al, -16(%ebp)
	incl	%edi
	movl	(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edi)
	incl	%edi
	movswl	2(%esi),%eax
	movb	%al, (%edi)
	movsbl	3(%esi),%eax
	movb	%al, 1(%edi)
	movl	%ecx, (%esp)
	movl	%edx, 4(%esp)
	movl	$4, 8(%esp)
	jmp	L25
L6:
	movzbl	(%esi), %eax
	movb	%al, (%edi)
	movl	(%esi), %eax
	sarl	$8, %eax
	movb	%al, 1(%edi)
	movl	%ecx, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$2, 8(%esp)
	jmp	L25
L2:
	testl	$-268435456, %ebx
	je	L22
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	jne	L19
	movl	%ecx, (%esp)
	movl	$0, 4(%esp)
	jmp	L24
L19:
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$536870912, %eax
	je	L22
	cmpl	$805306368, %eax
	jne	L16
L22:
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
L24:
	movl	%ebx, 8(%esp)
L25:
	movl	_list, %eax
	call	*8(%eax)
L16:
	movl	$_lineno.0, (%esp)
	movl	$_lnfname.1, 4(%esp)
	call	_src_get
	testl	%eax, %eax
	je	L23
	movl	_outfmt, %eax
	movl	16(%eax), %edx
	movl	_lnfname.1, %eax
	movl	%eax, (%esp)
	movl	_lineno.0, %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*12(%edx)
L23:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	28(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	_outfmt, %eax
	call	*32(%eax)
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_jmp_match;	.scl	3;	.type	32;	.endef
_jmp_match:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	20(%ebp), %ebx
	movl	24(%ebp), %esi
	movzbl	(%esi), %ecx
	movb	%cl, %al
	addb	$8, %al
	movl	$0, %edx
	cmpb	$1, %al
	ja	L26
	testb	$1, 80(%ebx)
	je	L28
	cmpl	$0, _optimizing
	js	L30
	testb	$4, 37(%ebx)
	je	L29
L30:
	movl	$1, %edx
	cmpb	$-8, %cl
	je	L26
L29:
	cmpl	$0, _pass0
	sete	%al
	jmp	L34
L28:
	movl	%edi, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%ebx, 12(%esp)
	movl	%esi, 16(%esp)
	call	_calcsize
	movl	%eax, %edx
	cmpl	%edi, 64(%ebx)
	je	L32
	movl	$0, %edx
	jmp	L26
L32:
	movl	68(%ebx), %eax
	subl	12(%ebp), %eax
	subl	%edx, %eax
	leal	128(%eax), %eax
	cmpl	$255, %eax
	setbe	%al
L34:
	movzbl	%al, %edx
L26:
	movl	%edx, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
.lcomm _fname.2,256
.lcomm _buf.3,2048
	.align 32
LC0:
	.ascii "instruction->times < 0 (%ld) in assemble()\0"
LC1:
	.ascii "one-byte relocation attempted\0"
	.align 32
LC2:
	.ascii "integer supplied to a D%c instruction\0"
LC3:
	.ascii "\0\0\0\0\0\0\0\0\0"
LC4:
	.ascii "\0"
LC5:
	.ascii "rb\0"
	.align 32
LC6:
	.ascii "`incbin': unable to open file `%s'\0"
	.align 32
LC7:
	.ascii "`incbin': unable to seek on file `%s'\0"
	.align 32
LC8:
	.ascii "`incbin': unexpected EOF while reading file `%s'\0"
	.align 32
LC9:
	.ascii "errors made it through from pass one\0"
	.align 32
LC10:
	.ascii "segr6 and segr7 cannot be used as prefixes\0"
LC11:
	.ascii "invalid instruction prefix\0"
LC12:
	.ascii "operation size not specified\0"
LC13:
	.ascii "mismatch in operand sizes\0"
	.align 32
LC14:
	.ascii "no instruction for this cpu level\0"
	.align 32
LC15:
	.ascii "invalid combination of opcode and operands\0"
	.align 2
.globl _assemble
	.def	_assemble;	.scl	2;	.type	32;	.endef
_assemble:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	16(%ebp), %edi
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	$0, -24(%ebp)
	movl	32(%ebp), %edx
	movl	%edx, _errfunc
	movl	20(%ebp), %eax
	movl	%eax, _cpu
	movl	28(%ebp), %eax
	movl	%eax, _outfmt
	movl	36(%ebp), %eax
	movl	%eax, _list
	movl	24(%ebp), %eax
	movl	24(%eax), %edx
	cmpl	$114, %edx
	je	L41
	cmpl	$114, %edx
	jg	L45
	cmpl	$106, %edx
	je	L38
	cmpl	$106, %edx
	jg	L46
	movl	$0, %eax
	cmpl	$-1, %edx
	je	L35
	jmp	L36
L46:
	cmpl	$107, %edx
	je	L40
	jmp	L36
L45:
	cmpl	$115, %edx
	je	L42
	cmpl	$116, %edx
	je	L39
	jmp	L36
L38:
	movl	$1, -24(%ebp)
	jmp	L36
L39:
	movl	$2, -24(%ebp)
	jmp	L36
L40:
	movl	$4, -24(%ebp)
	jmp	L36
L41:
	movl	$8, -24(%ebp)
	jmp	L36
L42:
	movl	$10, -24(%ebp)
L36:
	cmpl	$0, -24(%ebp)
	je	L47
	movl	24(%ebp), %edx
	movl	188(%edx), %edi
	testl	%edi, %edi
	jns	L48
	movl	$3, (%esp)
	movl	$LC0, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_errfunc
L48:
	decl	%edi
	cmpl	$-1, %edi
	je	L152
L70:
	movl	24(%ebp), %eax
	movl	180(%eax), %ebx
	testl	%ebx, %ebx
	je	L154
L68:
	cmpl	$2, 4(%ebx)
	jne	L56
	cmpl	$1, -24(%ebp)
	jne	L57
	cmpl	$-1, 16(%ebx)
	je	L58
	movl	$1, (%esp)
	movl	$LC1, 4(%esp)
	call	*_errfunc
	jmp	L60
L58:
	movzbl	20(%ebx), %eax
	movb	%al, -13(%ebp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-13(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$1, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	jmp	L165
L57:
	cmpl	$5, -24(%ebp)
	jle	L61
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	cmpl	$8, -24(%ebp)
	setne	%al
	movzbl	%al, %eax
	leal	81(%eax,%eax,2), %eax
	movl	%eax, 8(%esp)
	call	*_errfunc
	jmp	L60
L61:
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	20(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	-24(%ebp), %eax
	addl	$268435456, %eax
	movl	%eax, 12(%esp)
	movl	16(%ebx), %eax
	movl	%eax, 16(%esp)
	movl	24(%ebx), %eax
	movl	%eax, 20(%esp)
L165:
	call	_out
L60:
	movl	-24(%ebp), %edx
	addl	%edx, 12(%ebp)
	jmp	L54
L56:
	cmpl	$1, 4(%ebx)
	jne	L54
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
	movl	12(%ebx), %eax
	cltd
	idivl	-24(%ebp)
	movl	%edx, %esi
	testl	%edx, %edx
	je	L67
	movl	-24(%ebp), %eax
	subl	%edx, %eax
	movl	%eax, %esi
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC3, 8(%esp)
	movl	%esi, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
L67:
	movl	%esi, %eax
	addl	12(%ebx), %eax
	addl	%eax, 12(%ebp)
L54:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L68
L154:
	testl	%edi, %edi
	jle	L49
	movl	24(%ebp), %edx
	movl	188(%edx), %eax
	decl	%eax
	cmpl	%eax, %edi
	jne	L49
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	_list, %eax
	call	*8(%eax)
	movl	$5, (%esp)
	movl	_list, %eax
	call	*16(%eax)
L49:
	decl	%edi
	cmpl	$-1, %edi
	jne	L70
L152:
	movl	24(%ebp), %edx
	cmpl	$1, 188(%edx)
	jmp	L175
L164:
	movl	%ebx, (%esp)
	call	_nasm_free
	jmp	L75
L47:
	movl	24(%ebp), %eax
	cmpl	$233, 24(%eax)
	jne	L72
	movl	$LC4, %esi
	movl	$0, -32(%ebp)
	movl	$255, -28(%ebp)
	movl	180(%eax), %eax
	movl	$255, %edx
	cmpl	12(%eax), %edx
	jle	L73
	movl	12(%eax), %eax
	movl	%eax, -28(%ebp)
L73:
	movl	$_fname.2, (%esp)
	movl	24(%ebp), %edx
	movl	180(%edx), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_strncpy
	movl	-28(%ebp), %edx
	movb	$0, _fname.2(%edx)
L79:
	movl	%esi, (%esp)
	call	_strlen
	movl	-28(%ebp), %edx
	leal	1(%edx,%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	$_fname.2, 4(%esp)
	call	_strcat
	movl	%ebx, (%esp)
	movl	$LC5, 4(%esp)
	call	_fopen
	movl	%eax, %edi
	testl	%eax, %eax
	jne	L164
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	_pp_get_include_path_ptr
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	je	L75
	movl	(%eax), %esi
	jmp	L79
L75:
	testl	%edi, %edi
	jne	L80
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	jmp	L166
L80:
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	movl	$2, 8(%esp)
	call	_fseek
	testl	%eax, %eax
	jns	L82
	movl	$1, (%esp)
	movl	$LC7, 4(%esp)
L166:
	movl	$_fname.2, 8(%esp)
	call	*32(%ebp)
	jmp	L171
L82:
	movl	24(%ebp), %edx
	movl	188(%edx), %edx
	movl	%edx, -36(%ebp)
	movl	$0, -40(%ebp)
	movl	%edi, (%esp)
	call	_ftell
	movl	%eax, -28(%ebp)
	movl	24(%ebp), %edx
	movl	180(%edx), %eax
	cmpl	$0, (%eax)
	je	L84
	movl	(%eax), %eax
	movl	20(%eax), %edx
	movl	%edx, -40(%ebp)
	subl	%edx, -28(%ebp)
	cmpl	$0, (%eax)
	je	L84
	movl	(%eax), %eax
	movl	-28(%ebp), %edx
	cmpl	20(%eax), %edx
	jle	L84
	movl	20(%eax), %eax
	movl	%eax, -28(%ebp)
L84:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	_list, %eax
	call	*8(%eax)
	movl	$4, (%esp)
	movl	_list, %eax
	call	*16(%eax)
	decl	-36(%ebp)
	cmpl	$-1, -36(%ebp)
	je	L156
L95:
	movl	%edi, (%esp)
	movl	-40(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	call	_fseek
	movl	-28(%ebp), %esi
	testl	%esi, %esi
	jle	L86
L94:
	movl	$_buf.3, (%esp)
	movl	$1, 4(%esp)
	movl	%esi, %eax
	cmpl	$2048, %esi
	jbe	L92
	movl	$2048, %eax
L92:
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_fread
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L93
	movl	$1, (%esp)
	movl	$LC8, 4(%esp)
	movl	$_fname.2, 8(%esp)
	call	*32(%ebp)
	movl	$0, -36(%ebp)
	jmp	L86
L93:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$_buf.3, 8(%esp)
	movl	%ebx, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
	subl	%ebx, %esi
	testl	%esi, %esi
	jg	L94
L86:
	decl	-36(%ebp)
	cmpl	$-1, -36(%ebp)
	jne	L95
L156:
	movl	$4, (%esp)
	movl	_list, %eax
	call	*20(%eax)
	movl	24(%ebp), %eax
	cmpl	$1, 188(%eax)
	jle	L96
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	_list, %eax
	call	*8(%eax)
	movl	$5, (%esp)
	movl	_list, %eax
	call	*16(%eax)
	movl	$5, (%esp)
	movl	_list, %eax
	call	*20(%eax)
L96:
	movl	%edi, (%esp)
	call	_fclose
	movl	-28(%ebp), %eax
	movl	24(%ebp), %edx
	imull	188(%edx), %eax
	jmp	L35
L72:
	movl	$0, %esi
	movl	24(%ebp), %edx
	movl	24(%edx), %eax
	movl	_nasm_instructions(,%eax,4), %ebx
	cmpl	$-1, (%ebx)
	je	L163
L143:
	movl	%ebx, (%esp)
	movl	24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_matches
	cmpl	$99, %eax
	jne	L100
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, 8(%esp)
	movl	24(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	20(%ebx), %eax
	movl	%eax, 16(%esp)
	call	_jmp_match
	addl	$99, %eax
L100:
	cmpl	$100, %eax
	jne	L101
	movl	20(%ebx), %ebx
	movl	%ebx, -44(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%edi, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%ebx, 16(%esp)
	call	_calcsize
	movl	%eax, -48(%ebp)
	movl	24(%ebp), %eax
	movl	188(%eax), %esi
	cmpl	$0, -48(%ebp)
	jns	L102
	movl	$3, (%esp)
	movl	$LC9, 4(%esp)
	call	*32(%ebp)
	jmp	L103
L102:
	decl	%esi
	cmpl	$-1, %esi
	je	L103
L139:
	movl	$0, %ebx
	movl	24(%ebp), %edx
	cmpl	20(%edx), %ebx
	jge	L162
L137:
	movb	$0, -14(%ebp)
	movl	24(%ebp), %edx
	movl	4(%edx,%ebx,4), %eax
	subl	$18, %eax
	cmpl	$72, %eax
	ja	L134
	jmp	*L135(,%eax,4)
	.align 4
	.align 4
L135:
	.long	L118
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L119
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L120
	.long	L134
	.long	L134
	.long	L121
	.long	L122
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L125
	.long	L125
	.long	L134
	.long	L134
	.long	L123
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L134
	.long	L126
	.long	L128
	.long	L112
	.long	L130
	.long	L132
	.long	L117
	.long	L117
	.long	L114
	.long	L114
	.long	L117
L112:
	movb	$-16, -14(%ebp)
	jmp	L111
L114:
	movb	$-14, -14(%ebp)
	jmp	L111
L117:
	movb	$-13, -14(%ebp)
	jmp	L111
L118:
	movb	$46, -14(%ebp)
	jmp	L111
L119:
	movb	$62, -14(%ebp)
	jmp	L111
L120:
	movb	$38, -14(%ebp)
	jmp	L111
L121:
	movb	$100, -14(%ebp)
	jmp	L111
L122:
	movb	$101, -14(%ebp)
	jmp	L111
L123:
	movb	$54, -14(%ebp)
	jmp	L111
L125:
	movl	$1, (%esp)
	movl	$LC10, 4(%esp)
	jmp	L169
L126:
	cmpl	$16, %edi
	jmp	L172
L128:
	cmpl	$32, %edi
L172:
	je	L111
	movb	$103, -14(%ebp)
	jmp	L111
L130:
	cmpl	$16, %edi
	jmp	L173
L132:
	cmpl	$32, %edi
L173:
	je	L111
	movb	$102, -14(%ebp)
	jmp	L111
L134:
	movl	$3, (%esp)
	movl	$LC11, 4(%esp)
L169:
	call	*32(%ebp)
L111:
	cmpb	$0, -14(%ebp)
	je	L109
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-14(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$1, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
	incl	12(%ebp)
L109:
	incl	%ebx
	movl	24(%ebp), %eax
	cmpl	20(%eax), %ebx
	jl	L137
L162:
	movl	12(%ebp), %ebx
	addl	-48(%ebp), %ebx
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, 8(%esp)
	movl	24(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	-44(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	%ebx, 20(%esp)
	call	_gencode
	movl	%ebx, 12(%ebp)
	testl	%esi, %esi
	jle	L104
	movl	24(%ebp), %edx
	movl	188(%edx), %eax
	decl	%eax
	cmpl	%eax, %esi
	jne	L104
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	_list, %eax
	call	*8(%eax)
	movl	$5, (%esp)
	movl	_list, %eax
	call	*16(%eax)
L104:
	decl	%esi
	cmpl	$-1, %esi
	jne	L139
L103:
	movl	24(%ebp), %eax
	cmpl	$1, 188(%eax)
L175:
	jle	L140
	movl	$5, (%esp)
	movl	_list, %eax
	call	*20(%eax)
L140:
	movl	12(%ebp), %eax
	subl	-20(%ebp), %eax
	jmp	L35
L101:
	testl	%eax, %eax
	jle	L141
	cmpl	%esi, %eax
	jle	L141
	movl	%eax, %esi
L141:
	addl	$28, %ebx
	cmpl	$-1, (%ebx)
	jne	L143
L163:
	cmpl	$1, %esi
	jne	L145
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
	jmp	L170
L145:
	cmpl	$2, %esi
	jne	L147
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
	jmp	L170
L147:
	cmpl	$3, %esi
	jne	L149
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	jmp	L170
L149:
	movl	$1, (%esp)
	movl	$LC15, 4(%esp)
L170:
	call	*32(%ebp)
L171:
	movl	$0, %eax
L35:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _insn_size
	.def	_insn_size;	.scl	2;	.type	32;	.endef
_insn_size:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$316, %esp
	movl	8(%ebp), %edi
	movl	16(%ebp), %esi
	movl	28(%ebp), %eax
	movl	%eax, _errfunc
	movl	20(%ebp), %eax
	movl	%eax, _cpu
	movl	24(%ebp), %edx
	cmpl	$-1, 24(%edx)
	je	L206
	movl	24(%ebp), %ecx
	cmpl	$106, 24(%ecx)
	je	L179
	cmpl	$116, 24(%ecx)
	je	L179
	cmpl	$107, 24(%ecx)
	je	L179
	cmpl	$114, 24(%ecx)
	je	L179
	cmpl	$115, 24(%ecx)
	jne	L178
L179:
	movl	$0, %esi
	movl	$0, %edi
	movl	24(%ebp), %edx
	movl	24(%edx), %eax
	subl	$106, %eax
	cmpl	$10, %eax
	ja	L180
	jmp	*L186(,%eax,4)
	.align 4
	.align 4
L186:
	.long	L181
	.long	L183
	.long	L180
	.long	L180
	.long	L180
	.long	L180
	.long	L180
	.long	L180
	.long	L184
	.long	L185
	.long	L182
L181:
	movl	$1, %esi
	jmp	L180
L182:
	movl	$2, %esi
	jmp	L180
L183:
	movl	$4, %esi
	jmp	L180
L184:
	movl	$8, %esi
	jmp	L180
L185:
	movl	$10, %esi
L180:
	movl	24(%ebp), %eax
	movl	180(%eax), %ecx
	testl	%ecx, %ecx
	je	L227
L196:
	movl	$0, %ebx
	cmpl	$2, 4(%ecx)
	jne	L192
	movl	$1, %ebx
	jmp	L193
L192:
	cmpl	$1, 4(%ecx)
	jne	L193
	movl	12(%ecx), %ebx
L193:
	movl	%ebx, %eax
	negl	%eax
	cltd
	idivl	%esi
	testl	%edx, %edx
	jns	L195
	addl	%esi, %edx
L195:
	leal	(%edx,%ebx), %eax
	addl	%eax, %edi
	movl	(%ecx), %ecx
	testl	%ecx, %ecx
	jne	L196
L227:
	movl	%edi, %eax
	jmp	L231
L232:
	movl	%ebx, (%esp)
	call	_nasm_free
	jmp	L200
L178:
	movl	24(%ebp), %ecx
	cmpl	$233, 24(%ecx)
	jne	L197
	movl	$LC4, %esi
	movl	$0, %edi
	movl	$255, -284(%ebp)
	movl	180(%ecx), %eax
	movl	$255, %edx
	cmpl	12(%eax), %edx
	jle	L198
	movl	12(%eax), %eax
	movl	%eax, -284(%ebp)
L198:
	leal	-280(%ebp), %eax
	movl	%eax, (%esp)
	movl	24(%ebp), %ecx
	movl	180(%ecx), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-284(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_strncpy
	movl	-284(%ebp), %edx
	movb	$0, -280(%edx,%ebp)
L204:
	movl	%esi, (%esp)
	call	_strlen
	movl	-284(%ebp), %ecx
	leal	1(%ecx,%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	leal	-280(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcat
	movl	%ebx, (%esp)
	movl	$LC5, 4(%esp)
	call	_fopen
	movl	%eax, %esi
	testl	%eax, %eax
	jne	L232
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	%edi, (%esp)
	call	_pp_get_include_path_ptr
	movl	%eax, %edi
	testl	%eax, %eax
	je	L200
	movl	(%eax), %esi
	jmp	L204
L200:
	testl	%esi, %esi
	jne	L205
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	jmp	L234
L205:
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	movl	$2, 8(%esp)
	call	_fseek
	testl	%eax, %eax
	jns	L207
	movl	$1, (%esp)
	movl	$LC7, 4(%esp)
L234:
	leal	-280(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*28(%ebp)
	jmp	L206
L207:
	movl	%esi, (%esp)
	call	_ftell
	movl	%eax, -284(%ebp)
	movl	%esi, (%esp)
	call	_fclose
	movl	24(%ebp), %edx
	movl	180(%edx), %eax
	cmpl	$0, (%eax)
	je	L209
	movl	(%eax), %eax
	movl	20(%eax), %ecx
	subl	%ecx, -284(%ebp)
	cmpl	$0, (%eax)
	je	L209
	movl	(%eax), %eax
	movl	-284(%ebp), %edx
	cmpl	20(%eax), %edx
	jle	L209
	movl	20(%eax), %eax
	movl	%eax, -284(%ebp)
L209:
	movl	-284(%ebp), %eax
	movl	24(%ebp), %ecx
	imull	188(%ecx), %eax
	jmp	L176
L206:
	movl	$0, %eax
	jmp	L176
L197:
	movl	24(%ebp), %edx
	movl	24(%edx), %eax
	movl	_nasm_instructions(,%eax,4), %ebx
	cmpl	$-1, (%ebx)
	je	L229
L225:
	movl	%ebx, (%esp)
	movl	24(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_matches
	cmpl	$99, %eax
	jne	L214
	movl	%edi, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	movl	24(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	20(%ebx), %eax
	movl	%eax, 16(%esp)
	call	_jmp_match
	addl	$99, %eax
L214:
	cmpl	$100, %eax
	jne	L215
	movl	20(%ebx), %eax
	movl	%edi, (%esp)
	movl	12(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	24(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%eax, 16(%esp)
	call	_calcsize
	testl	%eax, %eax
	js	L229
	movl	$0, %edx
	movl	24(%ebp), %ecx
	cmpl	20(%ecx), %edx
	jge	L231
L224:
	movl	24(%ebp), %ecx
	cmpl	$81, 4(%ecx,%edx,4)
	je	L223
	cmpl	$84, 4(%ecx,%edx,4)
	je	L223
	cmpl	$16, %esi
	je	L222
L223:
	movl	24(%ebp), %ecx
	cmpl	$82, 4(%ecx,%edx,4)
	je	L219
	cmpl	$85, 4(%ecx,%edx,4)
	je	L219
	cmpl	$32, %esi
	jne	L219
L222:
	incl	%eax
L219:
	incl	%edx
	movl	24(%ebp), %ecx
	cmpl	20(%ecx), %edx
	jl	L224
L231:
	movl	24(%ebp), %edx
	imull	188(%edx), %eax
	jmp	L176
L215:
	addl	$28, %ebx
	cmpl	$-1, (%ebx)
	jne	L225
L229:
	movl	$-1, %eax
L176:
	addl	$316, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_is_sbyte;	.scl	3;	.type	32;	.endef
_is_sbyte:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	$0, %ebx
	cmpl	$0, 192(%ecx)
	je	L237
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	cmpl	$0, 80(%ecx,%eax)
	jne	L236
L237:
	cmpl	$0, _optimizing
	js	L236
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	addl	%ecx, %eax
	testb	$4, 37(%eax)
	jne	L236
	cmpl	$-1, 72(%eax)
	jne	L236
	cmpl	$-1, 64(%eax)
	jne	L236
	movl	$1, %ebx
L236:
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	68(%ecx,%eax), %edx
	cmpl	$16, 16(%ebp)
	jne	L238
	movswl	%dx,%edx
L238:
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L239
	cmpl	$-128, %edx
	jl	L239
	cmpl	$127, %edx
	jg	L239
	movl	$1, %eax
L239:
	popl	%ebx
	popl	%ebp
	ret
	.align 32
LC16:
	.ascii "attempt to reserve non-constant quantity of BSS space\0"
LC17:
	.ascii "invalid effective address\0"
	.align 32
LC18:
	.ascii "internal instruction table corrupt: instruction code 0x%02X given\0"
	.align 2
	.def	_calcsize;	.scl	3;	.type	32;	.endef
_calcsize:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	20(%ebp), %edi
	movl	24(%ebp), %ebx
	movl	$0, %esi
	cmpb	$0, (%ebx)
	je	L356
L354:
	movzbl	(%ebx), %eax
	movzbl	%al, %edx
	incl	%ebx
	cmpl	$251, %edx
	ja	L348
	jmp	*L353(,%edx,4)
	.align 4
	.align 4
L353:
	.long	L348
	.long	L247
	.long	L247
	.long	L247
	.long	L347
	.long	L347
	.long	L347
	.long	L347
	.long	L335
	.long	L335
	.long	L335
	.long	L348
	.long	L347
	.long	L347
	.long	L347
	.long	L347
	.long	L347
	.long	L347
	.long	L347
	.long	L348
	.long	L347
	.long	L347
	.long	L347
	.long	L348
	.long	L309
	.long	L309
	.long	L309
	.long	L348
	.long	L270
	.long	L270
	.long	L270
	.long	L309
	.long	L317
	.long	L317
	.long	L317
	.long	L348
	.long	L283
	.long	L283
	.long	L283
	.long	L348
	.long	L347
	.long	L347
	.long	L347
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L309
	.long	L309
	.long	L309
	.long	L348
	.long	L296
	.long	L296
	.long	L296
	.long	L348
	.long	L317
	.long	L317
	.long	L317
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L308
	.long	L308
	.long	L308
	.long	L321
	.long	L321
	.long	L321
	.long	L348
	.long	L348
	.long	L316
	.long	L316
	.long	L316
	.long	L321
	.long	L321
	.long	L321
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L324
	.long	L324
	.long	L324
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L330
	.long	L332
	.long	L241
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L330
	.long	L332
	.long	L241
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L335
	.long	L241
	.long	L241
	.long	L347
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L341
	.long	L341
	.long	L341
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L348
	.long	L241
	.long	L241
	.long	L241
	.long	L347
L247:
	movzbl	%al, %eax
	addl	%eax, %ebx
	jmp	L358
L270:
	movzbl	%al, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	-1308(%edi,%eax), %eax
	jmp	L364
L283:
	movzbl	%al, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	%edi, %eax
	cmpl	$0, -1688(%eax)
	je	L297
	cmpl	$16, -1688(%eax)
	jmp	L359
L296:
	movzbl	%al, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	-2460(%edi,%eax), %eax
L364:
	testl	$6, %eax
	je	L297
	testl	$2, %eax
	jne	L309
	jmp	L317
L297:
	cmpl	$16, 16(%ebp)
L359:
	je	L309
	jmp	L317
L308:
	movl	%edi, (%esp)
	movzbl	%al, %eax
	subl	$88, %eax
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	call	_is_sbyte
	testl	%eax, %eax
	jne	L347
L309:
	addl	$2, %esi
	jmp	L241
L316:
	movl	%edi, (%esp)
	movzbl	%al, %eax
	subl	$96, %eax
	movl	%eax, 4(%esp)
	movl	$32, 8(%esp)
	call	_is_sbyte
	testl	%eax, %eax
	jne	L347
L317:
	addl	$4, %esi
	jmp	L241
L321:
	addl	$2, %ebx
	jmp	L347
L324:
	movzbl	%al, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	leal	-9180(%eax,%edi), %eax
	movl	%eax, (%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_chsize
	jmp	L358
L330:
	cmpl	$32, 16(%ebp)
	jmp	L363
L332:
	cmpl	$16, 16(%ebp)
L363:
	jne	L241
	jmp	L347
L335:
	incl	%ebx
	jmp	L347
L341:
	cmpl	$-1, 64(%edi)
	je	L342
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	call	*_errfunc
	jmp	L241
L342:
	movzbl	%al, %ecx
	subl	$224, %ecx
	movl	68(%edi), %eax
	sall	%cl, %eax
L358:
	addl	%eax, %esi
	jmp	L241
L347:
	incl	%esi
	jmp	L241
L348:
	movb	%al, %dl
	subb	$64, %dl
	js	L349
	shrb	$3, %al
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	leal	36(%eax,%edi), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	192(%edi), %eax
	movl	%eax, 16(%esp)
	call	_process_ea
	testl	%eax, %eax
	jne	L350
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_errfunc
	movl	$-1, %eax
	jmp	L240
L350:
	addl	-32(%ebp), %esi
	jmp	L241
L349:
	movl	$3, (%esp)
	movl	$LC18, 4(%esp)
	movzbl	%al, %eax
	movl	%eax, 8(%esp)
	call	*_errfunc
L241:
	cmpb	$0, (%ebx)
	jne	L354
L356:
	movl	%esi, %eax
L240:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.data
_condval.4:
	.byte	7
	.byte	3
	.byte	2
	.byte	6
	.byte	2
	.byte	4
	.byte	15
	.byte	13
	.byte	12
	.byte	14
	.byte	6
	.byte	2
	.byte	3
	.byte	7
	.byte	3
	.byte	5
	.byte	14
	.byte	12
	.byte	13
	.byte	15
	.byte	1
	.byte	11
	.byte	9
	.byte	5
	.byte	0
	.byte	10
	.byte	10
	.byte	11
	.byte	8
	.byte	4
	.text
	.align 32
LC19:
	.ascii "bizarre 8086 segment register received\0"
	.align 32
LC20:
	.ascii "bizarre 386 segment register received\0"
	.align 32
LC21:
	.ascii "signed byte value exceeds bounds\0"
LC22:
	.ascii "byte value exceeds bounds\0"
	.align 32
LC23:
	.ascii "unsigned byte value exceeds bounds\0"
LC24:
	.ascii "word value exceeds bounds\0"
	.align 32
LC25:
	.ascii "value referenced by FAR is not relocatable\0"
	.align 32
LC26:
	.ascii "short relative jump outside segment\0"
LC27:
	.ascii "short jump is out of range\0"
	.align 32
LC28:
	.ascii "non-constant BSS size in pass two\0"
	.align 2
	.def	_gencode;	.scl	3;	.type	32;	.endef
_gencode:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	24(%ebp), %edi
	cmpb	$0, (%edi)
	je	L553
L551:
	movzbl	(%edi), %ebx
	movzbl	%bl, %eax
	incl	%edi
	cmpl	$251, %eax
	ja	L533
	jmp	*L550(,%eax,4)
	.align 4
	.align 4
L550:
	.long	L533
	.long	L372
	.long	L372
	.long	L372
	.long	L374
	.long	L392
	.long	L374
	.long	L392
	.long	L404
	.long	L404
	.long	L404
	.long	L533
	.long	L408
	.long	L408
	.long	L408
	.long	L405
	.long	L414
	.long	L414
	.long	L414
	.long	L533
	.long	L420
	.long	L420
	.long	L420
	.long	L533
	.long	L426
	.long	L426
	.long	L426
	.long	L533
	.long	L430
	.long	L430
	.long	L430
	.long	L438
	.long	L442
	.long	L442
	.long	L442
	.long	L533
	.long	L445
	.long	L445
	.long	L445
	.long	L533
	.long	L453
	.long	L453
	.long	L453
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L458
	.long	L458
	.long	L458
	.long	L533
	.long	L463
	.long	L463
	.long	L463
	.long	L533
	.long	L476
	.long	L476
	.long	L476
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L481
	.long	L481
	.long	L481
	.long	L487
	.long	L487
	.long	L487
	.long	L533
	.long	L533
	.long	L491
	.long	L491
	.long	L491
	.long	L496
	.long	L496
	.long	L496
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L500
	.long	L500
	.long	L500
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L503
	.long	L506
	.long	L366
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L510
	.long	L513
	.long	L366
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L517
	.long	L366
	.long	L366
	.long	L520
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L523
	.long	L523
	.long	L523
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L533
	.long	L366
	.long	L366
	.long	L366
	.long	L530
L372:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%edi, 8(%esp)
	movzbl	%bl, %ebx
	movl	%ebx, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
	addl	%ebx, %edi
	jmp	L526
L374:
	movl	20(%ebp), %ecx
	movl	44(%ecx), %eax
	cmpl	$31, %eax
	je	L379
	cmpl	$31, %eax
	jg	L390
	cmpl	$18, %eax
	je	L376
	jmp	L388
L390:
	cmpl	$39, %eax
	je	L382
	cmpl	$56, %eax
	je	L385
	jmp	L388
L376:
	cmpb	$4, %bl
	setne	%al
	movb	$15, %dl
	jmp	L554
L379:
	cmpb	$4, %bl
	setne	%al
	movb	$31, %dl
	jmp	L554
L382:
	cmpb	$4, %bl
	setne	%al
	movb	$7, %dl
	jmp	L554
L385:
	cmpb	$4, %bl
	setne	%al
	movb	$23, %dl
L554:
	subb	%al, %dl
	movzbl	%dl, %eax
	andl	$-256, -44(%ebp)
	orl	%eax, -44(%ebp)
	jmp	L579
L388:
	movl	$3, (%esp)
	movl	$LC19, 4(%esp)
	jmp	L584
L392:
	movl	20(%ebp), %ecx
	movl	44(%ecx), %eax
	cmpl	$42, %eax
	je	L394
	cmpl	$43, %eax
	je	L397
	jmp	L400
L394:
	cmpb	$5, %bl
	setne	%al
	movb	$-95, %dl
	jmp	L555
L397:
	cmpb	$5, %bl
	setne	%al
	movb	$-87, %dl
L555:
	subb	%al, %dl
	movb	%dl, %al
	jmp	L583
L400:
	movl	$3, (%esp)
	movl	$LC20, 4(%esp)
L584:
	call	*_errfunc
	jmp	L579
L404:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	-348(%eax,%ecx), %eax
	movl	%eax, (%esp)
	movzbl	(%edi), %ebx
	incl	%edi
	call	_regval
	addb	%al, %bl
	movb	%bl, -44(%ebp)
	jmp	L579
L405:
	movb	$0, -44(%ebp)
	jmp	L581
L408:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-508(%edx,%eax), %eax
	subl	$-128, %eax
	cmpl	$255, %eax
	jbe	L409
	movl	$0, (%esp)
	movl	$LC21, 4(%esp)
	call	*_errfunc
L409:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	cmpl	$-1, -512(%edx)
	je	L410
	movl	-508(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435457, 12(%esp)
	movl	-512(%edx), %eax
	movl	%eax, 16(%esp)
	movl	-504(%edx), %eax
	jmp	L582
L410:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movzbl	-508(%edx,%eax), %eax
	jmp	L587
L414:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-700(%edx,%eax), %eax
	addl	$256, %eax
	cmpl	$511, %eax
	jbe	L415
	movl	$0, (%esp)
	movl	$LC22, 4(%esp)
	call	*_errfunc
L415:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	cmpl	$-1, -704(%edx)
	je	L416
	movl	-700(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435457, 12(%esp)
	movl	-704(%edx), %eax
	movl	%eax, 16(%esp)
	movl	-696(%edx), %eax
	jmp	L582
L416:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movzbl	-700(%edx,%eax), %eax
	jmp	L587
L420:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	cmpl	$255, -892(%edx,%eax)
	jbe	L421
	movl	$0, (%esp)
	movl	$LC23, 4(%esp)
	call	*_errfunc
L421:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	cmpl	$-1, -896(%edx)
	je	L422
	movl	-892(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435457, 12(%esp)
	movl	-896(%edx), %eax
	movl	%eax, 16(%esp)
	movl	-888(%edx), %eax
L582:
	movl	%eax, 20(%esp)
	jmp	L570
L422:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movzbl	-892(%edx,%eax), %eax
L587:
	movb	%al, -44(%ebp)
	jmp	L581
L426:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	cmpl	$-1, -1088(%eax)
	jne	L427
	cmpl	$-1, -1080(%eax)
	jne	L427
	movl	-1084(%eax), %eax
	addl	$65536, %eax
	cmpl	$131071, %eax
	jbe	L427
	movl	$0, (%esp)
	movl	$LC24, 4(%esp)
	call	*_errfunc
L427:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-1084(%eax), %edx
	movl	%edx, -48(%ebp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	$268435458, 12(%esp)
	movl	-1088(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-1080(%eax), %eax
	jmp	L573
L430:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-1308(%edx,%eax), %eax
	testl	$6, %eax
	je	L431
	testl	$2, %eax
	sete	%al
	jmp	L559
L431:
	cmpl	$16, 16(%ebp)
	setne	%al
L559:
	movzbl	%al, %esi
	leal	2(%esi,%esi), %esi
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	movl	-1276(%ecx,%eax), %eax
	movl	%eax, -48(%ebp)
	cmpl	$2, %esi
	jne	L437
	addl	$65536, %eax
	cmpl	$131071, %eax
	jbe	L437
	movl	$0, (%esp)
	movl	$LC24, 4(%esp)
	call	*_errfunc
L437:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	268435456(%esi), %eax
	movl	%eax, 12(%esp)
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-1280(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-1272(%eax), %eax
	jmp	L572
L438:
	movl	20(%ebp), %ecx
	cmpl	$-1, 64(%ecx)
	jne	L439
	movl	$1, (%esp)
	movl	$LC25, 4(%esp)
	call	*_errfunc
L439:
	movl	$0, -48(%ebp)
	movl	20(%ebp), %edx
	movl	64(%edx), %eax
	incl	%eax
	movl	%eax, (%esp)
	movl	_outfmt, %eax
	call	*44(%eax)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-48(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	$268435458, 12(%esp)
	movl	%eax, 16(%esp)
	movl	20(%ebp), %ecx
	movl	72(%ecx), %eax
	jmp	L573
L442:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-1468(%eax), %edx
	movl	%edx, -48(%ebp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	$268435460, 12(%esp)
	movl	-1472(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-1464(%eax), %eax
	jmp	L574
L445:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	movl	-1660(%edx), %eax
	movl	%eax, -48(%ebp)
	cmpl	$0, -1688(%edx)
	je	L448
	cmpl	$16, -1688(%edx)
	jmp	L560
L448:
	cmpl	$16, 16(%ebp)
L560:
	jne	L446
	movl	$2, %esi
	jmp	L447
L446:
	movl	$4, %esi
L447:
	cmpl	$2, %esi
	jne	L450
	movl	-48(%ebp), %eax
	addl	$65536, %eax
	cmpl	$131071, %eax
	jbe	L450
	movl	$0, (%esp)
	movl	$LC24, 4(%esp)
	call	*_errfunc
L450:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	268435456(%esi), %eax
	movl	%eax, 12(%esp)
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-1664(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-1656(%eax), %eax
	jmp	L572
L453:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	8(%ebp), %edx
	movl	20(%ebp), %ecx
	cmpl	%edx, -1856(%ecx,%eax)
	je	L454
	movl	$1, (%esp)
	movl	$LC26, 4(%esp)
	call	*_errfunc
L454:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	movl	-1852(%ecx,%eax), %eax
	subl	28(%ebp), %eax
	movl	%eax, -48(%ebp)
	subl	$-128, %eax
	cmpl	$255, %eax
	jbe	L576
	movl	$1, (%esp)
	movl	$LC27, 4(%esp)
	call	*_errfunc
	jmp	L576
L458:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	movl	8(%ebp), %eax
	cmpl	%eax, -2240(%edx)
	je	L459
	movl	-2236(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	28(%ebp), %eax
	subl	%ecx, %eax
	addl	$536870912, %eax
	movl	%eax, 12(%esp)
	movl	-2240(%edx), %eax
	movl	%eax, 16(%esp)
	movl	-2232(%edx), %eax
	jmp	L573
L459:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-2236(%edx,%eax), %eax
	subl	28(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435458, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	jmp	L569
L463:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-2460(%edx,%eax), %eax
	testl	$6, %eax
	je	L464
	testl	$2, %eax
	sete	%al
	jmp	L562
L464:
	cmpl	$16, 16(%ebp)
	setne	%al
L562:
	movzbl	%al, %esi
	leal	2(%esi,%esi), %esi
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	leal	(%edx,%eax), %ecx
	movl	8(%ebp), %eax
	cmpl	%eax, -2432(%ecx)
	je	L470
	cmpl	$2, %esi
	setne	%al
	movzbl	%al, %eax
	decl	%eax
	andl	$-268435456, %eax
	movl	-2428(%ecx), %edx
	movl	%edx, -48(%ebp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-48(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	28(%ebp), %edx
	leal	805306368(%edx,%eax), %eax
	subl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-2432(%ecx), %eax
	movl	%eax, 16(%esp)
	movl	-2424(%ecx), %eax
L572:
	movl	%eax, 20(%esp)
	jmp	L563
L470:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	movl	-2428(%ecx,%eax), %eax
	subl	28(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	268435456(%esi), %eax
	movl	%eax, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
L563:
	call	_out
	jmp	L539
L476:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	movl	8(%ebp), %eax
	cmpl	%eax, -2624(%edx)
	je	L477
	movl	-2620(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	28(%ebp), %eax
	subl	%ecx, %eax
	addl	$805306368, %eax
	movl	%eax, 12(%esp)
	movl	-2624(%edx), %eax
	movl	%eax, 16(%esp)
	movl	-2616(%edx), %eax
	jmp	L574
L477:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movl	-2620(%edx,%eax), %eax
	subl	28(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435460, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	jmp	L568
L481:
	movzbl	%bl, %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	movl	-4156(%ecx,%eax), %eax
	movl	%eax, -48(%ebp)
	movl	%ecx, (%esp)
	subl	$88, %edx
	movl	%edx, 4(%esp)
	movl	$16, 8(%esp)
	call	_is_sbyte
	testl	%eax, %eax
	jne	L576
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	cmpl	$-1, -4160(%eax)
	jne	L484
	cmpl	$-1, -4152(%eax)
	jne	L484
	movl	-48(%ebp), %eax
	addl	$65536, %eax
	cmpl	$131071, %eax
	jbe	L484
	movl	$0, (%esp)
	movl	$LC24, 4(%esp)
	call	*_errfunc
L484:
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435458, 12(%esp)
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-4160(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-4152(%eax), %eax
L573:
	movl	%eax, 20(%esp)
L569:
	call	_out
	addl	$2, 12(%ebp)
	jmp	L366
L487:
	incl	%edi
	movzbl	(%edi), %eax
	movb	%al, -44(%ebp)
	incl	%edi
	movl	20(%ebp), %edx
	movl	%edx, (%esp)
	movzbl	%bl, %eax
	subl	$91, %eax
	movl	%eax, 4(%esp)
	movl	$16, 8(%esp)
	jmp	L588
L491:
	movzbl	%bl, %edx
	leal	(%edx,%edx,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	movl	-4540(%ecx,%eax), %eax
	movl	%eax, -48(%ebp)
	movl	%ecx, (%esp)
	subl	$96, %edx
	movl	%edx, 4(%esp)
	movl	$32, 8(%esp)
	call	_is_sbyte
	testl	%eax, %eax
	je	L492
L576:
	movzbl	-48(%ebp), %eax
L583:
	movb	%al, -44(%ebp)
	jmp	L579
L492:
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435460, 12(%esp)
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	-4544(%eax), %edx
	movl	%edx, 16(%esp)
	movl	-4536(%eax), %eax
L574:
	movl	%eax, 20(%esp)
L568:
	call	_out
	addl	$4, 12(%ebp)
	jmp	L366
L496:
	incl	%edi
	movzbl	(%edi), %eax
	movb	%al, -44(%ebp)
	incl	%edi
	movl	20(%ebp), %edx
	movl	%edx, (%esp)
	movzbl	%bl, %eax
	subl	$99, %eax
	movl	%eax, 4(%esp)
	movl	$32, 8(%esp)
L588:
	call	_is_sbyte
	testl	%eax, %eax
	je	L581
	orb	$2, -44(%ebp)
	jmp	L581
L500:
	movzbl	%bl, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	leal	-9180(%eax,%edx), %eax
	movl	%eax, (%esp)
	movl	16(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_chsize
	testl	%eax, %eax
	je	L366
	movb	$103, -44(%ebp)
	jmp	L579
L503:
	cmpl	$32, 16(%ebp)
	jne	L366
	movb	$103, -44(%ebp)
	jmp	L581
L506:
	cmpl	$16, 16(%ebp)
	jne	L366
	movb	$103, -44(%ebp)
	jmp	L566
L510:
	cmpl	$32, 16(%ebp)
	jne	L366
	movb	$102, -44(%ebp)
L579:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	jmp	L567
L513:
	cmpl	$16, 16(%ebp)
	jne	L366
	movb	$102, -44(%ebp)
	jmp	L581
L517:
	movl	20(%ebp), %edx
	movl	28(%edx), %eax
	movzbl	(%edi), %edx
	xorb	_condval.4(%eax), %dl
	movb	%dl, -44(%ebp)
	incl	%edi
L581:
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	jmp	L567
L520:
	movb	$-13, -44(%ebp)
	jmp	L566
L523:
	movl	20(%ebp), %eax
	cmpl	$-1, 64(%eax)
	je	L524
	movl	$3, (%esp)
	movl	$LC28, 4(%esp)
	call	*_errfunc
	jmp	L366
L524:
	movzbl	%bl, %ecx
	subl	$224, %ecx
	movl	20(%ebp), %edx
	movl	68(%edx), %eax
	movl	%eax, %ebx
	sall	%cl, %ebx
	testl	%ebx, %ebx
	jle	L526
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	leal	1073741824(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
L526:
	addl	%ebx, 12(%ebp)
	jmp	L366
L530:
	movb	$3, %al
	cmpl	$16, 16(%ebp)
	je	L532
	movb	$5, %al
L532:
	movb	%al, -44(%ebp)
L566:
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
L567:
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$1, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
L570:
	call	_out
	incl	12(%ebp)
	jmp	L366
L533:
	movb	%bl, %al
	subb	$64, %al
	js	L534
	testb	%bl, %bl
	js	L535
	movl	%ebx, %eax
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	leal	36(%eax,%edx), %eax
	movl	%eax, (%esp)
	call	_regval
	movl	%eax, %edx
	jmp	L536
L535:
	movl	%ebx, %edx
	andl	$7, %edx
L536:
	movb	%bl, %al
	shrb	$3, %al
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	36(%eax,%ecx), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	192(%ecx), %eax
	movl	%eax, 16(%esp)
	call	_process_ea
	testl	%eax, %eax
	jne	L537
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_errfunc
L537:
	movzbl	-28(%ebp), %eax
	movb	%al, -44(%ebp)
	leal	-43(%ebp), %edx
	cmpl	$0, -40(%ebp)
	je	L538
	movzbl	-27(%ebp), %eax
	movb	%al, (%edx)
	incl	%edx
L538:
	leal	-44(%ebp), %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%esi, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
	call	_out
	movl	-36(%ebp), %eax
	cmpl	$1, %eax
	je	L541
	cmpl	$1, %eax
	jle	L539
	cmpl	$2, %eax
	je	L545
	cmpl	$4, %eax
	je	L545
	jmp	L539
L541:
	movb	%bl, %al
	shrb	$3, %al
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %ecx
	leal	(%ecx,%eax), %edx
	cmpl	$-1, 64(%edx)
	je	L542
	movl	68(%edx), %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$268435457, 12(%esp)
	movl	64(%edx), %eax
	movl	%eax, 16(%esp)
	movl	72(%edx), %eax
	movl	%eax, 20(%esp)
	jmp	L565
L542:
	movb	%bl, %al
	shrb	$3, %al
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	20(%ebp), %edx
	movzbl	68(%edx,%eax), %eax
	movb	%al, -44(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$1, 12(%esp)
	movl	$-1, 16(%esp)
	movl	$-1, 20(%esp)
L565:
	call	_out
	incl	%esi
	jmp	L539
L545:
	movb	%bl, %al
	shrb	$3, %al
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	20(%ebp), %eax
	movl	68(%eax), %edx
	movl	%edx, -48(%ebp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	leal	-48(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	-36(%ebp), %edx
	addl	$268435456, %edx
	movl	%edx, 12(%esp)
	movl	64(%eax), %edx
	movl	%edx, 16(%esp)
	movl	72(%eax), %eax
	movl	%eax, 20(%esp)
	call	_out
	addl	-36(%ebp), %esi
L539:
	addl	%esi, 12(%ebp)
	jmp	L366
L534:
	movl	$3, (%esp)
	movl	$LC18, 4(%esp)
	movzbl	%bl, %eax
	movl	%eax, 8(%esp)
	call	*_errfunc
L366:
	cmpb	$0, (%edi)
	jne	L551
L553:
	addl	$76, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
_regvals:
	.long	-1
	.long	4
	.long	0
	.long	0
	.long	7
	.long	3
	.long	5
	.long	3
	.long	5
	.long	1
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	1
	.long	1
	.long	6
	.long	7
	.long	2
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	3
	.long	2
	.long	0
	.long	5
	.long	3
	.long	1
	.long	7
	.long	2
	.long	0
	.long	6
	.long	4
	.long	4
	.long	5
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	6
	.long	7
	.long	6
	.long	4
	.long	2
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.align 32
LC29:
	.ascii "invalid operand passed to regval()\0"
	.align 2
	.def	_regval;	.scl	3;	.type	32;	.endef
_regval:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	8(%ebx), %eax
	decl	%eax
	cmpl	$79, %eax
	jbe	L590
	movl	$3, (%esp)
	movl	$LC29, 4(%esp)
	call	*_errfunc
L590:
	movl	8(%ebx), %eax
	movl	_regvals(,%eax,4), %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_matches;	.scl	3;	.type	32;	.endef
_matches:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movl	(%ebx), %eax
	cmpl	24(%esi), %eax
	jne	L660
	movl	4(%ebx), %eax
	cmpl	32(%esi), %eax
	jne	L660
	movl	$0, %ecx
	cmpl	4(%ebx), %ecx
	jge	L655
L599:
	leal	(%ecx,%ecx,2), %edx
	sall	$4, %edx
	movl	8(%ebx,%ecx,4), %eax
	notl	%eax
	andl	36(%esi,%edx), %eax
	testl	$768, %eax
	jne	L660
	incl	%ecx
	cmpl	4(%ebx), %ecx
	jl	L599
	movl	$0, %ecx
	cmpl	4(%ebx), %ecx
	jge	L655
L609:
	leal	(%ecx,%ecx,2), %eax
	sall	$4, %eax
	leal	(%esi,%eax), %edx
	movl	36(%edx), %eax
	notl	%eax
	andl	8(%ebx,%ecx,4), %eax
	testl	%eax, %eax
	jne	L605
	movzbl	8(%ebx,%ecx,4), %eax
	testb	%al, %al
	je	L602
	cmpb	36(%edx), %al
	je	L602
L605:
	leal	(%ecx,%ecx,2), %eax
	sall	$4, %eax
	leal	(%esi,%eax), %edx
	movl	36(%edx), %eax
	notl	%eax
	andl	8(%ebx,%ecx,4), %eax
	testl	$-256, %eax
	jne	L660
	cmpb	$0, 36(%edx)
	jne	L660
	movl	$1, %eax
	jmp	L591
L602:
	incl	%ecx
	cmpl	4(%ebx), %ecx
	jl	L609
L655:
	movl	24(%ebx), %eax
	andl	$96, %eax
	je	L610
	movl	$0, -32(%ebp)
	movl	$0, -36(%ebp)
	movl	$0, -40(%ebp)
	cmpl	$64, %eax
	je	L613
	cmpl	$64, %eax
	ja	L617
	cmpl	$32, %eax
	je	L612
	jmp	L611
L617:
	cmpl	$96, %eax
	je	L614
	jmp	L611
L612:
	movl	$0, %ecx
	jmp	L611
L613:
	movl	$1, %ecx
	jmp	L611
L614:
	movl	$2, %ecx
L611:
	testb	$4, 24(%ebx)
	je	L618
	movl	$1, -40(%ebp,%ecx,4)
	jmp	L623
L618:
	testb	$8, 24(%ebx)
	je	L620
	movl	$2, -40(%ebp,%ecx,4)
	jmp	L623
L620:
	testb	$16, 24(%ebx)
	je	L623
	movl	$4, -40(%ebp,%ecx,4)
	jmp	L623
L610:
	movl	$0, %eax
	testb	$4, 24(%ebx)
	je	L624
	movl	$1, %eax
	jmp	L625
L624:
	testb	$8, 24(%ebx)
	je	L626
	movl	$2, %eax
	jmp	L625
L626:
	testb	$16, 24(%ebx)
	je	L625
	movl	$4, %eax
L625:
	movl	%eax, -32(%ebp)
	movl	%eax, -36(%ebp)
	movl	%eax, -40(%ebp)
L623:
	movl	24(%ebx), %eax
	testl	$3, %eax
	je	L643
	movl	$2, %edi
	testl	$2, %eax
	jne	L631
	movl	4(%ebx), %edi
L631:
	movl	$0, %ecx
	cmpl	%edi, %ecx
	jge	L643
L642:
	movzbl	8(%ebx,%ecx,4), %eax
	testl	%eax, %eax
	je	L634
	movl	$0, %edx
	cmpl	%edi, %edx
	jge	L643
L641:
	movl	%eax, -40(%ebp,%edx,4)
	incl	%edx
	cmpl	%edi, %edx
	jge	L643
	jmp	L641
L634:
	incl	%ecx
	cmpl	%edi, %ecx
	jl	L642
L643:
	movl	$0, %ecx
	cmpl	4(%ebx), %ecx
	jge	L659
L649:
	cmpb	$0, 8(%ebx,%ecx,4)
	jne	L646
	leal	(%ecx,%ecx,2), %edx
	sall	$4, %edx
	movzbl	-40(%ebp,%ecx,4), %eax
	notb	%al
	andb	36(%esi,%edx), %al
	testb	%al, %al
	jne	L661
L646:
	incl	%ecx
	cmpl	4(%ebx), %ecx
	jl	L649
L659:
	movl	24(%ebx), %eax
	andl	$251658240, %eax
	cmpl	_cpu, %eax
	jbe	L650
	movl	$3, %eax
	jmp	L591
L650:
	movl	20(%ebx), %eax
	cmpb	$-9, (%eax)
	jbe	L651
	movl	$99, %eax
	jmp	L591
L660:
	movl	$0, %eax
	jmp	L591
L661:
	movl	$2, %eax
	jmp	L591
L651:
	movl	$100, %eax
L591:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.data
	.align 32
_regs.5:
	.long	2
	.long	9
	.long	22
	.long	5
	.long	1
	.long	8
	.long	20
	.long	4
	.long	3
	.long	19
	.long	32
	.long	7
	.long	55
	.long	6
	.long	54
	.long	21
	.long	33
	.long	36
	.long	38
	.long	35
	.long	41
	.long	34
	.long	40
	.long	37
	.long	44
	.long	45
	.long	46
	.long	47
	.long	48
	.long	49
	.long	50
	.long	51
	.long	73
	.long	74
	.long	75
	.long	76
	.long	77
	.long	78
	.long	79
	.long	80
	.text
	.align 2
	.def	_process_ea;	.scl	3;	.type	32;	.endef
_process_ea:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$24, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx
	movl	(%esi), %eax
	xorl	$4096, %eax
	testl	$4096, %eax
	jne	L663
	movl	$0, %eax
	movl	$_regs.5, %ecx
	movl	8(%esi), %edx
L669:
	cmpl	(%ecx,%eax,4), %edx
	je	L665
	incl	%eax
	cmpl	$39, %eax
	jbe	L669
	jmp	L802
L665:
	cmpl	$39, %eax
	ja	L802
	movl	$0, (%edi)
	movl	$0, 4(%edi)
	movl	20(%ebp), %edx
	sall	$3, %edx
	andb	$7, %al
	orb	%dl, %al
	orb	$-64, %al
	jmp	L804
L663:
	cmpl	$-1, 8(%esi)
	jne	L673
	cmpl	$-1, 12(%esi)
	je	L674
	cmpl	$0, 16(%esi)
	jne	L673
L674:
	cmpl	$0, 4(%esi)
	je	L675
	movl	4(%esi), %ecx
L675:
	movl	$0, (%edi)
	cmpl	$32, %ecx
	sete	%al
	movzbl	%al, %eax
	leal	2(%eax,%eax), %eax
	movl	%eax, 4(%edi)
	movl	20(%ebp), %eax
	sall	$3, %eax
	cmpl	$32, %ecx
	jne	L678
	orb	$5, %al
	jmp	L804
L678:
	orb	$6, %al
	jmp	L804
L673:
	movl	8(%esi), %ecx
	movl	16(%esi), %ebx
	movl	32(%esi), %eax
	movl	%eax, -16(%ebp)
	movl	28(%esi), %eax
	movl	%eax, -20(%ebp)
	movl	20(%esi), %eax
	movl	%eax, -24(%ebp)
	movl	24(%esi), %eax
	movl	%eax, -28(%ebp)
	testl	%ebx, %ebx
	setne	%al
	movzbl	%al, %eax
	decl	%eax
	movl	12(%esi), %edx
	orl	%eax, %edx
	cmpl	$33, %edx
	je	L683
	cmpl	$35, %edx
	je	L683
	cmpl	$36, %edx
	je	L683
	cmpl	$38, %edx
	je	L683
	cmpl	$34, %edx
	je	L683
	cmpl	$41, %edx
	je	L683
	cmpl	$40, %edx
	je	L683
	cmpl	$37, %edx
	je	L683
	cmpl	$33, %ecx
	je	L683
	cmpl	$35, %ecx
	je	L683
	cmpl	$36, %ecx
	je	L683
	cmpl	$38, %ecx
	je	L683
	cmpl	$34, %ecx
	je	L683
	cmpl	$41, %ecx
	je	L683
	cmpl	$40, %ecx
	je	L683
	cmpl	$37, %ecx
	jne	L682
L683:
	cmpl	$-1, %edx
	je	L684
	cmpl	$33, %edx
	je	L684
	cmpl	$35, %edx
	je	L684
	cmpl	$36, %edx
	je	L684
	cmpl	$38, %edx
	je	L684
	cmpl	$34, %edx
	je	L684
	cmpl	$41, %edx
	je	L684
	cmpl	$40, %edx
	je	L684
	movl	$0, %eax
	cmpl	$37, %edx
	jne	L662
L684:
	cmpl	$-1, %ecx
	je	L685
	cmpl	$33, %ecx
	je	L685
	cmpl	$35, %ecx
	je	L685
	cmpl	$36, %ecx
	je	L685
	cmpl	$38, %ecx
	je	L685
	cmpl	$34, %ecx
	je	L685
	cmpl	$41, %ecx
	je	L685
	cmpl	$40, %ecx
	je	L685
	movl	$0, %eax
	cmpl	$37, %ecx
	jne	L662
L685:
	cmpl	$16, 4(%esi)
	je	L802
	cmpl	$1, %ebx
	jne	L687
	cmpl	%edx, %ecx
	je	L799
	cmpl	$-1, %ecx
	je	L687
	cmpl	$-1, %edx
	je	L687
	cmpl	%ecx, -24(%ebp)
	jne	L689
	cmpl	$2, -28(%ebp)
	je	L688
L689:
	cmpl	%edx, -24(%ebp)
	jne	L687
	cmpl	$1, -28(%ebp)
	jne	L687
L688:
	movl	%ecx, %eax
	movl	%edx, %ecx
	movl	%eax, %edx
L687:
	cmpl	%edx, %ecx
	jne	L690
L799:
	movl	$-1, %ecx
	incl	%ebx
L690:
	cmpl	$-1, %ecx
	jne	L691
	cmpl	$1, %ebx
	jne	L691
	cmpl	%edx, -24(%ebp)
	jne	L692
	cmpl	$2, -28(%ebp)
	je	L691
L692:
	movl	%edx, %ecx
	movl	$-1, %edx
L691:
	cmpl	$2, %ebx
	jne	L695
	cmpl	$41, %edx
	je	L695
	testb	$4, 40(%esi)
	je	L694
L695:
	cmpl	$3, %ebx
	je	L694
	cmpl	$5, %ebx
	je	L694
	cmpl	$9, %ebx
	jne	L693
L694:
	cmpl	$-1, %ecx
	jne	L693
	movl	%edx, %ecx
	decl	%ebx
L693:
	cmpl	$-1, %edx
	jne	L696
	cmpl	$41, %ecx
	je	L696
	testb	$4, 40(%esi)
	je	L696
	movl	%ecx, %edx
	movl	$-1, %ecx
	movl	$1, %ebx
L696:
	cmpl	$1, %ebx
	jne	L697
	cmpl	$41, %edx
	jne	L800
	movl	%ecx, %edx
	movl	$41, %ecx
L697:
	cmpl	$41, %edx
	je	L802
L800:
	leal	-1(%ebx), %eax
	cmpl	$1, %eax
	jbe	L698
	cmpl	$4, %ebx
	je	L698
	cmpl	$8, %ebx
	je	L698
	cmpl	$-1, %edx
	je	L801
	jmp	L802
L698:
	cmpl	$-1, %edx
	jne	L700
L801:
	cmpl	$41, %ecx
	je	L700
	leal	1(%ecx), %eax
	cmpl	$41, %eax
	ja	L802
	jmp	*L711(,%eax,4)
	.align 4
	.align 4
L711:
	.long	L709
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L702
	.long	L709
	.long	L705
	.long	L703
	.long	L708
	.long	L704
	.long	L802
	.long	L707
L702:
	movl	$0, %ebx
	jmp	L701
L703:
	movl	$1, %ebx
	jmp	L701
L704:
	movl	$2, %ebx
	jmp	L701
L705:
	movl	$3, %ebx
	jmp	L701
L707:
	movl	$6, %ebx
	jmp	L701
L708:
	movl	$7, %ebx
	jmp	L701
L709:
	movl	$5, %ebx
L701:
	cmpl	$-1, %ecx
	je	L713
	cmpl	$34, %ecx
	je	L712
	cmpl	$0, -16(%ebp)
	jne	L712
	cmpl	$-1, -20(%ebp)
	jne	L712
	cmpl	$0, 24(%ebp)
	jne	L712
	testb	$3, 40(%esi)
	jne	L712
L713:
	movl	$0, %edx
	jmp	L714
L712:
	movl	40(%esi), %edx
	testl	$1, %edx
	jne	L716
	movl	-16(%ebp), %eax
	subl	$-128, %eax
	cmpl	$255, %eax
	ja	L715
	cmpl	$-1, -20(%ebp)
	jne	L715
	cmpl	$0, 24(%ebp)
	jne	L715
	testl	$2, %edx
	jne	L715
L716:
	movl	$1, %edx
	jmp	L714
L715:
	movl	$2, %edx
L714:
	movl	$0, (%edi)
	cmpl	$-1, %ecx
	je	L718
	movl	%edx, %eax
	cmpl	$2, %edx
	jne	L719
L718:
	movl	$4, %eax
L719:
	movl	%eax, 4(%edi)
	jmp	L803
L700:
	leal	1(%ecx), %eax
	cmpl	$42, %eax
	ja	L802
	jmp	*L732(,%eax,4)
	.align 4
	.align 4
L732:
	.long	L728
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L722
	.long	L728
	.long	L725
	.long	L723
	.long	L730
	.long	L724
	.long	L802
	.long	L729
	.long	L726
L722:
	movl	$0, -36(%ebp)
	jmp	L721
L723:
	movl	$1, -36(%ebp)
	jmp	L721
L724:
	movl	$2, -36(%ebp)
	jmp	L721
L725:
	movl	$3, -36(%ebp)
	jmp	L721
L726:
	movl	$4, -36(%ebp)
	jmp	L721
L728:
	movl	$5, -36(%ebp)
	jmp	L721
L729:
	movl	$6, -36(%ebp)
	jmp	L721
L730:
	movl	$7, -36(%ebp)
L721:
	leal	1(%edx), %eax
	cmpl	$41, %eax
	ja	L802
	jmp	*L743(,%eax,4)
	.align 4
	.align 4
L743:
	.long	L738
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L802
	.long	L734
	.long	L739
	.long	L737
	.long	L735
	.long	L741
	.long	L736
	.long	L802
	.long	L740
L734:
	movl	$0, -32(%ebp)
	jmp	L733
L735:
	movl	$1, -32(%ebp)
	jmp	L733
L736:
	movl	$2, -32(%ebp)
	jmp	L733
L737:
	movl	$3, -32(%ebp)
	jmp	L733
L738:
	movl	$4, -32(%ebp)
	jmp	L733
L739:
	movl	$5, -32(%ebp)
	jmp	L733
L740:
	movl	$6, -32(%ebp)
	jmp	L733
L741:
	movl	$7, -32(%ebp)
L733:
	cmpl	$-1, %edx
	jne	L744
	movl	$1, %ebx
L744:
	cmpl	$2, %ebx
	je	L747
	cmpl	$2, %ebx
	jg	L752
	cmpl	$1, %ebx
	je	L746
	jmp	L802
L752:
	cmpl	$4, %ebx
	je	L748
	cmpl	$8, %ebx
	je	L749
	jmp	L802
L746:
	movl	$0, %ebx
	jmp	L745
L747:
	movl	$1, %ebx
	jmp	L745
L748:
	movl	$2, %ebx
	jmp	L745
L749:
	movl	$3, %ebx
L745:
	cmpl	$-1, %ecx
	je	L754
	cmpl	$34, %ecx
	je	L753
	cmpl	$0, -16(%ebp)
	jne	L753
	cmpl	$-1, -20(%ebp)
	jne	L753
	cmpl	$0, 24(%ebp)
	jne	L753
	testb	$3, 40(%esi)
	jne	L753
L754:
	movl	$0, %edx
	jmp	L755
L753:
	movl	40(%esi), %edx
	testl	$1, %edx
	jne	L757
	movl	-16(%ebp), %eax
	subl	$-128, %eax
	cmpl	$255, %eax
	ja	L756
	cmpl	$-1, -20(%ebp)
	jne	L756
	cmpl	$0, 24(%ebp)
	jne	L756
	testl	$2, %edx
	jne	L756
L757:
	movl	$1, %edx
	jmp	L755
L756:
	movl	$2, %edx
L755:
	movl	$1, (%edi)
	cmpl	$-1, %ecx
	je	L759
	movl	%edx, %eax
	cmpl	$2, %edx
	jne	L760
L759:
	movl	$4, %eax
L760:
	movl	%eax, 4(%edi)
	sall	$6, %edx
	movl	20(%ebp), %eax
	sall	$3, %eax
	orb	%dl, %al
	orb	$4, %al
	movb	%al, 12(%edi)
	movl	%ebx, %edx
	sall	$6, %edx
	movl	-32(%ebp), %eax
	sall	$3, %eax
	orb	%dl, %al
	orb	-36(%ebp), %al
	movb	%al, 13(%edi)
	jmp	L672
L682:
	cmpl	$-1, %ecx
	je	L764
	cmpl	$6, %ecx
	je	L764
	cmpl	$7, %ecx
	je	L764
	cmpl	$54, %ecx
	je	L764
	cmpl	$21, %ecx
	jne	L802
L764:
	cmpl	$-1, %edx
	je	L762
	cmpl	$6, %edx
	je	L762
	cmpl	$7, %edx
	je	L762
	cmpl	$54, %edx
	je	L762
	cmpl	$21, %edx
	jne	L802
L762:
	cmpl	$32, 4(%esi)
	je	L802
	cmpl	$1, %ebx
	je	L766
	movl	$0, %eax
	cmpl	$-1, %edx
	jne	L662
L766:
	cmpl	$-1, %ecx
	jne	L767
	cmpl	$-1, %edx
	je	L767
	movl	%edx, %ecx
	movl	$-1, %edx
L767:
	cmpl	$54, %ecx
	je	L769
	cmpl	$21, %ecx
	jne	L768
L769:
	cmpl	$-1, %edx
	je	L768
	movl	%ecx, %eax
	movl	%edx, %ecx
	movl	%eax, %edx
L768:
	movl	$0, %eax
	cmpl	%edx, %ecx
	je	L662
	cmpl	$-1, %edx
	je	L771
	cmpl	$-1, %ecx
	je	L802
	leal	-6(%edx), %eax
	cmpl	$1, %eax
	jbe	L802
	cmpl	$54, %ecx
	je	L802
	cmpl	$21, %ecx
	je	L802
L771:
	cmpl	$-1, %ecx
	jne	L773
L802:
	movl	$0, %eax
	jmp	L662
L773:
	movl	$-1, %ebx
	cmpl	$-1, %edx
	je	L774
	movl	%edx, %eax
	sall	$8, %eax
	addl	%ecx, %eax
	cmpl	$5383, %eax
	je	L777
	cmpl	$5383, %eax
	jg	L782
	cmpl	$5382, %eax
	je	L779
	jmp	L783
L782:
	cmpl	$13830, %eax
	je	L778
	cmpl	$13831, %eax
	jne	L783
	movl	$0, %ebx
	jmp	L783
L777:
	movl	$1, %ebx
	jmp	L783
L778:
	movl	$2, %ebx
	jmp	L783
L779:
	movl	$3, %ebx
	jmp	L783
L774:
	cmpl	$7, %ecx
	je	L788
	cmpl	$7, %ecx
	jg	L791
	cmpl	$6, %ecx
	je	L787
	jmp	L783
L791:
	cmpl	$21, %ecx
	je	L786
	cmpl	$54, %ecx
	jne	L783
	movl	$4, %ebx
	jmp	L783
L786:
	movl	$5, %ebx
	jmp	L783
L787:
	movl	$6, %ebx
	jmp	L783
L788:
	movl	$7, %ebx
L783:
	movl	$0, %eax
	cmpl	$-1, %ebx
	je	L662
	cmpl	$0, -16(%ebp)
	jne	L793
	cmpl	$-1, -20(%ebp)
	jne	L793
	cmpl	$0, 24(%ebp)
	jne	L793
	cmpl	$6, %ebx
	je	L793
	testb	$3, 40(%esi)
	jne	L793
	movl	$0, %eax
	jmp	L794
L793:
	movl	40(%esi), %edx
	testl	$1, %edx
	jne	L796
	movl	-16(%ebp), %eax
	subl	$-128, %eax
	cmpl	$255, %eax
	ja	L795
	cmpl	$-1, -20(%ebp)
	jne	L795
	cmpl	$0, 24(%ebp)
	jne	L795
	testl	$2, %edx
	jne	L795
L796:
	movl	$1, %eax
	jmp	L794
L795:
	movl	$2, %eax
L794:
	movl	$0, (%edi)
	movl	%eax, 4(%edi)
	movl	%eax, %edx
L803:
	sall	$6, %edx
	movl	20(%ebp), %eax
	sall	$3, %eax
	orb	%dl, %al
	orb	%bl, %al
L804:
	movb	%al, 12(%edi)
L672:
	movl	(%edi), %eax
	addl	4(%edi), %eax
	incl	%eax
	movl	%eax, 8(%edi)
	movl	%edi, %eax
L662:
	addl	$24, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_chsize;	.scl	3;	.type	32;	.endef
_chsize:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	(%edx), %eax
	notl	%eax
	testl	$2113536, %eax
	jne	L806
	movl	12(%edx), %eax
	movl	8(%edx), %ecx
	cmpl	$0, 16(%edx)
	jne	L807
	movl	$-1, %eax
L807:
	cmpl	$-1, %eax
	jne	L808
	cmpl	$-1, %ecx
	jne	L808
	movl	$0, %eax
	cmpl	$0, 4(%edx)
	je	L805
	cmpl	%ebx, 4(%edx)
	je	L805
	movl	$1, %eax
	jmp	L805
L808:
	cmpl	$33, %eax
	je	L811
	cmpl	$35, %eax
	je	L811
	cmpl	$36, %eax
	je	L811
	cmpl	$38, %eax
	je	L811
	cmpl	$34, %eax
	je	L811
	cmpl	$41, %eax
	je	L811
	cmpl	$40, %eax
	je	L811
	cmpl	$37, %eax
	je	L811
	cmpl	$33, %ecx
	je	L811
	cmpl	$35, %ecx
	je	L811
	cmpl	$36, %ecx
	je	L811
	cmpl	$38, %ecx
	je	L811
	cmpl	$34, %ecx
	je	L811
	cmpl	$41, %ecx
	je	L811
	cmpl	$40, %ecx
	je	L811
	cmpl	$37, %ecx
	jne	L810
L811:
	cmpl	$16, %ebx
	jmp	L814
L810:
	cmpl	$32, %ebx
L814:
	sete	%al
	movzbl	%al, %eax
	jmp	L805
L806:
	movl	$0, %eax
L805:
	popl	%ebx
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _cpu,16
.lcomm _errfunc,16
.lcomm _outfmt,16
.lcomm _list,16
	.def	_ftell;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_fread;	.scl	2;	.type	32;	.endef
	.def	_fseek;	.scl	2;	.type	32;	.endef
	.def	_pp_get_include_path_ptr;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_strcat;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_src_get;	.scl	2;	.type	32;	.endef
