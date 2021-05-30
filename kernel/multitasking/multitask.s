[GLOBAL save_stack]

save_stack:
    MOV EAX, ESP
    extern stack_one
    ;xchg bx, bx
    MOV ESP, [stack_one]
    PUSH 0
    PUSH 0x10
    PUSH stack_one
    PUSH 0x202
    PUSH 0x08
    PUSH 0x100F30
    PUSHAD
    MOV ESP, EAX
    RET
