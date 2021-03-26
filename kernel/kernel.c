#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/vga_text.h"
#include "include/uart.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/pic.h"
#include "include/keyboard.h"
#include "include/multiboot.h"
#include "include/paging.h"

extern uint8_t __kernel_end;

#define PORT 0x3f8 // COM1

void kernel_main(multiboot_info_t *mbd)
{
    initialize_terminal();
    initialize_serial(PORT);
    initialize_gdt();
    initialize_idt();
    initialize_pic();

    clear_mask_IRQ(0x01);

    uint32_t max_memory = calculate_max_memory(mbd);

    initialize_paging(__kernel_end, max_memory);

    int *test = allocate_page();
    printf("TEST = %d\n", test);

    *test = 5;

    printf("*TEST = %d\n", *test);
    free_page(test);

    int *best = allocate_page();

    *best = 15;

    printf("BEST = %d\n", best);
    printf("*BEST = %d\n", *best);
}
