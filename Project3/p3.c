#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_THREADS 4



int return_code[MAX_THREADS];
int arg_value[MAX_THREADS];
int num_pthreads = 0;

int zero = 0;
int one = 1;
int two = 2;
int three = 3;
int four = 4;

int MAX_ARG;

int p3test(int);

void* return_c (void *arg);

int main(int argc, char* argv[])
{
	//int div;
	//int max[MAX_THREADS];
	//bool isDiv = true;
	
	alarm(60);
	
	
	if (argc < 2)
	{
		printf("Not enough inputs.\n");
		exit(-1);
	}
	
	MAX_ARG = atoi(argv[2]);
	//printf("%d\n",MAX_ARG);
	num_pthreads = atoi(argv[1]);
	//printf("%d\n",num_pthreads);
	pthread_t thrdid[num_pthreads]; // array containing thread ids
	for (int i = 0; i < num_pthreads; i++)
	{
		//printf("i is %d\n", i);
		if (i == 0)
		{
			pthread_create(&thrdid[i], NULL, return_c, &zero);
		}
		if (i == 1)
		{
			pthread_create(&thrdid[i], NULL, return_c, &one);
		}
		if (i == 2)
		{
			pthread_create(&thrdid[i], NULL, return_c, &two);
		}
		if (i == 3)
		{
			pthread_create(&thrdid[i], NULL, return_c, &three);
		}
		//printf("i is %d\n", i);
	}
	
	for(int i = 0; i < num_pthreads; i++)
	{
		//printf("I is %d\n", i);
		pthread_join(thrdid[i], NULL);
		//printf("I is %d\n", i);
	}
	
	int rc = return_code[0];
	int arg = arg_value[0];
	for(int i = 0; i < num_pthreads; i++)
	{
		if (return_code[i] > rc)
		{
			rc = return_code[i];
			arg = arg_value[i];
		}
	}
	
	printf("%d %d\n", arg, rc); 
}

void* return_c (void *arg)
{
	int tdid = *((int *) arg);
	//printf("Thread id is %d\n",tdid);
	int rc;
	int max = 0;
	int arv = 0;
	
	
	//int thrdid = (int *) arg;
	//int thrdid = arg;
	
	int start = tdid + 1;
	
	while (start <= MAX_ARG)
	{
		rc = p3test(start);
		if (rc > max)
		{
			max = rc;
			arv = start;
		}
		start += num_pthreads;
	}
	//printf("Thread id is %d\n",tdid);
	return_code[tdid] = max;
	//printf("Thread id is %d\n",tdid);
	arg_value[tdid] = arv;
}




































	
	
