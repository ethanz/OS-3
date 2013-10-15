#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int rc = Mem_Init(40960);
	printf("Return Code: %d", rc);
	Mem_Dump();
	return 0;
}
