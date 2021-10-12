#include <pdlib.h>
#include <pdnet.h>

#include <stdarg.h>

#include "mud0.h"

int print_join(char *user)
{
	UserInfo *cur;

	cur=users;
	while(cur)
	{
		if(cur->con)
			kprintvf(cur->con->sock, "\x1b[32muser %s joined.\x1b[37m\r\n", user);

		cur=cur->next;
	}

	return(0);
}

int print_shout(UserInfo *usr, char *msg)
{
	UserInfo *cur;

	cur=users;
	while(cur)
	{
		if(cur->con)
			kprintvf(cur->con->sock, "%s: %s\r\n", usr->user, msg);

		cur=cur->next;
	}

	return(0);
}

int print_all(char *msg, ...)
{
	UserInfo *cur;
	char buf[256];
	va_list lst;

	va_start(lst, msg);
	vsprintf(buf, msg, lst);
	va_end(lst);

	cur=users;
	while(cur)
	{
		if(cur->con)
			kprintvf(cur->con->sock, "%s\r\n", buf);

		cur=cur->next;
	}

	return(0);
}

int print_targ(UserInfo *usr, char *msg, ...)
{
	UserInfo *cur;
	char buf[256];
	va_list lst;

	va_start(lst, msg);
	vsprintf(buf, msg, lst);
	va_end(lst);

	cur=users;
	while(cur)
	{
		if(!strcmp(cur->user, usr->targ))
		{
			if(cur->con)
				kprintvf(cur->con->sock, "%s: %s\r\n", usr->user, buf);
			else if(cur->talk)
				cur->talk(cur, usr, buf);
		}

		cur=cur->next;
	}

	return(0);
}

int print_users(Meta0_Con *con)
{
	UserInfo *cur;

	kprintvf(con->sock, "users:\r\n");

	cur=users;
	while(cur)
	{
		kprintvf(con->sock, "    %s\r\n", cur->user);

		cur=cur->next;
	}

	return(0);
}

int print_touser(char *user, char *msg, ...)
{
	UserInfo *cur;
	char buf[256];
	va_list lst;

	va_start(lst, msg);
	vsprintf(buf, msg, lst);
	va_end(lst);

	cur=users;
	while(cur)
	{
		if(!strcmp(cur->user, user))
		{
			if(cur->con)
				kprintvf(cur->con->sock, "%s\r\n", buf);
		}

		cur=cur->next;
	}

	return(0);
}

int print_inventory(UserInfo *usr)
{
	Item *cur;

	kprintvf(usr->con->sock, "inventory:\r\n");

	kprintvf(usr->con->sock, "    %d gold\r\n", usr->gold);

	cur=usr->inv;
	while(cur)
	{
		kprintvf(usr->con->sock, "    %d %s, %dg: %s\r\n",
			cur->cnt, cur->type->name, cur->type->cost,
			cur->type->desc);

		cur=cur->next;
	}

	return(0);
}

int print_items(UserInfo *usr, Item *items)
{
	Item *cur;

	cur=items;
	while(cur)
	{
		kprintvf(usr->con->sock, "    %d %s, %dg: %s\r\n",
			cur->cnt, cur->type->name, cur->type->cost,
			cur->type->desc);

		cur=cur->next;
	}

	return(0);
}

int print_talksig(UserInfo *usr)
{
	UserInfo *targ;

	print_touser(usr->targ, "\x1b[32m%s converses privately with you\x1b[37m\n",
		usr->user);

	targ=main_getuser(usr->targ);
	if(!targ)return(0);
	if(targ->engage)
		targ->engage(targ, usr);
	return(0);
}

int print_leavesig(UserInfo *usr)
{
	UserInfo *targ;

	if(!usr->targ)
	{
		kprintvf(usr->con->sock, "\x1b[32mnot in conversation\x1b[37m\r\n");
		return(0);
	}

	print_touser(usr->targ, "\x1b[32m%s leaves private conversation\x1b[37m",
		usr->user);

	targ=main_getuser(usr->targ);
	if(!targ)return(0);
	if(targ->disengage)
		targ->disengage(targ, usr);
	return(0);
}

int print_help(Meta0_Con *con)
{
	kprintvf(con->sock, "cmds:\r\n");
	kprintvf(con->sock, ".help\t\t\tthis text\r\n");
	kprintvf(con->sock, ".users\t\t\tlist users\r\n");

	kprintvf(con->sock, "\r\n");
	kprintvf(con->sock, ".talk <targ>\t\ttalk to a specific target\r\n");
	kprintvf(con->sock, ".bye\t\t\tleave conversation mode\r\n");

	kprintvf(con->sock, "\r\n");
	kprintvf(con->sock, ".get <cnt> <item>\tgive yourself items\r\n");
	kprintvf(con->sock, ".use <item>\t\tuse an item\r\n");
	kprintvf(con->sock, ".inv\t\t\tlist contents of inventory\r\n");

	kprintvf(con->sock, "\r\n");
	kprintvf(con->sock, ".hurt <amount>\t\tinflict damage on self\r\n");

	kprintvf(con->sock, "\r\n");
	kprintvf(con->sock, ".quit\t\t\tdisconnect\r\n");

	kprintvf(con->sock, "\r\n");

	return(0);
}
