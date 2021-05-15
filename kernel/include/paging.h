#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "multiboot.h"

size_t initialize_paging();
size_t calculate_max_memory(multiboot_info_t *mbd);