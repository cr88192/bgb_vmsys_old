#include <general.h>
#include <x86/desc.h>
#include <os1/syscalls.h>

extern VFILE *kstdin, *kstdout;
extern kprocess *current_process;

extern void _int48_ISR();
static int syscall_cnt;

VFILE **syscall_fd_table;
int syscall_fd_table_pos;

VDIR **syscall_dir_table;
int syscall_dir_table_pos;

int syscall_pushfd(VFILE *fd)
{
	int i;

	if(!fd)return(-1);

	for(i=0; i<syscall_fd_table_pos; i++)
		if(!syscall_fd_table[i])
	{
		syscall_fd_table[i]=fd;
		return(i);
	}

	i=syscall_fd_table_pos++;
	syscall_fd_table[i]=fd;

	return(i);
}

VFILE *syscall_getfd(int num)
{
	return(syscall_fd_table[num]);
}

int syscall_closefd(int num)
{
	if(syscall_fd_table[num])
		vfclose(syscall_fd_table[num]);
	syscall_fd_table[num]=NULL;
	return(0);
}

int syscall_pushdir(VDIR *dir)
{
	int i;

	if(!dir)return(-1);

	for(i=0; i<syscall_dir_table_pos; i++)
		if(!syscall_dir_table[i])
	{
		syscall_dir_table[i]=dir;
		return(i);
	}

	i=syscall_dir_table_pos++;
	syscall_dir_table[i]=dir;

	return(i);
}

VDIR *syscall_getdir(int num)
{
	return(syscall_dir_table[num]);
}

int syscall_closedir(int num)
{
	if(syscall_fd_table[num])
		VDir_CloseDir(syscall_fd_table[num]);
	syscall_dir_table[num]=NULL;
	return(0);
}

static void *bufgrab(void **buf, int sz)
{
	void *p;

	p=*buf;
	*buf=(void *)(((int)(*buf)+sz+3)&(~3));
	return(p);
}

static void *tycpy(void **dst, void *src, char *ty)
{
	void *p;

	p=NULL;
	if(!strcmp(ty, "int_t"))
	{
		p=bufgrab(dst, sizeof(int));
		*(int *)p=*(int *)src;
	}
	if(!strcmp(ty, "bool_t"))
	{
		p=bufgrab(dst, sizeof(int));
		*(int *)p=*(int *)src;
	}
	if(!strcmp(ty, "string_t"))
	{
		p=bufgrab(dst, strlen(src)+1);
		strcpy(p, src);
	}
	if(!p)kprint("Syscall: TyCpy: Unable to copy type '%s'\n", ty);
	return(p);
}

int syscall_rreaddir(int num, long *key,
	int cnt, char **types, char **names, void **values,
	int len, void *buffer)
{
	VDIR *dir;
	char **nbuf;
	void **vbuf;
	int i, j;
	long k;
	char *s, *t;

	dir=syscall_getdir(num);
	nbuf=kalloc(16*sizeof(char *));
	vbuf=kalloc(16*sizeof(void *));

	k=*key;
	j=VDir_ReadDir2(nbuf, vbuf, &k, dir);

	for(i=0; nbuf[i] && (i<cnt); i++)
	{
		t=bufgrab(&buffer, strlen(nbuf[i])+1);
		strcpy(t, nbuf[i]);
		names[i]=t;

		s=ObjType_GetTypeName(vbuf[i]);
		t=bufgrab(&buffer, strlen(s)+1);
		strcpy(t, s);
		types[i]=t;

		values[i]=tycpy(&buffer, vbuf[i], t);
	}

	types[i]=NULL;
	names[i]=NULL;
	values[i]=NULL;
	*key=k;

	return(j);
}

