	.file	"ndisasm.c"
	.text
	.align 32
LC0:
	.ascii "usage: ndisasm [-a] [-i] [-h] [-r] [-u] [-b bits] [-o origin] [-s sync...]\12               [-e bytes] [-k start,bytes] [-p vendor] file\12   -a or -i activates auto (intelligent) sync\12   -u sets USE32 (32-bit mode)\12   -b 16 or -b 32 sets number of bits too\12   -h displays this text\12   -r or -v displays the version number\12   -e skips <bytes> bytes of header\12   -k avoids disassembling <bytes> bytes from position <start>\12   -p selects the preferred vendor instruction set (intel, amd, cyrix, idt)\12\0"
	.data
	.align 4
_help:
	.long	LC0
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.align 32
LC1:
	.ascii "NDISASM version %s compiled Sep 30 2003\12\0"
LC2:
	.ascii "0.98.38\0"
LC4:
	.ascii "16\0"
LC5:
	.ascii "32\0"
	.align 32
LC6:
	.ascii "%s: argument to `-b' should be `16' or `32'\12\0"
LC18:
	.ascii "intel\0"
LC19:
	.ascii "amd\0"
LC20:
	.ascii "cyrix\0"
LC21:
	.ascii "idt\0"
LC22:
	.ascii "centaur\0"
LC23:
	.ascii "winchip\0"
	.align 32
LC24:
	.ascii "%s: unknown vendor `%s' specified with `-p'\12\0"
LC7:
	.ascii "\0"
	.align 32
LC25:
	.ascii "%s: unrecognised option `-%c'\12\0"
	.align 32
LC26:
	.ascii "%s: more than one filename specified\12\0"
LC27:
	.ascii "-\0"
LC28:
	.ascii "rb\0"
LC29:
	.ascii "%s: unable to open `%s': %s\12\0"
	.align 32
LC3:
	.ascii "%s: `-b' requires an argument\12\0"
	.align 32
LC8:
	.ascii "%s: `-o' requires an argument\12\0"
	.align 32
LC9:
	.ascii "%s: `-o' requires a numeric argument\12\0"
	.align 32
LC10:
	.ascii "%s: `-s' requires an argument\12\0"
	.align 32
LC11:
	.ascii "%s: `-s' requires a numeric argument\12\0"
	.align 32
LC12:
	.ascii "%s: `-e' requires an argument\12\0"
	.align 32
LC13:
	.ascii "%s: `-e' requires a numeric argument\12\0"
	.align 32
LC14:
	.ascii "%s: `-k' requires an argument\12\0"
	.align 32
LC15:
	.ascii "%s: `-k' requires two numbers separated by a comma\12\0"
	.align 32
LC16:
	.ascii "%s: `-k' requires numeric arguments\12\0"
	.align 32
LC17:
	.ascii "%s: `-p' requires an argument\12\0"
LC30:
	.ascii "%08lX  skipping 0x%lX bytes\12\0"
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$428, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	andl	$-16, %esp
	movl	$0, %eax
	call	__alloca
	call	___main
	movl	(%edi), %eax
	movl	%eax, -356(%ebp)
	movl	$0, -360(%ebp)
	movl	$0, -368(%ebp)
	movl	$0, -376(%ebp)
	movl	$16, -380(%ebp)
	movl	$0, -384(%ebp)
	movl	$0, -388(%ebp)
	movl	$0, -392(%ebp)
	call	_init_sync
	decl	%esi
	je	L108
L77:
	addl	$4, %edi
	movl	(%edi), %ebx
	cmpb	$45, (%ebx)
	jne	L5
	cmpb	$0, 1(%ebx)
	je	L5
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L2
L73:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_tolower
	subl	$97, %eax
	cmpl	$21, %eax
	ja	L71
	jmp	*L72(,%eax,4)
	.align 4
	.align 4
L72:
	.long	L11
	.long	L16
	.long	L71
	.long	L71
	.long	L40
	.long	L71
	.long	L71
	.long	L12
	.long	L11
	.long	L71
	.long	L47
	.long	L71
	.long	L71
	.long	L71
	.long	L26
	.long	L56
	.long	L71
	.long	L14
	.long	L33
	.long	L71
	.long	L15
	.long	L14
L11:
	movl	$1, -376(%ebp)
	jmp	L125
L12:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	_help, %eax
	movl	%eax, 4(%esp)
	call	_fprintf
	jmp	L106
L14:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC1, 4(%esp)
	movl	$LC2, 8(%esp)
	jmp	L128
L15:
	movl	$32, -380(%ebp)
L125:
	incl	%ebx
	jmp	L6
L16:
	cmpb	$0, 1(%ebx)
	je	L17
	incl	%ebx
	jmp	L18
