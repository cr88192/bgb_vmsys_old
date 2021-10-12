[bits 32]

org 0x10000

__start:
mov ax,16
mov ds,ax
mov es,ax

mov edi,0xB8000
mov esi,msg
mov ecx,msge-msg
mov ah,0x07
.l0:
lodsb
stosw
loop .l0

jmp $

msg db "Kernel has spawned..."
msge: