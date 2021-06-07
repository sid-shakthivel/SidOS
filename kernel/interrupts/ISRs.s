%macro fnHandleInterrupt 1
global fnInterruptHandler%1
fnInterruptHandler%1:
    PUSH %1
    PUSHAD
    CLD
    extern fnOnGenericInterrupt
    CALL fnOnGenericInterrupt
    POPAD
    ADD ESP, 0x04
    IRET
%endmacro

%macro fnHandleException 1
global fnExceptionHandler%1
fnExceptionHandler%1:
    PUSH %1
    PUSHAD
    CLD
    extern fnOnGenericException
    CALL fnOnGenericException
    POPAD
    ADD ESP, 0x04
    IRET
%endmacro



; Exceptioms
fnHandleException 0
fnHandleException 1
fnHandleException 2
fnHandleException 3
fnHandleException 4
fnHandleException 5
fnHandleException 6
fnHandleException 7
fnHandleException 8
fnHandleException 9
fnHandleException 10
fnHandleException 11
fnHandleException 12
fnHandleException 13
fnHandleException 14
fnHandleException 15
fnHandleException 16
fnHandleException 17
fnHandleException 18
fnHandleException 19
fnHandleException 20
fnHandleException 21

; Reserved
fnHandleException 22

; Timer
global fnInterruptHandler32
fnInterruptHandler32:
    CLD
    PUSHAD
    extern pSavedStack
    MOV [pSavedStack], ESP
    ;xchg bx, bx
    extern fnOnTimerInterrupt
    CALL fnOnTimerInterrupt
    ;xchg bx, bx
    extern pNextStack
    MOV ESP, [pNextStack]
    POPAD
    IRET

; Interrupts
fnHandleInterrupt 33
fnHandleInterrupt 34
fnHandleInterrupt 35
fnHandleInterrupt 36
fnHandleInterrupt 37
fnHandleInterrupt 38
fnHandleInterrupt 39
fnHandleInterrupt 40
fnHandleInterrupt 41
fnHandleInterrupt 42
fnHandleInterrupt 43
fnHandleInterrupt 44
fnHandleInterrupt 45
fnHandleInterrupt 46
