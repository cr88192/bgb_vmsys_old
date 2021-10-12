extern _kernel_page_table
global _Paging_SetUpCR3
global _Paging_SetCR3
global _Paging_GetCR3
global _Paging_FlushCR3

[section .text]
[bits 32]

_Paging_SetUpCR3:
push ebp
mov ebp,esp

;set kernel page tables
mov eax,[_kernel_page_table]
shl eax, 12
or eax, 3
mov cr3, eax

;enable paging
mov eax, cr0
or eax, 0x80000000
mov cr0, eax

mov eax, cr4
or al, 128	;allow global bit
mov cr4, eax

pop ebp
ret

_Paging_GetCR3:
push ebp
mov ebp,esp

mov eax, cr3
shr eax, 12

pop ebp
ret

_Paging_SetCR3:
push ebp
mov ebp,esp

mov eax, [ebp+8]
shl eax, 12
mov cr3, eax

pop ebp
ret

_Paging_FlushCR3:
push ebp
mov ebp,esp

mov eax, cr3
mov cr3, eax

pop ebp
ret

_Paging_FlushAddr:
push ebp
mov ebp,esp
push ebx

mov ebx, [ebp+8]
;invplg [ebx]

pop ebx
pop ebp
ret
