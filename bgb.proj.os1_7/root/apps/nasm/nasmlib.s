	.file	"nasmlib.c"
	.text
	.align 2
.globl _nasm_set_malloc_error
	.def	_nasm_set_malloc_error;	.scl	2;	.type	32;	.endef
_nasm_set_malloc_error:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, _nasm_malloc_error
	popl	%ebp
	ret
LC0:
	.ascii "out of memory\0"
	.align 2
.globl _nasm_malloc
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
_nasm_malloc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L3
	movl	$18, (%esp)
	movl	$LC0, 4(%esp)
	call	*_nasm_malloc_error
L3:
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_realloc
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
_nasm_realloc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	testl	%eax, %eax
	je	L5
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_realloc
	jmp	L8
L5:
	movl	%edx, (%esp)
	call	_malloc
L8:
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L7
	movl	$18, (%esp)
	movl	$LC0, 4(%esp)
	call	*_nasm_malloc_error
L7:
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_free
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
_nasm_free:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	je	L9
	movl	%eax, (%esp)
	call	_free
L9:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_strdup
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
_nasm_strdup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	%esi, (%esp)
	call	_strlen
	incl	%eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L12
	movl	$18, (%esp)
	movl	$LC0, 4(%esp)
	call	*_nasm_malloc_error
L12:
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	%ebx, %eax
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_strndup
	.def	_nasm_strndup;	.scl	2;	.type	32;	.endef
_nasm_strndup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	12(%ebp), %esi
	leal	1(%esi), %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L14
	movl	$18, (%esp)
	movl	$LC0, 4(%esp)
	call	*_nasm_malloc_error
L14:
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_strncpy
	movb	$0, (%esi,%ebx)
	movl	%ebx, %eax
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_stricmp
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
_nasm_stricmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	jmp	L16
L20:
	incl	%esi
	incl	%edi
L16:
	cmpb	$0, (%esi)
	je	L25
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_tolower
	movl	%eax, %ebx
	movsbl	(%edi),%eax
	movl	%eax, (%esp)
	call	_tolower
	cmpl	%eax, %ebx
	je	L20
	cmpb	$0, (%esi)
	jne	L21
L25:
	cmpb	$0, (%edi)
	jne	L21
	movl	$0, %eax
	jmp	L15
L21:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_tolower
	movl	%eax, %ebx
	movsbl	(%edi),%eax
	movl	%eax, (%esp)
	call	_tolower
	cmpl	%eax, %ebx
	setge	%al
	movzbl	%al, %eax
	leal	-1(%eax,%eax), %eax
L15:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _nasm_strnicmp
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
_nasm_strnicmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %edi
	jmp	L27
L31:
	incl	%esi
	incl	12(%ebp)
	decl	%edi
L27:
	testl	%edi, %edi
	jle	L28
	cmpb	$0, (%esi)
	je	L38
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_tolower
	movl	%eax, %ebx
	movl	12(%ebp), %edx
	movsbl	(%edx),%eax
	movl	%eax, (%esp)
	call	_tolower
	cmpl	%eax, %ebx
	je	L31
L28:
	cmpb	$0, (%esi)
	jne	L34
L38:
	movl	12(%ebp), %eax
	cmpb	$0, (%eax)
	je	L33
L34:
	testl	%edi, %edi
	jne	L32
L33:
	movl	$0, %eax
	jmp	L26
L32:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_tolower
	movl	%eax, %ebx
	movl	12(%ebp), %edx
	movsbl	(%edx),%eax
	movl	%eax, (%esp)
	call	_tolower
	cmpl	%eax, %ebx
	setge	%al
	movzbl	%al, %eax
	leal	-1(%eax,%eax), %eax
L26:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC1:
	.ascii "numeric constant %s does not fit in 32 bits\0"
	.align 2
.globl _readnum
	.def	_readnum;	.scl	2;	.type	32;	.endef
_readnum:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	$0, -20(%ebp)
	movl	$1, -24(%ebp)
	movl	12(%ebp), %eax
	movl	$0, (%eax)
	jmp	L40
L43:
	incl	%esi
L40:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L43
	cmpb	$45, (%esi)
	jne	L44
	incl	%esi
	movl	$-1, -24(%ebp)
L44:
	movl	%esi, %ebx
	jmp	L45
L48:
	incl	%ebx
L45:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	jne	L48
	cmpb	$36, (%ebx)
	je	L48
	cmpb	$48, (%esi)
	jne	L49
	cmpb	$120, 1(%esi)
	je	L50
	cmpb	$88, 1(%esi)
	jne	L49
L50:
	movl	$16, -16(%ebp)
	addl	$2, %esi
	jmp	L51
L49:
	cmpb	$36, (%esi)
	jne	L52
	movl	$16, -16(%ebp)
	incl	%esi
	jmp	L51
L52:
	cmpb	$72, -1(%ebx)
	je	L55
	cmpb	$104, -1(%ebx)
	jne	L54
L55:
	movl	$16, -16(%ebp)
	jmp	L81
L54:
	cmpb	$81, -1(%ebx)
	je	L58
	cmpb	$113, -1(%ebx)
	je	L58
	cmpb	$79, -1(%ebx)
	je	L58
	cmpb	$111, -1(%ebx)
	jne	L57
L58:
	movl	$8, -16(%ebp)
	jmp	L81
L57:
	cmpb	$66, -1(%ebx)
	je	L61
	cmpb	$98, -1(%ebx)
	jne	L60
L61:
	movl	$2, -16(%ebp)
L81:
	decl	%ebx
	jmp	L51
L60:
	movl	$10, -16(%ebp)
L51:
	cmpl	%ebx, %esi
	jb	L63
	movl	12(%ebp), %edi
	movl	$1, (%edi)
	jmp	L82
L63:
	movl	-16(%ebp), %edx
	sarl	%edx
	movl	$-2147483648, %eax
	movl	%edx, %edi
	movl	$0, %edx
	divl	%edi
	movl	%eax, %ecx
	cmpl	$10, -16(%ebp)
	sete	%al
	movzbl	%al, %edx
	decl	%edx
	andl	$-6, %edx
	addl	$6, %edx
	movl	$0, %edi
	cmpb	$0, (%esi)
	je	L67
	cmpl	%ebx, %esi
	jae	L67
L78:
	cmpb	$47, (%esi)
	jle	L71
	movzbl	(%esi), %eax
	subb	$58, %al
	cmpb	$6, %al
	jbe	L71
	cmpb	$96, (%esi)
	jle	L72
	movsbl	(%esi),%eax
	subl	$87, %eax
	jmp	L73
L72:
	cmpb	$64, (%esi)
	jle	L74
	movsbl	(%esi),%eax
	subl	$55, %eax
	jmp	L73
L74:
	movsbl	(%esi),%eax
	subl	$48, %eax
L73:
	cmpl	-16(%ebp), %eax
	jl	L70
L71:
	movl	12(%ebp), %eax
	movl	$1, (%eax)
L82:
	movl	$0, %eax
	jmp	L39
L70:
	cmpl	%ecx, %edi
	ja	L77
	cmpl	%ecx, %edi
	jne	L76
	cmpl	%edx, %eax
	jl	L76
L77:
	movl	$1, -20(%ebp)
L76:
	imull	-16(%ebp), %edi
	addl	%eax, %edi
	incl	%esi
	cmpb	$0, (%esi)
	je	L67
	cmpl	%ebx, %esi
	jb	L78
L67:
	cmpl	$0, -20(%ebp)
	je	L79
	movl	$1088, (%esp)
	movl	$LC1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_nasm_malloc_error
L79:
	movl	-24(%ebp), %eax
	imull	%edi, %eax
L39:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _readstrnum
	.def	_readstrnum;	.scl	2;	.type	32;	.endef
_readstrnum:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	movl	$0, %eax
	movl	$0, (%edi)
	addl	%esi, %ecx
	movl	$0, %ebx
	cmpl	%esi, %eax
	jge	L91
L89:
	testl	$-16777216, %eax
	je	L88
	movl	$1, (%edi)
L88:
	movl	%eax, %edx
	sall	$8, %edx
	decl	%ecx
	movzbl	(%ecx), %eax
	leal	(%eax,%edx), %eax
	incl	%ebx
	cmpl	%esi, %ebx
	jl	L89
L91:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _seg_init
	.def	_seg_init;	.scl	2;	.type	32;	.endef
_seg_init:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, _next_seg
	popl	%ebp
	ret
	.align 2
.globl _seg_alloc
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
_seg_alloc:
	pushl	%ebp
	movl	%esp, %ebp
	movl	_next_seg, %eax
	leal	2(%eax), %edx
	movl	%edx, _next_seg
	popl	%ebp
	ret
	.align 2
.globl _fwriteshort
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
_fwriteshort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movzbl	%bl,%eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	movzbl	%bh, %ebx
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _fwritelong
	.def	_fwritelong;	.scl	2;	.type	32;	.endef
_fwritelong:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movzbl	%bl,%eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	movzbl	%bh, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	movl	%ebx, %eax
	sarl	$16, %eax
	andl	$255, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	shrl	$24, %ebx
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	call	_fputc
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC2:
	.ascii "file name already ends in `%s': output will be in `nasm.out'\0"
	.align 32
LC3:
	.ascii "file name already has no extension: output will be in `nasm.out'\0"
LC4:
	.ascii "nasm.out\0"
	.align 2
.globl _standard_extension
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
_standard_extension:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	cmpb	$0, (%esi)
	jne	L96
	movl	8(%ebp), %edx
	movl	%esi, %ebx
	cmpb	$0, (%edx)
	je	L116
L101:
	movzbl	(%edx), %eax
	movb	%al, (%ebx)
	incl	%edx
	incl	%ebx
	cmpb	$0, (%edx)
	jne	L101
L116:
	movb	$0, (%ebx)
L102:
	cmpl	%esi, %ebx
	jbe	L103
	decl	%ebx
	cmpb	$46, (%ebx)
	jne	L102
	jmp	L106
L103:
	cmpb	$46, (%ebx)
	je	L106
	cmpb	$0, (%ebx)
	je	L106
L110:
	incl	%ebx
	cmpb	$0, (%ebx)
	jne	L110
L106:
	movl	%ebx, (%esp)
	movl	%edi, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L111
	cmpb	$0, (%edi)
	je	L112
	movl	$16, (%esp)
	movl	$LC2, 4(%esp)
	movl	%edi, 8(%esp)
	call	*20(%ebp)
	jmp	L113
L112:
	movl	$16, (%esp)
	movl	$LC3, 4(%esp)
	call	*20(%ebp)
L113:
	movl	%esi, (%esp)
	movl	$LC4, 4(%esp)
	jmp	L118
L111:
	movl	%ebx, (%esp)
	movl	%edi, 4(%esp)
L118:
	call	_strcpy
L96:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_real_raa_init;	.scl	3;	.type	32;	.endef
_real_raa_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	jne	L120
	movl	$16392, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	$0, (%eax)
	leal	8(%eax), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$16384, 8(%esp)
	call	_memset
	movl	$1, 4(%esi)
	jmp	L121
L120:
	movl	$4104, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%ebx, (%eax)
	movl	$0, %eax
L126:
	movl	$0, 8(%esi,%eax,4)
	incl	%eax
	cmpl	$1023, %eax
	jle	L126
	movl	$4096, 4(%esi)
	decl	%ebx
	je	L121
	movl	$4096, %eax
L130:
	sall	$10, %eax
	decl	%ebx
	jne	L130
	movl	%eax, 4(%esi)
L121:
	movl	%esi, %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _raa_init
	.def	_raa_init;	.scl	2;	.type	32;	.endef
_raa_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, (%esp)
	call	_real_raa_init
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _raa_free
	.def	_raa_free;	.scl	2;	.type	32;	.endef
_raa_free:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	cmpl	$0, (%esi)
	jne	L137
	movl	%esi, (%esp)
	call	_nasm_free
	jmp	L136
