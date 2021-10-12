#include <pdlib.h>
#include <pdnet.h>

#include "mud0.h"

ItemInfo *item_types;
ItemInfo *skill_types;

ItemInfo *item_locate_type(char *name)
{
	ItemInfo *cur;

	cur=item_types;
	while(cur)
	{
		if(!strcmp(name, cur->name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

ItemInfo *item_define_type(char *name, char *desc)
{
	ItemInfo *tmp;

	tmp=kalloc(sizeof(ItemInfo));
	tmp->name=strdup(name);
	tmp->desc=strdup(desc);

	tmp->next=item_types;
	item_types=tmp;

	return(tmp);
}

ItemInfo *item_locate_skill(char *name)
{
	ItemInfo *cur;

	cur=skill_types;
	while(cur)
	{
		if(!strcmp(name, cur->name))return(cur);
		cur=cur->next;
	}
	return(NULL);
}

ItemInfo *item_define_skill(char *name, char *desc)
{
	ItemInfo *tmp;

	tmp=kalloc(sizeof(ItemInfo));
	tmp->name=strdup(name);
	tmp->desc=strdup(desc);

	tmp->next=skill_types;
	skill_types=tmp;

	return(tmp);
}

Item *item_fetch_inv(Item *inv, char *name)
{
	Item *cur;

	cur=inv;
	while(cur)
	{
		if(!strcmp(cur->type->name, name))
			return(cur);
		cur=cur->next;
	}
	return(NULL);
}

UserInfo *ent_new(char *name)
{
	UserInfo *tmp;

	tmp=kalloc(sizeof(UserInfo));
	tmp->user=strdup(name);

	tmp->next=users;
	users=tmp;

	return(tmp);
}

int ent_damage(UserInfo *usr, UserInfo *from, int dmg)
{
	print_touser(usr->user, "\x1b[31m%s: caused %dhp damage\x1b[37m",
		from->user, dmg);

	usr->hp-=dmg;
	if(usr->damage)
		usr->damage(usr, from);

	print_touser(usr->user, "\x1b[33mhp %d/%d, mp %d/%d\x1b[37m",
		usr->hp, usr->thp, usr->mp, usr->tmp);
	print_touser(from->user, "\x1b[33menemy hp %d/%d, mp %d/%d\x1b[37m",
		usr->hp, usr->thp, usr->mp, usr->tmp);

	if(usr->hp<=0)
	{
		print_touser(usr->user, "\x1b[31myou are dead\x1b[37m");
		print_touser(from->user, "\x1b[33mtarget is dead\x1b[37m");

		if(usr->die)
			usr->die(usr, from);
	}

	return(0);
}

int ent_recieve_items(UserInfo *ent, char *item, int cnt)
{
	Item *cur;
	ItemInfo *type;

	type=item_locate_type(item);
	if(!type)
	{
		print_touser(ent->user, "\x1b[35mno item type %s\x1b[37m",
			item);
		return(-1);
	}

	cur=ent->inv;
	while(cur)
	{
		if(!strcmp(cur->type->name, item))
		{
			cur->cnt+=cnt;
			print_touser(ent->user, "\x1b[33myou recieved %d %s\x1b[37m",
				cnt, item);
			return(0);
		}
		cur=cur->next;
	}

	cur=kalloc(sizeof(Item));
	cur->next=ent->inv;
	cur->type=type;
	cur->cnt=cnt;

	ent->inv=cur;

	print_touser(ent->user, "\x1b[33myou recieved %d %s\x1b[37m",
		cnt, item);

	return(0);
}

int ent_lose_items(UserInfo *ent, char *item, int cnt)
{
	Item *cur, *lst;
	ItemInfo *type;

	type=item_locate_type(item);
	if(!type)
	{
		print_touser(ent->user, "\x1b[35mno item type %s\x1b[37m",
			item);
		return(-1);
	}

	lst=NULL;
	cur=ent->inv;
	while(cur)
	{
		if(!strcmp(cur->type->name, item))
		{
			if(cnt>cur->cnt)cnt=cur->cnt;
			cur->cnt-=cnt;
			if(!cur->cnt)
			{
				if(lst)lst->next=cur->next;
					else ent->inv=cur->next;
			}
			print_touser(ent->user, "\x1b[33myou lost %d %s\x1b[37m",
				cnt, item);
			return(cnt);
		}
		lst=cur;
		cur=cur->next;
	}

	return(0);
}

int ent_count_items(UserInfo *ent, char *item)
{
	Item *cur;

	cur=ent->inv;
	while(cur)
	{
		if(!strcmp(cur->type->name, item))
			return(cur->cnt);
		cur=cur->next;
	}

	return(0);
}

int ent_use_item(UserInfo *ent, char *item)
{
	int i;

	i=ent_count_items(ent, item);
	if(!i)
	{
		print_touser(ent->user, "\x1b[33myou don't have item %s\x1b[37m", item);
		return(0);
	}

	if(!strcmp(item, "heal"))
	{
		ent->hp+=25;
		if(ent->hp>ent->thp)ent->hp=ent->thp;
		print_touser(ent->user, "\x1b[33mhp %d/%d, mp %d/%d\x1b[37m",
			ent->hp, ent->thp, ent->mp, ent->tmp);

		ent_lose_items(ent, "heal", 1);
		return(0);
	}

	if(!strcmp(item, "xheal"))
	{
		ent->hp+=100;
		if(ent->hp>ent->thp)ent->hp=ent->thp;
		print_touser(ent->user, "\x1b[33mhp %d/%d, mp %d/%d\x1b[37m",
			ent->hp, ent->thp, ent->mp, ent->tmp);

		ent_lose_items(ent, "xheal", 1);
		return(0);
	}

	print_touser(ent->user, "\x1b[33mcan't use item %s\x1b[37m", item);

	return(0);
}

int ent_add_skill(UserInfo *ent, char *skill, int lvl)
{
	Item *cur;
	ItemInfo *type;

	type=item_locate_skill(skill);
	if(!type)
	{
		print_touser(ent->user, "\x1b[35mno skill type %s\x1b[37m",
			skill);
		return(-1);
	}

	cur=ent->skills;
	while(cur)
	{
		if(!strcmp(cur->type->name, skill))
		{
			cur->cnt+=lvl;
			print_touser(ent->user, "\x1b[33mskill %s leveled up %d\x1b[37m",
				skill, lvl);
			return(0);
		}
		cur=cur->next;
	}

	cur=kalloc(sizeof(Item));
	cur->next=ent->skills;
	cur->type=type;
	cur->cnt=lvl;

	ent->skills=cur;

	print_touser(ent->user, "\x1b[33myou gained level %d %s\x1b[37m",
		lvl, skill);

	return(0);
}

Item *ent_fetch_skill(UserInfo *ent, char *skill)
{
	Item *cur;

	cur=ent->skills;
	while(cur)
	{
		if(!strcmp(cur->type->name, skill))
			return(cur);
		cur=cur->next;
	}

	return(NULL);
}

int ent_use_skill(UserInfo *ent, char *skill)
{
	int i;
	Item *skl;
	UserInfo *targ;

	if(!ent->targ)
	{
		print_touser(ent->user, "\x1b[35mno target\x1b[37m");
		return(0);
	}

	targ=main_getuser(ent->targ);

	skl=ent_fetch_skill(ent, skill);
	if(!skill)
	{
		print_touser(ent->user, "\x1b[35myou don't have skill %s\x1b[37m", skill);
		return(0);
	}

	if(ent->mp<skl->type->cmp)
	{
		print_touser(ent->user, "\x1b[35mnot enough mp for skill %s\x1b[37m", skill);
		return(0);
	}

	ent->mp-=skl->type->cmp;
	i=rand()%skl->type->apr;
	if(i<ent->askil)
	{
		print_touser(ent->user, "\x1b[34mused skill %s\x1b[37m", skill);
		print_touser(targ->user, "\x1b[31menemy used skill %s\x1b[37m", skill);

		i=skl->type->ahr*ent->astr;
		ent_damage(targ, ent, i);
		print_touser(ent->user, "\x1b[33myou caused %d hp damage\x1b[37m",
			i);
//		print_touser(ent->user, "\x1b[33menemy %d/%d hp\x1b[37m",
//			targ->hp, targ->thp);
	}else
		print_touser(ent->user, "\x1b[35mskill %s fizzled\x1b[37m", skill);

	print_touser(ent->user, "\x1b[33mhp %d/%d, mp %d/%d\x1b[37m",
		ent->hp, ent->thp, ent->mp, ent->tmp);

	return(0);
}

int tstnpc_talk(UserInfo *self, UserInfo *usr, char *msg)
{
	char *s, *s2, *t;
	char tb[8][64];
	int i;
	Item *item;

	if(!usr)return(0);

	self->targ=usr->user;
//	print_targ(self, "you said '%s'", msg);

//	ent_damage(usr, self, 150);

	if(!*msg)return(0);

	s=msg;
	i=0;
	while(*s)
	{
		while(*s && (*s<=' '))s++;
		t=tb[i++];
		while(*s>' ')*t++=*s++;
		*t++=0;
	}

	if(!strcmp(tb[0], "help"))
	{
		print_touser(usr->user, "help\t\t\tthis text");
		print_touser(usr->user, "list\t\t\tlist items for sale");
		print_touser(usr->user, "buy <cnt> <item>\tbuy some items");
		print_touser(usr->user, "sell <cnt> <item>\tsell some items");
		return(0);
	}

	if(!strcmp(tb[0], "list"))
	{
		print_items(usr, self->inv);
		return(0);
	}

	if(!strcmp(tb[0], "buy"))
	{
		item=item_fetch_inv(self->inv, tb[2]);
		if(!item)
		{
			print_touser(usr->user, "don't have item %s",
				tb[2]);
			return(0);
		}

		i=atoi(tb[1]);
		if(i>item->cnt)
		{
			i=item->cnt;
			print_touser(usr->user,
				"don't have that many, selling %d", i);
		}

		if((i*item->type->cost)>usr->gold)
		{
			print_touser(usr->user, "you don't have enough gold");
			return(0);
		}

		usr->gold-=i*item->type->cost;
		self->gold+=i*item->type->cost;
		ent_lose_items(self, tb[2], i);
		ent_recieve_items(usr, tb[2], i);

		print_touser(usr->user, "\x1b[33myou have %d gold\x1b[37m",
			usr->gold);
		return(0);
	}

	if(!strcmp(tb[0], "sell"))
	{
		item=item_fetch_inv(usr->inv, tb[2]);
		if(!item)
		{
			print_touser(usr->user, "you don't have item %s",
				tb[2]);
			return(0);
		}

		i=atoi(tb[1]);
		if(i>item->cnt)
		{
			i=item->cnt;
			print_touser(usr->user,
				"you don't have that many, buying %d", i);
		}

		if((i*item->type->cost)>self->gold)
		{
			print_touser(usr->user, "I you don't have enough gold");
			return(0);
		}

		usr->gold+=i*item->type->cost;
		self->gold-=i*item->type->cost;

		ent_lose_items(usr, tb[2], i);
		ent_recieve_items(self, tb[2], i);

		print_touser(usr->user, "\x1b[33myou have %d gold\x1b[37m",
			usr->gold);
		return(0);
	}

	return(0);
}

int tstnpc_engage(UserInfo *self, UserInfo *usr)
{
	print_touser(usr->user, "hello");
	print_touser(usr->user, "type 'help' for help");
	print_touser(usr->user, "");

	print_touser(usr->user, "\x1b[33myou have %d gold\x1b[37m",
		usr->gold);
}

int tstnpc_disengage(UserInfo *self, UserInfo *usr)
{
	print_touser(usr->user, "come again...");
}

int tstnpc_damage(UserInfo *self, UserInfo *usr)
{
	print_touser(usr->user, "no, I think not");
	ent_damage(usr, self, 1000);
	self->hp=100;
}

int ent_init()
{
	UserInfo *usr;
	ItemInfo *type;

	type=item_define_type("heal", "restores 25 hp");
	type->cost=1;

	type=item_define_type("xheal", "restores 100 hp");
	type->cost=5;

	type=item_define_skill("fire", "balls of fire attack spell");
	type->cmp=1;
	type->ahr=1;
	type->apr=1;

	usr=ent_new("tstnpc");
	usr->talk=&tstnpc_talk;
	usr->engage=&tstnpc_engage;
	usr->disengage=&tstnpc_disengage;
	usr->damage=&tstnpc_damage;
	usr->gold=1000;

	usr->hp=100;
	usr->thp=100;

	ent_recieve_items(usr, "heal", 100);
	ent_recieve_items(usr, "xheal", 100);

	return(0);
}
