#include"led_matrix.h"
#include"port_registers.h"
#include"sim_registers.h"

extern char  _binary_image_raw_start;
volatile unsigned char frame[ 192 ] = {0};
volatile unsigned int row_matrix = 0;

// Reçoit 0 ou 1 comme paramètre et met la broche RST respectivement à 0 ou à 1.
static void RST( int x );

// Met tous les bits de bank0 à 1.
static void init_bank0();

void matrix_init()
{
	// Active les horloges A, B, C et D.
	SIM_SCGC5 |= ( (0x1 << 9) | (0x1 << 10) | (0x1 << 11) | (0x1 << 12) );
	
	// Configure des broches du port B en mode GPIO.
	PORTB_PCR0 = 0x100;
	PORTB_PCR1 = 0x100;
	PORTB_PCR2 = 0x100;

	// Configure des broches du port C en mode GPIO.
	PORTC_PCR8 = 0x100;
	PORTC_PCR9 = 0x100;
	
	// Configure des broches du port D en mode GPIO.
	PORTD_PCR2 = 0x100;
	PORTD_PCR4 = 0x100;
	PORTD_PCR6 = 0x100;
	PORTD_PCR7 = 0x100;
	PORTD_PCR5 = 0x100;

	// Configure des broches du port A en mode GPIO.
	PORTA_PCR4 = 0x100;
	PORTA_PCR12 = 0x100;
	PORTA_PCR13 = 0x100;

	// Met PSO à 0 afin de ne pas changer l'état des broches.
	GPIOA_PSOR = 0;
	GPIOB_PSOR = 0;
	GPIOC_PSOR = 0;
	GPIOD_PSOR = 0;

	// Met PCOR à 0 afin de ne pas changer l'état des broches.
	GPIOA_PCOR = 0;
	GPIOB_PCOR = 0;
	GPIOC_PCOR = 0;
	GPIOD_PCOR = 0;

	// Configure des broches du port B en sortie.
	GPIOB_PDDR = 0x7;

	// Configure des broches du port C en sortie.
	GPIOC_PDDR = 0x300;
	
	// Configure des broches du port D en sortie.
	GPIOD_PDDR = 0xF4;	

	// Configure des broches du porte A en sortie.
	GPIOA_PDDR = 0x3010;


	RST(0);
	LAT(1);
	SB(1);
	SCK(0);
	SDA(0);

	ROW0(0);
	ROW1(0);
	ROW2(0);
	ROW3(0);
	ROW4(0);
	ROW5(0);
	ROW6(0);
	ROW7(0);
	
	// Attend 125ms 
	sleep( 3000000 );

	RST(1);

	// Envoie 1 à tous bits du bank0.
	init_bank0();		
}


static void RST( int x )
{
	if( x == 1 )
		GPIOB_PSOR = (0x1 << 2);

	else if ( x == 0)
		GPIOB_PCOR = (0x1 << 2);
}
		
void deactivate_rows()
{
	// Eteint toutes les lignes.
	ROW0( 0 );
	ROW1( 0 );
	ROW2( 0 );
	ROW3( 0 );
	ROW4( 0 );
	ROW5( 0 );
	ROW6( 0 );
	ROW7( 0 );
}

void activate_row( int row )
{
	switch( row )
	{
		case 1:
			ROW1( 1 );
			break;
		case 2: 
			ROW2( 1 );
			break;
		case 3:
			ROW3( 1 );
			break;
		case 4: 
			ROW4( 1 );
			break;
		case 5:
			ROW5( 1 );
			break;
		case 6: 
			ROW6( 1 );
			break;
		case 7:
			ROW7( 1 );
			break;
		case 0:
			ROW0( 1 );
			break;
		default:
			break;
	}
}

void send_byte( uint8_t val , int bank )
{
	int i = 7;

	if ( bank == 1)
	{	// Met SB à 1 afin d'utiliser le BANK 1.
		SB ( 1 );
	}
	
	else if ( bank == 0)
	{	// Met SB à 0 afin d'utiliser le BANK 0.
		SB( 0 );	
	}
	else 	// afin de ne pas entrer dans la boucle.
		i = -4;
	
	for( ; i >= 0; i-- )
	{
		if( ( val & (0x1 << i) ) )
			SDA( 1 );
		else
			SDA( 0 );
		
		
		// pulse positif.
		pulse_SCK();	
	}
	
}

