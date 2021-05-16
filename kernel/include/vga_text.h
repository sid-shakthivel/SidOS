#ifndef VGA_TEXT_H
#define VGA_TEXT_H

#include <stddef.h>

void initialize_terminal(void);
void printf(char *string, ...);
void print_character(unsigned char character);
void delete_character();

#endif