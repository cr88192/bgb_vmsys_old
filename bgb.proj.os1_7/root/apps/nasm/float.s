	.file	"float.c"
	.text
	.align 2
	.def	_multiply;	.scl	3;	.type	32;	.endef
_multiply:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	$0, %esi
L6:
	movl	$0, -72(%ebp,%esi,4)
	incl	%esi
	cmpl	$11, %esi
	jle	L6
	movl	$0, %esi
L16:
	movl	$0, %ebx
	movl	8(%ebp), %eax
	movzwl	(%eax,%esi,2), %edi
L15:
	movl	12(%ebp), %edx
	movzwl	(%edx,%ebx,2), %eax
	imull	%edi, %eax
	leal	(%ebx,%esi), %edx
	movl	%eax, %ecx
	shrl	$16, %ecx
	addl	%ecx, -72(%ebp,%edx,4)
	andl	$65535, %eax
	addl	%eax, -68(%ebp,%edx,4)
	incl	%ebx
	cmpl	$5, %ebx
	jle	L15
	incl	%esi
	cmpl	$5, %esi
	jle	L16
	movl	$11, %esi
L21:
	movl	-72(%ebp,%esi,4), %eax
	movl	%eax, %edx
	shrl	$16, %edx
	addl	%edx, -76(%ebp,%esi,4)
	andl	$65535, %eax
	movl	%eax, -72(%ebp,%esi,4)
	decl	%esi
	jne	L21
	movl	-72(%ebp), %eax
	andl	$-32768, %eax
	movl	$0, %esi
	testw	%ax, %ax
	je	L33
L27:
	movl	-72(%ebp,%esi,4), %eax
	movl	8(%ebp), %edx
	movw	%ax, (%edx,%esi,2)
	incl	%esi
	movl	$0, %eax
	cmpl	$5, %esi
	jg	L1
	jmp	L27
L33:
	movl	-72(%ebp,%esi,4), %edx
	movl	-68(%ebp,%esi,4), %eax
	shrl	$15, %eax
	andl	$1, %eax
	leal	(%eax,%edx,2), %edx
	movl	8(%ebp), %eax
	movw	%dx, (%eax,%esi,2)
	incl	%esi
	cmpl	$5, %esi
	jle	L33
	movl	$-1, %eax
L1:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC0:
	.ascii "too many periods in floating-point constant\0"
	.align 32
LC1:
	.ascii "floating-point constant: `%c' is invalid character\0"
	.align 2
	.def	_flconvert;	.scl	3;	.type	32;	.endef
_flconvert:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	movl	8(%ebp), %edx
	movl	20(%ebp), %ebx
	leal	-56(%ebp), %esi
	movl	$0, -80(%ebp)
	movl	$0, %ecx
	movl	$0, -88(%ebp)
	cmpb	$0, (%edx)
	je	L63
	cmpb	$69, (%edx)
	je	L48
	cmpb	$101, (%edx)
	je	L48
L62:
	cmpb	$46, (%edx)
	jne	L51
	testl	%ecx, %ecx
	jne	L52
	movl	$1, %ecx
	jmp	L54
L52:
	movl	$1, (%esp)
	movl	$LC0, 4(%esp)
	call	*%ebx
	jmp	L46
L51:
	movzbl	(%edx), %eax
	subb	$48, %al
	cmpb	$9, %al
	ja	L55
	cmpb	$48, (%edx)
	jne	L56
	cmpl	$0, -88(%ebp)
	jne	L56
	testl	%ecx, %ecx
	je	L54
	decl	-80(%ebp)
	jmp	L54
L56:
	movl	$1, -88(%ebp)
	leal	-28(%ebp), %eax
	cmpl	%eax, %esi
	jae	L59
	movzbl	(%edx), %eax
	subb	$48, %al
	movb	%al, (%esi)
	incl	%esi
L59:
	testl	%ecx, %ecx
	jne	L54
	incl	-80(%ebp)
	jmp	L54
L55:
	movl	$1, (%esp)
	movl	$LC1, 4(%esp)
	movsbl	(%edx),%eax
	movl	%eax, 8(%esp)
	call	*%ebx
	jmp	L46
L54:
	incl	%edx
	cmpb	$0, (%edx)
	je	L63
	cmpb	$69, (%edx)
	je	L48
	cmpb	$101, (%edx)
	jne	L62
L48:
	cmpb	$0, (%edx)
	je	L63
	incl	%edx
	movl	%edx, (%esp)
	call	_atoi
	addl	%eax, -80(%ebp)
