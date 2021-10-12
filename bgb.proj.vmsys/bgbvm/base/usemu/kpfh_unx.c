#include <general.h>

#include <unistd.h>
#include <sys/mman.h>

void *KPFH_BasicMMap(void *addr, int length, int prot, int flags, VFILE *fd, int offs)
{
	void *tmp;

	tmp=mmap(addr, length, prot, flags|MAP_ANONYMOUS, 0, offs);
	if(tmp==((void *)-1))
	{
		perror(NULL);
		abort();
	}
	return(tmp);
}

int KPFH_Munmap(void *start, int length)
{
	return(munmap(start, length));
}

int KPFH_Msync(void *start, int length, int flags)
{
	return(msync(start, length, flags));
}

int KPFH_Mprotect(void *start, int length, int prot)
{
	return(mprotect(start, length, prot));
}


int KPFH_Alloc(int size)
{
	void *tmp;

//	tmp=mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS, 0, 0);
	tmp=malloc(size);
	if(tmp==((void *)-1))
	{
		perror(NULL);
		abort();
	}
	return(tmp);
}