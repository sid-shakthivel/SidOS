#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/string.h"

size_t strlen(uint8_t *string)
{
    size_t i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    return i;
}