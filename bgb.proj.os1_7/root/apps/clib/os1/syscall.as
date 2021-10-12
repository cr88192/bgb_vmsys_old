global _syscall

[section .text]
[bits 32]

_syscall: ;(int num, ...)
push ebp
mov ebp, esp

mov eax, [ebp+8]
mov ecx, ebp
add ecx, 12
int 0x30

pop ebp
ret
