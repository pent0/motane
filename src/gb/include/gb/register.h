#pragma once

#include <utils/type.h>

namespace motane {
    namespace gb {
		class Interpreter;
		class Cpu;
		
	    class Registers {
			friend class Interpreter;
			friend class Cpu;
			
		    short a, b, c, d, e, h, l, f;
			short sp, pc;
			
		public:
		    Registers();
		};
		
		class Clock {
		    friend class Interpreter;
			friend class Cpu;
			
			u32 m, t;
		
		public:
		    Clock();
			
			void add_m(u32 c) { m += c; }
			void add_t(u32 c) { t += c; }
		};
	}
}