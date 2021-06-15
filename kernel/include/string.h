#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

uint32_t strlen(char *szString);
bool strcmp(char *pcStringOne, char *pcStringTwo);
void strcpy(char *pcStringOne, char *pcStringTwo, uint32_t u32Size);
void memcpy(void *pDest, void *pSrc, uint32_t u32Limit);
void substr(char *pcDest, char *pcSrc, uint32_t u32Start, uint32_t u32End);

#endif