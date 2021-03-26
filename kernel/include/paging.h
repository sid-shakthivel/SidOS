#include "multiboot.h"

unsigned int calculate_max_memory(multiboot_info_t *mbd);
void initialize_paging(int start_memory_location, int final_memory_location);
int *allocate_page();
void free_page(int *memory_location_pointer);