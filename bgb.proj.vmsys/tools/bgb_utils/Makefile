CFLAGS = -g

SKYTOOL_OBJS = skytool.o targa.o grab.o
LMP2TGA_OBJS = lmp2tga.o targa.o
TGA2P32_OBJS = tga2p32.o targa.o

ALIAS2BGF_OBJS = alias2bgf0.o
BGF2ALIAS_OBJS = bgf2alias.o
BGF2TRIS_OBJS = bgf2tris.o
TRIS2BGF_OBJS = tris2bgf.o


all: skytool lmp2tga tga2p32 alias2bgf bgf2alias bgf2tris tris2bgf

skytool: $(SKYTOOL_OBJS)
	gcc -o skytool $(SKYTOOL_OBJS)

lmp2tga: $(LMP2TGA_OBJS)
	gcc -o lmp2tga $(LMP2TGA_OBJS)

tga2p32: $(TGA2P32_OBJS)
	gcc -o tga2p32 $(TGA2P32_OBJS)

alias2bgf: $(ALIAS2BGF_OBJS)
	gcc -o alias2bgf $(ALIAS2BGF_OBJS)

bgf2alias: $(BGF2ALIAS_OBJS)
	gcc -o bgf2alias $(BGF2ALIAS_OBJS)

bgf2tris: $(BGF2TRIS_OBJS)
	gcc -o bgf2tris  $(BGF2TRIS_OBJS)

tris2bgf: $(TRIS2BGF_OBJS)
	gcc -o tris2bgf $(TRIS2BGF_OBJS)

clean:
	rm *.o
