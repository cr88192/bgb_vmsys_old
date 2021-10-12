global keyb_isr
extern k_dataseg
extern keyb_handler

[section .text]
[bits 32]

keyb_isr:
pusha

call keyb_handler

mov al,0x20
out 0x20,al

popa
iret