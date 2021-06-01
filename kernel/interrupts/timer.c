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

STask *pTaskOne;
STask *pTaskTwo;
int i = 0;

uint32_t *pCurrentStack;
uint32_t *pOldStack;
uint32_t *pNextStack;

// TODO: Fix the task1, task2 thing
void fnSetupTimter(uint32_t u32Hertz, STask *task1, STask *task2)
{
	u32Hertz = 1193180 / u32Hertz;
	fnOutB(0x43, 0x36);
	fnOutB(0x40, u32Hertz & 0xFF);
	fnOutB(0x40, u32Hertz >> 8);

	pTaskOne = task1;
	pTaskTwo = task2;
}

void fnOnTimerInterrupt(void)
{
	if (i == 0)
	{
		pNextStack = pTaskOne->pu32ESP;
	}
	else if (i == 1)
	{
		pNextStack = pTaskTwo->pu32ESP;
	}
	else
	{
		pNextStack = pOldStack;
	}

	fnSendPICAcknowledgement(0x20);
	i++;
	pOldStack = pCurrentStack;
}
