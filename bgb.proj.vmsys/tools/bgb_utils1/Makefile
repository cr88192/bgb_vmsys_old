CFLAGS=-I. -DSAFLAG

all: alias2bgf bgf2alias bgfrender

%.o: %.c
	gcc $(CFLAGS) -pg -g -c -o $@ $<

BASE_OBJS = base_sa.o math.o parse.o typefcn.o ty_typex.o

alias2bgf: $(BASE_OBJS) alias2bgf1.o
	gcc -g -pg -o alias2bgf $(BASE_OBJS) alias2bgf1.o

bgf2alias: $(BASE_OBJS) bgf2alias.o
	gcc -g -pg -o bgf2alias $(BASE_OBJS) bgf2alias.o

RENDER_OBJS = render/gl_win.o render/main_win.o render/gl_draw.o render/gl_texture.o
RENDER_LDFLAGS=-L/usr/X11R6/lib -lGL -lGLw -lgdi32 -lopengl32 -lglaux -lglu32 -luser32 -lcomdlg32 -lwinmm -lwsock32

bgfrender: $(BASE_OBJS) $(RENDER_OBJS) 
	gcc -g -pg -o bgfrender $(BASE_OBJS) $(RENDER_OBJS) $(RENDER_LDFLAGS)
