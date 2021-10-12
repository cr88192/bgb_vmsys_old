	.file	"outobj.c"
	.text
	.align 2
	.def	_obj_clear;	.scl	3;	.type	32;	.endef
_obj_clear:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	movl	$0, 8(%eax)
	movl	$0, 12(%eax)
	movl	$0, 20(%eax)
	movl	$0, 24(%eax)
	movl	$0, 28(%eax)
	popl	%ebp
	ret
	.align 2
	.def	_obj_emit;	.scl	3;	.type	32;	.endef
_obj_emit:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	cmpl	$0, 28(%ebx)
	je	L3
	movl	28(%ebx), %eax
	movl	%eax, (%esp)
	call	_obj_emit
	movl	28(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L3:
	cmpl	$0, 8(%ebx)
	je	L4
	movl	%ebx, (%esp)
	call	_obj_fwrite
L4:
	cmpl	$0, 20(%ebx)
	je	L5
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_obj_emit
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L5:
	movl	%ebx, (%esp)
	call	_obj_clear
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_emit2;	.scl	3;	.type	32;	.endef
_obj_emit2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_obj_commit
	movl	%ebx, (%esp)
	call	_obj_emit
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_new;	.scl	3;	.type	32;	.endef
_obj_new:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$1068, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esp)
	call	_obj_clear
	movl	$_ori_null, (%eax)
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_bump;	.scl	3;	.type	32;	.endef
_obj_bump:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	4(%edi), %eax
	movl	%eax, -16(%ebp)
	movl	8(%edi), %edx
	movl	%edx, -20(%ebp)
	cmpl	$0, 24(%edi)
	je	L9
	movl	24(%edi), %ebx
	call	_obj_new
	movl	%eax, %esi
	movl	%eax, (%ebx)
	movl	(%edi), %eax
	movl	%eax, (%esi)
	movl	16(%edi), %eax
	movl	%eax, 16(%esi)
	movl	24(%edi), %eax
	movl	%eax, 24(%esi)
	movl	%edi, 28(%esi)
	leal	32(%esi), %eax
	movl	%eax, (%esp)
	leal	32(%edi), %eax
	movl	%eax, 4(%esp)
	movl	$12, 8(%esp)
	call	_memcpy
	jmp	L10
L9:
	movl	%edi, (%esp)
	call	_obj_emit
	movl	%eax, %esi
L10:
	movl	-20(%ebp), %eax
	subl	%eax, -16(%ebp)
	je	L11
	movl	$1, 8(%esi)
	movl	%esi, (%esp)
	call	*(%esi)
	movl	4(%esi), %eax
	movl	%eax, 8(%esi)
	leal	44(%eax,%esi), %eax
	movl	%eax, (%esp)
	movl	-20(%ebp), %edx
	leal	44(%edx,%edi), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_memcpy
	movl	-16(%ebp), %eax
	addl	8(%esi), %eax
	movl	%eax, 4(%esi)
L11:
	movl	%esi, %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_check;	.scl	3;	.type	32;	.endef
_obj_check:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	4(%ebx), %eax
	addl	12(%ebp), %eax
	cmpl	$1021, %eax
	jle	L13
	movl	%ebx, (%esp)
	call	_obj_bump
	movl	%eax, %ebx
L13:
	cmpl	$0, 8(%ebx)
	jne	L14
	movl	$1, 8(%ebx)
	movl	%ebx, (%esp)
	call	*(%ebx)
	movl	4(%ebx), %eax
	movl	%eax, 8(%ebx)
L14:
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_commit;	.scl	3;	.type	32;	.endef
_obj_commit:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	%edx, 8(%eax)
	popl	%ebp
	ret
	.align 2
	.def	_obj_byte;	.scl	3;	.type	32;	.endef
_obj_byte:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	%edx, (%esp)
	movl	$1, 4(%esp)
	call	_obj_check
	movl	%eax, %edx
	movl	4(%eax), %eax
	movb	%bl, 44(%edx,%eax)
	incl	%eax
	movl	%eax, 4(%edx)
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_word;	.scl	3;	.type	32;	.endef
_obj_word:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	%edx, (%esp)
	movl	$2, 4(%esp)
	call	_obj_check
	movl	%eax, %edx
	movl	4(%eax), %eax
	movb	%bl, 44(%edx,%eax)
	shrl	$8, %ebx
	movb	%bl, 45(%edx,%eax)
	addl	$2, %eax
	movl	%eax, 4(%edx)
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_rword;	.scl	3;	.type	32;	.endef
_obj_rword:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx
	movl	%ecx, (%esp)
	movl	$2, 4(%esp)
	call	_obj_check
	movl	%eax, %ecx
	movl	4(%eax), %eax
	movl	%ebx, %edx
	shrl	$8, %edx
	movb	%dl, 44(%ecx,%eax)
	movb	%bl, 45(%ecx,%eax)
	addl	$2, %eax
	movl	%eax, 4(%ecx)
	movl	%ecx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_dword;	.scl	3;	.type	32;	.endef
_obj_dword:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx
	movl	%ecx, (%esp)
	movl	$4, 4(%esp)
	call	_obj_check
	movl	%eax, %ecx
	movl	4(%eax), %eax
	movb	%bl, 44(%ecx,%eax)
	movl	%ebx, %edx
	shrl	$8, %edx
	movb	%dl, 45(%ecx,%eax)
	movl	%ebx, %edx
	shrl	$16, %edx
	movb	%dl, 46(%ecx,%eax)
	shrl	$24, %ebx
	movb	%bl, 47(%ecx,%eax)
	addl	$4, %eax
	movl	%eax, 4(%ecx)
	movl	%ecx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_force;	.scl	3;	.type	32;	.endef
_obj_force:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	%ebx, %eax
	xorl	$48, %eax
	cmpl	%eax, 12(%edx)
	jne	L21
	movl	%edx, (%esp)
	call	_obj_bump
	movl	%eax, %edx
L21:
	movl	%ebx, 12(%edx)
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_x;	.scl	3;	.type	32;	.endef
_obj_x:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	testb	$1, 16(%eax)
	je	L23
	movl	$32, 12(%eax)
L23:
	cmpl	$65535, %ebx
	jbe	L24
	movl	%eax, (%esp)
	movl	$32, 4(%esp)
	call	_obj_force
L24:
	cmpl	$32, 12(%eax)
	jne	L25
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_obj_dword
	jmp	L22
L25:
	movl	$16, 12(%eax)
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_obj_word
L22:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_index;	.scl	3;	.type	32;	.endef
_obj_index:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	cmpl	$127, %edx
	ja	L27
	movl	%eax, (%esp)
	movzbl	%dl, %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	jmp	L26
L27:
	movl	%eax, (%esp)
	movl	%edx, %eax
	shrl	$8, %eax
	sall	$8, %edx
	orl	%edx, %eax
	orl	$128, %eax
	movl	%eax, 4(%esp)
	call	_obj_word
L26:
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_value;	.scl	3;	.type	32;	.endef
_obj_value:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	cmpl	$128, %ebx
	ja	L29
	movl	%eax, (%esp)
	movzbl	%bl, %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	jmp	L28
L29:
	cmpl	$65535, %ebx
	ja	L30
	movl	%eax, (%esp)
	movl	$129, 4(%esp)
	call	_obj_byte
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_obj_word
	jmp	L28
L30:
	cmpl	$16777215, %ebx
	ja	L31
	movl	%eax, (%esp)
	movl	%ebx, %eax
	sall	$8, %eax
	addl	$132, %eax
	movl	%eax, 4(%esp)
	jmp	L32
L31:
	movl	%eax, (%esp)
	movl	$136, 4(%esp)
	call	_obj_byte
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
L32:
	call	_obj_dword
L28:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_obj_name;	.scl	3;	.type	32;	.endef
_obj_name:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %edi
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	leal	1(%eax), %eax
	movl	%eax, 4(%esp)
	call	_obj_check
	movl	%eax, 8(%ebp)
	movl	%eax, %esi
	addl	4(%eax), %esi
	addl	$44, %esi
	movl	%edi, %eax
	movb	%al, (%esi)
	incl	%esi
	movl	%edi, %eax
	movl	8(%ebp), %edx
	addl	4(%edx), %eax
	incl	%eax
	movl	%eax, 4(%edx)
	cmpl	$0, _obj_uppercase
	je	L34
	decl	%edi
	js	L39
L38:
	movl	12(%ebp), %edx
	movsbl	(%edx),%eax
	movl	%eax, (%esp)
	movl	%esi, %ebx
	incl	%esi
	call	_toupper
	movb	%al, (%ebx)
	incl	12(%ebp)
	decl	%edi
	js	L39
	jmp	L38
L34:
	movl	%esi, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, 8(%esp)
	call	_memcpy
L39:
	movl	8(%ebp), %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_ori_ledata;	.scl	3;	.type	32;	.endef
