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
	int free;//whether this block is free, 0 = free 1 = full 
} list_t;

list_t *head = NULL;

int Mem_Init(int sizeOfRegion)
{
	if (callCnt == 1 || sizeOfRegion <= 0){
		m_error = E_BAD_ARGS;	
		printf("mmap fail1");//test
		return -1;
	}

	callCnt = 1;
	int pageSize = getpagesize();
	sizeOfRegion += (8 - sizeOfRegion % pageSize); //round region size to be divisible by page size
	int fd = open("/dev/zero", O_RDWR);
	void *ptr = mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
		printf("mmap fail2");//test
	}

	head = (list_t *) ptr;
	head->size = sizeOfRegion;
	head->next = NULL;
	head->free = 0;

	close(fd);
	return 0;
}

void *Mem_Alloc(int size, int style)
{
	list_t *curr = head;
	int record = 0;
	list_t *fit = NULL;
	list_t *nxt = NULL;
	switch(style)
	{
		case BESTFIT:

			while(curr != NULL)
			{
				if(curr->free == 0)
				{
					if(curr->size == size)
					{
						curr->free = 1;
						return curr;
					}
					if(curr->size > size && (record == 0 || curr->size < record))
					{
						record = curr->size;
						fit = curr;
					}
					curr = curr->next;
				}
			}
			break;

		case WORSTFIT:

			while(curr != NULL)
			{
				if(curr->free == 0 && curr->size > size && (record == 0 || curr->size > record))
				{
					record = curr->size;
					fit = curr;
				}
				curr = curr->next;
			}
			break;

		case FIRSTFIT:

			while(curr != NULL)
			{
				if(curr->free == 0 && curr->size >= size)
				{
					if(curr->size != size)
					{
						nxt->next = curr->next;
						nxt->free = 0;
						nxt->size = curr->size - size;
						curr->next = nxt;
					}
					curr->free = 1;
					curr->size = size;
					return curr;
				}
				curr = curr->next;
			}
			break;
	}

	if(fit != NULL)
	{
		nxt->next = fit->next;
		nxt->free = 0;
		nxt->size = fit->size - size;
		fit->next = nxt;
		fit->free = 1;
		fit->size = size;
		return fit;
	}
	m_error = E_NO_SPACE;
	return NULL;
}

int Mem_Free(void *ptr)
{
	if(ptr == NULL || ((list_t *)ptr)->free == 0)
	{
		return -1; 
	}

	list_t* tmp = (list_t *) ptr;
	if(tmp->next != NULL)
	{
		list_t* nxt = (list_t *) tmp->next;
		tmp->next = nxt->next;
		tmp->size += nxt->size;
	}//leave nxt?

	tmp->free = 0;
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
