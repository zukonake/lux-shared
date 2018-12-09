#include <cstring>
#include <lux_shared/common.hpp>

struct OpcodeDef {
    Str str;
    enum class Arg1 { X, Y, V, T, } arg1;
    enum class Arg2 { NONE, Z, V, } arg2;
    U16 val;
};

struct MacroDef {
    Str str;
    enum class Args { ZERO, ONE, TWO } args;
    Str val;
};

static OpcodeDef constexpr opcodes[] = {
    {"copy"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0200},
    {"and"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0300},
    {"not"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0400},
    {"or"_l   , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0500},
    {"xor"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0600},
    {"rshf"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0700},
    {"lshf"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0800},
    {"add"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0900},
    {"sub"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0a00},
    {"mul"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0b00},
    {"div"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0c00},
    {"mod"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0d00},
    {"load"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0e00},
    {"save"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::Z   , 0x0f00},
    {"push"_l , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::NONE, 0x1000},
    {"pop"_l  , OpcodeDef::Arg1::Y, OpcodeDef::Arg2::NONE, 0x1100},
    {"pushv"_l, OpcodeDef::Arg1::V, OpcodeDef::Arg2::NONE, 0x1200},
    {"xcall"_l, OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0x6000},
    {"loadv"_l, OpcodeDef::Arg1::X, OpcodeDef::Arg2::V   , 0x7000},
    {"savev"_l, OpcodeDef::Arg1::X, OpcodeDef::Arg2::V   , 0x8000},
    {"const"_l, OpcodeDef::Arg1::X, OpcodeDef::Arg2::V   , 0x9000},
    {"addv"_l , OpcodeDef::Arg1::X, OpcodeDef::Arg2::V   , 0xa000},
    {"jmp"_l  , OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0xb000},
    {"jez"_l  , OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0xc000},
    {"jnz"_l  , OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0xd000},
    {"jgz"_l  , OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0xe000},
    {"jlz"_l  , OpcodeDef::Arg1::T, OpcodeDef::Arg2::NONE, 0xf000},
};

static MacroDef constexpr macros[] = {
    //{"subv"_l, MacroDef::Args::TWO , "addv $0 (#ff $1 #1 - -)"_l},
    //{"incr"_l, MacroDef::Args::ONE , "addv $0 #1"_l},
    //{"decr"_l, MacroDef::Args::ONE , "subv $0 #1"_l},
    {"cmp"_l , MacroDef::Args::TWO , "copy $1 CR\n"_l
                                     "sub  $0 CR"_l},
    {"jeq"_l , MacroDef::Args::ONE , "jez  $0"_l},
    {"jnq"_l , MacroDef::Args::ONE , "jnz  $0"_l},
    {"jgq"_l , MacroDef::Args::ONE , "jlz  $0"_l},
    {"jlq"_l , MacroDef::Args::ONE , "jgz  $0"_l},
    {"nop"_l , MacroDef::Args::ZERO, "and  r0 r0"_l},
};

struct LabelRef {
    Str ident;
    U16 pos;
};

struct LabelDef {
    Str ident;
    Uns pos;
};

static DynArr<U16>      bytecode;
static DynArr<LabelRef> label_refs;
static DynArr<LabelDef> label_defs;

static void error_expected(Str const& x, Str const& got) {
    LUX_LOG_ERR("expected %.*s, got \"%.*s\"",
                (int)x.len, x.beg, (int)got.len, got.beg);
}

LUX_MAY_FAIL static try_parse_digit(U8* out, char ch) {
    if(ch >= '0' && ch <= '9') {
        *out = ch - '0';
    } else if(ch >= 'a' && ch <= 'f') {
        *out = (ch - 'a') + 10;
    } else {
        return LUX_FAIL;
    }
    return LUX_OK;
}

LUX_MAY_FAIL static parse_digit(U8* out, char ch) {
    LUX_RETHROW(try_parse_digit(out, ch),
        "expected hexadecimal digit, got \"%c\"", ch);
    return LUX_OK;
}

