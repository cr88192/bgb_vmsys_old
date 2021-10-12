CFLAGS=-Iinclude -Wall

%.o: %.c; gcc $(CFLAGS) -pg -g -c -o $@ $<

PDLIB_OBJS=\
	pd_base/kfunc.o \
	pd_base/mm2ll_us.o \
	pd_base/memory2.o \
	pd_base/objtype.o \
	pd_base/image.o \
	pd_base/load.o \
	\
	pd_base/long64.o \
	pd_base/vfile.o \
	pd_base/vf_us.o

PDNET_OBJS=\
	pd_net/sock_us/w32_net.o \
	pd_net/sock_us/w32_guid.o \
	pd_net/sock_us/w32_tcpip.o \
	pd_net/sock_us/w32_udpip.o \
	\
	pd_net/parse/parse_tree.o \
	pd_net/parse/parse_sx.o \
	pd_net/parse/parse_xml.o \
	\
	pd_net/net.o\
	pd_net/rpc1.o\
	pd_net/vars.o\
	pd_net/netval.o\
	\
	pd_net/meta0/meta0_base.o \
	\
	pd_net/http/http_sv.o \
	pd_net/http/http_cl.o \
	pd_net/http/mime.o \
	\
	pd_net/xml_rpc2/xmlrpc_base.o \
	pd_net/xml_rpc2/xmlrpc_decode.o \
	pd_net/xml_rpc2/xmlrpc_encode.o \
	pd_net/xml_rpc2/verify.o \
	\
	pd_net/sxrpc0/sxrpc_base.o \
	pd_net/sxrpc0/sxrpc_node.o \
	\
	pd_net/mrpt022/mrpt_trans.o \
	pd_net/mrpt022/mrpt_tags.o \
	pd_net/mrpt022/mrpt_tlv.o

all: pdlib.dll pdnet.dll tst_app0 tst_app1 tst_app2 \
	tst_app3 tst_app4 tst_app5 \
	bshfs_sv bshfs_cl

FORCE:

pdlib.dll: $(PDLIB_OBJS)
	dlltool -e exports.o --export-all-symbols \
		$(PDLIB_OBJS)
	gcc -pg -g -shared -o pdlib.dll exports.o \
		$(PDLIB_OBJS)
	rm exports.o

pdnet.dll: $(PDNET_OBJS) pdlib.dll
	dlltool -e exports.o --export-all-symbols \
		$(PDNET_OBJS)
	gcc -pg -g -shared -o pdnet.dll exports.o \
		$(PDNET_OBJS) pdlib.dll -lwsock32 -lole32
	rm exports.o

tst_app0: pdlib.dll apps/tst_app0.o
	gcc -pg -g -o tst_app0 pdlib.dll apps/tst_app0.o

tst_app1: pdlib.dll pdnet.dll apps/tst_app1.o
	gcc -pg -g -o tst_app1 pdlib.dll pdnet.dll apps/tst_app1.o

TST_APP2_OBJS=\
	apps/mud0/misc_us.o \
	apps/mud0/print.o \
	apps/mud0/entities.o \
	apps/mud0/tst_app2.o

tst_app2: pdlib.dll pdnet.dll $(TST_APP2_OBJS)
	gcc -pg -g -o tst_app2 pdlib.dll pdnet.dll $(TST_APP2_OBJS)

tst_app3: pdlib.dll pdnet.dll apps/tst_app3.o
	gcc -pg -g -o tst_app3 pdlib.dll pdnet.dll apps/tst_app3.o

tst_app4: pdlib.dll pdnet.dll apps/tst_app4.o
	gcc -pg -g -o tst_app4 pdlib.dll pdnet.dll apps/tst_app4.o

tst_app5: pdlib.dll pdnet.dll apps/tst_app5.o
	gcc -pg -g -o tst_app5 pdlib.dll pdnet.dll apps/tst_app5.o

BSHFS_SV_OBJS=\
	apps/bshfs/server.o

bshfs_sv: pdlib.dll pdnet.dll $(BSHFS_SV_OBJS)
	gcc -pg -g -o bshfs_sv pdlib.dll pdnet.dll $(BSHFS_SV_OBJS)

BSHFS_CL_OBJS=\
	apps/bshfs/client.o

bshfs_cl: pdlib.dll pdnet.dll $(BSHFS_CL_OBJS)
	gcc -pg -g -o bshfs_cl pdlib.dll pdnet.dll $(BSHFS_CL_OBJS)

install:
	cp *.dll /usr/lib
	cp -rf include/* /usr/include

clean:
	rm -rf $(shell find -name \*.o) *.img
