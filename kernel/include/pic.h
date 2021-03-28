void initialize_pic(void);
void send_PIC_acknowledgment(uint8_t irq);
void clear_mask_IRQ(size_t irq);
void mask_IRQ(size_t irq);