;it carries items back and forth for now

.entry
alias r0 ix
alias r1 iy
alias r2 tx
alias r3 ty
ldro ix .data+0
ldro iy .data+1
ldro tx .data+3
ldro ty .data+4
alias r4 jmul
alias r5 dir
ldro jmul .data+5
.loop
call 'pickup'
.loopx
cmps ix tx
mul  jmul cr
jmpr cr
jmpv .endx ;0 eq
nop
nop
inc  ix    ;6 lt
val  dir 'dir_px'
jmpv .break
dec  ix    ;12 gt
val  dir 'dir_nx'
.break
push dir 
call 'sc_move'
jmpv .loopx
.endx
.loopx
cmps iy ty
mul  jmul cr
jmpr cr
jmpv .endy ;0 eq
nop
nop
inc  iy    ;6 lt
val  dir 'dir_py'
jmpv .break
dec  iy    ;12 gt
val  dir 'dir_ny'
.break
push dir 
call 'sc_move'
jmpv .loopy
.endy
call 'drop'
ldro tx .data+0
ldro ty .data+1
jmpv .loop
.data
-16, -2 ;from x y
10, 3   ;to   x y
0x6
