	.file	"outbin.c"
	.data
	.align 4
_rf:
	.long	0
	.align 4
_map_control:
	.long	0
	.text
	.align 32
LC0:
	.ascii "%define __SECT__ [section .text]\0"
LC1:
	.ascii "%imacro org 1+.nolist\0"
LC2:
	.ascii "[org %1]\0"
LC3:
	.ascii "%endmacro\0"
LC4:
	.ascii "%macro __NASM_CDecl__ 1\0"
	.data
	.align 4
_bin_stdmac:
	.long	LC0
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC3
	.long	0
	.text
	.align 2
	.def	_add_reloc;	.scl	3;	.type	32;	.endef
_add_reloc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	_reloctail, %ebx
	movl	$24, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, _reloctail
	movl	$0, (%eax)
	movl	8(%esi), %edx
	movl	%edx, 4(%eax)
	movl	12(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	16(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	20(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	%esi, 20(%eax)
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_find_section_by_name;	.scl	3;	.type	32;	.endef
_find_section_by_name:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L4
L8:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L4
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L8
L4:
	movl	%ebx, %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_find_section_by_index;	.scl	3;	.type	32;	.endef
_find_section_by_index:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	_sections, %eax
	testl	%eax, %eax
	je	L12
L17:
	cmpl	44(%eax), %edx
	je	L12
	cmpl	40(%eax), %edx
	je	L12
	movl	60(%eax), %eax
	testl	%eax, %eax
	jne	L17
L12:
	popl	%ebp
	ret
	.align 2
	.def	_create_section;	.scl	3;	.type	32;	.endef
_create_section:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	_last_section, %ebx
	movl	$64, (%esp)
	call	_nasm_malloc
	movl	%eax, 60(%ebx)
	movl	_last_section, %edx
	movl	60(%edx), %eax
	movl	%edx, 56(%eax)
	movl	_last_section, %eax
	movl	60(%eax), %eax
	movl	%eax, _last_section
	movl	$0, 48(%eax)
	movl	_last_section, %edx
	leal	48(%edx), %eax
	movl	%eax, 52(%edx)
	movl	_last_section, %ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, (%ebx)
	movl	_last_section, %ebx
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, 4(%ebx)
	movl	_last_section, %eax
	movl	$0, 36(%eax)
	movl	$0, 32(%eax)
	movl	_last_section, %eax
	movl	$0, 8(%eax)
	movl	_last_section, %eax
	movl	$0, 12(%eax)
	movl	_last_section, %eax
	movl	$0, 60(%eax)
	movl	_last_section, %ebx
	call	_seg_alloc
	movl	%eax, 44(%ebx)
	movl	_last_section, %ebx
	call	_seg_alloc
	movl	%eax, 40(%ebx)
	movl	_last_section, %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 32
LC5:
	.ascii "cannot mix real and virtual attributes in nobits section (%s)\0"
	.align 32
LC6:
	.ascii "section %s follows an invalid or unknown section (%s)\0"
	.align 32
LC7:
	.ascii "sections %s and %s can't both follow section %s\0"
	.align 32
LC8:
	.ascii "section %s begins before program origin\0"
	.align 32
LC9:
	.ascii "sections %s ~ %s and %s overlap!\0"
LC10:
	.ascii "sections %s and %s overlap!\0"
	.align 32
LC11:
	.ascii "section %s vfollows unknown section (%s)\0"
	.align 32
LC12:
	.ascii "cannot compute vstart for section %s\0"
	.align 32
LC13:
	.ascii "circular vfollows path detected\0"
LC14:
	.ascii "not defined\0"
LC15:
	.ascii "\12- NASM Map file \0"
	.align 32
LC16:
	.ascii "\12\12Source file:  %s\12Output file:  %s\12\12\0"
LC17:
	.ascii "-- Program origin \0"
LC18:
	.ascii "\12\12%08lX\12\12\0"
LC19:
	.ascii "-- Sections (summary) \0"
	.align 32
LC20:
	.ascii "\12\12Vstart    Start     Stop      Length    Class     Name\12\0"
LC21:
	.ascii "%08lX  %08lX  %08lX  %08lX  \0"
LC22:
	.ascii "progbits  \0"
LC23:
	.ascii "nobits    \0"
LC24:
	.ascii "%s\12\0"
LC25:
	.ascii "\12\0"
LC26:
	.ascii "-- Sections (detailed) \0"
LC27:
	.ascii "\12\12\0"
LC28:
	.ascii "---- Section %s \0"
LC29:
	.ascii "\12\12class:     \0"
LC30:
	.ascii "progbits\0"
LC31:
	.ascii "nobits\0"
	.align 32
LC32:
	.ascii "\12length:    %08lX\12start:     %08lX\12align:     \0"
LC33:
	.ascii "%08lX\0"
LC34:
	.ascii "\12follows:   \0"
LC35:
	.ascii "%s\0"
LC36:
	.ascii "\12vstart:    %08lX\12valign:    \0"
LC37:
	.ascii "\12vfollows:  \0"
LC38:
	.ascii "-- Symbols \0"
LC39:
	.ascii "---- No Section \0"
LC40:
	.ascii "\12\12Value     Name\12\0"
LC41:
	.ascii "%08lX  %s\12\0"
LC42:
	.ascii "\12\12Real      Virtual   Name\12\0"
LC43:
	.ascii "%08lX  %08lX  %s\12\0"
	.align 2
	.def	_bin_cleanup;	.scl	3;	.type	32;	.endef
_bin_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	$0, -32(%ebp)
	movl	$0, -16(%ebp)
	leal	-16(%ebp), %esi
	movl	_sections, %eax
	leal	60(%eax), %edi
	movl	60(%eax), %ebx
	testl	%ebx, %ebx
	je	L299
L32:
	cmpb	$0, 12(%ebx)
	jns	L25
	leal	60(%ebx), %edi
	jmp	L23
L25:
	movl	12(%ebx), %eax
	testl	$7, %eax
	je	L26
	testl	$56, %eax
	je	L27
	movl	$2, (%esp)
	movl	$LC5, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, 8(%esp)
	call	*_error
L27:
	movl	12(%ebx), %edx
	testl	$1, %edx
	je	L28
	movl	24(%ebx), %eax
	movl	%eax, 28(%ebx)
	movl	%edx, %eax
	orl	$8, %eax
	movl	%eax, 12(%ebx)
L28:
	movl	12(%ebx), %edx
	testl	$2, %edx
	je	L29
	movl	16(%ebx), %eax
	movl	%eax, 20(%ebx)
	movl	%edx, %eax
	orl	$16, %eax
	movl	%eax, 12(%ebx)
L29:
	movl	12(%ebx), %edx
	testl	$4, %edx
	je	L26
	movl	32(%ebx), %eax
	movl	%eax, 36(%ebx)
	movl	%edx, %eax
	orl	$32, %eax
	andl	$-5, %eax
	movl	%eax, 12(%ebx)
L26:
	movl	12(%ebx), %edx
	testl	$8, %edx
	je	L31
	movl	28(%ebx), %eax
	movl	%eax, 24(%ebx)
	movl	%edx, %eax
	orl	$1, %eax
	movl	%eax, 12(%ebx)
L31:
	movl	60(%ebx), %eax
	movl	%eax, (%edi)
	movl	$0, 60(%ebx)
	movl	%ebx, (%esi)
	leal	60(%ebx), %esi
L23:
	movl	(%edi), %ebx
	testl	%ebx, %ebx
	jne	L32
L299:
	movl	$_sections, %edi
	movl	_sections, %esi
	testl	%esi, %esi
	je	L34
L59:
	testb	$4, 12(%esi)
	jne	L37
	cmpl	$0, 60(%esi)
	je	L34
L42:
	movl	60(%esi), %eax
	testb	$4, 12(%eax)
	je	L41
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	60(%esi), %eax
	movl	32(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L39
L41:
	movl	60(%esi), %esi
	cmpl	$0, 60(%esi)
	jne	L42
	jmp	L34
L39:
	cmpl	$0, 60(%esi)
	je	L34
	leal	60(%esi), %edi
	movl	60(%esi), %esi
L37:
	movl	_sections, %ebx
	jmp	L44
L49:
	movl	60(%ebx), %ebx
L44:
	testl	%ebx, %ebx
	je	L356
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	32(%esi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L49
	testl	%ebx, %ebx
	jne	L50
L356:
	movl	$2, (%esp)
	movl	$LC6, 4(%esp)
	movl	(%esi), %eax
	movl	%eax, 8(%esp)
	movl	32(%esi), %eax
	movl	%eax, 12(%esp)
	call	*_error
L50:
	cmpl	$0, 60(%ebx)
	je	L51
	movl	60(%ebx), %eax
	testb	$4, 12(%eax)
	je	L51
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	60(%ebx), %eax
	movl	32(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L51
	movl	$2, (%esp)
	movl	$LC7, 4(%esp)
	movl	(%esi), %eax
	movl	%eax, 8(%esp)
	movl	60(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, 12(%esp)
	movl	(%ebx), %eax
	movl	%eax, 16(%esp)
	call	*_error
L51:
	leal	60(%esi), %edx
	movl	60(%esi), %eax
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	je	L53
	cmpl	%ebx, %eax
	je	L53
	testb	$1, 12(%eax)
	jne	L53
L58:
	movl	-32(%ebp), %edx
	cmpl	$0, 60(%edx)
	je	L54
	movl	60(%edx), %eax
	testb	$4, 12(%eax)
	je	L54
	movl	(%edx), %eax
	movl	%eax, (%esp)
	movl	60(%edx), %eax
	movl	32(%eax), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L54
	movl	-32(%ebp), %edx
	addl	$60, %edx
	movl	-32(%ebp), %eax
	movl	60(%eax), %eax
	movl	%eax, -32(%ebp)
	jmp	L53
L54:
	movl	-32(%ebp), %edx
	addl	$60, %edx
	movl	-32(%ebp), %eax
	movl	60(%eax), %eax
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	je	L53
	cmpl	%ebx, %eax
	je	L53
	testb	$1, 12(%eax)
	je	L58
L53:
	movl	60(%ebx), %eax
	movl	%eax, (%edx)
	movl	%esi, 60(%ebx)
	movl	-32(%ebp), %edx
	movl	%edx, (%edi)
	movl	%edx, %esi
	testl	%edx, %edx
	jne	L59
L34:
	movl	_sections, %esi
	movl	$0, _sections
	testl	%esi, %esi
	je	L304
L76:
	movl	$_sections, %edi
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L65
L69:
	testb	$1, 12(%ebx)
	je	L66
	movl	24(%esi), %eax
	cmpl	24(%ebx), %eax
	jb	L65
L66:
	leal	60(%ebx), %edi
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L69
L65:
	movl	60(%esi), %eax
	movl	%eax, -32(%ebp)
	leal	60(%esi), %edx
	testl	%eax, %eax
	je	L71
	testb	$1, 12(%eax)
	jne	L71
L75:
	movl	-32(%ebp), %edx
	addl	$60, %edx
	movl	-32(%ebp), %eax
	movl	60(%eax), %eax
	movl	%eax, -32(%ebp)
	testl	%eax, %eax
	je	L71
	testb	$1, 12(%eax)
	je	L75
L71:
	movl	%esi, (%edi)
	movl	%ebx, (%edx)
	movl	-32(%ebp), %esi
	testl	%esi, %esi
	jne	L76
L304:
	cmpl	$0, _origin_defined
	je	L77
	movl	_sections, %eax
	movl	12(%eax), %eax
	andl	$3, %eax
	cmpl	$1, %eax
	je	L80
	cmpl	$1, %eax
	jg	L86
	testl	%eax, %eax
	je	L83
	jmp	L87
L86:
	cmpl	$2, %eax
	je	L82
	cmpl	$3, %eax
	jne	L87
L80:
	movl	_sections, %edx
	movl	24(%edx), %eax
	cmpl	_origin, %eax
	jae	L87
	movl	$2, (%esp)
	movl	$LC8, 4(%esp)
	movl	(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L87
L82:
	movl	_sections, %ecx
	movl	16(%ecx), %edx
	movl	_origin, %eax
	addl	%edx, %eax
	decl	%eax
	negl	%edx
	andl	%edx, %eax
	movl	%eax, 24(%ecx)
	jmp	L87
L83:
	movl	_origin, %edx
	movl	_sections, %eax
	movl	%edx, 24(%eax)
	jmp	L87
L77:
	movl	_sections, %eax
	testb	$1, 12(%eax)
	jne	L88
	movl	$0, 24(%eax)
L88:
	movl	_sections, %eax
	movl	24(%eax), %eax
	movl	%eax, _origin
L87:
	movl	_sections, %eax
	orl	$1, 12(%eax)
	movl	_sections, %eax
	movl	24(%eax), %edi
	movl	%eax, %ebx
	movl	%eax, %esi
	testl	%eax, %eax
	je	L308
L109:
	cmpl	%ebx, %esi
	jne	L93
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	je	L93
	cmpl	$0, 8(%ebx)
	je	L99
	testb	$1, 12(%ebx)
	jne	L93
L99:
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	je	L93
	cmpl	$0, 8(%ebx)
	je	L99
	testb	$1, 12(%ebx)
	je	L99
L93:
	movl	12(%esi), %eax
	testl	$1, %eax
	jne	L100
	testl	$2, %eax
	jne	L101
	movl	$4, 16(%esi)
	orl	$2, %eax
	movl	%eax, 12(%esi)
L101:
	movl	16(%esi), %eax
	leal	-1(%eax,%edi), %edx
	negl	%eax
	andl	%eax, %edx
	movl	%edx, 24(%esi)
	orl	$1, 12(%esi)
L100:
	movl	12(%esi), %eax
	testl	$40, %eax
	jne	L102
	testl	$16, %eax
	je	L103
	movl	20(%esi), %eax
	leal	-1(%eax,%edi), %edx
	negl	%eax
	andl	%eax, %edx
	movl	%edx, 28(%esi)
	jmp	L104
L103:
	movl	24(%esi), %eax
	movl	%eax, 28(%esi)
L104:
	orl	$8, 12(%esi)
L102:
	cmpl	%edi, 24(%esi)
	jb	L91
	movl	24(%esi), %eax
	movl	%eax, %edi
	addl	8(%esi), %edi
	testl	%ebx, %ebx
	je	L106
	cmpl	24(%ebx), %eax
	jbe	L107
	movl	$2, (%esp)
	movl	$LC9, 4(%esp)
	movl	-32(%ebp), %edx
	movl	(%edx), %eax
	movl	%eax, 8(%esp)
	movl	(%esi), %eax
	movl	%eax, 12(%esp)
	movl	(%ebx), %eax
	movl	%eax, 16(%esp)
	call	*_error
L107:
	cmpl	24(%ebx), %edi
	jbe	L106
	movl	$2, (%esp)
	movl	$LC10, 4(%esp)
	movl	(%esi), %eax
	movl	%eax, 8(%esp)
	movl	(%ebx), %eax
	movl	%eax, 12(%esp)
	call	*_error
L106:
	movl	%esi, -32(%ebp)
L91:
	movl	60(%esi), %esi
	testl	%esi, %esi
	jne	L109
L308:
	movl	_sections, %ebx
	cmpl	$0, 60(%ebx)
	je	L311
L114:
	movl	60(%ebx), %ebx
	cmpl	$0, 60(%ebx)
	jne	L114
L311:
	movl	-16(%ebp), %eax
	movl	%eax, 60(%ebx)
	movl	%ebx, -36(%ebp)
L115:
	movl	$0, %edi
	movl	_sections, %esi
	testl	%esi, %esi
	je	L313
L143:
	movl	12(%esi), %eax
	testl	$8, %eax
	jne	L120
	testl	$32, %eax
	je	L123
	movl	_sections, %ebx
	jmp	L124
L129:
	movl	60(%ebx), %ebx
L124:
	testl	%ebx, %ebx
	je	L357
	movl	36(%esi), %eax
	movl	%eax, (%esp)
	movl	(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L129
	testl	%ebx, %ebx
	jne	L131
L357:
	movl	$2, (%esp)
	movl	$LC11, 4(%esp)
	movl	(%esi), %eax
	movl	%eax, 8(%esp)
	movl	36(%esi), %eax
	movl	%eax, 12(%esp)
	call	*_error
	jmp	L131
L123:
	cmpl	$0, 56(%esi)
	je	L132
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L131
	cmpl	56(%esi), %ebx
	je	L131
L138:
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	je	L131
	cmpl	56(%esi), %ebx
	jne	L138
	jmp	L131
L132:
	movl	-36(%ebp), %ebx
L131:
	testb	$8, 12(%ebx)
	je	L120
	movl	12(%esi), %eax
	testl	$16, %eax
	jne	L141
	movl	$4, 20(%esi)
	orl	$16, %eax
	movl	%eax, 12(%esi)
L141:
	movl	28(%ebx), %eax
	addl	8(%ebx), %eax
	movl	20(%esi), %edx
	leal	-1(%edx,%eax), %eax
	negl	%edx
	andl	%eax, %edx
	movl	%edx, 28(%esi)
	movl	12(%esi), %eax
	orl	$8, %eax
	movl	%eax, 12(%esi)
	incl	%edi
	testl	$256, %eax
	je	L120
	movl	%edx, 24(%esi)
L120:
	movl	60(%esi), %esi
	testl	%esi, %esi
	jne	L143
L313:
	testl	%edi, %edi
	jne	L115
	movl	$0, %edi
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L316
L150:
	testb	$8, 12(%ebx)
	jne	L147
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	incl	%edi
L147:
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L150
L316:
	testl	%edi, %edi
	je	L151
	movl	$2, (%esp)
	movl	$LC13, 4(%esp)
	call	*_error
L151:
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L318
L156:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L156
L318:
	movl	_relocs, %esi
	testl	%esi, %esi
	je	L320
L181:
	movl	20(%esi), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%esi), %eax
	movl	%eax, 12(%esp)
	call	_saa_fread
	leal	-20(%ebp), %eax
	movl	%eax, -40(%ebp)
	movzbl	-20(%ebp), %edi
	cmpl	$1, 8(%esi)
	jle	L161
	movzbl	1(%eax), %eax
	sall	$8, %eax
	addl	%eax, %edi
	cmpl	$4, 8(%esi)
	jne	L161
	movl	-40(%ebp), %edx
	movzbl	2(%edx), %eax
	sall	$16, %eax
	addl	%eax, %edi
	movzbl	3(%edx), %eax
	sall	$24, %eax
	addl	%eax, %edi
L161:
	movl	12(%esi), %eax
	movl	%eax, (%esp)
	call	_find_section_by_index
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L163
	movl	12(%esi), %eax
	cmpl	40(%ebx), %eax
	jne	L164
	addl	24(%ebx), %edi
	jmp	L163
L164:
	addl	28(%ebx), %edi
L163:
	movl	16(%esi), %eax
	movl	%eax, (%esp)
	call	_find_section_by_index
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L166
	movl	16(%esi), %eax
	cmpl	40(%ebx), %eax
	jne	L167
	subl	24(%ebx), %edi
	jmp	L166
L167:
	subl	28(%ebx), %edi
L166:
	cmpl	$4, 8(%esi)
	jne	L169
	movl	%edi, %eax
	movl	-40(%ebp), %edx
	movb	%al, (%edx)
	incl	%edx
	movl	%edi, %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movl	%edi, %eax
	sarl	$16, %eax
	movb	%al, (%edx)
	movl	%edi, %eax
	sarl	$24, %eax
	jmp	L358
L169:
	cmpl	$2, 8(%esi)
	jne	L176
	movl	%edi, %eax
	movl	-40(%ebp), %edx
	movb	%al, (%edx)
	movl	%edi, %eax
	sarl	$8, %eax
L358:
	movb	%al, 1(%edx)
	jmp	L175
L176:
	movl	%edi, %eax
	movl	-40(%ebp), %edx
	movb	%al, (%edx)
L175:
	movl	20(%esi), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%esi), %eax
	movl	%eax, 12(%esp)
	call	_saa_fwrite
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L181
L320:
	movl	_origin, %edi
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L183
	cmpb	$0, 12(%ebx)
	jns	L183
L194:
	cmpl	$0, 8(%ebx)
	je	L184
	movl	24(%ebx), %eax
	subl	%edi, %eax
	movl	%eax, %edi
	je	L323
L192:
	movl	$0, (%esp)
	movl	_fp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L192
L323:
	cmpl	$0, 8(%ebx)
	jle	L193
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	_fp, %eax
	movl	%eax, 4(%esp)
	call	_saa_fpwrite
L193:
	movl	24(%ebx), %eax
	movl	%eax, %edi
	addl	8(%ebx), %edi
L184:
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	je	L183
	cmpb	$0, 12(%ebx)
	js	L194
L183:
	movl	_fp, %eax
	movl	%eax, (%esp)
	call	_fclose
	cmpl	$0, _map_control
	je	L279
	movl	$LC14, %esi
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC15, 4(%esp)
	call	_fprintf
	movl	$63, %edi
L200:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L200
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC16, 4(%esp)
	movl	_infile, %eax
	movl	%eax, 8(%esp)
	movl	_outfile, %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	testb	$1, _map_control
	je	L201
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC17, 4(%esp)
	call	_fprintf
	movl	$61, %edi
L206:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L206
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC18, 4(%esp)
	movl	_origin, %eax
	movl	%eax, 8(%esp)
	call	_fprintf
L201:
	testb	$2, _map_control
	je	L207
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC19, 4(%esp)
	call	_fprintf
	movl	$57, %edi
L212:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L212
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC20, 4(%esp)
	call	_fprintf
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L331
L219:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC21, 4(%esp)
	movl	28(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	24(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	24(%ebx), %eax
	addl	8(%ebx), %eax
	movl	%eax, 16(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 20(%esp)
	call	_fprintf
	cmpb	$0, 12(%ebx)
	jns	L217
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC22, 4(%esp)
	jmp	L359
L217:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC23, 4(%esp)
L359:
	call	_fprintf
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC24, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L219
L331:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC25, 4(%esp)
	call	_fprintf
L207:
	testb	$4, _map_control
	je	L220
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC26, 4(%esp)
	call	_fprintf
	movl	$56, %edi
L225:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L225
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC27, 4(%esp)
	call	_fprintf
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L220
L245:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC28, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	$65, %edx
	movl	%edx, %edi
	subl	%eax, %edi
	je	L336
L234:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L234
L336:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC29, 4(%esp)
	call	_fprintf
	cmpb	$0, 12(%ebx)
	jns	L235
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC30, 4(%esp)
	jmp	L360
L235:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC31, 4(%esp)
L360:
	call	_fprintf
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esp)
	movl	24(%ebx), %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	testb	$2, 12(%ebx)
	je	L237
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC33, 4(%esp)
	movl	16(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	jmp	L238
L237:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fprintf
L238:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC34, 4(%esp)
	call	_fprintf
	testb	$4, 12(%ebx)
	je	L239
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC35, 4(%esp)
	movl	32(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	jmp	L240
L239:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fprintf
L240:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC36, 4(%esp)
	movl	28(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	testb	$16, 12(%ebx)
	je	L241
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC33, 4(%esp)
	movl	20(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	jmp	L242
L241:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fprintf
L242:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC37, 4(%esp)
	call	_fprintf
	testb	$32, 12(%ebx)
	je	L243
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC35, 4(%esp)
	movl	36(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	jmp	L244
L243:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_fprintf
L244:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC27, 4(%esp)
	call	_fprintf
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L245
L220:
	testb	$8, _map_control
	je	L195
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC38, 4(%esp)
	call	_fprintf
	movl	$68, %edi
L251:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L251
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC27, 4(%esp)
	call	_fprintf
	cmpl	$0, _no_seg_labels
	je	L252
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC39, 4(%esp)
	call	_fprintf
	movl	$63, %edi
L257:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L257
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC40, 4(%esp)
	call	_fprintf
	movl	_no_seg_labels, %esi
	testl	%esi, %esi
	je	L342
L262:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_lookup_label
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC41, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	(%esi), %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	movl	4(%esi), %esi
	testl	%esi, %esi
	jne	L262
L342:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC27, 4(%esp)
	call	_fprintf
L252:
	movl	_sections, %ebx
	testl	%ebx, %ebx
	je	L195
L278:
	cmpl	$0, 48(%ebx)
	je	L265
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC28, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, 8(%esp)
	call	_fprintf
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	$65, %edx
	movl	%edx, %edi
	subl	%eax, %edi
	je	L345
L272:
	movl	$45, (%esp)
	movl	_rf, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	decl	%edi
	jne	L272
L345:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC42, 4(%esp)
	call	_fprintf
	movl	48(%ebx), %esi
	testl	%esi, %esi
	je	L347
L277:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_lookup_label
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC43, 4(%esp)
	movl	-28(%ebp), %eax
	movl	24(%ebx), %edx
	addl	%eax, %edx
	movl	%edx, 8(%esp)
	addl	28(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	(%esi), %eax
	movl	%eax, 16(%esp)
	call	_fprintf
	movl	4(%esi), %esi
	testl	%esi, %esi
	jne	L277
L347:
	movl	_rf, %eax
	movl	%eax, (%esp)
	movl	$LC25, 4(%esp)
	call	_fprintf
L265:
	movl	60(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L278
L195:
	cmpl	$0, _map_control
	je	L279
	movl	_rf, %eax
	cmpl	_stdout, %eax
	je	L279
	cmpl	_stderr, %eax
	je	L279
	movl	%eax, (%esp)
	call	_fclose
L279:
	cmpl	$0, _sections
	je	L349
L289:
	movl	_sections, %ebx
	movl	60(%ebx), %eax
	movl	%eax, _sections
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_saa_free
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	testb	$4, 12(%ebx)
	je	L283
	movl	32(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L283:
	testb	$32, 12(%ebx)
	je	L284
	movl	36(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L284:
	cmpl	$0, 48(%ebx)
	je	L351
L288:
	movl	48(%ebx), %esi
	movl	4(%esi), %eax
	movl	%eax, 48(%ebx)
	movl	%esi, (%esp)
	call	_nasm_free
	cmpl	$0, 48(%ebx)
	jne	L288
L351:
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _sections
	jne	L289
L349:
	cmpl	$0, _no_seg_labels
	je	L353
L293:
	movl	_no_seg_labels, %esi
	movl	4(%esi), %eax
	movl	%eax, _no_seg_labels
	movl	%esi, (%esp)
	call	_nasm_free
	cmpl	$0, _no_seg_labels
	jne	L293
L353:
	cmpl	$0, _relocs
	je	L355
L297:
	movl	_relocs, %eax
	movl	(%eax), %esi
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%esi, _relocs
	testl	%esi, %esi
	jne	L297
L355:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC44:
	.ascii "WRT not supported by binary output format\0"
	.align 32
LC45:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC46:
	.ascii "code directed to nonexistent segment?\0"
	.align 32
LC47:
	.ascii "attempt to initialise memory in a nobits section: ignored\0"
	.align 32
LC48:
	.ascii "binary output format does not support segment base references\0"
	.align 32
LC49:
	.ascii "binary output format does not support external references\0"
	.align 32
LC50:
	.ascii "uninitialised space declared in %s section: zeroing\0"
	.align 2
	.def	_bin_out;	.scl	3;	.type	32;	.endef
_bin_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	16(%ebp), %ebx
	movl	20(%ebp), %edi
	cmpl	$-1, 24(%ebp)
	je	L362
	movl	$1, (%esp)
	movl	$LC44, 4(%esp)
	call	*_error
L362:
	cmpl	$-1, 8(%ebp)
	jne	L363
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	je	L361
	movl	$1, (%esp)
	movl	$LC45, 4(%esp)
	call	*_error
	jmp	L361
L363:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_find_section_by_index
	movl	%eax, %esi
	testl	%eax, %eax
	jne	L365
	movl	$3, (%esp)
	movl	$LC46, 4(%esp)
	call	*_error
L365:
	movl	12(%esi), %edx
	testl	$64, %edx
	jne	L366
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	jne	L367
	movl	%edx, %eax
	orl	$320, %eax
	movl	%eax, 12(%esi)
	jmp	L366
L367:
	orl	$192, 12(%esi)
L366:
	testb	$1, 13(%esi)
	je	L369
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	je	L369
	movl	$0, (%esp)
	movl	$LC47, 4(%esp)
	call	*_error
L369:
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$268435456, %eax
	jne	L370
	cmpl	$-1, %edi
	je	L371
	movl	%edi, (%esp)
	call	_find_section_by_index
	testl	%eax, %eax
	jne	L371
	testl	$1, %edi
	je	L372
	movl	$1, (%esp)
	movl	$LC48, 4(%esp)
	jmp	L411
L372:
	movl	$1, (%esp)
	movl	$LC49, 4(%esp)
L411:
	call	*_error
	movl	$-1, %edi
L371:
	cmpb	$0, 12(%esi)
	jns	L374
	cmpl	$-1, %edi
	je	L375
	movl	%esi, (%esp)
	movl	%ebx, %eax
	andl	$268435455, %eax
	movl	%eax, 4(%esp)
	movl	%edi, 8(%esp)
	movl	$-1, 12(%esp)
	call	_add_reloc
L375:
	leal	-16(%ebp), %edx
	movl	%ebx, %eax
	andl	$268435455, %eax
	cmpl	$4, %eax
	jne	L376
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	movb	%al, -16(%ebp)
	incl	%edx
	movl	(%ecx), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movswl	2(%ecx),%eax
	movb	%al, (%edx)
	movsbl	3(%ecx),%eax
	jmp	L412
L376:
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	movb	%al, (%edx)
	movl	(%ecx), %eax
	sarl	$8, %eax
L412:
	movb	%al, 1(%edx)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, %eax
	andl	$268435455, %eax
	movl	%eax, 8(%esp)
	call	_saa_wbytes
L374:
	movl	%ebx, %eax
	andl	$268435455, %eax
	addl	%eax, 8(%esi)
	jmp	L361
L370:
	testl	$-268435456, %ebx
	jne	L387
	andl	$268435455, %ebx
	cmpb	$0, 12(%esi)
	jns	L400
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	jmp	L415
L387:
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	jne	L390
	andl	$268435455, %ebx
	cmpb	$0, 12(%esi)
	jns	L400
	movl	$0, (%esp)
	movl	$LC50, 4(%esp)
	movl	(%esi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	jmp	L416
L390:
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$536870912, %eax
	je	L394
	cmpl	$805306368, %eax
	jne	L361
L394:
	movl	%ebx, %eax
	andl	$-268435456, %eax
	cmpl	$805306368, %eax
	sete	%al
	movzbl	%al, %ebx
	leal	2(%ebx,%ebx), %ebx
	cmpl	$-1, %edi
	je	L397
	movl	%edi, (%esp)
	call	_find_section_by_index
	testl	%eax, %eax
	jne	L397
	testl	$1, %edi
	je	L398
	movl	$1, (%esp)
	movl	$LC48, 4(%esp)
	jmp	L413
L398:
	movl	$1, (%esp)
	movl	$LC49, 4(%esp)
L413:
	call	*_error
	movl	$-1, %edi
L397:
	cmpb	$0, 12(%esi)
	jns	L400
	movl	%esi, (%esp)
	movl	%ebx, 4(%esp)
	movl	%edi, 8(%esp)
	movl	8(%ebp), %ecx
	movl	%ecx, 12(%esp)
	call	_add_reloc
	leal	-16(%ebp), %edx
	cmpl	$4, %ebx
	jne	L401
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	subb	$4, %al
	subb	8(%esi), %al
	movb	%al, -16(%ebp)
	incl	%edx
	movl	(%ecx), %eax
	subl	$4, %eax
	subl	8(%esi), %eax
	sarl	$8, %eax
	movb	%al, (%edx)
	incl	%edx
	movl	(%ecx), %eax
	subl	$4, %eax
	subl	8(%esi), %eax
	sarl	$16, %eax
	movb	%al, (%edx)
	movl	(%ecx), %eax
	subl	$4, %eax
	subl	8(%esi), %eax
	sarl	$24, %eax
	jmp	L414
L401:
	movl	12(%ebp), %ecx
	movzbl	(%ecx), %eax
	subb	%bl, %al
	subb	8(%esi), %al
	movb	%al, (%edx)
	movl	(%ecx), %eax
	subl	%ebx, %eax
	subl	8(%esi), %eax
	sarl	$8, %eax
L414:
	movb	%al, 1(%edx)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
L415:
	movl	%eax, 4(%esp)
L416:
	movl	%ebx, 8(%esp)
	call	_saa_wbytes
L400:
	addl	%ebx, 8(%esi)
L361:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC51:
	.ascii "binary format does not support any special symbol types\0"
	.align 32
LC52:
	.ascii "unrecognised special symbol `%s'\0"
	.align 32
LC53:
	.ascii "binary output format does not support common variables\0"
	.align 2
	.def	_bin_deflabel;	.scl	3;	.type	32;	.endef
_bin_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	cmpl	$0, 24(%ebp)
	je	L418
	movl	$1, (%esp)
	movl	$LC51, 4(%esp)
	jmp	L426
L418:
	cmpb	$46, (%edi)
	jne	L420
	cmpb	$46, 1(%edi)
	jne	L420
	cmpb	$64, 2(%edi)
	je	L420
	movl	$1, (%esp)
	movl	$LC52, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_error
	jmp	L417
L420:
	cmpl	$2, 20(%ebp)
	jne	L422
	movl	$1, (%esp)
	movl	$LC53, 4(%esp)
L426:
	call	*_error
	jmp	L417
L422:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_find_section_by_index
	movl	$_nsl_tail, %esi
	testl	%eax, %eax
	je	L425
	leal	52(%eax), %esi
L425:
	movl	(%esi), %ebx
	movl	$8, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	(%esi), %eax
	movl	(%eax), %eax
	movl	%edi, (%eax)
	movl	(%esi), %eax
	movl	(%eax), %eax
	movl	$0, 4(%eax)
	movl	(%esi), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	%eax, (%esi)
L417:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC54:
	.ascii "align=\0"
LC55:
	.ascii "start=\0"
LC56:
	.ascii "follows=\0"
LC57:
	.ascii "vstart=\0"
LC58:
	.ascii "valign=\0"
LC59:
	.ascii "vfollows=\0"
LC60:
	.ascii "()'\"\0"
LC62:
	.ascii "expecting `)'\0"
	.align 32
LC63:
	.ascii "No value given to attribute in `section' directive\0"
	.align 32
LC64:
	.ascii "section attribute value must be a critical expression\0"
	.align 32
LC65:
	.ascii "Invalid attribute value specified in `section' directive.\0"
	.align 32
LC61:
	.ascii "invalid syntax in `section' directive\0"
	.align 2
	.def	_bin_read_attribute;	.scl	3;	.type	32;	.endef
_bin_read_attribute:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	jmp	L428
L432:
	incl	(%ebx)
L428:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	je	L429
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L432
L429:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	je	L436
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC54, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L434
	movl	$1, (%esi)
	jmp	L485
L434:
	cmpb	$0, _format_mode
	je	L436
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC55, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L437
	movl	$0, (%esi)
L485:
	movl	$6, %edx
	jmp	L435
L437:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC56, 4(%esp)
	movl	$8, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L439
	movl	$2, (%esi)
	jmp	L488
L439:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC57, 4(%esp)
	movl	$7, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L441
	movl	$3, (%esi)
	jmp	L484
L441:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC58, 4(%esp)
	movl	$7, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L443
	movl	$4, (%esi)
L484:
	movl	$7, %edx
	jmp	L435
L443:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC59, 4(%esp)
	movl	$9, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L445
	movl	$5, (%esi)
	addl	$9, (%ebx)
	jmp	L487
L445:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC31, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L447
	movl	(%ebx), %eax
	movsbl	6(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L448
	movl	(%ebx), %eax
	cmpb	$0, 6(%eax)
	jne	L447
L448:
	movl	$6, (%esi)
	addl	$6, (%ebx)
	jmp	L487
L447:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC30, 4(%esp)
	movl	$8, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L436
	movl	(%ebx), %eax
	movsbl	8(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L451
	movl	(%ebx), %eax
	cmpb	$0, 8(%eax)
	jne	L436
L451:
	movl	$7, (%esi)
L488:
	addl	$8, (%ebx)
	jmp	L487
L436:
	movl	$0, %eax
	jmp	L427
L435:
	movl	(%ebx), %eax
	cmpb	$40, (%edx,%eax)
	je	L454
	leal	(%eax,%edx), %eax
	movl	%eax, (%ebx)
	movl	%eax, %edi
	jmp	L455
L459:
	incl	(%ebx)
L455:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	je	L456
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L459
L456:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	je	L461
	movb	$0, (%eax)
	incl	(%ebx)
	jmp	L461
L454:
	movl	$1, %esi
	movl	%edx, %eax
	addl	(%ebx), %eax
	incl	%eax
	movl	%eax, (%ebx)
	movl	%eax, %edi
L477:
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	movl	$LC60, 4(%esp)
	call	_strcspn
	addl	(%ebx), %eax
	movl	%eax, (%ebx)
	cmpb	$40, (%eax)
	jne	L465
	incl	%eax
	movl	%eax, (%ebx)
	incl	%esi
L465:
	movl	(%ebx), %eax
	cmpb	$41, (%eax)
	jne	L466
	incl	%eax
	movl	%eax, (%ebx)
	decl	%esi
	je	L463
L466:
	movl	(%ebx), %eax
	cmpb	$34, (%eax)
	je	L469
	cmpb	$39, (%eax)
	jne	L468
L469:
	movl	(%ebx), %eax
	movzbl	(%eax), %ecx
	testb	%cl, %cl
	je	L471
L474:
	movl	(%ebx), %edx
	leal	1(%edx), %eax
	movl	%eax, (%ebx)
	cmpb	%cl, 1(%edx)
	je	L471
	cmpb	$0, 1(%edx)
	jne	L474
L471:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	je	L483
	incl	(%ebx)
L468:
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	jne	L477
	movl	$1, (%esp)
	movl	$LC62, 4(%esp)
	jmp	L486
L463:
	movl	(%ebx), %eax
	movb	$0, -1(%eax)
L461:
	cmpb	$0, (%edi)
	jne	L478
	movl	$0, (%esp)
	movl	$LC63, 4(%esp)
	jmp	L486
L478:
	call	_stdscan_reset
	movl	%edi, _stdscan_bufptr
	movl	$-1, -40(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$1, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	_evaluate
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L479
	movl	%eax, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	jne	L481
	movl	$1, (%esp)
	movl	$LC64, 4(%esp)
	jmp	L486
L479:
	movl	$1, (%esp)
	movl	$LC65, 4(%esp)
	jmp	L486
L483:
	movl	$1, (%esp)
	movl	$LC61, 4(%esp)
L486:
	call	*_error
	movl	$-1, %eax
	jmp	L427
L481:
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	16(%ebp), %edx
	movl	%eax, (%edx)
L487:
	movl	$1, %eax
L427:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC66:
	.ascii "ignoring unknown section attribute: \"%s\"\0"
	.align 32
LC67:
	.ascii "attempt to change section type from progbits to nobits\0"
	.align 32
LC68:
	.ascii "attempt to change section type from nobits to progbits\0"
LC69:
	.ascii ".text\0"
	.align 32
LC70:
	.ascii "cannot specify an alignment to the .text section\0"
	.align 32
LC71:
	.ascii "argument to `align' is not a power of two\0"
	.align 32
LC72:
	.ascii "`align' value conflicts with section start address\0"
	.align 32
LC73:
	.ascii "argument to `valign' is not a power of two\0"
	.align 32
LC74:
	.ascii "`valign' value conflicts with `vstart' address\0"
	.align 32
LC75:
	.ascii "cannot combine `start' and `follows' section attributes\0"
	.align 32
LC77:
	.ascii "section start address redefined\0"
	.align 32
LC78:
	.ascii "`start' address conflicts with section alignment\0"
	.align 32
LC80:
	.ascii "section virtual start address (vstart) redefined\0"
	.align 32
LC81:
	.ascii "`vstart' address conflicts with `valign' value\0"
LC82:
	.ascii " \11\0"
	.align 32
LC83:
	.ascii "expecting section name for `follows' attribute\0"
	.align 32
LC79:
	.ascii "cannot combine `vstart' and `vfollows' section attributes\0"
	.align 32
LC84:
	.ascii "expecting section name for `vfollows' attribute\0"
	.align 2
	.def	_bin_assign_attributes;	.scl	3;	.type	32;	.endef
_bin_assign_attributes:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
L553:
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_bin_read_attribute
	cmpl	$-1, %eax
	je	L553
	testl	%eax, %eax
	jne	L494
	movl	12(%ebp), %eax
	cmpb	$0, (%eax)
	je	L489
	movl	%eax, %ebx
	jmp	L497
L501:
	incl	12(%ebp)
L497:
	movl	12(%ebp), %eax
	cmpb	$0, (%eax)
	je	L498
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L501
L498:
	movl	12(%ebp), %eax
	cmpb	$0, (%eax)
	je	L502
	movb	$0, (%eax)
	incl	12(%ebp)
L502:
	movl	$0, (%esp)
	movl	$LC66, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_error
	jmp	L553
L494:
	cmpl	$7, -12(%ebp)
	ja	L553
	movl	-12(%ebp), %eax
	jmp	*L551(,%eax,4)
	.align 4
	.align 4
L551:
	.long	L526
	.long	L510
	.long	L542
	.long	L535
	.long	L519
	.long	L546
	.long	L504
	.long	L507
L504:
	movl	12(%esi), %eax
	andl	$192, %eax
	cmpl	$192, %eax
	jne	L505
	movl	$1, (%esp)
	movl	$LC67, 4(%esp)
	jmp	L554
L505:
	orl	$320, 12(%esi)
	jmp	L553
L507:
	movl	12(%esi), %eax
	andl	$320, %eax
	cmpl	$320, %eax
	jne	L508
	movl	$1, (%esp)
	movl	$LC68, 4(%esp)
	jmp	L554
L508:
	orl	$192, 12(%esi)
	jmp	L553
L510:
	cmpb	$0, _format_mode
	jne	L511
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	$LC69, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L511
	movl	$1, (%esp)
	movl	$LC70, 4(%esp)
	jmp	L554
L511:
	cmpl	$0, -16(%ebp)
	je	L514
	movl	-16(%ebp), %eax
	decl	%eax
	andl	-16(%ebp), %eax
	testl	%eax, %eax
	je	L513
L514:
	movl	$1, (%esp)
	movl	$LC71, 4(%esp)
	jmp	L554
L513:
	testb	$2, 12(%esi)
	je	L516
	movl	-16(%ebp), %eax
	cmpl	16(%esi), %eax
	jae	L516
	movl	16(%esi), %eax
	movl	%eax, -16(%ebp)
L516:
	testb	$1, 12(%esi)
	je	L517
	movl	-16(%ebp), %eax
	decl	%eax
	andl	24(%esi), %eax
	testl	%eax, %eax
	je	L517
	movl	$1, (%esp)
	movl	$LC72, 4(%esp)
	jmp	L554
L517:
	movl	-16(%ebp), %eax
	movl	%eax, 16(%esi)
	orl	$2, 12(%esi)
	jmp	L553
L519:
	cmpl	$0, -16(%ebp)
	je	L521
	movl	-16(%ebp), %eax
	decl	%eax
	andl	-16(%ebp), %eax
	testl	%eax, %eax
	je	L520
L521:
	movl	$1, (%esp)
	movl	$LC73, 4(%esp)
	jmp	L554
L520:
	testb	$16, 12(%esi)
	je	L523
	movl	-16(%ebp), %eax
	cmpl	20(%esi), %eax
	jae	L523
	movl	20(%esi), %eax
	movl	%eax, -16(%ebp)
L523:
	testb	$8, 12(%esi)
	je	L524
	movl	-16(%ebp), %eax
	decl	%eax
	andl	28(%esi), %eax
	testl	%eax, %eax
	je	L524
	movl	$1, (%esp)
	movl	$LC74, 4(%esp)
	jmp	L554
L524:
	movl	-16(%ebp), %eax
	movl	%eax, 20(%esi)
	orl	$16, 12(%esi)
	jmp	L553
L526:
	testb	$4, 12(%esi)
	je	L529
	movl	$1, (%esp)
	movl	$LC75, 4(%esp)
	jmp	L554
L529:
	testb	$1, 12(%esi)
	je	L531
	movl	-16(%ebp), %eax
	cmpl	24(%esi), %eax
	je	L531
	movl	$1, (%esp)
	movl	$LC77, 4(%esp)
	jmp	L554
L531:
	movl	-16(%ebp), %edx
	movl	%edx, 24(%esi)
	movl	12(%esi), %eax
	orl	$1, %eax
	movl	%eax, 12(%esi)
	testl	$2, %eax
	je	L553
	movl	16(%esi), %eax
	decl	%eax
	testl	%edx, %eax
	je	L534
	movl	$1, (%esp)
	movl	$LC78, 4(%esp)
	call	*_error
L534:
	xorl	$2, 12(%esi)
	jmp	L553
L535:
	testb	$32, 12(%esi)
	jne	L555
	testb	$8, 12(%esi)
	je	L538
	movl	-16(%ebp), %eax
	cmpl	28(%esi), %eax
	je	L538
	movl	$1, (%esp)
	movl	$LC80, 4(%esp)
	jmp	L554
L538:
	movl	-16(%ebp), %edx
	movl	%edx, 28(%esi)
	movl	12(%esi), %eax
	orl	$8, %eax
	movl	%eax, 12(%esi)
	testl	$16, %eax
	je	L553
	movl	20(%esi), %eax
	decl	%eax
	testl	%edx, %eax
	je	L541
	movl	$1, (%esp)
	movl	$LC81, 4(%esp)
	call	*_error
L541:
	xorl	$16, 12(%esi)
	jmp	L553
L542:
	movl	12(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC82, 4(%esp)
	call	_strcspn
	addl	%eax, 12(%ebp)
	cmpl	%ebx, 12(%ebp)
	jne	L543
	movl	$1, (%esp)
	movl	$LC83, 4(%esp)
	jmp	L554
L543:
	movl	12(%ebp), %eax
	movb	$0, (%eax)
	incl	12(%ebp)
	testb	$1, 12(%esi)
	je	L545
	movl	$1, (%esp)
	movl	$LC75, 4(%esp)
	call	*_error
L545:
	movl	%ebx, (%esp)
	call	_nasm_strdup
	movl	%eax, 32(%esi)
	orl	$4, 12(%esi)
	jmp	L553
L546:
	testb	$8, 12(%esi)
	je	L547
L555:
	movl	$1, (%esp)
	movl	$LC79, 4(%esp)
	jmp	L554
L547:
	movl	12(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC82, 4(%esp)
	call	_strcspn
	addl	%eax, 12(%ebp)
	cmpl	%ebx, 12(%ebp)
	jne	L549
	movl	$1, (%esp)
	movl	$LC84, 4(%esp)
L554:
	call	*_error
	jmp	L553
L549:
	movl	12(%ebp), %eax
	movb	$0, (%eax)
	incl	12(%ebp)
	movl	%ebx, (%esp)
	call	_nasm_strdup
	movl	%eax, 36(%esi)
	orl	$32, 12(%esi)
	jmp	L553
L489:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.data
	.align 4
_labels_defined.0:
	.long	0
	.text
LC85:
	.ascii "section.\0"
LC86:
	.ascii ".start\0"
LC87:
	.ascii ".vstart\0"
	.align 2
	.def	_bin_define_section_labels;	.scl	3;	.type	32;	.endef
_bin_define_section_labels:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	cmpl	$0, _labels_defined.0
	jne	L556
	movl	_sections, %edi
	testl	%edi, %edi
	je	L564
L562:
	movl	(%edi), %eax
	movl	%eax, (%esp)
	call	_strlen
	leal	8(%eax), %ebx
	addl	$16, %eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %esi
	movl	%eax, (%esp)
	movl	$LC85, 4(%esp)
	call	_strcpy
	leal	8(%esi), %eax
	movl	%eax, (%esp)
	movl	(%edi), %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	leal	(%ebx,%esi), %ebx
	movl	%ebx, (%esp)
	movl	$LC86, 4(%esp)
	call	_strcpy
	call	_bin_get_ofmt
	movl	%esi, (%esp)
	movl	40(%edi), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	%eax, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	_define_label
	movl	%ebx, (%esp)
	movl	$LC87, 4(%esp)
	call	_strcpy
	call	_bin_get_ofmt
	movl	%esi, (%esp)
	movl	44(%edi), %edx
	movl	%edx, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	%eax, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	_define_label
	movl	%esi, (%esp)
	call	_nasm_free
	movl	60(%edi), %edi
	testl	%edi, %edi
	jne	L562
L564:
	movl	$1, _labels_defined.0
L556:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC88:
	.ascii ".data\0"
LC89:
	.ascii ".bss\0"
	.align 32
LC90:
	.ascii "section name must be .text, .data, or .bss\0"
	.align 2
	.def	_bin_secname;	.scl	3;	.type	32;	.endef
_bin_secname:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	testl	%edi, %edi
	jne	L566
	movl	$0, _origin_defined
	movl	_sections, %esi
	testl	%esi, %esi
	je	L588
L571:
	andl	$-28, 12(%esi)
	movl	60(%esi), %esi
	testl	%esi, %esi
	jne	L571
L588:
	cmpb	$0, _format_mode
	je	L572
	cmpl	$1, 12(%ebp)
	je	L572
	call	_bin_define_section_labels
L572:
	movl	16(%ebp), %eax
	movl	$16, (%eax)
	movl	$LC69, (%esp)
	call	_find_section_by_name
	movl	%eax, %esi
	orl	$192, 12(%eax)
	jmp	L586
L566:
	movl	%edi, %ebx
	jmp	L573
L577:
	incl	%ebx
L573:
	cmpb	$0, (%ebx)
	je	L578
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L577
	cmpb	$0, (%ebx)
	je	L578
	movb	$0, (%ebx)
	incl	%ebx
L578:
	movl	%edi, (%esp)
	call	_find_section_by_name
	movl	%eax, %esi
	testl	%eax, %eax
	jne	L579
	movl	%edi, (%esp)
	call	_create_section
	movl	%eax, %esi
	movl	%edi, (%esp)
	movl	$LC88, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L580
	orl	$192, 12(%esi)
	jmp	L579
L580:
	movl	%edi, (%esp)
	movl	$LC89, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L582
	orl	$320, 12(%esi)
	movl	$0, 56(%esi)
	jmp	L579
L582:
	cmpb	$0, _format_mode
	jne	L579
	movl	$1, (%esp)
	movl	$LC90, 4(%esp)
	call	*_error
	movl	_current_section, %eax
	jmp	L565
L579:
	cmpl	$1, 12(%ebp)
	je	L586
	movl	%esi, (%esp)
	movl	%ebx, 4(%esp)
	call	_bin_assign_attributes
	movl	12(%esi), %eax
	testl	$64, %eax
	jne	L586
	orl	$192, %eax
	movl	%eax, 12(%esi)
L586:
	movl	44(%esi), %eax
	movl	%eax, _current_section
L565:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC91:
	.ascii "org\0"
	.align 32
LC92:
	.ascii "org value must be a critical expression\0"
LC93:
	.ascii "program origin redefined\0"
	.align 32
LC94:
	.ascii "No or invalid offset specified in ORG directive.\0"
LC95:
	.ascii "map\0"
LC96:
	.ascii "all\0"
LC97:
	.ascii "brief\0"
LC98:
	.ascii "sections\0"
LC99:
	.ascii "segments\0"
LC100:
	.ascii "symbols\0"
LC101:
	.ascii "stdout\0"
LC102:
	.ascii "stderr\0"
LC103:
	.ascii "wt\0"
LC104:
	.ascii "unable to open map file `%s'\0"
LC105:
	.ascii "map file already specified\0"
	.align 2
	.def	_bin_directive;	.scl	3;	.type	32;	.endef
_bin_directive:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movl	%ebx, (%esp)
	movl	$LC91, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L590
	call	_stdscan_reset
	movl	%esi, _stdscan_bufptr
	movl	$-1, -24(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$1, 16(%esp)
	movl	_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	_evaluate
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L591
	movl	%eax, (%esp)
	call	_is_really_simple
	testl	%eax, %eax
	jne	L592
	movl	$1, (%esp)
	movl	$LC92, 4(%esp)
	jmp	L626
L592:
	movl	%ebx, (%esp)
	call	_reloc_value
	cmpl	$0, _origin_defined
	je	L594
	cmpl	_origin, %eax
	je	L594
	movl	$1, (%esp)
	movl	$LC93, 4(%esp)
	jmp	L626
L594:
	movl	%eax, _origin
	movl	$1, _origin_defined
	jmp	L623
L591:
	movl	$1, (%esp)
	movl	$LC94, 4(%esp)
L626:
	call	*_error
	jmp	L623
L590:
	cmpb	$0, _format_mode
	je	L597
	movl	%ebx, (%esp)
	movl	$LC95, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L597
	movl	$1, %eax
	cmpl	$1, 16(%ebp)
	jne	L589
	movl	%esi, (%esp)
	movl	$LC82, 4(%esp)
	call	_strspn
	addl	%eax, %esi
	cmpb	$0, (%esi)
	je	L625
L621:
	movl	%esi, %ebx
	movl	%esi, (%esp)
	movl	$LC82, 4(%esp)
	call	_strcspn
	addl	%eax, %esi
	cmpb	$0, (%esi)
	je	L603
	movb	$0, (%esi)
	incl	%esi
L603:
	movl	%ebx, (%esp)
	movl	$LC96, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L604
	orl	$15, _map_control
	jmp	L600
L604:
	movl	%ebx, (%esp)
	movl	$LC97, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L606
	orl	$3, _map_control
	jmp	L600
L606:
	movl	%ebx, (%esp)
	movl	$LC98, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L628
	movl	%ebx, (%esp)
	movl	$LC99, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L610
L628:
	orl	$7, _map_control
	jmp	L600
L610:
	movl	%ebx, (%esp)
	movl	$LC100, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L612
	orl	$8, _map_control
	jmp	L600
L612:
	cmpl	$0, _rf
	jne	L614
	movl	%ebx, (%esp)
	movl	$LC101, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L615
	movl	_stdout, %eax
	jmp	L627
L615:
	movl	%ebx, (%esp)
	movl	$LC102, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L617
	movl	_stderr, %eax
L627:
	movl	%eax, _rf
	jmp	L600
L617:
	movl	%ebx, (%esp)
	movl	$LC103, 4(%esp)
	call	_fopen
	movl	%eax, _rf
	testl	%eax, %eax
	jne	L600
	movl	$0, (%esp)
	movl	$LC104, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_error
	movl	$0, _map_control
	jmp	L623
L614:
	movl	$0, (%esp)
	movl	$LC105, 4(%esp)
	call	*_error
L600:
	cmpb	$0, (%esi)
	jne	L621
L625:
	cmpl	$0, _map_control
	jne	L622
	movl	$3, _map_control
L622:
	cmpl	$0, _rf
	jne	L623
	movl	_stdout, %eax
	movl	%eax, _rf
L623:
	movl	$1, %eax
	jmp	L589
L597:
	movl	$0, %eax
L589:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC106:
	.ascii "\0"
	.align 2
	.def	_bin_filename;	.scl	3;	.type	32;	.endef
_bin_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	$LC106, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_standard_extension
	movl	%ebx, _infile
	movl	%esi, _outfile
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_bin_segbase;	.scl	3;	.type	32;	.endef
_bin_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.align 2
	.def	_bin_set_info;	.scl	3;	.type	32;	.endef
_bin_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.align 2
	.def	_bin_init;	.scl	3;	.type	32;	.endef
_bin_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	%eax, _fp
	movl	12(%ebp), %eax
	movl	%eax, _error
	movl	$0, _relocs
	movl	$_relocs, _reloctail
	movl	$0, _origin_defined
	movl	$0, _no_seg_labels
	movl	$_no_seg_labels, _nsl_tail
	movb	$1, _format_mode
	movl	$64, (%esp)
	call	_nasm_malloc
	movl	%eax, _last_section
	movl	%eax, _sections
	movl	$0, 60(%eax)
	movl	_last_section, %ebx
	movl	$LC69, (%esp)
	call	_nasm_strdup
	movl	%eax, (%ebx)
	movl	_last_section, %ebx
	movl	$1, (%esp)
	call	_saa_init
	movl	%eax, 4(%ebx)
	movl	_last_section, %eax
	movl	$0, 36(%eax)
	movl	$0, 32(%eax)
	movl	_last_section, %eax
	movl	$0, 56(%eax)
	movl	_last_section, %eax
	movl	$0, 8(%eax)
	movl	_last_section, %eax
	movl	$192, 12(%eax)
	movl	_last_section, %eax
	movl	$0, 48(%eax)
	movl	_last_section, %edx
	leal	48(%edx), %eax
	movl	%eax, 52(%edx)
	movl	_last_section, %ebx
	call	_seg_alloc
	movl	%eax, 40(%ebx)
	movl	_last_section, %ebx
	call	_seg_alloc
	movl	%eax, _current_section
	movl	%eax, 44(%ebx)
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _of_bin
	.align 32
LC107:
	.ascii "flat-form binary files (e.g. DOS .COM, .SYS)\0"
LC108:
	.ascii "bin\0"
	.data
	.align 32
_of_bin:
	.long	LC107
	.long	LC108
	.long	0
	.long	_null_debug_arr
	.long	_null_debug_form
	.long	_bin_stdmac
	.long	_bin_init
	.long	_bin_set_info
	.long	_bin_out
	.long	_bin_deflabel
	.long	_bin_secname
	.long	_bin_segbase
	.long	_bin_directive
	.long	_bin_filename
	.long	_bin_cleanup
	.text
	.align 2
.globl _bin_get_ofmt
	.def	_bin_get_ofmt;	.scl	2;	.type	32;	.endef
_bin_get_ofmt:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$_of_bin, %eax
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _fp,16
.lcomm _error,16
.lcomm _no_seg_labels,16
.lcomm _nsl_tail,16
.lcomm _sections,16
.lcomm _last_section,16
.lcomm _relocs,16
.lcomm _reloctail,16
.lcomm _format_mode,16
.lcomm _current_section,16
.lcomm _origin,16
.lcomm _origin_defined,16
.lcomm _infile,16
.lcomm _outfile,16
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_strspn;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_bin_get_ofmt;	.scl	2;	.type	32;	.endef
	.def	_define_label;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_really_simple;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_evaluate;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_saa_wbytes;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_lookup_label;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_saa_fpwrite;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_saa_fwrite;	.scl	2;	.type	32;	.endef
	.def	_saa_fread;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
