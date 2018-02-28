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

#define tokenizing_p(tok) tok 
#define token_concat2_p(tok1, tok2) tokenizing_p(tok1)_##tok2
#define token_concat3_p(tok1, tok2, tok3) token_concat2_p(tok1, tok2)_##tok3

#define instr_reg88_1p_decl(func) \
    func(a); \
    func(b); \
	func(c); \
	func(d); \
	func(e); \
    func(h); \
    func(l);

#define instr_reg88_2p_rdecl(func, r) \
    func(r, a); \
    func(r, b); \
    func(r, c); \
    func(r, d); \
    func(r, e); \
    func(r, h); \
    func(r, l); 

#define instr_reg1616_2p_rdecl(func) \
    func(b, c); \
    func(d, e); \


#define instr_reg88_2p_decl(func) \
    instr_reg88_2p_rdecl(func, a) \
    instr_reg88_2p_rdecl(func, b) \
    instr_reg88_2p_rdecl(func, c) \
    instr_reg88_2p_rdecl(func, d) \
    instr_reg88_2p_rdecl(func, e) \
    instr_reg88_2p_rdecl(func, h) \
    instr_reg88_2p_rdecl(func, l)

#define instr_switch_1p_2r_decl(code, name, n) \
  case code + 0: token_concat2_p(name, n)_b(); break;   \
  case code + 1: token_concat2_p(name, n)_c(); break;   \
  case code + 2: token_concat2_p(name, n)_d(); break;   \
  case code + 3: token_concat2_p(name, n)_e(); break;   \
  case code + 4: token_concat2_p(name, n)_h(); break;   \
  case code + 5: token_concat2_p(name, n)_l(); break;   \
  case code + 7: token_concat2_p(name, n)_a(); break;

#define instr_switch_1p_1r_t1_decl(code, name) \
  case code + 0: tokenizing_p(name)_b(); break;   \
  case code + 0x10: tokenizing_p(name)_d(); break;   \
  case code + 0x20: tokenizing_p(name)_h(); break;   \
  case code + 0x08: tokenizing_p(name)_c(); break;   \
  case code + 0x18: tokenizing_p(name)_e(); break;   \
  case code + 0x28: tokenizing_p(name)_l(); break;   \
  case code + 0x38: tokenizing_p(name)_a(); break;

#define instr_switch_1p_1r_1n_t1_decl(code, name) \
  case code + 0: tokenizing_p(name)_b_n(); break;   \
  case code + 0x10: tokenizing_p(name)_d_n(); break;   \
  case code + 0x20: tokenizing_p(name)_h_n(); break;   \
  case code + 0x08: tokenizing_p(name)_c_n(); break;   \
  case code + 0x18: tokenizing_p(name)_e_n(); break;   \
  case code + 0x28: tokenizing_p(name)_l_n(); break;   \
  case code + 0x38: tokenizing_p(name)_a_n(); break;

//case code + 6: name_##n_hl(N, Hl); break;