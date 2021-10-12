global mul_int_824

[section .text]
[bits 32]

mul_int_824: ;int(int, fixed_824)
push ebp
mov ebp, esp

mov eax, [ebp+8]
mov ecx, [ebp+12]
mul ecx

shr eax, 24
shl edx, 8
add eax, edx

pop ebp
ret