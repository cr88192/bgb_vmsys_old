	.file	"outieee.c"
	.text
	.align 2
	.def	_ieee_init;	.scl	3;	.type	32;	.endef
_ieee_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	%edx, _ofp
	movl	%ecx, _error
	movl	16(%ebp), %eax
	movl	%eax, _deflabel
	movl	$0, _any_segs
	movl	$0, _fpubhead
	movl	$_fpubhead, _fpubtail
	movl	$0, _exthead
	movl	$_exthead, _exttail
	movl	$1, _externals
	movl	$0, _ebhead
	movl	$_ebhead, _ebtail
	movl	$0, _ieee_seg_needs_update
	movl	$0, _seghead
	movl	$_seghead, _segtail
	movl	$-1, _ieee_entry_seg
	movl	$0, _ieee_uppercase
	movl	$0, _checksum
	movl	$_of_ieee, (%esp)
	movl	$0, 4(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 12(%esp)
	movl	_of_ieee+16, %eax
	call	*8(%eax)
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_set_info;	.scl	3;	.type	32;	.endef
_ieee_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.align 2
	.def	_ieee_cleanup;	.scl	3;	.type	32;	.endef
_ieee_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ieee_write_file
	movl	_of_ieee+16, %eax
	call	*32(%eax)
	movl	_ofp, %eax
	movl	%eax, (%esp)
	call	_fclose
	cmpl	$0, _seghead
	je	L33
L19:
	movl	_seghead, %ebx
	movl	8(%ebx), %eax
	movl	%eax, _seghead
	cmpl	$0, 48(%ebx)
	je	L35
L10:
	movl	48(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, 48(%ebx)
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, 48(%ebx)
	jne	L10
L35:
	cmpl	$0, 12(%ebx)
	je	L37
L14:
	movl	12(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, 12(%ebx)
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, 12(%ebx)
	jne	L14
L37:
	cmpl	$0, (%ebx)
	je	L39
L18:
	movl	(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, (%ebx)
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, (%ebx)
	jne	L18
L39:
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _seghead
	jne	L19
L33:
	cmpl	$0, _fpubhead
	je	L41
L23:
	movl	_fpubhead, %edx
	movl	(%edx), %eax
	movl	%eax, _fpubhead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _fpubhead
	jne	L23
L41:
	cmpl	$0, _exthead
	je	L43
L27:
	movl	_exthead, %edx
	movl	(%edx), %eax
	movl	%eax, _exthead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _exthead
	jne	L27
L43:
	cmpl	$0, _ebhead
	je	L45
L31:
	movl	_ebhead, %edx
	movl	(%edx), %eax
	movl	%eax, _ebhead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _ebhead
	jne	L31
L45:
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
LC0:
	.ascii "unrecognised symbol type `%s'\0"
LC1:
	.ascii "..start\0"
	.align 2
	.def	_ieee_deflabel;	.scl	3;	.type	32;	.endef
_ieee_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	12(%ebp), %ebx
	movl	24(%ebp), %eax
	testl	%eax, %eax
	je	L47
	movl	$1, (%esp)
	movl	$LC0, 4(%esp)
	movl	%eax, 8(%esp)
	call	*_error
L47:
	cmpb	$46, (%edi)
	jne	L48
	cmpb	$46, 1(%edi)
	jne	L48
	movl	%edi, (%esp)
	movl	$LC1, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L46
	movl	%ebx, _ieee_entry_seg
	movl	16(%ebp), %eax
	movl	%eax, _ieee_entry_ofs
	jmp	L46
L48:
	cmpl	$0, _ieee_seg_needs_update
	je	L50
	movl	_ieee_seg_needs_update, %eax
	movl	%edi, 64(%eax)
	jmp	L46
L50:
	cmpl	$1073741823, %ebx
	jg	L74
	cmpl	$-1, %ebx
	je	L51
	testl	$1, %ebx
	jne	L46
L51:
	cmpl	$1073741823, %ebx
	jle	L52
L74:
	cmpl	$0, 20(%ebp)
	je	L46
	movl	_fpubtail, %esi
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esi)
	movl	%eax, _fpubtail
	movl	$0, (%eax)
	movl	%edi, 4(%eax)
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	%ebx, %edx
	andl	$-1073741825, %edx
	movl	%edx, 12(%eax)
	jmp	L46
L75:
	movl	52(%esi), %eax
	movl	%eax, -16(%ebp)
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	-16(%ebp), %edx
	movl	%eax, (%edx)
	movl	%eax, _last_defined
	movl	%eax, 52(%esi)
	movl	$0, (%eax)
	movl	%edi, 4(%eax)
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	24(%esi), %edx
	movl	%edx, 16(%eax)
	movl	$-1, 12(%eax)
	jmp	L46
L52:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L55
	cmpl	$0, 20(%ebp)
	je	L46
L60:
	cmpl	%ebx, 20(%esi)
	je	L75
	movl	8(%esi), %esi
	testl	%esi, %esi
	je	L55
	cmpl	$0, 20(%ebp)
	jne	L60
	jmp	L46
L55:
	cmpl	$0, 20(%ebp)
	je	L46
	movl	_exttail, %esi
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esi)
	movl	$0, (%eax)
	movl	%eax, _exttail
	movl	%edi, 4(%eax)
	cmpl	$2, 20(%ebp)
	setne	%dl
	movzbl	%dl, %edx
	decl	%edx
	andl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	%ebx, %eax
	shrl	$31, %eax
	leal	(%eax,%ebx), %eax
	movl	%eax, %edi
	sarl	%edi
	movl	_ebhead, %edx
	testl	%edx, %edx
	jne	L64
	movl	_ebtail, %esi
	movl	$2052, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esi)
	movl	%eax, %edx
	movl	$0, (%eax)
	movl	%eax, _ebtail
L64:
	cmpl	$512, %edi
	jle	L73
L70:
	testl	%edx, %edx
	je	L68
	cmpl	$0, (%edx)
	je	L68
	movl	(%edx), %edx
	jmp	L69
L68:
	movl	_ebtail, %esi
	movl	$2052, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esi)
	movl	%eax, %edx
	movl	$0, (%eax)
	movl	%eax, _ebtail
L69:
	subl	$512, %edi
	cmpl	$512, %edi
	jg	L70
L73:
	movl	_externals, %eax
	movl	%eax, 4(%edx,%edi,4)
	incl	_externals
L46:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC2:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
LC3:
	.ascii "__NASMDEFSEG\0"
	.align 32
LC4:
	.ascii "strange segment conditions in IEEE driver\0"
	.align 32
LC5:
	.ascii "code directed to nonexistent segment?\0"
	.align 32
LC6:
	.ascii "relative call to absolute address not supported by IEEE format\0"
	.align 2
	.def	_ieee_out;	.scl	3;	.type	32;	.endef
_ieee_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %ebx
	cmpl	$-1, %ebx
	jne	L77
	movl	16(%ebp), %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	je	L76
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*_error
	jmp	L76
L77:
	cmpl	$0, _any_segs
	jne	L79
	movl	$LC3, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_ieee_segment
	cmpl	%eax, %ebx
	je	L79
	movl	$3, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L79:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L110
L86:
	cmpl	%ebx, 20(%esi)
	je	L82
	movl	8(%esi), %esi
	testl	%esi, %esi
	jne	L86
	jmp	L110
