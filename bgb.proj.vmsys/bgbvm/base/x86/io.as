global inportb
global outportb
global inportw
global outportw

[section .text]
[bits 32]

  ;int inportb(int port)
inportb:
push ebp
mov ebp,esp
mov edx, [ebp+8]
xor eax, eax
in al, dx
pop ebp
ret

  ;int outportb(int port,int value)
outportb:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, al
pop ebp
ret

  ;int inportw(int port)
inportw:
push ebp
mov ebp,esp
mov edx,[ebp+8]
xor eax,eax
in ax,dx
pop ebp
ret

  ;int outportw(int port,int value)
outportw:
push ebp
mov ebp,esp
mov edx,[ebp+8]
mov eax,[ebp+12]
out dx,ax
pop ebp
ret
