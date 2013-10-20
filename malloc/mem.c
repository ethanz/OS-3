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

extern list_t *head;
list_t *head = NULL;

int Mem_Init(int sizeOfRegion)
{
	if (callCnt == 1 || sizeOfRegion <= 0){
		m_error = E_BAD_ARGS;	
		return -1;
	}

	callCnt = 1;
	int pageSize = getpagesize();
	if(sizeOfRegion % pageSize != 0)
	{
		sizeOfRegion += pageSize - (sizeOfRegion % pageSize); //round region size to be divisible by page size
	}
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
	head->free = 0;

	close(fd);
	return 0;
}

void *Mem_Alloc(int size, int style)
{
	if(size % 8 != 0)
	{
		size += (8 - size % 8);
	}

	list_t *curr = head;
	int record = 0;
	list_t *fit = NULL;
	list_t *nxt = NULL;
	int done = 0;

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
						return (void *)curr;
					}
					if(curr->size > size && (record == 0 || curr->size < record))
					{
						record = curr->size;
						fit = curr;
					}
				}
				curr = (list_t *)curr->next;
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

			while(curr != NULL && done != 1)
			{
				if(curr->free == 0 && curr->size >= size + sizeof(list_t))
				{
					fit = curr;
					done = 1;
				}
				if(done != 1)
				{
					curr = curr->next;
				}
			}
			break;
	}

	if(fit != NULL)
	{
		nxt = (void *)fit + size + sizeof(list_t);
		nxt->next = NULL;
		if(fit->next != NULL){
			nxt->next = fit->next;
		}
		nxt->free = 0;
		nxt->size = fit->size - size - sizeof(list_t);

		fit->next = nxt;
		fit->free = 1;
		fit->size = size;
		//printf("%p\n", fit);
		return fit;
	}

	m_error = E_NO_SPACE;
	return NULL;
}

int Mem_Free(void *ptr)
{
	if(ptr == NULL || ((list_t *)ptr)->free == 0)
	{
		m_error = E_BAD_POINTER;
		printf("Bad Pointer\n");
		return -1; 
	}

	list_t* tmp = (list_t *) ptr;
	list_t* prv = NULL;
	list_t* curr = head;
	while(curr != tmp)
	{
		prv = curr;
		curr = curr->next;
	}
	if(tmp->next != NULL)
	{
		list_t* nxt = (list_t *) (tmp->next);
		if(nxt->free == 0)
		{
			if(nxt->next != NULL)
			{
				tmp->next = nxt->next;
			}
			else
			{
				tmp->next = NULL;
			}
			tmp->size += nxt->size + sizeof(list_t);
			nxt = NULL;
		}
		if(prv != NULL)
		{
			if(prv->free == 0)
			{
				prv->next = tmp->next;
				prv->size += tmp->size + sizeof(list_t);
			}
		}
		//printf("freed: next is not NULL\n");
	}//leave nxt?
	//printf("freed\n");

	tmp->free = 0;
	return 0;
}

void Mem_Dump()
{
	printf("dump:\n");
	list_t *tmp = head;
	int count = 0;
	printf("%d\n", (int)sizeof(list_t));
	while(tmp != NULL)
	{
		count++;
		if(tmp->free == 0)
		{
			printf("Free Size: %d\n", tmp->size);
		}
		else
		{
			printf("Allocated Size: %d\n", tmp->size);
		}
		tmp = tmp->next;
	}
	printf("------------------------\n");
}
