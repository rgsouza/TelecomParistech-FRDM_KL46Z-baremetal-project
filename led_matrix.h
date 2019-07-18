// Auteur Rayanne Goncalves

#ifndef LED_MATRIX_H
#define LED_MATRIX_H
#include<stdint.h>
#include"gpio_registers.h"


typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} rgb_color;

// vecteur utilisé dans l'interruption du UART0.
extern volatile unsigned char frame [];

// Variable utilisée dans l'interruption pit.
extern volatile unsigned int row_matrix;

// Active les horloges des ports A,B,C et D.
// Configure des broches de ces ports en mode GPIO et en sortie.
// Initialise les sorties en mettant RST, SCK, SDA à 0 et LAT, SB à 1 et en éteignant toutes les lignes.
// Fait un appel à la fonction init_bank0. 
void matrix_init();

// Reçoit 0 ou 1 comme paramètre et met la broche SB respectivement à 0 ou à 1.
static inline void SB( int x )
{
        if( x == 1 )  
		GPIOB_PSOR = 0x01;

        else if ( x == 0 )
                GPIOB_PCOR = 0x01;
}

// Reçoit 0 ou 1 comme paramètre et met la broche LAT respectivement à 0 ou à 1.
static inline void LAT( int x )
{
        if( x == 1 )
                GPIOB_PSOR = (0x1 << 1);

        else if ( x == 0 )
                GPIOB_PCOR = (0x1 << 1);
}

// Reçoit 0 ou 1 comme paramètre et met la broche SCK respectivement à 0 ou à 1.
static inline void SCK( int x )
{
        if( x == 1 )
                GPIOC_PSOR = (0x1 << 8);

        else if( x == 0)
                GPIOC_PCOR = (0x1 << 8);
}

// Reçoit 0 ou 1 comme paramètre et met la broche SDA respectivement à 0 ou à 1.
static inline void SDA( int x )
{
        if( x == 1)
                GPIOC_PSOR = (0x1 << 9);

        else if( x == 0)
                GPIOC_PCOR = (0x1 << 9);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 0 est activée, si 0 elle est désactivée.
static inline void ROW0( int x )
{
        if( x == 1)
                GPIOA_PSOR = (0x1 << 13);

        else if( x == 0)
                GPIOA_PCOR = (0x1 << 13);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 1 est activée, si 0 elle est désactivée.
static inline void ROW1( int x )
{
        if( x == 1)
                GPIOD_PSOR = (0x1 << 2);

        else if( x == 0 )
                GPIOD_PCOR = (0x1 << 2);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 2 est activée, si 0 elle est désactivée.
static inline void ROW2( int x )
{
        if( x == 1)
                GPIOD_PSOR = (0x1 << 4);

        else if( x == 0)
                GPIOD_PCOR = (0x1 << 4);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 3 est activée, si 0 elle est désactivée.
static inline void ROW3( int x )
{
        if( x == 1 )
                GPIOD_PSOR = (0x1 << 6);

        else if( x == 0)
                GPIOD_PCOR = (0x1 << 6);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 4 est activée, si 0 elle est désactivée.
static inline void ROW4( int x )
{
        if( x == 1 )
                GPIOD_PSOR = (0x1 << 7);

        else if( x == 0)
                GPIOD_PCOR = (0x1 << 7);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 5 est activée, si 0 elle est désactivée.
static inline void ROW5( int x )
{
        if( x == 1)
                GPIOD_PSOR = (0x1 << 5);

        else if( x == 0)
                GPIOD_PCOR = (0x1 << 5);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 6 est activée, si 0 elle est désactivée.
static inline void ROW6( int x )
{
        if( x == 1 )
                GPIOA_PSOR = (0x1 << 12);

        else if( x == 0)
                GPIOA_PCOR = (0x1 << 12);
}

// Reçoit 0 ou 1 comme paramètre. Si 1 la ligne 7 est activée, si 0 elle est désactivée.
static inline void ROW7( int x )
{
        if( x == 1)
                GPIOA_PSOR = (0x1 << 4);

        else if( x == 0)
                GPIOA_PCOR = (0x1 << 4);
}

// Forme un pulse positif.
static inline void pulse_SCK()
{
        SCK( 0 );
	// ~42 ns
        asm volatile ("nop");
        SCK( 1 );
	// ~42 ns
        asm volatile ("nop");
        SCK( 0 );
	// ~42 ns
        asm volatile ("nop");
}

// Forme un pulse négatif.
static inline void pulse_LAT()
{
        LAT( 1 );
	// ~ 42 ns
    	asm volatile ("nop");
	LAT( 0 );
	// ~42 ns
        asm volatile ("nop");
	LAT( 1 );
	// ~42 ns
        asm volatile ("nop");
}

// Désactive toutes les lignes ( 0 à 7 ) de la matrice de LED.
void deactivate_rows();

// Reçoit un entière entre 0 et 7 en représentant la ligne à être activée et active cette ligne.
void active_row( int row );

// Reçoit un paramètre appelé val qui contient une valeur à être transmise au bank0 si le paramètre 
// bank vaut 0 ou au bank1 si ce paramètre vaut 1.
void send_byte( uint8_t val , int bank );

// Reçoit comme paramètre un tableau de 8 pixels, envoie ce tableau au bank1 et active la ligne reçue 
// à travers du paramètre row.
void mat_set_row( int row, const rgb_color *val );

// Allume chaque ligne avec une couleur rouge, vert, bleu, dégradé rouge, vert et bleu.
void test_pixels();

// Allume chaque ligne de la matrice LED en utilisant les valeurs de pixels obtenu à partir de 
//image.raw. 
void test_static_image();

// Affiche l'image de la trame courante stockée dans la matrice frame.
void display_image();

// Affiche une line en considerant sa valeur qui est mise à jour par l'interruption pit.
void display_line();

// Reçoit comme paramètre le nombre de fois à appeler l'instruction nop et appelle cette instruction
// dans une boucle.
void sleep( int time );


#endif
