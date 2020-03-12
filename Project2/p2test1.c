#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heap_init(int num_pages_for_heap);
void *heap_alloc(int num_bytes_to_allocate);
void heap_free(void *pointer_to_area_to_free);  // not used in this test

int main(int argc, char *argv[])
{
    char *p1, *p2, *p3, *p4, *p5, *p6;

    heap_init(2);

    p1 = (char *) heap_alloc(2000);
    if ((long int)p1 % 16 != 0)
    {
        printf("p1 bad %p  pmod16 %d\n",p1,((long int)p1)%16);
        exit(-1);
    }
    memset(p1,'X',2000);

    p2 = (char *) heap_alloc(2000);
    if ((long int)p2 % 16 != 0)
    {
        printf("p2 bad %p  pmod16 %d\n",p2,((long int)p2)%16);
        exit(-1);
    }
    memset(p2,'X',2000);

    p3 = (char *) heap_alloc(2000);
    if ((long int)p3 % 16 != 0)
    {
        printf("p3 bad %p  pmod16 %d\n",p3,((long int)p3)%16);
        exit(-1);
    }
    memset(p3,'X',2000);

    p4 = (char *) heap_alloc(1000);
    if ((long int)p4 % 16 != 0)
    {
        printf("p4 bad %p  pmod16 %d\n",p4,((long int)p4)%16);
        exit(-1);
    }
    memset(p4,'X',1000);

    p5 = (char *) heap_alloc(1000);
    if ((long int)p5 % 16 != 0)
    {
        printf("p5 bad %p  pmod16 %d\n",p5,((long int)p5)%16);
        exit(-1);
    }
    memset(p5,'X',1000);


    p6 = (char *) heap_alloc(1500);  // try 1500 first
    if (p6 != NULL)
    {
        printf("p6 should have been NULL, but is %p\n",p6);
        exit(-1);
    }

    p6 = (char *) heap_alloc(50);   // then just get 50
    if ((long int)p6 % 16 != 0)
    {
        printf("p6 bad %p  pmod16 %d\n",p6,((long int)p6)%16);
        exit(-1);
    }
    memset(p6,'X',50);

    printf("DONE\n");

    return 0;
}