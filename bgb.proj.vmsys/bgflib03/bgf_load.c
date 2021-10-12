#include <string.h>

#include "bgfrender.h"

//typedef float vec3[3];

int main_kill;

char *_argv[64];
int _argc;

HINSTANCE	global_hInstance;
int			global_nCmdShow;

float *vecbuf;
int vecs, frames, polys;
char framenames[256][16];
int *polybuf;

//piece_t piece[256];
//int pieces;

//bone_t bone[256];
//int bones;

//bgftexinfo_t texture[256];
//int textures;

int cvec;
int sw, sh;

vec3 v_origin, v_angles;
int v_frame;

bone_t *mod_bones;
piece_t *mod_pieces;
bgftexinfo_t *mod_textures;

piece_t *mod_findpiece(piece_t *par, char *name)
{
	int i;
	piece_t *cur;

	if(!*name)return(NULL); //don't search for unnamed pieces

	if(!par)par=mod_pieces;

#if 0
//	printf("find %s\n", name);
	for(i=0; i<pieces; i++)
	{
//		printf("p %s\n", piece[i].name);
		if(!strcmp(name, piece[i].name))
			return(&piece[i]);
	}
#endif

	cur=par;
	while(cur)
	{
		if(!strcmp(name, cur->name))
			return(cur);
		cur=cur->next;
	}

//	printf("fail\n");
	return(NULL);
}

bone_t *mod_findbone(bone_t *par, char *name)
{
	int i;
	bone_t *cur, *t;

	if(!*name)return(NULL); //don't search for unnamed bones

	cur=par;
	if(!cur)cur=mod_bones;

	while(cur)
	{
		if(!strcmp(name, cur->name))return(cur);
		if(cur->first)
		{
			t=mod_findbone(cur->first, name);
			if(t)return(t);
		}
		cur=cur->next;
	}

#if 0
//	if(!par)par=&bone[0];
//	i=par->first;

	for(i=0; i<bones; i++)
		if(!strcmp(name, bone[i].name))
		return(&bone[i]);
//	while(i!=-1)
//	{
//		if(!strcmp(name, bone[i].name))return(i);
//		i=bone[i].next;
//	}
#endif

	return(NULL);
}

bgftexinfo_t *mod_findskin(char *name)
{
	int i;
	bgftexinfo_t *cur;

	if(!*name)return(-1); //don't search for unnamed skins

	cur=mod_textures;
	while(cur)
	{
		if(!strcmp(name, cur->name))
			return(cur);
		cur=cur->next;
	}
	return(NULL);

#if 0
//	printf("find %s\n", name);

	for(i=0; i<textures; i++)
	{
//		printf("s %s\n", texture[i].name);
		if(!strcmp(name, texture[i].name))return(i);
	}
//	printf("fail\n");
	return(-1);
#endif
}

piece_t *piece_self, *piece_parent;
bone_t *bone_self, *bone_parent;
int bone_frame, bone_isframe;
bgftexinfo_t *texture_self, *texture_parent;

bone_t *bone_decode(elem obj);
int mod_decode_base(elem obj);
int texture_decode(elem obj);

