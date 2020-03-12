#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) 
{
    void *handle;
    char *error; 
    double (*function1)(double);
	double (*function2) (double, double);
	double (*function) ();
	double (*function3) (double, double, double);
	double (*function4) (double, double, double, double);

    /* Dynamically load the shared library that contains addvec() */
    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
	fprintf(stderr, "%s\n", dlerror());
	exit(1);
    }
    
    double arg1,arg2, arg3, arg4;
    arg1 = 0;
    arg2 = 0;
    arg3 = 0;
    arg4 = 0;
    
    if (argc == 4)
    {
	    arg1 = strtod(argv[3], NULL);
    }
    else if (argc == 5)
    {
	    arg1 = strtod(argv[3], NULL);
	    arg2 = strtod(argv[4], NULL);
    }
    else if (argc == 6)
    {
	    arg1 = strtod(argv[3], NULL);
	    arg2 = strtod(argv[4], NULL);
	    arg3 = strtod(argv[5], NULL);
    }
    else if (argc == 7)
    {
	    arg1 = strtod(argv[3], NULL);
	    arg2 = strtod(argv[4], NULL);
	    arg3 = strtod(argv[5], NULL);
	    arg4 = strtod(argv[6], NULL);
    }
    

    /* Get a pointer to the addvec() function we just loaded */
    if (argc == 3)
    {
	    function = dlsym(handle, argv[2]);
	    if ((error = dlerror()) != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	    }
    }
    else if (argc == 4)
    {
	    function1 = dlsym(handle, argv[2]);
	    if ((error = dlerror()) != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	    }
    }
    else if (argc == 5)
    {
	    function2 = dlsym(handle, argv[2]);
	    if ((error = dlerror()) != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	    }
    }
    else if (argc == 6)
    {
	    function3 = dlsym(handle, argv[2]);
	    if ((error = dlerror()) != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	    }
    }
    else if (argc == 7)
    {
	    function4 = dlsym(handle, argv[2]);
	    if ((error = dlerror()) != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	    }
    }

    double answer;
    answer = 0;
    /* Now we can call addvec() just like any other function */
    if (argc == 4)
    {
	    answer = function1(arg1);
    }
    else if (argc == 5)
    {
	    answer = function2(arg1,arg2);
    }
    else if (argc == 3)
    {
	    answer = function();
    }
    else if (argc == 6)
    {
	    answer = function3(arg1,arg2,arg3);
    }
    else if (argc == 7)
    {
	    answer = function4(arg1,arg2,arg3,arg4);
    }
    
    
    printf("%lf\n", answer);

    /* Unload the shared library */
    if (dlclose(handle) < 0) {
	fprintf(stderr, "%s\n", dlerror());
	exit(1);
    }
    return 0;
}
/* $end dll */