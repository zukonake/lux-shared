# RaseN 8C6 (RN8C6)

## General
  * 8-bit word
  * little endian
  * 16 registers
  * 0xf - comparison register (cr)

## Instructions

```
00 .. ..... |
01 .. ..... |
02 yz copy  | z    =   y
03 yz and   | z   &=   y
04 yz not   | z    =  ~y
05 yz or    | z   |=   y
06 yz xor   | z   ^=   y
07 yz rshf  | z  <<=   y
08 yz lshf  | z  >>=   y
09 yz add   | z   +=   y
0a yz sub   | z   -=   y
0b yz mul   | z   *=   y
0c yz div   | z   /=   y
0d yz mod   | z   %=   y
0e yz load  | z    = m[y]
0f yz save  | m[y] =   z
10 y- push  | push(y)
11 y- pop   | y    = pop()
12 vv pushv | push(v)
1. .. ..... |
2. .. ..... |
3. .. ..... |
4. .. ..... |
5. .. ..... |
6t tt xcall | xcall(t)
7x vv loadv | x    = m[v]
8x vv savev | m[v] =   x
9x vv const | x    =   v
ax vv addv  | x   +=   v
bt tt jmp   | pc   =   t
ct tt jez   | if(cr == 0) pc = t
dt tt jnz   | if(cr != 0) pc = t
et tt jgz   | if(cr  > 0) pc = t
ft tt jlz   | if(cr  < 0) pc = t
```
