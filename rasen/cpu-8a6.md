# RaseN 8A6 (RN8A6)

## General
  * 8-bit word
  * 16 8-bit accessible registers
    * `A0` - `A7` (0 - 7)
    * `B0` - `B4` (8 - C)
    * `CR`        (D)      CMP result
    * `PC`        (E)      program counter
    * `SP`        (F)      stack pointer
  * little endian

## Memory

256B stack - s
256B rom   - o
256B ram   - m

## Instructions

```
00 EE CALL
10 YZ COPY
11 YZ LOAD
12 YZ SAVE
13 YZ CMP 
14 YZ CMPS
15 YZ AND 
15 YZ NOT 
17 YZ OR 
18 YZ XOR 
19 YZ RSHF
1a YZ LSHF
1b YZ ADD
1c YZ SUB
1d YZ MUL
1e YZ DIV
1f YZ MOD
2X 00 PUSH 
3X 00 POP 
4X 00 INC 
5X 00 DEC 
6X EE LDRO
EX EE VAL
F0 EE JMPV
```
