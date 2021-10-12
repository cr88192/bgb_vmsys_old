global _rs232_isr
extern _rs232_handler

[section .text]
[bits 32]

_rs232_isr:
pusha
cli

call _rs232_handler

mov al,0x20
out 0x20,al

popa
iret