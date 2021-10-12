//#include <general.h>
//#include <graphics/render.h>

typedef struct TargaHeader_s {
	unsigned char 	id_length, ctype, itype;
	unsigned short	cindex, clength;
	unsigned char	csize;
	unsigned short	x_origin, y_origin, width, height;
	unsigned char	bpp, attributes;
} TargaHeader;

/* FIXME: support more diverse targa formats */
texturefile *Img_LoadTGA(VFILE *fd)
{
	texturefile *tmp;
	TargaHeader head;
	int pixlin, i;
	byte *dest, *src, *buf, r, g, b, a;

	head.id_length=vfgetc(fd);
	head.ctype=vfgetc(fd);
	head.itype=vfgetc(fd);
	head.cindex=vfgetc(fd)+(vfgetc(fd)<<8);
	head.clength=vfgetc(fd)+(vfgetc(fd)<<8);
	head.csize=vfgetc(fd);
	head.x_origin=vfgetc(fd)+(vfgetc(fd)<<8);
	head.y_origin=vfgetc(fd)+(vfgetc(fd)<<8);
	head.width=vfgetc(fd)+(vfgetc(fd)<<8);
	head.height=vfgetc(fd)+(vfgetc(fd)<<8);
	head.bpp=vfgetc(fd);
	head.attributes=vfgetc(fd);

	if((head.itype!=2) || ((head.bpp!=32) && (head.bpp!=24)) || (head.ctype!=0))
	{
		kprint("Img_LoadTGA: only RGB(24)/RGBA(32) uncompressed images supported.\n");
		kprint("   bpp: %d, type: %d\n", head.bpp, head.ctype);
		return(NULL);
	}

	vfseek(fd, head.id_length, SEEK_CUR); /* skip commentt */

	pixlin=head.width*head.height;
	tmp=kgalloc(sizeof(texturefile)+(pixlin*4));
	tmp->width=head.width;
	tmp->height=head.height;
	tmp->type=TF_TYPE_RGBA;
	tmp->buffer=(byte *)(tmp+1);
	tmp->palette=NULL;
	dest=tmp->buffer;

	buf=kalloc(pixlin*(head.bpp>>3));
	vfread(buf, 1, pixlin*(head.bpp>>3), fd);
	src=buf;

	for(i=0; i<pixlin; i++)
	{
/*		b=vfgetc(fd);
		g=vfgetc(fd);
		r=vfgetc(fd);
		if(head.bpp==32)
			a=vfgetc(fd);
			else a=255; */

		b=*src++;
		g=*src++;
		r=*src++;
		if(head.bpp==32)
			a=*src++;
			else a=255;
		*dest++=r;
		*dest++=g;
		*dest++=b;
		*dest++=a;
	}
//	MM_PFree(buf);
	kfree(buf);

	if(head.attributes&32)
	{
		dest=kalloc(pixlin*4);
		for(i=0; i<head.height; i++)
			memcpy(&dest[i*head.width*4], &tmp->buffer[(head.height-(i+1))*head.width*4], head.width*4);
		memcpy(tmp->buffer, dest, pixlin*4);
//		MM_PFree(dest);
		kfree(dest);
	}
	return(tmp);
}

int Img_StoreTGA(VFILE *fd, texturefile *tf)
{
	TargaHeader head;
	int pixlin, i;
	byte *buf, *src, *dst, t;

//	memset(&head, 0, sizeof(TargaHeader));

//	head.itype=2;
//	head.width=tf->width;
//	head.height=tf->height;
//	head.bpp=24;

//	vfseek(fd, head.id_length, SEEK_CUR); /* skip commentt */

	pixlin=tf->width*tf->height;
	buf=kalloc(pixlin*3+18);

	buf[2] = 2;		// uncompressed type
	buf[12] = tf->width&255;
	buf[13] = tf->width>>8;
	buf[14] = tf->height&255;
	buf[15] = tf->height>>8;
	buf[16] = 24;	// pixel size

	vfwrite(buf, 1, 18, fd);
	buf+=18;

	dst=buf;
	src=tf->buffer;

	for(i=0; i<pixlin; i++)
	{
		dst[0]=src[2];
		dst[1]=src[1];
		dst[2]=src[0];
		dst+=3;
		src+=4;
	}

	vfwrite(buf, 1, pixlin*3, fd);

	return(0);
}

int Img_Destroy(texturefile *tf)
{
//	MM_PFree(tf);
	return(0);
}
