#ifndef PIC_H
#define PIC_H

void fnInitialisePIC(void);
void fnSendPICAcknowledgement(uint8_t u8IRQ);
void fnClearMaskOfIRQ(uint32_t u32IRQ);
void fnMaskIRQ(uint32_t u32IRQ);

#endif