global __irq0_ISR
global __irq8_ISR
global _time_msec_count
global _time_system_ticks

extern _clock_second
extern _tev_think
extern _k_dataseg
extern _current_thread
extern _kthread_schedule

[section .text]
[bits 32]

__irq0_ISR: ;timer tick
pusha
;push ds
;push es
mov esi, [_current_thread]
mov [esi], esp
mov eax, cr3
mov [esi+8], eax

;mov ax,[cs:_k_dataseg]
;mov ds,ax
;mov es,ax

inc dword [_time_system_ticks]

add dword [_time_msec_count],10
cmp dword [_time_msec_count],1000
jbe .l0
mov dword [_time_msec_count],0
call _clock_second
.l0:

call _tev_think

mov al,0x20
out 0x20,al

call _kthread_schedule

mov esi, [_current_thread]
mov edi, [esi]

;mov eax, [esi+8]
;mov ebx, cr3
;cmp eax, ebx
;je .l1
;mov cr3, eax
;.l1:
mov eax, [esi+8]
mov cr3, eax

;pop es
;pop ds

mov esp, edi
popa
iret

__irq8_ISR: ;real time clock, called every 976usec
pusha
;push ds
;push es

;mov ax,[cs:k_dataseg]
;mov ds,ax
;mov es,ax

;inc dword [time_msec_count]
;cmp dword [time_msec_count],1024
;jbe .l0
;mov dword [time_msec_count],0
;call clock_second
;.l0:

mov al,0x20
out 0xA0,al
out 0x20,al

;pop es
;pop ds
popa
iret

[section .data]
[bits 32]
_time_msec_count dd 0
_time_system_ticks dd 0
