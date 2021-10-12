extern _main
extern ___stdio_init

global _start
global _exit
global _abort

global ___va_start
global ___va_arg
global ___va_end

global __alloca
global ___main

[section .text]
[bits 32]

_start:
mov ax, ss
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax

call ___stdio_init

call _main

_exit:
jmp $

_abort:
jmp $

___va_start: ;(long **lst, long *arg)
push ebp
mov ebp, esp
push edi

mov edi, [ebp+8]
mov eax, [ebp+12]
add eax, 4
mov [edi], eax

pop edi
pop ebp
ret

___va_arg: ;(long **lst)
push ebp
mov ebp, esp
push esi
push edi

mov edi, [ebp+8]
mov esi, [edi]
mov eax, [esi]
add esi, 4
mov [edi], esi

pop edi
pop esi
pop ebp
ret

___va_end:
ret

__alloca:
ret

___main:
ret