L63:
	movl	$32768, -76(%ebp)
	movl	12(%ebp), %ecx
	movl	%ecx, %eax
	addl	$12, %eax
	movl	%eax, %edx
	cmpl	%eax, %ecx
	jae	L112
L68:
	movw	$0, (%ecx)
	addl	$2, %ecx
	cmpl	%edx, %ecx
	jb	L68
L112:
	movl	12(%ebp), %ecx
	leal	-56(%ebp), %edi
	movl	$0, -88(%ebp)
	movl	$0, -84(%ebp)
	movl	%ecx, %eax
	addl	$12, %eax
	cmpl	%eax, %ecx
	jae	L70
L90:
	movl	$0, %ebx
	cmpl	%edi, %esi
	jbe	L70
	cmpb	$0, -1(%esi)
	jne	L73
L76:
	decl	%esi
	cmpl	%edi, %esi
	jbe	L70
	cmpb	$0, -1(%esi)
	je	L76
L73:
	cmpl	%edi, %esi
	jbe	L70
	leal	-1(%esi), %edx
L84:
	movsbl	(%edx),%eax
	leal	(%ebx,%eax,2), %eax
	cmpl	$9, %eax
	jle	L82
	movl	$1, %ebx
	subl	$10, %eax
	jmp	L83
L82:
	movl	$0, %ebx
L83:
	movb	%al, (%edx)
	movl	%edx, %eax
	decl	%edx
	cmpl	%edi, %eax
	ja	L84
	testw	%bx, %bx
	je	L85
	movzwl	(%ecx), %eax
	orl	-76(%ebp), %eax
	movw	%ax, (%ecx)
	movl	$1, -88(%ebp)
L85:
	cmpl	$0, -88(%ebp)
	je	L86
	cmpw	$1, -76(%ebp)
	jne	L87
	movl	$32768, -76(%ebp)
	addl	$2, %ecx
	jmp	L69
L87:
	shrl	-76(%ebp)
	jmp	L69
L86:
	decl	-84(%ebp)
L69:
	movl	12(%ebp), %eax
	addl	$12, %eax
	cmpl	%eax, %ecx
	jb	L90
L70:
	movl	-80(%ebp), %eax
	addl	%eax, -84(%ebp)
	testl	%eax, %eax
	jns	L91
	leal	-72(%ebp), %ecx
	leal	-60(%ebp), %eax
	movl	%eax, %edx
	cmpl	%eax, %ecx
	jae	L118
L96:
	movw	$-13108, (%ecx)
	addl	$2, %ecx
	cmpl	%edx, %ecx
	jb	L96
L118:
	movl	$-2, %ebx
	negl	-80(%ebp)
	jmp	L97
L91:
	cmpl	$0, -80(%ebp)
	jle	L98
	movw	$-24576, -72(%ebp)
	leal	-70(%ebp), %ecx
	leal	-60(%ebp), %eax
	movl	%eax, %edx
	cmpl	%eax, %ecx
	jae	L120
L103:
	movw	$0, (%ecx)
	addl	$2, %ecx
	cmpl	%edx, %ecx
	jb	L103
L120:
	movl	$3, %ebx
	jmp	L97
L98:
	movl	$0, %ebx
L97:
	cmpl	$0, -80(%ebp)
	je	L122
	leal	-72(%ebp), %esi
