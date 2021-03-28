#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/keyboard.h"
#include "../include/pic.h"

char *exceptions[31] = {"One Cannot Divide 0 By 0\n", "Single-step interrupt\n", "NMI\n", "Breakpoint\n", "Overflow\n", "Bounds\n", "Invalid Opcode IDIOT\n", "Coprocessor Not Available\n", "Double Fault\n", "Coprocessor Segment Overrun\n", "Invalid Task State Segment\n", "Segment Not Present\n", "Stack Fault\n", "General Protection Fault\n", "Page fault\n", "Reserved\n", "Math Fault\n", "Alignment Check\n", "Machine Check\n", "SIMD Floating-Point Exception\n", "Virtualisation Exception\n", "Control Protection Exception\n"};
typedef struct Registers
{
    uint32_t EDI;
    uint32_t ESI;
    uint32_t EBP;
    uint32_t ESP;
    uint32_t EBX;
    uint32_t EDX;
    uint32_t ECX;
    uint32_t EAX;
} registers;

void print_registers(registers registers_t)
{
    printf("Registers:\n");
    printf("%x\n", registers_t.EDI);
    printf("%x\n", registers_t.ESI);
    printf("%x\n", registers_t.EBP);
    printf("%x\n", registers_t.ESP);
    printf("%x\n", registers_t.EBX);
    printf("%x\n", registers_t.EDX);
    printf("%x\n", registers_t.ECX);
    printf("%x\n", registers_t.EAX);
}

void on_generic_exception(registers registers_t, size_t irq_number)
{
    irq_number > 0x15 ? printf("Intel Reserved\n") : printf(exceptions[irq_number]);
    // print_registers(registers_t);
}

void on_generic_interrupt(registers registers_t, size_t irq_number)
{
    switch (irq_number)
    {
    case 0x21:
        on_keyboard_interrupt();
        break;
    default:
        printf("Unknown Interrupt\n");
        break;
    }

    // print_registers(registers);

    send_PIC_acknowledgment(irq_number);
}