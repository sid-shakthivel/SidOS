#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/task.h"
#include "../include/page_frame_allocator.h"
#include "../include/string.h"
#include "../include/vga_text.h"

Task *create_task(char *name, int(*func)())
{
    Task *new_task = (Task *)allocate_page();
	new_task->name = name;

    // Stack will be 1 page
    new_task->stack_pointer = (uint32_t *)allocate_page() + 1023;

	// Set func to func
	new_task->func = func;

//	printf("ADDRESS IS %x\n", new_task);
    return new_task;
}
