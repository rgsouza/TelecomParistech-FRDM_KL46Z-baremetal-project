#include"buttons.h"
#include"gpio_registers.h"
#include"sim_registers.h"
#include"port_registers.h"
#include"irq.h"
#include"led.h"

void button_init( void )
{
	//Active l'horloge du port C
	SIM_SCGC5 |= (0x1 << 11);
	
	// Configure la broche en mode GPIO avec pull-up et interruption sur front descendant.
	PORTC_PCR3 = 0xA0103;
	
	// Configure la broche 3 en mode entrée.
	GPIOC_PDDR &= ~(0x1 << 3);

	// Active l'interruption du Port C: PORTCD_IRQHandler
	irq_enable( 31 );	
}

void PORTCD_IRQHandler()
{
	// Met interrupt Status Flag à 1 ( clear the flag ).
	PORTC_PCR3 |= ( 0x1 << 24);
	
	// Toggle la led rouge.	
	led_r_toggle();	
}

