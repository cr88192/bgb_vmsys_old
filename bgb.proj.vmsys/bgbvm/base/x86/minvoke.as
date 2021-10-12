global MInvoke_Function

[section .text]
[bits 32]

;int MInvoke_Function(int (*func)(int c,...), int parmc, int *parmv)
MInvoke_Function:
push ebp
mov ebp, esp
push esi
push edi

mov ecx, [ebp+12]
shl ecx, 2
sub esp, ecx
mov edi, esp
mov esi, [ebp+16]
shr ecx, 2
rep movsd
call dword [ebp+8]

mov ecx, [ebp+12]
shl ecx, 2
add esp, ecx

pop edi
pop esi

mov esp, ebp
pop ebp
ret
