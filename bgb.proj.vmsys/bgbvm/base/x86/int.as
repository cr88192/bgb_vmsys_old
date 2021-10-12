extern gdt
extern idt
extern gdt_ents
extern idt_ents
extern kprint
extern KPFH_HandleEvent

global Desc_Setup
global Desc_Get

global cpu_int0
global cpu_int1
global cpu_int2
global cpu_int3
global cpu_int4
global cpu_int5
global cpu_int6
global cpu_int7
global cpu_int8
global cpu_int9
global cpu_int10
global cpu_int11
global cpu_int12
global cpu_int13
global cpu_int14
global cpu_int15
global cpu_int16
global cpu_int17
global cpu_int18

global cpu_int13_catch

[section .text]
[bits 32]

Desc_Setup:
push ebp
mov ebp,esp

mov eax,[gdt_ents]
shl eax,3
dec eax
mov [gdtp],ax
mov eax,[gdt]
mov [gdtp+2],eax

lgdt [gdtp]

mov eax,[idt_ents]
shl eax,3
dec eax
mov [idtp],ax
mov eax,[idt]
mov [idtp+2],eax

lidt [idtp]

pop ebp
ret

;void Desc_Get(unsigned long *gdt, unsigned long *idt)
Desc_Get:
push ebp
mov ebp,esp
push edi

sgdt [gdtp]
sidt [idtp]

mov eax,[gdtp+2]
mov edi,[ebp+8]
mov [edi],eax

mov eax,[idtp+2]
mov edi,[ebp+12]
mov [edi],eax

pop edi
pop ebp
ret

cpu_int0:
pusha
push dword cpu_int0_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int1:
pusha
push dword cpu_int1_msg
call kprint
pop eax
popa
iret

cpu_int2:
pusha
push dword cpu_int2_msg
call kprint
pop eax
popa
iret

cpu_int3:
pusha
push dword cpu_int3_msg
call kprint
pop eax
popa
iret

cpu_int4:
pusha
push dword cpu_int4_msg
call kprint
pop eax
popa
iret

cpu_int5:
pusha
push dword cpu_int5_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int6:
pusha
push dword cpu_int6_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int7:
pusha
push dword cpu_int7_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int8:
pusha
push dword cpu_int8_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int9:
pusha
push dword cpu_int9_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int10:
pusha
push dword cpu_int10_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int11:
pusha
push dword cpu_int11_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int12:
pusha
push dword cpu_int12_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int13:
pusha

mov eax, [cpu_int13_catch]
or eax, eax
jz .l0
jmp [cpu_int13_catch]
.l0:

push dword cpu_int13_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int14:
pusha

mov eax, cr2
push eax
sti	;allow pf handler to block on io (in which case faulting thread is blocked)
call KPFH_HandleEvent
cli	;don't want ints anymore
pop ecx
and eax, eax
jnz .l0

push dword cpu_int14_msg
call kprint
pop eax
jmp $
.l0:

popa
add esp, 4
iret

cpu_int15:
pusha
push dword cpu_int15_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int16:
pusha
push dword cpu_int16_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int17:
pusha
push dword cpu_int17_msg
call kprint
pop eax
jmp $
popa
iret

cpu_int18:
pusha
push dword cpu_int18_msg
call kprint
pop eax
jmp $
popa
iret


[section .data]
[bits 32]

dw 0
gdtp:
dw 0
dd 0

dw 0
idtp:
dw 0
dd 0

cpu_int0_msg db "<<division error>>",10,0
cpu_int1_msg db "<<debug>>",10,0
cpu_int2_msg db "<<NMI>>",10,0
cpu_int3_msg db "<<breakpoint>>",10,0
cpu_int4_msg db "<<overflow>>",10,0
cpu_int5_msg db "<<bound>>",10,0
cpu_int6_msg db "<<opcode>>",10,0
cpu_int7_msg db "<<no fpu>>",10,0
cpu_int8_msg db "<<double fault>>",10,0
cpu_int9_msg db "<<fpu overrun>>",10,0
cpu_int10_msg db "<<bad tss>>",10,0
cpu_int11_msg db "<<bad desc>>",10,0
cpu_int12_msg db "<<no stack>>",10,0
cpu_int13_msg db "<<gpf>>",10,0
cpu_int14_msg db "<<page fault>>",10,0
cpu_int15_msg db "<<unknown>>",10,0
cpu_int16_msg db "<<fpu error>>",10,0
cpu_int17_msg db "<<align>>",10,0
cpu_int18_msg db "<<mc>>",10,0

cpu_int13_catch dd	0
