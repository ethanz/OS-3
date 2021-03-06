/* second allocation is too big to fit */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   Mem_Dump();
   assert(Mem_Alloc(2048, FIRSTFIT) != NULL);
   Mem_Dump();
   assert(Mem_Alloc(2049, FIRSTFIT) == NULL);
   Mem_Dump();
   assert(m_error == E_NO_SPACE);

   exit(0);
}
