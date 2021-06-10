#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

uint32_t strlen(char *szString);
bool strcmp(char *pcStringOne, char *pcStringTwo);
void strcpy(char *pcStringOne, char *pcStringTwo, uint32_t u32Size);

#endif