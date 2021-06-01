#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/task.h"
#include "../include/page_frame_allocator.h"
#include "../include/string.h"
#include "../include/vga_text.h"

void Task1Func() {
	printf("HELLO THERE\n");
	while (true) {
//		Do stuff
	}
}
Task *create_task(char *name, int(*func)())
{
	Task *new_task = (Task *)allocate_page();
	new_task->name = name;

//	printf("TASK1FUNC IS %x\n", (uint32_t) &Task1Func);
	uint32_t *esp = (uint32_t *)allocate_page() + 512;
	uint32_t *top_of_stack = esp;
	printf("TOP OF STACK IS %x\n", top_of_stack);
	new_task->esp = (uint32_t *)esp - 14;

	//	IRET Stuff
	*(--esp) = 0; // Stack Alignment
	*(--esp) = 0x10; // SS
	*(--esp) = (uint32_t)new_task->esp; // ESP
	*(--esp) = 0x202; // EFLAGS
	*(--esp) = 0x8; // CS
	*(--esp) = (uint32_t) func; // EIP

//	General Registers
	*(--esp) = 0; // EAX
	*(--esp) = 0; // ECX
	*(--esp) = 0; // EDX
	*(--esp) = 0; // EBX
	*(--esp) = 0; // ESP
	*(--esp) = (uint32_t)new_task->esp; // EBP
	*(--esp) = 0; // ESI
	*(--esp) = 0; // EDI

	// Set func to func
	new_task->func = func;

	return new_task;
}

void list_stack(uint32_t* esp) {
	uint32_t *thingy = (uint32_t *) esp + 20;
	for (uint32_t* i = esp; i < thingy; i++) {
		printf("%x = %x\n", i, *i);
	}
}

void clear_stack(uint32_t *esp) {
	uint32_t *thingy = (uint32_t *) esp + 20;
	for (uint32_t *i = esp; i < thingy; i++) {
		*i = 0;
	}
}

