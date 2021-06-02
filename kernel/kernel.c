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

int fnTestFunc()
{
	printf("TEST\n");
	while (true)
	{
		//		Do stuff
	}
	return 0;
}

int fnBestFunc()
{
	printf("BEST\n");
	while (true)
	{
		//		Do stuff
	}
	return 0;
}

void fnKernelMain(multiboot_info_t *pMBD)
{
	fnInitaliseTerminal();
	fnInitialiseSerial(PORT);
	fnInitialiseGDT();
	fnInitaliseIDT();
	fnInitialisePIC();
	uint32_t u32StartOfMemory = fnInitialisePaging();

	fnInitialisePageFrameAllocator(u32StartOfMemory, fnCalculateMaximumMemory(pMBD));

	STask *pTaskOne = fnCreateNewTask("Task 1", fnTestFunc);
	STask *pTaskTwo = fnCreateNewTask("Task 2", fnBestFunc);

	fnSetupTimter(100, pTaskOne, pTaskTwo);

	fnClearMaskOfIRQ(0x00);

	printf("WILL THIS GET CALLED?\n");
}