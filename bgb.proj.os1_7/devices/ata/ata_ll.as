extern _k_dataseg
extern _ata_handler
global _ata_isr

[section .text]
[bits 32]

_ata_isr:
pusha
;push ds
;push es

;mov ax,[cs:_k_dataseg]
;mov es,ax
;mov ds,ax

call [_ata_handler]

mov al,0x20
out 0xA0,al
out 0x20,al

;pop es
;pop ds
popa
iret