void mat_set_row( int row, const rgb_color *val )
{
	for( int i = 7; i >= 0; i--)
	{
		send_byte( val[i].b, 1 );
		send_byte( val[i].g, 1 );
		send_byte( val[i].r, 1 );
	}
	
	deactivate_rows();	
	pulse_LAT();
	// Active la rangée correspondante.
	activate_row( row );


}

static void init_bank0()
{
	uint8_t val = 0xFF;
		
	// Envoie 144 bits au bank0.
	for( int i = 0; i < 18; i++)
		send_byte( val, 0);	
	
	pulse_LAT();
}

void test_pixels()
{
	
	rgb_color color_gradient[ 6 ][ 8 ];
	
	
	for( int i = 0; i < 8; i++)
	{
		//  rouge
		color_gradient[ 0 ][ i ].r = 255;
		color_gradient[ 0 ][ i ].g = 0;
		color_gradient[ 0 ][ i ].b = 0;

		// Degradé rouge
		color_gradient[ 1 ][ i ].r = 255;
		color_gradient[ 1 ][ i ].g = i*200;
		color_gradient[ 1 ][ i ].b = i*10;

		// vert
		color_gradient[ 2 ][ i ].r = 0;
		color_gradient[ 2 ][ i ].g = 255;
		color_gradient[ 2 ][ i ].b = 0;

		// Dégradé vert
		color_gradient[ 3 ][ i ].r = i*5;
		color_gradient[ 3 ][ i ].g = 255;
		color_gradient[ 3 ][ i ].b = i*10;

		// bleu
		color_gradient[ 4 ][ i ].r = 0;
		color_gradient[ 4 ][ i ].g = 0;
		color_gradient[ 4 ][ i ].b = 255;

		// Dégradé bleu
		color_gradient[ 5 ][ i ].r = i*10;
		color_gradient[ 5 ][ i ].g = i*20;
		color_gradient[ 5 ][ i ].b = 255;
	}
	
	
	for( int i = 0; i < 3; i++)
	{	
		
		for ( int i = 0; i < 8; i++)
		{
			// Ligne avec la couleur rouge.
			mat_set_row( i, color_gradient[ 0 ] );
				sleep (9000000);

			// Ligne avec la couleur vert.
			mat_set_row( i, color_gradient[ 2 ] );
				sleep (9000000);

			// Ligne avec la couleur bleu.
			mat_set_row( i, color_gradient[ 4 ] );
				sleep (9000000);

			// Ligne avec un dégradé rouge.
			mat_set_row( i, color_gradient[ 1 ] );
				sleep (9000000);

			// Ligne avec un dégradé vert.
			mat_set_row( i, color_gradient[ 3 ] );
				sleep (9000000);
	
			// Ligne avec un dégradé bleu.
			mat_set_row( i, color_gradient[ 5 ] );
				sleep (9000000);
		}
	}
} 

void test_static_image()
{
	int i = 1000;
	while( i-- )
	{	char *pimage = &_binary_image_raw_start;	
	
		for ( int row = 0; row < 8; row++ )
		{	// Commence par la valeur bleu de la denière colonne de la matrix led et transmet une ligne complete.
			for(int i = 23; i >= 0 ; i--)
				send_byte( *(pimage + i), 1 );
			
			// adresse de la prochaine ligne.
			pimage += 24;
			deactivate_rows();
			//attente ~4.33 microseconde.
               		sleep(104);
			pulse_LAT();
			activate_row( row );
		}
	}
}

void display_image()
{

	for( int row = 0; row < 8; row++ )
	{	// Commence par la valeur bleu de la denière colonne de la matrix led et transmet une ligne complete.
		for( int i = 23; i >= 0; i--)
			send_byte( frame[ 24*row + i  ], 1);
		 
		deactivate_rows();
		//attente ~4.33 microseconde.
		sleep(104);
		pulse_LAT();
		activate_row( row );				
	}		
}

void display_line()
{
	// Commence par la valeur bleu de la denière colonne de la matrix led et transmet une ligne complete.
	for( int i = 23; i >= 0; i--)
                        send_byte( frame[ 24*row_matrix + i  ], 1);

	deactivate_rows();
        //attente ~4.33 microseconde.
	sleep(104);
        pulse_LAT();
	activate_row( row_matrix );

}

void sleep ( int time )
{
	for( int i = 0; i < time; i++ )
		asm volatile ("nop");
}
