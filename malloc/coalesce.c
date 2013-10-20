/* check for coalesce free space */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void * ptr[4];

   ptr[0] = Mem_Alloc(800, FIRSTFIT);
   assert(ptr[0] != NULL);
	   Mem_Dump();

   ptr[1] = Mem_Alloc(800, FIRSTFIT);
   assert(ptr[1] != NULL);
	   Mem_Dump();

   ptr[2] = Mem_Alloc(800, FIRSTFIT);
   assert(ptr[2] != NULL);
	   Mem_Dump();

   ptr[3] = Mem_Alloc(800, FIRSTFIT);
   assert(ptr[3] != NULL);
	   Mem_Dump();

   while (Mem_Alloc(800, FIRSTFIT) != NULL)
   {
	   Mem_Dump();
   }

   assert(m_error == E_NO_SPACE);

   assert(Mem_Free(ptr[1]) == 0);
   assert(Mem_Free(ptr[2]) == 0);

   ptr[2] = Mem_Alloc(1600, FIRSTFIT);
   assert(ptr[2] != NULL);

   exit(0);
}
