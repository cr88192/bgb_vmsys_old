global _irq0_ISR
global _irq8_ISR
global time_msec_count
global time_system_ticks

extern clock_second
extern tev_think
extern k_dataseg
extern current_thread
extern kthread_schedule

[section .text]
[bits 32]

_irq0_ISR: ;timer tick
pusha
;push ds
;push es
mov esi, [current_thread]
mov [esi], esp

;mov ax,[cs:k_dataseg]
;mov ds,ax
;mov es,ax

inc dword [time_system_ticks]

add dword [time_msec_count],10
cmp dword [time_msec_count],1000
jbe .l0
mov dword [time_msec_count],0
call clock_second
.l0:

call tev_think

mov al,0x20
out 0x20,al

call kthread_schedule

mov esi, [current_thread]
mov esp, [esi]

;pop es
;pop ds
popa
iret

_irq8_ISR: ;real time clock, called every 976usec
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
time_msec_count dd 0
time_system_ticks dd 0
