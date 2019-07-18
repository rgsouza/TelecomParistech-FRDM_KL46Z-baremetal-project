// Autheur Rayanne Goncalves

#ifndef UART_H
#define UART_H
#include<stdint.h>

// Active l'horloge UART0 et configure la transmission à 8 bits de donnée,
// pas de parité, 1 bit de stop et 115200bps.
void uart_init();

// L'UART transmet le caractere passe comme parametre.  
void uart_putchar(char c);

// Retourne un caractere trasmis a l'UART.
unsigned char uart_getchar();

// L'UART transmet la chaine de caractere passee comme parametre en appelant
// la fonction uart_putchar. Cette fonction transmet un '\n' au fin de la transmission
// de la chaine. 
void uart_puts( const char*s );

// Cette fonction place dans le vecteur s la chaine de caractere transmise a l'UART.
// La transmission de chaque caractere de la chaine a l'UART s'arrete si un '\n'
// est transmit ou si la taille maximale (size - 1) est atteinte. Un caracter nul 
// '\0' est place a la fin de la chaine. 
void uart_gets( char *s, int size );

uint32_t uart_sum_bytes( uint8_t *vbytes, int size );

#endif
