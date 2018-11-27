#pragma once

#include <lux_shared/common.hpp>

enum : U8 {
    RN_XC_HALT,                //void halt(void)
    RN_XC_ERR,                 //void err(U8 code)
    RN_XC_PRINT,               //void print(U8 num)
    RN_XC_ENTITY_ROTATE,       //void entity_rotate(U16 id, bool dir)
    RN_XC_ENTITY_MOVE,         //void entity_move(U16 id, bool dir)
    RN_XC_ENTITY_GET_POS,      //I8, I8 entity_get_pos(U16 id)
    RN_XC_ENTITY_GET_ROTATION, //U16 entity_get_rotation(U16 id)
};

enum : U8 {
    RN_ERR_ILLEGAL_OP      = 0x00,
    RN_ERR_ILLEGAL_XC      = 0x01,
    RN_ERR_NO_ENTITY       = 0x02,
    RN_ERR_ILLEGAL_XC_ARG  = 0x03,
};

#define RN_R0 0x0
#define RN_R1 0x1
#define RN_R2 0x2
#define RN_R3 0x3
#define RN_R4 0x4
#define RN_R5 0x5
#define RN_R6 0x6
#define RN_R7 0x7
#define RN_R8 0x8
#define RN_R9 0x9
#define RN_Ra 0xa
#define RN_Rb 0xb
#define RN_Rc 0xc
#define RN_Rd 0xd
#define RN_Re 0xe
#define RN_Rf 0xf
#define RN_SP RN_Re
#define RN_CR RN_Rf

//@TODO static asserts (y < 256 etc)
#define RN_COPY( y, z) (U16)(0x0200 | (y << 4) | z)
#define RN_AND(  y, z) (U16)(0x0300 | (y << 4) | z)
#define RN_NOT(  y, z) (U16)(0x0400 | (y << 4) | z)
#define RN_OR(   y, z) (U16)(0x0500 | (y << 4) | z)
#define RN_XOR(  y, z) (U16)(0x0600 | (y << 4) | z)
#define RN_RSHF( y, z) (U16)(0x0700 | (y << 4) | z)
#define RN_LSHF( y, z) (U16)(0x0800 | (y << 4) | z)
#define RN_ADD(  y, z) (U16)(0x0900 | (y << 4) | z)
#define RN_SUB(  y, z) (U16)(0x0a00 | (y << 4) | z)
#define RN_MUL(  y, z) (U16)(0x0b00 | (y << 4) | z)
#define RN_DIV(  y, z) (U16)(0x0c00 | (y << 4) | z)
#define RN_MOD(  y, z) (U16)(0x0d00 | (y << 4) | z)
#define RN_LOAD( y, z) (U16)(0x0e00 | (y << 4) | z)
#define RN_SAVE( y, z) (U16)(0x0f00 | (y << 4) | z)
#define RN_PUSH( y   ) (U16)(0x1000 | (y << 4))
#define RN_POP(  y   ) (U16)(0x1100 | (y << 4))
#define RN_PUSHV(v   ) (U16)(0x1200 | v)
#define RN_XCALL(t   ) (U16)(0x6000 | t)
#define RN_LOADV(x, v) (U16)(0x7000 | (x << 8) | v)
#define RN_SAVEV(x, v) (U16)(0x8000 | (x << 8) | v)
#define RN_CONST(x, v) (U16)(0x9000 | (x << 8) | v)
#define RN_ADDV( x, v) (U16)(0xa000 | (x << 8) | v)
#define RN_JMP(  t   ) (U16)(0xb000 | t)
#define RN_JEZ(  t   ) (U16)(0xc000 | t)
#define RN_JNZ(  t   ) (U16)(0xd000 | t)
#define RN_JGZ(  t   ) (U16)(0xe000 | t)
#define RN_JLZ(  t   ) (U16)(0xf000 | t)

///macros
#define RN_SUBV (x, v) RN_ADDV(x, (0xff) - (v - 1))
#define RN_INCR (x)    RN_ADDV(x, 1)
#define RN_DECR (x)    RN_SUBV(x, 1)
#define RN_CMP  (x, y) RN_COPY(y, RN_CR), RN_SUB(x, RN_CR)
#define RN_JEQ  (t)    RN_JEZ(t)
#define RN_JNQ  (t)    RN_JNZ(t)
#define RN_JGT  (t)    RN_JLZ(t)
#define RN_JLT  (t)    RN_JGZ(t)
