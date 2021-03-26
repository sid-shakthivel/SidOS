#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/io.h"
#include "../include/pic.h"
#include "../include/vga_text.h"

bool bshift = false;

char kbd_US[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', /* <-- Tab */
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, /* <-- control key */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*',
        0,   /* Option */
        ' ', /* Space bar */
};

char get_key(unsigned char scancode)
{
    unsigned char character = 0;

    character = bshift ? (kbd_US[scancode] - 32) : kbd_US[scancode];

    if (bshift)
    {
        switch (scancode)
        {
        case 0x27:
            return ':';
        case 0x28:
            return '"';
        case 0x29:
            return '|';
        case 0x33:
            return '<';
        case 0x34:
            return '>';
        case 0x35:
            return '?';
        case 0x1A:
            return '{';
        case 0x1B:
            return '}';
        }
    }

    if (scancode == 0x2A || scancode == 0x36 || scancode == 0x3A || scancode == 0x0E)
    {
        bshift = true;
        return 0;
    }

    return character;
}

void on_keyboard_interrupt()
{
    unsigned char scancode = inb(0x60);

    if (scancode == 0xAA || scancode == 0xBA || scancode == 0xB6)
        bshift = false;

    if (scancode == 0x0E)
        delete_character();

    if (scancode < 0x81)
    {
        print_character(get_key(scancode));
    }
}