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