int piece_decode_opts(elem obj)
{
	float tmat[16];
	vec4 v;
	int w, h;
	byte *b;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("piece_decode_opts: non-list parsed where list expected\n");
	}

	if(CAR(obj) == SYM("name"))
	{
		strcpy(piece_self->name, ELEM_TOSYMBOL(CADR(obj)));		
	}
	if(CAR(obj) == SYM("texture"))
	{
		texture_decode(obj);
	}

	if(CAR(obj) == SYM("height-map"))
	{
		b=Tex_LoadFileRaw(ELEM_TOSTRING(CADR(obj)), &w, &h);
		piece_self->hmap=b;
		piece_self->hmapwidth=w;
		piece_self->hmapheight=h;
		piece_self->hmapbias=1;
		piece_self->hmapscale=piece_self->trad/256;
		if(CDDR(obj) != MISC_EOL)
		{
			b=Tex_LoadFileRaw(ELEM_TOSTRING(CADDR(obj)), &w, &h);
			piece_self->hmap2=b;
		}
	}
	if(CAR(obj) == SYM("height-range"))
	{
		piece_self->hmapscale=TOFLOAT(CADR(obj))/256;		
	}
	if(CAR(obj) == SYM("height-bias"))
	{
		piece_self->hmapbias=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("min"))
	{
		piece_self->min[0]=TOFLOAT(CADR(obj));
		piece_self->min[1]=TOFLOAT(CADDR(obj));
		piece_self->min[2]=TOFLOAT(CADDDR(obj));
	}
	if(CAR(obj) == SYM("max"))
	{
		piece_self->max[0]=TOFLOAT(CADR(obj));
		piece_self->max[1]=TOFLOAT(CADDR(obj));
		piece_self->max[2]=TOFLOAT(CADDDR(obj));
	}
	if(CAR(obj) == SYM("dir"))
	{
		piece_self->dir[0]=TOFLOAT(CADR(obj));
		piece_self->dir[1]=TOFLOAT(CADDR(obj));
		piece_self->dir[2]=TOFLOAT(CADDDR(obj));
	}
	if(CAR(obj) == SYM("radius-top"))
	{
		piece_self->trad=TOFLOAT(CADR(obj));		
	}
	if(CAR(obj) == SYM("radius-bottom"))
	{
		piece_self->brad=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("radius"))
	{
		piece_self->trad=TOFLOAT(CADR(obj));
		piece_self->brad=TOFLOAT(CADR(obj));
//		printf("rad %lf\n", TOFLOAT(CADR(obj)));
	}
	if(CAR(obj) == SYM("height"))
	{
		piece_self->h=TOFLOAT(CADR(obj));		
	}

	if(CAR(obj) == SYM("origin"))
	{
		piece_self->org[0]=TOFLOAT(CADR(obj));
		piece_self->org[1]=TOFLOAT(CADDR(obj));
		piece_self->org[2]=TOFLOAT(CADDDR(obj));
	}

	if(CAR(obj) == SYM("scale"))
	{
		v[0]=TOFLOAT(CADR(obj));
		v[1]=TOFLOAT(CADDR(obj));
		v[2]=TOFLOAT(CADDDR(obj));
		v[3]=1;
		MatN_MatMultVectorf(piece_self->transform, v, tmat, 4);
		MatN_Copyf(tmat, piece_self->transform, 4, 4);
	}

	if(CAR(obj) == SYM("rotate"))
	{
		v[0]=TOFLOAT(CADR(obj));
		v[1]=TOFLOAT(CADDR(obj));
		v[2]=TOFLOAT(CADDDR(obj));
		v[3]=0;
		Vec16_RotateMatrixf(piece_self->transform, v, tmat);
		MatN_Copyf(tmat, piece_self->transform, 4, 4);
	}

	if(CAR(obj) == SYM("translate"))
	{
		v[0]=TOFLOAT(CADR(obj));
		v[1]=TOFLOAT(CADDR(obj));
		v[2]=TOFLOAT(CADDDR(obj));
		v[3]=0;
		Vec16_TranslateMatrixf(piece_self->transform, v, tmat);
		MatN_Copyf(tmat, piece_self->transform, 4, 4);
	}

	return(0);
}

piece_t *piece_decode(elem obj)
{
	int i;

	piece_t *tmp, *opar;
	elem cur;

//	tmp=&piece[pieces++];
	tmp=BGF_NewPiece();

	strcpy(tmp->name, "");

	opar=piece_parent;
	piece_parent=piece_self;
	piece_self=tmp;
	piece_self->first=NULL;
	piece_self->next=NULL;

	piece_self->skin=NULL;
	piece_self->trad=1;
	piece_self->brad=1;

	piece_self->dir[0]=0;
	piece_self->dir[1]=0;
	piece_self->dir[2]=1;

	for(i=0; i<16; i++)
		piece_self->transform[i]=0;
	for(i=0; i<4; i++)
		piece_self->transform[i*4+i]=1;

	piece_self->type=PIECE_NONE;

	if(piece_parent)
	{
		piece_self->next=piece_parent->first;
		piece_parent->first=piece_self;
	}else
	{
		piece_self->next=mod_pieces;
		mod_pieces=piece_self;
	}

	piece_self->firstvert=cvec;
	piece_self->firstpoly=polys;

	cur=CDR(obj);
	while(cur!=MISC_EOL)
	{
		piece_decode_opts (CAR(cur));
		cur=CDR(cur);
	}

	piece_self->numverts=cvec-piece_self->firstvert;
	piece_self->numpolys=polys-piece_self->firstpoly;

	piece_self=piece_parent;
	piece_parent=opar;

	return(tmp);
}

