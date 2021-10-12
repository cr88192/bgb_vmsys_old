CFLAGS=-ffreestanding -nostdinc -I. -I../include -I../../include

all: gui0.exe gapp0.exe

FORCE:

LIBC_OBJS = \
	../clib/libc.o

GUI_OBJS = \
	gui0.o

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.ao: %.as
	nasm -f win32 -o $@ $<

../clib/libc.o: FORCE
	make -C ../clib

gui0.exe: $(LIBC_OBJS) $(GUI_OBJS)
	ld -e _start -o gui0.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) $(GUI_OBJS)

GAPP0_OBJS = \
	gapp0.o

gapp0.exe: $(LIBC_OBJS) $(GAPP0_OBJS)
	ld -e _start -o gapp0.exe -Ttext 0x40000000 \
		$(LIBC_OBJS) $(GAPP0_OBJS)
