//#include <general.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>
#include <GL/GL.h>
//#include <render/keys.h>
#include <general.h>
#include <graphics/render.h>

//the coding of this is horrid...

//typedef float vec3[3];

int main_kill;

char *_argv[64];
int _argc;

HINSTANCE	global_hInstance;
int			global_nCmdShow;

unsigned char keybuf[32];


float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

typedef struct {
char name[16];
int first, next;

int type; //0=mesh, 1=cube, 2=cylinder, 3=sphere
vec3 min, max;
vec3 org, dir;
float trad, brad, h;

int skin;

//mesh data
int firstvert;
int numverts;

int firstpoly;
int numpolys;
}piece_t;

typedef struct {
char name[16];
float org[64*3];
float ang[64*3];
int piece;
int first, next;
}bone_t;

typedef struct {
char name[16];
int num;
int width, height;
}texinfo_t;

piece_t piece[256];
int pieces;

bone_t bone[256];
int bones;

texinfo_t texture[256];
int textures;

int cvec;
int sw, sh;

vec3 v_origin, v_angles;
int v_frame;

int mod_findpiece(char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed pieces
//	printf("find %s\n", name);
	for(i=0; i<pieces; i++)
	{
//		printf("p %s\n", piece[i].name);
		if(!strcmp(name, piece[i].name))return(i);
	}
//	printf("fail\n");
	return(-1);
}

int mod_findbone(int par, char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed bones

	if(par==-1)par=0;
	i=bone[par].first;

	for(i=0; i<bones; i++)
		if(!strcmp(name, bone[i].name))return(i);
//	while(i!=-1)
//	{
//		if(!strcmp(name, bone[i].name))return(i);
//		i=bone[i].next;
//	}
	return(-1);
}

int mod_findskin(char *name)
{
	int i;

	if(!*name)return(-1); //don't search for unnamed skins

	printf("find %s\n", name);

	for(i=0; i<textures; i++)
	{
		printf("s %s\n", texture[i].name);
		if(!strcmp(name, texture[i].name))return(i);
	}
	printf("fail\n");
	return(-1);
}

int bone_ref=-1;
int piece_ref=-1;

int mod_decode(elem obj)
{
	elem cur;
	int i, j, w, h;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("bgf2alias: non-list parsed top level\n");
	}

