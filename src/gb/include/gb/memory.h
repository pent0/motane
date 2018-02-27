#pragma once

#include <utils/type.h>
#include <utils/log.h>

#include <vector>

namespace motane {
    namespace gb {
		enum {
			MEMORY_SIZE = 0xFFFF
		};
		
	    class Memory {
		    std::vector<char> mem;
			
		public:
		    Memory()
			   : mem(MEMORY_SIZE) {}
			
			template <typename T>
			T read(u32 offset) {
				u32 mirror = 0;
				
				if (0xFEA0 <= offset &&
                    offset <= 0xFEFF) {
					motane_log_warn("Trying to access invalid offset: {}", offset);
					return T();
				}
				
			    if (0xE000 <= offset &&
                    offset <= 0xFDFF) {
					mirror = 0xC000;
				}
				
			    T res();
				memcpy(&res, &mem[offset-mirror], sizeof(T));
					
				return res;
			}
			
			template <typename T>
			void write(u32 offset, T data) {
			    memcpy(&mem[offset], &data, sizeof(T));
			}
			
			void clear() {
		        mem.clear();
			}
		};
	}
}