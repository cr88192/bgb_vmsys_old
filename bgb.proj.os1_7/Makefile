CFLAGS=-DX86_BOOT -I$(PWD)/include

all: x86 root/apps

x86: bin/x86/boot bin/x86/boot_fat bin/x86/setup bin/x86/kernel

%.o: %.c
	gcc $(CFLAGS) -DKERNEL -c -o $@ $<

#	as --emulation=elf32-i386 -o $@ $<

#mainly for convienience
%.ao: %.as; nasm -f win32 -o $@ $<

%.as: %.scm
	scm2as $< $@

FORCE:

bin/x86/boot: boot/x86/boot0.as
	nasm -f bin -o bin/x86/boot boot/x86/boot0.as

bin/x86/setup: boot/x86/setup2.as
	nasm -f bin -o bin/x86/setup boot/x86/setup2.as

bin/x86/boot_fat: boot/x86/boot_fat3.as
	nasm -f bin -o bin/x86/boot_fat boot/x86/boot_fat3.as

boot/x86/head.o: boot/x86/head0.as
	nasm -f win32 -o boot/x86/head.o boot/x86/head0.as

BGBSCM_OBJS = \
	bgbscm4/main_ka2.o \
	\
	bgbscm4/parse.o \
	bgbscm4/parse2.o \
	bgbscm4/typefcn.o \
	bgbscm4/namespace2.o \
	bgbscm4/hpi3_compile.o \
	bgbscm4/hpi4_interp.o \
	bgbscm4/asm_x86nasm.o \
	bgbscm4/builtin.o \
	bgbscm4/interp.o \
	bgbscm4/ty_obj0.o \
	bgbscm4/ty_math.o

KERNEL_OBJS = \
	base/bitarray2.o\
	base/c_main.o	\
	base/console.o	\
	base/devreg.o	\
	base/kfunc.o	\
	\
	base/memory2.o	\
	\
	base/vars.o		\
	base/vfile.o	\
	base/vf_misc.o	\
	base/parse.o	\
	base/objtype.o	\
	\
	base/long64.o	\
	base/usemu/miscmath.o	\
	\
	devices/initdev.o	\
	fs/vpath.o		\
	fs/vmount.o		\
	fs/vdir.o		\
	fs/vfs.o		\
	fs/vfs_ns.o		\
	fs/sltype.o		\
	\
	fs/devfs/devfs.o	\
	fs/ramfs/ramfs.o	\
	fs/bshfs/bshfs.o	\
	\
	fs/fatfs/fatfs.o	\
	fs/fatfs/cluster.o	\
	fs/fatfs/file.o	\
	fs/fatfs/dir.o	\
	fs/fatfs/fatsl.o	\
	\
	k_main.o		\
	\
	devices/ptab/part_ms.o \
	\
	net/net.o		\
	net/netval.o		\
	net/rpc1.o		\
	\
	net/ethernet/eth.o	\
	net/ethernet/arp.o	\
	\
	net/ipv4/ipv4.o		\
	net/ipv4/icmpv4.o	\
	net/ipv4/udpv4.o	\
	net/ipv4/tcpv4.o	\
	\
	net/netapi/meta0_base.o	\
	\
	net/http/http_sv.o	\
	net/http/http_cl.o	\
	net/http/mime.o		\
	\
	net/ppp/ppp.o		\
	net/ppp/rfc1661.o	\
	net/ppp/rfc1662.o	\
	net/ppp/rfc2472.o	\
	net/ppp/rfc1332.o


#	fs/vpathvm.o		\
#	base/storage.o	\
#	\
#	base/vf_sock.o	\
#	base/memory3.o	\

#	base/memory2.o	\

#	bgbscm3/main_ka.o		\
#	bgbscm3/parse.o			\
#	bgbscm3/typefcn.o		\
#	bgbscm3/interp2.o		\
#	bgbscm3/namespace.o		\
#	bgbscm3/ty_obj.o		\
#	bgbscm3/ty_port.o		\
#	bgbscm3/hpi_compile.o	\
#	bgbscm3/hpi_interp.o	\
#	bgbscm3/builtin.o		\
#	\
#	perheap/page_linux.o	\
#
#	core/x86/minvoke.ao	\
#	\
#	bgbscm2/main_ka.o	\
#	bgbscm2/parse.o		\
#	bgbscm2/typefcn.o	\
#	bgbscm2/ty_port.o	\
#	bgbscm2/ty_obj.o	\
#	bgbscm2/interp2.o	\
#	bgbscm2/namespace.o

#	bgbscm2/interp.o	\
#	bgbscm2/scm_fcns.o	\
#
#	bgbscm/bgbscm.o		\
#	bgbscm/scmfcn0.ao

#	$(MZSCM_OBJS)

#	fs/ramfs/buffer.o	\

KERNEL_DRIVERS = \
	devices/condev/condev.o		\
	devices/condev/keyboard.o	\
	devices/condev/text.o		\
	\
	devices/rs232/rs232.o		\
	devices/rs232/rs232_ll.ao	\
	\
	devices/fdc/fdc.o			\
	devices/fdc/dma.o			\
	\
	devices/ata/ata.o			\
	devices/ata/ata_ll.ao		\
	\
	devices/gfxdev2/gfxdev.o	\
	\
	devices/gfx_vga/gfxdrv.o		\
	devices/gfx_vga/gfx.o		\
	devices/gfx_vga/640x480x16.o	\
	devices/gfx_vga/twkuser.o		\
	devices/gfx_vga/vgalib.o		\
	\
	devices/mouse/mouse.o	\
	devices/pcibus/pcibus.o \
	devices/rtl8139/rtl8139.o

#	devices/gfx_vesa/gfxvesa.o	\
#	\
#	devices/gfxdev/gfxdev.o		\
#	devices/gfxdev/fonts.o		\
#	devices/gfxdev/font0.o		\
#	devices/gfxdev/koi8r.o		\
#	devices/gfxdev/cp866.o		\
#
#
#	devices/gfx_vesa/vesa_v86.ao	\
#
#	devices/imagedev/imagedev.o
#
#	devices/gfx_vga/gfxdrv.o		\
#	devices/gfx_vga/gfx.o		\
#	devices/gfx_vga/320x240x256.o	\
#	devices/gfx_vga/640x480x16.o	\
#	devices/gfx_vga/gencctab.o		\
#	devices/gfx_vga/palette_c.o		\
#	devices/gfx_vga/palette_g.o		\
#	devices/gfx_vga/screen.o		\
#	devices/gfx_vga/twkuser.o		\
#	devices/gfx_vga/vgalib.o		\

#	core/x86/memory.o	\

KERNEL_X86_OBJS = \
	base/x86/clock.o	\
	base/x86/desc.o		\
	base/x86/irq.o		\
	base/x86/main.o		\
	base/x86/page.o		\
	base/x86/pit.o		\
	base/x86/t_event.o	\
	base/x86/tss.o		\
	base/x86/kthread.o	\
	base/x86/kpfh.o		\
	base/x86/syscall.o	\
	base/x86/peload.o	\
	\
	base/mm2ll_x86.o	\
	\
	base/x86/kthread_ll.ao	\
	base/x86/int.ao		\
	base/x86/io.ao		\
	base/x86/page.ao	\
	base/x86/time.ao	\
	base/x86/tss_ll.ao	\
	base/x86/memcnt.ao	\
	base/x86/syscall_ll.ao	\
	\
	base/string.o	\
	base/endian.o		\
	\
	$(KERNEL_DRIVERS)

#	base/mm2ll_x86.o	\
#	perheap/page_x86.o	\
#	\
#	base/usemu/memory.o	\

KERNEL_US_OBJS = \
	base/usemu/s_main.o	\
	base/usemu/vf_us.o	\
	base/usemu/kthread.o	\
	base/usemu/kpfh.o	\
	base/mm31_us.o	\
	base/misc_us.o \
	\
	devices/condev_us/condev.o	\
	devices/condev_us/rs232.o	\
	devices/fdc_us/fdc.o		\
	\
	devices/gfx_x11/gfxdev_x11.o	\
	devices/gfx_x11/gfxdrv.o	\
	\
	devices/gfxdev/gfxdev.o		\
	devices/gfxdev/fonts.o		\
	devices/gfxdev/font0.o		\
	devices/gfxdev/koi8r.o		\
	devices/gfxdev/cp866.o		\
	\
	devices/mouse_us/mouse_us.o

#	base/mm2ll_us.o	\
#	devices/imagedev_us/imagedev.o
#	perheap/page_linux.o	\
#	\
#

X86_LDFLAGS=

bin/x86/kernel: boot/x86/head.o $(KERNEL_OBJS) $(KERNEL_X86_OBJS)
	ld -e _start -o bin/x86/kernel.sys -Ttext 0x100000 \
		boot/x86/head.o \
		$(KERNEL_OBJS) $(KERNEL_X86_OBJS)
	objcopy -O binary -S \
		bin/x86/kernel.sys bin/x86/kernel

kernel.so: boot/x86/head.o $(KERNEL_OBJS) $(KERNEL_X86_OBJS)
	ld -r -o kernel.so \
		boot/x86/head.o \
		$(KERNEL_OBJS)

root/apps: FORCE
	make -C root/apps

# $(KERNEL_X86_OBJS)

# -Ttext 0x10000 
#	ld --oformat binary -o bin/x86/kernel -Ttext 0x10000 \
#		 boot/x86/head0.ao bin/x86/kernel.elf

#	ld --oformat binary -e _start -o bin/x86/kernel -Ttext 0x10000 \
#		boot/x86/head.o $(KERNEL_OBJS) $(KERNEL_X86_OBJS)

US_LDFLAGS=-L/usr/X11/lib -lGL -lX11 -lXext -lXxf86dga -lXxf86vm

kernel_us: $(KERNEL_OBJS) $(KERNEL_US_OBJS)
	gcc $(US_LDFLAGS) -pg -g -o kernel_us $(KERNEL_OBJS) $(KERNEL_US_OBJS)

KERNEL_HOSTED_OBJS = \
	kernel/hosted/main.o \
	kernel/hosted/kfunc.o

HOST_LINUX_BOOT_OBJS = \
	boot/host_linux/boot.o

bin/host_linux/boot: $(HOST_LINUX_BOOT_OBJS)
	gcc -ldl -o bin/host_linux/boot $(HOST_LINUX_BOOT_OBJS)

bin/host_linux/kernel-hosted.so: $(KERNEL_OBJS) $(KERNEL_HOSTED_OBJS); \
	gcc -shared -nostdinc -nostdlib -nostartfiles \
		-o bin/host_linux/kernel-hosted.so \
		$(KERNEL_OBJS) $(KERNEL_HOSTED_OBJS)

KERNEL_BAKS = $(KERNEL_OBJS:.o=.c~)
KERNEL_X86_BAKS = $(KERNEL_X86_OBJS:.o=.c~)
KERNEL_HOSTED_BAKS = $(KERNEL_HOSTED_OBJS:.o=.c~)

clean: FORCE
	rm -rf $(shell find -name \*.o)
	rm -rf $(shell find -name \*.c~)
