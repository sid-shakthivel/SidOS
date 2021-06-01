#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/idt.h"
#include "../include/uart.h"
#include "../include/vga_text.h"
#include "../include/io.h"
#include "../include/pic.h"

extern void fnSetIDT(uint32_t u32Offset, uint16_t u16Size);

extern void fnExceptionHandler0();
extern void fnExceptionHandler1();
extern void fnExceptionHandler2();
extern void fnExceptionHandler3();
extern void fnExceptionHandler4();
extern void fnExceptionHandler5();
extern void fnExceptionHandler6();
extern void fnExceptionHandler7();
extern void fnExceptionHandler8();
extern void fnExceptionHandler9();
extern void fnExceptionHandler10();
extern void fnExceptionHandler11();
extern void fnExceptionHandler12();
extern void fnExceptionHandler13();
extern void fnExceptionHandler14();
extern void fnExceptionHandler15();
extern void fnExceptionHandler16();
extern void fnExceptionHandler17();
extern void fnExceptionHandler18();
extern void fnExceptionHandler19();
extern void fnExceptionHandler20();
extern void fnExceptionHandler21();

extern void fnExceptionHandler22();

extern void fnInterruptHandler32();
extern void fnInterruptHandler33();
extern void fnInterruptHandler34();
extern void fnInterruptHandler35();
extern void fnInterruptHandler36();
extern void fnInterruptHandler37();
extern void fnInterruptHandler38();
extern void fnInterruptHandler39();
extern void fnInterruptHandler40();
extern void fnInterruptHandler41();
extern void fnInterruptHandler42();
extern void fnInterruptHandler43();
extern void fnInterruptHandler44();
extern void fnInterruptHandler45();
extern void fnInterruptHandler46();

SIDT_Descriptor rgIDT[256];

void fnSetIDTEntry(uint32_t u32Num, uint32_t u32Offset, uint16_t u16Selector, uint8_t u8TypeAttribute)
{
    rgIDT[u32Num].u16LowerOffset = 0x0000FFFF & u32Offset; // 0 - 15
    rgIDT[u32Num].u16Selector = u16Selector;
    rgIDT[u32Num].u8Zero = 0xFFFFFFFF & 0;
    rgIDT[u32Num].u8TypeAttribute = u8TypeAttribute;
    rgIDT[u32Num].u16HigherOffset = 0xFFFF & (u32Offset >> 16); // 16 - 31
}

void fnInitaliseIDT(void)
{
    // Exceptions
    fnSetIDTEntry(0x00, (uint32_t)fnExceptionHandler0, 0x08, 0b11101111);
    fnSetIDTEntry(0x01, (uint32_t)fnExceptionHandler1, 0x08, 0b11101111);
    fnSetIDTEntry(0x02, (uint32_t)fnExceptionHandler2, 0x08, 0b11101111);
    fnSetIDTEntry(0x03, (uint32_t)fnExceptionHandler3, 0x08, 0b11101111);
    fnSetIDTEntry(0x04, (uint32_t)fnExceptionHandler4, 0x08, 0b11101111);
    fnSetIDTEntry(0x05, (uint32_t)fnExceptionHandler5, 0x08, 0b11101111);
    fnSetIDTEntry(0x06, (uint32_t)fnExceptionHandler6, 0x08, 0b11101111);
    fnSetIDTEntry(0x07, (uint32_t)fnExceptionHandler7, 0x08, 0b11101111);
    fnSetIDTEntry(0x08, (uint32_t)fnExceptionHandler8, 0x08, 0b11101111);
    fnSetIDTEntry(0x09, (uint32_t)fnExceptionHandler9, 0x08, 0b11101111);
    fnSetIDTEntry(0x0A, (uint32_t)fnExceptionHandler10, 0x08, 0b11101111);
    fnSetIDTEntry(0x0C, (uint32_t)fnExceptionHandler11, 0x08, 0b11101111);
    fnSetIDTEntry(0x0D, (uint32_t)fnExceptionHandler12, 0x08, 0b11101111);
    fnSetIDTEntry(0x0B, (uint32_t)fnExceptionHandler13, 0x08, 0b11101111);
    fnSetIDTEntry(0x0E, (uint32_t)fnExceptionHandler14, 0x08, 0b11101111);
    fnSetIDTEntry(0x0F, (uint32_t)fnExceptionHandler15, 0x08, 0b11101111);
    fnSetIDTEntry(0x10, (uint32_t)fnExceptionHandler16, 0x08, 0b11101111);
    fnSetIDTEntry(0x11, (uint32_t)fnExceptionHandler17, 0x08, 0b11101111);
    fnSetIDTEntry(0x12, (uint32_t)fnExceptionHandler18, 0x08, 0b11101111);
    fnSetIDTEntry(0x13, (uint32_t)fnExceptionHandler19, 0x08, 0b11101111);
    fnSetIDTEntry(0x14, (uint32_t)fnExceptionHandler20, 0x08, 0b11101111);
    fnSetIDTEntry(0x15, (uint32_t)fnExceptionHandler21, 0x08, 0b11101111);

    // Reserved
    fnSetIDTEntry(0x16, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x17, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x18, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x19, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1A, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1B, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1C, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1D, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1E, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);
    fnSetIDTEntry(0x1F, (uint32_t)fnExceptionHandler22, 0x08, 0b11101111);

    // User Defined Interrupts (PIC)
    fnSetIDTEntry(0x20, (uint32_t)fnInterruptHandler32, 0x08, 0b11101110);
    fnSetIDTEntry(0x21, (uint32_t)fnInterruptHandler33, 0x08, 0b11101110);
    fnSetIDTEntry(0x22, (uint32_t)fnInterruptHandler34, 0x08, 0b11101110);
    fnSetIDTEntry(0x23, (uint32_t)fnInterruptHandler35, 0x08, 0b11101110);
    fnSetIDTEntry(0x24, (uint32_t)fnInterruptHandler36, 0x08, 0b11101110);
    fnSetIDTEntry(0x25, (uint32_t)fnInterruptHandler37, 0x08, 0b11101110);
    fnSetIDTEntry(0x26, (uint32_t)fnInterruptHandler38, 0x08, 0b11101110);
    fnSetIDTEntry(0x27, (uint32_t)fnInterruptHandler39, 0x08, 0b11101110);
    fnSetIDTEntry(0x28, (uint32_t)fnInterruptHandler40, 0x08, 0b11101110);
    fnSetIDTEntry(0x29, (uint32_t)fnInterruptHandler41, 0x08, 0b11101110);
    fnSetIDTEntry(0x2B, (uint32_t)fnInterruptHandler42, 0x08, 0b11101110);
    fnSetIDTEntry(0x2C, (uint32_t)fnInterruptHandler43, 0x08, 0b11101110);
    fnSetIDTEntry(0x2A, (uint32_t)fnInterruptHandler44, 0x08, 0b11101110);
    fnSetIDTEntry(0x2D, (uint32_t)fnInterruptHandler45, 0x08, 0b11101110);
    fnSetIDTEntry(0x2E, (uint32_t)fnInterruptHandler46, 0x08, 0b11101110);

    fnSetIDT((uint32_t)&rgIDT, sizeof(SIDT_Descriptor) * 256 - 1);
}