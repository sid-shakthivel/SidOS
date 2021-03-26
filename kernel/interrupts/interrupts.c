#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/keyboard.h"
#include "../include/pic.h"

char *exceptions[31] = {"One Cannot Divide 0 By 0\n", "Single-step interrupt\n", "NMI\n", "Breakpoint\n", "Overflow\n", "Bounds\n", "Invalid Opcode\n", "Coprocessor Not Available\n", "Double Fault\n", "Coprocessor Segment Overrun\n", "Invalid Task State Segment\n", "Segment Not Present\n", "Stack Fault\n", "General Protection Fault\n", "Page fault\n", "Reserved\n", "Math Fault\n", "Alignment Check\n", "Machine Check\n", "SIMD Floating-Point Exception\n", "Virtualisation Exception\n", "Control Protection Exception\n"};

struct registers_t
{
    uint32_t EDI;
    uint32_t ESI;
    uint32_t EBP;
    uint32_t ESP;
    uint32_t EBX;
    uint32_t EDX;
    uint32_t ECX;
    uint32_t EAX;
};

typedef struct register_t registers;

void print_registers(struct registers_t registers)
{
    printf("Registers: ");
    printf("%x\n", registers.EDI);
    printf("%x\n", registers.ESI);
    printf("%x\n", registers.EBP);
    printf("%x\n", registers.ESP);
    printf("%x\n", registers.EBX);
    printf("%x\n", registers.EDX);
    printf("%x\n", registers.ECX);
    printf("%x\n", registers.EAX);
}

void on_generic_exception(struct registers_t registers, unsigned int irq_number)
{
    irq_number > 0x15 ? printf("Intel Reserved\n") : printf(exceptions[irq_number]);
    // print_registers(registers);
}

void on_generic_interrupt(struct registers_t registers, unsigned int irq_number)
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