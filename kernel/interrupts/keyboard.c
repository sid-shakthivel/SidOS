#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/io.h"
#include "../include/pic.h"
#include "../include/vga_text.h"

bool bShift = false;

uint8_t rgcUSKeyboard[128] =
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

uint8_t fnGetKey(uint8_t u8Scancode)
{
    uint8_t u8Character = 0;

    u8Character = bShift ? (rgcUSKeyboard[u8Scancode] - 32) : rgcUSKeyboard[u8Character];

    if (bShift)
    {
        switch (u8Scancode)
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

    if (u8Scancode == 0x2A || u8Scancode == 0x36 || u8Scancode == 0x3A || u8Scancode == 0x0E)
    {
        bShift = true;
        return 0;
    }

    return u8Character;
}

void fnOnKeyboardInterrupt(void)
{
    uint8_t u8Scancode = fnInB(0x60);

    if (u8Scancode == 0xAA || u8Scancode == 0xBA || u8Scancode == 0xB6)
        bShift = false;

    if (u8Scancode == 0x0E)
        fnDeleteCharacter();

    if (u8Scancode < 0x81)
    {
        fnPrintCharacter(fnGetKey(u8Scancode));
    }
}
