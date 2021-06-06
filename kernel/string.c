#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/string.h"
#include "include/vga_text.h"

uint32_t strlen(char *szString)
{
    uint32_t i = 0;
    while (szString[i] != '\0')
    {
        i++;
    }
    return i;
}

bool strcmp(char *szStringOne, char *szStringTwo) {
	uint32_t u32LengthOfStringOne = strlen(szStringOne);
	uint32_t u32LengthOfStringTwo = strlen(szStringTwo);

	if (u32LengthOfStringOne != u32LengthOfStringTwo) {
		return false;
	}

	for (uint32_t i = 0; i < u32LengthOfStringOne; i++) {
		if (szStringOne[i] != szStringTwo[i]) {
			return false;
		}
	}

	return true;
}