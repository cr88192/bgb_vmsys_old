typedef struct texframe_s {
struct texframe_s *next;
teximage *image;
float size[2];
}texframe;

typedef struct texlayer_s {
struct texlayer_s *next;
texframe *frame, *fcur;
teximage *image;
float lastframe;
float framerate;
float size[2];
}texlayer;

typedef struct texture_s {
struct texture_s *next;
char *name;

texlayer *layer;
texframe *frame, *fcur;
teximage *image;
float lastframe;
float framerate;
float size[2];
}texture;

texture *Tex_GetTexture(char *name);
teximage *Tex_GetTeximage(char *name);
teximage *Tex_GetTeximage_NoMip(char *name);
