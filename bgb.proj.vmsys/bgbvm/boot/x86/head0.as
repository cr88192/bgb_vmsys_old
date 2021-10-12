global _start
global __data_start
extern main
extern CountRamPages
extern mem_pages

[section .text]
[bits 32]

_start:
jmp short .l0
db "should be at start of kernel", 0
.l0:
cli
mov ax,0x10
mov ds,ax
mov es,ax
mov ss,ax
mov fs,ax
mov gs,ax
mov esp,0x7C00	;0x7C00-0x8000 will be a tld area
mov ebp,esp

;jmp $

call CountRamPages
mov [mem_pages], eax

call main
jmp $

[section .data]
__data_start: