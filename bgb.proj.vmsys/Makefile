CFLAGS=-I$(PWD)/bgbvm/include -I$(PWD)/bgbui/include \
	-I$(PWD)/bgbscm4 -I$(PWD)/bgbeng/qk_include \
	-I$(PWD)/bgflib03 -DGLQUAKE -Wall

all: bgfrender_glw gui0_glw bgbvmc bgbvmc2 bgbvmc3

FORCE:

%.o: %.c; gcc $(CFLAGS) -pg -g -c -o $@ $<

BGBSCM_OBJS = \
	bgbscm4/parse.o \
	bgbscm4/parse2.o \
	bgbscm4/parse3.o \
	bgbscm4/namespace2.o \
	bgbscm4/namespace3.o \
	bgbscm4/hpi3_compile.o \
	bgbscm4/hpi4_interp.o \
	bgbscm4/asm_x86nasm.o \
	bgbscm4/builtin.o \
	bgbscm4/interp.o \
	\
	bgbscm4/typefcn.o \
	bgbscm4/ty_typex.o \
	bgbscm4/ty_obj1.o \
	bgbscm4/ty_math.o \
	bgbscm4/ty_print.o


KERNEL_OBJS = \
	bgbvm/base/bitarray2.o\
	bgbvm/base/c_main.o	\
	bgbvm/base/console.o	\
	bgbvm/base/devreg.o	\
	bgbvm/base/kfunc.o	\
	bgbvm/base/memory3_1.o	\
	bgbvm/base/mm31_store.o	\
	bgbvm/base/vfile.o	\
	bgbvm/base/vf_misc.o	\
	bgbvm/base/parse.o	\
	bgbvm/base/vars.o	\
	\
	bgbvm/base/storage.o	\
	\
	bgbvm/base/long64.o	\
	bgbvm/base/usemu/miscmath.o	\
	\
	bgbvm/pdrel/objtype.o	\
	bgbvm/pdrel/image.o	\
	bgbvm/pdrel/load.o	\
	\
	bgbvm/fs/vpath.o		\
	bgbvm/fs/vmount.o		\
	bgbvm/fs/vdir.o		\
	bgbvm/fs/vfs.o		\
	\
	bgbvm/fs/devfs/devfs.o	\
	bgbvm/fs/fatfs/fatfs.o	\
	bgbvm/fs/ramfs/ramfs.o	\
	bgbvm/fs/dirfs/dirfs.o	\
	\
	bgbvm/devices/initdev.o	\
	\
	bgbvm/devices/ptab/part_ms.o \
	\
	bgbscm4/main_dll_ka2.o \
	\
	bgbvm/lbsext/lbsext.o \
	\
	bgbvm/lbsext/cgen_compile.o \
	\
	bgbvm/lbsext/hash0.o \
	bgbvm/lbsext/loadtext.o	\
	bgbvm/lbsext/parse_xml.o	\
	bgbvm/lbsext/miscext.o	\
	bgbvm/lbsext/fs_lbs.o	\
	\
	bgbvm/lbsext/vec_math.o	\
	bgbvm/lbsext/mathlib.o	\
	bgbvm/lbsext/mathlibf.o

#	\
#	$(BGBSCM_OBJS)
#	bgbvm/fs/vpathvm.o		\

#	bgbscm.dll

NET_OBJS = \
	bgbvm/net/net.o	\
	bgbvm/net/rpc1.o	\
	bgbvm/net/netval.o	\
	\
	bgbvm/net/ppp/ppp.o		\
	bgbvm/net/ppp/rfc1661.o	\
	bgbvm/net/ppp/rfc1662.o	\
	bgbvm/net/ppp/rfc2472.o	\
	bgbvm/net/ppp/rfc1332.o \
	\
	bgbvm/net/sock_us/w32_net.o	\
	bgbvm/net/sock_us/w32_udpip.o	\
	bgbvm/net/sock_us/w32_tcpip.o	\
	\
	bgbvm/net/sock_us/w32_guid.o	\
	\
	bgbvm/net/meta0/meta0_base.o	\
	\
	bgbvm/net/mrp01/mrp_proto.o \
	bgbvm/net/mrp01/mrp_message.o \
	bgbvm/net/mrp01/mrp_trans.o \
	bgbvm/net/mrp01/mrp_udpbuf.o \
	\
	bgbvm/net/parse/parse_tree.o \
	bgbvm/net/parse/parse_xml.o \
	bgbvm/net/parse/parse_sx.o \
	\
	bgbvm/net/sxrpc0/sxrpc_base.o \
	bgbvm/net/sxrpc0/sxrpc_node.o \
	bgbvm/net/sxrpc0/sxrpc_lbs.o \
	\
	bgbvm/net/http/http_sv.o \
	bgbvm/net/http/http_cl.o \
	bgbvm/net/http/mime.o \
	\
	bgbvm/net/xml_rpc2/verify.o \
	bgbvm/net/xml_rpc2/xmlrpc_base.o \
	bgbvm/net/xml_rpc2/xmlrpc_decode.o \
	bgbvm/net/xml_rpc2/xmlrpc_encode.o


