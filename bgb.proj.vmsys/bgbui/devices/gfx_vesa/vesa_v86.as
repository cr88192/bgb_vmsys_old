;regs16 [ax cx dx bx sp bp si di ds es]

extern kprint
extern cpu_int13_catch
global vesall_getinfo

vesall_segfault:
mov dword [cpu_int13_catch], 0
mov esp, [pm_sp]

jmp $

mov ax, ss
mov ds, ax
mov es, ax

popa
popf
pop ebp
ret


vesall_getinfo:
push ebp
mov ebp, esp

pushf
pusha

cli

mov dword [cpu_int13_catch], vesall_segfault

mov edx, esp
mov [pm_sp], edx

xor eax, eax
push eax	;gs
push eax	;fs
push eax	;ds
push eax	;es
push eax	;ss

push edx	;esp

push dword 0x23002	;eflags, vm iopl=3 if=0

mov eax, v86frag
and eax, 0xF0000
shr eax, 4
push eax	;cs
mov eax, v86frag
and eax, 0xFFFF
push eax	;eip


mov eax, v86frag
push eax

push dword v86str
call kprint

pop eax ;str
pop eax	;lin

iret

jmp vesall_segfault

v86str db "V86: LIN=%X, EIP=%X, CS=%X, EFLAGS=%X, ESP=%X, SS=%X, ES=%X, DS=%X, FS=%X, GS=%X", 10, 0

align 16

v86frag:
[bits 16]

;pushf
;call far [40h]

jmp $

int 0	;gpf


[section .data]
[bits 32]

pm_sp dd 0