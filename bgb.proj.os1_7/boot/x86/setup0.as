;kernel loaded 0x10000
;setup gdt at 0xFA00(192 ents)
;setup idt at 0xF800(64 ents)
;start kernel(flat mode)

;a kernel stack exists at 0x8000, use 0x6000 as a local call stack, use 0x4000 for scratchpad data

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
call EnableA20
call ResetIRQ
  ;realitivly simple
cli

mov ax,0x0E40
int 0x10

lgdt [gdtp]
lidt [idtp]
  ;switch to pm
mov eax,cr0
inc eax
mov cr0,eax
  ;start kernel
;jmp $

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

buf0 times 256 db 0



	;data for pm/rm interface

pm_stack32 dd 0
pm_cr3 dd 0
pm_rmodefcn dd 0
pm_args dd  0,0,0,0



	;vesa functions

misc_vesa_getinfo:
mov ax, 0x4F00
mov edi, 0x4000
mov dword [di], 'VBE2'
int 0x10
mov [pm_args], edi
ret

misc_vesa_getmodeinfo:
mov ax, 0x4F01
mov edi, 0x4200
mov cx, [pm_args]
int 0x10
mov [pm_args], edi
ret

misc_vesa_setmode:
mov ax, 0x4F02
mov bx, [pm_args]
int 0x10
ret

misc_vesa_getmode:
mov ax, 0x4F03
int 0x10
mov [pm_args], bx
ret

misc_vesa_setbank:
mov ax, 0x4F05
xor bx, bx		;window A
mov dx, [pm_args]
int 0x10

;mov ax, 0x4F05
;inc bx			;window B
;mov dx, [pm_args]
;int 0x10
ret

misc_vesa_setpalette:

mov ax, [pm_args]
mov di, ax
mov ax, [pm_args+2]
mov es, ax

mov ax, 0x4F09
xor bx, bx
mov cx, 256
xor dx, dx
int 0x10

ret


misc_vesa_blitscreen: ;(void *buf, int banks, int banksz)

;point to vidmem and buffer
mov esi, [pm_args]
cld

mov ax, 0xA000
mov es, ax

;get bank count and set initial bank
mov cx, [pm_args+4]
xor dx, dx

;start loop
.l0:
push cx
push dx

;set bank
mov ax, 0x4F05
xor bx, bx		;window A
pop dx
push dx
int 0x10

;mov ax, 0x4F05
;inc bx			;window B
;pop dx
;push dx
;int 0x10

;xor di, di
;mov ecx, [pm_args+8]
;shr ecx, 2
;mov ecx, 32768
;a32 fs rep movsw

;pop dx
;inc dx
;pop cx
;loop .l0
;ret


cli

push ds
push es

mov eax, cr0
;or eax, 0x80000001
inc eax
mov cr0, eax

;or eax, 0x80000000
;mov cr0, eax

jmp dword 8:.l1

[bits 32]
.l1:
mov ax, 0x10
mov ds, ax
mov es, ax

;copy contents from buffer to bank
mov edi, 0xA0000
;mov ecx, [pm_args+8]
;shr ecx, 2
mov ecx, 16384
rep movsd

jmp 24:.l2

[bits 16]
.l2:

;enter real mode, restore seg regs
mov eax, cr0
;and eax, 0x7fffffff
;mov cr0, eax

dec eax
mov cr0, eax

jmp 0:.l3
;[bits 16]
.l3:

pop es
pop ds

pop dx
inc dx

pop cx
loop .l0

;jmp short $

;done
ret



	;code to call rm functions

[bits 32]
trans_rm32: ;(far func, ...)
push ebp
mov ebp, esp
pusha
push ds
push es
push ss
push fs
push gs

mov [pm_stack32], esp
mov eax, [ebp+8]
mov [pm_rmodefcn], eax

mov eax, [ebp+12]
mov [pm_args], eax
mov eax, [ebp+16]
mov [pm_args+4], eax
mov eax, [ebp+20]
mov [pm_args+8], eax
mov eax, [ebp+24]
mov [pm_args+12], eax

cli

;set registers to valid 16bit p-mode values
mov ax, 0x20
mov ds, ax
mov es, ax
;mov fs, ax
;mov gs, ax

;16 bit stack
mov ss, ax
mov esp, 0x6000

;transition to pmode-16
jmp 24:l0

[bits 16]
l0:
;disable paging
mov eax, cr0
and eax, 0x7fffffff
mov cr0, eax

;store cr3
mov eax, cr3
mov [pm_cr3], eax

;flush tlb
;xor eax, eax
;mov cr3, eax

;real mode idt
sidt [idtp]
lidt [idtp_rm]

;enter real mode
mov eax, cr0
and eax, 0x7ffffffe
mov cr0, eax

;jump to real mode
jmp 0:l1

l1:
;now in real mode
xor ax, ax
mov ds, ax
mov es, ax
;mov fs, ax
;mov gs, ax

mov ss, ax

call far [pm_rmodefcn]

;mov ax, 0x0E07
;int 0x10
;int 0x10
;jmp $

;begin treck back to protected mode
lidt [idtp]

mov eax,cr0
inc eax
mov cr0,eax

;mov eax, [pm_cr3]
;mov cr3, eax

mov eax,cr0
or eax, 0x80000000
mov cr0,eax

;jump into 32 bit protected mode
jmp 8:l2
[bits 32]
l2:

mov ax, 16
mov ds, ax
mov es, ax
mov ss, ax
mov esp, [pm_stack32]

sti

pop gs
pop fs
pop ss
pop es
pop ds
popa

mov eax, [pm_args]	;return value

pop ebp
ret

[bits 16]



	;general data

idtp_rm:
dw 1024
dd 0x0

idtp:
dw 512
dd 0xF800
gdtp:
dw 1536
dd 0xFA00

;setupmsg db "LDR2",13,10,0

times 0x7600-($-$$) db 0 ;function pointers to rm-16/rm-32 interfaces
dd trans_rm32
dw misc_vesa_getinfo, 0
dw misc_vesa_getmodeinfo, 0
dw misc_vesa_setmode, 0
dw misc_vesa_getmode, 0
dw misc_vesa_setbank, 0
dw misc_vesa_setpalette, 0

dw misc_vesa_blitscreen, 0

times 0x7800-($-$$) db 0 ;the initial idt and gdt
idt:
times 128 dd 0
gdt:
  ;null
dd 0x00000000
dd 0x00000000
  ;code, 8
dd 0x0000FFFF
dd 0x00CF9A00
  ;data, 16
dd 0x0000FFFF
dd 0x00CF9200
  ;code-16, 24
dd 0x0000FFFF
dd 0x00009A00
  ;data-16, 32
dd 0x0000FFFF
dd 0x00009200
  ;data-16, 40, window
dd 0x0000FFFF
dd 0x00009200
  ;free
times 372 dd 0
