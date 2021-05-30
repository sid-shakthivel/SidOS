#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task
{
	char *name;
	int (*func)(void);
	uint32_t *esp;
} Task;

Task *create_task(char *name, int(*func)());

void list_stack(uint32_t* stack);

#endif