#ifndef PAGE_FRAME_ALLOCATOR_H
#define PAGE_FRAME_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void initialize_page_frame_allocator(uint32_t start_memory_location, uint32_t final_memory_location);
uint32_t *allocate_page(void);
void free_page(uint32_t *memory_location_pointer);

#endif