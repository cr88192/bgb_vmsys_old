global CountRamPages

[section .text]
[bits 32]

CountRamPages:
push ebp
mov ebp, esp
push esi

xor esi, esi
.l0:
mov edx, [esi]
mov eax, 0x55AA55AA
mov [esi], eax
cmp [esi], eax
jne .l1
mov [esi], edx
add esi, 1024*1024
jmp .l0
.l1:

mov eax, esi
shr eax, 12

pop esi
pop ebp
ret
