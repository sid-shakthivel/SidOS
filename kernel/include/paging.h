#include "multiboot.h"

size_t calculate_max_memory(multiboot_info_t *mbd);
void initialize_paging(size_t start_memory_location, size_t final_memory_location);
size_t *allocate_page(void);
void free_page(size_t *memory_location_pointer);