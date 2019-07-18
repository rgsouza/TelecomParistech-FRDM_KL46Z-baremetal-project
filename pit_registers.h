#ifndef PIT_REGISTERS_H
#define PIT_REGISTERS_H

#define PIT_MCR (*(volatile uint32_t*) 0x40037000 )
#define PIT_TCTRL0 (*(volatile uint32_t*) 0x40037108 )
#define PIT_LDVAL0 (*(volatile uint32_t*) 0x40037100 )
#define PIT_TFLG0 (*(volatile uint32_t*) 0x4003710C )


#endif
