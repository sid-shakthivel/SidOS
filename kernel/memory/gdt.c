#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/gdt.h"
#include "../include/vga_text.h"

extern void setGdt(uint32_t base, uint16_t limit);

struct gdt_descriptor
{
    uint16_t lower_limit;
    uint16_t lower_base;
    uint8_t middle_base;
    uint8_t access_byte;
    uint8_t granularity;
    uint8_t upper_base;
};

struct gdt_descriptor gdt[5];

void set_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t granularity)
{
    gdt[num].lower_limit = (0x0000FFFF & limit);
    gdt[num].lower_base = 0x0000FFFF & base;
    gdt[num].middle_base = 0x00FF0000 & base;
    gdt[num].access_byte = access_byte & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].upper_base = 0xFF000000 & base;
}

void initialize_gdt()
{
    set_gdt_entry(0, 0, 0, 0, 0);                // Null Descriptor
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code Entry (kernel)
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data Entry (kernel mode)
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Code Entry (user mode)
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Data Entry (user mode)
    // // Add a TSS later (when I know what one is

    setGdt((uint32_t)&gdt, (sizeof(struct gdt_descriptor) * 5) - 1);
}