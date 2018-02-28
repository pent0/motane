#include <gb/memory.h>

namespace motane {
   namespace gb {
	   Memory fillMemWithRom(const char *data, u32 romSize) {
		   Memory newMem;
		   memcpy(&newMem.mem[0], data, romSize);

		   return newMem;
	   }
   }
}