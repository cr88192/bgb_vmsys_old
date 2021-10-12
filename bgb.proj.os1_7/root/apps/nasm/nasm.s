	.file	"nasm.c"
.globl _tasm_compatible_mode
	.data
	.align 4
_tasm_compatible_mode:
	.long	0
	.align 4
_ofmt:
	.long	0
	.align 4
_ofile:
	.long	0
.globl _optimizing
	.align 4
_optimizing:
	.long	-1
	.align 4
_cmd_sb:
	.long	16
	.align 4
_cmd_cpu:
	.long	251658240
	.align 4
_cpu:
	.long	251658240
_suppressed:
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	1
	.text
LC0:
	.ascii "macro-params\0"
LC1:
	.ascii "macro-selfref\0"
LC2:
	.ascii "orphan-labels\0"
LC3:
	.ascii "number-overflow\0"
LC4:
	.ascii "gnu-elf-extensions\0"
	.data
	.align 4
_suppressed_names:
	.long	0
	.long	LC0
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.text
	.align 32
LC5:
	.ascii "macro calls with wrong no. of params\0"
LC6:
	.ascii "cyclic macro self-references\0"
	.align 32
LC7:
	.ascii "labels alone on lines without trailing `:'\0"
	.align 32
LC8:
	.ascii "numeric constants greater than 0xFFFFFFFF\0"
	.align 32
LC9:
	.ascii "using 8- or 16-bit relocation in ELF, a GNU extension\0"
	.data
	.align 4
_suppressed_what:
	.long	0
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.align 4
_no_pp:
	.long	_no_pp_reset
	.long	_no_pp_getline
	.long	_no_pp_cleanup
.globl _user_nolist
	.align 4
_user_nolist:
	.long	0
	.text
	.align 2
	.def	_nasm_fputs;	.scl	3;	.type	32;	.endef
_nasm_fputs:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	testl	%ebx, %ebx
	je	L2
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_fputs
	movl	$10, (%esp)
	movl	%ebx, 4(%esp)
	call	_fputc
	jmp	L1
L2:
	movl	%eax, (%esp)
	call	_puts
L1:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
LC10:
	.ascii "__OUTPUT_FORMAT__=%s\12\0"
LC11:
	.ascii "%s: %s\0"
LC12:
	.ascii "w\0"
	.align 32
LC13:
	.ascii "unable to open output file `%s'\0"
LC14:
	.ascii "\0"
LC15:
	.ascii "%%line %ld+%d %s\12\0"
LC16:
	.ascii "wb\0"
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$124, %esp
	andl	$-16, %esp
	movl	$0, %eax
	call	__alloca
	call	___main
	movl	$1, _pass0
	movl	$0, _terminate_after_phase
	movl	$0, _want_usage
	movl	$_report_error_gnu, _report_error
	movl	$_report_error_gnu, (%esp)
	call	_nasm_set_malloc_error
	call	_raa_init
	movl	%eax, _offsets
	movl	$8, (%esp)
	call	_saa_init
	movl	%eax, _forwrefs
	movl	$_nasmpp, _preproc
	movl	$0, _operating_mode
	movl	_stderr, %eax
	movl	%eax, _error_file
	call	_seg_init
	call	_register_output_formats
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_parse_cmdline
	cmpl	$0, _terminate_after_phase
	je	L5
	cmpl	$0, _want_usage
	je	L43
	call	_usage
	jmp	L43
L5:
	cmpl	$0, _using_debug_info
	jne	L7
	movl	_ofmt, %eax
	movl	$_null_debug_form, 16(%eax)
L7:
	movl	_ofmt, %eax
	cmpl	$0, 20(%eax)
	je	L8
	movl	20(%eax), %eax
	movl	%eax, (%esp)
	call	_pp_extra_stdmac
