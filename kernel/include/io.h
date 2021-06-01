#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void fnOutB(uint16_t u16Port, uint8_t u8Value);
uint8_t fnInB(uint16_t u16Port);

#endif