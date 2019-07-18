// Auteur Rayanne Goncalves
// Main de teste pour la partie final.

#include"led_matrix.h"
#include"buttons.h"
#include"irq.h"
#include"led.h"
#include"uart.h"
#include"pit.h"
#include"mcg.h"


int main()
{
	clocks_init();	
	irq_init();
	led_init();
	led_r_off();
	reset_config_led_g();
	uart_init();
	matrix_init();
	button_init();
	pit_init();
	
	return 0;
}
