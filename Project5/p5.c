#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>

#define BUFFER_LEN           100    
#define SERVER_ACK           "ACK_FROM_SERVER\n"

/* extern char *sys_errlist[]; */

// READ FILE LINE BY LINE
// char *s = NULL;
// size_t n = 0;
// while(getline(&s,&n,fp) != -1)

char* key[33];
char* val[33];
int num;
char arr[10][33];

int getWords(char *base, char target[10][33]);
void server(int port);
int setup_to_accept(int por);
int accept_connection(int accept_socket);
void serve_one_connection(int client_socket);
//void client(char *server_host);
//int connect_to_server(char *hostname, int port);
void send_msg(int fd, char *buf, int size);
int recv_msg(int fd, char *buf);
void error_check(int val, const char *str);

void main(int argc,char *argv[])
{
	int port;
	port = atoi(argv[1]);
	printf("%d\n",atoi(argv[1]));
	/* second argument, if supplied, is host where server is running */
	/*if (argc == 2)
	{
		printf("calling client\n");
		client(argv[1]);
		printf("back from client\n");
	}*/
	//else  /* if no arguments then running as the server */
	//{
	num = 0;
        printf("calling server\n");
        server(port);
        printf("back from server\n");
	//}
}

void server(int port)
{
	int rc, accept_socket, client_socket;

	accept_socket = setup_to_accept(port);
	for (;;)
	{
		client_socket = accept_connection(accept_socket);
		serve_one_connection(client_socket);
	}
}

void serve_one_connection(int client_socket)
{
	int rc, ack_length;
	char buf[BUFFER_LEN];
    
	ack_length = strlen(SERVER_ACK)+1;
	rc = recv_msg(client_socket, buf);   
	buf[rc] = '\0';
	if ( (buf[rc-1] == '\n') || (buf[rc-1] == '\0')  )
	{
		buf[rc-1] = 0;
	}
	
	/*int i = 0;
	char a = buf[0];
	while (  (a != ' ') || (a != '\0') || (a != '\n')  & (i < rc) )
	{
		
	}*/
	
	int n; //number of words
	int i; //loop counter 
	
	
	
	
	
	
	//num = 0;
	
	
	
	/*char* token;
	char* saveptr;
	token = strtok_r(buf," ",&saveptr);*/
	
	while (rc != 0)
	{
		
		char arr[10][33];
		n=getWords(buf,arr);
		//i = 0;
		//while (i<=n)
		//{
		if (strcmp(strdup(arr[0]),"put") == 0)
		{
			printf("Command: %s\n",buf);
			key[num] = strdup(arr[1]);
			val[num] = strdup(arr[2]);
			num++;
		}
		if (strcmp(strdup(arr[0]),"get") == 0)
		{
			printf("Command: %s\n",buf);
			int j = 0;
			while (strcmp(arr[1],key[j]) != 0)
			{
				//printf("key: %s arr[1]: %s\n", key[j],arr[1]);
				j++;
			}
			printf("%s %s\n", key[j],val[j]);
		}
			//i++;
		//}*/
	
		
		
		
		
		
		/*if (strcmp(token,"put") == 0)
		{
			char* k = strtok_r(NULL," ",&saveptr);
			key[num] = k;
			char* v = strtok_r(NULL, " ",&saveptr);
			val[num] = v;
			printf("put: %s %s %d\n",key[num - 1],val[num - 1],num-1);
			printf("put: %s %s %d\n",key[num],val[num],num);
			num++;
		}
		//token = "";
		if (strcmp(token,"get") == 0)
		{
			token = strtok_r(NULL, " ",&saveptr);
			char* k;
			int i = 0;
			while (k != token)
			{
				k = key[i];
				i++;
			}
			printf("get: %s %s\n",k,val[i]);
		}		
		//token = "";
		
		*/
		//send_msg(client_socket, (char *)SERVER_ACK, ack_length);
		rc = recv_msg(client_socket, buf);    
		buf[rc] = '\0';
		if ( (buf[rc-1] == '\n') || (buf[rc-1] == '\0')  )
		{
			buf[rc-1] = 0;
		}
		/*int k =0;
		while (k < 10)
		{
			arr[k] = " ";
			k++;
		}*/
		
		/*token = "";
		token = strtok_r(buf," ",&saveptr);*/
	}
	
	//int k = 0;
	//	while (k < num)
	//	{
	//		printf("value: %s\n", val[k]);
	//		printf("key: %s\n", key[k]);
	//		k++;
	//	}
	//	printf("\n");
	close(client_socket);
}

int setup_to_accept(int port)    
{
	int rc, accept_socket;
	int optval = 1;
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	accept_socket = socket(AF_INET, SOCK_STREAM, 0);
	error_check(accept_socket, "setup_to_accept socket");

	setsockopt(accept_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&optval,sizeof(optval));

	rc = bind(accept_socket, (struct sockaddr *)&sin ,sizeof(sin));
	error_check(rc, "setup_to_accept bind");

	rc = listen(accept_socket, 5);
	error_check(rc, "setup_to_accept listen");

	return(accept_socket);
}

int accept_connection(int accept_socket)    
{
	struct sockaddr_in from;
	int fromlen, client_socket, gotit;
	int optval = 1;

	fromlen = sizeof(from);
	gotit = 0;
	while (!gotit)
	{
		client_socket = accept(accept_socket, (struct sockaddr *)&from,
					       (socklen_t *)&fromlen);
		if (client_socket == -1)
		{
			/* Did we get interrupted? If so, try again */
			if (errno == EINTR)
				continue;
			else
				error_check(client_socket, "accept_connection accept");
		}
		else
			gotit = 1;
	}
		setsockopt(client_socket,IPPROTO_TCP,TCP_NODELAY,(char *)&optval,sizeof(optval));
		return(client_socket);
}

int recv_msg(int fd, char *buf)
{
	int bytes_read;

	bytes_read = read(fd, buf, BUFFER_LEN);
	error_check( bytes_read, "recv_msg read");
	return( bytes_read );
}

void send_msg(int fd, char *buf, int size)    
{
	int n;

	n = write(fd, buf, size);
	error_check(n, "send_msg write");
}

void error_check(int val, const char *str)    
{
	if (val < 0)
	{
		printf("%s :%d: %s\n", str, val, strerror(errno));
		exit(1);
	}
}


int getWords(char *base, char target[10][33])
{
	int n=0,i,j=0;
	
	for(i=0;strlen(base);i++)
	{
		if(base[i]!=' '){
			target[n][j++]=base[i];
		}
		else{
			target[n][j++]='\0';//insert NULL
			n++;
			j=0;
		}
		if(base[i]=='\0')
		    break;
	}
	return n;
	
}
