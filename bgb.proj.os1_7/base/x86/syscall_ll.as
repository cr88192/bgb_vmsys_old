global __int48_ISR
global __syscall_jumpuser

extern _syscall_handle

[section .text]
[bits 32]

__int48_ISR: ;syscalls, eax=syscall_id, ecx=old_esp
push ebx
push esi
push edi
push ebp

push ds
push es
push fs
push gs

mov dx, ss
mov ds, dx
mov es, dx
mov fs, dx
mov gs, dx

sti

push ecx
push eax
call _syscall_handle
pop ecx
pop ecx

cli

pop gs
pop fs
pop es
pop ds

pop ebp
pop edi
pop esi
pop ebx

iret

__syscall_jumpuser: ;(int addr, int esp)
push ebp
mov ebp, esp

;dummy code, app is run in ring 0
;push the stack objects since there is no real stack jump
mov esi, [ebp+12]
;push dword [esi+12]
push dword [esi+8] ;env
push dword [esi+4] ;argv
push dword [esi+0] ;argc

;dummy jump, test
push dword [ebp+8]
ret

;this is what would be called on a real jump
push 0x3B		;ss
push dword [ebp+12]	;esp
push 0x00003000		;eflags, IOPL=3, IF=0
push 0x33		;cs
push dword [ebp+8]	;eip

iret
