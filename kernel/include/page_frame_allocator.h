#ifndef PAGE_FRAME_ALLOCATOR_H
#define PAGE_FRAME_ALLOCATOR_H

void initialize_page_frame_allocator(size_t start_memory_location, size_t final_memory_location);
size_t *allocate_page(void);
void free_page(size_t *memory_location_pointer);

#endif