//	frames=0;


	if(CAR(obj) == SYM("cube"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=1;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;

		pieces++;
		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;
	}

	if(CAR(obj) == SYM("sphere"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=3;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;

		pieces++;

		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;
	}

	if(CAR(obj) == SYM("cylinder"))
	{
		if(CADR(obj) != MISC_NULL)
			strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
		piece[pieces].type=2;
		piece[pieces].first=-1;
		piece[pieces].next=-1;

		if(piece_ref != -1)
		{
			piece[pieces].next=piece[piece_ref].first;
			piece[piece_ref].first=pieces;
		}

		piece[pieces].trad=1;
		piece[pieces].brad=1;

		piece[pieces].dir[0]=0;
		piece[pieces].dir[1]=0;
		piece[pieces].dir[2]=1;
		pieces++;

		i=piece_ref;
		piece_ref=pieces-1;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		piece_ref=i;

	}

	if(CAR(obj) == SYM("skin"))
	{
		i=mod_findskin(ELEM_TOSYMBOL(CADR(obj)));
		if(i==-1)
		{
			j=Tex_LoadFile(ELEM_TOSTRING(CADDR(obj)), &w, &h);
			i=textures++;
			strcpy(texture[i].name, ELEM_TOSYMBOL(CADR(obj)));
			texture[i].num=j;
			texture[i].width=w;
			texture[i].height=h;
		}
		if(piece_ref != -1)
		{
			piece[piece_ref].skin=i;
		}
	}
	if(CAR(obj) == SYM("min"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].min[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].min[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].min[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("max"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].max[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].max[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].max[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("dir"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].dir[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].dir[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].dir[2]=TOFLOAT(CADDDR(obj));
		}
	}
	if(CAR(obj) == SYM("radius-top"))
	{
		piece[piece_ref].trad=TOFLOAT(CADR(obj));		
	}
	if(CAR(obj) == SYM("radius-bottom"))
	{
		piece[piece_ref].brad=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("radius"))
	{
		piece[piece_ref].trad=TOFLOAT(CADR(obj));		
		piece[piece_ref].brad=TOFLOAT(CADR(obj));		
	}
	if(CAR(obj) == SYM("height"))
	{
		piece[piece_ref].h=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("org"))
	{
		if(piece_ref != -1)
		{
			piece[piece_ref].org[0]=TOFLOAT(CADR(obj));
			piece[piece_ref].org[1]=TOFLOAT(CADDR(obj));
			piece[piece_ref].org[2]=TOFLOAT(CADDDR(obj));
		}
		if(bone_ref != -1)
		{
			bone[bone_ref].org[frames*3+0]=TOFLOAT(CADR(obj));
			bone[bone_ref].org[frames*3+1]=TOFLOAT(CADDR(obj));
			bone[bone_ref].org[frames*3+2]=TOFLOAT(CADDDR(obj));
			if(!frames)for(i=1; i<64; i++)
			{
				bone[bone_ref].org[i*3+0]=bone[bone_ref].org[0];
				bone[bone_ref].org[i*3+1]=bone[bone_ref].org[1];
				bone[bone_ref].org[i*3+2]=bone[bone_ref].org[2];
			}
		}
	}

	if(CAR(obj) == SYM("angle"))
	{
		bone[bone_ref].ang[frames*3+0]=TOFLOAT(CADR(obj));
		bone[bone_ref].ang[frames*3+1]=TOFLOAT(CADDR(obj));
		bone[bone_ref].ang[frames*3+2]=TOFLOAT(CADDDR(obj));

		if(!frames)for(i=1; i<64; i++)
		{
			bone[bone_ref].ang[i*3+0]=bone[bone_ref].ang[0];
			bone[bone_ref].ang[i*3+1]=bone[bone_ref].ang[1];
			bone[bone_ref].ang[i*3+2]=bone[bone_ref].ang[2];
		}
	}

	if(CAR(obj) == SYM("bone"))
	{
		j=-1;

//		i=0;
//		if(bone_ref != -1)i=bone_ref;

		if(CADR(obj) != MISC_NULL)
			j=mod_findbone(0, ELEM_TOSYMBOL(CADR(obj)));

		if(j == -1)
		{
			if(CADR(obj) != MISC_NULL)
				strcpy(bone[bones].name, ELEM_TOSYMBOL(CADR(obj)));
			bone[bones].first=-1;
			bone[bones].next=-1;
			bone[bones].piece=-1;
			bones++;
			j=bones-1;

			printf("bone %d %s\n", j, bone[j].name);

			if(bone_ref != -1)
			{
				bone[j].next=bone[bone_ref].first;
				bone[bone_ref].first=bones-1;
			}
		}

		i=bone_ref;
		bone_ref=j;

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		bone_ref=i;
	}

	if(CAR(obj) == SYM("piece"))
	{
		printf("piece\n");
		if(CDDR(obj) != MISC_EOL)
		{
			if(CADR(obj) != MISC_NULL)
				strcpy(piece[pieces].name, ELEM_TOSYMBOL(CADR(obj)));
			piece[pieces].first=-1;
			piece[pieces].next=-1;

			printf("piece def %s\n", piece[pieces].name);

			if(piece_ref != -1)
			{
				piece[pieces].next=piece[piece_ref].first;
				piece[piece_ref].first=pieces;
			}

			piece[pieces].firstvert=cvec;
			piece[pieces].firstpoly=polys;

			j=pieces;
			pieces++;

			i=piece_ref;
			piece_ref = j;

			cur=CDDR(obj);
			while(cur!=MISC_EOL)
			{
				mod_decode (CAR(cur));
				cur=CDR(cur);
			}
			piece_ref=i;

			piece[j].numverts=cvec-piece[j].firstvert;
			piece[j].numpolys=polys-piece[j].firstpoly;
		}
		if(bone_ref != -1)
		{
			printf("piece bone ref %d\n", bone_ref);
			bone[bone_ref].piece=
				mod_findpiece(ELEM_TOSYMBOL(CADR(obj)));
		}
	}

	if(CAR(obj) == SYM("frameset"))
	{
		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("frame"))
	{
		strcpy(framenames[frames], ELEM_TOSYMBOL(CADR(obj)));
//		printf("%s\n", framenames[frames-1]);

		if(!vecs)vecs=LENGTH(CDDR(obj));

		cur=CDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
		frames++;
	}
	if(CAR(obj) == SYM("vertices"))
	{
		vecs=TOINT(LENGTH(CDR(obj)));
//		sprintf(framenames[frames++], "frame%d", frames);

		cur=CDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}
	}
	if(CAR(obj) == SYM("vertex"))
	{
		vecbuf[(cvec*6)+0]=TOFLOAT(CADR(obj));
		vecbuf[(cvec*6)+1]=TOFLOAT(CADDR(obj));
		vecbuf[(cvec*6)+2]=TOFLOAT(CADDDR(obj));

//		vecbuf[(cvec*6)+3]=atof(tokbuf[5]);
//		vecbuf[(cvec*6)+4]=atof(tokbuf[6]);
//		vecbuf[(cvec*6)+5]=atof(tokbuf[7]);

		cur=CDDDDR(obj);
		while(cur!=MISC_EOL)
		{
			mod_decode (CAR(cur));
			cur=CDR(cur);
		}

		cvec++;
	}
	if(CAR(obj) == SYM("st"))
	{
		vecbuf[(cvec*6)+3]=TOFLOAT(CADR(obj));
		vecbuf[(cvec*6)+4]=TOFLOAT(CADDR(obj));
	}
	if(CAR(obj) == SYM("seam"))
	{
		vecbuf[(cvec*6)+5]=TOFLOAT(CADR(obj));
	}

	if(CAR(obj) == SYM("polyidx"))
	{
		polybuf[(polys*4)+0]=TOINT(CAR(CADR(obj)));
		polybuf[(polys*4)+1]=TOINT(CADR(CADR(obj)));
		polybuf[(polys*4)+2]=TOINT(CADDR(CADR(obj)));

//		polybuf[(polys*4)+0]=atoi(tokbuf[2]);
//		polybuf[(polys*4)+1]=atoi(tokbuf[3]);
//		polybuf[(polys*4)+2]=atoi(tokbuf[4]);
//		polybuf[(polys*4)+3]=atoi(tokbuf[6]);
		polys++;
	}
	if(CAR(obj) == SYM("key"))
	{
		if(CADR(obj) == SYM("skinwidth"))
		{
			sw=TOINT(CADDR(obj));
		}
		if(CADR(obj) == SYM("skinheight"))
		{
			sh=TOINT(CADDR(obj));
		}
	}
}
