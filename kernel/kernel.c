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
#include "include/timer.h"

#define PORT 0x3f8 // COM1

extern void preserve_registers();

void kernel_main(multiboot_info_t *mbd)
{
	initialize_terminal();
	initialize_serial(PORT);
	initialize_gdt();
	initialize_idt();
	initialize_pic();
	uint32_t start_of_memory = initialize_paging();
	initialize_page_frame_allocator(start_of_memory, calculate_max_memory(mbd));
	setup_timer(100);

	clear_mask_IRQ(0x00);

//	Save those registers

	printf("THING 1\n");

//	Switch back to those registers above

	asm volatile ("int $0x20");
}