piece_t *union_decode(elem obj)
{
	piece_t *tmp, *opar;
	elem cur;
	int i;

//	tmp=&piece[pieces++];
	tmp=BGF_NewPiece();

	opar=piece_parent;
	piece_parent=piece_self;
	piece_self=tmp;
	piece_self->first=NULL;
	piece_self->next=NULL;
	piece_self->type=PIECE_UNION;
	piece_self->skin=NULL;

	for(i=0; i<16; i++)
		piece_self->transform[i]=0;
	for(i=0; i<4; i++)
		piece_self->transform[i*4+i]=1;

	if(piece_parent)
	{
		piece_self->next=piece_parent->first;
		piece_parent->first=piece_self;
	}else
	{
		piece_self->next=mod_pieces;
		mod_pieces=piece_self;
	}

	cur=CDR(obj);
	while(cur!=MISC_EOL)
	{
		mod_decode_base (CAR(cur));
		cur=CDR(cur);
	}
	piece_self=piece_parent;
	piece_parent=opar;

	return(tmp);
}

int bone_decode_opts(elem obj)
{
	int i;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("bone_decode_opts: non-list parsed where list expected\n");
	}

	if(CAR(obj) == SYM("name"))
	{
		strcpy(bone_self->name, ELEM_TOSYMBOL(CADR(obj)));
//		printf("(name %s)", bone_self->name);
	}
	if(CAR(obj) == SYM("piece"))
	{
		bone_self->piece=mod_findpiece(NULL, ELEM_TOSYMBOL(CADR(obj)));		
	}

	if(CAR(obj) == SYM("origin"))
	{
		bone_self->org[bone_frame*3+0]=TOFLOAT(CADR(obj));
		bone_self->org[bone_frame*3+1]=TOFLOAT(CADDR(obj));
		bone_self->org[bone_frame*3+2]=TOFLOAT(CADDDR(obj));

		if(!bone_isframe)
			for(i=1; i<64; i++)
		{
			bone_self->org[i*3+0]=bone_self->org[0];
			bone_self->org[i*3+1]=bone_self->org[1];
			bone_self->org[i*3+2]=bone_self->org[2];
		}
	}

	if(CAR(obj) == SYM("angles"))
	{
		bone_self->ang[bone_frame*3+0]=TOFLOAT(CADR(obj));
		bone_self->ang[bone_frame*3+1]=TOFLOAT(CADDR(obj));
		bone_self->ang[bone_frame*3+2]=TOFLOAT(CADDDR(obj));

		if(!bone_isframe)
			for(i=1; i<64; i++)
		{
			bone_self->ang[i*3+0]=bone_self->ang[0];
			bone_self->ang[i*3+1]=bone_self->ang[1];
			bone_self->ang[i*3+2]=bone_self->ang[2];
		}
	}

	if(CAR(obj) == SYM("bone"))
	{
		bone_decode(obj);
	}

	return(0);
}

