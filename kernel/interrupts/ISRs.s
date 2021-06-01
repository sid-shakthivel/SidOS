%macro handle_interrupt 1
global InterruptHandler%1
InterruptHandler%1:
    PUSH %1
    PUSHAD
    CLD
    extern on_generic_interrupt
    CALL on_generic_interrupt
    POPAD
    ADD ESP, 0x04
    IRET
%endmacro

%macro exception_handler 1
global ExceptionHandler%1
ExceptionHandler%1:
    PUSH %1
    PUSHAD
    CLD
    extern on_generic_exception
    CALL on_generic_exception
    POPAD
    ADD ESP, 0x04
    IRET
%endmacro

; Exceptioms
exception_handler 0
exception_handler 1
exception_handler 2
exception_handler 3
exception_handler 4
exception_handler 5
exception_handler 6
exception_handler 7
exception_handler 8
exception_handler 9
exception_handler 10
exception_handler 11
exception_handler 12
exception_handler 13
exception_handler 14
exception_handler 15
exception_handler 16
exception_handler 17
exception_handler 18
exception_handler 19
exception_handler 20
exception_handler 21

; Reserved
exception_handler 22

; Timer
global InterruptHandler32
InterruptHandler32:
    CLD
    PUSHAD
    extern current_stack
    MOV [current_stack], ESP
    extern on_timer_interrupt
    CALL on_timer_interrupt
    extern next_stack
    MOV ESP, [next_stack]
    POPAD
    IRET

; Interrupts
handle_interrupt 33
handle_interrupt 34
handle_interrupt 35
handle_interrupt 36
handle_interrupt 37
handle_interrupt 38
handle_interrupt 39
handle_interrupt 40
handle_interrupt 41
handle_interrupt 42
handle_interrupt 43
handle_interrupt 44
handle_interrupt 45
handle_interrupt 46
