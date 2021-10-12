CFLAGS=-ffreestanding -nostdinc -I. -Iinclude -I../../include

all: app0.exe app1.exe app2.exe copy.exe # gui0.exe gapp0.exe nasm.exe ndisasm.exe ls.exe

FORCE:

LIBC_OBJS = \
	clib/libc.o

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.ao: %.as
	nasm -f win32 -o $@ $<

nasm.exe: FORCE
	make -C nasm -f Makefile.os1

ndisasm.exe: FORCE
	make -C nasm -f Makefile.os1

clib/libc.o: FORCE
	make -C clib

app0.exe: $(LIBC_OBJS) app0.o
	ld -e _start -o app0.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) app0.o

app1.exe: $(LIBC_OBJS) app1.o
	ld -e _start -o app1.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) app1.o

app2.exe: $(LIBC_OBJS) app2.o
	ld -e _start -o app2.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) app2.o

copy.exe: $(LIBC_OBJS) copy.o
	ld -e _start -o copy.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) copy.o

ls.exe: $(LIBC_OBJS) ls.o
	ld -e _start -o ls.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) ls.o

gui0/gui0.exe: FORCE
	make -C gui0

gui0.exe: gui0/gui0.exe
	cp gui0/gui0.exe ./

gui0/gapp0.exe: FORCE
	make -C gui0

gapp0.exe: gui0/gapp0.exe
	cp gui0/gapp0.exe ./