L137:
	leal	8(%esi), %ebx
L144:
	cmpl	$0, (%ebx)
	je	L141
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_raa_free
L141:
	addl	$4, %ebx
	movl	%ebx, %eax
	subl	%esi, %eax
	subl	$8, %eax
	sarl	$2, %eax
	cmpl	$1023, %eax
	jle	L144
L136:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _raa_read
	.def	_raa_read;	.scl	2;	.type	32;	.endef
_raa_read:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edx
	movl	4(%ebx), %eax
	cmpl	$0, (%ebx)
	jne	L148
	sall	$12, %eax
	jmp	L158
L148:
	sall	$10, %eax
L158:
	cmpl	%eax, %edx
	jl	L147
	movl	$0, %eax
	jmp	L146
L147:
	cmpl	$0, (%ebx)
	jle	L156
L154:
	movl	%edx, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ldiv
	movl	8(%ebx,%eax,4), %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L146
	cmpl	$0, (%ebx)
	jg	L154
L156:
	movl	8(%ebx,%edx,4), %eax
L146:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 32
LC5:
	.ascii "negative position in raa_write\0"
	.align 2
.globl _raa_write
	.def	_raa_write;	.scl	2;	.type	32;	.endef
_raa_write:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	testl	%esi, %esi
	jns	L161
	movl	$3, (%esp)
	movl	$LC5, 4(%esp)
	call	*_nasm_malloc_error
	jmp	L161
L173:
	movl	$4104, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	$0, %eax
L170:
	movl	$0, 8(%edx,%eax,4)
	incl	%eax
	cmpl	$1023, %eax
	jle	L170
	movl	(%ebx), %eax
	incl	%eax
	movl	%eax, (%edx)
	movl	4(%ebx), %eax
	cmpl	$0, (%ebx)
	jne	L171
	sall	$12, %eax
	jmp	L172
L171:
	sall	$10, %eax
L172:
	movl	%eax, 4(%edx)
	movl	%ebx, 8(%edx)
	movl	%edx, %ebx
L161:
	movl	4(%ebx), %eax
	cmpl	$0, (%ebx)
	jne	L164
	sall	$12, %eax
	jmp	L183
L164:
	sall	$10, %eax
L183:
	cmpl	%esi, %eax
	jle	L173
	movl	%ebx, -20(%ebp)
	cmpl	$0, (%ebx)
	jle	L182
L178:
	movl	%esi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ldiv
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	movl	-32(%ebp), %eax
	leal	(%ebx,%eax,4), %esi
	leal	8(%esi), %edi
	cmpl	$0, 8(%esi)
	jne	L177
	movl	(%ebx), %eax
	decl	%eax
	movl	%eax, (%esp)
	call	_real_raa_init
	movl	%eax, 8(%esi)
L177:
	movl	(%edi), %ebx
	movl	-28(%ebp), %esi
	cmpl	$0, (%ebx)
	jg	L178
L182:
	movl	16(%ebp), %eax
	movl	%eax, 8(%ebx,%esi,4)
	movl	-20(%ebp), %eax
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC6:
	.ascii "SAA with huge elements\0"
	.align 2
.globl _saa_init
	.def	_saa_init;	.scl	2;	.type	32;	.endef
_saa_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	cmpl	$8192, %esi
	jle	L185
	movl	$19, (%esp)
	movl	$LC6, 4(%esp)
	call	*_nasm_malloc_error
L185:
	movl	$36, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	$0, 24(%eax)
	movl	$0, 20(%eax)
	movl	%esi, 12(%eax)
	movl	$8192, %ecx
	movl	%ecx, %eax
	cltd
	idivl	%esi
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, 16(%ebx)
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 32(%ebx)
	movl	$0, (%ebx)
	movl	%ebx, 4(%ebx)
	movl	%ebx, %eax
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _saa_free
	.def	_saa_free;	.scl	2;	.type	32;	.endef
_saa_free:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	testl	%esi, %esi
	je	L192
L190:
	movl	(%esi), %ebx
	movl	32(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%esi, (%esp)
	call	_nasm_free
	movl	%ebx, %esi
	testl	%ebx, %ebx
	jne	L190
L192:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _saa_wstruct
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
_saa_wstruct:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	4(%esi), %ebx
	movl	16(%ebx), %eax
	subl	20(%ebx), %eax
	cmpl	12(%esi), %eax
	jge	L194
	movl	$36, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	4(%esi), %edx
	movl	(%edx), %ebx
	movl	24(%edx), %eax
	addl	20(%edx), %eax
	movl	%eax, 24(%ebx)
	movl	%ebx, 4(%esi)
	movl	16(%esi), %eax
	movl	%eax, 16(%ebx)
	movl	$0, (%ebx)
	movl	$0, 20(%ebx)
	movl	16(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 32(%ebx)
L194:
	movl	4(%esi), %edx
	movl	20(%edx), %ecx
	movl	32(%edx), %eax
	addl	%ecx, %eax
	addl	12(%esi), %ecx
	movl	%ecx, 20(%edx)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _saa_wbytes
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
_saa_wbytes:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %edi
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
	testl	%edi, %edi
	jle	L206
L204:
	movl	4(%esi), %edx
	movl	16(%edx), %eax
	movl	%eax, %ebx
	subl	20(%edx), %ebx
	cmpl	%edi, %ebx
	jle	L199
	movl	%edi, %ebx
L199:
	testl	%ebx, %ebx
	jle	L200
	cmpl	$0, -16(%ebp)
	je	L201
	movl	4(%esi), %edx
	movl	32(%edx), %eax
	addl	20(%edx), %eax
	movl	%eax, (%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_memcpy
	addl	%ebx, -16(%ebp)
	jmp	L202
L201:
	movl	4(%esi), %edx
	movl	32(%edx), %eax
	addl	20(%edx), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_memset
L202:
	movl	4(%esi), %eax
	addl	%ebx, 20(%eax)
	subl	%ebx, %edi
L200:
	testl	%edi, %edi
	jle	L206
	movl	4(%esi), %ebx
	movl	$36, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	4(%esi), %edx
	movl	(%edx), %ebx
	movl	24(%edx), %eax
	addl	20(%edx), %eax
	movl	%eax, 24(%ebx)
	movl	%ebx, 4(%esi)
	movl	16(%esi), %eax
	movl	%eax, 16(%ebx)
	movl	$0, (%ebx)
	movl	$0, 20(%ebx)
	movl	16(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 32(%ebx)
	jmp	L204
L206:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _saa_rewind
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
_saa_rewind:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, 8(%eax)
	movl	$0, 28(%eax)
	popl	%ebp
	ret
	.align 2
.globl _saa_rstruct
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
_saa_rstruct:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	cmpl	$0, 8(%ecx)
	je	L212
	movl	8(%ecx), %edx
	movl	20(%edx), %eax
	subl	28(%ecx), %eax
	cmpl	12(%ecx), %eax
	jge	L210
	movl	(%edx), %eax
	movl	%eax, 8(%ecx)
	testl	%eax, %eax
	jne	L211
L212:
	movl	$0, %eax
	jmp	L208
L211:
	movl	$0, 28(%ecx)
L210:
	movl	8(%ecx), %eax
	movl	28(%ecx), %edx
	movl	32(%eax), %eax
	addl	%edx, %eax
	addl	12(%ecx), %edx
	movl	%edx, 28(%ecx)
L208:
	popl	%ebp
	ret
	.align 2
.globl _saa_rbytes
	.def	_saa_rbytes;	.scl	2;	.type	32;	.endef
_saa_rbytes:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	8(%ebp), %esi
	cmpl	$0, 8(%esi)
	jne	L214
	movl	$0, %eax
	jmp	L213
L214:
	movl	8(%esi), %eax
	movl	28(%esi), %ecx
	movl	32(%eax), %ebx
	addl	%ecx, %ebx
	movl	20(%eax), %edx
	subl	%ecx, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%esi), %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esi)
	movl	$0, 28(%esi)
	movl	%ebx, %eax
L213:
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _saa_rnbytes
	.def	_saa_rnbytes;	.scl	2;	.type	32;	.endef
_saa_rnbytes:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %edi
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
	testl	%edi, %edi
	jle	L215
L223:
	cmpl	$0, 8(%esi)
	je	L215
	movl	8(%esi), %eax
	movl	20(%eax), %eax
	movl	%eax, %ebx
	subl	28(%esi), %ebx
	cmpl	%edi, %ebx
	jle	L220
	movl	%edi, %ebx
L220:
	testl	%ebx, %ebx
	jle	L221
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%esi), %eax
	movl	32(%eax), %eax
	addl	28(%esi), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_memcpy
	addl	%ebx, -16(%ebp)
	addl	%ebx, 28(%esi)
	subl	%ebx, %edi
L221:
	testl	%edi, %edi
	jle	L215
	movl	8(%esi), %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esi)
	movl	$0, 28(%esi)
	jmp	L223
L215:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _saa_fread
	.def	_saa_fread;	.scl	2;	.type	32;	.endef
_saa_fread:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	12(%ebp), %esi
	movl	20(%ebp), %edi
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	8(%ebp), %edx
	cmpl	$0, 8(%edx)
	je	L227
	movl	8(%edx), %eax
	cmpl	24(%eax), %esi
	jge	L226
L227:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_saa_rewind
L226:
	movl	8(%ebp), %edx
	movl	8(%edx), %ebx
	movl	24(%ebx), %eax
	addl	20(%ebx), %eax
	cmpl	%eax, %esi
	jl	L240
L232:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L225
	movl	24(%ebx), %eax
	addl	20(%ebx), %eax
	cmpl	%eax, %esi
	jge	L232
L240:
	movl	%esi, %edx
	subl	24(%ebx), %edx
	testl	%edi, %edi
	je	L242
L238:
	movl	20(%ebx), %eax
	movl	%eax, %esi
	subl	%edx, %esi
	cmpl	%edi, %esi
	jle	L236
	movl	%edi, %esi
