# RaseN 8BC (RN8BC)

## General
  * 8-bit word
  * little endian
  * 16 registers
  * 0xe - stack pointer (sp)
  * 0xf - comparison register (cr)

## Instructions

```
00 .. .....
01 .. .....
02 yz copy
03 yz and
04 yz not
05 yz or
06 yz xor
07 yz rshf
08 yz lshf
09 yz add
0a yz sub
0b yz mul
0c yz div
0d yz mod
0e yz load
0f yz save
10 y- push
11 y- pop
12 vv pushv
1. .. .....
2. .. .....
3. .. .....
4. .. .....
5. .. .....
6t tt xcall
7x vv loadv
8x vv savev
9x vv const
ax vv addv
bt tt jmp
ct tt jez
dt tt jnz
et tt jgz
ft tt jlz
```

macros
```
subv  rx #v
incr  rx
decr  rx
cmp   rx ry
jeq   #t
jnq   #t
jgt   #t
jlt   #t
pushd Ry
popd  Ry
```
