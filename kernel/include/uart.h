#ifndef UART_H
#define UART_H

void initialize_serial(uint32_t port);
void write_string_to_serial(uint8_t *string);

#endif