#ifndef PIC_H
#define PIC_H

void initialize_pic(void);
void send_PIC_acknowledgment(uint8_t irq);
void clear_mask_IRQ(uint32_t irq);
void mask_IRQ(uint32_t irq);

#endif