#pragma once

#include <gb/register.h>
#include <gb/memory.h>

#include <utils/decl.h>
#include <utils/type.h>
#include <utils/conv.h>

#define add_a_instr(r) void add_a_##r() { \
	reg.a += reg.##r; \
	reg.f = 0; \
	if (!(reg.a & 255)) { reg.f |= zero; } \
	if (reg.a > 255) { reg.f |= carry; } \
	reg.a &= 255; \
	clock.add_m(1); \
	clock.add_t(4); \
}

#define dec_instr(r) void dec_##r() { \
    --reg.##r; \
    reg.##r &= 255; \
    fz(reg.##r); \
    clock.add_m(1); \
    clock.add_m(4); \
}

#define inc_instr(r) void inc_##r() { \
    ++reg.##r; \
    reg.##r &= 255; \
    fz(reg.##r); \
    clock.add_m(1); \
    clock.add_m(4); \
}

#define and_a_instr(r) void and_a_##r() { \
    reg.a &= reg.##r; \
    reg.a &= 255; \
    fz(reg.a); \
    clock.add_m(1); \
    clock.add_m(4); \
}

#define or_a_instr(r) void or_a_##r() { \
    reg.a |= reg.##r; \
    reg.a &= 255; \
    fz(reg.a); \
    clock.add_m(1); \
    clock.add_m(4); \
}

#define xor_a_instr(r) void xor_a_##r() { \
    reg.a ^= reg.##r; \
    reg.a &= 255; \
    fz(reg.a); \
    clock.add_m(1); \
    clock.add_m(4); \
}

#define dec16_instr(r1, r2) void dec_##r1##r2() { \
\
}

#define ld_instr(r1, r2) void ld_##r1_##r2() { \
    reg.##r1 = reg.##r2; \
    clock.add_m(1); \
    clock.add_t(4); \
}

namespace motane {
    namespace gb {
		enum flag {
			zero = 0x80,
			carry = 0x40,
			half = 0x20,
			underflow = 0x10
		};
		
	    class Interpreter {
		    Registers& reg;
			Memory& mem;
			Clock& clock;

			void fz(short i, bool as = false) {
				reg.f = 0; if (!(i & 255)) reg.f |= 128; reg.f |= (as ? carry : 0);
			}

		    void nop() {
				clock.add_m(1);
				clock.add_t(4);
			}
			
			instr_reg88_1p_decl(add_a_instr)
			
			instr_reg88_1p_decl(and_a_instr)
			instr_reg88_1p_decl(or_a_instr)
			instr_reg88_1p_decl(xor_a_instr)

			instr_reg88_1p_decl(dec_instr)
			instr_reg88_1p_decl(inc_instr)
	
			instr_reg88_2p_decl(ld_instr)

		};
	};
};