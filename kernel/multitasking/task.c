#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/task.h"
#include "../include/page_frame_allocator.h"
#include "../include/string.h"
#include "../include/vga_text.h"

typedef struct task
{
    char *name;
    uint32_t *stack_pointer;
} Task;

uint32_t *create_task(char *name)
{
    Task *new_task = (Task *)allocate_page();
    strcpy(new_task->name, name);

    // Stack will be 1 page
    new_task->stack_pointer = (uint32_t *)allocate_page() + 1023;

    printf("\nSTACK IS AT %x\n", new_task->stack_pointer);
    return 0;
}