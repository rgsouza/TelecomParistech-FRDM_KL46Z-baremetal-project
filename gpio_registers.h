// Auteur Rayanne Goncalves
#ifndef GPIO_REGISTERS_H
#define GPIO_REGISTERS_H

#include<stdint.h>

#define GPIOC_PDDR ( *(volatile uint32_t*) 0x400FF094 )
#define GPIOD_PDDR (*( volatile uint32_t* ) 0x400FF0D4 )
#define GPIOD_PSOR (*( volatile uint32_t* ) 0x400FF0C4 )
#define GPIOD_PCOR (*( volatile uint32_t* ) 0x400FF0C8 )
#define GPIOA_PDDR ( *(volatile uint32_t*) 0x400FF014 )
#define GPIOA_PSOR ( *(volatile uint32_t*) 0x400FF004 )
#define GPIOA_PCOR ( *(volatile uint32_t*) 0x400FF008 )
#define GPIOB_PDDR ( *(volatile uint32_t*) 0x400FF054 )
#define GPIOB_PSOR ( *(volatile uint32_t*) 0x400FF044 )
#define GPIOB_PCOR ( *(volatile uint32_t*) 0x400FF048 )
#define GPIOC_PSOR ( *(volatile uint32_t*) 0x400FF084 )
#define GPIOC_PCOR ( *(volatile uint32_t*) 0x400FF088 )
#define GPIOE_PDDR (*( volatile uint32_t* ) 0x400FF114 )
#define GPIOE_PSOR (*( volatile uint32_t* ) 0x400FF104 )
#define GPIOD_PDOR (*( volatile uint32_t* ) 0x400FF0C0 )
#define GPIOE_PDOR (*( volatile uint32_t* ) 0x400FF100 )
#define GPIOE_PCOR (*( volatile uint32_t* ) 0x400FF108 )
#define GPIOD_PTOR (*( volatile uint32_t* ) 0x400FF0CC )
#define GPIOE_PTOR (*( volatile uint32_t* ) 0x400FF10C )

#endif
