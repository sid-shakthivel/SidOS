idt DW 0
    DD 0

GLOBAL fnSetIDT
fnSetIDT:
    MOV EAX, [esp + 4]
    MOV [idt + 2], EAX
    MOV AX, [esp + 8]
    MOV [idt], AX
    LIDT [idt]
    RET