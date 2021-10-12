global _inportb
global _outportb
global _inportw
global _outportw
global _inportd
global _outportd

[section .text]
[bits 32]

  ;int inportb(int port)
_inportb:
push ebp
mov ebp,esp
mov edx, [ebp+8]
xor eax, eax
in al, dx
pop ebp
ret

  ;int outportb(int port,int value)
_outportb:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, al
pop ebp
ret

  ;int inportw(int port)
_inportw:
push ebp
mov ebp,esp
mov edx,[ebp+8]
xor eax,eax
in ax,dx
pop ebp
ret

  ;int outportw(int port,int value)
_outportw:
push ebp
mov ebp,esp
mov edx,[ebp+8]
mov eax,[ebp+12]
out dx,ax
pop ebp
ret

  ;int inportd(int port)
_inportd:
push ebp
mov ebp, esp
mov edx, [ebp+8]
xor eax, eax
in eax, dx
pop ebp
ret

  ;int outportd(int port,int value)
_outportd:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, eax
pop ebp
ret
