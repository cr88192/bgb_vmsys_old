#include <general.h>

elem storage_manproto;
elem storage_env;

elem *storage_minipool;
elem *storage_poolend, *storage_poolsize;

extern void *(*sa_allocfcn)(int size, void *data);
extern void *sa_allocdata;

extern elem form_return, form_apply, form_halt;

int Storage_Init()
{
	kprint("init storage.\n");

	MMGC3_AddRoot(&storage_manproto);
	MMGC3_AddRoot(&storage_env);

	storage_minipool=kalloc(1<<20);
	storage_poolsize=storage_minipool+(1<<18);
	storage_poolend=storage_minipool;

	return(0);
}

void *Storage_PoolAlloc(int size, void *data)
{
	void *t;
	t=storage_poolend;
	storage_poolend+=size;
	storage_poolend=(void *)(((int)storage_poolend+7)&(~7));

	if((int)(storage_poolend)>=(int)storage_poolsize)
	{
		kprint("heap overflow, %d with %d/%d.\n", size, (int)(storage_poolend-storage_minipool), 1<<20);
		while(1);
	}

	return(t);
}

elem Storage_Register(elem name, elem man)
{
//	Namespace_CreateEnvBinding(storage_env, name, man);
	return(MISC_UNDEFINED);
}

int Storage_CollectAll()
{
	elem cur, t, x;
	void *(*oldfcn)(int size, void *data);

//	oldfcn=sa_allocfcn;
//	sa_allocfcn=&Storage_PoolAlloc;
//	storage_poolend=storage_minipool;

	cur=OBJ_PEEK(storage_env, 1);
	cur=CAR(cur);
	while(cur!=MISC_EOL)
	{
		cur=CDR(cur);
	}

//	sa_allocfcn=oldfcn;
}