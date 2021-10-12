;kernel loaded 0x10000
;setup gdt at 0xFA00(192 ents)
;setup idt at 0xF800(64 ents)
;start kernel(flat mode)
;
;objective: load kernel above 1MB mark, also load modules

org 0x8000
__start:

jmp _skern

.l0:
  ;reset vars as some commands mess these up
push cs
pop ax
mov ds,ax
mov es,ax
  ;read line
mov di,buf0
call $ReadLine
cmp byte [buf0],'d'
je .dump
mov ax,0x0E07
int 0x10
jmp .l0

.dump:
mov si,buf0+2
call $ParseWord
mov bx,dx
mov si,buf0+7
call $ParseWord
mov si,dx
mov ds,bx
call $DumpLine
jmp .l0

jmp $

_skern:

xor ax,ax
mov es,ax
mov si, 0x7c00
mov di, fat_head
mov cx, 16
rep movsw

mov ax,[rents]
mov cl,4		;assume sbytes==512
shr ax,cl		;512/32=16=2^4, 512>>4=16
add ax,[root_start]
mov [data_start],ax

;mov ax,[rsize]
;;mov cx,[fatsz]
;mov cx,8
;mov bx,0x1000
;call readsectors
;xor ax,ax
;mov es,ax

;mov ax,[root_start]
;mov cx,8
;mov bx,0x2000
;call readsectors
;xor ax,ax
;mov es,ax

push word 0x1000
push word kernelname
call _loadfile
pop ax
pop ax


call EnableA20
call ResetIRQ
  ;realitivly simple
cli

lgdt [gdtp]
lidt [idtp]
  ;switch to pm
mov eax,cr0
inc eax
mov cr0,eax
  ;start kernel
jmp dword 8:0x10000

ResetIRQ:
mov al,0x11
out 0x20,al
out 0xA0,al

mov al,0x20
out 0x21,al
mov al,0x28
out 0xA1,al

mov al,0x04
out 0x21,al
mov al,0x02
out 0xA1,al

mov al,0x01
out 0x21,al
out 0xA1,al

mov al,0xFB
out 0x21,al
mov al,0xFF
out 0xA1,al

ret

EnableA20:
call Empty8042
mov al,0xD1
out 0x64,al
call Empty8042
mov al,0xDF
out 0x60,al
ret

Empty8042:
in al,0x64
test al,1
jz .out
in al,0x60
jmp Empty8042
.out:
test al,2
jnz Empty8042
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

$ParseWord: ;ds:si=str, returns dx=value
xor dx,dx
call ParseDig
call ParseDig
call ParseDig
call ParseDig
ret

$ParseDig:
lodsb
sub al,'0'
cmp al,9
jbe .l0
sub al,7
.l0:
shl dx,4
add dl,al
ret

$DumpLine: ;ds:si=line
  ;segment
push ds
pop ax
call $PrintWord
  ;colon
mov ax,0x0E3A
int 0x10
  ;offset
push si
pop ax
call $PrintWord
  ;space
mov ax,0x0E20
int 0x10
  ;chars
mov cx,16
.l0:
lodsb
call $PrintByte
  ;space
mov ax,0x0E20
int 0x10
loop .l0
  ;new line
mov ax,0x0E0D
int 0x10
mov ax,0x0E0A
int 0x10
ret

$ReadLine: ;es:di=buffer
mov si,di
.l0:
xor ax,ax
int 0x16
cmp al,' '
jb .cont
stosb
mov ah,0x0E
int 0x10
jmp .l0
.cont:
cmp al,0x0D
je .nl
cmp al,0x08
je .bs
mov ax,0x0E07
int 0x10
jmp .l0
.bs:
cmp di,si
jbe .l0
dec di
mov ax,0x0E08
int 0x10
mov al,' '
int 0x10
mov al,0x08
int 0x10
jmp .l0
.nl:
mov ah,0x0E
int 0x10
mov al,0x0A
int 0x10
mov al,0
stosb
ret

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

add si, cx
add si, 21
cmp si, 0x2800
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



;scratchpad space
root_start dw 0
data_start dw 0

buf0 times 256 db 0

fat_head:
times 11 db 0
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
times 32 db 0

kernelname	db "KERNEL  BIN"

idtp:
dw 512
dd 0xF800
gdtp:
dw 1536
dd 0xFA00

times 0x7800-($-$$) db 0
idt:
times 128 dd 0
gdt:
  ;null
dd 0x00000000
dd 0x00000000
  ;code
dd 0x0000FFFF
dd 0x00CF9A00
  ;data
dd 0x0000FFFF
dd 0x00CF9200
  ;free
times 378 dd 0
