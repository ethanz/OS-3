/* a few aligned allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   Mem_Dump();
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   Mem_Dump();
   assert(Mem_Alloc(16, FIRSTFIT) != NULL);
   Mem_Dump();
   assert(Mem_Alloc(32, FIRSTFIT) != NULL);
   Mem_Dump();
   assert(Mem_Alloc(8, FIRSTFIT) != NULL);
   Mem_Dump();
   exit(0);
}
