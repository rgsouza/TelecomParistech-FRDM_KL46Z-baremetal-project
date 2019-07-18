// Auteur Rayanne GOncalves
// Ce fichier contient des registres mappés en mémoire des ports A,B,C,D et E.
#ifndef PORT_REGISTRES_H
#define PORT_REGISTRES_H
#include<stdint.h>

#define PORTA_PCR1 ( *(volatile uint32_t*) 0x40049004 )
#define PORTA_PCR2 ( *(volatile uint32_t*) 0x40049008 )
#define PORTC_PCR3 (*(volatile uint32_t*) 0x4004B00C )
#define PORTB_PCR0 ( *(volatile uint32_t*) 0x4004A000 )
#define PORTB_PCR1 ( *(volatile uint32_t*) 0x4004A004 )
#define PORTB_PCR2 ( *(volatile uint32_t*) 0x4004A008 )
#define PORTC_PCR8 ( *(volatile uint32_t*) 0x4004B020 )
#define PORTC_PCR9 ( *(volatile uint32_t*) 0x4004B024 )
#define PORTD_PCR2 ( *(volatile uint32_t*) 0x4004C008 )
#define PORTD_PCR4 ( *(volatile uint32_t*) 0x4004C010 )
#define PORTD_PCR5 (*( volatile uint32_t* ) 0x4004C014 )
#define PORTD_PCR6 ( *(volatile uint32_t*) 0x4004C018 )
#define PORTD_PCR7 ( *(volatile uint32_t*) 0x4004C01C )
#define PORTA_PCR4 ( *(volatile uint32_t*) 0x40049010 )
#define PORTA_PCR12 ( *(volatile uint32_t*) 0x40049030 )
#define PORTA_PCR13 ( *(volatile uint32_t*) 0x40049034 )
#define PORTE_PCR29 (*( volatile uint32_t* ) 0x4004D074 )


#endif
