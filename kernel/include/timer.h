#ifndef TESOS_TIMER_H
#define TESOS_TIMER_H

#include "./task.h"
#include <stdint.h>

void on_timer_interrupt(uint32_t ebp, uint32_t esp, uint32_t flags);
void setup_timer(uint32_t hz, Task *task1, Task *task2);

#endif //TESOS_TIMER_H
