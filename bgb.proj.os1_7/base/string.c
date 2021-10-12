int strlen(const char *s)
{
	int c;
	for(c=0;*s;s++)c++;
	return(c);
}

int strcpy(char *s1,const char *s2)
{
	while(*s2)
	{
		*s1=*s2;
		s1++;
		s2++;
	}
	*s1=0;
}

int strncpy(char *s1, const char *s2, int n)
{
	int c;
	c=0;
	while(*s2 && c<n)
	{
		*s1=*s2;
		s1++;
		s2++;
		c++;
	}
	*s1=0;
}

/* int strcmp(const char *s1,const char *s2)
{
	int c;
	c=0;
	while(*s1||*s2)
	{
		if(*s1)
		{
			c+=*s1;
			s1++;
		}
		if(*s2)
		{
			c-=*s2;
			s2++;
		}
	}
	return(c);
} */

int strcmp(const char *s1, const char *s2)
{
	while((*s1==*s2) && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if(*s1!=*s2)return(-1);
	return(0);
}

int stricmp(const char *s1, const char *s2)
{
	while((tolower(*s1)==tolower(*s2)) && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if(*s1!=*s2)return(-1);
	return(0);
}

/* int strncmp(const char *s1, const char *s2, int n)
{
	int c, d;
	c=0;
	d=0;
	while((*s1||*s2)&&(d<n))
	{
		if(*s1)
		{
			c+=*s1;
			s1++;
		}
		if(*s2)
		{
			c-=*s2;
			s2++;
		}
		d++;
	}
	return(c);
} */

int strncmp(const char *s1, const char *s2, int n)
{
	int i;
	for(i=0; (*s1==*s2) && *s1 && *s2 && i<n; i++)
	{
		s1++;
		s2++;
	}
	if(i==n)return(0);
	if(*s1!=*s2)return(-1);
	return(0);
}

int memcpy(void *dest, const void *src, int len)
{
	unsigned long *s, *d;
	unsigned char *s2, *d2;
	int i;

	s=src;
	d=dest;
	i=len/sizeof(unsigned long);
	while(i--)*d++=*s++;

	s2=(unsigned char *)s;
	d2=(unsigned char *)d;
	i=len%sizeof(unsigned long);
	while(i--)*d2++=*s2++;

#if 0
	while(len--)
	{
		*(char *)dest=*(char *)src;
		dest++;
		src++;
	}
#endif
}

char *memset(void *s, int c, int n)
{
	unsigned long *d;
	unsigned char *d2;
	int i;

	c&=0xff;
	c=c|(c<<8)|(c<<16)|(c<<24);

	d=s;
	i=n/sizeof(unsigned long);
	while(i--)*d++=c;
	d2=(unsigned char *)d;
	i=n%sizeof(unsigned long);
	while(i--)*d2++=c;

#if 0
	while(n)
	{
		*(char *)s=c;
		s++;
		n--;
	}
#endif
}

char *strcat(char *s, char *s2)
{
	char *st;
	st=s+strlen(s);
	strcpy(st, s2);
	return(s);
}

int isalpha(char c)
{
	if(c>='A' && c<='Z')return(1);
	if(c>='a' && c<='z')return(1);
	return(0);
}

int isdigit(char c)
{
	if(c>='0' && c<='9')return(1);
	return(0);
}

int isalnum(char c)
{
	if(c>='A' && c<='Z')return(1);
	if(c>='a' && c<='z')return(1);
	if(c>='0' && c<='9')return(1);
	return(0);
}

int tolower(char c)
{
	if(c>='A' && c<='Z')return(c-'A'+'a');
	return(c);
}
