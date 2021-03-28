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
extern void best();

#define PORT 0x3f8 // COM1

void kernel_main(multiboot_info_t *mbd)
{
    initialize_terminal();
    initialize_serial(PORT);
    initialize_gdt();
    initialize_idt();
    initialize_pic();
    initialize_paging(__kernel_end, calculate_max_memory(mbd));

    size_t *test = allocate_page();
    printf("TEST = %d\n", test);

    // free_page(test);

    size_t *best = allocate_page();
    printf("BEST = %d\n", best);

    clear_mask_IRQ(0x01);
}