L17:
	decl	%esi
	je	L19
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L18
L19:
	movl	$0, %ebx
L18:
	testl	%ebx, %ebx
	je	L113
	movl	%ebx, (%esp)
	movl	$LC4, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L22
	movl	$16, -380(%ebp)
	jmp	L63
L22:
	movl	%ebx, (%esp)
	movl	$LC5, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L24
	movl	$32, -380(%ebp)
	jmp	L63
L24:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC6, 4(%esp)
	movl	-356(%ebp), %edx
	movl	%edx, 8(%esp)
	call	_fprintf
	jmp	L63
L26:
	cmpb	$0, 1(%ebx)
	je	L27
	incl	%ebx
	jmp	L28
L27:
	decl	%esi
	je	L29
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L28
L29:
	movl	$0, %ebx
L28:
	testl	%ebx, %ebx
	je	L114
	movl	%ebx, (%esp)
	leal	-348(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -392(%ebp)
	cmpl	$0, -348(%ebp)
	jne	L115
	jmp	L63
L33:
	cmpb	$0, 1(%ebx)
	je	L34
	incl	%ebx
	jmp	L35
L34:
	decl	%esi
	je	L36
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L35
L36:
	movl	$0, %ebx
L35:
	testl	%ebx, %ebx
	je	L116
	movl	%ebx, (%esp)
	leal	-348(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_add_sync
	cmpl	$0, -348(%ebp)
	jne	L117
	jmp	L63
L40:
	cmpb	$0, 1(%ebx)
	je	L41
	incl	%ebx
	jmp	L42
L41:
	decl	%esi
	je	L43
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L42
L43:
	movl	$0, %ebx
L42:
	testl	%ebx, %ebx
	je	L118
	movl	%ebx, (%esp)
	leal	-348(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -368(%ebp)
	cmpl	$0, -348(%ebp)
	jne	L119
	jmp	L63
L47:
	cmpb	$0, 1(%ebx)
	je	L48
	incl	%ebx
	jmp	L49
L48:
	decl	%esi
	je	L50
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L49
L50:
	movl	$0, %ebx
L49:
	testl	%ebx, %ebx
	je	L120
	movl	%ebx, (%esp)
	movl	$44, 4(%esp)
	call	_strchr
	movl	%eax, -400(%ebp)
	testl	%eax, %eax
	je	L121
	movb	$0, (%eax)
	incl	-400(%ebp)
	movl	%ebx, (%esp)
	leal	-348(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -364(%ebp)
	cmpl	$0, -348(%ebp)
	jne	L122
	movl	-400(%ebp), %eax
	movl	%eax, (%esp)
	leal	-348(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -352(%ebp)
	cmpl	$0, -348(%ebp)
	jne	L123
	movl	-364(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	call	_add_sync
	jmp	L63
L56:
	cmpb	$0, 1(%ebx)
	je	L57
	incl	%ebx
	jmp	L58
L57:
	decl	%esi
	je	L59
	addl	$4, %edi
	movl	(%edi), %ebx
	jmp	L58
L59:
	movl	$0, %ebx
L58:
	testl	%ebx, %ebx
	je	L124
	movl	%ebx, (%esp)
	movl	$LC18, 4(%esp)
	call	_strcmp
	movl	$0, -388(%ebp)
	testl	%eax, %eax
	je	L63
	movl	%ebx, (%esp)
	movl	$LC19, 4(%esp)
	call	_strcmp
	movl	$536903680, -388(%ebp)
	testl	%eax, %eax
	je	L63
	movl	%ebx, (%esp)
	movl	$LC20, 4(%esp)
	call	_strcmp
	movl	$268468224, -388(%ebp)
	testl	%eax, %eax
	je	L63
	movl	%ebx, (%esp)
	movl	$LC21, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L69
	movl	%ebx, (%esp)
	movl	$LC22, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L69
	movl	%ebx, (%esp)
	movl	$LC23, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L68
L69:
	movl	$32768, -388(%ebp)
	jmp	L63
L68:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC24, 4(%esp)
	movl	-356(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%ebx, 12(%esp)
	jmp	L135
L63:
	movl	$LC7, %ebx
	jmp	L6
L71:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC25, 4(%esp)
	movl	-356(%ebp), %edx
	movl	%edx, 8(%esp)
	movsbl	(%ebx),%eax
	movl	%eax, 12(%esp)
L135:
	call	_fprintf
	jmp	L127
L6:
	cmpb	$0, (%ebx)
	je	L2
	jmp	L73
L5:
	cmpl	$0, -360(%ebp)
	jne	L75
	movl	%ebx, -360(%ebp)
	jmp	L2
L75:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC26, 4(%esp)
	jmp	L134
L2:
	decl	%esi
	jne	L77
L108:
	cmpl	$0, -360(%ebp)
	jne	L78
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	_help, %eax
	movl	%eax, 4(%esp)
	movl	-356(%ebp), %edx
	movl	%edx, 8(%esp)
L128:
	call	_fprintf
	jmp	L106
L78:
	movl	-360(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC27, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L79
	movl	-360(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC28, 4(%esp)
	call	_fopen
	movl	%eax, -396(%ebp)
	testl	%eax, %eax
	jne	L81
	movl	_errno, %eax
	movl	%eax, (%esp)
	call	_strerror
	movl	_stderr, %edx
	movl	%edx, (%esp)
	movl	$LC29, 4(%esp)
	movl	-356(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	-360(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%eax, 16(%esp)
	call	_fprintf
	jmp	L127
L113:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC3, 4(%esp)
	jmp	L134
L114:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC8, 4(%esp)
	jmp	L130
L115:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC9, 4(%esp)
	jmp	L134
L116:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC10, 4(%esp)
	jmp	L130
L117:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC11, 4(%esp)
	jmp	L134
L118:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC12, 4(%esp)
	jmp	L130
L119:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC13, 4(%esp)
	jmp	L134
L120:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC14, 4(%esp)
	jmp	L130
L121:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC15, 4(%esp)
	jmp	L134
L122:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC16, 4(%esp)
	jmp	L130
L123:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC16, 4(%esp)
L134:
	movl	-356(%ebp), %eax
	movl	%eax, 8(%esp)
	jmp	L126
L124:
	movl	_stderr, %eax
	movl	%eax, (%esp)
	movl	$LC17, 4(%esp)
L130:
	movl	-356(%ebp), %edx
	movl	%edx, 8(%esp)
L126:
	call	_fprintf
L127:
	movl	$1, %eax
	jmp	L1
L79:
	movl	_stdin, %eax
	movl	%eax, -396(%ebp)
L81:
	cmpl	$0, -368(%ebp)
	je	L82
	movl	-368(%ebp), %edx
	movl	%edx, (%esp)
	movl	-396(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_skip
L82:
	leal	-88(%ebp), %esi
	movl	%esi, %edi
	movl	-392(%ebp), %edx
	movl	%edx, (%esp)
	leal	-352(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_next_sync
	movl	%eax, -364(%ebp)
L83:
	leal	-24(%ebp), %ecx
	subl	%edi, %ecx
	movl	-364(%ebp), %edx
	subl	-392(%ebp), %edx
	movl	%edi, %eax
	subl	%esi, %eax
	subl	%eax, %edx
	cmpl	%edx, %ecx
	jbe	L86
	movl	%edx, %ecx
L86:
	testl	%ecx, %ecx
	je	L87
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	movl	%ecx, 8(%esp)
	movl	-396(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_fread
	movl	%eax, -372(%ebp)
	testl	%eax, %eax
	jne	L89
	movl	$1, -384(%ebp)
	jmp	L89
L87:
	movl	$0, -372(%ebp)
L89:
	addl	-372(%ebp), %edi
	movl	-364(%ebp), %edx
	cmpl	%edx, -392(%ebp)
	jne	L90
	cmpl	$0, -352(%ebp)
	je	L91
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC30, 4(%esp)
	movl	-392(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-352(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	movl	-352(%ebp), %eax
	addl	%eax, -392(%ebp)
	movl	%eax, (%esp)
	movl	-396(%ebp), %edx
	movl	%edx, 4(%esp)
	call	_skip
L91:
	leal	-88(%ebp), %esi
	movl	%esi, %edi
	movl	-392(%ebp), %eax
	movl	%eax, (%esp)
	leal	-352(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_next_sync
	movl	%eax, -364(%ebp)
L90:
	cmpl	%esi, %edi
	jbe	L93
	movl	%edi, %eax
	subl	%esi, %eax
	cmpl	$31, %eax
	jg	L98
	cmpl	$0, -372(%ebp)
	jne	L93
L98:
	movl	%esi, (%esp)
	leal	-344(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-380(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	-392(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-376(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	-388(%ebp), %eax
	movl	%eax, 20(%esp)
	call	_disasm
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L97
	movl	%edi, %eax
	subl	%esi, %eax
	cmpl	%eax, %ebx
	jg	L97
	movl	-364(%ebp), %eax
	subl	-392(%ebp), %eax
	cmpl	%eax, %ebx
	jbe	L96
L97:
	movl	%esi, (%esp)
	leal	-344(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_eatbyte
	movl	%eax, %ebx
L96:
	movl	-392(%ebp), %edx
	movl	%edx, (%esp)
	movl	%esi, 4(%esp)
	movl	%ebx, 8(%esp)
	leal	-344(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_output_ins
	addl	%ebx, %esi
	addl	%ebx, -392(%ebp)
	cmpl	%esi, %edi
	jbe	L93
	movl	%edi, %eax
	subl	%esi, %eax
	cmpl	$31, %eax
	jg	L98
	cmpl	$0, -372(%ebp)
	je	L98
L93:
	leal	-88(%ebp), %edx
	leal	-56(%ebp), %eax
	cmpl	%eax, %esi
	jb	L85
	movl	%edx, %ebx
	movl	%esi, %ecx
	movl	%edi, %edx
	subl	%esi, %edx
	decl	%edx
	cmpl	$-1, %edx
	je	L112
L103:
	movzbl	(%ecx), %eax
	movb	%al, (%ebx)
	incl	%ecx
	incl	%ebx
	decl	%edx
	cmpl	$-1, %edx
	jne	L103
L112:
	leal	-88(%ebp), %edx
	movl	%esi, %eax
	subl	%edx, %eax
	subl	%eax, %edi
	movl	%edx, %esi
L85:
	cmpl	$0, -372(%ebp)
	jg	L83
	cmpl	$0, -384(%ebp)
	jne	L84
	movl	-396(%ebp), %eax
	movl	%eax, (%esp)
	call	_feof
	testl	%eax, %eax
	je	L83
L84:
	movl	-396(%ebp), %edx
	cmpl	_stdin, %edx
	je	L106
	movl	%edx, (%esp)
	call	_fclose
L106:
	movl	$0, %eax
L1:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC31:
	.ascii "%08lX  \0"
LC32:
	.ascii "%02X\0"
LC33:
	.ascii "%*s%s\12\0"
LC34:
	.ascii "         -\0"
LC35:
	.ascii "\12\0"
	.align 2
	.def	_output_ins;	.scl	3;	.type	32;	.endef
_output_ins:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	12(%ebp), %edi
	movl	16(%ebp), %ebx
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC31, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	movl	$0, %esi
	testl	%ebx, %ebx
	jle	L138
L141:
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	movzbl	(%edi), %eax
	movl	%eax, 8(%esp)
	incl	%edi
	call	_fprintf
	incl	%esi
	decl	%ebx
	testl	%ebx, %ebx
	jle	L138
	cmpl	$7, %esi
	jle	L141
L138:
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC33, 4(%esp)
	movl	$9, %eax
	subl	%esi, %eax
	addl	%eax, %eax
	movl	%eax, 8(%esp)
	movl	$LC7, 12(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 16(%esp)
	call	_fprintf
	testl	%ebx, %ebx
	jle	L153
L150:
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC34, 4(%esp)
	call	_fprintf
	movl	$0, %esi
	testl	%ebx, %ebx
	jle	L146
L149:
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	movzbl	(%edi), %eax
	movl	%eax, 8(%esp)
	incl	%edi
	call	_fprintf
	incl	%esi
	decl	%ebx
	testl	%ebx, %ebx
	jle	L146
	cmpl	$7, %esi
	jle	L149
L146:
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC35, 4(%esp)
	call	_fprintf
	testl	%ebx, %ebx
	jg	L150
L153:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC36:
	.ascii "fread\0"
	.align 2
	.def	_skip;	.scl	3;	.type	32;	.endef
_skip:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$284, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	%edi, (%esp)
	call	_ftell
	leal	(%eax,%esi), %eax
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	call	_fseek
	testl	%eax, %eax
	je	L155
	testl	%esi, %esi
	je	L155
L162:
	movl	%esi, %ebx
	cmpl	$256, %esi
	jbe	L160
	movl	$256, %ebx
L160:
	leal	-280(%ebp), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	%edi, 12(%esp)
	call	_fread
	cmpl	%ebx, %eax
	jae	L161
	movl	$LC36, (%esp)
	call	_perror
	movl	$1, (%esp)
	call	_exit
L161:
	subl	%ebx, %esi
	jne	L162
L155:
	addl	$284, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_perror;	.scl	2;	.type	32;	.endef
	.def	_ftell;	.scl	2;	.type	32;	.endef
	.def	_fseek;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_feof;	.scl	2;	.type	32;	.endef
	.def	_eatbyte;	.scl	2;	.type	32;	.endef
	.def	_disasm;	.scl	2;	.type	32;	.endef
	.def	_fread;	.scl	2;	.type	32;	.endef
	.def	_next_sync;	.scl	2;	.type	32;	.endef
	.def	_strerror;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_strchr;	.scl	2;	.type	32;	.endef
	.def	_add_sync;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_tolower;	.scl	2;	.type	32;	.endef
	.def	_init_sync;	.scl	2;	.type	32;	.endef
