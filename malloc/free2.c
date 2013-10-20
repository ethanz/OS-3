/* a few aligned allocations and frees */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void* ptr[4];

   ptr[0] = Mem_Alloc(8, FIRSTFIT);
   Mem_Dump();
   ptr[1] = Mem_Alloc(16, FIRSTFIT);
   Mem_Dump();
   assert(Mem_Free(ptr[0]) == 0);
   Mem_Dump();
   assert(Mem_Free(ptr[1]) == 0);
   Mem_Dump();

   ptr[2] = Mem_Alloc(32, FIRSTFIT);
   Mem_Dump();
   ptr[3] = Mem_Alloc(8, FIRSTFIT);
   Mem_Dump();
   assert(Mem_Free(ptr[2]) == 0);
   Mem_Dump();
   assert(Mem_Free(ptr[3]) == 0);
   Mem_Dump();

   exit(0);
}
