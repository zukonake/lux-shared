.entry
call 'sc_rand'
pop  r0
ldro r1 .data+0
mod  r1 r0
ldro r1 .data+1
mul  r1 r0
jmpr r0
val  r0 'dir_up'    ;0
jmpv .break
val  r0 'dir_right' ;4
jmpv .break
val  r0 'dir_down'  ;8
jmpv .break
val  r0 'dir_left'  ;12
.break
push r0
push r0
call 'sc_check_dir'
pop  r0
ldro r1 .data+2
cmp  r0 r1
jmpr cr
jmpv .nomove   ;eq
nop            ;lt
call 'sc_move' ;gt
.nomove
jmpv .entry
.data
0x4
0x4
0x1
