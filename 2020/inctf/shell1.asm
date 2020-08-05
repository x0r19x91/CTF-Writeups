; shell1
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
next:   call here
        nop
        nop
here:   pop rax
        mov byte [rax-5], 0xc3
        nop
        nop
        nop
        nop
        nop
        jmp next
