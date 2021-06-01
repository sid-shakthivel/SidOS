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

int test_func()
{
	printf("TEST\n");
	while (true)
	{
		//		Do stuff
	}
	return 0;
}

int best_func()
{
	printf("BEST\n");
	while (true)
	{
		//		Do stuff
	}
	return 0;
}

void kernel_main(multiboot_info_t *pMBD)
{
	fnInitaliseTerminal();
	fnInitialiseSerial(PORT);
	fnInitialiseGDT();
	fnInitaliseIDT();
	fnInitialisePIC();
	uint32_t u32StartOfMemory = fnInitialisePaging();

	fnInitialisePageFrameAllocator(u32StartOfMemory, fnCalculateMaximumMemory(pMBD));

	STask *pTaskOne = fnCreateNewTask("Task 1", test_func);
	STask *pTaskTwo = fnCreateNewTask("Task 2", best_func);

	fnSetupTimter(100, pTaskOne, pTaskTwo);

	fnClearMaskOfIRQ(0x00);

	printf("WILL THIS GET CALLED?\n");
}