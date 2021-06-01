#ifndef IDT_H
#define IDT_H

typedef struct SIDT_Descriptor
{
	uint16_t u16LowerOffset;
	uint16_t u16Selector;
	uint8_t u8Zero;
	uint8_t u8TypeAttribute;
	uint16_t u16HigherOffset;
} SIDT_Descriptor;

void fnInitaliseIDT(void);

#endif