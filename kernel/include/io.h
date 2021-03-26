#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void outb(uint16_t port, unsigned char val);
uint8_t inb(uint16_t port);