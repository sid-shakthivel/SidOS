; Exceptions
[GLOBAL irq_0_handler]
[GLOBAL irq_1_handler]
[GLOBAL irq_2_handler]
[GLOBAL irq_3_handler]
[GLOBAL irq_4_handler]
[GLOBAL irq_5_handler]
[GLOBAL irq_6_handler]
[GLOBAL irq_7_handler]
[GLOBAL irq_8_handler]
[GLOBAL irq_9_handler]
[GLOBAL irq_10_handler]
[GLOBAL irq_11_handler]
[GLOBAL irq_12_handler]
[GLOBAL irq_13_handler]
[GLOBAL irq_14_handler]
[GLOBAL irq_15_handler]
[GLOBAL irq_16_handler]
[GLOBAL irq_17_handler]
[GLOBAL irq_18_handler]
[GLOBAL irq_19_handler]
[GLOBAL irq_20_handler]
[GLOBAL irq_21_handler]
[GLOBAL irq_reserved_handler]

; Interrupts
[GLOBAL irq_32_handler]
[GLOBAL irq_33_handler]
[GLOBAL irq_34_handler]
[GLOBAL irq_35_handler]
[GLOBAL irq_36_handler]
[GLOBAL irq_37_handler]
[GLOBAL irq_38_handler]
[GLOBAL irq_39_handler]
[GLOBAL irq_40_handler]
[GLOBAL irq_41_handler]
[GLOBAL irq_42_handler]
[GLOBAL irq_43_handler]
[GLOBAL irq_44_handler]
[GLOBAL irq_45_handler]
[GLOBAL irq_46_handler]
[GLOBAL irq_47_handler]

%macro handle_generic_interrupt 1
    PUSH %1
    PUSHAD
    CLD
    extern on_generic_interrupt
    CALL on_generic_interrupt
    POPAD
    ADD ESP, 0x04
%endmacro

%macro handle_generic_exception 1
    PUSH %1
    PUSHAD
    CLD
    extern on_generic_exception
    CALL on_generic_exception
    POPAD
    ADD ESP, 0x04
%endmacro

irq_32_handler:
    CLD

    ;xchg bx, bx
    PUSHAD
    extern current_stack
    MOV [current_stack], ESP

    extern on_timer_interrupt
    CALL on_timer_interrupt

    extern next_stack
    MOV ESP, [next_stack]
    POPAD

    IRET

irq_0_handler:
    handle_generic_exception 0x00
    IRET

irq_1_handler:
    handle_generic_exception 0x01
    IRET

irq_2_handler:
    handle_generic_exception 0x02
    IRET

irq_3_handler:
    handle_generic_exception 0x03
    IRET

irq_4_handler:
    handle_generic_exception 0x04
    IRET

irq_5_handler:
    handle_generic_exception 0x05
    IRET

irq_6_handler:
    handle_generic_exception 0x06
    IRET

irq_7_handler:
    handle_generic_exception 0x07
    IRET

irq_8_handler:
    handle_generic_exception 0x08
    IRET

irq_9_handler:
    handle_generic_exception 0x09
    IRET

irq_10_handler:
    handle_generic_exception 0x0A
    IRET

irq_11_handler:
    handle_generic_exception 0x0B
    IRET

irq_12_handler:
    handle_generic_exception 0x0C
    IRET

irq_13_handler:
    handle_generic_exception 0x0D
    IRET

irq_14_handler:
    handle_generic_exception 0x0E
    IRET

irq_15_handler:
    handle_generic_exception 0x0F
    IRET

irq_16_handler:
    handle_generic_exception 0x10
    IRET

irq_17_handler:
    handle_generic_exception 0x11
    IRET

irq_18_handler:
    handle_generic_exception 0x12
    IRET

irq_19_handler:
    handle_generic_exception 0x13
    IRET

irq_20_handler:
    handle_generic_exception 0x14
    IRET

irq_21_handler:
    handle_generic_exception 0x15
    IRET

irq_reserved_handler:
    handle_generic_exception 0x16
    IRET

irq_33_handler:
    handle_generic_interrupt 0x21
    IRET
    
irq_34_handler:
    handle_generic_interrupt 0x22
    IRET

irq_35_handler:
    handle_generic_interrupt 0x23
    IRET

irq_36_handler:
    handle_generic_interrupt 0x24
    IRET

irq_37_handler:
    handle_generic_interrupt 0x25
    IRET

irq_38_handler:
    handle_generic_interrupt 0x26
    IRET

irq_39_handler:
    handle_generic_interrupt 0x27
    IRET

irq_40_handler:
    handle_generic_interrupt 0x28
    IRET

irq_41_handler:
    handle_generic_interrupt 0x29
    IRET

irq_42_handler:
    handle_generic_interrupt 0x2A
    IRET

irq_43_handler:
    handle_generic_interrupt 0x2B
    IRET

irq_44_handler:
    handle_generic_interrupt 0x2C
    IRET

irq_45_handler:
    handle_generic_interrupt 0x2D
    IRET

irq_46_handler:
    handle_generic_interrupt 0x2E
    IRET