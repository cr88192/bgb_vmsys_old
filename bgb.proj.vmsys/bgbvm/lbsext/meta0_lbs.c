#include <general.h>
#include <net/pdnet.h>

elem Meta0LBS_WrapCon(Meta0_Con *con)
{
	elem t;

	t=TyFcn_TypeX(SYM("socket"), sizeof(Meta0_Con *), &fd);

	return(t);
}

Meta0_Con *Meta0LBS_UnwrapCon(elem f)
{
	Meta0_Con *con;

	con=*(Meta0_Con **)TypeX_Data(f);

	return(fd);
}

elem Meta0LBS_Read(elem rest)
{
	VFILE *fd;
	elem t;
	int i, j, is, ic;
	char *buf, *s;

	if(rest==MISC_EOL)
	{
		t=Interp_FetchDyn(SYM("stdin"));
//		fd=Meta0LBS_UnwrapVFile(t);
	}else
	{
//		fd=Meta0LBS_UnwrapVFile(CAR(rest));
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

elem Meta0LBS_Apply(elem obj, elem rest)
{
	Meta0_Con *con;
	VFILE *fd;
	elem t;
	int i;
	byte *s;

	con=Meta0LBS_UnwrapCon(obj);
	fd=con->sock;

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

int Meta0LBS_Init()
{
	elem t;
	typexinfo *txi;

	kprint("Meta0LBS_Init.\n");

	txi=TypeX_GetInfo("port");
	txi->apply=&Meta0LBS_Apply;
}
