/*
gui core.
the gui is an app that accepts incomming connections, manages
rendering/input, ...

thought:
make basic gui consist of a number of potentially drawable "surfaces"
(including "textures"). drawing will be recursive (eg: the contents of one
surface are drawn onto another to show the widget). at the top level, surfaces
are drawn to the screen by way of "windows". whether the surfaces are "real"
or not is an implementation issue.

the next layer of gui will concern itself primarily with widgets.

8.6.10.8, 0.catagory.ctx.tag
catagory:
	0: basic protocol
	1: drawing/widget messages
		1: new surface, xs ys -> surfnum
		2: set surface, num x y w h ->
		3: add surface parent, num parent ->
		4: show surface, num ->
	2: input/interface messages
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphics/opcodes2.h>
#include <graphics/mouse.h>
#include <graphics/keys.h>
#include <os1/gui.h>

#define SURF_DIRTY	1	//recursively set to indicate need for redraw

struct gui_surf_s {
struct gui_surf_s *next;	//next surface in tree list
struct gui_surf_s *first;	//first child surface
struct gui_surf_s *up;		//parent surface
struct gui_surf_s *lnext;	//next surface in linear space

int id;		//surface id
int flags;	//surface flags

int x, y;	//origin of surface rel to parent, points
int w, h;	//width and height of surface, points

int xs, ys;	//dimensions of backbuffer
void *backbuf;	//backbuffer, RGBA32 normal, may later depend on vid card
};

struct gui_con_s {
int con;

long *stack;
int stackpos;
};

FILE *screen_fd;
FILE *keyboard_fd;
FILE *keymap_fd;
FILE *mouse_fd;

int gui_msg_sock;
struct gui_con_s **gui_cons;

int gui_width;	//virtual width of the screen in points
int gui_xorg;	//coords for the gui origin, points
int gui_yorg;

struct gui_surf_s *gui_rootsurf;	//root of surface tree, front->back
struct gui_surf_s *gui_firstsurf;	//first surface in linear list

int gui_lastsurfid;	//last surface id

unsigned char render_keymap[32];
int render_keybuf[64], render_keybuf_pos;

int render_mouse_pos[2], render_mouse_b;
int render_mouse_origin[2];

int Render_PollKey(int key)
{
	if(key<0 || key>255)return(0);
	if(render_keymap[key/8]&(1<<(key&7)))return(1);
	return(0);
}

struct gui_surf_s *Gui_NewSurface(int xs, int ys)
{
	int i, j;
	struct gui_surf_s *tmp;

	printf("New Surface %d %d\n", xs, ys);

	tmp=malloc(sizeof(struct gui_surf_s));
	memset(tmp, 0, sizeof(struct gui_surf_s));

	tmp->id=gui_lastsurfid++;

	tmp->xs=xs;
	tmp->ys=ys;
	tmp->backbuf=malloc(xs*ys*4);
//	memset(tmp->backbuf, 255, xs*ys*4);
	for(i=0; i<ys; i++)for(j=0; j<xs; j++)
		if((i^j)&1)
	{
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+0]=255;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+1]=255;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+2]=255;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+3]=255;
	}else
	{
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+0]=0;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+1]=0;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+2]=0;
		((char *)tmp->backbuf)[(((i*xs)+j)*4)+3]=255;
	}

	tmp->next=gui_firstsurf;
	gui_firstsurf=tmp;

	printf("Surface Created\n");

	return(tmp);
}

struct gui_surf_s *Gui_FindSurface(int id)
{
	struct gui_surf_s *cur;

	cur=gui_firstsurf;
	while(cur)
	{
		if(cur->id==id)return(cur);
		cur=cur->next;
	}
	return(NULL);
}

int Gui_AddSurfaceParent(int surf, int par)
{
	struct gui_surf_s *surf1, *surf2;

	printf("Add Surface Parent %d %d\n", surf, par);

	surf1=Gui_FindSurface(surf);
	surf2=Gui_FindSurface(par);

	if(!surf1 || !surf2)
	{
		fprintf(stderr, "Gui_AddSurfaceParent: bad surface\n");
		return(-1);
	}

	surf1->up=surf2;
	surf1->next=surf2->first;
	surf2->first=surf1;

	return(0);
}

int Gui_ShowSurface(int id)
{
	struct gui_surf_s *surf;

	printf("Show Surface %d\n", id);

	surf=Gui_FindSurface(id);

	surf->next=gui_rootsurf;
	gui_rootsurf=surf;
	return(0);
}

int Gui_HideSurface(int id)
{
	struct gui_surf_s *cur, *lst;

	printf("Hide Surface %d\n", id);

	cur=gui_rootsurf;
	lst=NULL;
	while(cur)
	{
		if(cur->id==id)
		{
			if(lst)lst->next=cur->next;
				else gui_rootsurf=lst->next;
		}
		lst=cur;
		cur=cur->next;
	}
	return(0);
}

int Gui_DropSurface(int id)
{
	struct gui_surf_s *cur, *cur2, *lst;

	printf("Destroy Surface %d\n", id);

	Gui_HideSurface(id);

	cur=gui_firstsurf;
	lst=NULL;
	while(cur)
	{
		if(cur->id==id)
		{
			if(lst)lst->next=cur->next;
				else gui_firstsurf=lst->next;
			cur2=cur->next;
			free(cur->backbuf);
			free(cur);
			cur=cur2;
			continue;
		}
		lst=cur;
		cur=cur->next;
	}
	return(0);
}

int Scr_WriteInt(int val)
{
	char buf[16];
	void *p;

	if(!screen_fd)return(-1);

	p=buf;
	*(short *)p=GFXOP2_INTEGER;
	p+=sizeof(short);
	*(short *)p=sizeof(long);
	p+=sizeof(short);
	*(long *)p=val;
	p+=sizeof(long);

	fwrite(buf, 1, (int)p-(int)(&buf), screen_fd);
	return(0);
}

int Scr_WriteString(char *str)
{
	char buf[512];
	void *p;

	if(!screen_fd)return(-1);

	p=buf;
	*(short *)p=GFXOP2_STRING;
	p+=sizeof(short);
	*(short *)p=strlen(str);
	p+=sizeof(short);
	strcpy(p, str);
	p+=strlen(str);

	fwrite(buf, 1, (int)p-(int)(&buf), screen_fd);
	return(0);
}

int Scr_WriteData(int sz, void *s)
{
	char buf[512];
	void *p;

	if(!screen_fd)return(-1);

	p=buf;
	*(short *)p=GFXOP2_DATAGLOB;
	p+=sizeof(short);
	*(short *)p=sizeof(long)+sizeof(void *);
	p+=sizeof(short);

	*(long *)p=sz;
	p+=sizeof(long);
	*(void **)p=s;
	p+=sizeof(void *);

	fwrite(buf, 1, (int)p-(int)(&buf), screen_fd);
	return(0);
}

int Scr_WriteOpcode(int code)
{
	char buf[16];
	void *p;

	if(!screen_fd)return(-1);

	p=buf;
	*(short *)p=code;
	p+=sizeof(short);
	*(short *)p=0;
	p+=sizeof(short);

	fwrite(buf, 1, (int)p-(int)(&buf), screen_fd);
	return(0);
}

int Scr_FillSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Scr_WriteInt(x);
	Scr_WriteInt(y);
	Scr_WriteInt(w);
	Scr_WriteInt(h);

	Scr_WriteInt(r);
	Scr_WriteInt(g);
	Scr_WriteInt(b);
	Scr_WriteInt(a);

	Scr_WriteOpcode(GFXOP2_FILLSQUARE);

	return(0);
}

int Scr_DrawImage(int x, int y, int w, int h, void *buf, int xs, int ys)
{
	Scr_WriteInt(x);
	Scr_WriteInt(y);
	Scr_WriteInt(w);
	Scr_WriteInt(h);

	Scr_WriteData(xs*ys*4, buf);
	Scr_WriteInt(xs);
	Scr_WriteInt(ys);

	Scr_WriteOpcode(GFXOP2_DRAWIMAGE);

	return(0);
}

int Gui_AcceptCon(int conid)
{
	int i;
	for(i=0; i<1024; i++)
		if(!gui_cons[i])
	{
		gui_cons[i]=malloc(sizeof(struct gui_con_s));
		gui_cons[i]->con=conid;

		gui_cons[i]->stack=malloc(256*sizeof(long));
		gui_cons[i]->stackpos=0;
		return(i);
	}
	return(-1);
}

int Gui_PollForCons()
{
	int i, j;

	i=0;
	while(i!=-1)
	{
		i=msg_accept(gui_msg_sock);
		if(i!=-1)
		{
			printf("gui: got con %d\n", i);
			j=Gui_AcceptCon(i);
		}
	}
	return(0);
}

int Gui_HandleCons()
{
	int class, size;
	int i, j;
	void *buf, *buf2;
	long *st, *mt;
	struct gui_con_s *con;
	struct gui_surf_s *surf;

	for(i=0; i<1024; i++)if(gui_cons[i])
		while(1)
	{
		con=gui_cons[i];
		buf=malloc(256);
		size=256;

		j=msg_get_message(con->con, &class, &size, buf);
		if((j==-1) && (size<=0))break;
		if((j==-1) && (size>0))
		{
			free(buf);
			buf=malloc(size);
			j=msg_get_message(con->con, &class, &size, buf);
		}
		switch(class)
		{
		case GUI_POPRET:
			printf("PR E\n");
			con->stackpos--;
			st=con->stack+con->stackpos;
			msg_send_message(con->con, GUI_INTEGER, sizeof(long), st);
			printf("PR OK\n");
			break;
		case GUI_INTEGER:
			st=con->stack+con->stackpos;
			con->stackpos++;
			st[0]=*(long *)buf;
			break;
		case GUI_STRING:
			st=con->stack+con->stackpos;
			con->stackpos++;
			st[0]=(long)strdup(buf);
			break;
		case GUI_DATA:
			st=con->stack+con->stackpos;
			con->stackpos++;
			buf2=malloc(size);
			memcpy(buf2, buf, size);
			st[0]=(long)buf2;
			break;

		case GUI_NEWSURF:
//			con->stackpos-=2;
			st=con->stack+con->stackpos;
			mt=buf;

			surf=Gui_NewSurface(mt[0], mt[1]);
			st[0]=surf->id;
			con->stackpos++;
			printf("NS OK\n");
			break;
		case GUI_SETSURFSZ:
//			con->stackpos-=5;
			st=con->stack+con->stackpos;
			mt=buf;

			surf=Gui_FindSurface(mt[0]);
			surf->x=mt[1];
			surf->y=mt[2];
			surf->w=mt[3];
			surf->h=mt[4];
			break;
		case GUI_ADDSURF:
//			con->stackpos-=2;
			st=con->stack+con->stackpos;
			mt=buf;
			Gui_AddSurfaceParent(mt[0], mt[1]);
			break;
		case GUI_SHOWSURF:
			mt=buf;
			Gui_ShowSurface(mt[0]);
			break;
		case GUI_HIDESURF:
			mt=buf;
			Gui_HideSurface(mt[0]);
			break;
		case GUI_DROPSURF:
			mt=buf;
			Gui_DropSurface(mt[0]);
			break;

		case GUI_FILLSURF:
			con->stackpos--;
			st=con->stack+con->stackpos;
			mt=buf;
			surf=Gui_FindSurface(mt[0]);
			memcpy(surf->backbuf, (void *)(st[0]),
				surf->xs*surf->ys*4);
			free((void *)(st[0]));
			break;

		default:
			break;
		}
		free(buf);
	}
}

int Gui_DrawSurfaces()
{
	struct gui_surf_s *cur;
	int rx, ry, rw, rh;

	cur=gui_rootsurf;
	while(cur)
	{
//		printf("Gui_DrawSurfaces: Surf %d\n", cur->id);

		rx=((cur->x-gui_xorg)*640)/gui_width;
		ry=((cur->y-gui_xorg)*640)/gui_width; //same scale
		rw=(cur->w*640)/gui_width;
		rh=(cur->h*640)/gui_width;

		rx+=320;
		ry+=240;

//		Scr_FillSquare(rx, ry, rw, rh, 255, 0, 0, 255);
		Scr_DrawImage(rx, ry, rw, rh,
			cur->backbuf, cur->xs, cur->ys);

		cur=cur->next;
	}
	return(0);
}

int main(int argc, char *argv[], char *env[])
{
	char buf[64];
	int i, fc;
	mouseinfo mi;

	screen_fd=NULL;

	keyboard_fd=fopen("/devices/keyboard", "r+b");
	keymap_fd=fopen("/devices/keyboard/keymap", "r+b");
	mouse_fd=fopen("/devices/mouse", "r+b");
	screen_fd=fopen("/devices/gfxdev", "r+b");

	gui_msg_sock=msg_new_socket();
	gui_cons=malloc(1024*sizeof(struct gui_con_s));
	memset(gui_cons, 0, 1024*sizeof(struct gui_con_s));

	gui_rootsurf=NULL;
	gui_firstsurf=NULL;
	gui_lastsurfid=1;

	gui_width=640;

	sprintf(buf, "0:%d:%d", getpid(), gui_msg_sock);
	kvar_set("volatile/system/gui-addr", buf);

//	execute("gapp0.exe", argv, env);

	fc=0;

	while(1)
	{
//		printf("frame begin\n");
		if(keymap_fd)
			fread(render_keymap, 1, 32, keymap_fd);
		render_keybuf_pos=0;

		if(keyboard_fd)
			while(finready(keyboard_fd))
		{
			i=fgetc(keyboard_fd)<<8;
			i+=fgetc(keyboard_fd);

			render_keybuf[render_keybuf_pos++]=i;
			printf("kb got %d\n", i);
		}

		render_keybuf[render_keybuf_pos]=0;

		memset(&mi, 0, sizeof(mi));
		if(mouse_fd)
			fread(&mi, 1, sizeof(mi), mouse_fd);
		render_mouse_pos[0]+=mi.dx;
		render_mouse_pos[1]+=mi.dy;
		render_mouse_b=mi.flags;

		if(render_mouse_pos[0]<=-320)render_mouse_pos[0]=-320+1;
		if(render_mouse_pos[1]<=-240)render_mouse_pos[1]=-240+1;
		if(render_mouse_pos[0]>=320)render_mouse_pos[0]=320-1;
		if(render_mouse_pos[1]>=240)render_mouse_pos[1]=240-1;

//		printf("mouse %d %d %d\n",
//			render_mouse_pos[0], render_mouse_pos[1],
//			render_mouse_b);

//		render_mouse_origin[0]=(render_mouse_pos[0]*gui_width)

		if(Render_PollKey(K_DEL))
		{
			gui_width=(gui_width*9)/10;
		}
		if(Render_PollKey(K_END))
		{
			gui_width=(gui_width*11)/10;
		}


		Gui_PollForCons();
		Gui_HandleCons();

		Scr_WriteOpcode(GFXOP2_BEGINDRAWING);
//		Scr_FillSquare(0, 0, 320, 240, 255, 255, 255, 255);

		Gui_DrawSurfaces();

		Scr_FillSquare(
			render_mouse_pos[0]+320, render_mouse_pos[1]+240,
			16, 16,
			(fc&1)?255:0, (fc&2)?255:0, (fc&4)?255:0, 255);

		Scr_WriteOpcode(GFXOP2_ENDDRAWING);

		fc++;
//		printf("frame end\n");
	}
}
