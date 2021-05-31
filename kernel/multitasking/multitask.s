[GLOBAL save_stack]
[GLOBAL stack_stuff]

save_stack:
    PUSH EBP
    MOV EBP, ESP
    MOV ESP, EBP
    POP EBP
    RET

stack_stuff:
    xchg bx, bx
    PUSHAD
    RET