L8:
	movl	_ofmt, %eax
	movl	%eax, (%esp)
	movl	$_location, 4(%esp)
	call	_parser_global_info
	movl	_ofmt, %eax
	movl	%eax, (%esp)
	movl	$_lookup_label, 4(%esp)
	movl	$_location, 8(%esp)
	call	_eval_global_info
	leal	-88(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC10, 4(%esp)
	movl	_ofmt, %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	movl	%ebx, (%esp)
	call	_pp_pre_define
	movl	_operating_mode, %eax
	cmpl	$1, %eax
	je	L16
	cmpl	$1, %eax
	jb	L32
	cmpl	$2, %eax
	jne	L9
	movl	$_inname, (%esp)
	movl	$0, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	movl	$_evaluate, 12(%esp)
	movl	$_nasmlist, 16(%esp)
	movl	_preproc, %eax
	call	*(%eax)
	cmpb	$0, _outname
	jne	L11
	movl	$_inname, (%esp)
	movl	$_outname, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	movl	_ofmt, %eax
	call	*52(%eax)
L11:
	movl	$0, _ofile
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC11, 4(%esp)
	movl	$_outname, 8(%esp)
	movl	$_inname, 12(%esp)
	call	_fprintf
	jmp	L12
L15:
	movl	%eax, (%esp)
	call	_nasm_free
L12:
	movl	_preproc, %eax
	call	*4(%eax)
	testl	%eax, %eax
	jne	L15
	movl	$0, (%esp)
	movl	_preproc, %eax
	call	*8(%eax)
	movl	$10, (%esp)
	movl	_stdout, %eax
	movl	%eax, 4(%esp)
	call	_putc
	jmp	L9
L16:
	movl	$0, -96(%ebp)
	movl	$0, %esi
	movl	$0, %edi
	cmpb	$0, _outname
	je	L17
	movl	$_outname, (%esp)
	movl	$LC12, 4(%esp)
	call	_fopen
	movl	%eax, _ofile
	testl	%eax, %eax
	jne	L19
	movl	$18, (%esp)
	movl	$LC13, 4(%esp)
	movl	$_outname, 8(%esp)
	call	*_report_error
	jmp	L19
L17:
	movl	$0, _ofile
L19:
	movl	$0, _location+8
	movl	$_inname, (%esp)
	movl	$2, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	movl	$_evaluate, 12(%esp)
	movl	$_nasmlist, 16(%esp)
	movl	_preproc, %eax
	call	*(%eax)
	jmp	L20
L29:
	addl	%edi, %esi
	movl	%esi, -92(%ebp)
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	leal	-96(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_src_get
	testl	%eax, %eax
	je	L23
	cmpl	$1, %eax
	jne	L24
	cmpl	$1, %edi
	jne	L24
	movl	$LC14, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_nasm_fputs
	jmp	L25
L24:
	movl	$0, %edx
	cmpl	$-1, %eax
	jne	L27
	cmpl	$1, %edi
	je	L26
L27:
	movl	$1, %edx
L26:
	movl	%edx, %edi
	movl	_ofile, %eax
	testl	%eax, %eax
	jne	L28
	movl	_stdout, %eax
L28:
	movl	%eax, (%esp)
	movl	$LC15, 4(%esp)
	movl	-92(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	movl	-96(%ebp), %eax
	movl	%eax, 16(%esp)
	call	_fprintf
L25:
	movl	-92(%ebp), %esi
L23:
	movl	%ebx, (%esp)
	movl	_ofile, %eax
	movl	%eax, 4(%esp)
	call	_nasm_fputs
	movl	%ebx, (%esp)
	call	_nasm_free
L20:
	movl	_preproc, %eax
	call	*4(%eax)
	movl	%eax, %ebx
	testl	%eax, %eax
	jne	L29
	movl	-96(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
	movl	$0, (%esp)
	movl	_preproc, %eax
	call	*8(%eax)
	cmpl	$0, _ofile
	je	L9
	movl	_ofile, %eax
	movl	%eax, (%esp)
	call	_fclose
	cmpl	$0, _ofile
	je	L9
	cmpl	$0, _terminate_after_phase
	je	L9
	movl	$_outname, (%esp)
	jmp	L42
L32:
	movl	$_inname, (%esp)
	movl	$_outname, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	movl	_ofmt, %eax
	call	*52(%eax)
	movl	$_outname, (%esp)
	movl	$LC16, 4(%esp)
	call	_fopen
	movl	%eax, _ofile
	testl	%eax, %eax
	jne	L33
	movl	$18, (%esp)
	movl	$LC13, 4(%esp)
	movl	$_outname, 8(%esp)
	call	*_report_error
L33:
	call	_init_labels
	movl	_ofile, %eax
	movl	%eax, (%esp)
	movl	_report_error, %eax
	movl	%eax, 4(%esp)
	movl	$_define_label, 8(%esp)
	movl	$_evaluate, 12(%esp)
	movl	_ofmt, %eax
	call	*24(%eax)
	movl	$_inname, (%esp)
	call	_assemble_file
	cmpl	$0, _terminate_after_phase
	jne	L34
	movl	_using_debug_info, %eax
	movl	%eax, (%esp)
	movl	_ofmt, %eax
	call	*56(%eax)
	call	_cleanup_labels
	jmp	L9
L34:
	movl	$_outname, (%esp)
	call	_remove
	cmpb	$0, _listname
	je	L9
	movl	$_listname, (%esp)
L42:
	call	_remove
L9:
	cmpl	$0, _want_usage
	je	L39
	call	_usage
L39:
	movl	_offsets, %eax
	movl	%eax, (%esp)
	call	_raa_free
	movl	_forwrefs, %eax
	movl	%eax, (%esp)
	call	_saa_free
	call	_eval_cleanup
	call	_nasmlib_cleanup
	cmpl	$0, _terminate_after_phase
	je	L40
L43:
	movl	$1, %eax
	jmp	L4
L40:
	movl	$0, %eax
L4:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC17:
	.ascii "option `-%c' requires an argument\0"
	.align 2
	.def	_get_param;	.scl	3;	.type	32;	.endef
_get_param:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	$0, (%edx)
	cmpb	$0, 2(%ebx)
	je	L45
	addl	$2, %ebx
	jmp	L46
L49:
	incl	%ebx
L46:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	movl	%ebx, %edx
	testl	%eax, %eax
	je	L44
	jmp	L49
L45:
	testl	%eax, %eax
	je	L50
	cmpb	$0, (%eax)
	je	L50
	movl	$1, (%edx)
	movl	%eax, %edx
	jmp	L44
L50:
	movl	$49, (%esp)
	movl	$LC17, 4(%esp)
	movsbl	1(%ebx),%eax
	movl	%eax, 8(%esp)
	call	*_report_error
	movl	$0, %edx
L44:
	movl	%edx, %eax
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _textopts
LC18:
	.ascii "prefix\0"
LC19:
	.ascii "postfix\0"
	.data
	.align 4
_textopts:
	.long	LC18
	.long	0
	.long	LC19
	.long	1
	.long	0
	.long	0
.globl _stopoptions
	.align 4
_stopoptions:
	.long	0
	.text
	.align 32
LC20:
	.ascii "unrecognised output format `%s' - use -hf for a list\0"
	.align 32
LC21:
	.ascii "command line optimization level must be 'v', 0..3 or <nn>\0"
	.align 32
LC22:
	.ascii "cannot open file `%s' for error messages\0"
	.align 32
LC23:
	.ascii "unrecognized debug format `%s' for output format `%s'\0"
LC24:
	.ascii "vc\0"
LC25:
	.ascii "gnu\0"
	.align 32
LC26:
	.ascii "unrecognized error reporting format `%s'\0"
	.align 32
LC27:
	.ascii "usage: nasm [-@ response file] [-o outfile] [-f format] [-l listfile]\12            [options...] [--] filename\12    or nasm -r   for version info (obsolete)\12    or nasm -v   for version info (preferred)\12\12    -t          Assemble in SciTech TASM compatible mode\12    -g          Generate debug information in selected format.\12\0"
	.align 32
LC28:
	.ascii "    -e          preprocess only (writes output to stdout by default)\12    -a          don't preprocess (assemble only)\12    -M          generate Makefile dependencies on stdout\12\12    -E<file>    redirect error messages to file\12    -s          redirect error messages to stdout\12\12    -F format   select a debugging format\12\12    -I<path>    adds a pathname to the include file path\12\0"
	.align 32
LC29:
	.ascii "    -O<digit>   optimize branch offsets (-O0 disables, default)\12    -P<file>    pre-includes a file\12    -D<macro>[=<value>] pre-defines a macro\12    -U<macro>   undefines a macro\12    -X<format>  specifies error reporting format (gnu or vc)\12    -w+foo      enables warnings about foo; -w-foo disables them\12where foo can be:\12\0"
LC30:
	.ascii "    %-23s %s (default %s)\12\0"
LC31:
	.ascii "off\0"
LC32:
	.ascii "on\0"
	.align 32
LC33:
	.ascii "\12response files should contain command line parameters, one per line.\12\0"
	.align 32
LC34:
	.ascii "\12valid output formats for -f are (`*' denotes default):\12\0"
	.align 32
LC35:
	.ascii "\12For a list of valid output formats, use -hf.\12\0"
	.align 32
LC36:
	.ascii "For a list of debug formats, use -f <form> -y.\12\0"
	.align 32
LC37:
	.ascii "\12valid debug formats for '%s' output format are ('*' denotes default):\12\0"
	.align 32
LC38:
	.ascii "NASM version 0.98.38 compiled on Sep 30 2003\0"
LC39:
	.ascii "invalid option to `-w'\0"
	.align 32
LC40:
	.ascii "option `--%s' requires an argument\0"
LC41:
	.ascii "unrecognised option `--%s'\0"
LC42:
	.ascii "unrecognised option `-%c'\0"
	.align 32
LC43:
	.ascii "more than one input file specified\0"
	.align 2
	.def	_process_arg;	.scl	3;	.type	32;	.endef
_process_arg:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	12(%ebp), %ebx
	movl	$0, -16(%ebp)
	cmpl	$0, 8(%ebp)
	je	L53
	movl	8(%ebp), %eax
	cmpb	$0, (%eax)
	jne	L52
L53:
	movl	$0, %eax
	jmp	L51
L52:
	movl	8(%ebp), %eax
	cmpb	$45, (%eax)
	jne	L54
	cmpl	$0, _stopoptions
	jne	L54
	movsbl	1(%eax),%eax
	subl	$45, %eax
	cmpl	$76, %eax
	ja	L169
	jmp	*L171(,%eax,4)
	.align 4
	.align 4
L171:
	.long	L152
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L71
	.long	L71
	.long	L71
	.long	L169
	.long	L169
	.long	L71
	.long	L169
	.long	L169
	.long	L169
	.long	L151
	.long	L169
	.long	L71
	.long	L71
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L71
	.long	L169
	.long	L169
	.long	L71
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L169
	.long	L139
	.long	L169
	.long	L169
	.long	L71
	.long	L138
	.long	L71
	.long	L123
	.long	L124
	.long	L71
	.long	L169
	.long	L169
	.long	L71
	.long	L169
	.long	L169
	.long	L71
	.long	L71
	.long	L169
	.long	L137
	.long	L56
	.long	L135
	.long	L71
	.long	L137
	.long	L140
	.long	L169
	.long	L134
L56:
	movl	_stdout, %eax
	movl	%eax, _error_file
	jmp	L172
L71:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_get_param
	movl	%eax, %esi
	testl	%eax, %eax
	je	L172
	movl	8(%ebp), %eax
	cmpb	$111, 1(%eax)
	jne	L73
	movl	$_outname, (%esp)
	jmp	L185
L73:
	movl	8(%ebp), %eax
	cmpb	$102, 1(%eax)
	jne	L75
	movl	%esi, (%esp)
	call	_ofmt_find
	movl	%eax, _ofmt
	testl	%eax, %eax
	jne	L76
	movl	$50, (%esp)
	movl	$LC20, 4(%esp)
	jmp	L188
L76:
	movl	_ofmt, %eax
	movl	12(%eax), %edx
	movl	(%edx), %edx
	movl	%edx, 16(%eax)
	jmp	L172
L75:
	movl	8(%ebp), %eax
	cmpb	$79, 1(%eax)
	jne	L79
	movl	$-99, %ebx
	cmpb	$0, (%esi)
	je	L81
L95:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	je	L83
	movl	%esi, (%esp)
	call	_atoi
	movl	%eax, %ebx
L84:
	incl	%esi
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L84
	testl	%ebx, %ebx
	jg	L87
	movl	$-1, _optimizing
	jmp	L80
L87:
	cmpl	$1, %ebx
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	andl	%ebx, %eax
	movl	%eax, _optimizing
	jmp	L80
L83:
	cmpb	$118, (%esi)
	je	L93
	cmpb	$43, (%esi)
	jne	L92
L93:
	incl	%esi
	movl	$1, _opt_verbose_info
	movl	$0, %ebx
	jmp	L80
L92:
	movl	$-99, %ebx
	jmp	L81
L80:
	cmpb	$0, (%esi)
	jne	L95
L81:
	cmpl	$-99, %ebx
	jne	L172
	movl	$2, (%esp)
	movl	$LC21, 4(%esp)
	jmp	L181
L79:
	movl	8(%ebp), %eax
	cmpb	$80, 1(%eax)
	je	L99
	cmpb	$112, 1(%eax)
	jne	L98
L99:
	movl	%esi, (%esp)
	call	_pp_pre_include
	jmp	L172
L98:
	movl	8(%ebp), %eax
	cmpb	$68, 1(%eax)
	je	L102
	cmpb	$100, 1(%eax)
	jne	L101
L102:
	movl	%esi, (%esp)
	call	_pp_pre_define
	jmp	L172
L101:
	movl	8(%ebp), %eax
	cmpb	$85, 1(%eax)
	je	L105
	cmpb	$117, 1(%eax)
	jne	L104
L105:
	movl	%esi, (%esp)
	call	_pp_pre_undefine
	jmp	L172
L104:
	movl	8(%ebp), %eax
	cmpb	$73, 1(%eax)
	je	L108
	cmpb	$105, 1(%eax)
	jne	L107
L108:
	movl	%esi, (%esp)
	call	_pp_include_path
	jmp	L172
L107:
	movl	8(%ebp), %eax
	cmpb	$108, 1(%eax)
	jne	L110
	movl	$_listname, (%esp)
L185:
	movl	%esi, 4(%esp)
	jmp	L184
L110:
	movl	8(%ebp), %eax
	cmpb	$69, 1(%eax)
	jne	L112
	movl	%esi, (%esp)
	movl	$LC12, 4(%esp)
	call	_fopen
	movl	%eax, _error_file
	testl	%eax, %eax
	jne	L172
	movl	_stderr, %eax
	movl	%eax, _error_file
	movl	$50, (%esp)
	movl	$LC22, 4(%esp)
	jmp	L188
L112:
	movl	8(%ebp), %eax
	cmpb	$70, 1(%eax)
	jne	L115
	movl	_ofmt, %ebx
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	call	_dfmt_find
	movl	%eax, 16(%ebx)
	movl	_ofmt, %eax
	cmpl	$0, 16(%eax)
	jne	L172
	movl	$50, (%esp)
	movl	$LC23, 4(%esp)
	movl	%esi, 8(%esp)
	movl	4(%eax), %eax
	movl	%eax, 12(%esp)
	call	*_report_error
	jmp	L172
L115:
	movl	8(%ebp), %eax
	cmpb	$88, 1(%eax)
	jne	L172
	movl	$LC24, (%esp)
	movl	%esi, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L119
	movl	$_report_error_vc, _report_error
	jmp	L172
L119:
	movl	$LC25, (%esp)
	movl	%esi, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L121
	movl	$_report_error_gnu, _report_error
	jmp	L172
L121:
	movl	$50, (%esp)
	movl	$LC26, 4(%esp)
L188:
	movl	%esi, 8(%esp)
	jmp	L183
L123:
	movl	$1, _using_debug_info
	jmp	L172
L124:
	movl	$LC27, (%esp)
	call	_printf
	movl	$LC28, (%esp)
	call	_printf
	movl	$LC29, (%esp)
	call	_printf
	movl	$1, %ebx
L131:
	movl	$LC30, (%esp)
	movl	_suppressed_names(,%ebx,4), %eax
	movl	%eax, 4(%esp)
	movl	_suppressed_what(,%ebx,4), %eax
	movl	%eax, 8(%esp)
	cmpb	$0, _suppressed(%ebx)
	je	L129
	movl	$LC31, %eax
	jmp	L130
L129:
	movl	$LC32, %eax
L130:
	movl	%eax, 12(%esp)
	call	_printf
	incl	%ebx
	cmpl	$5, %ebx
	jle	L131
	movl	$LC33, (%esp)
	call	_printf
	movl	8(%ebp), %eax
	cmpb	$102, 2(%eax)
	jne	L132
	movl	$LC34, (%esp)
	call	_printf
	movl	_ofmt, %eax
	movl	%eax, (%esp)
	movl	_stdout, %eax
	movl	%eax, 4(%esp)
	call	_ofmt_list
	jmp	L182
L132:
	movl	$LC35, (%esp)
	call	_printf
	movl	$LC36, (%esp)
	call	_printf
	jmp	L182
L134:
	movl	$LC37, (%esp)
	movl	_ofmt, %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	call	_printf
	movl	_ofmt, %eax
	movl	%eax, (%esp)
	movl	_stdout, %eax
	movl	%eax, 4(%esp)
	call	_dfmt_list
	jmp	L182
L135:
	movl	$1, _tasm_compatible_mode
	jmp	L172
L137:
	movl	$LC38, (%esp)
	call	_puts
L182:
	movl	$0, (%esp)
	call	_exit
	jmp	L172
L138:
	movl	$1, _operating_mode
	jmp	L172
L139:
	movl	$_no_pp, _preproc
	jmp	L172
L140:
	movl	8(%ebp), %eax
	cmpb	$43, 2(%eax)
	je	L141
	cmpb	$45, 2(%eax)
	jne	L149
L141:
	movl	$1, %ebx
L148:
	movl	8(%ebp), %eax
	addl	$3, %eax
	movl	%eax, (%esp)
	movl	_suppressed_names(,%ebx,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L144
	incl	%ebx
	cmpl	$5, %ebx
	jle	L148
	jmp	L149
L144:
	cmpl	$5, %ebx
	jg	L149
	movl	8(%ebp), %eax
	cmpb	$45, 2(%eax)
	sete	_suppressed(%ebx)
	jmp	L172
L149:
	movl	$49, (%esp)
	movl	$LC39, 4(%esp)
	jmp	L181
L151:
	movl	$2, _operating_mode
	jmp	L172
L152:
	movl	8(%ebp), %eax
	cmpb	$0, 2(%eax)
	jne	L153
	movl	$1, _stopoptions
	jmp	L172
L153:
	movl	$0, %edi
	cmpl	$0, _textopts
	je	L155
	movl	$_textopts, %esi
L159:
	movl	8(%ebp), %eax
	addl	$2, %eax
	movl	%eax, (%esp)
	movl	(%esi,%edi,8), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L155
	incl	%edi
	cmpl	$0, (%esi,%edi,8)
	jne	L159
L155:
	cmpl	$1, %edi
	ja	L167
	testl	%ebx, %ebx
	jne	L163
	movl	$49, (%esp)
	movl	$LC40, 4(%esp)
	jmp	L186
L163:
	movl	$1, -16(%ebp)
	testl	%edi, %edi
	jne	L165
	movl	$_lprefix, (%esp)
	movl	%ebx, 4(%esp)
	movl	$9, 8(%esp)
	call	_strncpy
	movb	$0, _lprefix+9
	jmp	L172
L165:
	cmpl	$1, %edi
	jne	L172
	movl	$_lpostfix, (%esp)
	movl	%ebx, 4(%esp)
	movl	$9, 8(%esp)
	call	_strncpy
	movb	$0, _lpostfix+9
	jmp	L172
L167:
	movl	$49, (%esp)
	movl	$LC41, 4(%esp)
L186:
	movl	8(%ebp), %eax
	addl	$2, %eax
	jmp	L180
L169:
	movl	$0, (%esp)
	leal	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	_ofmt, %eax
	call	*28(%eax)
	testl	%eax, %eax
	jne	L172
	movl	$49, (%esp)
	movl	$LC42, 4(%esp)
	movl	8(%ebp), %eax
	movsbl	1(%eax),%eax
L180:
	movl	%eax, 8(%esp)
L183:
	call	*_report_error
	jmp	L172
L54:
	cmpb	$0, _inname
	je	L173
	movl	$49, (%esp)
	movl	$LC43, 4(%esp)
L181:
	call	*_report_error
	jmp	L172
L173:
	movl	$_inname, (%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
L184:
	call	_strcpy
L172:
	movl	-16(%ebp), %eax
L51:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
LC44:
	.ascii "\15\12\32\0"
	.align 2
	.def	_process_respfile;	.scl	3;	.type	32;	.endef
_process_respfile:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$128, -24(%ebp)
	movl	$128, -20(%ebp)
	movl	$128, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	movl	$128, (%esp)
	call	_nasm_malloc
	movl	%eax, -16(%ebp)
	movb	$0, (%eax)
L213:
	movl	%edi, %ebx
L199:
	movl	%ebx, (%esp)
	movl	%ebx, %eax
	subl	%edi, %eax
	movl	-20(%ebp), %edx
	subl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_fgets
	movl	%eax, %esi
	testl	%eax, %eax
	je	L214
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
	cmpl	%edi, %ebx
	jbe	L197
	cmpb	$10, -1(%ebx)
	je	L194
L197:
	movl	%ebx, %esi
	subl	%edi, %esi
	movl	-20(%ebp), %eax
	subl	$10, %eax
	cmpl	%eax, %esi
	jle	L199
	subl	$-128, -20(%ebp)
	movl	%edi, (%esp)
	movl	-20(%ebp), %edx
	movl	%edx, 4(%esp)
	call	_nasm_realloc
	movl	%eax, %edi
	leal	(%esi,%eax), %ebx
	jmp	L199
L194:
	testl	%esi, %esi
	jne	L200
L214:
	cmpl	%edi, %ebx
	jne	L200
	movl	-16(%ebp), %eax
	cmpb	$0, (%eax)
	je	L201
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_process_arg
L201:
	movl	%edi, (%esp)
	call	_nasm_free
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	call	_nasm_free
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L200:
	movl	%edi, (%esp)
	movl	$LC44, 4(%esp)
	call	_strcspn
	leal	(%eax,%edi), %ebx
	jmp	L215
L206:
	decl	%ebx
L215:
	movb	$0, (%ebx)
	cmpl	%edi, %ebx
	jbe	L203
	movsbl	-1(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L206
L203:
	movl	%edi, %ebx
	jmp	L207
L210:
	incl	%ebx
L207:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L210
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	_process_arg
	testl	%eax, %eax
	je	L211
	movb	$0, (%ebx)
L211:
	movl	%ebx, (%esp)
	call	_strlen
	movl	-24(%ebp), %edx
	subl	$10, %edx
	cmpl	%edx, %eax
	jle	L212
	subl	$-128, -24(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, -16(%ebp)
L212:
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	movl	%ebx, 4(%esp)
	call	_strcpy
	jmp	L213
	.align 2
	.def	_process_args;	.scl	3;	.type	32;	.endef
_process_args:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movb	$32, -9(%ebp)
	movl	8(%ebp), %ebx
	cmpb	$0, (%ebx)
	je	L217
	cmpb	$45, (%ebx)
	je	L217
	movzbl	(%ebx), %eax
	movb	%al, -9(%ebp)
	incl	%ebx
L217:
	movl	$0, %esi
	cmpb	$0, (%ebx)
	je	L234
L231:
	movl	%ebx, %edx
	cmpb	$0, (%ebx)
	je	L222
	movzbl	-9(%ebp), %eax
	cmpb	%al, (%ebx)
	je	L229
L225:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L222
	movzbl	-9(%ebp), %eax
	cmpb	%al, (%ebx)
	jne	L225
	jmp	L229
L222:
	movzbl	-9(%ebp), %eax
	cmpb	%al, (%ebx)
	jne	L237
L229:
	movb	$0, (%ebx)
	incl	%ebx
	movzbl	-9(%ebp), %eax
	cmpb	%al, (%ebx)
	je	L229
L237:
	movl	%esi, %eax
	movl	%edx, %esi
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_process_arg
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	decl	%eax
	andl	%eax, %esi
	cmpb	$0, (%ebx)
	jne	L231
L234:
	testl	%esi, %esi
	je	L216
	movl	%esi, (%esp)
	movl	$0, 4(%esp)
	call	_process_arg
L216:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
LC45:
	.ascii "NASMENV\0"
LC46:
	.ascii "r\0"
LC47:
	.ascii "out of memory\0"
	.align 32
LC48:
	.ascii "unable to open response file `%s'\0"
LC49:
	.ascii "no input file specified\0"
	.align 2
	.def	_parse_cmdline;	.scl	3;	.type	32;	.endef
_parse_cmdline:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movb	$0, _listname
	movb	$0, _outname
	movb	$0, _inname
	movl	$LC45, (%esp)
	call	_getenv
	testl	%eax, %eax
	je	L239
	movl	%eax, (%esp)
	call	_nasm_strdup
	movl	%eax, %ebx
	movl	%eax, (%esp)
	call	_process_args
	movl	%ebx, (%esp)
	call	_nasm_free
L239:
	decl	%edi
	je	L262
L259:
	addl	$4, %esi
	movl	(%esi), %eax
	cmpb	$64, (%eax)
	jne	L243
	movl	$2048, (%esp)
	call	_malloc
	movl	%eax, %ebx
	movl	(%esi), %eax
	incl	%eax
	movl	%eax, (%esp)
	movl	$LC46, 4(%esp)
	call	_fopen
	movl	%eax, -24(%ebp)
	testl	%ebx, %ebx
	jne	L244
	movl	$LC47, (%esp)
	call	_printf
	movl	$-1, (%esp)
	call	_exit
L244:
	cmpl	$0, -24(%ebp)
	je	L245
	jmp	L246
L249:
	movl	%ebx, (%esp)
	call	_process_args
L246:
	movl	%ebx, (%esp)
	movl	$2048, 4(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_fgets
	testl	%eax, %eax
	jne	L249
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	_fclose
L245:
	movl	%ebx, (%esp)
	call	_free
	decl	%edi
	addl	$4, %esi
L243:
	cmpl	$0, _stopoptions
	jne	L250
	movl	(%esi), %eax
	cmpb	$45, (%eax)
	jne	L250
	cmpb	$64, 1(%eax)
	jne	L250
	movl	%eax, (%esp)
	movl	$0, %eax
	cmpl	$1, %edi
	jle	L253
	movl	4(%esi), %eax
L253:
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_get_param
	movl	%eax, -20(%ebp)
	testl	%eax, %eax
	je	L256
	movl	%eax, (%esp)
	movl	$LC46, 4(%esp)
	call	_fopen
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L254
	movl	%eax, (%esp)
	call	_process_respfile
	movl	%ebx, (%esp)
	call	_fclose
	jmp	L256
L254:
	movl	$49, (%esp)
	movl	$LC48, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	call	*_report_error
	jmp	L256
L250:
	movl	(%esi), %eax
	movl	%eax, (%esp)
	movl	$0, %eax
	cmpl	$1, %edi
	jle	L258
	movl	4(%esi), %eax
L258:
	movl	%eax, 4(%esp)
	call	_process_arg
	movl	%eax, -16(%ebp)
L256:
	movl	-16(%ebp), %eax
	leal	(%esi,%eax,4), %esi
	subl	%eax, %edi
	decl	%edi
	jne	L259
L262:
	cmpb	$0, _inname
	jne	L238
	movl	$49, (%esp)
	movl	$LC49, 4(%esp)
	call	*_report_error
L238:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC50:
	.ascii "command line: 32-bit segment size requires a higher cpu\0"
	.align 32
LC51:
	.ascii "segment name `%s' not recognised\0"
	.align 32
LC52:
	.ascii "identifier expected after EXTERN\0"
	.align 32
LC53:
	.ascii "identifier expected after GLOBAL\0"
	.align 32
LC54:
	.ascii "identifier expected after COMMON\0"
	.align 32
LC55:
	.ascii "invalid size specified in COMMON declaration\0"
	.align 32
LC56:
	.ascii "no size specified in COMMON declaration\0"
	.align 32
LC57:
	.ascii "cannot use non-relocatable expression as ABSOLUTE address\0"
	.align 32
LC58:
	.ascii "invalid ABSOLUTE address in pass two\0"
	.align 32
LC59:
	.ascii "identifier expected after DEBUG\0"
	.align 32
LC60:
	.ascii "invalid warning id in WARNING directive\0"
	.align 32
LC61:
	.ascii "invalid parameter to \"list\" directive\0"
LC62:
	.ascii "unrecognised directive [%s]\0"
LC63:
	.ascii "EQU not preceded by label\0"
LC64:
	.ascii "bad syntax for EQU\0"
	.align 32
LC65:
	.ascii "phase error detected at end of assembly.\0"
	.align 32
LC66:
	.ascii "info:: assembly required 1+%d+1 passes\12\0"
	.align 2
	.def	_assemble_file;	.scl	3;	.type	32;	.endef
_assemble_file:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$396, %esp
	movl	$0, -356(%ebp)
	cmpl	$32, _cmd_sb
	jne	L264
	cmpl	$50331647, _cmd_cpu
	ja	L264
	movl	$2, (%esp)
	movl	$LC50, 4(%esp)
	call	*_report_error
L264:
	movl	_optimizing, %eax
	movl	%eax, -352(%ebp)
	shrl	$31, %eax
	decl	%eax
	andl	%eax, -352(%ebp)
	addl	$2, -352(%ebp)
	cmpl	$0, _optimizing
	setle	%al
	movzbl	%al, %eax
	movl	%eax, _pass0
	movl	$1, -348(%ebp)
	movl	-352(%ebp), %eax
	cmpl	%eax, -348(%ebp)
	jg	L267
	cmpl	$2, _pass0
	jg	L267
L506:
	movl	-352(%ebp), %eax
	cmpl	%eax, -348(%ebp)
	setge	%al
	movzbl	%al, %eax
	incl	%eax
	movl	%eax, -360(%ebp)
	cmpl	$2, -348(%ebp)
	setge	%al
	movzbl	%al, %eax
	incl	%eax
	movl	%eax, -364(%ebp)
	movl	$_redefine_label, -368(%ebp)
	cmpl	$1, -348(%ebp)
	jg	L276
	movl	$_define_label, -368(%ebp)
L276:
	movl	_cmd_sb, %eax
	movl	%eax, _sb
	movl	_cmd_cpu, %eax
	movl	%eax, _cpu
	cmpl	$2, _pass0
	jne	L277
	cmpb	$0, _listname
	je	L277
	movl	$_listname, (%esp)
	movl	_report_error, %eax
	movl	%eax, 4(%esp)
	call	*_nasmlist
L277:
	movl	$0, _in_abs_seg
	movl	$0, _global_offset_changed
	movl	$0, (%esp)
	movl	-364(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_sb, 8(%esp)
	movl	_ofmt, %eax
	call	*40(%eax)
	movl	%eax, _location
	cmpl	$1, -348(%ebp)
	jle	L279
	movl	_forwrefs, %eax
	movl	%eax, (%esp)
	call	_saa_rewind
	movl	_forwrefs, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, _forwref
	movl	_offsets, %eax
	movl	%eax, (%esp)
	call	_raa_free
	call	_raa_init
	movl	%eax, _offsets
L279:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	-360(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	movl	$_evaluate, 12(%esp)
	movl	$_nasmlist, 16(%esp)
	movl	_preproc, %eax
	call	*(%eax)
	movl	$0, _globallineno
	cmpl	$1, -348(%ebp)
	jne	L280
	movl	$1, _location+8
L280:
	cmpl	$0, _in_abs_seg
	je	L530
	jmp	L495
L497:
	incl	_globallineno
	movl	%edi, -332(%ebp)
	leal	-332(%ebp), %eax
	movl	%eax, (%esp)
	leal	-336(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_getkw
	testl	%eax, %eax
	je	L286
	cmpl	$10, %eax
	ja	L428
	jmp	*L432(,%eax,4)
	.align 4
	.align 4
L432:
	.long	L428
	.long	L288
	.long	L293
	.long	L315
	.long	L316
	.long	L337
	.long	L373
	.long	L382
	.long	L399
	.long	L417
	.long	L419
L288:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	movl	-364(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$_sb, 8(%esp)
	movl	_ofmt, %eax
	call	*40(%eax)
	cmpl	$-1, %eax
	jne	L289
	cmpl	$1, -360(%ebp)
	setne	%al
	movzbl	%al, %eax
	leal	1(%eax,%eax), %eax
	movl	%eax, (%esp)
	movl	$LC51, 4(%esp)
	movl	-336(%ebp), %eax
	jmp	L528
L289:
	movl	$0, _in_abs_seg
	movl	%eax, _location
	jmp	L433
L293:
	movl	-336(%ebp), %eax
	cmpb	$36, (%eax)
	jne	L294
	incl	%eax
	movl	%eax, -336(%ebp)
L294:
	cmpl	$2, _pass0
	jne	L295
	movl	-336(%ebp), %esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	je	L520
L300:
	incl	%esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	jne	L300
	jmp	L520
L295:
	cmpl	$1, -348(%ebp)
	jne	L433
	movl	-336(%ebp), %esi
	movl	$1, -344(%ebp)
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L304
	cmpb	$95, (%esi)
	je	L304
	cmpb	$46, (%esi)
	je	L304
	cmpb	$63, (%esi)
	je	L304
	cmpb	$64, (%esi)
	je	L304
	movl	$0, -344(%ebp)
L304:
	cmpb	$0, (%esi)
	je	L306
	cmpb	$58, (%esi)
	je	L306
L310:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L309
	cmpb	$95, (%esi)
	je	L309
	cmpb	$46, (%esi)
	je	L309
	cmpb	$63, (%esi)
	je	L309
	cmpb	$64, (%esi)
	je	L309
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L309
	cmpb	$36, (%esi)
	je	L309
	cmpb	$35, (%esi)
	je	L309
	cmpb	$126, (%esi)
	je	L309
	movl	$0, -344(%ebp)
L309:
	incl	%esi
	cmpb	$0, (%esi)
	je	L306
	cmpb	$58, (%esi)
	jne	L310
L306:
	cmpl	$0, -344(%ebp)
	jne	L311
	movl	$1, (%esp)
	movl	$LC52, 4(%esp)
	jmp	L527
L311:
	cmpb	$58, (%esi)
	jne	L312
	movb	$0, (%esi)
	incl	%esi
	jmp	L313
L312:
	movl	$0, %esi
L313:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_extern
	testl	%eax, %eax
	jne	L433
	movl	_pass0, %ebx
	movl	$1, _pass0
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	call	_declare_as_global
	call	_seg_alloc
	movl	-336(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$1, 20(%esp)
	movl	_ofmt, %eax
	movl	%eax, 24(%esp)
	movl	_report_error, %eax
	movl	%eax, 28(%esp)
	call	_define_label
	movl	%ebx, _pass0
	jmp	L433
L315:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_bits
	movl	%eax, _sb
	jmp	L433
L316:
	movl	-336(%ebp), %eax
	cmpb	$36, (%eax)
	jne	L317
	incl	%eax
	movl	%eax, -336(%ebp)
L317:
	cmpl	$2, _pass0
	jne	L318
	movl	-336(%ebp), %esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	je	L520
L323:
	incl	%esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	jne	L323
	jmp	L520
L318:
	cmpl	$1, -364(%ebp)
	jne	L433
	movl	-336(%ebp), %esi
	movl	$1, -344(%ebp)
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L327
	cmpb	$95, (%esi)
	je	L327
	cmpb	$46, (%esi)
	je	L327
	cmpb	$63, (%esi)
	je	L327
	cmpb	$64, (%esi)
	je	L327
	movl	$0, -344(%ebp)
L327:
	cmpb	$0, (%esi)
	je	L329
	cmpb	$58, (%esi)
	je	L329
L333:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L332
	cmpb	$95, (%esi)
	je	L332
	cmpb	$46, (%esi)
	je	L332
	cmpb	$63, (%esi)
	je	L332
	cmpb	$64, (%esi)
	je	L332
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L332
	cmpb	$36, (%esi)
	je	L332
	cmpb	$35, (%esi)
	je	L332
	cmpb	$126, (%esi)
	je	L332
	movl	$0, -344(%ebp)
L332:
	incl	%esi
	cmpb	$0, (%esi)
	je	L329
	cmpb	$58, (%esi)
	jne	L333
L329:
	cmpl	$0, -344(%ebp)
	jne	L334
	movl	$1, (%esp)
	movl	$LC53, 4(%esp)
	jmp	L527
L334:
	cmpb	$58, (%esi)
	jne	L335
	movb	$0, (%esi)
	incl	%esi
	jmp	L336
L335:
	movl	$0, %esi
L336:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	_report_error, %eax
	movl	%eax, 8(%esp)
	call	_declare_as_global
	jmp	L433
L337:
	movl	-336(%ebp), %eax
	cmpb	$36, (%eax)
	jne	L338
	incl	%eax
	movl	%eax, -336(%ebp)
L338:
	cmpl	$1, _pass0
	jne	L339
	movl	-336(%ebp), %ebx
	movl	$1, -344(%ebp)
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L341
	cmpb	$95, (%ebx)
	je	L341
	cmpb	$46, (%ebx)
	je	L341
	cmpb	$63, (%ebx)
	je	L341
	cmpb	$64, (%ebx)
	je	L341
	movl	$0, -344(%ebp)
	jmp	L341
L346:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L345
	cmpb	$95, (%ebx)
	je	L345
	cmpb	$46, (%ebx)
	je	L345
	cmpb	$63, (%ebx)
	je	L345
	cmpb	$64, (%ebx)
	je	L345
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L345
	cmpb	$36, (%ebx)
	je	L345
	cmpb	$35, (%ebx)
	je	L345
	cmpb	$126, (%ebx)
	je	L345
	movl	$0, -344(%ebp)
L345:
	incl	%ebx
L341:
	cmpb	$0, (%ebx)
	je	L342
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L346
L342:
	cmpl	$0, -344(%ebp)
	jne	L347
	movl	$1, (%esp)
	movl	$LC54, 4(%esp)
	jmp	L527
L347:
	cmpb	$0, (%ebx)
	je	L348
	jmp	L521
L353:
	movb	$0, (%ebx)
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L350
L521:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L353
L350:
	movl	%ebx, %esi
	cmpb	$0, (%ebx)
	je	L355
	cmpb	$58, (%ebx)
	je	L519
L358:
	incl	%esi
	cmpb	$0, (%esi)
	je	L355
	cmpb	$58, (%esi)
	jne	L358
	jmp	L519
L355:
	cmpb	$58, (%esi)
	jne	L359
L519:
	movb	$0, (%esi)
	incl	%esi
	jmp	L360
L359:
	movl	$0, %esi
L360:
	movl	%ebx, (%esp)
	leal	-340(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_readnum
	movl	%eax, %ebx
	cmpl	$0, -340(%ebp)
	je	L361
	movl	$1, (%esp)
	movl	$LC55, 4(%esp)
	jmp	L527
L361:
	call	_seg_alloc
	movl	-336(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	movl	%ebx, 8(%esp)
	movl	%esi, 12(%esp)
	movl	_ofmt, %eax
	movl	%eax, 16(%esp)
	movl	_report_error, %eax
	movl	%eax, 20(%esp)
	call	_define_common
	jmp	L433
L348:
	movl	$1, (%esp)
	movl	$LC56, 4(%esp)
	jmp	L527
L339:
	cmpl	$2, _pass0
	jne	L433
	movl	-336(%ebp), %esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	je	L520
L371:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L370
	movb	$0, (%esi)
L370:
	incl	%esi
	cmpb	$0, (%esi)
	je	L367
	cmpb	$58, (%esi)
	jne	L371
	jmp	L520
L367:
	cmpb	$58, (%esi)
	jne	L433
L520:
	movb	$0, (%esi)
	incl	%esi
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	movl	$3, 12(%esp)
	movl	%esi, 16(%esp)
	movl	_ofmt, %eax
	call	*36(%eax)
	jmp	L433
L373:
	call	_stdscan_reset
	movl	-336(%ebp), %eax
	movl	%eax, _stdscan_bufptr
	movl	$-1, -328(%ebp)
	movl	$_stdscan, (%esp)
	movl	$0, 4(%esp)
	leal	-328(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	-364(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	_report_error, %eax
	movl	%eax, 20(%esp)
	movl	$0, 24(%esp)
	call	_evaluate
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L374
	movl	%eax, (%esp)
	call	_is_reloc
	testl	%eax, %eax
	jne	L375
	cmpl	$1, _pass0
	jne	L376
	movl	$1, %eax
	jmp	L377
L376:
	movl	$3, %eax
L377:
	movl	%eax, (%esp)
	movl	$LC57, 4(%esp)
	jmp	L522
L375:
	movl	%ebx, (%esp)
	call	_reloc_seg
	movl	%eax, _abs_seg
	movl	%ebx, (%esp)
	call	_reloc_value
	movl	%eax, _abs_offset
	jmp	L379
L374:
	cmpl	$1, -348(%ebp)
	jne	L380
	movl	$256, _abs_offset
	jmp	L379
L380:
	movl	$3, (%esp)
	movl	$LC58, 4(%esp)
L522:
	call	*_report_error
L379:
	movl	$1, _in_abs_seg
	movl	$-1, _location
	jmp	L433
L382:
	movl	-336(%ebp), %ebx
	leal	-104(%ebp), %esi
	movl	$1, -344(%ebp)
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L384
	cmpb	$95, (%ebx)
	je	L384
	cmpb	$46, (%ebx)
	je	L384
	cmpb	$63, (%ebx)
	je	L384
	cmpb	$64, (%ebx)
	je	L384
	movl	$0, -344(%ebp)
	jmp	L384
L389:
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isalpha
	testl	%eax, %eax
	jne	L388
	cmpb	$95, (%ebx)
	je	L388
	cmpb	$46, (%ebx)
	je	L388
	cmpb	$63, (%ebx)
	je	L388
	cmpb	$64, (%ebx)
	je	L388
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isdigit
	testl	%eax, %eax
	jne	L388
	cmpb	$36, (%ebx)
	je	L388
	cmpb	$35, (%ebx)
	je	L388
	cmpb	$126, (%ebx)
	je	L388
	movl	$0, -344(%ebp)
L388:
	movzbl	(%ebx), %eax
	movb	%al, (%esi)
	incl	%ebx
	incl	%esi
L384:
	cmpb	$0, (%ebx)
	je	L385
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L389
L385:
	movb	$0, (%esi)
	cmpl	$0, -344(%ebp)
	jne	L393
	cmpl	$1, -348(%ebp)
	setne	%al
	movzbl	%al, %eax
	leal	1(%eax,%eax), %eax
	movl	%eax, (%esp)
	movl	$LC59, 4(%esp)
	jmp	L527
L397:
	incl	%ebx
L393:
	cmpb	$0, (%ebx)
	je	L394
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L397
L394:
	movl	-352(%ebp), %eax
	cmpl	%eax, -348(%ebp)
	jne	L433
	movl	_ofmt, %eax
	movl	16(%eax), %edx
	leal	-104(%ebp), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	call	*20(%edx)
	jmp	L433
L399:
	cmpl	$1, -360(%ebp)
	jne	L433
	jmp	L401
L405:
	incl	-336(%ebp)
L401:
	movl	-336(%ebp), %eax
	cmpb	$0, (%eax)
	je	L402
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L405
L402:
	movl	-336(%ebp), %eax
	cmpb	$43, (%eax)
	je	L407
	cmpb	$45, (%eax)
	jne	L406
L407:
	movl	-336(%ebp), %eax
	cmpb	$45, (%eax)
	sete	%dl
	movzbl	%dl, %edx
	movl	%edx, -344(%ebp)
	incl	%eax
	movl	%eax, -336(%ebp)
	jmp	L408
L406:
	movl	$0, -344(%ebp)
L408:
	movl	$1, %ebx
L414:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	movl	_suppressed_names(,%ebx,4), %eax
	movl	%eax, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L410
	incl	%ebx
	cmpl	$5, %ebx
	jle	L414
	jmp	L415
L410:
	cmpl	$5, %ebx
	jg	L415
	movzbl	-344(%ebp), %eax
	movb	%al, _suppressed(%ebx)
	jmp	L433
L415:
	movl	$1, (%esp)
	movl	$LC60, 4(%esp)
	jmp	L527
L417:
	movl	-336(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_cpu
	movl	%eax, _cpu
	jmp	L433
L423:
	incl	-336(%ebp)
L419:
	movl	-336(%ebp), %eax
	cmpb	$0, (%eax)
	je	L420
	movsbl	(%eax),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L423
L420:
	movl	-336(%ebp), %eax
	cmpb	$43, (%eax)
	jne	L424
	movl	$0, _user_nolist
	jmp	L433
L424:
	movl	-336(%ebp), %eax
	cmpb	$45, (%eax)
	jne	L426
	movl	$1, _user_nolist
	jmp	L433
L426:
	movl	$1, (%esp)
	movl	$LC61, 4(%esp)
L527:
	call	*_report_error
	jmp	L433
L428:
	movl	-332(%ebp), %eax
	movl	%eax, (%esp)
	movl	-336(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-364(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	_ofmt, %eax
	call	*48(%eax)
	testl	%eax, %eax
	jne	L433
	cmpl	$1, -360(%ebp)
	setne	%al
	movzbl	%al, %eax
	leal	1(%eax,%eax), %eax
	movl	%eax, (%esp)
	movl	$LC62, 4(%esp)
	movl	-332(%ebp), %eax
L528:
	movl	%eax, 8(%esp)
	call	*_report_error
	jmp	L433
L286:
	movl	-360(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edi, 4(%esp)
	leal	-312(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	_report_error, %eax
	movl	%eax, 12(%esp)
	movl	$_evaluate, 16(%esp)
	movl	-368(%ebp), %eax
	movl	%eax, 20(%esp)
	call	_parse_line
	cmpl	$0, _optimizing
	jg	L442
	cmpl	$2, -348(%ebp)
	jne	L434
	cmpl	$0, _forwref
	je	L435
	movl	_globallineno, %edx
	movl	_forwref, %eax
	cmpl	(%eax), %edx
	jne	L435
	movl	$1, -120(%ebp)
L436:
	movl	_forwref, %eax
	movl	4(%eax), %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	orl	$1, -232(%ebp,%eax)
	movl	_forwrefs, %eax
	movl	%eax, (%esp)
	call	_saa_rstruct
	movl	%eax, _forwref
	testl	%eax, %eax
	je	L434
	movl	(%eax), %eax
	cmpl	_globallineno, %eax
	je	L436
	jmp	L434
L435:
	movl	$0, -120(%ebp)
L434:
	cmpl	$0, _optimizing
	jg	L442
	cmpl	$0, -120(%ebp)
	je	L442
	cmpl	$1, -348(%ebp)
	jne	L443
	movl	$0, %ebx
	cmpl	-280(%ebp), %ebx
	jge	L442
L449:
	leal	(%ebx,%ebx,2), %eax
	sall	$4, %eax
	testb	$1, -232(%ebp,%eax)
	je	L446
	movl	_forwrefs, %eax
	movl	%eax, (%esp)
	call	_saa_wstruct
	movl	_globallineno, %edx
	movl	%edx, (%eax)
	movl	%ebx, 4(%eax)
L446:
	incl	%ebx
	cmpl	-280(%ebp), %ebx
	jge	L442
	jmp	L449
L443:
	cmpl	$1, -280(%ebp)
	jle	L442
	testb	$1, -184(%ebp)
	je	L442
	andl	$-1082130433, -228(%ebp)
L442:
	cmpl	$119, -288(%ebp)
	jne	L452
	cmpl	$1, -360(%ebp)
	jne	L453
	cmpl	$0, -312(%ebp)
	jne	L454
	movl	$1, (%esp)
	movl	$LC63, 4(%esp)
	jmp	L526
L454:
	movl	-312(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L457
	cmpb	$46, 1(%eax)
	jne	L457
	cmpb	$64, 2(%eax)
	jne	L468
L457:
	cmpl	$1, -280(%ebp)
	jne	L458
	testb	$32, -275(%ebp)
	je	L458
	cmpl	$-1, -240(%ebp)
	jne	L458
	movl	-232(%ebp), %edx
	andl	$2, %edx
	movl	-312(%ebp), %eax
	movl	%eax, (%esp)
	movl	-248(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-244(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	%edx, 20(%esp)
	jmp	L525
L458:
	cmpl	$2, -280(%ebp)
	jne	L466
	movl	-276(%ebp), %eax
	andl	$8704, %eax
	cmpl	$8704, %eax
	jne	L466
	cmpl	$-1, -248(%ebp)
	jne	L466
	cmpl	$-1, -240(%ebp)
	jne	L466
	testb	$32, -227(%ebp)
	je	L466
	cmpl	$-1, -200(%ebp)
	jne	L466
	cmpl	$-1, -192(%ebp)
	jne	L466
	movl	-312(%ebp), %eax
	movl	%eax, (%esp)
	movl	-244(%ebp), %eax
	orl	$1073741824, %eax
	movl	%eax, 4(%esp)
	movl	-196(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
L525:
	movl	_ofmt, %eax
	movl	%eax, 24(%esp)
	movl	_report_error, %eax
	movl	%eax, 28(%esp)
	call	*-368(%ebp)
	jmp	L468
L453:
	movl	-312(%ebp), %eax
	cmpb	$46, (%eax)
	jne	L468
	cmpb	$46, 1(%eax)
	jne	L468
	cmpb	$64, 2(%eax)
	je	L468
	cmpl	$1, -280(%ebp)
	jne	L464
	testb	$32, -275(%ebp)
	je	L464
	movl	%eax, (%esp)
	movl	-248(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-244(%ebp), %eax
	jmp	L524
L464:
	cmpl	$2, -280(%ebp)
	jne	L466
	movl	-276(%ebp), %eax
	andl	$8704, %eax
	cmpl	$8704, %eax
	jne	L466
	cmpl	$-1, -248(%ebp)
	jne	L466
	testb	$32, -227(%ebp)
	je	L466
	cmpl	$-1, -200(%ebp)
	jne	L466
	movl	-312(%ebp), %eax
	movl	%eax, (%esp)
	movl	-244(%ebp), %eax
	orl	$1073741824, %eax
	movl	%eax, 4(%esp)
	movl	-196(%ebp), %eax
L524:
	movl	%eax, 8(%esp)
	movl	$0, 12(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	_ofmt, %eax
	movl	%eax, 24(%esp)
	movl	_report_error, %eax
	movl	%eax, 28(%esp)
	call	_define_label
	jmp	L468
L466:
	movl	$1, (%esp)
	movl	$LC64, 4(%esp)
L526:
	call	*_report_error
	jmp	L468
L452:
	cmpl	$1, -360(%ebp)
	jne	L469
	movl	_location, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	_sb, %eax
	movl	%eax, 8(%esp)
	movl	_cpu, %eax
	movl	%eax, 12(%esp)
	leal	-312(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	_report_error, %eax
	movl	%eax, 20(%esp)
	call	_insn_size
	movl	%eax, %ebx
	cmpl	$0, _using_debug_info
	je	L470
	movl	-280(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	movl	-288(%ebp), %eax
	cmpl	$116, %eax
	je	L478
	cmpl	$116, %eax
	jg	L486
	cmpl	$107, %eax
	je	L479
	cmpl	$107, %eax
	jg	L487
	cmpl	$106, %eax
	je	L477
	jmp	L484
L487:
	cmpl	$114, %eax
	je	L482
	cmpl	$115, %eax
	je	L483
	jmp	L484
L486:
	cmpl	$474, %eax
	je	L475
	cmpl	$474, %eax
	jg	L488
	cmpl	$472, %eax
	je	L472
	cmpl	$473, %eax
	je	L474
	jmp	L484
L488:
	cmpl	$475, %eax
	je	L476
	cmpl	$476, %eax
	je	L473
	jmp	L484
L472:
	movl	-244(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	jmp	L477
L473:
	movl	-244(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	jmp	L478
L474:
	movl	-244(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	jmp	L480
L475:
	movl	-244(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	jmp	L482
L476:
	movl	-244(%ebp), %eax
	movl	%eax, %edx
	sall	$8, %edx
	jmp	L483
L477:
	orl	$16, %edx
	jmp	L471
L478:
	orl	$24, %edx
	jmp	L471
L479:
	cmpl	$0, -128(%ebp)
	je	L480
	orl	$40, %edx
	jmp	L471
L480:
	orl	$32, %edx
	jmp	L471
L482:
	orl	$48, %edx
	jmp	L471
L483:
	orl	$56, %edx
	jmp	L471
L484:
	movl	$8, %edx
L471:
	movl	_ofmt, %eax
	movl	16(%eax), %eax
	movl	%edx, (%esp)
	call	*24(%eax)
L470:
	cmpl	$-1, %ebx
	je	L468
	addl	%ebx, %esi
	jmp	L529
L469:
	movl	_location, %eax
	movl	%eax, (%esp)
	movl	%esi, 4(%esp)
	movl	_sb, %eax
	movl	%eax, 8(%esp)
	movl	_cpu, %eax
	movl	%eax, 12(%esp)
	leal	-312(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	_ofmt, %eax
	movl	%eax, 20(%esp)
	movl	_report_error, %eax
	movl	%eax, 24(%esp)
	movl	$_nasmlist, 28(%esp)
	call	_assemble
	addl	%eax, %esi
L529:
	cmpl	$0, _in_abs_seg
	je	L493
	movl	%esi, _abs_offset
	jmp	L468
L493:
	movl	_offsets, %eax
	movl	%eax, (%esp)
	movl	_location, %eax
	movl	%eax, 4(%esp)
	movl	%esi, 8(%esp)
	call	_raa_write
	movl	%eax, _offsets
L468:
	leal	-312(%ebp), %eax
	movl	%eax, (%esp)
	call	_cleanup_insn
L433:
	movl	%edi, (%esp)
	call	_nasm_free
	cmpl	$0, _in_abs_seg
	jne	L495
L530:
	movl	_offsets, %eax
	movl	%eax, (%esp)
	movl	_location, %eax
	movl	%eax, 4(%esp)
	call	_raa_read
	movl	%eax, %esi
	jmp	L496
L495:
	movl	_abs_offset, %esi
L496:
	movl	%esi, _location+4
	movl	_preproc, %eax
	call	*4(%eax)
	movl	%eax, %edi
	testl	%eax, %eax
	jne	L497
	cmpl	$2, -360(%ebp)
	jne	L498
	cmpl	$0, _global_offset_changed
	je	L498
	movl	$1, (%esp)
	movl	$LC65, 4(%esp)
	call	*_report_error
L498:
	cmpl	$1, -360(%ebp)
	jne	L500
	movl	$1, (%esp)
	movl	_preproc, %eax
	call	*8(%eax)
	cmpl	$0, _terminate_after_phase
	je	L500
	movl	_ofile, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$_outname, (%esp)
	call	_remove
	cmpl	$0, _want_usage
	je	L501
	call	_usage
L501:
	movl	$1, (%esp)
	call	_exit
L500:
	incl	-356(%ebp)
	cmpl	$1, -348(%ebp)
	jle	L502
	cmpl	$0, _global_offset_changed
	jne	L502
	incl	_pass0
	cmpl	$2, _pass0
	jne	L268
	movl	-352(%ebp), %eax
	decl	%eax
	movl	%eax, -348(%ebp)
	jmp	L268
L502:
	cmpl	$0, _optimizing
	jg	L268
	incl	_pass0
L268:
	incl	-348(%ebp)
	movl	-352(%ebp), %eax
	cmpl	%eax, -348(%ebp)
	jg	L267
	cmpl	$2, _pass0
	jle	L506
L267:
	movl	$0, (%esp)
	movl	_preproc, %eax
	call	*8(%eax)
	call	*_nasmlist+4
	cmpl	$0, _optimizing
	jle	L263
	cmpl	$0, _opt_verbose_info
	je	L263
	movl	_stdout, %eax
	movl	%eax, (%esp)
	movl	$LC66, 4(%esp)
	movl	-356(%ebp), %eax
	subl	$2, %eax
	movl	%eax, 8(%esp)
	call	_fprintf
L263:
	addl	$396, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC67:
	.ascii "segment\0"
LC68:
	.ascii "section\0"
LC69:
	.ascii "extern\0"
LC70:
	.ascii "bits\0"
LC71:
	.ascii "global\0"
LC72:
	.ascii "common\0"
LC73:
	.ascii "absolute\0"
LC74:
	.ascii "debug\0"
LC75:
	.ascii "warning\0"
LC76:
	.ascii "cpu\0"
LC77:
	.ascii "list\0"
	.align 2
	.def	_getkw;	.scl	3;	.type	32;	.endef
_getkw:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edi
	movl	(%edi), %ebx
	cmpb	$32, (%ebx)
	je	L535
	cmpb	$9, (%ebx)
	jne	L576
L535:
	incl	%ebx
	cmpb	$32, (%ebx)
	je	L535
	cmpb	$9, (%ebx)
	je	L535
L576:
	cmpb	$91, (%ebx)
	jne	L584
	movl	%ebx, %esi
	cmpb	$0, (%ebx)
	je	L584
	cmpb	$93, (%ebx)
	je	L538
L541:
	incl	%esi
	cmpb	$0, (%esi)
	je	L584
	cmpb	$93, (%esi)
	jne	L541
L538:
	cmpb	$0, (%esi)
	je	L584
	movl	%esi, -16(%ebp)
	incl	%esi
	cmpb	$0, (%esi)
	je	L544
	cmpb	$59, (%esi)
	je	L544
L548:
	movsbl	(%esi),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	je	L584
	incl	%esi
	cmpb	$0, (%esi)
	je	L544
	cmpb	$59, (%esi)
	jne	L548
L544:
	movl	-16(%ebp), %eax
	movb	$0, 1(%eax)
	leal	1(%ebx), %esi
	movl	%esi, (%edi)
	cmpb	$0, (%ebx)
	je	L550
	cmpb	$32, (%ebx)
	je	L550
	cmpb	$93, (%ebx)
	je	L583
	cmpb	$9, (%ebx)
	je	L550
L553:
	incl	%ebx
	cmpb	$0, (%ebx)
	je	L550
	cmpb	$32, (%ebx)
	je	L550
	cmpb	$93, (%ebx)
	je	L583
	cmpb	$9, (%ebx)
	jne	L553
L550:
	cmpb	$93, (%ebx)
	jne	L554
L583:
	movb	$0, (%ebx)
	movl	12(%ebp), %eax
	movl	%ebx, (%eax)
	jmp	L555
L554:
	movb	$0, (%ebx)
L559:
	incl	%ebx
	movsbl	(%ebx),%eax
	movl	%eax, (%esp)
	call	_isspace
	testl	%eax, %eax
	jne	L559
	movl	12(%ebp), %eax
	movl	%ebx, (%eax)
	cmpb	$93, (%ebx)
	je	L581
L563:
	incl	%ebx
	cmpb	$93, (%ebx)
	jne	L563
L581:
	movb	$0, (%ebx)
L555:
	movl	%esi, (%esp)
	movl	$LC67, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L565
	movl	%esi, (%esp)
	movl	$LC68, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L564
L565:
	movl	$1, %edx
	jmp	L531
L564:
	movl	%esi, (%esp)
	movl	$LC69, 4(%esp)
	call	_nasm_stricmp
	movl	$2, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC70, 4(%esp)
	call	_nasm_stricmp
	movl	$3, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC71, 4(%esp)
	call	_nasm_stricmp
	movl	$4, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC72, 4(%esp)
	call	_nasm_stricmp
	movl	$5, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC73, 4(%esp)
	call	_nasm_stricmp
	movl	$6, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC74, 4(%esp)
	call	_nasm_stricmp
	movl	$7, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC75, 4(%esp)
	call	_nasm_stricmp
	movl	$8, %edx
	testl	%eax, %eax
	je	L531
	movl	%esi, (%esp)
	movl	$LC76, 4(%esp)
	call	_nasm_stricmp
	movl	$9, %edx
	testl	%eax, %eax
	je	L531
	jmp	L573
L584:
	movl	$0, %edx
	jmp	L531
L573:
	movl	%esi, (%esp)
	movl	$LC77, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %edx
	decl	%edx
	orl	$10, %edx
L531:
	movl	%edx, %eax
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC78:
	.ascii "nasm: \0"
LC79:
	.ascii "%s:%ld: \0"
	.align 2
	.def	_report_error_gnu;	.scl	3;	.type	32;	.endef
_report_error_gnu:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_is_suppressed_warning
	testl	%eax, %eax
	jne	L585
	testl	$16, %ebx
	je	L587
	movl	$LC78, (%esp)
	movl	_error_file, %eax
	movl	%eax, 4(%esp)
	call	_fputs
	jmp	L588
L587:
	movl	$0, -12(%ebp)
	movl	$0, -8(%ebp)
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_src_get
	movl	_error_file, %eax
	movl	%eax, (%esp)
	movl	$LC79, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-8(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L588:
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	leal	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	___va_start
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_report_error_common
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	___va_end
L585:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
LC80:
	.ascii "%s(%ld) : \0"
	.align 2
	.def	_report_error_vc;	.scl	3;	.type	32;	.endef
_report_error_vc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_is_suppressed_warning
	testl	%eax, %eax
	jne	L589
	testl	$16, %ebx
	je	L591
	movl	$LC78, (%esp)
	movl	_error_file, %eax
	movl	%eax, 4(%esp)
	call	_fputs
	jmp	L592
L591:
	movl	$0, -12(%ebp)
	movl	$0, -8(%ebp)
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_src_get
	movl	_error_file, %eax
	movl	%eax, (%esp)
	movl	$LC80, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-8(%ebp), %eax
	movl	%eax, 12(%esp)
	call	_fprintf
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_nasm_free
L592:
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	leal	12(%ebp), %eax
	movl	%eax, 4(%esp)
	call	___va_start
	movl	%ebx, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_report_error_common
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	___va_end
L589:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_is_suppressed_warning;	.scl	3;	.type	32;	.endef
_is_suppressed_warning:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	$0, %ecx
	testl	$15, %edx
	jne	L596
	movl	%edx, %eax
	andl	$-256, %eax
	testw	%ax, %ax
	je	L596
	movzbl	%dh, %eax
	cmpb	$0, _suppressed(%eax)
	jne	L595
L596:
	testl	$64, %edx
	je	L594
	cmpl	$2, _pass0
	jne	L594
L595:
	movl	$1, %ecx
L594:
	movl	%ecx, %eax
	popl	%ebp
	ret
LC81:
	.ascii "warning: \0"
LC82:
	.ascii "error: \0"
LC83:
	.ascii "fatal: \0"
LC84:
	.ascii "panic: \0"
LC85:
	.ascii "debug: \0"
	.align 2
	.def	_report_error_common;	.scl	3;	.type	32;	.endef
_report_error_common:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, %eax
	andl	$15, %eax
	cmpl	$8, %eax
	ja	L598
	jmp	*L604(,%eax,4)
	.align 4
	.align 4
L604:
	.long	L599
	.long	L600
	.long	L601
	.long	L602
	.long	L598
	.long	L598
	.long	L598
	.long	L598
	.long	L603
L599:
	movl	$LC81, (%esp)
	jmp	L617
L600:
	movl	$LC82, (%esp)
	jmp	L617
L601:
	movl	$LC83, (%esp)
	jmp	L617
L602:
	movl	$LC84, (%esp)
	jmp	L617
L603:
	movl	$LC85, (%esp)
L617:
	movl	_error_file, %eax
	movl	%eax, 4(%esp)
	call	_fputs
L598:
	movl	_error_file, %eax
	movl	%eax, (%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_vfprintf
	movl	$10, (%esp)
	movl	_error_file, %eax
	movl	%eax, 4(%esp)
	call	_fputc
	testl	$32, %ebx
	je	L606
	movl	$1, _want_usage
L606:
	movl	%ebx, %eax
	andl	$15, %eax
	cmpl	$8, %eax
	ja	L597
	jmp	*L615(,%eax,4)
	.align 4
	.align 4
L615:
	.long	L597
	.long	L610
	.long	L611
	.long	L614
	.long	L597
	.long	L597
	.long	L597
	.long	L597
	.long	L597
L610:
	movl	$1, _terminate_after_phase
	jmp	L597
L611:
	cmpl	$0, _ofile
	je	L612
	movl	_ofile, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$_outname, (%esp)
	call	_remove
L612:
	cmpl	$0, _want_usage
	je	L613
	call	_usage
L613:
	movl	$1, (%esp)
	jmp	L618
L614:
	movl	$0, (%esp)
	call	_fflush
	movl	$3, (%esp)
L618:
	call	_exit
L597:
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
LC86:
	.ascii "type `nasm -h' for help\12\0"
	.align 2
	.def	_usage;	.scl	3;	.type	32;	.endef
_usage:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$LC86, (%esp)
	movl	_error_file, %eax
	movl	%eax, 4(%esp)
	call	_fputs
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.def	_register_output_formats;	.scl	3;	.type	32;	.endef
_register_output_formats:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_report_error, %eax
	movl	%eax, (%esp)
	call	_ofmt_register
	movl	%eax, _ofmt
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC87:
	.ascii "unable to open input file `%s'\0"
	.align 2
	.def	_no_pp_reset;	.scl	3;	.type	32;	.endef
_no_pp_reset:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_nasm_strdup
	movl	%eax, (%esp)
	call	_src_set_fname
	movl	$0, (%esp)
	call	_src_set_linnum
	movl	$1, _no_pp_lineinc
	movl	16(%ebp), %eax
	movl	%eax, _no_pp_err
	movl	%ebx, (%esp)
	movl	$LC46, 4(%esp)
	call	_fopen
	movl	%eax, _no_pp_fp
	testl	%eax, %eax
	jne	L622
	movl	$18, (%esp)
	movl	$LC87, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_no_pp_err
L622:
	movl	24(%ebp), %eax
	movl	%eax, _no_pp_list
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
LC88:
	.ascii "%line\0"
LC89:
	.ascii "%ld+%d %s\0"
	.align 2
	.def	_no_pp_getline;	.scl	3;	.type	32;	.endef
_no_pp_getline:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	$512, -24(%ebp)
	movl	$512, (%esp)
	call	_nasm_malloc
	movl	%eax, %edi
	call	_src_get_linnum
	addl	_no_pp_lineinc, %eax
	movl	%eax, (%esp)
	call	_src_set_linnum
L637:
	movl	%edi, %ebx
L633:
	movl	%ebx, (%esp)
	movl	%ebx, %eax
	subl	%edi, %eax
	movl	-24(%ebp), %edx
	subl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	_no_pp_fp, %eax
	movl	%eax, 8(%esp)
	call	_fgets
	movl	%eax, %esi
	testl	%eax, %eax
	je	L638
	movl	%ebx, (%esp)
	call	_strlen
	addl	%eax, %ebx
	cmpl	%edi, %ebx
	jbe	L631
	cmpb	$10, -1(%ebx)
	je	L628
L631:
	movl	%ebx, %esi
	subl	%edi, %esi
	movl	-24(%ebp), %eax
	subl	$10, %eax
	cmpl	%eax, %esi
	jle	L633
	addl	$512, -24(%ebp)
	movl	%edi, (%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_nasm_realloc
	movl	%eax, %edi
	leal	(%esi,%eax), %ebx
	jmp	L633
L628:
	testl	%esi, %esi
	jne	L634
L638:
	cmpl	%edi, %ebx
	jne	L634
	movl	%edi, (%esp)
	call	_nasm_free
	movl	$0, %eax
	jmp	L623
L634:
	movl	%edi, (%esp)
	movl	$LC44, 4(%esp)
	call	_strcspn
	movb	$0, (%eax,%edi)
	movl	%edi, (%esp)
	movl	$LC88, 4(%esp)
	movl	$5, 8(%esp)
	call	_strncmp
	testl	%eax, %eax
	jne	L625
	movl	%edi, (%esp)
	call	_strlen
	movl	%eax, (%esp)
	call	_nasm_malloc
	movl	%eax, %ebx
	leal	5(%edi), %eax
	movl	%eax, (%esp)
	movl	$LC89, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%ebx, 16(%esp)
	call	_sscanf
	cmpl	$3, %eax
	jne	L636
	movl	%ebx, (%esp)
	call	_src_set_fname
	movl	%eax, (%esp)
	call	_nasm_free
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_src_set_linnum
	movl	-20(%ebp), %eax
	movl	%eax, _no_pp_lineinc
	jmp	L637
L636:
	movl	%ebx, (%esp)
	call	_nasm_free
L625:
	movl	$0, (%esp)
	movl	%edi, 4(%esp)
	movl	_no_pp_list, %eax
	call	*12(%eax)
	movl	%edi, %eax
L623:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_no_pp_cleanup;	.scl	3;	.type	32;	.endef
_no_pp_cleanup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_no_pp_fp, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	%ebp, %esp
	popl	%ebp
	ret
LC90:
	.ascii "8086\0"
LC91:
	.ascii "186\0"
LC92:
	.ascii "286\0"
LC93:
	.ascii "386\0"
LC94:
	.ascii "486\0"
LC95:
	.ascii "586\0"
LC96:
	.ascii "pentium\0"
LC97:
	.ascii "686\0"
LC98:
	.ascii "ppro\0"
LC99:
	.ascii "pentiumpro\0"
LC100:
	.ascii "p2\0"
LC101:
	.ascii "p3\0"
LC102:
	.ascii "katmai\0"
LC103:
	.ascii "p4\0"
LC104:
	.ascii "willamette\0"
LC105:
	.ascii "prescott\0"
LC106:
	.ascii "ia64\0"
LC107:
	.ascii "ia-64\0"
LC108:
	.ascii "itanium\0"
LC109:
	.ascii "itanic\0"
LC110:
	.ascii "merced\0"
LC111:
	.ascii "unknown 'cpu' type\0"
	.align 2
	.def	_get_cpu;	.scl	3;	.type	32;	.endef
_get_cpu:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	$LC90, 4(%esp)
	call	_strcmp
	movl	$0, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC91, 4(%esp)
	call	_strcmp
	movl	$16777216, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC92, 4(%esp)
	call	_strcmp
	movl	$33554432, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC93, 4(%esp)
	call	_strcmp
	movl	$50331648, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC94, 4(%esp)
	call	_strcmp
	movl	$67108864, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC95, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L647
	movl	%ebx, (%esp)
	movl	$LC96, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L646
L647:
	movl	$83886080, %edx
	jmp	L640
L646:
	movl	%ebx, (%esp)
	movl	$LC97, 4(%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L649
	movl	%ebx, (%esp)
	movl	$LC98, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L649
	movl	%ebx, (%esp)
	movl	$LC99, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L649
	movl	%ebx, (%esp)
	movl	$LC100, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L648
L649:
	movl	$100663296, %edx
	jmp	L640
L648:
	movl	%ebx, (%esp)
	movl	$LC101, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L651
	movl	%ebx, (%esp)
	movl	$LC102, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L650
L651:
	movl	$117440512, %edx
	jmp	L640
L650:
	movl	%ebx, (%esp)
	movl	$LC103, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L653
	movl	%ebx, (%esp)
	movl	$LC104, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	jne	L652
L653:
	movl	$134217728, %edx
	jmp	L640
L652:
	movl	%ebx, (%esp)
	movl	$LC105, 4(%esp)
	call	_nasm_stricmp
	movl	$150994944, %edx
	testl	%eax, %eax
	je	L640
	movl	%ebx, (%esp)
	movl	$LC106, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L659
	movl	%ebx, (%esp)
	movl	$LC107, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L659
	movl	%ebx, (%esp)
	movl	$LC108, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L659
	movl	%ebx, (%esp)
	movl	$LC109, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L659
	movl	%ebx, (%esp)
	movl	$LC110, 4(%esp)
	call	_nasm_stricmp
	testl	%eax, %eax
	je	L659
	cmpl	$1, _pass0
	jg	L657
	movl	$1, %eax
	jmp	L658
L657:
	movl	$2, %eax
L658:
	movl	%eax, (%esp)
	movl	$LC111, 4(%esp)
	call	*_report_error
L659:
	movl	$251658240, %edx
L640:
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 32
LC112:
	.ascii "cannot specify 32-bit segment on processor below a 386\0"
	.align 32
LC113:
	.ascii "`%s' is not a valid segment size; must be 16 or 32\0"
	.align 2
	.def	_get_bits;	.scl	3;	.type	32;	.endef
_get_bits:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -4(%ebp)
	movl	8(%ebp), %ebx
	movl	%ebx, (%esp)
	call	_atoi
	movl	$16, %edx
	cmpl	$16, %eax
	je	L660
	cmpl	$32, %eax
	jne	L663
	cmpl	$50331647, _cpu
	ja	L662
	movl	$1, (%esp)
	movl	$LC112, 4(%esp)
	call	*_report_error
	jmp	L668
L663:
	cmpl	$1, _pass0
	jg	L666
	movl	$1, %eax
	jmp	L667
L666:
	movl	$2, %eax
L667:
	movl	%eax, (%esp)
	movl	$LC113, 4(%esp)
	movl	%ebx, 8(%esp)
	call	*_report_error
L668:
	movl	$16, %eax
L662:
	movl	%eax, %edx
L660:
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
	.comm	_pass0, 16	 # 4
.lcomm _report_error,16
.lcomm _using_debug_info,16
.lcomm _opt_verbose_info,16
.lcomm _inname,256
.lcomm _outname,256
.lcomm _listname,256
.lcomm _globallineno,16
.lcomm _error_file,16
.lcomm _sb,16
	.comm	_global_offset_changed, 16	 # 4
.lcomm _location,16
	.comm	_in_abs_seg, 16	 # 4
	.comm	_abs_seg, 16	 # 4
	.comm	_abs_offset, 16	 # 4
.lcomm _offsets,16
.lcomm _forwrefs,16
.lcomm _forwref,16
.lcomm _preproc,16
.lcomm _operating_mode,16
.lcomm _want_usage,16
.lcomm _terminate_after_phase,16
.lcomm _no_pp_fp,16
.lcomm _no_pp_err,16
.lcomm _no_pp_list,16
.lcomm _no_pp_lineinc,16
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_sscanf;	.scl	2;	.type	32;	.endef
	.def	_strncmp;	.scl	2;	.type	32;	.endef
	.def	_strcspn;	.scl	2;	.type	32;	.endef
	.def	_src_get_linnum;	.scl	2;	.type	32;	.endef
	.def	_src_set_linnum;	.scl	2;	.type	32;	.endef
	.def	_src_set_fname;	.scl	2;	.type	32;	.endef
	.def	_ofmt_register;	.scl	2;	.type	32;	.endef
	.def	_fputs;	.scl	2;	.type	32;	.endef
	.def	_fflush;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_remove;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_vfprintf;	.scl	2;	.type	32;	.endef
	.def	___va_end;	.scl	2;	.type	32;	.endef
	.def	___va_start;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_isspace;	.scl	2;	.type	32;	.endef
	.def	_cleanup_insn;	.scl	2;	.type	32;	.endef
	.def	_assemble;	.scl	2;	.type	32;	.endef
	.def	_raa_write;	.scl	2;	.type	32;	.endef
	.def	_insn_size;	.scl	2;	.type	32;	.endef
	.def	_saa_wstruct;	.scl	2;	.type	32;	.endef
	.def	_parse_line;	.scl	2;	.type	32;	.endef
	.def	_reloc_value;	.scl	2;	.type	32;	.endef
	.def	_reloc_seg;	.scl	2;	.type	32;	.endef
	.def	_is_reloc;	.scl	2;	.type	32;	.endef
	.def	_stdscan;	.scl	2;	.type	32;	.endef
	.def	_stdscan_reset;	.scl	2;	.type	32;	.endef
	.def	_define_common;	.scl	2;	.type	32;	.endef
	.def	_readnum;	.scl	2;	.type	32;	.endef
	.def	_seg_alloc;	.scl	2;	.type	32;	.endef
	.def	_declare_as_global;	.scl	2;	.type	32;	.endef
	.def	_is_extern;	.scl	2;	.type	32;	.endef
	.def	_isalpha;	.scl	2;	.type	32;	.endef
	.def	_raa_read;	.scl	2;	.type	32;	.endef
	.def	_saa_rstruct;	.scl	2;	.type	32;	.endef
	.def	_saa_rewind;	.scl	2;	.type	32;	.endef
	.def	_redefine_label;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_nasm_strdup;	.scl	2;	.type	32;	.endef
	.def	_getenv;	.scl	2;	.type	32;	.endef
	.def	_nasm_realloc;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_nasm_malloc;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_dfmt_list;	.scl	2;	.type	32;	.endef
	.def	_ofmt_list;	.scl	2;	.type	32;	.endef
	.def	_nasm_stricmp;	.scl	2;	.type	32;	.endef
	.def	_dfmt_find;	.scl	2;	.type	32;	.endef
	.def	_pp_include_path;	.scl	2;	.type	32;	.endef
	.def	_pp_pre_undefine;	.scl	2;	.type	32;	.endef
	.def	_pp_pre_include;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
	.def	_isdigit;	.scl	2;	.type	32;	.endef
	.def	_ofmt_find;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_nasmlib_cleanup;	.scl	2;	.type	32;	.endef
	.def	_eval_cleanup;	.scl	2;	.type	32;	.endef
	.def	_saa_free;	.scl	2;	.type	32;	.endef
	.def	_raa_free;	.scl	2;	.type	32;	.endef
	.def	_cleanup_labels;	.scl	2;	.type	32;	.endef
	.def	_define_label;	.scl	2;	.type	32;	.endef
	.def	_init_labels;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_src_get;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_putc;	.scl	2;	.type	32;	.endef
	.def	_nasm_free;	.scl	2;	.type	32;	.endef
	.def	_evaluate;	.scl	2;	.type	32;	.endef
	.def	_pp_pre_define;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_lookup_label;	.scl	2;	.type	32;	.endef
	.def	_eval_global_info;	.scl	2;	.type	32;	.endef
	.def	_parser_global_info;	.scl	2;	.type	32;	.endef
	.def	_pp_extra_stdmac;	.scl	2;	.type	32;	.endef
	.def	_seg_init;	.scl	2;	.type	32;	.endef
	.def	_saa_init;	.scl	2;	.type	32;	.endef
	.def	_raa_init;	.scl	2;	.type	32;	.endef
	.def	_nasm_set_malloc_error;	.scl	2;	.type	32;	.endef
