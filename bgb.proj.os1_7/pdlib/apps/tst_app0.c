#include <pdlib.h>

int main()
{
	float *fv, *fv2;
	char **rf, **rf2;
	char *s1, *s2;
	int i;

	ObjType_Init();
	ObjType_NewType("foo_t", "int:a;int:b;*char:c;2byte;short;*foo_t;");
	ObjType_NewType("vec3_t", "3float;");
	ObjType_NewType("ref_t", "string;");

	fv=ObjType_New("vec3_t", 0);
	for(i=0; i<3; i++)fv[i]=(i+1)*10;

	rf=ObjType_New("ref_t", 0);
	s1=strdup("this is a test\n");
//	*rf=fv;
	*rf=s1;

	PDLIB_Image_NameObj("rootvec", rf);
	PDLIB_StoreImage("tst.img");

	PDLIB_LoadImage("tst.img");

	rf2=PDLIB_Image_FetchName("rootvec");
//	fv2=*rf2;
	s2=*rf2;
//	printf("%f %f %f\n", fv2[0], fv2[1], fv2[2]);
	printf("'%s'\n", s2);

	return(0);
}
