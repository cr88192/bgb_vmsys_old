global _start
global __data_start
extern _k_main
extern _CountRamPages
extern _mem_pages

extern _Text_Init
extern _Text_WriteString

[section .text]
[bits 32]

_start:
jmp short .l0
dd _start
db "should be at start of kernel", 0
.l0:
cli
mov ax,0x10
mov ds,ax
mov es,ax
mov ss,ax
mov fs,ax
mov gs,ax

xor eax, eax
mov ax, sp
mov esp, eax
;mov esp,0x7C00	;0x7C00-0x8000 will be a tld area
mov ebp, esp

;jmp $

;call _Text_Init

;push ktststr
;call _Text_WriteString
;pop eax

mov edi, 0xB8000
mov eax, 'T E '
mov [edi], eax

;jmp $

call _CountRamPages
;mov eax, 131072

jmp .l3
xor esi, esi
.l1:
mov edx, [esi]
mov eax, 0x55AA55AA
mov [esi], eax
cmp [esi], eax
jne .l2
mov [esi], edx
add esi, 1024*1024
jmp .l1
.l2:

mov eax, esi
shr eax, 12

.l3:

mov [_mem_pages], eax

mov edi, 0xB8000
mov eax, 'X T '
mov [edi+4], eax

;jmp $

call _k_main

mov edi, 0xB8000
mov eax, 'R T '
mov [edi+8], eax

jmp $

[section .data]
__data_start:

ktststr db "kernel1\r\n", 0
