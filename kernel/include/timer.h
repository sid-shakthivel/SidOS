#ifndef TESOS_TIMER_H
#define TESOS_TIMER_H

#include "./task.h"
#include <stdint.h>

void fnSetupTimer(uint32_t u32Hertz);

extern STask *pOldTask;

#endif //TESOS_TIMER_H
