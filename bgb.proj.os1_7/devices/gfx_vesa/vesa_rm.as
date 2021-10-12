;keep this small enough that I can use short jumps for everything
;this will make use of the fact that <1MiB is linear-mapped

global vesall_getinfo

[section .text]
[bits 32]

vesall_getinfo:
push ebp
mov ebp, esp

pusha

cli

mov eax, cr3
mov [pm_cr3], eax

mov [pm_esp], esp
mov esp, 0xA000		;use a stack at 0xA000 (8KiB before clash with kernel stack)
;push cs

;goto real mode
mov eax, cr0
and eax, 0x7FFFFFFE
mov cr0, eax

;mov ax, 0xB800
;mov fs, ax
;mov byte [fs:0], 0xF041

push cs
push dword vesall_getinfo_return

;calculate address
mov eax, vesall_getinfo_rm
shr eax, 4
push eax
mov eax, vesall_getinfo_rm
and eax, 0xf
push eax

;jump
;retf

;fragment to avoid jump
mov eax, cr0
or eax, 0x80000001
mov cr0, eax

vesall_getinfo_return:

;mov byte [fs:0], 'E'

mov ax, ds
mov ds, ax	;in case ds was pushed/popped in rm

mov es, ax
mov ss, ax
;mov fs, ax
;mov gs, ax

mov esp, [pm_esp]

;mov eax, [pm_cr3]
;mov cr3, eax

;mov byte [fs:0], 'F'
sti

popa
pop ebp
ret


[bits 16]
vesall_getinfo_rm:
;xor ax, ax
;mov ss, ax
;mov es, ax

;mov byte [fs:0], 'B'

;mov ax, 0x4F00
;mov di, 0xA000	;use this addr as a scratchpad

;mov dword [es:di], 'VBE2'

;pushf
;call far [0x40]

;mov byte [fs:0], 'C'

;enter protected mode again
mov eax, cr0
or eax, 0x80000001
mov cr0, eax

;mov byte [fs:0], 'D'

;jump to return point, cs allready on stack
;push dword vesall_getinfo_return
;retfd
db 0x67, 0xCB ;0x66

;jmp dword 8:vesall_getinfo_return

[section .data]
[bits 32]

pm_esp dd 0
pm_cr3 dd 0
;pm_ss dd 0