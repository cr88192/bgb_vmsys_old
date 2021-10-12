#include <general.h>

int LBSExt_Init()
{
	Dict_Init();
	LoadText_Init();
	CGEN_Init();
	VecMath_Init();
	MiscExt_Init();
	ParseXML_Init();

	FSLBS_Init();

	return(0);
}
