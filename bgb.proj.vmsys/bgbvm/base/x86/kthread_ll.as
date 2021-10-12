extern current_thread
extern active_list

extern kthread_terminate
extern kthread_schedule
extern kthread_insert_active

global kthread_ll_thread
global kthread_start
global kthread_ll_endquantum

[section .text]
[bits 32]

;int kthread_ll_thread(kthread *thread, int (*entry)(void *), void *data)
kthread_ll_thread:
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
call kthread_terminate

mov esi, [current_thread]
mov esp, [esi]
popa
iret

;int kthread_start(kthread *thread, int prio)
kthread_start:
push ebp
mov ebp, esp

cli
;store thread context for the parent
pushf
push cs
push dword .l0
pusha
mov esi, [current_thread]
mov [esi], esp

;start new thread
mov eax, [active_list]
mov esi, [ebp+8]
mov [esi+4], eax

mov [current_thread], esi
mov esp, [esi]

popa
iret

.l0:
sti

pop ebp
ret

kthread_ll_endquantum:
push ebp
mov ebp, esp

cli

pushf
push cs
push dword .l0
pusha

mov esi, [current_thread]
mov [esi], esp

call kthread_schedule

mov esi, [current_thread]
mov esp, [esi]
popa
iret

.l0:
sti
pop ebp
ret