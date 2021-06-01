#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/idt.h"
#include "../include/uart.h"
#include "../include/vga_text.h"
#include "../include/io.h"
#include "../include/pic.h"

extern void setIdt(uint32_t offset, uint16_t size);

extern void ExceptionHandler0();
extern void ExceptionHandler1();
extern void ExceptionHandler2();
extern void ExceptionHandler3();
extern void ExceptionHandler4();
extern void ExceptionHandler5();
extern void ExceptionHandler6();
extern void ExceptionHandler7();
extern void ExceptionHandler8();
extern void ExceptionHandler9();
extern void ExceptionHandler10();
extern void ExceptionHandler11();
extern void ExceptionHandler12();
extern void ExceptionHandler13();
extern void ExceptionHandler14();
extern void ExceptionHandler15();
extern void ExceptionHandler16();
extern void ExceptionHandler17();
extern void ExceptionHandler18();
extern void ExceptionHandler19();
extern void ExceptionHandler20();
extern void ExceptionHandler21();

extern void ExceptionHandler22();

extern void InterruptHandler32();
extern void InterruptHandler33();
extern void InterruptHandler34();
extern void InterruptHandler35();
extern void InterruptHandler36();
extern void InterruptHandler37();
extern void InterruptHandler38();
extern void InterruptHandler39();
extern void InterruptHandler40();
extern void InterruptHandler41();
extern void InterruptHandler42();
extern void InterruptHandler43();
extern void InterruptHandler44();
extern void InterruptHandler45();
extern void InterruptHandler46();

typedef struct IDT_Descriptor
{
    uint16_t lower_offset;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t higher_offset;
} idt_descriptor;

idt_descriptor idt[256];

void set_idt_descriptor(uint32_t num, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    idt[num].lower_offset = 0x0000FFFF & offset; // 0 - 15
    idt[num].selector = selector;
    idt[num].zero = 0xFFFFFFFF & 0;
    idt[num].type_attr = type_attr;
    idt[num].higher_offset = 0xFFFF & (offset >> 16); // 16 - 31
}

void initialize_idt(void)
{
    // Exceptions
    set_idt_descriptor(0x00, (uint32_t)ExceptionHandler0, 0x08, 0b11101111);
    set_idt_descriptor(0x01, (uint32_t)ExceptionHandler1, 0x08, 0b11101111);
    set_idt_descriptor(0x02, (uint32_t)ExceptionHandler2, 0x08, 0b11101111);
    set_idt_descriptor(0x03, (uint32_t)ExceptionHandler3, 0x08, 0b11101111);
    set_idt_descriptor(0x04, (uint32_t)ExceptionHandler4, 0x08, 0b11101111);
    set_idt_descriptor(0x05, (uint32_t)ExceptionHandler5, 0x08, 0b11101111);
    set_idt_descriptor(0x06, (uint32_t)ExceptionHandler6, 0x08, 0b11101111);
    set_idt_descriptor(0x07, (uint32_t)ExceptionHandler7, 0x08, 0b11101111);
    set_idt_descriptor(0x08, (uint32_t)ExceptionHandler8, 0x08, 0b11101111);
    set_idt_descriptor(0x09, (uint32_t)ExceptionHandler9, 0x08, 0b11101111);
    set_idt_descriptor(0x0A, (uint32_t)ExceptionHandler10, 0x08, 0b11101111);
    set_idt_descriptor(0x0C, (uint32_t)ExceptionHandler11, 0x08, 0b11101111);
    set_idt_descriptor(0x0D, (uint32_t)ExceptionHandler12, 0x08, 0b11101111);
    set_idt_descriptor(0x0B, (uint32_t)ExceptionHandler13, 0x08, 0b11101111);
    set_idt_descriptor(0x0E, (uint32_t)ExceptionHandler14, 0x08, 0b11101111);
    set_idt_descriptor(0x0F, (uint32_t)ExceptionHandler15, 0x08, 0b11101111);
    set_idt_descriptor(0x10, (uint32_t)ExceptionHandler16, 0x08, 0b11101111);
    set_idt_descriptor(0x11, (uint32_t)ExceptionHandler17, 0x08, 0b11101111);
    set_idt_descriptor(0x12, (uint32_t)ExceptionHandler18, 0x08, 0b11101111);
    set_idt_descriptor(0x13, (uint32_t)ExceptionHandler19, 0x08, 0b11101111);
    set_idt_descriptor(0x14, (uint32_t)ExceptionHandler20, 0x08, 0b11101111);
    set_idt_descriptor(0x15, (uint32_t)ExceptionHandler21, 0x08, 0b11101111);

	// Reserved
    set_idt_descriptor(0x16, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x17, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x18, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x19, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1A, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1B, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1C, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1D, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1E, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);
    set_idt_descriptor(0x1F, (uint32_t)ExceptionHandler22, 0x08, 0b11101111);

    // User Defined Interrupts (PIC)
    set_idt_descriptor(0x20, (uint32_t)InterruptHandler32, 0x08, 0b11101110);
    set_idt_descriptor(0x21, (uint32_t)InterruptHandler33, 0x08, 0b11101110);
    set_idt_descriptor(0x22, (uint32_t)InterruptHandler34, 0x08, 0b11101110);
    set_idt_descriptor(0x23, (uint32_t)InterruptHandler35, 0x08, 0b11101110);
    set_idt_descriptor(0x24, (uint32_t)InterruptHandler36, 0x08, 0b11101110);
    set_idt_descriptor(0x25, (uint32_t)InterruptHandler37, 0x08, 0b11101110);
    set_idt_descriptor(0x26, (uint32_t)InterruptHandler38, 0x08, 0b11101110);
    set_idt_descriptor(0x27, (uint32_t)InterruptHandler39, 0x08, 0b11101110);
    set_idt_descriptor(0x28, (uint32_t)InterruptHandler40, 0x08, 0b11101110);
    set_idt_descriptor(0x29, (uint32_t)InterruptHandler41, 0x08, 0b11101110);
    set_idt_descriptor(0x2B, (uint32_t)InterruptHandler42, 0x08, 0b11101110);
    set_idt_descriptor(0x2C, (uint32_t)InterruptHandler43, 0x08, 0b11101110);
    set_idt_descriptor(0x2A, (uint32_t)InterruptHandler44, 0x08, 0b11101110);
    set_idt_descriptor(0x2D, (uint32_t)InterruptHandler45, 0x08, 0b11101110);
    set_idt_descriptor(0x2E, (uint32_t)InterruptHandler46, 0x08, 0b11101110);

    setIdt((uint32_t)&idt, sizeof(idt_descriptor) * 256 - 1);
}