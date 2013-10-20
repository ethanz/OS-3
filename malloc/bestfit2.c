/* use best fit free space for allocation */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void *ptr[4];
   void *first, *best, *worst;

   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   ptr[0] = Mem_Alloc(40, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   ptr[1] = Mem_Alloc(56, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   first = Mem_Alloc(256, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   best = Mem_Alloc(128, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   ptr[2] = Mem_Alloc(32, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   worst = Mem_Alloc(512, FIRSTFIT);
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   ptr[3] = Mem_Alloc(32, FIRSTFIT);
   Mem_Dump();
   int count = 0;
   while(Mem_Alloc(128, FIRSTFIT) != NULL)
   {
	   printf("%d\n", count);
	   count++;
   	Mem_Dump();
   }
   assert(m_error == E_NO_SPACE);

   assert(Mem_Free(ptr[2]) == 0);
   assert(Mem_Free(ptr[3]) == 0);
   Mem_Dump();
   assert(Mem_Free(first) == 0);
   Mem_Dump();
   assert(Mem_Free(best) == 0);
   Mem_Dump();
   assert(Mem_Free(ptr[1]) == 0);
   Mem_Dump();
   assert(Mem_Free(worst) == 0);
   Mem_Dump();
   assert(Mem_Free(ptr[0]) == 0);
   Mem_Dump();

   assert(Mem_Alloc(128, BESTFIT) == best);
   Mem_Dump();

   exit(0);
}
