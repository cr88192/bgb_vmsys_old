extern _current_thread
extern _active_list

extern _kthread_terminate
extern _kthread_schedule
extern _kthread_insert_active

global _kthread_ll_thread
global _kthread_ll_start
global _kthread_ll_endquantum

[section .text]
[bits 32]

;int kthread_ll_thread(kthread *thread, int (*entry)(void *), void *data)
_kthread_ll_thread:
push ebp
mov ebp, esp
push esi
push edi

cli
mov edi, esp

mov esi, [ebp+8]
mov esp, [esi]

push dword [ebp+16]
push dword .l1
push dword [ebp+12]

pushf
push dword 8
push dword .l0

pusha

mov [esi], esp
mov eax, cr3
mov [esi+8], eax

mov esp, edi

sti

pop edi
pop esi
pop ebp
ret

.l0:
sti
ret

.l1:
call _kthread_terminate

mov esi, [_current_thread]
mov esp, [esi]
mov eax, [esi+8]
mov cr3, eax
popa
iret

;int kthread_start(kthread *thread, int prio)
_kthread_ll_start:
push ebp
mov ebp, esp

cli
;store thread context for the parent
pushf
push cs
push dword .l0
pusha
mov esi, [_current_thread]
mov [esi], esp
mov eax, cr3
mov [esi+8], eax

;start new thread
mov eax, [_active_list]
mov esi, [ebp+8]
mov [esi+4], eax

mov [_current_thread], esi
mov esp, [esi]
mov eax, [esi+8]
mov cr3, eax

popa
iret

.l0:
sti

pop ebp
ret

_kthread_ll_endquantum:
push ebp
mov ebp, esp

cli

pushf
push cs
push dword .l0
pusha

mov esi, [_current_thread]
mov [esi], esp
mov eax, cr3
mov [esi+8], eax

call _kthread_schedule

mov esi, [_current_thread]
mov esp, [esi]
mov eax, [esi+8]
mov cr3, eax

popa
iret

.l0:
sti
pop ebp
ret
