;code boots at 0x7C00
;loads disk image 0x7E0:0x0

org 0x7C00
__ep:
  ;setup vars
cld
cli
xor ax,ax
mov ds,ax
mov es,ax
mov ss,ax
mov sp,0x7C00
sti
  ;load
mov bp,sp
push ds         ;make space on stack for track count
mov ax,0x7E0
mov es,ax
.l1:
  ;head 0
mov ax,0x0212
xor bx,bx
mov ch,[bp-2]
mov cl,1
xor dx,dx
int 0x13
jc .err1
  ;head 1
.l2:
mov ax,0x0212
mov bx,9216
mov ch,[bp-2]
mov cl,1
mov dh,1
int 0x13
jc .err2
  ;update
.l3:
mov ax,es
add ax,1152
mov es,ax
  ;dot
mov ax,0x0E2E
int 0x10
  ;loop
inc byte [bp-2]
cmp byte [bp-2],33
jb .l1
  ;nl
mov ax,0x0E0D
int 0x10
mov ax,0x0E0A
int 0x10
  ;go
jmp 0:0x8000

.err1:
;mov al,ah
;call $PrintByte
call _rs1
jmp .l2

.err2:
;mov al,ah
;call $PrintByte
call _rs1
jmp .l3

_rs1:
mov cl,1
.l0:
mov ax,0x0201
int 0x13
inc cl
add bh,2
cmp cl,18
jbe .l0
ret

$PrintByte:
rol al,4
call $PrintDig
rol al,4
$PrintDig:
push ax
and al,0x0F
add al,'0'
cmp al,'9'
jbe .l0
add al,7
.l0:
mov ah,0x0E
int 0x10
pop ax
ret

times 510-($-$$) db 0
dw 0xAA55