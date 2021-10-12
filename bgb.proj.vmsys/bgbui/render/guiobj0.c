#include <general.h>
#include <graphics/render.h>
#include <graphics/gfxapi.h>

extern elem interp_repl_ctx;
extern VFILE *render_screen;
int render_keybuf[64], render_keybuf_pos;

vec2 render_mouse_origin;
vec2i render_mouse_pos;
int render_mouse_b;
vec4i color_white, color_black;

int objsk_nodraw=0;

elem objsk_root;
extern elem root_object;
elem objsk_render_object;

elem objsk_renderer;

vec2 objsk_lmo;
int objsk_lmb, objsk_lmk, objsk_lmkd;

elem sym_origin=MISC_NULL;
elem sym_size=MISC_NULL;
elem sym_extents=MISC_NULL;
elem sym_dragK=MISC_NULL;
elem sym_renderK=MISC_NULL;
elem sym_useK=MISC_NULL;
elem sym_keydownK=MISC_NULL;
elem sym_children=MISC_NULL;
elem sym_offset=MISC_NULL;
elem sym_scale=MISC_NULL;

int Render_Translate(float x, float y);
int Render_Scale(float x, float y);

elem ObjSK_GetSlot(elem obj, elem sym)
{
	elem t;

	if(ELEM_ENVOBJP(obj))
	{
		t=TyObj_GetSlot(obj, sym);
	}else
	{
		t=MRP_ApplyFrom(obj, objsk_renderer, CONS(sym, MISC_EOL));

//		t=Interp_ApplyCtxSafe(interp_repl_ctx, obj,
//			CONS(sym, MISC_EOL));
	}
	return(t);
}

elem ObjSK_SetSlot(elem obj, elem sym, elem val)
{
	elem t;

	if(ELEM_ENVOBJP(obj))
	{
		t=TyObj_SetSlot2(obj, sym, val);
	}else
	{
		t=MRP_ApplyFrom(obj, objsk_renderer, CONS(sym,
			CONS(val, MISC_EOL)));

//		t=Interp_ApplyCtxSafe(interp_repl_ctx, obj,
//			CONS(sym, MISC_EOL));
	}
	return(t);
}

elem ObjSK_Send(elem obj, elem sym, elem rest)
{
	elem t;
//	t=Interp_ApplyCtxSafe(interp_repl_ctx, obj,
//		CONS(sym, rest));
	t=MRP_ApplyFrom(obj, objsk_renderer, CONS(sym, rest));
	return(t);
}

