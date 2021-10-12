;kernel loaded 0x10000
;setup gdt at 0xFA00(192 ents)
;setup idt at 0xF800(64 ents)
;start kernel(flat mode)

;a kernel stack exists at 0x8000, use 0x6000 as a local call stack, use 0x4000 for scratchpad data
;modify to load a pe kernel, load to 1MB

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

BadKernel:
mov si, badkernel
jmp DieString

_skern:

mov ax, 0x0E0D
int 0x10
mov ax, 0x0E0A
int 0x10

call EnableA20
  ;realitivly simple
;cli

mov si, msg1
call PrintString

;mov ax, 0x0E2E
;int 0x10

;jmp .l1

cli
lgdt [gdtp]
  ;switch to pm
mov eax, cr0
inc eax
mov cr0, eax

;big real
mov ax, 0x10
mov fs, ax
;mov gs, ax

mov eax, cr0
dec eax
mov cr0, eax
sti

.l1:

;mov ax, 0x0E2E
;int 0x10

mov esi, 0x10000
mov ax, [fs:esi]
cmp ax, 'MZ'
jne BadKernel

;mov ax, 0x0E31
;int 0x10

mov eax, [fs:esi+0x3C]
add esi, eax
mov ax, [fs:esi]
cmp ax, 'PE'
jne BadKernel

;mov ax, 0x0E32
;int 0x10

mov ax, [fs:esi+6]	;sections
push ax

mov ax, [fs:esi+20]	;len opthead
push 0
push ax

add esi, 24

mov eax, [fs:esi+16]	;vma entry
push eax

mov eax, [fs:esi+28]	;vma base
push eax

;vma-base:32,0 vma-entry:32,4 len-opthead:32,8 sections:16,12
mov bp, sp

;skip optional header
mov eax, [bp+8]
add esi, eax

;mov ax, 0x0E2E
;int 0x10

mov cx, [bp+12]
.l0:
push esi
push ecx

;calculate target vma
mov eax, [bp]
mov edi, [fs:esi+12]
add edi, eax

mov ecx, [fs:esi+16]

mov eax, 0x10000
mov esi, [fs:esi+20]
add esi, eax

call MemCopy

pop ecx
pop esi
add esi, 40

loop .l0

  ;start kernel
;jmp $

;jmp dword 8:0x10000

mov eax, 8
push eax
mov eax, [bp+4]	;vma entry
add eax, [bp+0]	;vma base
push eax

mov edx, eax
mov si, msg2
call PrintString

mov ax, 0x0E20
int 0x10
mov eax, edx
call $PrintDWord

mov ax, 0x0E20
int 0x10
mov esi, 0x100002
mov eax, [fs:esi]
call $PrintDWord

mov ax, 0x0E0D
int 0x10
mov ax, 0x0E0A
int 0x10

cli
call ResetIRQ
lidt [idtp]

mov eax, cr0
inc eax
mov cr0, eax

;jmp $

retfd
jmp dword 8:0x100000



MemCopy: ;fs:esi, fs:edi, ecx
push esi
mov si, msg3
call PrintString
pop esi

mov eax, esi
call $PrintDWord

mov ax, 0x0E20
int 0x10
mov eax, edi
call $PrintDWord

mov ax, 0x0E20
int 0x10
mov eax, ecx
call $PrintDWord

mov ax, 0x0E0D
int 0x10
mov ax, 0x0E0A
int 0x10

.l0:
mov al, [fs:esi]
mov [fs:edi], al
inc esi
inc edi

or ecx, ecx
jz .l1
dec ecx
jmp .l0
.l1:

ret

PrintString: ;ds:si=string
lodsb
or al, al
jz .l0
mov ah, 0x0E
int 0x10
jmp PrintString
.l0:
ret

DieString: ;ds:si=string
call PrintString
mov ax,0x0E07
int 0x10
int 0x10
xor ax,ax
int 0x16
int 0x19


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

$PrintDWord:
push eax
rol eax, 16
call $PrintWord
pop eax
call $PrintWord
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
msg1 db "Setup Loader Started", 13, 10, 0

badkernel db "Bad Kernel Image", 13, 10, 0
msg2 db "Starting Kernel, Entry VMA: ", 0

msg3 db "MemCopy(src, dst, len): ", 0

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
  ;code, 8(0x8)
dd 0x0000FFFF
dd 0x00CF9A00
  ;data, 16(0x10)
dd 0x0000FFFF
dd 0x00CF9200
  ;code-16, 24(0x18)
dd 0x0000FFFF
dd 0x00009A00
  ;data-16, 32(0x20)
dd 0x0000FFFF
dd 0x00009200
  ;data-16, 40(0x28), window
dd 0x0000FFFF
dd 0x00009200

  ;code (ring 3), 48(0x30)
dd 0x0000FFFF
dd 0x00CFFA00
  ;data (ring 3), 56(0x38)
dd 0x0000FFFF
dd 0x00CFF200
  ;free
times 368 dd 0
