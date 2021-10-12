#include <general.h>

int vfsend(VFILE *vfd, VADDR *targ, void *msg, int len, int flags)
{
	if(vfd->send)return(vfd->send(vfd, targ, msg, len, flags));
	return(-1);
}

int vfasend(VFILE *vfd, VADDR *targ, void *msg, int len, int flags)
{
	if(vfd->chain)return(vfsend(vfd->chain, targ, msg, len, flags));
	return(-1);
}

int vfalink(VFILE *src, VFILE *dst)
{
	src->chain=dst;
	return(0);
}

int vfadylink(VFILE *src, VFILE *dst)
{
	src->chain=dst;
	dst->chain=src;
	return(0);
}

int vfadyunlink(VFILE *vfd)
{
	if(vfd->chain)vfd->chain->chain=NULL;
	vfd->chain=NULL;
	return(0);
}

int vfarelay(VFILE *src)
{
	if(!src->chain)return(0);
	while(vfinready(src))vfaputc(vfgetc(src), src); /* not terribly effecient */
	return(1);
}

/* insert/remove, ringbuffer semantics */
VFILE *vfainsert(VFILE *src, VFILE *list)
{
	if(list)
	{
		src->chain=list;
		src->ch_prev=list->ch_prev;
		if(list->ch_prev)list->ch_prev->chain=src;
		if(list->chain)list->chain->ch_prev=src;
	}
	return(src);
}

VFILE *vfacinsert(VFILE *src, VFILE *list)
{
	if(list)
	{
		src->c_next=list;
		src->c_prev=list->c_prev;
		if(list->c_prev)list->c_prev->c_next=src;
		if(list->c_next)list->c_next->c_prev=src;
	}
	return(src);
}

VFILE *vfaremove(VFILE *src)
{
	if(src->ch_prev)src->ch_prev->chain=src->chain;
	if(src->chain)src->chain->ch_prev=src->ch_prev;
	if(src->chain==src)return(NULL);
	return(src->chain);
}

VFILE *vfacremove(VFILE *src)
{
	if(src->c_prev)src->c_prev->c_next=src->c_next;
	if(src->c_next)src->c_next->c_prev=src->c_prev;
	if(src->c_next==src)return(NULL);
	return(src->c_next);
}

int VAddr_Match(VADDR *src, VADDR *targ)
{
	int mask;
	if((src->proto&(~255))!=(targ->proto&(~255)))return(0);
	if(targ->proto&255)if((src->proto&255)!=(targ->proto&255))return(0);
	switch(src->proto&(~255))
	{
	case PROTO_IPV4:
		mask=~((1<<(32-(targ->ipv4.flags&255)))-1);
		if((ntohl(src->ipv4.addr)&mask)==(ntohl(targ->ipv4.addr)&mask))return(1);
		break;
	case PROTO_IPV6:
	default:
		break;
	}
	return(0);
}

/* return true if targ1 is closer than targ2 */
int VAddr_Closer(VADDR *src, VADDR *targ1, VADDR *targ2)
{
	int cnt1, cnt2;
	if(!VAddr_Match(src, targ1))return(0);
	if(!VAddr_Match(src, targ2))return(0);

	switch(src->proto&(~255))
	{
	case PROTO_IPV4:
		cnt1=(32-(targ1->ipv4.flags&255));
		cnt2=(32-(targ2->ipv4.flags&255));
		if(cnt1<cnt2)return(1);
			else return(0);
		break;
	case PROTO_IPV6:
	default:
		break;
	}
	return(0);
}

dirobj *VAddr_Lookup(VADDR *src, dirobj *list)
{
	dirobj *cur, *near;
	cur=list;
	near=NULL;
	while(cur)
	{
		if(VAddr_Match(src, cur->addr))
			if(!near)near=cur;
			else if(VAddr_Closer(src, cur->addr, near->addr))
			near=cur;
		cur=cur->next;
	}
	return(near);
}

dirobj *VAddr_LookupExact(VADDR *src, dirobj *list)
{
	dirobj *cur;
	cur=list;
	while(cur)
	{
		if(cur->addr->proto==src->proto)switch(cur->addr->proto&(~255))
		{
		case PROTO_IPV4:
			if(cur->addr->ipv4.port==src->ipv4.port)
				if(cur->addr->ipv4.addr==src->ipv4.addr)
				return(cur);
			break;
		default:
			break;
		}
		cur=cur->next;
	}
	return(NULL);
}

int addrspace_close(VDIR *dir)
{
	/* is collected */
}

dirobj *addrspace_lookupdirobjaddr(VDIR *dir, VADDR *addr)
{
	dirobj *hdl;
	hdl=dir->data;
	return(VAddr_Lookup(addr, hdl));
}

dirobj *addrspace_createdirobjaddr(VDIR *dir, VADDR *addr)
{
	dirobj *hdl, *tmp;
	hdl=dir->data;
	tmp=kgalloc(sizeof(dirobj));
	tmp->next=hdl->first;
	if(hdl->first)hdl->first->prev=tmp;
	hdl->first=tmp;

	tmp->addr=addr;
	return(tmp);
}

VDIR *VAddr_NewSpace()
{
	VDIR *tmp;
	dirobj *hdl;
	VFILE *vfd;

	tmp=kgalloc(sizeof(VDIR));
	hdl=kgalloc(sizeof(dirobj));
	vfd=kgalloc(sizeof(VFILE));

	hdl->data=vfd;

	tmp->data=hdl;
	tmp->close=addrspace_close;
	tmp->lookupdirobjaddr=addrspace_lookupdirobjaddr;
	tmp->createdirobjaddr=addrspace_createdirobjaddr;
	return(tmp);
}

int VAddr_BindVFile(VDIR *space, VADDR *addr, VFILE *vfd)
{
	dirobj *dobj, *hdl;

	hdl=space->data;

	dobj=VAddr_LookupExact(addr, hdl->first);
	if(dobj)
	{
		dobj->data=vfd;
		vfd->chain=hdl->data;
		return(0);
	}
	dobj=VDir_CreateObjAddr(space, addr);
	if(dobj)
	{
		dobj->data=vfd;
		vfd->chain=hdl->data;
		return(0);
	}
	return(-1);
}