#	bgbvm/net/xml_rpc/http.o \
#	bgbvm/net/xml_rpc/xml_rpc.o \
#	bgbvm/net/xml_rpc/verify.o \
#	\
#	$(BGBSCM_OBJS)	\
#	\


BGBUI_OBJS = \
	bgbui/devices/initdev.o	\
	\
	bgbui/render/gfxapi.o	\
	bgbui/render/render.o	\
	bgbui/render/guiobj0.o	\
	bgbui/render/uicon.o	\
	\
	bgbui/render/obj3d/render3d.o	\
	bgbui/render/obj3d/prim.o	\
	bgbui/render/obj3d/group.o	\
	bgbui/render/obj3d/sprite.o	\
	bgbui/render/obj3d/phys.o	\
	bgbui/render/obj3d/texture.o	\
	bgbui/render/obj3d/skycube.o

KERNEL_DRIVERS = \
	bgbvm/devices/condev/condev.o		\
	bgbvm/devices/condev/keyboard.o	\
	bgbvm/devices/condev/text.o		\
	\
	bgbvm/devices/rs232/rs232.o		\
	bgbvm/devices/rs232/rs232_ll.ao	\
	\
	bgbvm/devices/fdc/fdc.o			\
	bgbvm/devices/fdc/dma.o			\
	\
	bgbvm/devices/ata/ata.o			\
	bgbvm/devices/ata/ata_ll.ao		\
	\
	bgbvm/devices/gfx_vga/gfxdrv.o		\
	bgbvm/devices/gfx_vga/gfx.o		\
	bgbvm/devices/gfx_vga/640x480x16.o	\
	bgbvm/devices/gfx_vga/twkuser.o		\
	bgbvm/devices/gfx_vga/vgalib.o		\
	\
	bgbvm/devices/gfxdev/gfxdev.o		\
	bgbvm/devices/gfxdev/fonts.o		\
	bgbvm/devices/gfxdev/font0.o		\
	bgbvm/devices/gfxdev/koi8r.o		\
	bgbvm/devices/gfxdev/cp866.o		\
	\
	bgbvm/devices/mouse/mouse.o

KERNEL_US_OBJS = \
	bgbvm/base/usemu/s_main.o	\
	bgbvm/base/usemu/kthread.o	\
	bgbvm/base/usemu/kpfh.o	\
	bgbvm/base/mm31_us.o	\
	bgbvm/base/misc_us.o \
	\
	bgbvm/devices/condev_us/condev.o	\
	bgbvm/devices/condev_us/rs232.o	\
	bgbvm/devices/fdc_us/fdc.o


#	\
#	bgbvm/misc0.o

BGBUI_DRV_OBJS = \
	bgbui/devices/ifdev_us/keyb.o	\
	\
	bgbui/devices/gfx_glwin/gl_win.o	\
	bgbui/devices/gfx_glwin/gfxdev.o		\
	bgbui/devices/gfx_glwin/fonts.o		\
	bgbui/devices/gfx_glwin/font0.o		\
	bgbui/devices/gfx_glwin/koi8r.o		\
	bgbui/devices/gfx_glwin/cp866.o		\
	bgbui/devices/gfx_glwin/gl_draw.o	\
	bgbui/devices/gfx_glwin/gl_texture.o	\
	\
	bgbui/devices/mouse_us/mouse_us.o

#	devices/gfx_x11/gfxdev_x11.o	\
#	devices/gfx_x11/gfxdrv.o	\
#	\
#	devices/gfxdev/gfxdev.o		\
#	devices/gfxdev/fonts.o		\
#	devices/gfxdev/font0.o		\
#	devices/gfxdev/koi8r.o		\
#	devices/gfxdev/cp866.o		\
#	\
#	devices/mouse_us/mouse_us.o

#	main_win.o	\

BGFLIB_OBJS = \
	bgflib03/bgf_render.o \
	bgflib03/bgf_load.o \
	bgflib03/bgf_lb.o

VMUS_LDFLAGS=-lws2_32 -lole32

