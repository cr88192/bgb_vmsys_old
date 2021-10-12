extern k_dataseg
extern ata_handler
global ata_isr

[section .text]
[bits 32]

ata_isr:
pusha
;push ds
;push es

;mov ax,[cs:k_dataseg]
;mov es,ax
;mov ds,ax

call [ata_handler]

mov al,0x20
out 0xA0,al
out 0x20,al

;pop es
;pop ds
popa
iret