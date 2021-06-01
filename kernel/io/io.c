#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/io.h"

void fnOutB(uint16_t u16Port, uint8_t u8Value)
{
    asm volatile("out %0, %1"
                 :
                 : "a"(u8Value), "Nd"(u16Port));
}

uint8_t fnInB(uint16_t u16Port)
{
    uint8_t u8Result;
    asm volatile("inb %1, %0"
                 : "=a"(u8Result)
                 : "Nd"(u16Port));
    return u8Result;
}
