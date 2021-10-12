global GrabTSS
global StartKernelTSS
extern TS_DumpTaskState

[section .text]
[bits 32]

;generate a tss from execution state, esp's and eip should be changed before
;use under any condition

;void GrabTSS(struct tss32_t *tss)
GrabTSS:
push ebp
mov ebp,esp
push edi	;-4

pushfd		;-8
cli
pushad		;-12

mov edi,[ebp+8]
mov [edi+4],esp
mov [edi+8],ss
mov [edi+12],esp
mov [edi+16],ss
mov [edi+20],esp
mov [edi+24],ss
mov eax,cr3
mov [edi+28],eax
;push eip
;pop eax
xor eax,eax
mov [edi+32],eax
mov eax,[ebp-8]
mov [edi+36],eax

mov eax,[ebp-12]
mov [edi+40],eax
mov eax,[ebp-16]
mov [edi+44],eax
mov eax,[ebp-20]
mov [edi+48],eax
mov eax,[ebp-24]
mov [edi+52],eax
mov eax,[ebp-28]
mov [edi+56],eax
mov eax,[ebp-32]
mov [edi+60],eax
mov eax,[ebp-36]
mov [edi+64],eax
mov eax,[ebp-40]
mov [edi+68],eax

push es
pop eax
mov [edi+72],eax
push cs
pop eax
mov [edi+76],eax
push ss
pop eax
mov [edi+80],eax
push ds
pop eax
mov [edi+84],eax
push fs
pop eax
mov [edi+88],eax
push gs
pop eax
mov [edi+92],eax

sldt ax
mov [edi+96],ax

popad
sti
popfd

pop edi
pop ebp
ret

;void StartKernelTSS(int num, struct tss32_t *tss)
StartKernelTSS:
push ebp
mov ebp,esp
push edi

mov edi,[ebp+12]

;hrm... most of this is not needed, as the tss would be filled on task switch
push edi
call GrabTSS
pop eax

mov [edi+4],esp
mov [edi+12],esp
mov [edi+20],esp
mov [edi+56],esp
mov [edi+60],ebp

mov dword [edi+32],.exit0

;push edi
;call TS_DumpTaskState
;pop eax

;this here is all that is really needed
mov ax,[ebp+8]
ltr ax

.exit0:
pop edi
pop ebp
ret