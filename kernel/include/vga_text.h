#ifndef VGA_TEXT_H
#define VGA_TEXT_H

#include <stddef.h>

void fnInitialiseTerminal(void);
void printf(char *szString, ...);
void fnPrintCharacter(uint8_t u8Character);
void fnDeleteCharacter(void);

#endif