bone_t *bone_decode(elem obj)
{
	elem cur;
	bone_t *opar, *tmp;

//	printf("(bone ");

	if(ELEM_SYMBOLP(CADR(obj)))
	{
		opar=bone_parent;
		bone_parent=bone_self;
		bone_self=mod_findbone(NULL, ELEM_TOSYMBOL(CADR(obj)));
		if(!bone_self)
			sa_fatal("bone_decode: failed find '%s'\n",
			ELEM_TOSYMBOL(CADR(obj)));
		cur=CDDR(obj);

//		printf("(bone %s:%d", bone_self->name, bone_frame);
	}else
	{
		opar=bone_parent;
		bone_parent=bone_self;
//		bone_self=&bone[bones++];
		bone_self=BGF_NewBone();
		bone_self->first=NULL;
		bone_self->next=NULL;
		bone_self->piece=NULL;

		if(bone_parent)
		{
			bone_self->next=bone_parent->first;
			bone_parent->first=bone_self;
		}else
		{
			bone_self->next=mod_bones;
			mod_bones=bone_self;
		}
		cur=CDR(obj);
	}

	while(cur!=MISC_EOL)
	{
		bone_decode_opts (CAR(cur));
		cur=CDR(cur);
	}

	tmp=bone_self;
	bone_self=bone_parent;
	bone_parent=opar;

//	if(bone_isframe)printf(")");

	return(tmp);
}

int frame_decode_opts(elem obj)
{
	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("frame_decode_opts: non-list parsed where list expected\n");
	}

	if(CAR(obj) == SYM("name"))
	{
		strcpy(framenames[bone_frame], ELEM_TOSYMBOL(CADR(obj)));		
	}
	if(CAR(obj) == SYM("bone"))
	{
		bone_decode(obj);
	}

	return(0);
}

int frame_decode(elem obj)
{
	elem cur;

	bone_frame=frames++;
	bone_isframe=1;

	cur=CDR(obj);
	while(cur!=MISC_EOL)
	{
		frame_decode_opts (CAR(cur));
		cur=CDR(cur);
	}
	bone_frame=0;
	bone_isframe=0;

	return(0);
}

int texture_decode_opts(elem obj)
{
	int i, w, h;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("bone_decode_opts: non-list parsed where list expected\n");
	}

	if(CAR(obj) == SYM("name"))
	{
		strcpy(texture_self->name, ELEM_TOSYMBOL(CADR(obj)));
	}

	if(CAR(obj) == SYM("image"))
	{
		i=Tex_LoadFile(ELEM_TOSTRING(CADR(obj)), &w, &h);
		texture_self->num=i;
		texture_self->width=w;
		texture_self->height=h;
	}

	if(CAR(obj) == SYM("origin"))
	{
		texture_self->org[0]=TOFLOAT(CADR(obj));
		texture_self->org[1]=TOFLOAT(CADDR(obj));
		texture_self->org[2]=TOFLOAT(CADDDR(obj));
	}

	if(CAR(obj) == SYM("normal"))
	{
		texture_self->norm[0]=TOFLOAT(CADR(obj));
		texture_self->norm[1]=TOFLOAT(CADDR(obj));
		texture_self->norm[2]=TOFLOAT(CADDDR(obj));
	}

	if(CAR(obj) == SYM("up"))
	{
		texture_self->up[0]=TOFLOAT(CADR(obj));
		texture_self->up[1]=TOFLOAT(CADDR(obj));
		texture_self->up[2]=TOFLOAT(CADDDR(obj));
	}

	if(CAR(obj) == SYM("right"))
	{
		texture_self->right[0]=TOFLOAT(CADR(obj));
		texture_self->right[1]=TOFLOAT(CADDR(obj));
		texture_self->right[2]=TOFLOAT(CADDDR(obj));
	}

	if(CAR(obj) == SYM("scale-st"))
	{
		texture_self->scale_s=TOFLOAT(CADR(obj));
		texture_self->scale_t=TOFLOAT(CADDR(obj));
	}

	if(CAR(obj) == SYM("texture"))
	{
		texture_decode(obj);
	}

	return(0);
}

int vecz(vec3 v);