L82:
	testl	%esi, %esi
	jne	L87
L110:
	movl	$3, (%esp)
	movl	$LC5, 4(%esp)
	call	*_error
L87:
	movl	16(%ebp), %edi
	andl	$268435455, %edi
	movl	16(%ebp), %ebx
	andl	$-268435456, %ebx
	jne	L88
	movl	12(%ebp), %ebx
	decl	%edi
	cmpl	$-1, %edi
	je	L76
L92:
	movl	%esi, (%esp)
	movzbl	(%ebx), %eax
	movl	%eax, 4(%esp)
	incl	%ebx
	call	_ieee_write_byte
	decl	%edi
	cmpl	$-1, %edi
	je	L76
	jmp	L92
L88:
	cmpl	$268435456, %ebx
	je	L95
	cmpl	$536870912, %ebx
	je	L95
	cmpl	$805306368, %ebx
	jne	L94
L95:
	cmpl	$-1, 20(%ebp)
	jne	L96
	cmpl	$268435456, %ebx
	je	L96
	movl	$1, (%esp)
	movl	$LC6, 4(%esp)
	call	*_error
L96:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	cmpl	$536870912, %ebx
	jne	L97
	leal	-2(%edi,%eax), %eax
	movl	%eax, -20(%ebp)
L97:
	cmpl	$805306368, %ebx
	jne	L98
	movl	-20(%ebp), %eax
	leal	-4(%edi,%eax), %eax
	movl	%eax, -20(%ebp)
