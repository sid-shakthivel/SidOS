#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga_text.h"
#include "../include/keyboard.h"
#include "../include/pic.h"
#include "../include/timer.h"

char *rgszExceptions[31] = {"One Cannot Divide 0 By 0\n", "Single-step interrupt\n", "NMI\n", "Breakpoint\n", "Overflow\n", "Bounds\n", "Invalid Opcode\n", "Coprocessor Not Available\n", "Double Fault\n", "Coprocessor Segment Overrun\n", "Invalid Task State Segment\n", "Segment Not Present\n", "Stack Fault\n", "General Protection Fault\n", "Page fault\n", "Reserved\n", "Math Fault\n", "Alignment Check\n", "Machine Check\n", "SIMD Floating-Point Exception\n", "Virtualisation Exception\n", "Control Protection Exception\n"};

typedef struct SRegisters
{
	uint32_t EDI;
	uint32_t ESI;
	uint32_t EBP;
	uint32_t ESP;
	uint32_t EBX;
	uint32_t EDX;
	uint32_t ECX;
	uint32_t EAX;
} SRegisters;

void fnPrintRegisters(SRegisters Registers)
{
	printf("Registers:\n");
	printf("EDI IS %x\n", Registers.EDI);
	printf("ESI IS %x\n", Registers.ESI);
	printf("EBP IS %x\n", Registers.EBP);
	printf("ESP IS %x\n", Registers.ESP);
	printf("EBX IS %x\n", Registers.EBX);
	printf("EDX IS %x\n", Registers.EDX);
	printf("ECX IS %x\n", Registers.ECX);
	printf("EAX IS %x\n", Registers.EAX);
}

void fnOnGenericException(SRegisters Registers, uint32_t u32IRQNumber)
{
	u32IRQNumber > 0x15 ? printf("Intel Reserved\n") : printf(rgszExceptions[u32IRQNumber]);
	Registers = Registers;
	// print_registers(registers_t);
}

void fnOnGenericInterrupt(SRegisters Registers, uint32_t u32IRQNumber)
{
	switch (u32IRQNumber)
	{
	case 0x20:
		//		on_timer_interrupt();
		break;
	case 0x21:
		fnOnKeyboardInterrupt();
		break;
	default:
		printf("Unknown Interrupt\n");
		break;
	}

	Registers = Registers;

	fnSendPICAcknowledgement(u32IRQNumber);
}