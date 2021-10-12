;boot fat:
;	load "setup.bin": 0x0000:0x8000

org 0x7C00
jmp short _start
nop

times ($$-$)+11 db 0
;fat shit
sbytes	dw 0	;bytes/sector
csize	db 0	;sectors/cluster
rsize	dw 0	;reserved
fats	db 0	;fats
rents	dw 0	;root entries
sects	dw 0	;total sectors
media	db 0	;dos media descriptor
fatsz	dw 0	;sectors/fat
tracksz	dw 0	;sectors/track
heads	dw 0	;heads
hidden	dw 0	;hidden
;past this I don't care about
times ($$-$)+0x3E db 0

_start:
cld
cli
xor ax,ax
mov ss,ax
mov sp,0x7C00
mov ds,ax
mov es,ax
sti

	;fat_start=rsize
	;root_start=fat_start+fatsz*fats
	;data_start=root_start+rents/(sbytes/32)
	;data[0]=cluster[2]

mov ax,[fatsz]
;mul byte [fats]
shl ax,1	;this is a hack
add ax,[rsize]
mov [root_start],ax

mov ax,[rents]
mov cl,4		;assume sbytes==512
shr ax,cl		;512/32=16=2^4, 512>>4=16
add ax,[root_start]
mov [data_start],ax

mov ax,[rsize]
;mov cx,[fatsz]
mov cx,8
mov bx,0x1000
call readsectors
xor ax,ax
mov es,ax

mov ax,[root_start]
mov cx,8
mov bx,0x2000
call readsectors
xor ax,ax
mov es,ax


;push word 0x1000
;push word kernelname
;call _loadfile
;pop ax
;pop ax

push word 0x800
push word setupname
call _loadfile
pop ax
pop ax

;jmp $

	;setup is loaded, now start it
jmp 0:0x8000

_loadfile: ;(char *name, int seg)
push bp
mov bp,sp

xor ax,ax
mov es,ax

mov si,0x2000
.l1:
mov di,[bp+4]
mov cx,11
repe cmpsb
je .l0

add si,21
cmp si,0x2800
jae .l2
jmp short .l1
.l2:

mov ax,0x0E07
int 0x10
int 0x10
xor ax,ax
int 0x16
int 0x19
.l0:

;mov ax,0x0E2E
;int 0x10

	;at this point si points to the attribute byte is the file entry for
	;the file, si+15=base, si+17=size
mov ax,[si+15]
mov bx,[bp+6]
mov es,bx

xor si,si
xor di,di

.l3:
;push ax
;mov ax,0x0E2E
;int 0x10
;pop ax

xor bx,bx

push ax
sub ax,2
add ax,[data_start]
call readsector
mov ax,es
add ax,32
mov es,ax
pop ax

call getfatent
mov bx,ax		;check for EOF
and bx,0xFF8		;0xFF8<=EOF<=0xFFF
cmp bx,0xFF8		;easy range check
jne .l3			;not in range

pop bp
ret


lba2chs: ;ax=lba, out ch=track, cl=sector, dh=head
xor dx,dx
div word [tracksz]
inc dl
mov cl,dl
xor dx,dx		;calc head/track
div byte [heads]
mov ch,al
mov dh,ah
ret

readsector: ;ax=lba, es:bx=buffer
call lba2chs
mov ax,0x0201
int 0x13
ret

readsectors: ;ax=lba, es:bx=buffer, cx=cnt
push cx
push ax
call readsector
mov ax,es
add ax,32
mov es,ax
pop ax
pop cx
loop readsectors
ret

getfatent: ;ax=num, return ax=val
test ax,1
jnz .odd

;even
mov cx,3
mul cx
shr ax,1
xor cl,cl
jmp short .dec

.odd:
mov cx,3
mul cx
shr ax,1
mov cl,4

.dec:
mov bx,ax
mov ax,[bx+0x1000]
shr ax,cl
and ax,0xFFF
ret

setupname	db "SETUP   BIN"
;kernelname	db "KERNEL  BIN"

;scratchpad space
root_start dw 0
data_start dw 0

times ($$-$)+510 db 0
db 0x55,0xAA
