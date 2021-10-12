	.file	"preproc.c"
	.text
LC0:
	.ascii "a\0"
LC1:
	.ascii "ae\0"
LC2:
	.ascii "b\0"
LC3:
	.ascii "be\0"
LC4:
	.ascii "c\0"
LC5:
	.ascii "cxz\0"
LC6:
	.ascii "e\0"
LC7:
	.ascii "ecxz\0"
LC8:
	.ascii "g\0"
LC9:
	.ascii "ge\0"
LC10:
	.ascii "l\0"
LC11:
	.ascii "le\0"
LC12:
	.ascii "na\0"
LC13:
	.ascii "nae\0"
LC14:
	.ascii "nb\0"
LC15:
	.ascii "nbe\0"
LC16:
	.ascii "nc\0"
LC17:
	.ascii "ne\0"
LC18:
	.ascii "ng\0"
LC19:
	.ascii "nge\0"
LC20:
	.ascii "nl\0"
LC21:
	.ascii "nle\0"
LC22:
	.ascii "no\0"
LC23:
	.ascii "np\0"
LC24:
	.ascii "ns\0"
LC25:
	.ascii "nz\0"
LC26:
	.ascii "o\0"
LC27:
	.ascii "p\0"
LC28:
	.ascii "pe\0"
LC29:
	.ascii "po\0"
LC30:
	.ascii "s\0"
LC31:
	.ascii "z\0"
	.data
	.align 32
_conditions:
	.long	LC0
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC5
	.long	LC6
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
	.align 32
_inverse_ccs:
	.long	12
	.long	13
	.long	14
	.long	15
	.long	16
	.long	-1
	.long	17
	.long	-1
	.long	18
	.long	19
	.long	20
	.long	21
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	6
	.long	8
	.long	9
	.long	10
	.long	11
	.long	26
	.long	27
	.long	30
	.long	31
	.long	22
	.long	23
	.long	29
	.long	28
	.long	24
	.long	25
	.text
LC32:
	.ascii "%arg\0"
LC33:
	.ascii "%assign\0"
LC34:
	.ascii "%clear\0"
LC35:
	.ascii "%define\0"
LC36:
	.ascii "%elif\0"
LC37:
	.ascii "%elifctx\0"
LC38:
	.ascii "%elifdef\0"
LC39:
	.ascii "%elifid\0"
LC40:
	.ascii "%elifidn\0"
LC41:
	.ascii "%elifidni\0"
LC42:
	.ascii "%elifmacro\0"
LC43:
	.ascii "%elifnctx\0"
LC44:
	.ascii "%elifndef\0"
LC45:
	.ascii "%elifnid\0"
LC46:
	.ascii "%elifnidn\0"
LC47:
	.ascii "%elifnidni\0"
LC48:
	.ascii "%elifnmacro\0"
LC49:
	.ascii "%elifnnum\0"
LC50:
	.ascii "%elifnstr\0"
LC51:
	.ascii "%elifnum\0"
LC52:
	.ascii "%elifstr\0"
LC53:
	.ascii "%else\0"
LC54:
	.ascii "%endif\0"
LC55:
	.ascii "%endm\0"
LC56:
	.ascii "%endmacro\0"
LC57:
	.ascii "%endrep\0"
LC58:
	.ascii "%error\0"
LC59:
	.ascii "%exitrep\0"
LC60:
	.ascii "%iassign\0"
LC61:
	.ascii "%idefine\0"
LC62:
	.ascii "%if\0"
LC63:
	.ascii "%ifctx\0"
LC64:
	.ascii "%ifdef\0"
LC65:
	.ascii "%ifid\0"
LC66:
	.ascii "%ifidn\0"
LC67:
	.ascii "%ifidni\0"
LC68:
	.ascii "%ifmacro\0"
LC69:
	.ascii "%ifnctx\0"
LC70:
	.ascii "%ifndef\0"
LC71:
	.ascii "%ifnid\0"
LC72:
	.ascii "%ifnidn\0"
LC73:
	.ascii "%ifnidni\0"
LC74:
	.ascii "%ifnmacro\0"
LC75:
	.ascii "%ifnnum\0"
LC76:
	.ascii "%ifnstr\0"
LC77:
	.ascii "%ifnum\0"
LC78:
	.ascii "%ifstr\0"
LC79:
	.ascii "%imacro\0"
LC80:
	.ascii "%include\0"
LC81:
	.ascii "%ixdefine\0"
LC82:
	.ascii "%line\0"
LC83:
	.ascii "%local\0"
LC84:
	.ascii "%macro\0"
LC85:
	.ascii "%pop\0"
LC86:
	.ascii "%push\0"
LC87:
	.ascii "%rep\0"
LC88:
	.ascii "%repl\0"
LC89:
	.ascii "%rotate\0"
LC90:
	.ascii "%stacksize\0"
LC91:
	.ascii "%strlen\0"
LC92:
	.ascii "%substr\0"
LC93:
	.ascii "%undef\0"
LC94:
	.ascii "%xdefine\0"
	.data
	.align 32
_directives:
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
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
	.text
	.align 2
	.def	_is_condition;	.scl	3;	.type	32;	.endef
_is_condition:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	$0, %ecx
	leal	-4(%edx), %eax
	cmpl	$18, %eax
	jbe	L3
	leal	-30(%edx), %eax
	cmpl	$16, %eax
	ja	L2
L3:
	movl	$1, %ecx
L2:
	movl	%ecx, %eax
	popl	%ebp
	ret
LC95:
	.ascii "arg\0"
LC96:
	.ascii "elif\0"
LC97:
	.ascii "else\0"
LC98:
	.ascii "endif\0"
LC99:
	.ascii "if\0"
LC100:
	.ascii "ifdef\0"
LC101:
	.ascii "ifdifi\0"
LC102:
	.ascii "ifndef\0"
LC103:
	.ascii "include\0"
LC104:
	.ascii "local\0"
	.data
	.align 32
_tasm_directives:
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
	.align 4
_StackSize:
	.long	4
	.text
LC105:
	.ascii "ebp\0"
	.data
	.align 4
_StackPointer:
	.long	LC105
	.align 4
_ArgOffset:
	.long	8
	.align 4
_LocalOffset:
	.long	4
	.align 4
_ipath:
	.long	0
	.align 4
_predef:
	.long	0
	.text
LC106:
	.ascii "%idefine IDEAL\0"
LC107:
	.ascii "%idefine JUMPS\0"
LC108:
	.ascii "%idefine P386\0"
LC109:
	.ascii "%idefine P486\0"
LC110:
	.ascii "%idefine P586\0"
LC111:
	.ascii "%idefine END\0"
LC112:
	.ascii "%define __FILE__\0"
LC113:
	.ascii "%define __LINE__\0"
LC114:
	.ascii "%define __SECT__\0"
LC115:
	.ascii "%imacro section 1+.nolist\0"
LC116:
	.ascii "%define __SECT__ [section %1]\0"
LC117:
	.ascii "__SECT__\0"
LC118:
	.ascii "%imacro segment 1+.nolist\0"
LC119:
	.ascii "%define __SECT__ [segment %1]\0"
LC120:
	.ascii "%imacro absolute 1+.nolist\0"
	.align 32
LC121:
	.ascii "%define __SECT__ [absolute %1]\0"
LC122:
	.ascii "%imacro struc 1.nolist\0"
LC123:
	.ascii "%push struc\0"
LC124:
	.ascii "%define %$strucname %1\0"
LC125:
	.ascii "[absolute 0]\0"
LC126:
	.ascii "%$strucname:\0"
LC127:
	.ascii "%imacro endstruc 0.nolist\0"
LC128:
	.ascii "%{$strucname}_size:\0"
LC129:
	.ascii "%imacro istruc 1.nolist\0"
LC130:
	.ascii "%push istruc\0"
LC131:
	.ascii "%$strucstart:\0"
LC132:
	.ascii "%imacro at 1-2+.nolist\0"
	.align 32
LC133:
	.ascii "times %1-($-%$strucstart) db 0\0"
LC134:
	.ascii "%2\0"
LC135:
	.ascii "%imacro iend 0.nolist\0"
	.align 32
LC136:
	.ascii "times %{$strucname}_size-($-%$strucstart) db 0\0"
LC137:
	.ascii "%imacro align 1-2+.nolist nop\0"
LC138:
	.ascii "times ($$-$) & ((%1)-1) %2\0"
	.align 32
LC139:
	.ascii "%imacro alignb 1-2+.nolist resb 1\0"
LC140:
	.ascii "%imacro extern 1-*.nolist\0"
LC141:
	.ascii "%rep %0\0"
LC142:
	.ascii "[extern %1]\0"
LC143:
	.ascii "%rotate 1\0"
LC144:
	.ascii "%imacro bits 1+.nolist\0"
LC145:
	.ascii "[bits %1]\0"
LC146:
	.ascii "%imacro use16 0.nolist\0"
LC147:
	.ascii "[bits 16]\0"
LC148:
	.ascii "%imacro use32 0.nolist\0"
LC149:
	.ascii "[bits 32]\0"
LC150:
	.ascii "%imacro global 1-*.nolist\0"
LC151:
	.ascii "[global %1]\0"
LC152:
	.ascii "%imacro common 1-*.nolist\0"
LC153:
	.ascii "[common %1]\0"
LC154:
	.ascii "%imacro cpu 1+.nolist\0"
LC155:
	.ascii "[cpu %1]\0"
LC156:
	.ascii "%define __NASM_MAJOR__ 0\0"
LC157:
	.ascii "%define __NASM_MINOR__ 98\0"
LC158:
	.ascii "%define __NASM_SUBMINOR__ 38\0"
LC159:
	.ascii "%define __NASM_PATCHLEVEL__ 0\0"
	.align 32
LC160:
	.ascii "%define __NASM_VERSION_ID__ 000622600h\0"
	.align 32
LC161:
	.ascii "%define __NASM_VER__ \"0.98.38\"\0"
	.data
	.align 32
_stdmac:
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
	.long	LC117
	.long	LC56
	.long	LC118
	.long	LC119
	.long	LC117
	.long	LC56
	.long	LC120
	.long	LC121
	.long	LC117
	.long	LC56
	.long	LC122
	.long	LC123
	.long	LC124
	.long	LC125
	.long	LC126
	.long	LC56
	.long	LC127
	.long	LC128
	.long	LC85
	.long	LC117
	.long	LC56
	.long	LC129
	.long	LC130
	.long	LC124
	.long	LC131
	.long	LC56
	.long	LC132
	.long	LC133
	.long	LC134
	.long	LC56
	.long	LC135
	.long	LC136
	.long	LC85
	.long	LC56
	.long	LC137
	.long	LC138
	.long	LC56
	.long	LC139
	.long	LC138
	.long	LC56
	.long	LC140
	.long	LC141
	.long	LC142
	.long	LC143
	.long	LC57
	.long	LC56
	.long	LC144
	.long	LC145
	.long	LC56
	.long	LC146
	.long	LC147
	.long	LC56
	.long	LC148
	.long	LC149
	.long	LC56
	.long	LC150
	.long	LC141
	.long	LC151
	.long	LC143
	.long	LC57
	.long	LC56
	.long	LC152
	.long	LC141
	.long	LC153
	.long	LC143
	.long	LC57
	.long	LC56
	.long	LC154
	.long	LC155
	.long	LC56
	.long	LC156
	.long	LC157
	.long	LC158
	.long	LC159
	.long	LC160
	.long	LC161
	.long	0
	.align 4
_extrastdmac:
	.long	0
	.align 4
_freeTokens:
	.long	0
	.align 4
_blocks:
	.long	0
	.long	0
	.text
LC162:
	.ascii "ifdef BOGUS\0"
	.align 2
	.def	_check_tasm_directive;	.scl	3;	.type	32;	.endef
_check_tasm_directive:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %ebx
	jmp	L5
L9:
	incl	%ebx
L5:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L6
	cmpb	$0, (%ebx)
	jne	L9
L6:
	movl	$-1, -16(%ebp)
	movl	$10, -20(%ebp)
	movl	$0, %esi
	jmp	L10
L14:
	incl	%esi
