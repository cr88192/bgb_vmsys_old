;this is planned to be the replacer of flat images

org 0x7C00
xor ax,ax
mov ss,ax
mov sp,0x7C00
mov ds,ax
mov es,ax

  ;read sector, es:bx=buffer
ReadSector:
mov ax,0x0201
mov ch,[track]
mov cl,[sect]
mov dh,[head]
xor dl,dl
int 0x13

mov ax,es
add ax,32
mov es,ax

call NextSector

ret

NextSector:
inc byte [sect]
cmp byte [sect],18
jbe .l0
mov byte [sect],1
inc byte [head]
cmp byte [head],1
jbe .l0
mov byte [head],0
inc word [track]
.l0:
ret

sect db 2
head db 0
track dw 0