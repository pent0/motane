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

#define dec16_instr(r1, r2) voiddec_##r1##r2() { \
\
}

#define ld_instr(r1, r2) void \
    token_concat3_p(ld, r1, r2) () { \
    reg.##r1 = reg.##r2; \
    clock.add_m(1); \
    clock.add_t(4); \
}

#define ld_t1_switch_decl() \
    instr_switch_1p_decl(0x40, ld, b) \
    instr_switch_1p_decl(0x48, ld, c) \
    instr_switch_1p_decl(0x50, ld, d) \
    instr_switch_1p_decl(0x58, ld, e) \
    instr_switch_1p_decl(0x60, ld, h) \
    instr_switch_1p_decl(0x68, ld, l) 

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

			void jp_nn() {
				reg.pc = mem.read<u16>(reg.pc);

			    motane_log_info("Jumping to address: {}", reg.pc);

				clock.add_m(3);
				clock.add_t(12);
			}
			
			instr_reg88_1p_decl(add_a_instr)
			
			instr_reg88_1p_decl(and_a_instr)
			instr_reg88_1p_decl(or_a_instr)
			instr_reg88_1p_decl(xor_a_instr)

			instr_reg88_1p_decl(dec_instr)
			instr_reg88_1p_decl(inc_instr)
	
			instr_reg88_2p_decl(ld_instr)

		public:

			Interpreter() = delete;
			Interpreter(Memory &mem, Registers &reg, Clock &clock)
				: mem(mem), reg(reg), clock(clock) {}

			bool fetch() {
				auto op = mem.read<u8>(reg.pc++);              // Fetch instruction
			 
				switch (op) {
				     case 0x00: nop(); break;
					 case 0xc3: jp_nn(); break;
				     
				     ld_t1_switch_decl()
					 
					 default: motane_log_error("Unimplemented opcode: {:x}", op); return false;
				}

				return true;
			}
		};
	};
};