L236:
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %eax
	addl	32(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_memcpy
	subl	%esi, %edi
	addl	%esi, -16(%ebp)
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L225
	movl	$0, %edx
	testl	%edi, %edi
	jne	L238
L242:
	movl	8(%ebp), %edx
	movl	%ebx, 8(%edx)
L225:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _saa_fwrite
	.def	_saa_fwrite;	.scl	2;	.type	32;	.endef
_saa_fwrite:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	12(%ebp), %esi
	movl	20(%ebp), %edi
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	8(%ebp), %edx
	cmpl	$0, 8(%edx)
	je	L245
	movl	8(%edx), %eax
	cmpl	24(%eax), %esi
	jge	L244
L245:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_saa_rewind
L244:
	movl	8(%ebp), %edx
	movl	8(%edx), %ebx
	movl	24(%ebx), %eax
	addl	20(%ebx), %eax
	cmpl	%eax, %esi
	jl	L258
L250:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L243
	movl	24(%ebx), %eax
	addl	20(%ebx), %eax
	cmpl	%eax, %esi
	jge	L250
L258:
	movl	%esi, %edx
	subl	24(%ebx), %edx
	testl	%edi, %edi
	je	L260
L256:
	movl	20(%ebx), %eax
	movl	%eax, %esi
	subl	%edx, %esi
	cmpl	%edi, %esi
	jle	L254
	movl	%edi, %esi
L254:
	movl	%edx, %eax
	addl	32(%ebx), %eax
	movl	%eax, (%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_memcpy
	subl	%esi, %edi
	addl	%esi, -16(%ebp)
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L243
	movl	$0, %edx
	testl	%edi, %edi
	jne	L256
L260:
	movl	8(%ebp), %edx
	movl	%ebx, 8(%edx)
L243:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _saa_fpwrite
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
_saa_fpwrite:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	%esi, (%esp)
	call	_saa_rewind
	leal	-16(%ebp), %ebx
	jmp	L262
L265:
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_fwrite
L262:
	movl	%esi, (%esp)
	movl	%ebx, 4(%esp)
	call	_saa_rbytes
	testl	%eax, %eax
	jne	L265
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC7:
	.ascii "a\0"
LC8:
	.ascii "ae\0"
LC9:
	.ascii "b\0"
LC10:
	.ascii "be\0"
LC11:
	.ascii "c\0"
LC12:
	.ascii "e\0"
LC13:
	.ascii "g\0"
LC14:
	.ascii "ge\0"
LC15:
	.ascii "l\0"
LC16:
	.ascii "le\0"
LC17:
	.ascii "na\0"
LC18:
	.ascii "nae\0"
LC19:
	.ascii "nb\0"
LC20:
	.ascii "nbe\0"
LC21:
	.ascii "nc\0"
LC22:
	.ascii "ne\0"
LC23:
	.ascii "ng\0"
LC24:
	.ascii "nge\0"
LC25:
	.ascii "nl\0"
LC26:
	.ascii "nle\0"
LC27:
	.ascii "no\0"
LC28:
	.ascii "np\0"
LC29:
	.ascii "ns\0"
LC30:
	.ascii "nz\0"
LC31:
	.ascii "o\0"
LC32:
	.ascii "p\0"
LC33:
	.ascii "pe\0"
LC34:
	.ascii "po\0"
LC35:
	.ascii "s\0"
LC36:
	.ascii "z\0"
	.data
	.align 32
_conditions:
	.long	LC7
	.long	LC8
	.long	LC9
	.long	LC10
	.long	LC11
	.long	LC12
	.long	LC13
	.long	LC14
	.long	LC15
	.long	LC16
	.long	LC17
	.long	LC18
	.long	LC19
	.long	LC20
	.long	LC21
	.long	LC22
	.long	LC23
	.long	LC24
	.long	LC25
	.long	LC26
	.long	LC27
	.long	LC28
	.long	LC29
	.long	LC30
	.long	LC31
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
	.text
LC37:
	.ascii "ah\0"
LC38:
	.ascii "al\0"
LC39:
	.ascii "ax\0"
LC40:
	.ascii "bh\0"
LC41:
	.ascii "bl\0"
LC42:
	.ascii "bp\0"
LC43:
	.ascii "bx\0"
LC44:
	.ascii "ch\0"
LC45:
	.ascii "cl\0"
LC46:
	.ascii "cr0\0"
LC47:
	.ascii "cr1\0"
LC48:
	.ascii "cr2\0"
LC49:
	.ascii "cr3\0"
LC50:
	.ascii "cr4\0"
LC51:
	.ascii "cr5\0"
LC52:
	.ascii "cr6\0"
LC53:
	.ascii "cr7\0"
LC54:
	.ascii "cs\0"
LC55:
	.ascii "cx\0"
LC56:
	.ascii "dh\0"
LC57:
	.ascii "di\0"
LC58:
	.ascii "dl\0"
LC59:
	.ascii "dr0\0"
LC60:
	.ascii "dr1\0"
LC61:
	.ascii "dr2\0"
LC62:
	.ascii "dr3\0"
LC63:
	.ascii "dr4\0"
LC64:
	.ascii "dr5\0"
LC65:
	.ascii "dr6\0"
LC66:
	.ascii "dr7\0"
LC67:
	.ascii "ds\0"
LC68:
	.ascii "dx\0"
LC69:
	.ascii "eax\0"
LC70:
	.ascii "ebp\0"
LC71:
	.ascii "ebx\0"
LC72:
	.ascii "ecx\0"
LC73:
	.ascii "edi\0"
LC74:
	.ascii "edx\0"
LC75:
	.ascii "es\0"
LC76:
	.ascii "esi\0"
LC77:
	.ascii "esp\0"
LC78:
	.ascii "fs\0"
LC79:
	.ascii "gs\0"
LC80:
	.ascii "mm0\0"
LC81:
	.ascii "mm1\0"
LC82:
	.ascii "mm2\0"
LC83:
	.ascii "mm3\0"
LC84:
	.ascii "mm4\0"
LC85:
	.ascii "mm5\0"
LC86:
	.ascii "mm6\0"
LC87:
	.ascii "mm7\0"
LC88:
	.ascii "segr6\0"
LC89:
	.ascii "segr7\0"
LC90:
	.ascii "si\0"
LC91:
	.ascii "sp\0"
LC92:
	.ascii "ss\0"
LC93:
	.ascii "st0\0"
LC94:
	.ascii "st1\0"
LC95:
	.ascii "st2\0"
LC96:
	.ascii "st3\0"
LC97:
	.ascii "st4\0"
LC98:
	.ascii "st5\0"
LC99:
	.ascii "st6\0"
LC100:
	.ascii "st7\0"
LC101:
	.ascii "tr0\0"
LC102:
	.ascii "tr1\0"
LC103:
	.ascii "tr2\0"
LC104:
	.ascii "tr3\0"
LC105:
	.ascii "tr4\0"
LC106:
	.ascii "tr5\0"
LC107:
	.ascii "tr6\0"
LC108:
	.ascii "tr7\0"
LC109:
	.ascii "xmm0\0"
LC110:
	.ascii "xmm1\0"
LC111:
	.ascii "xmm2\0"
LC112:
	.ascii "xmm3\0"
LC113:
	.ascii "xmm4\0"
LC114:
	.ascii "xmm5\0"
LC115:
	.ascii "xmm6\0"
LC116:
	.ascii "xmm7\0"
	.data
	.align 32
_reg_names:
	.long	LC37
	.long	LC38
	.long	LC39
	.long	LC40
	.long	LC41
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC48
	.long	LC49
	.long	LC50
	.long	LC51
	.long	LC52
	.long	LC53
	.long	LC54
	.long	LC55
	.long	LC56
	.long	LC57
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	LC62
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC69
	.long	LC70
	.long	LC71
	.long	LC72
	.long	LC73
	.long	LC74
	.long	LC75
	.long	LC76
	.long	LC77
	.long	LC78
	.long	LC79
	.long	LC80
	.long	LC81
	.long	LC82
	.long	LC83
	.long	LC84
	.long	LC85
	.long	LC86
	.long	LC87
	.long	LC88
	.long	LC89
	.long	LC90
	.long	LC91
	.long	LC92
	.long	LC93
	.long	LC94
	.long	LC95
	.long	LC96
	.long	LC97
	.long	LC98
	.long	LC99
	.long	LC100
	.long	LC101
	.long	LC102
	.long	LC103
	.long	LC104
	.long	LC105
	.long	LC106
	.long	LC107
	.long	LC108
	.long	LC109
	.long	LC110
	.long	LC111
	.long	LC112
	.long	LC113
	.long	LC114
	.long	LC115
	.long	LC116
	.text
LC117:
	.ascii "aaa\0"
LC118:
	.ascii "aad\0"
LC119:
	.ascii "aam\0"
LC120:
	.ascii "aas\0"
LC121:
	.ascii "adc\0"
LC122:
	.ascii "add\0"
LC123:
	.ascii "addpd\0"
LC124:
	.ascii "addps\0"
LC125:
	.ascii "addsd\0"
LC126:
	.ascii "addss\0"
LC127:
	.ascii "addsubpd\0"
LC128:
	.ascii "addsubps\0"
LC129:
	.ascii "and\0"
LC130:
	.ascii "andnpd\0"
LC131:
	.ascii "andnps\0"
LC132:
	.ascii "andpd\0"
LC133:
	.ascii "andps\0"
LC134:
	.ascii "arpl\0"
LC135:
	.ascii "bound\0"
LC136:
	.ascii "bsf\0"
LC137:
	.ascii "bsr\0"
LC138:
	.ascii "bswap\0"
LC139:
	.ascii "bt\0"
LC140:
	.ascii "btc\0"
LC141:
	.ascii "btr\0"
LC142:
	.ascii "bts\0"
LC143:
	.ascii "call\0"
LC144:
	.ascii "cbw\0"
LC145:
	.ascii "cdq\0"
LC146:
	.ascii "clc\0"
LC147:
	.ascii "cld\0"
LC148:
	.ascii "clflush\0"
LC149:
	.ascii "cli\0"
LC150:
	.ascii "clts\0"
LC151:
	.ascii "cmc\0"
LC152:
	.ascii "cmp\0"
LC153:
	.ascii "cmpeqpd\0"
LC154:
	.ascii "cmpeqps\0"
LC155:
	.ascii "cmpeqsd\0"
LC156:
	.ascii "cmpeqss\0"
LC157:
	.ascii "cmplepd\0"
LC158:
	.ascii "cmpleps\0"
LC159:
	.ascii "cmplesd\0"
LC160:
	.ascii "cmpless\0"
LC161:
	.ascii "cmpltpd\0"
LC162:
	.ascii "cmpltps\0"
LC163:
	.ascii "cmpltsd\0"
LC164:
	.ascii "cmpltss\0"
LC165:
	.ascii "cmpneqpd\0"
LC166:
	.ascii "cmpneqps\0"
LC167:
	.ascii "cmpneqsd\0"
LC168:
	.ascii "cmpneqss\0"
LC169:
	.ascii "cmpnlepd\0"
LC170:
	.ascii "cmpnleps\0"
LC171:
	.ascii "cmpnlesd\0"
LC172:
	.ascii "cmpnless\0"
LC173:
	.ascii "cmpnltpd\0"
LC174:
	.ascii "cmpnltps\0"
LC175:
	.ascii "cmpnltsd\0"
LC176:
	.ascii "cmpnltss\0"
LC177:
	.ascii "cmpordpd\0"
LC178:
	.ascii "cmpordps\0"
LC179:
	.ascii "cmpordsd\0"
LC180:
	.ascii "cmpordss\0"
LC181:
	.ascii "cmppd\0"
LC182:
	.ascii "cmpps\0"
LC183:
	.ascii "cmpsb\0"
LC184:
	.ascii "cmpsd\0"
LC185:
	.ascii "cmpss\0"
LC186:
	.ascii "cmpsw\0"
LC187:
	.ascii "cmpunordpd\0"
LC188:
	.ascii "cmpunordps\0"
LC189:
	.ascii "cmpunordsd\0"
LC190:
	.ascii "cmpunordss\0"
LC191:
	.ascii "cmpxchg\0"
LC192:
	.ascii "cmpxchg486\0"
LC193:
	.ascii "cmpxchg8b\0"
LC194:
	.ascii "comisd\0"
LC195:
	.ascii "comiss\0"
LC196:
	.ascii "cpuid\0"
LC197:
	.ascii "cvtdq2pd\0"
LC198:
	.ascii "cvtdq2ps\0"
LC199:
	.ascii "cvtpd2dq\0"
LC200:
	.ascii "cvtpd2pi\0"
LC201:
	.ascii "cvtpd2ps\0"
LC202:
	.ascii "cvtpi2pd\0"
LC203:
	.ascii "cvtpi2ps\0"
LC204:
	.ascii "cvtps2dq\0"
LC205:
	.ascii "cvtps2pd\0"
LC206:
	.ascii "cvtps2pi\0"
LC207:
	.ascii "cvtsd2si\0"
LC208:
	.ascii "cvtsd2ss\0"
LC209:
	.ascii "cvtsi2sd\0"
LC210:
	.ascii "cvtsi2ss\0"
LC211:
	.ascii "cvtss2sd\0"
LC212:
	.ascii "cvtss2si\0"
LC213:
	.ascii "cvttpd2dq\0"
LC214:
	.ascii "cvttpd2pi\0"
LC215:
	.ascii "cvttps2dq\0"
LC216:
	.ascii "cvttps2pi\0"
LC217:
	.ascii "cvttsd2si\0"
LC218:
	.ascii "cvttss2si\0"
LC219:
	.ascii "cwd\0"
LC220:
	.ascii "cwde\0"
LC221:
	.ascii "daa\0"
LC222:
	.ascii "das\0"
LC223:
	.ascii "db\0"
LC224:
	.ascii "dd\0"
LC225:
	.ascii "dec\0"
LC226:
	.ascii "div\0"
LC227:
	.ascii "divpd\0"
LC228:
	.ascii "divps\0"
LC229:
	.ascii "divsd\0"
LC230:
	.ascii "divss\0"
LC231:
	.ascii "dq\0"
LC232:
	.ascii "dt\0"
LC233:
	.ascii "dw\0"
LC234:
	.ascii "emms\0"
LC235:
	.ascii "enter\0"
LC236:
	.ascii "equ\0"
LC237:
	.ascii "f2xm1\0"
LC238:
	.ascii "fabs\0"
LC239:
	.ascii "fadd\0"
LC240:
	.ascii "faddp\0"
LC241:
	.ascii "fbld\0"
LC242:
	.ascii "fbstp\0"
LC243:
	.ascii "fchs\0"
LC244:
	.ascii "fclex\0"
LC245:
	.ascii "fcmovb\0"
LC246:
	.ascii "fcmovbe\0"
LC247:
	.ascii "fcmove\0"
LC248:
	.ascii "fcmovnb\0"
LC249:
	.ascii "fcmovnbe\0"
LC250:
	.ascii "fcmovne\0"
LC251:
	.ascii "fcmovnu\0"
LC252:
	.ascii "fcmovu\0"
LC253:
	.ascii "fcom\0"
LC254:
	.ascii "fcomi\0"
LC255:
	.ascii "fcomip\0"
LC256:
	.ascii "fcomp\0"
LC257:
	.ascii "fcompp\0"
LC258:
	.ascii "fcos\0"
LC259:
	.ascii "fdecstp\0"
LC260:
	.ascii "fdisi\0"
LC261:
	.ascii "fdiv\0"
LC262:
	.ascii "fdivp\0"
LC263:
	.ascii "fdivr\0"
LC264:
	.ascii "fdivrp\0"
LC265:
	.ascii "femms\0"
LC266:
	.ascii "feni\0"
LC267:
	.ascii "ffree\0"
LC268:
	.ascii "ffreep\0"
LC269:
	.ascii "fiadd\0"
LC270:
	.ascii "ficom\0"
LC271:
	.ascii "ficomp\0"
LC272:
	.ascii "fidiv\0"
LC273:
	.ascii "fidivr\0"
LC274:
	.ascii "fild\0"
LC275:
	.ascii "fimul\0"
LC276:
	.ascii "fincstp\0"
LC277:
	.ascii "finit\0"
LC278:
	.ascii "fist\0"
LC279:
	.ascii "fistp\0"
LC280:
	.ascii "fisttp\0"
LC281:
	.ascii "fisub\0"
LC282:
	.ascii "fisubr\0"
LC283:
	.ascii "fld\0"
LC284:
	.ascii "fld1\0"
LC285:
	.ascii "fldcw\0"
LC286:
	.ascii "fldenv\0"
LC287:
	.ascii "fldl2e\0"
LC288:
	.ascii "fldl2t\0"
LC289:
	.ascii "fldlg2\0"
LC290:
	.ascii "fldln2\0"
LC291:
	.ascii "fldpi\0"
LC292:
	.ascii "fldz\0"
LC293:
	.ascii "fmul\0"
LC294:
	.ascii "fmulp\0"
LC295:
	.ascii "fnclex\0"
LC296:
	.ascii "fndisi\0"
LC297:
	.ascii "fneni\0"
LC298:
	.ascii "fninit\0"
LC299:
	.ascii "fnop\0"
LC300:
	.ascii "fnsave\0"
LC301:
	.ascii "fnstcw\0"
LC302:
	.ascii "fnstenv\0"
LC303:
	.ascii "fnstsw\0"
LC304:
	.ascii "fpatan\0"
LC305:
	.ascii "fprem\0"
LC306:
	.ascii "fprem1\0"
LC307:
	.ascii "fptan\0"
LC308:
	.ascii "frndint\0"
LC309:
	.ascii "frstor\0"
LC310:
	.ascii "fsave\0"
LC311:
	.ascii "fscale\0"
LC312:
	.ascii "fsetpm\0"
LC313:
	.ascii "fsin\0"
LC314:
	.ascii "fsincos\0"
LC315:
	.ascii "fsqrt\0"
LC316:
	.ascii "fst\0"
LC317:
	.ascii "fstcw\0"
LC318:
	.ascii "fstenv\0"
LC319:
	.ascii "fstp\0"
LC320:
	.ascii "fstsw\0"
LC321:
	.ascii "fsub\0"
LC322:
	.ascii "fsubp\0"
LC323:
	.ascii "fsubr\0"
LC324:
	.ascii "fsubrp\0"
LC325:
	.ascii "ftst\0"
LC326:
	.ascii "fucom\0"
LC327:
	.ascii "fucomi\0"
LC328:
	.ascii "fucomip\0"
LC329:
	.ascii "fucomp\0"
LC330:
	.ascii "fucompp\0"
LC331:
	.ascii "fwait\0"
LC332:
	.ascii "fxam\0"
LC333:
	.ascii "fxch\0"
LC334:
	.ascii "fxrstor\0"
LC335:
	.ascii "fxsave\0"
LC336:
	.ascii "fxtract\0"
LC337:
	.ascii "fyl2x\0"
LC338:
	.ascii "fyl2xp1\0"
LC339:
	.ascii "haddpd\0"
LC340:
	.ascii "haddps\0"
LC341:
	.ascii "hlt\0"
LC342:
	.ascii "hsubpd\0"
LC343:
	.ascii "hsubps\0"
LC344:
	.ascii "ibts\0"
LC345:
	.ascii "icebp\0"
LC346:
	.ascii "idiv\0"
LC347:
	.ascii "imul\0"
LC348:
	.ascii "in\0"
LC349:
	.ascii "inc\0"
LC350:
	.ascii "incbin\0"
LC351:
	.ascii "insb\0"
LC352:
	.ascii "insd\0"
LC353:
	.ascii "insw\0"
LC354:
	.ascii "int\0"
LC355:
	.ascii "int01\0"
LC356:
	.ascii "int03\0"
LC357:
	.ascii "int1\0"
LC358:
	.ascii "int3\0"
LC359:
	.ascii "into\0"
LC360:
	.ascii "invd\0"
LC361:
	.ascii "invlpg\0"
LC362:
	.ascii "iret\0"
LC363:
	.ascii "iretd\0"
LC364:
	.ascii "iretw\0"
LC365:
	.ascii "jcxz\0"
LC366:
	.ascii "jecxz\0"
LC367:
	.ascii "jmp\0"
LC368:
	.ascii "jmpe\0"
LC369:
	.ascii "lahf\0"
LC370:
	.ascii "lar\0"
LC371:
	.ascii "lddqu\0"
LC372:
	.ascii "ldmxcsr\0"
LC373:
	.ascii "lds\0"
LC374:
	.ascii "lea\0"
LC375:
	.ascii "leave\0"
LC376:
	.ascii "les\0"
LC377:
	.ascii "lfence\0"
LC378:
	.ascii "lfs\0"
LC379:
	.ascii "lgdt\0"
LC380:
	.ascii "lgs\0"
LC381:
	.ascii "lidt\0"
LC382:
	.ascii "lldt\0"
LC383:
	.ascii "lmsw\0"
LC384:
	.ascii "loadall\0"
LC385:
	.ascii "loadall286\0"
LC386:
	.ascii "lodsb\0"
LC387:
	.ascii "lodsd\0"
LC388:
	.ascii "lodsw\0"
LC389:
	.ascii "loop\0"
LC390:
	.ascii "loope\0"
LC391:
	.ascii "loopne\0"
LC392:
	.ascii "loopnz\0"
LC393:
	.ascii "loopz\0"
LC394:
	.ascii "lsl\0"
LC395:
	.ascii "lss\0"
LC396:
	.ascii "ltr\0"
LC397:
	.ascii "maskmovdqu\0"
LC398:
	.ascii "maskmovq\0"
LC399:
	.ascii "maxpd\0"
LC400:
	.ascii "maxps\0"
LC401:
	.ascii "maxsd\0"
LC402:
	.ascii "maxss\0"
LC403:
	.ascii "mfence\0"
LC404:
	.ascii "minpd\0"
LC405:
	.ascii "minps\0"
LC406:
	.ascii "minsd\0"
LC407:
	.ascii "minss\0"
LC408:
	.ascii "monitor\0"
LC409:
	.ascii "mov\0"
LC410:
	.ascii "movapd\0"
LC411:
	.ascii "movaps\0"
LC412:
	.ascii "movd\0"
LC413:
	.ascii "movddup\0"
LC414:
	.ascii "movdq2q\0"
LC415:
	.ascii "movdqa\0"
LC416:
	.ascii "movdqu\0"
LC417:
	.ascii "movhlps\0"
LC418:
	.ascii "movhpd\0"
LC419:
	.ascii "movhps\0"
LC420:
	.ascii "movlhps\0"
LC421:
	.ascii "movlpd\0"
LC422:
	.ascii "movlps\0"
LC423:
	.ascii "movmskpd\0"
LC424:
	.ascii "movmskps\0"
LC425:
	.ascii "movntdq\0"
LC426:
	.ascii "movnti\0"
LC427:
	.ascii "movntpd\0"
LC428:
	.ascii "movntps\0"
LC429:
	.ascii "movntq\0"
LC430:
	.ascii "movq\0"
LC431:
	.ascii "movq2dq\0"
LC432:
	.ascii "movsb\0"
LC433:
	.ascii "movsd\0"
LC434:
	.ascii "movshdup\0"
LC435:
	.ascii "movsldup\0"
LC436:
	.ascii "movss\0"
LC437:
	.ascii "movsw\0"
LC438:
	.ascii "movsx\0"
LC439:
	.ascii "movupd\0"
LC440:
	.ascii "movups\0"
LC441:
	.ascii "movzx\0"
LC442:
	.ascii "mul\0"
LC443:
	.ascii "mulpd\0"
LC444:
	.ascii "mulps\0"
LC445:
	.ascii "mulsd\0"
LC446:
	.ascii "mulss\0"
LC447:
	.ascii "mwait\0"
LC448:
	.ascii "neg\0"
LC449:
	.ascii "nop\0"
LC450:
	.ascii "not\0"
LC451:
	.ascii "or\0"
LC452:
	.ascii "orpd\0"
LC453:
	.ascii "orps\0"
LC454:
	.ascii "out\0"
LC455:
	.ascii "outsb\0"
LC456:
	.ascii "outsd\0"
LC457:
	.ascii "outsw\0"
LC458:
	.ascii "packssdw\0"
LC459:
	.ascii "packsswb\0"
LC460:
	.ascii "packuswb\0"
LC461:
	.ascii "paddb\0"
LC462:
	.ascii "paddd\0"
LC463:
	.ascii "paddq\0"
LC464:
	.ascii "paddsb\0"
LC465:
	.ascii "paddsiw\0"
LC466:
	.ascii "paddsw\0"
LC467:
	.ascii "paddusb\0"
LC468:
	.ascii "paddusw\0"
LC469:
	.ascii "paddw\0"
LC470:
	.ascii "pand\0"
LC471:
	.ascii "pandn\0"
LC472:
	.ascii "pause\0"
LC473:
	.ascii "paveb\0"
LC474:
	.ascii "pavgb\0"
LC475:
	.ascii "pavgusb\0"
LC476:
	.ascii "pavgw\0"
LC477:
	.ascii "pcmpeqb\0"
LC478:
	.ascii "pcmpeqd\0"
LC479:
	.ascii "pcmpeqw\0"
LC480:
	.ascii "pcmpgtb\0"
LC481:
	.ascii "pcmpgtd\0"
LC482:
	.ascii "pcmpgtw\0"
LC483:
	.ascii "pdistib\0"
LC484:
	.ascii "pextrw\0"
LC485:
	.ascii "pf2id\0"
LC486:
	.ascii "pf2iw\0"
LC487:
	.ascii "pfacc\0"
LC488:
	.ascii "pfadd\0"
LC489:
	.ascii "pfcmpeq\0"
LC490:
	.ascii "pfcmpge\0"
LC491:
	.ascii "pfcmpgt\0"
LC492:
	.ascii "pfmax\0"
LC493:
	.ascii "pfmin\0"
LC494:
	.ascii "pfmul\0"
LC495:
	.ascii "pfnacc\0"
LC496:
	.ascii "pfpnacc\0"
LC497:
	.ascii "pfrcp\0"
LC498:
	.ascii "pfrcpit1\0"
LC499:
	.ascii "pfrcpit2\0"
LC500:
	.ascii "pfrsqit1\0"
LC501:
	.ascii "pfrsqrt\0"
LC502:
	.ascii "pfsub\0"
LC503:
	.ascii "pfsubr\0"
LC504:
	.ascii "pi2fd\0"
LC505:
	.ascii "pi2fw\0"
LC506:
	.ascii "pinsrw\0"
LC507:
	.ascii "pmachriw\0"
LC508:
	.ascii "pmaddwd\0"
LC509:
	.ascii "pmagw\0"
LC510:
	.ascii "pmaxsw\0"
LC511:
	.ascii "pmaxub\0"
LC512:
	.ascii "pminsw\0"
LC513:
	.ascii "pminub\0"
LC514:
	.ascii "pmovmskb\0"
LC515:
	.ascii "pmulhriw\0"
LC516:
	.ascii "pmulhrwa\0"
LC517:
	.ascii "pmulhrwc\0"
LC518:
	.ascii "pmulhuw\0"
LC519:
	.ascii "pmulhw\0"
LC520:
	.ascii "pmullw\0"
LC521:
	.ascii "pmuludq\0"
LC522:
	.ascii "pmvgezb\0"
LC523:
	.ascii "pmvlzb\0"
LC524:
	.ascii "pmvnzb\0"
LC525:
	.ascii "pmvzb\0"
LC526:
	.ascii "pop\0"
LC527:
	.ascii "popa\0"
LC528:
	.ascii "popad\0"
LC529:
	.ascii "popaw\0"
LC530:
	.ascii "popf\0"
LC531:
	.ascii "popfd\0"
LC532:
	.ascii "popfw\0"
LC533:
	.ascii "por\0"
LC534:
	.ascii "prefetch\0"
LC535:
	.ascii "prefetchnta\0"
LC536:
	.ascii "prefetcht0\0"
LC537:
	.ascii "prefetcht1\0"
LC538:
	.ascii "prefetcht2\0"
LC539:
	.ascii "prefetchw\0"
LC540:
	.ascii "psadbw\0"
LC541:
	.ascii "pshufd\0"
LC542:
	.ascii "pshufhw\0"
LC543:
	.ascii "pshuflw\0"
LC544:
	.ascii "pshufw\0"
LC545:
	.ascii "pslld\0"
LC546:
	.ascii "pslldq\0"
LC547:
	.ascii "psllq\0"
LC548:
	.ascii "psllw\0"
LC549:
	.ascii "psrad\0"
LC550:
	.ascii "psraw\0"
LC551:
	.ascii "psrld\0"
LC552:
	.ascii "psrldq\0"
LC553:
	.ascii "psrlq\0"
LC554:
	.ascii "psrlw\0"
LC555:
	.ascii "psubb\0"
LC556:
	.ascii "psubd\0"
LC557:
	.ascii "psubq\0"
LC558:
	.ascii "psubsb\0"
LC559:
	.ascii "psubsiw\0"
LC560:
	.ascii "psubsw\0"
LC561:
	.ascii "psubusb\0"
LC562:
	.ascii "psubusw\0"
LC563:
	.ascii "psubw\0"
LC564:
	.ascii "pswapd\0"
LC565:
	.ascii "punpckhbw\0"
LC566:
	.ascii "punpckhdq\0"
LC567:
	.ascii "punpckhqdq\0"
LC568:
	.ascii "punpckhwd\0"
LC569:
	.ascii "punpcklbw\0"
LC570:
	.ascii "punpckldq\0"
LC571:
	.ascii "punpcklqdq\0"
LC572:
	.ascii "punpcklwd\0"
LC573:
	.ascii "push\0"
LC574:
	.ascii "pusha\0"
LC575:
	.ascii "pushad\0"
LC576:
	.ascii "pushaw\0"
LC577:
	.ascii "pushf\0"
LC578:
	.ascii "pushfd\0"
LC579:
	.ascii "pushfw\0"
LC580:
	.ascii "pxor\0"
LC581:
	.ascii "rcl\0"
LC582:
	.ascii "rcpps\0"
LC583:
	.ascii "rcpss\0"
LC584:
	.ascii "rcr\0"
LC585:
	.ascii "rdmsr\0"
LC586:
	.ascii "rdpmc\0"
LC587:
	.ascii "rdshr\0"
LC588:
	.ascii "rdtsc\0"
LC589:
	.ascii "resb\0"
LC590:
	.ascii "resd\0"
LC591:
	.ascii "resq\0"
LC592:
	.ascii "rest\0"
LC593:
	.ascii "resw\0"
LC594:
	.ascii "ret\0"
LC595:
	.ascii "retf\0"
LC596:
	.ascii "retn\0"
LC597:
	.ascii "rol\0"
LC598:
	.ascii "ror\0"
LC599:
	.ascii "rsdc\0"
LC600:
	.ascii "rsldt\0"
LC601:
	.ascii "rsm\0"
LC602:
	.ascii "rsqrtps\0"
LC603:
	.ascii "rsqrtss\0"
LC604:
	.ascii "rsts\0"
LC605:
	.ascii "sahf\0"
LC606:
	.ascii "sal\0"
LC607:
	.ascii "salc\0"
LC608:
	.ascii "sar\0"
LC609:
	.ascii "sbb\0"
LC610:
	.ascii "scasb\0"
LC611:
	.ascii "scasd\0"
LC612:
	.ascii "scasw\0"
LC613:
	.ascii "sfence\0"
LC614:
	.ascii "sgdt\0"
LC615:
	.ascii "shl\0"
LC616:
	.ascii "shld\0"
LC617:
	.ascii "shr\0"
LC618:
	.ascii "shrd\0"
LC619:
	.ascii "shufpd\0"
LC620:
	.ascii "shufps\0"
LC621:
	.ascii "sidt\0"
LC622:
	.ascii "sldt\0"
LC623:
	.ascii "smi\0"
LC624:
	.ascii "smint\0"
LC625:
	.ascii "smintold\0"
LC626:
	.ascii "smsw\0"
LC627:
	.ascii "sqrtpd\0"
LC628:
	.ascii "sqrtps\0"
LC629:
	.ascii "sqrtsd\0"
LC630:
	.ascii "sqrtss\0"
LC631:
	.ascii "stc\0"
LC632:
	.ascii "std\0"
LC633:
	.ascii "sti\0"
LC634:
	.ascii "stmxcsr\0"
LC635:
	.ascii "stosb\0"
LC636:
	.ascii "stosd\0"
LC637:
	.ascii "stosw\0"
LC638:
	.ascii "str\0"
LC639:
	.ascii "sub\0"
LC640:
	.ascii "subpd\0"
LC641:
	.ascii "subps\0"
LC642:
	.ascii "subsd\0"
LC643:
	.ascii "subss\0"
LC644:
	.ascii "svdc\0"
LC645:
	.ascii "svldt\0"
LC646:
	.ascii "svts\0"
LC647:
	.ascii "syscall\0"
LC648:
	.ascii "sysenter\0"
LC649:
	.ascii "sysexit\0"
LC650:
	.ascii "sysret\0"
LC651:
	.ascii "test\0"
LC652:
	.ascii "ucomisd\0"
LC653:
	.ascii "ucomiss\0"
LC654:
	.ascii "ud0\0"
LC655:
	.ascii "ud1\0"
LC656:
	.ascii "ud2\0"
LC657:
	.ascii "umov\0"
LC658:
	.ascii "unpckhpd\0"
LC659:
	.ascii "unpckhps\0"
LC660:
	.ascii "unpcklpd\0"
LC661:
	.ascii "unpcklps\0"
LC662:
	.ascii "verr\0"
LC663:
	.ascii "verw\0"
LC664:
	.ascii "wait\0"
LC665:
	.ascii "wbinvd\0"
LC666:
	.ascii "wrmsr\0"
LC667:
	.ascii "wrshr\0"
LC668:
	.ascii "xadd\0"
LC669:
	.ascii "xbts\0"
LC670:
	.ascii "xchg\0"
LC671:
	.ascii "xlat\0"
LC672:
	.ascii "xlatb\0"
LC673:
	.ascii "xor\0"
LC674:
	.ascii "xorpd\0"
LC675:
	.ascii "xorps\0"
LC676:
	.ascii "xstore\0"
	.data
	.align 32
_insn_names:
	.long	LC117
	.long	LC118
	.long	LC119
	.long	LC120
	.long	LC121
	.long	LC122
	.long	LC123
	.long	LC124
	.long	LC125
	.long	LC126
	.long	LC127
	.long	LC128
	.long	LC129
	.long	LC130
	.long	LC131
	.long	LC132
	.long	LC133
	.long	LC134
	.long	LC135
	.long	LC136
	.long	LC137
	.long	LC138
	.long	LC139
	.long	LC140
	.long	LC141
	.long	LC142
	.long	LC143
	.long	LC144
	.long	LC145
	.long	LC146
	.long	LC147
	.long	LC148
	.long	LC149
	.long	LC150
	.long	LC151
	.long	LC152
	.long	LC153
	.long	LC154
	.long	LC155
	.long	LC156
	.long	LC157
	.long	LC158
	.long	LC159
	.long	LC160
	.long	LC161
	.long	LC162
	.long	LC163
	.long	LC164
	.long	LC165
	.long	LC166
	.long	LC167
	.long	LC168
	.long	LC169
	.long	LC170
	.long	LC171
	.long	LC172
	.long	LC173
	.long	LC174
	.long	LC175
	.long	LC176
	.long	LC177
	.long	LC178
	.long	LC179
	.long	LC180
	.long	LC181
	.long	LC182
	.long	LC183
	.long	LC184
	.long	LC185
	.long	LC186
	.long	LC187
	.long	LC188
	.long	LC189
	.long	LC190
	.long	LC191
	.long	LC192
	.long	LC193
	.long	LC194
	.long	LC195
	.long	LC196
	.long	LC197
	.long	LC198
	.long	LC199
	.long	LC200
	.long	LC201
	.long	LC202
	.long	LC203
	.long	LC204
	.long	LC205
	.long	LC206
	.long	LC207
	.long	LC208
	.long	LC209
	.long	LC210
	.long	LC211
	.long	LC212
	.long	LC213
	.long	LC214
	.long	LC215
	.long	LC216
	.long	LC217
	.long	LC218
	.long	LC219
	.long	LC220
	.long	LC221
	.long	LC222
	.long	LC223
	.long	LC224
	.long	LC225
	.long	LC226
	.long	LC227
	.long	LC228
	.long	LC229
	.long	LC230
	.long	LC231
	.long	LC232
	.long	LC233
	.long	LC234
	.long	LC235
	.long	LC236
	.long	LC237
	.long	LC238
	.long	LC239
	.long	LC240
	.long	LC241
	.long	LC242
	.long	LC243
	.long	LC244
	.long	LC245
	.long	LC246
	.long	LC247
	.long	LC248
	.long	LC249
	.long	LC250
	.long	LC251
	.long	LC252
	.long	LC253
	.long	LC254
	.long	LC255
	.long	LC256
	.long	LC257
	.long	LC258
	.long	LC259
	.long	LC260
	.long	LC261
	.long	LC262
	.long	LC263
	.long	LC264
	.long	LC265
	.long	LC266
	.long	LC267
	.long	LC268
	.long	LC269
	.long	LC270
	.long	LC271
	.long	LC272
	.long	LC273
	.long	LC274
	.long	LC275
	.long	LC276
	.long	LC277
	.long	LC278
	.long	LC279
	.long	LC280
	.long	LC281
	.long	LC282
	.long	LC283
	.long	LC284
	.long	LC285
	.long	LC286
	.long	LC287
	.long	LC288
	.long	LC289
	.long	LC290
	.long	LC291
	.long	LC292
	.long	LC293
	.long	LC294
	.long	LC295
	.long	LC296
	.long	LC297
	.long	LC298
	.long	LC299
	.long	LC300
	.long	LC301
	.long	LC302
	.long	LC303
	.long	LC304
	.long	LC305
	.long	LC306
	.long	LC307
	.long	LC308
	.long	LC309
	.long	LC310
	.long	LC311
	.long	LC312
	.long	LC313
	.long	LC314
	.long	LC315
	.long	LC316
	.long	LC317
	.long	LC318
	.long	LC319
	.long	LC320
	.long	LC321
	.long	LC322
	.long	LC323
	.long	LC324
	.long	LC325
	.long	LC326
	.long	LC327
	.long	LC328
	.long	LC329
	.long	LC330
	.long	LC331
	.long	LC332
	.long	LC333
	.long	LC334
	.long	LC335
	.long	LC336
	.long	LC337
	.long	LC338
	.long	LC339
	.long	LC340
	.long	LC341
	.long	LC342
	.long	LC343
	.long	LC344
	.long	LC345
	.long	LC346
	.long	LC347
	.long	LC348
	.long	LC349
	.long	LC350
	.long	LC351
	.long	LC352
	.long	LC353
	.long	LC354
	.long	LC355
	.long	LC356
	.long	LC357
	.long	LC358
	.long	LC359
	.long	LC360
	.long	LC361
	.long	LC362
	.long	LC363
	.long	LC364
	.long	LC365
	.long	LC366
	.long	LC367
	.long	LC368
	.long	LC369
	.long	LC370
	.long	LC371
	.long	LC372
	.long	LC373
	.long	LC374
	.long	LC375
	.long	LC376
	.long	LC377
	.long	LC378
	.long	LC379
	.long	LC380
	.long	LC381
	.long	LC382
	.long	LC383
	.long	LC384
	.long	LC385
	.long	LC386
	.long	LC387
	.long	LC388
	.long	LC389
	.long	LC390
	.long	LC391
	.long	LC392
	.long	LC393
	.long	LC394
	.long	LC395
	.long	LC396
	.long	LC397
	.long	LC398
	.long	LC399
	.long	LC400
	.long	LC401
	.long	LC402
	.long	LC403
	.long	LC404
	.long	LC405
	.long	LC406
	.long	LC407
	.long	LC408
	.long	LC409
	.long	LC410
	.long	LC411
	.long	LC412
	.long	LC413
	.long	LC414
	.long	LC415
	.long	LC416
	.long	LC417
	.long	LC418
	.long	LC419
	.long	LC420
	.long	LC421
	.long	LC422
	.long	LC423
	.long	LC424
	.long	LC425
	.long	LC426
	.long	LC427
	.long	LC428
	.long	LC429
	.long	LC430
	.long	LC431
	.long	LC432
	.long	LC433
	.long	LC434
	.long	LC435
	.long	LC436
	.long	LC437
	.long	LC438
	.long	LC439
	.long	LC440
	.long	LC441
	.long	LC442
	.long	LC443
	.long	LC444
	.long	LC445
	.long	LC446
	.long	LC447
	.long	LC448
	.long	LC449
	.long	LC450
	.long	LC451
	.long	LC452
	.long	LC453
	.long	LC454
	.long	LC455
	.long	LC456
	.long	LC457
	.long	LC458
	.long	LC459
	.long	LC460
	.long	LC461
	.long	LC462
	.long	LC463
	.long	LC464
	.long	LC465
	.long	LC466
	.long	LC467
	.long	LC468
	.long	LC469
	.long	LC470
	.long	LC471
	.long	LC472
	.long	LC473
	.long	LC474
	.long	LC475
	.long	LC476
	.long	LC477
	.long	LC478
	.long	LC479
	.long	LC480
	.long	LC481
	.long	LC482
	.long	LC483
	.long	LC484
	.long	LC485
	.long	LC486
	.long	LC487
	.long	LC488
	.long	LC489
	.long	LC490
	.long	LC491
	.long	LC492
	.long	LC493
	.long	LC494
	.long	LC495
	.long	LC496
	.long	LC497
	.long	LC498
	.long	LC499
	.long	LC500
	.long	LC501
	.long	LC502
	.long	LC503
	.long	LC504
	.long	LC505
	.long	LC506
	.long	LC507
	.long	LC508
	.long	LC509
	.long	LC510
	.long	LC511
	.long	LC512
	.long	LC513
	.long	LC514
	.long	LC515
	.long	LC516
	.long	LC517
	.long	LC518
	.long	LC519
	.long	LC520
	.long	LC521
	.long	LC522
	.long	LC523
	.long	LC524
	.long	LC525
	.long	LC526
	.long	LC527
	.long	LC528
	.long	LC529
	.long	LC530
	.long	LC531
	.long	LC532
	.long	LC533
	.long	LC534
	.long	LC535
	.long	LC536
	.long	LC537
	.long	LC538
	.long	LC539
	.long	LC540
	.long	LC541
	.long	LC542
	.long	LC543
	.long	LC544
	.long	LC545
	.long	LC546
	.long	LC547
	.long	LC548
	.long	LC549
	.long	LC550
	.long	LC551
	.long	LC552
	.long	LC553
	.long	LC554
	.long	LC555
	.long	LC556
	.long	LC557
	.long	LC558
	.long	LC559
	.long	LC560
	.long	LC561
	.long	LC562
	.long	LC563
	.long	LC564
	.long	LC565
	.long	LC566
	.long	LC567
	.long	LC568
	.long	LC569
	.long	LC570
	.long	LC571
	.long	LC572
	.long	LC573
	.long	LC574
	.long	LC575
	.long	LC576
	.long	LC577
	.long	LC578
	.long	LC579
	.long	LC580
	.long	LC581
	.long	LC582
	.long	LC583
	.long	LC584
	.long	LC585
	.long	LC586
	.long	LC587
	.long	LC588
	.long	LC589
	.long	LC590
	.long	LC591
	.long	LC592
	.long	LC593
	.long	LC594
	.long	LC595
	.long	LC596
	.long	LC597
	.long	LC598
	.long	LC599
	.long	LC600
	.long	LC601
	.long	LC602
	.long	LC603
	.long	LC604
	.long	LC605
	.long	LC606
	.long	LC607
	.long	LC608
	.long	LC609
	.long	LC610
	.long	LC611
	.long	LC612
	.long	LC613
	.long	LC614
	.long	LC615
	.long	LC616
	.long	LC617
	.long	LC618
	.long	LC619
	.long	LC620
	.long	LC621
	.long	LC622
	.long	LC623
	.long	LC624
	.long	LC625
	.long	LC626
	.long	LC627
	.long	LC628
	.long	LC629
	.long	LC630
	.long	LC631
	.long	LC632
	.long	LC633
	.long	LC634
	.long	LC635
	.long	LC636
	.long	LC637
	.long	LC638
	.long	LC639
	.long	LC640
	.long	LC641
	.long	LC642
	.long	LC643
	.long	LC644
	.long	LC645
	.long	LC646
	.long	LC647
	.long	LC648
	.long	LC649
	.long	LC650
	.long	LC651
	.long	LC652
	.long	LC653
	.long	LC654
	.long	LC655
	.long	LC656
	.long	LC657
	.long	LC658
	.long	LC659
	.long	LC660
	.long	LC661
	.long	LC662
	.long	LC663
	.long	LC664
	.long	LC665
	.long	LC666
	.long	LC667
	.long	LC668
	.long	LC669
	.long	LC670
	.long	LC671
	.long	LC672
	.long	LC673
	.long	LC674
	.long	LC675
	.long	LC676
	.text
LC677:
	.ascii "cmov\0"
LC678:
	.ascii "j\0"
LC679:
	.ascii "set\0"
	.data
	.align 4
_icn:
	.long	LC677
	.long	LC678
	.long	LC679
	.align 4
_ico:
	.long	560
	.long	561
	.long	562
	.text
LC680:
	.ascii "byte\0"
LC681:
	.ascii "dword\0"
LC682:
	.ascii "far\0"
LC683:
	.ascii "long\0"
LC684:
	.ascii "near\0"
LC685:
	.ascii "nosplit\0"
LC686:
	.ascii "qword\0"
LC687:
	.ascii "short\0"
LC688:
	.ascii "strict\0"
LC689:
	.ascii "to\0"
LC690:
	.ascii "tword\0"
LC691:
	.ascii "word\0"
	.data
	.align 32
_special_names:
	.long	LC680
	.long	LC681
	.long	LC682
	.long	LC683
	.long	LC684
	.long	LC685
	.long	LC686
	.long	LC687
	.long	LC688
	.long	LC689
	.long	LC690
	.long	LC691
	.text
LC692:
	.ascii "a16\0"
LC693:
	.ascii "a32\0"
LC694:
	.ascii "lock\0"
LC695:
	.ascii "o16\0"
LC696:
	.ascii "o32\0"
LC697:
	.ascii "rep\0"
LC698:
	.ascii "repe\0"
LC699:
	.ascii "repne\0"
LC700:
	.ascii "repnz\0"
LC701:
	.ascii "repz\0"
LC702:
	.ascii "times\0"
	.data
	.align 32
_prefix_names:
	.long	LC692
	.long	LC693
	.long	LC694
	.long	LC695
	.long	LC696
	.long	LC697
	.long	LC698
	.long	LC699
	.long	LC700
	.long	LC701
	.long	LC702
	.align 4
_stdscan_tempstorage:
	.long	0
	.align 4
_stdscan_tempsize:
	.long	0
	.align 4
_stdscan_templen:
	.long	0
	.text
	.align 2
	.def	_stdscan_pop;	.scl	3;	.type	32;	.endef
_stdscan_pop:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_stdscan_templen, %eax
	decl	%eax
	movl	%eax, _stdscan_templen
	movl	_stdscan_tempstorage, %edx
	movl	(%edx,%eax,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _stdscan_reset
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
_stdscan_reset:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, _stdscan_templen
	jle	L273
L271:
	call	_stdscan_pop
	cmpl	$0, _stdscan_templen
	jg	L271
L273:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasmlib_cleanup
	.def	_nasmlib_cleanup;	.scl	2;	.type	32;	.endef
_nasmlib_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	_stdscan_reset
	movl	_stdscan_tempstorage, %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_stdscan_copy;	.scl	3;	.type	32;	.endef
_stdscan_copy:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	12(%ebp), %ebx
	leal	1(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_strncpy
	movb	$0, (%ebx,%esi)
	movl	_stdscan_templen, %eax
	cmpl	_stdscan_tempsize, %eax
	jl	L276
	movl	_stdscan_tempsize, %eax
	addl	$256, %eax
	movl	%eax, _stdscan_tempsize
	movl	_stdscan_tempstorage, %edx
	movl	%edx, (%esp)
	sall	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, _stdscan_tempstorage
L276:
	movl	_stdscan_templen, %edx
	movl	_stdscan_tempstorage, %eax
	movl	%esi, (%eax,%edx,4)
	incl	_stdscan_templen
	movl	%esi, %eax
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
.globl _stdscan_bufptr
	.data
	.align 4
_stdscan_bufptr:
	.long	0
	.text
LC703:
	.ascii "seg\0"
LC704:
	.ascii "wrt\0"
	.align 2
.globl _stdscan
	.def	_stdscan;	.scl	2;	.type	32;	.endef
_stdscan:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	jmp	L278
L281:
	incl	_stdscan_bufptr
L278:
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L281
	movl	_stdscan_bufptr, %eax
	cmpb	$0, (%eax)
	je	L377
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L284
	movl	_stdscan_bufptr, %eax
	cmpb	$95, (%eax)
	je	L284
	cmpb	$46, (%eax)
	je	L284
	cmpb	$63, (%eax)
	je	L284
	cmpb	$64, (%eax)
	je	L284
	cmpb	$36, (%eax)
	jne	L283
	movsbl	1(%eax),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L284
	movl	_stdscan_bufptr, %eax
	cmpb	$95, 1(%eax)
	je	L284
	cmpb	$46, 1(%eax)
	je	L284
	cmpb	$63, 1(%eax)
	je	L284
	cmpb	$64, 1(%eax)
	jne	L283
L284:
	movl	$0, %ebx
	movl	_stdscan_bufptr, %eax
	cmpb	$36, (%eax)
	jne	L285
	movl	$1, %ebx
	incl	%eax
	movl	%eax, _stdscan_bufptr
L285:
	movl	_stdscan_bufptr, %edi
	leal	1(%edi), %eax
	movl	%eax, _stdscan_bufptr
	jmp	L286
L289:
	incl	_stdscan_bufptr
L286:
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L289
	movl	_stdscan_bufptr, %eax
	cmpb	$95, (%eax)
	je	L289
	cmpb	$46, (%eax)
	je	L289
	cmpb	$63, (%eax)
	je	L289
	cmpb	$64, (%eax)
	je	L289
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L289
	movl	_stdscan_bufptr, %eax
	cmpb	$36, (%eax)
	je	L289
	cmpb	$35, (%eax)
	je	L289
	cmpb	$126, (%eax)
	je	L289
	movl	%edi, (%esp)
	subl	%edi, %eax
	cmpl	$4095, %eax
	jle	L290
	movl	$4095, %eax
L290:
	movl	%eax, 4(%esp)
	call	_stdscan_copy
	movl	12(%ebp), %edx
	movl	%eax, 12(%edx)
	testl	%ebx, %ebx
	jne	L292
	movl	_stdscan_bufptr, %eax
	subl	%edi, %eax
	cmpl	$11, %eax
	jle	L291
L292:
	movl	12(%ebp), %ecx
	movl	$256, (%ecx)
	jmp	L376
L291:
	movl	12(%ebp), %eax
	movl	12(%eax), %esi
	leal	-40(%ebp), %edi
	cmpb	$0, (%esi)
	je	L367
L297:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	movl	%edi, %ebx
	incl	%edi
	call	_tolower
	movb	%al, (%ebx)
	incl	%esi
	cmpb	$0, (%esi)
	jne	L297
L367:
	movb	$0, (%edi)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$_reg_names, 4(%esp)
	movl	$80, 8(%esp)
	call	_bsi
	movl	12(%ebp), %edx
	movl	%eax, 4(%edx)
	testl	%eax, %eax
	js	L298
	incl	%eax
	movl	%eax, 4(%edx)
	movl	$258, (%edx)
	movl	$258, %eax
	jmp	L277
L298:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$_insn_names, 4(%esp)
	movl	$560, 8(%esp)
	call	_bsi
	movl	12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	testl	%eax, %eax
	js	L299
	movl	$259, (%ecx)
	jmp	L375
L299:
	movl	$0, %ebx
	movl	$_icn, %esi
	leal	-40(%ebp), %edi
L307:
	movl	(%esi,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%edi, (%esp)
	movl	(%esi,%ebx,4), %edx
	movl	%edx, 4(%esp)
	movl	%eax, 8(%esp)
	call	_strncmp
	testl	%eax, %eax
	jne	L303
	movl	(%esi,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_strlen
	leal	(%eax,%edi), %eax
	movl	_ico(,%ebx,4), %edx
	movl	12(%ebp), %ecx
	movl	%edx, 4(%ecx)
	movl	%eax, (%esp)
	movl	$_conditions, 4(%esp)
	movl	$30, 8(%esp)
	call	_bsi
	movl	12(%ebp), %edx
	movl	%eax, 8(%edx)
	testl	%eax, %eax
	jns	L371
L303:
	incl	%ebx
	cmpl	$2, %ebx
	jbe	L307
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$_prefix_names, 4(%esp)
	movl	$11, 8(%esp)
	call	_bsi
	movl	12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	testl	%eax, %eax
	js	L308
	addl	$81, %eax
	movl	%eax, 4(%ecx)
	movl	$264, (%ecx)
	movl	$264, %eax
	jmp	L277
L308:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$_special_names, 4(%esp)
	movl	$12, 8(%esp)
	call	_bsi
	movl	12(%ebp), %edx
	movl	%eax, 4(%edx)
	testl	%eax, %eax
	js	L309
	movl	$263, (%edx)
	movl	$263, %eax
	jmp	L277
L309:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC703, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L310
	movl	12(%ebp), %ecx
	movl	$275, (%ecx)
	movl	$275, %eax
	jmp	L277
L310:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC704, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L311
	movl	12(%ebp), %eax
	movl	$276, (%eax)
	movl	$276, %eax
	jmp	L277
L311:
	movl	12(%ebp), %edx
	movl	$256, (%edx)
L376:
	movl	$256, %eax
	jmp	L277
L283:
	movl	_stdscan_bufptr, %eax
	cmpb	$36, (%eax)
	jne	L313
	movsbl	1(%eax),%eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	jne	L313
	movl	_stdscan_bufptr, %edx
	leal	1(%edx), %eax
	movl	%eax, _stdscan_bufptr
	cmpb	$36, 1(%edx)
	jne	L314
	leal	2(%edx), %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %ecx
	movl	$262, (%ecx)
	movl	$262, %eax
	jmp	L277
L314:
	movl	12(%ebp), %eax
	movl	$261, (%eax)
	movl	$261, %eax
	jmp	L277
L313:
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L317
	movl	_stdscan_bufptr, %eax
	cmpb	$36, (%eax)
	jne	L316
L317:
	movl	_stdscan_bufptr, %edi
	leal	1(%edi), %eax
	movl	%eax, _stdscan_bufptr
	jmp	L318
L321:
	incl	_stdscan_bufptr
L318:
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	jne	L321
	movl	_stdscan_bufptr, %eax
	cmpb	$46, (%eax)
	jne	L322
	incl	%eax
	movl	%eax, _stdscan_bufptr
	jmp	L323
L328:
	incl	_stdscan_bufptr
L323:
	movl	_stdscan_bufptr, %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	jne	L328
	movl	_stdscan_bufptr, %eax
	cmpb	$101, -1(%eax)
	je	L327
	cmpb	$69, -1(%eax)
	jne	L324
L327:
	movl	_stdscan_bufptr, %eax
	cmpb	$45, (%eax)
	je	L328
	cmpb	$43, (%eax)
	je	L328
L324:
	movl	%edi, (%esp)
	movl	_stdscan_bufptr, %eax
	subl	%edi, %eax
	movl	%eax, 4(%esp)
	call	_stdscan_copy
	movl	12(%ebp), %edx
	movl	%eax, 12(%edx)
	movl	$277, (%edx)
	movl	$277, %eax
	jmp	L277
L322:
	movl	%edi, (%esp)
	movl	_stdscan_bufptr, %eax
	subl	%edi, %eax
	movl	%eax, 4(%esp)
	call	_stdscan_copy
	movl	%eax, (%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	call	_stdscan_pop
	cmpl	$0, -44(%ebp)
	je	L329
	movl	12(%ebp), %eax
	movl	$260, (%eax)
	jmp	L374
L329:
	movl	12(%ebp), %edx
	movl	$0, 12(%edx)
	movl	$257, (%edx)
	jmp	L373
L316:
	movl	_stdscan_bufptr, %eax
	cmpb	$39, (%eax)
	je	L332
	cmpb	$34, (%eax)
	jne	L331
L332:
	movl	_stdscan_bufptr, %eax
	movzbl	(%eax), %ecx
	incl	%eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %edx
	movl	%eax, 12(%edx)
	movl	%eax, %ebx
	movl	_stdscan_bufptr, %eax
	cmpb	$0, (%eax)
	je	L334
	cmpb	%cl, (%eax)
	je	L334
L337:
	movl	_stdscan_bufptr, %edx
	leal	1(%edx), %eax
	movl	%eax, _stdscan_bufptr
	cmpb	$0, 1(%edx)
	je	L334
	cmpb	%cl, 1(%edx)
	jne	L337
L334:
	movl	_stdscan_bufptr, %eax
	subl	%ebx, %eax
	movl	12(%ebp), %ecx
	movl	%eax, 8(%ecx)
	movl	_stdscan_bufptr, %eax
	cmpb	$0, (%eax)
	jne	L338
	movl	$260, (%ecx)
L374:
	movl	$260, %eax
	jmp	L277
L338:
	incl	_stdscan_bufptr
	movl	%ebx, (%esp)
	movl	12(%ebp), %edx
	movl	8(%edx), %eax
	movl	%eax, 4(%esp)
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_readstrnum
	movl	12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	$257, (%ecx)
L373:
	movl	$257, %eax
	jmp	L277
L331:
	movl	_stdscan_bufptr, %eax
	cmpb	$59, (%eax)
	jne	L340
L377:
	movl	12(%ebp), %eax
	movl	$0, (%eax)
	movl	$0, %eax
	jmp	L277
L340:
	movl	_stdscan_bufptr, %eax
	cmpb	$62, (%eax)
	jne	L342
	cmpb	$62, 1(%eax)
	jne	L342
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %edx
	movl	$266, (%edx)
	movl	$266, %eax
	jmp	L277
L342:
	movl	_stdscan_bufptr, %eax
	cmpb	$60, (%eax)
	jne	L344
	cmpb	$60, 1(%eax)
	jne	L344
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %ecx
	movl	$265, (%ecx)
	movl	$265, %eax
	jmp	L277
L344:
	movl	_stdscan_bufptr, %eax
	cmpb	$47, (%eax)
	jne	L346
	cmpb	$47, 1(%eax)
	jne	L346
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %eax
	movl	$267, (%eax)
	movl	$267, %eax
	jmp	L277
L346:
	movl	_stdscan_bufptr, %eax
	cmpb	$37, (%eax)
	jne	L348
	cmpb	$37, 1(%eax)
	jne	L348
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %edx
	movl	$268, (%edx)
	movl	$268, %eax
	jmp	L277
L348:
	movl	_stdscan_bufptr, %eax
	cmpb	$61, (%eax)
	jne	L350
	cmpb	$61, 1(%eax)
	jne	L350
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %ecx
	movl	$61, (%ecx)
	movl	$61, %eax
	jmp	L277
L350:
	movl	_stdscan_bufptr, %eax
	cmpb	$60, (%eax)
	jne	L352
	cmpb	$62, 1(%eax)
	jne	L352
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %eax
	movl	$271, (%eax)
	jmp	L372
L352:
	movl	_stdscan_bufptr, %eax
	cmpb	$33, (%eax)
	jne	L354
	cmpb	$61, 1(%eax)
	jne	L354
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %edx
	movl	$271, (%edx)
L372:
	movl	$271, %eax
	jmp	L277
L354:
	movl	_stdscan_bufptr, %eax
	cmpb	$60, (%eax)
	jne	L356
	cmpb	$61, 1(%eax)
	jne	L356
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %ecx
	movl	$270, (%ecx)
	movl	$270, %eax
	jmp	L277
L356:
	movl	_stdscan_bufptr, %eax
	cmpb	$62, (%eax)
	jne	L358
	cmpb	$61, 1(%eax)
	jne	L358
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %eax
	movl	$269, (%eax)
	movl	$269, %eax
	jmp	L277
L358:
	movl	_stdscan_bufptr, %eax
	cmpb	$38, (%eax)
	jne	L360
	cmpb	$38, 1(%eax)
	jne	L360
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %edx
	movl	$272, (%edx)
	movl	$272, %eax
	jmp	L277
L360:
	movl	_stdscan_bufptr, %eax
	cmpb	$94, (%eax)
	jne	L362
	cmpb	$94, 1(%eax)
	jne	L362
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %ecx
	movl	$274, (%ecx)
	movl	$274, %eax
	jmp	L277
L362:
	movl	_stdscan_bufptr, %eax
	cmpb	$124, (%eax)
	jne	L364
	cmpb	$124, 1(%eax)
	jne	L364
	addl	$2, %eax
	movl	%eax, _stdscan_bufptr
	movl	12(%ebp), %eax
	movl	$273, (%eax)
	movl	$273, %eax
	jmp	L277
L371:
	movl	12(%ebp), %edx
	movl	$259, (%edx)
L375:
	movl	$259, %eax
	jmp	L277
L364:
	movl	_stdscan_bufptr, %eax
	movzbl	(%eax), %eax
	movl	12(%ebp), %ecx
	movl	%eax, (%ecx)
	incl	_stdscan_bufptr
L277:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _is_simple
	.def	_is_simple;	.scl	2;	.type	32;	.endef
_is_simple:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L391
	cmpl	$0, 4(%eax)
	jne	L380
L383:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L391
	cmpl	$0, 4(%eax)
	je	L383
L380:
	cmpl	$0, (%eax)
	je	L391
	cmpl	$126, (%eax)
	jne	L394
L386:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L391
	cmpl	$0, 4(%eax)
	je	L386
	cmpl	$0, (%eax)
	je	L391
	cmpl	$1073741951, (%eax)
	jg	L391
L394:
	movl	$0, %eax
	jmp	L378
L391:
	movl	$1, %eax
L378:
	popl	%ebp
	ret
	.align 2
.globl _is_really_simple
	.def	_is_really_simple;	.scl	2;	.type	32;	.endef
_is_really_simple:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L408
	cmpl	$0, 4(%eax)
	jne	L397
L400:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L408
	cmpl	$0, 4(%eax)
	je	L400
L397:
	cmpl	$0, (%eax)
	je	L408
	cmpl	$126, (%eax)
	jne	L411
L403:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L408
	cmpl	$0, 4(%eax)
	je	L403
	cmpl	$0, (%eax)
	je	L408
L411:
	movl	$0, %eax
	jmp	L395
L408:
	movl	$1, %eax
L395:
	popl	%ebp
	ret
	.align 2
.globl _is_reloc
	.def	_is_reloc;	.scl	2;	.type	32;	.endef
_is_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L445
	cmpl	$0, 4(%eax)
	jne	L414
L417:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L445
	cmpl	$0, 4(%eax)
	je	L417
L414:
	cmpl	$0, (%eax)
	je	L445
	cmpl	$125, (%eax)
	jle	L440
	cmpl	$126, (%eax)
	jne	L420
L421:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L445
	cmpl	$0, 4(%eax)
	je	L421
	cmpl	$0, (%eax)
	je	L445
L420:
	cmpl	$127, (%eax)
	jne	L427
L428:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L445
	cmpl	$0, 4(%eax)
	je	L428
	cmpl	$0, (%eax)
	je	L445
L427:
	cmpl	$1, 4(%eax)
	ja	L440
L435:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L445
	cmpl	$0, 4(%eax)
	je	L435
	cmpl	$0, (%eax)
	jne	L440
L445:
	movl	$1, %eax
	jmp	L412
L440:
	movl	$0, %eax
L412:
	popl	%ebp
	ret
	.align 2
.globl _is_unknown
	.def	_is_unknown;	.scl	2;	.type	32;	.endef
_is_unknown:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L448
	cmpl	$124, (%eax)
	jg	L448
L451:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L448
	cmpl	$124, (%eax)
	jle	L451
L448:
	cmpl	$125, (%eax)
	sete	%al
	movzbl	%al, %eax
	popl	%ebp
	ret
	.align 2
.globl _is_just_unknown
	.def	_is_just_unknown;	.scl	2;	.type	32;	.endef
_is_just_unknown:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L455
	cmpl	$0, 4(%eax)
	jne	L455
L458:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L455
	cmpl	$0, 4(%eax)
	je	L458
L455:
	cmpl	$125, (%eax)
	sete	%al
	movzbl	%al, %eax
	popl	%ebp
	ret
	.align 2
.globl _reloc_value
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
_reloc_value:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L467
	cmpl	$0, 4(%eax)
	jne	L462
L465:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L467
	cmpl	$0, 4(%eax)
	je	L465
L462:
	cmpl	$0, (%eax)
	je	L467
	cmpl	$126, (%eax)
	jne	L467
	movl	4(%eax), %eax
	jmp	L460
L467:
	movl	$0, %eax
L460:
	popl	%ebp
	ret
	.align 2
.globl _reloc_seg
	.def	_reloc_seg;	.scl	2;	.type	32;	.endef
_reloc_seg:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L473
	cmpl	$127, (%eax)
	je	L476
	cmpl	$0, 4(%eax)
	jne	L473
L476:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L473
	cmpl	$127, (%eax)
	je	L476
	cmpl	$0, 4(%eax)
	je	L476
L473:
	cmpl	$126, (%eax)
	jne	L477
L478:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L486
	cmpl	$127, (%eax)
	je	L478
	cmpl	$0, 4(%eax)
	je	L478
L477:
	cmpl	$0, (%eax)
	jne	L483
L486:
	movl	$-1, %eax
	jmp	L471
L483:
	movl	(%eax), %eax
	addl	$-128, %eax
L471:
	popl	%ebp
	ret
	.align 2
.globl _reloc_wrt
	.def	_reloc_wrt;	.scl	2;	.type	32;	.endef
_reloc_wrt:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	$0, (%eax)
	je	L489
	cmpl	$126, (%eax)
	jg	L489
L492:
	addl	$8, %eax
	cmpl	$0, (%eax)
	je	L489
	cmpl	$126, (%eax)
	jle	L492
L489:
	cmpl	$127, (%eax)
	jne	L493
	movl	4(%eax), %eax
	jmp	L487
L493:
	movl	$-1, %eax
L487:
	popl	%ebp
	ret
	.align 2
.globl _bsi
	.def	_bsi;	.scl	2;	.type	32;	.endef
_bsi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	$-1, %edi
	movl	16(%ebp), %esi
	leal	1(%esi), %eax
	cmpl	$1, %eax
	jle	L506
L504:
	leal	(%esi,%edi), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	movl	%eax, %ebx
	sarl	%ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %edx
	movl	(%edx,%ebx,4), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jns	L500
	movl	%ebx, %esi
	jmp	L497
L500:
	movl	%ebx, %edi
	testl	%eax, %eax
	jg	L497
	movl	%ebx, %eax
	jmp	L496
L497:
	movl	%esi, %eax
	subl	%edi, %eax
	cmpl	$1, %eax
	jg	L504
L506:
	movl	$-1, %eax
L496:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.data
	.align 4
_file_name:
	.long	0
	.align 4
_line_number:
	.long	0
	.text
	.align 2
.globl _src_set_fname
	.def	_src_set_fname;	.scl	2;	.type	32;	.endef
_src_set_fname:
	pushl	%ebp
	movl	%esp, %ebp
	movl	_file_name, %eax
	movl	8(%ebp), %edx
	movl	%edx, _file_name
	popl	%ebp
	ret
	.align 2
.globl _src_set_linnum
	.def	_src_set_linnum;	.scl	2;	.type	32;	.endef
_src_set_linnum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	_line_number, %eax
	movl	8(%ebp), %edx
	movl	%edx, _line_number
	popl	%ebp
	ret
	.align 2
.globl _src_get_linnum
	.def	_src_get_linnum;	.scl	2;	.type	32;	.endef
_src_get_linnum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	_line_number, %eax
	popl	%ebp
	ret
	.align 2
.globl _src_get
	.def	_src_get;	.scl	2;	.type	32;	.endef
_src_get:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	cmpl	$0, _file_name
	je	L512
	cmpl	$0, (%ebx)
	je	L512
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	_file_name, %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L511
L512:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	cmpl	$0, _file_name
	je	L513
	movl	_file_name, %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	jmp	L514
L513:
	movl	$0, %eax
L514:
	movl	%eax, (%ebx)
	movl	_line_number, %eax
	movl	%eax, (%esi)
	movl	$-2, %eax
	jmp	L510
L511:
	movl	(%esi), %edx
	cmpl	_line_number, %edx
	je	L515
	movl	_line_number, %eax
	movl	%eax, (%esi)
	subl	%edx, %eax
	jmp	L510
L515:
	movl	$0, %eax
L510:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _nasm_quote
	.def	_nasm_quote;	.scl	2;	.type	32;	.endef
_nasm_quote:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %esi
	movl	(%edi), %eax
	movzbl	(%eax), %edx
	movb	%dl, -13(%ebp)
	cmpl	$1, %esi
	jle	L517
	cmpb	%dl, -1(%eax,%esi)
	jne	L517
	cmpb	$34, %dl
	je	L516
	cmpb	$39, %dl
	je	L516
L517:
	movb	$34, -13(%ebp)
	movl	(%edi), %eax
	movl	%eax, (%esp)
	movl	$34, 4(%esp)
	call	_strchr
	testl	%eax, %eax
	je	L519
	movb	$39, -13(%ebp)
L519:
	leal	3(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	leal	1(%eax), %eax
	movl	%eax, (%esp)
	movl	(%edi), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movzbl	-13(%ebp), %eax
	movb	%al, (%ebx)
	movb	%al, 1(%esi,%ebx)
	movb	$0, 2(%esi,%ebx)
	movl	%ebx, (%edi)
L516:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _nasm_strcat
	.def	_nasm_strcat;	.scl	2;	.type	32;	.endef
_nasm_strcat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	%esi, (%esp)
	call	_strlen
	movl	%eax, %edi
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	leal	1(%eax,%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	leal	(%edi,%ebx), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	%ebx, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_init
	.def	_null_debug_init;	.scl	2;	.type	32;	.endef
_null_debug_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_linenum
	.def	_null_debug_linenum;	.scl	2;	.type	32;	.endef
_null_debug_linenum:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_deflabel
	.def	_null_debug_deflabel;	.scl	2;	.type	32;	.endef
_null_debug_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_routine
	.def	_null_debug_routine;	.scl	2;	.type	32;	.endef
_null_debug_routine:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_typevalue
	.def	_null_debug_typevalue;	.scl	2;	.type	32;	.endef
_null_debug_typevalue:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_output
	.def	_null_debug_output;	.scl	2;	.type	32;	.endef
_null_debug_output:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _null_debug_cleanup
	.def	_null_debug_cleanup;	.scl	2;	.type	32;	.endef
_null_debug_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _null_debug_form
LC705:
	.ascii "Null debug format\0"
LC706:
	.ascii "null\0"
	.data
	.align 32
_null_debug_form:
	.long	LC705
	.long	LC706
	.long	_null_debug_init
	.long	_null_debug_linenum
	.long	_null_debug_deflabel
	.long	_null_debug_routine
	.long	_null_debug_typevalue
	.long	_null_debug_output
	.long	_null_debug_cleanup
.globl _null_debug_arr
	.align 4
_null_debug_arr:
	.long	_null_debug_form
	.long	0
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _nasm_malloc_error,16
.lcomm _next_seg,16
	.def	_strchr;	.scl	2;	.type	32;	.endef
	.def	_strncmp;	.scl	2;	.type	32;	.endef
	.def	_bsi;	.scl	2;	.type	32;	.endef
	.def	_isdigit;	.scl	2;	.type	32;	.endef
	.def	_isalpha;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_ldiv;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_isalnum;	.scl	2;	.type	32;	.endef
	.def	_tolower;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_realloc;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
