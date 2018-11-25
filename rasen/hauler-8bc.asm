;it carries items back and forth for now

.entry
alias r0 ix
alias r1 iy
alias r2 tx
alias r3 ty
const 16 ix
const -3 iy
const 10 tx
const  2 ty
xcall 'pickup'
.xloop
cmp  ix tx
jlt  .xlt
jgt  .xgt
jeq  .xend
.xlt
inc  ix
pushv 'dir_px'
jmp .xbreak
.xgt
dec  ix
pushv 'dir_nx'
.xbreak
xcall 'sc_move'
jmpv .xloop
.xend
.yloop
cmp  iy ty
jlt  .ylt
jgt  .ygt
jeq  .yend
.ylt
inc  iy
pushv 'dir_py'
jmp .ybreak
.ygt
dec  iy
pushv 'dir_ny'
.ybreak
xcall 'sc_move'
jmpv .yloop
.yend
xcall 'drop'
