#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int
main(int argc, char *argv[])
{

			      assert(Mem_Init(4096) == 0);
			       void * ptr[4];
			       
			           ptr[0] = Mem_Alloc(900, BESTFIT);
			            assert(ptr[0] != NULL);
				  
				  printf("pass first alloc\n");
				      ptr[1] = Mem_Alloc(900, BESTFIT);
				       assert(ptr[1] != NULL);
				     
				        ptr[2] = Mem_Alloc(900, BESTFIT);
				          assert(ptr[2] != NULL);
				        
				            assert(Mem_Free(ptr[1]) == 0);
					     ptr[1] = NULL;
					   
					       ptr[1] = Mem_Alloc(900, BESTFIT);
					        assert(ptr[1] != NULL);
					      
					          ptr[3] = Mem_Alloc(1100, BESTFIT);
					           assert(ptr[3] != NULL);
	if(ptr == NULL){
	printf("No Return value\n");}
	Mem_Dump();
	return 0;
}