int texture_decode(elem obj)
{
	elem cur;
	float *vi, *vj, *vk;
	int i;
	bgftexinfo_t *otex, *t;

	otex=texture_parent;
	texture_parent=texture_self;
//	texture_self=&texture[textures++];
	texture_self=BGF_NewTexture();

	if(ELEM_SYMBOLP(CADR(obj)))
	{
		t=mod_findskin(ELEM_TOSYMBOL(CADR(obj)));

		if(!t)
			sa_fatal("texture %s not found\n",
			ELEM_TOSYMBOL(CADR(obj)));

		memcpy(texture_self, t, sizeof(bgftexinfo_t));

//		texture_self->first=NULL;
		texture_self->next=NULL;
		strcpy(texture_self->name, "");

		cur=CDDR(obj);
	}else
	{
		memset(texture_self, 0, sizeof(bgftexinfo_t));
		texture_self->scale_s=1;
		texture_self->scale_t=1;
		texture_self->num=-1;
		cur=CDR(obj);
	}

//	printf("(texture ");

	while(cur!=MISC_EOL)
	{
		texture_decode_opts (CAR(cur));
		cur=CDR(cur);
	}

	vi=texture_self->right;
	vj=texture_self->up;
	vk=texture_self->norm;

	if(!vecz(vj) && !vecz(vk) && vecz(vi))
		cross(vj, vk, vi);
	if(!vecz(vk) && !vecz(vi) && vecz(vj))
		cross(vk, vi, vj);
	if(!vecz(vi) && !vecz(vj) && vecz(vk))
		cross(vi, vj, vk);

//	printf("(num %d))\n", texture_self->num);

	if(piece_self)
	{
		piece_self->skin=texture_self;
	}

	if(texture_parent)
	{
		texture_self->next=texture_parent->first;
		texture_parent->first=texture_self;
	}else if(texture_self->name[0])
	{
		texture_self->next=mod_textures;
		mod_textures=texture_self;
	}

	texture_self=texture_parent;
	texture_parent=otex;

	return(0);
}

int mod_decode_base(elem obj)
{
	piece_t *pcur;

	if(!ELEM_CONSP(obj))
	{
		sa_fatal ("mod_decode_base: non-list parsed where list expected\n");
	}

	if(CAR(obj) == SYM("union"))
	{
		pcur=union_decode(obj);
	}

	if(CAR(obj) == SYM("mesh"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_MESH;
	}
	if(CAR(obj) == SYM("cube"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_CUBE;
	}
	if(CAR(obj) == SYM("cylinder"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_CYLINDER;
	}
	if(CAR(obj) == SYM("sphere"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_SPHERE;
	}
	if(CAR(obj) == SYM("disk"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_DISK;
	}
	if(CAR(obj) == SYM("diplane"))
	{
		pcur=piece_decode(obj);
		pcur->type=PIECE_DIPLANE;
	}

	if(CAR(obj) == SYM("bone"))
	{
		bone_decode(obj);
	}

	if(CAR(obj) == SYM("frame"))
	{
		frame_decode(obj);
	}

	if(CAR(obj) == SYM("texture"))
	{
		texture_decode(obj);
	}

	//union related
	if(piece_self)
	{
//		if(CAR(obj) == SYM("name"))
//		{
//			strcpy(piece_self->name, ELEM_TOSYMBOL(CADR(obj)));		
//		}
		piece_decode_opts(obj);
	}

	return(0);
}

int mod_decode(elem obj)
{
	return(mod_decode_base(obj));
}

bgfmodinfo_t *BGF_LoadModel(char *buf)
{
	char *fcur, *s;
	bgfmodinfo_t *inf;
	elem obj;

	mod_bones=NULL;
	mod_pieces=NULL;
	mod_textures=NULL;

	fcur=buf;
	while(*fcur)
	{
		s=fcur;
		obj=ScmParse_Line(&fcur, 0);
		fcur=ScmParse_EatWhite(fcur);
		if(obj==MISC_UNDEFINED)break;

		mod_decode (obj);
	}

//	inf=kalloc(sizeof(bgfmodinfo_t));
	inf=BGF_NewModel();
	inf->bones=mod_bones;
	inf->pieces=mod_pieces;
	inf->textures=mod_textures;

	return(inf);
}

bgfmodinfo_t *Bgf_LoadModel(char *buf)
{
	return(BGF_LoadModel(buf));
}
