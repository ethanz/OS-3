#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

//declare & define global variables
extern int callCnt;

int callCnt = 0;
int m_error = 0;

typedef struct __list_t {
	int size;
	void *next;
} list_t;

list_t *head = NULL;

int Mem_Init(int sizeOfRegion)
{
	if (callCnt == 1 || sizeOfRegion <= 0){
		m_error = E_BAD_ARGS;	
		return -1;
	}

	callCnt = 1;
	int pageSize = getpagesize();
	sizeOfRegion -= sizeOfRegion % pageSize; //round region size to be divisible by page size
	int fd = open("/dev/zero", O_RDWR);
	void *ptr = mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}

	head = (list_t *) ptr;
	head->size = sizeOfRegion;
	head->next = NULL;
	close(fd);

	return 0;
}

void *Mem_Alloc(int size, int style)
{
	return NULL;
}

int Mem_Free(void *ptr)
{
	if(ptr == NULL)
	{
		return -1; 
	}
	return 0;
}

void Mem_Dump()
{
	printf("dump:\n");
	list_t *tmp = head;
	while(tmp != NULL)
	{
		printf("Free Size: %d\n", tmp->size);
		tmp = tmp->next;
	}
}
