CFLAGS=-I. -DLB2AS

BGBSCM_OBJS = \
	parse.o \
	parse2.o \
	parse3.o \
	namespace2.o \
	namespace3.o \
	hpi3_compile.o \
	hpi4_interp.o \
	asm_x86nasm.o \
	builtin.o \
	interp.o \
	\
	typefcn.o \
	ty_typex.o \
	ty_obj1.o \
	ty_math.o \
	ty_print.o

%.o: %.c; gcc $(CFLAGS) -pg -g -c -o $@ $<

all: bgbscm.dll

bgbscm.dll: $(BGBSCM_OBJS) main_dll.o
	dlltool -e exports.o --export-all-symbols \
		$(BGBSCM_OBJS) main_dll.o
	gcc -pg -shared -o bgbscm.dll exports.o \
		$(BGBSCM_OBJS) main_dll.o
	rm exports.o

bgbscm: $(BGBSCM_OBJS)
	gcc -g -o bgbscm $(BGBSCM_OBJS) main_sa.o

clean:
	rm -rf $(shell find -name \*.o)
