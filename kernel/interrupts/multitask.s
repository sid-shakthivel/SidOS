[GLOBAL test]

test:
    MOV EAX, [ESP + 4]
    MOV EDX, EAX
    RET