#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/timer.h"
#include "../include/io.h"
#include "../include/pic.h"
#include "../include/vga_text.h"
#include "../include/task.h"
#include "../include/pic.h"
#include "../include/memory.h"
#include "../include/string.h"

uint32_t *pSavedStack;
uint32_t *pNextStack;

uint32_t *pSavedKernelStackESP;

STask *pOldTask;

void fnSetupTimer(uint32_t u32Hertz)
{
	u32Hertz = 1193180 / u32Hertz;
	fnOutB(0x43, 0x36);
	fnOutB(0x40, u32Hertz & 0xFF);
	fnOutB(0x40, u32Hertz >> 8);
}

void fnOnTimerInterrupt(void)
{
	STask *pTask = fnReturnNewTask();

	if(pOldTask != NULL) {
		pOldTask->pu32ESP = pSavedStack;
	} else {
		printf("SAVING KERNEL STACK\n");
		pSavedKernelStackESP = pSavedStack;
	}

	pNextStack = pTask->pu32ESP;
	pOldTask = pTask;

	fnSendPICAcknowledgement(0x20);
}
