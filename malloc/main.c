#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int rc = Mem_Init(40960);
	printf("Return Code: %d\n", rc);
	int rt = Mem_Alloc(8, FIRSTFIT);
	printf("Alloc Return Code: %d\n", rt);
	Mem_Dump();
	return 0;
}
