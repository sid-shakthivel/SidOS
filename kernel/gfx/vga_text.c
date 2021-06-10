#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/uart.h"
#include "../include/string.h"

#define VGA_HEIGHT 25
#define VGA_WIDTH 80

uint16_t *pu16TerminalBuffer;

uint32_t u32TerminalColumn = 0;
uint32_t u32TerminalRow = 0;

uint8_t rgcHexArray[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

enum VGAColour
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void fnPrintCharacter(uint8_t u8Character);
uint32_t fnPrintNumber(uint32_t u32Number, uint32_t u32NumericBase);
void fnDeleteCharacter(void);
uint8_t fnColourFormat(enum VGAColour BackgroundColour, enum VGAColour ForegroundColour);
uint16_t fnVGAEntry(uint8_t u8Letter, uint8_t u8Colours);

void fnInitaliseTerminal(void)
{
    pu16TerminalBuffer = (uint16_t *)0xB8000;

    uint8_t u8Colour = fnColourFormat(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    for (uint32_t x = 0; x < VGA_WIDTH; x++)
    {
        for (uint32_t y = 0; y < VGA_HEIGHT; y++)
        {
            const uint32_t u32Index = y * VGA_WIDTH + x;
            pu16TerminalBuffer[u32Index] = fnVGAEntry(' ', u8Colour);
        }
    }
}

void printf(char *szString, ...)
{
    va_list valist;

    char *pcCharacter;

    va_start(valist, szString);

    for (pcCharacter = szString; *pcCharacter; pcCharacter++)
    {
        if (*pcCharacter != '%')
        {
            fnPrintCharacter(*pcCharacter);
            continue;
        }

        switch (*++pcCharacter)
        {
        	case 'o':
				fnPrintNumber(va_arg(valist, uint32_t), 8);
				break;
        	case 's':
				printf(va_arg(valist, char *));
				break;
			case 'd':
				fnPrintNumber(va_arg(valist, uint32_t), 10);
				break;
			case 'x':
				fnPrintCharacter('0');
				fnPrintCharacter('x');
				fnPrintNumber(va_arg(valist, uint32_t), 16);
				break;
        }
    }

    va_end(valist);
}

void fnPrintCharacter(uint8_t u8Character)
{
    if ((u8Character == 0))
        return;

    if (u8Character == '\n')
    {
        u32TerminalRow += 1;
        u32TerminalColumn = 0;
        return;
    }

    const uint32_t u32Index = u32TerminalRow * VGA_WIDTH + u32TerminalColumn;
    pu16TerminalBuffer[u32Index] = fnVGAEntry(u8Character, fnColourFormat(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

    u32TerminalColumn++;

    if (u32TerminalColumn >= VGA_WIDTH)
    {
        u32TerminalRow += 1;
        u32TerminalColumn = 0;
    }

    if (u32TerminalRow >= VGA_HEIGHT)
    {
        for (uint32_t x = 0; x < VGA_WIDTH; x++)
        {
            for (uint32_t y = 0; y <= VGA_HEIGHT; y++)
            {
                pu16TerminalBuffer[y * VGA_WIDTH + x] = pu16TerminalBuffer[(y + 2) * VGA_WIDTH + x];
            }
        }

        for (uint32_t x = 0; x < VGA_WIDTH; x++)
        {
            pu16TerminalBuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = fnVGAEntry(' ', fnColourFormat(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
        }

        u32TerminalRow = (VGA_HEIGHT - 2);

        return;
    }
}

void fnDeleteCharacter(void)
{
    u32TerminalColumn--;
    const uint32_t u32Index = u32TerminalRow * VGA_WIDTH + u32TerminalColumn;
    pu16TerminalBuffer[u32Index] = fnVGAEntry(' ', fnColourFormat(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

uint32_t fnPrintNumber(uint32_t u32Number, uint32_t u32NumericBase)
{
    uint32_t u32Digit = 0;

    if (u32Number < u32NumericBase)
    {
        if (u32NumericBase == 10)
            fnPrintCharacter(u32Number + '0');
        if (u32NumericBase == 8)
			fnPrintCharacter(u32Number + '0');
        else if (u32NumericBase == 16)
            fnPrintCharacter(rgcHexArray[u32Number]);
    }
    else
    {
        u32Digit = fnPrintNumber(u32Number / u32NumericBase, u32NumericBase);
        u32Digit = fnPrintNumber(u32Number % u32NumericBase, u32NumericBase);
    }

    return u32Digit;
}

uint8_t fnColourFormat(enum VGAColour BackgroundColour, enum VGAColour ForegroundColour)
{
    return (uint8_t)BackgroundColour | (uint8_t)ForegroundColour << 4;
}

uint16_t fnVGAEntry(uint8_t u8Letter, uint8_t u8Colours)
{
    return (uint16_t)u8Letter | (uint16_t)u8Colours << 8;
}
