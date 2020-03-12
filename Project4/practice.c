#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	alarm(60);
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
		
		char buf[100];
		scanf("%s", buf);
		printf("%s", buf);
		
	}
	if (rc > 0)
	{
		parent = getpid();
		
		close(stdin_pipe_fds[0]);
		close(stdout_pipe_fds[1]);
		close(stdout_pipe_fds[1]);
		
		
		char str[100];
		char buf2[100];
		while (fgets(str,100,fp) != NULL)
		{
			write(stdin_pipe_fds[1], str,strlen(str));
			read(stdout_pipe_fds[0], buf2, 100);
			printf("%s",buf2);
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
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
		
		//char buf[100];
		
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		int ws;
		retval2 = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
		   /* Don't rely on the value of tv now! */

		if (retval2 == 0)
		{
			printf("select timed out\n");
		}
		if (retval2 == -1)
		{
		       printf("select interrupted\n");//perror("select()");
		}
		if (retval2 < 0)
		{
			printf("select failed\n");
		}
		if (FD_ISSET(0, &rfds))
		{
			ws = read(0, buf, 100);
			//printf("%s", buf);
			if (ws == -1)
			{
				printf("read failed\n");
			}
		}
		//read(0,buf,100);
		//read(stdin_pipe_fds[0],buf,100);
		//scanf("%s", buf);
		//write(1, buf,100);
		//write(stdout_pipe_fds[1],buf,100);
		//---printf("%s", buf);
		//write(1,buf,100);
		//execve("/usr/bin/bc", args, NULL);
	}
	if (rc > 0)
	{
		parent = getpid();
		
		close(stdin_pipe_fds[0]);
		close(stdout_pipe_fds[1]);
		close(stderr_pipe_fds[1]);
		
		/*close(1);
		dup(stdin_pipe_fds[1]);//, 0);
		close(stdin_pipe_fds[1]);
		close(0);
		dup(stdout_pipe_fds[0]);//,1);
		close(stdout_pipe_fds[0]);
		close(2);
		dup(stderr_pipe_fds[0]);//,2);
		close(stderr_pipe_fds[0]);*/
		
		/*int i,j;
		i = write(stdin_pipe_fds[1], "hello\n",strlen("hello\n"));
		char buf2[100];
		j = read(stdout_pipe_fds[0], buf2, 100);
		//printf("%d", 5);
		printf("%s",buf2);*/
		
		FD_ZERO(&rfds);
		FD_SET(stdout_pipe_fds[0], &rfds);
		
		tv.tv_sec = 1;
		tv.tv_usec = 0;


		//select(stdout_pipe_fds[0],
		
		//char *c = fgets(str,100,fp);
		while (fgets(str,100,fp) != NULL)
		{
			int wstatus;
			//printf("%s",str);
			wstatus = write(stdin_pipe_fds[1], str,strlen(str));
			
			//wait(child
			//scanf("%s",buf2);
			retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
			   /* Don't rely on the value of tv now! */

			if (retval == 0)
			{
				printf("select timed out\n");
			}
			if (retval == -1)
			{
			       printf("select interrupted\n");//perror("select()");
			}
			if (retval < 0)
			{
				printf("select failed\n");
			}
			if (FD_ISSET(stdout_pipe_fds[0], &rfds))
			{
				wstatus = read(stdout_pipe_fds[0], buf2, 100);
				if (wstatus == -1)
				{
					printf("read failed\n");
				}
			}
			/*else if (retval)
			{
				printf("Data is available now.\n");
				read(stdout_pipe_fds[0], buf2, 100);
			       /* FD_ISSET(0, &rfds) will be true. 
			}
			else
			{
			       printf("No data within one second.\n");
			}*/
			//exit(EXIT_SUCCESS);

			
			//read(stdout_pipe_fds[0], buf2, 100);
			printf("%s\n",buf2);
			//printf("%s",str);
			printf("%d\n",wstatus);
			//c = fgets(str,100,fp);
		}
	}
	
	/*char str[100];
	while (fgets(str,100,fp) != NULL)
	{
		if (rc > 0)
		{
			//printf("%s",str);
			//write(stdin_pipe_fds[1], str,sizeof(str));//(int*)n);
			write(stdin_pipe_fds[1], "hello\n",strlen("hello\n"));
			char buf2[100];
			read(stdout_pipe_fds[0], buf2, 100);
			printf("%s",buf2);
		}
		if (rc == 0)
		{
			char buf[100];
			read(0,buf,100);
			//read(stdin_pipe_fds[0],buf,100);
			//scanf("%s", buf);
			//write(1, buf,100);
			//write(stdout_pipe_fds[1],buf,100);
			printf("%s", buf);
		}
		/*if (rc > 0)
		{
			char buf2[100];
			read(stdout_pipe_fds[0], buf2, 100);
			printf("%s",buf2);
		}
		//sz = getline(lptr, n, fp);
	}*/
	fclose(fp);
}