US_LDFLAGS=-L/usr/X11R6/lib -lGL -lGLw -lgdi32 -lopengl32 -lglaux -lglu32 \
	-luser32 -lcomdlg32 -lwinmm -lws2_32 -lole32 -lrpcrt4 -lkernel32

eng2: $(KERNEL_OBJS) $(KERNEL_US_OBJS) $(GLQUAKE_OBJS) $(BGFLIB_OBJS)
	gcc -pg -g -o eng2 $(KERNEL_OBJS) $(KERNEL_US_OBJS) $(GLQUAKE_OBJS) $(BGFLIB_OBJS) $(US_LDFLAGS)


#bgbscm.dll: $(BGBSCM_OBJS) bgbvm/bgbscm4/main_dll.o
#	dlltool -e exports.o --export-all-symbols \
#		$(BGBSCM_OBJS) bgbvm/bgbscm4/main_dll.o
#	gcc -pg -shared -o bgbscm.dll exports.o \
#		$(BGBSCM_OBJS) bgbvm/bgbscm4/main_dll.o
#	rm exports.o

bgbscm4/bgbscm.dll: FORCE
	make -C bgbscm4 bgbscm.dll

bgbscm.dll: bgbscm4/bgbscm.dll
	cp bgbscm4/bgbscm.dll ./

bgbvm.dll: $(KERNEL_OBJS) $(KERNEL_US_OBJS) bgbscm.dll
	dlltool -e exports.o --export-all-symbols \
		$(KERNEL_OBJS) $(KERNEL_US_OBJS)
	gcc -pg -shared -o bgbvm.dll exports.o \
		$(KERNEL_OBJS) $(KERNEL_US_OBJS) bgbscm.dll
	rm exports.o

net.dll: $(NET_OBJS) bgbscm.dll bgbvm.dll
	dlltool -e exports.o --export-all-symbols \
		$(NET_OBJS)
	gcc -pg -shared -o net.dll exports.o \
		$(NET_OBJS) bgbscm.dll bgbvm.dll $(VMUS_LDFLAGS)
	rm exports.o

#	$(KERNEL_OBJS) \
#	$(KERNEL_US_OBJS) \

RENDER_OBJS = \
	bgbscm.dll \
	bgbvm.dll \
	net.dll \
	$(BGFLIB_OBJS) \
	$(BGBUI_OBJS) \
	$(BGBUI_DRV_OBJS) \
	bgfrender/main_win.o

# bgfrender/gl_draw.o bgfrender/gl_texture.o

bgfrender_glw:  $(RENDER_OBJS)
	gcc -pg -g -o bgfrender_glw $(RENDER_OBJS) $(US_LDFLAGS)

GUI0_OBJS = \
	bgbscm.dll \
	bgbvm.dll \
	net.dll \
	$(BGBUI_OBJS) \
	$(BGBUI_DRV_OBJS) \
	gui0/main_win.o

# $(KERNEL_OBJS) $(KERNEL_US_OBJS)

gui0_glw: $(GUI0_OBJS)
	gcc -pg -g -o gui0_glw $(GUI0_OBJS) $(US_LDFLAGS)

BGBVMC_OBJS = \
	$(BGBSCM_OBJS)	\
	bgbscm4/main_sa.o

bgbvmc: $(BGBVMC_OBJS)
	gcc -pg -g -o bgbvmc $(BGBVMC_OBJS)

BGBVMC2_OBJS = \
	bgbscm.dll \
	bgbvm.dll \
	vmc2/main_win.o

#	$(KERNEL_OBJS) \
#	$(KERNEL_US_OBJS) \

bgbvmc2: $(BGBVMC2_OBJS)
	gcc -pg -g -o bgbvmc2 $(BGBVMC2_OBJS) $(US_LDFLAGS)

#	$(KERNEL_OBJS) \
#	$(KERNEL_US_OBJS) \
#	$(NET_OBJS) \

BGBVMC3_OBJS = \
	bgbscm.dll \
	bgbvm.dll \
	net.dll \
	$(BGBUI_OBJS) \
	$(BGBUI_DRV_OBJS) \
	vmc3/main_win.o

bgbvmc3: $(BGBVMC3_OBJS)
	gcc -pg -g -o bgbvmc3 $(BGBVMC3_OBJS) $(US_LDFLAGS)

KERNEL_BAKS = $(KERNEL_OBJS:.o=.c~)
KERNEL_X86_BAKS = $(KERNEL_X86_OBJS:.o=.c~)

clean:
	rm -rf $(shell find -name \*.o)