long syscall_handle(int num, long *args)
{
	VFILE *fd;
	VDIR *dir;
	long stat;
	int i;
	char *s;

	struct {
	VFILE *fd;
	VADDR *addr;
	}acc;

//	kprint("got syscall %d (itr %d)\n", num, syscall_cnt++);
	switch(num)
	{
	case SYSCALL_PRINT:
		kprint(args[0]);
		stat=0;
		break;
	case SYSCALL_OPEN:
		fd=vffopen((char *)args[0], (char *)args[1]);
		stat=syscall_pushfd(fd);
		break;
	case SYSCALL_READ:
		stat=vfread((void *)args[1], 1, args[2], syscall_getfd(args[0]));
		break;
	case SYSCALL_WRITE:
		stat=vfwrite((void *)args[1], 1, args[2], syscall_getfd(args[0]));
		break;
	case SYSCALL_CLOSE:
		stat=syscall_closefd(args[0]);
		break;
	case SYSCALL_LSEEK:
		stat=vfseek(syscall_getfd(args[0]), args[1], args[2]);
		break;
	case SYSCALL_IOCTL:
		stat=vfioctl(syscall_getfd(args[0]), args[1], (void *)args[2]);
		break;
	case SYSCALL_EOF:
		stat=vfeof(syscall_getfd(args[0]));
		break;
	case SYSCALL_INREADY:
		stat=vfinready(syscall_getfd(args[0]));
		break;
	case SYSCALL_SENDTO:
		stat=vfsend(syscall_getfd(args[0]),
			(VADDR *)args[1], (void *)args[2], args[3], args[4]);
		break;
	case SYSCALL_RECVFROM:
		stat=vfget((void *)args[0], args[1], (VADDR *)args[2], syscall_getfd(args[3]));
		break;
	case SYSCALL_ACCEPT:
//		vfioctls(syscall_getfd(args[0]), "accept", &fd, args[1]);
		acc.fd=NULL;
		acc.addr=(VADDR *)args[1];
		vfioctl(syscall_getfd(args[0]), IOCTL_ACCEPT, &acc);
		if(acc.fd)stat=syscall_pushfd(acc.fd);
			else stat=-1;
		break;

	case SYSCALL_MOREMEM:
		i=Address_AllocRegionUS(0, (args[0]+4095)>>12);
		stat=i<<12;
		break;

	case SYSCALL_EXECUTE:
		PELoad_StartApp(args[0], args[1], args[2]);
		stat=0;
		break;

	case SYSCALL_SENDMSG:
		stat=kprocess_sendmessage(args[0], args[1], args[2],
			args[3], args[4], (void *)args[5]);
		break;
	case SYSCALL_RECVMSG:
		stat=kprocess_getmessage(current_process,
			args[0], (int *)args[1],
			(int *)args[2], (void *)args[3]);
		break;

	case SYSCALL_SETKVAR:
		Var_SetString((char *)args[0], (char *)args[1]);
		stat=0;
		break;
	case SYSCALL_GETKVAR:
		s=Var_GetString((char *)args[0]);
		if(s)
		{
			strcpy((char *)args[1], s);
			stat=0;
		}else stat=-1;
		break;

	case SYSCALL_GETPID:
		stat=current_process->pid;
		break;

	case SYSCALL_GETMSTICKS:
		stat=Sys_TimeMS();
		break;
	case SYSCALL_USLEEP:
		stat=kusleep(args[0]);
		break;

	case SYSCALL_MOUNT: //path type opts
		stat=VPath_Mount(args[0], args[1], args[2]);
		break;

	case SYSCALL_UMOUNT: //name
		stat=VPath_Unmount(args[0]);
		break;

	case SYSCALL_RREADDIR:
		stat=syscall_rreaddir(args[0], args[1],
			args[2], args[3], args[4], args[5],
			args[6], args[7]);
		break;

	case SYSCALL_OPENDIR:
		dir=VPath_OpenDir(args[0]);
		stat=syscall_pushdir(dir);
		break;

	case SYSCALL_CLOSEDIR:
		stat=syscall_closedir(args[0]);
		break;

	default:
		stat=-1;
		break;
	}
	return(stat);
}

int syscall_init()
{
	syscall_cnt=0;
	NewIntISR(&_int48_ISR, 0x30, GDT_FLAG_DPL3);

	syscall_fd_table=kalloc(1024*sizeof(VFILE *));
	syscall_fd_table_pos=0;

	syscall_pushfd(kstdin);		//stdin
	syscall_pushfd(kstdout);	//stdout
	syscall_pushfd(kstdout);	//stderr

	return(0);
}
