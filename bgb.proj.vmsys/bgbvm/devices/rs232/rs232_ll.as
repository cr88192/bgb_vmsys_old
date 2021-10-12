global rs232_isr
extern rs232_handler

[section .text]
[bits 32]

rs232_isr:
pusha
cli

call rs232_handler

mov al,0x20
out 0x20,al

popa
iret