LUX_MAY_FAIL static parse_number(U8* out, Str str) {
    U8  digit = 0;
    Uns i     = 0;
    *out      = 0;
    while(i < str.len && try_parse_digit(&digit, str[i]) == LUX_OK) {
        *out *= 0x10;
        *out += digit;
        i++;
    }
    return LUX_OK;
}

void static skip_spaces(Str* out, Str in) {
    Uns i = 0;
    while(i < in.len && (in[i] == ' ' || in[i] == '\t')) i++;
    *out += i;
}

LUX_MAY_FAIL static _parse_expr(Deque<U8>* stack, Str str) {
    if(str.len == 0) return LUX_OK;
    skip_spaces(&str, str);
    if(str.len >= 2 && str[0] == '#') {
        stack->emplace_back();
        return parse_number(&stack->back(), str + 1);
    }
    LUX_UNIMPLEMENTED();
    /*if(str.len >= 2 && str[0] == '(' && str[str.len - 1] == ')') {
        str += 1;
        str.len -= 1;
        return _parse_expr(&stack, str);
    } 
    if(str.len >= 1)
        if(str[0] == '-') {
            if(stack->len < 2) {
                LUX_LOG_ERR("expected 2 stack elements, got %zu", stack->len);
                return LUX_FAIL;
            }
            U8 v1 = stack->back();
            stack->pop_back();
            U8 v2 = stack->back();
            stack->pop_back();
            stack->emplace(v2 - v1);
            return LUX_OK;
        }
        if(str[0] == '+') {
            if(stack->len < 2) {
                LUX_LOG_ERR("expected 2 stack elements, got %zu", stack->len);
                return LUX_FAIL;
            }
            U8 v1 = stack->back();
            stack->pop_back();
            U8 v2 = stack->back();
            stack->pop_back();
            stack->emplace(v2 + v1);
            return LUX_OK;
        }
    }*/
    LUX_LOG_ERR("unrecognized expression");
    return LUX_FAIL;
}

LUX_MAY_FAIL static parse_expr(U8* out, Str str) {
    static Deque<U8> stack;
    stack.clear();
    LUX_RETHROW(_parse_expr(&stack, str));
    if(stack.size() == 0) {
        LUX_LOG_ERR("expression stack empty, could not evaluate expression");
        return LUX_FAIL;
    }
    if(stack.size() > 1) {
        LUX_LOG_ERR("excess value(s) in expression stack");
        return LUX_FAIL;
    }
    *out = stack.back();
    return LUX_OK;
}

LUX_MAY_FAIL static assemble_arg(U8* out, Str str, U16 mask) {
    if(str.len == 0) {
        error_expected("argument"_l, str);
        return LUX_FAIL;
    }
    if(str[0] == 'r') {
        if(str.len != 2) {
            error_expected("register argument"_l, str);
            return LUX_FAIL;
        }
        LUX_RETHROW(parse_digit(out, str[1]));
    } else if(str[0] == '@') {
        if(mask != 0xfff) {
            LUX_LOG_ERR("invalid argument mask for label");
            return LUX_FAIL;
        }
        str.beg += 1;
        str.len -= 1;
        label_refs.push({str, (U16)(bytecode.len - 1)});
        *out = 0;
    } else if(str[0] == '#') {
        U8 expr;
        LUX_RETHROW(parse_expr(&expr, str),
                    "failed to parse expression");
        *out = expr;
    } else if(str[0] == '(' && str.len >= 3 && str[str.len - 1] == ')') {
        U8 expr;
        LUX_RETHROW(parse_expr(&expr, str),
                    "failed to parse expression");
        *out = expr;
    } else if(str[0] == 'C') {
        if(str.len != 2 || str[1] != 'R') {
            error_expected("comparison register"_l, str);
            return LUX_FAIL;
        }
        *out = 0xf;
    } else {
        error_expected("argument"_l, str);
        return LUX_FAIL;
    }
    return LUX_OK;
}

