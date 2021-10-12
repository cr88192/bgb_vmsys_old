;boot fat:
;	load "setup.bin": 0x0000:0x8000
;	load "kernel.bin": 0x1000:0x0000

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

	;figure start of root dir
mov ax,[fatsz]
;mul byte [fats]
shl ax,1	;this is a hack
add ax,[rsize]
mov [root_start],ax

	;figure start of data area
mov ax,[rents]
mov cl,4		;assume sbytes==512
shr ax,cl		;512/32=16=2^4, 512>>4=16
add ax,[root_start]
mov [data_start],ax

	;read fat
mov ax,[rsize]
;mov cx,[fatsz]
mov cx,8
mov bx,0x1000
call readsectors
xor ax,ax
mov es,ax

	;read root dir
mov ax,[root_start]
mov cx,1
mov bx,0x2000
call readsectors
xor ax,ax
mov es,ax

	;opening brace
mov ax,0x0E3C
int 0x10

	;read kernel
push word 0x1000
push word kernelname
call _loadfile
pop ax
pop ax

	;close brace
mov ax,0x0E3E
int 0x10

	;opening brace
mov ax,0x0E3C
int 0x10

	;read setup
push word 0x800
push word setupname
call _loadfile
pop ax
pop ax

	;close brace
mov ax,0x0E3E
int 0x10

;jmp $

	;setup is loaded, now start it
jmp 0:0x8000


_loadfile: ;(char *name, int seg)
push bp
mov bp, sp

xor ax, ax
mov es, ax

mov si,0x2000
.l1:
	;check names match
mov di,[bp+4]
mov cx,11
repe cmpsb
je .l0	;if so jump

	;else pad and try again, stopping at 0x2800
add si, cx
add si, 21
cmp si, 0x2800
jae .l2
jmp short .l1
.l2:

	;file not found, beep and block
mov ax,0x0E07
int 0x10
int 0x10
xor ax,ax
int 0x16
int 0x19
.l0:

	;file found

;mov ax,0x0E3A
;int 0x10

	;at this point si points to the attribute byte is the file entry for
	;the file, si+15=base, si+17=size
mov ax,[si+15]
mov bx,[bp+6]
mov es,bx

xor si,si
xor di,di

.l3:
	;debug dot
push ax
mov ax,0x0E2E
int 0x10
pop ax

xor bx,bx

push ax
sub ax,2
add ax,[data_start]
call readsector
mov ax,es
add ax,32
mov es,ax
pop ax

	;check eof
call getfatent
mov bx,ax		;check for EOF
and bx,0xFF8		;0xFF8<=EOF<=0xFFF
cmp bx,0xFF8		;easy range check
jne .l3			;not eof, continue reading

;and bx,0xF00		;0xFF8<=EOF<=0xFFF
;cmp bx,0xF00		;easy range check

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
inc ax	;increment sector

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
;call printword
ret

printword:
push ax
call $PrintWord
pop ax
ret

  ;ax=value
$PrintWord:
xchg ah,al
call $PrintByte
xchg ah,al
  ;al=value
$PrintByte:
rol al,4
call $PrintDig
rol al,4
  ;al&0x0F=value
$PrintDig:
push ax
mov ah,0x0E
and al,0x0F
add al,'0'
cmp al,'9'
jbe .l0
add al,7
.l0:
int 0x10
pop ax
ret

setupname	db "SETUP   BIN"
kernelname	db "KERNEL  BIN"

;scratchpad space
root_start dw 0
data_start dw 0

times ($$-$)+510 db 0
db 0x55,0xAA
