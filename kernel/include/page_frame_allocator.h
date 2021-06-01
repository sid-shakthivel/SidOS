#ifndef PAGE_FRAME_ALLOCATOR_H
#define PAGE_FRAME_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void fnInitialisePageFrameAllocator(uint32_t u32StartOfMemory, uint32_t u32EndOfMemory);
uint32_t *fnAllocPage(void);
void fnFreePage(uint32_t *pu32PageFrameAddress);

#endif