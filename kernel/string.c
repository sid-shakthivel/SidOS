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

bool strcmp(char *pcStringOne, char *pcStringTwo) {
	uint32_t u32LengthOfStringOne = strlen(pcStringOne);
	uint32_t u32LengthOfStringTwo = strlen(pcStringTwo);

	if (u32LengthOfStringOne != u32LengthOfStringTwo) {
		return false;
	}

	for (uint32_t i = 0; i < u32LengthOfStringOne; i++) {
		if (pcStringOne[i] != pcStringTwo[i]) {
			return false;
		}
	}

	return true;
}

// src, dest
void strcpy(char *pcStringOne, char *pcStringTwo, uint32_t u32Size) {
	for (uint32_t i = 0; i < u32Size; i++) {
		pcStringTwo[i] = pcStringOne[i];
	}
}