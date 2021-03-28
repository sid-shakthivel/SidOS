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

void initialize_pic(void)
{
    outb(PIC1, ICW1); // Initialises PICS
    outb(PIC2, ICW1);

    outb((PIC1 + 1), 0x20); // Offset PICS
    outb((PIC2 + 1), 0x28);

    outb((PIC1 + 1), 4); // tell Master PIC that there is a slave PIC
    outb((PIC2 + 1), 2); // tell Slave PIC its cascade identity

    outb((PIC1 + 1), ICW4_8086);
    outb((PIC2 + 1), ICW4_8086);

    outb((PIC1 + 1), 0xFF);
    outb((PIC2 + 1), 0xFF);
    asm("sti");
}

void send_PIC_acknowledgment(uint8_t irq)
{
    if (irq >= 0x28)
    {
        outb((PIC2), 0x20);
    }
    outb((PIC1), 0x20);
}

void clear_mask_IRQ(size_t irq)
{
    if (irq < 0x08)
    {
        outb((PIC1 + 1), inb((PIC1 + 1)) & ~(1 << irq));
    }
    else
    {
        outb((PIC2 + 1), inb(PIC2 + 1) & (1 << (irq - 8)));
    }
}

void mask_IRQ(size_t irq)
{
    if (irq < 0x08)
    {
        outb((PIC1 + 1), inb(PIC1 + 1) & (1 << irq));
    }
    else
    {
        outb((PIC2 + 1), inb(PIC2 + 1) & (1 << irq));
    }
}