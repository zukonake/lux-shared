@entry
 3, -2 ;ty iy
10,-16 ;tx ix

'pickup' xcll

@xloop
.xnq jnq
    .xend jmp
@xnq
.xgt jgt
    inc
    'dir_px'
    .xlt jmp
@xgt
.xlt jlt
    dec
    'dir_nx'
@xlt
'xc_move' xcll
@xend
del del ;ty iy
@yloop
.ynq jnq
    .yend jmp
@ynq
.ygt jgt
    inc
    'dir_py'
    .ylt jmp
@ygt
.ylt jlt
    dec
    'dir_ny'
@ylt
'xc_move' xcll
@yend
del del
'drop' xcll
