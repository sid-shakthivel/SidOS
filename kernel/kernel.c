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
#include "include/page_frame_allocator.h"
#include "include/paging.h"

extern void best();

#define PORT 0x3f8 // COM1

void kernel_main(multiboot_info_t *mbd)
{
    initialize_terminal();
    initialize_serial(PORT);
    initialize_gdt();
    initialize_idt();
    initialize_pic();
	size_t start_of_memory = initialize_paging(calculate_max_memory(mbd));
	initialize_page_frame_allocator(start_of_memory, calculate_max_memory(mbd));

//    clear_mask_IRQ(0x01);
//    clear_mask_IRQ(0x21);
//
//	size_t *test = allocate_page();
//	printf("TEST = %d\n", test);
//
//	 free_page(test);
//
//	size_t *best = allocate_page();
//	printf("BEST = %d\n", best);
//
//	clear_mask_IRQ(0x01);
//
//    for (;;)
//    {
//        asm("hlt");
//    }
}