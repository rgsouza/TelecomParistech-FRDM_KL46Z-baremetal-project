// Auteur Rayanne Goncalves

#ifndef UART_REGISTRES_H
#define UART_REGISTRES_H

#include<stdint.h>

#define UART0_C4  ( *(volatile uint8_t*) 0x4006A00A )
#define UART0_BDH ( *(volatile uint8_t*) 0x4006A000 )
#define UART0_BDL ( *(volatile uint8_t*) 0x4006A001 )
#define UART0_C1 ( *(volatile uint8_t*) 0x4006A002 )
#define UART0_C2 ( *(volatile uint8_t*) 0x4006A003 )
#define UART0_C3 ( *(volatile uint8_t*) 0x4006A006 )
#define UART0_S1 ( *(volatile uint8_t*) 0x4006A004 )
#define UART0_S2 ( *(volatile uint8_t*) 0x4006A005 )
#define UART0_D ( *(volatile uint8_t*) 0x4006A007 )



#endif
