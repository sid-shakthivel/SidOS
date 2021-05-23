#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

uint32_t strlen(uint8_t *string);
void strcpy(char *dest, char *src);

#endif