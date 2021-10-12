#include <general.h>
#include <bgfrender.h>

elem bgf_models;
extern bone_t *mod_bones;
extern piece_t *mod_pieces;
extern bgftexinfo_t *mod_textures;

extern piece_t *piece_self, *piece_parent;
extern bone_t *bone_self, *bone_parent;
extern bgftexinfo_t *texture_self, *texture_parent;

elem BGFLB_ApplyPiece(elem obj, elem rest);
elem BGFLB_MarkPiece(elem obj);

elem BGFLB_ApplyBone(elem obj, elem rest);
elem BGFLB_MarkBone(elem obj);

elem BGFLB_ApplyTexture(elem obj, elem rest);
elem BGFLB_MarkTexture(elem obj);

elem BGFLB_ApplyModel(elem obj, elem rest);
elem BGFLB_MarkModel(elem obj);

elem BGFLB_LoadModel(elem f);
bgfmodinfo_t *BGF_LoadModel(char *buf);

int BGFLB_Init()
{
	typexinfo *txi;

	txi=TypeX_GetInfo("bgf-piece");
	txi->apply=&BGFLB_ApplyPiece;
	txi->mark=&BGFLB_MarkPiece;

	txi=TypeX_GetInfo("bgf-bone");
	txi->apply=&BGFLB_ApplyBone;
	txi->mark=&BGFLB_MarkBone;

	txi=TypeX_GetInfo("bgf-texture");
	txi->apply=&BGFLB_ApplyTexture;
	txi->mark=&BGFLB_MarkTexture;

	txi=TypeX_GetInfo("bgf-model");
	txi->apply=&BGFLB_ApplyModel;
	txi->mark=&BGFLB_MarkModel;

	Interp_DefinePrimative("bgf-load", &BGFLB_LoadModel, 1);

	return(0);
}

elem BGFLB_ApplyPiece(elem obj, elem rest)
{
	piece_t *opar, *tmp;
	elem cur;

	if(ELEM_SYMBOLP(CAR(rest)))
	{
		opar=TypeX_Data(obj);
		tmp=mod_findpiece(opar->first, ELEM_TOSYMBOL(CAR(rest)));
		return(MMGC3_GetReference(tmp));
	}

	opar=piece_parent;
	piece_parent=piece_self;
	piece_self=TypeX_Data(obj);

	cur=rest;
	while(cur!=MISC_EOL)
	{
		piece_decode_opts (CAR(cur));
		cur=CDR(cur);
	}
	piece_self=piece_parent;
	piece_parent=opar;

	return(MISC_NULL);
}

elem BGFLB_ApplyBone(elem obj, elem rest)
{
	bone_t *opar, *tmp;
	elem cur;

	if(ELEM_SYMBOLP(CAR(rest)))
	{
		opar=TypeX_Data(obj);
		if(CAR(rest)==SYM("piece"))
			return(MMGC3_GetReference(opar->piece));

		tmp=mod_findbone(opar->first, ELEM_TOSYMBOL(CAR(rest)));
		return(MMGC3_GetReference(tmp));
	}

	opar=bone_parent;
	bone_parent=bone_self;
	bone_self=TypeX_Data(obj);

	cur=rest;
	while(cur!=MISC_EOL)
	{
		bone_decode_opts (CAR(cur));
		cur=CDR(cur);
	}
	bone_self=bone_parent;
	bone_parent=opar;

	return(MISC_NULL);
}

elem BGFLB_ApplyTexture(elem obj, elem rest)
{
	return(MISC_NULL);
}

elem BGFLB_ApplyModel(elem obj, elem rest)
{
	bgfmodinfo_t *opar;
	piece_t *p;
	bone_t *b;

	if(ELEM_SYMBOLP(CAR(rest)))
	{
		opar=TypeX_Data(obj);
		p=mod_findpiece(opar->pieces, ELEM_TOSYMBOL(CAR(rest)));
		if(p)return(MMGC3_GetReference(p));
		b=mod_findpiece(opar->bones, ELEM_TOSYMBOL(CAR(rest)));
		if(b)return(MMGC3_GetReference(b));
		return(MISC_NULL);
	}

	return(MISC_NULL);
}


elem BGFLB_MarkPiece(elem obj)
{
	piece_t *p;

	p=TypeX_Data(obj);
	MMGC3_TracePush(MMGC3_GetReference(p->next));
	MMGC3_TracePush(MMGC3_GetReference(p->first));
	MMGC3_TracePush(MMGC3_GetReference(p->skin));

	return(0);
}

elem BGFLB_MarkBone(elem obj)
{
	bone_t *p;

	p=TypeX_Data(obj);
	MMGC3_TracePush(MMGC3_GetReference(p->next));
	MMGC3_TracePush(MMGC3_GetReference(p->first));
	MMGC3_TracePush(MMGC3_GetReference(p->piece));

	return(0);
}

elem BGFLB_MarkTexture(elem obj)
{
	bgftexinfo_t *p;

	p=TypeX_Data(obj);
	MMGC3_TracePush(MMGC3_GetReference(p->next));
	MMGC3_TracePush(MMGC3_GetReference(p->first));

	return(0);
}

elem BGFLB_MarkModel(elem obj)
{
	bgfmodinfo_t *p;

	p=TypeX_Data(obj);
	MMGC3_TracePush(MMGC3_GetReference(p->bones));
	MMGC3_TracePush(MMGC3_GetReference(p->pieces));
	MMGC3_TracePush(MMGC3_GetReference(p->textures));

	return(0);
}

elem BGFLB_LoadModel(elem f)
{
	VFILE *fd;
	int i;
	bgfmodinfo_t *m;

	char *fbuf;

	fd=vffopen(ELEM_TOSTRING(f), "rb");

	vfseek(fd, 0, 2);
	i=vftell(fd);
	fbuf=kalloc(i+16);
	memset(fbuf, 0, i+16);
	vfseek(fd, 0, 0);
	vfread(fbuf, 1, i, fd);

	m=BGF_LoadModel(fbuf);
	kfree(fbuf);

	return(MMGC3_GetReference(m));
}

int BGF_Init()
{
	BGFLB_Init();

	MMGC3_AddCRoot(&mod_bones);
	MMGC3_AddCRoot(&mod_pieces);
	MMGC3_AddCRoot(&mod_textures);

	bgf_models=MISC_EOL;
	MMGC3_AddRoot(&bgf_models);

	return(0);
}

piece_t *BGF_NewPiece()
{
	piece_t *tmp;

	tmp=TypeX_Alloc("bgf-piece", sizeof(piece_t));
//	tmp=malloc(sizeof(piece_t));
//	memset(tmp, 0, sizeof(piece_t));
	return(tmp);
}

bone_t *BGF_NewBone()
{
	bone_t *tmp;

	tmp=TypeX_Alloc("bgf-bone", sizeof(bone_t));
	return(tmp);
}

bgftexinfo_t *BGF_NewTexture()
{
	bgftexinfo_t *tmp;

	tmp=TypeX_Alloc("bgf-texture", sizeof(bgftexinfo_t));
	return(tmp);
}

bgfmodinfo_t *BGF_NewModel()
{
	bgfmodinfo_t *tmp;

	tmp=TypeX_Alloc("bgf-model", sizeof(bgfmodinfo_t));
	return(tmp);
}

int BGF_LockModel(bgfmodinfo_t *mod)
{
	elem l;

	l=MMGC3_GetReference(mod);
	bgf_models=CONS(l, bgf_models);

	return(0);
}
