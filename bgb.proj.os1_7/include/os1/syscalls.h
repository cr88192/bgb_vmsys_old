#ifndef __OS1_SYSCALLS_H__
#define __OS1_SYSCALLS_H__

#define SYSCALL_PRINT		1
#define SYSCALL_OPEN		2
#define SYSCALL_READ		3
#define SYSCALL_WRITE		4
#define SYSCALL_CLOSE		5
#define SYSCALL_LSEEK		6
#define SYSCALL_IOCTL		7
#define SYSCALL_EOF		8
#define SYSCALL_INREADY		9
#define SYSCALL_SENDTO		10
#define SYSCALL_RECVFROM	11
#define SYSCALL_ACCEPT		12

#define SYSCALL_MOREMEM		16
#define SYSCALL_GETPID		17
#define SYSCALL_FORK		18
#define SYSCALL_EXECUTE		19
#define SYSCALL_SENDMSG		20
#define SYSCALL_RECVMSG		21
#define SYSCALL_SETKVAR		22
#define SYSCALL_GETKVAR		23
//24 unused
#define SYSCALL_GETMSTICKS	25
#define SYSCALL_USLEEP		26

#define SYSCALL_MOUNT		27
#define SYSCALL_UMOUNT		28
#define SYSCALL_RREADDIR	29
#define SYSCALL_OPENDIR		30
#define SYSCALL_CLOSEDIR	31

#endif