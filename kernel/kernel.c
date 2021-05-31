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
#include "include/task.h"

#define PORT 0x3f8 // COM1

extern void stack_stuff();

int test_func() {
	printf("TEST\n");
	return 0;
}

int best_func() {
	printf("BEST\n");
	return 0;
}

void kernel_main(multiboot_info_t *mbd)
{
	initialize_terminal();
	initialize_serial(PORT);
	initialize_gdt();
	initialize_idt();
	initialize_pic();
	uint32_t start_of_memory = initialize_paging();
	initialize_page_frame_allocator(start_of_memory, calculate_max_memory(mbd));

	Task *task_1 = create_task("Task 1", test_func);
	Task *task_2 = create_task("Task 2", best_func);

	printf("TASK 1'S ESP IS %x\n", task_1->esp);

	setup_timer(100, task_1, task_2);

//	stack_stuff();
	
	clear_mask_IRQ(0x00);
}