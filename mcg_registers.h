// Auteur Rayanne Goncalves
#ifndef MCG_REGISTERS_H
#define MCG_REGISTERS_H

#include<stdint.h>

#define MCG_C2 ( *(volatile uint8_t*) 0x40064001 )
#define MCG_C1 ( *(volatile uint8_t*) 0x40064000 )
#define MCG_S  ( *(volatile uint8_t*) 0x40064006 )
#define MCG_C5 ( *(volatile uint8_t*) 0x40064004 )
#define MCG_C6 ( *(volatile uint8_t*) 0x40064005 )

#endif
