#include <general.h>
#include <scmcc.h>

elem LoadText_File(elem name)
{
	VFILE *fd;
	int fsz, i;
	byte *buf, *s, *s2;
	u2 *bufu, *su, *tu;
	elem t, x;

	s=ELEM_TOSTRING(name);
	buf=sa_malloc(strlen(s)+1);
	strcpy(buf, s);
	s=buf;

	buf=sa_loadfile(s, &fsz);
	if(!buf)
	{
		return(MISC_UNDEFINED);
	}

	
	s=buf;
	if((s[0]==0xFF) && (s[1]==0xFE))
	{
		bufu=kalloc(fsz);
		tu=bufu;
		i=(fsz/2)-1;
		while(i--)
		{
			*tu++=s[0]+(s[1]<<8);
			s+=2;
		}
		*tu++=0;

		return(STRING16(bufu));
	}
	if((s[0]==0xFE) && (s[1]==0xFF))
	{
		bufu=kalloc(fsz);
		tu=bufu;
		i=(fsz/2)-1;
		while(i--)
		{
			*tu++=s[1]+(s[0]<<8);
			s+=2;
		}
		*tu++=0;

		return(STRING16(bufu));
	}

	t=STRING(buf);

	return(t);
}

int LoadText_Init()
{
	Interp_DefinePrimative("load-text", &LoadText_File, 1);

	return(0);
}
