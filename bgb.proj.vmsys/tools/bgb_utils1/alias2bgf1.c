#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float vec3_t[3];
typedef unsigned char byte;

#define ALIAS_VERSION	6

#define ALIAS_ONSEAM				0x0020

// must match definition in spritegn.h
#ifndef SYNCTYPE_T
#define SYNCTYPE_T
typedef enum {ST_SYNC=0, ST_RAND } synctype_t;
#endif

typedef enum { ALIAS_SINGLE=0, ALIAS_GROUP } aliasframetype_t;

typedef enum { ALIAS_SKIN_SINGLE=0, ALIAS_SKIN_GROUP } aliasskintype_t;

typedef struct {
	int			ident;
	int			version;
	vec3_t		scale;
	vec3_t		scale_origin;
	float		boundingradius;
	vec3_t		eyeposition;
	int			numskins;
	int			skinwidth;
	int			skinheight;
	int			numverts;
	int			numtris;
	int			numframes;
	synctype_t	synctype;
	int			flags;
	float		size;
} mdl_t;

// TODO: could be shorts

typedef struct {
	int		onseam;
	int		s;
	int		t;
} stvert_t;

typedef struct dtriangle_s {
	int					facesfront;
	int					vertindex[3];
} dtriangle_t;

#define DT_FACES_FRONT				0x0010

// This mirrors trivert_t in trilib.h, is present so Quake knows how to
// load this data

typedef struct {
	byte	v[3];
	byte	lightnormalindex;
} trivertx_t;

typedef struct {
	trivertx_t	bboxmin;	// lightnormal isn't used
	trivertx_t	bboxmax;	// lightnormal isn't used
	char		name[16];	// frame name from grabbing
} daliasframe_t;

typedef struct {
	int			numframes;
	trivertx_t	bboxmin;	// lightnormal isn't used
	trivertx_t	bboxmax;	// lightnormal isn't used
} daliasgroup_t;

typedef struct {
	int			numskins;
} daliasskingroup_t;

typedef struct {
	float	interval;
} daliasinterval_t;

typedef struct {
	float	interval;
} daliasskininterval_t;

typedef struct {
	aliasframetype_t	type;
} daliasframetype_t;

typedef struct {
	aliasskintype_t	type;
} daliasskintype_t;

#define IDPOLYHEADER	(('O'<<24)+('P'<<16)+('D'<<8)+'I')
														// little-endian "IDPO"
typedef struct
{
	int					firstpose;
	int					numposes;
	float				interval;
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int					frame;
	char				name[16];
} maliasframedesc_t;

typedef struct
{
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int					frame;
} maliasgroupframedesc_t;

typedef struct
{
	int						numframes;
	int						intervals;
	maliasgroupframedesc_t	frames[1];
} maliasgroup_t;

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct mtriangle_s {
	int					facesfront;
	int					vertindex[3];
} mtriangle_t;


#define	MAX_SKINS	32
typedef struct {
	int			ident;
	int			version;
	vec3_t		scale;
	vec3_t		scale_origin;
	float		boundingradius;
	vec3_t		eyeposition;
	int			numskins;
	int			skinwidth;
	int			skinheight;
	int			numverts;
	int			numtris;
	int			numframes;
	synctype_t	synctype;
	int			flags;
	float		size;

	int					numposes;
	int					poseverts;
	int					posedata;	// numposes*poseverts trivert_t
	int					commands;	// gl command list with embedded s/t
	int					gl_texturenum[MAX_SKINS][4];
	int					texels[MAX_SKINS];	// only for player skins
	maliasframedesc_t	frames[1];	// variable sized
} aliashdr_t;

#define	MAXALIASVERTS	1024
#define	MAXALIASFRAMES	256
#define	MAXALIASTRIS	2048
extern	aliashdr_t	*pheader;
extern	stvert_t	stverts[MAXALIASVERTS];
extern	mtriangle_t	triangles[MAXALIASTRIS];
extern	trivertx_t	*poseverts[MAXALIASFRAMES];


aliashdr_t	*pheader;

stvert_t	stverts[MAXALIASVERTS];
mtriangle_t	triangles[MAXALIASTRIS];

// a pose is a single set of vertexes.  a frame may be
// an animating sequence of poses
trivertx_t	*poseverts[MAXALIASFRAMES];
int			posenum;

long LittleLong(long v)
{
	return(v);
}

float LittleFloat(float v)
{
	return(v);
}

