#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task
{
	char *name;
	int (*func)(void);
	uint32_t *stack_pointer, eax, ebx, ecx, edx, esi, edi, esp, ebp, eflags;
} Task;

Task *create_task(char *name, int(*func)());

#endif