LUX_MAY_FAIL static parse_opcode(OpcodeDef const& def, Arr<Str, 2> const& args) {
    bytecode.emplace(def.val);
    auto& out = bytecode.last();
    out = def.val;
    U16 arg1;
    U16 arg1_mask;
    U16 arg1_shift;
    switch(def.arg1) {
        case OpcodeDef::Arg1::X: arg1_shift = 8; arg1_mask = 0xf;   break;
        case OpcodeDef::Arg1::Y: arg1_shift = 4; arg1_mask = 0xf;   break;
        case OpcodeDef::Arg1::V: arg1_shift = 0; arg1_mask = 0xff;  break;
        case OpcodeDef::Arg1::T: arg1_shift = 0; arg1_mask = 0xfff; break;
        default: LUX_UNREACHABLE();
    }
    LUX_RETHROW(assemble_arg((U8*)&arg1, args[0], arg1_mask),
                "failed to parse first argument");
    out |= arg1 << arg1_shift;
    if(def.arg2 != OpcodeDef::Arg2::NONE) {
        U16 arg2;
        U16 arg2_mask;
        switch(def.arg2) {
            case OpcodeDef::Arg2::Z: arg2_mask = 0xf;  break;
            case OpcodeDef::Arg2::V: arg2_mask = 0xff; break;
            default: LUX_UNREACHABLE();
        }
        LUX_RETHROW(assemble_arg((U8*)&arg2, args[1], arg2_mask),
                    "failed to parse second argument");
        out |= arg2;
    }
    return LUX_OK;
}

LUX_MAY_FAIL static parse_opcodes(Str const& in, Arr<Str, 2> const& args) {
    for(Uns j = 0; j < arr_len(opcodes); j++) {
        auto const& opcode = opcodes[j];
        if(in == opcode.str) {
            LUX_RETHROW(parse_opcode(opcode, args),
                        "failed to parse opcode \"%.*s %.*s %.*s\"",
                        (int)in.len, in.beg,
                        (int)args[0].len, args[0].beg,
                        (int)args[1].len, args[1].beg);
            return LUX_OK;
        }
    }
    return LUX_FAIL;
}

LUX_MAY_FAIL static rasm_str(Str const& in);

LUX_MAY_FAIL static parse_macro(MacroDef const& def, Arr<Str, 2> const& args) {
    MacroDef::Args args_num =
        args[0].len == 0 ? MacroDef::Args::ZERO :
        args[1].len == 0 ? MacroDef::Args::ONE  : MacroDef::Args::TWO;
    if(def.args != args_num) {
        //@TODO more info?
        LUX_LOG_ERR("unexpected number of arguments");
        return LUX_FAIL;
    }
    struct Subst {
        U16 pos;
        Uns arg;
    };
    DynArr<Subst> substs;
    Uns buff_len = def.val.len;
    Arr<Arr<char, 2>, 2> s_args;
    for(Uns j = 0; j < 2; j++) {
        s_args[j][0] = '$';
        s_args[j][1] = (char)(j + '0');
    }
    for(Uns i = 0; i < def.val.len; i++) {
        for(Uns j = 0; j < 2; j++) {
            ///not possible for a s_arg to exist
            SizeT s_len = arr_len(s_args[j]);
            if(def.val.len - i < s_len) break;
            if(Str(s_args[j], s_len) == Str(def.val.beg + i, s_len)) {
                buff_len -= s_len;
                buff_len += args[j].len;
                substs.push({(U16)(substs.len == 0 ? i :
                                   i - substs.last().pos - s_len), j});
            }
        }
    }
    DynArr<char> buff(buff_len);
    Uns b = 0;
    Uns s = 0;
    for(Uns i = 0; i < substs.len; i++) {
        std::memcpy(buff.beg + b, def.val.beg + s, substs[i].pos);
        b += substs[i].pos;
        s += substs[i].pos;
        LUX_ASSERT(substs[i].arg < arr_len(args));
        auto const& arg = args[substs[i].arg];
        std::memcpy(buff.beg + b, arg.beg, arg.len);
        b += arg.len;
        s += arr_len(s_args[substs[i].arg]);
    }
    std::memcpy(buff.beg + b, def.val.beg + s, def.val.len - s);
    return rasm_str((Str)buff);
}

