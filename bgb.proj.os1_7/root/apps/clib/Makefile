# zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

CFLAGS=-ffreestanding -nostdinc -I. -I../include -I../../../include

all: libc.o

LIBC_OBJS = \
	stdio.o \
	malloc.o \
	printf.o \
	string.o \
	stdlib.o \
	\
	memory2.o \
	mm2ll_os1.o \
	\
	os1/crt0.ao \
	os1/syscall.ao \
	os1/cl_syscalls.o \
	os1/readdir.o \
	\
	os1/msgutil.o

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.ao: %.as
	nasm -f win32 -o $@ $<

libc.o: $(LIBC_OBJS)
	ld -r -o libc.o $(LIBC_OBJS)
