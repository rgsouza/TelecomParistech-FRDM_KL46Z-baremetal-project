#include"uart.h"
#include"uart_registers.h"
#include"sim_registers.h"
#include"irq.h"
#include"port_registers.h"
#include"led_matrix.h"

void uart_init()
{
	// Active l'horloge UART0.
	SIM_SCGC4 |= (0x1 << 10);

	// Emetteur et recepteur desactives.
	UART0_C2 = 0;
	
	// Active interruption pour la reception.		
	UART0_C2 |= (0x1 << 5);

	// Selectionne l'horloge MCGPLLCLK/2.
	SIM_SOPT2 =( (SIM_SOPT2 | (0x1 << 26)) & (~(0x1 << 27)));

	// Selectionne l'horloge MCGPLLCLK/2 dans le champs PLLFLLSEL.
	SIM_SOPT2 |= (0x1 << 16);

	// Configure a 8 bits de donnees et sans parite.
	UART0_C1 = 0;

	// Configurations recommendees afin d'eviter un comportement inattendu
	UART0_C3 = 0;
	UART0_S2 |= 0xC0;

	// Met FE, NF et OR à 0
	UART0_S1 = 0xFF;
		
	// Oversampling à 24
	UART0_C4 = 0x18;

	// 1 bit de stop
	UART0_BDH = 0;

	// La valeur de SBR 25
	UART0_BDL = 0x19;
	
		
	// Active la porte A
	SIM_SCGC5 |= (0x1 << 9);
	
	// Broche Rx passe au mode  UART0 
	SIM_SOPT5 &= ~(0x1 << 2);

	// Selectionne l'alternative MUX PTA1 (RX)
	PORTA_PCR1 = 0x200;

	// Selectionne l'alternaive 2 dans MUX de PTA2 (TX).
	PORTA_PCR2 = 0x200;
	
	// Broche Tx passe au mode UART0
	SIM_SOPT5 &= ~ ( 0x1 | (0x1 << 1));
	
	// Active recepteur et emetteur
	UART0_C2 |= ( (0x1 << 2) | (0x1 << 3) );

	// Lecture du buffer.
	UART0_D;

	// Active l'interruption du UART0.
	irq_enable( 12 );
}

void uart_putchar( char c)
{
	// Attend que le buffer UART0_D soit vide.
	while ( !( UART0_S1 & (0x1 << 7)));

	UART0_D = c;	

}

unsigned char uart_getchar()
{
	// Attend que le buffer UART_D soit plein.
	while( !(UART0_S1 & (0x1 << 5)) );	
	
	// Teste le flag FE.
	if( (UART0_S1 & (0x1 << 1) ))
		while(1);

	// Teste le flag OR.
	if( (UART0_S1 & (0x1 << 3)) )
		while(1);

	return UART0_D;	
}

void uart_puts( const char *s )
{
	int i = 0;
	while ( s[i] )
	{	
		uart_putchar( s[i] );
		i++;
	}
	uart_putchar('\n');
}

void uart_gets( char *s, int size )
{						
	int i = 0;	
	for ( ; i  < (size - 1); i++ )
	{
		s[i] = uart_getchar();
		if( s[i] == '\n' )
		{	
			i++;
			break;
		}
	}	
	s[i] = '\0';
}


uint32_t uart_sum_bytes( uint8_t *vbytes, int size )
{
	uint32_t sum = 0;
	
	for( int i = 0; i < size; i++)
	{
		vbytes[i] = (uint8_t)uart_getchar();
		sum += vbytes[i];
	} 


	return sum;

}

// Represent l'indice courant du vecteur de pixels frame.
static int index = 0;
static int uart_error = 0;

void UART0_IRQHandler ( )
{
	unsigned char  auxiliary = UART0_D;

	// Signale un erreur si la flag OR ou FE est 1.	
	if( (UART0_S1 & 0x2) || (UART0_S1 & 0x8) )
	{
		uart_error = 1;
		UART0_S1 |= (0x2 | 0x8);
	}

	else
	{	// Verifie si est une nouvelle trame.
		if ( auxiliary == 255 ) 
		{	uart_error = 0;
			index= 0;
		}
		else if ( !uart_error )
		{	frame[ index ] = auxiliary;		
			index++;
		}	
	}
}

