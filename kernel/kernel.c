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
#include "include/filesystem.h"

#define PORT 0x3f8 // COM1

int fnTestFunc()
{
	printf("TEST\n");
	fnExit();
	return 0;
}

int fnBestFunc()
{
	printf("BEST\n");
	fnExit();
	return 0;
}

void fnKernelMain(multiboot_info_t *pMBD)
{
	fnInitialiseTerminal();
	fnInitialiseSerial(PORT);
	fnInitialiseGDT();
	fnInitaliseIDT();
	fnInitialisePIC();

	multiboot_module_t *pGrubModule = (multiboot_module_t *)pMBD->mods_addr;
	uint32_t pModuleStartAddress = (uint32_t)pGrubModule->mod_start;

	uint32_t u32SizeOfTarBall = fnCalculateEndOfTarball(pModuleStartAddress) - pModuleStartAddress;

	memcpy((char *)5283840, (char *)pModuleStartAddress, u32SizeOfTarBall);

	fnCalculateEndOfTarball(5283840);

	uint32_t u32StartOfMemory = fnInitialisePaging(u32SizeOfTarBall);

	fnInitialisePageFrameAllocator(u32StartOfMemory, fnCalculateMaximumMemory(pMBD));

	fnInitialiseFilesystem();

	printf("IN %s: %s and %s\n", pRootFolder->szFormattedFilename, pRootFolder->pNextHeader[0]->szFormattedFilename, pRootFolder->pNextHeader[1]->szFormattedFilename);

	fnInitialiseTasks();

	fnSetupTimer(100);

	//  fnClearMaskOfIRQ(0x00);

	STask *pTaskOne = fnCreateNewTask("Task 1", fnTestFunc);
	STask *pTaskTwo = fnCreateNewTask("Task 2", fnBestFunc);

	pTaskOne = pTaskOne;
	pTaskTwo = pTaskTwo;
}
