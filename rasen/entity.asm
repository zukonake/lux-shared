#import 'entity'

#export 'move'
    pop   CR ;forward
    jez @back
    const CR #ff
    @back
    pushv #0
    push  CR
    xcall 'entity_raw_add_vel'
#export_end

#export 'rotate'
    pop   CR ;rightward
    jez @back
    const CR #ff
    @back
    push  CR
    xcall 'entity_raw_add_rotation'
#export_end
