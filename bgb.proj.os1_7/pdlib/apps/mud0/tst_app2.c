#include <pdlib.h>
#include <pdnet.h>

#include <stdarg.h>

#include "mud0.h"

Meta0_PortInfo *main_inf;
UserInfo *users;

UserInfo *main_getuser(char *name)
{
	UserInfo *cur;

	cur=users;
	while(cur)
	{
		if(!strcmp(cur->user, name))
			return(cur);

		cur=cur->next;
	}

	return(NULL);
}

int main_line(Meta0_Con *con, char *buf)
{
	char tokb[8][64];
	char *s, *t;
	int i;

	UserInfo *usr;

	usr=con->data;

	if(buf[0]=='.')
	{
		s=buf;
		i=0;
		while(*s)
		{
			while(*s && (*s<=' '))s++;
			t=tokb[i++];
			while(*s>' ')*t++=*s++;
			*t++=0;
		}

		if(!strcmp(tokb[0], ".quit"))
			return(-1);

		if(!strcmp(tokb[0], ".help"))
		{
			print_help(con);
			return(0);
		}

		if(!strcmp(tokb[0], ".users"))
		{
			print_users(con);
			return(0);
		}

		if(!strcmp(tokb[0], ".talk"))
		{
			usr->targ=strdup(tokb[1]);
			print_talksig(usr);
			return(0);
		}

		if(!strcmp(tokb[0], ".bye"))
		{
			print_leavesig(usr);
			usr->targ=NULL;
			return(0);
		}


		if(!strcmp(tokb[0], ".inv"))
		{
			print_inventory(usr);
			return(0);
		}

		if(!strcmp(tokb[0], ".get"))
		{
			ent_recieve_items(usr, tokb[2], atoi(tokb[1]));
			return(0);
		}

		if(!strcmp(tokb[0], ".use"))
		{
			ent_use_item(usr, tokb[1]);
			return(0);
		}

		if(!strcmp(tokb[0], ".hurt"))
		{
			ent_damage(usr, usr, atoi(tokb[1]));
			return(0);
		}

		if(!strcmp(tokb[0], ".cast"))
		{
			ent_use_skill(usr, tokb[1]);
			return(0);
		}

		kprintvf(con->sock, "bad command\r\n");
	}else if(buf[0])
	{
		if(usr->targ)
		{
			print_targ(usr, buf);
		}else print_shout(usr, buf);
	}
	return(0);
}

int main_dropuser(UserInfo *usr)
{
	UserInfo *cur;

	if(users==usr)
	{
		users=usr->next;
		return(0);
	}

	cur=users;
	while(cur->next)
	{
		if(cur->next==usr)
		{
			cur->next=cur->next->next;
			break;
		}
		cur=cur->next;
	}
	return(0);
}

int main_newcon(Meta0_Con *con)
{
	UserInfo *usr;

//	kprintvf(con->sock, "hello\r\n");
	kprintvf(con->sock, "\x1b[40;37;1m");
	kprintvf(con->sock, "\x1b[2J");

	usr=kalloc(sizeof(UserInfo));
	usr->user=NULL;
	con->data=usr;
	usr->con=con;

	usr->next=users;
	users=usr;

	kprintvf(con->sock, "user: ");

	return(0);
}

int main_closed(Meta0_Con *con)
{
	UserInfo *usr;

	usr=con->data;

	main_dropuser(usr);
	print_all("\x1b[32muser %s left.\x1b[37m", usr->user);

	return(0);
}

int main_input(Meta0_Con *con)
{
	char buf[256], *s, *t, *t2;
	UserInfo *usr;
	int i;

//	kprintvf(con->sock, "hello\n");

	usr=con->data;

	s=con->buf;
	t=s;

	if(!usr->user)
	{
		t2=ksgets(buf, 255, t);
		if(t2==t)return(0);

		if(!buf[0])
		{
			kprintvf(con->sock, "\r\n");
			kprintvf(con->sock, "user: ");
			return(t2-s);
		}

		usr->user=strdup(buf);
		kprintvf(con->sock, "\x1b[32mwelcome %s\x1b[37m\r\n", usr->user);
		kprintvf(con->sock, "\x1b[32mtype .help for help\x1b[37m\r\n");
		kprintvf(con->sock, "\r\n");
		print_join(usr->user);

		usr->hp=100;
		usr->thp=100;
		usr->mp=25;
		usr->tmp=25;

		usr->gold=50;

		usr->astr=5;
		usr->askil=1;

		ent_recieve_items(usr, "heal", 5);
		ent_add_skill(usr, "fire", 1);

		return(t2-s);
	}

	while(1)
	{
		t2=ksgets(buf, 255, t);
		if(t2==t)break;
		t=t2;

//		kprintvf(con->sock, "got '%s'\r\n", buf);
		i=main_line(con, buf);
		if(i==-1)return(-1);
	}

	return(t2-s);
}

int main()
{
	int port, i;
	char *s, *s2, *t;
	char tb[8][64];
	NET_Reference *ref;
	void *a[8];

	Sys_OpenShell();
	ObjType_Init();

	Var_Init();
	Var_LoadConfig("tst2.cfg");

	NET_Init();
	HttpNode_Init();
	XmlRpc_Init();

	MRPT_Init();

	port=Var_GetValue("mud_port");
	if(!port)port=23;

	main_inf=Meta0_CreatePort(port, "mudserver");
	main_inf->new_con=&main_newcon;
	main_inf->input=&main_input;
	main_inf->closed=&main_closed;

	users=NULL;

	ent_init();


//	ref=NET_DecodeURL("http://www.hotmail.com/a_test.txt");
//	s=NET_FetchReference(ref);
//	s="test to check server response.\n";
//	s=HttpNode_Post(ref, "text/plain", s, strlen(s));
//	if(s)kprint("got '%s'\n", s);

	ref=NET_DecodeURL("xml-rpc://127.0.0.1/RPC2?validator1.simpleStructReturnTest");;
	a[0]=NetVal_WrapInt(19);
	a[1]=NULL;
	NET_CallReference(ref, a);

	while(1)
	{
		s2=Sys_ReadLine();

		if(s2)
		{
			s=s2;
			i=0;
			while(*s)
			{
				while(*s && (*s<=' '))s++;
				t=tb[i++];
				while(*s>' ')*t++=*s++;
				*t++=0;
			}

			if(!strcmp(tb[0], "quit"))break;
		}

		NET_Poll();
		usleep(1000);
	}

	return(0);
}
