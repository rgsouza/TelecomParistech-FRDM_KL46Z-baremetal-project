// Auteur Rayanne Gonçalves
// Ce fichier contient des registres mappés en mémoire SIM.
#ifndef SIM_REGISTERS_H
#define SIM_REGISTERS_H

#include<stdint.h>

#define SIM_SCGC5 (*( volatile uint32_t* ) 0x40048038 )
#define SIM_SCGC6 (*(volatile uint32_t*) 0x4004803C )
#define SIM_SCGC4 ( *(volatile uint32_t*) 0x40048034 )
#define SIM_SOPT2 ( *(volatile uint32_t*) 0x40048004 )
#define SIM_SOPT5 ( *(volatile uint32_t*) 0x40048010 )
#define SIM_CLKDIV1 ( *(volatile uint32_t*) 0x40048044 )
#define SIM_COPC ( *(volatile uint32_t*) 0x40048100 )

#endif
