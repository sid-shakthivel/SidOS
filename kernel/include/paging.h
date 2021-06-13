#ifndef PAGING_H
#define PAGING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "multiboot.h"

typedef struct SMultibootSegment
{
	unsigned int uiSize;
	unsigned long long int lliAddress;
	unsigned long long int lliLength;
	unsigned int uiType;
} SMultibootSegment;

uint32_t fnInitialisePaging(uint32_t u32TarBallSize);
uint32_t fnCalculateMaximumMemory(multiboot_info_t *pMBD);

#endif