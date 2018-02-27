#pragma once

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