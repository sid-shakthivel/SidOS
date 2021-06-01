#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/string.h"
#include "include/vga_text.h"

uint32_t strlen(uint8_t *szString)
{
    uint32_t i = 0;
    while (szString[i] != '\0')
    {
        i++;
    }
    return i;
}