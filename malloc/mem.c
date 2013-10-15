#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//declare & define global variables
extern int callCnt;
extern *void ptr;

int callCnt = 0;
int m_error = 0;
*void ptr = NULL;

int Mem_Init(int sizeOfRegion)
{
	if (callCnt == 1 || sizeOfRegion <= 0){
		m_error = E_BAD_ARGS;	
		return -1;
	}
	callCnt = 1;
	int pageSize = getpagesize();

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
	
}
