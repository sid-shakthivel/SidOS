#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/pic.h"
#include "../include/io.h"
#include "../include/vga_text.h"

#define PIC1 0x20 // Command line, 0x21 is the data line
#define PIC2 0xA0

#define ICW1 0x11

#define ICW4_8086 0x01 /* 8086/88 (MCS-80/85) mode */

void fnInitialisePIC(void)
{
    fnOutB(PIC1, ICW1); // Initialises PICS
    fnOutB(PIC2, ICW1);

    fnOutB((PIC1 + 1), 0x20); // Offset PICS
    fnOutB((PIC2 + 1), 0x28);

    fnOutB((PIC1 + 1), 4); // tell Master PIC that there is a slave PIC
    fnOutB((PIC2 + 1), 2); // tell Slave PIC its cascade identity

    fnOutB((PIC1 + 1), ICW4_8086);
    fnOutB((PIC2 + 1), ICW4_8086);

    fnOutB((PIC1 + 1), 0xFF);
    fnOutB((PIC2 + 1), 0xFF);
    asm("sti");
}

void fnSendPICAcknowledgement(uint8_t u8IRQ)
{
    if (u8IRQ >= 0x28)
    {
        fnOutB((PIC2), 0x20);
    }
    fnOutB((PIC1), 0x20);
}

void fnClearMaskOfIRQ(uint32_t u32IRQ)
{
    if (u32IRQ < 0x08)
    {
        fnOutB((PIC1 + 1), fnInB((PIC1 + 1)) & ~(1 << u32IRQ));
    }
    else
    {
        fnOutB((PIC2 + 1), fnInB(PIC2 + 1) & (1 << (u32IRQ - 8)));
    }
}

void fnMaskIRQ(uint32_t u32IRQ)
{
    if (u32IRQ < 0x08)
    {
        fnOutB((PIC1 + 1), fnInB(PIC1 + 1) & (1 << u32IRQ));
    }
    else
    {
        fnOutB((PIC2 + 1), fnInB(PIC2 + 1) & (1 << u32IRQ));
    }
}