#ifndef TESOS_TIMER_H
#define TESOS_TIMER_H

#include "./task.h"
#include <stdint.h>

typedef struct IretStack {
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t ss;
} IretStack;

void on_timer_interrupt();
void setup_timer(uint32_t hz, Task *task1, Task *task2);

#endif //TESOS_TIMER_H
