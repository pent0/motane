/*
	Motane
	Copyright (C) 2018 Do Trong Thu

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
					return T{};
				}
				
			    if (0xE000 <= offset &&
                    offset <= 0xFDFF) {
					mirror = 0xC000;
				}
				
			    T res;
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

			friend Memory fillMemWithRom(const char *data, u32 romSize);
		};

		Memory fillMemWithRom(const char *data, u32 romSize);
	}
}