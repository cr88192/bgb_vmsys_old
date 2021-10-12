global main

global prim_apply
global prim_close
global prim_frame
global prim_bind
global prim_bindargs

global S_G
global S_S

extern S_untitled
extern printf
extern S_rectst2
extern S_rectst
extern S_nop

[section .text]
[bits 32]

prim_close:
ret

prim_apply:
;mov esi, [edi]
mov edx, eax
push dword 0
push dword 0
;mov [edi], esp

mov esi, esp
push edi
mov edi, [edi+20]
mov ecx, 16
rep movsd
pop edi

mov eax, [edi+20]
mov [edi], eax
mov esp, [edi+20]

jmp edx

;currently broken
prim_bind:
ret

prim_bindargs:
ret

prim_frame:
pop ecx
mov esi, esp
push dword 0		;20
push eax			;16
push esi			;12
push edi			;8
push dword 0		;4
mov edx, [edi]
push edx			;0
mov edi, esp

sub esp, 64
mov [edi+20], esp

jmp ecx

test_G:
mov esi, [edi]
mov eax, [esi+8]
mov edx, [esi+12]

cmp eax, edx
jle .l0
mov eax, 0x202
jmp .l1
.l0:
mov eax, 0x102
.l1:

mov edx, [edi+16]
mov esp, [edi+12]
mov edi, [edi+8]
jmp edx


test_S:
mov esi, [edi]
mov eax, [esi+8]
mov edx, [esi+12]
sub eax, edx

mov edx, [edi+16]
mov esp, [edi+12]
mov edi, [edi+8]
jmp edx

test_doing:
mov esi, [edi]
mov eax, [esi+8]

push eax
push esp
push dword doing_str
call printf
pop ecx
pop ecx
pop ecx

mov edx, [edi+16]
mov esp, [edi+12]
mov edi, [edi+8]
jmp edx

test_done:
push esp
push dword done_str
call printf
pop ecx

mov edx, [edi+16]
mov esp, [edi+12]
mov edi, [edi+8]
jmp edx

main:
push ebp
mov ebp, esp

call S_untitled

;mov esi, esp
;push dword main1	;16
;push esi			;12
;push dword 0		;8
;push dword 0		;4
;push dword 0		;0
;mov edi, esp

mov eax, main1
call prim_frame

push dword test_done
push dword test_doing
push dword 80
mov eax, [S_rectst2]
jmp prim_apply

main1:
push esp
push dword done_str
call printf
pop ecx
pop ecx

mov esp, ebp
pop ebp
ret

[section .data]
[bits 32]
doing_str db "doing %p %d", 10, 0
done_str db "done %p", 10, 0
S_S dd test_S
S_G dd test_G