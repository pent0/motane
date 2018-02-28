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

namespace motane {
    namespace gb {
		class Interpreter;
		class Cpu;
		
	    class Registers {
			friend class Interpreter;
			friend class Cpu;
			
			short a, b, c, d, e, h, l, f = 0;
			short sp, pc = 0;
			
		public:
			Registers()
				:pc(0x100) {}
		};
		
		class Clock {
		    friend class Interpreter;
			friend class Cpu;
			
			u32 m, t = 0;
		
		public:
			Clock() = default;
			
			void add_m(u32 c) { m += c; }
			void add_t(u32 c) { t += c; }
		};
	}
}