L10:
	movsbl	(%esi,%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L11
	cmpb	$0, (%esi,%ebx)
	jne	L14
L11:
	testl	%esi, %esi
	je	L15
	movzbl	(%esi,%ebx), %eax
	movb	%al, -25(%ebp)
	movb	$0, (%esi,%ebx)
	movl	-20(%ebp), %eax
	subl	-16(%ebp), %eax
	cmpl	$1, %eax
	jle	L27
L25:
	movl	-20(%ebp), %eax
	addl	-16(%ebp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	movl	%eax, %edi
	sarl	%edi
	movl	%ebx, (%esp)
	movl	_tasm_directives(,%edi,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L19
	movzbl	-25(%ebp), %eax
	movb	%al, (%esi,%ebx)
	movl	%ebx, (%esp)
	call	_strlen
	movl	%eax, %esi
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	leal	2(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 8(%ebp)
	movb	$37, (%eax)
	cmpl	$6, %edi
	jne	L20
	movl	8(%ebp), %eax
	incl	%eax
	movl	%eax, (%esp)
	movl	$LC162, 4(%esp)
	call	_strcpy
	jmp	L21
L20:
	movl	8(%ebp), %eax
	incl	%eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	leal	1(%esi), %eax
	movl	%eax, 8(%esp)
	call	_memcpy
L21:
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	jmp	L15
L19:
	testl	%eax, %eax
	jns	L23
	movl	%edi, -20(%ebp)
	jmp	L16
L23:
	movl	%edi, -16(%ebp)
L16:
	movl	-20(%ebp), %eax
	subl	-16(%ebp), %eax
	cmpl	$1, %eax
	jg	L25
L27:
	movzbl	-25(%ebp), %eax
	movb	%al, (%esi,%ebx)
L15:
	movl	8(%ebp), %eax
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC163:
	.ascii "0123456789 \0"
LC164:
	.ascii "\"\0"
LC165:
	.ascii "%%line %d %.*s\0"
	.align 2
	.def	_prepreproc;	.scl	3;	.type	32;	.endef
_prepreproc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %esi
	cmpb	$35, (%esi)
	jne	L29
	cmpb	$32, 1(%esi)
	jne	L29
	movl	%esi, -20(%ebp)
	leal	2(%esi), %edi
	movl	%edi, (%esp)
	call	_atoi
	movl	%eax, -16(%ebp)
	movl	%edi, (%esp)
	movl	$LC163, 4(%esp)
	call	_strspn
	addl	%eax, %edi
	cmpb	$34, (%edi)
	jne	L30
	incl	%edi
L30:
	movl	%edi, (%esp)
	movl	$LC164, 4(%esp)
	call	_strcspn
	movl	%eax, %ebx
	leal	20(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%eax, (%esp)
	movl	$LC165, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%ebx, 12(%esp)
	movl	%edi, 16(%esp)
	call	_sprintf
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L29:
	cmpl	$0, _tasm_compatible_mode
	je	L31
	movl	%esi, (%esp)
	call	_check_tasm_directive
	jmp	L28
L31:
	movl	%esi, %eax
L28:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
_multipliers.0:
	.long	1
	.long	3
	.long	9
	.long	27
	.long	19
	.long	26
	.long	16
	.long	17
	.long	20
	.long	29
	.long	25
	.long	13
	.long	8
	.long	24
	.long	10
	.long	30
	.long	28
	.long	22
	.long	4
	.long	12
	.long	5
	.long	15
	.long	14
	.long	11
	.long	2
	.long	6
	.long	18
	.long	23
	.long	7
	.long	21
	.align 2
	.def	_hash;	.scl	3;	.type	32;	.endef
_hash:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %ebx
	movl	$0, %edi
	movl	$0, %esi
	cmpb	$0, (%ebx)
	je	L39
L37:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_toupper
	movzbl	%al, %eax
	imull	_multipliers.0(,%esi,4), %eax
	addl	%eax, %edi
	incl	%ebx
	incl	%esi
	cmpl	$30, %esi
	sbbl	%eax, %eax
	andl	%eax, %esi
	cmpb	$0, (%ebx)
	jne	L37
L39:
	movl	$138547333, %ecx
	movl	%edi, %eax
	mull	%ecx
	movl	%edi, %eax
	subl	%edx, %eax
	shrl	%eax
	addl	%edx, %eax
	shrl	$4, %eax
	movl	%eax, %edx
	sall	$5, %edx
	subl	%eax, %edx
	subl	%edx, %edi
	movl	%edi, %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_free_tlist;	.scl	3;	.type	32;	.endef
_free_tlist:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	je	L46
L44:
	movl	%eax, (%esp)
	call	_delete_Token
	testl	%eax, %eax
	jne	L44
L46:
	leave
	ret
	.align 2
	.def	_free_llist;	.scl	3;	.type	32;	.endef
_free_llist:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	testl	%esi, %esi
	je	L53
L51:
	movl	%esi, %ebx
	movl	(%esi), %esi
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	%ebx, (%esp)
	call	_nasm_free
	testl	%esi, %esi
	jne	L51
L53:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_free_mmacro;	.scl	3;	.type	32;	.endef
_free_mmacro:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	32(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	36(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	44(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_llist
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ctx_pop;	.scl	3;	.type	32;	.endef
_ctx_pop:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cstk, %edi
	movl	(%edi), %eax
	movl	%eax, _cstk
	movl	4(%edi), %esi
	testl	%esi, %esi
	je	L61
L59:
	movl	%esi, %ebx
	movl	(%esi), %esi
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	%ebx, (%esp)
	call	_nasm_free
	testl	%esi, %esi
	jne	L59
L61:
	movl	8(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%edi, (%esp)
	call	_nasm_free
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC166:
	.ascii "\32\0"
	.align 2
	.def	_read_line;	.scl	3;	.type	32;	.endef
_read_line:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	cmpl	$0, _stdmacpos
	je	L63
	movl	_stdmacpos, %edx
	cmpl	$0, (%edx)
	je	L64
	movl	(%edx), %eax
	movl	%eax, (%esp)
	leal	4(%edx), %eax
	movl	%eax, _stdmacpos
	call	_nasm_strdup
	movl	%eax, -28(%ebp)
	movl	_stdmacpos, %eax
	cmpl	$0, (%eax)
	jne	L65
	cmpl	$0, _any_extrastdmac
	je	L65
	movl	_extrastdmac, %eax
	movl	%eax, _stdmacpos
	movl	$0, _any_extrastdmac
	jmp	L66
L65:
	movl	_stdmacpos, %eax
	cmpl	$0, (%eax)
	jne	L66
	movl	_predef, %edi
	testl	%edi, %edi
	je	L66
L76:
	movl	$0, -16(%ebp)
	leal	-16(%ebp), %esi
	movl	8(%edi), %ebx
	testl	%ebx, %ebx
	je	L97
L75:
	movl	$0, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, (%esi)
	movl	%eax, %esi
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L75
L97:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_istk, %edx
	movl	12(%edx), %edx
	movl	%edx, (%eax)
	movl	-16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	$0, 4(%eax)
	movl	_istk, %edx
	movl	%eax, 12(%edx)
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L76
L66:
	movl	-28(%ebp), %eax
	jmp	L62
L64:
	movl	$0, _stdmacpos
L63:
	movl	$512, -20(%ebp)
	movl	$512, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	movl	%eax, %ebx
	movl	$0, -24(%ebp)
L88:
	movl	%ebx, (%esp)
	movl	%ebx, %eax
	subl	%edi, %eax
	movl	-20(%ebp), %edx
	subl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	_istk, %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	call	_fgets
	movl	%eax, %esi
	testl	%eax, %eax
	je	L99
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
	cmpl	%edi, %ebx
	jbe	L82
	cmpb	$10, -1(%ebx)
	jne	L82
	leal	-2(%ebx), %eax
	cmpl	%edi, %eax
	jbe	L83
	cmpb	$92, -3(%ebx)
	jne	L83
	cmpb	$13, -2(%ebx)
	jne	L83
	subl	$3, %ebx
	jmp	L100
L83:
	leal	-1(%ebx), %eax
	cmpl	%edi, %eax
	jbe	L79
	cmpb	$92, -2(%ebx)
	jne	L79
	subl	$2, %ebx
L100:
	movb	$0, (%ebx)
	incl	-24(%ebp)
L82:
	movl	%ebx, %esi
	subl	%edi, %esi
	movl	-20(%ebp), %eax
	subl	$10, %eax
	cmpl	%eax, %esi
	jle	L88
	addl	$512, -20(%ebp)
	movl	%edi, (%esp)
	movl	-20(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_nasm_realloc
	movl	%eax, %edi
	leal	(%esi,%eax), %ebx
	jmp	L88
L79:
	testl	%esi, %esi
	jne	L89
L99:
	cmpl	%edi, %ebx
	jne	L89
	movl	%edi, (%esp)
	call	_nasm_free
	movl	$0, %eax
	jmp	L62
L89:
	call	_src_get_linnum
	movl	_istk, %edx
	addl	24(%edx), %eax
	movl	-24(%ebp), %ecx
	imull	24(%edx), %ecx
	addl	%ecx, %eax
	movl	%eax, (%esp)
	call	_src_set_linnum
	decl	%ebx
	cmpl	%edi, %ebx
	jb	L91
	cmpb	$10, (%ebx)
	je	L94
	cmpb	$13, (%ebx)
	jne	L91
L94:
	movb	$0, (%ebx)
	decl	%ebx
	cmpl	%edi, %ebx
	jb	L91
	cmpb	$10, (%ebx)
	je	L94
	cmpb	$13, (%ebx)
	je	L94
L91:
	movl	%edi, (%esp)
	movl	$LC166, 4(%esp)
	call	_strcspn
	movb	$0, (%eax,%edi)
	movl	$0, (%esp)
	movl	%edi, 4(%esp)
	movl	_list, %eax
	call	*12(%eax)
	movl	%edi, %eax
L62:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC167:
	.ascii "unterminated string\0"
	.align 2
	.def	_tokenise;	.scl	3;	.type	32;	.endef
_tokenise:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	$0, -16(%ebp)
	leal	-16(%ebp), %eax
	movl	%eax, -20(%ebp)
	cmpb	$0, (%esi)
	je	L193
L191:
	movl	%esi, %ebx
	cmpb	$37, (%esi)
	jne	L105
	leal	1(%esi), %ebx
	movsbl	1(%esi),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L110
	cmpb	$45, 1(%esi)
	je	L109
	cmpb	$43, 1(%esi)
	jne	L106
L109:
	movsbl	1(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L110
	cmpb	$43, (%ebx)
	jne	L106
	movsbl	1(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L110
	cmpb	$0, 1(%ebx)
	jne	L106
L110:
	incl	%ebx
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	movl	$4, %edi
	testl	%eax, %eax
	je	L132
	jmp	L110
L106:
	cmpb	$123, (%ebx)
	jne	L115
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L117
	cmpb	$125, (%ebx)
	je	L117
L120:
	movzbl	(%ebx), %eax
	movb	%al, -1(%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L117
	cmpb	$125, (%ebx)
	jne	L120
L117:
	movb	$0, -1(%ebx)
	cmpb	$0, (%ebx)
	je	L198
	incl	%ebx
	jmp	L198
L115:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L126
	cmpb	$95, (%ebx)
	je	L126
	cmpb	$46, (%ebx)
	je	L126
	cmpb	$63, (%ebx)
	je	L126
	cmpb	$64, (%ebx)
	je	L126
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L126
	cmpb	$36, (%ebx)
	je	L126
	cmpb	$35, (%ebx)
	je	L126
	cmpb	$126, (%ebx)
	je	L126
	cmpb	$33, (%ebx)
	je	L125
	cmpb	$37, (%ebx)
	je	L125
	cmpb	$36, (%ebx)
	jne	L123
L125:
	movsbl	1(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L126
	cmpb	$95, 1(%ebx)
	je	L126
	cmpb	$46, 1(%ebx)
	je	L126
	cmpb	$63, 1(%ebx)
	je	L126
	cmpb	$64, 1(%ebx)
	je	L126
	movsbl	1(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L126
	cmpb	$36, 1(%ebx)
	je	L126
	cmpb	$35, 1(%ebx)
	je	L126
	cmpb	$126, 1(%ebx)
	jne	L123
L126:
	incl	%ebx
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L126
	cmpb	$95, (%ebx)
	je	L126
	cmpb	$46, (%ebx)
	je	L126
	cmpb	$63, (%ebx)
	je	L126
	cmpb	$64, (%ebx)
	je	L126
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L126
	cmpb	$36, (%ebx)
	je	L126
	cmpb	$35, (%ebx)
	je	L126
	cmpb	$126, (%ebx)
	je	L126
L198:
	movl	$4, %edi
	jmp	L132
L123:
	movl	$8, %edi
	cmpb	$37, (%ebx)
	jne	L132
	jmp	L178
L105:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L134
	cmpb	$95, (%esi)
	je	L134
	cmpb	$46, (%esi)
	je	L134
	cmpb	$63, (%esi)
	je	L134
	cmpb	$64, (%esi)
	je	L134
	cmpb	$36, (%esi)
	jne	L133
	movsbl	1(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L134
	cmpb	$95, 1(%esi)
	je	L134
	cmpb	$46, 1(%esi)
	je	L134
	cmpb	$63, 1(%esi)
	je	L134
	cmpb	$64, 1(%esi)
	jne	L133
L134:
	movl	$3, %edi
L139:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L132
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L139
	cmpb	$95, (%ebx)
	je	L139
	cmpb	$46, (%ebx)
	je	L139
	cmpb	$63, (%ebx)
	je	L139
	cmpb	$64, (%ebx)
	je	L139
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L139
	cmpb	$36, (%ebx)
	je	L139
	cmpb	$35, (%ebx)
	je	L139
	cmpb	$126, (%ebx)
	je	L139
	jmp	L132
L133:
	cmpb	$39, (%ebx)
	je	L142
	cmpb	$34, (%ebx)
	jne	L141
L142:
	movzbl	(%ebx), %eax
	incl	%ebx
	movl	$5, %edi
	cmpb	$0, (%ebx)
	je	L148
	cmpb	%al, (%ebx)
	je	L144
L147:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L148
	cmpb	%al, (%ebx)
	jne	L147
L144:
	cmpb	$0, (%ebx)
	jne	L178
L148:
	movl	$0, (%esp)
	movl	$LC167, 4(%esp)
	call	_error
	jmp	L132
L141:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L152
	cmpb	$36, (%ebx)
	jne	L151
L152:
	movl	$6, %edi
L157:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L132
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	jne	L157
	jmp	L132
L151:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L159
	movl	$1, %edi
L164:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L166
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L164
	cmpb	$0, (%ebx)
	je	L166
	cmpb	$59, (%ebx)
	jne	L132
L166:
	movl	$2, %edi
	cmpb	$0, (%ebx)
	je	L132
L170:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L132
	jmp	L170
L159:
	cmpb	$59, (%ebx)
	jne	L172
	movl	$2, %edi
L176:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L132
	jmp	L176
L172:
	movl	$8, %edi
	cmpb	$62, (%ebx)
	jne	L180
	cmpb	$62, 1(%ebx)
	je	L179
L180:
	cmpb	$60, (%ebx)
	jne	L181
	cmpb	$60, 1(%ebx)
	je	L179
L181:
	cmpb	$47, (%ebx)
	jne	L182
	cmpb	$47, 1(%ebx)
	je	L179
L182:
	cmpb	$60, (%ebx)
	jne	L183
	cmpb	$61, 1(%ebx)
	je	L179
L183:
	cmpb	$62, (%ebx)
	jne	L184
	cmpb	$61, 1(%ebx)
	je	L179
L184:
	cmpb	$61, (%ebx)
	jne	L185
	cmpb	$61, 1(%ebx)
	je	L179
L185:
	cmpb	$33, (%ebx)
	jne	L186
	cmpb	$61, 1(%ebx)
	je	L179
L186:
	cmpb	$60, (%ebx)
	jne	L187
	cmpb	$62, 1(%ebx)
	je	L179
L187:
	cmpb	$38, (%ebx)
	jne	L188
	cmpb	$38, 1(%ebx)
	je	L179
L188:
	cmpb	$124, (%ebx)
	jne	L189
	cmpb	$124, 1(%ebx)
	je	L179
L189:
	cmpb	$94, (%ebx)
	jne	L178
	cmpb	$94, 1(%ebx)
	jne	L178
L179:
	incl	%ebx
L178:
	incl	%ebx
L132:
	cmpl	$2, %edi
	je	L190
	movl	$0, (%esp)
	movl	%edi, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, %eax
	subl	%esi, %eax
	movl	%eax, 12(%esp)
	call	_new_Token
	movl	-20(%ebp), %edx
	movl	%eax, (%edx)
	movl	%eax, -20(%ebp)
L190:
	movl	%ebx, %esi
	cmpb	$0, (%ebx)
	jne	L191
L193:
	movl	-16(%ebp), %eax
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_new_Block;	.scl	3;	.type	32;	.endef
_new_Block:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	$_blocks, %ebx
	cmpl	$0, _blocks
	je	L205
L203:
	movl	(%ebx), %ebx
	cmpl	$0, (%ebx)
	jne	L203
L205:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 4(%ebx)
	movl	$8, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	$0, (%eax)
	movl	(%ebx), %eax
	movl	$0, 4(%eax)
	movl	4(%ebx), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_delete_Blocks;	.scl	3;	.type	32;	.endef
_delete_Blocks:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	$_blocks, %ebx
	testl	%ebx, %ebx
	je	L214
L212:
	cmpl	$0, 4(%ebx)
	je	L210
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L210:
	movl	%ebx, %eax
	movl	(%ebx), %ebx
	cmpl	$_blocks, %eax
	je	L207
	movl	%eax, (%esp)
	call	_nasm_free
L207:
	testl	%ebx, %ebx
	jne	L212
L214:
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.def	_new_Token;	.scl	3;	.type	32;	.endef
_new_Token:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	16(%ebp), %edi
	movl	20(%ebp), %esi
	cmpl	$0, _freeTokens
	jne	L216
	movl	$65536, (%esp)
	call	_new_Block
	movl	%eax, _freeTokens
	movl	$0, %ecx
L221:
	movl	%ecx, %eax
	sall	$4, %eax
	addl	_freeTokens, %eax
	leal	16(%eax), %edx
	movl	%edx, (%eax)
	incl	%ecx
	cmpl	$4094, %ecx
	jle	L221
	movl	%ecx, %edx
	sall	$4, %edx
	movl	_freeTokens, %eax
	movl	$0, (%eax,%edx)
L216:
	movl	_freeTokens, %ebx
	movl	(%ebx), %eax
	movl	%eax, _freeTokens
	movl	8(%ebp), %eax
	movl	%eax, (%ebx)
	movl	$0, 8(%ebx)
	movl	12(%ebp), %eax
	movl	%eax, 12(%ebx)
	cmpl	$1, %eax
	je	L223
	testl	%edi, %edi
	jne	L222
L223:
	movl	$0, 4(%ebx)
	jmp	L224
L222:
	testl	%esi, %esi
	jne	L225
	movl	%edi, (%esp)
	call	_strlen
	movl	%eax, %esi
L225:
	leal	1(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 4(%ebx)
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	movl	%esi, 8(%esp)
	call	_strncpy
	movl	4(%ebx), %eax
	movb	$0, (%esi,%eax)
L224:
	movl	%ebx, %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_delete_Token;	.scl	3;	.type	32;	.endef
_delete_Token:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	(%ebx), %esi
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	_freeTokens, %eax
	movl	%eax, (%ebx)
	movl	%ebx, _freeTokens
	movl	%esi, %eax
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC168:
	.ascii "$\0"
LC169:
	.ascii "..@%lu.\0"
	.align 2
	.def	_detoken;	.scl	3;	.type	32;	.endef
_detoken:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	$0, %edi
	movl	8(%ebp), %esi
	testl	%esi, %esi
	je	L252
L242:
	cmpl	$4, 12(%esi)
	jne	L234
	movl	4(%esi), %eax
	cmpb	$33, 1(%eax)
	jne	L234
	addl	$2, %eax
	movl	%eax, (%esp)
	call	_getenv
	movl	%eax, %ebx
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	testl	%ebx, %ebx
	je	L235
	movl	%ebx, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%esi)
	jmp	L234
L235:
	movl	$0, 4(%esi)
L234:
	cmpl	$0, 12(%ebp)
	je	L237
	cmpl	$4, 12(%esi)
	jne	L237
	cmpl	$0, 4(%esi)
	je	L237
	movl	4(%esi), %eax
	cmpb	$37, (%eax)
	jne	L237
	cmpb	$36, 1(%eax)
	jne	L237
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -76(%ebp)
	testl	%eax, %eax
	je	L237
	movl	4(%esi), %ebx
	addl	$2, %ebx
	movl	%ebx, (%esp)
	movl	$LC168, 4(%esp)
	call	_strspn
	addl	%eax, %ebx
	leal	-72(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC169, 4(%esp)
	movl	-76(%ebp), %edx
	movl	12(%edx), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	leal	-72(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_nasm_strcat
	movl	%eax, %ebx
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, 4(%esi)
L237:
	cmpl	$1, 12(%esi)
	jne	L239
	incl	%edi
	jmp	L232
L239:
	cmpl	$0, 4(%esi)
	je	L232
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_strlen
	addl	%eax, %edi
L232:
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L242
L252:
	leal	1(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	movl	%eax, %ebx
	movl	8(%ebp), %esi
	testl	%esi, %esi
	je	L254
L250:
	cmpl	$1, 12(%esi)
	jne	L247
	movb	$32, (%ebx)
	incl	%ebx
	movb	$0, (%ebx)
	jmp	L245
L247:
	cmpl	$0, 4(%esi)
	je	L245
	movl	%ebx, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
L245:
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L250
L254:
	movb	$0, (%ebx)
	movl	%edi, %eax
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC170:
	.ascii "seg\0"
LC171:
	.ascii "character constant too long\0"
LC172:
	.ascii "<<\0"
LC173:
	.ascii ">>\0"
LC174:
	.ascii "//\0"
LC175:
	.ascii "%%\0"
LC176:
	.ascii "==\0"
LC177:
	.ascii "<>\0"
LC178:
	.ascii "!=\0"
LC179:
	.ascii "<=\0"
LC180:
	.ascii ">=\0"
LC181:
	.ascii "&&\0"
LC182:
	.ascii "^^\0"
LC183:
	.ascii "||\0"
	.align 2
	.def	_ppscan;	.scl	3;	.type	32;	.endef
_ppscan:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	12(%ebp), %esi
	movl	8(%ebp), %edx
L256:
	movl	(%edx), %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	L260
	movl	(%ebx), %eax
L260:
	movl	%eax, (%edx)
	testl	%ebx, %ebx
	je	L288
	movl	12(%ebx), %eax
	decl	%eax
	cmpl	$1, %eax
	jbe	L256
	testl	%ebx, %ebx
	jne	L263
L288:
	movl	$0, (%esi)
	movl	$0, %eax
	jmp	L255
L263:
	movl	4(%ebx), %eax
	cmpb	$36, (%eax)
	jne	L264
	cmpb	$0, 1(%eax)
	jne	L264
	movl	$261, (%esi)
	movl	$261, %eax
	jmp	L255
L264:
	movl	4(%ebx), %eax
	cmpb	$36, (%eax)
	jne	L265
	cmpb	$36, 1(%eax)
	jne	L265
	cmpb	$0, 2(%eax)
	jne	L265
	movl	$262, (%esi)
	movl	$262, %eax
	jmp	L255
L265:
	cmpl	$3, 12(%ebx)
	jne	L266
	movl	4(%ebx), %edx
	movl	%edx, 12(%esi)
	movl	4(%ebx), %eax
	cmpb	$36, (%eax)
	jne	L267
	leal	1(%edx), %eax
	movl	%eax, 12(%esi)
	jmp	L268
L267:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC170, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L268
	movl	$275, (%esi)
	movl	$275, %eax
	jmp	L255
L268:
	movl	$256, (%esi)
	movl	$256, %eax
	jmp	L255
L266:
	cmpl	$6, 12(%ebx)
	jne	L269
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 4(%esi)
	cmpl	$0, -12(%ebp)
	jne	L273
	jmp	L274
L269:
	cmpl	$5, 12(%ebx)
	jne	L271
	movl	4(%ebx), %ebx
	movzbl	(%ebx), %eax
	movb	%al, -17(%ebp)
	incl	%ebx
	movl	%ebx, (%esp)
	call	_strlen
	testl	%eax, %eax
	je	L273
	movzbl	-17(%ebp), %edx
	cmpb	%dl, -1(%eax,%ebx)
	je	L272
L273:
	movl	$260, (%esi)
	movl	$260, %eax
	jmp	L255
L272:
	movl	%ebx, (%esp)
	decl	%eax
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_readstrnum
	movl	%eax, 4(%esi)
	cmpl	$0, -16(%ebp)
	je	L274
	movl	$64, (%esp)
	movl	$LC171, 4(%esp)
	call	_error
L274:
	movl	$0, 12(%esi)
	movl	$257, (%esi)
	movl	$257, %eax
	jmp	L255
L271:
	cmpl	$8, 12(%ebx)
	jne	L275
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC172, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L276
	movl	$265, (%esi)
	movl	$265, %eax
	jmp	L255
L276:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC173, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L277
	movl	$266, (%esi)
	movl	$266, %eax
	jmp	L255
L277:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC174, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L278
	movl	$267, (%esi)
	movl	$267, %eax
	jmp	L255
L278:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC175, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L279
	movl	$268, (%esi)
	movl	$268, %eax
	jmp	L255
L279:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC176, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L280
	movl	$61, (%esi)
	movl	$61, %eax
	jmp	L255
L280:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC177, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L289
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC178, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L282
L289:
	movl	$271, (%esi)
	movl	$271, %eax
	jmp	L255
L282:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC179, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L283
	movl	$270, (%esi)
	movl	$270, %eax
	jmp	L255
L283:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC180, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L284
	movl	$269, (%esi)
	movl	$269, %eax
	jmp	L255
L284:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC181, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L285
	movl	$272, (%esi)
	movl	$272, %eax
	jmp	L255
L285:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC182, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L286
	movl	$274, (%esi)
	movl	$274, %eax
	jmp	L255
L286:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC183, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L275
	movl	$273, (%esi)
	movl	$273, %eax
	jmp	L255
L275:
	movl	4(%ebx), %eax
	movsbl	(%eax),%eax
	movl	%eax, (%esi)
L255:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_mstrcmp;	.scl	3;	.type	32;	.endef
_mstrcmp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	cmpl	$0, 16(%ebp)
	je	L291
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_strcmp
	jmp	L290
L291:
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_nasm_stricmp
L290:
	movl	%ebp, %esp
	popl	%ebp
	ret
LC184:
	.ascii "`%s': context stack is empty\0"
	.align 32
LC185:
	.ascii "`%s': context stack is only %d level%s deep\0"
LC186:
	.ascii "\0"
	.align 2
	.def	_get_ctx;	.scl	3;	.type	32;	.endef
_get_ctx:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	je	L320
	cmpb	$37, (%ebx)
	jne	L320
	cmpb	$36, 1(%ebx)
	jne	L320
	cmpl	$0, _cstk
	jne	L295
	movl	$1, (%esp)
	movl	$LC184, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_error
	jmp	L320
L295:
	leal	2(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC168, 4(%esp)
	call	_strspn
	movl	%eax, %edx
	movl	_cstk, %edi
	testl	%eax, %eax
	jle	L297
	testl	%edi, %edi
	je	L318
L301:
	movl	(%edi), %edi
	decl	%edx
	testl	%edx, %edx
	jle	L297
	testl	%edi, %edi
	jne	L301
	jmp	L318
L297:
	testl	%edi, %edi
	jne	L302
L318:
	movl	$1, (%esp)
	movl	$LC185, 4(%esp)
	movl	%ebx, 8(%esp)
	leal	-1(%edx), %eax
	movl	%eax, 12(%esp)
	movl	$LC186, %eax
	cmpl	$2, %edx
	je	L304
	movl	$LC30, %eax
L304:
	movl	%eax, 16(%esp)
	call	_error
	jmp	L320
L302:
	movl	%edi, %eax
	cmpl	$0, 12(%ebp)
	je	L292
	jmp	L306
L319:
	movl	%edi, %eax
	jmp	L292
L306:
	movl	4(%edi), %esi
	testl	%esi, %esi
	je	L317
L313:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	je	L319
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L313
L317:
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L306
L320:
	movl	$0, %eax
L292:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.data
	.align 4
_namelen.1:
	.long	0
	.text
LC187:
	.ascii "r\0"
LC188:
	.ascii " \\\12  \0"
LC189:
	.ascii " %s\0"
	.align 32
LC190:
	.ascii "unable to open include file `%s'\0"
	.align 2
	.def	_inc_fopen;	.scl	3;	.type	32;	.endef
_inc_fopen:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$LC186, %esi
	movl	_ipath, %edi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, -16(%ebp)
L329:
	movl	%esi, (%esp)
	call	_strlen
	movl	-16(%ebp), %edx
	leal	1(%edx,%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcat
	movl	%ebx, (%esp)
	movl	$LC187, 4(%esp)
	call	_fopen
	movl	%eax, %esi
	cmpl	$0, _pass
	jne	L325
	testl	%eax, %eax
	je	L325
	movl	%ebx, (%esp)
	call	_strlen
	addl	_namelen.1, %eax
	incl	%eax
	movl	%eax, _namelen.1
	cmpl	$62, %eax
	jle	L326
	movl	$LC188, (%esp)
	call	_printf
	movl	$2, _namelen.1
L326:
	movl	$LC189, (%esp)
	movl	%ebx, 4(%esp)
	call	_printf
L325:
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	%esi, %eax
	testl	%esi, %esi
	jne	L321
	testl	%edi, %edi
	je	L323
	movl	4(%edi), %esi
	movl	(%edi), %edi
	jmp	L329
L323:
	movl	$2, (%esp)
	movl	$LC190, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, 8(%esp)
	call	_error
	movl	$0, %eax
L321:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_smacro_defined;	.scl	3;	.type	32;	.endef
_smacro_defined:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	testl	%edx, %edx
	jne	L350
	cmpb	$37, (%esi)
	jne	L333
	cmpb	$36, 1(%esi)
	jne	L333
	cmpl	$0, _cstk
	je	L334
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, %edx
L334:
	movl	$0, %eax
	testl	%edx, %edx
	je	L330
L350:
	movl	4(%edx), %ebx
	jmp	L332
L333:
	movl	%esi, (%esp)
	call	_hash
	movl	_smacros(,%eax,4), %ebx
L332:
	testl	%ebx, %ebx
	je	L349
L347:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	$0, %eax
	cmpl	$0, 8(%ebx)
	je	L341
	cmpl	$0, 24(%ebp)
	je	L341
	movl	$1, %eax
L341:
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	jne	L340
	testl	%edi, %edi
	jle	L342
	cmpl	$0, 12(%ebx)
	je	L342
	cmpl	12(%ebx), %edi
	jne	L340
L342:
	cmpl	$0, 20(%ebp)
	je	L343
	cmpl	12(%ebx), %edi
	je	L345
	cmpl	$-1, %edi
	jne	L344
L345:
	movl	20(%ebp), %eax
	movl	%ebx, (%eax)
	jmp	L343
L344:
	movl	20(%ebp), %eax
	movl	$0, (%eax)
L343:
	movl	$1, %eax
	jmp	L330
L340:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L347
L349:
	movl	$0, %eax
L330:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC191:
	.ascii "{\0"
LC192:
	.ascii "}\0"
LC193:
	.ascii ",\0"
	.align 32
LC194:
	.ascii "braces do not enclose all of macro parameter\0"
	.align 2
	.def	_count_mmac_params;	.scl	3;	.type	32;	.endef
_count_mmac_params:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edi
	movl	$0, -16(%ebp)
	movl	$0, (%edi)
	movl	16(%ebp), %eax
	movl	$0, (%eax)
	testl	%ebx, %ebx
	je	L378
L376:
	movl	-16(%ebp), %edx
	cmpl	%edx, (%edi)
	jl	L355
	addl	$16, %edx
	movl	%edx, -16(%ebp)
	movl	16(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%eax, (%esp)
	movl	%edx, %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	16(%ebp), %edx
	movl	%eax, (%edx)
L355:
	testl	%ebx, %ebx
	je	L356
	cmpl	$1, 12(%ebx)
	jne	L356
	movl	(%ebx), %ebx
L356:
	movl	$0, %esi
	testl	%ebx, %ebx
	je	L357
	cmpl	$8, 12(%ebx)
	jne	L357
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC191, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L357
	movl	$1, %esi
L357:
	movl	(%edi), %edx
	movl	16(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%ebx, (%eax,%edx,4)
	incl	(%edi)
	jmp	L358
L364:
	movl	(%ebx), %ebx
L358:
	testl	%ebx, %ebx
	je	L378
	cmpl	$8, 12(%ebx)
	jne	L364
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC192, %eax
	testl	%esi, %esi
	jne	L363
	movl	$LC193, %eax
L363:
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L364
	testl	%ebx, %ebx
	je	L378
	movl	(%ebx), %ebx
	testl	%esi, %esi
	je	L352
	testl	%ebx, %ebx
	je	L378
	cmpl	$1, 12(%ebx)
	jne	L367
	movl	(%ebx), %ebx
L367:
	testl	%ebx, %ebx
	je	L378
	cmpl	$8, 12(%ebx)
	jne	L369
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L368
L369:
	movl	$1, (%esp)
	movl	$LC194, 4(%esp)
	call	_error
	jmp	L370
L374:
	movl	(%ebx), %ebx
L370:
	testl	%ebx, %ebx
	je	L378
	cmpl	$8, 12(%ebx)
	jne	L374
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L374
L368:
	testl	%ebx, %ebx
	je	L378
	movl	(%ebx), %ebx
L352:
	testl	%ebx, %ebx
	jne	L376
L378:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC195:
	.ascii "`%s' expects context identifiers\0"
	.align 32
LC196:
	.ascii "`%s' expects macro identifiers\0"
	.align 32
LC197:
	.ascii "`%s' expects two comma-separated arguments\0"
LC199:
	.ascii "`%s' expects a macro name\0"
	.align 32
LC200:
	.ascii "`%s' expects a parameter count or nothing\0"
	.align 32
LC201:
	.ascii "unable to parse parameter count `%s'\0"
LC202:
	.ascii "-\0"
LC203:
	.ascii "*\0"
	.align 32
LC204:
	.ascii "`%s' expects a parameter count after `-'\0"
	.align 32
LC205:
	.ascii "minimum parameter count exceeds maximum\0"
LC206:
	.ascii "+\0"
	.align 32
LC207:
	.ascii "trailing garbage after expression ignored\0"
	.align 32
LC208:
	.ascii "non-constant value given to `%s'\0"
	.align 32
LC198:
	.ascii "`%s': more than one comma on line\0"
	.align 32
LC209:
	.ascii "preprocessor directive `%s' not yet implemented\0"
	.align 2
	.def	_if_condition;	.scl	3;	.type	32;	.endef
_if_condition:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$188, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	%esi, -152(%ebp)
	leal	-4(%edi), %eax
	cmpl	$42, %eax
	ja	L516
	jmp	*L517(,%eax,4)
	.align 4
	.align 4
L517:
	.long	L512
	.long	L384
	.long	L399
	.long	L487
	.long	L417
	.long	L417
	.long	L447
	.long	L384
	.long	L399
	.long	L487
	.long	L417
	.long	L417
	.long	L447
	.long	L487
	.long	L487
	.long	L487
	.long	L487
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L516
	.long	L512
	.long	L384
	.long	L399
	.long	L487
	.long	L417
	.long	L417
	.long	L447
	.long	L384
	.long	L399
	.long	L487
	.long	L417
	.long	L417
	.long	L447
	.long	L487
	.long	L487
	.long	L487
	.long	L487
L384:
	movl	$0, -140(%ebp)
	cmpl	$0, _cstk
	je	L386
	testl	%esi, %esi
	je	L386
L523:
	cmpl	$1, 12(%esi)
	jne	L389
	movl	(%esi), %esi
L389:
	testl	%esi, %esi
	je	L391
	cmpl	$3, 12(%esi)
	je	L390
L391:
	movl	$1, (%esp)
	movl	$LC195, 4(%esp)
	jmp	L536
L390:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	_cstk, %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L392
	movl	$1, -140(%ebp)
L392:
	movl	(%esi), %esi
	cmpl	$0, _cstk
	je	L386
	testl	%esi, %esi
	jne	L523
L386:
	cmpl	$37, %edi
	je	L409
	cmpl	$11, %edi
	jmp	L538
L399:
	movl	$0, -140(%ebp)
	testl	%esi, %esi
	je	L520
L524:
	cmpl	$1, 12(%esi)
	jne	L403
	movl	(%esi), %esi
L403:
	testl	%esi, %esi
	je	L405
	cmpl	$3, 12(%esi)
	je	L404
	cmpl	$4, 12(%esi)
	jne	L405
	movl	4(%esi), %eax
	cmpb	$36, 1(%eax)
	je	L404
L405:
	movl	$1, (%esp)
	movl	$LC196, 4(%esp)
	jmp	L536
L404:
	movl	$0, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$1, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	je	L406
	movl	$1, -140(%ebp)
L406:
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L524
L520:
	cmpl	$38, %edi
	je	L409
	cmpl	$12, %edi
L538:
	jne	L408
L409:
	cmpl	$0, -140(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -140(%ebp)
L408:
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L533
L417:
	movl	%esi, (%esp)
	call	_expand_smacro
	movl	%eax, %esi
	movl	%eax, %ebx
	movl	%eax, -144(%ebp)
	jmp	L418
L422:
	movl	(%ebx), %ebx
L418:
	testl	%ebx, %ebx
	je	L525
	cmpl	$8, 12(%ebx)
	jne	L422
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L422
	testl	%ebx, %ebx
	jne	L423
L525:
	movl	$1, (%esp)
	movl	$LC197, 4(%esp)
	jmp	L535
L423:
	movl	(%ebx), %ebx
	movl	$0, -148(%ebp)
	cmpl	$34, %edi
	je	L425
	cmpl	$8, %edi
	je	L425
	cmpl	$40, %edi
	je	L425
	cmpl	$14, %edi
	jne	L424
L425:
	movl	$1, -148(%ebp)
L424:
	movl	$1, -140(%ebp)
	jmp	L426
L439:
	cmpl	$8, 12(%ebx)
	jne	L431
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L527
L431:
	movl	-144(%ebp), %eax
	cmpl	$1, 12(%eax)
	jne	L432
	movl	(%eax), %eax
	movl	%eax, -144(%ebp)
	jmp	L426
L432:
	cmpl	$1, 12(%ebx)
	je	L528
	movl	-144(%ebp), %edx
	movl	12(%ebx), %eax
	cmpl	12(%edx), %eax
	jne	L437
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	4(%edx), %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	je	L436
L437:
	movl	$0, -140(%ebp)
	jmp	L427
L436:
	movl	-144(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -144(%ebp)
L528:
	movl	(%ebx), %ebx
L426:
	movl	-144(%ebp), %eax
	cmpl	$8, 12(%eax)
	jne	L430
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L427
L430:
	testl	%ebx, %ebx
	jne	L439
L427:
	movl	-144(%ebp), %eax
	cmpl	$8, 12(%eax)
	jne	L441
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L441
	testl	%ebx, %ebx
	je	L440
L441:
	movl	$0, -140(%ebp)
L440:
	cmpl	$40, %edi
	je	L510
	cmpl	$14, %edi
	je	L510
	cmpl	$41, %edi
	je	L510
	cmpl	$15, %edi
	jmp	L537
L447:
	movl	$0, -156(%ebp)
	movl	(%esi), %esi
	testl	%esi, %esi
	je	L448
	cmpl	$1, 12(%esi)
	jne	L448
	movl	(%esi), %esi
L448:
	movl	%esi, (%esp)
	call	_expand_id
	movl	%eax, %esi
	testl	%eax, %eax
	je	L450
	cmpl	$3, 12(%eax)
	je	L449
L450:
	movl	$1, (%esp)
	movl	$LC199, 4(%esp)
	jmp	L534
L449:
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, -132(%ebp)
	cmpl	$52, %edi
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -128(%ebp)
	movl	$0, -116(%ebp)
	movl	$0, -112(%ebp)
	movl	$0, -108(%ebp)
	movl	$0, -84(%ebp)
	movl	$0, -124(%ebp)
	movl	$2147483647, -120(%ebp)
	movl	(%esi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, %esi
	testl	%eax, %eax
	je	L466
	cmpl	$1, 12(%eax)
	jne	L451
	movl	(%eax), %esi
L451:
	testl	%esi, %esi
	je	L466
	cmpl	$6, 12(%esi)
	je	L454
	movl	$1, (%esp)
	movl	$LC200, 4(%esp)
	movl	_directives(,%edi,4), %eax
	jmp	L529
L454:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	leal	-140(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -120(%ebp)
	movl	%eax, -124(%ebp)
	cmpl	$0, -140(%ebp)
	je	L453
	movl	$1, (%esp)
	movl	$LC201, 4(%esp)
	movl	4(%esi), %eax
L529:
	movl	%eax, 8(%esp)
	call	_error
L453:
	testl	%esi, %esi
	je	L466
	cmpl	$0, (%esi)
	je	L458
	movl	(%esi), %eax
	cmpl	$8, 12(%eax)
	jne	L458
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC202, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L458
	movl	(%esi), %eax
	movl	(%eax), %esi
	testl	%esi, %esi
	je	L462
	cmpl	$8, 12(%esi)
	jne	L459
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	$LC203, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L459
	movl	$2147483647, -120(%ebp)
	jmp	L458
L459:
	testl	%esi, %esi
	je	L462
	cmpl	$6, 12(%esi)
	je	L461
L462:
	movl	$1, (%esp)
	movl	$LC204, 4(%esp)
	movl	_directives(,%edi,4), %eax
	movl	%eax, 8(%esp)
	call	_error
	jmp	L458
L461:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	leal	-140(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -120(%ebp)
	cmpl	$0, -140(%ebp)
	je	L464
	movl	$1, (%esp)
	movl	$LC201, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, 8(%esp)
	call	_error
L464:
	movl	-124(%ebp), %eax
	cmpl	-120(%ebp), %eax
	jle	L458
	movl	$1, (%esp)
	movl	$LC205, 4(%esp)
	call	_error
L458:
	testl	%esi, %esi
	je	L466
	cmpl	$0, (%esi)
	je	L466
	movl	(%esi), %eax
	cmpl	$8, 12(%eax)
	jne	L466
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC206, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L466
	movl	$1, -116(%ebp)
L466:
	movl	-132(%ebp), %eax
	movl	%eax, (%esp)
	call	_hash
	movl	_mmacros(,%eax,4), %ebx
	testl	%ebx, %ebx
	je	L468
L473:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	-132(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L470
	movl	12(%ebx), %eax
	cmpl	-120(%ebp), %eax
	jle	L471
	cmpl	$0, -116(%ebp)
	je	L470
L471:
	movl	-124(%ebp), %eax
	cmpl	16(%ebx), %eax
	jle	L472
	cmpl	$0, 20(%ebx)
	je	L470
L472:
	movl	$1, -156(%ebp)
	jmp	L468
L470:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L473
L468:
	movl	-132(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	cmpl	$42, %edi
	je	L475
	cmpl	$16, %edi
	jne	L474
L475:
	cmpl	$0, -156(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -156(%ebp)
L474:
	movl	-156(%ebp), %eax
	jmp	L379
L487:
	movl	%esi, (%esp)
	call	_expand_smacro
	movl	%eax, %esi
	movl	%eax, -144(%ebp)
	testl	%eax, %eax
	je	L489
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	jne	L489
L492:
	movl	(%edx), %eax
	movl	%eax, -144(%ebp)
	testl	%eax, %eax
	je	L489
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	je	L492
L489:
	movl	$0, -140(%ebp)
	cmpl	$0, -144(%ebp)
	je	L493
	leal	-7(%edi), %eax
	cmpl	$39, %eax
	ja	L493
	jmp	*L507(,%eax,4)
	.align 4
	.align 4
L507:
	.long	L498
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L498
	.long	L493
	.long	L493
	.long	L493
	.long	L502
	.long	L506
	.long	L502
	.long	L506
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L498
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L493
	.long	L498
	.long	L493
	.long	L493
	.long	L493
	.long	L502
	.long	L506
	.long	L502
	.long	L506
L498:
	movl	-144(%ebp), %eax
	cmpl	$3, 12(%eax)
	jmp	L530
L502:
	movl	-144(%ebp), %eax
	cmpl	$6, 12(%eax)
	jmp	L530
L506:
	movl	-144(%ebp), %eax
	cmpl	$5, 12(%eax)
L530:
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -140(%ebp)
L493:
	cmpl	$39, %edi
	je	L510
	cmpl	$13, %edi
	je	L510
	cmpl	$43, %edi
	je	L510
	cmpl	$17, %edi
	je	L510
	cmpl	$44, %edi
	je	L510
	cmpl	$18, %edi
L537:
	jne	L509
L510:
	cmpl	$0, -140(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -140(%ebp)
L509:
	movl	%esi, (%esp)
L533:
	call	_free_tlist
	movl	-140(%ebp), %eax
	jmp	L379
L512:
	movl	%esi, (%esp)
	call	_expand_smacro
	movl	%eax, %esi
	movl	%eax, -144(%ebp)
	movl	$-1, -40(%ebp)
	movl	$_ppscan, (%esp)
	leal	-144(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass, %eax
	orl	$256, %eax
	movl	%eax, 16(%esp)
	movl	$_error, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_free_tlist
	movl	$-1, %eax
	testl	%ebx, %ebx
	je	L379
	cmpl	$0, -40(%ebp)
	je	L514
	movl	$0, (%esp)
	movl	$LC207, 4(%esp)
	call	_error
L514:
	movl	%ebx, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L515
	movl	$1, (%esp)
	movl	$LC208, 4(%esp)
L534:
	movl	_directives(,%edi,4), %eax
	movl	%eax, 8(%esp)
	call	_error
	jmp	L532
L515:
	movl	%ebx, (%esp)
	call	_reloc_value
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	jmp	L379
L527:
	movl	$1, (%esp)
	movl	$LC198, 4(%esp)
L535:
	movl	_directives(,%edi,4), %eax
	movl	%eax, 8(%esp)
	call	_error
	movl	%esi, (%esp)
	jmp	L531
L516:
	movl	$2, (%esp)
	movl	$LC209, 4(%esp)
L536:
	movl	_directives(,%edi,4), %eax
	movl	%eax, 8(%esp)
	call	_error
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
L531:
	call	_free_tlist
L532:
	movl	$-1, %eax
L379:
	addl	$188, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _expand_macros_in_string
	.def	_expand_macros_in_string;	.scl	2;	.type	32;	.endef
_expand_macros_in_string:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_detoken
	movl	%eax, (%ebx)
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC210:
	.ascii "unknown preprocessor directive `%s'\0"
	.align 32
LC211:
	.ascii "`%%stacksize' missing size parameter\0"
LC212:
	.ascii "flat\0"
LC213:
	.ascii "large\0"
LC214:
	.ascii "bp\0"
LC215:
	.ascii "small\0"
	.align 32
LC216:
	.ascii "`%%stacksize' invalid size type\0"
	.align 32
LC217:
	.ascii "`%%arg' missing argument parameter\0"
	.align 32
LC218:
	.ascii "Syntax error processing `%%arg' directive\0"
	.align 32
LC219:
	.ascii "`%%arg' missing size type parameter\0"
LC220:
	.ascii "byte\0"
LC221:
	.ascii "word\0"
LC222:
	.ascii "dword\0"
LC223:
	.ascii "qword\0"
LC224:
	.ascii "tword\0"
	.align 32
LC225:
	.ascii "Invalid size type for `%%arg' missing directive\0"
LC226:
	.ascii "%%define %s (%s+%d)\0"
	.align 32
LC227:
	.ascii "`%%local' missing argument parameter\0"
	.align 32
LC228:
	.ascii "Syntax error processing `%%local' directive\0"
	.align 32
LC229:
	.ascii "`%%local' missing size type parameter\0"
	.align 32
LC230:
	.ascii "Invalid size type for `%%local' missing directive\0"
LC231:
	.ascii "%%define %s (%s-%d)\0"
	.align 32
LC232:
	.ascii "%%assign %%$localsize %%$localsize+%d\0"
	.align 32
LC233:
	.ascii "trailing garbage after `%%clear' ignored\0"
	.align 32
LC234:
	.ascii "`%%include' expects a file name\0"
	.align 32
LC235:
	.ascii "trailing garbage after `%%include' ignored\0"
	.align 32
LC236:
	.ascii "`%%push' expects a context identifier\0"
	.align 32
LC237:
	.ascii "trailing garbage after `%%push' ignored\0"
	.align 32
LC238:
	.ascii "`%%repl' expects a context identifier\0"
	.align 32
LC239:
	.ascii "trailing garbage after `%%repl' ignored\0"
	.align 32
LC240:
	.ascii "`%%repl': context stack is empty\0"
	.align 32
LC241:
	.ascii "trailing garbage after `%%pop' ignored\0"
	.align 32
LC242:
	.ascii "`%%pop': context stack is already empty\0"
LC243:
	.ascii "%s\0"
LC244:
	.ascii "`%s': no matching `%%if'\0"
	.align 32
LC245:
	.ascii "trailing garbage after `%%else' ignored\0"
LC246:
	.ascii "`%%else': no matching `%%if'\0"
	.align 32
LC247:
	.ascii "trailing garbage after `%%endif' ignored\0"
LC248:
	.ascii "`%%endif': no matching `%%if'\0"
	.align 32
LC249:
	.ascii "`%%%smacro': already defining a macro\0"
LC250:
	.ascii "i\0"
	.align 32
LC251:
	.ascii "`%%%smacro' expects a macro name\0"
	.align 32
LC252:
	.ascii "`%%%smacro' expects a parameter count\0"
	.align 32
LC253:
	.ascii "`%%%smacro' expects a parameter count after `-'\0"
LC254:
	.ascii ".nolist\0"
	.align 32
LC255:
	.ascii "redefining multi-line macro `%s'\0"
LC256:
	.ascii "`%s': not defining a macro\0"
	.align 32
LC257:
	.ascii "`%%rotate' missing rotate count\0"
	.align 32
LC258:
	.ascii "non-constant value given to `%%rotate'\0"
	.align 32
LC259:
	.ascii "`%%rotate' invoked outside a macro call\0"
	.align 32
LC260:
	.ascii "`%%rotate' invoked within macro without parameters\0"
	.align 32
LC261:
	.ascii "non-constant value given to `%%rep'\0"
	.align 32
LC262:
	.ascii "`%%rep' expects a repeat count\0"
	.align 32
LC263:
	.ascii "`%%endrep': no matching `%%rep'\0"
	.align 32
LC264:
	.ascii "`%%exitrep' not within `%%rep' block\0"
	.align 32
LC265:
	.ascii "`%%%s%sdefine' expects a macro identifier\0"
LC266:
	.ascii "x\0"
LC267:
	.ascii "(\0"
LC268:
	.ascii "parameter identifier expected\0"
LC270:
	.ascii ")\0"
	.align 32
LC271:
	.ascii "`)' expected to terminate macro template\0"
	.align 32
LC272:
	.ascii "single-line macro `%s' defined both with and without parameters\0"
	.align 32
LC273:
	.ascii "`%%undef' expects a macro identifier\0"
	.align 32
LC274:
	.ascii "trailing garbage after macro name ignored\0"
	.align 32
LC275:
	.ascii "`%%strlen' expects a macro identifier as first parameter\0"
	.align 32
LC276:
	.ascii "`%%strlen` requires string as second parameter\0"
	.align 32
LC277:
	.ascii "`%%substr' expects a macro identifier as first parameter\0"
	.align 32
LC278:
	.ascii "`%%substr` requires string as second parameter\0"
	.align 32
LC279:
	.ascii "non-constant value given to `%%substr`\0"
LC280:
	.ascii "'''\0"
	.align 32
LC281:
	.ascii "`%%%sassign' expects a macro identifier\0"
	.align 32
LC282:
	.ascii "non-constant value given to `%%%sassign'\0"
LC283:
	.ascii "`%%line' expects line number\0"
	.align 32
LC284:
	.ascii "`%%line' expects line increment\0"
	.align 32
LC269:
	.ascii "`%s': parameter identifier expected\0"
	.align 2
	.def	_do_directive;	.scl	3;	.type	32;	.endef
_do_directive:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$648, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	%edi, -608(%ebp)
	testl	%edi, %edi
	je	L971
	cmpl	$1, 12(%edi)
	jne	L541
	movl	(%edi), %edi
L541:
	testl	%edi, %edi
	je	L971
	cmpl	$4, 12(%edi)
	jne	L971
	movl	4(%edi), %edx
	movzbl	1(%edx), %eax
	subb	$36, %al
	cmpb	$1, %al
	jbe	L971
	cmpb	$33, 1(%edx)
	je	L971
	movl	$-1, -576(%ebp)
	movl	$63, -560(%ebp)
	movl	$63, %eax
	movl	%eax, %edx
	incl	%eax
	cmpl	$1, %eax
	jle	L545
L554:
	movl	-576(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	movl	%eax, %esi
	sarl	%esi
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	_directives(,%esi,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L547
	cmpl	$0, _tasm_compatible_mode
	jne	L964
	testl	%esi, %esi
	je	L545
	cmpl	$51, %esi
	je	L545
	cmpl	$58, %esi
	je	L545
L964:
	movl	%esi, -576(%ebp)
	movl	$-2, -560(%ebp)
	jmp	L545
L547:
	testl	%eax, %eax
	jns	L552
	movl	%esi, -560(%ebp)
	jmp	L544
L552:
	movl	%esi, -576(%ebp)
L544:
	movl	-560(%ebp), %edx
	movl	%edx, %eax
	subl	-576(%ebp), %eax
	cmpl	$1, %eax
	jg	L554
L545:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	je	L557
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L557
	cmpl	$2, 4(%eax)
	jne	L556
L557:
	movl	_istk, %eax
	cmpl	$0, 28(%eax)
	je	L555
	movl	28(%eax), %eax
	cmpl	$0, 28(%eax)
	jne	L555
L556:
	movl	-576(%ebp), %edx
	movl	%edx, (%esp)
	call	_is_condition
	movl	$0, %edx
	testl	%eax, %eax
	je	L540
L555:
	cmpl	$0, _defining
	je	L558
	cmpl	$52, -576(%ebp)
	je	L558
	cmpl	$47, -576(%ebp)
	je	L558
	cmpl	$24, -576(%ebp)
	je	L558
	cmpl	$23, -576(%ebp)
	je	L558
	movl	_defining, %eax
	cmpl	$0, 4(%eax)
	jne	L971
	cmpl	$25, -576(%ebp)
	je	L558
	cmpl	$55, -576(%ebp)
	jne	L971
L558:
	cmpl	$-2, -560(%ebp)
	je	L560
	movl	$1, (%esp)
	movl	$LC210, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_error
L971:
	movl	$0, %edx
	jmp	L540
L560:
	cmpl	$62, -576(%ebp)
	ja	L941
	movl	-576(%ebp), %ecx
	jmp	*L942(,%ecx,4)
	.align 4
	.align 4
L942:
	.long	L572
	.long	L915
	.long	L630
	.long	L816
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L709
	.long	L716
	.long	L722
	.long	L764
	.long	L764
	.long	L799
	.long	L668
	.long	L804
	.long	L915
	.long	L816
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L688
	.long	L726
	.long	L645
	.long	L816
	.long	L932
	.long	L601
	.long	L726
	.long	L664
	.long	L652
	.long	L782
	.long	L657
	.long	L766
	.long	L562
	.long	L878
	.long	L894
	.long	L860
	.long	L816
L562:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L565
	cmpl	$1, 12(%edi)
	jne	L563
	movl	(%edi), %edi
L563:
	testl	%edi, %edi
	je	L565
	cmpl	$3, 12(%edi)
	je	L564
L565:
	movl	$1, (%esp)
	movl	$LC211, 4(%esp)
	jmp	L1025
L564:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC212, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L566
	movl	$4, _StackSize
	movl	$LC105, _StackPointer
	movl	$8, _ArgOffset
	movl	$4, _LocalOffset
	jmp	L940
L566:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC213, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L568
	movl	$2, _StackSize
	movl	$LC214, _StackPointer
	movl	$4, _ArgOffset
	jmp	L965
L568:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC215, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L570
	movl	$2, _StackSize
	movl	$LC214, _StackPointer
	movl	$6, _ArgOffset
L965:
	movl	$2, _LocalOffset
	jmp	L940
L570:
	movl	$1, (%esp)
	movl	$LC216, 4(%esp)
	jmp	L1040
L572:
	movl	_ArgOffset, %eax
	movl	%eax, -584(%ebp)
L573:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L578
	cmpl	$1, 12(%edi)
	jne	L576
	movl	(%edi), %edi
L576:
	testl	%edi, %edi
	je	L578
	cmpl	$3, 12(%edi)
	je	L577
L578:
	movl	$1, (%esp)
	movl	$LC217, 4(%esp)
	jmp	L1040
L577:
	movl	4(%edi), %ecx
	movl	%ecx, -612(%ebp)
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L580
	cmpl	$8, 12(%edi)
	jne	L580
	movl	4(%edi), %eax
	cmpb	$58, (%eax)
	je	L579
L580:
	movl	$1, (%esp)
	movl	$LC218, 4(%esp)
	jmp	L1025
L579:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L582
	cmpl	$3, 12(%edi)
	je	L581
L582:
	movl	$1, (%esp)
	movl	$LC219, 4(%esp)
	jmp	L1040
L581:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, -572(%ebp)
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, -572(%ebp)
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC220, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L583
	movl	_StackSize, %esi
	cmpl	$1, %esi
	jge	L585
	movl	$1, %esi
	jmp	L585
L583:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC221, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L586
	movl	_StackSize, %esi
	cmpl	$2, %esi
	jge	L585
	movl	$2, %esi
	jmp	L585
L586:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC222, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L589
	movl	_StackSize, %esi
	cmpl	$4, %esi
	jge	L585
	movl	$4, %esi
	jmp	L585
L589:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC223, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L592
	movl	_StackSize, %esi
	cmpl	$8, %esi
	jge	L585
	movl	$8, %esi
	jmp	L585
L592:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC224, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L595
	movl	_StackSize, %esi
	cmpl	$10, %esi
	jge	L585
	movl	$10, %esi
	jmp	L585
L595:
	movl	$1, (%esp)
	movl	$LC225, 4(%esp)
	call	_error
	movl	-572(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L1044
L585:
	movl	-572(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	leal	-296(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC226, 4(%esp)
	movl	-612(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	_StackPointer, %eax
	movl	%eax, 12(%esp)
	movl	-584(%ebp), %edx
	movl	%edx, 16(%esp)
	call	_sprintf
	movl	%ebx, (%esp)
	call	_tokenise
	movl	%eax, (%esp)
	call	_do_directive
	addl	%esi, -584(%ebp)
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L940
	cmpl	$1, 12(%edi)
	jne	L575
	movl	(%edi), %edi
L575:
	testl	%edi, %edi
	je	L940
	cmpl	$8, 12(%edi)
	jne	L940
	movl	4(%edi), %eax
	cmpb	$44, (%eax)
	je	L573
	jmp	L940
L601:
	movl	_LocalOffset, %eax
	movl	%eax, -584(%ebp)
L602:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L607
	cmpl	$1, 12(%edi)
	jne	L605
	movl	(%edi), %edi
L605:
	testl	%edi, %edi
	je	L607
	cmpl	$3, 12(%edi)
	je	L606
L607:
	movl	$1, (%esp)
	movl	$LC227, 4(%esp)
	jmp	L1040
L606:
	movl	4(%edi), %esi
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L609
	cmpl	$8, 12(%edi)
	jne	L609
	movl	4(%edi), %eax
	cmpb	$58, (%eax)
	je	L608
L609:
	movl	$1, (%esp)
	movl	$LC228, 4(%esp)
	jmp	L1043
L608:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L611
	cmpl	$3, 12(%edi)
	je	L610
L611:
	movl	$1, (%esp)
	movl	$LC229, 4(%esp)
	jmp	L1025
L610:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, -572(%ebp)
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, -572(%ebp)
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC220, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L612
	movl	_StackSize, %ebx
	cmpl	$1, %ebx
	jge	L614
	movl	$1, %ebx
	jmp	L614
L612:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC221, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L615
	movl	_StackSize, %ebx
	cmpl	$2, %ebx
	jge	L614
	movl	$2, %ebx
	jmp	L614
L615:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC222, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L618
	movl	_StackSize, %ebx
	cmpl	$4, %ebx
	jge	L614
	movl	$4, %ebx
	jmp	L614
L618:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC223, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L621
	movl	_StackSize, %ebx
	cmpl	$8, %ebx
	jge	L614
	movl	$8, %ebx
	jmp	L614
L621:
	movl	-572(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC224, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L624
	movl	_StackSize, %ebx
	cmpl	$10, %ebx
	jge	L614
	movl	$10, %ebx
	jmp	L614
L624:
	movl	$1, (%esp)
	movl	$LC230, 4(%esp)
	call	_error
	movl	-572(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L1041
L614:
	movl	-572(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	leal	-552(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	$LC231, 4(%esp)
	movl	%esi, 8(%esp)
	movl	_StackPointer, %eax
	movl	%eax, 12(%esp)
	movl	-584(%ebp), %eax
	movl	%eax, 16(%esp)
	call	_sprintf
	leal	-552(%ebp), %edx
	movl	%edx, (%esp)
	call	_tokenise
	movl	%eax, (%esp)
	call	_do_directive
	addl	%ebx, -584(%ebp)
	leal	-552(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	$LC232, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_sprintf
	leal	-552(%ebp), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, (%esp)
	call	_do_directive
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L1024
	cmpl	$1, 12(%edi)
	jne	L604
	movl	(%edi), %edi
L604:
	testl	%edi, %edi
	je	L1024
	cmpl	$8, 12(%edi)
	jne	L1024
	movl	4(%edi), %eax
	cmpb	$44, (%eax)
	je	L602
	jmp	L1024
L630:
	cmpl	$0, (%edi)
	je	L631
	movl	$0, (%esp)
	movl	$LC233, 4(%esp)
	call	_error
L631:
	movl	$0, -560(%ebp)
	cmpl	$30, -560(%ebp)
	jg	L940
L644:
	movl	-560(%ebp), %eax
	movl	%eax, %edx
	cmpl	$0, _mmacros(,%eax,4)
	je	L947
	movl	$_mmacros, %ebx
L639:
	movl	%edx, %eax
	movl	(%ebx,%edx,4), %ecx
	movl	(%ecx), %edx
	movl	%edx, (%ebx,%eax,4)
	movl	%ecx, (%esp)
	call	_free_mmacro
	movl	-560(%ebp), %edx
	cmpl	$0, (%ebx,%edx,4)
	jne	L639
L947:
	movl	-560(%ebp), %eax
	movl	%eax, %edx
	cmpl	$0, _smacros(,%eax,4)
	je	L949
	movl	$_smacros, %esi
L643:
	movl	(%esi,%edx,4), %ebx
	movl	(%ebx), %eax
	movl	%eax, (%esi,%edx,4)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	%ebx, (%esp)
	call	_nasm_free
	movl	-560(%ebp), %edx
	cmpl	$0, (%esi,%edx,4)
	jne	L643
L949:
	incl	-560(%ebp)
	cmpl	$30, -560(%ebp)
	jle	L644
	jmp	L940
L645:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L648
	cmpl	$1, 12(%edi)
	jne	L646
	movl	(%edi), %edi
L646:
	testl	%edi, %edi
	je	L648
	cmpl	$5, 12(%edi)
	je	L647
	cmpl	$10, 12(%edi)
	je	L647
L648:
	movl	$1, (%esp)
	movl	$LC234, 4(%esp)
	jmp	L1025
L647:
	cmpl	$0, (%edi)
	je	L649
	movl	$0, (%esp)
	movl	$LC235, 4(%esp)
	call	_error
L649:
	cmpl	$10, 12(%edi)
	je	L650
	movl	4(%edi), %eax
	incl	%eax
	movl	%eax, -556(%ebp)
	movl	%eax, (%esp)
	call	_strlen
	addl	-556(%ebp), %eax
	movb	$0, -1(%eax)
	jmp	L651
L650:
	movl	4(%edi), %eax
	movl	%eax, -556(%ebp)
L651:
	leal	-556(%ebp), %eax
	movl	%eax, (%esp)
	call	_expand_macros_in_string
	movl	$32, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	_istk, %eax
	movl	%eax, (%ebx)
	movl	$0, 8(%ebx)
	movl	-556(%ebp), %eax
	movl	%eax, (%esp)
	call	_inc_fopen
	movl	%eax, 4(%ebx)
	movl	-556(%ebp), %eax
	movl	%eax, (%esp)
	call	_src_set_fname
	movl	%eax, 16(%ebx)
	movl	$0, (%esp)
	call	_src_set_linnum
	movl	%eax, 20(%ebx)
	movl	$1, 24(%ebx)
	movl	$0, 12(%ebx)
	movl	$0, 28(%ebx)
	movl	%ebx, _istk
	movl	$3, (%esp)
	movl	_list, %eax
	call	*16(%eax)
	jmp	L1024
L652:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L653
	cmpl	$1, 12(%edi)
	jne	L653
	movl	(%edi), %edi
L653:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L655
	cmpl	$3, 12(%eax)
	je	L654
L655:
	movl	$1, (%esp)
	movl	$LC236, 4(%esp)
	jmp	L1043
L654:
	cmpl	$0, (%eax)
	je	L656
	movl	$0, (%esp)
	movl	$LC237, 4(%esp)
	call	_error
L656:
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, -592(%ebp)
	movl	_cstk, %eax
	movl	-592(%ebp), %edx
	movl	%eax, (%edx)
	movl	$0, 4(%edx)
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	-592(%ebp), %ecx
	movl	%eax, 8(%ecx)
	movl	_unique, %eax
	movl	%eax, 12(%ecx)
	incl	_unique
	movl	%ecx, _cstk
	jmp	L1023
L657:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L658
	cmpl	$1, 12(%edi)
	jne	L658
	movl	(%edi), %edi
L658:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L660
	cmpl	$3, 12(%eax)
	je	L659
L660:
	movl	$1, (%esp)
	movl	$LC238, 4(%esp)
	jmp	L1040
L659:
	cmpl	$0, (%eax)
	je	L661
	movl	$0, (%esp)
	movl	$LC239, 4(%esp)
	call	_error
L661:
	cmpl	$0, _cstk
	jne	L662
	movl	$1, (%esp)
	movl	$LC240, 4(%esp)
	jmp	L1043
L662:
	movl	_cstk, %eax
	movl	8(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	_cstk, %ebx
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 8(%ebx)
	jmp	L940
L664:
	cmpl	$0, (%edi)
	je	L665
	movl	$0, (%esp)
	movl	$LC241, 4(%esp)
	call	_error
L665:
	cmpl	$0, _cstk
	jne	L666
	movl	$1, (%esp)
	movl	$LC242, 4(%esp)
	jmp	L1025
L666:
	call	_ctx_pop
	jmp	L1023
L668:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, (%edi)
	movl	%eax, %edi
	testl	%eax, %eax
	je	L670
	cmpl	$1, 12(%eax)
	jne	L669
	movl	(%eax), %edi
L669:
	testl	%edi, %edi
	je	L670
	cmpl	$5, 12(%edi)
	jne	L670
	movl	4(%edi), %eax
	incl	%eax
	movl	%eax, -556(%ebp)
	movl	%eax, (%esp)
	call	_strlen
	addl	-556(%ebp), %eax
	movb	$0, -1(%eax)
	leal	-556(%ebp), %eax
	movl	%eax, (%esp)
	call	_expand_macros_in_string
	movl	$1, (%esp)
	movl	$LC243, 4(%esp)
	movl	-556(%ebp), %eax
	jmp	L966
L670:
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_detoken
	movl	%eax, -556(%ebp)
	movl	$0, (%esp)
	movl	$LC243, 4(%esp)
L966:
	movl	%eax, 8(%esp)
	call	_error
	movl	-556(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	jmp	L1024
L688:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	je	L689
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L689
	cmpl	$2, 4(%eax)
	je	L689
	movl	$4, -560(%ebp)
	jmp	L690
L689:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	movl	-576(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_if_condition
	movl	%eax, -560(%ebp)
	movl	$0, (%edi)
	movl	-608(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	cmpl	$0, -560(%ebp)
	js	L691
	cmpl	$0, -560(%ebp)
	sete	%al
	movzbl	%al, %eax
	jmp	L692
L691:
	movl	$4, %eax
L692:
	movl	%eax, -560(%ebp)
L690:
	movl	$8, (%esp)
	call	_nasm_malloc
	movl	%eax, %ecx
	movl	_istk, %eax
	movl	8(%eax), %eax
	movl	%eax, (%ecx)
	movl	-560(%ebp), %eax
	movl	%eax, 4(%ecx)
	movl	_istk, %eax
	movl	%ecx, 8(%eax)
	jmp	L561
L709:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	jne	L710
	movl	$2, (%esp)
	movl	$LC244, 4(%esp)
	movl	-576(%ebp), %edx
	movl	_directives(,%edx,4), %eax
	movl	%eax, 8(%esp)
	call	_error
L710:
	movl	_istk, %eax
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L712
	cmpl	$2, 4(%eax)
	je	L712
	cmpl	$4, 4(%eax)
	jne	L711
L712:
	movl	_istk, %eax
	movl	8(%eax), %eax
	movl	$4, 4(%eax)
	jmp	L561
L711:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_mmac_params
	movl	%eax, (%esp)
	movl	-576(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_if_condition
	movl	%eax, -560(%ebp)
	movl	$0, (%edi)
	movl	-608(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	_istk, %eax
	movl	8(%eax), %edx
	cmpl	$0, -560(%ebp)
	js	L714
	cmpl	$0, -560(%ebp)
	sete	%al
	movzbl	%al, %eax
	jmp	L715
L714:
	movl	$4, %eax
L715:
	movl	%eax, 4(%edx)
	jmp	L561
L716:
	cmpl	$0, (%edi)
	je	L717
	movl	$0, (%esp)
	movl	$LC245, 4(%esp)
	call	_error
L717:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	jne	L718
	movl	$2, (%esp)
	movl	$LC246, 4(%esp)
	call	_error
L718:
	movl	_istk, %eax
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L720
	cmpl	$2, 4(%eax)
	je	L720
	cmpl	$4, 4(%eax)
	jne	L719
L720:
	movl	_istk, %eax
	movl	8(%eax), %eax
	movl	$3, 4(%eax)
	jmp	L1024
L719:
	movl	_istk, %eax
	movl	8(%eax), %eax
	movl	$2, 4(%eax)
	jmp	L1024
L722:
	cmpl	$0, (%edi)
	je	L723
	movl	$0, (%esp)
	movl	$LC247, 4(%esp)
	call	_error
L723:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	jne	L724
	movl	$2, (%esp)
	movl	$LC248, 4(%esp)
	call	_error
L724:
	movl	_istk, %edx
	movl	8(%edx), %ecx
	movl	(%ecx), %eax
	movl	%eax, 8(%edx)
	movl	%ecx, (%esp)
	jmp	L1042
L726:
	cmpl	$0, _defining
	je	L727
	movl	$2, (%esp)
	movl	$LC249, 4(%esp)
	movl	$LC250, %eax
	cmpl	$47, -576(%ebp)
	je	L729
	movl	$LC186, %eax
L729:
	movl	%eax, 8(%esp)
	call	_error
L727:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L730
	cmpl	$1, 12(%edi)
	jne	L730
	movl	(%edi), %edi
L730:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L732
	cmpl	$3, 12(%eax)
	je	L731
L732:
	movl	$1, (%esp)
	movl	$LC251, 4(%esp)
	movl	$LC250, %eax
	cmpl	$47, -576(%ebp)
	je	L992
	movl	$LC186, %eax
	jmp	L992
L731:
	movl	$84, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, _defining
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	cmpl	$52, -576(%ebp)
	sete	%al
	movzbl	%al, %edx
	movl	_defining, %eax
	movl	%edx, 8(%eax)
	movl	_defining, %eax
	movl	$0, 20(%eax)
	movl	_defining, %eax
	movl	$0, 24(%eax)
	movl	_defining, %eax
	movl	$0, 28(%eax)
	movl	_defining, %eax
	movl	$0, 52(%eax)
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, %edi
	testl	%eax, %eax
	je	L737
	cmpl	$1, 12(%eax)
	jne	L735
	movl	(%eax), %edi
L735:
	testl	%edi, %edi
	je	L737
	cmpl	$6, 12(%edi)
	je	L736
L737:
	movl	$1, (%esp)
	movl	$LC252, 4(%esp)
	movl	$LC250, %eax
	cmpl	$47, -576(%ebp)
	je	L739
	movl	$LC186, %eax
L739:
	movl	%eax, 8(%esp)
	call	_error
	movl	_defining, %eax
	movl	$0, 16(%eax)
	movl	$0, 12(%eax)
	jmp	L740
L736:
	movl	_defining, %ebx
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	leal	-560(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 16(%ebx)
	movl	%eax, 12(%ebx)
	cmpl	$0, -560(%ebp)
	je	L740
	movl	$1, (%esp)
	movl	$LC201, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_error
L740:
	testl	%edi, %edi
	je	L753
	cmpl	$0, (%edi)
	je	L742
	movl	(%edi), %eax
	cmpl	$8, 12(%eax)
	jne	L742
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC202, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L742
	movl	(%edi), %eax
	movl	(%eax), %edi
	testl	%edi, %edi
	je	L746
	cmpl	$8, 12(%edi)
	jne	L743
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC203, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L743
	movl	_defining, %eax
	movl	$2147483647, 16(%eax)
	jmp	L742
L743:
	testl	%edi, %edi
	je	L746
	cmpl	$6, 12(%edi)
	je	L745
L746:
	movl	$1, (%esp)
	movl	$LC253, 4(%esp)
	movl	$LC250, %eax
	cmpl	$47, -576(%ebp)
	je	L748
	movl	$LC186, %eax
L748:
	movl	%eax, 8(%esp)
	call	_error
	jmp	L742
L745:
	movl	_defining, %ebx
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	leal	-560(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 16(%ebx)
	cmpl	$0, -560(%ebp)
	je	L750
	movl	$1, (%esp)
	movl	$LC201, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_error
L750:
	movl	_defining, %edx
	movl	12(%edx), %eax
	cmpl	16(%edx), %eax
	jle	L742
	movl	$1, (%esp)
	movl	$LC205, 4(%esp)
	call	_error
L742:
	testl	%edi, %edi
	je	L753
	cmpl	$0, (%edi)
	je	L752
	movl	(%edi), %eax
	cmpl	$8, 12(%eax)
	jne	L752
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC206, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L752
	movl	(%edi), %edi
	movl	_defining, %eax
	movl	$1, 20(%eax)
L752:
	testl	%edi, %edi
	je	L753
	cmpl	$0, (%edi)
	je	L753
	movl	(%edi), %eax
	cmpl	$3, 12(%eax)
	jne	L753
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC254, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L753
	movl	(%edi), %edi
	movl	_defining, %eax
	movl	$1, 24(%eax)
L753:
	movl	_defining, %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_hash
	movl	_mmacros(,%eax,4), %ebx
	testl	%ebx, %ebx
	je	L755
L760:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_defining, %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L757
	movl	_defining, %edx
	movl	12(%ebx), %eax
	cmpl	16(%edx), %eax
	jle	L758
	cmpl	$0, 20(%edx)
	je	L757
L758:
	movl	_defining, %eax
	movl	12(%eax), %eax
	cmpl	16(%ebx), %eax
	jle	L759
	cmpl	$0, 20(%ebx)
	je	L757
L759:
	movl	$0, (%esp)
	movl	$LC255, 4(%esp)
	movl	_defining, %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	call	_error
	jmp	L755
L757:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L760
L755:
	testl	%edi, %edi
	je	L761
	cmpl	$0, (%edi)
	je	L761
	movl	(%edi), %edx
	movl	_defining, %eax
	movl	%edx, 32(%eax)
	movl	$0, (%edi)
	movl	_defining, %eax
	movl	32(%eax), %edx
	movl	%edx, (%esp)
	leal	40(%eax), %edx
	movl	%edx, 4(%esp)
	addl	$36, %eax
	movl	%eax, 8(%esp)
	call	_count_mmac_params
	jmp	L762
L761:
	movl	_defining, %eax
	movl	$0, 32(%eax)
	movl	_defining, %eax
	movl	$0, 36(%eax)
L762:
	movl	_defining, %eax
	movl	$0, 44(%eax)
	jmp	L1023
L764:
	cmpl	$0, _defining
	jne	L765
	movl	$1, (%esp)
	movl	$LC256, 4(%esp)
	movl	4(%edi), %eax
	jmp	L992
L765:
	movl	_defining, %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_hash
	movl	%eax, %esi
	movl	$_mmacros, %ecx
	movl	(%ecx,%eax,4), %edx
	movl	_defining, %eax
	movl	%edx, (%eax)
	movl	_defining, %eax
	movl	%eax, (%ecx,%esi,4)
	movl	$0, _defining
	jmp	L1024
L766:
	cmpl	$0, (%edi)
	je	L959
	movl	(%edi), %eax
	cmpl	$1, 12(%eax)
	jne	L767
	movl	%eax, %edi
L767:
	cmpl	$0, (%edi)
	jne	L768
L959:
	movl	-608(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_free_tlist
	movl	$1, (%esp)
	movl	$LC257, 4(%esp)
	jmp	L998
L768:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, -564(%ebp)
	movl	$0, (%edi)
	movl	-608(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	-564(%ebp), %edi
	leal	-564(%ebp), %eax
	movl	$-1, -40(%ebp)
	movl	$_ppscan, (%esp)
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass, %eax
	movl	%eax, 16(%esp)
	movl	$_error, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	movl	%edi, (%esp)
	call	_free_tlist
	movl	$1, %edx
	testl	%esi, %esi
	je	L540
	cmpl	$0, -40(%ebp)
	je	L770
	movl	$0, (%esp)
	movl	$LC207, 4(%esp)
	call	_error
L770:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L771
	movl	$1, (%esp)
	movl	$LC258, 4(%esp)
	jmp	L998
L771:
	movl	_istk, %eax
	movl	28(%eax), %ebx
	testl	%ebx, %ebx
	je	L960
	cmpl	$0, 4(%ebx)
	jne	L773
L776:
	movl	48(%ebx), %ebx
	testl	%ebx, %ebx
	je	L960
	cmpl	$0, 4(%ebx)
	je	L776
L773:
	testl	%ebx, %ebx
	jne	L777
L960:
	movl	$1, (%esp)
	movl	$LC259, 4(%esp)
	jmp	L998
L777:
	cmpl	$0, 64(%ebx)
	jne	L779
	movl	$1, (%esp)
	movl	$LC260, 4(%esp)
	jmp	L998
L779:
	movl	%esi, (%esp)
	call	_reloc_value
	addl	68(%ebx), %eax
	movl	%eax, 68(%ebx)
	testl	%eax, %eax
	jns	L781
	negl	%eax
	cltd
	idivl	64(%ebx)
	movl	64(%ebx), %eax
	subl	%edx, %eax
	movl	%eax, 68(%ebx)
L781:
	movl	68(%ebx), %eax
	cltd
	idivl	64(%ebx)
	movl	%edx, 68(%ebx)
	jmp	L561
L782:
	movl	$0, -580(%ebp)
L783:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L794
	cmpl	$1, 12(%edi)
	je	L783
	testl	%edi, %edi
	je	L794
	cmpl	$3, 12(%edi)
	jne	L788
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC254, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L788
	movl	$1, -580(%ebp)
L789:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L794
	cmpl	$1, 12(%edi)
	je	L789
L788:
	testl	%edi, %edi
	je	L794
	movl	%edi, (%esp)
	call	_expand_smacro
	movl	%eax, -564(%ebp)
	leal	-564(%ebp), %eax
	movl	$-1, -40(%ebp)
	movl	$_ppscan, (%esp)
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass, %eax
	movl	%eax, 16(%esp)
	movl	$_error, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	testl	%eax, %eax
	je	L1024
	cmpl	$0, -40(%ebp)
	je	L796
	movl	$0, (%esp)
	movl	$LC207, 4(%esp)
	call	_error
L796:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L797
	movl	$1, (%esp)
	movl	$LC261, 4(%esp)
	jmp	L998
L797:
	movl	%esi, (%esp)
	call	_reloc_value
	movl	%eax, -576(%ebp)
	incl	-576(%ebp)
	jmp	L798
L794:
	movl	$1, (%esp)
	movl	$LC262, 4(%esp)
	call	_error
	movl	$0, -576(%ebp)
L798:
	movl	-608(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_free_tlist
	movl	_defining, %ebx
	movl	$84, (%esp)
	call	_nasm_malloc
	movl	%eax, _defining
	movl	$0, 4(%eax)
	movl	_defining, %eax
	movl	$0, 8(%eax)
	movl	_defining, %eax
	movl	$0, 20(%eax)
	movl	_defining, %eax
	movl	-580(%ebp), %edx
	movl	%edx, 24(%eax)
	movl	_defining, %eax
	movl	-576(%ebp), %ecx
	movl	%ecx, 28(%eax)
	movl	_defining, %eax
	movl	$0, 16(%eax)
	movl	$0, 12(%eax)
	movl	_defining, %eax
	movl	$0, 36(%eax)
	movl	_defining, %eax
	movl	$0, 32(%eax)
	movl	_defining, %eax
	movl	$0, 44(%eax)
	movl	_istk, %eax
	movl	28(%eax), %edx
	movl	_defining, %eax
	movl	%edx, 48(%eax)
	movl	_defining, %eax
	movl	%ebx, 52(%eax)
	jmp	L561
L799:
	cmpl	$0, _defining
	je	L801
	movl	_defining, %eax
	cmpl	$0, 4(%eax)
	je	L800
L801:
	movl	$1, (%esp)
	movl	$LC263, 4(%esp)
L998:
	call	_error
	jmp	L561
L800:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	_istk, %eax
	movl	12(%eax), %eax
	movl	%eax, (%edx)
	movl	_defining, %eax
	movl	%eax, 4(%edx)
	movl	$0, 8(%edx)
	movl	_istk, %eax
	movl	%edx, 12(%eax)
	movl	_defining, %edx
	movl	_istk, %eax
	movl	%edx, 28(%eax)
	movl	_list, %edx
	movl	_defining, %eax
	cmpl	$0, 24(%eax)
	je	L802
	movl	$2, %eax
	jmp	L803
L802:
	movl	$1, %eax
L803:
	movl	%eax, (%esp)
	call	*16(%edx)
	movl	_defining, %ebx
	movl	52(%ebx), %eax
	movl	%eax, _defining
	jmp	L1023
L804:
	movl	_istk, %eax
	movl	12(%eax), %edx
	testl	%edx, %edx
	je	L811
L810:
	cmpl	$0, 4(%edx)
	je	L807
	movl	4(%edx), %eax
	cmpl	$0, 4(%eax)
	je	L806
L807:
	movl	(%edx), %edx
	testl	%edx, %edx
	jne	L810
	jmp	L811
L806:
	testl	%edx, %edx
	je	L811
	movl	4(%edx), %eax
	movl	$0, 28(%eax)
	jmp	L1024
L811:
	movl	$1, (%esp)
	movl	$LC264, 4(%esp)
	jmp	L1040
L816:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L817
	cmpl	$1, 12(%edi)
	jne	L817
	movl	(%edi), %edi
L817:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L819
	cmpl	$3, 12(%eax)
	je	L818
	cmpl	$4, 12(%eax)
	jne	L819
	movl	4(%eax), %eax
	cmpb	$36, 1(%eax)
	je	L818
L819:
	movl	$1, (%esp)
	movl	$LC265, 4(%esp)
	cmpl	$29, -576(%ebp)
	je	L822
	movl	$LC186, %eax
	cmpl	$49, -576(%ebp)
	jne	L821
L822:
	movl	$LC250, %eax
L821:
	movl	%eax, 8(%esp)
	cmpl	$62, -576(%ebp)
	je	L825
	movl	$LC186, %eax
	cmpl	$49, -576(%ebp)
	jne	L824
L825:
	movl	$LC266, %eax
L824:
	movl	%eax, 12(%esp)
	call	_error
	jmp	L940
L818:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -592(%ebp)
	testl	%eax, %eax
	jne	L826
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_hash
	leal	_smacros(,%eax,4), %eax
	jmp	L968
L826:
	movl	-592(%ebp), %eax
	addl	$4, %eax
L968:
	movl	%eax, -596(%ebp)
	movl	4(%edi), %edx
	movl	%edx, -588(%ebp)
	movl	%edi, %ebx
	movl	(%edi), %edi
	movl	%edi, -600(%ebp)
	movl	$0, %esi
	cmpl	$62, -576(%ebp)
	je	L829
	cmpl	$49, -576(%ebp)
	jne	L828
L829:
	movl	%edi, (%esp)
	call	_expand_smacro
	movl	%eax, %edi
L828:
	testl	%edi, %edi
	je	L842
	cmpl	$8, 12(%edi)
	jne	L830
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC267, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L830
L969:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L961
	cmpl	$1, 12(%edi)
	jne	L834
	movl	(%edi), %edi
L834:
	testl	%edi, %edi
	jne	L835
L961:
	movl	$1, (%esp)
	movl	$LC268, 4(%esp)
L1043:
	call	_error
	jmp	L940
L835:
	cmpl	$3, 12(%edi)
	jne	L963
	leal	9(%esi), %eax
	movl	%eax, 12(%edi)
	incl	%esi
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L840
	cmpl	$1, 12(%edi)
	jne	L837
	movl	(%edi), %edi
L837:
	testl	%edi, %edi
	je	L840
	cmpl	$8, 12(%edi)
	jne	L838
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L969
L838:
	testl	%edi, %edi
	je	L840
	cmpl	$8, 12(%edi)
	jne	L840
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC270, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L832
L840:
	movl	$1, (%esp)
	movl	$LC271, 4(%esp)
	jmp	L1025
L832:
	movl	%edi, %ebx
	movl	(%edi), %edi
L830:
	testl	%edi, %edi
	je	L842
	cmpl	$1, 12(%edi)
	jne	L842
	movl	%edi, %ebx
	movl	(%edi), %edi
L842:
	movl	$0, -604(%ebp)
	movl	$0, (%ebx)
	movl	%edi, -564(%ebp)
	testl	%edi, %edi
	je	L954
L853:
	movl	-564(%ebp), %eax
	cmpl	$3, 12(%eax)
	jne	L846
	movl	-600(%ebp), %edx
	movl	%edx, -572(%ebp)
	testl	%edx, %edx
	je	L846
L852:
	movl	-572(%ebp), %eax
	cmpl	$8, 12(%eax)
	jle	L849
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	-564(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L849
	movl	-572(%ebp), %eax
	movl	12(%eax), %edx
	movl	-564(%ebp), %eax
	movl	%edx, 12(%eax)
L849:
	movl	-572(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -572(%ebp)
	testl	%eax, %eax
	jne	L852
L846:
	movl	-564(%ebp), %eax
	movl	(%eax), %edx
	movl	%edx, -572(%ebp)
	movl	-604(%ebp), %ecx
	movl	%ecx, (%eax)
	movl	-564(%ebp), %eax
	movl	%eax, -604(%ebp)
	movl	-572(%ebp), %eax
	movl	%eax, -564(%ebp)
	testl	%eax, %eax
	jne	L853
L954:
	movl	-592(%ebp), %edx
	movl	%edx, (%esp)
	movl	-588(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	leal	-568(%ebp), %eax
	movl	%eax, 12(%esp)
	cmpl	$3, -576(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	je	L854
	cmpl	$0, -568(%ebp)
	jne	L855
	movl	$0, (%esp)
	movl	$LC272, 4(%esp)
	movl	-588(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_error
	movl	-608(%ebp), %edx
	movl	%edx, (%esp)
	call	_free_tlist
	movl	-604(%ebp), %ecx
	jmp	L1026
L855:
	movl	-568(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-568(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	jmp	L857
L854:
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, -568(%ebp)
	movl	-596(%ebp), %eax
	movl	(%eax), %edx
	movl	-568(%ebp), %eax
	movl	%edx, (%eax)
	movl	-568(%ebp), %eax
	movl	-596(%ebp), %edx
	movl	%eax, (%edx)
L857:
	movl	-568(%ebp), %ebx
	movl	-588(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	movl	-568(%ebp), %eax
	movl	$0, %edx
	cmpl	$3, -576(%ebp)
	je	L859
	cmpl	$62, -576(%ebp)
	jne	L858
L859:
	movl	$1, %edx
L858:
	movl	%edx, 8(%eax)
	movl	-568(%ebp), %eax
	movl	%esi, 12(%eax)
	jmp	L1036
L860:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L861
	cmpl	$1, 12(%edi)
	jne	L861
	movl	(%edi), %edi
L861:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L863
	cmpl	$3, 12(%eax)
	je	L862
	cmpl	$4, 12(%eax)
	jne	L863
	movl	4(%eax), %eax
	cmpb	$36, 1(%eax)
	je	L862
L863:
	movl	$1, (%esp)
	movl	$LC273, 4(%esp)
	jmp	L1025
L862:
	cmpl	$0, (%edi)
	je	L864
	movl	$0, (%esp)
	movl	$LC274, 4(%esp)
	call	_error
L864:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -592(%ebp)
	testl	%eax, %eax
	jne	L865
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_hash
	leal	_smacros(,%eax,4), %eax
	movl	%eax, -596(%ebp)
	jmp	L866
L865:
	movl	-592(%ebp), %edx
	addl	$4, %edx
	movl	%edx, -596(%ebp)
L866:
	movl	4(%edi), %ecx
	movl	%ecx, -588(%ebp)
	movl	$0, (%edi)
	jmp	L867
L877:
	movl	-596(%ebp), %edx
	cmpl	$0, (%edx)
	je	L867
	movl	(%edx), %eax
	cmpl	-568(%ebp), %eax
	je	L871
L875:
	movl	(%edx), %edx
	cmpl	$0, (%edx)
	je	L867
	movl	(%edx), %eax
	cmpl	-568(%ebp), %eax
	jne	L875
L871:
	cmpl	$0, (%edx)
	je	L867
	movl	-568(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	movl	-568(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-568(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	-568(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L867:
	movl	-592(%ebp), %eax
	movl	%eax, (%esp)
	movl	-588(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$-1, 8(%esp)
	leal	-568(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$1, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	jne	L877
	jmp	L940
L878:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L879
	cmpl	$1, 12(%edi)
	jne	L879
	movl	(%edi), %edi
L879:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L881
	cmpl	$3, 12(%eax)
	je	L880
	cmpl	$4, 12(%eax)
	jne	L881
	movl	4(%eax), %eax
	cmpb	$36, 1(%eax)
	je	L880
L881:
	movl	$1, (%esp)
	movl	$LC275, 4(%esp)
	jmp	L1025
L880:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -592(%ebp)
	testl	%eax, %eax
	jne	L882
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_hash
	leal	_smacros(,%eax,4), %eax
	movl	%eax, -596(%ebp)
	jmp	L883
L882:
	movl	-592(%ebp), %edx
	addl	$4, %edx
	movl	%edx, -596(%ebp)
L883:
	movl	4(%edi), %ecx
	movl	%ecx, -588(%ebp)
	movl	%edi, %ebx
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, %edi
	movl	$0, (%ebx)
	movl	%eax, -564(%ebp)
	testl	%eax, %eax
	je	L885
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	jne	L885
L888:
	movl	(%edx), %eax
	movl	%eax, -564(%ebp)
	testl	%eax, %eax
	je	L885
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	je	L888
L885:
	movl	-564(%ebp), %eax
	cmpl	$5, 12(%eax)
	je	L889
	movl	$1, (%esp)
	movl	$LC276, 4(%esp)
	jmp	L1035
L889:
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, -604(%ebp)
	movl	$0, (%eax)
	movl	-564(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_strlen
	subl	$2, %eax
	movl	-604(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	call	_make_tok_num
	movl	-604(%ebp), %ecx
	movl	$0, 8(%ecx)
	movl	-592(%ebp), %eax
	movl	%eax, (%esp)
	movl	-588(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	leal	-568(%ebp), %eax
	movl	%eax, 12(%esp)
	cmpl	$59, -576(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	je	L890
	cmpl	$0, -568(%ebp)
	jne	L891
	movl	$0, (%esp)
	movl	$LC272, 4(%esp)
	movl	-588(%ebp), %ecx
	movl	%ecx, 8(%esp)
	call	_error
	jmp	L893
L891:
	movl	-568(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-568(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	jmp	L893
L890:
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, -568(%ebp)
	movl	-596(%ebp), %eax
	movl	(%eax), %edx
	movl	-568(%ebp), %eax
	movl	%edx, (%eax)
	movl	-568(%ebp), %eax
	movl	-596(%ebp), %edx
	movl	%eax, (%edx)
L893:
	movl	-568(%ebp), %ebx
	movl	-588(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	cmpl	$59, -576(%ebp)
	jmp	L1039
L894:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L895
	cmpl	$1, 12(%edi)
	jne	L895
	movl	(%edi), %edi
L895:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L897
	cmpl	$3, 12(%eax)
	je	L896
	cmpl	$4, 12(%eax)
	jne	L897
	movl	4(%eax), %eax
	cmpb	$36, 1(%eax)
	je	L896
L897:
	movl	$1, (%esp)
	movl	$LC277, 4(%esp)
	jmp	L1025
L896:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -592(%ebp)
	testl	%eax, %eax
	jne	L898
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_hash
	leal	_smacros(,%eax,4), %eax
	movl	%eax, -596(%ebp)
	jmp	L899
L898:
	movl	-592(%ebp), %edx
	addl	$4, %edx
	movl	%edx, -596(%ebp)
L899:
	movl	4(%edi), %ecx
	movl	%ecx, -588(%ebp)
	movl	%edi, %ebx
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, %edi
	movl	$0, (%ebx)
	movl	(%eax), %eax
	movl	%eax, -564(%ebp)
	testl	%eax, %eax
	je	L901
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	jne	L901
L904:
	movl	(%edx), %eax
	movl	%eax, -564(%ebp)
	testl	%eax, %eax
	je	L901
	movl	%eax, %edx
	cmpl	$1, 12(%eax)
	je	L904
L901:
	movl	-564(%ebp), %eax
	cmpl	$5, 12(%eax)
	je	L905
	movl	$1, (%esp)
	movl	$LC278, 4(%esp)
L1035:
	call	_error
	movl	%edi, (%esp)
	call	_free_tlist
	jmp	L1023
L905:
	movl	-564(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -572(%ebp)
	leal	-572(%ebp), %eax
	movl	$-1, -40(%ebp)
	movl	$_ppscan, (%esp)
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass, %eax
	movl	%eax, 16(%esp)
	movl	$_error, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	testl	%eax, %eax
	jne	L906
	movl	%edi, (%esp)
L1041:
	call	_free_tlist
	jmp	L1024
L906:
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L907
	movl	$1, (%esp)
	movl	$LC279, 4(%esp)
	call	_error
	jmp	L1038
L907:
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, -604(%ebp)
	movl	$0, (%eax)
	movl	$LC280, (%esp)
	call	_nasm_strdup
	movl	-604(%ebp), %edx
	movl	%eax, 4(%edx)
	cmpl	$0, 4(%esi)
	jle	L908
	movl	-564(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_strlen
	decl	%eax
	cmpl	%eax, 4(%esi)
	jge	L908
	movl	-604(%ebp), %eax
	movl	4(%eax), %ecx
	movl	-564(%ebp), %eax
	movl	4(%eax), %edx
	movl	4(%esi), %eax
	movzbl	(%eax,%edx), %eax
	movb	%al, 1(%ecx)
	jmp	L909
L908:
	movl	-604(%ebp), %edx
	movl	4(%edx), %eax
	movb	$0, 2(%eax)
L909:
	movl	-604(%ebp), %ecx
	movl	$5, 12(%ecx)
	movl	$0, 8(%ecx)
	movl	-592(%ebp), %eax
	movl	%eax, (%esp)
	movl	-588(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	leal	-568(%ebp), %eax
	movl	%eax, 12(%esp)
	cmpl	$60, -576(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	je	L910
	cmpl	$0, -568(%ebp)
	jne	L911
	movl	$0, (%esp)
	movl	$LC272, 4(%esp)
	movl	-588(%ebp), %ecx
	movl	%ecx, 8(%esp)
	call	_error
	jmp	L913
L911:
	movl	-568(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-568(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	jmp	L913
L910:
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, -568(%ebp)
	movl	-596(%ebp), %eax
	movl	(%eax), %edx
	movl	-568(%ebp), %eax
	movl	%edx, (%eax)
	movl	-568(%ebp), %eax
	movl	-596(%ebp), %edx
	movl	%eax, (%edx)
L913:
	movl	-568(%ebp), %ebx
	movl	-588(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	cmpl	$60, -576(%ebp)
L1039:
	sete	%al
	movzbl	%al, %edx
	movl	-568(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-568(%ebp), %eax
	movl	$0, 12(%eax)
	movl	-568(%ebp), %eax
	movl	-604(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	-568(%ebp), %eax
	movl	$0, 16(%eax)
L1038:
	movl	%edi, (%esp)
L1044:
	call	_free_tlist
	jmp	L940
L915:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L916
	cmpl	$1, 12(%edi)
	jne	L916
	movl	(%edi), %edi
L916:
	movl	%edi, (%esp)
	call	_expand_id
	movl	%eax, %edi
	testl	%eax, %eax
	je	L918
	cmpl	$3, 12(%eax)
	je	L917
	cmpl	$4, 12(%eax)
	jne	L918
	movl	4(%eax), %eax
	cmpb	$36, 1(%eax)
	je	L917
L918:
	movl	$1, (%esp)
	movl	$LC281, 4(%esp)
	movl	$LC250, %eax
	cmpl	$28, -576(%ebp)
	je	L1027
	movl	$LC186, %eax
	jmp	L1027
L917:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_get_ctx
	movl	%eax, -592(%ebp)
	testl	%eax, %eax
	jne	L921
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_hash
	leal	_smacros(,%eax,4), %eax
	movl	%eax, -596(%ebp)
	jmp	L922
L921:
	movl	-592(%ebp), %edx
	addl	$4, %edx
	movl	%edx, -596(%ebp)
L922:
	movl	4(%edi), %ecx
	movl	%ecx, -588(%ebp)
	movl	%edi, %ebx
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_expand_smacro
	movl	%eax, %edi
	movl	$0, (%ebx)
	movl	%eax, -564(%ebp)
	leal	-564(%ebp), %eax
	movl	$-1, -40(%ebp)
	movl	$_ppscan, (%esp)
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	_pass, %eax
	movl	%eax, 16(%esp)
	movl	$_error, 20(%esp)
	movl	$0, 24(%esp)
	call	*_evaluate
	movl	%eax, %esi
	movl	%edi, (%esp)
	call	_free_tlist
	testl	%esi, %esi
	je	L1023
	cmpl	$0, -40(%ebp)
	je	L924
	movl	$0, (%esp)
	movl	$LC207, 4(%esp)
	call	_error
L924:
	movl	%esi, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L925
	movl	$1, (%esp)
	movl	$LC282, 4(%esp)
	movl	$LC250, %eax
	cmpl	$28, -576(%ebp)
	je	L927
	movl	$LC186, %eax
L927:
	movl	%eax, 8(%esp)
	call	_error
	jmp	L1024
L925:
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%eax, -604(%ebp)
	movl	$0, (%eax)
	movl	%esi, (%esp)
	call	_reloc_value
	movl	-604(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	_make_tok_num
	movl	-604(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-592(%ebp), %edx
	movl	%edx, (%esp)
	movl	-588(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$0, 8(%esp)
	leal	-568(%ebp), %eax
	movl	%eax, 12(%esp)
	cmpl	$1, -576(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 16(%esp)
	call	_smacro_defined
	testl	%eax, %eax
	je	L928
	cmpl	$0, -568(%ebp)
	jne	L929
	movl	$0, (%esp)
	movl	$LC272, 4(%esp)
	movl	-588(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_error
	jmp	L931
L929:
	movl	-568(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-568(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	jmp	L931
L928:
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, -568(%ebp)
	movl	-596(%ebp), %ecx
	movl	(%ecx), %edx
	movl	%edx, (%eax)
	movl	-568(%ebp), %eax
	movl	%eax, (%ecx)
L931:
	movl	-568(%ebp), %ebx
	movl	-588(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	cmpl	$1, -576(%ebp)
	sete	%al
	movzbl	%al, %edx
	movl	-568(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-568(%ebp), %eax
	movl	$0, 12(%eax)
L1036:
	movl	-568(%ebp), %eax
	movl	-604(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	-568(%ebp), %eax
	movl	$0, 16(%eax)
	jmp	L940
L932:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L935
	cmpl	$1, 12(%edi)
	jne	L933
	movl	(%edi), %edi
L933:
	testl	%edi, %edi
	je	L935
	cmpl	$6, 12(%edi)
	je	L934
L935:
	movl	$1, (%esp)
	movl	$LC283, 4(%esp)
L1025:
	call	_error
	jmp	L1023
L934:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	leal	-560(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, %esi
	movl	$1, %ebx
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L939
	cmpl	$8, 12(%edi)
	jne	L936
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC206, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L936
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L938
	cmpl	$6, 12(%edi)
	je	L937
L938:
	movl	$1, (%esp)
	movl	$LC284, 4(%esp)
L1040:
	call	_error
L1024:
	movl	-608(%ebp), %edx
	movl	%edx, (%esp)
	jmp	L1022
L937:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	leal	-560(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, %ebx
	movl	(%edi), %edi
L936:
	testl	%edi, %edi
	je	L939
	cmpl	$1, 12(%edi)
	jne	L939
	movl	(%edi), %edi
L939:
	movl	%esi, (%esp)
	call	_src_set_linnum
	movl	_istk, %eax
	movl	%ebx, 24(%eax)
	testl	%edi, %edi
	je	L940
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_detoken
	movl	%eax, (%esp)
	call	_src_set_fname
	movl	%eax, (%esp)
L1042:
	call	_nasm_free
L940:
	movl	-608(%ebp), %ecx
L1026:
	movl	%ecx, (%esp)
	jmp	L1022
L963:
	movl	$1, (%esp)
	movl	$LC269, 4(%esp)
	movl	4(%edi), %eax
L1027:
	movl	%eax, 8(%esp)
	call	_error
L1023:
	movl	-608(%ebp), %eax
	movl	%eax, (%esp)
L1022:
	call	_free_tlist
	jmp	L561
L941:
	movl	$2, (%esp)
	movl	$LC209, 4(%esp)
	movl	-576(%ebp), %edx
	movl	_directives(,%edx,4), %eax
L992:
	movl	%eax, 8(%esp)
	call	_error
L561:
	movl	$1, %edx
L540:
	movl	%edx, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_find_cc;	.scl	3;	.type	32;	.endef
_find_cc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	je	L1046
	cmpl	$1, 12(%ebx)
	jne	L1046
	movl	(%ebx), %ebx
L1046:
	cmpl	$3, 12(%ebx)
	jne	L1050
	movl	(%ebx), %eax
	testl	%eax, %eax
	je	L1049
	cmpl	$1, 12(%eax)
	jne	L1048
	movl	(%eax), %eax
L1048:
	testl	%eax, %eax
	je	L1049
	cmpl	$8, 12(%eax)
	jne	L1050
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L1049
L1050:
	movl	$-1, %eax
	jmp	L1045
L1061:
	movl	%esi, %edi
	movl	$-2, -16(%ebp)
	jmp	L1052
L1049:
	movl	$-1, %edi
	movl	$32, -16(%ebp)
L1058:
	movl	-16(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	movl	%eax, %esi
	sarl	%esi
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_conditions(,%esi,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L1061
	testl	%eax, %eax
	jns	L1056
	movl	%esi, -16(%ebp)
	jmp	L1051
L1056:
	movl	%esi, %edi
L1051:
	movl	-16(%ebp), %eax
	subl	%edi, %eax
	cmpl	$1, %eax
	jg	L1058
L1052:
	cmpl	$-2, -16(%ebp)
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	orl	%edi, %eax
L1045:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC285:
	.ascii "`%s': not in a macro call\0"
LC286:
	.ascii "%d\0"
	.align 32
LC288:
	.ascii "condition code `%s' is not invertible\0"
	.align 32
LC287:
	.ascii "macro parameter %d is not a condition code\0"
	.align 2
	.def	_expand_mmac_params;	.scl	3;	.type	32;	.endef
_expand_mmac_params:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$108, %esp
	leal	-60(%ebp), %eax
	movl	%eax, -64(%ebp)
	movl	$0, -60(%ebp)
	cmpl	$0, 8(%ebp)
	je	L1128
L1109:
	movl	8(%ebp), %edx
	cmpl	$4, 12(%edx)
	jne	L1066
	movl	4(%edx), %eax
	cmpb	$43, 1(%eax)
	je	L1069
	cmpb	$45, 1(%eax)
	jne	L1068
L1069:
	movl	8(%ebp), %ecx
	movl	4(%ecx), %eax
	cmpb	$0, 2(%eax)
	jne	L1067
L1068:
	movl	8(%ebp), %edx
	movl	4(%edx), %eax
	cmpb	$37, 1(%eax)
	je	L1067
	movzbl	1(%eax), %eax
	subb	$48, %al
	cmpb	$9, %al
	ja	L1066
L1067:
	movl	$0, %ebx
	movl	$0, -68(%ebp)
	movl	8(%ebp), %edi
	movl	(%edi), %ecx
	movl	%ecx, 8(%ebp)
	movl	_istk, %eax
	movl	28(%eax), %esi
	testl	%esi, %esi
	je	L1132
	cmpl	$0, 4(%esi)
	jne	L1071
L1074:
	movl	48(%esi), %esi
	testl	%esi, %esi
	je	L1132
	cmpl	$0, 4(%esi)
	je	L1074
L1071:
	testl	%esi, %esi
	jne	L1075
L1132:
	movl	$1, (%esp)
	movl	$LC285, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_error
	jmp	L1076
L1075:
	movl	4(%edi), %eax
	movsbl	1(%eax),%eax
	cmpl	$45, %eax
	je	L1080
	cmpl	$45, %eax
	jg	L1105
	cmpl	$37, %eax
	je	L1079
	cmpl	$43, %eax
	je	L1088
	jmp	L1094
L1105:
	cmpl	$48, %eax
	jne	L1094
	movl	$6, -68(%ebp)
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC286, 4(%esp)
	movl	64(%esi), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	leal	-56(%ebp), %edx
	movl	%edx, (%esp)
	jmp	L1140
L1079:
	movl	$3, -68(%ebp)
	leal	-56(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	$LC169, 4(%esp)
	movl	76(%esi), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	4(%edi), %eax
	addl	$2, %eax
	movl	%eax, 4(%esp)
	call	_nasm_strcat
	jmp	L1134
L1080:
	movl	4(%edi), %eax
	addl	$2, %eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, -72(%ebp)
	decl	-72(%ebp)
	movl	-72(%ebp), %edx
	cmpl	64(%esi), %edx
	jl	L1081
	movl	$0, %ebx
	jmp	L1082
L1081:
	cmpl	$1, 64(%esi)
	jle	L1083
	movl	68(%esi), %ecx
	addl	%ecx, -72(%ebp)
	movl	-72(%ebp), %eax
	cltd
	idivl	64(%esi)
	movl	%edx, -72(%ebp)
L1083:
	movl	56(%esi), %eax
	movl	-72(%ebp), %ecx
	movl	(%eax,%ecx,4), %ebx
L1082:
	movl	%ebx, (%esp)
	call	_find_cc
	cmpl	$-1, %eax
	je	L1139
	movl	$3, -68(%ebp)
	cmpl	$-1, _inverse_ccs(,%eax,4)
	jne	L1086
	movl	$1, (%esp)
	movl	$LC288, 4(%esp)
	movl	_conditions(,%eax,4), %eax
	jmp	L1136
L1086:
	movl	_inverse_ccs(,%eax,4), %eax
	jmp	L1133
L1088:
	movl	4(%edi), %eax
	addl	$2, %eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, -72(%ebp)
	decl	-72(%ebp)
	movl	-72(%ebp), %eax
	cmpl	64(%esi), %eax
	jl	L1089
	movl	$0, %ebx
	jmp	L1090
L1089:
	cmpl	$1, 64(%esi)
	jle	L1091
	movl	68(%esi), %edx
	addl	%edx, -72(%ebp)
	movl	-72(%ebp), %eax
	cltd
	idivl	64(%esi)
	movl	%edx, -72(%ebp)
L1091:
	movl	56(%esi), %eax
	movl	-72(%ebp), %ecx
	movl	(%eax,%ecx,4), %ebx
L1090:
	movl	%ebx, (%esp)
	call	_find_cc
	cmpl	$-1, %eax
	jne	L1092
L1139:
	movl	$1, (%esp)
	movl	$LC287, 4(%esp)
	movl	-72(%ebp), %eax
	incl	%eax
L1136:
	movl	%eax, 8(%esp)
	call	_error
	jmp	L1098
L1092:
	movl	$3, -68(%ebp)
L1133:
	movl	_conditions(,%eax,4), %eax
	movl	%eax, (%esp)
L1140:
	call	_nasm_strdup
L1134:
	movl	%eax, %ebx
	jmp	L1076
L1094:
	movl	4(%edi), %eax
	incl	%eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, -72(%ebp)
	decl	-72(%ebp)
	movl	-72(%ebp), %eax
	cmpl	64(%esi), %eax
	jl	L1095
	movl	$0, %ebx
	jmp	L1096
L1095:
	cmpl	$1, 64(%esi)
	jle	L1097
	movl	68(%esi), %edx
	addl	%edx, -72(%ebp)
	movl	-72(%ebp), %eax
	cltd
	idivl	64(%esi)
	movl	%edx, -72(%ebp)
L1097:
	movl	56(%esi), %eax
	movl	-72(%ebp), %ecx
	movl	(%eax,%ecx,4), %ebx
L1096:
	testl	%ebx, %ebx
	je	L1098
	movl	$0, -76(%ebp)
	movl	72(%esi), %eax
	movl	$0, %ecx
	movl	-72(%ebp), %edx
	cmpl	(%eax,%edx,4), %ecx
	jge	L1098
L1103:
	movl	$0, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	-64(%ebp), %edx
	movl	%eax, (%edx)
	movl	%eax, -64(%ebp)
	movl	(%ebx), %ebx
	incl	-76(%ebp)
	movl	72(%esi), %eax
	movl	-76(%ebp), %edx
	movl	-72(%ebp), %ecx
	cmpl	(%eax,%ecx,4), %edx
	jl	L1103
L1098:
	movl	$0, %ebx
L1076:
	testl	%ebx, %ebx
	jne	L1106
	movl	%edi, (%esp)
	call	_delete_Token
	jmp	L1063
L1106:
	movl	-64(%ebp), %ecx
	movl	%edi, (%ecx)
	movl	%edi, -64(%ebp)
	movl	-68(%ebp), %eax
	movl	%eax, 12(%edi)
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, 4(%edi)
	movl	$0, 8(%edi)
	jmp	L1063
L1066:
	movl	8(%ebp), %ecx
	movl	-64(%ebp), %edx
	movl	%ecx, (%edx)
	movl	(%ecx), %eax
	movl	%eax, 8(%ebp)
	movl	$0, 8(%ecx)
	movl	%ecx, -64(%ebp)
L1063:
	cmpl	$0, 8(%ebp)
	jne	L1109
L1128:
	movl	-64(%ebp), %edx
	movl	$0, (%edx)
	movl	-60(%ebp), %edi
	testl	%edi, %edi
	je	L1111
	movl	(%edi), %ebx
	testl	%ebx, %ebx
	je	L1111
L1126:
	movl	12(%edi), %eax
	cmpl	$3, %eax
	je	L1118
	cmpl	$3, %eax
	jg	L1125
	cmpl	$1, %eax
	je	L1116
	jmp	L1112
L1125:
	cmpl	$6, %eax
	je	L1121
	jmp	L1112
L1116:
	cmpl	$1, 12(%ebx)
	jne	L1112
	jmp	L1138
L1118:
	cmpl	$3, 12(%ebx)
	je	L1137
L1121:
	cmpl	$6, 12(%ebx)
	jne	L1112
L1137:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_nasm_strcat
	movl	%eax, %esi
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%esi, 4(%edi)
L1138:
	movl	%ebx, (%esp)
	call	_delete_Token
	movl	%eax, (%edi)
L1112:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L1111
	movl	(%edi), %ebx
	testl	%ebx, %ebx
	jne	L1126
L1111:
	movl	-60(%ebp), %eax
	addl	$108, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC289:
	.ascii "__FILE__\0"
LC290:
	.ascii "__LINE__\0"
	.align 32
LC291:
	.ascii "macro call expects terminating `)'\0"
	.align 32
LC292:
	.ascii "macro `%s' exists, but not taking %d parameters\0"
LC293:
	.ascii "%+\0"
	.align 2
	.def	_expand_smacro;	.scl	3;	.type	32;	.endef
_expand_smacro:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	8(%ebp), %eax
	movl	%eax, -56(%ebp)
	testl	%eax, %eax
	je	L1143
	movl	(%eax), %eax
	movl	%eax, (%esp)
	movl	-56(%ebp), %edx
	movl	12(%edx), %eax
	movl	%eax, 4(%esp)
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, 8(%ebp)
	movl	-56(%ebp), %ecx
	movl	8(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 8(%edx)
	movl	4(%ecx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-56(%ebp), %ecx
	movl	$0, 4(%ecx)
L1143:
	leal	-16(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	$0, -16(%ebp)
	cmpl	$0, 8(%ebp)
	je	L1255
L1226:
	movl	8(%ebp), %edx
	movl	4(%edx), %edx
	movl	%edx, -60(%ebp)
	testl	%edx, %edx
	je	L1147
	movl	8(%ebp), %ecx
	movl	12(%ecx), %eax
	subl	$3, %eax
	cmpl	$1, %eax
	ja	L1148
	movl	%edx, (%esp)
	movl	$1, 4(%esp)
	call	_get_ctx
	jmp	L1149
L1148:
	movl	$0, %eax
L1149:
	testl	%eax, %eax
	jne	L1150
	movl	-60(%ebp), %eax
	movl	%eax, (%esp)
	call	_hash
	movl	_smacros(,%eax,4), %eax
	jmp	L1151
L1150:
	movl	4(%eax), %eax
L1151:
	movl	%eax, %esi
	testl	%eax, %eax
	je	L1147
L1157:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	-60(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	je	L1153
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L1157
	jmp	L1147
L1153:
	testl	%esi, %esi
	je	L1147
	movl	8(%ebp), %ecx
	movl	%ecx, -28(%ebp)
	movl	$0, -36(%ebp)
	movl	$0, -40(%ebp)
	cmpl	$0, 12(%esi)
	jne	L1164
	cmpl	$0, 20(%esi)
	jne	L1163
	movl	$LC289, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L1161
	movl	$0, -20(%ebp)
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ebx
	addl	$4, %ebx
	movl	%ebx, 4(%esp)
	call	_src_get
	movl	%ebx, (%esp)
	call	_nasm_quote
	movl	8(%ebp), %eax
	movl	$5, 12(%eax)
	jmp	L1144
L1161:
	movl	$LC290, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L1162
	movl	8(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	call	_src_get_linnum
	movl	8(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	_make_tok_num
	jmp	L1144
L1162:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L1273
L1164:
	movl	8(%ebp), %edx
	movl	(%edx), %edi
	testl	%edi, %edi
	je	L1168
	cmpl	$7, 12(%edi)
	jne	L1168
L1171:
	movl	8(%edi), %eax
	movl	$0, 16(%eax)
	movl	$0, 4(%edi)
	movl	%edi, (%esp)
	call	_delete_Token
	movl	8(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	%eax, %edi
	testl	%eax, %eax
	je	L1168
	cmpl	$7, 12(%eax)
	je	L1171
L1168:
	movl	%edi, 8(%ebp)
	testl	%edi, %edi
	je	L1175
	cmpl	$1, 12(%edi)
	je	L1164
	testl	%edi, %edi
	je	L1175
	cmpl	$8, 12(%edi)
	jne	L1175
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC267, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L1174
L1175:
	movl	-28(%ebp), %eax
	movl	%eax, 8(%ebp)
	movl	$0, %esi
	jmp	L1163
L1270:
	movl	$1, (%esp)
	movl	$LC291, 4(%esp)
	call	_error
	jmp	L1178
L1174:
	movl	$0, -64(%ebp)
	movl	$0, %ebx
	movl	$0, -52(%ebp)
	movl	$0, -44(%ebp)
	movl	$16, -48(%ebp)
	movl	$64, (%esp)
	call	_nasm_malloc
	movl	%eax, -36(%ebp)
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	-36(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	$64, (%esp)
	call	_nasm_malloc
	movl	%eax, -40(%ebp)
	movl	$0, (%eax)
L1201:
	movl	8(%ebp), %eax
	movl	(%eax), %edi
	testl	%edi, %edi
	je	L1181
	cmpl	$7, 12(%edi)
	jne	L1181
L1184:
	movl	8(%edi), %eax
	movl	$0, 16(%eax)
	movl	$0, 4(%edi)
	movl	%edi, (%esp)
	call	_delete_Token
	movl	8(%ebp), %edx
	movl	%eax, (%edx)
	movl	%eax, %edi
	testl	%eax, %eax
	je	L1181
	cmpl	$7, 12(%eax)
	je	L1184
L1181:
	movl	%edi, 8(%ebp)
	testl	%edi, %edi
	je	L1270
	cmpl	$1, 12(%edi)
	jne	L1186
	cmpl	$0, -52(%ebp)
	jg	L1186
	movl	-44(%ebp), %ecx
	movl	-40(%ebp), %eax
	cmpl	$0, (%eax,%ecx,4)
	je	L1272
	incl	%ebx
	jmp	L1201
L1186:
	movl	8(%ebp), %ecx
	cmpl	$8, 12(%ecx)
	jne	L1189
	movl	4(%ecx), %eax
	cmpb	$0, 1(%eax)
	jne	L1189
	movzbl	(%eax), %eax
	cmpb	$44, %al
	jne	L1190
	cmpl	$0, -64(%ebp)
	jne	L1190
	cmpl	$0, -52(%ebp)
	jg	L1190
	incl	-44(%ebp)
	movl	-48(%ebp), %eax
	cmpl	%eax, -44(%ebp)
	jl	L1191
	addl	$16, %eax
	movl	%eax, -48(%ebp)
	movl	-36(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ebx
	sall	$2, %ebx
	movl	%ebx, 4(%esp)
	call	_nasm_realloc
	movl	%eax, -36(%ebp)
	movl	-40(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%ebx, 4(%esp)
	call	_nasm_realloc
	movl	%eax, -40(%ebp)
L1191:
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	-44(%ebp), %ecx
	movl	-36(%ebp), %edx
	movl	%eax, (%edx,%ecx,4)
	movl	-40(%ebp), %eax
	movl	$0, (%eax,%ecx,4)
	jmp	L1271
L1190:
	cmpb	$123, %al
	jne	L1192
	cmpl	$0, -52(%ebp)
	jg	L1193
	cmpl	$0, -52(%ebp)
	jne	L1192
	movl	-44(%ebp), %edx
	movl	-40(%ebp), %ecx
	cmpl	$0, (%ecx,%edx,4)
	jne	L1192
L1193:
	incl	-52(%ebp)
	cmpl	$1, -52(%ebp)
	jne	L1192
L1272:
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	-44(%ebp), %ecx
	movl	-36(%ebp), %edx
	movl	%eax, (%edx,%ecx,4)
	jmp	L1201
L1192:
	cmpb	$125, %al
	jne	L1195
	cmpl	$0, -52(%ebp)
	jle	L1195
	decl	-52(%ebp)
	jne	L1195
	movl	$-1, -52(%ebp)
	jmp	L1201
L1195:
	cmpb	$40, %al
	jne	L1197
	cmpl	$0, -52(%ebp)
	jne	L1197
	incl	-64(%ebp)
L1197:
	cmpb	$41, %al
	jne	L1189
	cmpl	$0, -52(%ebp)
	jg	L1189
	decl	-64(%ebp)
	js	L1178
L1189:
	cmpl	$0, -52(%ebp)
	jns	L1200
	movl	$0, -52(%ebp)
	movl	$1, (%esp)
	movl	$LC194, 4(%esp)
	call	_error
L1200:
	movl	%ebx, %eax
	movl	-44(%ebp), %ecx
	movl	-40(%ebp), %edx
	addl	(%edx,%ecx,4), %eax
	incl	%eax
	movl	%eax, (%edx,%ecx,4)
L1271:
	movl	$0, %ebx
	jmp	L1201
L1178:
	incl	-44(%ebp)
	jmp	L1202
L1206:
	movl	(%esi), %esi
L1202:
	testl	%esi, %esi
	je	L1266
	movl	-44(%ebp), %ecx
	cmpl	%ecx, 12(%esi)
	jne	L1206
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	-60(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	jne	L1206
	testl	%esi, %esi
	jne	L1267
L1266:
	movl	$256, (%esp)
	movl	$LC292, 4(%esp)
	movl	-28(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	movl	-44(%ebp), %ecx
	movl	%ecx, 12(%esp)
	call	_error
L1163:
	testl	%esi, %esi
	je	L1268
L1267:
	cmpl	$0, 16(%esi)
	je	L1208
	movl	$0, %esi
L1208:
	testl	%esi, %esi
	jne	L1209
L1268:
	movl	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-40(%ebp), %edx
	movl	%edx, (%esp)
	call	_nasm_free
	movl	-28(%ebp), %ecx
	movl	%ecx, 8(%ebp)
	jmp	L1147
L1209:
	movl	8(%ebp), %edi
	testl	%edi, %edi
	je	L1211
	movl	(%edi), %eax
	movl	%eax, 8(%ebp)
	movl	$0, (%edi)
L1211:
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	$7, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%esi, 8(%eax)
	movl	$1, 16(%esi)
	movl	%eax, 8(%ebp)
	movl	20(%esi), %edi
	testl	%edi, %edi
	je	L1260
L1223:
	cmpl	$8, 12(%edi)
	jle	L1216
	movl	8(%ebp), %ecx
	movl	%ecx, -24(%ebp)
	leal	-24(%ebp), %eax
	movl	%eax, -68(%ebp)
	movl	12(%edi), %eax
	sall	$2, %eax
	movl	-36(%ebp), %edx
	movl	-36(%eax,%edx), %ebx
	movl	-40(%ebp), %ecx
	movl	-36(%eax,%ecx), %esi
	decl	%esi
	js	L1262
L1221:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	-68(%ebp), %edx
	movl	%eax, (%edx)
	movl	%eax, -68(%ebp)
	movl	(%ebx), %ebx
	decl	%esi
	jns	L1221
L1262:
	movl	-24(%ebp), %ecx
	movl	%ecx, 8(%ebp)
	jmp	L1214
L1216:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%edi), %eax
	movl	%eax, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, 8(%ebp)
L1214:
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L1223
L1260:
	movl	-36(%ebp), %edx
	movl	%edx, (%esp)
	call	_nasm_free
	movl	-40(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_nasm_free
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	jmp	L1144
L1147:
	movl	8(%ebp), %edx
	cmpl	$7, 12(%edx)
	jne	L1224
	movl	8(%edx), %eax
	movl	$0, 16(%eax)
	movl	%edx, (%esp)
L1273:
	call	_delete_Token
	movl	%eax, 8(%ebp)
	jmp	L1144
L1224:
	movl	8(%ebp), %eax
	movl	-32(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	8(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, 8(%ebp)
	movl	$0, 8(%eax)
	movl	$0, (%eax)
	movl	%eax, -32(%ebp)
L1144:
	cmpl	$0, 8(%ebp)
	jne	L1226
L1255:
	movl	-16(%ebp), %edi
	movl	$0, %esi
	testl	%edi, %edi
	je	L1228
L1269:
	cmpl	$3, 12(%edi)
	je	L1231
	cmpl	$4, 12(%edi)
	je	L1231
L1234:
	movl	(%edi), %edi
	testl	%edi, %edi
	je	L1228
	cmpl	$3, 12(%edi)
	je	L1231
	cmpl	$4, 12(%edi)
	jne	L1234
L1231:
	testl	%edi, %edi
	je	L1228
	cmpl	$0, (%edi)
	je	L1228
	movl	(%edi), %edx
	movl	12(%edx), %eax
	subl	$3, %eax
	cmpl	$1, %eax
	jbe	L1238
	cmpl	$6, 12(%edx)
	jne	L1237
L1238:
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	(%edi), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_nasm_strcat
	movl	%eax, %ebx
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_delete_Token
	movl	%eax, (%edi)
	movl	%ebx, 4(%edi)
	movl	$1, %esi
	jmp	L1227
L1237:
	movl	(%edi), %eax
	cmpl	$1, 12(%eax)
	jne	L1240
	cmpl	$0, (%eax)
	je	L1240
	movl	(%eax), %eax
	cmpl	$4, 12(%eax)
	jne	L1240
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC293, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L1240
	movl	$1, %ebx
L1247:
	cmpl	$0, (%edi)
	je	L1227
	cmpl	$2, %ebx
	je	L1245
	movl	(%edi), %eax
	cmpl	$1, 12(%eax)
	jne	L1227
L1245:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_delete_Token
	movl	%eax, (%edi)
	incl	%ebx
	cmpl	$3, %ebx
	jg	L1227
	jmp	L1247
L1240:
	movl	(%edi), %edi
L1227:
	testl	%edi, %edi
	jne	L1269
L1228:
	testl	%esi, %esi
	je	L1250
	movl	-16(%ebp), %ecx
	movl	%ecx, 8(%ebp)
	jmp	L1143
L1250:
	cmpl	$0, -56(%ebp)
	je	L1251
	cmpl	$0, -16(%ebp)
	je	L1252
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	movl	-56(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	4(%edx), %eax
	movl	%eax, 4(%ecx)
	movl	8(%edx), %eax
	movl	%eax, 8(%ecx)
	movl	12(%edx), %eax
	movl	%eax, 12(%ecx)
	movl	-16(%ebp), %eax
	movl	$0, 4(%eax)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_delete_Token
	jmp	L1253
L1252:
	movl	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$16, 8(%esp)
	call	_memset
	movl	-56(%ebp), %edx
	movl	$0, 4(%edx)
	movl	$1, 12(%edx)
L1253:
	movl	-56(%ebp), %ecx
	movl	%ecx, -16(%ebp)
L1251:
	movl	-16(%ebp), %eax
	addl	$76, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_expand_id;	.scl	3;	.type	32;	.endef
_expand_id:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ecx
	movl	$0, %esi
	testl	%ecx, %ecx
	je	L1284
	cmpl	$0, (%ecx)
	je	L1284
	movl	%ecx, %ebx
	cmpl	$0, (%ecx)
	je	L1278
	movl	(%ecx), %edx
	movl	12(%edx), %eax
	subl	$3, %eax
	cmpl	$1, %eax
	jbe	L1281
	cmpl	$6, 12(%edx)
	jne	L1278
L1281:
	movl	(%ebx), %ebx
	cmpl	$0, (%ebx)
	je	L1278
	movl	(%ebx), %edx
	movl	12(%edx), %eax
	subl	$3, %eax
	cmpl	$1, %eax
	jbe	L1281
	cmpl	$6, 12(%edx)
	je	L1281
L1278:
	movl	%ecx, %eax
	cmpl	%ecx, %ebx
	je	L1274
	testl	%ebx, %ebx
	je	L1283
	movl	(%ebx), %esi
	movl	$0, (%ebx)
L1283:
	movl	%ecx, (%esp)
	call	_expand_smacro
	movl	%eax, %ecx
	testl	%ebx, %ebx
	je	L1284
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L1284
	cmpl	$0, (%eax)
	je	L1286
L1289:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L1284
	cmpl	$0, (%ebx)
	jne	L1289
L1286:
	testl	%ebx, %ebx
	je	L1284
	movl	%esi, (%ebx)
L1284:
	movl	%ecx, %eax
L1274:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_is_mmacro;	.scl	3;	.type	32;	.endef
_is_mmacro:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_hash
	movl	_mmacros(,%eax,4), %ebx
	testl	%ebx, %ebx
	je	L1329
L1299:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	je	L1295
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L1299
	jmp	L1329
L1295:
	testl	%ebx, %ebx
	je	L1329
	movl	(%esi), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_count_mmac_params
	testl	%ebx, %ebx
	je	L1323
L1320:
	movl	12(%ebx), %eax
	cmpl	-12(%ebp), %eax
	jg	L1304
	cmpl	$0, 20(%ebx)
	jne	L1305
	movl	-12(%ebp), %eax
	cmpl	16(%ebx), %eax
	jg	L1304
L1305:
	cmpl	$0, 28(%ebx)
	jne	L1328
	cmpl	$0, 36(%ebx)
	je	L1307
	movl	12(%ebx), %eax
	addl	40(%ebx), %eax
	cmpl	%eax, -12(%ebp)
	jge	L1307
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebx), %eax
	addl	40(%ebx), %eax
	leal	4(,%eax,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, -16(%ebp)
	movl	12(%ebx), %eax
	movl	%eax, %edx
	addl	40(%ebx), %eax
	cmpl	%eax, -12(%ebp)
	jge	L1307
L1311:
	movl	-12(%ebp), %ecx
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	movl	36(%ebx), %eax
	movl	(%eax,%edx,4), %edx
	movl	-16(%ebp), %eax
	movl	%edx, (%eax,%ecx,4)
	incl	-12(%ebp)
	movl	12(%ebx), %edx
	movl	%edx, %eax
	addl	40(%ebx), %eax
	cmpl	%eax, -12(%ebp)
	jl	L1311
L1307:
	cmpl	$0, 20(%ebx)
	je	L1312
	movl	-12(%ebp), %eax
	cmpl	16(%ebx), %eax
	jle	L1312
	movl	16(%ebx), %eax
	movl	%eax, -12(%ebp)
L1312:
	cmpl	$0, -16(%ebp)
	jne	L1313
	movl	$4, (%esp)
	call	_nasm_malloc
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
L1313:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	-16(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	%ebx, %eax
	jmp	L1293
L1304:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L1323
L1319:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_mstrcmp
	testl	%eax, %eax
	je	L1301
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L1319
	jmp	L1323
L1301:
	testl	%ebx, %ebx
	jne	L1320
L1323:
	movl	$256, (%esp)
	movl	$LC292, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_error
L1328:
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L1329:
	movl	$0, %eax
L1293:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
LC294:
	.ascii ":\0"
	.align 2
	.def	_expand_mmacro;	.scl	3;	.type	32;	.endef
_expand_mmacro:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	$0, -24(%ebp)
	movl	$0, -28(%ebp)
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L1339
	cmpl	$1, 12(%eax)
	jne	L1331
	movl	(%eax), %ebx
L1331:
	testl	%ebx, %ebx
	je	L1339
	movl	12(%ebx), %eax
	subl	$3, %eax
	cmpl	$1, %eax
	ja	L1339
	movl	%ebx, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_is_mmacro
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	jne	L1334
	movl	%ebx, %esi
	movl	%ebx, -24(%ebp)
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L1339
	cmpl	$1, 12(%ebx)
	jne	L1335
	movl	%ebx, %esi
	movl	(%ebx), %ebx
L1335:
	testl	%ebx, %ebx
	je	L1339
	cmpl	$8, 12(%ebx)
	jne	L1336
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC294, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L1336
	movl	$1, -28(%ebp)
	movl	%ebx, %esi
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L1339
	cmpl	$1, 12(%ebx)
	jne	L1336
	movl	%ebx, %esi
	movl	(%ebx), %ebx
L1336:
	testl	%ebx, %ebx
	je	L1339
	cmpl	$3, 12(%ebx)
	jne	L1339
	movl	%ebx, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_is_mmacro
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	jne	L1338
L1339:
	movl	$0, %eax
	jmp	L1330
L1338:
	movl	$0, (%esi)
	movl	%ebx, 8(%ebp)
L1334:
	movl	$0, -36(%ebp)
	movl	-16(%ebp), %eax
	cmpl	$0, (%eax)
	je	L1386
L1344:
	incl	-36(%ebp)
	movl	-36(%ebp), %edx
	cmpl	$0, (%eax,%edx,4)
	jne	L1344
L1386:
	cmpl	$0, -36(%ebp)
	je	L1345
	movl	-36(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	jmp	L1346
L1345:
	movl	$0, %edi
L1346:
	movl	$0, %esi
	movl	-16(%ebp), %eax
	cmpl	$0, (%eax)
	je	L1388
L1362:
	movl	$0, -40(%ebp)
	movl	$0, -44(%ebp)
	movl	-32(%ebp), %eax
	cmpl	$0, 20(%eax)
	je	L1352
	movl	-36(%ebp), %eax
	decl	%eax
	cmpl	%eax, %esi
	jge	L1351
L1352:
	movl	$1, -44(%ebp)
L1351:
	movl	-16(%ebp), %eax
	movl	(%eax,%esi,4), %ebx
	testl	%ebx, %ebx
	je	L1354
	cmpl	$1, 12(%ebx)
	jne	L1353
	movl	(%ebx), %ebx
L1353:
	testl	%ebx, %ebx
	je	L1354
	cmpl	$8, 12(%ebx)
	jne	L1354
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC191, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L1354
	movl	(%ebx), %ebx
	movl	$1, -40(%ebp)
	movl	$0, -44(%ebp)
L1354:
	movl	-16(%ebp), %eax
	movl	%ebx, (%eax,%esi,4)
	movl	$0, (%edi,%esi,4)
	testl	%ebx, %ebx
	je	L1349
L1361:
	cmpl	$0, -44(%ebp)
	je	L1359
	cmpl	$8, 12(%ebx)
	jne	L1358
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L1349
L1358:
	cmpl	$0, -44(%ebp)
	je	L1359
	cmpl	$1, 12(%ebx)
	jne	L1359
	cmpl	$0, (%ebx)
	je	L1359
	movl	(%ebx), %eax
	cmpl	$8, 12(%eax)
	jne	L1359
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC193, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L1349
L1359:
	cmpl	$0, -40(%ebp)
	je	L1360
	cmpl	$8, 12(%ebx)
	jne	L1360
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC192, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L1349
L1360:
	movl	(%ebx), %ebx
	incl	(%edi,%esi,4)
	testl	%ebx, %ebx
	jne	L1361
L1349:
	incl	%esi
	movl	-16(%ebp), %eax
	cmpl	$0, (%eax,%esi,4)
	jne	L1362
L1388:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	_istk, %eax
	movl	12(%eax), %eax
	movl	%eax, (%edx)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%edx)
	movl	$0, 8(%edx)
	movl	_istk, %eax
	movl	%edx, 12(%eax)
	movl	-32(%ebp), %edx
	movl	$1, 28(%edx)
	movl	-16(%ebp), %eax
	movl	%eax, 56(%edx)
	movl	8(%ebp), %eax
	movl	%eax, 60(%edx)
	movl	-36(%ebp), %eax
	movl	%eax, 64(%edx)
	movl	$0, 68(%edx)
	movl	%edi, 72(%edx)
	movl	_unique, %eax
	movl	%eax, 76(%edx)
	incl	_unique
	movl	$0, 80(%edx)
	movl	_istk, %eax
	movl	28(%eax), %eax
	movl	%eax, 48(%edx)
	movl	_istk, %eax
	movl	%edx, 28(%eax)
	movl	44(%edx), %edi
	testl	%edi, %edi
	je	L1391
L1374:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	$0, 4(%eax)
	movl	_istk, %eax
	movl	12(%eax), %eax
	movl	%eax, (%edx)
	movl	_istk, %eax
	movl	%edx, 12(%eax)
	leal	8(%edx), %esi
	movl	8(%edi), %ebx
	testl	%ebx, %ebx
	je	L1393
L1373:
	movl	%ebx, %edx
	cmpl	$4, 12(%ebx)
	jne	L1371
	movl	4(%ebx), %eax
	cmpb	$48, 1(%eax)
	jne	L1371
	cmpb	$48, 2(%eax)
	jne	L1371
	movl	$-1, -28(%ebp)
	movl	-24(%ebp), %edx
	testl	%edx, %edx
	je	L1369
L1371:
	movl	$0, (%esp)
	movl	12(%edx), %eax
	movl	%eax, 4(%esp)
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, (%esi)
	movl	%eax, %esi
L1369:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L1373
L1393:
	movl	$0, (%esi)
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L1374
L1391:
	cmpl	$0, -24(%ebp)
	je	L1375
	cmpl	$0, -28(%ebp)
	jns	L1376
	movl	-20(%ebp), %edx
	movl	%edx, (%esp)
	call	_free_tlist
	jmp	L1375
L1376:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %edx
	movl	$0, 4(%eax)
	movl	_istk, %eax
	movl	12(%eax), %eax
	movl	%eax, (%edx)
	movl	_istk, %eax
	movl	%edx, 12(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%edx)
	cmpl	$0, -28(%ebp)
	jne	L1375
	movl	-24(%ebp), %edx
	cmpl	$0, (%edx)
	je	L1395
L1382:
	movl	-24(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -24(%ebp)
	cmpl	$0, (%eax)
	jne	L1382
L1395:
	movl	$0, (%esp)
	movl	$8, 4(%esp)
	movl	$LC294, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	-24(%ebp), %edx
	movl	%eax, (%edx)
L1375:
	movl	_list, %edx
	movl	-32(%ebp), %eax
	cmpl	$0, 24(%eax)
	je	L1383
	movl	$2, %eax
	jmp	L1384
L1383:
	movl	$1, %eax
L1384:
	movl	%eax, (%esp)
	call	*16(%edx)
	movl	$1, %eax
L1330:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC295:
	.ascii "(%s:%d) %s\0"
	.align 2
	.def	_error;	.scl	3;	.type	32;	.endef
_error:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$1072, %esp
	movl	8(%ebp), %esi
	cmpl	$0, _istk
	je	L1397
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	je	L1397
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L1397
	cmpl	$2, 4(%eax)
	jne	L1396
L1397:
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	leal	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	___va_start
	leal	-1032(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-1036(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_vsprintf
	movl	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	___va_end
	cmpl	$0, _istk
	je	L1398
	movl	_istk, %edx
	cmpl	$0, 28(%edx)
	je	L1398
	movl	28(%edx), %eax
	cmpl	$0, 4(%eax)
	je	L1398
	movl	%esi, %eax
	orl	$64, %eax
	movl	%eax, (%esp)
	movl	$LC295, 4(%esp)
	movl	28(%edx), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	movl	28(%edx), %eax
	movl	80(%eax), %eax
	movl	%eax, 12(%esp)
	movl	%ebx, 16(%esp)
	call	*__error
	jmp	L1396
L1398:
	movl	%esi, %eax
	orl	$64, %eax
	movl	%eax, (%esp)
	movl	$LC243, 4(%esp)
	leal	-1032(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*__error
L1396:
	addl	$1072, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC296:
	.ascii "unable to open input file `%s'\0"
	.align 2
	.def	_pp_reset;	.scl	3;	.type	32;	.endef
_pp_reset:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %eax
	movl	%eax, __error
	movl	$0, _cstk
	movl	$32, (%esp)
	call	_nasm_malloc
	movl	%eax, _istk
	movl	$0, (%eax)
	movl	_istk, %eax
	movl	$0, 8(%eax)
	movl	_istk, %eax
	movl	$0, 12(%eax)
	movl	_istk, %eax
	movl	$0, 28(%eax)
	movl	_istk, %ebx
	movl	%esi, (%esp)
	movl	$LC187, 4(%esp)
	call	_fopen
	movl	%eax, 4(%ebx)
	movl	_istk, %eax
	movl	$0, 16(%eax)
	movl	%esi, (%esp)
	call	_nasm_strdup
	movl	%eax, (%esp)
	call	_src_set_fname
	movl	$0, (%esp)
	call	_src_set_linnum
	movl	_istk, %eax
	movl	$1, 24(%eax)
	movl	_istk, %eax
	cmpl	$0, 4(%eax)
	jne	L1401
	movl	$18, (%esp)
	movl	$LC296, 4(%esp)
	movl	%esi, 8(%esp)
	call	_error
L1401:
	movl	$0, _defining
	movl	$0, %eax
	movl	$_mmacros, %ecx
	movl	$_smacros, %edx
L1406:
	movl	$0, (%ecx,%eax,4)
	movl	$0, (%edx,%eax,4)
	incl	%eax
	cmpl	$30, %eax
	jle	L1406
	movl	$0, _unique
	cmpl	$0, _tasm_compatible_mode
	je	L1407
	movl	$_stdmac, _stdmacpos
	jmp	L1408
L1407:
	movl	$_stdmac+24, _stdmacpos
L1408:
	cmpl	$0, _extrastdmac
	setne	%al
	movzbl	%al, %eax
	movl	%eax, _any_extrastdmac
	movl	24(%ebp), %eax
	movl	%eax, _list
	movl	20(%ebp), %eax
	movl	%eax, _evaluate
	movl	12(%ebp), %eax
	movl	%eax, _pass
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC297:
	.ascii "defining with name in expansion\0"
	.align 32
LC298:
	.ascii "`%%rep' without `%%endrep' within expansion of macro `%s'\0"
	.align 32
LC299:
	.ascii "expected `%%endif' before end of file\0"
	.align 2
	.def	_pp_getline;	.scl	3;	.type	32;	.endef
_pp_getline:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
L1462:
	movl	_istk, %eax
	cmpl	$0, 12(%eax)
	je	L1449
	movl	12(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L1449
L1439:
	movl	_istk, %eax
	movl	12(%eax), %esi
	movl	4(%esi), %eax
	cmpl	$0, 4(%eax)
	jne	L1419
	cmpl	$1, 28(%eax)
	jle	L1419
	decl	28(%eax)
	movl	4(%esi), %eax
	movl	44(%eax), %esi
	testl	%esi, %esi
	je	L1415
L1431:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, -16(%ebp)
	movl	_istk, %eax
	movl	12(%eax), %eax
	movl	-16(%ebp), %edx
	movl	%eax, (%edx)
	movl	$0, 4(%edx)
	movl	$0, 8(%edx)
	movl	%edx, %edi
	addl	$8, %edi
	movl	8(%esi), %ebx
	testl	%ebx, %ebx
	je	L1467
L1430:
	cmpl	$0, 4(%ebx)
	jne	L1429
	cmpl	$1, 12(%ebx)
	jne	L1426
L1429:
	movl	$0, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, (%edi)
	movl	%eax, %edi
L1426:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L1430
L1467:
	movl	_istk, %eax
	movl	-16(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	(%esi), %esi
	testl	%esi, %esi
	je	L1415
	jmp	L1431
L1419:
	cmpl	$0, _defining
	je	L1433
	movl	_defining, %eax
	cmpl	$0, 4(%eax)
	je	L1434
	movl	$3, (%esp)
	movl	$LC297, 4(%esp)
	call	_error
	jmp	L1433
L1434:
	movl	_istk, %edx
	movl	28(%edx), %eax
	cmpl	$0, 4(%eax)
	je	L1433
	movl	$2, (%esp)
	movl	$LC298, 4(%esp)
	movl	28(%edx), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	call	_error
L1433:
	movl	_istk, %edx
	movl	28(%edx), %ebx
	movl	48(%ebx), %eax
	movl	%eax, 28(%edx)
	cmpl	$0, 4(%ebx)
	je	L1437
	movl	56(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	60(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	72(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	4(%esi), %eax
	movl	$0, 28(%eax)
	jmp	L1438
L1437:
	movl	%ebx, (%esp)
	call	_free_mmacro
L1438:
	movl	(%esi), %eax
	movl	_istk, %edx
	movl	%eax, 12(%edx)
	movl	%esi, (%esp)
	call	_nasm_free
	movl	$1, (%esp)
	movl	_list, %eax
	call	*20(%eax)
L1415:
	movl	_istk, %eax
	cmpl	$0, 12(%eax)
	je	L1449
	movl	12(%eax), %eax
	cmpl	$0, 4(%eax)
	jne	L1439
L1449:
	movl	_istk, %eax
	cmpl	$0, 12(%eax)
	je	L1443
	movl	12(%eax), %ecx
	cmpl	$0, 28(%eax)
	je	L1444
	movl	28(%eax), %eax
	incl	80(%eax)
L1444:
	movl	8(%ecx), %esi
	movl	(%ecx), %edx
	movl	_istk, %eax
	movl	%edx, 12(%eax)
	movl	%ecx, (%esp)
	call	_nasm_free
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	call	_detoken
	movl	%eax, %ebx
	movl	$1, (%esp)
	movl	%eax, 4(%esp)
	movl	_list, %eax
	call	*12(%eax)
	jmp	L1470
L1443:
	call	_read_line
	testl	%eax, %eax
	jne	L1468
	movl	_istk, %ebx
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_fclose
	cmpl	$0, 8(%ebx)
	je	L1446
	movl	$2, (%esp)
	movl	$LC299, 4(%esp)
	call	_error
L1446:
	cmpl	$0, (%ebx)
	je	L1447
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_src_set_linnum
	movl	16(%ebx), %eax
	movl	%eax, (%esp)
	call	_src_set_fname
	movl	%eax, (%esp)
	call	_nasm_free
L1447:
	movl	(%ebx), %eax
	movl	%eax, _istk
	movl	$3, (%esp)
	movl	_list, %eax
	call	*20(%eax)
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _istk
	jne	L1449
	movl	$0, %eax
	jmp	L1411
L1470:
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _defining
	jne	L1450
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	je	L1451
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L1451
	cmpl	$2, 4(%eax)
	jne	L1450
L1451:
	movl	%esi, (%esp)
	call	_expand_mmac_params
	movl	%eax, %esi
L1450:
	movl	%esi, (%esp)
	call	_do_directive
	cmpl	$1, %eax
	je	L1462
	cmpl	$0, _defining
	je	L1454
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_defining, %edx
	movl	44(%edx), %edx
	movl	%edx, (%eax)
	movl	%esi, 8(%eax)
	movl	$0, 4(%eax)
	movl	_defining, %edx
	movl	%eax, 44(%edx)
	jmp	L1462
L1468:
	movl	%eax, (%esp)
	call	_prepreproc
	movl	%eax, %ebx
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, %esi
	jmp	L1470
L1454:
	movl	_istk, %eax
	cmpl	$0, 8(%eax)
	je	L1456
	movl	8(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L1456
	cmpl	$2, 4(%eax)
	jne	L1469
L1456:
	movl	_istk, %eax
	cmpl	$0, 28(%eax)
	je	L1458
	movl	28(%eax), %eax
	cmpl	$0, 28(%eax)
	jne	L1458
L1469:
	movl	%esi, (%esp)
	call	_free_tlist
	jmp	L1462
L1458:
	movl	%esi, (%esp)
	call	_expand_smacro
	movl	%eax, %esi
	movl	%eax, (%esp)
	call	_expand_mmacro
	testl	%eax, %eax
	jne	L1462
	movl	%esi, (%esp)
	movl	$1, 4(%esp)
	call	_detoken
	movl	%eax, %ebx
	movl	%esi, (%esp)
	call	_free_tlist
	movl	%ebx, %eax
L1411:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC300:
	.ascii "end of file while still defining macro `%s'\0"
	.align 2
	.def	_pp_cleanup;	.scl	3;	.type	32;	.endef
_pp_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	cmpl	$0, _defining
	je	L1472
	movl	$1, (%esp)
	movl	$LC300, 4(%esp)
	movl	_defining, %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	call	_error
	movl	_defining, %eax
	movl	%eax, (%esp)
	call	_free_mmacro
L1472:
	cmpl	$0, _cstk
	je	L1500
L1476:
	call	_ctx_pop
	cmpl	$0, _cstk
	jne	L1476
L1500:
	movl	$0, %esi
L1489:
	cmpl	$0, _mmacros(,%esi,4)
	je	L1504
	movl	$_mmacros, %ebx
L1484:
	movl	(%ebx,%esi,4), %edx
	movl	(%edx), %eax
	movl	%eax, (%ebx,%esi,4)
	movl	%edx, (%esp)
	call	_free_mmacro
	cmpl	$0, (%ebx,%esi,4)
	jne	L1484
L1504:
	cmpl	$0, _smacros(,%esi,4)
	je	L1506
	movl	$_smacros, %edi
L1488:
	movl	(%edi,%esi,4), %ebx
	movl	(%ebx), %eax
	movl	%eax, (%edi,%esi,4)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_free_tlist
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, (%edi,%esi,4)
	jne	L1488
L1506:
	incl	%esi
	cmpl	$30, %esi
	jle	L1489
	cmpl	$0, _istk
	je	L1508
L1493:
	movl	_istk, %ebx
	movl	(%ebx), %eax
	movl	%eax, _istk
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	16(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _istk
	jne	L1493
L1508:
	cmpl	$0, _cstk
	je	L1510
L1497:
	call	_ctx_pop
	cmpl	$0, _cstk
	jne	L1497
L1510:
	cmpl	$0, 8(%ebp)
	jne	L1471
	movl	_predef, %eax
	movl	%eax, (%esp)
	call	_free_llist
	call	_delete_Blocks
L1471:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _pp_include_path
	.def	_pp_include_path;	.scl	2;	.type	32;	.endef
_pp_include_path:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	$8, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	movl	$0, (%ebx)
	cmpl	$0, _ipath
	je	L1512
	movl	_ipath, %eax
	cmpl	$0, (%eax)
	je	L1519
L1516:
	movl	(%eax), %eax
	cmpl	$0, (%eax)
	jne	L1516
L1519:
	movl	%ebx, (%eax)
	jmp	L1511
L1512:
	movl	%ebx, _ipath
L1511:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _pp_get_include_path_ptr
	.def	_pp_get_include_path_ptr;	.scl	2;	.type	32;	.endef
_pp_get_include_path_ptr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	jne	L1521
	cmpl	$0, _ipath
	je	L1522
	movl	_ipath, %eax
	addl	$4, %eax
	jmp	L1520
L1522:
	movl	$0, %eax
	jmp	L1520
L1521:
	movl	-4(%eax), %eax
	leal	4(%eax), %edx
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	andl	%edx, %eax
L1520:
	popl	%ebp
	ret
	.align 2
.globl _pp_pre_include
	.def	_pp_pre_include;	.scl	2;	.type	32;	.endef
_pp_pre_include:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	$0, (%esp)
	movl	$10, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, (%esp)
	movl	$4, 4(%esp)
	movl	$LC80, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, %ebx
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_predef, %edx
	movl	%edx, (%eax)
	movl	%ebx, 8(%eax)
	movl	$0, 4(%eax)
	movl	%eax, _predef
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _pp_pre_define
	.def	_pp_pre_define;	.scl	2;	.type	32;	.endef
_pp_pre_define:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$61, 4(%esp)
	call	_strchr
	movl	%eax, %ebx
	movl	$0, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, %esi
	movl	%eax, (%esp)
	movl	$4, 4(%esp)
	movl	$LC35, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, %edi
	testl	%ebx, %ebx
	je	L1528
	movb	$32, (%ebx)
L1528:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, (%esi)
	testl	%ebx, %ebx
	je	L1529
	movb	$61, (%ebx)
L1529:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_predef, %edx
	movl	%edx, (%eax)
	movl	%edi, 8(%eax)
	movl	$0, 4(%eax)
	movl	%eax, _predef
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _pp_pre_undefine
	.def	_pp_pre_undefine;	.scl	2;	.type	32;	.endef
_pp_pre_undefine:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	$0, (%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, %ebx
	movl	%eax, (%esp)
	movl	$4, 4(%esp)
	movl	$LC93, 8(%esp)
	movl	$0, 12(%esp)
	call	_new_Token
	movl	%eax, %esi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tokenise
	movl	%eax, (%ebx)
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_predef, %edx
	movl	%edx, (%eax)
	movl	%esi, 8(%eax)
	movl	$0, 4(%eax)
	movl	%eax, _predef
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
.globl _pp_extra_stdmac
	.def	_pp_extra_stdmac;	.scl	2;	.type	32;	.endef
_pp_extra_stdmac:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, _extrastdmac
	popl	%ebp
	ret
LC301:
	.ascii "%ld\0"
	.align 2
	.def	_make_tok_num;	.scl	3;	.type	32;	.endef
_make_tok_num:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	leal	-40(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC301, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	movl	%ebx, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%esi)
	movl	$6, 12(%esi)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
.globl _nasmpp
	.data
	.align 4
_nasmpp:
	.long	_pp_reset
	.long	_pp_getline
	.long	_pp_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _cstk,16
.lcomm _istk,16
.lcomm __error,16
.lcomm _evaluate,16
.lcomm _pass,16
.lcomm _unique,16
.lcomm _list,16
.lcomm _mmacros,128
.lcomm _smacros,128
.lcomm _defining,16
.lcomm _stdmacpos,16
	.comm	_any_extrastdmac, 16	 # 4
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_strchr;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	___va_end;	.scl	2;	.type	32;	.endef
	.def	_vsprintf;	.scl	2;	.type	32;	.endef
	.def	___va_start;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_nasm_quote;	.scl	2;	.type	32;	.endef
	.def	_src_get;	.scl	2;	.type	32;	.endef
	.def	_src_set_fname;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_strcat;	.scl	2;	.type	32;	.endef
	.def	_strspn;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_readstrnum;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_nasm_strcat;	.scl	2;	.type	32;	.endef
	.def	_getenv;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_isalnum;	.scl	2;	.type	32;	.endef
	.def	_isalpha;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_isdigit;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_src_get_linnum;	.scl	2;	.type	32;	.endef
	.def	_src_set_linnum;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_toupper;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
