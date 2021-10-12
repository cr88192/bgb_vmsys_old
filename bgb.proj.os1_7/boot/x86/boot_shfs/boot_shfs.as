org 0x7C00

cld
cli
xor ax,ax
mov ss,ax
mov sp,0x7C00
mov ds,ax
mov es,ax
sti

;read rest of loader and header to 0x600
mov ax,0x0203
mov bx,0x0600
mov cx,0x0002
mov dx,0x0000
int 0x13

;copy rest of boot code to 0x7E00
mov si,0x0600
mov di,0x7E00
mov cx,256
rep movsw

;alc_start=2
;data_start=(1440*2+(1024-1))/1024+alc_start=5
;read rest of loader and header to 0x600

;copy alc to 0x1000, uses 3K
mov ax,0x0206
mov bx,0x1000
mov cx,0x0005
mov dx,0x0000
int 0x13

;copy root to 0x2000, uses 4K
mov ax,0x0208
mov bx,0x2000
mov cx,0x000B
mov dx,0x0000
int 0x13


;find loader
mov si,0x2000
.l1:
cmp byte [si+111], 0x20
jne .l0
push si
mov di,ldr_name+2
mov cx,[ldr_name]
repe cmpsb
je .l3
pop si

.l0:
add si, 128
cmp si, 0x3000
jb .l1
push noldr
jmp kill

.l3:

;loader found, si points to entry

message:
pop si
lodsw
mov cx,ax
mov ah,0x0E
.l0:
lodsb
int 0x10
loop .l0
ret

kill:
call message
mov ax,0x0E07
int 0x10
int 0x10
xor ax,ax
int 0x16
int 0x19

noldr db (.end-$),0,"no loader found.",13,10
.end:

ldr_name db (.end-$),0,".loader",0
.end:
