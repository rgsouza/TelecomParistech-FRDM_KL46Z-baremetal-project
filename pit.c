#include"pit.h"
#include"irq.h"
#include"led.h"
#include"sim_registers.h"
#include"pit_registers.h"
#include"led_matrix.h"

void pit_init()
{
	// Active horloge de PIT.
	SIM_SCGC6 |= (0x1 << 23);

	// Active PIT.
	PIT_MCR = 0x0;

	// Valeur correspondant à l'affichage de la trame en 80 fois par seconde.
	PIT_LDVAL0 = 0x927B;

	// Efface le flag d'interruption.
	PIT_TFLG0 = 0x1;

	// Active l'interruption du PIT.	
	irq_enable(22);
	
	// Active Timer Interrupt et le start timer (TEN)
        PIT_TCTRL0 = 0x3;
}

// Compteur qui permettre savoir quand basculer la led rouge.
static unsigned int times_led = 1;

void PIT_IRQHandler()
{
	if ( times_led == 640 ) 
	{	times_led = 1;
		// Toggle la led rouge.
       		led_r_toggle();
	}
	times_led++;
	// Mise à jour de la ligne à être affichée par display_ligne().
        if ( row_matrix < 8 )
                row_matrix++;
	else  row_matrix = 0;

        // Deactive TEN afin de recommencer le compteur.
        PIT_TCTRL0 &= ~(0x1);

        // Affiche une ligne sur la matrice de leds.
        display_line();

        // Efface le flag d'interruption.
        PIT_TFLG0 = 0x1;
	
	// Recommence le compteur.
        PIT_TCTRL0 |= (0x1);
}	
