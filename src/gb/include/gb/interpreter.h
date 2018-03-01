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

#define ld_rn_instr(r) void \
    token_concat2_p(ld, r)_n() { \
    reg.##r = mem.read<u8>(reg.pc++); \
    clock.add_m(1); \
    clock.add_t(4); \
}

#define ld_t1_switch_decl() \
    instr_switch_1p_2r_decl(0x40, ld, b) \
    instr_switch_1p_2r_decl(0x48, ld, c) \
    instr_switch_1p_2r_decl(0x50, ld, d) \
    instr_switch_1p_2r_decl(0x58, ld, e) \
    instr_switch_1p_2r_decl(0x60, ld, h) \
    instr_switch_1p_2r_decl(0x68, ld, l) 

#define dec_t1_switch_decl() \
    instr_switch_1p_1r_t1_decl(0x05, dec)

#define inc_t1_switch_decl() \
    instr_switch_1p_1r_t1_decl(0x04, inc)

#define and_t1_switch_decl() \
    instr_switch_1p_2r_decl(0xA0, and, a)

#define xor_t1_switch_decl() \
    instr_switch_1p_2r_decl(0xA8, xor, a)

#define or_t1_switch_decl() \
    instr_switch_1p_2r_decl(0xB0, or, a)

#define ld_rn_t1_switch_decl() \
    instr_switch_1p_1r_1n_t1_decl(0x06, ld) 

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

				clock.add_m(3);
				clock.add_t(12);
			}

			void ld_hl_nn() {
				reg.l = mem.read<u8>(reg.pc++);
				reg.h = mem.read<u8>(reg.pc++);

				clock.add_m(3);
				clock.add_t(12);
			}

			void inc_bc() { 
				reg.c += 1;

				if (!reg.c) 
					reg.b += 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void inc_de() {
				reg.e += 1;

				if (!reg.e)
					reg.d += 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void inc_hl() {
				reg.l += 1;

				if (!reg.l)
					reg.h += 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void inc_sp() {
				reg.sp += 1; 

				clock.add_m(1);
				clock.add_t(4);
			}

			void ld_cbc_a() {
				mem.write<u8>(make_u16(reg.b, reg.c), reg.a);

				clock.add_m(2);
				clock.add_t(8);
			}

			void ld_cde_a() {
				mem.write<u8>(make_u16(reg.d, reg.e), reg.a);

				clock.add_m(2);
				clock.add_t(8);
			}

			void ld_chli_a() {
				mem.write<u8>(make_u16(reg.h, reg.l), reg.a);

				reg.l += 1;

				if (!reg.l)
					reg.h += 1;

				clock.add_m(2);
				clock.add_t(8);
			}

			void ld_chld_a() {
				mem.write<u8>(make_u16(reg.h, reg.l), reg.a);

				reg.l -= 1;

				if (reg.l == 255)
					reg.h -= 1;

				clock.add_m(2);
				clock.add_t(8);
			}

			void dec_bc() {
				reg.c -= 1;

				if (reg.b == 255)
					reg.b -= 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void dec_de() {
				reg.e -= 1;

				if (reg.e == 255)
					reg.d -= 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void  dec_hl() {
				reg.l -= 1;

				//Auto overflow, jumpback to 255, so not to worry
				if (reg.l == 255)
					reg.h -= 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			void dec_sp() {
				reg.sp -= 1;

				clock.add_m(1);
				clock.add_t(4);
			}

			//From here, jump function
			void jr_nz_n() {
				s16 i = static_cast<s16>(mem.read<u8>(reg.pc++));

				if (i > 127) {
					i = -((~i + 1) & 255);
				}

				clock.add_m(2);
				clock.add_t(8);

				if (!(reg.f & zero)) {
					reg.pc += i;

					clock.add_m(1);
					clock.add_t(4);
				}
			}

			void jr_nc_n() {
				s16 i = static_cast<s16>(mem.read<u8>(reg.pc++));

				if (i > 127) {
					i = -((~i + 1) & 255);
				}

				clock.add_m(2);
				clock.add_t(8);

				if (!(reg.f & carry)) {
					reg.pc += i;

					clock.add_m(1);
					clock.add_t(4);
				}
			}

			void jr_c_n() {
				s16 i = static_cast<s16>(mem.read<u8>(reg.pc++));

				if (i > 127) {
					i = -((~i + 1) & 255);
				}

				clock.add_m(2);
				clock.add_t(8);

				if (reg.f & carry) {
					reg.pc += i;

					clock.add_m(1);
					clock.add_t(4);
				}
			}

			void jr_z_n() {
				s16 i = static_cast<s16>(mem.read<u8>(reg.pc++));

				if (i > 127) {
					i = -((~i + 1) & 255);
				}

				clock.add_m(2);
				clock.add_t(8);

				if (reg.f & zero) {
					reg.pc += i;

					clock.add_m(1);
					clock.add_t(4);
				}
			}

			instr_reg88_1p_decl(add_a_instr)
			
			instr_reg88_1p_decl(and_a_instr)
			instr_reg88_1p_decl(or_a_instr)
			instr_reg88_1p_decl(xor_a_instr)

			instr_reg88_1p_decl(dec_instr)
			instr_reg88_1p_decl(inc_instr)

			instr_reg88_1p_decl(ld_rn_instr)
	
			instr_reg88_2p_decl(ld_instr)

		public:

			Interpreter() = delete;
			Interpreter(Memory &mem, Registers &reg, Clock &clock)
				: mem(mem), reg(reg), clock(clock) {}

			bool fetch() {
				auto op = mem.read<u8>(reg.pc++);              // Fetch instruction
			 
				motane_log_info("Code: 0x{:x}", op);

				//These are enough to run Tetris open screen for now :)
				switch (op) {
				     case 0x00: nop(); break;
					 case 0xc3: jp_nn(); break;
					 case 0x21: ld_hl_nn(); break;
					 case 0x03: inc_bc(); break;
					 case 0x13: inc_de(); break;
					 case 0x23: inc_hl(); break;
					 case 0x33: inc_sp(); break;
					 case 0x02: ld_cbc_a(); break;
					 case 0x12: ld_cde_a(); break;
					 case 0x22: ld_chli_a(); break;
					 case 0x32: ld_chld_a(); break;
					 case 0x0B: dec_bc(); break;
					 case 0x1B: dec_de(); break;
					 case 0x2B: dec_hl(); break;
					 case 0x3B: dec_sp(); break;
					 case 0x20: jr_nz_n(); break;
					 case 0x28: jr_z_n(); break;
					 case 0x30: jr_nc_n(); break;
					 case 0x38: jr_c_n(); break;

				     ld_t1_switch_decl()
					 dec_t1_switch_decl()
					 inc_t1_switch_decl()
					 and_t1_switch_decl()
				     xor_t1_switch_decl()
				     or_t1_switch_decl()
					 ld_rn_t1_switch_decl()

					 default: motane_log_error("Unimplemented opcode: {:x}", op); return false;
				}

				return true;
			}
		};
	};
};