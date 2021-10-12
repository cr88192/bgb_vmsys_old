#include <general.h>

extern VFILE *con_stream;

elem VPathVM_OpenInputFile(elem name)
{
	VFILE *fd;
	elem t;

	fd=vffopen(ELEM_TOSTRING(name), "r+");
//	t=TyFcn_TypeX(SYM("port"), sizeof(VFILE *), &fd);
	t=MMGC3_GetReference(fd);
	return(t);
}

elem VPathVM_OpenOutputFile(elem name)
{
	VFILE *fd;
	elem t;

	fd=vffopen(ELEM_TOSTRING(name), "w+");
//	t=TyFcn_TypeX(SYM("port"), sizeof(VFILE *), &fd);
	t=MMGC3_GetReference(fd);
	return(t);
}

elem VPathVM_ReadChar(elem rest)
{
	VFILE *fd;
	elem t;

//	fd=*(VFILE **)TyFcn_TypeX_Data(port);
//	fd=MMGC3_GetCData(port);
	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=MMGC3_GetCData(t);
	}else fd=MMGC3_GetCData(CAR(rest));

	if(vfeof(fd))return(MISC_EOF);
	return(ELEM_FROMCHAR(vfgetc(fd)));
}

elem VPathVM_WriteChar(elem ch, elem rest)
{
	VFILE *fd;
	elem t;

//	fd=*(VFILE **)TyFcn_TypeX_Data(port);
//	fd=MMGC3_GetCData(port);
	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdout"));
		fd=MMGC3_GetCData(t);
	}else fd=MMGC3_GetCData(CAR(rest));

	vfputc(ELEM_TOCHAR(ch), fd);
	return(MISC_NULL);
}

elem VPathVM_FilePosition(elem port, elem rest)
{
	VFILE *fd;
//	fd=*(VFILE **)TyFcn_TypeX_Data(port);
	fd=MMGC3_GetCData(port);

	if(rest==MISC_EOL)
	{
		vfseek(fd, ELEM_TOFIXNUM(CAR(rest)), 0);
		return(MISC_NULL);
	}else return(ELEM_FROMFIXNUM(vftell(fd)));
}

elem VPathVM_CharReadyP(elem rest)
{
	VFILE *fd;
	elem t;

//	fd=*(VFILE **)TyFcn_TypeX_Data(port);
	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=MMGC3_GetCData(t);
	}else fd=MMGC3_GetCData(CAR(rest));
	return(ELEM_FROMBOOL(vfinready(fd)));
}

elem VPathVM_EofObjectP(elem obj)
{
	return(ELEM_FROMBOOL(obj==MISC_EOF));
}

elem VPathVM_Read(elem rest)
{
	VFILE *fd;
	elem t;
	int i, j, is, ic;
	char *buf, *s;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=MMGC3_GetCData(t);
	}else fd=MMGC3_GetCData(CAR(rest));

	buf=kalloc(4096);
	s=buf;
	i=0;
	is=0;
	ic=0;

	j=0;
	while(j<=' ')
	{
		if(vfeof(fd))return(MISC_EOF);
		j=vfgetc(fd);
	}
	while(i || is || ic || (j>' '))
	{
		*s++=j;

//		kprint("char %c\n", j);

		if(j==';')ic=1;
		if(j=='\n')ic=0;

		if(!ic)
		{
			if(j=='\"')is^=1;
			if(!is)
			{
				if(j=='(')i++;
				if(j==')')i--;
				if(j=='[')i++;
				if(j==']')i--;
				if(j=='{')i++;
				if(j=='}')i--;
			}
		}
		if(vfeof(fd))break;
		j=vfgetc(fd);
	}
	*s++=0;

	if(!*buf || i || is || ic)return(MISC_EOF); //no or incomplete data

	s=buf;
	t=ScmParse_Line(&s, 0);

	kfree(buf);

	return(t);
}

elem VPathVM_Ls(elem name)
{
	VDIR *dir;
	long key, lkey;

	long buf[16];
	char *cols[16];
	int i;

	dir=VPath_OpenDir(ELEM_TOSTRING(name));
	if(!dir)
	{
		kprint("no dir \"%s\"\n", ELEM_TOSTRING(name));
		return(MISC_NULL);
	}

	key=0;
	while(1)
	{
		lkey=VDir_DupKey(dir, key);
		i=VDir_ReadDir(buf, cols, &key, dir);
		if(!i)break;
		if(!lkey)
		{
			kprint("(");
			for(i=0; i<16 && cols[i]; i++)
			{
				if(i)kprint(" ");
				kprint("%s", cols[i]);
			}
			kprint(")\n");
		}

		kprint("(");
		for(i=0; i<16 && cols[i]; i++)
		{
			if(i)kprint(" ");
			if(cols[i][0]=='$')kprint("%s", buf[i]);
			if(cols[i][0]=='%')kprint("%d", buf[i]);
		}
		kprint(")\n");
	}
	return(MISC_NULL);
}

int VPathVM_Init()
{
	elem t;

	kprint("VPathVM_Init.\n");

	return(0);

	Interp_DefinePrimative("open-input-file",	&VPathVM_OpenInputFile,		1);
	Interp_DefinePrimative("open-output-file",	&VPathVM_OpenOutputFile,	1);
	Interp_DefinePrimative("read-char",			&VPathVM_ReadChar,			-1);
	Interp_DefinePrimative("write-char",		&VPathVM_WriteChar,			-2);
	Interp_DefinePrimative("file-position",		&VPathVM_FilePosition,		-1);
	Interp_DefinePrimative("char-ready?",		&VPathVM_CharReadyP,		-1);
	Interp_DefinePrimative("eof-object?",		&VPathVM_EofObjectP,		1);

	Interp_DefinePrimative("read",				&VPathVM_Read,				-1);

	Interp_DefinePrimative("ls",				&VPathVM_Ls,				1);

//	t=TyFcn_TypeX(SYM("port"), sizeof(VFILE *), &con_stream);

	t=MMGC3_GetReference(kstdin);
	Interp_DefineDyn("stdin", t);

//	t=TyFcn_TypeX(SYM("port"), sizeof(VFILE *), &con_stream);

	t=MMGC3_GetReference(kstdout);
	Interp_DefineDyn("stdout", t);
}
