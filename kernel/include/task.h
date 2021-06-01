#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct STask
{
	char *szName;
	uint32_t *pu32ESP;
} STask;

STask *fnCreateNewTask(char *szName, int(*fnFunc)());

#endif