#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/gdt.h"
#include "../include/vga_text.h"

extern void fnSetGDT(uint32_t base, uint16_t limit);

typedef struct SGDTDescriptor
{
    uint16_t u16LowerLimit;
    uint16_t u16LowerBase;
    uint8_t u8MiddleBase;
    uint8_t u8AccessByte;
    uint8_t u8Granularity;
    uint8_t u8UpperBase;
} SGDTDescriptor;

SGDTDescriptor rgGDT[5];

void fnSetGDTEntry(uint32_t u32Num, uint32_t u32base, uint32_t u32Limit, uint8_t u8AccessByte, uint8_t u8Granularity)
{
	rgGDT[u32Num].u16LowerLimit = (0x0000FFFF & u32Limit);
	rgGDT[u32Num].u16LowerBase = 0x0000FFFF & u32base;
	rgGDT[u32Num].u8MiddleBase = 0x00FF0000 & u32base;
	rgGDT[u32Num].u8AccessByte = u8AccessByte & 0xFFFF;
	rgGDT[u32Num].u8Granularity = (u32Limit >> 16) & 0x0F;
	rgGDT[u32Num].u8Granularity |= u8Granularity & 0xF0;
	rgGDT[u32Num].u8UpperBase = 0xFF000000 & u32base;
}

void fnInitialiseGDT(void)
{
	fnSetGDTEntry(0, 0, 0, 0, 0);                // Null Descriptor
	fnSetGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code Entry (kernel)
	fnSetGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data Entry (kernel mode)
	fnSetGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Code Entry (user mode)
	fnSetGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Data Entry (user mode)

	fnSetGDT((uint32_t)&rgGDT, (sizeof(SGDTDescriptor) * 5) - 1);
}