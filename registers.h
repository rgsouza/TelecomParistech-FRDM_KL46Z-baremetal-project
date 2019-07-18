// Auteur Rayanne Goncalves
// registers.h contient des registres mappes en memoire d'utilisation usuelle. 

#ifndef REGISTERS_H
#define REGISTERS_H

#include<stdint.h>

// Registre qui permet d'activer et desactiver les portes A, B, C, D et E. 
#define SIM_SCGC5 (*( volatile uint32_t* ) 0x40048038 )
#define SIM_SCGC4 ( *(volatile uint32_t*) 0x40048034 )
#define SIM_SOPT2 ( *(volatile uint32_t*) 0x40048004 )
#define SIM_SOPT5 ( *(volatile uint32_t*) 0x40048010 )
#define PORTA_PCR1 ( *(volatile uint32_t*) 0x40049004 )
#define PORTA_PCR2 ( *(volatile uint32_t*) 0x40049008 )
#define GPIOC_PDDR ( *(volatile uint32_t*) 0x400FF094 )
#define PORTD_PCR5 (*( volatile uint32_t* ) 0x4004C014 )
#define GPIOD_PDDR (*( volatile uint32_t* ) 0x400FF0D4 )
#define GPIOD_PSOR (*( volatile uint32_t* ) 0x400FF0C4 ) 
#define GPIOD_PCOR (*( volatile uint32_t* ) 0x400FF0C8 )


#endif
