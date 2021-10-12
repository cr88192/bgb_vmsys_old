/*
os1 message passing utility functions.

class:
major:8.minor:24
	major 0: app/connection specific
	major 1: change in connection status
	major 2: rpc

1.0: reserved
1.1: request connection, string:sender-address
1.2: accept, string:connection-target

 */

#include <unistd.h>

struct os1msg_conn_s {
int domain;
int pid;
int conid;
};

static int			os1msg_lastcon=0;
static struct os1msg_conn_s	msg_cons[1024];

int msg_new_socket()
{
	return(os1msg_lastcon++);
}

int msg_accept(int con)
{
	int stat, class, size;
	int i;
	char *buf;

	buf=malloc(256);
	while(1)
	{
		size=256;
		stat=recieve_message(con, &class, &size, buf);
		if(stat==-1)break;

		printf("msg_accept: got msg %d %X %d\n", con, class, size);

		switch(class)
		{
		case ((1<<24)+1):
			i=msg_new_socket();
			sscanf(buf, "%d:%d:%d", &msg_cons[i].domain,
				&msg_cons[i].pid, &msg_cons[i].conid);

			sprintf(buf, "%d:%d:%d", 0, getpid(), i);
			send_message(msg_cons[i].domain,
				msg_cons[i].pid, msg_cons[i].conid,
				((1<<24)+2), strlen(buf), buf);
			free(buf);
			return(i);
			break;
		default:
			break;
		}
	}
	free(buf);

	return(-1);
}

int msg_connect(int domain, int pid, int conid)
{
	int i, j, t;
	int stat, class, size;
	char *buf;

	buf=malloc(256);
	i=msg_new_socket();

	sprintf(buf, "%d:%d:%d", 0, getpid(), i);
	send_message(domain, pid, conid,
		((1<<24)+1), strlen(buf), buf);


	t=getmsticks();
	while((getmsticks()-t)<1000)
	{
		size=256;
		stat=recieve_message(conid, &class, &size, buf);
		if(stat<0)
		{
			usleep(1000);
			continue;
		}

		switch(class)
		{
		case ((1<<24)+2):
			sscanf(buf, "%d:%d:%d", &msg_cons[i].domain,
				&msg_cons[i].pid, &msg_cons[i].conid);
			return(i);
		default:
			break;
		}
	}
	return(-1);
}

int msg_send_message(int con, int class, int size, char *buf)
{
	int i;

	i=send_message(msg_cons[con].domain,
		msg_cons[con].pid, msg_cons[con].conid,
		class, size, buf);
	return(i);
}

int msg_get_message(int con, int *class, int *size, char *buf)
{
	int i;

	i=recieve_message(con, class, size, buf);
	return(i);
}

int msg_wait_message(int con, int *class, int *size, char *buf)
{
	int i;

	while(1)
	{
		i=recieve_message(con, class, size, buf);
		if((i==-1) && !*size)
		{
			usleep(1000);
			continue;
		}
		break;
	}
	return(i);
}
