#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/timer.h"
#include "../include/io.h"
#include "../include/pic.h"
#include "../include/vga_text.h"

uint32_t timer_ticks = 0;

void setup_timer(uint32_t hz)
{
	hz = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, hz & 0xFF);
	outb(0x40, hz >> 8);
}

void on_timer_interrupt(void)
{
	timer_ticks += 1;
	if (timer_ticks % 100 == 0) {
//		printf("1 SECOND HAS PASSED\n");
// TODO: Call scheduler to switch tasks
	}
}