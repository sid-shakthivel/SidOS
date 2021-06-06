#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/string.h"
#include "../include/uart.h"
#include "../include/io.h"

uint32_t ku32Port = 0;

int fnIsTransmitEmpty(void)
{
    return fnInB(ku32Port + 5) & 0x20;
}

void fnWriteSerial(uint8_t u8a)
{
    while (fnIsTransmitEmpty() == 0)
        ;

    fnOutB(ku32Port, u8a);
}

void fnWriteStringToSerial(char *szString)
{
    uint32_t u32Length = strlen(szString);

    for (uint32_t i = 0; i < u32Length; i++)
    {
        fnWriteSerial(szString[i]);
    }
}

void fnInitialiseSerial(uint32_t u32Port)
{
    ku32Port = u32Port;

    fnOutB(ku32Port + 1, 0x00); // Disable all interrupts
    fnOutB(ku32Port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    fnOutB(ku32Port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    fnOutB(ku32Port + 1, 0x00); //                  (hi byte)
    fnOutB(ku32Port + 3, 0x03); // 8 bits, no parity, one stop bit
    fnOutB(ku32Port + 4, 0x0B); // IRQs enabled, RTS/DSR set
}