/*
=================
Mod_LoadAliasFrame
=================
*/
void * Mod_LoadAliasFrame (void * pin, maliasframedesc_t *frame)
{
	trivertx_t		*pframe, *pinframe;
	int				i, j;
	daliasframe_t	*pdaliasframe;
	
	pdaliasframe = (daliasframe_t *)pin;

	strcpy (frame->name, pdaliasframe->name);
	frame->firstpose = posenum;
	frame->numposes = 1;

	for (i=0 ; i<3 ; i++)
	{
	// these are byte values, so we don't have to worry about
	// endianness
		frame->bboxmin.v[i] = pdaliasframe->bboxmin.v[i];
		frame->bboxmin.v[i] = pdaliasframe->bboxmax.v[i];
	}

	pinframe = (trivertx_t *)(pdaliasframe + 1);

	poseverts[posenum] = pinframe;
	posenum++;

	pinframe += pheader->numverts;

	return (void *)pinframe;
}


/*
=================
Mod_LoadAliasGroup
=================
*/
void *Mod_LoadAliasGroup (void * pin,  maliasframedesc_t *frame)
{
	daliasgroup_t		*pingroup;
	int					i, numframes;
	daliasinterval_t	*pin_intervals;
	void				*ptemp;
	
	pingroup = (daliasgroup_t *)pin;

	numframes = LittleLong (pingroup->numframes);

	frame->firstpose = posenum;
	frame->numposes = numframes;

	for (i=0 ; i<3 ; i++)
	{
	// these are byte values, so we don't have to worry about endianness
		frame->bboxmin.v[i] = pingroup->bboxmin.v[i];
		frame->bboxmin.v[i] = pingroup->bboxmax.v[i];
	}

	pin_intervals = (daliasinterval_t *)(pingroup + 1);

	frame->interval = LittleFloat (pin_intervals->interval);

	pin_intervals += numframes;

	ptemp = (void *)pin_intervals;

	for (i=0 ; i<numframes ; i++)
	{
		poseverts[posenum] = (trivertx_t *)((daliasframe_t *)ptemp + 1);
		posenum++;

		ptemp = (trivertx_t *)((daliasframe_t *)ptemp + 1) + pheader->numverts;
	}

	return ptemp;
}

/*
===============
Mod_LoadAllSkins
===============
*/
void *Mod_LoadAllSkins (int numskins, daliasskintype_t *pskintype)
{
	int		i, j, k;
	char	name[32];
	int		s;
	byte	*copy;
	byte	*skin;
	byte	*texels;
	daliasskingroup_t		*pinskingroup;
	int		groupskins;
	daliasskininterval_t	*pinskinintervals;
	
	skin = (byte *)(pskintype + 1);

//	if (numskins < 1 || numskins > MAX_SKINS)
//		Sys_Error ("Mod_LoadAliasModel: Invalid # of skins: %d\n", numskins);

	s = pheader->skinwidth * pheader->skinheight;

	for (i=0 ; i<numskins ; i++)
	{
		if (pskintype->type == ALIAS_SKIN_SINGLE) {
//			Mod_FloodFillSkin( skin, pheader->skinwidth, pheader->skinheight );

			// save 8 bit texels for the player model to remap
	//		if (!strcmp(loadmodel->name,"progs/player.mdl")) {
//				texels = Hunk_AllocName(s, loadname);
				texels = malloc(s);
				pheader->texels[i] = texels - (byte *)pheader;
				memcpy (texels, (byte *)(pskintype + 1), s);
	//		}
//			sprintf (name, "%s_%i", loadmodel->name, i);
//			pheader->gl_texturenum[i][0] =
//			pheader->gl_texturenum[i][1] =
//			pheader->gl_texturenum[i][2] =
//			pheader->gl_texturenum[i][3] =
//				GL_LoadTexture (name, pheader->skinwidth, 
//				pheader->skinheight, (byte *)(pskintype + 1), true, false);
			pskintype = (daliasskintype_t *)((byte *)(pskintype+1) + s);
		} else {
			// animating skin group.  yuck.
			pskintype++;
			pinskingroup = (daliasskingroup_t *)pskintype;
			groupskins = LittleLong (pinskingroup->numskins);
			pinskinintervals = (daliasskininterval_t *)(pinskingroup + 1);

			pskintype = (void *)(pinskinintervals + groupskins);

			for (j=0 ; j<groupskins ; j++)
			{
//					Mod_FloodFillSkin( skin, pheader->skinwidth, pheader->skinheight );
					if (j == 0) {
//						texels = Hunk_AllocName(s, loadname);
						texels = malloc(s);
						pheader->texels[i] = texels - (byte *)pheader;
						memcpy (texels, (byte *)(pskintype), s);
					}
//					sprintf (name, "%s_%i_%i", loadmodel->name, i,j);
//					pheader->gl_texturenum[i][j&3] = 
//						GL_LoadTexture (name, pheader->skinwidth, 
//						pheader->skinheight, (byte *)(pskintype), 1, 0);
					pskintype = (daliasskintype_t *)((byte *)(pskintype) + s);
			}
			k = j;
			for (/* */; j < 4; j++)
				pheader->gl_texturenum[i][j&3] = 
				pheader->gl_texturenum[i][j - k]; 
		}
	}

	return (void *)pskintype;
}

