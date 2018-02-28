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

#define instr_switch_1p_decl(code, name, n) \
  case code + 0: token_concat2_p(name, n)_b(); break;   \
  case code + 1: token_concat2_p(name, n)_c(); break;   \
  case code + 2: token_concat2_p(name, n)_d(); break;   \
  case code + 3: token_concat2_p(name, n)_e(); break;   \
  case code + 4: token_concat2_p(name, n)_h(); break;   \
  case code + 5: token_concat2_p(name, n)_l(); break;   \
  case code + 7: token_concat2_p(name, n)_a(); break;

//case code + 6: name_##n_hl(N, Hl); break;