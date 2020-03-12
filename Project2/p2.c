#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>


//#define page_size getpagesize()

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

int page_size;
int num_pages;
void* region;
unsigned char *cp;

/*typedef struct block
{
	int size;
	unsigned char* at;
	int isFree;
	struct block* next;
	struct block* prev;
} block_t;*/
int count = 0;
int bytes_available = 0;
struct block_t {
	int size;
	unsigned char* at;
	int isFree;
	struct block_t* next;
	struct block_t* prev;
};

struct block_t* head = NULL;
struct block_t* traverse = NULL;
//traverse = NULL;


void heap_init(int num_pages_for_heap)
{
	struct block_t head_p;
	head = &head_p;
	
	page_size = getpagesize();
	num_pages = num_pages_for_heap;
	region = mmap(NULL, page_size*num_pages_for_heap, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	
	//head->at = (unsigned char*) region;
	head->at = region;
	cp = (unsigned char*) region;
	cp = region;
	
	if ((long int)cp % 16 != 0)
	{
		while ((long int)cp % 16 != 0)
		{
			cp+= 1;
			count+=1;
		}
	}
	region = cp;
	head->at = cp;
	head->next = NULL;
	head->prev = NULL;
	head->size = (page_size*num_pages_for_heap) - count;
	head->isFree = 1;
	
	bytes_available = (page_size*num_pages_for_heap) - count;
	count = 0;
}


void *heap_alloc(int num_bytes_to_allocate)
{
	if (num_bytes_to_allocate > bytes_available)
	{
		return NULL;
	}
	
	struct block_t head_p;
	head = &head_p;
	
	traverse = head;
	traverse->at = head->at;
	traverse->size = head->size;
	traverse->next = head->next;
	traverse->prev = head->prev;
	traverse->isFree = head->isFree;
	int allocated = 0;
	while( (traverse != NULL) && (allocated != 1 ) )
	{
		if ( (traverse->size >= num_bytes_to_allocate) && (traverse->isFree == 1) )
		{
			if ( (traverse->next == NULL) && (num_bytes_to_allocate != bytes_available) )
			{
				cp = traverse->at;
				cp += num_bytes_to_allocate;
				if ((long int)cp % 16 != 0)
				{
					while ((long int)cp % 16 != 0)
					{
						cp+= 1;
						count+=1;
					}
				}
				bytes_available -= num_bytes_to_allocate + count;
				traverse->size = num_bytes_to_allocate + count;
				traverse->isFree = 0;
				traverse->next = traverse;
				traverse->next->at = cp;
				traverse->next->size = bytes_available;
				traverse->next->isFree = 1;
				traverse->next->next = NULL;
				//traverse->next->prev->at= traverse->at;
				//traverse->next = *cp;
			
				count = 0;
				allocated = 1;
			}
			return traverse->at;
		}
		traverse = traverse->next;
		traverse->at = traverse->next->at;
		traverse->size = traverse->next->size;
		traverse->next = traverse->next->next;
		traverse->prev = traverse->next->prev;
		traverse->isFree = traverse->next->isFree;
	}
	
	if (traverse == NULL)
	{
		return NULL;
	}
	
	
	/*cp = region + num_bytes_to_allocate;
	if (&cp % 16 != 0)
	{
		while (&cp % 16 != 0)
		{
			cp += 1;
			count+=1;
		}
	}
	block.next.size = block.size - num_bytes_to_allocate;
	block.size = num_bytes_to_allocate;
	
	return block.at;*/
	
	//void* ptr = malloc(num_bytes_to_allocate);
}

void  heap_free(void *pointer_to_area_to_free)
{
	struct block_t head_p;
	head = &head_p;
	traverse = head;
	traverse->at = head->at;
	traverse->size = head->size;
	traverse->next = head->next;
	traverse->prev = head->prev;
	traverse->isFree = head->isFree;
	int isThere = 1;
	if (traverse != pointer_to_area_to_free)
	{
		while ( (traverse != pointer_to_area_to_free) && (isThere == 1) )
		{
			if (traverse->next != NULL)
			{
				isThere = 0;
				return;
			}
			traverse = traverse->next;
		}
	}
	
	if (isThere == 1)
	{
		bytes_available += traverse->size;
		traverse->isFree = 1;
		if ( (traverse->next != NULL) && (traverse->next->isFree == 1) )
		{
			traverse->size += traverse->next->size;
			traverse->next->size = 0;
			traverse->next = traverse->next->next;
			traverse->next = NULL;
		}
		
		if ( (traverse->prev != NULL) && (traverse->prev->isFree == 1) )
		{
			traverse->prev->size += traverse->size;
			traverse->size = 0;
			traverse->prev->next = traverse->next;
			traverse->at = NULL;
		}
	}
	
}