//=========================================================================

/*
=================
Mod_LoadAliasModel
=================
*/
void Mod_LoadAliasModel (void *buffer)
{
	int					i, j;
	mdl_t				*pinmodel;
	stvert_t			*pinstverts;
	dtriangle_t			*pintriangles;
	int					version, numframes, numskins;
	int					size;
	daliasframetype_t	*pframetype;
	daliasskintype_t	*pskintype;
	int					start, end, total;
	
//	start = Hunk_LowMark ();

	pinmodel = (mdl_t *)buffer;

	version = LittleLong (pinmodel->version);
//	if (version != ALIAS_VERSION)
//		Sys_Error ("%s has wrong version number (%i should be %i)",
//				 mod->name, version, ALIAS_VERSION);

//
// allocate space for a working header, plus all the data except the frames,
// skin and group info
//
	size = 	sizeof (aliashdr_t) 
			+ (LittleLong (pinmodel->numframes) - 1) *
			sizeof (pheader->frames[0]);
//	pheader = Hunk_AllocName (size, loadname);
	pheader = malloc(size);
	
//	mod->flags = LittleLong (pinmodel->flags);

//
// endian-adjust and copy the data, starting with the alias model header
//
	pheader->boundingradius = LittleFloat (pinmodel->boundingradius);
	pheader->numskins = LittleLong (pinmodel->numskins);
	pheader->skinwidth = LittleLong (pinmodel->skinwidth);
	pheader->skinheight = LittleLong (pinmodel->skinheight);


	pheader->numverts = LittleLong (pinmodel->numverts);

	pheader->numtris = LittleLong (pinmodel->numtris);

	pheader->numframes = LittleLong (pinmodel->numframes);
	numframes = pheader->numframes;

//	pheader->size = LittleFloat (pinmodel->size) * ALIAS_BASE_SIZE_RATIO;

	for (i=0 ; i<3 ; i++)
	{
		pheader->scale[i] = LittleFloat (pinmodel->scale[i]);
		pheader->scale_origin[i] = LittleFloat (pinmodel->scale_origin[i]);
		pheader->eyeposition[i] = LittleFloat (pinmodel->eyeposition[i]);
	}


//
// load the skins
//
	pskintype = (daliasskintype_t *)&pinmodel[1];
	pskintype = Mod_LoadAllSkins (pheader->numskins, pskintype);

//
// load base s and t vertices
//
	pinstverts = (stvert_t *)pskintype;

	for (i=0 ; i<pheader->numverts ; i++)
	{
		stverts[i].onseam = LittleLong (pinstverts[i].onseam);
		stverts[i].s = LittleLong (pinstverts[i].s);
		stverts[i].t = LittleLong (pinstverts[i].t);
	}

//
// load triangle lists
//
	pintriangles = (dtriangle_t *)&pinstverts[pheader->numverts];

	for (i=0 ; i<pheader->numtris ; i++)
	{
		triangles[i].facesfront = LittleLong (pintriangles[i].facesfront);

		for (j=0 ; j<3 ; j++)
		{
			triangles[i].vertindex[j] =
					LittleLong (pintriangles[i].vertindex[j]);
		}
	}

//
// load the frames
//
	posenum = 0;
	pframetype = (daliasframetype_t *)&pintriangles[pheader->numtris];

	for (i=0 ; i<numframes ; i++)
	{
		aliasframetype_t	frametype;

		frametype = LittleLong (pframetype->type);

		if (frametype == ALIAS_SINGLE)
		{
			pframetype = (daliasframetype_t *)
					Mod_LoadAliasFrame (pframetype + 1, &pheader->frames[i]);
		}
		else
		{
			pframetype = (daliasframetype_t *)
					Mod_LoadAliasGroup (pframetype + 1, &pheader->frames[i]);
		}
	}

	pheader->numposes = posenum;

//	mod->type = mod_alias;

// FIXME: do this right
//	mod->mins[0] = mod->mins[1] = mod->mins[2] = -16;
//	mod->maxs[0] = mod->maxs[1] = mod->maxs[2] = 16;

//
// move the complete, relocatable alias model to the cache
//	
//	end = Hunk_LowMark ();
//	total = end - start;
	
//	Cache_Alloc (&mod->cache, total, loadname);
//	if (!mod->cache.data)
//		return;
//	memcpy (mod->cache.data, pheader, total);

//	Hunk_FreeToLowMark (start);
}


