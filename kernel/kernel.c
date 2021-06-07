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
#include "include/memory.h"
#include "include/string.h"

#define PORT 0x3f8 // COM1

int fnTestFunc()
{
	printf("TEST\n");
		pOldTask->szStatus = "STOP";
		asm volatile ("int $0x20");
	return 0;
}

int fnBestFunc()
{
	printf("BEST\n");
	pOldTask->szStatus = "STOP";
	asm volatile ("int $0x20");
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

	fnInitialiseTasks();

	STask *pTaskOne = fnCreateNewTask("Task 1", fnTestFunc);
	STask *pTaskTwo = fnCreateNewTask("Task 2", fnBestFunc);

	fnSetupTimer(100);

	fnClearMaskOfIRQ(0x00);

	printf("DOES EXECUTION REACH HERE?\n");
}