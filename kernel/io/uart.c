#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/uart.h"
#include "../include/io.h"

int PORT = 0;

int is_transmit_empty()
{
    return inb(PORT + 5) & 0x20;
}

void write_serial(char a)
{
    while (is_transmit_empty() == 0)
        ;

    outb(PORT, a);
}

void write_string_to_serial(char *string)
{
    unsigned int i = 0;
    unsigned int length = strlen(string);

    for (i = 0; i < length; i++)
    {
        write_serial(string[i]);
    }
}

void initialize_serial(int port)
{
    PORT = port;

    outb(PORT + 1, 0x00); // Disable all interrupts
    outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00); //                  (hi byte)
    outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}