L98:
	movl	20(%ebp), %eax
	movl	%eax, (%esp)
	movl	24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%edi, 12(%esp)
	movl	%ebx, 16(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 20(%esp)
	call	_ieee_write_fixup
	cmpl	$2, %edi
	jne	L99
	movl	%esi, (%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_word
	jmp	L76
L99:
	movl	%esi, (%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_dword
	jmp	L76
L94:
	cmpl	$1073741824, %ebx
	jne	L76
	decl	%edi
	cmpl	$-1, %edi
	je	L76
L106:
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	call	_ieee_write_byte
	decl	%edi
	cmpl	$-1, %edi
	jne	L106
L76:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_ieee_data_new;	.scl	3;	.type	32;	.endef
_ieee_data_new:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	cmpl	$0, (%esi)
	jne	L112
	movl	$1028, (%esp)
	call	_nasm_malloc
	movl	%eax, 4(%esi)
	movl	%eax, (%esi)
	jmp	L113
L112:
	movl	4(%esi), %ebx
	movl	$1028, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, 4(%esi)
L113:
	movl	4(%esi), %eax
	movl	$0, (%eax)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC7:
	.ascii "Source of WRT must be an offset\0"
	.align 32
LC8:
	.ascii "unrecognised WRT value in ieee_write_fixup\0"
	.align 32
LC9:
	.ascii "target of WRT must be a section \0"
	.align 32
LC10:
	.ascii "Segment of a rel not supported in ieee_write_fixup\0"
	.align 32
LC11:
	.ascii "unrecognised segment value in ieee_write_fixup\0"
	.align 32
LC12:
	.ascii "IEEE format can only handle 2-byte segment base references\0"
	.align 2
	.def	_ieee_write_fixup;	.scl	3;	.type	32;	.endef
_ieee_write_fixup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	20(%ebp), %edi
	movl	24(%ebp), %esi
	movl	28(%ebp), %ebx
	cmpl	$-1, %edx
	jne	L115
	cmpl	$-1, %ecx
	je	L114
L115:
	movl	$-1, -52(%ebp)
	cmpl	$-1, %edx
	je	L116
	movl	$4, -52(%ebp)
	movl	%ebx, -32(%ebp)
	cmpl	$1073741823, %edx
	jle	L117
	movl	$1073741824, %eax
	subl	%edx, %eax
	movl	%eax, -44(%ebp)
	jmp	L191
L117:
	testl	$1, %edx
	je	L119
	cmpl	$536870912, %esi
	je	L119
	cmpl	$805306368, %esi
	je	L119
	decl	%edx
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L126
L125:
	cmpl	%edx, 20(%eax)
	je	L121
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L125
	jmp	L126
L121:
	testl	%eax, %eax
	je	L126
	movl	24(%eax), %eax
	movl	%eax, -44(%ebp)
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L133
L132:
	cmpl	%ecx, 20(%eax)
	je	L128
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L132
	jmp	L133
L128:
	testl	%eax, %eax
	je	L133
	movl	24(%eax), %eax
	jmp	L203
L133:
	movl	%ecx, %eax
	shrl	$31, %eax
	leal	(%eax,%ecx), %eax
	movl	%eax, %edx
	sarl	%edx
	movl	_ebhead, %eax
	cmpl	$512, %edx
	jle	L136
L140:
	testl	%eax, %eax
	je	L141
	movl	(%eax), %eax
	subl	$512, %edx
	cmpl	$512, %edx
	jg	L140
L136:
	testl	%eax, %eax
	je	L141
	movl	$6, -52(%ebp)
	movl	$0, -32(%ebp)
	movl	4(%eax,%edx,4), %eax
L203:
	movl	%eax, -40(%ebp)
	jmp	L191
L141:
	movl	$1, (%esp)
	movl	$LC7, 4(%esp)
	jmp	L208
L126:
	movl	$3, (%esp)
	movl	$LC8, 4(%esp)
	jmp	L208
L119:
	movl	$1, (%esp)
	movl	$LC9, 4(%esp)
	jmp	L208
L116:
	cmpl	$-1, %ecx
	je	L114
	movl	$0, -52(%ebp)
	movl	$0, -44(%ebp)
	cmpl	$1073741823, %ecx
	jle	L146
	movl	$-1073741825, %eax
	subl	%ecx, %eax
	jmp	L207
L146:
	testl	$1, %ecx
	je	L148
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L155
	leal	-1(%ecx), %edx
L154:
	cmpl	%edx, 20(%eax)
	je	L150
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L154
	jmp	L155
L150:
	testl	%eax, %eax
	je	L155
	movl	24(%eax), %eax
	jmp	L207
L155:
	movl	%ecx, %eax
	shrl	$31, %eax
	leal	(%eax,%ecx), %eax
	movl	%eax, %edx
	sarl	%edx
	movl	_ebhead, %eax
	cmpl	$512, %edx
	jle	L158
L162:
	testl	%eax, %eax
	je	L186
	movl	(%eax), %eax
	subl	$512, %edx
	cmpl	$512, %edx
	jg	L162
L158:
	testl	%eax, %eax
	je	L186
	cmpl	$536870912, %esi
	je	L165
	cmpl	$805306368, %esi
	jne	L164
L165:
	movl	$3, (%esp)
	movl	$LC10, 4(%esp)
	jmp	L206
L164:
	movl	$7, -52(%ebp)
	jmp	L204
L148:
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L175
L174:
	cmpl	%ecx, 20(%eax)
	je	L170
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L174
	jmp	L175
L170:
	testl	%eax, %eax
	je	L175
	cmpl	$536870912, %esi
	je	L177
	cmpl	$805306368, %esi
	jne	L176
L177:
	movl	24(%eax), %eax
	movl	%eax, -44(%ebp)
	movl	$1, -52(%ebp)
	jmp	L205
L176:
	movl	24(%eax), %eax
	movl	%eax, -44(%ebp)
	movl	$2, -52(%ebp)
L205:
	movw	%di, -48(%ebp)
	movl	%ebx, -32(%ebp)
	jmp	L147
L175:
	movl	%ecx, %eax
	shrl	$31, %eax
	leal	(%eax,%ecx), %eax
	movl	%eax, %edx
	sarl	%edx
	movl	_ebhead, %eax
	cmpl	$512, %edx
	jle	L181
L185:
	testl	%eax, %eax
	je	L186
	movl	(%eax), %eax
	subl	$512, %edx
	cmpl	$512, %edx
	jg	L185
L181:
	testl	%eax, %eax
	je	L186
	cmpl	$536870912, %esi
	je	L188
	cmpl	$805306368, %esi
	jne	L187
L188:
	movl	$5, -52(%ebp)
	jmp	L204
L187:
	movl	$3, -52(%ebp)
L204:
	movl	$0, -32(%ebp)
	movl	4(%eax,%edx,4), %eax
L207:
	movl	%eax, -44(%ebp)
	jmp	L147
L186:
	movl	$3, (%esp)
	movl	$LC11, 4(%esp)
L206:
	call	*_error
L147:
	cmpl	$2, %edi
	je	L191
	cmpl	$0, -52(%ebp)
	jne	L191
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
L208:
	call	*_error
L191:
	movw	%di, -48(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	leal	-56(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_ieee_install_fixup
L114:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_ieee_install_fixup;	.scl	3;	.type	32;	.endef
_ieee_install_fixup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	12(%ebp), %ebx
	movl	$28, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	$28, 8(%esp)
	call	_memcpy
	movl	28(%edi), %eax
	movl	%eax, 20(%esi)
	movswl	8(%ebx),%eax
	addl	%eax, 28(%edi)
	movl	$0, (%esi)
	cmpl	$0, 12(%edi)
	je	L210
	movl	16(%edi), %eax
	movl	%esi, (%eax)
	movl	%esi, 16(%edi)
	jmp	L209
L210:
	movl	%esi, 16(%edi)
	movl	%esi, 12(%edi)
L209:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC13:
	.ascii "segment attributes specified on redeclaration of segment: ignoring\0"
LC14:
	.ascii "private\0"
LC15:
	.ascii "public\0"
LC16:
	.ascii "common\0"
LC17:
	.ascii "use16\0"
LC18:
	.ascii "use32\0"
LC19:
	.ascii "align=\0"
	.align 32
LC20:
	.ascii "segment alignment should be numeric\0"
LC21:
	.ascii "invalid alignment value %d\0"
LC22:
	.ascii "absolute=\0"
	.align 32
LC23:
	.ascii "argument to `absolute' segment attribute should be numeric\0"
	.align 2
	.def	_ieee_segment;	.scl	3;	.type	32;	.endef
_ieee_segment:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	cmpl	$0, 8(%ebp)
	jne	L213
	movl	16(%ebp), %eax
	movl	$16, (%eax)
	cmpl	$0, _any_segs
	jne	L214
	movl	$0, %eax
	jmp	L212
L214:
	movl	_seghead, %eax
	movl	20(%eax), %eax
	jmp	L212
L213:
	movl	$0, -20(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L299
L219:
	incl	8(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	je	L219
L299:
	movl	8(%ebp), %ebx
	jmp	L220
L224:
	incl	%ebx
L220:
	cmpb	$0, (%ebx)
	je	L301
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L224
	cmpb	$0, (%ebx)
	je	L301
L230:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L301
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L230
	cmpb	$0, (%ebx)
	je	L301
	jmp	L308
L238:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L239
L308:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L238
	cmpb	$0, (%ebx)
	je	L239
L244:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L239
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L244
L239:
	incl	-20(%ebp)
	cmpb	$0, (%ebx)
	jne	L308
L301:
	movl	$1, %edi
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L303
L254:
	incl	%edi
	movl	64(%esi), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L248
	cmpl	$0, -20(%ebp)
	jle	L312
	cmpl	$1, 12(%ebp)
	jne	L312
	movl	$0, (%esp)
	movl	$LC13, 4(%esp)
	call	*_error
	jmp	L312
L248:
	movl	8(%esi), %esi
	testl	%esi, %esi
	jne	L254
L303:
	movl	_segtail, %ebx
	movl	$68, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%eax, (%ebx)
	movl	$0, 8(%eax)
	leal	8(%eax), %eax
	movl	%eax, _segtail
	call	_seg_alloc
	movl	%eax, 20(%esi)
	movl	%edi, 24(%esi)
	movl	$1, _any_segs
	movl	$0, 64(%esi)
	movl	$0, 28(%esi)
	movl	$1, 32(%esi)
	movl	16(%ebp), %eax
	cmpl	$32, (%eax)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 44(%esi)
	movl	$2, 40(%esi)
	movl	$0, 48(%esi)
	leal	48(%esi), %eax
	movl	%eax, 52(%esi)
	movl	$0, (%esi)
	movl	$0, 12(%esi)
	movl	$0, 56(%esi)
	leal	56(%esi), %eax
	movl	%eax, 60(%esi)
	movl	8(%ebp), %ebx
	decl	-20(%ebp)
	cmpl	$-1, -20(%ebp)
	je	L305
L293:
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
	cmpb	$0, (%ebx)
	jne	L307
L261:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L261
L307:
	movl	%ebx, (%esp)
	movl	$LC14, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L262
	movl	$0, 40(%esi)
	jmp	L255
L262:
	movl	%ebx, (%esp)
	movl	$LC15, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L264
	movl	$2, 40(%esi)
	jmp	L255
L264:
	movl	%ebx, (%esp)
	movl	$LC16, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L266
	movl	$6, 40(%esi)
	jmp	L255
L266:
	movl	%ebx, (%esp)
	movl	$LC17, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L268
	movl	$0, 44(%esi)
	jmp	L255
L268:
	movl	%ebx, (%esp)
	movl	$LC18, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L270
	movl	$1, 44(%esi)
	jmp	L255
L270:
	movl	%ebx, (%esp)
	movl	$LC19, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L272
	leal	6(%ebx), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 32(%esi)
	testl	%eax, %eax
	jne	L273
	movl	$1, 32(%esi)
L273:
	cmpl	$0, -16(%ebp)
	je	L274
	movl	$1, 32(%esi)
	movl	$1, (%esp)
	movl	$LC20, 4(%esp)
	call	*_error
L274:
	movl	32(%esi), %eax
	cmpl	$16, %eax
	je	L255
	cmpl	$16, %eax
	jg	L287
	cmpl	$4, %eax
	je	L255
	cmpl	$4, %eax
	jg	L288
	decl	%eax
	cmpl	$1, %eax
	ja	L285
	jmp	L255
L288:
	cmpl	$8, %eax
	jmp	L309
L287:
	cmpl	$64, %eax
	je	L255
	cmpl	$64, %eax
	jg	L289
	cmpl	$32, %eax
	jmp	L309
L289:
	cmpl	$128, %eax
	je	L255
	cmpl	$256, %eax
L309:
	je	L255
L285:
	movl	$1, (%esp)
	movl	$LC21, 4(%esp)
	movl	32(%esi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$1, 32(%esi)
	jmp	L255
L272:
	movl	%ebx, (%esp)
	movl	$LC22, 4(%esp)
	movl	$9, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L255
	leal	9(%ebx), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	addl	$1073741824, %eax
	movl	%eax, 32(%esi)
	cmpl	$0, -16(%ebp)
	je	L255
	movl	$1, (%esp)
	movl	$LC23, 4(%esp)
	call	*_error
L255:
	decl	-20(%ebp)
	cmpl	$-1, -20(%ebp)
	jne	L293
L305:
	movl	%esi, _ieee_seg_needs_update
	cmpl	$1073741823, 32(%esi)
	jle	L294
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, 4(%esp)
	movl	32(%esi), %eax
	subl	$1073741824, %eax
	movl	%eax, 8(%esp)
	jmp	L310
L294:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	20(%esi), %eax
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
L310:
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_ieee, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*_deflabel
	movl	$0, _ieee_seg_needs_update
L312:
	cmpl	$0, 44(%esi)
	je	L296
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	jmp	L297
L296:
	movl	16(%ebp), %eax
	movl	$16, (%eax)
L297:
	movl	20(%esi), %eax
L212:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC24:
	.ascii "uppercase\0"
	.align 2
	.def	_ieee_directive;	.scl	3;	.type	32;	.endef
_ieee_directive:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC24, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L314
	movl	$1, _ieee_uppercase
	movl	$1, %eax
	jmp	L313
L314:
	movl	$0, %eax
L313:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_segbase;	.scl	3;	.type	32;	.endef
_ieee_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L323
	leal	-1(%ecx), %edx
L321:
	cmpl	%edx, 20(%eax)
	je	L317
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L321
	jmp	L323
L317:
	testl	%eax, %eax
	je	L323
	cmpl	$1073741823, 32(%eax)
	jle	L323
	movl	32(%eax), %eax
	jmp	L315
L323:
	movl	%ecx, %eax
L315:
	popl	%ebp
	ret
LC25:
	.ascii ".o\0"
	.align 2
	.def	_ieee_filename;	.scl	3;	.type	32;	.endef
_ieee_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	$_ieee_infile, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC25, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.data
_boast.0:
	.ascii "The Netwide Assembler 0.98.38\0"
	.text
LC26:
	.ascii "MBFNASM,%02X%s.\15\12\0"
LC27:
	.ascii "CO0,%02X%s.\15\12\0"
LC28:
	.ascii "AD8,4,L.\15\12\0"
LC29:
	.ascii "DT%04d%02d%02d%02d%02d%02d.\15\12\0"
LC30:
	.ascii "C0105,%02X%s.\15\12\0"
LC31:
	.ascii "CO101,07ENDHEAD.\15\12\0"
LC32:
	.ascii "??LINE\0"
LC33:
	.ascii "ST%X,A,%02X%s.\15\12\0"
LC34:
	.ascii "ASL%X,%lX.\15\12\0"
LC35:
	.ascii "ST%X,%c,%02X%s.\15\12\0"
LC36:
	.ascii "SA%X,%lX.\15\12\0"
LC37:
	.ascii "ASS%X,%X.\15\12\0"
	.align 32
LC38:
	.ascii "Start address records are incorrect\0"
LC39:
	.ascii "ASG,R%X,%lX,+.\15\12\0"
LC40:
	.ascii "NI%X,%02X%s.\15\12\0"
LC41:
	.ascii "ASI%X,R%X,%lX,+.\15\12\0"
LC42:
	.ascii "ASI%X,%lX,%lX,+.\15\12\0"
LC43:
	.ascii "ATI%X,T%X.\15\12\0"
LC44:
	.ascii "ATI%X,%X.\15\12\0"
LC45:
	.ascii "NX%X,%02X%s.\15\12\0"
LC46:
	.ascii "CO100,06ENDSYM.\15\12\0"
LC47:
	.ascii "TY%X,20,%X,%lX.\15\12\0"
LC48:
	.ascii "NN%X,%02X%s.\15\12\0"
LC49:
	.ascii "ASN%X,R%X,%lX,+.\15\12\0"
LC50:
	.ascii "ASN%X,%lX,%lX,+.\15\12\0"
LC51:
	.ascii "ATN%X,T%X.\15\12\0"
LC52:
	.ascii "ATN%X,%X.\15\12\0"
LC53:
	.ascii "SB%X.\15\12\0"
LC54:
	.ascii "ME.\15\12\0"
	.align 2
	.def	_ieee_write_file;	.scl	3;	.type	32;	.endef
_ieee_write_file:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$1340, %esp
	movl	$_ieee_infile, (%esp)
	call	_strlen
	movl	$LC26, (%esp)
	movl	%eax, 4(%esp)
	movl	$_ieee_infile, 8(%esp)
	call	_ieee_putascii
	movl	$_boast.0, (%esp)
	call	_strlen
	movl	$LC27, (%esp)
	movl	%eax, 4(%esp)
	movl	$_boast.0, 8(%esp)
	call	_ieee_putascii
	movl	$LC28, (%esp)
	call	_ieee_putascii
	leal	-1308(%ebp), %eax
	movl	%eax, (%esp)
	call	_time
	leal	-1308(%ebp), %eax
	movl	%eax, (%esp)
	call	_localtime
	movl	$LC29, (%esp)
	movl	20(%eax), %edx
	addl	$1900, %edx
	movl	%edx, 4(%esp)
	movl	16(%eax), %edx
	incl	%edx
	movl	%edx, 8(%esp)
	movl	12(%eax), %edx
	movl	%edx, 12(%esp)
	movl	8(%eax), %edx
	movl	%edx, 16(%esp)
	movl	4(%eax), %edx
	movl	%edx, 20(%esp)
	movl	(%eax), %eax
	movl	%eax, 24(%esp)
	call	_ieee_putascii
	movl	_fnhead, %ebx
	testl	%ebx, %ebx
	je	L329
	cmpl	$0, 8(%ebp)
	je	L329
L333:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	$LC30, (%esp)
	movl	%eax, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_ieee_putascii
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L329
	cmpl	$0, 8(%ebp)
	jne	L333
L329:
	movl	$LC31, (%esp)
	call	_ieee_putascii
	movl	$0, (%esp)
	call	_ieee_putcs
	movl	_seghead, %eax
	movl	%eax, -1312(%ebp)
	cmpl	$0, 8(%ebp)
	jne	L334
	movl	64(%eax), %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L334
	movl	-1312(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, -1312(%ebp)
L334:
	cmpl	$0, -1312(%ebp)
	je	L431
	leal	-280(%ebp), %esi
L347:
	movl	-1312(%ebp), %ecx
	movl	40(%ecx), %eax
	cmpl	$2, %eax
	je	L340
	cmpl	$2, %eax
	ja	L344
	movb	$83, -1313(%ebp)
	testl	%eax, %eax
	jmp	L451
L344:
	movb	$77, -1313(%ebp)
	cmpl	$6, %eax
L451:
	je	L338
L340:
	movb	$67, -1313(%ebp)
L338:
	leal	-280(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	-1312(%ebp), %edx
	movl	64(%edx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_unqualified_name
	movl	-1312(%ebp), %ecx
	cmpl	$1073741823, 32(%ecx)
	jle	L345
	movl	%ebx, (%esp)
	call	_strlen
	movl	$LC33, (%esp)
	movl	-1312(%ebp), %ecx
	movl	24(%ecx), %edx
	movl	%edx, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%ebx, 12(%esp)
	call	_ieee_putascii
	movl	$LC34, (%esp)
	movl	-1312(%ebp), %edx
	movl	24(%edx), %eax
	movl	%eax, 4(%esp)
	movl	32(%edx), %eax
	subl	$1073741824, %eax
	sall	$4, %eax
	jmp	L452
L345:
	movl	%esi, (%esp)
	call	_strlen
	movl	$LC35, (%esp)
	movl	-1312(%ebp), %ecx
	movl	24(%ecx), %edx
	movl	%edx, 4(%esp)
	movsbl	-1313(%ebp),%edx
	movl	%edx, 8(%esp)
	movl	%eax, 12(%esp)
	movl	%esi, 16(%esp)
	call	_ieee_putascii
	movl	$LC36, (%esp)
	movl	-1312(%ebp), %edx
	movl	24(%edx), %eax
	movl	%eax, 4(%esp)
	movl	32(%edx), %eax
	movl	%eax, 8(%esp)
	call	_ieee_putascii
	movl	$LC37, (%esp)
	movl	-1312(%ebp), %ecx
	movl	24(%ecx), %eax
	movl	%eax, 4(%esp)
	movl	28(%ecx), %eax
L452:
	movl	%eax, 8(%esp)
	call	_ieee_putascii
	movl	-1312(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -1312(%ebp)
	testl	%eax, %eax
	jne	L347
L431:
	cmpl	$0, _ieee_entry_seg
	je	L348
	movl	_seghead, %edx
	movl	%edx, -1312(%ebp)
	testl	%edx, %edx
	je	L450
L354:
	movl	-1312(%ebp), %ecx
	movl	20(%ecx), %eax
	cmpl	_ieee_entry_seg, %eax
	je	L350
	movl	8(%ecx), %eax
	movl	%eax, -1312(%ebp)
	testl	%eax, %eax
	jne	L354
	jmp	L450
L350:
	cmpl	$0, -1312(%ebp)
	jne	L355
L450:
	movl	$3, (%esp)
	movl	$LC38, 4(%esp)
	call	*_error
	jmp	L348
L355:
	movl	$LC39, (%esp)
	movl	-1312(%ebp), %edx
	movl	24(%edx), %eax
	movl	%eax, 4(%esp)
	movl	_ieee_entry_ofs, %eax
	movl	%eax, 8(%esp)
	call	_ieee_putascii
L348:
	movl	$0, (%esp)
	call	_ieee_putcs
	movl	$1, %esi
	movl	_seghead, %ecx
	movl	%ecx, -1312(%ebp)
	testl	%ecx, %ecx
	je	L434
L371:
	movl	-1312(%ebp), %eax
	movl	48(%eax), %ebx
	testl	%ebx, %ebx
	je	L436
	leal	-536(%ebp), %edi
L370:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_unqualified_name
	movl	%edi, (%esp)
	call	_strlen
	movl	$LC40, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_ieee_putascii
	cmpl	$-1, 12(%ebx)
	jne	L365
	movl	$LC41, (%esp)
	movl	%esi, 4(%esp)
	movl	16(%ebx), %eax
	jmp	L453
L365:
	movl	$LC42, (%esp)
	movl	%esi, 4(%esp)
	movl	12(%ebx), %eax
	sall	$4, %eax
L453:
	movl	%eax, 8(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_ieee_putascii
	cmpl	$0, 8(%ebp)
	je	L367
	cmpl	$255, 20(%ebx)
	jle	L368
	movl	$LC43, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
	subl	$256, %eax
	jmp	L454
L368:
	movl	$LC44, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
L454:
	movl	%eax, 8(%esp)
	call	_ieee_putascii
L367:
	incl	%esi
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L370
L436:
	movl	-1312(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, -1312(%ebp)
	testl	%edx, %edx
	jne	L371
L434:
	movl	_fpubhead, %ebx
	movl	$1, %esi
	testl	%ebx, %ebx
	je	L438
	leal	-792(%ebp), %edi
L380:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_unqualified_name
	movl	%edi, (%esp)
	call	_strlen
	movl	$LC40, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_ieee_putascii
	cmpl	$-1, 12(%ebx)
	jne	L375
	movl	$LC41, (%esp)
	movl	%esi, 4(%esp)
	movl	16(%ebx), %eax
	jmp	L455
L375:
	movl	$LC42, (%esp)
	movl	%esi, 4(%esp)
	movl	12(%ebx), %eax
	sall	$4, %eax
L455:
	movl	%eax, 8(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_ieee_putascii
	cmpl	$0, 8(%ebp)
	je	L377
	cmpl	$255, 20(%ebx)
	jle	L378
	movl	$LC43, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
	subl	$256, %eax
	jmp	L456
L378:
	movl	$LC44, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
L456:
	movl	%eax, 8(%esp)
	call	_ieee_putascii
L377:
	incl	%esi
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L380
L438:
	movl	_exthead, %ebx
	movl	$1, %esi
	testl	%ebx, %ebx
	je	L440
	leal	-1048(%ebp), %edi
L384:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_unqualified_name
	movl	%edi, (%esp)
	call	_strlen
	movl	$LC45, (%esp)
	movl	%esi, 4(%esp)
	incl	%esi
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_ieee_putascii
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L384
L440:
	movl	$0, (%esp)
	call	_ieee_putcs
	movl	$LC46, (%esp)
	call	_ieee_putascii
	movl	$1, %esi
	movl	_arrhead, %ebx
	testl	%ebx, %ebx
	je	L386
	cmpl	$0, 8(%ebp)
	je	L386
L390:
	movl	$LC47, (%esp)
	movl	%esi, 4(%esp)
	incl	%esi
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_ieee_putascii
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	L386
	cmpl	$0, 8(%ebp)
	jne	L390
L386:
	movl	$1, %esi
	movl	_seghead, %ecx
	movl	%ecx, -1312(%ebp)
	testl	%ecx, %ecx
	je	L392
	cmpl	$0, 8(%ebp)
	je	L392
L406:
	movl	-1312(%ebp), %eax
	movl	56(%eax), %ebx
	testl	%ebx, %ebx
	je	L444
	leal	-1304(%ebp), %edi
L405:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_unqualified_name
	movl	%edi, (%esp)
	call	_strlen
	movl	$LC48, (%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_ieee_putascii
	cmpl	$-1, 12(%ebx)
	jne	L400
	movl	$LC49, (%esp)
	movl	%esi, 4(%esp)
	movl	16(%ebx), %eax
	jmp	L457
L400:
	movl	$LC50, (%esp)
	movl	%esi, 4(%esp)
	movl	12(%ebx), %eax
	sall	$4, %eax
L457:
	movl	%eax, 8(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_ieee_putascii
	cmpl	$0, 8(%ebp)
	je	L402
	cmpl	$255, 20(%ebx)
	jle	L403
	movl	$LC51, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
	subl	$256, %eax
	jmp	L458
L403:
	movl	$LC52, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebx), %eax
L458:
	movl	%eax, 8(%esp)
	call	_ieee_putascii
L402:
	incl	%esi
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L405
L444:
	movl	-1312(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, -1312(%ebp)
	testl	%edx, %edx
	je	L392
	cmpl	$0, 8(%ebp)
	jne	L406
L392:
	movl	_seghead, %ecx
	movl	%ecx, -1312(%ebp)
	cmpl	$0, 8(%ebp)
	jne	L407
	movl	64(%ecx), %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L407
	movl	-1312(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -1312(%ebp)
L407:
	cmpl	$0, -1312(%ebp)
	je	L446
L428:
	movl	-1312(%ebp), %edx
	cmpl	$0, 28(%edx)
	je	L411
	movl	$0, %ebx
	movl	(%edx), %edi
	movl	$LC53, (%esp)
	movl	24(%edx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_putascii
	movl	-1312(%ebp), %ecx
	movl	12(%ecx), %esi
	testl	%esi, %esi
	je	L448
L421:
	movl	%ebx, %eax
	testl	%ebx, %ebx
	jns	L415
	leal	1023(%ebx), %eax
L415:
	andl	$-1024, %eax
	movl	%ebx, %edx
	subl	%eax, %edx
	movl	$1024, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	leal	(%ebx,%eax), %eax
	movl	-1312(%ebp), %ecx
	cmpl	28(%ecx), %eax
	jle	L416
	movl	28(%ecx), %eax
	subl	%ebx, %eax
	jmp	L417
L416:
	movl	%edx, %eax
L417:
	movl	%eax, %edx
	movl	20(%esi), %eax
	subl	%ebx, %eax
	cmpl	%edx, %eax
	jle	L418
	movl	%edx, %eax
L418:
	movl	%ebx, (%esp)
	leal	(%eax,%ebx), %eax
	movl	%eax, 4(%esp)
	leal	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_ieee_putld
	movl	%eax, %ebx
	testl	$1023, %eax
	jne	L419
	movl	(%edi), %edi
L419:
	cmpl	20(%esi), %ebx
	jne	L412
	movl	%esi, (%esp)
	call	_ieee_putlr
	addl	%eax, %ebx
	movl	(%esi), %esi
L412:
	testl	%esi, %esi
	jne	L421
L448:
	movl	-1312(%ebp), %eax
	cmpl	28(%eax), %ebx
	jge	L423
	testl	%edi, %edi
	je	L423
L427:
	movl	-1312(%ebp), %edx
	movl	28(%edx), %eax
	movl	%eax, %edx
	subl	%ebx, %edx
	cmpl	$1024, %edx
	jle	L426
	movl	$1024, %edx
L426:
	movl	%ebx, (%esp)
	leal	(%edx,%ebx), %eax
	movl	%eax, 4(%esp)
	leal	4(%edi), %eax
	movl	%eax, 8(%esp)
	call	_ieee_putld
	movl	%eax, %ebx
	movl	(%edi), %edi
	movl	-1312(%ebp), %ecx
	cmpl	28(%ecx), %eax
	jge	L423
	testl	%edi, %edi
	jne	L427
L423:
	movl	$0, (%esp)
	call	_ieee_putcs
L411:
	movl	-1312(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -1312(%ebp)
	testl	%eax, %eax
	jne	L428
L446:
	movl	$LC54, (%esp)
	call	_ieee_putascii
	addl	$1340, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_ieee_write_byte;	.scl	3;	.type	32;	.endef
_ieee_write_byte:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	28(%esi), %edx
	movl	%edx, %ecx
	leal	1(%edx), %eax
	movl	%eax, 28(%esi)
	testl	%edx, %edx
	jns	L461
	leal	1023(%edx), %ecx
L461:
	movl	%ecx, %eax
	andl	$-1024, %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	jne	L460
	movl	%esi, (%esp)
	call	_ieee_data_new
L460:
	movl	4(%esi), %edx
	movl	12(%ebp), %eax
	movb	%al, 4(%ebx,%edx)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_write_word;	.scl	3;	.type	32;	.endef
_ieee_write_word:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	%esi, (%esp)
	movzbl	%bl,%eax
	movl	%eax, 4(%esp)
	call	_ieee_write_byte
	movl	%esi, (%esp)
	movzbl	%bh, %ebx
	movl	%ebx, 4(%esp)
	call	_ieee_write_byte
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_write_dword;	.scl	3;	.type	32;	.endef
_ieee_write_dword:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	%esi, (%esp)
	movzbl	%bl,%eax
	movl	%eax, 4(%esp)
	call	_ieee_write_byte
	movl	%esi, (%esp)
	movzbl	%bh, %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_byte
	movl	%esi, (%esp)
	movl	%ebx, %eax
	sarl	$16, %eax
	andl	$255, %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_byte
	movl	%esi, (%esp)
	shrl	$24, %ebx
	movl	%ebx, 4(%esp)
	call	_ieee_write_byte
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_putascii;	.scl	3;	.type	32;	.endef
_ieee_putascii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$288, %esp
	leal	-268(%ebp), %eax
	movl	%eax, (%esp)
	leal	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	___va_start
	leal	-264(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-268(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_vsprintf
	movl	%ebx, (%esp)
	call	_strlen
	movl	%eax, %esi
	movl	$0, %ecx
	cmpl	%eax, %ecx
	jge	L472
	movl	_checksum, %ebx
L470:
	movsbl	-264(%ecx,%ebp),%edx
	movzbl	%dl,%eax
	cmpl	$31, %eax
	jle	L467
	leal	(%ebx,%edx), %ebx
L467:
	incl	%ecx
	cmpl	%esi, %ecx
	jl	L470
	movl	%ebx, _checksum
L472:
	movl	-268(%ebp), %eax
	movl	%eax, (%esp)
	call	___va_end
	movl	_ofp, %eax
	movl	%eax, (%esp)
	leal	-264(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_fprintf
	addl	$288, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
LC55:
	.ascii "CS.\15\12\0"
LC56:
	.ascii "CS%02X.\15\12\0"
	.align 2
	.def	_ieee_putcs;	.scl	3;	.type	32;	.endef
_ieee_putcs:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	je	L475
	movl	$LC55, (%esp)
	call	_ieee_putascii
	jmp	L476
L475:
	movl	_checksum, %eax
	addl	$150, %eax
	movl	%eax, _checksum
	movl	$LC56, (%esp)
	andl	$127, %eax
	movl	%eax, 4(%esp)
	call	_ieee_putascii
L476:
	movl	$0, _checksum
	movl	%ebp, %esp
	popl	%ebp
	ret
LC57:
	.ascii "LD\0"
LC58:
	.ascii "%02X\0"
LC59:
	.ascii ".\15\12\0"
	.align 2
	.def	_ieee_putld;	.scl	3;	.type	32;	.endef
_ieee_putld:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %esi
	movl	%esi, %eax
	cmpl	12(%ebp), %esi
	je	L477
	movl	%esi, %eax
	testl	%esi, %esi
	jns	L479
	leal	1023(%esi), %eax
L479:
	andl	$-1024, %eax
	movl	%esi, %edi
	subl	%eax, %edi
	movl	12(%ebp), %eax
	subl	%esi, %eax
	cmpl	$31, %eax
	jle	L495
L488:
	movl	$LC57, (%esp)
	call	_ieee_putascii
	movl	$0, %ebx
L487:
	movl	$LC58, (%esp)
	movl	16(%ebp), %edx
	movzbl	(%edi,%edx), %eax
	movl	%eax, 4(%esp)
	incl	%edi
	call	_ieee_putascii
	incl	%esi
	incl	%ebx
	cmpl	$31, %ebx
	jle	L487
	movl	$LC59, (%esp)
	call	_ieee_putascii
	movl	12(%ebp), %eax
	subl	%esi, %eax
	cmpl	$31, %eax
	jg	L488
L495:
	movl	%esi, %eax
	cmpl	12(%ebp), %esi
	je	L477
	movl	$LC57, (%esp)
	call	_ieee_putascii
	cmpl	12(%ebp), %esi
	jge	L499
L493:
	movl	$LC58, (%esp)
	movl	16(%ebp), %edx
	movzbl	(%edi,%edx), %eax
	movl	%eax, 4(%esp)
	incl	%edi
	call	_ieee_putascii
	incl	%esi
	cmpl	12(%ebp), %esi
	jl	L493
L499:
	movl	$LC59, (%esp)
	call	_ieee_putascii
	movl	%esi, %eax
L477:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC60:
	.ascii "%lX\0"
LC61:
	.ascii "L%lX,10,/\0"
LC62:
	.ascii "R%lX,%lX,+\0"
LC63:
	.ascii "R%lX,%lX,+,P,-,%X,-\0"
LC64:
	.ascii "R%lX,%lX,+,L%lX,+,%lX,-\0"
LC65:
	.ascii "R%lX,%lX,+,L%lX,+,L%lX,-\0"
LC66:
	.ascii "X%lX\0"
LC67:
	.ascii "X%lX,P,-,%lX,-\0"
LC68:
	.ascii "Y%lX,10,/\0"
LC69:
	.ascii "X%lX,Y%lX,+,%lX,-\0"
LC70:
	.ascii "X%lX,Y%lX,+,L%lX,-\0"
LC71:
	.ascii "LR(%s,%lX).\15\12\0"
	.align 2
	.def	_ieee_putlr;	.scl	3;	.type	32;	.endef
_ieee_putlr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$88, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ecx
	movswl	8(%ecx),%ebx
	cmpl	$7, 4(%ecx)
	ja	L501
	movl	4(%ecx), %eax
	jmp	*L516(,%eax,4)
	.align 4
	.align 4
L516:
	.long	L502
	.long	L506
	.long	L505
	.long	L510
	.long	L507
	.long	L511
	.long	L513
	.long	L512
L502:
	cmpl	$0, 12(%ecx)
	jns	L503
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC60, 4(%esp)
	movl	12(%ecx), %eax
	negl	%eax
	jmp	L522
L503:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC61, 4(%esp)
	jmp	L519
L505:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC62, 4(%esp)
	movl	12(%ecx), %eax
	movl	%eax, 8(%esp)
	movl	24(%ecx), %eax
	movl	%eax, 12(%esp)
	jmp	L521
L506:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC63, 4(%esp)
	movl	12(%ecx), %eax
	movl	%eax, 8(%esp)
	movl	24(%ecx), %eax
	movl	%eax, 12(%esp)
	movswl	8(%ecx),%eax
	jmp	L518
L507:
	cmpl	$0, 16(%ecx)
	jns	L508
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC64, 4(%esp)
	movl	16(%ecx), %edx
	movl	%edx, 8(%esp)
	movl	24(%ecx), %eax
	movl	%eax, 12(%esp)
	movl	%edx, 16(%esp)
	movl	12(%ecx), %eax
	negl	%eax
	sall	$4, %eax
	jmp	L520
L508:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC65, 4(%esp)
	movl	16(%ecx), %edx
	movl	%edx, 8(%esp)
	movl	24(%ecx), %eax
	movl	%eax, 12(%esp)
	movl	%edx, 16(%esp)
	movl	12(%ecx), %eax
L520:
	movl	%eax, 20(%esp)
	call	_sprintf
	jmp	L501
L510:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC66, 4(%esp)
	jmp	L519
L511:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC67, 4(%esp)
	movl	12(%ecx), %eax
	movl	%eax, 8(%esp)
	movl	%ebx, 12(%esp)
L521:
	call	_sprintf
	jmp	L501
L512:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC68, 4(%esp)
L519:
	movl	12(%ecx), %eax
L522:
	movl	%eax, 8(%esp)
	call	_sprintf
	jmp	L501
L513:
	cmpl	$0, 16(%ecx)
	jns	L514
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC69, 4(%esp)
	movl	16(%ecx), %eax
	movl	%eax, 8(%esp)
	movl	%eax, 12(%esp)
	movl	12(%ecx), %eax
	negl	%eax
	sall	$4, %eax
	jmp	L518
L514:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC70, 4(%esp)
	movl	16(%ecx), %eax
	movl	%eax, 8(%esp)
	movl	%eax, 12(%esp)
	movl	12(%ecx), %eax
L518:
	movl	%eax, 16(%esp)
	call	_sprintf
L501:
	movl	$LC71, (%esp)
	leal	-56(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_ieee_putascii
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ieee_unqualified_name;	.scl	3;	.type	32;	.endef
_ieee_unqualified_name:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	cmpl	$0, _ieee_uppercase
	je	L524
	cmpb	$0, (%esi)
	je	L531
L528:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	incl	%esi
	movl	%edi, %ebx
	incl	%edi
	call	_toupper
	movb	%al, (%ebx)
	cmpb	$0, (%esi)
	jne	L528
L531:
	movb	$0, (%edi)
	jmp	L523
L524:
	movl	%edi, (%esp)
	movl	%esi, 4(%esp)
	call	_strcpy
L523:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _dbgls_init
	.def	_dbgls_init;	.scl	2;	.type	32;	.endef
_dbgls_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$0, _fnhead
	movl	$_fnhead, _fntail
	movl	$1, _arrindex
	movl	$0, _arrhead
	movl	$_arrhead, _arrtail
	movl	$LC32, (%esp)
	movl	$2, 4(%esp)
	leal	-4(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_ieee_segment
	movl	$0, _any_segs
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_dbgls_cleanup;	.scl	3;	.type	32;	.endef
_dbgls_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	cmpl	$0, _fnhead
	je	L552
L537:
	movl	_fnhead, %ebx
	movl	(%ebx), %eax
	movl	%eax, _fnhead
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _fnhead
	jne	L537
L552:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L554
L546:
	cmpl	$0, 56(%esi)
	je	L556
L545:
	movl	56(%esi), %ebx
	movl	(%ebx), %eax
	movl	%eax, 56(%esi)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, 56(%esi)
	jne	L545
L556:
	movl	8(%esi), %esi
	testl	%esi, %esi
	jne	L546
L554:
	cmpl	$0, _arrhead
	je	L558
L550:
	movl	_arrhead, %edx
	movl	(%edx), %eax
	movl	%eax, _arrhead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _arrhead
	jne	L550
L558:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC72:
	.ascii "strange segment conditions in OBJ driver\0"
	.align 32
LC73:
	.ascii "lineno directed to nonexistent segment?\0"
	.align 2
	.def	_dbgls_linnum;	.scl	3;	.type	32;	.endef
_dbgls_linnum:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$0, %edi
	cmpl	$-1, 16(%ebp)
	je	L559
	cmpl	$0, _any_segs
	jne	L561
	movl	$LC3, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_ieee_segment
	cmpl	%eax, 16(%ebp)
	je	L561
	movl	$3, (%esp)
	movl	$LC72, 4(%esp)
	call	*_error
L561:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L579
L568:
	movl	16(%ebp), %eax
	cmpl	%eax, 20(%esi)
	je	L564
	movl	8(%esi), %esi
	testl	%esi, %esi
	jne	L568
	jmp	L579
L564:
	testl	%esi, %esi
	jne	L569
L579:
	movl	$3, (%esp)
	movl	$LC73, 4(%esp)
	call	*_error
L569:
	movl	_fnhead, %ebx
	testl	%ebx, %ebx
	je	L580
L575:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L571
	incl	%edi
	movl	_fnhead, %eax
	movl	(%eax), %ebx
	testl	%ebx, %ebx
	jne	L575
	jmp	L580
L571:
	testl	%ebx, %ebx
	jne	L576
L580:
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	incl	%eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 4(%ebx)
	movl	%edi, 8(%ebx)
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	$0, (%ebx)
	movl	_fntail, %eax
	movl	%ebx, (%eax)
	movl	%ebx, _fntail
L576:
	movl	_seghead, %eax
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_byte
	movl	_seghead, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_ieee_write_word
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, 4(%esp)
	movl	_seghead, %eax
	movl	%eax, 8(%esp)
	movl	$4, 12(%esp)
	movl	$268435456, 16(%esp)
	movl	28(%esi), %eax
	movl	%eax, 20(%esp)
	call	_ieee_write_fixup
L559:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_dbgls_deflabel;	.scl	3;	.type	32;	.endef
_dbgls_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	12(%ebp), %edi
	movl	20(%ebp), %ebx
	cmpl	$3, %ebx
	je	L581
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L583
	cmpb	$46, 1(%eax)
	jne	L583
	cmpb	$64, 2(%eax)
	jne	L581
L583:
	cmpl	$0, _ieee_seg_needs_update
	jne	L581
	cmpl	$1073741823, %edi
	jg	L581
	cmpl	$-1, %edi
	je	L585
	testl	$1, %edi
	jne	L581
L585:
	cmpl	$1073741823, %edi
	jg	L581
	cmpl	$-1, %edi
	je	L581
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L581
L594:
	cmpl	%edi, 20(%esi)
	jne	L590
	testl	%ebx, %ebx
	jne	L590
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, -16(%ebp)
	movl	%eax, _last_defined
	movl	60(%esi), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%eax)
	movl	%edx, 60(%esi)
	movl	$0, (%edx)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	-16(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	16(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	$-1, 12(%edx)
	movl	24(%esi), %eax
	movl	%eax, 16(%edx)
L590:
	movl	8(%esi), %esi
	testl	%esi, %esi
	jne	L594
L581:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_dbgls_typevalue;	.scl	3;	.type	32;	.endef
_dbgls_typevalue:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, %ebx
	shrl	$8, %ebx
	andl	$248, %eax
	cmpl	$0, _last_defined
	je	L596
	subl	$16, %eax
	cmpl	$40, %eax
	ja	L605
	jmp	*L606(,%eax,4)
	.align 4
	.align 4
L606:
	.long	L599
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L600
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L601
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L602
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L603
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L605
	.long	L604
L599:
	movl	_last_defined, %eax
	movl	$1, 20(%eax)
	jmp	L598
L600:
	movl	_last_defined, %eax
	movl	$3, 20(%eax)
	jmp	L598
L601:
	movl	_last_defined, %eax
	movl	$5, 20(%eax)
	jmp	L598
L602:
	movl	_last_defined, %eax
	movl	$9, 20(%eax)
	jmp	L598
L603:
	movl	_last_defined, %eax
	movl	$10, 20(%eax)
	jmp	L598
L604:
	movl	_last_defined, %eax
	movl	$11, 20(%eax)
	jmp	L598
L605:
	movl	_last_defined, %eax
	movl	$16, 20(%eax)
L598:
	cmpl	$1, %ebx
	jle	L607
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_last_defined, %edx
	movl	20(%edx), %edx
	movl	%ebx, 4(%eax)
	movl	%edx, 8(%eax)
	movl	$0, (%eax)
	movl	_arrindex, %ecx
	addl	$256, %ecx
	movl	_last_defined, %edx
	movl	%ecx, 20(%edx)
	incl	_arrindex
	movl	_arrtail, %edx
	movl	%eax, (%edx)
	movl	%eax, _arrtail
L607:
	movl	$0, _last_defined
L596:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_dbgls_output;	.scl	3;	.type	32;	.endef
_dbgls_output:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
LC74:
	.ascii "LADsoft Debug Records\0"
LC75:
	.ascii "ladsoft\0"
	.data
	.align 32
_ladsoft_debug_form:
	.long	LC74
	.long	LC75
	.long	_dbgls_init
	.long	_dbgls_linnum
	.long	_dbgls_deflabel
	.long	_null_debug_routine
	.long	_dbgls_typevalue
	.long	_dbgls_output
	.long	_dbgls_cleanup
	.align 4
_ladsoft_debug_arr:
	.long	_ladsoft_debug_form
	.long	_null_debug_form
	.long	0
.globl _of_ieee
	.text
	.align 32
LC76:
	.ascii "IEEE-695 (LADsoft variant) object file format\0"
LC77:
	.ascii "ieee\0"
	.data
	.align 32
_of_ieee:
	.long	LC76
	.long	LC77
	.long	0
	.long	_ladsoft_debug_arr
	.long	_null_debug_form
	.long	0
	.long	_ieee_init
	.long	_ieee_set_info
	.long	_ieee_out
	.long	_ieee_deflabel
	.long	_ieee_segment
	.long	_ieee_segbase
	.long	_ieee_directive
	.long	_ieee_filename
	.long	_ieee_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _ieee_infile,256
.lcomm _ieee_uppercase,16
.lcomm _error,16
.lcomm _deflabel,16
.lcomm _ofp,16
.lcomm _any_segs,16
.lcomm _arrindex,16
.lcomm _fnhead,16
.lcomm _fntail,16
.lcomm _arrhead,16
.lcomm _arrtail,16
.lcomm _fpubhead,16
.lcomm _fpubtail,16
.lcomm _last_defined,16
.lcomm _exthead,16
.lcomm _exttail,16
.lcomm _externals,16
.lcomm _ebhead,16
.lcomm _ebtail,16
.lcomm _seghead,16
.lcomm _segtail,16
.lcomm _ieee_seg_needs_update,16
.lcomm _ieee_entry_seg,16
.lcomm _ieee_entry_ofs,16
.lcomm _checksum,16
	.def	_null_debug_routine;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_toupper;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	___va_end;	.scl	2;	.type	32;	.endef
	.def	_vsprintf;	.scl	2;	.type	32;	.endef
	.def	___va_start;	.scl	2;	.type	32;	.endef
	.def	_localtime;	.scl	2;	.type	32;	.endef
	.def	_time;	.scl	2;	.type	32;	.endef
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
