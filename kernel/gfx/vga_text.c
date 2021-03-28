#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/uart.h"
#include "../include/string.h"

#define VGA_HEIGHT 25
#define VGA_WIDTH 80

uint16_t *terminal_buffer;

size_t terminal_col = 0;
size_t terminal_row = 0;

uint8_t hex_array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

enum vga_color
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

void print_character(uint8_t character);
size_t print_numeric_character(size_t numberic_character, size_t numberic_base);
void delete_character(void);
uint8_t colour_format(enum vga_color background_colour, enum vga_color foreground_colour);
uint16_t vga_entry(uint8_t letter, uint8_t colours);

void initialize_terminal(void)
{
    terminal_buffer = (uint16_t *)0xB8000;

    uint8_t colour = colour_format(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        for (size_t y = 0; y < VGA_HEIGHT; y++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', colour);
        }
    }
}

void printf(char *string, ...)
{
    va_list valist;

    char *p;

    va_start(valist, string);

    for (p = string; *p; p++)
    {
        if (*p != '%')
        {
            print_character(*p);
            continue;
        }

        switch (*++p)
        {
        case 'd':
            print_numeric_character(va_arg(valist, size_t), 10);
            break;
        case 'x':
            print_character('0');
            print_character('x');
            print_numeric_character(va_arg(valist, size_t), 16);
            break;
        }
    }

    va_end(valist);
}

void print_character(uint8_t character)
{
    if ((character == 0))
        return;

    if (character == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    const size_t index = terminal_row * VGA_WIDTH + terminal_col;
    terminal_buffer[index] = vga_entry(character, colour_format(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

    terminal_col++;

    if (terminal_col >= VGA_WIDTH)
    {
        terminal_row += 1;
        terminal_col = 0;
    }

    if (terminal_row >= VGA_HEIGHT)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            for (size_t y = 0; y <= VGA_HEIGHT; y++)
            {
                terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 2) * VGA_WIDTH + x];
            }
        }

        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', colour_format(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
        }

        terminal_row = (VGA_HEIGHT - 2);

        return;
    }
}

void delete_character(void)
{
    terminal_col--;
    const size_t index = terminal_row * VGA_WIDTH + terminal_col;
    terminal_buffer[index] = vga_entry(' ', colour_format(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

size_t print_numeric_character(size_t numberic_character, size_t numberic_base)
{
    size_t digit = 0;

    if (numberic_character < numberic_base)
    {
        if (numberic_base == 10)
            print_character(numberic_character + '0');
        else if (numberic_base == 16)
            print_character(hex_array[numberic_character]);
    }
    else
    {
        digit = print_numeric_character(numberic_character / numberic_base, numberic_base);
        digit = print_numeric_character(numberic_character % numberic_base, numberic_base);
    }

    return digit;
}

uint8_t colour_format(enum vga_color background_colour, enum vga_color foreground_colour)
{
    return (uint8_t)background_colour | (uint8_t)foreground_colour << 4;
}

uint16_t vga_entry(uint8_t letter, uint8_t colours)
{
    return (uint16_t)letter | (uint16_t)colours << 8;
}
