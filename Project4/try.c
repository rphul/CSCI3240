#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	char buf[100];
	FILE *fp;
	fp = fopen (argv[1],"r");
	if (fp)
	{
		printf("opened\n");
		char str[100];
		if (fgets(str,100,fp) != NULL)
		{
			printf("%s",str);
		}
			
	}
	
	fclose(fp);
}

/*
char*lptr[100];
	size_t *n;
	int sz;
	sz = getline(lptr, n, fp);
/*