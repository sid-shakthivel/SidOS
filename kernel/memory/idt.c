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

extern void irq_0_handler();
extern void irq_1_handler();
extern void irq_2_handler();
extern void irq_3_handler();
extern void irq_4_handler();
extern void irq_5_handler();
extern void irq_6_handler();
extern void irq_7_handler();
extern void irq_8_handler();
extern void irq_9_handler();
extern void irq_10_handler();
extern void irq_11_handler();
extern void irq_12_handler();
extern void irq_13_handler();
extern void irq_14_handler();
extern void irq_15_handler();
extern void irq_16_handler();
extern void irq_17_handler();
extern void irq_18_handler();
extern void irq_19_handler();
extern void irq_20_handler();
extern void irq_21_handler();
extern void irq_reserved_handler();

extern void irq_32_handler();
extern void irq_33_handler();
extern void irq_34_handler();
extern void irq_35_handler();
extern void irq_36_handler();
extern void irq_37_handler();
extern void irq_38_handler();
extern void irq_39_handler();
extern void irq_40_handler();
extern void irq_41_handler();
extern void irq_42_handler();
extern void irq_43_handler();
extern void irq_44_handler();
extern void irq_45_handler();
extern void irq_46_handler();

struct idt_descriptor
{
    uint16_t lower_offset;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t higher_offset;
};

struct idt_descriptor idt[256];

void set_idt_descriptor(uint32_t num, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    idt[num].lower_offset = 0x0000FFFF & offset; // 0 - 15
    idt[num].selector = selector;
    idt[num].zero = 0xFFFFFFFF & 0;
    idt[num].type_attr = type_attr;
    idt[num].higher_offset = 0xFFFF & (offset >> 16); // 16 - 31
}

void initialize_idt()
{
    // Exceptions
    set_idt_descriptor(0x00, (uint32_t)irq_0_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x01, (uint32_t)irq_1_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x02, (uint32_t)irq_2_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x03, (uint32_t)irq_3_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x04, (uint32_t)irq_4_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x05, (uint32_t)irq_5_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x06, (uint32_t)irq_6_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x07, (uint32_t)irq_7_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x08, (uint32_t)irq_8_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x09, (uint32_t)irq_9_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0A, (uint32_t)irq_10_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0B, (uint32_t)irq_11_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0C, (uint32_t)irq_12_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0D, (uint32_t)irq_13_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0E, (uint32_t)irq_14_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x0F, (uint32_t)irq_15_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x10, (uint32_t)irq_16_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x11, (uint32_t)irq_17_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x12, (uint32_t)irq_18_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x13, (uint32_t)irq_19_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x14, (uint32_t)irq_20_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x15, (uint32_t)irq_21_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x16, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x17, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x18, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x19, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1A, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1B, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1C, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1D, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1E, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);
    set_idt_descriptor(0x1F, (uint32_t)irq_reserved_handler, 0x08, 0b11101111);

    // User Defined Interrupts (PIC)
    set_idt_descriptor(0x20, (uint32_t)irq_32_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x21, (uint32_t)irq_33_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x22, (uint32_t)irq_34_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x23, (uint32_t)irq_35_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x24, (uint32_t)irq_36_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x25, (uint32_t)irq_37_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x26, (uint32_t)irq_38_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x27, (uint32_t)irq_39_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x28, (uint32_t)irq_40_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x29, (uint32_t)irq_41_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x2A, (uint32_t)irq_42_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x2B, (uint32_t)irq_43_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x2C, (uint32_t)irq_44_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x2D, (uint32_t)irq_45_handler, 0x08, 0b11101110);
    set_idt_descriptor(0x2E, (uint32_t)irq_46_handler, 0x08, 0b11101110);

    setIdt((uint32_t)&idt, sizeof(struct idt_descriptor) * 256 - 1);
}