int ObjSK_PointInObj(elem obj, vec2 o)
{
	vec2i m, n, p;
	elem t;

	if(TypeX_TypeP(obj, "longref"))return(0);

//	t=TyObj_GetSlot(obj, SYMG(sym_origin, "origin"));
	t=ObjSK_GetSlot(obj, SYMG(sym_origin, "origin"));
	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

//	t=TyObj_GetSlot(obj, SYMG(sym_size, "size"));
	t=ObjSK_GetSlot(obj, SYMG(sym_size, "size"));
	n[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	n[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

	if(o[0]<m[0])return(0);
	if(o[1]<m[1])return(0);
	if(o[0]>(m[0]+n[0]))return(0);
	if(o[1]>(m[1]+n[1]))return(0);
	return(-1);
}

int ObjSK_HeighlightObj(elem obj)
{
	vec2i m, n;
	vec4i c;
	elem t;

//	kprint("heighlight.\n");

//	t=TyObj_GetSlot(obj, SYMG(sym_origin, "origin"));
	t=ObjSK_GetSlot(obj, SYMG(sym_origin, "origin"));
	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

//	t=TyObj_GetSlot(obj, SYMG(sym_size, "size"));
	t=ObjSK_GetSlot(obj, SYMG(sym_size, "size"));
	n[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	n[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

	c[0]=0;
	c[1]=0;
	c[2]=1;
	c[3]=1;
//	Draw_FillSquare(m[0]-10, m[1]-10, n[0]+20, n[1]+20, c);
	GfxApi_FillSquare(render_screen, m[0]-10, m[1]-10, n[0]+20, n[1]+20, 0, 0, 255, 255);
}

int ObjSK_CheckObjRange(elem obj)
{
	elem t;
	vec2i m;

//	kprint("heighlight.\n");

//	t=TyObj_GetSlot(obj, SYMG(sym_extents, "extents"));
	t=ObjSK_GetSlot(obj, SYMG(sym_extents, "extents"));

	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));
}

int ObjSK_TranslateObj(elem obj, vec2 p)
{
	vec2i m;
	elem t;

	t=TyFcn_NewVector(ELEM_FROMFIXNUM(2));
	TyFcn_VectorSet(t, ELEM_FROMFIXNUM(0), ELEM_FROMFIXNUM(p[0]));
	TyFcn_VectorSet(t, ELEM_FROMFIXNUM(1), ELEM_FROMFIXNUM(p[1]));

//	Interp_ApplyCtxSafe(interp_repl_ctx, obj, CONS(SYMG(sym_dragK, "drag:"), CONS(t, MISC_EOL)));
	ObjSK_Send(obj, SYMG(sym_dragK, "drag:"), CONS(t, MISC_EOL));

	return(0);
}

elem ObjSK_RenderObject(elem obj)
{
	int i;
	elem cur, t;
	vec2 d;
	static elem sym_render=MISC_NULL;

	SYMG(sym_render, "render:");

	if(ELEM_CONSP(obj))
	{
		cur=obj;
		while(ELEM_CONSP(cur))
		{
			ObjSK_RenderObject(CAR(cur));
			cur=CDR(cur);
		}
		return(MISC_NULL);
	}

//	kprint("render-object\n");

	if(ELEM_ENVOBJP(obj) || TypeX_TypeP(obj, "longref"))
	{
//		kprint("render-object: envobj\n");

		if(ObjSK_PointInObj(obj, render_mouse_origin) || ObjSK_PointInObj(obj, objsk_lmo))
		{
			ObjSK_HeighlightObj(obj);
			if((render_mouse_b&1)&&(objsk_lmb&1))
			{
//				VecN_Subtract(render_mouse_origin, objsk_lmo, d, 3);
				d[0]=render_mouse_origin[0]-objsk_lmo[0];
				d[1]=render_mouse_origin[1]-objsk_lmo[1];

				ObjSK_TranslateObj(obj, d);
			}
			if(Render_PollKey(K_ENTER))
			{
//				kprint("use\n");
				if(!(objsk_lmkd&1))
//					Interp_ApplyCtxSafe(interp_repl_ctx, obj, CONS(SYMG(sym_useK, "use:"), MISC_EOL));
					ObjSK_Send(obj, SYMG(sym_useK, "use:"), MISC_EOL);
				objsk_lmkd|=1;
			}else objsk_lmkd&=~1;
			for(i=0; i<render_keybuf_pos; i++)
//				Interp_ApplyCtxSafe(interp_repl_ctx, obj, CONS(SYMG(sym_keydownK, "keydown:"), CONS(ELEM_FROMCHAR(render_keybuf[i]), MISC_EOL)));
				ObjSK_Send(obj, SYMG(sym_keydownK, "keydown:"), CONS(ELEM_FROMCHAR(render_keybuf[i]), MISC_EOL));
		}

//		Interp_ApplyCtxSafe(interp_repl_ctx, obj, CONS(sym_render, MISC_EOL));
		ObjSK_Send(obj, SYMG(sym_renderK, "render:"), MISC_EOL);

//		kprint("render-object: envobj ok\n");
		return(MISC_NULL);
	}

//	kprint("render-object: ok\n");
	return(MISC_NULL);
}

elem ObjSK_RenderText(elem str, elem org, elem sz, elem color, elem rest)
{
	vec3i m;
	vec4i c;
	elem cur;
	char *fnt;

//	return(MISC_NULL);

//	kprint("render-text\n");

	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(org, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(org, ELEM_FROMFIXNUM(1)));
	m[2]=ELEM_TOFIXNUM(sz);

	c[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(0)));
	c[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(1)));
	c[2]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(2)));
	c[3]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(3)));

	cur=rest;
	fnt="fixed";

	while(cur!=MISC_EOL)
	{
		if(CAR(cur)==SYM("font:"))
		{
			fnt=ELEM_TOSTRING(CADR(cur));
			cur=CDDR(cur);
			continue;
		}
		cur=CDR(cur);
	}

//	printf("%g %g %g %s\n", m[0], m[1], m[2], ELEM_TOSTRING(str));

//	Render_String(m[0], m[1], m[2], c, ELEM_TOSTRING(str));