LUX_MAY_FAIL static parse_macros(Str const& in, Arr<Str, 2> const& args) {
    for(Uns j = 0; j < arr_len(macros); j++) {
        auto const& macro = macros[j];
        if(in == macro.str) {
            LUX_RETHROW(parse_macro(macro, args));
            return LUX_OK;
        }
    }
    return LUX_FAIL;
}

LUX_MAY_FAIL static parse_arg(Str* remaining, Str* arg, Str in) {
    *remaining = in;
    *arg = in;
    Uns i = 0;
    bool parens = false;
    while(i < in.len && (in[i] != ' ' || parens)) {
             if(in[i] == '(') parens = true;
        else if(in[i] == ')') parens = false;
        i++;
    }
    if(parens) {
        LUX_LOG_ERR("unterminated parens");
        return LUX_FAIL;
    }
    arg->len = i;
    *remaining += arg->len;
    return LUX_OK;
}

LUX_MAY_FAIL static parse_line(Str* remaining, Str str) {
    //@CONSIDER doing it in one run, instead of finding newline first etc.
    *remaining = str;
    ///find line length
    Uns line_end = 0;
    {   Uns i = 0;
        while(i < str.len && str[i] != '\n') i++;
        line_end = i;
        str.len = line_end;
        *remaining += str.len;
    }
    /// skip comments
    {   Uns i = 0;
        while(i < str.len && str[i] != ';') i++;
        str.len = i;
    }
    if(str.len == 0) return LUX_OK;
    ///skip prefix whitespaces
    {   Uns i = 0;
        while(i < str.len && (str[i] == ' ' || str[i] == '\t')) i++;
        str += i;
    }
    Str op = str;
    ///find last non-space char, now we have the opcode
    {   Uns i = 0;
        while(i < str.len && str[i] != ' ') i++;
        op.len = i;
    }
    if(op.len == 0) return LUX_OK;
    if(op[0] == '@') {
        if(op.len <= 1) {
            error_expected("label definition"_l, op);
            return LUX_FAIL;
        }
        op += 1;
        label_defs.push({op, bytecode.len});
        return LUX_OK;
    } else {
        str += op.len;
        skip_spaces(&str, str);
        Str arg1;
        LUX_RETHROW(parse_arg(&str, &arg1, str),
                    "failed to parse first argument");
        skip_spaces(&str, str);
        Str arg2;
        LUX_RETHROW(parse_arg(&str, &arg2, str),
                    "failed to parse second argument");
        return (LuxRval)(parse_opcodes(op, {arg1, arg2}) ||
                         parse_macros( op, {arg1, arg2}));
    }
}

LUX_MAY_FAIL static rasm_str(Str const& in) {
    Str remaining = in;
    Uns line_num  = 1;
    while(remaining.len > 0) {
        ///we skip the newline from previous iteration
        if(remaining.beg[0] == '\n') {
            if(remaining.len > 1) {
                remaining.len -= 1;
                remaining.beg += 1;
            } else break;
        }
        LUX_RETHROW(parse_line(&remaining, remaining),
                    "assembly failed at line %zu", line_num);
        line_num++;
    }
    return LUX_OK;
}

LUX_MAY_FAIL rasm(DynArr<U16>** out, Str const& in) {
    bytecode.clear();
    LUX_RETHROW(rasm_str(in));
    for(Uns i = 0; i < label_refs.len; i++) {
        bool found = false;
        for(Uns j = 0; j < label_defs.len; j++) {
            if(label_defs[j].ident == label_refs[i].ident) {
                LUX_ASSERT(label_refs[i].pos < bytecode.len);
                bytecode[label_refs[i].pos] |= label_defs[j].pos;
                found = true;
                break;
            }
        }
        if(!found) {
            auto const& ident = label_refs[i].ident;
            LUX_LOG_ERR("undefined label \"%.*s\"", (int)ident.len, ident.beg);
            return LUX_FAIL;
        }
    }
    *out = &bytecode;
    return LUX_OK;
}

