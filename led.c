#include"led.h"
#include"sim_registers.h"
#include"port_registers.h"
#include"gpio_registers.h"

void led_init()
{
	// Active les horloges des ports D et E.
	SIM_SCGC5 = (0x1 << 12) | SIM_SCGC5;
	SIM_SCGC5 = (0x1 << 13) | SIM_SCGC5;

	// Configure en mode GPIO.
	PORTD_PCR5 = 0x100;
	PORTE_PCR29 = 0x100;
	
	// Configure en mode sortie.
	GPIOE_PDDR |= (0x1 << 29);
	GPIOD_PDDR |= (0x1 << 5);
	
	// Il met les broches a l'etat bas afin d'allumer les LEDs. 
	GPIOD_PCOR = (0x1 << 5);
	GPIOE_PCOR = (0x1 << 29);
		
}

void reset_config_led_g()
{
	// Configuration reset pour utilisation de la broche PCR5 par la matrice LED.
	PORTD_PCR5 = 0;
	GPIOD_PDDR &= ~(0x1 << 5);
}
void led_r_on()
{
	// Modifie PDOR à 0 afin de mettre la broche 29 à l'état bas pour allumer la led rouge.
	GPIOE_PCOR = (0x1 << 29);
}

void led_r_off()
{
	// Modifie PDOR à 1 afin de mettre la broche 29 à l'état haut pour éteindre la led rouge.
	GPIOE_PSOR = (0x1 << 29); 
}

void led_r_toggle()
{
	// Inverse l'état courant de PDOR afin d'inverser l'état courant de la broche 29.
	GPIOE_PTOR = (0x1 << 29);	
}

void led_g_on()
{
	// Modifie PDOR à 0 afin de mettre la broche 5 à l'état bas pour allumer la led verte. 
	GPIOD_PCOR = (0x1 << 5);
}

void led_g_off()
{
	// Modifie PDOR à 1 afin de mettre la broche 5 à l'état haut pour éteindre la led verte.
	GPIOD_PSOR = (0x1 << 5);
}

void led_g_toggle()
{
	// Inverse l'état courant de PDOR afin d'inverser l'état courant de la broche 5.
	GPIOD_PTOR = (0x1 << 5);	
}