//	GfxApi_SetFont(render_screen, "unicode");
//	GfxApi_SetFont(render_screen, "fixed");
//	GfxApi_FontSize(render_screen, 12);
	GfxApi_SetFont(render_screen, fnt);

	GfxApi_MoveTo(render_screen, m[0], m[1]);
	GfxApi_FontSize(render_screen, m[2]);
	GfxApi_TextColor(render_screen, c[0], c[1], c[2], c[3]);
	GfxApi_ShowU2(render_screen, ELEM_TOSTRING16(str));

//	kprint("render-text: ok\n");

	return(MISC_NULL);
}

elem ObjSK_RenderSquare(elem org, elem sz, elem color)
{
	vec2i m, n;
	vec4i c;

	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(org, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(org, ELEM_FROMFIXNUM(1)));

	n[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(sz, ELEM_FROMFIXNUM(0)));
	n[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(sz, ELEM_FROMFIXNUM(1)));

	c[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(0)));
	c[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(1)));
	c[2]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(2)));
	c[3]=ELEM_TOFIXNUM(TyFcn_VectorRef(color, ELEM_FROMFIXNUM(3)));

//	kprint("square (%d %d) (%d %d) (%d %d %d %d)\n", m[0], m[1], n[0], n[1], c[0], c[1], c[2], c[3]);

//	printf("%g %g %g %s\n", m[0], m[1], m[2], ELEM_TOSTRING(str));

//	Draw_FillSquare(m[0], m[1], n[0], n[1], c);
	GfxApi_FillSquare(render_screen, m[0], m[1], n[0], n[1], c[0], c[1], c[2], c[3]);

	return(MISC_NULL);
}