_ori_ledata:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	36(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	32(%ebx), %eax
	movl	%eax, 40(%ebx)
	movl	%ebx, (%esp)
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ori_pubdef;	.scl	3;	.type	32;	.endef
_ori_pubdef:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	32(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%ebx, (%esp)
	movl	36(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	32(%ebx), %eax
	orl	36(%ebx), %eax
	jne	L42
	movl	%ebx, (%esp)
	movl	40(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
L42:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ori_linnum;	.scl	3;	.type	32;	.endef
_ori_linnum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	32(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%ebx, (%esp)
	movl	36(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ori_local;	.scl	3;	.type	32;	.endef
_ori_local:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%ebx, (%esp)
	movl	$230, 4(%esp)
	call	_obj_byte
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_ori_null;	.scl	3;	.type	32;	.endef
_ori_null:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.def	_obj_init;	.scl	3;	.type	32;	.endef
_obj_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	movl	%ebx, _ofp
	movl	%esi, _error
	movl	20(%ebp), %eax
	movl	%eax, _evaluate
	movl	16(%ebp), %eax
	movl	%eax, _deflabel
	call	_seg_alloc
	movl	%eax, _first_seg
	movl	$0, _any_segs
	movl	$0, _fpubhead
	movl	$_fpubhead, _fpubtail
	movl	$0, _exthead
	movl	$_exthead, _exttail
	movl	$0, _imphead
	movl	$_imphead, _imptail
	movl	$0, _exphead
	movl	$_exphead, _exptail
	movl	$0, _dws
	movl	$0, _externals
	movl	$0, _ebhead
	movl	$_ebhead, _ebtail
	movl	$0, _obj_seg_needs_update
	movl	$0, _seghead
	movl	$_seghead, _segtail
	movl	$0, _obj_grp_needs_update
	movl	$0, _grphead
	movl	$_grphead, _grptail
	movl	$-1, _obj_entry_seg
	movl	$0, _obj_uppercase
	movl	$0, _obj_use32
	movl	$0, _passtwo
	movl	$0, _current_seg
	movl	$_of_obj, (%esp)
	movl	$0, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	%esi, 12(%esp)
	movl	_of_obj+16, %eax
	call	*8(%eax)
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_obj_set_info;	.scl	3;	.type	32;	.endef
_obj_set_info:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.align 2
	.def	_obj_cleanup;	.scl	3;	.type	32;	.endef
_obj_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_obj_write_file
	movl	_of_obj+16, %eax
	call	*32(%eax)
	movl	_ofp, %eax
	movl	%eax, (%esp)
	call	_fclose
	cmpl	$0, _seghead
	je	L83
L57:
	movl	_seghead, %esi
	movl	(%esi), %eax
	movl	%eax, _seghead
	cmpl	$0, 32(%esi)
	je	L85
L56:
	movl	32(%esi), %ebx
	movl	(%ebx), %eax
	movl	%eax, 32(%esi)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, 32(%esi)
	jne	L56
L85:
	movl	52(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	56(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%esi, (%esp)
	call	_nasm_free
	cmpl	$0, _seghead
	jne	L57
L83:
	cmpl	$0, _fpubhead
	je	L87
L61:
	movl	_fpubhead, %ebx
	movl	(%ebx), %eax
	movl	%eax, _fpubhead
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _fpubhead
	jne	L61
L87:
	cmpl	$0, _exthead
	je	L89
L65:
	movl	_exthead, %edx
	movl	(%edx), %eax
	movl	%eax, _exthead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _exthead
	jne	L65
L89:
	cmpl	$0, _imphead
	je	L91
L69:
	movl	_imphead, %ebx
	movl	(%ebx), %eax
	movl	%eax, _imphead
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	16(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _imphead
	jne	L69
L91:
	cmpl	$0, _exphead
	je	L93
L73:
	movl	_exphead, %ebx
	movl	(%ebx), %eax
	movl	%eax, _exphead
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _exphead
	jne	L73
L93:
	cmpl	$0, _ebhead
	je	L95
L77:
	movl	_ebhead, %edx
	movl	(%edx), %eax
	movl	%eax, _ebhead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _ebhead
	jne	L77
L95:
	cmpl	$0, _grphead
	je	L97
L81:
	movl	_grphead, %edx
	movl	(%edx), %eax
	movl	%eax, _grphead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _grphead
	jne	L81
L97:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.def	_obj_ext_set_defwrt;	.scl	3;	.type	32;	.endef
_obj_ext_set_defwrt:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	_seghead, %ebx
	testl	%ebx, %ebx
	je	L112
L104:
	movl	48(%ebx), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L101
	movl	$2, 20(%edi)
	jmp	L115
L101:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L104
L112:
	movl	_grphead, %ebx
	testl	%ebx, %ebx
	je	L114
L110:
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L107
	movl	$3, 20(%edi)
L115:
	movl	%ebx, 24(%edi)
	movl	%esi, (%esp)
	call	_nasm_free
	jmp	L98
L107:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L110
L114:
	movl	$1, 20(%edi)
	movl	%esi, 24(%edi)
	movl	_dws, %eax
	movl	%eax, 28(%edi)
	movl	%edi, _dws
L98:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC0:
	.ascii "..start\0"
	.align 32
LC1:
	.ascii "unrecognised special symbol `%s'\0"
LC3:
	.ascii "__NASMDEFSEG\0"
	.align 32
LC4:
	.ascii "strange segment conditions in OBJ driver\0"
LC5:
	.ascii "wrt\0"
LC6:
	.ascii " \11\0"
LC7:
	.ascii ":\0"
	.align 32
LC8:
	.ascii "`:' expected in special symbol text for `%s'\0"
LC9:
	.ascii "far\0"
	.align 32
LC10:
	.ascii "`%s': `far' keyword may only be applied to common variables\12\0"
LC11:
	.ascii "near\0"
	.align 32
LC12:
	.ascii "cannot use relocatable expression as common-variable element size\0"
	.align 32
LC13:
	.ascii "`%s': element-size specifications only apply to common variables\0"
	.align 32
LC2:
	.ascii "OBJ supports no special symbol features for this symbol type\0"
	.align 2
	.def	_obj_deflabel;	.scl	3;	.type	32;	.endef
_obj_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$104, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	20(%ebp), %ebx
	movl	$0, -52(%ebp)
	cmpl	$3, %ebx
	je	L116
	cmpb	$46, (%edi)
	jne	L118
	cmpb	$46, 1(%edi)
	jne	L118
	cmpb	$64, 2(%edi)
	je	L118
	movl	%edi, (%esp)
	movl	$LC0, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L119
	movl	12(%ebp), %eax
	movl	%eax, _obj_entry_seg
	movl	16(%ebp), %edx
	movl	%edx, _obj_entry_ofs
	jmp	L116
L119:
	movl	$1, (%esp)
	movl	$LC1, 4(%esp)
	movl	%edi, 8(%esp)
	call	*_error
L118:
	cmpl	$0, _obj_seg_needs_update
	je	L120
	movl	_obj_seg_needs_update, %eax
	movl	%edi, 48(%eax)
	jmp	L116
L120:
	cmpl	$0, _obj_grp_needs_update
	je	L121
	movl	_obj_grp_needs_update, %eax
	movl	%edi, 4(%eax)
	jmp	L116
L121:
	cmpl	$1073741823, 12(%ebp)
	jg	L125
	cmpl	$-1, 12(%ebp)
	je	L123
	testl	$1, 12(%ebp)
	jne	L116
L123:
	cmpl	$1073741823, 12(%ebp)
	jg	L125
	cmpl	$-1, 12(%ebp)
	jne	L124
L125:
	testl	%ebx, %ebx
	je	L195
	movl	_fpubtail, %esi
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, -56(%ebp)
	movl	%eax, (%esi)
	movl	-56(%ebp), %eax
	movl	%eax, _fpubtail
	movl	$0, (%eax)
	movl	%edi, (%esp)
	call	_nasm_strdup
	movl	-56(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	16(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	12(%ebp), %edx
	andl	$-1073741825, %edx
	cmpl	$-1, 12(%ebp)
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	andl	%eax, %edx
	movl	-56(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L195
L124:
	cmpl	$0, _any_segs
	jne	L130
	movl	12(%ebp), %edx
	cmpl	_first_seg, %edx
	jne	L130
	movl	$LC3, (%esp)
	movl	$2, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_obj_segment
	cmpl	%eax, 12(%ebp)
	je	L130
	movl	$3, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L130:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L133
	testl	%ebx, %ebx
	je	L116
L139:
	movl	12(%ebp), %eax
	cmpl	%eax, 4(%esi)
	jne	L134
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, -60(%ebp)
	movl	36(%esi), %eax
	movl	-60(%ebp), %edx
	movl	%edx, (%eax)
	movl	%edx, 36(%esi)
	movl	$0, (%edx)
	movl	%edi, (%esp)
	call	_nasm_strdup
	movl	-60(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	16(%ebp), %eax
	movl	%eax, 8(%edx)
L195:
	cmpl	$0, 24(%ebp)
	je	L116
	jmp	L194
L134:
	movl	(%esi), %esi
	testl	%esi, %esi
	je	L133
	testl	%ebx, %ebx
	jne	L139
	jmp	L116
L133:
	testl	%ebx, %ebx
	je	L116
	movl	_exttail, %esi
	movl	$32, (%esp)
	call	_nasm_malloc
	movl	%eax, (%esi)
	movl	%eax, -48(%ebp)
	movl	$0, (%eax)
	movl	-48(%ebp), %edx
	movl	%edx, _exttail
	movl	%edi, 4(%edx)
	movl	$0, 20(%edx)
	cmpl	$0, _current_seg
	je	L141
	movl	_current_seg, %eax
	cmpl	$0, 28(%eax)
	je	L141
	cmpl	$0, 12(%eax)
	je	L142
	movl	$3, 20(%edx)
	movl	_current_seg, %eax
	movl	12(%eax), %eax
	jmp	L192
L142:
	movl	-48(%ebp), %eax
	movl	$2, 20(%eax)
	movl	_current_seg, %eax
	movl	-48(%ebp), %edx
L192:
	movl	%eax, 24(%edx)
L141:
	cmpl	$2, %ebx
	jne	L144
	movl	16(%ebp), %edx
	movl	-48(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	$1, 12(%eax)
	jmp	L146
L144:
	movl	-48(%ebp), %eax
	movl	$0, 8(%eax)
L146:
	cmpl	$0, 24(%ebp)
	je	L148
	movl	24(%ebp), %edx
	cmpb	$0, (%edx)
	je	L148
	movl	$1, -52(%ebp)
L176:
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC5, 4(%esp)
	movl	$3, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L151
	addl	$3, 24(%ebp)
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC6, 4(%esp)
	call	_strspn
	addl	%eax, 24(%ebp)
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC7, 4(%esp)
	call	_strcspn
	movl	%eax, %esi
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	call	_nasm_strndup
	movl	-48(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	call	_obj_ext_set_defwrt
	addl	%esi, 24(%ebp)
	movl	24(%ebp), %eax
	cmpb	$0, (%eax)
	je	L152
	cmpb	$58, (%eax)
	je	L190
	movl	$1, (%esp)
	movl	$LC8, 4(%esp)
	movl	-48(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L151
L152:
	movl	24(%ebp), %eax
	cmpb	$58, (%eax)
	jne	L151
L190:
	incl	24(%ebp)
L151:
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC9, 4(%esp)
	movl	$3, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L155
	movl	-48(%ebp), %eax
	cmpl	$0, 8(%eax)
	je	L156
	movl	$1, 12(%eax)
	jmp	L157
L156:
	movl	$1, (%esp)
	movl	$LC10, 4(%esp)
	movl	-48(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
L157:
	addl	$3, 24(%ebp)
	jmp	L193
L155:
	movl	24(%ebp), %edx
	movl	%edx, (%esp)
	movl	$LC11, 4(%esp)
	movl	$4, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L158
	movl	-48(%ebp), %eax
	cmpl	$0, 8(%eax)
	je	L160
	movl	$0, 12(%eax)
	jmp	L161
L160:
	movl	$1, (%esp)
	movl	$LC10, 4(%esp)
	movl	-48(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
L161:
	addl	$4, 24(%ebp)
L193:
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC6, 4(%esp)
	call	_strspn
	addl	%eax, 24(%ebp)
L158:
	movl	24(%ebp), %edx
	cmpb	$58, (%edx)
	jne	L162
	incl	%edx
	movl	%edx, 24(%ebp)
	jmp	L147
L162:
	movl	24(%ebp), %eax
	cmpb	$0, (%eax)
	je	L147
	movl	-48(%ebp), %edx
	cmpl	$0, 8(%edx)
	je	L165
	call	_stdscan_reset
	movl	24(%ebp), %eax
	movl	%eax, _stdscan_bufptr
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
	call	*_evaluate
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L166
	movl	%eax, (%esp)
	call	_is_simple
	testl	%eax, %eax
	jne	L167
	movl	$1, (%esp)
	movl	$LC12, 4(%esp)
	call	*_error
	jmp	L166
L167:
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	-48(%ebp), %edx
	movl	%eax, 12(%edx)
L166:
	movl	_stdscan_bufptr, %eax
	movl	%eax, 24(%ebp)
	jmp	L147
L165:
	movl	$1, (%esp)
	movl	$LC13, 4(%esp)
	movl	-48(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	24(%ebp), %eax
	cmpb	$0, (%eax)
	je	L171
	cmpb	$58, (%eax)
	je	L191
L174:
	incl	24(%ebp)
	movl	24(%ebp), %edx
	cmpb	$0, (%edx)
	je	L171
	cmpb	$58, (%edx)
	jne	L174
	jmp	L191
L171:
	movl	24(%ebp), %eax
	cmpb	$58, (%eax)
	jne	L147
L191:
	incl	24(%ebp)
L147:
	cmpl	$0, 24(%ebp)
	je	L148
	movl	24(%ebp), %edx
	cmpb	$0, (%edx)
	jne	L176
L148:
	movl	12(%ebp), %eax
	shrl	$31, %eax
	addl	12(%ebp), %eax
	movl	%eax, %esi
	sarl	%esi
	movl	_ebhead, %eax
	testl	%eax, %eax
	jne	L177
	movl	_ebtail, %edi
	movl	$1028, (%esp)
	call	_nasm_malloc
	movl	%eax, (%edi)
	movl	$0, (%eax)
	movl	%eax, _ebtail
L177:
	cmpl	$255, %esi
	jle	L189
L183:
	testl	%eax, %eax
	je	L181
	cmpl	$0, (%eax)
	je	L181
	movl	(%eax), %eax
	jmp	L182
L181:
	movl	_ebtail, %edi
	movl	$1028, (%esp)
	call	_nasm_malloc
	movl	%eax, (%edi)
	movl	$0, (%eax)
	movl	%eax, _ebtail
L182:
	subl	$256, %esi
	cmpl	$255, %esi
	jg	L183
L189:
	movl	-48(%ebp), %edx
	movl	%edx, 4(%eax,%esi,4)
	movl	_externals, %eax
	incl	%eax
	movl	%eax, _externals
	movl	%eax, 16(%edx)
	cmpl	$0, 24(%ebp)
	je	L116
	cmpl	$0, -52(%ebp)
	jne	L116
L194:
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*_error
L116:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC14:
	.ascii "attempt to assemble code in [ABSOLUTE] space\0"
	.align 32
LC15:
	.ascii "code directed to nonexistent segment?\0"
	.align 32
LC16:
	.ascii "relative call to absolute address not supported by OBJ format\0"
	.align 32
LC17:
	.ascii "far-absolute relocations not supported by OBJ format\0"
	.align 32
LC18:
	.ascii "OBJ format cannot handle complex dword-size segment base references\0"
	.align 2
	.def	_obj_out;	.scl	3;	.type	32;	.endef
_obj_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %ebx
	cmpl	$-1, %ebx
	jne	L197
	movl	16(%ebp), %eax
	andl	$-268435456, %eax
	cmpl	$1073741824, %eax
	je	L196
	movl	$1, (%esp)
	movl	$LC14, 4(%esp)
	call	*_error
	jmp	L196
L197:
	cmpl	$0, _any_segs
	jne	L199
	movl	$LC3, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_obj_segment
	cmpl	%eax, %ebx
	je	L199
	movl	$3, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L199:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L233
L206:
	cmpl	%ebx, 4(%esi)
	je	L202
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L206
	jmp	L233
L202:
	testl	%esi, %esi
	jne	L207
L233:
	movl	$3, (%esp)
	movl	$LC15, 4(%esp)
	call	*_error
L207:
	movl	60(%esi), %edi
	movl	16(%esi), %eax
	movl	%eax, 32(%edi)
	movl	16(%ebp), %eax
	andl	$268435455, %eax
	movl	%eax, -20(%ebp)
	movl	16(%ebp), %ebx
	andl	$-268435456, %ebx
	jne	L208
	movl	12(%ebp), %edx
	movl	%edx, -24(%ebp)
	testl	%eax, %eax
	je	L214
L213:
	movl	60(%esi), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_obj_check
	movl	%eax, %edi
	movl	$1021, %ebx
	subl	4(%eax), %ebx
	cmpl	-20(%ebp), %ebx
	jbe	L212
	movl	-20(%ebp), %ebx
L212:
	movl	%edi, %eax
	addl	4(%edi), %eax
	addl	$44, %eax
	movl	%eax, (%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	call	_memcpy
	movl	%ebx, %eax
	addl	4(%edi), %eax
	movl	%eax, 4(%edi)
	movl	%eax, 8(%edi)
	movl	%ebx, %eax
	addl	16(%esi), %eax
	movl	%eax, 16(%esi)
	movl	%eax, 32(%edi)
	addl	%ebx, -24(%ebp)
	subl	%ebx, -20(%ebp)
	je	L214
	jmp	L213
L208:
	cmpl	$268435456, %ebx
	je	L216
	cmpl	$536870912, %ebx
	je	L216
	cmpl	$805306368, %ebx
	jne	L215
L216:
	cmpl	$-1, 20(%ebp)
	jne	L217
	cmpl	$268435456, %ebx
	je	L217
	movl	$1, (%esp)
	movl	$LC16, 4(%esp)
	call	*_error
L217:
	cmpl	$1073741823, 20(%ebp)
	jle	L218
	movl	$1, (%esp)
	movl	$LC17, 4(%esp)
	call	*_error
L218:
	movl	12(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, -28(%ebp)
	cmpl	$536870912, %ebx
	jne	L219
	movl	-20(%ebp), %eax
	leal	-2(%eax,%edx), %edx
	movl	%edx, -28(%ebp)
	movl	$2, -20(%ebp)
L219:
	cmpl	$805306368, %ebx
	jne	L220
	movl	-28(%ebp), %edx
	movl	-20(%ebp), %eax
	leal	-4(%eax,%edx), %edx
	movl	%edx, -28(%ebp)
	movl	$4, -20(%ebp)
L220:
	cmpl	$2, -20(%ebp)
	jne	L221
	movl	%edi, (%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 4(%esp)
	call	_obj_word
	jmp	L234
L221:
	movl	%edi, (%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_obj_dword
L234:
	movl	%eax, %edi
	movl	-20(%ebp), %edx
	movl	%edx, -32(%ebp)
	cmpl	$1073741823, 20(%ebp)
	jg	L223
	cmpl	$-1, 20(%ebp)
	je	L225
	testl	$1, 20(%ebp)
	je	L223
	cmpl	$4, %edx
	jne	L223
	movl	$2, -32(%ebp)
	cmpw	$0, -28(%ebp)
	je	L223
	movl	$1, (%esp)
	movl	$LC18, 4(%esp)
	call	*_error
L223:
	cmpl	$-1, 20(%ebp)
	je	L225
	movl	%edi, (%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	cmpl	$268435456, %ebx
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	andl	$-16384, %eax
	addl	$16384, %eax
	movl	%eax, 8(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	%esi, 20(%esp)
	call	_obj_write_fixup
L225:
	movl	-20(%ebp), %eax
	addl	%eax, 16(%esi)
	jmp	L214
L215:
	cmpl	$1073741824, %ebx
	jne	L214
	cmpl	$0, 8(%edi)
	je	L230
	movl	%edi, (%esp)
	call	_obj_bump
	movl	%eax, %edi
L230:
	movl	-20(%ebp), %edx
	addl	%edx, 16(%esi)
L214:
	movl	%edi, (%esp)
	call	_obj_commit
L196:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC19:
	.ascii "`obj' output driver does not support one-byte relocations\0"
	.align 32
LC20:
	.ascii "OBJ: 4-byte segment base fixup got through sanity check\0"
	.align 32
LC21:
	.ascii "unrecognised segment value in obj_write_fixup\0"
	.align 32
LC22:
	.ascii "default WRT specification for external `%s' unresolved\0"
	.align 32
LC23:
	.ascii "unrecognised WRT value in obj_write_fixup\0"
	.align 2
	.def	_obj_write_fixup;	.scl	3;	.type	32;	.endef
_obj_write_fixup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	20(%ebp), %esi
	movl	$0, -32(%ebp)
	cmpl	$1, 12(%ebp)
	jne	L236
	movl	$1, (%esp)
	movl	$LC19, 4(%esp)
	call	*_error
	jmp	L235
L236:
	movl	8(%ebp), %eax
	movl	20(%eax), %edi
	testl	%edi, %edi
	jne	L237
	call	_obj_new
	movl	%eax, %edi
	movl	8(%ebp), %edx
	movl	%eax, 20(%edx)
	movl	%edx, %eax
	addl	$20, %eax
	movl	%eax, 24(%edi)
	movl	28(%ebp), %eax
	cmpl	$0, 28(%eax)
	je	L238
	movl	$157, 16(%edi)
	jmp	L237
L238:
	movl	$156, 16(%edi)
L237:
	testl	$1, %esi
	je	L240
	movl	$1, -20(%ebp)
	movl	$34816, %ebx
	decl	%esi
	cmpl	$2, 12(%ebp)
	je	L242
	movl	$3, (%esp)
	movl	$LC20, 4(%esp)
	call	*_error
	jmp	L242
L240:
	movl	$0, -20(%ebp)
	cmpl	$2, 12(%ebp)
	setne	%al
	movzbl	%al, %ebx
	decl	%ebx
	andl	$-8192, %ebx
	addl	$41984, %ebx
	cmpl	$0, 16(%ebp)
	jne	L242
	movl	%edi, (%esp)
	movl	12(%ebp), %eax
	sall	$3, %eax
	movl	%eax, 4(%esp)
	call	_obj_force
	movl	%eax, %edi
L242:
	movl	%edi, (%esp)
	movl	16(%ebp), %edx
	orl	%ebx, %edx
	movl	8(%ebp), %ecx
	movl	32(%ecx), %eax
	subl	40(%ecx), %eax
	orl	%eax, %edx
	movl	%edx, 4(%esp)
	call	_obj_rword
	movl	%eax, %edi
	movl	$-1, -28(%ebp)
	movl	$-1, -24(%ebp)
	movl	$0, -16(%ebp)
	movl	_seghead, %ebx
	testl	%ebx, %ebx
	je	L252
L251:
	cmpl	%esi, 4(%ebx)
	je	L247
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L251
	jmp	L252
L247:
	testl	%ebx, %ebx
	je	L252
	movl	$4, -16(%ebp)
	movl	8(%ebx), %eax
	jmp	L313
L252:
	movl	_grphead, %eax
	testl	%eax, %eax
	je	L260
L259:
	cmpl	%esi, 8(%eax)
	je	L255
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	L259
	jmp	L260
L255:
	testl	%eax, %eax
	je	L260
	movl	$5, -16(%ebp)
	movl	12(%eax), %eax
L313:
	movl	%eax, -24(%ebp)
	jmp	L253
L260:
	movl	%esi, %eax
	shrl	$31, %eax
	leal	(%eax,%esi), %eax
	sarl	%eax
	movl	_ebhead, %edx
	cmpl	$256, %eax
	jle	L263
L267:
	testl	%edx, %edx
	je	L268
	movl	(%edx), %edx
	subl	$256, %eax
	cmpl	$256, %eax
	jg	L267
L263:
	testl	%edx, %edx
	je	L268
	movl	$6, -16(%ebp)
	movl	4(%edx,%eax,4), %eax
	movl	%eax, -32(%ebp)
	movl	16(%eax), %edx
	movl	%edx, -24(%ebp)
	jmp	L253
L268:
	movl	$3, (%esp)
	movl	$LC21, 4(%esp)
	call	*_error
L253:
	cmpl	$-1, 24(%ebp)
	jne	L270
	cmpl	$0, -20(%ebp)
	jne	L273
	testl	%ebx, %ebx
	je	L271
	cmpl	$0, 12(%ebx)
	je	L271
	orl	$16, -16(%ebp)
	movl	12(%ebx), %eax
	jmp	L316
L271:
	cmpl	$0, -20(%ebp)
	jne	L273
	cmpl	$0, -32(%ebp)
	je	L273
	movl	-32(%ebp), %ecx
	cmpl	$0, 20(%ecx)
	je	L273
	cmpl	$2, 20(%ecx)
	jne	L274
	movl	24(%ecx), %eax
	movl	8(%eax), %eax
	jmp	L314
L274:
	movl	-32(%ebp), %eax
	cmpl	$3, 20(%eax)
	jne	L276
	orl	$16, -16(%ebp)
	movl	24(%eax), %eax
	jmp	L316
L276:
	movl	$1, (%esp)
	movl	$LC22, 4(%esp)
	movl	-32(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	*_error
L273:
	orl	$80, -16(%ebp)
	movl	$-1, -28(%ebp)
	jmp	L279
L270:
	movl	_seghead, %ebx
	testl	%ebx, %ebx
	je	L286
	movl	24(%ebp), %eax
	decl	%eax
L285:
	cmpl	%eax, 4(%ebx)
	je	L281
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L285
	jmp	L286
L281:
	testl	%ebx, %ebx
	je	L286
	movl	8(%ebx), %ebx
	movl	%ebx, -28(%ebp)
	jmp	L279
L286:
	movl	_grphead, %eax
	testl	%eax, %eax
	je	L294
	movl	24(%ebp), %edx
	decl	%edx
L293:
	cmpl	%edx, 8(%eax)
	je	L289
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	L293
	jmp	L294
L289:
	testl	%eax, %eax
	je	L294
	orl	$16, -16(%ebp)
L316:
	movl	12(%eax), %eax
	jmp	L314
L294:
	movl	24(%ebp), %eax
	shrl	$31, %eax
	addl	24(%ebp), %eax
	movl	%eax, %edx
	sarl	%edx
	movl	_ebhead, %eax
	cmpl	$256, %edx
	jle	L297
L301:
	testl	%eax, %eax
	je	L302
	movl	(%eax), %eax
	subl	$256, %edx
	cmpl	$256, %edx
	jg	L301
L297:
	testl	%eax, %eax
	je	L302
	orl	$32, -16(%ebp)
	movl	4(%eax,%edx,4), %eax
	movl	16(%eax), %eax
L314:
	movl	%eax, -28(%ebp)
	jmp	L279
L302:
	movl	$3, (%esp)
	movl	$LC23, 4(%esp)
	call	*_error
L279:
	movl	%edi, (%esp)
	movzbl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	movl	%eax, %edi
	cmpl	$-1, -28(%ebp)
	je	L304
	movl	%eax, (%esp)
	movl	-28(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_obj_index
	movl	%eax, %edi
L304:
	movl	%edi, (%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%eax, (%esp)
	call	_obj_commit
L235:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC24:
	.ascii "segment attributes specified on redeclaration of segment: ignoring\0"
LC25:
	.ascii "private\0"
LC26:
	.ascii "public\0"
LC27:
	.ascii "common\0"
LC28:
	.ascii "stack\0"
LC29:
	.ascii "use16\0"
LC30:
	.ascii "use32\0"
LC31:
	.ascii "flat\0"
LC32:
	.ascii "FLAT\0"
LC33:
	.ascii "group\0"
LC34:
	.ascii "failure to define FLAT?!\0"
LC35:
	.ascii "class=\0"
LC36:
	.ascii "overlay=\0"
LC37:
	.ascii "align=\0"
	.align 32
LC38:
	.ascii "segment alignment should be numeric\0"
	.align 32
LC39:
	.ascii "OBJ format does not support alignment of 8: rounding up to 16\0"
	.align 32
LC40:
	.ascii "OBJ format does not support alignment of %d: rounding up to 256\0"
	.align 32
LC41:
	.ascii "OBJ format does not support alignment of %d: rounding up to 4096\0"
LC42:
	.ascii "invalid alignment value %d\0"
LC43:
	.ascii "absolute=\0"
	.align 32
LC44:
	.ascii "argument to `absolute' segment attribute should be numeric\0"
	.align 32
LC45:
	.ascii "segment `%s' is already part of a group: first one takes precedence\0"
	.align 2
	.def	_obj_segment;	.scl	3;	.type	32;	.endef
_obj_segment:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	cmpl	$0, 8(%ebp)
	jne	L318
	movl	16(%ebp), %eax
	movl	$16, (%eax)
	movl	$0, _current_seg
	movl	_first_seg, %eax
	jmp	L317
L318:
	movl	$0, -20(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L451
L323:
	incl	8(%ebp)
	movl	8(%ebp), %eax
	cmpb	$46, (%eax)
	je	L323
L451:
	movl	8(%ebp), %ebx
	jmp	L324
L328:
	incl	%ebx
L324:
	cmpb	$0, (%ebx)
	je	L453
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L328
	cmpb	$0, (%ebx)
	je	L453
L334:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L453
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L334
	cmpb	$0, (%ebx)
	je	L453
	jmp	L470
L342:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L343
L470:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L342
	cmpb	$0, (%ebx)
	je	L343
L348:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L343
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L348
L343:
	incl	-20(%ebp)
	cmpb	$0, (%ebx)
	jne	L470
L453:
	movl	$1, %esi
	movl	_seghead, %edi
	testl	%edi, %edi
	je	L455
L358:
	incl	%esi
	movl	48(%edi), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L352
	cmpl	$0, -20(%ebp)
	jle	L467
	cmpl	$1, 12(%ebp)
	jne	L467
	movl	$0, (%esp)
	movl	$LC24, 4(%esp)
	call	*_error
	jmp	L467
L352:
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L358
L455:
	movl	_segtail, %ebx
	movl	$64, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	movl	%eax, (%ebx)
	movl	$0, (%eax)
	movl	%eax, _segtail
	cmpl	$0, _any_segs
	je	L359
	call	_seg_alloc
	jmp	L360
L359:
	movl	_first_seg, %eax
L360:
	movl	%eax, 4(%edi)
	movl	%esi, 8(%edi)
	movl	$0, 12(%edi)
	movl	$1, _any_segs
	movl	$0, 48(%edi)
	movl	$0, 16(%edi)
	movl	$1, 20(%edi)
	movl	$0, 28(%edi)
	movl	$2, 24(%edi)
	movl	$0, 56(%edi)
	movl	$0, 52(%edi)
	movl	$0, 32(%edi)
	leal	32(%edi), %eax
	movl	%eax, 36(%edi)
	movl	$0, 40(%edi)
	leal	40(%edi), %eax
	movl	%eax, 44(%edi)
	call	_obj_new
	movl	%eax, 60(%edi)
	leal	60(%edi), %edx
	movl	%edx, 24(%eax)
	movl	60(%edi), %eax
	movl	$_ori_ledata, (%eax)
	movl	60(%edi), %eax
	movl	$160, 16(%eax)
	movl	60(%edi), %eax
	movl	%esi, 36(%eax)
	movl	8(%ebp), %ebx
	decl	-20(%ebp)
	cmpl	$-1, -20(%ebp)
	je	L457
L426:
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
	cmpb	$0, (%ebx)
	jne	L459
L367:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L367
L459:
	movl	%ebx, (%esp)
	movl	$LC25, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L368
	movl	$0, 24(%edi)
	jmp	L361
L368:
	movl	%ebx, (%esp)
	movl	$LC26, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L370
	movl	$2, 24(%edi)
	jmp	L361
L370:
	movl	%ebx, (%esp)
	movl	$LC27, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L372
	movl	$6, 24(%edi)
	jmp	L361
L372:
	movl	%ebx, (%esp)
	movl	$LC28, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L374
	movl	$5, 24(%edi)
	jmp	L361
L374:
	movl	%ebx, (%esp)
	movl	$LC29, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L376
	movl	$0, 28(%edi)
	jmp	L361
L376:
	movl	%ebx, (%esp)
	movl	$LC30, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L378
	movl	$1, 28(%edi)
	jmp	L361
L378:
	movl	%ebx, (%esp)
	movl	$LC31, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L380
	movl	_grphead, %esi
	testl	%esi, %esi
	je	L468
L386:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L382
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L386
	jmp	L468
L382:
	testl	%esi, %esi
	jne	L387
L468:
	movl	$LC33, (%esp)
	movl	$LC32, 4(%esp)
	movl	$1, 8(%esp)
	call	_obj_directive
	movl	_grphead, %esi
	testl	%esi, %esi
	je	L469
L393:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	movl	$LC32, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L389
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L393
	jmp	L469
L389:
	testl	%esi, %esi
	jne	L387
L469:
	movl	$3, (%esp)
	movl	$LC34, 4(%esp)
	call	*_error
L387:
	movl	%esi, 12(%edi)
	jmp	L361
L380:
	movl	%ebx, (%esp)
	movl	$LC35, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L396
	leal	6(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 52(%edi)
	jmp	L361
L396:
	movl	%ebx, (%esp)
	movl	$LC36, 4(%esp)
	movl	$8, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L398
	leal	8(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 56(%edi)
	jmp	L361
L398:
	movl	%ebx, (%esp)
	movl	$LC37, 4(%esp)
	movl	$6, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L400
	leal	6(%ebx), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 20(%edi)
	cmpl	$0, -16(%ebp)
	je	L401
	movl	$1, 20(%edi)
	movl	$1, (%esp)
	movl	$LC38, 4(%esp)
	call	*_error
L401:
	movl	20(%edi), %eax
	cmpl	$64, %eax
	je	L412
	cmpl	$64, %eax
	jg	L418
	cmpl	$4, %eax
	je	L361
	cmpl	$4, %eax
	jg	L419
	decl	%eax
	cmpl	$1, %eax
	ja	L416
	jmp	L361
L419:
	cmpl	$16, %eax
	je	L361
	cmpl	$16, %eax
	jg	L420
	cmpl	$8, %eax
	je	L409
	jmp	L416
L420:
	cmpl	$32, %eax
	je	L412
	jmp	L416
L418:
	cmpl	$512, %eax
	je	L415
	cmpl	$512, %eax
	jg	L421
	cmpl	$128, %eax
	je	L412
	cmpl	$256, %eax
	jmp	L471
L421:
	cmpl	$2048, %eax
	je	L415
	cmpl	$2048, %eax
	jg	L422
	cmpl	$1024, %eax
	je	L415
	jmp	L416
L422:
	cmpl	$4096, %eax
L471:
	je	L361
	jmp	L416
L409:
	movl	$0, (%esp)
	movl	$LC39, 4(%esp)
	call	*_error
	movl	$16, 20(%edi)
	jmp	L361
L412:
	movl	$0, (%esp)
	movl	$LC40, 4(%esp)
	movl	20(%edi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$256, 20(%edi)
	jmp	L361
L415:
	movl	$0, (%esp)
	movl	$LC41, 4(%esp)
	movl	20(%edi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$4096, 20(%edi)
	jmp	L361
L416:
	movl	$1, (%esp)
	movl	$LC42, 4(%esp)
	movl	20(%edi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	movl	$1, 20(%edi)
	jmp	L361
L400:
	movl	%ebx, (%esp)
	movl	$LC43, 4(%esp)
	movl	$9, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L361
	leal	9(%ebx), %eax
	movl	%eax, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	addl	$1073741824, %eax
	movl	%eax, 20(%edi)
	cmpl	$0, -16(%ebp)
	je	L361
	movl	$1, (%esp)
	movl	$LC44, 4(%esp)
	call	*_error
L361:
	decl	-20(%ebp)
	cmpl	$-1, -20(%ebp)
	jne	L426
L457:
	movl	_obj_use32, %eax
	orl	28(%edi), %eax
	movl	%eax, _obj_use32
	movl	%edi, _obj_seg_needs_update
	cmpl	$1073741823, 20(%edi)
	jle	L427
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, 4(%esp)
	movl	20(%edi), %eax
	subl	$1073741824, %eax
	movl	%eax, 8(%esp)
	jmp	L472
L427:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	4(%edi), %eax
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
L472:
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_obj, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*_deflabel
	movl	$0, _obj_seg_needs_update
	movl	_grphead, %ebx
	testl	%ebx, %ebx
	je	L463
L441:
	movl	20(%ebx), %esi
	cmpl	16(%ebx), %esi
	jge	L465
L440:
	movl	24(%ebx,%esi,4), %eax
	movl	%eax, (%esp)
	movl	48(%edi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L435
	movl	24(%ebx,%esi,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	20(%ebx), %edx
	movl	24(%ebx,%edx,4), %eax
	movl	%eax, 24(%ebx,%esi,4)
	movl	8(%edi), %eax
	movl	%eax, 24(%ebx,%edx,4)
	incl	20(%ebx)
	cmpl	$0, 12(%edi)
	je	L438
	movl	$0, (%esp)
	movl	$LC45, 4(%esp)
	movl	48(%edi), %eax
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L435
L438:
	movl	%ebx, 12(%edi)
L435:
	incl	%esi
	cmpl	16(%ebx), %esi
	jl	L440
L465:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L441
L463:
	movl	$_dws, %ebx
	cmpl	$0, _dws
	je	L467
L447:
	movl	(%ebx), %eax
	cmpl	$1, 20(%eax)
	jne	L445
	movl	24(%eax), %eax
	movl	%eax, (%esp)
	movl	48(%edi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L445
	movl	(%ebx), %eax
	movl	24(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%ebx), %eax
	movl	$2, 20(%eax)
	movl	(%ebx), %eax
	movl	%edi, 24(%eax)
	movl	(%ebx), %eax
	movl	28(%eax), %eax
	movl	%eax, (%ebx)
	jmp	L442
L445:
	movl	(%ebx), %ebx
	addl	$28, %ebx
L442:
	cmpl	$0, (%ebx)
	jne	L447
L467:
	cmpl	$0, 28(%edi)
	je	L448
	movl	16(%ebp), %eax
	movl	$32, (%eax)
	jmp	L449
L448:
	movl	16(%ebp), %eax
	movl	$16, (%eax)
L449:
	movl	%edi, _current_seg
	movl	4(%edi), %eax
L317:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC47:
	.ascii "uppercase\0"
LC48:
	.ascii "import\0"
	.align 32
LC49:
	.ascii "`import' directive requires symbol name and library name\0"
LC50:
	.ascii "export\0"
	.align 32
LC51:
	.ascii "`export' directive requires export name\0"
LC52:
	.ascii "\0"
LC53:
	.ascii "resident\0"
LC54:
	.ascii "nodata\0"
LC55:
	.ascii "parm=\0"
	.align 32
LC56:
	.ascii "value `%s' for `parm' is non-numeric\0"
LC46:
	.ascii "group `%s' defined twice\0"
	.align 32
LC57:
	.ascii "unrecognised export qualifier `%s'\0"
	.align 2
	.def	_obj_directive;	.scl	3;	.type	32;	.endef
_obj_directive:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edi
	movl	16(%ebp), %esi
	movl	%ebx, (%esp)
	movl	$LC33, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L475
	cmpl	$1, %esi
	jne	L622
	movl	%edi, %esi
	cmpb	$46, (%edi)
	jne	L610
L480:
	incl	%esi
	cmpb	$46, (%esi)
	je	L480
L610:
	movl	%esi, -32(%ebp)
	jmp	L481
L485:
	incl	%esi
L481:
	cmpb	$0, (%esi)
	je	L482
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L485
L482:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L486
	movb	$0, (%esi)
L491:
	incl	%esi
	cmpb	$0, (%esi)
	je	L486
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L491
L486:
	movl	$1, -36(%ebp)
	movl	_grphead, %edi
	testl	%edi, %edi
	je	L612
L497:
	incl	-36(%ebp)
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L619
	movl	(%edi), %edi
	testl	%edi, %edi
	jne	L497
L612:
	movl	_grptail, %ebx
	movl	$1048, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	movl	%eax, (%ebx)
	movl	$0, (%eax)
	movl	%eax, _grptail
	call	_seg_alloc
	movl	%eax, 8(%edi)
	movl	-36(%ebp), %eax
	movl	%eax, 12(%edi)
	movl	$0, 16(%edi)
	movl	$0, 20(%edi)
	movl	$0, 4(%edi)
	movl	%edi, _obj_grp_needs_update
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%edi), %eax
	incl	%eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	$_of_obj, 24(%esp)
	movl	_error, %eax
	movl	%eax, 28(%esp)
	call	*_deflabel
	movl	$0, _obj_grp_needs_update
	cmpb	$0, (%esi)
	je	L614
L522:
	movl	%esi, -28(%ebp)
	jmp	L501
L505:
	incl	%esi
L501:
	cmpb	$0, (%esi)
	je	L502
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L505
L502:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L506
	movb	$0, (%esi)
L511:
	incl	%esi
	cmpb	$0, (%esi)
	je	L506
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L511
L506:
	movl	_seghead, %ebx
	testl	%ebx, %ebx
	je	L518
L517:
	movl	48(%ebx), %eax
	movl	%eax, (%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L513
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L517
	jmp	L518
L513:
	testl	%ebx, %ebx
	je	L518
	movl	16(%edi), %eax
	movl	20(%edi), %ecx
	movl	24(%edi,%ecx,4), %edx
	movl	%edx, 24(%edi,%eax,4)
	incl	%eax
	movl	%eax, 16(%edi)
	movl	8(%ebx), %eax
	movl	%eax, 24(%edi,%ecx,4)
	incl	20(%edi)
	cmpl	$0, 12(%ebx)
	je	L519
	movl	$0, (%esp)
	movl	$LC45, 4(%esp)
	movl	48(%ebx), %eax
	movl	%eax, 8(%esp)
	call	*_error
	jmp	L498
L519:
	movl	%edi, 12(%ebx)
	jmp	L498
L518:
	movl	16(%edi), %ebx
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	incl	16(%edi)
	call	_nasm_strdup
	movl	%eax, 24(%edi,%ebx,4)
L498:
	cmpb	$0, (%esi)
	jne	L522
L614:
	movl	$_dws, %ebx
	cmpl	$0, _dws
	je	L622
L528:
	movl	(%ebx), %eax
	cmpl	$1, 20(%eax)
	jne	L526
	movl	24(%eax), %eax
	movl	%eax, (%esp)
	movl	4(%edi), %eax
	movl	%eax, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L526
	movl	(%ebx), %eax
	movl	24(%eax), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%ebx), %eax
	movl	$3, 20(%eax)
	movl	(%ebx), %eax
	movl	%edi, 24(%eax)
	movl	(%ebx), %eax
	movl	28(%eax), %eax
	movl	%eax, (%ebx)
	jmp	L523
L526:
	movl	(%ebx), %ebx
	addl	$28, %ebx
L523:
	cmpl	$0, (%ebx)
	jne	L528
	jmp	L622
L475:
	movl	%ebx, (%esp)
	movl	$LC47, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L529
	movl	$1, _obj_uppercase
	jmp	L622
L529:
	movl	%ebx, (%esp)
	movl	$LC48, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L530
	movl	$1, %eax
	movl	%edi, %ebx
	cmpl	$2, %esi
	jne	L532
	jmp	L474
L536:
	incl	%ebx
L532:
	cmpb	$0, (%ebx)
	je	L533
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L536
L533:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L537
	movb	$0, (%ebx)
L542:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L537
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L542
L537:
	movl	%ebx, -40(%ebp)
	jmp	L543
L547:
	incl	%ebx
L543:
	cmpb	$0, (%ebx)
	je	L544
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L547
L544:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L548
	movb	$0, (%ebx)
L553:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L548
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L553
L548:
	movl	%ebx, %esi
	cmpb	$0, (%edi)
	je	L555
	movl	-40(%ebp), %eax
	cmpb	$0, (%eax)
	jne	L554
L555:
	movl	$1, (%esp)
	movl	$LC49, 4(%esp)
	jmp	L625
L554:
	movl	$0, -16(%ebp)
	movl	_imptail, %ebx
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, (%ebx)
	movl	%eax, %ebx
	movl	%eax, _imptail
	movl	$0, (%eax)
	movl	%edi, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	movl	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 8(%ebx)
	movl	%esi, (%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, 12(%ebx)
	cmpb	$0, (%esi)
	je	L558
	cmpl	$0, -16(%ebp)
	je	L557
L558:
	movl	%esi, (%esp)
	call	_nasm_strdup
	jmp	L624
L557:
	movl	$0, 16(%ebx)
	jmp	L622
L530:
	movl	%ebx, (%esp)
	movl	$LC50, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L560
	movl	$0, -48(%ebp)
	movl	$0, -52(%ebp)
	movl	$1, %eax
	cmpl	$2, %esi
	je	L474
	movl	%edi, -44(%ebp)
	movl	%edi, %ebx
	jmp	L562
L566:
	incl	%ebx
L562:
	cmpb	$0, (%ebx)
	je	L563
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L566
L563:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L567
	movb	$0, (%ebx)
L572:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L567
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L572
L567:
	movl	%ebx, %edi
	jmp	L573
L577:
	incl	%ebx
L573:
	cmpb	$0, (%ebx)
	je	L574
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L577
L574:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L578
	movb	$0, (%ebx)
L583:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L578
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L583
L578:
	movl	-44(%ebp), %eax
	cmpb	$0, (%eax)
	jne	L584
	movl	$1, (%esp)
	movl	$LC51, 4(%esp)
L625:
	call	*_error
	jmp	L622
L584:
	cmpb	$0, (%edi)
	jne	L585
	movl	-44(%ebp), %edi
	movl	$LC52, -44(%ebp)
L585:
	cmpb	$0, (%ebx)
	je	L618
L608:
	movl	%ebx, %esi
	jmp	L589
L593:
	incl	%ebx
L589:
	cmpb	$0, (%ebx)
	je	L590
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L593
L590:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L594
	movb	$0, (%ebx)
L599:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L594
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L599
L594:
	movl	%esi, (%esp)
	movl	$LC53, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L600
	orl	$64, -48(%ebp)
	jmp	L586
L600:
	movl	%esi, (%esp)
	movl	$LC54, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L602
	orl	$32, -48(%ebp)
	jmp	L586
L602:
	movl	%esi, (%esp)
	movl	$LC55, 4(%esp)
	movl	$5, 8(%esp)
	call	_nasm_strnicmp
	testl	%eax, %eax
	jne	L604
	movl	$0, -20(%ebp)
	addl	$5, %esi
	movl	%esi, (%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	andl	$31, %eax
	orl	%eax, -48(%ebp)
	cmpl	$0, -20(%ebp)
	je	L586
	movl	$1, (%esp)
	movl	$LC56, 4(%esp)
	jmp	L623
L604:
	movl	$0, -24(%ebp)
	movl	%esi, (%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, -52(%ebp)
	cmpl	$0, -24(%ebp)
	jne	L620
	orl	$128, -48(%ebp)
L586:
	cmpb	$0, (%ebx)
	jne	L608
L618:
	movl	_exptail, %esi
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%eax, (%esi)
	movl	%eax, _exptail
	movl	$0, (%eax)
	movl	%edi, (%esp)
	call	_nasm_strdup
	movl	%eax, 8(%ebx)
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, 4(%ebx)
	movl	-52(%ebp), %eax
	movl	%eax, 12(%ebx)
	movl	-48(%ebp), %eax
L624:
	movl	%eax, 16(%ebx)
	jmp	L622
L619:
	movl	$1, (%esp)
	movl	$LC46, 4(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	jmp	L621
L620:
	movl	$1, (%esp)
	movl	$LC57, 4(%esp)
L623:
	movl	%esi, 8(%esp)
L621:
	call	*_error
L622:
	movl	$1, %eax
	jmp	L474
L560:
	movl	$0, %eax
L474:
	addl	$76, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_obj_segbase;	.scl	3;	.type	32;	.endef
_obj_segbase:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	_seghead, %eax
	testl	%eax, %eax
	je	L652
	leal	-1(%ecx), %edx
L632:
	cmpl	%edx, 4(%eax)
	je	L628
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	L632
	jmp	L652
L628:
	testl	%eax, %eax
	jne	L633
L652:
	movl	%ecx, %eax
	shrl	$31, %eax
	leal	(%eax,%ecx), %eax
	movl	%eax, %edx
	sarl	%edx
	movl	_ebhead, %eax
	cmpl	$256, %edx
	jle	L635
L639:
	testl	%eax, %eax
	je	L648
	movl	(%eax), %eax
	subl	$256, %edx
	cmpl	$256, %edx
	jg	L639
L635:
	testl	%eax, %eax
	je	L648
	movl	4(%eax,%edx,4), %eax
	cmpl	$0, 20(%eax)
	je	L648
	cmpl	$2, 20(%eax)
	jne	L643
	movl	24(%eax), %eax
	movl	4(%eax), %eax
	jmp	L654
L643:
	cmpl	$3, 20(%eax)
	jne	L645
	movl	24(%eax), %eax
	jmp	L653
L645:
	movl	$-1, %eax
	jmp	L626
L633:
	cmpl	$1073741823, 20(%eax)
	jle	L647
	movl	20(%eax), %eax
	jmp	L626
L647:
	cmpl	$0, 12(%eax)
	je	L648
	movl	12(%eax), %eax
L653:
	movl	8(%eax), %eax
L654:
	incl	%eax
	jmp	L626
L648:
	movl	%ecx, %eax
L626:
	popl	%ebp
	ret
LC58:
	.ascii ".obj\0"
	.align 2
	.def	_obj_filename;	.scl	3;	.type	32;	.endef
_obj_filename:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	$_obj_infile, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC58, 8(%esp)
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
	.align 32
LC59:
	.ascii "segment `%s' requires more alignment than OBJ format supports\0"
	.align 32
LC60:
	.ascii "group `%s' contains undefined segment `%s'\0"
	.align 32
LC61:
	.ascii "entry point is not in this module\0"
LC62:
	.ascii "start_of_program\0"
	.align 2
	.def	_obj_write_file;	.scl	3;	.type	32;	.endef
_obj_write_file:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	$0, -16(%ebp)
	call	_obj_new
	movl	%eax, %edi
	movl	$128, 16(%eax)
	movl	%eax, (%esp)
	movl	$_obj_infile, 4(%esp)
	call	_obj_name
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	$136, 16(%edi)
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_rword
	movl	%edi, (%esp)
	movl	$_boast.0, 4(%esp)
	call	_obj_name
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	$136, 16(%edi)
	movl	_imphead, %ebx
	testl	%ebx, %ebx
	je	L817
L665:
	movl	%edi, (%esp)
	movl	$160, 4(%esp)
	call	_obj_rword
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	call	_obj_byte
	cmpl	$0, 16(%ebx)
	je	L661
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	jmp	L851
L661:
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
L851:
	call	_obj_byte
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%edi, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	cmpl	$0, 16(%ebx)
	je	L663
	movl	%edi, (%esp)
	movl	16(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	jmp	L664
L663:
	movl	%edi, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
L664:
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L665
L817:
	movl	_exphead, %ebx
	testl	%ebx, %ebx
	je	L819
L671:
	movl	%edi, (%esp)
	movl	$160, 4(%esp)
	call	_obj_rword
	movl	%edi, (%esp)
	movl	$2, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movzbl	16(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	cmpb	$0, 16(%ebx)
	jns	L670
	movl	%edi, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
L670:
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L671
L819:
	cmpl	$0, 8(%ebp)
	je	L672
	movl	$136, 16(%edi)
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$161, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
L672:
	movl	$150, 16(%edi)
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	$1, -24(%ebp)
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L821
L679:
	movl	%edi, (%esp)
	movl	48(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, %edi
	cmpl	$0, 52(%esi)
	je	L677
	movl	%eax, (%esp)
	movl	52(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, %edi
L677:
	cmpl	$0, 56(%esi)
	je	L678
	movl	%edi, (%esp)
	movl	56(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, %edi
L678:
	movl	%edi, (%esp)
	call	_obj_commit
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L679
L821:
	movl	_grphead, %esi
	testl	%esi, %esi
	je	L823
L684:
	movl	%edi, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L684
L823:
	movl	%edi, (%esp)
	call	_obj_emit
	movl	$152, 16(%edi)
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L825
L710:
	movl	16(%esi), %eax
	movl	%eax, -28(%ebp)
	movl	24(%esi), %eax
	leal	0(,%eax,4), %ebx
	cmpl	$0, 28(%esi)
	je	L689
	orl	$1, %ebx
	jmp	L690
L689:
	cmpl	$65536, -28(%ebp)
	jne	L690
	movl	$0, -28(%ebp)
	orl	$2, %ebx
L690:
	cmpl	$1073741823, 20(%esi)
	jg	L693
	cmpl	$4095, 20(%esi)
	jle	L694
	cmpl	$4096, 20(%esi)
	jle	L695
	movl	$1, (%esp)
	movl	$LC59, 4(%esp)
	movl	48(%esi), %eax
	movl	%eax, 8(%esp)
	call	*_error
L695:
	orl	$192, %ebx
	jmp	L693
L694:
	cmpl	$255, 20(%esi)
	jle	L697
	orl	$128, %ebx
	jmp	L693
L697:
	cmpl	$15, 20(%esi)
	jle	L699
	orl	$96, %ebx
	jmp	L693
L699:
	cmpl	$3, 20(%esi)
	jle	L701
	orl	$160, %ebx
	jmp	L693
L701:
	cmpl	$1, 20(%esi)
	jle	L703
	orl	$64, %ebx
	jmp	L693
L703:
	orl	$32, %ebx
L693:
	movl	%edi, (%esp)
	movzbl	%bl, %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	testb	$64, 23(%esi)
	je	L705
	movl	%edi, (%esp)
	movl	20(%esi), %eax
	subl	$1073741824, %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
L705:
	movl	%edi, (%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 4(%esp)
	call	_obj_x
	movl	%edi, (%esp)
	incl	-24(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%edi, (%esp)
	cmpl	$0, 52(%esi)
	je	L706
	incl	-24(%ebp)
	movl	-24(%ebp), %eax
	jmp	L707
L706:
	movl	$1, %eax
L707:
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%edi, (%esp)
	cmpl	$0, 56(%esi)
	je	L708
	incl	-24(%ebp)
	movl	-24(%ebp), %eax
	jmp	L709
L708:
	movl	$1, %eax
L709:
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L710
L825:
	movl	$154, 16(%edi)
	movl	_grphead, %esi
	testl	%esi, %esi
	je	L827
L726:
	movl	20(%esi), %eax
	cmpl	16(%esi), %eax
	je	L715
	movl	%eax, %ebx
	cmpl	16(%esi), %eax
	jge	L715
L720:
	movl	$1, (%esp)
	movl	$LC60, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, 8(%esp)
	movl	24(%esi,%ebx,4), %eax
	movl	%eax, 12(%esp)
	call	*_error
	movl	24(%esi,%ebx,4), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	$0, 24(%esi,%ebx,4)
	incl	%ebx
	cmpl	16(%esi), %ebx
	jl	L720
L715:
	movl	%edi, (%esp)
	incl	-24(%ebp)
	movl	-24(%ebp), %edx
	movl	%edx, 4(%esp)
	call	_obj_index
	movl	$0, %ebx
	cmpl	20(%esi), %ebx
	jge	L830
L725:
	movl	%edi, (%esp)
	movl	$255, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	24(%esi,%ebx,4), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	incl	%ebx
	cmpl	20(%esi), %ebx
	jl	L725
L830:
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L726
L827:
	movl	$144, 16(%edi)
	movl	$_ori_pubdef, (%edi)
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L832
L738:
	cmpl	$0, 12(%esi)
	je	L731
	movl	12(%esi), %eax
	movl	12(%eax), %eax
	jmp	L732
L731:
	movl	$0, %eax
L732:
	movl	%eax, 32(%edi)
	movl	8(%esi), %eax
	movl	%eax, 36(%edi)
	movl	32(%esi), %ebx
	testl	%ebx, %ebx
	je	L834
L737:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L737
L834:
	movl	%edi, (%esp)
	call	_obj_emit
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L738
L832:
	movl	$0, 32(%edi)
	movl	$0, 36(%edi)
	movl	_fpubhead, %ebx
	testl	%ebx, %ebx
	je	L836
L744:
	movl	40(%edi), %eax
	cmpl	12(%ebx), %eax
	je	L743
	movl	%edi, (%esp)
	call	_obj_emit
	movl	12(%ebx), %eax
	movl	%eax, 40(%edi)
L743:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L744
L836:
	movl	%edi, (%esp)
	call	_obj_emit
	movl	$_ori_null, (%edi)
	movl	_exthead, %ebx
	testl	%ebx, %ebx
	je	L838
L755:
	cmpl	$0, 8(%ebx)
	jne	L749
	cmpl	$140, 16(%edi)
	je	L750
	movl	%edi, (%esp)
	call	_obj_emit
	movl	$140, 16(%edi)
L750:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_obj_index
	jmp	L853
L749:
	cmpl	$176, 16(%edi)
	je	L752
	movl	%edi, (%esp)
	call	_obj_emit
	movl	$176, 16(%edi)
L752:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_obj_index
	cmpl	$0, 12(%ebx)
	je	L753
	movl	%eax, (%esp)
	movl	$97, 4(%esp)
	call	_obj_byte
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	cltd
	idivl	12(%ebx)
	movl	%eax, 4(%esp)
	call	_obj_value
	movl	%eax, (%esp)
	movl	12(%ebx), %eax
	jmp	L852
L753:
	movl	%eax, (%esp)
	movl	$98, 4(%esp)
	call	_obj_byte
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
L852:
	movl	%eax, 4(%esp)
	call	_obj_value
L853:
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L755
L838:
	movl	%edi, (%esp)
	call	_obj_emit
	cmpl	$0, 8(%ebp)
	jne	L757
	cmpl	$-1, _obj_entry_seg
	jne	L756
L757:
	movl	$136, 16(%edi)
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$162, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
L756:
	cmpl	$0, 8(%ebp)
	je	L758
	movl	_arrhead, %eax
	movl	%eax, -32(%ebp)
	movl	$136, 16(%edi)
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$234, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$4, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$24, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$6, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$42, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$25, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$36, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$26, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$36, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$27, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$35, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$28, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$35, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$4, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$29, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$35, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$1, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$30, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$35, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$5, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	$31, %ebx
	cmpl	_arrindex, %ebx
	jge	L758
L763:
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$227, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	%ebx, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	-32(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
	movl	%edi, (%esp)
	movl	$26, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	-32(%ebp), %edx
	movzbl	8(%edx), %eax
	movl	%eax, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	-32(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -32(%ebp)
	incl	%ebx
	cmpl	_arrindex, %ebx
	jl	L763
L758:
	cmpl	$0, _fnhead
	je	L764
	cmpl	$0, 8(%ebp)
	je	L764
	movl	_fnhead, %edx
	movl	8(%edx), %eax
	movl	4(%eax), %esi
	movl	%edx, -20(%ebp)
	testl	%edx, %edx
	je	L764
L777:
	movl	$136, 16(%edi)
	movl	$_ori_null, (%edi)
	movl	%edi, (%esp)
	movl	$64, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$232, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	-20(%ebp), %edx
	movl	4(%edx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_dword
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	$148, 16(%edi)
	movl	$_ori_linnum, (%edi)
	movl	-20(%ebp), %eax
	movl	8(%eax), %ebx
	testl	%ebx, %ebx
	je	L842
L776:
	cmpl	4(%ebx), %esi
	je	L773
	movl	4(%ebx), %esi
	movl	%edi, (%esp)
	call	_obj_emit
L773:
	cmpl	$0, 12(%esi)
	je	L774
	movl	12(%esi), %eax
	movl	12(%eax), %eax
	jmp	L775
L774:
	movl	$0, %eax
L775:
	movl	%eax, 32(%edi)
	movl	8(%esi), %eax
	movl	%eax, 36(%edi)
	movl	%edi, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L776
L842:
	movl	%edi, (%esp)
	call	_obj_emit
	movl	-20(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, -20(%ebp)
	testl	%edx, %edx
	jne	L777
L764:
	cmpl	$-1, _obj_entry_seg
	je	L778
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L849
L784:
	movl	4(%esi), %eax
	cmpl	_obj_entry_seg, %eax
	je	L850
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L784
	jmp	L849
L850:
	movl	%esi, -16(%ebp)
	testl	%esi, %esi
	jne	L778
L849:
	movl	$1, (%esp)
	movl	$LC61, 4(%esp)
	call	*_error
L778:
	movl	$136, 16(%edi)
	movl	$_ori_local, (%edi)
	cmpl	$0, 8(%ebp)
	je	L786
	cmpl	$-1, _obj_entry_seg
	je	L786
	movl	%edi, (%esp)
	movl	$LC62, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	$25, 4(%esp)
	call	_obj_word
	movl	%eax, (%esp)
	cmpl	$0, 12(%esi)
	je	L787
	movl	12(%esi), %eax
	movl	12(%eax), %eax
	jmp	L788
L787:
	movl	$0, %eax
L788:
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%eax, (%esp)
	movl	8(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%eax, (%esp)
	movl	_obj_entry_ofs, %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
L786:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L790
	cmpl	$0, 8(%ebp)
	je	L790
L801:
	movl	40(%esi), %ebx
	testl	%ebx, %ebx
	je	L846
L800:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_name
	movl	%eax, (%esp)
	movl	16(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_word
	movl	%eax, (%esp)
	cmpl	$0, 12(%esi)
	je	L798
	movl	12(%esi), %eax
	movl	12(%eax), %eax
	jmp	L799
L798:
	movl	$0, %eax
L799:
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%eax, (%esp)
	movl	8(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	movl	%eax, %edi
	movl	%eax, (%esp)
	call	_obj_commit
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L800
L846:
	movl	(%esi), %esi
	testl	%esi, %esi
	je	L790
	cmpl	$0, 8(%ebp)
	jne	L801
L790:
	cmpl	$0, 4(%edi)
	je	L802
	movl	%edi, (%esp)
	call	_obj_emit
L802:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L848
L807:
	movl	60(%esi), %eax
	movl	%eax, (%esp)
	call	_obj_emit
	movl	60(%esi), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L807
L848:
	cmpl	$0, _obj_use32
	je	L808
	movl	$139, %eax
	jmp	L809
L808:
	movl	$138, %eax
L809:
	movl	%eax, 16(%edi)
	movl	$_ori_null, (%edi)
	cmpl	$0, -16(%ebp)
	je	L810
	movl	-16(%ebp), %eax
	cmpl	$0, 28(%eax)
	je	L811
	movl	$139, %eax
	jmp	L812
L811:
	movl	$138, %eax
L812:
	movl	%eax, 16(%edi)
	movl	%edi, (%esp)
	movl	$193, 4(%esp)
	call	_obj_byte
	movl	-16(%ebp), %esi
	cmpl	$0, 12(%esi)
	je	L813
	movl	%edi, (%esp)
	movl	$16, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	12(%esi), %eax
	movl	12(%eax), %eax
	jmp	L854
L813:
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
	movl	%edi, (%esp)
	movl	8(%esi), %eax
L854:
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%edi, (%esp)
	movl	8(%esi), %eax
	movl	%eax, 4(%esp)
	call	_obj_index
	movl	%edi, (%esp)
	movl	_obj_entry_ofs, %eax
	movl	%eax, 4(%esp)
	call	_obj_x
	jmp	L815
L810:
	movl	%edi, (%esp)
	movl	$0, 4(%esp)
	call	_obj_byte
L815:
	movl	%edi, (%esp)
	call	_obj_emit2
	movl	%edi, (%esp)
	call	_nasm_free
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_obj_fwrite;	.scl	3;	.type	32;	.endef
_obj_fwrite:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %esi
	movl	16(%esi), %edi
	cmpl	$32, 12(%esi)
	jne	L856
	orl	$1, %edi
L856:
	movl	%edi, (%esp)
	movl	_ofp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	movl	8(%esi), %ebx
	leal	1(%ebx), %ecx
	movzbl	%cl,%eax
	movzbl	%ch, %edx
	addl	%edx, %eax
	addl	%eax, %edi
	movl	%ecx, (%esp)
	movl	_ofp, %eax
	movl	%eax, 4(%esp)
	call	_fwriteshort
	addl	$44, %esi
	movl	%esi, (%esp)
	movl	$1, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	_ofp, %eax
	movl	%eax, 12(%esp)
	call	_fwrite
	movl	%esi, %edx
	movl	%ebx, %ecx
	testl	%ebx, %ebx
	je	L863
L861:
	movzbl	(%edx), %eax
	addl	%eax, %edi
	incl	%edx
	decl	%ecx
	jne	L861
L863:
	movl	%edi, %eax
	negl	%eax
	andl	$255, %eax
	movl	%eax, (%esp)
	movl	_ofp, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC63:
	.ascii "%define __SECT__ [section .text]\0"
LC64:
	.ascii "%imacro group 1+.nolist\0"
LC65:
	.ascii "[group %1]\0"
LC66:
	.ascii "%endmacro\0"
LC67:
	.ascii "%imacro uppercase 0+.nolist\0"
LC68:
	.ascii "[uppercase %1]\0"
LC69:
	.ascii "%imacro export 1+.nolist\0"
LC70:
	.ascii "[export %1]\0"
LC71:
	.ascii "%imacro import 1+.nolist\0"
LC72:
	.ascii "[import %1]\0"
LC73:
	.ascii "%macro __NASM_CDecl__ 1\0"
	.data
	.align 32
_obj_stdmac:
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC66
	.long	LC69
	.long	LC70
	.long	LC66
	.long	LC71
	.long	LC72
	.long	LC66
	.long	LC73
	.long	LC66
	.long	0
	.text
	.align 2
.globl _dbgbi_init
	.def	_dbgbi_init;	.scl	2;	.type	32;	.endef
_dbgbi_init:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, _fnhead
	movl	$_fnhead, _fntail
	movl	$31, _arrindex
	movl	$0, _arrhead
	movl	$_arrhead, _arrtail
	popl	%ebp
	ret
	.align 2
	.def	_dbgbi_cleanup;	.scl	3;	.type	32;	.endef
_dbgbi_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	cmpl	$0, _fnhead
	je	L888
L873:
	movl	_fnhead, %ebx
	cmpl	$0, 8(%ebx)
	je	L890
L872:
	movl	_fnhead, %edx
	movl	8(%edx), %ecx
	movl	(%ecx), %eax
	movl	%eax, 8(%edx)
	movl	%ecx, (%esp)
	call	_nasm_free
	movl	_fnhead, %eax
	cmpl	$0, 8(%eax)
	jne	L872
L890:
	movl	_fnhead, %eax
	movl	(%eax), %eax
	movl	%eax, _fnhead
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, _fnhead
	jne	L873
L888:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L892
L882:
	cmpl	$0, 40(%esi)
	je	L894
L881:
	movl	40(%esi), %ebx
	movl	(%ebx), %eax
	movl	%eax, 40(%esi)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	%ebx, (%esp)
	call	_nasm_free
	cmpl	$0, 40(%esi)
	jne	L881
L894:
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L882
L892:
	cmpl	$0, _arrhead
	je	L896
L886:
	movl	_arrhead, %edx
	movl	(%edx), %eax
	movl	%eax, _arrhead
	movl	%edx, (%esp)
	call	_nasm_free
	cmpl	$0, _arrhead
	jne	L886
L896:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC74:
	.ascii "lineno directed to nonexistent segment?\0"
	.align 2
	.def	_dbgbi_linnum;	.scl	3;	.type	32;	.endef
_dbgbi_linnum:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %edi
	movl	16(%ebp), %ebx
	cmpl	$-1, %ebx
	je	L897
	cmpl	$0, _any_segs
	jne	L899
	movl	$LC3, (%esp)
	movl	$2, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_obj_segment
	cmpl	%eax, %ebx
	je	L899
	movl	$3, (%esp)
	movl	$LC4, 4(%esp)
	call	*_error
L899:
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L917
L906:
	cmpl	%ebx, 4(%esi)
	je	L902
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L906
	jmp	L917
L902:
	testl	%esi, %esi
	jne	L907
L917:
	movl	$3, (%esp)
	movl	$LC74, 4(%esp)
	call	*_error
L907:
	movl	_fnhead, %ebx
	testl	%ebx, %ebx
	je	L918
L913:
	movl	%edi, (%esp)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L909
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	jne	L913
	jmp	L918
L909:
	testl	%ebx, %ebx
	jne	L914
L918:
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	movl	%edi, (%esp)
	call	_strlen
	incl	%eax
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, 4(%ebx)
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	call	_strcpy
	movl	$0, 8(%ebx)
	leal	8(%ebx), %eax
	movl	%eax, 12(%ebx)
	movl	$0, (%ebx)
	movl	_fntail, %eax
	movl	%ebx, (%eax)
	movl	%ebx, _fntail
L914:
	movl	$16, (%esp)
	call	_nasm_malloc
	movl	%esi, 4(%eax)
	movl	16(%esi), %edx
	movl	%edx, 8(%eax)
	movl	12(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	$0, (%eax)
	movl	12(%ebx), %edx
	movl	%eax, (%edx)
	movl	%eax, 12(%ebx)
L897:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_dbgbi_deflabel;	.scl	3;	.type	32;	.endef
_dbgbi_deflabel:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	12(%ebp), %ebx
	cmpl	$3, 20(%ebp)
	je	L919
	cmpb	$46, (%edi)
	jne	L921
	cmpb	$46, 1(%edi)
	jne	L921
	cmpb	$64, 2(%edi)
	jne	L919
L921:
	cmpl	$0, _obj_seg_needs_update
	jne	L919
	cmpl	$0, _obj_grp_needs_update
	jne	L919
	cmpl	$1073741823, %ebx
	jg	L919
	cmpl	$-1, %ebx
	je	L925
	testl	$1, %ebx
	jne	L919
L925:
	cmpl	$1073741823, %ebx
	jg	L919
	cmpl	$-1, %ebx
	je	L919
	movl	_seghead, %esi
	testl	%esi, %esi
	je	L919
L933:
	cmpl	%ebx, 4(%esi)
	jne	L930
	movl	$20, (%esp)
	call	_nasm_malloc
	movl	%eax, -16(%ebp)
	movl	44(%esi), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%eax)
	movl	%edx, _last_defined
	movl	%edx, 44(%esi)
	movl	$0, (%edx)
	movl	%edi, (%esp)
	call	_nasm_strdup
	movl	-16(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	16(%ebp), %eax
	movl	%eax, 8(%edx)
L930:
	movl	(%esi), %esi
	testl	%esi, %esi
	jne	L933
L919:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_dbgbi_typevalue;	.scl	3;	.type	32;	.endef
_dbgbi_typevalue:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, %ebx
	shrl	$8, %ebx
	andl	$248, %eax
	cmpl	$0, _last_defined
	je	L935
	subl	$16, %eax
	cmpl	$40, %eax
	ja	L944
	jmp	*L945(,%eax,4)
	.align 4
	.align 4
L945:
	.long	L938
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L939
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L940
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L941
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L942
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L944
	.long	L943
L938:
	movl	_last_defined, %eax
	movl	$8, 16(%eax)
	movl	$1, %esi
	jmp	L937
L939:
	movl	_last_defined, %eax
	movl	$10, 16(%eax)
	movl	$2, %esi
	jmp	L937
L940:
	movl	_last_defined, %eax
	movl	$12, 16(%eax)
	jmp	L947
L941:
	movl	_last_defined, %eax
	movl	$14, 16(%eax)
L947:
	movl	$4, %esi
	jmp	L937
L942:
	movl	_last_defined, %eax
	movl	$15, 16(%eax)
	movl	$8, %esi
	jmp	L937
L943:
	movl	_last_defined, %eax
	movl	$16, 16(%eax)
	movl	$10, %esi
	jmp	L937
L944:
	movl	_last_defined, %eax
	movl	$25, 16(%eax)
	movl	$0, %esi
L937:
	cmpl	$1, %ebx
	jle	L946
	movl	$12, (%esp)
	call	_nasm_malloc
	movl	_last_defined, %edx
	movl	16(%edx), %ecx
	movl	%esi, %edx
	imull	%ebx, %edx
	movl	%edx, 4(%eax)
	movl	%ecx, 8(%eax)
	movl	$0, (%eax)
	movl	_arrindex, %ecx
	movl	_last_defined, %edx
	movl	%ecx, 16(%edx)
	incl	_arrindex
	movl	_arrtail, %edx
	movl	%eax, (%edx)
	movl	%eax, _arrtail
L946:
	movl	$0, _last_defined
L935:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_dbgbi_output;	.scl	3;	.type	32;	.endef
_dbgbi_output:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
LC75:
	.ascii "Borland Debug Records\0"
LC76:
	.ascii "borland\0"
	.data
	.align 32
_borland_debug_form:
	.long	LC75
	.long	LC76
	.long	_dbgbi_init
	.long	_dbgbi_linnum
	.long	_dbgbi_deflabel
	.long	_null_debug_routine
	.long	_dbgbi_typevalue
	.long	_dbgbi_output
	.long	_dbgbi_cleanup
	.align 4
_borland_debug_arr:
	.long	_borland_debug_form
	.long	_null_debug_form
	.long	0
.globl _of_obj
	.text
	.align 32
LC77:
	.ascii "MS-DOS 16-bit/32-bit OMF object files\0"
LC78:
	.ascii "obj\0"
	.data
	.align 32
_of_obj:
	.long	LC77
	.long	LC78
	.long	0
	.long	_borland_debug_arr
	.long	_null_debug_form
	.long	_obj_stdmac
	.long	_obj_init
	.long	_obj_set_info
	.long	_obj_out
	.long	_obj_deflabel
	.long	_obj_segment
	.long	_obj_segbase
	.long	_obj_directive
	.long	_obj_filename
	.long	_obj_cleanup
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
.lcomm _obj_uppercase,16
.lcomm _obj_use32,16
.lcomm _obj_infile,256
.lcomm _error,16
.lcomm _evaluate,16
.lcomm _deflabel,16
.lcomm _ofp,16
.lcomm _first_seg,16
.lcomm _any_segs,16
.lcomm _passtwo,16
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
.lcomm _dws,16
.lcomm _externals,16
.lcomm _ebhead,16
.lcomm _ebtail,16
.lcomm _seghead,16
.lcomm _segtail,16
.lcomm _obj_seg_needs_update,16
.lcomm _grphead,16
.lcomm _grptail,16
.lcomm _obj_grp_needs_update,16
.lcomm _imphead,16
.lcomm _imptail,16
.lcomm _exphead,16
.lcomm _exptail,16
.lcomm _obj_entry_seg,16
.lcomm _obj_entry_ofs,16
.lcomm _current_seg,16
	.def	_null_debug_routine;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fwriteshort;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_standard_extension;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_is_simple;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_nasm_strndup;	.scl	2;	.type	32;	.endef
	.def	_strspn;	.scl	2;	.type	32;	.endef
	.def	_nasm_strnicmp;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_toupper;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
