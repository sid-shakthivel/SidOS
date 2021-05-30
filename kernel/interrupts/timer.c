#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/timer.h"
#include "../include/io.h"
#include "../include/pic.h"
#include "../include/vga_text.h"
#include "../include/task.h"
#include "../include/pic.h"

uint32_t timer_ticks = 0;

Task *task_one;
Task *task_two;
int i = 0;

extern void save_stack();

uint32_t *stack_one;
uint32_t *stack_two;

void setup_timer(uint32_t hz, Task *task1, Task *task2)
{
	hz = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, hz & 0xFF);
	outb(0x40, hz >> 8);

	task_one = task1;
	task_two = task2;
}

void on_timer_interrupt() {
	printf("HERE\n");
	if (i == 0) {
		stack_two = task_one->esp;
	} else if (i % 2 == 0) {
		stack_one = task_one->esp;
		stack_two = task_two->esp;
		save_stack();
	} else {
		stack_one = task_one->esp;
		stack_two = task_two->esp;
		save_stack();
	}

	send_PIC_acknowledgment(0x20);
	i++;
}

// Stack One always pushes
// Stack Two always pops