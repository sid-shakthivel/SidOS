#ifndef TESOS_MEMORY_H
#define TESOS_MEMORY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

uint32_t *malloc(uint32_t u32Size);
void free(uint32_t *pNode);
void fnPrintFreeList();

#endif //TESOS_MEMORY_H
