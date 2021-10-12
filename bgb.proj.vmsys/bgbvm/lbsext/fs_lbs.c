#include <general.h>

extern VFILE *con_stream;

elem FSLBS_WrapVFile(VFILE *fd)
{
	elem t;

	t=TyFcn_TypeX(SYM("port"), sizeof(VFILE *), &fd);
//	t=MMGC3_GetReference(fd);

	return(t);
}

VFILE *FSLBS_UnwrapVFile(elem f)
{
	VFILE *fd;

	fd=*(VFILE **)TypeX_Data(f);
//	fd=MMGC3_GetCData(f);

	return(fd);
}

elem FSLBS_OpenInputFile(elem name)
{
	VFILE *fd;
	elem t;

	fd=vffopen(ELEM_TOSTRING(name), "r+");
	t=FSLBS_WrapVFile(fd);

	return(t);
}

elem FSLBS_OpenOutputFile(elem name)
{
	VFILE *fd;
	elem t;

	fd=vffopen(ELEM_TOSTRING(name), "w+");
	t=FSLBS_WrapVFile(fd);

	return(t);
}

elem FSLBS_ReadChar(elem rest)
{
	VFILE *fd;
	elem t;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=FSLBS_UnwrapVFile(t);
	}else
	{
		fd=FSLBS_UnwrapVFile(CAR(rest));
	}

	if(vfeof(fd))return(MISC_EOF);
	return(ELEM_FROMCHAR(vfgetc(fd)));
}

elem FSLBS_WriteChar(elem ch, elem rest)
{
	VFILE *fd;
	elem t;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdout"));
		fd=FSLBS_UnwrapVFile(t);
	}else
	{
		fd=FSLBS_UnwrapVFile(CAR(rest));
	}

	vfputc(ELEM_TOCHAR(ch), fd);
	return(MISC_NULL);
}

elem FSLBS_FilePosition(elem port, elem rest)
{
	VFILE *fd;
	fd=FSLBS_UnwrapVFile(port);

	if(rest!=MISC_EOL)
	{
		vfseek(fd, ELEM_TOFIXNUM(CAR(rest)), 0);
		return(MISC_NULL);
	}else return(ELEM_FROMFIXNUM(vftell(fd)));
}

elem FSLBS_CharReadyP(elem rest)
{
	VFILE *fd;
	elem t;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=FSLBS_UnwrapVFile(t);
	}else
	{
		fd=FSLBS_UnwrapVFile(CAR(rest));
	}
	return(ELEM_FROMBOOL(vfinready(fd)));
}

elem FSLBS_EofObjectP(elem obj)
{
	return(ELEM_FROMBOOL(obj==MISC_EOF));
}

elem FSLBS_Read(elem rest)
{
	VFILE *fd;
	elem t;
	int i, j, is, ic;
	char *buf, *s;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
		fd=FSLBS_UnwrapVFile(t);
	}else
	{
		fd=FSLBS_UnwrapVFile(CAR(rest));
	}

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

elem FSLBS_Apply(elem port, elem rest)
{
	VFILE *fd;
	elem t;
	int i;
	byte *s;

	fd=FSLBS_UnwrapVFile(port);

	if(CAR(rest)==SYM("read-char:"))
	{
		if(vfeof(fd))return(MISC_EOF);
		return(ELEM_FROMCHAR(vfgetc(fd)));
	}

	if(CAR(rest)==SYM("write-char:"))
	{
		vfputc(ELEM_TOCHAR(CADR(rest)), fd);
		return(MISC_NULL);
	}

	if(CAR(rest)==SYM("write-string:"))
	{
		s=ELEM_TOSTRING(CADR(rest));
		i=strlen(s);
		vfwrite(s, 1, i, fd);
		return(MISC_NULL);
	}

	if(CAR(rest)==SYM("write-line:"))
	{
		s=ELEM_TOSTRING(CADR(rest));
		i=strlen(s);
		vfwrite(s, 1, i, fd);
		vfputc(13, fd);
		vfputc(10, fd);
		return(MISC_NULL);
	}

	if(CAR(rest)==SYM("read-byte:"))
	{
		if(vfeof(fd))return(MISC_EOF);
		return(FIXNUM(vfgetc(fd)));
	}

	if(CAR(rest)==SYM("write-byte:"))
	{
		vfputc(TOINT(CADR(rest)), fd);
		return(MISC_NULL);
	}

	if(CAR(rest)==SYM("read-bytes:"))
	{
		if(vfeof(fd))return(MISC_EOF);
		i=TOINT(CADR(rest));
		t=VECTOR_NEWT(i, VECTOR_U8);
		s=TyFcn_ByteVectorBody(t);
		vfread(s, 1, i, fd);
		return(t);
	}

	if(CAR(rest)==SYM("write-bytes:"))
	{
		t=CADR(rest);
		s=TyFcn_ByteVectorBody(t);
		i=VECTOR_LEN(t);
		if(CDDR(rest)!=MISC_EOL)
			i=TOINT(CADDR(rest));

		vfwrite(s, 1, i, fd);
		return(MISC_NULL);
	}


	if(CAR(rest)==SYM("position:"))
	{
		if(CDR(rest)!=MISC_EOL)
		{
			vfseek(fd, ELEM_TOFIXNUM(CADR(rest)), 0);
			return(MISC_NULL);
		}else return(ELEM_FROMFIXNUM(vftell(fd)));
	}

	if(CAR(rest)==SYM("char-ready?:"))
	{
		return(ELEM_FROMBOOL(vfinready(fd)));
	}

	if(CAR(rest)==SYM("eof?:"))
	{
		return(ELEM_FROMBOOL(vfeof(fd)));
	}

	kprint("FS-LBS: Unknown operation '%s'\n", ELEM_TOSYMBOL(CAR(rest)));
	return(MISC_NULL);
}

elem FSLBS_Ls(elem name)
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

int FSLBS_Init()
{
	elem t;
	typexinfo *txi;

	kprint("FSLBS_Init.\n");

	txi=TypeX_GetInfo("port");
	txi->apply=&FSLBS_Apply;

	Interp_DefinePrimative("open-input-file",	&FSLBS_OpenInputFile,		1);
	Interp_DefinePrimative("open-output-file",	&FSLBS_OpenOutputFile,	1);
	Interp_DefinePrimative("read-char",		&FSLBS_ReadChar,			-1);
	Interp_DefinePrimative("write-char",		&FSLBS_WriteChar,			-2);
	Interp_DefinePrimative("file-position",		&FSLBS_FilePosition,		-1);
	Interp_DefinePrimative("char-ready?",		&FSLBS_CharReadyP,		-1);
	Interp_DefinePrimative("eof-object?",		&FSLBS_EofObjectP,		1);

	Interp_DefinePrimative("read",			&FSLBS_Read,			-1);

	Interp_DefinePrimative("ls",			&FSLBS_Ls,			1);

	t=FSLBS_WrapVFile(kstdin);
	Interp_DefineDyn("stdin", t);

	t=FSLBS_WrapVFile(kstdout);
	Interp_DefineDyn("stdout", t);
}
