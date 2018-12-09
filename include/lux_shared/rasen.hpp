#pragma once

#include <lux_shared/common.hpp>

enum : U8 {
    RN_SC_HALT,  //void halt(void)
    RN_SC_ERR,   //void err(U8 code)
    RN_SC_PRINT, //void print(U8 num)
};

enum : U8 {
    RN_SC_ERR_ILLEGAL_OP     = 0x00,
    RN_SC_ERR_ILLEGAL_SC     = 0x01,
    RN_SC_ERR_ILLEGAL_SC_ARG = 0x02,
    RN_SC_ERR_ILLEGAL_CALL   = 0x02,
};

LUX_MAY_FAIL rasm(DynArr<U16>** out, Str const& in);