int main(int argc, char *argv[])
{
	FILE *infd, *outfd;
	void *inbuf;
	int sz;
	int i, j;

	infd=fopen(argv[1], "rb");
	outfd=fopen(argv[2], "wt");

	fseek(infd, 0, 2);
	sz=ftell(infd);
	fseek(infd, 0, 0);
	inbuf=malloc(sz);
	fread(inbuf, 1, sz, infd);

	Mod_LoadAliasModel(inbuf);

	printf("ident		%d\n", pheader->ident);
	printf("version		%d\n", pheader->version);
	printf("scale		%f %f %f\n", pheader->scale[0], pheader->scale[1], pheader->scale[2]);
	printf("scale_org	%f %f %f\n", pheader->scale_origin[0], pheader->scale_origin[1], pheader->scale_origin[2]);
	printf("radius		%f\n", pheader->boundingradius);
	printf("eyepos		%f %f %f\n", pheader->eyeposition[0], pheader->eyeposition[1], pheader->eyeposition[2]);
	printf("numskins	%d\n", pheader->numskins);
	printf("skinwidth	%d\n", pheader->skinwidth);
	printf("skinheigh	%d\n", pheader->skinheight);
	printf("numverts	%d\n", pheader->numverts);
	printf("numtris		%d\n", pheader->numtris);
	printf("numframes	%d\n", pheader->numframes);
	printf("synctype	%d\n", pheader->synctype);
	printf("flags		%d\n", pheader->flags);
	printf("size		%f\n", pheader->size);

	printf("numposes	%d\n", pheader->numposes);
	printf("posverts	%d\n", pheader->poseverts);
	printf("posdata		%d\n", pheader->posedata);

	fprintf(outfd, "(key skinwidth %d)\n", pheader->skinwidth);
	fprintf(outfd, "(key skinheight %d)\n", pheader->skinheight);

	for(i=0; i<pheader->numtris; i++)
	{
		//set vertex seam values, 0=front, 1=seam, 2=back
		//this assumes none are shared between front and back tris
		if(triangles[i].facesfront)
		{
			j=triangles[i].vertindex[0];
			if(stverts[j].onseam)stverts[j].onseam=1;
			j=triangles[i].vertindex[1];
			if(stverts[j].onseam)stverts[j].onseam=1;
			j=triangles[i].vertindex[2];
			if(stverts[j].onseam)stverts[j].onseam=1;
		}else
		{
			j=triangles[i].vertindex[0];
			if(!stverts[j].onseam)stverts[j].onseam=2;
			j=triangles[i].vertindex[1];
			if(!stverts[j].onseam)stverts[j].onseam=2;
			j=triangles[i].vertindex[2];
			if(!stverts[j].onseam)stverts[j].onseam=2;
		}
	}

	fprintf(outfd, "(frameset #z");
	for(i=0; i<pheader->numframes; i++)
	{
		fprintf(outfd, "\n");
		fprintf(outfd, "  (frame %s", pheader->frames[i].name);
		for(j=0; j<pheader->numverts; j++)
		{
			fprintf(outfd, "\n");
			fprintf(outfd, "    (vertex %f %f %f "
				"(st %d %d) (seam %d))",
				(poseverts[i][j].v[0]*pheader->scale[0])+
					pheader->scale_origin[0],
				(poseverts[i][j].v[1]*pheader->scale[1])+
					pheader->scale_origin[1],
				(poseverts[i][j].v[2]*pheader->scale[2])+
					pheader->scale_origin[2],
				stverts[j].s, stverts[j].t,
				stverts[j].onseam+1);
		}
		fprintf(outfd, ")");
	}
	fprintf(outfd, ")\n");

	for(i=0; i<pheader->numtris; i++)
	{
		fprintf(outfd, "(polyidx (%d %d %d))\n", triangles[i].vertindex[0],
			triangles[i].vertindex[1], triangles[i].vertindex[2]);
	}
}
