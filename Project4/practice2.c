#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	alarm(60);
	
	fd_set rfds;
	fd_set r2fds;
	struct timeval tv;
	int retval;
	int retval2;
	
	
	int i = argc;
	int rc;
	FILE *fp;
	fp = fopen (argv[1],"r");
	
	char *args[3];
	int j = 0;
	while (j < i)
	{
		args[j] = argv[j+2];
		j++;
	}
	
	int stdin_pipe_fds[2], stdout_pipe_fds[2], stderr_pipe_fds[2];
	
	pipe(stdin_pipe_fds);
	pipe(stdout_pipe_fds);
	pipe(stderr_pipe_fds);
	
	
	
	rc = fork();
	if (rc == -1)
	{
		while (rc == -1)
		{
			rc = fork();
		}
	}
	
	pid_t child;
	pid_t parent;
	
	char str[100];
	//string str;
	char buf2[100];
	char buf[100];
	
	if (rc == 0)
	{
		alarm(60);
		
		child = getpid();
		
		close(stdin_pipe_fds[1]);
		close(stdout_pipe_fds[0]);
		close(stdout_pipe_fds[0]);
		
		close(0);
		dup(stdin_pipe_fds[0]);//, 0);
		close(stdin_pipe_fds[0]);
		close(1);
		dup(stdout_pipe_fds[1]);//,1);
		close(stdout_pipe_fds[1]);
		close(2);
		dup(stderr_pipe_fds[1]);//,2);
		close(stderr_pipe_fds[1]);
		//int m = 0;
		//while 
		scanf("%s",buf);
		printf("%s", buf);
		buf[0] = '\0';
		
		/*FD_ZERO(&r2fds);
		FD_SET(0, &r2fds);
		
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		int ws;
		retval2 = select(FD_SETSIZE, &r2fds, NULL, NULL, &tv);

		if (FD_ISSET(0, &r2fds))
		{
			//ws = read(0, buf, 100);
			scanf("%s",buf);
			printf("%s", "hello");
			//write(1,"hello",100);
			/*if (ws == -1)
			{
				printf("read failed\n");
			}
		}*/
	}
	if (rc > 0)
	{
		parent = getpid();
		
		close(stdin_pipe_fds[0]);
		close(stdout_pipe_fds[1]);
		close(stderr_pipe_fds[1]);
		
		
		int k = 1;
		while (fgets(str,100,fp) != NULL)
		{
			int wstatus;
			int wsta;

			printf("%s %d %s","string",k,str);
			wsta = write(stdin_pipe_fds[1],str,strlen(str));
			wstatus = read(stdout_pipe_fds[0], buf2, 100);
			/*FD_ZERO(&rfds);
			FD_SET(stdout_pipe_fds[0], &rfds);
			
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			
			
			//wsta = write(stdin_pipe_fds[1],str,strlen(str));
			
			retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
			if (FD_ISSET(stdout_pipe_fds[0], &rfds))
			{
				//wsta = write(stdin_pipe_fds[1],str,strlen(str));
				wstatus = read(stdout_pipe_fds[0], buf2, 100);
				printf("From child: %s\n",buf2);
				if (wstatus == -1)
				{
					printf("read failed\n");
					//continue;
				}
				//wsta = write(stdin_pipe_fds[1],str,strlen(str));
			}*/
			//printf("%s\n",str);
			//printf("%s\n",buf2);
			buf2[0] = '\0';
			printf("%d\n",wsta);
			printf("%d\n",wstatus);
			k++;
		}
	}
	fclose(fp);
}



/*/*FD_ZERO(&rfds);
	FD_SET(stdout_pipe_fds[0], &rfds);
			
	tv.tv_sec = 1;
	tv.tv_usec = 0;
			
			
			//wsta = write(stdin_pipe_fds[1],str,strlen(str));
	if (rc == 0)
	{
		alarm(60);
		
		//int m = 0;
		//while 
		scanf("%s",buf);
		printf("%s", buf);
		//write(1,"hello",strlen("hello"));
		//buf[0] = '\0';
	}
		
	
	while ((fgets(str,100,fp)) != NULL)
	{		
		if (rc > 0)
		{	
			//int k = 1;
			//fgets(str,100,fp);		//{
			//int wstatus;
			int wsta;
			int status;
			//printf("%s %d %s","string",k,str);
			wsta = write(stdin_pipe_fds[1],str,strlen(str));
			
			//buf2[0] = '\0';
			//printf("%s",buf2);
			printf("%d\n",wsta);
			//printf("%d\n",wstatus);
			//k++;
			wait(NULL);
			int wstatus;
			retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
			if (FD_ISSET(stdout_pipe_fds[0], &rfds))
			{
				//wsta = write(stdin_pipe_fds[1],str,strlen(str));
				wstatus = read(stdout_pipe_fds[0], buf2, 100);
				printf("From child: %s\n",buf2);
				if (wstatus == -1)
				{
					printf("read failed\n");
					//continue;
				}
				//wsta = write(stdin_pipe_fds[1],str,strlen(str));
			}
		}
		
	}*/