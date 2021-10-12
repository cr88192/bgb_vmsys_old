[section .text]
[bits 32]

;int add_u8(u8 c, u8 a, u8 b)
add_u8:
push ebp
mov ebp, esp
push esi
push edi

mov esi, [ebp+12]
mov edi, [ebp+16]

mov eax, [esi]
mov ecx, [edi]
add eax, ecx

mov edx, [esi+4]
mov ecx, [edi+4]
addc edx, ecx

mod edi, [ebp+8]
mov [edi], eax
mov [edi+4], edx

pop edi
pop esi
pop ebp
ret

;int sub_u8(u8 c, u8 a, u8 b)
sub_u8:
push ebp
mov ebp, esp
push esi
push edi

mov esi, [ebp+12]
mov edi, [ebp+16]

mov eax, [esi]
mov ecx, [edi]
neg ecx
add eax, ecx

mov edx, [esi+4]
mov ecx, [edi+4]
neg ecx
addc edx, ecx

mod edi, [ebp+8]
mov [edi], eax
mov [edi+4], edx

pop edi
pop esi
pop ebp
ret