L109:
	testl	$1, -80(%ebp)
	je	L108
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	leal	-72(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_multiply
	leal	(%eax,%ebx), %eax
	addl	%eax, -84(%ebp)
L108:
	addl	%ebx, %ebx
	movl	%esi, (%esp)
	movl	%esi, 4(%esp)
	call	_multiply
	addl	%eax, %ebx
	sarl	-80(%ebp)
	jne	L109
L122:
	movl	16(%ebp), %eax
	movl	-84(%ebp), %edx
	movl	%edx, (%eax)
L46:
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_shr;	.scl	3;	.type	32;	.endef
_shr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %edi
	movl	$0, %esi
	movl	$0, -16(%ebp)
	movl	$16, %eax
	movl	%eax, %ebx
	subl	%edi, %ebx
L128:
	movl	-16(%ebp), %edx
	movl	8(%ebp), %ecx
	movzwl	(%ecx,%edx,2), %eax
	movl	%eax, %edx
	movb	%bl, %cl
	sall	%cl, %edx
	movl	%edi, %ecx
	sarl	%cl, %eax
	orl	%esi, %eax
	movl	-16(%ebp), %esi
	movl	8(%ebp), %ecx
	movw	%ax, (%ecx,%esi,2)
	movzwl	%dx, %esi
	incl	-16(%ebp)
	cmpl	$5, -16(%ebp)
	jle	L128
	addl	$4, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_round;	.scl	3;	.type	32;	.endef
_round:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	movzwl	(%ecx,%edx,2), %eax
	andl	$-32768, %eax
	testw	%ax, %ax
	je	L132
L133:
	decl	%edx
	movzwl	(%ecx,%edx,2), %eax
	incl	%eax
	movw	%ax, (%ecx,%edx,2)
	testl	%edx, %edx
	jle	L134
	testw	%ax, %ax
	je	L133
L134:
	movl	$0, %eax
	testl	%edx, %edx
	jne	L131
	cmpw	$0, (%ecx)
	jne	L131
	movl	$1, %eax
	jmp	L131
L132:
	movl	$0, %eax
L131:
	popl	%ebp
	ret
	.align 32
LC2:
	.ascii "overflow in floating-point constant\0"
	.align 2
	.def	_to_double;	.scl	3;	.type	32;	.endef
_to_double:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	12(%ebp), %edi
	movl	20(%ebp), %esi
	movl	%edi, %eax
	shrl	$31, %eax
	decl	%eax
	andl	$-32768, %eax
	leal	32768(%eax), %edi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %ebx
	movl	%ebx, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%esi, 12(%esp)
	call	_flconvert
	movl	-40(%ebp), %eax
	andl	$-32768, %eax
	testw	%ax, %ax
	je	L142
	decl	-44(%ebp)
	movl	-44(%ebp), %edx
	leal	1022(%edx), %eax
	cmpl	$2046, %eax
	ja	L143
	leal	1023(%edx), %eax
	movl	%eax, -44(%ebp)
	movl	%ebx, (%esp)
	movl	$11, 4(%esp)
	call	_shr
	movl	%ebx, (%esp)
	movl	$4, 4(%esp)
	call	_round
	movl	-40(%ebp), %eax
	andl	$32, %eax
	testw	%ax, %ax
	je	L144
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	incl	-44(%ebp)
L144:
	movl	-40(%ebp), %eax
	andl	$15, %eax
	movw	%ax, -40(%ebp)
	movl	-44(%ebp), %edx
	sall	$4, %edx
	movzbl	-40(%ebp), %eax
	orb	%dl, %al
	orl	%edi, %eax
	movl	16(%ebp), %ecx
	movb	%al, 6(%ecx)
	movzwl	-40(%ebp), %eax
	orl	%eax, %edx
	orl	%edi, %edx
	sarl	$8, %edx
	movb	%dl, 7(%ecx)
	movzbl	-38(%ebp), %eax
	movb	%al, 4(%ecx)
	movzbl	-37(%ebp), %eax
	movb	%al, 5(%ecx)
	movzbl	-36(%ebp), %eax
	movb	%al, 2(%ecx)
	movzbl	-35(%ebp), %eax
	movb	%al, 3(%ecx)
	movzbl	-34(%ebp), %eax
	movb	%al, (%ecx)
	movzbl	-33(%ebp), %eax
	jmp	L174
L143:
	movl	-44(%ebp), %edx
	leal	1074(%edx), %eax
	cmpl	$51, %eax
	ja	L146
	addl	$1011, %edx
	negl	%edx
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L147
	leal	15(%edx), %eax
L147:
	andl	$-16, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, -48(%ebp)
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L148
	addl	$15, %eax
L148:
	movl	%eax, %esi
	sarl	$4, %esi
	leal	-40(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	-48(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_shr
	movl	%ebx, (%esp)
	movl	$4, %eax
	subl	%esi, %eax
	movl	%eax, 4(%esp)
	call	_round
	testl	%eax, %eax
	jne	L150
	cmpl	$0, -48(%ebp)
	jle	L149
	movzwl	-40(%ebp), %edx
	movl	-48(%ebp), %ecx
	decl	%ecx
	movl	$32768, %eax
	sarl	%cl, %eax
	testl	%eax, %edx
	je	L149
L150:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	cmpl	$0, -48(%ebp)
	jne	L151
	movl	-40(%ebp), %eax
	orl	$-32768, %eax
	movw	%ax, -40(%ebp)
L151:
	incl	-44(%ebp)
L149:
	movl	%edi, %eax
	testl	%esi, %esi
	jne	L153
	movzbl	-40(%ebp), %eax
	orl	%edi, %eax
L153:
	movl	16(%ebp), %edx
	movb	%al, 6(%edx)
	testl	%esi, %esi
	jne	L154
	movzwl	-40(%ebp), %eax
	orl	%edi, %eax
	jmp	L172
L154:
	movl	%edi, %eax
L172:
	shrl	$8, %eax
	movl	16(%ebp), %ecx
	movb	%al, 7(%ecx)
	cmpl	$1, %esi
	jg	L156
	movl	$1, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L157
L156:
	movb	$0, %al
L157:
	movl	16(%ebp), %edx
	movb	%al, 4(%edx)
	cmpl	$1, %esi
	jg	L158
	movl	$1, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L159
L158:
	movb	$0, %al
L159:
	movl	16(%ebp), %ecx
	movb	%al, 5(%ecx)
	cmpl	$2, %esi
	jg	L160
	movl	$2, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L161
L160:
	movb	$0, %al
L161:
	movl	16(%ebp), %edx
	movb	%al, 2(%edx)
	cmpl	$2, %esi
	jg	L162
	movl	$2, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L163
L162:
	movb	$0, %al
L163:
	movl	16(%ebp), %ecx
	movb	%al, 3(%ecx)
	cmpl	$3, %esi
	jg	L164
	movl	$3, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L165
L164:
	movb	$0, %al
L165:
	movl	16(%ebp), %edx
	movb	%al, (%edx)
	cmpl	$3, %esi
	jg	L166
	movl	$3, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L167
L166:
	movb	$0, %al
L167:
	movl	16(%ebp), %ecx
L174:
	movb	%al, 1(%ecx)
	jmp	L171
L146:
	cmpl	$0, -44(%ebp)
	jle	L169
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*%esi
	movl	$0, %eax
	jmp	L139
L169:
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L173
L142:
	movl	16(%ebp), %edx
	movl	%edx, (%esp)
L173:
	movl	$0, 4(%esp)
	movl	$8, 8(%esp)
	call	_memset
L171:
	movl	$1, %eax
L139:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_to_float;	.scl	3;	.type	32;	.endef
_to_float:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	12(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%esi, %eax
	shrl	$31, %eax
	decl	%eax
	andl	$-32768, %eax
	leal	32768(%eax), %esi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %ebx
	movl	%ebx, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 12(%esp)
	call	_flconvert
	movl	-40(%ebp), %eax
	andl	$-32768, %eax
	testw	%ax, %ax
	je	L178
	decl	-44(%ebp)
	movl	-44(%ebp), %edx
	leal	126(%edx), %eax
	cmpl	$254, %eax
	ja	L179
	leal	127(%edx), %eax
	movl	%eax, -44(%ebp)
	movl	%ebx, (%esp)
	movl	$8, 4(%esp)
	call	_shr
	movl	%ebx, (%esp)
	movl	$2, 4(%esp)
	call	_round
	movl	-40(%ebp), %eax
	andl	$256, %eax
	testw	%ax, %ax
	je	L180
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	incl	-44(%ebp)
L180:
	movl	-40(%ebp), %eax
	andl	$127, %eax
	movw	%ax, -40(%ebp)
	movl	-44(%ebp), %edx
	sall	$7, %edx
	movzbl	-40(%ebp), %eax
	orb	%dl, %al
	orl	%esi, %eax
	movl	16(%ebp), %ecx
	movb	%al, 2(%ecx)
	movzwl	-40(%ebp), %eax
	orl	%eax, %edx
	orl	%esi, %edx
	sarl	$8, %edx
	movb	%dl, 3(%ecx)
	movzbl	-38(%ebp), %eax
	movb	%al, (%ecx)
	movzbl	-37(%ebp), %eax
	jmp	L202
L179:
	movl	-44(%ebp), %edx
	leal	149(%edx), %eax
	cmpl	$22, %eax
	ja	L182
	addl	$118, %edx
	negl	%edx
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L183
	leal	15(%edx), %eax
L183:
	andl	$-16, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, -48(%ebp)
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L184
	addl	$15, %eax
L184:
	movl	%eax, %edi
	sarl	$4, %edi
	leal	-40(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	-48(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_shr
	movl	%ebx, (%esp)
	movl	$2, %eax
	subl	%edi, %eax
	movl	%eax, 4(%esp)
	call	_round
	testl	%eax, %eax
	jne	L186
	cmpl	$0, -48(%ebp)
	jle	L185
	movzwl	-40(%ebp), %edx
	movl	-48(%ebp), %ecx
	decl	%ecx
	movl	$32768, %eax
	sarl	%cl, %eax
	testl	%eax, %edx
	je	L185
L186:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	cmpl	$0, -48(%ebp)
	jne	L187
	movl	-40(%ebp), %eax
	orl	$-32768, %eax
	movw	%ax, -40(%ebp)
L187:
	incl	-44(%ebp)
L185:
	movl	%esi, %eax
	testl	%edi, %edi
	jne	L189
	movzbl	-40(%ebp), %eax
	orl	%esi, %eax
L189:
	movl	16(%ebp), %edx
	movb	%al, 2(%edx)
	testl	%edi, %edi
	jne	L190
	movzwl	-40(%ebp), %eax
	orl	%esi, %eax
	jmp	L200
L190:
	movl	%esi, %eax
L200:
	shrl	$8, %eax
	movl	16(%ebp), %ecx
	movb	%al, 3(%ecx)
	cmpl	$1, %edi
	jg	L192
	movl	$1, %eax
	subl	%edi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L193
L192:
	movb	$0, %al
L193:
	movl	16(%ebp), %edx
	movb	%al, (%edx)
	cmpl	$1, %edi
	jg	L194
	movl	$1, %eax
	subl	%edi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L195
L194:
	movb	$0, %al
L195:
	movl	16(%ebp), %ecx
L202:
	movb	%al, 1(%ecx)
	jmp	L199
L182:
	cmpl	$0, -44(%ebp)
	jle	L197
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*%edi
	movl	$0, %eax
	jmp	L175
L197:
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L201
L178:
	movl	16(%ebp), %edx
	movl	%edx, (%esp)
L201:
	movl	$0, 4(%esp)
	movl	$4, 8(%esp)
	call	_memset
L199:
	movl	$1, %eax
L175:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_to_ldoub;	.scl	3;	.type	32;	.endef
_to_ldoub:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	12(%ebp), %edi
	movl	20(%ebp), %esi
	movl	%edi, %eax
	shrl	$31, %eax
	decl	%eax
	andl	$-32768, %eax
	leal	32768(%eax), %edi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	leal	-40(%ebp), %ebx
	movl	%ebx, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%esi, 12(%esp)
	call	_flconvert
	movl	-40(%ebp), %eax
	andl	$-32768, %eax
	testw	%ax, %ax
	je	L206
	decl	-44(%ebp)
	movl	-44(%ebp), %eax
	addl	$16383, %eax
	cmpl	$32767, %eax
	ja	L207
	movl	%eax, -44(%ebp)
	movl	%ebx, (%esp)
	movl	$4, 4(%esp)
	call	_round
	testl	%eax, %eax
	je	L208
	movl	%ebx, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	movl	-40(%ebp), %eax
	orl	$-32768, %eax
	movw	%ax, -40(%ebp)
	incl	-44(%ebp)
L208:
	movzbl	-44(%ebp), %eax
	orl	%edi, %eax
	movl	16(%ebp), %edx
	movb	%al, 8(%edx)
	movl	%edi, %eax
	orl	-44(%ebp), %eax
	sarl	$8, %eax
	movb	%al, 9(%edx)
	movzbl	-40(%ebp), %eax
	movb	%al, 6(%edx)
	movzbl	-39(%ebp), %eax
	movb	%al, 7(%edx)
	movzbl	-38(%ebp), %eax
	movb	%al, 4(%edx)
	movzbl	-37(%ebp), %eax
	movb	%al, 5(%edx)
	movzbl	-36(%ebp), %eax
	movb	%al, 2(%edx)
	movzbl	-35(%ebp), %eax
	movb	%al, 3(%edx)
	movzbl	-34(%ebp), %eax
	movb	%al, (%edx)
	movzbl	-33(%ebp), %eax
	movb	%al, 1(%edx)
	jmp	L235
L207:
	movl	-44(%ebp), %edx
	leal	16446(%edx), %eax
	cmpl	$62, %eax
	ja	L210
	addl	$16383, %edx
	negl	%edx
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L211
	leal	15(%edx), %eax
L211:
	andl	$-16, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, -48(%ebp)
	movl	%edx, %eax
	testl	%edx, %edx
	jns	L212
	addl	$15, %eax
L212:
	movl	%eax, %esi
	sarl	$4, %esi
	leal	-40(%ebp), %ebx
	movl	%ebx, (%esp)
	movl	-48(%ebp), %eax
	movl	%eax, 4(%esp)
	call	_shr
	movl	%ebx, (%esp)
	movl	$4, %eax
	subl	%esi, %eax
	movl	%eax, 4(%esp)
	call	_round
	testl	%eax, %eax
	jne	L214
	cmpl	$0, -48(%ebp)
	jle	L213
	movzwl	-40(%ebp), %edx
	movl	-48(%ebp), %ecx
	decl	%ecx
	movl	$32768, %eax
	sarl	%cl, %eax
	testl	%eax, %edx
	je	L213
L214:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	call	_shr
	cmpl	$0, -48(%ebp)
	jne	L215
	movl	-40(%ebp), %eax
	orl	$-32768, %eax
	movw	%ax, -40(%ebp)
L215:
	incl	-44(%ebp)
L213:
	movl	%edi, %edx
	movl	16(%ebp), %ecx
	movb	%dl, 8(%ecx)
	movl	%edi, %eax
	sarl	$8, %eax
	movb	%al, 9(%ecx)
	movb	$0, %al
	testl	%esi, %esi
	jne	L217
	movzbl	-40(%ebp), %eax
L217:
	movl	16(%ebp), %edx
	movb	%al, 6(%edx)
	movb	$0, %al
	testl	%esi, %esi
	jne	L219
	movzbl	-39(%ebp), %eax
L219:
	movl	16(%ebp), %ecx
	movb	%al, 7(%ecx)
	cmpl	$1, %esi
	jg	L220
	movl	$1, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L221
L220:
	movb	$0, %al
L221:
	movl	16(%ebp), %edx
	movb	%al, 4(%edx)
	cmpl	$1, %esi
	jg	L222
	movl	$1, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L223
L222:
	movb	$0, %al
L223:
	movl	16(%ebp), %ecx
	movb	%al, 5(%ecx)
	cmpl	$2, %esi
	jg	L224
	movl	$2, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L225
L224:
	movb	$0, %al
L225:
	movl	16(%ebp), %edx
	movb	%al, 2(%edx)
	cmpl	$2, %esi
	jg	L226
	movl	$2, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L227
L226:
	movb	$0, %al
L227:
	movl	16(%ebp), %ecx
	movb	%al, 3(%ecx)
	cmpl	$3, %esi
	jg	L228
	movl	$3, %eax
	subl	%esi, %eax
	movzbl	-40(%ebp,%eax,2), %eax
	jmp	L229
L228:
	movb	$0, %al
L229:
	movl	16(%ebp), %edx
	movb	%al, (%edx)
	cmpl	$3, %esi
	jg	L230
	movl	$3, %eax
	subl	%esi, %eax
	movzbl	-39(%ebp,%eax,2), %eax
	jmp	L231
L230:
	movb	$0, %al
L231:
	movl	16(%ebp), %ecx
	movb	%al, 1(%ecx)
	jmp	L235
L210:
	cmpl	$0, -44(%ebp)
	jle	L233
	movl	$1, (%esp)
	movl	$LC2, 4(%esp)
	call	*%esi
	movl	$0, %eax
	jmp	L203
L233:
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	jmp	L236
L206:
	movl	16(%ebp), %edx
	movl	%edx, (%esp)
L236:
	movl	$0, 4(%esp)
	movl	$10, 8(%esp)
	call	_memset
L235:
	movl	$1, %eax
L203:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 32
LC3:
	.ascii "strange value %d passed to float_const\0"
	.align 2
.globl _float_const
	.def	_float_const;	.scl	2;	.type	32;	.endef
_float_const:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	20(%ebp), %eax
	movl	24(%ebp), %ebx
	cmpl	$4, %eax
	jne	L238
	movl	%edx, (%esp)
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, 12(%esp)
	call	_to_float
	jmp	L237
L238:
	cmpl	$8, %eax
	jne	L240
	movl	%edx, (%esp)
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, 12(%esp)
	call	_to_double
	jmp	L237
L240:
	cmpl	$10, %eax
	jne	L242
	movl	%edx, (%esp)
	movl	%ecx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, 12(%esp)
	call	_to_ldoub
	jmp	L237
L242:
	movl	$3, (%esp)
	movl	$LC3, 4(%esp)
	movl	%eax, 8(%esp)
	call	*%ebx
	movl	$0, %eax
L237:
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