elem ObjSK_RenderBox(elem obj)
{
	elem cur, t;
	vec4i c;
	vec2i m, n, o;
	int osv;

	t=ObjSK_GetSlot(obj, sym_origin);
	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

	t=ObjSK_GetSlot(obj, sym_size);
	n[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	n[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

//	glMatrixMode(GL_MODELVIEW);

//	glPushMatrix();
//	GfxApi_PushMatrix(render_screen);
	Render_PushState();

	Render_Translate(m[0], m[1]);

//	printf("%f %f\n", render_mouse_origin[0], render_mouse_origin[0]);

//	Render_ConvCoords(render_screen, render_mouse_pos[0], render_mouse_pos[1], &render_mouse_origin[0], &render_mouse_origin[1]);

	cur=ObjSK_GetSlot(obj, SYMG(sym_children, "children"));
	while(ELEM_CONSP(cur))
	{
		ObjSK_RenderObject(CAR(cur));

		cur=CDR(cur);
	}

//	glPopMatrix();
//	GfxApi_PopMatrix(render_screen);
	Render_PopState();

//	Render_ConvCoords(render_screen, render_mouse_pos[0], render_mouse_pos[1], &render_mouse_origin[0], &render_mouse_origin[1]);

	return(MISC_NULL);
}

elem ObjSK_RenderContainer(elem obj)
{
	elem cur, t;
	vec4i c;
	vec2i m, n, o;
	int osv;

	static int ptime;

	t=ObjSK_GetSlot(obj, sym_origin);
	m[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	m[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

	t=ObjSK_GetSlot(obj, sym_size);
	n[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	n[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));

	Render_PushState();

	o[0]=m[0]+n[0];
	o[1]=m[1]+n[1];
	Render_SetClip(m, o);

#if 1
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	GfxApi_PushMatrix(render_screen);

	t=ObjSK_GetSlot(obj, SYMG(sym_offset, "offset"));
	o[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
	o[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));
	Render_Translate(m[0]-o[0], m[1]-o[1]);

//	t=TyObj_GetSlot(obj, SYMG(sym_scale, "scale"));
//	o[0]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(0)));
//	o[1]=ELEM_TOFIXNUM(TyFcn_VectorRef(t, ELEM_FROMFIXNUM(1)));
//	Render_Scale(o[0], o[1]);

#endif

#if 0
	if(Sys_TimeMS()>(ptime+100))
	{
		printf("%f %f\n", render_mouse_origin[0], render_mouse_origin[0]);
		ptime=Sys_TimeMS();
	}
#endif

	cur=ObjSK_GetSlot(obj, SYMG(sym_children, "children"));

	while(ELEM_CONSP(cur))
	{

		ObjSK_RenderObject(CAR(cur));
		cur=CDR(cur);
	}

	Render_PopState();


	return(MISC_NULL);
}

elem ObjSK_RenderShow(elem obj)
{
	objsk_root=CONS(obj, objsk_root);
	return(MISC_NULL);
}

elem ObjSK_RenderHide(elem obj)
{
	elem cur, lst;

	lst=MISC_EOL;
	cur=objsk_root;

	while(cur!=MISC_EOL)
	{
		if(CAR(cur)==obj)
		{
			if(lst!=MISC_EOL)
				TyFcn_SetCdr(lst, CDR(cur));
				else objsk_root=CDR(cur);
			cur=CDR(cur);
			continue;
		}
		lst=cur;
		cur=CDR(cur);
	}

	return(MISC_NULL);
}

elem ObjSK_ToggleNodraw()
{
	objsk_nodraw=!objsk_nodraw;
	return(MISC_NULL);
}

elem ObjSK_Render(elem key, elem rest)
{
	if(key == SYM("render-container:"))
		return(ObjSK_RenderContainer(CAR(rest)));
	if(key == SYM("render-box:"))
		return(ObjSK_RenderBox(CAR(rest)));
	if(key == SYM("render-text:"))
		return(ObjSK_RenderText(CAR(rest), CADR(rest), CADDR(rest), CADDDR(rest), CDDDDR(rest)));
	if(key == SYM("render-square:"))
		return(ObjSK_RenderSquare(CAR(rest), CADR(rest), CADDR(rest)));
	if(key == SYM("render-show:"))
		return(ObjSK_RenderShow(CAR(rest)));
	if(key == SYM("render-object:"))
		return(ObjSK_RenderObject(CAR(rest)));
	if(key == SYM("render-nodraw:"))
		return(ObjSK_ToggleNodraw());

	if(key == SYM("container:"))
		return(ObjSK_RenderContainer(CAR(rest)));
	if(key == SYM("box:"))
		return(ObjSK_RenderBox(CAR(rest)));
	if(key == SYM("text:"))
		return(ObjSK_RenderText(CAR(rest), CADR(rest), CADDR(rest), CADDDR(rest), CDDDDR(rest)));
	if(key == SYM("square:"))
		return(ObjSK_RenderSquare(CAR(rest), CADR(rest), CADDR(rest)));
	if(key == SYM("object:"))
		return(ObjSK_RenderObject(CAR(rest)));

	if(key == SYM("show:"))
		return(ObjSK_RenderShow(CAR(rest)));
	if(key == SYM("hide:"))
		return(ObjSK_RenderHide(CAR(rest)));
	if(key == SYM("nodraw:"))
		return(ObjSK_ToggleNodraw());

	if(key == SYM("show-3d:"))
		return(Prim_Show(CAR(rest)));

	sa_print("ObjSK_Render: unknown call: ");
	TyFcn_DumpElem(key);
	sa_print("\n");

	return(MISC_UNDEFINED);
}

int ObjSK_Frame()
{
	if(objsk_nodraw)return(0);

	ObjSK_RenderObject(objsk_root);
	objsk_lmk=objsk_lmkd;

	objsk_lmo[0]=render_mouse_origin[0];
	objsk_lmo[1]=render_mouse_origin[1];

	objsk_lmb=render_mouse_b;
	return(0);
}

int ObjSK_Init()
{
	elem t;

	objsk_root=MISC_EOL;
	MMGC3_AddNamedRoot(&objsk_root, "render-root");

	objsk_renderer=MISC_NULL;
	MMGC3_AddRoot(&objsk_renderer);

	SYMG(sym_origin, "origin");
	SYMG(sym_size, "size");

	objsk_renderer=TyFcn_Function(&ObjSK_Render, -2);
	Interp_DefineDyn("render", objsk_renderer);

	Interp_DefinePrimative("render-container",	&ObjSK_RenderContainer,		1);
	Interp_DefinePrimative("render-box",		&ObjSK_RenderBox,		1);
	Interp_DefinePrimative("render-text",		&ObjSK_RenderText,		-5);
	Interp_DefinePrimative("render-square",		&ObjSK_RenderSquare,		3);
	Interp_DefinePrimative("render-show",		&ObjSK_RenderShow,		1);
	Interp_DefinePrimative("render-object",		&ObjSK_RenderObject,		1);
	Interp_DefinePrimative("render-nodraw",		&ObjSK_ToggleNodraw,		0);
}
