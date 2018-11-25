# RaseN 8BB (RN8BB)

## General
  * 16-bit word
  * little endian

## Instructions

```
00 xcll(-ext)           +?
01 icll(-int)           +?
02 load(-addr)          +1
03 save(-target, -addr) +0
04 and(-a, -b)          +1
05 not(-a)              +1
06 or(-a, -b)           +1
07 xor(-a, -b)          +1
08 rshf(-a, -b)         +1
09 lshf(-a, -b)         +1
0a add(-a, -b)          +1
0b sub(-a, -b)          +1
0c mul(-a, -b)          +1
0d div(-a, -b)          +1
0e mod(-a, -b)          +1
0f del(-a)              +0
10 dupl(a)              +1
11 take(-a)             +1
12 inc(-a)              +1
13 dec(-a)              +1
14 jmp(-a)              +0
15 jmpr(-a)             +0
16 jeq(?addr, ?a, ?b)   +0
17 jnq(?addr, ?a, ?b)   +0
18 jlt(?addr, ?a, ?b)   +0
19 jgt(?addr, ?a, ?b)   +0
1a swp(-a, -b)          +2
..
..
..
..
..
..
```
