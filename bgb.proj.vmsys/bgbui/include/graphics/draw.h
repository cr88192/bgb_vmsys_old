typedef struct teximage_s {
struct teximage_s *next;
char *name;

int width;
int height;
void *data;
}teximage;

#define TF_TYPE_RGB		1
#define TF_TYPE_RGBA	2
#define TF_TYPE_GREY	3
#define TF_TYPE_PAL8	4

typedef struct {
int width;
int height;
byte *buffer; /* lower left to upper right */
byte *palette;
int type;
}texturefile;

int Draw_SetSolid_2D(float aspect, int xo, int yo, int xs, int ys);
int Draw_SetPerspective_3D(float aspect, int fov, vec3 org, vec3 angles,  int xo, int yo, int xs, int ys);
//int Draw_SetPerspective_3D(float aspect, int fov, vec16 pos);
int Draw_SetOrtho_3D(float aspect, int size, vec3 org, vec3 angles, int x, int y, int w, int h);

int Draw_Square(int x, int y, int w, int h);
int Draw_FillSquare(int x, int y, int w, int h, vec4f c);
int Draw_Picture(int x, int y, int w, int h, teximage *tex);
int Draw_PictureCrop(int x, int y, int w, int h, int cx, int cy, int cw, int ch, teximage *tex);
int Draw_Init();

int Draw_OrthoGrid(int osize, int gstep, vec3 org, vec3 angles);

int Draw_Character(int x, int y, int w, int h, vec4f c, int ch);
int Draw_String(int x, int y, int n, char *s);
int Draw_Bind(teximage *tex);

int Render_String(int x, int y, int sz, vec4f c, char *s);

//texturefile *Img_LoadTGA(VFILE *fd);
int Img_Destroy(texturefile *tf);

teximage *Tex_LoadTexture(int w, int h, byte *buf, int calcmip);
teximage *Tex_FromTexturefile(texturefile *tf);

int Tex_Init();
