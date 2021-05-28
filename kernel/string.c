#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/string.h"
#include "include/vga_text.h"

uint32_t strlen(uint8_t *string)
{
    uint32_t i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    return i;
}