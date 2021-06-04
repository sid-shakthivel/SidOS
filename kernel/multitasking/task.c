#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/task.h"
#include "../include/page_frame_allocator.h"
#include "../include/string.h"
#include "../include/vga_text.h"

STask *fnCreateNewTask(char *szName, int(*fnFunc)())
{
	printf("SIZE OF TASK IS %x\n", sizeof(STask));
	STask *pNewTask = (STask *)fnAllocPage();
	pNewTask->szName = szName;

	uint32_t *pu32ESP = (uint32_t *)fnAllocPage() + 512;
	pNewTask->pu32ESP = (uint32_t *)pu32ESP - 14;

	//	IRET Stuff
	*(--pu32ESP) = 0; // Stack Alignment
	*(--pu32ESP) = 0x10; // SS
	*(--pu32ESP) = (uint32_t)pNewTask->pu32ESP; // ESP
	*(--pu32ESP) = 0x202; // EFLAGS
	*(--pu32ESP) = 0x8; // CS
	*(--pu32ESP) = (uint32_t) fnFunc; // EIP

//	General Registers
	*(--pu32ESP) = 0; // EAX
	*(--pu32ESP) = 0; // ECX
	*(--pu32ESP) = 0; // EDX
	*(--pu32ESP) = 0; // EBX
	*(--pu32ESP) = 0; // ESP
	*(--pu32ESP) = (uint32_t)pNewTask->pu32ESP; // EBP
	*(--pu32ESP) = 0; // ESI
	*(--pu32ESP) = 0; // EDI

	return pNewTask;
}



