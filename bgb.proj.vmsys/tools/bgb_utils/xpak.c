#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
unsigned long idc;
unsigned long offset;
unsigned long size;
}PakHead;

typedef struct {
unsigned char name[56];
unsigned long offset;
unsigned long size;
}PakEnt;

int main(int argc,char *argv[])
{
    FILE *f,*o;
    PakHead head;
    PakEnt ent;
    int i;
    char *buf;
    
    buf=malloc(1024);
    
    f=fopen(argv[1],"rb");
    fread(&head,1,12,f);
    printf("%d %d\n",head.offset,head.size);
    fseek(f,head.offset,0);
    for(i=0;i<head.size/64;i++)
    {
    	fread(&ent,1,64,f);
//    	printf("%s %d %d\n",ent.name,ent.offset,ent.size);
	if(!strcmp(ent.name,argv[2]))
	{
	    fseek(f,ent.offset,0);
	    o=fopen(argv[2],"wb");
	    while(ent.size>1024)
	    {
	        fread(buf,1,1024,f);
	        fwrite(buf,1,1024,o);
	        ent.size-=1024;
	    }
	    while(ent.size)
	    {
	        fread(buf,1,1,f);
	        fwrite(buf,1,1,o);
	        ent.size--;
	    }
	}
    }
}