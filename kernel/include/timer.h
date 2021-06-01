#ifndef TESOS_TIMER_H
#define TESOS_TIMER_H

#include "./task.h"
#include <stdint.h>

void fnSetupTimter(uint32_t u32Hertz, STask *task1, STask *task2);

#endif //TESOS_TIMER_H
