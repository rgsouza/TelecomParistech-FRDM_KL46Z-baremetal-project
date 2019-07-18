#ifndef IRQ_H
#define IRQ_H
#include<stdint.h>

// Active toutes interruptions.
#define enable_irq() asm ("cpsie i")

// Desactive toutes interruptions.
#define disable_irq() asm ("cpsid i")

// Stocke l'adresse de la table de vecteurs d'interruption dans VTOR.
void irq_init( void );

// Active les interruptions externes en considérant le nùmero fourni.  
void irq_enable( int irq_number );

// Desactive les interruptions externes en considérant le nùmero fourni.
void irq_disable( int irq_number );


#endif
