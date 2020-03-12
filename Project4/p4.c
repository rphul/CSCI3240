#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <wait.h>


int main(int argc, char *argv[])
{
	alarm(60);
	
	fd_set rfds;
	fd_set r2fds;
	struct timeval tv;
	int retval;
	int retval2;
	
	
	int i = argc; 
	//printf("%d\n",i);
	int rc;
	FILE *fp;
	fp = fopen (argv[1],"r");
	
	char *args[4];
	// i = 3 ./p4 stuff -l
	args[0] = "/usr/bin/bc";
	int j = 1;	// 2nd element in args
	while (j < (i -1))		// while j < 2
	{
		args[j] = argv[j+1];	//args[1] = argv[2]  (args[2] = argv[3])  (args[3] = argv[4])
		j++;				// j = 1 j=2 j=3
	}
	args[j] = NULL;		// args[4] = NULL
	
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
		
		execve("/usr/bin/bc", args,NULL);
		//printf("%s\n", "should not see");		
		
	}
	
	char *s = NULL;
	size_t n = 0;
	
	if (rc > 0)
	{
		parent = getpid();
			
		close(stdin_pipe_fds[0]);
		close(stdout_pipe_fds[1]);
		close(stderr_pipe_fds[1]);
		  
		while(getline(&s,&n,fp) != -1)
		{   
			printf("in: %s",s);
			int wr;
			wr = write(stdin_pipe_fds[1], s, strlen(s));    
			
			FD_ZERO(&rfds);
			FD_SET(stdout_pipe_fds[0], &rfds);
			
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			
			int w;
			retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
			if (retval == 0)
			{
				printf("bc: \n");
				printf("\n");
				//continue;
			}
			if (retval == -1 &&  errno == EINTR)
			{
			       printf("select interrupted\n");//perror("select()");
				//continue;
			}
			if (retval < 0)
			{
				printf("select failed\n");
			}
			if (FD_ISSET(stdout_pipe_fds[0], &rfds))
			{
				w = read(stdout_pipe_fds[0], buf2, sizeof(buf2));
				buf2[w] = '\0';
				printf("bc: %s",buf2);
				printf("\n");
				if (w == -1)
				{
					printf("read failed\n");
				}
			}
		
			
		}
		close(stdin_pipe_fds[1]);
		wait(0);
	}
	fclose(fp);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	